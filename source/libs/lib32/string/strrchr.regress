include string.inc
include stdio.inc
include malloc.inc
include winbase.inc

    .data

s0  db 0
s1  db "0123456789ABCDEFabcxxxx",0
s2  db "xxxxxxxxxxxxxxaabcdxxx",0
s3  db "xxxxxxxxxxxxx  abc",0
s4  db "xxxxxxxxxxx..a.abc",0

az  db "0123456789"
    db "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    db "abcdefghijklmnopqrstuvwxyz"
    db 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1
    db 0

table label dword
    dd 'x',s0,0
    dd  0 ,s0,s0
    dd  0 ,s1,s1+23
    dd 'x',s1,s1+22
    dd 'a',s1,s1+16
    dd 'b',s1,s1+17
    dd 'c',s1,s1+18
    dd 'd',s2,s2+18
    dd ' ',s3,s3+14
    dd '.',s4,s4+14
    dd 0

nerror  dd 0

    .code

overlapped proc uses esi edi ebx

    .if VirtualAlloc(0,4096,MEM_COMMIT,PAGE_READWRITE)
        push MEM_RELEASE
        push 0
        push eax
        mov ebx,eax
        mov edi,eax
        mov ecx,4096
        mov eax,'x'
        rep stosb
        mov edi,4096
        mov byte ptr [ebx+4096-1],0
        lea eax,[ebx+15]
        strrchr(ebx,'y')
        strrchr(ebx,'x')
        strrchr(ebx,0)
        .repeat
            dec edi
            inc ebx
            strrchr(ebx,0)
        .until edi == 4096 - 33
        VirtualFree()
    .endif
    ret

overlapped endp

regress proc uses esi edi ebx

    lea esi,az
    mov edi,esi
    .repeat

        .while 1
            lodsb
            .break .if !al
            strrchr(edi, eax)
            lea edx,[esi-1]
            movzx ecx,byte ptr [edx]
            .if eax != edx
                printf("\n\nerror: eax = %X (%X) strrchr2(%s, %c, %c) : %s\n",
                    eax, edx, edi, ecx, eax)
                inc nerror
                xor eax,eax
                .break(1)
            .endif
        .endw

        xor edi,edi
        lea esi,table
        .repeat
            lodsd
            mov ecx,eax
            lodsd
            strrchr(eax, ecx)
            mov edx,eax
            mov ebx,[esi-4]
            lodsd
            .if eax != edx
                mov esi,[esi-12]
                printf("\n\ntable[%d]: eax = %X (%X) strrchr2(%s, %c, %c)\n",
                    edi, edx, eax, ebx, esi)
                inc nerror
                xor eax,eax
                .break(1)
            .endif
            inc edi
            mov eax,[esi]
        .until !eax
        inc eax
    .until 1
    ret
regress endp

main proc
    .if regress()
        overlapped()
    .endif
    mov eax,nerror
    ret
main endp

    END
