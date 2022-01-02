; DEF64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include stdio.inc
include winbase.inc
include tchar.inc

    .code

CreateDef proc uses rsi rdi rbx r12 r13 r14 file:string_t, windef:bool

  local dll[256] :char_t,
        def[256] :char_t,
        count    :uint_t

    lea rdi,dll
    lea r14,def
    .if !strrchr(strcpy(rdi, rcx), '.')
        strcat(rdi, ".dll")
    .else
        strcpy(rax, ".dll")
    .endif
    strcpy(strrchr(strcpy(r14, rdi), '.'), ".def")

    .if ( fopen(r14, "wt") == NULL )

        perror(rdi)
       .return( -1 )
    .endif
    mov r13,rax

    .if ( windef )

        _strupr(rdi)
        fprintf(r13,
            "LIBRARY %s\n"
            "EXPORTS\n", rdi)
    .endif

    .if ( LoadLibrary(rdi) == NULL )

        perror(rdi)
        mov byte ptr [strrchr(rdi, '.')],0
        .if ( windef )
            fprintf(r13, "%s_dummy\n", rdi)
        .else
            fprintf(r13, "++%s_dummy.'%s.dll'\n", rdi, rdi)
        .endif
        fclose(r13)
       .return( 0 )
    .endif

    mov r12,rax
    mov rcx,rax
    mov eax,[rcx].IMAGE_DOS_HEADER.e_lfanew
    mov esi,[rcx+rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
    add rsi,rcx
    mov count,[rsi].IMAGE_EXPORT_DIRECTORY.NumberOfNames
    mov ebx,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfNames
    add rbx,rcx

    .for ( esi = 0 : esi < count : esi++ )

        mov eax,[rbx+rsi*4]
        add rax,r12
        .continue .if byte ptr [rax] == '?'

        .if ( windef )
            fprintf(r13, "%s\n", rax)
        .else
            fprintf(r13, "++%s.'%s'\n", rax, rdi)
        .endif
    .endf
    fclose(r13)
    FreeLibrary(r12)
   .return( 1 )

CreateDef endp

main proc argc:int_t, argv:array_t

   .new count:int_t = 0
   .new windef:bool = false

    .if ( ecx == 1 )

        printf("Usage: DEF64 [-windef] <lib-files>\n")
       .return( 1 )
    .endif

    lea ebx,[rcx-1]
    lea rsi,[rdx+8]
    mov rdx,[rsi]

    .if ( dword ptr [rdx] == 'niw-' )

        mov windef,true
        add rsi,8
        dec ebx
    .endif

    .while ebx

        lodsq
        CreateDef(rax, windef)
        dec ebx
        inc count
    .endw
    .if ( count == 0 )
        .return( 1 )
    .endif
    .return( 0 )

main endp

    end _tstart

