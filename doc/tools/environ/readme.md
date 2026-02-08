Asmc Macro Assembler Reference

# Asmc Build Environment Reference

Build environment usually refers to a batch file that configures the local environment for a specific toolchain. Local configurations are preferred over global settings because globals can conflict with other installed tools.

### In This Section

- Asmc Build Environment
- Using Asmc with Visual Studio

### Asmc Build Environment

The batch file for the Asmc environment is located in the root directory and is currently named `asmc-2.37.cmd`. Run it at least once; it generates additional batch files, binaries, build import libraries, and `libc`. You may use this batch file to enter the Asmc environment. For more precise local console control (font, window size, startup directory, etc.), prefer a direct link to the main shell, `bin/dz.exe`.

In Linux, the `asmc-profile.sh` script sets the environment. This is installed in the `/etc/profile.d` directory and will be sourced automatically for users whose shells read `/etc/profile.d/*`. The script adds `/usr/lib/asmc` to `LIBRARY_PATH`, and adds `/usr/lib/asmc/include` to `INCLUDE`, allowing compilers and linkers to find Asmc headers and libraries from any terminal session.

### Using Asmc with Visual Studio

The included `*.vcxproj` project files target Visual Studio 2022. Configuration files are in the `bin` directory. Projects should build out of the box if you launch Visual Studio from the Asmc shell (for example, by running the environment batch script or `bin/dz.exe`) so the required environment variables are set. Most makefiles include a `vs` target that generates a `.vcxproj` file — see `source/tools/project` for details.

#### See Also

[Asmc Reference](../readme.md)
