## Notes:

- The "efficient" algorithms take advantage of the first 1000 prime numbers to reduce the amount of computation needed.
- And in the "efficient" methods, primality tests are used whenever applicable.
- _Primality tests aren't used in `piEfficient` because they are less efficient compared to factorization when dealing with sufficiently small numbers (<10 Million)._


- The [runprimes.cpp](runprimes.cpp) command line interface was originally designed to use with python (through command prompt instead of messing with `_ctypes` and imports).
- [this](run) binary file is compiled from the previous files.