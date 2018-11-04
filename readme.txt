                  Simple data copier

     Low-level file copying tool by Popov Evgeniy Alekseyevich

                  Version 1.3.5

Program description

This program is low-level tool for copying files.
It simple but powerful and easy to use.
It designed as safe and cross-platform software.

License

This software distributed under GNU GENERAL PUBLIC LICENSE(Version 2 or later) terms.

Program usage

This software is a text interface/console program. Let's look to command line argument.
First argument is input file name.
Second argument is output file name.
3hd argument is buffer length in megabytes. It is unsigned decimal value. Maximum buffer length is 512 megabytes. Minimum buffer length is 1 megabyte.
4hd argument is start offset in bytes. It is unsigned decimal value. 1 is first byte.
5hd argument is data end offset. It is unsigned decimal value. End offset is optional. End offset is equivalent of input file size by default.

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create or open output file.
3 - Can't allocate memory.
4 - Can't decode argument.
5 - Buffer length is too small.
6 - Buffer length is too big.
7 - Input files with zero length not supported.
8 - Invalid offset.
9 - Invalid start offset! Minimal start offset:1
10 - Can't jump to start offset.
11 - Can't read data.
12 - Can't write data.

Some remarks about source code

Program source compatibility with any modern C compiler.
Open sdcopy.c file and check platform identifier before start compiling.

Install and uninstall under Linux

Install steps:

1.Extract content of source code archive.
2.Open sdcopy.c file and change platform identifier. Save changes.
3.Open terminal and go to source code directory.
4.Run: make install

Uninstall steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.Run: make uninstall

Version history

0.1 - Initial version.
0.2 - 1.0 - Unstable branch.
1.1 - First stable version.
1.2 - 1.3 - Small changes in source code.
1.3.0.1 - Small changes in make file.
1.3.0.2 – Documentation was updated.
1.3.1 - 1.3.5 - Small changes.