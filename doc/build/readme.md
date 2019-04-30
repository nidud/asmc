Asmc Macro Assembler Reference

## Build Environment for Asmc

The main shell (dz.exe) sets the relevant environment variables (PATH, ASMCDIR, INCLUDE, LIB). Otherwise these variables should be set manually in a batch file.

    SET ASMCDIR=%1
    SET PATH=%1\bin;%PATH%
    SET LIB=%1\lib
    SET INCLUDE=%1\include
    make

The shell may also be used in batch mode.

    %1\bin\dz.exe make.exe
