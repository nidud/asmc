Asmc Macro Assembler Reference

# Asmc Library Manager Reference

### In This Section

- About LIBW
- Library Manager options

### About LIBW

LIBW is a fork of JWlib.
- https://github.com/Baron-von-Riedesel/jwlink/tree/master/JWlib

The changes in the JWlib sources are:
- added a MS LINK comp.id entry in 64-bit import libs for VS
- added some MS LIB compatible command-line options
- added module-definition (.def) input

### Library Manager options

<table>
<tr><td><b>Option</b></td><td><b>Purpose</b></td></tr>
<tr><td>/DEF:<i>filename</i></td><td>Passes a module-definition (.def) file.</td></tr>
<tr><td>/LIST[:<i>filename</i>]</td><td>Make list (-l)</td></tr>
<tr><td>/MACHINE:{X64|X86}</td><td>Specifies the target platform.</td></tr>
<tr><td>/NODEC</td><td>No symbol decoration (.def input).</td></tr>
<tr><td>/NOLOGO</td><td>Suppresses the startup banner.</td></tr>
<tr><td>/OUT:<i>filename</i></td><td>Specifies the output file name.</td></tr>
</table>

#### See Also

[Asmc Build Tools Reference](../readme.md) | [Asmc Linker Reference](../linkw/readme.md)
