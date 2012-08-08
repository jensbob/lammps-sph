#! /bin/bash

set -e
set -u
configfile=$HOME/lammps-sph-nana.sh
if [ -f "${configfile}" ]; then
    source "${configfile}"
else
    printf "cannot find config file: %s\n" ${configfile} > "/dev/stderr"
    exit -1
fi

#rm -rf dum* im* poly* log.lammps

nproc=8
ndim=2d
Nbeads=25
Nsolvent=25
dx=8.333333e-4
nx=128
ny=32
nextbond=5
polymer_normal=2
polymer_extbond=3
dname=fene-nb${Nbeads}-ns${Nsolvent}-nx${nx}-next${nextbond}

vars="-var dx ${dx} -var ny ${ny} -var nx ${nx} -var ndim ${ndim} -var dname ${dname}"

${lmp} ${vars} -in sdpd-polymer-init.lmp
${restart2data} poly3d.restart poly3d.txt

# make wall particles
awk -v wall_type=4 \
    -v dx=${dx} \
    -v ny=${ny} \
    -v xd=0.3 \
    -v xb=0.1 \
    -v d=-0.0 \
    -v a=0.5 -v b=-0.7 \
    -f makewall.awk poly3d.txt > poly3.txt

mv poly3.txt poly3d.txt

awk -v wall_type=4 -v polymer_normal=${polymer_normal} -v polymer_extbond=${polymer_extbond} \
    -v nextbond=${nextbond} \
    -v cutoff=3.0 -v Nbeads=${Nbeads} -v Nsolvent=${Nsolvent} -v Npoly=full \
     -f addpolymer.awk poly3d.txt > poly3.txt
awk -v Nbeads=${Nbeads} -v polymer_normal=${polymer_normal} -v polymer_extbond=${polymer_extbond} \
    -f killsmall.awk poly3.txt poly3.txt > poly3d.txt

nangles=$(tail -n 1 poly3d.txt | awk '{print $1}')
nbounds=$(awk '/Angles/{exit} NF' poly3d.txt | tail -n 1  | awk '{print $1}')
sed -e "s/_NUMBER_OF_ANGLES_/$nangles/1" -e "s/_NUMBER_OF_BOUNDS_/$nbounds/1" poly3d.txt > poly3.txt
mv poly3.txt poly3d.txt

# output directory name

mkdir -p ${dname}
${mpirun} -np ${nproc} ${lmp} ${vars} -in sdpd-polymer-run.lmp
