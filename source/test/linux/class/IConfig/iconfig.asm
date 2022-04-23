include stdio.inc
include malloc.inc
include string.inc
include iconfig.inc

    .code

    option cstack:on

    assume rbx:ptr IConfig
    assume rdi:ptr IConfig

IConfig::IConfig proc

    @ComAlloc(IConfig)
    lea rdx,strcmp
    mov [rax].IConfig.Compare,rdx
    ret

IConfig::IConfig endp

IConfig::Release proc uses rbx

    mov rbx,rdi
    .while rbx
        free([rbx]._name)
        .if [rbx].flags & _I_SECTION
            mov rdi,[rbx]._list
            .if rdi
                [rdi].Release()
            .endif
        .endif
        mov rdi,rbx
        mov rbx,[rbx]._next
        free(rdi)
    .endw
    ret

IConfig::Release endp

TruncateString proc private string:LPSTR

    .repeat

        mov al,[rdi]
        inc rdi

        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .continue(0) .if al == 10
        .continue(0) .if al == 13
    .until 1
    dec rdi

    mov rdx,rdi
    xor eax,eax
    .while [rdi] != al

        inc rdi
    .endw

    .repeat

        .break .if rdi <= rdx

        dec rdi
        mov al,[rdi]
        mov [rdi],ah

        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .continue(0) .if al == 10
        .continue(0) .if al == 13

        mov [rdi],al
        inc rdi

    .until 1

    sub rdi,rdx
    mov rax,rdi
    ret

TruncateString endp

IConfig::Read proc uses rbx r12 r13 r14 file:LPSTR

  local fp:LPFILE, buffer[256]:sbyte

    mov r12,rdi
    mov rbx,rdi
    mov rdi,rsi

    .if fopen(rdi, "rt")

        .for ( r14=rax, r13=&buffer : fgets(r13, 256, r14) : )

            .continue .ifd !TruncateString(r13)

            .if byte ptr [rdx] == '['

                .if strchr(r13, ']')

                    mov byte ptr [rax],0
                    .break .if ![rbx].Create(&[r13+1])
                    mov rbx,rax
                .endif
            .else
                [rbx].Create(rdx)
            .endif
        .endf
        fclose(r14)
        mov rax,r12
    .endif
    ret

IConfig::Read endp

IConfig::Write proc uses rbx r12 r13 file:LPSTR

    mov rbx,rdi
    mov rdi,rsi
    .if fopen(rdi, "wt")

        .for ( r13 = rax : rbx : rbx = [rbx]._next )

            .if [rbx].flags & _I_SECTION

                fprintf(r13, "\n[%s]\n", [rbx]._name)
            .endif

            .for ( r12 = [rbx]._list : r12 : r12 = [r12].IConfig._next )

                mov rdx,[r12].IConfig._name
                mov eax,[r12].IConfig.flags
                .if eax & _I_ENTRY

                    fprintf(r13, "%s=%s\n", rdx, [r12].IConfig.value)
                .elseif eax & _I_COMMENT
                    fprintf(r13, "%s\n", rdx)
                .else
                    fprintf(r13, ";%s\n", rdx)
                .endif
            .endf
        .endf
        fclose(r13)
        mov eax,1
    .endif
    ret

IConfig::Write endp

IConfig::Find proc uses rbx r12 r13 string:LPSTR

    xor r13,r13
    mov r12,rsi
    xor eax,eax

    .while rdi

        .if ( [rdi].flags & ( _I_SECTION or _I_ENTRY ) )

            mov rbx,rdi
            .if !( [rbx].Compare([rbx]._name, r12) )

                mov rdx,r13
                mov rdi,rbx
                mov rax,rbx
                .break
            .endif
            xor eax,eax
            mov rdi,rbx
        .endif
        mov r13,rdi
        mov rdi,[rdi]._next
    .endw
    ret

IConfig::Find endp

IConfig::GetValue proc uses rbx Section:LPSTR, Entry:LPSTR

    mov rbx,rdx
    .if [rdi].Find(rsi)

        mov rax,[rdi]._list
        .if rax

            [rax].IConfig.Find(rbx)
        .endif
    .endif
    ret

IConfig::GetValue endp

IConfig::Create proc uses rbx r12 r13 r14 format:LPSTR, argptr:VARARG

 local string[256]:sbyte

    mov rbx,rdi
    lea r13,string

    .repeat

        .break .ifd !vsprintf(r13, rsi, rax)
        .break .ifd !TruncateString(r13)

        xor r12,r12
        mov r13,rdx

        .if byte ptr [rdx] != ';'

            mov al,'='
            mov rdi,rdx
            repnz scasb
            .ifz
                mov r12,rdi
                mov byte ptr [rdi-1],0
                mov r13,rdx
                TruncateString(r12)
                TruncateString(r13)
                mov rdx,r13
            .endif
            mov r13,rdx
        .endif

        .break .if [rbx].Find(rdx)
        .break .if !IConfig::IConfig(NULL)

        mov ecx,_I_SECTION
        .if r12
            mov byte ptr [r12-1],'='
            mov ecx,_I_ENTRY
        .elseif byte ptr [r13] == ';'
            mov ecx,_I_COMMENT
        .endif
        mov [rax].IConfig.flags,ecx

        mov r14,r13
        mov r13,rax

        .break .if !malloc( &[ strlen( r14 ) + 1 ] )
        mov [r13].IConfig._name,strcpy( rax, r14 )

        mov rax,[rbx]._next
        .if r12 && [rbx].flags & _I_SECTION

            mov rax,[rbx]._list
            .if !rax

                mov [rbx]._list,r13
                xor rbx,rbx
            .endif
        .endif

        .while rax

            mov rbx,rax
            mov rax,[rbx]._next
        .endw

        .if rbx

            mov [rbx]._next,r13
        .endif

        mov rbx,r13
        .if r12

            .if strchr([rbx]._name, '=')

                mov byte ptr [rax],0
                inc rax
                mov [rbx].value,rax
            .endif
        .endif

        mov rax,r13
    .until 1
    mov rdi,rax
    ret

IConfig::Create endp

IConfig::Delete proc SectionName:LPSTR

    .if [rdi].Find(rsi)

        .if rdx

            [rax].IConfig.Unlink(rdx)
        .endif
    .endif
    ret

IConfig::Delete endp

IConfig::Unlink proc Parent:ptr IConfig

    mov rax,[rdi]._next
    mov [rsi].IConfig._next,rax
    xor eax,eax
    mov [rdi]._next,rax
    [rdi].Release()
    ret

IConfig::Unlink endp

    END
