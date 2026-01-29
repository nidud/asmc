
;/******************************************************************
;*                                                                 *
;*  RingBuffer                                                     *
;*                                                                 *
;******************************************************************/

TIME_RING_BUFFER_SIZE equ 4

maxElements equ TIME_RING_BUFFER_SIZE

.template RingBuffer

    m_start     UINT ?
    m_count     UINT ?
    m_elements  dq maxElements dup(?)

    .inline RingBuffer {
        mov [rcx].RingBuffer.m_start,0
        mov [rcx].RingBuffer.m_count,0
        }

    .inline AddT :qword {

        mov eax,[rcx].RingBuffer.m_start
        add eax,[rcx].RingBuffer.m_count
        and eax,maxElements-1
        mov [rcx].RingBuffer.m_elements[rax*8],rdx
        .if ([rcx].RingBuffer.m_count < maxElements)
            inc [rcx].RingBuffer.m_count
        .else
            mov eax,[rcx].RingBuffer.m_start
            inc eax
            and eax,maxElements-1
            mov [rcx].RingBuffer.m_start,eax
        .endif
        }

    .inline GetFirst {

        .Assert(m_count > 0)

        mov eax,[rcx].RingBuffer.m_start
        mov rax,[rcx].RingBuffer.m_elements[rax*8]
        }

    .inline GetLast {

        .Assert(m_count > 0)

        mov eax,[rcx].RingBuffer.m_start
        add eax,[rcx].RingBuffer.m_count
        dec eax
        and eax,maxElements-1
        mov rax,[rcx].RingBuffer.m_elements[rax*8]
        }

    .inline GetCount {
        mov eax,[rcx].RingBuffer.m_count
        }

    .inline Reset {
        mov [rcx].RingBuffer.m_start,0
        mov [rcx].RingBuffer.m_count,0
        }

    .ends
    LPRingBuffer typedef ptr RingBuffer
