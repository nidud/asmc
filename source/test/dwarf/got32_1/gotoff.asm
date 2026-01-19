include stdio.inc

.data
 named_data1 dd 42
 named_data2 dd 42

.code

main proc

    call @F
@@: pop eax
    add eax,_GLOBAL_OFFSET_TABLE_ + 2
    mov ebx,eax
    lea edx,named_data1[ebx] ; GOTOFF
    lea ecx,named_data2[ebx] ; GOTOFF
    lea edi,named_func[ebx]  ; GOTOFF
    printf( "GOT: %X, data1: %d, data2: %d, func: %X\n" [ebx], ebx, [edx], [ecx], edi)
    xor eax,eax
    ret
    endp

named_func proc
    xor eax,eax
    ret
    endp

    end
