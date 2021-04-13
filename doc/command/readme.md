Asmc Macro Assembler Reference

## Asmc Command-Line Reference

Assembles and links one or more assembly-language source files. The command-line options are case sensitive.

**ASMC** [[options]] filename [[ [[options]] filename]]

_options_

The options listed in the following table.

| Option | Meaning |
| ------ |:------- |
| **/[0..10]**[p] | Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486, 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64\. [p] allows privileged instructions. |
| **/arch**:AVX[[2][512]] | Specifies the architecture for code generation on x64.  |
| [**/assert**](../directive/dot_assert.md) | Generate .assert(code). |
| **/autostack** | Calculate required stack space for arguments. |
| **/bin** | Generate plain binary file. |
| **/Cs** | Push user registers before [stack-frame](../directive/opt_cstack.md) is created in a proc. |
| **/coff** | Generate COFF format object file. |
| **/Cp** | Preserves case of all user identifiers. |
| **/Cu** | Maps all identifiers to upper case (default). |
| **/cui** | Link switch used with **/pe** -- subsystem:console (default). |
| **/Cx** | Preserves case in public and extern symbols. |
| **/D**_symbol_[[=_value_]] | Defines a text macro with the given name. If value is missing, it is blank. Multiple tokens separated by spaces must be enclosed in quotation marks. |
| **/e**_number_ | Set error limit number. |
| **/elf** | Generate 32-bit ELF object file. Defines _LINUX(1). |
| **/elf64** | Generate 64-bit ELF object file. Defines _LINUX(2) and _WIN64. |
| **/EP** | Generates a preprocessed source listing (sent to STDOUT). See /Sf. |
| **/eq** | Don't display error messages. |
| **/Fd**[_file_] | Write import definition file. |
| **/Fi**_file_ | Force _file_ to be included. |
| **/Fl**[[_filename_]] | Generates an assembled code listing. See /Sf. |
| **/Fo**_filename_ | Names an object file. |
| **/Fw**_filename_ | Set errors file name. |
| **/FPi** | Generates emulator fix-ups for floating-point arithmetic (mixed language only). |
| **/FPi87** | 80x87 instructions (default). |
| **/fpc** | Disallow floating-point instructions. |
| **/fp**_n_ | Set FPU: 0=8087, 2=80287, 3=80387. |
| **/frame** | Auto generate unwind information. |
| **/Gc** | Specifies use of FORTRAN- or Pascal-style function calling and naming conventions. Same as **OPTION LANGUAGE:PASCAL**. |
| **/Gd** | Specifies use of C-style function calling and naming conventions. Same as **OPTION LANGUAGE:C**. |
| **/Ge** | Emit a conditional _chkstk() inside the prologue. |
| **/gui** | Link switch used with **/pe** -- subsystem:windows. |
| **/Gv** | Specifies use of VECTORCALL-style function calling and naming conventions. |
| **/Gz** | Specifies use of STDCALL-style function calling and naming conventions. Defines _STDCALL_SUPPORTED. Same as **OPTION LANGUAGE:STDCALL**. |
| **/homeparams** | Forces parameters passed in registers to be written to their locations on the stack upon function entry. |
| **/I**_pathname_ | Sets path for include file. |
| **/logo** | Print logo string and exit. |
| **/m**[_tscmlhf_] | Set memory model. |
| **/mz** | Generate DOS MZ binary file. |
| **/nc**_name_ | Set class name of code segment. |
| **/nd**_name_ | Set name of data segment. |
| **/nm**_name_ | Set name of module. |
| **/nt**_name_ | Set name of text segment. |
| **/nolib** | Ignore INCLUDELIB directive. |
| **/nologo** | Suppresses messages for successful assembly. |
| **/omf** | Generates object module file format (OMF) type of object module. |
| **/pe** | Generate PE binary file, 32/64-bit. |
| **/pf** | Preserve Flags (Epilogue/Invoke). |
| **/q** | Suppress copyright message. |
| **/r** | Recurse subdirectories with use of wild args. |
| **/Sa** | Turns on listing of all available information. |
| **/safeseh** | Marks the object as either containing no exception handlers or containing exception handlers that are all declared with SAFESEH. |
| **/Sf** | Adds first-pass listing to listing file. |
| **/Sg** | Turns on listing of assembly-generated code. |
| **/Sn** | Turns off symbol table when producing a listing. |
| **/Sp**[n] | Set segment alignment. |
| **/stackalign** | Align stack variables to 16-byte. |
| [**/swc**](../directive/dot_switch.md) | Specifies use of C-style .SWITCH convention (default). |
| [**/swn**](../directive/dot_switch.md) | No jump-table creation in .SWITCH. |
| [**/swp**](../directive/dot_switch.md) | Specifies use of Pascal-style .SWITCH convention (auto break). |
| [**/swr**](../directive/dot_switch.md) | Allows use of register [E]AX or r11 in .SWITCH code. |
| [**/swt**](../directive/dot_switch.md) | Allows use of jump-table creation in .SWITCH code (default). |
| **/Sx** | Turns on false conditionals in listing. |
| **/w** | Same as /W0. |
| **/W**_level_ | Sets the warning level, where _level_ = 0, 1, 2, or 3.|
| **/win64** | Generate 64-bit COFF object. Defines _WIN64. |
| [**/ws**](../directive/opt_wstring.md)[_CodePage_] | Store quoted strings as Unicode. Defines _UNICODE. |
| **/WX** | Returns an error code if warnings are generated. |
| **/X** | Ignore INCLUDE environment path. |
| **/zcw** | No decoration for C symbols. |
| **/Zd** | Generates line-number information in object file. |
| **/Zf** | Make all symbols public. |
| **/zf**[01] | Set FASTCALL type: MS/OW. |
| **/Zg** | Generate code to match Masm. |
| [**/Zi**](Zi.md) | Add symbolic debug info. |
| **/zlc** | No OMF records of data in code. |
| **/zld** | No OMF records of far call. |
| **/zlf** | Suppress items in COFF: No file entry. |
| **/zlp** | Suppress items in COFF: No static procs. |
| **/zls** | Suppress items in COFF: No section aux entry. |
| **/Zm** | Enable MASM 5.10 compatibility. |
| [**/Zne**](Zne.md) | Disable non Masm extensions. |
| [**/Znk**](Znk.md) | Disable non Masm keywords. |
| **/Zp**[[_alignment_]] | Packs structures on the specified byte boundary. |
| **/Zs** | Perform syntax check only. |
| **/zt**[012] | Set STDCALL decoration. |
| **/Zv8** | Enable Masm v8+ PROC visibility. |
| **/zze** | No export symbol decoration. |
| **/zzs** | Store name of start address. |
| _filename_ | The name of the file. |

#### Environment Variables

| | |
| -------- |:------- |
| **INCLUDE** | Specifies search path for include files. |
| **ASMC** | Specifies default command-line options. |
| **TEMP** | Specifies path for temporary files. |

#### See Also

[ASMC Error Messages](../error/readme.md)
