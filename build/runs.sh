#!/bin/bash

## ---- ROOT6 ----
# !!!!!!!! NEED TO SPECIFY YOUR ROOTSYS !!!!!!!!!!!!
export ROOTSYS=/Users/tatsuno/cern/ROOT/root6
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

# select your macro files
./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_160Mevc.mac

# you can continue brabrabra
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_160Mevc.mac
#./g4_stopmu mac/Kapton100Air015/Ar010atm/gausbeam_event10k_160Mevc.mac
