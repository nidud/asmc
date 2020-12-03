;
; MD5 Algorithm Description:
;
; https://www.ietf.org/rfc/rfc1321.txt
;
; Note: The code differ from the documentation above and follows
;       the implementation from NTDLL.DLL used in Windows 10.
;

    option win64:3
    option frame:auto

; MD5 context

.template MD5_CTX
    state   dd 4 dup(?)     ; state (ABCD)
    count   dd 2 dup(?)     ; number of bits, modulo 2^64 (lsb first)
    buffer  db 64 dup(?)    ; input buffer
    digest  db 16 dup(?)    ; added: used in MD5Final(ntdll.dll)
   .ends

MD5Init proto :ptr MD5_CTX
MD5Update proto :ptr MD5_CTX, :ptr byte, :dword
MD5Final proto :ptr MD5_CTX ; changed to fit the ntdll.dll version
MD5Transform proto private :ptr dword, :ptr byte

; inline basic MD5 functions

F proto x:dword, y:dword, z:abs { ; (((x) & (y)) | ((~x) & (z)))
    xor y,z
    and x,y
    xor x,z
    }

G proto x:dword, y:dword, z:abs { ; (((x) & (z)) | ((y) & (~z)))
    xor x,y
    and x,z
    xor x,y
    }

H proto x:dword, y:dword, z:abs { ; ((x) ^ (y) ^ (z))
    xor x,y
    xor x,z
    }

I proto x:dword, y:dword, z:abs { ; ((y) ^ ((x) | (~z)))
    not z
    or  x,z
    not z
    xor x,y
    }

; rotates x left n bits

ROTATE_LEFT macro x, n ; (((x) << (n)) | ((x) >> (32-(n))))
    if n le 16
     rol x,n
    else
     ror x,32-n
    endif
    exitm<>
    endm

; transformations for rounds 1, 2, 3, and 4

FF macro f, w, x, y, z, i, ac, s
    add w,[r11+i*4]
    f(x, y, z)
    add w,ecx
    add w,ac
    ROTATE_LEFT(w, s)
    add w,x
    exitm<>
    endm

; MD5 initialization.

.code

; Begins an MD5 operation, writing a new context.

    assume rcx:ptr MD5_CTX

MD5Init proc frame ctx:ptr MD5_CTX

    mov [rcx].state[0x00],0x67452301
    mov [rcx].state[0x04],0xefcdab89
    mov [rcx].state[0x08],0x98badcfe
    mov [rcx].state[0x0C],0x10325476
    mov [rcx].count[0x00],0
    mov [rcx].count[0x04],0
    ret

MD5Init endp

; MD5 block update operation. Continues an MD5 message-digest
; operation, processing another message block, and updating the
; context.

    assume rcx:nothing
    assume rbx:ptr MD5_CTX

MD5Update proc frame uses rsi rdi rbx ctx:ptr MD5_CTX, buf:ptr byte, len:dword

    mov rbx,rcx
    mov r8d,[rbx].count[0]
    mov eax,r8d
    shl eax,3
    add [rbx].count[0],eax
    adc [rbx].count[4],0

    mov eax,r8d
    shr eax,29
    add [rbx].count[4],eax

    mov eax,r8d
    shr eax,3
    and eax,0x3f
    mov rsi,rdx
    mov edi,r8d

    .ifnz

        lea rdi,[rbx].buffer[rax]
        mov ecx,64
        sub ecx,eax
        mov eax,ecx

        .if r8d < ecx

            mov ecx,r8d
            rep movsb
            .return
        .endif
        rep movsb
        mov edi,r8d
        sub edi,eax

        MD5Transform( &[rbx].state, &[rbx].buffer )
    .endif

    .while edi >= 64

        lea rdx,[rbx].buffer
        xchg rdx,rdi
        mov ecx,64
        rep movsb
        mov edi,edx

        MD5Transform( &[rbx].state, &[rbx].buffer )
        sub edi,64
    .endw

    mov ecx,edi
    lea rdi,[rbx].buffer
    rep movsb
    ret

MD5Update endp

; MD5 finalization. Ends an MD5 message-digest operation, writing the
; the message digest and zeroizing the context.

MD5Final proc frame uses rsi rdi rbx ctx:ptr MD5_CTX

    mov rbx,rcx

    mov ecx,[rbx].count
    shr ecx,3
    and ecx,0x3F
    lea rsi,[rbx].buffer
    lea rdi,[rsi+rcx]
    mov al,0x80
    stosb
    mov eax,64 - 1
    sub eax,ecx
    mov ecx,eax
    xor eax,eax

    .if ecx < 8

        rep stosb

        MD5Transform( &[rbx].state, rsi )

        mov rdi,rsi
        mov ecx,56
        xor eax,eax
        rep stosb
    .else

        sub ecx,8
        rep stosb
    .endif

    mov [rsi+14*4],[rbx].count
    mov [rsi+15*4],[rbx].count[4]

    MD5Transform( &[rbx].state, rsi )

    lea rsi,[rbx].state
    lea rdi,[rbx].digest
    mov ecx,16
    rep movsb
    ret

MD5Final endp

; MD5 basic transformation. Transforms state based on block.

MD5Transform proc private frame buf:ptr dword, inp:ptr byte

    mov r11,rdx

    a equ <eax> ; register arguments used
    b equ <r8d>
    c equ <r9d>
    d equ <r10d>

    mov a,[rcx+0x00]
    mov b,[rcx+0x04]
    mov c,[rcx+0x08]
    mov d,[rcx+0x0C]

    ; Round 1

    FF( F, a, b, c, d,  0, 0xd76aa478,  7 )
    FF( F, d, a, b, c,  1, 0xe8c7b756, 12 )
    FF( F, c, d, a, b,  2, 0x242070db, 17 )
    FF( F, b, c, d, a,  3, 0xc1bdceee, 22 )
    FF( F, a, b, c, d,  4, 0xf57c0faf,  7 )
    FF( F, d, a, b, c,  5, 0x4787c62a, 12 )
    FF( F, c, d, a, b,  6, 0xa8304613, 17 )
    FF( F, b, c, d, a,  7, 0xfd469501, 22 )
    FF( F, a, b, c, d,  8, 0x698098d8,  7 )
    FF( F, d, a, b, c,  9, 0x8b44f7af, 12 )
    FF( F, c, d, a, b, 10, 0xffff5bb1, 17 )
    FF( F, b, c, d, a, 11, 0x895cd7be, 22 )
    FF( F, a, b, c, d, 12, 0x6b901122,  7 )
    FF( F, d, a, b, c, 13, 0xfd987193, 12 )
    FF( F, c, d, a, b, 14, 0xa679438e, 17 )
    FF( F, b, c, d, a, 15, 0x49b40821, 22 )

    ; Round 2

    FF( G, a, b, c, d,  1, 0xf61e2562,  5 )
    FF( G, d, a, b, c,  6, 0xc040b340,  9 )
    FF( G, c, d, a, b, 11, 0x265e5a51, 14 )
    FF( G, b, c, d, a,  0, 0xe9b6c7aa, 20 )
    FF( G, a, b, c, d,  5, 0xd62f105d,  5 )
    FF( G, d, a, b, c, 10, 0x02441453,  9 )
    FF( G, c, d, a, b, 15, 0xd8a1e681, 14 )
    FF( G, b, c, d, a,  4, 0xe7d3fbc8, 20 )
    FF( G, a, b, c, d,  9, 0x21e1cde6,  5 )
    FF( G, d, a, b, c, 14, 0xc33707d6,  9 )
    FF( G, c, d, a, b,  3, 0xf4d50d87, 14 )
    FF( G, b, c, d, a,  8, 0x455a14ed, 20 )
    FF( G, a, b, c, d, 13, 0xa9e3e905,  5 )
    FF( G, d, a, b, c,  2, 0xfcefa3f8,  9 )
    FF( G, c, d, a, b,  7, 0x676f02d9, 14 )
    FF( G, b, c, d, a, 12, 0x8d2a4c8a, 20 )

    ; Round 3

    FF( H, a, b, c, d,  5, 0xfffa3942,  4 )
    FF( H, d, a, b, c,  8, 0x8771f681, 11 )
    FF( H, c, d, a, b, 11, 0x6d9d6122, 16 )
    FF( H, b, c, d, a, 14, 0xfde5380c, 23 )
    FF( H, a, b, c, d,  1, 0xa4beea44,  4 )
    FF( H, d, a, b, c,  4, 0x4bdecfa9, 11 )
    FF( H, c, d, a, b,  7, 0xf6bb4b60, 16 )
    FF( H, b, c, d, a, 10, 0xbebfbc70, 23 )
    FF( H, a, b, c, d, 13, 0x289b7ec6,  4 )
    FF( H, d, a, b, c,  0, 0xeaa127fa, 11 )
    FF( H, c, d, a, b,  3, 0xd4ef3085, 16 )
    FF( H, b, c, d, a,  6, 0x04881d05, 23 )
    FF( H, a, b, c, d,  9, 0xd9d4d039,  4 )
    FF( H, d, a, b, c, 12, 0xe6db99e5, 11 )
    FF( H, c, d, a, b, 15, 0x1fa27cf8, 16 )
    FF( H, b, c, d, a,  2, 0xc4ac5665, 23 )

    ; Round 4

    FF( I, a, b, c, d,  0, 0xf4292244,  6 )
    FF( I, d, a, b, c,  7, 0x432aff97, 10 )
    FF( I, c, d, a, b, 14, 0xab9423a7, 15 )
    FF( I, b, c, d, a,  5, 0xfc93a039, 21 )
    FF( I, a, b, c, d, 12, 0x655b59c3,  6 )
    FF( I, d, a, b, c,  3, 0x8f0ccc92, 10 )
    FF( I, c, d, a, b, 10, 0xffeff47d, 15 )
    FF( I, b, c, d, a,  1, 0x85845dd1, 21 )
    FF( I, a, b, c, d,  8, 0x6fa87e4f,  6 )
    FF( I, d, a, b, c, 15, 0xfe2ce6e0, 10 )
    FF( I, c, d, a, b,  6, 0xa3014314, 15 )
    FF( I, b, c, d, a, 13, 0x4e0811a1, 21 )
    FF( I, a, b, c, d,  4, 0xf7537e82,  6 )
    FF( I, d, a, b, c, 11, 0xbd3af235, 10 )
    FF( I, c, d, a, b,  2, 0x2ad7d2bb, 15 )
    FF( I, b, c, d, a,  9, 0xeb86d391, 21 )

    mov rdx,buf
    add [rdx+0x00],a
    add [rdx+0x04],b
    add [rdx+0x08],c
    add [rdx+0x0C],d
    ret

MD5Transform endp

    end
