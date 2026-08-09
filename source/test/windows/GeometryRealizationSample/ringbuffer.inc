
; RingBuffer

TIME_RING_BUFFER_SIZE equ 4

maxElements equ TIME_RING_BUFFER_SIZE

.class RingBuffer

    m_start     UINT ?
    m_count     UINT ?
    m_elements  dq maxElements dup(?)

    RingBuffer  proc
    Release     proc
    AddElement  proc :qword
    GetFirst    proc
    GetLast     proc
    GetCount    proc
    Reset       proc
   .ends
