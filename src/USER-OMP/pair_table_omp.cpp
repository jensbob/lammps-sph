/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   This software is distributed under the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing author: Axel Kohlmeyer (Temple U)
------------------------------------------------------------------------- */

#include "math.h"
#include "pair_table_omp.h"
#include "atom.h"
#include "comm.h"
#include "error.h"
#include "force.h"
#include "neighbor.h"
#include "neigh_list.h"

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

PairTableOMP::PairTableOMP(LAMMPS *lmp) :
  PairTable(lmp), ThrOMP(lmp, PAIR)
{
  respa_enable = 0;
}

/* ---------------------------------------------------------------------- */

void PairTableOMP::compute(int eflag, int vflag)
{
  if (eflag || vflag) {
    ev_setup(eflag,vflag);
    ev_setup_thr(this);
  } else evflag = vflag_fdotr = 0;

  const int nall = atom->nlocal + atom->nghost;
  const int nthreads = comm->nthreads;
  const int inum = list->inum;

#if defined(_OPENMP)
#pragma omp parallel default(shared)
#endif
  {
    int ifrom, ito, tid;
    double **f;

    f = loop_setup_thr(atom->f, ifrom, ito, tid, inum, nall, nthreads);

    if (evflag) {
      if (eflag) {
	if (force->newton_pair) eval<1,1,1>(f, ifrom, ito, tid);
	else eval<1,1,0>(f, ifrom, ito, tid);
      } else {
	if (force->newton_pair) eval<1,0,1>(f, ifrom, ito, tid);
	else eval<1,0,0>(f, ifrom, ito, tid);
      }
    } else {
      if (force->newton_pair) eval<0,0,1>(f, ifrom, ito, tid);
      else eval<0,0,0>(f, ifrom, ito, tid);
    }

    // reduce per thread forces into global force array.
    data_reduce_thr(&(atom->f[0][0]), nall, nthreads, 3, tid);
  } // end of omp parallel region

  // reduce per thread energy and virial, if requested.
  if (evflag) ev_reduce_thr(this);
  if (vflag_fdotr) virial_fdotr_compute();
}

template <int EVFLAG, int EFLAG, int NEWTON_PAIR>
void PairTableOMP::eval(double **f, int iifrom, int iito, int tid)
{
  int i,j,ii,jj,jnum,itype,jtype,itable;
  double xtmp,ytmp,ztmp,delx,dely,delz,evdwl,fpair;
  double rsq,factor_lj,fraction,value,a,b;
  int *ilist,*jlist,*numneigh,**firstneigh;
  Table *tb;
  
  union_int_float_t rsq_lookup;
  int tlm1 = tablength - 1;

  evdwl = 0.0;

  double **x = atom->x;
  int *type = atom->type;
  int nlocal = atom->nlocal;
  double *special_lj = force->special_lj;
  double fxtmp,fytmp,fztmp;

  ilist = list->ilist;
  numneigh = list->numneigh;
  firstneigh = list->firstneigh;

  // loop over neighbors of my atoms

  for (ii = iifrom; ii < iito; ++ii) {

    i = ilist[ii];
    xtmp = x[i][0];
    ytmp = x[i][1];
    ztmp = x[i][2];
    itype = type[i];
    jlist = firstneigh[i];
    jnum = numneigh[i];
    fxtmp=fytmp=fztmp=0.0;

    for (jj = 0; jj < jnum; jj++) {
      j = jlist[jj];
      factor_lj = special_lj[sbmask(j)];
      j &= NEIGHMASK;

      delx = xtmp - x[j][0];
      dely = ytmp - x[j][1];
      delz = ztmp - x[j][2];
      rsq = delx*delx + dely*dely + delz*delz;
      jtype = type[j];
      
      if (rsq < cutsq[itype][jtype]) {
	tb = &tables[tabindex[itype][jtype]];
	if (rsq < tb->innersq)
	  error->one(FLERR,"Pair distance < table inner cutoff");
 
	if (tabstyle == LOOKUP) {
	  itable = static_cast<int> ((rsq - tb->innersq) * tb->invdelta);
	  if (itable >= tlm1)
	    error->one(FLERR,"Pair distance > table outer cutoff");
	  fpair = factor_lj * tb->f[itable];
	} else if (tabstyle == LINEAR) {
	  itable = static_cast<int> ((rsq - tb->innersq) * tb->invdelta);
	  if (itable >= tlm1)
	    error->one(FLERR,"Pair distance > table outer cutoff");
	  fraction = (rsq - tb->rsq[itable]) * tb->invdelta;
	  value = tb->f[itable] + fraction*tb->df[itable];
	  fpair = factor_lj * value;
	} else if (tabstyle == SPLINE) {
	  itable = static_cast<int> ((rsq - tb->innersq) * tb->invdelta);
	  if (itable >= tlm1)
	    error->one(FLERR,"Pair distance > table outer cutoff");
	  b = (rsq - tb->rsq[itable]) * tb->invdelta;
	  a = 1.0 - b;
	  value = a * tb->f[itable] + b * tb->f[itable+1] + 
	    ((a*a*a-a)*tb->f2[itable] + (b*b*b-b)*tb->f2[itable+1]) * 
            tb->deltasq6;
	  fpair = factor_lj * value;
	} else {
	  rsq_lookup.f = rsq;
	  itable = rsq_lookup.i & tb->nmask;
	  itable >>= tb->nshiftbits;
	  fraction = (rsq_lookup.f - tb->rsq[itable]) * tb->drsq[itable];
	  value = tb->f[itable] + fraction*tb->df[itable];
	  fpair = factor_lj * value;
	}

	fxtmp += delx*fpair;
	fytmp += dely*fpair;
	fztmp += delz*fpair;
	if (NEWTON_PAIR || j < nlocal) {
	  f[j][0] -= delx*fpair;
	  f[j][1] -= dely*fpair;
	  f[j][2] -= delz*fpair;
	}

	if (EFLAG) {
	  if (tabstyle == LOOKUP)
	    evdwl = tb->e[itable];
	  else if (tabstyle == LINEAR || tabstyle == BITMAP)
	    evdwl = tb->e[itable] + fraction*tb->de[itable];
	  else
	    evdwl = a * tb->e[itable] + b * tb->e[itable+1] + 
	      ((a*a*a-a)*tb->e2[itable] + (b*b*b-b)*tb->e2[itable+1]) * 
	      tb->deltasq6;
	  evdwl *= factor_lj;
	}

	if (EVFLAG) ev_tally_thr(this,i,j,nlocal,NEWTON_PAIR,
				 evdwl,0.0,fpair,delx,dely,delz,tid);
      }
    }

    f[i][0] += fxtmp;
    f[i][1] += fytmp;
    f[i][2] += fztmp;
  }
}

/* ---------------------------------------------------------------------- */

double PairTableOMP::memory_usage()
{
  double bytes = memory_usage_thr();
  bytes += PairTable::memory_usage();

  return bytes;
}
