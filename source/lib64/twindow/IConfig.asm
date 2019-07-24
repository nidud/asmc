; ICONFIG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include string.inc
include iconfig.inc

ICMAXLINE equ 256

    .code

    assume rcx:config_t
    assume rbx:config_t


IConfig::Release proc uses rbx

    .for ( rbx = rcx : rbx : )

        free([rbx].Name)

        .if ( [rbx].Flags & _I_SECTION )

            mov rcx,[rbx].List
            .if rcx

                [rcx].Release()
            .endif
        .endif

        mov rcx,rbx
        mov rbx,[rbx].Next

        free(rcx)
    .endf
    ret

IConfig::Release endp


TruncateString proc private string:string_t

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


IConfig::Read proc uses rsi rdi rbx file:string_t

  local fp:LPFILE, buffer[ICMAXLINE]:sbyte

    mov rbx,rcx
    mov rcx,rdx

    .return .if !fopen(rcx, "rt")

    .for ( rdi = rax,
           rsi = &buffer : fgets(rsi, ICMAXLINE, rdi) : )

        .continue .ifd !TruncateString(rsi)

        .if ( byte ptr [rdx] == '[' )

            .if strchr(rsi, ']')

                mov byte ptr [rax],0
                mov rbx,[rbx].Create(&[rsi+1])

                .break .if ![rbx].Create(&[rsi+1])
                 mov rbx,rax
            .endif
        .else

            [rbx].Create(rdx)
        .endif
    .endf

    fclose(rdi)
    mov rax,this
    ret

IConfig::Read endp


IConfig::Write proc uses rsi rdi rbx file:string_t

    mov rbx,rcx
    mov rcx,rdx

    .return .if !fopen(rcx, "wt")

    .for ( rdi = rax : rbx : rbx = [rbx].Next )

        .if [rbx].Flags & _I_SECTION

            fprintf(rdi, "\n[%s]\n", [rbx].Name)
        .endif

        .for ( rsi = [rbx].List : rsi : rsi = [rsi].IConfig.Next )

            mov r8,[rsi].IConfig.Name
            mov eax,[rsi].IConfig.Flags
            .if ( eax & _I_ENTRY )
                fprintf(rdi, "%s=%s\n", r8, [rsi].IConfig.List)
            .elseif eax & _I_COMMENT
                fprintf(rdi, "%s\n", r8)
            .else
                fprintf(rdi, ";%s\n", r8)
            .endif
        .endf
    .endf

    fclose(rdi)
    mov eax,1
    ret

IConfig::Write endp


IConfig::Find proc uses rsi rdi rbx string:string_t

    .for ( edi = 0, eax = 0, rsi = rdx : rcx : rdi = rcx, rcx = [rcx].Next )

        .if ( [rcx].Flags & ( _I_SECTION or _I_ENTRY ) )

            mov rbx,rcx

            .ifd !strcmp([rbx].Name, rsi)

                mov rdx,rdi
                mov rcx,rbx
                .return rbx
            .endif

            xor eax,eax
            mov rcx,rbx
        .endif
    .endf
    ret

IConfig::Find endp


IConfig::GetEntry proc Section:string_t, Entry:string_t

    .if [rcx].Find(rdx)

        mov rax,[rcx].List
        .if rax

            [rax].IConfig.Find(Entry)
        .endif
    .endif
    ret

IConfig::GetEntry endp


IConfig::Create proc uses rsi rdi rbx r12 format:string_t, argptr:vararg

 local string[ICMAXLINE]:sbyte

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
        mov [rax].IConfig.Flags,ecx

        mov r12,rdi
        mov rdi,rax

        .break .if !malloc(&[strlen(r12)+1])
        mov [rdi].IConfig.Name,strcpy(rax, r12)

        mov rax,[rbx].Next
        .if esi && [rbx].Flags & _I_SECTION

            mov rax,[rbx].List
            .if !rax

                mov [rbx].List,rdi
                xor rbx,rbx
            .endif
        .endif

        .while rax
            mov rbx,rax
            mov rax,[rbx].Next
        .endw
        .if rbx
            mov [rbx].Next,rdi
        .endif

        mov rbx,rdi
        .if esi
            .if strchr([rbx].Name, '=')
                mov byte ptr [rax],0
                inc rax
                mov [rbx].List,rax
            .endif
        .endif

        mov rax,rdi
    .until 1
    mov rcx,rax
    ret

IConfig::Create endp


IConfig::Delete proc SectionName:string_t

    .if [rcx].Find(rdx)

        .if rdx

            [rax].IConfig.Unlink(rdx)
        .endif
    .endif
    ret

IConfig::Delete endp


IConfig::Unlink proc Parent:config_t

    mov rax,[rcx].Next
    mov [rdx].IConfig.Next,rax
    xor eax,eax
    mov [rcx].Next,rax
    [rcx].Release()
    ret

IConfig::Unlink endp


    .data
    IConfig_vtable IConfigVtbl { \
        IConfig_Release,
        IConfig_Read,
        IConfig_Write,
        IConfig_Find,
        IConfig_GetEntry,
        IConfig_Create,
        IConfig_Delete,
        IConfig_Unlink }

    .code

IConfig::IConfig proc

    .return .if !malloc(sizeof(IConfig))

    mov rcx,rax
    mov rdx,this
    .if rdx
        mov [rdx],rax
    .endif

    lea rax,IConfig_vtable
    mov [rcx].lpVtbl,rax

    xor eax,eax
    mov [rcx].Next,rax
    mov [rcx].Name,rax
    mov [rcx].List,rax
    mov [rcx].Flags,eax

    mov rax,rcx
    ret

IConfig::IConfig endp

    end
