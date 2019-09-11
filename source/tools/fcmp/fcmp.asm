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

.code

main proc uses esi edi ebx argc:int_t, argv:array_t

  local fp      :ptr FILE
  local file1   :string_t
  local file2   :string_t
  local buffer1 :string_t
  local buffer2 :string_t
  local c       :char_t     ; Compare COFF
  local p       :char_t     ; Compare PE
  local d       :char_t     ; Desimal (default is hex)
  local v       :char_t     ; Verbose
  local o       :int_t      ; Offset start of compare
  local n       :int_t      ; Number of lines (default is 10)
  local size1   :uint_t
  local size2   :uint_t
  local unequal :uint_t
  local h1      :int_t
  local h2      :int_t

    xor eax,eax
    mov file1,eax
    mov file2,eax
    mov unequal,eax
    mov c,al
    mov p,al
    mov d,al
    mov v,al
    mov o,eax
    mov n,10
    lea eax,stdout ; default to stdout
    mov fp,eax
    mov edi,ecx
    mov esi,edx
    lodsd
    dec edi

    .repeat

        .while edi

            mov edx,[esi]
            mov eax,[edx]
            .if al == '/' || al == '-'
                or  ah,0x20
                .if ah == 'd'
                    inc d
                .elseif ah == 'c'
                    inc c
                .elseif ah == 'p'
                    inc p
                .elseif ah == 'v'
                    inc v
                .elseif ah == 'n'
                    add edx,2
                    .if atol(edx)
                        mov n,eax
                    .endif
                .elseif ah == 'o'
                    add edx,2
                    .if atol(edx)
                        mov o,eax
                    .endif
                .else
                    perror(edx)
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
        .endw
        .break .if file1 && file2
        fprintf(fp,
            "Usage:     FCMP [-/option] <file1> <file2>\n"
            "\n"
            "/D         Desimal (default is hex)\n"
            "/V         Verbose\n"
            "/P         Compare PE\n"
            "/C         Compare COFF\n"
            "/O<offs>   Offset start of compare\n"
            "/N<lines>  Number of lines (default is 10)\n"
            "\n"
        )
        .return 1
    .until 1

    mov edi,file1
    .if _open(edi, O_RDONLY or O_BINARY, 0) == -1
        perror(edi)
        .return 1
    .endif
    mov h1,eax

    mov edi,file2
    .if _open(edi, O_RDONLY or O_BINARY, 0) == -1
        _close(h1)
        perror(edi)
        .return 1
    .endif
    mov h2,eax

    mov size2,_filelength(eax)
    mov size1,_filelength(h1)
    add eax,size2
    .if !malloc(eax)
        perror("No memory")
        .return 1
    .endif
    mov buffer1,eax
    add eax,size1
    mov buffer2,eax

    .if _read(h1, buffer1, size1) != size1

        perror("Read error")
        .return 1
    .endif

    .if _read(h2, buffer2, size2) != size2
        perror("Read error")
        .return 1
    .endif

    _close(h1)
    _close(h2)

    mov esi,buffer1
    mov edi,buffer2
    mov ecx,size1
    mov eax,o
    .if eax >= ecx
        perror("Offset >= File Size")
        .return 1
    .endif

    sub ecx,eax
    add esi,eax
    add edi,eax

    .if p

        .repeat
            .repeat

                mov     eax,[esi+0x3C]
                add     esi,eax
                .break .if size1 < eax
                .break .if dword ptr [esi] != 'EP'
                mov     eax,[edi+0x3C]
                add     edi,eax
                .break .if size2 < eax
                .break .if dword ptr [edi] != 'EP'

                mov     h1,[esi+4+20+0x3C]
                mov     h2,[edi+4+20+0x3C]
                movzx   eax,word ptr [esi+4+2]
                imul    ecx,eax,40
                add     ecx,0xE0+20+4
                mov     eax,[esi+8]
                mov     [edi+8],eax
                .repeat
                    repe cmpsb
                    .break .ifz
                    inc     unequal
                    mov     ebx,ecx
                    mov     ecx,esi
                    sub     ecx,buffer1
                    dec     ecx
                    movzx   eax,byte ptr [edi-1]
                    movzx   edx,byte ptr [esi-1]
                    .if d
                        fprintf(fp, "%d: %d %d\n", ecx, edx, eax)
                    .else
                        fprintf(fp, "%08X: %02X %02X\n", ecx, edx, eax)
                    .endif
                    mov     ecx,ebx
                    dec     n
                    .break .ifz
                .until !ecx
                mov     esi,buffer1
                mov     eax,h1
                add     esi,eax
                sub     size1,eax
                .break .ifb
                mov     edi,buffer2
                mov     eax,h2
                add     edi,eax
                sub     size2,eax
                .break .ifb
                mov     ecx,size1
                .break(1)
            .until 1
            perror("invalid PE binary")
            .return 1
        .until 1

    .elseif c

        mov eax,[edi+4]
        mov [esi+4],eax
    .endif

    .if size1 != size2
        fprintf(fp, "%s(%d), %s(%d): file sizes differ\n", file1, size1, file2, size2)
        .if size1 > size2
            mov size1,size2
        .else
            mov size2,size1
        .endif
        mov ecx,size1
    .endif

    .repeat
        repe cmpsb
        .break .ifz
        inc     unequal
        mov     ebx,ecx
        mov     ecx,esi
        sub     ecx,buffer1
        dec     ecx
        movzx   eax,byte ptr [edi-1]
        movzx   edx,byte ptr [esi-1]
        .if d
            fprintf(fp, "%d: %d %d\n", ecx, edx, eax)
        .else
            fprintf(fp, "%08X: %02X %02X\n", ecx, edx, eax)
        .endif
        mov     ecx,ebx
        dec     n
        .break .ifz
    .until !ecx

    .if !unequal
        .if v
            fprintf(fp, "%s == %s (Ok)\n", file1, file2)
        .endif
        xor eax,eax
    .else
        fprintf(fp, "%d unequal bytes found cmp(%s, %s)\n", unequal, file1, file2)
        mov eax,1
    .endif
    ret

main endp

    end _tstart
