# DHBW_horn_resolver
Algorithmus zur Resolution von Horn Formeln

## Dependencies

You will need the following tools for this to build:

   `make`

   `gcc`

   `bison`
   
   `flex`

## Build
Clone Repository

`make`

if something with automatic make strategy is not working you can use
`make forceall`
to build all files without looking for changes.

## Usage

### Automatic tests

You can use the make command to run automated tests on the build.

  `make test-s`
  Will run all satisfiable testfiles

  `make test-u`
  Will run all unsatisfiable testfiles

### manual run

  `./hornschema [Path to File]`
  Will run the binary and read in the given file

  `./hornschema`
  Will run the binary and read clauses from stdin

### Return Values

The Program will return Values between 0 and 2

  * `0` Resolution is satisfiable
  * `1` Resolution is not satisfiable
  * `2` Resolution is not decidable (running into max deph)
