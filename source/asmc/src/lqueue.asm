; LQUEUE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; handle the line queue.
; this queue is used for "generated code".
;

include io.inc
include malloc.inc

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

    .new numbuf[64]:char_t
    .new fldwidth:uint_t
    .new radix:uint_t
    .new sign:char_t
    .new char:char_t

    .for ( rsi = format, rdi = buffer : byte ptr [rsi] : )

        lodsb
        .if ( al == '%' )

            mov char,' '
            mov fldwidth,0
            mov sign,0
            mov rbx,argptr

            lodsb
            .if ( al == '*' )

                mov eax,[rbx]
                add rbx,size_t

                .ifs ( eax < 0 )

                    mov sign,'-'
                    neg eax
                .endif
                mov fldwidth,eax
                lodsb
            .endif

            .if ( al == '-' )

                mov sign,al
                lodsb
            .endif

            .if ( al == '0' || al == '.' )

                mov char,al
                lodsb
            .endif

            .while ( al >= '0' && al <= '9' )

                movsx   eax,al
                imul    edx,fldwidth,10
                add     eax,edx
                add     eax,-48
                mov     fldwidth,eax
                lodsb
            .endw

            xor edx,edx
            mov ecx,[rbx]

            .if ( al == 'l' )
                lodsb
                .if ( al == 'l' )
                    lodsb
                .endif
ifdef _WIN64
                mov rcx,[rbx]
            .elseif ( al == 's' )
                mov rcx,[rbx]
else
                add ebx,4
                mov edx,[ebx]
endif
            .elseif ( al == 'd' )
ifdef _WIN64
                movsxd rcx,ecx
else
                mov eax,ecx
                cdq
                mov eax,'d'
endif
            .endif
            add rbx,size_t
            mov argptr,rbx
            mov ebx,16  ; radix & signed

            .switch al

            .case 'r'
                lea     rdx,ResWordTable
                imul    ecx,ecx,ReservedWord
                mov     rax,[rdx+rcx].ReservedWord.name
                movzx   ecx,[rdx+rcx].ReservedWord.len
                xchg    rax,rsi
                rep     movsb
                mov     byte ptr [rdi],0
                mov     rsi,rax
               .endc

            .case 'c'
                .if cl
                    mov al,cl
                    stosb
                .endif
               .endc

            .case 's'
                .if ( rcx == NULL )
                    lea rcx,@CStr("(null)")
                .endif
                mov rdx,rdi
                .repeat
                    mov al,[rcx]
                    stosb
                    inc rcx
                .until !al
                dec rdi
                .if ( sign || rdi == rdx )

                    mov rax,rdi
                    sub rax,rdx

                    .if ( eax < fldwidth )

                        mov ecx,fldwidth
                        sub ecx,eax
                        mov al,char
                        rep stosb
                    .endif
                .endif
               .endc

            .case 'd'
ifdef _WIN64
                test rcx,rcx
else
                test edx,edx
endif
                sets bh
            .case 'u'
                mov bl,10 ; radix
            .case 'x'
            .case 'X'

                movzx eax,bl
                mov radix,eax
                shr ebx,8
ifdef _WIN64
                mov ebx,myltoa( rcx, &numbuf, eax, ebx, FALSE )
else
                mov ebx,myltoa( edx::ecx, &numbuf, eax, ebx, FALSE )
endif
                .if ( !sign && eax < fldwidth )

                    mov ecx,fldwidth
                    sub ecx,eax
                    mov al,char
                    rep stosb
                .endif

                mov ecx,ebx
                mov rdx,rsi
                lea rsi,numbuf
                rep movsb

                .if ( sign && ebx < fldwidth )

                    mov ecx,fldwidth
                    sub ecx,ebx
                    mov al,char
                    rep stosb
                .endif
                mov rsi,rdx
                mov al,[rsi-1]

                ; v2.07: add a 't' suffix if radix is != 10

               .endc .if ( radix == 10 )
               .endc .if ( al != 'd' && al != 'u' )
                mov al,'t'
                stosb
               .endc

            .case 'p'
                mov rax,argptr
                mov rcx,[rax-size_t]
                mov fldwidth,size_t*2
                mov char,'0'
               .gotosw('X')
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

    tvfprintf( file, format, &argptr )
    ret

tfprintf endp


tsprintf proc __ccall buffer:string_t, format:string_t, argptr:vararg

    tvsprintf( buffer, format, &argptr )
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
    call    MemAlloc
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
