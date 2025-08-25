Asmc Macro Assembler Reference

# Asmc Linker Reference

### In This Section

- About Linkw
- Asmc and Linkw
- Linker options

## About Linkw

Linkw is a fork of JWlink:
- https://github.com/Baron-von-Riedesel/jwlink

The changes in the JWlink sources are:
- added some MS LINK compatible command-line options
- added module-definition (.def) input for /DLL
- added import lib creation from (.def) input
- added auto assignment of library directories and startup modules
- added support for Unicode response file input
- changed the default name of the linker directive file to **linkw.lnk**
- changed the default environment variable to **LINKW_LNK**

## Asmc and Linkw

Asmc will spawn Linkw if the -c option is omitted or if the -Fe, -Bl, or -link option is used. If option -q is used -nologo is added. The options -machine and -subsystem is added if not defined.

## Linker options

### Syntax

The normal command line syntax is continues:

**linkw** [_options_] [[_option_] _file_, ...] [[_option_] \{ _files_ \}] ... [_options_]

As the additional syntax is _options files_ it breaks with the above logic as follows:
```
while options
    if /option
        while /option
            process option
        endw
        process files
        break
    endif
    process option
endw
```

_options_

Options may be preceded by both a forward slash (/) and a dash (-). The options are listed in the following table:

### Parameters

<table>
<tr><td><b>Option</b></td><td><b>Action</b></td></tr>
<tr><td>@</td><td>Specifies a response file.</td></tr>
<tr><td><a href="align.md">/Align</a></td><td>Specifies the alignment of each section.</td></tr>
<tr><td><a href="base.md">/Base</a></td><td>Sets a base address for the program.</td></tr>
<tr><td><a href="def.md">/DEF</a></td><td>Passes a module-definition (.def) file to the linker.</td></tr>
<tr><td><a href="defaultlib.md">/Defaultlib</a></td><td>Searches the specified library when external references are resolved.</td></tr>
<tr><td><a href="dll.md">/DLL</a></td><td>Builds a DLL.</td></tr>
<tr><td><a href="entry.md">/Entry</a></td><td>Sets the starting address.</td></tr>
<tr><td><a href="export.md">/EXport</a></td><td>Exports a function.</td></tr>
<tr><td><a href="filealign.md">/FILEALIGN</a></td><td>Aligns sections within the output file on multiples of a specified value.</td></tr>
<tr><td><a href="fixed.md">/FIXED</a></td><td>Creates a program that can be loaded only at its preferred base address.</td></tr>
<tr><td><a href="force.md">/FORCE</a></td><td>Forces a link to complete even with unresolved symbols or symbols defined more than once.</td></tr>
<tr><td><a href="heap.md">/Heap</a></td><td>Sets the size of the heap, in bytes.</td></tr>
<tr><td><a href="implib.md">/IMPLIB</a></td><td>Overrides the default import library name.</td></tr>
<tr><td><a href="include.md">/Include</a></td><td>Forces symbol references.</td></tr>
<tr><td><a href="largeaddressaware.md">/LArgeaddressaware</a></td><td>Tells the compiler that the application supports addresses larger than 2 gigabytes.</td></tr>
<tr><td><a href="libpath.md">/Libpath</a></td><td>Specifies a path to search before the environmental library path.</td></tr>
<tr><td><a href="machine.md">/MAChine</a></td><td>Specifies the target platform.</td></tr>
<tr><td><a href="manifest.md">/MANIFEST</a></td><td>Creates a side-by-side manifest file and optionally embeds it in the binary.</td></tr>
<tr><td><a href="manifestdependency.md">/MANIFESTDEPENDENCY</a></td><td>Specifies a _dependentAssembly_ section in the manifest file.</td></tr>
<tr><td><a href="manifestfile.md">/MANIFESTFILE</a></td><td>Changes the default name of the manifest file.</td></tr>
<tr><td><a href="map.md">/Map</a></td><td>Creates a mapfile.</td></tr>
<tr><td><a href="merge.md">/MERGE</a></td><td>Combines sections.</td></tr>
<tr><td><a href="nodefaultlib.md">/NODefaultlib</a></td><td>Ignores all (or the specified) default libraries when external references are resolved.</td></tr>
<tr><td><a href="nologo.md">/NOLogo</a></td><td>Suppresses the startup banner.</td></tr>
<tr><td><a href="norelocs.md">/NORelocs</a></td><td>ELF option.</td></tr>
<tr><td><a href="nxcompat.md">/NXCOMPAT</a></td><td>Marks an executable as verified to be compatible with the Windows Data Execution Prevention feature.</td></tr>
<tr><td><a href="out.md">/Out</a></td><td>Specifies the output file name.</td></tr>
<tr><td><a href="resource.md">/RESource</a></td><td>Attaches a .RES file to a Win32 program.</td></tr>
<tr><td><a href="section.md">/SECTION</a></td><td>Overrides the attributes of a section.</td></tr>
<tr><td><a href="stack.md">/STack</a></td><td>Sets the size of the stack in bytes.</td></tr>
<tr><td><a href="stub.md">/STUB</a></td><td>Attaches an MS-DOS stub program to a Win32 program.</td></tr>
<tr><td><a href="subsystem.md">/SUBsystem</a></td><td>Tells the operating system how to run the .exe file.</td></tr>
<tr><td><a href="verbose.md">/Verbose</a></td><td>Prints linker progress messages.</td></tr>
<tr><td><a href="version.md">/VERSION</a></td><td>Assigns a version number.</td></tr>
</table>
The Open Watcom Linker User’s Guide

- https://open-watcom.github.io/open-watcom-v2-wikidocs/lguide.pdf

#### See Also

[Asmc Build Tools Reference](../readme.md) | [Asmc Library Manager Reference](../libw/readme.md)
