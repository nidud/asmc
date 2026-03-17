Asmc Macro Assembler Reference

## OPTION DLLIMPORT

**OPTION DLLIMPORT**:[ &lt;dll_name&gt; | NONE ]

Use this directive to instruct the assembler that subsequent declarations is imported from a DLL.

- `<dll_name>` must be enclosed in angle brackets, for example `<kernel32.dll>`.
- `NONE` restores the default behavior (no DLL import assumed).

When `OPTION DLLIMPORT` is in effect, declarations that follow will be treated as external DLL imports, allowing the assembler to generate appropriate import references.

Used in conjunction with the `IMPORT` directive, it simplifies the process of accessing imported functions or variables from a DLL.

Example:
```
option dllimport:<msvcrt>
externdef import _dstbias:ptr
exit proto :sdword
printf proto :ptr, :vararg
.code
start proc
    mov rax,_dstbias
    printf("_dstbias: %d\n", [rax])
    exit(0)
    endp
    end start
```
#### See Also

[Option](option.md) | [Directives Reference](readme.md)
