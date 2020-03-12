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

./g4_stopmu mac/Ne01atm_gausbeam_event10k_16Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_17Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_18Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_19Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_20Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_21Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_22Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_23Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_24Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_25Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_26Mevc.mac
./g4_stopmu mac/Ne01atm_gausbeam_event10k_27Mevc.mac
