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

LineQueue equ <ModuleInfo.line_queue>

    .code

; free items of current line queue

DeleteLineQueue proc __ccall uses rsi rdi

    .for rsi = LineQueue.head : rsi : rsi = rdi

        mov rdi,[rsi].qitem.next
        MemFree(rsi)
    .endf
    mov LineQueue.head,NULL
    ret

DeleteLineQueue endp

; Add a line to the current line queue, "printf" format.

tvsprintf proc __ccall uses rsi rdi rbx r12 r13 buffer:string_t, format:string_t, argptr:ptr

  local numbuf[64]:char_t

    UNREFERENCED_PARAMETER(buffer)
    UNREFERENCED_PARAMETER(format)

    .for ( r12 = r8, rsi = rdx, rdi = rcx : byte ptr [rsi] : )

        lodsb
        .if ( al == '%' )

            mov ebx,' '     ; BH: sign, BL: fill-char
            xor r13d,r13d   ; fldwidth

            lodsb
            .if ( al == '*' )
                mov eax,[r12]
                add r12,8
                .ifs eax < 0
                    mov bh,'-'
                    neg eax
                .endif
                mov r13d,eax
                lodsb
            .endif
            .if ( al == '-' )
                mov bh,al
                lodsb
            .endif
            .if ( al == '0' )
                mov bl,al
                lodsb
            .endif
            .while ( al >= '0' && al <= '9' )

                movsx eax,al
                imul edx,r13d,10
                add eax,edx
                add eax,-48
                mov r13d,eax
                lodsb
            .endw

            xor edx,edx
            mov ecx,[r12]
            .if ( al == 'l' )
                lodsb
                mov rcx,[r12]
                inc edx
            .endif
            add r12,8

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
                    mov [rdi],cl
                    inc rdi
                .endif
               .endc

            .case 's'
                mov rcx,[r12-8]
                .if ( rcx == NULL )
                    lea rcx,@CStr("(null)")
                .endif
                mov rdx,rdi
                .repeat
                    mov al,[rcx]
                    mov [rdi],al
                    inc rcx
                    inc rdi
                .until !al
                dec rdi
                .if ( bh || rdi == rdx )

                    mov r8,rdi
                    sub r8,rdx

                    .if ( r8d < r13d )

                        mov ecx,r13d
                        sub ecx,r8d
                        mov al,bl
                        rep stosb
                    .endif
                .endif
               .endc

            .case 'd'
            .case 'u'
            .case 'x'
            .case 'X'
                xor r9d,r9d
                or  al,0x20
                cmp al,'x'
                mov eax,16
                .ifnz
                    mov eax,10
                    .if edx
                        and rcx,rcx
                    .else
                        and ecx,ecx
                    .endif
                    .ifs
                        inc r9d
                    .endif
                .endif
                mov r9d,myltoa( rcx, &numbuf, eax, r9d, FALSE )

                .if ( !bh && r9d < r13d )

                    mov ecx,r13d
                    sub ecx,r9d
                    mov al,bl
                    rep stosb
                .endif
                mov ecx,r9d
                mov rdx,rsi
                lea rsi,numbuf
                rep movsb
                .if ( bh && r9d < r13d )

                    mov ecx,r13d
                    sub ecx,r9d
                    mov al,bl
                    rep stosb
                .endif
                mov rsi,rdx
                mov al,[rsi-1]

                ; v2.07: add a 't' suffix if radix is != 10

               .endc .if ( ModuleInfo.radix == 10 )
               .endc .if ( al != 'd' && al != 'u' )
                mov al,'t'
                stosb
               .endc
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

tvfprintf proc __ccall file:ptr FILE, format:string_t, argptr:ptr

  local buffer[4096]:char_t

    UNREFERENCED_PARAMETER(format)

    tvsprintf( &buffer, rdx, argptr )
    fwrite( &buffer, 1, eax, file )
    ret

tvfprintf endp

tsprintf proc __ccall buffer:string_t, format:string_t, argptr:vararg

    UNREFERENCED_PARAMETER(buffer)
    UNREFERENCED_PARAMETER(format)

    tvsprintf( rcx, rdx, &argptr )
    ret

tsprintf endp

tprintf proc __ccall format:string_t, argptr:vararg

  local buffer[4096]:char_t

    UNREFERENCED_PARAMETER(format)

    tvsprintf( &buffer, rcx, &argptr )
    _write( 1, &buffer, eax )
    ret

tprintf endp

; Add a line to the current line queue.

    option dotname

AddLineQueue proc __ccall uses rsi rdi rbx line:string_t

    UNREFERENCED_PARAMETER(line)

    mov     rsi,rcx
    mov     rdi,rcx
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

   .new buffer:ptr char_t = alloca(ModuleInfo.max_line_len)

    tvsprintf( rax, fmt, &argptr )
    AddLineQueue(buffer)
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
    inc ModuleInfo.GeneratedCode

    ; v2.11: line queues are no longer pushed onto the file stack.
    ; Instead, the queue is processed directly here.

    .for ( rsi = LineQueue.head, LineQueue.head = NULL : rsi : rsi = rdi )

        mov rdi,[rsi].lq_line.next

        strcpy( CurrSource, &[rsi].lq_line.line )
        MemFree( rsi )

        .if PreprocessLine( tokenarray )

            ParseLine( tokenarray )
        .endif
    .endf
    dec ModuleInfo.GeneratedCode
    PopInputStatus( &oldstat )
    ret

RunLineQueue endp

InsertLineQueue proc __ccall uses rsi rdi rbx

  local oldstat:input_status
  local tokenarray:token_t

    mov ebx,ModuleInfo.GeneratedCode
    mov tokenarray,PushInputStatus( &oldstat )

    mov ModuleInfo.GeneratedCode,0
    .for ( rsi = LineQueue.head, LineQueue.head = NULL : rsi : rsi = rdi )

        mov rdi,[rsi].lq_line.next

        strcpy( CurrSource, &[rsi].lq_line.line )
        MemFree( rsi )

        .if PreprocessLine( tokenarray )

            ParseLine( tokenarray )
        .endif
    .endf

    mov ModuleInfo.GeneratedCode,ebx
    PopInputStatus( &oldstat )
    ret

InsertLineQueue endp

    end
