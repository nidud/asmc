Asmc Macro Assembler Reference

# Asmc Build Environment Reference

Build Environment usually refers to a batch file that sets the local environment for a specific tool chain. A local configuration is preferred over using global settings as this may be in conflict with other tools in the system.

### In This Section

- Asmc Build Environment
- Using Asmc with Visual Studio

### Asmc Build Environment

The batch file for the Asmc environment is located in the root directory and currently named asmc-2.36.cmd. This should be run at least ones as it produce additional batch files and binaries in addition to build import libraries and libc.

You may then use this batch file as an entry to the Asmc environment. However, a direct link to the main shell (bin/dz.exe) is preferred as this will enable local configuration of the console (font, window size, startup directory etc).

### Using Asmc with Visual Studio

The project files provided use VS2022. The configuration files are located in the bin directory. This should work out-of-the-box provided you launch VC from within the shell.

#### See Also

[Asmc Reference](../readme.md)
