; FCMP.ASM--
; Copyright (c) 2016 GNU General Public License www.gnu.org/licenses
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; Change history:
; 2013-10-23 - created for the regression test of ASMC
;
include io.inc
include stdio.inc
include stdlib.inc
include fcntl.inc
include tchar.inc

        .data

cp_info  db "FCMP Version 1.0 Copyright (c) 2016 GNU General Public License",10,10,0
cp_usage db "USAGE:     FCMP [-/option] <file1> <file2>",10
         db 10
         db "/D         Desimal (default is hex)",10
         db "/V         Verbose",10
         db "/P         Compare PE",10
         db "/C         Compare COFF",10
         db "/O<offs>   Offset start of compare",10
         db "/N<lines>  Number of lines (default is 10)",10
         db 10,0

option_c dd 0
option_p dd 0
option_d dd 0
option_v dd 0
option_o dd 0
option_n dd 10

file1    dd 0
file2    dd 0
result   dd 1
fp       dd 0    ; default to stdout


    .code

main proc
local h1, h2, m1, m2, z1, z2

    lea eax,stdout
    mov fp,eax

    mov edi,ecx
    mov esi,edx
    cmp edi,1
    jna printusage

    lodsd
    dec edi
    .repeat
        mov edx,[esi]
        mov eax,[edx]
        .if al == '/' || al == '-'
            or  ah,20h
            .if ah == 'd'
                inc option_d
            .elseif ah == 'c'
                inc option_c
            .elseif ah == 'p'
                inc option_p
            .elseif ah == 'v'
                inc option_v
            .elseif ah == 'n'
                add edx,2
                .if atol(edx)
                    mov option_n,eax
                .endif
            .elseif ah == 'o'
                add edx,2
                .if atol(edx)
                    mov option_o,eax
                .endif
            .else
                perror( edx )
            .endif
        .else
            .if file1
                mov file2,edx
            .else
                mov file1,edx
            .endif
        .endif
        add esi,4
        dec edi
    .until !edi

    .if !(file1 && file2)
        jmp printusage
    .endif
    mov edi,file1
    .if _open(edi, O_RDONLY or O_BINARY, 0) == -1
        perror(edi)
        jmp toend
    .endif
    mov h1,eax
    mov edi,file2
    .if _open(edi, O_RDONLY or O_BINARY, 0) == -1
        _close(h1)
        perror(edi)
        jmp toend
    .endif
    mov h2,eax

    mov z2,_filelength(eax)
    mov z1,_filelength(h1)
    add eax,z2
    .if !malloc(eax)
        perror("No memory")
        jmp toend
    .endif
    mov m1,eax
    add eax,z1
    mov m2,eax
    .if _read(h1, m1, z1) != z1
        perror( "Read error" )
        jmp toend
    .endif
    .if _read(h2, m2, z2) != z2
        perror("Read error")
        jmp toend
    .endif
    _close(h1)
    _close(h2)
    mov esi,m1
    mov edi,m2
    mov ecx,z1
    mov eax,option_o
    cmp eax,ecx
    jae toend
    dec result
    sub ecx,eax
    add esi,eax
    add edi,eax
    .if option_p
        mov eax,[esi+3Ch]
        add esi,eax
        cmp z1,eax
        jb  pe_error
        cmp dword ptr [esi],'EP'
        jne pe_error
        mov eax,[edi+3Ch]
        add edi,eax
        cmp z2,eax
        jb  pe_error
        cmp dword ptr [edi],'EP'
        jnz pe_error
        mov eax,[esi+4+20+3Ch]
        mov h1,eax
        mov eax,[edi+4+20+3Ch]
        mov h2,eax
        movzx eax,word ptr [esi+4+2]
        mov ecx,40
        mul ecx
        add eax,0E0h
        add eax,20+4
        mov ecx,eax
        mov eax,[esi+8]
        mov [edi+8],eax
        compare()
        mov esi,m1
        mov eax,h1
        add esi,eax
        sub z1,eax
        jb  pe_error
        mov edi,m2
        mov eax,h2
        add edi,eax
        sub z2,eax
        jc  pe_error
        mov ecx,z1
    .elseif option_c
        mov eax,[edi+4]
        mov [esi+4],eax
    .endif
    mov eax,z1
    .if eax != z2
        fprintf(fp, "%s, %s: file sizes differ\n", file1, file2)
        mov result,1
        jmp toend
    .endif
    compare()
    .if !result
        .if option_v
            fprintf(fp, "%s == %s (Ok)\n", file1, file2)
        .endif
    .else
        fprintf(fp, "%d unequal bytes found cmp(%s, %s)\n", result, file1, file2)
        mov result,1
    .endif
toend:
    mov eax,result
    ret
pe_error:
    perror("invalid PE binary")
    mov result,1
    jmp toend
printusage:
    printf(addr cp_info)
    printf(addr cp_usage)
    jmp toend
compare:
    .repeat
        repe cmpsb
        .break .if ZERO?
        inc result
        push ecx
        mov ecx,esi
        sub ecx,m1
        dec ecx
        movzx eax,byte ptr [edi-1]
        movzx edx,byte ptr [esi-1]
        .if option_d
            fprintf(fp, "%d: %d %d\n", ecx, edx, eax)
        .else
            fprintf(fp, "%08X: %02X %02X\n", ecx, edx, eax)
        .endif
        pop ecx
        dec option_n
        .break .if ZERO?
    .until !ecx
    retn
main endp

    end _tstart
