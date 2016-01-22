#!/bin/bash
HERE=$(pwd)
export LD_LIBRARY_PATH=${HERE}/resources/libs/:$LD_LIBRARY_PATH
./invSim64 $@
