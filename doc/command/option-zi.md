Asmc Macro Assembler Reference

## option -Zi

#### CodeView Symbolic Debug.

Asmc allows in addition to **CV4** (default), **CV5** and **CV8** debug format.

<table>
<tr><td><b>CV4</b></td><td><b>CV5</b></td><td><b>CV8</b></td><td><b>Symbols for</b></td></tr>
<tr><td>-Zi0</td><td>-Zi05</td><td>-Zi08</td><td>Globals</td></tr>
<tr><td>-Zi1</td><td>-Zi15</td><td>-Zi18</td><td>Globals and Locals</td></tr>
<tr><td><b>-Zi</b></td><td>-Zi25</td><td><b>-Z7</b></td><td>Globals, Locals and Types</td></tr>
<tr><td>-Zi3</td><td>-Zi35</td><td>-Zi38</td><td>Globals, Locals, Types and Constants</td></tr>
</table>

#### See Also

[Asmc Command-Line Reference](readme.md)
