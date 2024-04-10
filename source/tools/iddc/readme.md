## Asmc Binary Resource Compiler

Compiler for TUI (console/terminal) IDD resource files.

### Iddc Command-Line Reference

Compiles one or more resource files. The command-line options are case sensitive.

**IDDC** [[options]] filename

_options_

The options listed in the following table.

| Option | Meaning |
| ------ |:------- |
| **-coff** | Generate COFF format object file. |
| **-Fo**_filename_ | Names an object file. |
| **-mc** | Set memory model to Compact |
| **-ml** | Set memory model to Large |
| **-mf** | Set memory model to Flat (default) |
| **-omf** | Generates object module file format (OMF) type of object module. |
| **-q** | Suppress copyright message. |
| **-r** | Recurse subdirectories with use of wildcards. |
| **-t** | Compile text file (add zero) |
| **-win64** | Generate 64-bit COFF object. |
| _filename_ | The name of the file. |

