; SF.ASM--
; Copyright (C) 2017 Asmc Developers
;
; You should have received a copy of the GNU General Public License
; along with this program. If not, see http://www.gnu.org/licenses/
;
; - Creates Source Files
; - Insert Copyright string in source files
; - Insert Modification Date in source files
;
include io.inc
include stdio.inc
include stdlib.inc
include conio.inc
include string.inc
include tchar.inc

MAXLABEL    equ 32
MAXTOKEN    equ 1000

APOS        equ 39
QUOTE       equ '"'
CCOMMENT    equ ';'

FILE_C      equ 1
FILE_H      equ 2
FILE_I      equ 3
FILE_A      equ 4
FILE_M      equ 5

.data

UserId      db "name@",0
Copyright   db "Copyright (C) 2017 Asmc Developers",0

NoLicense   db 0

LicenseC    db "This program is free software; you can redistribute it and/or modify",10
            db " * it under the terms of the GNU General Public License as published by",10
            db " * the Free Software Foundation; either version 2 of the License, or",10
            db " * (at your option) any later version.",10
            db " *",10
            db " * This program is distributed in the hope that it will be useful,",10
            db " * but WITHOUT ANY WARRANTY; without even the implied warranty of",10
            db " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the",10
            db " * GNU General Public License for more details.",10
            db " *",10
            db " * You should have received a copy of the GNU General Public License",10
            db " * along with this program. If not, see http://www.gnu.org/licenses/",0


LicenseA    db "; This program is free software; you can redistribute it and/or modify",10
            db "; it under the terms of the GNU General Public License as published by",10
            db "; the Free Software Foundation; either version 2 of the License, or",10
            db "; (at your option) any later version.",10
            db ";",10
            db "; This program is distributed in the hope that it will be useful,",10
            db "; but WITHOUT ANY WARRANTY; without even the implied warranty of",10
            db "; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the",10
            db "; GNU General Public License for more details.",10
            db ";",10
            db "; You should have received a copy of the GNU General Public License",10
            db "; along with this program. If not, see http://www.gnu.org/licenses/",10
            db ";",0

License     dd NoLicense

ahead       db ";",10,"; Change history:",10,0
chead       db " *",10," * Change history:",10,0
tchars      db "%.0123456789?ABCDEFGHIJKLMNOPQRSTUVWXYZ_",0
tokfile     db "TOKENLST.TXT",0

option_g    db 0
option_d    db 0
option_x    db 0
option_h    db 0
option_m    db 0
option_t    db 0

align       4

fblock      WIN32_FIND_DATA <>

ftype       dd 0
fdate       dd 0
create      dd 0

T macro string
    local x
    .const
    x db string,0
    .data
    exitm<x>
    endm

token       dd T(".code")
            dd T(".data")
            dd T(".model")
            dd T("align")
            dd T("assume")
            dd T("byte")
            dd T("dword")
            dd T("endm")
            dd T("endp")
            dd T("exitm")
            dd T("extrn")
            dd T("flat")
            dd T("macro")
            dd T("nothing")
            dd T("offset")
            dd T("option")
            dd T("private")
            dd T("proc")
            dd T("proto")
            dd T("ptr")
            dd T("public")
            dd T("qword")
            dd T("sbyte")
            dd T("sdword")
            dd T("uses")
            dd T("word")
tokcount = (($ - token) / 4)
            dd MAXTOKEN - tokcount dup(0)
tcount      dd tokcount

filename    db _MAX_PATH dup(0)
unixname    db _MAX_PATH dup(0)
tempfile    db _MAX_PATH dup(0)
procname    db _MAX_PATH dup(0)
tokenfile   dd NULL

align 16
tword_b     db 512 dup(0)
temp_b      db 512 dup(0)
line_b      db 512 dup(0)
tword       dd tword_b
temp        dd temp_b
line        dd line_b

fp_src      LPFILE 0
fp_out      LPFILE 0

.code

istoken proc x:SINT

    toupper(x)
    mov ecx,eax
    xor eax,eax
    .for (edx = 0: tchars[edx]: edx++)
        .if (cl == tchars[edx])
            inc eax
            .break
        .endif
    .endf
    ret

istoken endp

cmptword proc uses esi edi o:SINT

    .repeat
        .for esi=&token: dword ptr [esi]: esi+=4
            mov edi,[esi]
            .if o == strlen(edi)
                .if !_strnicmp(edi, tword, o)
                    strcat(temp, edi)
                    mov eax,o
                    .break(1)
                .endif
            .endif
        .endf
        xor eax,eax
    .until 1
    ret

cmptword endp

strtrim PROC string:LPSTR

    .if strlen(string)

        mov ecx,eax
        add ecx,string
        .while 1
            dec ecx
            .break .if byte ptr [ecx] > ' '
            mov byte ptr [ecx],0
            dec eax
            .break .ifz
        .endw
    .endif
    ret

strtrim ENDP

cmpword proc uses esi edi ebx q:LPSTR

    strcpy(tword, q)
    strtrim(tword)
    .for (esi=tword:: esi++)
        movzx eax,byte ptr [esi]
        .break .if !istoken(eax)
    .endf
    mov byte ptr [esi],0
    mov ebx,strlen(tword)
    .repeat

        .if (ebx < 2)
            strcat(temp, tword)
            mov eax,ebx
            .break
        .endif

        .for esi=&token: dword ptr [esi]: esi+=4
            mov edi,[esi]
            .if ebx == strlen(edi)
                .if !_strnicmp(edi, tword, ebx)
                    strcat(temp, edi)
                    mov eax,ebx
                    .break(1)
                .endif
            .endif
        .endf

        .if strchr(tword, '.')
            mov byte ptr [eax],0
            mov edi,eax
            mov ebx,strlen(tword)
            .break .if cmptword(ebx)
            mov byte ptr [edi],'.'
            mov ebx,strlen(tword)
        .endif
        strcat(temp, tword)
        mov eax,ebx
    .until 1
    ret

cmpword endp

parseline proc uses esi edi ebx

    local o,quote,apos
    local q,b

    mov quote,0
    mov apos,0
    mov edi,temp
    mov esi,line
    memset(edi, 0, 512)

    .repeat

        .while byte ptr [esi]

            .if (byte ptr [esi] == CCOMMENT)
                .if temp_b
                    fputs(temp, fp_out)
                .endif
                fputs(esi, fp_out)
                mov eax,1
                .break(1)
            .endif

            .if (quote == 0 && byte ptr [esi] == APOS)
                .if (apos)
                    mov apos,0
                .else
                    mov apos,1
                .endif
                movsb
                .continue
            .endif

            .if (apos == 0 && byte ptr [esi] == QUOTE)
                .if (quote)
                    mov quote,0
                .else
                    mov quote,1
                .endif
                movsb
                .continue
            .endif

            movzx eax,byte ptr [esi]
            .if al == 9
                inc esi
                mov al,' '
                stosb
                .while edi & 3
                    stosb
                .endw
                .continue
            .endif

            .if (apos || quote || al < 33)
                movsb
                .continue
            .endif

            .if !istoken(eax)
                movsb
                .continue
            .endif

            cmpword(esi)
            add edi,eax
            add esi,eax
        .endw
        .if temp_b
            mov esi,temp
            .while strstr(esi, "( ")
                lea esi,[eax+1]
                strcpy(esi, &[eax+2])
            .endw
            mov esi,temp
            .while strstr(esi, " )")
                mov esi,eax
                strcpy(esi, &[eax+1])
            .endw
            fputs(temp, fp_out)
        .endif
        mov eax,1
    .until 1
    ret

parseline endp

read_token proc argv:ptr

    local p:LPSTR
    local fp:LPFILE

    .repeat

        .if tokenfile

            .if !fopen(&tokenfile, "rt")

                perror(&tokenfile)
                xor eax,eax
                .break
            .endif
        .else

            mov eax,argv
            mov eax,[eax]
            .break .if !strrchr(strcpy(temp, eax), '\')
            inc eax
            lea edx,tokfile
            strcpy(eax, edx)
            .break .if !fopen(temp, "rt")
        .endif
        mov fp,eax

        mov tcount,0
        .while tcount < MAXTOKEN

            .break .if !fgets(temp, 256, fp)

            .if strchr(temp, CCOMMENT)
                mov byte ptr [eax],0
            .endif

            .continue .if strtrim(temp) < 2

            movzx eax,temp_b
            .continue .if !istoken(eax)

            .if strchr(temp, ' ')
                mov byte ptr [eax],0
                inc eax
                ;strcpy(newtoken[tcount], p);
            .endif

            strcpy(malloc(&[strlen(temp)+1]), temp)
            mov ecx,tcount
            inc tcount
            mov token[ecx*4],eax
        .endw
        fclose(fp)
        mov eax,tcount
    .until 1
    ret

read_token endp

write_token proc uses esi edi

    local fp:LPFILE

    .repeat
        lea esi,tokfile
        .if !_access(esi, 0)
            printf("The file %s exist!\n owerwrite? (y, n): ", esi)
            mov edi,_getch()
            printf("%c\n\n", edi)
            .if toupper(edi) != 'Y'
                mov eax,1
                .break
            .endif
        .endif

        .if !fopen(esi, "wt")
            perror(esi)
            mov eax,1
            .break
        .endif
        mov fp,eax

        fprintf(fp,
            "; %s - Configuration file\n;\n"
            "; MAXIDLEN: 32\n"
            "; MAXTOKEN: 1000\n;\n"
            "; These are the valid characters used as identifiers\n;\n"
            ";\t%%.0123456789?ABCDEFGHIJKLMNOPQRSTUVWXYZ\n;\n",
            esi)

        .for (esi=&token, edi=0: dword ptr [esi]: edi++)
            lodsd
            fprintf(fp, "%s\n", eax)
        .endf
        mov eax,MAXTOKEN
        sub eax,tcount
        fprintf(fp, ";\n; %d of total %d (%d free)\n;\n", edi, MAXTOKEN, eax)
        fclose(fp)
        xor eax,eax
    .until 1
    ret

write_token endp

InsertProc proc

    fprintf(fp_out,
        "include\tstdio.inc\n\n"
        ".data\n"
        ".code\n\n"
        "%s proc uses esi edi ebx\n"
        "    ret\n"
        "%s endp\n\n"
        "    end\n", &procname, &procname)
    ret

InsertProc endp

datetostring proc p:LPSTR, ft:LPFILETIME

    local s:SYSTEMTIME
    local f:FILETIME

    FileTimeToLocalFileTime(ft, &f)
    FileTimeToSystemTime(&f, &s)
    sprintf(p, "%04d-%02d-%02d", s.wYear, s.wMonth, s.wDay)
    mov eax,p
    ret

datetostring endp

write_head proc form:LPSTR

    _strupr(strcpy(temp, &fblock.cFileName))

    .if option_d
        datetostring(tword, &fblock.ftCreationTime)
        fprintf(fp_out, form, temp, &Copyright, License, tword)
    .else
        fprintf(fp_out, form, temp, &Copyright, License)
    .endif
    mov eax,1
    ret

write_head endp

write_creation proc string:LPSTR

    .if create
        fprintf(fp_out, "%s%s - (%s)\n", string,
            datetostring(temp, &fblock.ftCreationTime), &UserId)
        mov eax,1
    .else
        fprintf(fp_out, "%s\n", string)
        xor eax,eax
    .endif
    ret

write_creation endp

write_modification proc string:LPSTR

    fprintf(fp_out, string)
    fprintf(fp_out, "%s - (%s)\n", datetostring(temp, &fblock.ftLastWriteTime), &UserId)
    mov eax,1
    ret

write_modification endp

write_chead proc

    write_head("/* %s--\n * %s\n *\n * %s\n")
    .if option_d
        fprintf(fp_out, &chead)
        write_modification(" * ")
    .endif
    mov eax,1
    ret

write_chead endp

write_hhead proc uses esi edi

    write_chead()

    .repeat

        mov eax,1
        .break .if !create

        mov edi,temp
        strcpy(edi, "__INC_")
        strcat(edi, &procname)
        _strupr(edi)
        lea esi,[edi+5]

        .while byte ptr [esi]
            movzx eax,byte ptr [esi]
            .if !istoken(eax)
                mov byte ptr [esi],0
                .break
            .endif
            inc esi
        .endw

        fprintf(fp_out,
            "#ifndef %s\n"
            "#define %s\n"
            "#ifn!defined(__INC_DEFS)\n"
            " #include <defs.h>\n"
            "#endif\n"
            "#ifdef __cplusplus\n"
            " extern \"C\" {\n"
            "#endif\n"
            "#ifdef __cplusplus\n"
            " }\n"
            "#endif /* __cplusplus */\n"
            "#endif /* %s */\n", edi, edi, edi)
        mov eax,1
    .until 1
    ret

write_hhead endp

write_ihead proc

    write_head("; %s--\n; %s\n;\n%s\n")
    .if option_d
        fprintf(fp_out, &ahead)
        write_modification("; ")
    .endif
    mov eax,1
    ret

write_ihead endp

write_ahead proc

    write_ihead()
    .if create
        InsertProc()
    .endif
    mov eax,1
    ret

write_ahead endp

write_mhead proc

    write_head("# %s--\n# %s\n")
    .if option_d
        write_creation("# ")
        write_modification("# ")
    .endif
    fprintf(fp_out, "#\n")
    mov eax,1
    ret

write_mhead endp

get_comment proc x:SINT, ci:SINT

    mov line_b,0
    .if fgets(line, 511, fp_src)
        mov eax,x
        mov edx,ci
        .if line_b[edx] == al
            mov eax,1
        .else
            xor eax,eax
        .endif
    .endif
    ret

get_comment endp

insertdate proc uses esi edi ebx

    local b[64]:byte
    local ft:FILETIME

    GetSystemTimeAsFileTime(&ft)
    xor ebx,ebx
    .repeat

        .switch ftype
          .case FILE_C
          .case FILE_H
            inc ebx
            mov edi,'*'
            .endc
          .case FILE_I
          .case FILE_A
            mov edi,';'
            .endc
          .case FILE_M
            mov edi,'#'
            .endc
          .default
            xor eax,eax
            .break
        .endsw

        .if !get_comment(edi, ebx)

            .switch ftype
              .case FILE_C
                write_chead()
                fprintf(fp_out, &chead)
                .endc
              .case FILE_H
                write_hhead()
                fprintf(fp_out, &chead)
                .endc
              .case FILE_A
                write_ahead()
                fprintf(fp_out, &ahead)
                .endc
              .case FILE_I
                write_ihead()
                fprintf(fp_out, &ahead)
                .endc
              .default
                xor eax,eax
                .break
            .endsw

            .if ebx
                fprintf(fp_out, " * ")
            .else
                fprintf(fp_out, "%c ", edi)
            .endif

            fprintf(fp_out, "%s - (%s)\n", datetostring(&b, &ft), &UserId)

            .if ebx
                fprintf(fp_out, " */\n")
            .endif

            fputs(line, fp_out)

            mov eax,1
            .break
        .endif

        fputs(line, fp_out)
        .while 1

            mov esi,get_comment(edi, ebx)

            .if esi && ebx && line_b[2] == '/'  ; ' */'
                fprintf(fp_out, &chead)
                fprintf(fp_out, " * %s - (%s)\n", datetostring(&b, &ft), &UserId)
                fputs(line, fp_out)
                mov eax,1
                .break
            .endif

            .if !esi
                .if ebx
                    fprintf(fp_out, &chead)
                    fprintf(fp_out, " * ")
                .else
                    fprintf(fp_out, &ahead)
                    fprintf(fp_out, "%c ", edi)
                .endif
                fprintf(fp_out, "%s - (%s)\n", datetostring(&b, &ft), &UserId)
                .if ebx
                    fprintf(fp_out, " */\n")
                .endif
                fputs(line, fp_out);
                mov eax,1
                .break
            .endif
            .if strstr(line, "Change history:")
                fputs(line, fp_out)
                .if ebx
                    fprintf(fp_out, " * ")
                .else
                    fprintf(fp_out, "%c ", edi)
                .endif
                fprintf(fp_out, "%s - (%s)\n", datetostring(&b, &ft), &UserId)
                xor eax,eax
                .break
            .endif
            fputs(line, fp_out)
        .endw
    .until 1
    ret

insertdate endp

init_srcfile proc uses esi edi ebx fn:LPSTR

    .repeat

        .if _access(fn, 2) ; Create a new source file

            .if !fopen(fn, "wt")

                perror(fn)
                xor eax,eax
                .break
            .endif
            fclose(eax)
            inc create
            inc option_h
        .endif

        xor ebx,ebx
        .if FindFirstFile(fn, &fblock) != -1

            FindClose(eax)
            inc ebx
        .endif

        .if !ebx
            perror(fn)
            xor eax,eax
            .break
        .endif

        lea esi,filename
        strcpy(esi, &fblock.cFileName)
        GetFullPathName(esi, _MAX_PATH, esi, 0)

        strcpy(&unixname, &[esi+3])
        .while byte ptr [eax]

            .if byte ptr [eax] == '\'

                mov byte ptr [eax],'/'
            .endif
            inc eax
        .endw

        .if strrchr(strcpy(&tempfile, esi), '.')
            strcpy(eax, ".tmp")
        .else
            strcat(&tempfile, ".tmp")
        .endif

        .if strrchr(esi, '\')
            inc eax
        .else
            mov eax,esi
        .endif
        .if strchr(strcpy(&procname, eax), '.')
            mov byte ptr [eax],0
            inc eax
        .endif
        mov ebx,eax

        .if !ftype && eax
            mov al,[eax]
            and al,NOT 0x20
            .switch al
              .case 'H': mov ftype,FILE_H: .endc
              .case 'C': mov ftype,FILE_C: .endc
              .case 'A': mov ftype,FILE_A: .endc
              .case 'I': mov ftype,FILE_I: .endc
              .case 'M': mov ftype,FILE_M: .endc
            .endsw
        .endif
        mov eax,1
    .until 1
    ret

init_srcfile endp

exit_usage proc

    puts(
        "         SF [@listfile] [-option] [source]\n"
        "\n"
        "@listfile  File name for token-list (optional)\n"
        "  default: 1. Search current directory\n"
        "           2. Search program directory\n"
        "           3. Use program default list\n"
        "\n"
        "-#         Assume # <comment>\n"
        "-;         Assume ; <comment>\n"
        "-*         Assume /* <comment> */\n"
        "-h         Write header info\n"
        "-d         Write date in header info\n"
        "-g         Include GNU General Public License\n"
        "-m         Insert Modification Date\n"
        "-x         Exclude backup (.BAK) file\n"
        "-w         Write the default TOKENLST.TXT to current directory\n"
    )
    exit(0)
    ret

exit_usage endp

main proc argc:dword, argv:ptr

    puts("Source File Version 1.06 Copyright (c) 2017 GNU General Public License\n")

    .if (argc < 2)
        exit_usage()
    .endif

    .for edi = 1: edi < argc: edi++

        mov esi,argv
        mov esi,[esi+edi*4]
        mov al,[esi]
        .switch al
          .case '?'
            exit_usage()
          .case '/'
          .case '-'
            mov al,[esi+1]
            .switch al
              .case 'g'
                inc option_g
                .endc
              .case 'x'
                inc option_x
                .endc
              .case 'w'
                write_token()
              .case ';'
                mov ftype,FILE_A
                .endc
              .case '*'
                mov ftype,FILE_C
                .endc
              .case '#'
                mov ftype,FILE_M
                .endc
              .case 'd'
                inc option_d
                .endc
              .case 'h'
                inc option_h
                .endc
              .case 'm'
                inc option_m
                .endc
              .case 't'
                inc option_t
                .endc
              .default
                exit_usage()
            .endsw
            .endc
          .default
            .if (al == '@')
                inc esi
                mov tokenfile,esi
            .elseif !init_srcfile(esi)
                exit(1)
            .endif
            .endc
        .endsw
    .endf

    read_token(argv)

    .if !fopen(&filename, "rt")
        perror(&filename)
        exit(0)
    .endif
    mov fp_src,eax

    .if !fopen(&tempfile, "wt")
        perror(&tempfile)
        fclose(fp_src)
        exit(0)
    .endif
    mov fp_out,eax

    .if option_g
        .if (ftype == FILE_A || ftype == FILE_I)
            lea eax,LicenseA
            mov License,eax
        .elseif (ftype == FILE_C || ftype == FILE_H)
            lea eax,LicenseC
            mov License,eax
        .endif
    .endif

    .if option_m
        insertdate()
    .elseif option_h
        .switch ftype
          .case FILE_C
            write_chead()
            fprintf(fp_out, " */\n")
            .endc
          .case FILE_H
            write_hhead()
            fprintf(fp_out, " */\n");
            .endc
          .case FILE_A
            write_ahead()
            .endc
          .case FILE_I
            write_ihead()
            .endc
          .case FILE_M
            write_mhead()
            .endc
        .endsw
    .endif
    .while 1
        .break .if !fgets(line, 511, fp_src)
        .if (option_h || option_m) && !option_t
            fputs(line, fp_out)
        .else
            parseline()
        .endif
    .endw

    fclose(fp_out)
    fclose(fp_src)

    lea esi,filename
    .if !option_x && !create

        strcpy(temp, esi)

        .if strrchr(temp, '.')
            strcpy(eax, ".bak")
        .else
            strcat(temp, ".bak")
        .endif
        remove(temp)
        rename(esi, temp)
    .else
        remove(esi)
    .endif
    rename(&tempfile, esi)
    exit(0)

main endp

    end _tstart

