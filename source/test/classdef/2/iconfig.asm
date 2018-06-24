include stdio.inc
include malloc.inc
include string.inc
ifndef __ICONFIG_INC
include iconfig.inc
endif

    .data

    virtual_table label qword
        dq IConfig_Release
        dq IConfig_Read
        dq IConfig_Write
        dq IConfig_Find
        dq IConfig_Create
        dq IConfig_Delete
        dq IConfig_GetValue
        dq IConfig_Unlink

    .code

    option win64:nosave
    option cstack:on

    assume rcx:ptr IConfig
    assume rbx:ptr IConfig

IConfig::IConfig proc

    .repeat
        .if !rcx

            .break .if !malloc( sizeof(IConfig) )
            mov rcx,rax
        .endif
        lea rax,virtual_table
        mov [rcx].lpVtbl,rax
        xor eax,eax
        mov [rcx]._next,rax
        mov [rcx]._name,rax
        mov [rcx]._list,rax
        mov [rcx].flags,eax
ifdef __PE__
        mov rax,__imp_strcmp
else
        lea rax,strcmp
endif
        mov [rcx].Compare,rax
        mov rax,rcx
    .until 1
    ret
ifdef __PE__
    strcmp(rcx, rdx) ; __imp_strcmp
endif
IConfig::IConfig endp

IConfig::Release proc uses rbx

    mov rbx,rcx
    .while rbx
        free([rbx]._name)
        .if [rbx].flags & _I_SECTION
            mov rcx,[rbx]._list
            .if rcx
                [rcx].Release()
            .endif
        .endif
        mov rcx,rbx
        mov rbx,[rbx]._next
        free(rcx)
    .endw
    ret

IConfig::Release endp

TruncateString proc private string:LPSTR

    .repeat

        mov al,[rcx]
        inc rcx

        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .continue(0) .if al == 10
        .continue(0) .if al == 13
    .until 1
    dec rcx

    mov rdx,rcx
    xor eax,eax
    .while [rcx] != al

        inc rcx
    .endw

    .repeat

        .break .if rcx <= rdx

        dec rcx
        mov al,[rcx]
        mov [rcx],ah

        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .continue(0) .if al == 10
        .continue(0) .if al == 13

        mov [rcx],al
        inc rcx

    .until 1

    sub rcx,rdx
    mov rax,rcx
    ret

TruncateString endp

IConfig::Read proc uses rsi rdi rbx r12 file:LPSTR

  local fp:LPFILE, buffer[256]:sbyte

    mov r12,rcx
    mov rbx,rcx
    .if fopen(rdx, "rt")

        .for ( rdi=rax, rsi=&buffer : fgets(rsi, 256, rdi) : )

            .continue .ifd !TruncateString(rsi)

            .if byte ptr [rdx] == '['

                .if strchr(rsi, ']')

                    mov byte ptr [rax],0
                    .break .if ![rbx].Create(&[rsi+1])
                    mov rbx,rax
                .endif
            .else
                [rbx].Create(rdx)
            .endif
        .endf
        fclose(rdi)
        mov rax,r12
    .endif
    ret

IConfig::Read endp

IConfig::Write proc uses rsi rdi rbx file:LPSTR

    mov rbx,rcx
    .if fopen(rdx, "wt")

        .for ( rdi=rax : rbx : rbx=[rbx]._next )

            .if [rbx].flags & _I_SECTION

                fprintf(rdi, "\n[%s]\n", [rbx]._name)
            .endif

            .for ( rsi=[rbx]._list : rsi : rsi=[rsi].IConfig._next )

                mov r8,[rsi].IConfig._name
                mov eax,[rsi].IConfig.flags
                .if eax & _I_ENTRY

                    fprintf(rdi, "%s=%s\n", r8, [rsi].IConfig.value)
                .elseif eax & _I_COMMENT
                    fprintf(rdi, "%s\n", r8)
                .else
                    fprintf(rdi, ";%s\n", r8)
                .endif
            .endf
        .endf
        fclose(rdi)
        mov eax,1
    .endif
    ret

IConfig::Write endp

IConfig::Find proc uses rsi rdi rbx string:LPSTR

    xor edi,edi
    mov rsi,rdx
    xor eax,eax

    .while rcx

        .if ( [rcx].flags & ( _I_SECTION or _I_ENTRY ) )

            mov rbx,rcx
            .if !( [rbx].Compare([rbx]._name, rsi) )

                mov rdx,rdi
                mov rcx,rbx
                mov rax,rbx
                .break
            .endif
            xor eax,eax
            mov rcx,rbx
        .endif
        mov rdi,rcx
        mov rcx,[rcx]._next
    .endw
    ret

IConfig::Find endp

IConfig::GetValue proc uses rsi rdi rbx Section:LPSTR, Entry:LPSTR

    mov rbx,rcx
    mov rsi,rdx
    mov rdi,r8

    .if [rbx].Find(rdx)

        mov rax,[rcx]._list
        .if rax

            [rax].IConfig.Find(rdi)
        .endif
    .endif
    ret

IConfig::GetValue endp

    option win64:save

IConfig::Create proc uses rsi rdi rbx r12 format:LPSTR, argptr:VARARG

 local string[256]:sbyte

    mov rbx,rcx
    lea rdi,string

    .repeat

        .break .ifd !vsprintf(rdi, rdx, &argptr)
        .break .ifd !TruncateString(rdi)

        xor esi,esi
        mov rdi,rdx

        .if byte ptr [rdx] != ';'

            mov al,'='
            repnz scasb
            .ifz
                mov rsi,rdi
                mov byte ptr [rdi-1],0
                mov rdi,rdx
                TruncateString(rsi)
                TruncateString(rdi)
                mov rdx,rdi
            .endif
            mov rdi,rdx
        .endif

        .break .if [rbx].Find(rdx)
        .break .if !IConfig::IConfig(NULL)

        mov ecx,_I_SECTION
        .if esi
            mov byte ptr [rsi-1],'='
            mov ecx,_I_ENTRY
        .elseif byte ptr [rdi] == ';'
            mov ecx,_I_COMMENT
        .endif
        mov [rax].IConfig.flags,ecx

        mov r12,rdi
        mov rdi,rax

        .break .if !malloc( &[ strlen( r12 ) + 1 ] )
        mov [rdi].IConfig._name,strcpy( rax, r12 )

        mov rax,[rbx]._next
        .if esi && [rbx].flags & _I_SECTION

            mov rax,[rbx]._list
            .if !rax

                mov [rbx]._list,rdi
                xor rbx,rbx
            .endif
        .endif

        .while rax

            mov rbx,rax
            mov rax,[rbx]._next
        .endw

        .if rbx

            mov [rbx]._next,rdi
        .endif

        mov rbx,rdi
        .if esi

            .if strchr([rbx]._name, '=')

                mov byte ptr [rax],0
                inc rax
                mov [rbx].value,rax
            .endif
        .endif

        mov rax,rdi
    .until 1
    mov rcx,rax
    ret

IConfig::Create endp

    option win64:nosave

IConfig::Delete proc SectionName:LPSTR

    .if [rcx].Find(rdx)

        .if rdx

            [rax].IConfig.Unlink(rdx)
        .endif
    .endif
    ret

IConfig::Delete endp

IConfig::Unlink proc Parent:LPICONFIG

    mov rax,[rcx]._next
    mov [rdx].IConfig._next,rax
    xor eax,eax
    mov [rcx]._next,rax
    [rcx].Release()
    ret

IConfig::Unlink endp

ifndef __PE__
IEND equ <end>
else
IEND equ <>
endif
    IEND
