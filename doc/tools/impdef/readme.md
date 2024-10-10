Asmc Macro Assembler Reference

# Asmc Module Definition Manager Reference

### In This Section

- About IMPDEF
- Module Definition Manager options

### About IMPDEF

IMPDEF creates Module Definition (.def) files from .DLL files.

The 32-bit vesion works differently as it scans the functions for a RET [_size_] instruction to create the STDCALL mangle symbole.

### Module Definition Manager options

Usage: IMPDEF [ options ] _dllfile_ [ [ options ] _dllfile_ ... ]

<table>
<tr><td><b>Option</b></td><td><b>Purpose</b></td></tr>
<tr><td>-q</td><td>Operate quietly</td></tr>
<tr><td>-nologo</td><td>Suppress copyright message</td></tr>
<tr><td>-c[-]</td><td>Specify C calling convention</td></tr>
<tr><td>-c++</td><td>Include C++ functions</td></tr>
<tr><td>-p#</td><td>Set output directory</td></tr>
</table>

#### See Also

[Asmc Build Tools Reference](../readme.md) | [Asmc Reference](../../readme.md)
