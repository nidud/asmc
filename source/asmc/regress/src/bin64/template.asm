
; v2.31.06 .template

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    option win64:auto
    option casemap:none

.template S syscall

    m_db db ?
    m_dw dw ?
    m_dd dd ?
    m_dq dq ?
    m_r4 real4 ?

    Clear   proc
    Init    proc :word, :byte, :real4, :qword, :dword

    .ends

.template F fastcall

    m_db db ?
    m_dw dw ?
    m_r4 real4 ?

    Clear   proc
    Init    proc :word, :byte, :real4

    .ends


F_Clear macro this
    assume this:ptr F
    mov [this].m_db,0
    mov [this].m_dw,0
    exitm<mov [this].m_r4,0.0>
    endm

F_Init macro this, a, b, c          ; rcx, dx, r8b, xmm3
    assume this:ptr F
    mov [this].m_dw,a
    mov [this].m_db,b
    exitm<movss [this].m_r4,c>
    endm

S_Clear macro this
    assume this:ptr S
    mov [this].m_db,0
    mov [this].m_dw,0
    mov [this].m_dd,0
    mov [this].m_dq,0
    exitm<mov [this].m_r4,0.0>
    endm

S_Init macro this, a, b, c, d, e    ; rdi, si, dl, xmm0, rcx, r8d
    assume this:ptr S
    mov [this].m_dw,a
    mov [this].m_db,b
    movss [this].m_r4,c
    mov [this].m_dq,d
    exitm<mov [this].m_dd,e>
    endm

    .code

foo proc

  local f:F
  local s:S

    f.Clear()
    f.Init(s.m_dw,s.m_db,3.0)
    s.Clear()
    s.Init(f.m_dw,f.m_db,f.m_r4,4,5)
    ret

foo endp

    end
