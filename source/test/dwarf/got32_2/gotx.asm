include stdio.inc

public named_data1 ; public + -fPIC = GOT32X
public named_data2

.data
 named_data1 dd 42
 named_data2 dd 42

.code

main proc

    call @F
@@: pop eax
    add eax,_GLOBAL_OFFSET_TABLE_ + 2
    mov ebx,eax
    mov edx,named_data1[ebx] ; GOT32X
    mov ecx,named_data2[ebx] ; GOT32X
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
