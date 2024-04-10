; IDDC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2024-04-08 - added 64-bit
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
include conio.inc
include time.inc
include winnt.inc
include tchar.inc

define __IDDC__ 108
define version <"1.08">

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
                db "Asmc Binary Resource Compiler v", version,0
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

c_header            label BYTE

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

l_10                dd 0
                    dd 5                    ; SymbolTableIndex
                    dw 6                    ; Type

c_end               db ".text",0,0,0        ; Name
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
    Selection       dw 16h                  ; Selection
                    db ".data",0,0,0        ; Name
                    dd 0                    ; Value
                    dw 2                    ; SectionNumber
                    dw 0                    ; Type
                    db 3                    ; StorageClass
                    db 1                    ; NumberOfAuxSymbols
    DLength         dd ?                    ; Length
                    dw 1                    ; NumberOfRelocations
                    dw 0                    ; NumberOfLinenumbers
                    dd 0                    ; CheckSum
                    dw 0
                    dw 0                    ; Number
                    dw 0                    ; Selection
    ce_size         equ $ - c_end

    .code

strfn proc path:string_t

    ldr rcx,path
    .for ( rax = rcx, dl = [rcx] : dl : rcx++, dl=[rcx] )

        .if ( dl == '\' || dl == '/' )

            .if ( byte ptr [rcx+1] )

                lea rax,[rcx+1]
            .endif
        .endif
    .endf
    ret

strfn endp


strfcat proc uses rsi rdi buffer:string_t, path:string_t, file:string_t

    mov rdx,buffer
    mov rsi,path
    xor eax,eax
    mov ecx,-1

    .if rsi
        mov rdi,rsi
        repne scasb
        mov rdi,rdx
        not ecx
        rep movsb
    .else
        mov rdi,rdx
        repne scasb
    .endif

    dec rdi
    .if rdi != rdx
        mov al,[rdi-1]
        .if !( al == '\' || al == '/' )
            mov al,'\'
            stosb
        .endif
    .endif
    mov rsi,file

    .repeat
        lodsb
        stosb
    .until !eax
    mov rax,rdx
    ret

strfcat endp


owrite proc fp:LPFILE, b:ptr, l:int_t

    .ifd ( fwrite(b, 1, l, fp) != l )

        perror(&fileobj)
        exit(2)
    .endif
    ret

owrite endp


omf_write proc uses rsi fp:LPFILE

    lea rsi,omf
    xor eax,eax
    xor edx,edx
    movzx ecx,[rsi].S_OMFR.o_length
    add ecx,2
    .repeat
        lodsb
        add edx,eax
    .untilcxz
    lea rsi,omf
    dec edx
    not edx
    movzx ecx,[rsi].S_OMFR.o_length
    add ecx,2
    mov [rsi+rcx],dl
    inc ecx
    owrite(fp, rsi, ecx)
    ret

omf_write endp


write_coff proc uses rdi rbx fp:LPFILE, rbuf:ptr, len:int_t

  local path[_MAX_PATH]:BYTE
  local is:IMAGE_SYMBOL
  local n:int_t, j:int_t

    .if option_win64
        mov Machine,IMAGE_FILE_MACHINE_AMD64
        ;
        ; pointers from DD to DQ: + 8 byte for each object
        ;
if 0
        mov rcx,rbuf
        movzx eax,[rcx].S_ROBJ.rs_count
        inc eax
        shl eax,3
        add [rcx].S_ROBJ.rs_memsize,ax
endif
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
    owrite(fp, &c_header, eax)
    owrite(fp, rbuf, len)

    mov eax,len
    add eax,ch_size + 4
    .if option_win64
        add eax,4
        mov word ptr l_10[8],1
    .endif
    .if eax & 1
        mov n,0
        owrite(fp, &n, 1)
    .endif
    owrite(fp, &l_10, 10)

    mov eax,len
    add eax,4
    .if option_win64
        add eax,4
        mov Selection,0
    .endif
    mov DLength,eax
    owrite(fp, &c_end, ce_size)

    mov n,0
    mov ecx,sizeof(IMAGE_SYMBOL)
    lea rdi,is
    xor eax,eax
    rep stosb
    mov is.SectionNumber,2
    mov is.StorageClass,2

    lea rbx,idname
    .if option_win64
        inc rbx
    .endif
    .ifd strlen(rbx) <= 8
        memcpy(&is.ShortName, rbx, eax)
    .else
        mov is._Long,4
        inc eax
        mov n,eax
    .endif
    owrite(fp, &is, sizeof(IMAGE_SYMBOL))

    mov ecx,sizeof(IMAGE_SYMBOL)
    lea rdi,is
    xor eax,eax
    rep stosb
    lea rbx,path
    lea rdx,idname[4]
    .if option_win64
        inc rdx
    .endif
    strcpy(rbx, rdx)
    mov j,0

    mov is.Value,4
    .if option_win64
        mov is.Value,8
    .endif
    mov is.SectionNumber,2
    mov is.StorageClass,2
    .ifd strlen(strcat(rbx, "_RC")) <= 8
        memcpy(&is.ShortName, rbx, eax)
    .else
        mov edx,n
        add edx,4
        mov is._Long,edx
        inc eax
        mov j,eax
    .endif
    owrite(fp, &is, sizeof(IMAGE_SYMBOL))

    mov eax,n
    add eax,4
    add eax,j
    mov DLength,eax
    owrite(fp, &DLength, 4)
    .if n
        lea rax,idname
        .if option_win64
            inc rax
        .endif
        owrite(fp, rax, n)
    .endif
    .if j
        owrite(fp, rbx, j)
    .endif
    fclose(fp)
    xor eax,eax
    ret

write_coff endp


write_omf proc fp:LPFILE, rbuf:ptr, len:int_t

    mov rdx,strfn(&fileidd)
    strlen(strcpy(&omf.o_data[1], rdx))
    mov omf.o_type,OMF_THEADR
    mov omf.o_data,al
    add eax,2
    mov omf.o_length,ax
    omf_write(fp)

    memcpy(&omf, &COMENT, COMENT_SIZE)
    omf_write(fp)

    .if option_m == 'f'
        memcpy(&omf, &LNAMES32, LNAMES_SIZE32)
    .else
        memcpy(&omf, &LNAMES, LNAMES_SIZE)
    .endif
    omf_write(fp)

    mov eax,len
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
    omf_write(fp)

    .if option_m == 'f'
        mov omf.o_type,OMF_COMENT
        mov omf.o_length,5
        mov omf.o_data,080h
        mov omf.o_data[1],0FEh
        mov omf.o_data[2],04Fh
        mov omf.o_data[3],1
        omf_write(fp)
        mov eax,len
        add eax,4
        mov omf.o_type,OMF_SEGDEF
        mov omf.o_length,7
        mov omf.o_data,0A9h
        mov omf.o_data[1],al
        mov omf.o_data[2],ah
        mov omf.o_data[3],6
        mov omf.o_data[4],5
        mov omf.o_data[5],1
        omf_write(fp)
        mov omf.o_type,9Ah
        mov omf.o_length,2
        mov omf.o_data,02h
        mov omf.o_data[1],62h
        omf_write(fp)
    .endif
    mov omf.o_type,OMF_PUBDEF
    .if option_m == 'f'
        mov omf.o_data[0],1
        mov omf.o_data[1],2
    .else
        mov omf.o_data[0],0
        mov omf.o_data[1],1
    .endif
    lea rdx,idname
    .if option_m != 'f'
        inc rdx
    .endif
    strlen(strcpy(&omf.o_data[3], rdx))
    mov omf.o_data[2],al
    add eax,7
    mov omf.o_length,ax
    lea rcx,omf
    mov [rcx].S_OMFR.o_data[rax-4],0
    mov [rcx].S_OMFR.o_data[rax-3],0
    mov [rcx].S_OMFR.o_data[rax-2],0
    mov [rcx].S_OMFR.o_data[rax-1],0
    omf_write(fp)
    mov omf.o_type,OMF_COMENT
    mov omf.o_length,4
    mov omf.o_data,0
    mov omf.o_data[1],0A2h
    mov omf.o_data[2],1
    omf_write(fp)
    mov rdx,rdi
    mov ecx,1024
    lea rdi,omf.o_data
    xor eax,eax
    rep stosb
    mov rdi,rdx
    mov eax,len
    add eax,8
    mov omf.o_type,OMF_LEDATA
    mov omf.o_length,ax
    mov omf.o_data,1
    .if option_m == 'f'
        inc omf.o_data
    .endif
    mov ecx,len
    .if option_t
        dec ecx
    .endif
    memcpy(&omf.o_data[3+4], &dialog, ecx)
    mov omf.o_data[3],4
    omf_write(fp)
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
    omf_write(fp)
    mov omf.o_type,OMF_MODEND
    mov omf.o_length,2
    mov omf.o_data,0
    omf_write(fp)
    fclose(fp)
    xor eax,eax
    ret

write_omf endp


AssembleModule proc uses rbx module:string_t

    .new fp:LPFILE
    .new len:int_t

    .if _access(module, 0)

        perror(module)
        exit( 1 )
    .endif

    .if strrchr(strcpy(&dlname, strfn(module)), '.')

        mov byte ptr [rax],0
    .endif

    lea rbx,fileobj
    .if !option_f

        _getcwd(rbx, _MAX_PATH)
        strfcat(rbx, 0, strfn(module))
        .if strrchr(rbx, '.')
            mov byte ptr [rax],0
        .endif
        strcat(rbx, &extobj)
    .endif

    .if !fopen(module, "rb")

        perror(module)
        exit( 2 )
    .endif
    mov fp,rax

    mov len,fread(&dialog, 1, MAXIDDSIZE, fp)
    fclose(fp)

    .if ( len == 0 )

        perror(module)
        exit( 3 )
    .endif
    .if ( option_t )
        inc len
    .endif

    .if ( len > 1020 )

        perror("Resource is to big -- > 1024")
        exit( 3 )
    .endif

    .if !fopen(rbx, "wb")

        perror(rbx)
        exit( 2 )
    .endif

    mov fp,rax
    .if option_omf
        write_omf(fp, &dialog, len)
    .else
        write_coff(fp, &dialog, len)
    .endif
    ret

AssembleModule endp


AssembleSubdir proc directory:string_t, wild:string_t

   .new path[_MAX_PATH]:char_t
   .new ff:_finddata_t
   .new h:ptr
   .new rc:int_t = 0

    mov rcx,strfcat(&path, directory, wild)
    .ifd ( _findfirst(rcx, &ff) != -1 )

        mov h,rax
        .repeat
            mov rc,AssembleModule(strfcat(&path, directory, &ff.name))
        .untild _findnext(h, &ff)
        _findclose(h)
    .endif

    mov rcx,strfcat(&path, directory, "*.*")
    .ifd ( _findfirst(rcx, &ff) != -1 )

        mov h,rax
        .repeat
            mov eax,dword ptr ff.name
            and eax,00FFFFFFh
            .if ( ff.attrib & _A_SUBDIR && ax != '.' && eax != '..' )
                perror(&ff.name)
                .if AssembleSubdir(strfcat(&path, directory, &ff.name), wild)
                    mov rc,eax
                   .break
                .endif
            .endif
        .untild _findnext(h, &ff)
        _findclose(h)
    .endif
    mov eax,rc
    ret

AssembleSubdir endp


exit_usage proc

    printf( "Asmc Binary Resource Compiler Version %d.%d.%d.%d\n"
            "Usage: IDDC [-Options] <idd-file>\n"
            " Options:\n"
            "  -mc     Set memory model to Compact\n"
            "  -ml     Set memory model to Large\n"
            "  -mf     Set memory model to Flat (default)\n"
            "  -win64  Generate 64-bit COFF object\n"
            "  -omf    Generate OMF format object file (default)\n"
            "  -coff   Generate COFF format object file\n"
            "  -Fo#    Names an object file\n"
            "  -r      Recurse subdirectories with use of wildcards\n"
            "  -t      Compile text file (add zero)\n",
            __IDDC__ / 100, __IDDC__ mod 100,
            __ASMC__ / 100, __ASMC__ mod 100 )
    exit( 0 )
    ret

exit_usage endp


main proc argc:int_t, argv:array_t

  local path[_MAX_PATH]:char_t

    .if ( argc <= 1 )
        exit_usage()
    .endif

    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rdx,argv
        mov rcx,[rdx+rbx*size_t]
        mov eax,[rcx]

        .switch al
        .case 'h'
ifndef __UNIX__
        .case '?'
endif
            exit_usage()
        .case '-'
ifndef __UNIX__
        .case '/'
endif
            shr eax,8
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
            .case 'F'
                inc option_f
                add rcx,3
                .if ( byte ptr [rcx] == 0 )
                    inc ebx
                    .if ( ebx < argc )
                        mov rcx,[rdx+rbx*size_t]
                    .endif
                .endif
                strcpy(&fileobj, rcx)
               .endc
            .case 'r'
                inc option_r
               .endc
            .case 't'
                inc option_t
               .endc
            .default
                .gotosw(1:'h')
            .endsw
            .endc
        .default
            .if !fileidd
                strcpy(&fileidd, rcx)
            .else
                .gotosw('?')
            .endif
        .endsw
    .endf

    lea rbx,fileidd
    .if !option_r
        AssembleModule(rbx)
    .else
        strcpy(&path, rbx)
        .if strfn(rbx) > rbx
            dec rax
        .endif
        mov BYTE PTR [rax],0
        AssembleSubdir(rbx, strfn(&path))
    .endif
    ret

main endp

    end _tstart
