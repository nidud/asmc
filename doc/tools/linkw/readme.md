Asmc Macro Assembler Reference

# Asmc Linker Reference

### In This Section

- About LINKW
- Linker options

### About LINKW

LINKW is a fork of JWlink:
- https://github.com/Baron-von-Riedesel/jwlink

The changes in the JWlink sources are:
- added some MS LINK compatible command-line options
- added module-definition (.def) input for /DLL
- added import lib creation from (.def) input
- added auto assignment of library directories and startup modules
- added support for Unicode response file input
- changed the default name of the linker directive file to **linkw.lnk**
- changed the default environment variable to **LINKW_LNK**

### Linker options

- @ Specifies a response file.
- [/ALIGN](align.md) Specifies the alignment of each section.
- [/BASE](base.md) Sets a base address for the program.
- [/DEF](def.md) Passes a module-definition (.def) file to the linker.
- [/DEFAULTLIB](defaultlib.md) Searches the specified library when external references are resolved.
- [/DLL](dll.md) Builds a DLL.
- [/ENTRY](entry.md) Sets the starting address.
- [/EXPORT](export.md) Exports a function.
- [/FILEALIGN](filealign.md) Aligns sections within the output file on multiples of a specified value.
- [/FIXED](fixed.md) Creates a program that can be loaded only at its preferred base address.
- [/FORCE](force.md) Forces a link to complete even with unresolved symbols or symbols defined more than once.
- [/HEAP](heap.md) Sets the size of the heap, in bytes.
- [/IMPLIB](implib.md) Overrides the default import library name.
- [/INCLUDE](include.md) Forces symbol references.
- [/LARGEADDRESSAWARE](largeaddressaware.md) Tells the compiler that the application supports addresses larger than 2 gigabytes
- [/LIBPATH](libpath.md) Specifies a path to search before the environmental library path.
- [/MACHINE](machine.md) Specifies the target platform.
- [/MANIFEST](manifest.md) Creates a side-by-side manifest file and optionally embeds it in the binary.
- [/MANIFESTDEPENDENCY](manifestdependency.md) Specifies a _dependentAssembly_ section in the manifest file.
- [/MANIFESTFILE](manifestfile.md) Changes the default name of the manifest file.
- [/MAP](map.md) Creates a mapfile.
- [/MERGE](merge.md) Combines sections.
- [/NODEFAULTLIB](nodefaultlib.md) Ignores all (or the specified) default libraries when external references are resolved.
- [/NOLOGO](nologo.md) Suppresses the startup banner.
- [/NXCOMPAT](nxcompat.md) Marks an executable as verified to be compatible with the Windows Data Execution Prevention feature.
- [/OUT](out.md) Specifies the output file name.
- [/SECTION](section.md) Overrides the attributes of a section.
- [/STACK](stack.md) Sets the size of the stack in bytes.
- [/STUB](stub.md) Attaches an MS-DOS stub program to a Win32 program.
- [/SUBSYSTEM](subsystem.md) Tells the operating system how to run the .exe file.
- [/VERBOSE](verbose.md) Prints linker progress messages.
- [/VERSION](version.md) Assigns a version number.

The Open Watcom Linker User’s Guide

- https://open-watcom.github.io/open-watcom-v2-wikidocs/lguide.pdf

#### See Also

[Asmc Build Tools Reference](../readme.md) | [Asmc Library Manager Reference](../libw/readme.md)
