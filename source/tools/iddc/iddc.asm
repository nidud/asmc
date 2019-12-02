;
; Change history:
; 2016-09-24 - added switch -win64
; 2016-04-05 - added switch -coff and -omf
; 2014-08-18 - moved IDD_ to top -- align 16
; 2014-08-09 - added switch -r
; 2013-01-01 - created
;
include io.inc
include direct.inc
include stdio.inc
include stdlib.inc
include string.inc
include consx.inc
include time.inc
include winnt.inc
include tchar.inc

__IDDC__        equ 106

MAXIDDSIZE      equ 2048
OMF_THEADR      equ 080h
OMF_COMENT      equ 088h
OMF_PUBDEF      equ 090h
OMF_LNAMES      equ 096h
OMF_SEGDEF      equ 098h
OMF_LEDATA      equ 0A0h
OMF_FIXUPP      equ 09Ch
OMF_MODEND      equ 08Ah
OMF_FIXUPP32    equ 09Dh

S_OMFR          STRUC
o_type          db ?
o_length        dw ?
o_data          db MAXIDDSIZE dup(?)
o_cksum         db ?
S_OMFR          ENDS

.data

console         dd 0
PUBLIC          console

omf             S_OMFR  <0>
fileidd         db _MAX_PATH dup(0)
fileobj         db _MAX_PATH dup(0)
idname          db '_IDD_'
dlname          db 128 dup(0)
dialog          db MAXIDDSIZE dup(0)
extobj          db '.obj',0
options         db "fmtrocw",0
option_f        db 0
option_m        db 'f'  ; -mc, -ml, -mf
option_t        db 0
option_r        db 0
option_omf      db 1
option_coff     db 0
option_win64    db 0

COMENT          db 88h,1Ch,00h,1Ah
                db 'Doszip Resource Edit v2.33',0
COMENT_SIZE     = $ - COMENT

LNAMES          db 96h,0Dh,00h,00h
                db 4, 'DATA'
                db 5, '_DATA'
LNAMES_SIZE     = $ - LNAMES

LNAMES32        db 96h,1Dh,00h,00h
                db 4, 'FLAT'
                db 4, 'CODE'
                db 5, '_TEXT'
                db 4, 'DATA'
                db 5, '_DATA'
LNAMES_SIZE32   = $ - LNAMES

        .code

strfn proc uses edi ecx path:LPSTR
    mov edi,path
    lea eax,[edi+strlen(edi)-1]
@@:
    cmp byte ptr [eax],'\'
    je  @F
    cmp byte ptr [eax],'/'
    je  @F
    dec eax
    cmp eax,edi
    ja  @B
    lea eax,[edi-1]
@@:
    inc eax
    ret
strfn endp

strfcat PROC USES esi edi ecx edx buffer:LPSTR, path:LPSTR, file:LPSTR

    mov edx,buffer
    mov esi,path
    xor eax,eax
    lea ecx,[eax-1]

    .if esi
        mov edi,esi ; overwrite buffer
        repne scasb
        mov edi,edx
        not ecx
        rep movsb
    .else
        mov edi,edx ; length of buffer
        repne scasb
    .endif

    dec edi
    .if edi != edx  ; add slash if missing

        mov al,[edi-1]
        .if !( al == '\' || al == '/' )

            mov al,'\'
            stosb
        .endif
    .endif

    mov esi,file    ; add file name
    .repeat
        lodsb
        stosb
    .until !eax
    mov eax,edx
    ret

strfcat ENDP

owrite proc fp, b, l

    .if fwrite(b, 1, l, fp) != l

        perror(addr fileobj)
        exit(2)
    .endif
    ret

owrite  ENDP

omf_write proc uses esi
    lea esi,omf
    xor eax,eax
    xor edx,edx
    movzx ecx,[esi].S_OMFR.o_length
    add ecx,2
    .repeat
        lodsb
        add edx,eax
    .untilcxz
    lea esi,omf
    dec edx
    not edx
    movzx ebx,[esi].S_OMFR.o_length
    add ebx,2
    mov [esi+ebx],dl
    inc ebx
    owrite(edi, esi, ebx)
    ret
omf_write endp

WR_COFF PROC USES esi edi ebx handle, rbuf, len
local path[_MAX_PATH]:BYTE
local is:IMAGE_SYMBOL

    .data
    c_header        label BYTE
    Machine         dw IMAGE_FILE_MACHINE_I386
    Sections        dw 2
    TimeStamp       dd ?
    SymbolTable     dd ?
    Symbols         dd 6
    OptionalHeader  dw 0
    Characteristics dw 0
                    db ".text",0,0,0        ; Name
                    dd 0                    ; PhysicalAddress
                    dd 0                    ; VirtualAddress
                    dd 0                    ; SizeOfRawData
                    dd 0                    ; PointerToRawData
                    dd 0                    ; PointerToRelocations
                    dd 0                    ; PointerToLinenumbers
                    dw 0                    ; NumberOfRelocations
                    dw 0                    ; NumberOfLinenumbers
                    dd 60500020h            ; Characteristics
                    db ".data",0,0,0
                    dd 0                    ; PhysicalAddress
                    dd 0                    ; VirtualAddress
    SizeOfRawData   dd ?                    ; SizeOfRawData
                    dd 64h                  ; PointerToRawData
    Relocations     dd ?                    ; PointerToRelocations
                    dd 0                    ; PointerToLinenumbers
                    dw 1                    ; NumberOfRelocations
                    dw 0                    ; NumberOfLinenumbers
                    dd 0C0500040h           ; Characteristics
                    dd 0                    ; _IDD_*
    ch_size         equ $ - c_header
                    dd 0
    .code

    .if option_win64
        mov Machine,IMAGE_FILE_MACHINE_AMD64
        ;
        ; pointers from DD to DQ: + 8 byte for each object
        ;
        mov ecx,rbuf
        movzx eax,[ecx].S_ROBJ.rs_count
        inc eax
        shl eax,3
        add [ecx].S_ROBJ.rs_memsize,ax
    .endif

    _time(&TimeStamp)
    mov eax,len
    add eax,4
    .if option_win64
        add eax,4
    .endif
    mov SizeOfRawData,eax
    .if eax & 1
        add eax,1
    .endif
    add eax,64h
    mov Relocations,eax
    add eax,10
    mov SymbolTable,eax

    mov eax,ch_size
    .if option_win64
        add eax,4
    .endif
    owrite(handle, &c_header, eax)
    owrite(handle, rbuf, len)

    .data
        l_10    dd 0
                dd 5            ; SymbolTableIndex
                dw 6            ; Type
    .code

    mov eax,len
    add eax,ch_size + 4
    .if option_win64
        add eax,4
        mov WORD PTR l_10[8],1
    .endif
    .if eax & 1
        push 0
        mov eax,esp
        owrite(handle, eax, 1)
        pop eax
    .endif
    owrite(handle, &l_10, 10)

    .data
    c_end       db ".text",0,0,0        ; Name
                dd 0                    ; Value
                dw 1                    ; SectionNumber
                dw 0                    ; Type
                db 3                    ; StorageClass
                db 1                    ; NumberOfAuxSymbols
                dd 0                    ; Length
                dw 0                    ; NumberOfRelocations
                dw 0                    ; NumberOfLinenumbers
                dd 0                    ; CheckSum
                dw 0
                dw 0                    ; Number
    Selection   dw 16h                  ; Selection
                db ".data",0,0,0        ; Name
                dd 0                    ; Value
                dw 2                    ; SectionNumber
                dw 0                    ; Type
                db 3                    ; StorageClass
                db 1                    ; NumberOfAuxSymbols
    DLength     dd ?                    ; Length
                dw 1                    ; NumberOfRelocations
                dw 0                    ; NumberOfLinenumbers
                dd 0                    ; CheckSum
                dw 0
                dw 0                    ; Number
                dw 0                    ; Selection
    ce_size equ $ - c_end
    .code

    mov eax,len
    add eax,4
    .if option_win64
        add eax,4
        mov Selection,0
    .endif
    mov DLength,eax
    owrite(handle, addr c_end, ce_size)

    xor esi,esi
    mov ecx,sizeof(IMAGE_SYMBOL)
    lea edi,is
    xor eax,eax
    rep stosb
    mov is.SectionNumber,2
    mov is.StorageClass,2

    lea edi,idname
    .if option_win64
        inc edi
    .endif
    .if strlen(edi) <= 8
        memcpy(&is.ShortName, edi, eax)
    .else
        mov is._Long,4
        lea esi,[eax+1]
    .endif
    owrite(handle, &is, sizeof(IMAGE_SYMBOL))

    mov ecx,sizeof(IMAGE_SYMBOL)
    lea edi,is
    xor eax,eax
    rep stosb
    lea ebx,path
    lea edi,idname[4]
    .if option_win64
        inc edi
    .endif
    strcpy(ebx, edi)
    xor edi,edi

    mov is.Value,4
    .if option_win64
        mov is.Value,8
    .endif
    mov is.SectionNumber,2
    mov is.StorageClass,2
    .if strlen(strcat(ebx, "_RC")) <= 8
        memcpy(&is.ShortName, ebx, eax)
    .else
        lea edx,[esi+4]
        mov is._Long,edx
        lea edi,[eax+1]
    .endif
    owrite(handle, &is, sizeof(IMAGE_SYMBOL))

    lea eax,[esi+edi+4]
    mov DLength,eax
    owrite(handle, &DLength, 4)

    .if esi
        lea eax,idname
        .if option_win64
            inc eax
        .endif
        owrite(handle, eax, esi)
    .endif
    .if edi
        owrite(handle, ebx, edi)
    .endif

    fclose(handle)
    xor eax,eax
    ret

WR_COFF endp

WR_OMF proc uses esi edi ebx handle, rbuf, len

    mov edx,strfn(&fileidd)
    strlen(strcpy(&omf.o_data[1], edx))
    mov omf.o_type,OMF_THEADR
    mov omf.o_data,al
    add eax,2
    mov omf.o_length,ax
    omf_write()

    memcpy(&omf, &COMENT, COMENT_SIZE)
    omf_write()

    .if option_m == 'f'
        memcpy(&omf, &LNAMES32, LNAMES_SIZE32)
    .else
        memcpy(&omf, &LNAMES, LNAMES_SIZE)
    .endif
    omf_write()

    mov eax,esi
    add eax,4
    mov omf.o_type,OMF_SEGDEF
    mov omf.o_length,7

    .if option_m == 'f'
        mov omf.o_data,0A9h
        mov omf.o_data[1],0
        mov omf.o_data[2],0
        mov omf.o_data[3],4
        mov omf.o_data[4],3
        mov omf.o_data[5],1
    .else
        mov omf.o_data,48h
        mov omf.o_data[1],al
        mov omf.o_data[2],ah
        mov omf.o_data[3],3
        mov omf.o_data[4],2
        mov omf.o_data[5],1
    .endif
    omf_write()

    .if option_m == 'f'
        mov omf.o_type,OMF_COMENT
        mov omf.o_length,5
        mov omf.o_data,080h
        mov omf.o_data[1],0FEh
        mov omf.o_data[2],04Fh
        mov omf.o_data[3],1
        omf_write()
        mov eax,esi
        add eax,4
        mov omf.o_type,OMF_SEGDEF
        mov omf.o_length,7
        mov omf.o_data,0A9h
        mov omf.o_data[1],al
        mov omf.o_data[2],ah
        mov omf.o_data[3],6
        mov omf.o_data[4],5
        mov omf.o_data[5],1
        omf_write()
        mov omf.o_type,9Ah
        mov omf.o_length,2
        mov omf.o_data,02h
        mov omf.o_data[1],62h
        omf_write()
    .endif
    mov omf.o_type,OMF_PUBDEF
    .if option_m == 'f'
        mov omf.o_data[0],1
        mov omf.o_data[1],2
    .else
        mov omf.o_data[0],0
        mov omf.o_data[1],1
    .endif
    mov edx,offset idname
    .if option_m != 'f'
        inc edx
    .endif
    strlen(strcpy(&omf.o_data[3], edx))
    mov omf.o_data[2],al
    add eax,7
    mov omf.o_length,ax
    mov ebx,eax
    mov omf.o_data[ebx-4],0
    mov omf.o_data[ebx-3],0
    mov omf.o_data[ebx-2],0
    mov omf.o_data[ebx-1],0
    omf_write()
    mov omf.o_type,OMF_COMENT
    mov omf.o_length,4
    mov omf.o_data,0
    mov omf.o_data[1],0A2h
    mov omf.o_data[2],1
    omf_write()
    mov edx,edi
    mov ecx,1024
    lea edi,omf.o_data
    xor eax,eax
    rep stosb
    mov edi,edx
    mov eax,esi
    add eax,8
    mov omf.o_type,OMF_LEDATA
    mov omf.o_length,ax
    mov omf.o_data,1
    .if option_m == 'f'
        inc omf.o_data
    .endif
    mov ecx,esi
    .if option_t
        dec ecx
    .endif
    memcpy(&omf.o_data[3+4], &dialog, ecx)
    mov omf.o_data[3],4
    omf_write()
    mov omf.o_type,OMF_FIXUPP
    .if option_m == 'f'
        mov omf.o_type,OMF_FIXUPP32
    .endif
    mov omf.o_length,5
    mov omf.o_data[1],0
    mov al,0CCh
    .if option_m == 'f'
        mov al,0E4h
    .endif
    mov omf.o_data[0],al
    mov omf.o_data[2],54h
    mov omf.o_data[3],1
    .if option_m == 'f'
        mov omf.o_data[3],2
    .endif
    mov omf.o_data[4],0
    omf_write()
    mov omf.o_type,OMF_MODEND
    mov omf.o_length,2
    mov omf.o_data,0
    omf_write()
    fclose(edi)
    xor eax,eax
    ret
WR_OMF endp


AssembleModule PROC USES esi edi ebx module

    .if _access(module, 0)

        perror(module)
        exit(1)
    .endif

    .if strrchr(strcpy(&dlname, strfn(module)), '.')

        mov byte ptr [eax],0
    .endif

    lea edi,fileobj

    .if !option_f

        _getcwd(edi, _MAX_PATH)
        strfcat(edi, 0, strfn(module))

        .if strrchr(edi, '.')

            mov byte ptr [eax],0
        .endif
        strcat(edi, &extobj)
    .endif

    .if !fopen(module, "rb")

        perror(module)
        exit(2)
    .endif
    mov ebx,eax

    mov esi,fread(&dialog, 1, MAXIDDSIZE, ebx)
    fclose(ebx)

    .if !esi

        perror(module)
        exit(3)
    .endif

    .if option_t
        inc esi
    .endif

    .if esi > 1020

        perror("Resource is to big -- > 1024")
        exit(3)
    .endif

    .if !fopen(edi, "wb")

        perror(edi)
        exit(2)
    .endif

    mov edi,eax
    .if option_omf
        WR_OMF(edi, &dialog, esi)
    .else
        WR_COFF(edi, &dialog, esi)
    .endif
    ret

AssembleModule ENDP


AssembleSubdir PROC USES esi edi ebx directory, wild

  local path[_MAX_PATH]:BYTE
  local ff:_finddata_t
  local h:HANDLE
  local rc:DWORD

    lea esi,path
    lea edi,ff
    lea ebx,ff.name
    mov rc,0

    .if _findfirst(strfcat(esi, directory, wild), edi) != -1

        mov h,eax

        .repeat

            mov rc,AssembleModule(strfcat(esi, directory, ebx))

        .until _findnext(h, edi)

        _findclose(h)

    .endif

    .if _findfirst(strfcat(esi, directory, "*.*"), edi) != -1

        mov h,eax

        .repeat

            mov eax,[ebx]
            and eax,00FFFFFFh

            .if ff.attrib & _A_SUBDIR && ax != '.' && eax != '..'

                perror(ebx)

                .if AssembleSubdir(strfcat(esi, directory, ebx), wild)

                    mov rc,eax
                    .break
                .endif
            .endif

        .until _findnext(h, edi)

        _findclose(h)
    .endif
    mov eax,rc
    ret

AssembleSubdir ENDP

arg_option proc uses ebx arg:ptr

    mov ebx,arg
    mov eax,[ebx]

    .switch al

      .case '?'

        printf( "Binary Resource Compiler Version %d.%d.%d.%d\n"
                "Usage: IDDC [-/Options] <idd-file>\n"
                " Options:\n"
                "  -mc     output 16-bit .compact\n"
                "  -ml     output 16-bit .large\n"
                "  -mf     output 32-bit .flat (default)\n"
                "  -win64  output 64-bit .flat\n"
                "  -omf    output OMF object (default)\n"
                "  -coff   output COFF object\n"
                "  -f#     full pathname of .OBJ file\n"
                "  -r      recurse subdirectories\n"
                "  -t      compile text file (add zero)\n"
                "\n",
                __IDDC__ / 100, __IDDC__ mod 100,
                __ASMC__ / 100, __ASMC__ mod 100 )
        exit(0)

      .case '-'
      .case '/'

        shr eax,8
        or  eax,0x202020

        .switch al

          .case 'w'
            inc option_win64

          .case 'c'
            mov option_omf,0
            inc option_coff
            .endc

          .case 'm'
            mov option_m,ah
            .endc

          .case 'o'
            mov option_coff,0
            inc option_omf
            .endc

          .case 'f'
            inc option_f
            add ebx,2
            strcpy(&fileobj, ebx)
            .endc

          .case 'r'
            inc option_r
            .endc

          .case 't'
            inc option_t
            .endc

          .default
            .gotosw(1:'?')
        .endsw
        .endc

      .default
        .if !fileidd
            strcpy(&fileidd, ebx)
        .else
            .gotosw('?')
        .endif
    .endsw

    xor eax,eax
    inc eax
    ret

arg_option endp


main proc argc:int_t, argv:array_t

  local path[_MAX_PATH]:BYTE

    mov edi,argc
    mov esi,argv

    .if edi == 1
        arg_option("?")
    .endif
    dec edi

    lodsd
    .repeat
        lodsd
        arg_option(eax)
        dec edi
    .until !edi

    lea esi,fileidd
    lea edi,path

    .if !option_r
        AssembleModule(esi)
    .else
        strcpy(edi, esi)
        .if strfn(esi) > esi
            dec eax
        .endif
        mov BYTE PTR [eax],0
        AssembleSubdir(esi, strfn(edi))
    .endif
    ret

main endp

    end _tstart
