Asmc Macro Assembler Reference

## option -pe

Option -pe will make Asmc create a binary in Windows PE format.

#### Extended options

<table>
<tr><td><b>Option</b></td><td><b>Global</b></td><td><b></b></td></tr>
<tr><td>-pec</td><td>\_\_CUI\_\_</td><td>Subsystem Console (default)</td></tr>
<tr><td>-peg</td><td>\_\_GUI\_\_</td><td>Subsystem Windows</td></tr>
<tr><td>-ped</td><td>\_\_DLL\_\_</td><td>Builds a DLL</td></tr>
</table>

You can use the [comment](../directive/dot-pragma.md) pragma to specify some linker options.

Valid options are [/BASE](../tools/link-base.md), [/ENTRY](../tools/link-entry.md), [/FIXED](../tools/link-fixed.md), [/LARGEADDRESSAWARE](../tools/link-largeaddressaware.md), [/SUBSYSTEM](../tools/link-subsystem.md), and [/DLL](../tools/link-dll.md).

#### See Also

[Asmc Command-Line Reference](readme.md) | [OPTION DLLIMPORT](../directive/option-dllimport.md)
