#! /bin/bash



rm -rf dum* im* poly* log.lammps
../../../../src/lmp_linux -in sdpd-polymer3D-inti.lmp
../../../../tools/restart2data poly3d.restart poly3d.txt


 awk -v cutoff=3.0 -v Nbeads=25 -v Nsolvent=0 -v Npoly=full \
     -f addpolymer.awk poly3d.txt > poly3.txt
 nbound=$(tail -n 1 poly3.txt | awk '{print $1}')
 sed "s/_NUMBER_OF_BOUNDS_/$nbound/1" poly3.txt > poly3d.txt

<<<<<<< HEAD
#time /scratch/qingguang/prefix-nana/bin/mpirun -np 6  ../../../../src/lmp_linux -in sdpd-polymer3D-run.lmp
mpiexec  -np 2 ../../../../src/lmp_linux -in sdpd-polymer3D-run.lmp
=======
time /scratch/qingguang/prefix-nana/bin/mpirun -np 4  ../../../../src/lmp_linux -in sdpd-polymer3D-run.lmp
#mpirun  -np 2 ../../../../src/lmp_linux -in sdpd-polymer3D-run.lmp
>>>>>>> 5e622a9eaf08ef5c5d3c9decbc0af857c3e07727
#../../../../src/lmp_linux -in sdpd-polymer-run.lmp
