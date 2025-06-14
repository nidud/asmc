# Asmc Macro Assembler

## About Asmc

Asmc is technically a slow-burning design project to make a functional programming language out of assembly. It started as a modified version of JWasm in 2011 with some simple but specific goals:

- Remove the necessity of labels.
- Merge macro and function calls.
- Enable data declaration where you need it.
- Enhanced compatibility with Masm.

Asmc supports AVX-512 instructions (Masm v14) but the [Version](doc/symbol/at-version.md) macro is currently set to v10.

## Change Log
- [source/asmc/history.txt](source/asmc/history.txt)

## Install Asmc

Download the zip-file or use Git:

    git clone https://github.com/nidud/asmc.git

For Windows run the asmc-2.36.cmd file in the root directory.

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
