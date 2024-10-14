Asmc Macro Assembler Reference

## option -pe

Option -pe will make Asmc create a binary in Windows PE format.

#### Extended options

<table>
<tr><td><b>Option</b></td><td><b>Global</b></td><td><b></b></td></tr>
<tr><td>-pec</td><td>__CUI__</td><td>Subsystem Console (default)</td></tr>
<tr><td>-peg</td><td>__GUI__</td><td>Subsystem Windows</td></tr>
<tr><td>-ped</td><td>__DLL__</td><td>Builds a DLL</td></tr>
</table>

You can use the [comment](../directive/dot-pragma.md) pragma to specify some linker options.

Valid options are [/BASE](../tools/linkw/base.md), [/ENTRY](../tools/linkw/entry.md), [/FIXED](../tools/linkw/fixed.md), [/LARGEADDRESSAWARE](../tools/linkw/largeaddressaware.md), [/SUBSYSTEM](../tools/linkw/subsystem.md), and [/DLL](../tools/linkw/dll.md).

#### See Also

[Asmc Command-Line Reference](readme.md) | [OPTION DLLIMPORT](../directive/option-dllimport.md)
