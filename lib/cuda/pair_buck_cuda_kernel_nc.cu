/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator 

   Original Version:
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov 

   See the README file in the top-level LAMMPS directory. 

   ----------------------------------------------------------------------- 

   USER-CUDA Package and associated modifications:
   https://sourceforge.net/projects/lammpscuda/ 

   Christian Trott, christian.trott@tu-ilmenau.de
   Lars Winterfeld, lars.winterfeld@tu-ilmenau.de
   Theoretical Physics II, University of Technology Ilmenau, Germany 

   See the README file in the USER-CUDA directory. 

   This software is distributed under the GNU General Public License.
------------------------------------------------------------------------- */
__device__ inline F_FLOAT PairBuckCuda_Eval(const F_FLOAT& rsq,const int ij_type,F_FLOAT& factor_lj,int& eflag, ENERGY_FLOAT& evdwl)
{
    const F_FLOAT r2inv = F_F(1.0)/rsq;
	const F_FLOAT r6inv = r2inv*r2inv*r2inv;
   	const F_FLOAT r = _RSQRT_(r2inv);
	const F_FLOAT rexp = _EXP_(-r*_rhoinv[ij_type]);
	const F_FLOAT forcebuck = _buck1[ij_type]*r*rexp - _buck2[ij_type]*r6inv;
	if(eflag) evdwl += factor_lj*(_a[ij_type]*rexp - _c[ij_type]*r6inv - 
			    			_offset[ij_type]);		
	return (factor_lj*forcebuck) * r2inv;
}
