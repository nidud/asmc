
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

AddLineQueueX proc uses esi edi ebx fmt:string_t, argptr:vararg

  local buffer[MAX_LINE_LEN]:char_t

    lea ebx,argptr
    .for ( esi = fmt, edi = &buffer : byte ptr [esi] : )

        lodsb
        .if al == '%'
            lodsb
            .switch al
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

    end
