Asmc Macro Assembler Reference

# Asmc Command-Line Reference

Assembles and links one or more assembly-language source files. The command-line options are case sensitive.

## Syntax

**asmc**[64] [_options_] _filename_ [ [_options_] _filename_] ... [-link _link\_options_]

_filename_

The name of the file(s) including wildcard.

_options_

Options may be preceded by both a forward slash (/) and a dash (-) in Windows but only a dash in the Linux version. The options are listed in the following table:

### Parameters

<table>
<tr><td width=24%><b>Option</b></td><td><b>Action</b></td></tr>
<tr><td><b></b></td><td><b></b></td></tr>
<tr><td><b>-[0..10][p]</b></td><td>Selects <a href="option-cpu.md">CPU</a>. Not available in ASMC64.</td></tr>
<tr><td><b>-arch</b>:<i>option</i></td><td>Specifies the <a href="option-arch.md">architecture</a> for code generation.</td></tr>
<tr><td><b>-assert</b></td><td>Generate <a href="../directive/dot-assert.md">assert code</a>.</td></tr>
<tr><td><b>-autostack</b></td><td>Calculate <a href="../directive/option-win64.md">required stack space</a> for arguments.</td></tr>
<tr><td><b>-bin</b></td><td>Generate plain binary file.</td></tr>
<tr><td><b>-Bl</b> <i>filename</i></td><td>Selects an alternate <a href="option-link.md">linker</a> in <i>filename</i>.</td></tr>
<tr><td><b>-c</b></td><td>Assembles only. Does no linking.</td></tr>
<tr><td><b>-Cs</b></td><td>Push user registers before <a href="../directive/option-cstack.md">stack-frame</a> is created in a proc.</td></tr>
<tr><td><b>-coff</b></td><td>Generate COFF format object file.</td></tr>
<tr><td><b>-Cp</b></td><td>Preserves case of all user identifiers.</td></tr>
<tr><td><b>-Cu</b></td><td>Maps all identifiers to upper case (default).</td></tr>
<tr><td><b>-Cx</b></td><td>Preserves case in public and extern symbols.</td></tr>
<tr><td><b>-D</b> <i>symbol</i>[=<i>value</i>]</td><td>Defines a text macro with the given name <i>symbol</i>. If <i>value</i> is missing, it's blank. Multiple tokens separated by spaces must be enclosed in quotation marks.</td></tr>
<tr><td><b>-dotname</b></td><td>Allows names of identifiers to begin with a period.</td></tr>
<tr><td><b>-e</b> <i>number</i></td><td>Set error limit number.</td></tr>
<tr><td><b>-elf</b></td><td>Generate 32-bit ELF format object file.</td></tr>
<tr><td><b>-elf64</b></td><td>Generate 64-bit ELF format object file.</td></tr>
<tr><td><b>-endbr</b></td><td>Insert ENDBR instruction at function entry.</td></tr>
<tr><td><b>-EP</b></td><td>Generates a preprocessed source listing (sent to STDOUT). See <b>-Sf</b>.</td></tr>
<tr><td><b>-eq</b></td><td>Don't display error messages.</td></tr>
<tr><td><b>-Fd</b>[<i>filename</i>]</td><td>Write import definition file.</td></tr>
<tr><td><b>-Fe</b> <i>filename</i></td><td>Names the executable file.</td></tr>
<tr><td><b>-Fi</b> <i>filename</i></td><td>Force <i>file</i> to be included.</td></tr>
<tr><td><b>-Fl</b>[<i>filename</i>]</td><td>Generates an assembled code listing. See <b>-Sf</b>.</td></tr>
<tr><td><b>-Fo</b> <i>filename</i></td><td>Names an object file. Se Remarks.</td></tr>
<tr><td><b>-fp</b> <i>number</i></td><td>Set FPU: 0=8087, 2=80287, 3=80387. Not available in ASMC64.</td></tr>
<tr><td><b>-fpc</b></td><td>Disallow floating-point instructions. Not available in ASMC64.</td></tr>
<tr><td><b>-FPi</b></td><td>Generates emulator fix-ups for floating-point arithmetic (mixed language only). Not available in ASMC64.</td></tr>
<tr><td><b>-FPi87</b></td><td>80x87 instructions (default). Not available in ASMC64.</td></tr>
<tr><td><b>-fpic</b></td><td>Enables the generation of position-independent code for ELF64.</td></tr>
<tr><td><b>-fno-pic</b></td><td>Disables the generation of position-independent code for ELF64 (default).</td></tr>
<tr><td><b>-frame</b></td><td>Auto generate unwind information.</td></tr>
<tr><td><b>-Fw</b> <i>filename</i></td><td>Set errors file name.</td></tr>
<tr><td><b>-Gc</b></td><td>Specifies use of FORTRAN- or Pascal-style function calling and naming conventions.</td></tr>
<tr><td><b>-Gd</b></td><td>Specifies use of C-style function calling and naming conventions.</td></tr>
<tr><td><b>-Ge</b></td><td>Emit a conditional _chkstk() inside the prologue.</td></tr>
<tr><td><b>-Gr</b></td><td>Specifies use of FASTCALL-style function calling and naming conventions.</td></tr>
<tr><td><b>-Gs</b></td><td>Specifies use of SYSCALL (System V)-style function calling and naming conventions.</td></tr>
<tr><td><b>-Gv</b></td><td>Specifies use of VECTORCALL-style function calling and naming conventions.</td></tr>
<tr><td><b>-Gw</b></td><td>Specifies use of WATCALL-style function calling and naming conventions.</td></tr>
<tr><td><b>-Gz</b></td><td>Specifies use of STDCALL-style function calling and naming conventions. Defines _STDCALL_SUPPORTED.</td></tr>
<tr><td><b>-help</b></td><td>Displays a summary of Asmc command-line syntax and options.</td></tr>
<tr><td><b>-homeparams</b></td><td>Forces parameters passed in registers to be written to their locations on the stack upon function entry.</td></tr>
<tr><td><b>-I</b> <i>pathname</i></td><td>Sets path for include file.</td></tr>
<tr><td><b>-idd</b></td><td>Assemble source as <a href="option-idd.md">binary data</a>.</td></tr>
<tr><td><b>-iddt</b></td><td>Assemble source as <a href="option-idd.md">text file</a>.</td></tr>
<tr><td><b>-link</b></td><td>The link options. For more information, see <a href="option-link.md">Linker options</a>.</td></tr>
<tr><td><b>-logo</b></td><td>Print logo string and exit.</td></tr>
<tr><td><b>-m</b>&lt;<i>model</i>&gt;</td><td>Set <a href="option-m.md">memory model</a>. Not available in ASMC64.</td></tr>
<tr><td><b>-MD[d]</b></td><td>Defines _MSVCRT [_DEBUG].</td></tr>
<tr><td><b>-MT[d]</b></td><td>Defines _MT [_DEBUG].</td></tr>
<tr><td><b>-mz</b></td><td>Generate DOS MZ binary file. Not available in ASMC64.</td></tr>
<tr><td><b>-nc</b> <i>name</i></td><td>Set class name of code segment.</td></tr>
<tr><td><b>-nd</b> <i>name</i></td><td>Set name of data segment.</td></tr>
<tr><td><b>-nm</b> <i>name</i></td><td>Set name of module.</td></tr>
<tr><td><b>-nt</b> <i>name</i></td><td>Set name of text segment.</td></tr>
<tr><td><b>-nolib</b></td><td>Ignore INCLUDELIB directive.</td></tr>
<tr><td><b>-nologo</b></td><td>Suppresses messages for successful assembly.</td></tr>
<tr><td><b>-omf</b></td><td>Generates object module file format (OMF) type of object module.</td></tr>
<tr><td><b>-pe</b></td><td>Generate <a href="option-pe.md">PE</a> binary file, 32/64-bit.</td></tr>
<tr><td><b>-q</b></td><td>Suppress copyright message.</td></tr>
<tr><td><b>-r</b></td><td>Recurse subdirectories with use of wildcards.</td></tr>
<tr><td><b>-Sa</b></td><td>Turns on listing of all available information.</td></tr>
<tr><td><b>-safeseh</b></td><td>Marks the object as either containing no exception handlers or containing exception handlers that are all declared with SAFESEH.</td></tr>
<tr><td><b>-Sf</b></td><td>Adds first-pass listing to listing file.</td></tr>
<tr><td><b>-Sg</b></td><td>Turns on listing of assembly-generated code.</td></tr>
<tr><td><b>-Sn</b></td><td>Turns off symbol table when producing a listing.</td></tr>
<tr><td><b>-Sp</b> <i>alignment</i></td><td>Set segment alignment.</td></tr>
<tr><td><b>-stackalign</b></td><td>Align stack variables to 16-byte.</td></tr>
<tr><td><b>-sysvregs</b></td><td>Ignore RDI and RSI in USES for Linux64.</td></tr>
<tr><td><b>-Sx</b></td><td>Turns on false conditionals in listing.</td></tr>
<tr><td><b>-w</b></td><td>Same as /W0.</td></tr>
<tr><td><b>-W</b>&lt;<i>level</i>&gt;</td><td>Sets the warning level, where <i>level</i> = 0, 1, 2, or 3.</td></tr>
<tr><td><b>-win64</b></td><td>Generate 64-bit COFF object. Defines _WIN64.</td></tr>
<tr><td><b>-ws</b>[<i>codepage</i>]</td><td>Store quoted strings as <a href="../directive/option-wstring.md">Unicode</a>. Defines _UNICODE.</td></tr>
<tr><td><b>-WX</b></td><td>Returns an error code if warnings are generated.</td></tr>
<tr><td><b>-X</b></td><td>Ignore INCLUDE environment path.</td></tr>
<tr><td><b>-Z7</b></td><td>Add full symbolic <a href="option-zi.md">debugging information</a>.</td></tr>
<tr><td><b>-zcw</b></td><td>No decoration for C symbols.</td></tr>
<tr><td><b>-Zd</b></td><td>Generates line-number information in object file.</td></tr>
<tr><td><b>-Zf</b></td><td>Make all symbols public.</td></tr>
<tr><td><b>-zf0</b></td><td>JWasm compatible FASTCALL type: MS (Use -Gr).</td></tr>
<tr><td><b>-zf1</b></td><td>JWasm compatible FASTCALL type: OW (Use -Gw).</td></tr>
<tr><td><b>-Zg</b></td><td>Generate code to <a href="option-zg.md">match Masm</a>.</td></tr>
<tr><td><b>-Zi</b></td><td>Add symbolic <a href="option-zi.md">debugging information</a>.</td></tr>
<tr><td><b>-zlc</b></td><td>No OMF records of data in code. Not available in ASMC64.</td></tr>
<tr><td><b>-zld</b></td><td>No OMF records of far call. Not available in ASMC64.</td></tr>
<tr><td><b>-zlf</b></td><td>Suppress items in COFF: No file entry.</td></tr>
<tr><td><b>-zlp</b></td><td>Suppress items in COFF: No static procs.</td></tr>
<tr><td><b>-zls</b></td><td>Suppress items in COFF: No section aux entry.</td></tr>
<tr><td><b>-Zm</b></td><td>Enable MASM 5.10 compatibility. Not available in ASMC64.</td></tr>
<tr><td><b>-Zne</b></td><td>Disable <a href="option-zne.md">syntax extensions</a> not supported and enable syntax supported by Masm.</td></tr>
<tr><td><b>-Zp</b> <i>alignment</i></td><td>Packs structures of the specified byte boundary.</td></tr>
<tr><td><b>-Zs</b></td><td>Perform syntax check only.</td></tr>
<tr><td><b>-zt</b></td><td>Set <a href="option-zt.md">STDCALL decoration</a>.</td></tr>
<tr><td><b>-Zv8</b></td><td>Enable Masm v8+ PROC visibility.</td></tr>
<tr><td><b>-zze</b></td><td>No export symbol decoration.</td></tr>
<tr><td><b>-zzs</b></td><td>Store name of start address.</td></tr>
</table>

### Remarks

Some command-line options to ASMC and ASMC64 are placement-sensitive. For example, because ASMC and ASMC64 can accept several wildcard options, any corresponding **-Fo** options must be specified before files. When wildcard is used the _filename_ part of the **-Fo** option may be replaced by an  asterisk (*) as the following command-line example illustrates:
```
asmc -c -r *.asm -ws -Fo w* _t*.asm
```

### Environment Variables

<table>
<tr><td><b>INCLUDE</b></td><td>Specifies search path for include files.</td></tr>
<tr><td><b>ASMC</b></td><td>Specifies default command-line options.</td></tr>
<tr><td><b>TEMP</b></td><td>Specifies path for temporary files.</td></tr>
</table>

#### See Also

[Asmc Reference](../readme.md) | [Error Messages](../error/readme.md) | [Predefined macros](../symbol/predefined-macros.md)
