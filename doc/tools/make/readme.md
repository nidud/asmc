Asmc Macro Assembler Reference

# Asmc Program Maintenance Utility Reference

### In This Section

- About MAKE
- Program Maintenance Utility options

### About MAKE

MAKE is a simple make utility but somewhat compatible with GNU MAKE and Watcom WMAKE. It handles both & and \\ as line breaks; **!else** and **else** directives.

### Library Manager options

Usage: MAKE [-/options] [macro=text] [target(s)]

options:

<table>
<tr><td><b>Option</b></td><td><b>Purpose</b></td></tr>
<tr><td>-a</td><td>Build all targets (always set)</td></tr>
<tr><td>-d</td><td>Debug - echo progress of work</td></tr>
<tr><td>-f#</td><td>Full pathname of make file</td></tr>
<tr><td>-h</td><td>Do not print program header</td></tr>
<tr><td>-I</td><td>Ignore exit codes from commands</td></tr>
<tr><td>-I#</td><td>Set include path</td></tr>
<tr><td>-s</td><td>Suppress executed-commands display</td></tr>
</table>

#### See Also

[Asmc Build Tools Reference](../readme.md) | [Asmc Reference](../../readme.md)
