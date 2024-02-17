#!/bin/bash
#SBATCH --time=00:45:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --exclusive
#SBATCH --job-name mp1-benchmark
#SBATCH -p eng-instruction


### BEGIN SNIPPET FROM https://stackoverflow.com/questions/56962129/
# check if script is started via SLURM or bash
# if with SLURM: there variable '$SLURM_JOB_ID' will exist
# `if [ -n $SLURM_JOB_ID ]` checks if $SLURM_JOB_ID is not an empty string
if [ -n $SLURM_JOB_ID ];  then
    # check the original location through scontrol and $SLURM_JOB_ID
    SCRIPT_PATH=$(scontrol show job $SLURM_JOBID | awk -F= '/Command=/{print $2}')
	SCRIPT_DIR=$(dirname ${SCRIPT_PATH})
else
    # otherwise: started with bash. Get the real location.
    echo "Not running under SLURM. Exiting." 1>&2
	exit 1
fi
### END SNIPPET

#moves to the directory the user was in when they ran sbatch
cd ${SLURM_SUBMIT_DIR} #assumed to be the source tree

export PBS_O_WORKDIR=${SLURM_SUBMIT_DIR}
/projects/eng/shared/cs484/sing_exec.sh ${SCRIPT_DIR}/batch_script.pbs
