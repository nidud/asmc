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

lq_line struct  ;; item of a line queue
next    ptr_t ?
line    char_t 1 dup(?)
lq_line ends

LineQueue equ <ModuleInfo.line_queue>

    .code

    option procalign:4

;; free items of current line queue

DeleteLineQueue proc uses esi edi

    .for esi = LineQueue.head : esi : esi = edi

        mov edi,[esi].qitem.next
        MemFree(esi)
    .endf
    mov LineQueue.head,NULL
    ret

DeleteLineQueue endp

; Add a line to the current line queue, "printf" format.

tvsprintf proc uses esi edi ebx buffer:string_t, fmt:string_t, argptr:ptr

  local numbuf[64]:char_t
  local fldwidth:uint_t
  local sign:byte, char:byte

    .for ( esi = fmt, edi = buffer : byte ptr [esi] : )

        lodsb
        .if ( al == '%' )

            mov fldwidth,0
            mov sign,0
            mov char,' '
            mov ebx,argptr
            lodsb
            .if ( al == '*' )
                mov eax,[ebx]
                add ebx,4
                .ifs eax < 0
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
            .if ( al == '0' )
                mov char,al
                lodsb
            .endif
            .while ( al >= '0' && al <= '9' )

                movsx eax,al
                imul edx,fldwidth,10
                add eax,edx
                add eax,-48
                mov fldwidth,eax
                lodsb
            .endw

            xor edx,edx
            mov ecx,[ebx]
            add ebx,4
            .if ( al == 'l' )
                lodsb
                mov edx,[ebx]
                add ebx,4
            .elseif ( al == 'd' )
                mov eax,ecx
                cdq
                mov eax,'d'
            .endif
            mov argptr,ebx
            mov ebx,16 ; radix

            .switch al

            .case 'r'
                mov     eax,ResWordTable[ecx*8].name
                movzx   ecx,ResWordTable[ecx*8].len
                xchg    eax,esi
                rep     movsb
                mov     byte ptr [edi],0
                mov     esi,eax
               .endc

            .case 'c'
                .if cl
                    mov [edi],cl
                    inc edi
                .endif
               .endc

            .case 's'
                .if ( ecx == NULL )
                    lea ecx,@CStr("(null)")
                .endif
                mov edx,edi
                .repeat
                    mov al,[ecx]
                    mov [edi],al
                    inc ecx
                    inc edi
                .until !al
                dec edi
                .if ( sign || edi == edx )

                    mov ebx,edi
                    sub ebx,edx

                    .if ( ebx < fldwidth )

                        mov ecx,fldwidth
                        sub ecx,ebx
                        mov al,char
                        rep stosb
                    .endif
                .endif
               .endc

            .case 'd'
                test edx,edx
                .ifs
                    inc bh
                .endif
            .case 'u'
                mov bl,10
            .case 'x'
            .case 'X'

                movzx eax,bl
                shr ebx,8
                mov ebx,myltoa( edx::ecx, &numbuf, eax, ebx, FALSE )

                .if ( !sign && ebx < fldwidth )

                    mov ecx,fldwidth
                    sub ecx,ebx
                    mov al,char
                    rep stosb
                .endif
                mov ecx,ebx
                mov edx,esi
                lea esi,numbuf
                rep movsb
                .if ( sign && ebx < fldwidth )

                    mov ecx,fldwidth
                    sub ecx,ebx
                    mov al,char
                    rep stosb
                .endif
                mov esi,edx
                mov al,[esi-1]

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
    mov byte ptr [edi],0
    mov eax,edi
    sub eax,buffer
    ret

tvsprintf endp

tvfprintf proc file:ptr FILE, fmt:string_t, argptr:ptr

  local buffer[4096]:char_t

    tvsprintf( &buffer, fmt, argptr )
    fwrite( &buffer, 1, eax, file )
    ret

tvfprintf endp

tsprintf proc __cdecl buffer:string_t, fmt:string_t, argptr:vararg

    tvsprintf( buffer, fmt, &argptr )
    ret

tsprintf endp

tprintf proc __cdecl fmt:string_t, argptr:vararg

  local buffer[4096]:char_t

    tvsprintf( &buffer, fmt, &argptr )
    _write( 1, &buffer, eax )
    ret

tprintf endp

; Add a line to the current line queue.

    option dotname

AddLineQueue proc fastcall uses esi edi ebx lines:string_t

    mov     esi,lines
    mov     edi,lines
    xor     eax,eax
    mov     ecx,-1
    repnz   scasb
    not     ecx
    mov     ebx,ecx
    dec     ebx
    jz      .3
.0:
    mov     edi,esi
    mov     ecx,ebx
    mov     eax,10
    repnz   scasb
    setz    al
    sub     edi,eax
    mov     ecx,edi
    sub     ecx,esi
    sub     ebx,ecx
    test    ecx,ecx
    jz      .2

    add     ecx,sizeof(lq_line)
    call    MemAlloc
    xor     ecx,ecx
    mov     [eax].lq_line.next,ecx
    cmp     ecx,LineQueue.head
    jz      .4
    mov     ecx,LineQueue.tail
    mov     [ecx].qnode.next,eax
.1:
    mov     LineQueue.tail,eax
    mov     ecx,edi
    sub     ecx,esi
    lea     edi,[eax].lq_line.line
    rep     movsb
    mov     [edi],cl
.2:
    inc     esi
    dec     ebx
    jg      .0
.3:
    ret
.4:
    mov     LineQueue.head,eax
    jmp     .1

AddLineQueue endp

AddLineQueueX proc fmt:string_t, argptr:vararg

   .new buffer:string_t = alloca( ModuleInfo.max_line_len )
    tvsprintf( buffer, fmt, &argptr )
    AddLineQueue( buffer )
    ret

AddLineQueueX endp

; RunLineQueue() is called whenever generated code is to be assembled. It
; - saves current input status
; - processes the line queue
; - restores input status


RunLineQueue proc uses esi edi

  local oldstat:input_status
  local tokenarray:token_t

    ; v2.03: ensure the current source buffer is still aligned

    mov tokenarray,PushInputStatus( &oldstat )
    inc ModuleInfo.GeneratedCode

    ; v2.11: line queues are no longer pushed onto the file stack.
    ; Instead, the queue is processed directly here.

    .for ( esi = LineQueue.head, LineQueue.head = NULL : esi : esi = edi )

        mov edi,[esi].lq_line.next

        strcpy( CurrSource, &[esi].lq_line.line )
        MemFree( esi )

        .if PreprocessLine( tokenarray )

            ParseLine( tokenarray )
        .endif
    .endf
    dec ModuleInfo.GeneratedCode
    PopInputStatus( &oldstat )
    ret

RunLineQueue endp

InsertLineQueue proc uses esi edi ebx

  local oldstat:input_status
  local tokenarray:token_t

    mov ebx,ModuleInfo.GeneratedCode
    mov tokenarray,PushInputStatus( &oldstat )

    mov ModuleInfo.GeneratedCode,0
    .for ( esi = LineQueue.head, LineQueue.head = NULL : esi : esi = edi )

        mov edi,[esi].lq_line.next

        strcpy( CurrSource, &[esi].lq_line.line )
        MemFree( esi )

        .if PreprocessLine( tokenarray )

            ParseLine( tokenarray )
        .endif
    .endf

    mov ModuleInfo.GeneratedCode,ebx
    PopInputStatus( &oldstat )
    ret

InsertLineQueue endp

    end
