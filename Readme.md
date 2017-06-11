# Praktikum Softwareengineering 1 - HAW Hamburg, SS17

## How to makefile:
* Update dependencies: `make deps` (creates a bunch of .d files)
* Build executable: `make` or `make all`
* Build tests: `make test`
* Cleanup: `make clean`
* Update doxygen (HTML documentation): `make docs`

## How to run:
Run `make`. This creates the executable `se1.out` which contains the main program.

## How to test:
Run `make test`. This will create `se1_unit_test.out` and `se1_fsm_test.out`, which contain Unit Tests and State based tests respectively. Because the FSM test generates a lot of output, it's better to run the shell script `test_fsm.sh` which will only print the result. In case of a failure, the full output is stored in `output.log` and can be referenced. (using `lesss` for example)