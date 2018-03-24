include string.inc
include stdio.inc
include malloc.inc
include winbase.inc

    .data

s1  db "xxxxxxxxxxxxxxxxcbaabx"
s2  db "x",0
s3  db "xxxxxxxxxxxxxxxzabcdef"

    db "0123456789"
az  db "9876543210"
    db "ZYXWVUTSRQPONMLKJIHGFEDCBA"
    db "abcdefghijklmnopqrstuvwxyz"
    db 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1
    db 0

table label dword
;   dd 0 ,s1,0;s2+1
    dd 'x',s1,s1
    dd 'a',s1,s1+18
    dd 'b',s1,s1+17
    dd 'c',s1,s1+16
    dd 'xxxx',s1,s1
    dd 'z',s2,0
    dd 'x',s2,s2
    dd 'z',s3,s3+15
    dd 'a',s3,s3+16
    dd 'b',s3,s3+17
    dd 'c',s3,s3+18
    dd 'd',s3,s3+19
    dd 'e',s3,s3+20
    dd 'f',s3,s3+21

    dd 0

nerror  dd 0

    .code

overlapped proc uses esi edi ebx
    .if VirtualAlloc(0,4096,MEM_COMMIT,PAGE_READWRITE)
        mov esi,eax
        mov edi,eax
        mov ecx,4096-1
        mov eax,'x'
        rep stosb
        mov [edi],ah
        mov edi,4096-15
        add esi,15
        strchr(esi, 'z')
        strchr(esi, 'x')
        strchr(esi, 0)
        .repeat
            dec edi
            mov byte ptr [esi+edi],0
            strchr(esi, 'r')
            mov byte ptr [esi+edi-1],'r'
            strchr(esi, 'r')
        .until edi == 4096 - 33 - 15
        sub esi,15
        VirtualFree(esi,0,MEM_RELEASE)
    .endif
    ret
overlapped endp

regress proc uses esi edi ebx
    lea esi,table - 2
    lea edi,az
loop_az:
    cmp esi,edi
    jb  do_table
    mov al,[esi]
    dec esi
    strchr(edi, eax)
    lea edx,[esi+1]
    movzx   ecx,byte ptr [edx]
    jz  error2
    cmp eax,edx
    jne error1
    jmp loop_az

do_table:

    xor edi,edi
    lea esi,table
lupe:
    lodsd
    mov ecx,eax
    lodsd
    strchr(eax, ecx)
    mov edx,eax
    mov ecx,[esi-8]
    mov ebx,[esi-4]
    lodsd
    cmp eax,edx
    jne error
    inc edi
    mov eax,[esi]
    test    eax,eax
    jnz lupe
    inc eax
toend:
    ret
error2:
    printf("\n\nZERO flag set: eax = %X (%X) strchr(%s, %c) : %s\n",
        eax, edx, edi, ecx, eax)
    inc nerror
    xor eax,eax
    jmp toend
error1:
    printf("\n\nerror: eax = %X (%X) strchr(%s, %c) : %s\n",
        eax,edx,edi,ecx, eax)
    inc nerror
    xor eax,eax
    jmp toend
error:
    printf("\n\ntable %d: eax = %X (%X) strchr(%s, %c)\n",edi,edx,eax,ebx,ecx)
    inc nerror
    xor eax,eax
    jmp toend
regress endp

main proc
    .if regress()
        overlapped()
    .endif
    mov eax,nerror
    ret
main endp

    END
