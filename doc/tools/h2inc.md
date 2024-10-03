Asmc Macro Assembler Reference

# Asmc C Include File Translator

### In This Section

- About H2INC
- C Include File Translator options

### About H2INC

Converts C header (.h) files into Asmc-compatible include (.inc) files.

### C Include File Translator options

Usage: H2INC [ options ] filename

<table>
<tr><td><b>Option</b></td><td><b>Purpose</b></td></tr>
<tr><td>-q</td><td>Operate quietly</td></tr>
<tr><td>-nologo</td><td>Suppress copyright message</td></tr>
<tr><td>-c#</td><td>Specify string (calling convention) for PROTO</td></tr>
<tr><td>-v#</td><td>Specify string for PROTO using VARARG</td></tr>
<tr><td>-b</td><td>Add &lt;brackets&gt; on define &lt;ID&gt;</td></tr>
<tr><td>-m</td><td>Skip empty macro lines followed by a blank</td></tr>
<tr><td>-f#</td><td>Strip functon: -f__attribute__</td></tr>
<tr><td>-Fo#</td><td>Name of output file (default is <i>input</i>.inc</td></tr>
<tr><td>-w#</td><td>Strip word (a valid identifier)</td></tr>
<tr><td>-s#</td><td>Strip string</td></tr>
<tr><td>-r# #</td><td>Replace string</td></tr>
<tr><td>-o# #</td><td>Replace output string</td></tr>
</table>

Note that "quotes" are stripped so use -r"\\"old\\"" "\\"new\\"" to replace actual "quoted strings".

#### See Also

[Asmc Build Tools Reference](readme.md) | [Asmc Reference](../readme.md)
