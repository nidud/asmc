
;; handle the line queue.
;; this queue is used for "generated code".

include asmc.inc
include memalloc.inc
include reswords.inc
include input.inc
include parser.inc
include preproc.inc

myltoa proto :uint_t, :string_t, :uint_t, :int_t, :int_t
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

NewLineQueue proc
    ret
NewLineQueue endp

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

;; Add a line to the current line queue, "printf" format.

VLSPrintF proc uses esi edi ebx buffer:string_t, fmt:string_t, argptr:ptr

  local numbuf[16]:char_t

    mov ebx,argptr
    .for ( esi = fmt, edi = buffer : byte ptr [esi] : )

        lodsb
        .if al == '%'
            lodsb
            .switch al
            .case 'q' ; added v2.31.32: qword hex
                push    esi
                push    edi
                push    ebx
                lea     edi,numbuf
                mov     ecx,16
                mov     eax,'0'
                rep     stosb
                mov     eax,[ebx]
                mov     edx,[ebx+4]
                lea     ebx,[edi-1]
                mov     edi,16
                .fors ( : eax || edx || edi > 0 : edi-- )
                    .if !edx
                        mov ecx,16
                        div ecx
                        mov ecx,edx
                        xor edx,edx
                    .else
                        push edi
                        .for ecx = 64, esi = 0, edi = 0 : ecx : ecx--
                            add eax,eax
                            adc edx,edx
                            adc esi,esi
                            adc edi,edi
                            .if edi || esi >= 16
                                sub esi,16
                                sbb edi,0
                                inc eax
                            .endif
                        .endf
                        mov ecx,esi
                        pop edi
                    .endif
                    add ecx,'0'
                    .ifs ecx > '9'
                        add ecx,'A'-'9'-1
                    .endif
                    mov [ebx],cl
                    dec ebx
                .endf
                pop     ebx
                pop     edi
                pop     esi
                add     ebx,8
                mov     ecx,16
                lea     eax,numbuf
                xchg    eax,esi
                rep     movsb
                mov     byte ptr [edi],0
                mov     esi,eax
                .endc
            .case 'r'
                mov     eax,[ebx]
                add     ebx,4
                movzx   ecx,ResWordTable[eax*8].len
                mov     eax,ResWordTable[eax*8].name
                xchg    eax,esi
                rep     movsb
                mov     byte ptr [edi],0
                mov     esi,eax
                .endc
            .case 's'
                mov edx,[ebx]
                add ebx,4
                .repeat
                    mov al,[edx]
                    mov [edi],al
                    inc edx
                    inc edi
                .until !al
                dec edi
                .endc
            .case 'd'
            .case 'u'
            .case 'x'
                mov edx,[ebx]
                add ebx,4
                .if ( al == 'x' )
                    myltoa( edx, edi, 16, FALSE, FALSE )
                    add edi,strlen(edi)
                .else
                    mov eax,1
                    .ifs edx >= 0
                        dec eax
                    .endif
                    myltoa( edx, edi, 10, eax, FALSE )
                    add edi,strlen(edi)
                    ;; v2.07: add a 't' suffix if radix is != 10
                    .endc .if ( ModuleInfo.radix == 10 )
                    mov al,'t'
                    stosb
                .endif
                .endc
            .default
                stosb
            .endsw
       .else
            stosb
       .endif
    .endf
    mov byte ptr [edi],0
    mov eax,buffer
    ret

VLSPrintF endp

LSPrintF proc buffer:string_t, fmt:string_t, argptr:vararg

    VLSPrintF( buffer, fmt, &argptr )
    mov eax,buffer
    ret

LSPrintF endp

AddLineQueueX proc fmt:string_t, argptr:vararg

  local buffer[MAX_LINE_LEN]:char_t

    VLSPrintF( &buffer, fmt, &argptr )
    AddLineQueue(&buffer)
    ret

AddLineQueueX endp


;; RunLineQueue() is called whenever generated code is to be assembled. It
;; - saves current input status
;; - processes the line queue
;; - restores input status


RunLineQueue proc uses esi edi ebx

  local oldstat:input_status

    ;; v2.03: ensure the current source buffer is still aligned
    mov ebx,PushInputStatus(&oldstat)
    inc ModuleInfo.GeneratedCode

    ;; v2.11: line queues are no longer pushed onto the file stack.
    ;; Instead, the queue is processed directly here.

    .for ( esi = LineQueue.head, LineQueue.head = NULL : esi : esi = edi )

        mov edi,[esi].lq_line.next

        strcpy(CurrSource, &[esi].lq_line.line)
        MemFree(esi)

        .if PreprocessLine(CurrSource, ebx)

            ParseLine(ebx)
        .endif
    .endf

    dec ModuleInfo.GeneratedCode
    PopInputStatus( &oldstat )
    ret

RunLineQueue endp

InsertLineQueue proc uses esi edi ebx

  local oldstat:input_status
  local codestate:int_t

    mov codestate,ModuleInfo.GeneratedCode
    mov ebx,PushInputStatus(&oldstat)

    mov ModuleInfo.GeneratedCode,0

    .for ( esi = LineQueue.head, LineQueue.head = NULL : esi : esi = edi )

        mov edi,[esi].lq_line.next

        strcpy(CurrSource, &[esi].lq_line.line)
        MemFree(esi)

        .if PreprocessLine(CurrSource, ebx)

            ParseLine(ebx)
        .endif
    .endf

    mov ModuleInfo.GeneratedCode,codestate
    PopInputStatus( &oldstat )
    ret

InsertLineQueue endp

    end
