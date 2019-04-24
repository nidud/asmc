Asmc Macro Assembler Reference

### OPTION DLLIMPORT

This option makes the assembler assume that all PROTOs that follow this directive represent functions located in a dll. Syntax:

**OPTION DLLIMPORT**:<dll_name> | NONE

<dll_name> must be enclosed in angle brackets. Argument NONE will switch back to the default mode.

#### Sample

The following sample builds two files with the following command:

    asmc -pe -win64 main.asm -Fo extern.dll extern.asm

The dll file imports printf() and export dllproc():

    .code ; extern.asm

    option dllimport:<msvcrt>
    printf proto :ptr, :vararg

    dllproc proc export
    printf("dllproc() called\n")
    ret
    dllproc endp

    DllMain::
    mov eax,1
    ret
    end DllMain

The main file import exit() and dllproc():

    .code ; main.asm

    option dllimport:<msvcrt>
    exit proto :dword
    option dllimport:<extern>
    dllproc proto

    main proc
    dllproc()
    exit(0)
    main endp

    end main

#### See Also

[Directives Reference](readme.md)
