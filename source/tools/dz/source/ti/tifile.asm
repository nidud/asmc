include tinfo.inc
include string.inc
include stdio.inc
include wsub.inc
include direct.inc
include io.inc
include iost.inc
include cfini.inc
include stdlib.inc
include ltype.inc
include dzlib.inc
include crtl.inc

.code

tigetfile proc uses ebx ti:PTINFO

    xor eax,eax ; AX first file
    mov edx,eax ; DX last file
    xor ecx,ecx ; CX count
    mov ebx,ti

    .if ebx
        .if [ebx].S_TINFO.ti_flag & _T_FILE
            mov edx,ebx
            .repeat
                mov eax,ebx
                mov ebx,[ebx].S_TINFO.ti_prev
            .until !ebx || ebx == edx
            mov ebx,eax

            .repeat
                mov edx,ebx
                mov ebx,[ebx].S_TINFO.ti_next
                add ecx,1
            .until !ebx || ebx == eax
            add ebx,1
        .endif
    .endif
    ret

tigetfile endp

tigetfilename proc uses esi edi ti:PTINFO

    mov esi,ti
    lea edi,_bufin
    .if strfn(strcpy(edi, [esi].S_TINFO.ti_file)) == edi

        mov byte ptr [edi],0
        GetCurrentDirectory(_MAX_PATH, edi)
        mov eax,[esi].S_TINFO.ti_file
    .else
        mov byte ptr [eax-1],0
    .endif
    .if wdlgopen(edi, eax, _WSAVE or _WNEWFILE)

        strcpy([esi].S_TINFO.ti_file, eax)
    .endif
    test eax,eax
    ret

tigetfilename endp

tiftime proc uses esi edi ti:PTINFO
    mov esi,ti
    .if osopen([esi].S_TINFO.ti_file, 0, M_RDONLY, A_OPEN) == -1
        or  [esi].S_TINFO.ti_flag,_T_MODIFIED
        xor eax,eax
    .else
        mov edi,eax
        getftime(edi)
        mov esi,eax
        _close(edi)
        mov eax,esi
    .endif
    test eax,eax
    ret
tiftime endp

    assume edx:ptr S_TINFO
    ;
    ; Produce output to clipboard or file
    ;
tiflushl proc uses esi edi ebx ti:PTINFO, line_start:UINT, offs_start:UINT,
    line_end:UINT, offs_end:UINT

local line_index:UINT

    mov edi,offs_start
    mov ebx,offs_end
    mov eax,line_start
    mov line_index,eax

    .if !tigetline(ti, eax)

        inc eax
        stc
    .else
        mov esi,eax
        strtrim(eax)
        tioptimalfill(ti, esi)

        sub eax,esi
        add edi,eax
        add ebx,eax

        .while  1

            inc edi
            mov eax,[edx].ti_bcol
            mov ecx,line_end

            .if ecx == line_index
                mov eax,ebx
            .endif

            .if edi > eax       ; end of selection buffer

                .if ecx == line_index ; break if last line
                    xor eax,eax
                    inc eax
                    clc
                    .break
                .endif
                jmp case_EOL    ; end of line
            .endif

            mov al,[esi+edi-1]
            .switch al

              .case 0
               case_EOL:

                inc line_index
                .if line_index > ecx
                    dec line_index
                    xor eax,eax
                    inc eax
                    clc
                    jmp toend
                .endif

                tigetnextl( ti )
                mov esi,eax

                .if ZERO?       ; break if last line (EOF)
                    xor eax,eax
                    inc eax
                    stc
                    jmp toend
                .endif

                strtrim(esi)
                tioptimalfill(ti, esi)
                mov esi,eax

                sub edi,edi
                .if [edx].ti_flag & _T_USECRLF
                    ;
                    ; insert line: 0D0A or 0A
                    ;
                    mov al,0Dh
                    oputc()
                .endif

                mov al,0Ah
                oputc()
                jz case_EOF    ; v3.24 -- eof()
                .endc

              .case 9
                mov eax,TIMAXTABSIZE-1
                .while byte ptr [esi+edi] == TITABCHAR
                    inc edi
                    dec eax
                    .break .if ZERO?
                .endw
                mov eax,9
              .default
                oputc()
                jz case_EOF
            .endsw
        .endw
    .endif
toend:                  ; out:  EAX result
    mov ecx,edi         ;   EDX line index
    mov edx,line_index  ;   ECX line offset
    ret
case_EOF:
    xor eax,eax
    stc
    jmp toend
tiflushl endp

    assume  edx:nothing

tiflush proc uses esi edi ebx ti:PTINFO

local path[_MAX_PATH]:byte

    mov esi,ti
    lea edi,path
    .if getfattr(strcpy(edi, [esi].S_TINFO.ti_file)) == -1
        .if tigetfilename(esi)
            strcpy(edi, eax)
        .else
            xor edi,edi
        .endif
    .elseif eax & _A_RDONLY
        ermsg(0, "The file is Read-Only")
        xor edi,edi
    .endif

    .if edi

        ioopen(&STDO, setfext(edi, ".$$$"), M_WRONLY, OO_MEM64K)

        .ifs eax > 0

            mov ecx,[esi].S_TINFO.ti_lcnt
            dec ecx
            tiflushl(esi, 0, 0, ecx, -1)

            .ifz

                ioclose(&STDO)
                remove(edi)
                xor edi,edi
            .else

                ioflush(&STDO)
                ioclose(&STDO)
                .if [esi].S_TINFO.ti_flag & _T_USEBAKFILE
                    remove(setfext(edi, ".bak"))
                    rename([esi].S_TINFO.ti_file, edi)
                    setfext(edi, ".$$$")
                .endif

                remove([esi].S_TINFO.ti_file)
                rename(edi, [esi].S_TINFO.ti_file)

                lea edi,[eax+1]
                and [esi].S_TINFO.ti_flag,not _T_MODIFIED

                tiftime(esi)
                mov [esi].S_TINFO.ti_time,eax

                ;
                ; update .INI file ?
                ;
                mov eax,__argv
                mov ecx,[eax]

                setfext(strcpy(&path, ecx), ".ini")
                .if !_stricmp([esi].S_TINFO.ti_file, eax)

                    CFClose()
                    CFRead(&path)
                .endif
            .endif
        .else
            xor edi,edi
        .endif
    .endif
    mov eax,edi
    test eax,eax
    ret
tiflush endp

;
; 1. Attrib A - Set background and forground color
; 2. Control    O - Set color of CONTROL characters
; 3. Quote  Q - Set color of quoted text
; 4. Digit  D - Set color of numbers
; 5. Char   C - Set color of chars
; 6. String S - Set color of string
; 7. Begin  B - Set color from start of string
; 8. Word   W - Set color of words
; 9. Nested N - Set color of nested strings
;

ID_TYPE     equ 0
ID_ATTRIB   equ 1

ST_ATTRIB   equ 1   ; attrib    <at> [<char>]
ST_CONTROL  equ 2   ; control   <at>
ST_QUOTE    equ 3   ; quote     <at>
ST_NUMBER   equ 4   ; number    <at>
ST_CHAR     equ 5   ; char      <at> <chars>
ST_STRING   equ 6   ; string    <at> <string>
ST_START    equ 7   ; start     <at> <string>
ST_WORD     equ 8   ; word      <at> <words> ...
ST_NESTED   equ 9   ; nested    <at> <string1> <string2>
ST_COUNT    equ 9

    .data
    cp_typech db "aoqdcsbwn",0


    .code

    option proc:private

TIReadLabel proc uses esi edi ebx section, buffer, endbuf, attrib

local st_type,i,p,q

    .repeat

        .break .if !INIGetEntryID(section, ID_TYPE)

        mov p,eax
        mov al,[eax]
        or  al,20h
        lea edi,cp_typech
        mov ecx,sizeof(cp_typech)
        repnz scasb

        .break .ifnz
        mov eax,edi
        sub eax,offset cp_typech
        mov st_type,eax

        mov edi,buffer
        mov edi,[edi]
        .break .if edi >= endbuf

        stosb           ; store type
        mov esi,p
        xor eax,eax
        mov i,eax

        .repeat
            inc esi
            mov al,[esi]

            .continue .if al == '_'

        .until !( byte ptr _ltype[eax+1] & _UPPER or _LOWER or _DIGIT )

        .repeat
            lodsb
            .switch
              .case al == ' '
                mov eax,esi
                .endc
              .case al
                .continue
              .default
                mov i,1
                .break .if !INIGetEntryID(section, ID_ATTRIB)
            .endsw

            mov esi,eax
            add eax,2
            mov p,eax

            __xtol(esi)       ; Attrib XX
            mov ecx,[esi]
            or  ecx,2020h
            mov ebx,attrib
            .switch
              .case cx == 'xx'
                mov al,[ebx]
                .endc
              .case cl == 'x'   ; Use default background
                __xtol(&[esi+1])
                mov ah,[ebx]
                and ah,0xF0
                or  al,ah
                .endc
              .case ch == 'x'   ; Use default foreground
                mov ah,[ebx]
                and ah,0x0F
                or  al,ah
                .endc
            .endsw
            stosb       ; store attrib

            mov esi,p
            .while byte ptr [esi] == ' '
                add esi,1
            .endw

            .if st_type == ST_ATTRIB

                mov [ebx],al    ; .ti_stat[1]
                .if byte ptr [esi]

                    __xtol(esi)
                    stosb
                .endif
                .break
            .endif

            .while  1
                .while  1
                    lodsb
                    .break .if !al
                    .break .if edi >= endbuf
                    cmp al,' '
                    sete dl
                    dec dl
                    and al,dl
                    stosb
                .endw
                .break .if al
                stosb
                inc i
                .break .if i == 100
                .break .if !INIGetEntryID(section, i)
                mov esi,eax
            .endw
        .until 1

        xor eax,eax
        .if [edi-1] != al
            stosb
        .endif
        stosb
        mov ecx,buffer
        mov [ecx],edi
        inc eax
    .until 1
    ret

TIReadLabel endp

TIDoSection proc uses esi edi ebx cfile, sname, buffer, endbuf, attrib

local file[_MAX_PATH]:sbyte, entry[_MAX_PATH]:sbyte, section, index

    mov esi,sname
    lea edi,entry

    .if byte ptr [esi] == '['
        ;
        ; [Section]   - this file
        ; [#File]     - extern file [.]
        ; [#File#Section] - extern file [<Section>]
        ;
        inc esi
        mov ebx,edi
        ;
        ; copy <Section>
        ;
        .repeat
            lodsb
            stosb
            .break .if !al
        .until al == ']'
        mov byte ptr [edi-1],0
        ;
        ; do a recursive call
        ;
        .if byte ptr [ebx] == '#'

            inc ebx
            mov eax,[ebx]
            .switch
              .case ah == ':'
              .case al == '%'
              .case al == '\'
              .case al == '/'
              .case ax == '..'
                strcpy(&file, ebx)
                .endc
              .default
                strfcat(&file, _pgmpath, ebx)
            .endsw

            mov esi,eax
            lea edi,@CStr(".")

            .if strchr(expenviron(eax), '#')

                mov byte ptr [eax],0
                lea edi,[eax+1]
            .endif

            .if INIRead(0, esi)

                mov esi,eax

                TIDoSection(esi, edi, buffer, endbuf, attrib)
                INIClose(esi)
            .endif
        .else

            TIDoSection(cfile, ebx, buffer, endbuf, attrib)
        .endif

    .elseif INIGetSection(cfile, esi)

        mov section,eax
        mov index,0

        .while INIGetEntryID(section, index)

            inc index

            .if byte ptr [eax] == '['

                TIDoSection(cfile, eax, buffer, endbuf, attrib)

            .elseif INIGetSection(cfile, eax)

                TIReadLabel(eax, buffer, endbuf, attrib)
            .endif
        .endw
    .endif
    ret

TIDoSection endp

    option proc:public

tireadstyle proc uses esi edi ebx ti:PTINFO

local file[_MAX_PATH]:sbyte
local section[64]:sbyte
local buffer:PVOID
local endbuf:PVOID   ; style + SIZE style - 2

    mov esi,ti

    mov eax,[esi].S_TINFO.ti_style
    mov buffer,eax
    mov edi,eax
    add eax,STYLESIZE-4
    mov endbuf,eax

    xor eax,eax
    mov ecx,STYLESIZE/4
    rep stosd

    strcpy(&section, "style_default")
    strcpy(&file, strfn([esi].S_TINFO.ti_file))
    mov edi,eax

    .if byte ptr [edi+strlen(edi)-1] == '.'

        mov byte ptr [edi+eax-1],0
    .endif

    .if CFGetSection("Style")

        mov ebx,eax
        .if !INIGetEntry(ebx, edi) ; FILENAME[.EXT]

            .if strext(edi)   ; .EXT ?

                inc eax
                INIGetEntry(ebx, eax)
            .endif
        .endif
    .endif

    .if eax

        lea ecx,section
        strcpy(ecx, eax)
    .endif

    TIDoSection(__CFBase, addr section, addr buffer, endbuf,
        &[esi].S_TINFO.ti_stat[1])

    mov edi,buffer
    xor eax,eax
    stosw
    inc eax
    ret

tireadstyle endp

    assume esi: ptr S_TINFO

tiread proc uses esi edi ebx ti:PTINFO

local line_count, tabs_used:byte

    mov esi,ti      ; v2.49 - auto detect CR/LF
    mov tabs_used,0

    tiftime(esi)
    mov [esi].ti_time,eax

    mov line_count,0
    mov edi,[esi].ti_bp

    .if ioopen(&STDI, [esi].ti_file, M_RDONLY, OO_MEMBUF) != -1

        mov eax,dword ptr STDI.ios_fsize
        mov [esi].ti_size,eax

        xor eax,eax
        .if eax == dword ptr STDI.ios_fsize[4]

            mov line_count,eax  ; file offset (size)
            mov ebx,eax     ; line offset (for tabs)
            mov edx,edi
            add edx,[esi].ti_blen
            sub edx,TIMAXTABSIZE

            .while  1

                .if edi >= edx

                    tirealloc(esi)
                    jz err_filetobig

                    sub edi,eax
                    add edi,[esi].ti_bp
                    mov edx,[esi].ti_bp
                    add edx,[esi].ti_blen
                    sub edx,TIMAXTABSIZE
                 .endif

                ogetc()
                .break .ifz

                .switch al

                  .case 0
                    mov al,0Ah      ; @v3.29 - convert 0 to LF
                    or  [esi].ti_flag,_T_MODIFIED

                  .case 0Ah
                    mov ecx,line_count
                    add ecx,ebx
                    .ifnz
                        .if byte ptr [edi-1] != 0Dh
                            and [esi].ti_flag,not _T_USECRLF
                        .endif
                    .endif
                    stosb
                    inc line_count
                    xor ebx,ebx
                    .endc

                  .case 09h
                    mov tabs_used,al
                    .if !( [esi].ti_flag & _T_USETABS )

                        or [esi].ti_flag,_T_MODIFIED
                        mov al,' '
                        stosb

                        inc ebx
                        mov ecx,[esi].ti_tabz
                        dec ecx
                        and ecx,TIMAXTABSIZE-1

                        .while ebx & ecx
                            .break .if ebx == [esi].ti_bcol
                            stosb
                            inc ebx
                        .endw
                    .else
                        stosb
                        inc ebx
                    .endif
                    .endc

                  .case 0Dh
                    or [esi].ti_flag,_T_USECRLF

                  .default
                    stosb
                    inc ebx
                .endsw

                .if ebx == [esi].ti_bcol

                    .if [esi].ti_flag & _T_USECRLF
                        mov byte ptr [edi],0Dh
                        inc edi
                    .endif

                    mov byte ptr [edi],0Ah
                    inc edi
                    stosb

                    push edx
                    .if !( [esi].ti_flag & _T_MODIFIED )

                        or [esi].ti_flag,_T_MODIFIED
                        ermsg(0, "Line too long, was truncated")
                    .endif
                    pop edx
                    inc line_count
                    xor ebx,ebx
                .endif
            .endw
        .else

         err_filetobig:

            ermsg(0, "File too big, no more memory")

            mov line_count,-1
            .if edi != [esi].ti_bp
                dec edi
            .endif
        .endif
        mov byte ptr [edi],0
        ioclose(&STDI)

        inc line_count
        mov eax,line_count
        mov [esi].ti_lcnt,eax
    .endif

    mov eax,line_count
    .if [esi].ti_flag & _T_UNREAD
        and [esi].ti_flag,NOT _T_UNREAD
        .if !tabs_used && eax > 1 && [esi].ti_flag & _T_USETABS
        and [esi].ti_flag,NOT _T_USETABS
        mov [esi].ti_tabz,4
        .endif
    .endif
    test eax,eax

    ret
tiread endp

    END
