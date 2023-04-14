#!/bin/bash

export DPRC=dprc.3
DPNI_NAME=dpni.5
chmod +x udpecho
export LD_LIBRARY_PATH=$(pwd)
#export ODP_PLATFORM_PARAMS="--socket-mem 1024 -v --file-prefix udpecho --iova-mode=va --mbuf-pool-ops-name dpaa2"
export ODP_PLATFORM_PARAMS="--socket-mem 1024 -v --file-prefix ofp --iova-mode=va -a ${DPNI_NAME}"
./udpecho -i "0" -f ./ofp.cli
