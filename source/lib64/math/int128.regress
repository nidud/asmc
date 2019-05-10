include string.inc
include stdio.inc
include crtl.inc
include intrin.inc

compare macro p, a, b, r
  local x,y,z
    .data
    x oword a
    y oword b
    z oword r
    .code
    mov rcx,qword ptr x
    mov rdx,qword ptr x[8]
    mov r8,qword ptr y
    mov r9,qword ptr y[8]
    call p
    mov r10,qword ptr z
    mov r11,qword ptr z[8]
    exitm<.assert(rax == r10 && rdx == r11)>
    endm

shift128 macro p, val, count, r
  local x,z
    .data
    x oword val
    z oword r
    .code
    mov ecx,count
    mov rax,qword ptr x
    mov rdx,qword ptr x[8]
    call p
    mov rbx,qword ptr z
    mov rcx,qword ptr z[8]
    exitm<.assert(rax == rbx && rdx == rcx)>
    endm

    .code

main proc

  local h_128:oword

    compare(_allmul, 1, 1, 1)
    compare(_allmul, 1, 2, 2)
    compare(_allmul, 10, 100000000000000000, 1000000000000000000)
    compare(_allmul, 0x40000000000000000000000000000000, 2, 0x80000000000000000000000000000000)

    compare(_aulldiv, 1, 1, 1)
    compare(_aulldiv, 10, 2, 5)
    compare(_aulldiv, 0x80000000000000000000000000000000, 2, 0x40000000000000000000000000000000)
    compare(_aulldiv, 3, 2, 1)
    .assert(r8 == 1 && r9 == 0)

    compare(_alldiv, -1, 1, -1)
    .assert(r8 == 0 && r9 == 0)
    compare(_alldiv, 13, 10, 1)
    .assert(r8 == 3 && r9 == 0)
    compare(_alldiv, 100, 10, 10)
    .assert(r8 == 0 && r9 == 0)
    compare(_alldiv, 100007, 100000, 1)
    .assert(r8 == 7 && r9 == 0)

    compare(_allrem, -1, 1, 0)
    compare(_allrem, 13, 10, 3)
    compare(_allrem, 100, 10, 0)
    compare(_allrem, 100007, 100000, 7)

    compare(_aullrem, -1, 1, 0)
    compare(_aullrem, 13, 10, 3)
    compare(_aullrem, 100, 10, 0)
    compare(_aullrem, 100007, 100000, 7)

    shift128(_allshl, 0, 0, 0)
    shift128(_allshl, 0x00000000000000000000000000000001,  16, 0x00000000000000000000000000010000)
    shift128(_allshl, 0x00000000000000000000000000000001,  32, 0x00000000000000000000000100000000)
    shift128(_allshl, 0x00000000000000000000000000000001,  48, 0x00000000000000000001000000000000)
    shift128(_allshl, 0x00000000000000000000000000000001, 127, 0x80000000000000000000000000000000)
    shift128(_allshl, 0x00000000000000000000000000000001, 128, 0x00000000000000000000000000000000)
    shift128(_allshl, 0x40000000000000000000000000000000,   1, 0x80000000000000000000000000000000)

    shift128(_allshr, 0, 0, 0)
    shift128(_allshr, 0x00000000000000000000000000000001,   1, 0x00000000000000000000000000000000)
    shift128(_allshr, 0x00000000000000000000000100000000,  32, 0x00000000000000000000000000000001)
    shift128(_allshr, 0x00000000000000000001000000000000,  48, 0x00000000000000000000000000000001)
    shift128(_allshr, 0x80000000000000000000000000000000, 127, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)
    shift128(_allshr, 0x80000000000000000000000000000000, 128, 0x00000000000000000000000000000000)
    shift128(_allshr, 0x80000000000000000000000000000000,   1, 0xC0000000000000000000000000000000)

    shift128(_aullshr, 0, 0, 0)
    shift128(_aullshr, 0x00000000000000000000000000000001,   1, 0x00000000000000000000000000000000)
    shift128(_aullshr, 0x00000000000000000000000100000000,  32, 0x00000000000000000000000000000001)
    shift128(_aullshr, 0x00000000000000000001000000000000,  48, 0x00000000000000000000000000000001)
    shift128(_aullshr, 0x80000000000000000000000000000000, 127, 0x00000000000000000000000000000001)
    shift128(_aullshr, 0x80000000000000000000000000000000, 128, 0x00000000000000000000000000000000)
    shift128(_aullshr, 0x80000000000000000000000000000000,   1, 0x40000000000000000000000000000000)

    umul256(0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,&h_128)
    .assert(rax == 1 && rdx == 0)
    mov rax,qword ptr h_128
    mov rdx,qword ptr h_128[8]
    .assert ( rax == 0xFFFFFFFFFFFFFFFE && rdx == 0xFFFFFFFFFFFFFFFF )

    xor eax,eax
    ret

main endp

    end
