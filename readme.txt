                  Simple data copier

     The low-level file copying tool by Popov Evgeniy Alekseyevich

                  Version 1.8.6

The program description.

This program is a low-level file copying tool.
It is simple but powerful and easy to use.
It is designed as safe and cross-platform software.

License.

This software is distributed under the GNU GENERAL PUBLIC LICENSE (version 2 or later) terms.

The program usage.

This software is a text interface/console program. Let's look at the command-line arguments.

The first argument is the input file name.
The second argument is the output file name.

The 3rd argument is the start offset in bytes. It is an unsigned decimal value. 0 is the first byte.
The start offset is an optional argument. The start offset is the first byte by default.

The last argument is the block length. It is an unsigned decimal value.
The block length is an optional argument. It is equal to the input file size by default.

Important remark.

An input file with zero length is not supported.

Exit codes.

0: The operation was successfully completed.
1: Can't open the input file!
2: Can't create or open the output file!
3: Can't jump to the start offset!
4: Can't read data!
5: Can't write data!
6: The start offset is invalid!
7: The block length is invalid!
8: The block length is too large!
9: Can't decode an argument.
10: Can't allocate memory!

The source code.

The source code is compatible with any modern C compiler.

Install and uninstall under Linux.

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Version history.

0.1: The initial version.
0.2-1.0: The unstable branch.
1.1: The first stable version.
1.2-1.3: The small changes in the source code.
1.3.0.1: The small changes in the makefile.
1.3.0.2: The documentation has been updated.
1.3.1-1.3.5: The small changes.
1.3.5.1: The makefile has been updated.
1.3.6-1.3.7: The small changes.
1.3.7.1: The source code was recompiled under Open Watcom V2 Fork.
1.3.8: The small changes.
1.3.8.1: The makefile has been updated.
1.3.9: The small changes.
1.3.9.1-1.3.9.2: The documentation has been updated.
1.4-1.4.3: The small changes.
1.4.4: The command-line options have been changed.
1.4.5: The exit codes have been changed.
1.4.6-1.5: The small changes.
1.5.1: Visual C++ support has improved.
1.5.2: The small changes.
1.5.3: The small bug has been fixed.
1.5.4: The small changes.
1.5.4.1: The documentation has been updated.
1.5.5: The small changes.
1.5.5.1-1.5.5.2: The documentation has been updated.
1.5.6: The source code was recompiled under Tiny C Compiler.
1.5.7: The small changes.
1.5.8: The code portability has improved.
1.5.9-1.6: The small changes.
1.6.0.1: The documentation has been updated.
1.6.1-1.6.4: The small changes.
1.6.4.1: The documentation has been updated.
1.6.5-1.6.6: The small changes.
1.6.7-1.6.9: The small bug has been fixed.
1.7-1.7.2: The small changes.
1.7.3: The small bug has been fixed.
1.7.4: The small changes.
1.7.5-1.7.6: The small bug has been fixed.
1.7.7: The file offset style has been changed.
1.7.8-1.7.9: The small changes.
1.8: The small bug has been fixed.
1.8.1-1.8.2: The small changes.
1.8.3: The file processing has improved.
1.8.4: The small changes.
1.8.5-1.8.6: The file processing has improved.