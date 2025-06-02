Asmc Macro Assembler Reference

## option -zt

Option -zt will fine-tune name decoration for STDCALL symbols. Syntax is:

<table>
<tr><td><b>Option</b></td><td><b>Decoration</b></td></tr>
<tr><td><b>-zt0</b></td><td>None</td></tr>
<tr><td><b>-zt1</b></td><td>Underscore prefix</td></tr>
<tr><td><b>-zt2</b></td><td>Full (default)</td></tr>
</table>

Option **-zt0** will make object modules compatible to ALINK + Win32.lib. It may also ease adding assembly modules to Borland's C++Builder or Delphi projects.

#### See Also

[Asmc Command-Line Reference](readme.md)
