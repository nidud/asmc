include intn.inc

.data

_shrU label dword
    dq 0000000000000000h, 0000000000000000h, 0
    dq 0000000000000001h, 0000000000000000h, 1
    dq 8000000000000001h, 0000000000000000h, 64
    dq 8000000000000001h, 0000000000000001h, 63

_shrI label dword
    dq 0000000000000000h, 0000000000000000h, 0
    dq 0000000000000001h, 0000000000000000h, 1
    dq 0000000000000010h, 0000000000000008h, 1
    dq 0000000000000020h, 0000000000000010h, 1
    dq 0000000000000040h, 0000000000000002h, 5
    dq 4000000180000000h, 20000000C0000000h, 1
    dq 8000000000000000h,0FFFFFFFF00000000h, 31
    dq 8000000000000000h,0FFFFFFFF80000000h, 32
    dq 8000000000000000h,0FFFFFFFFC0000000h, 33
    dq 8000000000000000h,0FFFFFFFFFFFFFFF8h, 60
    dq 0800000000000000h, 0000000000000080h, 52
    dq 4000000000000000h, 0000000000000000h, 64

_shl label dword
    dd 00000000h,   00000000h,  0,  00000000h,  00000000h
    dd 00000001h,   00000000h,  16, 00010000h,  00000000h
    dd 00000001h,   00000000h,  32, 00000000h,  00000001h
    dd 00000000h,   00000001h,  32, 00000000h,  00000000h
    dd 00008000h,   00000000h,  48, 00000000h,  80000000h
    dd 80000000h,   00000080h,  1,  00000000h,  00000101h
    dd 00000001h,   00000000h,  63, 00000000h,  80000000h
    dd 00000001h,   00000000h,  64, 00000000h,  00000000h
_shlend label dword

.code

bits macro val, cnt
    local x
    .data
    x oword val
    .code
    _bsrnd(addr x, 4)
    mov ebx,cnt
    exitm<.assert( eax == ebx )>
    endm

main proc

    lea esi,_shrU
    .while esi < offset _shrI
        _shrnd(esi, [esi+16], 2)
        .assert( !_cmpnd(esi, &[esi+8], 2 ) )
        add esi,3*8
    .endw

    lea esi,_shl
    .while esi < offset _shlend
        _shlnd(esi, [esi+8], 2)
        .assert( !_cmpnd(esi, &[esi+12], 2 ) )
        add esi,5*4
    .endw

    lea esi,_shrI
    .while esi < offset _shl
        _sarnd(esi, [esi+16], 2)
        .assert( !_cmpnd(esi, &[esi+8], 2 ) )
        add esi,3*8
    .endw

    bits( 0, 0 )
    bits( 1, 1 )
    bits( 2, 2 )
    bits( 7, 3 )
    bits( 0x80000000, 32 )
    bits( 0x100000000, 33 )
    bits( 0x8000000000000000, 64 )
    bits( 0x10000000000000000, 65 )
    bits( 0x800000000000000000000000, 96 )
    bits( 0x1000000000000000000000000, 97 )
    bits( 0x80000000000000000000000000000000, 128 )
    bits( 0x70000000000000000000000000000000, 127 )

    xor eax,eax
    ret

main endp

    end
