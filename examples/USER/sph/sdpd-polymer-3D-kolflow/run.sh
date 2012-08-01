#! /bin/bash

set -e
set -u
configfile=$HOME/lammps-sph-kana.sh
if [ -f "${configfile}" ]; then
    source "${configfile}"
else
    printf "cannot find config file: %s\n" ${configfile} > "/dev/stderr"
    exit -1
fi

nproc=6
ndim=2d

cp ${ndim}-vars.lmp ${ndim}-model.lmp

rm -rf dum* im* poly* log.lammps
${lmp} -var ndim ${ndim} -in sdpd-polymer-init.lmp
${restart2data} poly3d.restart poly3d.txt

 awk -v cutoff=3.0 -v Nbeads=12 -v Nsolvent=12 -v Npoly=full \
     -f addpolymer.awk poly3d.txt > poly3.txt
 nbound=$(tail -n 1 poly3.txt | awk '{print $1}')
 sed "s/_NUMBER_OF_BOUNDS_/$nbound/1" poly3.txt > poly3d.txt

${mpirun} -np ${nproc} ${lmp} -var ndim ${ndim} -in sdpd-polymer-run.lmp