#!/bin/bash

## ---- ROOT6 ----
export ROOTSYS=/Users/tatsuno/cern/ROOT/root6
#export ROOTSYS=/Users/tatsuno/cern/ROOT/root_old
if [ -z "$BASH_VERSION" ]; then
    cdir=$(pwd)
    cd $ROOTSYS/bin
    source thisroot.sh
    echo "ROOT6 setup done."
    cd $cdir
    unset cdir
else
    source $ROOTSYS/bin/thisroot.sh
fi


./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_160Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_170Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_180Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_190Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_200Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_210Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_220Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_230Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_240Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_250Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_260Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_270Mevc.mac
