; ICONFIG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include malloc.inc
include string.inc
include iconfig.inc

ICMAXLINE equ 256

    .code

    assume rcx:config_t
    assume rbx:config_t

IConfig::Unlink proc uses rbx

    ldr rbx,this

    .if ( rbx )

        mov rcx,[rbx].prev
        .if ( rcx )

            .if ( [rcx].type == C_SECTION && [rbx].type == C_ENTRY )
                mov [rcx].entry,NULL
            .else
                mov [rcx].next,NULL
            .endif
        .endif

        .while ( rbx )

            .if ( [rbx].type == C_SECTION )

                IConfig::Unlink([rbx].entry)
            .endif

            mov rcx,rbx
            mov rbx,[rbx].next
            free(rcx)
        .endw
    .endif
    ret

IConfig::Unlink endp


IConfig::Release proc uses rbx

    ldr rbx,this

    IConfig::Unlink([rbx].next)
    free([rbx].name)
    free(rbx)
    ret

IConfig::Release endp


IConfig::Read proc uses rbx

   .new fp:LPFILE
   .new buffer[ICMAXLINE]:sbyte
   .new p:string_t

    ldr rbx,this

    .if ( fopen([rbx].name, "rt") != NULL )

        .for ( fp = rax : fgets(&buffer, ICMAXLINE, fp) : )

            .ifd ( strtrunc(rax) )

                .if ( byte ptr [rcx] == '[' )

                    inc rcx
                    mov p,rcx

                    .if strchr(rcx, ']')

                        mov byte ptr [rax],0
                    .endif
                    mov rbx,IConfig::Append(rbx, p)
                   .break .if ( rbx == NULL )
                .else
                    IConfig::Append(rbx, rcx)
                .endif
            .endif
        .endf
        fclose(fp)
        mov eax,1
    .endif
    ret

IConfig::Read endp


IConfig::Write proc uses rbx

   .new fp:LPFILE
   .new n:config_t

    ldr rbx,this

    .if ( fopen([rbx].name, "wt") != NULL )

        .for ( fp = rax, rbx = [rbx].next : rbx : rbx = [rbx].next )

            .if ( [rbx].type == C_SECTION )

                fprintf(fp, "[%s]\n", [rbx].name)

                .for ( n = rbx, rbx = [rbx].entry : rbx : rbx = [rbx].next )

                    .if ( [rbx].type == C_ENTRY )

                        fprintf(fp, "%s=%s\n", [rbx].name, [rbx].value)
                    .endif
                .endf
                mov rbx,n
            .endif
        .endf
        fclose(fp)
        mov eax,1
    .endif
    ret

IConfig::Write endp


IConfig::Find proc uses rbx string:string_t

    ldr rbx,this

    .for ( : rbx : rbx = [rbx].next )

        .if ( [rbx].type == C_SECTION || [rbx].type == C_ENTRY )

            .ifd !strcmp([rbx].name, string)

                .return( rbx )
            .endif
        .endif
    .endf
    xor eax,eax
    ret

IConfig::Find endp


IConfig::GetEntry proc entry:string_t

    ldr rcx,this
    ldr rdx,entry

    mov rax,[rcx].entry
    .if ( rax )

        .if ( IConfig::Find(rax, rdx) )

            mov rax,[rax].IConfig.value
        .endif
    .endif
    ret

IConfig::GetEntry endp


IConfig::GetID proc uses rbx id:int_t

   .new name[32]:char_t

    ldr rbx,this
    ldr ecx,id

    sprintf(&name, "%d", ecx)
    IConfig::GetEntry(rbx, &name)
    ret

IConfig::GetID endp


IConfig::Append proc uses rbx format:string_t, argptr:vararg

   .new buffer[ICMAXLINE]:char_t
   .new p:string_t
   .new q:string_t
   .new size:int_t
   .new type:int_t

    ldr rbx,this

    .return .ifd !vsprintf(&buffer, format, &argptr)
    .return .ifd !strtrunc(&buffer)

    add eax,IConfig+1
    mov size,eax
    mov p,rcx

    .if ( strchr(rcx, '=') )

        mov byte ptr [rax],0
        strtrunc(&[rax+1])
        mov q,rcx
        strtrunc(p)
        mov type,C_ENTRY
        mov rcx,[rbx].entry
        .if ( rcx )
            IConfig::Remove(rcx, p)
        .endif
    .else
        mov type,C_SECTION
        .return .if IConfig::Find(rbx, p)
        .while [rbx].next
            mov rbx,[rbx].next
        .endw
    .endif
    .return .if !malloc(size)

    mov rcx,[rbx]
    mov [rax],rcx

    .if ( type == C_ENTRY )

        mov rcx,[rbx].entry
        .if ( rcx )
            .while [rcx].next
                mov rcx,[rcx].next
            .endw
            mov [rcx].next,rax
        .else
            mov [rbx].entry,rax
            mov rcx,rbx
        .endif
    .else
        mov [rbx].next,rax
        mov rcx,rbx
    .endif

    mov rbx,rax
    mov [rbx].prev,rcx
    mov [rbx].next,NULL
    add rax,IConfig
    mov [rbx].name,rax
    mov [rbx].type,type
    strcpy([rbx].name, p)

    .if ( type == C_ENTRY )

        strlen(rax)
        add rax,[rbx].name
        inc rax
        mov [rbx].value,rax
        strcpy(rax, q)
    .endif
    mov rax,rbx
    ret

IConfig::Append endp


IConfig::Clear proc uses rbx

    ldr rcx,this

    .if ( [rcx].type == C_SECTION )

        IConfig::Unlink([rcx].entry)
    .endif
    ret

IConfig::Clear endp


IConfig::Remove proc uses rbx name:string_t

    ldr rcx,this
    ldr rdx,name

    .if IConfig::Find(rcx, rdx)

        mov rbx,rax

        IConfig::Clear(rbx)
        mov rcx,[rbx].prev
        mov rax,[rbx].next
        .if ( rax )
            mov [rax].IConfig.prev,rcx
        .endif
        .if ( rcx )
            .if ( [rcx].type == C_SECTION && [rbx].type == C_ENTRY )
                mov [rcx].entry,rax
            .else
                mov [rcx].next,rax
            .endif
        .endif

        free(rbx)
    .endif
    ret

IConfig::Remove endp


IConfig::Update proc uses rbx

    ldr rbx,this

    xor eax,eax
    .if ( [rbx].type == C_BASE )

        IConfig::Unlink([rbx].next)
        IConfig::Read(rbx)
    .endif
    ret

IConfig::Update endp


IConfig::ReadFile proc uses rbx file:string_t

   .new path:string_t

    ldr rbx,this
    xor eax,eax
    .if ( [rbx].type == C_BASE )

        mov path,[rbx].name
        mov [rbx].name,file
        IConfig::Unlink([rbx].next)
        IConfig::Read(rbx)
        mov rcx,path
        mov [rbx].name,rcx
    .endif
    ret

IConfig::ReadFile endp


IConfig::IConfig proc uses rbx file:string_t

   .new path:string_t

    ldr rcx,file
    .if ( rcx )
        mov path,_strdup(rcx)
    .else
        mov path,_strdup(_pgmptr)
        setfext(rax, ".ini")
    .endif

    mov rbx,@ComAlloc(IConfig)
    .if ( rbx )

        mov [rbx].name,path

        xor eax,eax
        mov [rbx].type,C_BASE
        mov [rbx].next,rax
        mov [rbx].prev,rax
        mov [rbx].value,rax
    .endif
    mov rax,rbx
    ret

IConfig::IConfig endp

    end
