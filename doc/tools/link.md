Asmc Macro Assembler Reference

# Asmc Linker Reference

### In This Section

- About LINKW
- Linker options
- Asmc-controlled linker options

### About LINKW

LINKW is a fork of JWlink:
- https://github.com/Baron-von-Riedesel/jwlink

The changes in the JWlink sources are:
- added some MS LINK compatible command-line options
- added module-definition (.def) input for /DLL
- added import lib creation from (.def) input
- added auto assignment of library directories and startup modules

### Linker options

- @ Specifies a response file.
- [/ALIGN](link-align.md) Specifies the alignment of each section.
- [/BASE](link-base.md) Sets a base address for the program.
- [/DEF](link-def.md) Passes a module-definition (.def) file to the linker.
- [/DEFAULTLIB](link-defaultlib.md) Searches the specified library when external references are resolved.
- [/DLL](link-dll.md) Builds a DLL.
- [/ENTRY](link-entry.md) Sets the starting address.
- [/EXPORT](link-export.md) Exports a function.
- [/FILEALIGN](link-filealign.md) Aligns sections within the output file on multiples of a specified value.
- [/FIXED](link-fixed.md) Creates a program that can be loaded only at its preferred base address.
- [/FORCE](link-force.md) Forces a link to complete even with unresolved symbols or symbols defined more than once.
- [/HEAP](link-heap.md) Sets the size of the heap, in bytes.
- [/IMPLIB](link-implib.md) Overrides the default import library name.
- [/INCLUDE](link-include.md) Forces symbol references.
- [/LARGEADDRESSAWARE](link-largeaddressaware.md) Tells the compiler that the application supports addresses larger than 2 gigabytes
- [/LIBPATH](link-libpath.md) Specifies a path to search before the environmental library path.
- [/MACHINE](link-machine.md) Specifies the target platform.
- [/MANIFEST](link-manifest.md) Creates a side-by-side manifest file and optionally embeds it in the binary.
- [/MANIFESTDEPENDENCY](link-manifestdependency.md) Specifies a _dependentAssembly_ section in the manifest file.
- [/MANIFESTFILE](link-manifestfile.md) Changes the default name of the manifest file.
- [/MAP](link-map.md) Creates a mapfile.
- [/MERGE](link-merge.md) Combines sections.
- [/NODEFAULTLIB](link-nodefaultlib.md) Ignores all (or the specified) default libraries when external references are resolved.
- [/NOLOGO](link-nologo.md) Suppresses the startup banner.
- [/NXCOMPAT](link-nxcompat.md) Marks an executable as verified to be compatible with the Windows Data Execution Prevention feature.
- [/OUT](link-out.md) Specifies the output file name.
- [/SECTION](link-section.md) Overrides the attributes of a section.
- [/STACK](link-stack.md) Sets the size of the stack in bytes.
- [/STUB](link-stub.md) Attaches an MS-DOS stub program to a Win32 program.
- [/SUBSYSTEM](link-subsystem.md) Tells the operating system how to run the .exe file.
- [/VERBOSE](link-verbose.md) Prints linker progress messages.
- [/VERSION](link-version.md) Assigns a version number.

### Asmc-controlled Linker options

You can use the [comment](../directive/dot-pragma.md) pragma to specify some linker options.

Valid options are [/DEFAULTLIB](link-defaultlib.md), [/ENTRY](link-entry.md), [/EXPORT](link-export.md), /IMPORT, and [/MANIFESTDEPENDENCY](link-manifestdependency.md)

#### See Also

[Asmc Build Tools Reference](readme.md) | [Asmc Reference](../readme.md)
