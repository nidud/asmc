; LQUEUE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; handle the line queue.
; this queue is used for "generated code".
;

include io.inc

include asmc.inc
include memalloc.inc
include reswords.inc
include input.inc
include parser.inc
include preproc.inc

extern ResWordTable:ReservedWord

lq_line struct  ; item of a line queue
next    ptr_t ?
line    char_t 1 dup(?)
lq_line ends

LineQueue equ <MODULE.line_queue>

.code

; free items of current line queue

DeleteLineQueue proc __ccall uses rsi rdi

    .for ( rsi = LineQueue.head : rsi : rsi = rdi )

        mov rdi,[rsi].qitem.next
        MemFree(rsi)
    .endf
    mov LineQueue.head,NULL
    ret

DeleteLineQueue endp


; Add a line to the current line queue, "printf" format.

tvsprintf proc __ccall uses rsi rdi rbx buffer:string_t, format:string_t, argptr:ptr

    .new fldwidth:uint_t
    .new radix:uint_t
    .new count:uint_t
    .new sign:char_t
    .new char:char_t
    .new long:char_t
    .new hexoff:char_t
    .new tmpbuf[64]:char_t

    .for ( rdi = ldr(buffer), rsi = ldr(format), rbx = ldr(argptr) : byte ptr [rsi] : )

        lodsb

        .if ( al == '%' )

            mov char,' '
            mov fldwidth,0
            mov sign,0
            mov long,0
            mov radix,10

            lodsb
            .switch al
            .case 's'
                mov rdx,[rbx]
                .if ( rdx )
                    xchg    rdx,rdi
                    mov     ecx,-1
                    xor     eax,eax
                    repnz   scasb
                    mov     eax,ecx
                    mov     rdi,rdx
                    not     eax
                    dec     eax
                    mov     rdx,[rbx]
                    add     rbx,size_t
                    jmp     .1
                .endif
            .case 'r'
                mov     ecx,[rbx]
                add     rbx,size_t
                lea     rdx,ResWordTable
                imul    ecx,ecx,ReservedWord
                cmp     ecx,T_CCALL*ReservedWord
                movzx   eax,[rdx+rcx].ReservedWord.len
                mov     rdx,[rdx+rcx].ReservedWord.name
                jnz     .1
                mov     eax,1
                jmp     .1

            .case 'd'
                mov rax,[rbx]
                add rbx,size_t
ifdef _WIN64
                .if ( !long )
                    movsxd rax,eax
                .endif
                test rax,rax
else
                cdq
                .if ( long )
                    add ebx,4
                    mov edx,[ebx]
                .endif
                test edx,edx
endif
                .ifs
                    mov byte ptr [rdi],'-'
                    inc rdi
                    neg rax
ifndef _WIN64
                    neg edx
                    sbb edx,0
endif
                .endif

            .case 'D'

                mov ecx,63
ifdef _WIN64
                .if ( rax <= 9 )
else
                .if ( eax <= 9 && edx == 0 )
endif
                    add al,'0'
                    mov tmpbuf[rcx],al
                .else
ifdef _WIN64
                    .for ( r8d = radix : rax : ecx-- )

                        xor edx,edx
                        div r8
                        add dl,'0'
                        .if dl > '9'
                            add dl,hexoff
                        .endif
                        mov tmpbuf[rcx],dl
                    .endf
else
                    push esi
                    push edi
                    push ebx

                    .for ( esi = ecx : eax || edx : esi-- )

                        .if ( edx == 0 )

                            div radix
                            mov ecx,edx
                            xor edx,edx
                        .else
                            .for ( ebx = 64, ecx = 0, edi = 0 : ebx : ebx-- )

                                add eax,eax
                                adc edx,edx
                                adc ecx,ecx
                                adc edi,edi
                                .if ( edi || ecx >= radix )
                                    sub ecx,radix
                                    sbb edi,0
                                    inc eax
                                .endif
                            .endf
                        .endif
                        add cl,'0'
                        .if cl > '9'
                            add cl,hexoff
                        .endif
                        mov tmpbuf[esi],cl
                    .endf
                    mov ecx,esi
                    pop ebx
                    pop edi
                    pop esi
endif
                    inc ecx
                .endif

                mov eax,64
                sub eax,ecx
                lea rdx,tmpbuf[rcx]
            .1:
                mov count,eax
                .if ( !sign && eax < fldwidth )

                    mov ecx,fldwidth
                    sub ecx,eax
                    mov al,char
                    rep stosb
                .endif

                mov  ecx,count
                xchg rsi,rdx
                mov  eax,ecx
                rep  movsb
                mov  rsi,rdx

                .if ( sign && eax < fldwidth )

                    mov ecx,fldwidth
                    sub ecx,eax
                    mov al,char
                    rep stosb
                .endif

                ; v2.07: add a 't' suffix if radix is != 10

                mov al,[rsi-1]
                .if ( radix != 10 && ( al == 'd' || al == 'u' ) )
                    mov al,'t'
                    stosb
                .endif
                .endc

            .case 'u'
                mov rax,[rbx]
                add rbx,size_t
ifdef _WIN64
                .if ( !long )
                    mov eax,eax
                .endif
else
                xor edx,edx
                .if ( long )
                    mov edx,[ebx]
                    add ebx,4
                .endif
endif
                .gotosw('D')

            .case 'x'
                mov hexoff,'a'-'9'-1
            .case 'X'
                .if ( al == 'X' )
                    mov hexoff,'A'-'9'-1
                .endif
                mov radix,16
                mov rax,[rbx]
                add rbx,size_t
ifdef _WIN64
                .if ( !long )
                    mov eax,eax
                .endif
else
                xor edx,edx
                .if ( long )
                    mov edx,[ebx]
                    add ebx,4
                .endif
endif
                .gotosw('D')

            .case 'p'
                mov al,'X'
                mov fldwidth,size_t*2
                mov char,'0'
               .gotosw('X')

            .case '*'
                mov eax,[rbx]
                add rbx,size_t
                .ifs ( eax < 0 )
                    mov sign,'-'
                    neg eax
                .endif
                mov fldwidth,eax
                lodsb
               .gotosw
            .case '-'
                mov sign,al
                lodsb
               .gotosw
            .case '.'
                mov char,al
                lodsb
               .gotosw
            .case '0'
                .gotosw('.') .if ( char == ' ' )
            .case '1'
            .case '2'
            .case '3'
            .case '4'
            .case '5'
            .case '6'
            .case '7'
            .case '8'
            .case '9'
                .while ( al >= '0' && al <= '9' )
                    movsx   eax,al
                    imul    edx,fldwidth,10
                    add     eax,edx
                    add     eax,-48
                    mov     fldwidth,eax
                    lodsb
                .endw
                .gotosw
            .case 'l'
                mov long,al
                lodsb
                .if ( al == 'l' )
                    lodsb
                .endif
                .gotosw
            .case 'c'
                mov eax,[rbx]
                add rbx,size_t
               .endc .if ( al == 0 )
            .default
                stosb
            .endsw
       .else
            stosb
       .endif
    .endf
    mov byte ptr [rdi],0
    mov rax,rdi
    sub rax,buffer
    ret

tvsprintf endp


tvfprintf proc __ccall uses rsi rdi file:ptr FILE, format:string_t, argptr:ptr

  local buffer[4096]:char_t

    tvsprintf( &buffer, format, argptr )
    fwrite( &buffer, 1, eax, file )
    ret

tvfprintf endp


tfprintf proc __ccall file:ptr FILE, format:string_t, argptr:vararg

    tvfprintf( ldr(file), ldr(format), &argptr )
    ret

tfprintf endp


tsprintf proc __ccall buffer:string_t, format:string_t, argptr:vararg

    tvsprintf( ldr(buffer), ldr(format), &argptr )
    ret

tsprintf endp


tprintf proc __ccall uses rsi rdi format:string_t, argptr:vararg

  local buffer[4096]:char_t

    tvsprintf( &buffer, format, &argptr )
    _write( 1, &buffer, eax )
    ret

tprintf endp


; Add a line to the current line queue.

AddLineQueue proc fastcall uses rsi rdi rbx lineptr:string_t

    mov     rsi,rcx
    mov     rdi,rsi
    xor     eax,eax
    mov     ecx,-1
    repnz   scasb
    not     ecx
    mov     ebx,ecx
    dec     ebx
    jz      .3
.0:
    mov     rdi,rsi
    mov     ecx,ebx
    mov     eax,10
    repnz   scasb
    setz    al
    sub     rdi,rax
    mov     rcx,rdi
    sub     rcx,rsi
    sub     ebx,ecx
    test    ecx,ecx
    jz      .2

    add     ecx,sizeof(lq_line)
    invoke  MemAlloc,ecx
    xor     ecx,ecx
    mov     [rax].lq_line.next,rcx
    cmp     rcx,LineQueue.head
    jz      .4
    mov     rcx,LineQueue.tail
    mov     [rcx].qnode.next,rax
.1:
    mov     LineQueue.tail,rax
    mov     rcx,rdi
    sub     rcx,rsi
    lea     rdi,[rax].lq_line.line
    rep     movsb
    mov     [rdi],cl
.2:
    inc     rsi
    dec     ebx
    jg      .0
.3:
    ret
.4:
    mov     LineQueue.head,rax
    jmp     .1

AddLineQueue endp


AddLineQueueX proc __ccall fmt:string_t, argptr:vararg

   .new buffer:string_t

    mov buffer,alloc_line()
    tvsprintf( buffer, fmt, &argptr )
    AddLineQueue(buffer)
    free_line(buffer)
    ret

AddLineQueueX endp


; RunLineQueue() is called whenever generated code is to be assembled. It
; - saves current input status
; - processes the line queue
; - restores input status


RunLineQueue proc __ccall uses rsi rdi

  local oldstat:input_status
  local tokenarray:token_t

    ; v2.03: ensure the current source buffer is still aligned

    mov tokenarray,PushInputStatus( &oldstat )
    inc MODULE.GeneratedCode

    ; v2.11: line queues are no longer pushed onto the file stack.
    ; Instead, the queue is processed directly here.

    .for ( rsi = LineQueue.head, LineQueue.head = NULL : rsi : )

        tstrcpy( CurrSource, &[rsi].lq_line.line )
        .if PreprocessLine( tokenarray )

            ParseLine( tokenarray )
        .endif
        mov rcx,rsi
        mov rsi,[rsi].lq_line.next
        MemFree( rcx )
    .endf
    dec MODULE.GeneratedCode
    PopInputStatus( &oldstat )
    ret

RunLineQueue endp


InsertLineQueue proc __ccall uses rsi rdi rbx

  local oldstat:input_status
  local tokenarray:token_t

    mov ebx,MODULE.GeneratedCode
    mov tokenarray,PushInputStatus( &oldstat )

    mov MODULE.GeneratedCode,0
    .for ( rsi = LineQueue.head, LineQueue.head = NULL : rsi : )

        tstrcpy( CurrSource, &[rsi].lq_line.line )
        .if PreprocessLine( tokenarray )

            ParseLine( tokenarray )
        .endif
        mov rcx,rsi
        mov rsi,[rsi].lq_line.next
        MemFree( rcx )
    .endf
    mov MODULE.GeneratedCode,ebx
    PopInputStatus( &oldstat )
    ret

InsertLineQueue endp

    end
