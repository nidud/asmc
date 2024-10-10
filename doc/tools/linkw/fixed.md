Asmc Linker Reference

## /FIXED

**/FIXED**[:NO]

Tells the operating system to load the program only at its preferred base address. If the preferred base address is unavailable, the operating system does not load the file. For more information, see /BASE (Base Address).

/FIXED:NO is the default setting for a DLL, and /FIXED is the default setting for any other project type.

When /FIXED is specified, LINK does not generate a relocation section in the program. At run time, if the operating system is unable to load the program at the specified address, it issues an error message and does not load the program.

Specify /FIXED:NO to generate a relocation section in the program.

#### See Also

[Asmc Linker Reference](readme.md)
