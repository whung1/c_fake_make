# c_make
a C-implementation to parse and make fake "Makefile's" titled Fakefiles with fake.c, relying on execlp and child processes.

1. Make fake.c by typing `make`
2. use program "fake" that reads "Fakefile" to create executable programs
e.g. `./fake Fakefile cat` creates a program "cat" like the cat command in Linux
e.g. `./fake Fakefile segfault` runs code in Fakefile and segfaults appropriately


Made for UIUC CS241
