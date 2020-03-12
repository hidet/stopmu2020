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

./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_160Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_165Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_170Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_175Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_180Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_185Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_190Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_195Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_200Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_205Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_210Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_215Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_220Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_225Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_230Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_235Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_240Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_245Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_250Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_255Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_260Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_265Mevc.mac
./g4_stopmu mac/Ne075atm/Ne075atm_gausbeam_event10k_270Mevc.mac
