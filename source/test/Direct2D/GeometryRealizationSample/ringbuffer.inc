
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

    .operator RingBuffer {
        mov [rcx].RingBuffer.m_start,0
        mov [rcx].RingBuffer.m_count,0
        }

    .operator AddT :qword {

        mov r8,rdx
        mov eax,[rcx].RingBuffer.m_start
        add eax,[rcx].RingBuffer.m_count
        mov r9d,maxElements
        xor edx,edx
        div r9d
        mov [rcx].RingBuffer.m_elements[rdx*8],r8

        .if ([rcx].RingBuffer.m_count < maxElements)

            inc [rcx].RingBuffer.m_count

        .else
            mov eax,[rcx].RingBuffer.m_start
            inc eax
            xor edx,edx
            div r9d
            mov [rcx].RingBuffer.m_start,edx
        .endif
        }

    .operator GetFirst {

        .Assert(m_count > 0)

        mov eax,[rcx].RingBuffer.m_start
        mov rax,[rcx].RingBuffer.m_elements[rax*8]
        }

    .operator GetLast {

        .Assert(m_count > 0)

        mov eax,[rcx].RingBuffer.m_start
        add eax,[rcx].RingBuffer.m_count
        dec eax
        mov r8d,maxElements
        xor edx,edx
        div r8d
        mov rax,[rcx].RingBuffer.m_elements[rdx*8]
        }

    .operator GetCount {
        mov eax,[rcx].RingBuffer.m_count
        }

    .operator Reset {
        mov [rcx].RingBuffer.m_start,0
        mov [rcx].RingBuffer.m_count,0
        }

    .ends
    LPRingBuffer typedef ptr RingBuffer
