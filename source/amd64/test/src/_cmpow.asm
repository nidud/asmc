include intn.inc

.data

table label dword
    dd 000000000h,?,?,?, 0, 0, 0, 0
    dd 000000001h,?,?,?, 1, 0, 0, 0
    dd 0000001FFh,?,?,?,-1, 1, 0, 0
    dd 000000100h,?,?,?, 0, 1, 0, 0
    dd 00001FF01h,?,?,?, 1,-1, 1, 0
    dd 00001FFFFh,?,?,?,-1,-1, 1, 0
    dd 000010000h,?,?,?, 0, 0, 1, 0
    dd 000010001h,?,?,?, 1, 0, 1, 0
    dd 001FF01FFh,?,?,?,-1, 1,-1, 1
    dd 001FF0100h,?,?,?, 0, 1,-1, 1
    dd 001FFFF01h,?,?,?, 1,-1,-1, 1
    dd 001FFFFFFh,?,?,?,-1,-1,-1, 1
    dd 001000000h,?,?,?, 0, 0, 0, 1
    dd 001000001h,?,?,?, 1, 0, 0, 1
    dd 0010001FFh,?,?,?,-1, 1, 0, 1
    dd 001000100h,?,?,?, 0, 1, 0, 1
    dd 0FF01FF01h,?,?,?, 1,-1, 1,-1
    dd 0FF01FFFFh,?,?,?,-1,-1, 1,-1
    dd 0FF010000h,?,?,?, 0, 0, 1,-1
    dd 0FF010001h,?,?,?, 1, 0, 1,-1
    dd 0FFFF01FFh,?,?,?,-1, 1,-1,-1
    dd 0FFFF0100h,?,?,?, 0, 1,-1,-1
    dd 0FFFFFF01h,?,?,?, 1,-1,-1,-1
    dd 0FFFFFFFFh,?,?,?,-1,-1,-1,-1
    dd 0FEFFFFFFh,?,?,?,-1,-1,-1,-2
    dd 0FFFEFFFFh,?,?,?,-1,-1,-2,-1
    dd 0FFFFFEFFh,?,?,?,-1,-2,-1,-1
    dd 0FFFFFFFEh,?,?,?,-2,-1,-1,-1
    dd 040000000h,?,?,?, 0,0,0,40000000h
    dd 040000001h,?,?,?, 1,0,0,40000000h
    dd 040000100h,?,?,?, 0,1,0,40000000h
    dd 040010000h,?,?,?, 0,0,1,40000000h
    dd 041000000h,?,?,?, 0,0,0,40000001h
    dd 080000000h,?,?,?, 0,0,0,80000000h
    dd 080000001h,?,?,?, 1,0,0,80000000h
    dd 080000100h,?,?,?, 0,1,0,80000000h
    dd 080010000h,?,?,?, 0,0,1,80000000h
    dd 081000000h,?,?,?, 0,0,0,80000001h
    dd 0C0000000h,?,?,?, 0,0,0,0C0000000h
    dd 0C0000001h,?,?,?, 1,0,0,0C0000000h
    dd 0C0000100h,?,?,?, 0,1,0,0C0000000h
    dd 0C0010000h,?,?,?, 0,0,1,0C0000000h
    dd 0C1000000h,?,?,?, 0,0,0,0C0000001h

endtable label byte

.code

test_cmpow proc uses rsi rdi a:ptr, b:ptr

    mov rsi,a
    mov rdi,b
    mov eax,[rsi]
    cmp eax,[rdi]
    pushfq
    lea rcx,[rsi+16]
    lea rdx,[rdi+16]

    option epilogue:flags

    _cmpow(rcx, rdx)

    mov ecx,eax
    mov eax,[rsi+16]
    mov edx,[rdi+16]

    pushfq
    pop rsi ; ESI = test compare result flags
    pop rdi ; EDI = standard compare result flags

if 0
    and esi,880h
    and edi,880h    ; OF SF only
else
 if 0
    and esi,41h
    and edi,41h     ; ZF CF only
 else
  if 1
    and esi,8C1h
    and edi,8C1h    ; OF SF ZF CF only
  else
    and esi,8C5h
    and edi,8C5h    ; OF SF ZF PF CF
  endif
 endif
endif

if 0
    mov eax,esi     ; exclude JO/JS
    xor eax,880h
    .assert( eax == edi || esi == edi )
else
    .assert( esi == edi )
endif
    ret
test_cmpow endp

test_ucmpo proc uses rsi rdi a:ptr, b:ptr

    mov rsi,a
    mov rdi,b
    mov eax,[rsi]
    cmp eax,[rdi]
    pushfq
    lea rcx,[rsi+16]
    lea rdx,[rdi+16]
    _ucmpo(rcx, rdx)
    mov ecx,eax
    mov eax,[rsi+16]
    mov edx,[rdi+16]
    pushfq
    pop rsi     ; ESI = test compare result flags
    pop rdi     ; EDI = standard compare result flags
    and esi,41h ; ZF CF only
    and edi,41h
    .assert( esi == edi )
    ret

test_ucmpo endp

main proc

    lea rsi,table
    lea rbx,endtable
    mov rdi,rsi

    .while rsi < rbx
        push rdi
        .while rdi < rbx
            test_ucmpo(rsi, rdi)
            test_cmpow(rsi, rdi)
            add rdi,32
        .endw
        pop rdi
        add rsi,32
    .endw

    xor eax,eax
    ret

main endp

    end
