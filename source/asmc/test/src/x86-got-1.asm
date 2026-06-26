
.486
.model flat, syscall

public export a
public b

externdef external_data:dword
baz proto

.data
 a dd 1
 b dd 2
 q dd 3

.code

foo proc
    call @F
@@: pop eax
    add eax,_GLOBAL_OFFSET_TABLE_ + 2
    mov ecx,a[eax]
    mov edx,b[eax]
    mov eax,q
    mov eax,external_data
    ret
    endp

bar proc
    mov eax,external_data[4000]
    mov eax,foo[99]
    call baz
    ret
    endp

    end
