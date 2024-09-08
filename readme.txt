                  Simple data copier

     Low-level file copying tool by Popov Evgeniy Alekseyevich

                  Version 1.5.4.1

Program description

This program is a low-level tool for copying files.
It is simple but powerful and easy to use.
It is designed as safe and cross-platform software.

License

This software is distributed under GNU GENERAL PUBLIC LICENSE(Version 2 or later) terms.

Program usage

This software is a text interface/console program. Let's look at command-line arguments.

The first argument is an input file name.
The second argument is an output file name.

The 3rd argument is the start offset in bytes. It is an unsigned decimal value. 1 is the first byte.
Start offset is an optional argument. The start offset is the first byte by default.

The last argument is data end offset. It is an unsigned decimal value.
End offset is optional. End offset is equivalent to input file size by default.

Exit codes

0 - Operation successfully completed.
1 - Can't open input file.
2 - Can't create or open output file.
3 - Can't allocate memory.
4 - Can't decode argument.
5 - Input files with zero length are not supported.
6 - Invalid offset.
7 - Invalid start offset! Minimal start offset: 1
8 - Can't jump to start offset.
9 - Can't read data.
10 - Can't write data.

Some remarks about source code

The source code compatibility with any modern C compiler.

Install and uninstall under Linux

Install steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3. Run as root: make install

Uninstall steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3. Run as root: make uninstall

Version history

0.1 – Initial version.
0.2 – 1.0 – Unstable branch.
1.1 – First stable version.
1.2 – 1.3 – Small changes in source code.
1.3.0.1 – Small changes in the make file.
1.3.0.2 – Documentation updated.
1.3.1 – 1.3.5 – Small changes.
1.3.5.1 – Makefile updated.
1.3.6 – 1.3.7 – Small changes.
1.3.7.1 – Source code recompiled under Open Watcom V2 Fork.
1.3.8 – Small changes.
1.3.8.1 – Makefile updated.
1.3.9 – Small changes.
1.3.9.1 – 1.3.9.2 – Documentation updated.
1.4 – 1.4.3 – Small changes.
1.4.4 – Command–line options changed.
1.4.5 – Exit codes changes.
1.4.6 – 1.5 – Small changes.
1.5.1 – Visual C++ support improved.
1.5.2 – Small changes.
1.5.3 – Small bug fixed.
1.5.4 – Small changes.
1.5.4.1 – Documentation updated.