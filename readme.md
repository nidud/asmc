# Asmc Macro Assembler

## About Asmc

Asmc is a slow-burning attempt of making a functional programming language out of assembly. It supports AVX-512 instructions (Masm v14) but the [Version](doc/symbol/at-version.md) macro is currently set to v10. The assembler is written in assembly and is open source under the GNU General Public License. It runs on Windows and Linux.

## Change Log
- [source/asmc/history.txt](source/asmc/history.txt)

## Install Asmc

Download the zip-file or use Git:

    git clone https://github.com/nidud/asmc.git

For Windows run the asmc-2.37.cmd file in the root directory.

Linux:

    cd asmc/source/asmc
    make
    make install


Asmc Macro Assembler Reference

## Reference

- [Asmc Command-Line Reference](doc/command/readme.md)
- [Asmc Error Messages](doc/error/readme.md)
- [Directives Reference](doc/directive/readme.md)
- [Symbols Reference](doc/symbol/readme.md)
- [Operators Reference](doc/operator/readme.md)
- [Asmc Build Tools Reference](doc/tools/readme.md)
