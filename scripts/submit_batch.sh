#!/bin/bash

##
#Snippet from
#
#http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
#
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#
#end snippet
##

pushd "${SCRIPT_DIR}/.."

# qsub ${SCRIPT_DIR}/batch_script.pbs
sbatch "${SCRIPT_DIR}/batch_script.slurm"

popd
