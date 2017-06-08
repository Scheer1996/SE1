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
Run `make test`. This will create `se1_unit_test.out` and `se1_fsm_test.out`, which contain Unit Tests and State based tests respectively.