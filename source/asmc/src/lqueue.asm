; LQUEUE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; handle the line queue.
; this queue is used for "generated code".
;

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

;; Add a line to the current line queue.

AddLineQueue proc uses esi edi line:string_t

    mov esi,line
    mov edi,strlen(esi)
    MemAlloc( &[edi+sizeof(lq_line)] )
    mov [eax].lq_line.next,0
    .if ( LineQueue.head == NULL )
        mov LineQueue.head,eax
    .else ;; insert at the tail
        mov ecx,LineQueue.tail
        mov [ecx].qnode.next,eax
    .endif
    mov LineQueue.tail,eax
    lea ecx,[edi+1]
    lea edi,[eax].lq_line.line
    rep movsb
    ret

AddLineQueue endp

; Add a line to the current line queue, "printf" format.

tvsprintf proc private uses esi edi ebx buffer:string_t, fmt:string_t, argptr:ptr

  local numbuf[64]:char_t
  local fldwidth:uint_t

    .for ( esi = fmt, edi = buffer : byte ptr [esi] : )

        lodsb
        .if ( al == '%' )

            mov fldwidth,0
            lodsb
            .while ( al >= '0' && al <= '9' )

                movsx eax,al
                imul edx,fldwidth,10
                add eax,edx
                add eax,-48
                mov fldwidth,eax
                lodsb
            .endw
            mov ebx,argptr
            xor edx,edx
            mov ecx,[ebx]
            add ebx,4
            .if ( al == 'l' )
                lodsb
                mov edx,[ebx]
                add ebx,4
            .endif
            mov argptr,ebx

            .switch al

            .case 'r'
                mov     eax,ResWordTable[ecx*8].name
                movzx   ecx,ResWordTable[ecx*8].len
                xchg    eax,esi
                rep     movsb
                mov     byte ptr [edi],0
                mov     esi,eax
               .endc

            .case 's'
                .repeat
                    mov al,[ecx]
                    mov [edi],al
                    inc ecx
                    inc edi
                .until !al
                dec edi
               .endc

            .case 'd'
            .case 'u'
            .case 'x'
            .case 'X'
                xor ebx,ebx
                or  al,0x20
                cmp al,'x'
                mov eax,16
                .ifnz
                    mov eax,10
                    and ecx,ecx
                    .ifs
                        inc ebx
                    .endif
                .endif

                .if ( myltoa( edx::ecx, &numbuf, eax, ebx, FALSE ) < fldwidth )

                    mov ecx,fldwidth
                    sub ecx,eax
                    mov edx,eax
                    mov al,'0'
                    rep stosb
                    mov eax,edx
                .endif
                mov ecx,eax
                mov edx,esi
                lea esi,numbuf
                rep movsb
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

tsprintf proc __cdecl buffer:string_t, fmt:string_t, argptr:vararg

    tvsprintf( buffer, fmt, &argptr )
    ret

tsprintf endp

AddLineQueueX proc __cdecl fmt:string_t, argptr:vararg

  local buffer:ptr char_t

    mov buffer,alloca(ModuleInfo.max_line_len)

    tvsprintf( buffer, fmt, &argptr )
    AddLineQueue(buffer)
    ret

AddLineQueueX endp


;; RunLineQueue() is called whenever generated code is to be assembled. It
;; - saves current input status
;; - processes the line queue
;; - restores input status


RunLineQueue proc uses esi edi

  local oldstat:input_status
  local tokenarray:token_t

    ;; v2.03: ensure the current source buffer is still aligned
    mov tokenarray,PushInputStatus( &oldstat )
    inc ModuleInfo.GeneratedCode

    ;; v2.11: line queues are no longer pushed onto the file stack.
    ;; Instead, the queue is processed directly here.

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
