# Building on Campus Cluster
You can build the project by running:
```
sbatch ./scripts/compile_script.sh
```
This will build and test your code.
It is expected that you will initially fail the test `Cache.TileSizeChosen`. You will choose the tile size in a later part of the assignment.

# Benchmarking on Campus Cluster
You can benchmark the project by running:
```
sbatch ./scripts/submit_batch.sh
```
This will test and benchmark your code. 
The slurm-<JOBID>.out file will tell you whether you pass or fail the tests. Output files in the writeup directory will tell you benchmarking metrics. 

## SLURM (Campus Cluster since 2021)
On a Slurm cluster (Campus Cluster since 2021), move to the the base directory of your cloned repo, and submit the batch script.

That process looks like this:

```
git clone <URL to my turnin repo/mp1.git>
cd mp1
sbatch ./scripts/batch_script.slurm
```
This script builds, tests, and benchmarks your code.

## PBS/Torque (Pre-2021 Campus Cluster)
On a PBS/Torque cluster (Pre-2021 Campus Cluster), move to the the base directory of your cloned repo, and submit the batch script.

That process looks like this:

```
git clone <URL to my turnin repo/mp1.git>
cd mp1
qsub ./scripts/batch_script.pbs
```
This script builds, tests, and benchmarks your code.

# Manual Building

Note: If you choose to do this on Campus Cluster (you should not need to), be sure that you are using the appropriate Singularity shell.

To build, create a new directory, anywhere. We will call it "build".
Change to that directory and type

```
cmake <path_to_source_directory>
make
```
in your shell.

This will create programs named

* `build/bin/multiply_runner`
* `build/bin/transpose_runner`
* `build/bin/openmp_runner`
* `build/bin/run_tests`
* `build/bin/run_benchmarks`
* `build/bin/student_benchmarks`
* `build/bin/find_tile_size`

# Running tests

You can run the tests we provide by executing
`/projects/eng/shared/cs484/run_singularity.sh`
to launch the Singularity container that provides your environment, then from inside the container execute the program
`build/bin/run_tests`

Try the "--help" option to see various options.

## Running benchmarks

Run benchmarks by executing
`/projects/eng/shared/cs484/run_singularity.sh`
to launch the Singularity container that provides your environment, then from inside the container execute the program
`build/bin/run_benchmarks`

Try the "--help" option to see various options.

## Custom benchmarks

You may add benchmarks of your own to the file `tests/student_benchmarks.cpp` in the source tree.
We will not run yours when grading.

See the documentation at [Google Benchmark GitHub Project](https://github.com/google/benchmark) .

## Running the programs
You can use (and modify) these programs during development to do individual benchmarks.

You can run the programs by typing:
* `build/bin/multiply_runner <array_size> <tile_size> [num_trials (default 5)]`
* `build/bin/transpose_runner <array_size> <tile_size> [num_trials (default 5)]`
* `build/bin/openmp_runner <array_size> [num_trials=1]`
