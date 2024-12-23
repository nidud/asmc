; ZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include direct.inc
include stdio.inc
include stdlib.inc
include string.inc
include time.inc
include deflate.inc

define MAXPATH 0x8000
define MAXMASK 0x0200

ifdef __UNIX__
define PC '/'
else
define PC '\'
endif

.class Zip

    path        string_t ?
    base        string_t ?
    file        string_t ?
    mask        string_t ?
    arch        string_t ?
    fpz         LPFILE ?
    fpc         LPFILE ?
    recurse     int_t ?
    verbose     int_t ?
    zl          ZipLocal <>
    zc          ZipCentral <>
    ze          ZipEndCent <>
    pbuf        char_t MAXPATH dup(?)
    mbuf        char_t MAXMASK dup(?)

    Zip         proc
    Release     proc
    Open        proc :string_t
    AddFile     proc :string_t
    ScanFiles   proc
    Compress    proc :ptr _finddata_t
   .ends

   .code

    assume rbx:ptr Zip

Zip::Compress proc uses rsi rdi rbx ff:ptr _finddata_t

   .new rc:int_t
   .new fn[_MAX_PATH]:char_t

    ldr rbx,this
    ldr rdx,ff

    ; collect base and convert to unix

    .for ( eax = 1, rdi = &fn, rsi = [rbx].base, rcx = rdi : eax : )

        lodsb
        .if ( al == '\' || al == '/' )
            mov al,'/'
            lea rcx,[rdi+1] ; start of file name
        .endif
        stosb
    .endf

    ; set ff.name to file in path and unix name

    .for ( eax = 1, rdi = rcx, rsi = &[rdx]._finddata_t.name, rcx = [rbx].file : eax : rcx++ )

        lodsb
        stosb
        mov [rcx],al
    .endf

    ; set file name length

    lea rax,fn
    sub rdi,rax
    dec di
    mov [rbx].zl.fnsize,di
    mov [rbx].zc.fnsize,di

    ; offset of local header

    mov rcx,[rbx].fpz
    mov rax,[rcx].FILE._ptr
    sub rax,[rcx].FILE._base
    mov [rbx].zc.off_local,eax

    ; last mod file time

    .ifd localtime( &[rdx]._finddata_t.time_write )

        mov     rcx,rax
        mov     eax,[rcx].tm.tm_year
        sub     eax,DT_BASEYEAR - 1900
        shl     eax,9
        mov     edx,[rcx].tm.tm_mon
        inc     edx
        shl     edx,5
        or      eax,edx
        or      eax,[rcx].tm.tm_mday
        mov     [rbx].zl.date,ax
        mov     [rbx].zc.date,ax
        mov     eax,[rcx].tm.tm_sec
        shr     eax,1
        mov     edx,eax ; second/2
        mov     al,byte ptr [rcx].tm.tm_hour
        mov     ecx,[rcx].tm.tm_min
        shl     ecx,5
        shl     eax,11
        or      eax,ecx
        or      eax,edx
        mov     [rbx].zl.time,ax
        mov     [rbx].zc.time,ax
    .else
        mov     [rbx].zl.time,ax
        mov     [rbx].zc.time,ax
        mov     [rbx].zl.date,ax
        mov     [rbx].zc.date,ax
    .endif

    mov rc,-1

    .repeat

        ; write local header

        .break .ifd ( fwrite(&[rbx].zl, 1, ZipLocal, [rbx].fpz) != ZipLocal )
        fwrite(&fn, 1, [rbx].zl.fnsize, [rbx].fpz)
        .break .if ( ax != [rbx].zl.fnsize )

        ; compress

        .break .ifd ( deflate([rbx].path, [rbx].fpz, &[rbx].zl) == 0 )

        ; update local and central file header

        mov ecx,[rbx].zc.off_local
        mov rdx,[rbx].fpz
        add rcx,[rdx].FILE._base

        mov [rbx].zc.crc,[rbx].zl.crc
        mov [rcx].ZipLocal.crc,eax
        mov [rbx].zc.csize,[rbx].zl.csize
        mov [rcx].ZipLocal.csize,eax
        mov [rbx].zc.fsize,[rbx].zl.fsize
        mov [rcx].ZipLocal.fsize,eax
        mov [rbx].zc.method,[rbx].zl.method
        mov [rcx].ZipLocal.method,ax

        ; write central file header

        .break .ifd ( fwrite(&[rbx].zc, 1, ZipCentral, [rbx].fpc) != ZipCentral )
        fwrite(&fn, 1, [rbx].zl.fnsize, [rbx].fpc)
        .break .if ( ax != [rbx].zl.fnsize )

        inc [rbx].ze.entry_dir
        mov rc,0
        .if ( [rbx].verbose )
            printf(" %s\n", &fn)
        .endif
    .until 1
    mov eax,rc
    ret

Zip::Compress endp


Zip::ScanFiles proc uses rbx

   .new fh:intptr_t
   .new np:string_t
   .new ff:_finddata_t
   .new rc:int_t = 0

    ldr rbx,this

    .ifd ( _findfirst( [rbx].path, &ff) != -1 )

        mov fh,rax
        .repeat
            .if !( ff.attrib & _F_SUBDIR )

                .ifd [rbx].Compress(&ff)

                    mov rc,eax
                   .break
                .endif
            .endif
        .until _findnext(fh, &ff)
        _findclose(fh)
    .endif

    .if ( [rbx].recurse )

        strcpy([rbx].file, "*.*")
        .ifd ( _findfirst( [rbx].path, &ff) != -1 )

            mov fh,rax
            .repeat

                mov eax,dword ptr ff.name
                and eax,0x00FFFFFF

                .if ( ax != '.' && eax != '..' && ff.attrib & _F_SUBDIR )

                    mov np,[rbx].file
                    mov [rbx].file,strfn(strfcat([rbx].file, &ff.name, [rbx].mask))
                    .ifd [rbx].ScanFiles()
                        mov rc,eax
                       .break
                    .endif
                    mov [rbx].file,np
                .endif
            .until _findnext(fh, &ff)
            _findclose(fh)
        .endif
    .endif
    .return( rc )

Zip::ScanFiles endp


Zip::AddFile proc uses rsi rdi rbx name:string_t

   .new p:string_t

    ldr rbx,this
    ldr rsi,name

    mov [rbx].file,rsi
    mov rdi,[rbx].path
    mov rsi,[rbx].file

    assume rsi:string_t
    assume rdi:string_t

    .repeat

        mov eax,dword ptr [rsi]
ifdef __UNIX__
        .if ( al == '/' )

            inc rsi
else
        .if ( ah == ':' || al == '/' || al == '\' )

            .if ( ah == ':' )
                add rsi,2
            .endif
            .while ( [rsi] == '/' || [rsi] == '\' )
                inc rsi
            .endw
endif
        .else

            .break .if !_getcwd( rdi, MAXPATH )

            add strlen(rax),[rbx].path
            mov rdi,rax
ifdef __UNIX__
ifdef _WIN64
            mov rsi,[rbx].file
endif
            .if ( [rdi-1] == '/' )
else
            .if ( [rdi-1] == '/' || [rdi-1] == '\' )
endif
                dec rdi
            .endif
        .endif

        mov rax,[rbx].path
        lea rcx,[rax+MAXPATH-1]
        mov [rdi],PC
        mov [rbx].base,&[rdi+1]

        .while ( [rsi] )

            mov ax,word ptr [rsi+1]
            .if ( [rsi] == '.' && al == '.' && ( !ah || ah == '\' || ah == '/' ) )

                .repeat
                    dec rdi
                    mov al,[rdi]
                .until ( al == '\' || al == '/' || rdi < [rbx].path )

                .if ( rdi < [rbx].path )

                    _set_errno( EACCES )
                    xor eax,eax
                   .break( 1 )
                .endif

                add rsi,2
                .if ( [rsi] )
                    inc rsi
                .endif
                mov [rbx].base,&[rdi+1]

            .elseif ( [rsi] == '.' && ( al == '\' || al == '/' || !al ) )

                inc rsi
                .if ( [rsi] )
                    inc rsi
                .endif

            .else

                mov rdx,rdi
                mov al,[rsi]

                .while ( al && al != '\' && al != '/' && rdi < rcx )

                    inc rsi
                    inc rdi
                    mov [rdi],al
                    mov al,[rsi]
                .endw

                .if ( rdi >= rcx )

                    _set_errno( ERANGE )
                    xor eax,eax
                   .break( 1 )
                .endif

                .if ( rdi == rdx )

                    _set_errno( EINVAL )
                    xor eax,eax
                   .break( 1 )
                .endif

                inc rdi
                mov [rdi],PC
                .if ( [rsi] == '\' || [rsi] == '/' )
                    inc rsi
                .endif
            .endif
        .endw
        mov [rdi],0
        mov rax,[rbx].path
    .until 1
    .if ( rax == NULL )

        perror([rbx].file)
       .return( 0 )
    .endif

    mov [rbx].file,strfn([rbx].path)
    .if !strpbrk([rbx].path, "*?")
        lea rax,@CStr("*.*")
    .else
        mov rax,[rbx].file
    .endif
    strcpy([rbx].mask, rax)

    assume rsi:nothing
    assume rdi:nothing

    [rbx].ScanFiles()
    ret

Zip::AddFile endp


Zip::Open proc uses rbx name:string_t

    ldr rbx,this
    ldr rcx,name

    mov [rbx].arch,rcx
    .if ( fopen(rcx, "wb") == NULL )

        .return
    .endif
    mov [rbx].fpz,rax
    _fsetmode(rax, _IOMEMBUF)
    mov [rbx].fpc,_fopenm(rax)
    mov [rbx].zl.Signature,ZIPLOCALID
    mov [rbx].zc.Signature,ZIPCENTRALID
    mov [rbx].ze.Signature,ZIPENDSENTRID
    mov [rbx].zl.version,20
    mov [rbx].zc.version_made,20
    mov [rbx].zc.version_need,10
    mov eax,1
    ret

Zip::Open endp


Zip::Release proc uses rbx

   .new error:errno_t

    ldr rbx,this

    _get_errno(&error)
    mov rcx,[rbx].fpz
    mov rdx,[rbx].fpc

    .if ( !rcx || !rdx || ![rbx].ze.entry_dir )

        .if ( rcx )

            fclose(rcx)
            remove([rbx].arch)
        .endif
        perror([rbx].arch)
        .if ( [rbx].fpc )

            fclose([rbx].fpc)
        .endif
    .else
        mov rax,[rcx].FILE._ptr
        sub rax,[rcx].FILE._base
        mov [rbx].ze.off_cent,eax
        mov rax,[rdx].FILE._ptr
        sub rax,[rdx].FILE._base
        mov [rbx].ze.size_cent,eax
        fwrite(&[rbx].ze, 1, ZipEndCent, [rbx].fpc)
        _fsetmode([rbx].fpz, 0)
        _fsetmode([rbx].fpc, 0)
        fflush([rbx].fpz)
        fflush([rbx].fpc)
        fclose([rbx].fpz)
        fclose([rbx].fpc)
    .endif
    free(rbx)
    ret

Zip::Release endp


Zip::Zip proc uses rbx

    _set_errno(0)
    mov rbx,@ComAlloc(Zip)
    mov [rbx].path,&[rbx].pbuf
    mov [rbx].mask,&[rbx].mbuf
    mov rax,rbx
    ret

Zip::Zip endp


main proc argc:int_t, argv:array_t

    .new i:int_t
    .new a:int_t = 0
    .new zip:ptr Zip()

    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rdx,argv
        mov rcx,[rdx+rbx*size_t]
        mov eax,[rcx]

        .switch al
ifndef __UNIX__
        .case '/'
endif
        .case '-'
            .if ah == 'r'

                mov rax,zip
                inc [rax].Zip.recurse
               .endc
            .elseif ah == 'v'
                mov rax,zip
                inc [rax].Zip.verbose
               .endc
            .endif
        .case 'h'
ifndef __UNIX__
        .case '?'
endif
            printf(
                "Usage: zip [options] <archive> <file(s)>\n"
                "\n"
                "-r Recurse subdirectories\n"
                "-v Make some noise\n"
                )
           .break

        .default
            .if ( a == 0 )
                zip.Open(rcx)
                inc a
            .else
                zip.AddFile(rcx)
            .endif
            .break .if !eax
        .endsw
    .endf
    zip.Release()
    xor eax,eax
    ret

main endp

    end
