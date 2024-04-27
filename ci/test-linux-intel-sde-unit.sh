#!/bin/bash
set -x

if [ -z "$INTEL_SDE_ARCH" ]
then
	echo "Please define the 'INTEL_SDE_ARCH' environment variable (ex.: -skx)."
	exit 1
fi

# install Intel SDE emulator --------------------------------------------------
apt update
apt install -y wget xz-utils
echo 0 > /proc/sys/kernel/yama/ptrace_scope
WD=$(pwd)
mkdir softwares
cd softwares
wget https://largo.lip6.fr/monolithe/downloads/sde-external-9.33.0-2024-01-07-lin.tar.xz
tar -xvvf sde-external-9.33.0-2024-01-07-lin.tar.xz
ln -s $WD/softwares/sde-external-9.33.0-2024-01-07-lin $WD/softwares/sde
export PATH=$WD/softwares/sde:$PATH
cd ..
# -----------------------------------------------------------------------------

for build in "$@"
do
	cd $build
	sde64 $INTEL_SDE_ARCH -- ./bin/run-tests
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
done
