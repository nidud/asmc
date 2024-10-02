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

<table>
<tr><td>**Option**</td><td>**Purpose**</td></tr>
<tr><td>@</td><td>Specifies a response file.</td></tr>
<tr><td>[/ALIGN](link-align.md)</td><td>Specifies the alignment of each section.</td></tr>
<tr><td>[/BASE](link-base.md)</td><td>Sets a base address for the program.</td></tr>
<tr><td>[/DEF](link-def.md)</td><td>Passes a module-definition (.def) file to the linker.</td></tr>
<tr><td>[/DEFAULTLIB](link-defaultlib.md)</td><td>Searches the specified library when external references are resolved.</td></tr>
<tr><td>[/DLL](link-dll.md)</td><td>Builds a DLL.</td></tr>
<tr><td>[/ENTRY](link-entry.md)</td><td>Sets the starting address.</td></tr>
<tr><td>[/EXPORT](link-export.md)</td><td>Exports a function.</td></tr>
<tr><td>[/FILEALIGN](link-filealign.md)</td><td>Aligns sections within the output file on multiples of a specified value.</td></tr>
<tr><td>[/FIXED](link-fixed.md)</td><td>Creates a program that can be loaded only at its preferred base address.</td></tr>
<tr><td>[/FORCE](link-force.md)</td><td>Forces a link to complete even with unresolved symbols or symbols defined more than once.</td></tr>
<tr><td>[/HEAP](link-heap.md)</td><td>Sets the size of the heap, in bytes.</td></tr>
<tr><td>[/IMPLIB](link-implib.md)</td><td>Overrides the default import library name.</td></tr>
<tr><td>[/INCLUDE](link-include.md)</td><td>Forces symbol references.</td></tr>
<tr><td>[/LARGEADDRESSAWARE](link-largeaddressaware.md)</td><td>Tells the compiler that the application supports addresses larger than 2 gigabytes</td></tr>
<tr><td>[/LIBPATH](link-libpath.md)</td><td>Specifies a path to search before the environmental library path.</td></tr>
<tr><td>[/MACHINE](link-machine.md)</td><td>Specifies the target platform.</td></tr>
<tr><td>[/MANIFEST](link-manifest.md)</td><td>Creates a side-by-side manifest file and optionally embeds it in the binary.</td></tr>
<tr><td>[/MANIFESTDEPENDENCY](link-manifestdependency.md)</td><td>Specifies a _dependentAssembly_ section in the manifest file.</td></tr>
<tr><td>[/MANIFESTFILE](link-manifestfile.md)</td><td>Changes the default name of the manifest file.</td></tr>
<tr><td>[/MAP](link-map.md)</td><td>Creates a mapfile.</td></tr>
<tr><td>[/MERGE](link-merge.md)</td><td>Combines sections.</td></tr>
<tr><td>[/NODEFAULTLIB](link-nodefaultlib.md)</td><td>Ignores all (or the specified) default libraries when external references are resolved.</td></tr>
<tr><td>[/NOLOGO](link-nologo.md)</td><td>Suppresses the startup banner.</td></tr>
<tr><td>[/NXCOMPAT](link-nxcompat.md)</td><td>Marks an executable as verified to be compatible with the Windows Data Execution Prevention feature.</td></tr>
<tr><td>[/OUT](link-out.md)</td><td>Specifies the output file name.</td></tr>
<tr><td>[/SECTION](link-section.md)</td><td>Overrides the attributes of a section.</td></tr>
<tr><td>[/STACK](link-stack.md)</td><td>Sets the size of the stack in bytes.</td></tr>
<tr><td>[/STUB](link-stub.md)</td><td>Attaches an MS-DOS stub program to a Win32 program.</td></tr>
<tr><td>[/SUBSYSTEM](link-subsystem.md)</td><td>Tells the operating system how to run the .exe file.</td></tr>
<tr><td>[/VERBOSE](link-verbose.md)</td><td>Prints linker progress messages.</td></tr>
<tr><td>[/VERSION](link-version.md)</td><td>Assigns a version number.</td></tr>
</table>

### Asmc-controlled Linker options

You can use the [comment](../directive/dot-pragma.md) pragma to specify some linker options.

Valid options are [/DEFAULTLIB](link-defaultlib.md), [/ENTRY](link-entry.md), [/EXPORT](link-export.md), /IMPORT, and [/MANIFESTDEPENDENCY](link-manifestdependency.md)

#### See Also

[Asmc Build Tools Reference](readme.md) | [Asmc Reference](../readme.md)
