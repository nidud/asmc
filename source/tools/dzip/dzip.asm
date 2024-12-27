; DZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2024-12-22 - Added 64K dictionary
; 2024-12-21 - Added explode
; 2024-12-20 - Added inflate (-x)
; 2024-12-19 - Test case for deflate
;
include io.inc
include share.inc
include fcntl.inc
include errno.inc
include direct.inc
include stdio.inc
include stdlib.inc
include string.inc
include time.inc
include deflate.inc
include fltintrn.inc

define __DZIP__ 103

define MAXPATH  0x8000    ; 32K directory
define MAXMASK  0x0200    ;
define MAXHEAP  0x1000000 ; 16M --> zip file

define METHOD_STORE     0 ; supported method for unzip
define METHOD_DEFLATE   8
define METHOD_DEFLATE64 9
define METHOD_IMPLODE   6

ifdef __UNIX__
define PC '/'
else
define PC '\'
endif

.data?

    path        string_t ?
    base        string_t ?
    file        string_t ?
    mask        string_t ?
    arch        string_t ?
    outp        string_t ?
    offs        size_t ?
    fpz         LPFILE ?
    fpc         LPFILE ?
    pbuf        char_t MAXPATH dup(?)
    mbuf        char_t MAXMASK dup(?)
    zl          ZIPLOCAL <>
    zc          ZIPCENTRAL <>
    ze          ZIPENDCENTRAL <>
    option_x    int_t ?
    option_r    int_t ?
    option_v    int_t ?
    DSIZE       equ ($ - path)

.code


InitPath proc uses rsi rdi name:string_t

   .new p:string_t

    ldr rsi,name

    mov file,rsi
    mov rdi,path

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

            add strlen(rax),path
            mov rdi,rax
ifdef __UNIX__
ifdef _WIN64
            mov rsi,file
endif
            .if ( [rdi-1] == '/' )
else
            .if ( [rdi-1] == '/' || [rdi-1] == '\' )
endif
                dec rdi
            .endif
        .endif

        mov rax,path
        lea rcx,[rax+MAXPATH-1]
        mov [rdi],PC
        mov base,&[rdi+1]

        .while ( [rsi] )

            mov ax,word ptr [rsi+1]
            .if ( [rsi] == '.' && al == '.' && ( !ah || ah == '\' || ah == '/' ) )

                .repeat
                    dec rdi
                    mov al,[rdi]
                .until ( al == '\' || al == '/' || rdi < path )

                .if ( rdi < path )

                    _set_errno( EACCES )
                    xor eax,eax
                   .break( 1 )
                .endif

                add rsi,2
                .if ( [rsi] )
                    inc rsi
                .endif
                mov base,&[rdi+1]

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
        mov rax,path
    .until 1

    .if ( rax == NULL )

        perror(file)
        xor eax,eax
    .else
        mov eax,1
    .endif
    assume rsi:nothing
    assume rdi:nothing
    ret

InitPath endp


Compress proc uses rsi rdi rbx ff:ptr _finddata_t

   .new rc:int_t
   .new fn[_MAX_PATH]:char_t

    ldr rdx,ff

    ; collect base and convert to unix

    .for ( eax = 1, rdi = &fn, rsi = base, rcx = rdi : eax : )

        lodsb
        .if ( al == '\' || al == '/' )
            mov al,'/'
            lea rcx,[rdi+1] ; start of file name
        .endif
        stosb
    .endf

    ; set ff.name to file in path and unix name

    .for ( eax = 1, rdi = rcx, rsi = &[rdx]._finddata_t.name, rcx = file : eax : rcx++ )

        lodsb
        stosb
        mov [rcx],al
    .endf

    ; file name length

    lea rax,fn
    sub rdi,rax
    dec di
    mov zl.fnsize,di
    mov zc.fnsize,di

    ; file attrib

ifdef __UNIX__
    xor eax,eax
else
    mov eax,[rdx]._finddata_t.attrib
    and eax,_A_RDONLY or _A_HIDDEN or _A_SYSTEM or _A_ARCH
endif
    mov zc.ext_attrib,eax

    ; last mod file time

    .ifd gmtime( &[rdx]._finddata_t.time_write )

        mov     rcx,rax
        mov     eax,[rcx].tm.tm_year
        sub     eax,DT_BASEYEAR - 1900
        shl     eax,9
        mov     edx,[rcx].tm.tm_mon
        inc     edx
        shl     edx,5
        or      eax,edx
        or      eax,[rcx].tm.tm_mday
        mov     zl.date,ax
        mov     zc.date,ax
        mov     eax,[rcx].tm.tm_sec
        shr     eax,1
        mov     edx,eax ; second/2
        mov     al,byte ptr [rcx].tm.tm_hour
        mov     ecx,[rcx].tm.tm_min
        shl     ecx,5
        shl     eax,11
        or      eax,ecx
        or      eax,edx
        mov     zl.time,ax
        mov     zc.time,ax
    .else
        mov     zl.time,ax
        mov     zc.time,ax
        mov     zl.date,ax
        mov     zc.date,ax
    .endif

    mov rc,-1

    .repeat

        ; offset of local header

        mov rbx,fpz
        mov rax,[rbx].FILE._ptr
        sub rax,[rbx].FILE._base
        .if ( eax > MAXHEAP )

            add offs,rax
            _fsetmode(rbx, 0)
            .break .ifd fflush(rbx)
            _fsetmode(rbx, _IOMEMBUF)
            xor eax,eax
        .endif
        add rax,offs
        mov zc.off_local,eax

        ; write local header

        .break .ifd ( fwrite(&zl, 1, ZIPLOCAL, rbx) != ZIPLOCAL )
        fwrite(&fn, 1, zl.fnsize, rbx)
        .break .if ( ax != zl.fnsize )

        ; compress

        .break .ifd ( deflate(path, rbx, &zl) == 0 )

        ; update local and central file header

        mov ecx,zc.off_local
        sub rcx,offs
        add rcx,[rbx].FILE._base

        mov zc.crc,zl.crc
        mov [rcx].ZIPLOCAL.crc,eax
        mov zc.csize,zl.csize
        mov [rcx].ZIPLOCAL.csize,eax
        mov zc.fsize,zl.fsize
        mov [rcx].ZIPLOCAL.fsize,eax
        mov zc.method,zl.method
        mov [rcx].ZIPLOCAL.method,ax

        ; write central file header

        .break .ifd ( fwrite(&zc, 1, ZIPCENTRAL, fpc) != ZIPCENTRAL )
        fwrite(&fn, 1, zl.fnsize, fpc)
        .break .if ( ax != zl.fnsize )

        inc ze.entry_dir
        mov rc,0
        .if ( option_v )
            printf(" %s\n", &fn)
        .endif
    .until 1
    mov eax,rc
    ret

Compress endp


ScanFiles proc

   .new fh:intptr_t
   .new np:string_t
   .new ff:_finddata_t
   .new rc:int_t = 0

    .ifd ( _findfirst( path, &ff) != -1 )

        mov fh,rax
        .repeat
            .if !( ff.attrib & _F_SUBDIR )

                .ifd Compress(&ff)

                    mov rc,eax
                   .break
                .endif
            .endif
        .until _findnext(fh, &ff)
        _findclose(fh)
    .endif

    .if ( option_r )

        strcpy(file, "*.*")
        .ifd ( _findfirst( path, &ff) != -1 )

            mov fh,rax
            .repeat

                mov eax,dword ptr ff.name
                and eax,0x00FFFFFF

                .if ( ax != '.' && eax != '..' && ff.attrib & _F_SUBDIR )

                    mov np,file
                    mov file,strfn(strfcat(file, &ff.name, mask))
                    .ifd ScanFiles()
                        mov rc,eax
                       .break
                    .endif
                    mov file,np
                .endif
            .until _findnext(fh, &ff)
            _findclose(fh)
        .endif
    .endif
    .return( rc )

ScanFiles endp


AddFile proc name:string_t

    .ifd ( InitPath( ldr(name) ) == 0 )

        dec rax
       .return
    .endif
    mov file,strfn(path)
    .if !strpbrk(path, "*?")
        lea rax,@CStr("*.*")
    .else
        mov rax,file
    .endif
    strcpy(mask, rax)
    ScanFiles()
    ret

AddFile endp


Decompress proc uses rbx

   .new rc:int_t = 0

    mov rcx,outp
    .if ( rcx == NULL )
        lea rcx,@CStr("")
    .endif
    .ifd ( InitPath( rcx ) == 0 )

        dec rax
       .return
    .endif
    mov rbx,base
    .if ( byte ptr [rbx] )

        _mkdir(path)
        .while strchr(rbx, PC)

            lea rbx,[rax+1]
            _mkdir(path)
        .endw
        add rbx,strlen(rbx)
        mov byte ptr [rbx],PC
        inc rbx
        mov base,rbx
    .else
        mov byte ptr [rbx-1],PC
    .endif

    .while ( rc == 0 )

        .ifd ( fread(&zl, 1, ZIPLOCAL, fpz) != ZIPLOCAL )

            mov rc,ER_ZIP
           .break
        .endif
        .break .if ( zl.Signature != ZIPLOCALID )

        movzx ebx,zl.fnsize
        .ifd ( fread(base, 1, ebx, fpz) != ebx )

            mov rc,ER_ZIP
           .break
        .endif
        .for ( : zl.extsize : zl.extsize-- )

            .ifsd ( fgetc(fpz) == -1 )

                mov rc,ER_ZIP
               .break( 1 )
            .endif
        .endf

        mov rcx,base
        .continue .if ( byte ptr [rcx+rbx-1] == '/' )

        mov byte ptr [rcx+rbx],0
        mov rbx,rcx
        .while strchr(rbx, '/')

            mov rbx,rax
            mov byte ptr [rbx],0
            _mkdir(path)
            mov byte ptr [rbx],PC
            inc rbx
        .endw

        .switch zl.method
        .case METHOD_STORE
        .case METHOD_DEFLATE
        .case METHOD_DEFLATE64
            mov rc,inflate(path, fpz, &zl)
           .endc
        .case METHOD_IMPLODE
            mov rc,explode(path, fpz, &zl)
           .endc
        .default
            mov rc,_set_errno( ENOSYS )
        .endsw
    .endw

    .if ( rc || zl.Signature != ZIPCENTRALID )

        perror(arch)
       .return( rc )
    .endif

ifndef __UNIX__

    memcpy(&zc, &zl, ZIPLOCAL)
    add rax,ZIPLOCAL
    .ifd ( fread(rax, 1, ZIPCENTRAL-ZIPLOCAL, fpz) != ZIPCENTRAL-ZIPLOCAL )

        .return( ER_ZIP )
    .endif

    .while 1

        movzx ebx,zc.fnsize
        .ifd ( fread(base, 1, ebx, fpz) != ebx )

            mov rc,ER_ZIP
           .break
        .endif
        mov rcx,base
        mov byte ptr [rcx+rbx],0
        mov rbx,rcx

        .while strchr(rbx, '/')

            mov byte ptr [rax],'\'
            lea rbx,[rax+1]
        .endw

        .ifsd ( _sopen( path, O_RDWR or O_BINARY, SH_DENYNO, 0 ) > 0 )

            mov ebx,eax
            mov ax,zc.date
            shl eax,16
            mov ax,zc.time
            setftime(ebx, eax)
            _close(ebx)

            setfattr(path, zc.ext_attrib)
        .endif

        .ifd ( fread(&zc, 1, ZIPCENTRAL, fpz) != ZIPCENTRAL )

            mov rc,ER_ZIP
           .break
        .endif
        .break .if ( zc.Signature != ZIPCENTRALID )
    .endw
endif
    mov eax,rc
    ret

Decompress endp


Open proc name:string_t

    ldr rcx,name

    mov arch,rcx
    lea rdx,@CStr("rb")
    .if ( option_x == 0 )
        lea rdx,@CStr("wb")
    .endif
    .if ( fopen(rcx, rdx) == NULL )

        dec rax
       .return
    .endif
    mov fpz,rax
    .if ( option_x == 0 )

        _fsetmode(rax, _IOMEMBUF)
        mov fpc,_fopenm(rax)
        mov zl.Signature,ZIPLOCALID
        mov zc.Signature,ZIPCENTRALID
        mov ze.Signature,ZIPENDCENTRALID
        mov zl.version,20
        mov zc.version_made,20
        mov zc.version_need,10
        xor eax,eax
    .else
        Decompress()
    .endif
    ret

Open endp


Release proc

    mov rcx,fpz

    .if ( option_x )

        xor eax,eax
        .if ( rcx )

            fclose(rcx)
        .endif
        .return
    .endif

    mov rdx,fpc
    .if ( !rcx || !rdx || !ze.entry_dir )

        .if ( rcx )

            fclose(rcx)
            remove(arch)
        .endif
        perror(arch)
        .if ( fpc )

            fclose(fpc)
        .endif

    .else

        mov rax,[rcx].FILE._ptr
        sub rax,[rcx].FILE._base
        add rax,offs
        mov ze.off_cent,eax

        mov rax,[rdx].FILE._ptr
        sub rax,[rdx].FILE._base
        mov ze.size_cent,eax
        fwrite(&ze, 1, ZIPENDCENTRAL, fpc)

        _fsetmode(fpz, 0)
        _fsetmode(fpc, 0)
        fflush(fpz)
        fflush(fpc)
        fclose(fpz)
        fclose(fpc)
        xor eax,eax
    .endif
    ret

Release endp


%define BUILD_DATE <"&@Date">

Usage proc

    printf(
        "DZIP Version %d.%02d " BUILD_DATE "Copyright (c) The Asmc Contributors\n"
        "\n"
        "Usage: dzip [<options>] <archive> [<file(s)>]\n"
        "\n"
        "-0..9      Compress level (default is 9)\n"
        "-r         Recurse subdirectories\n"
        "-x         Extract files with full paths\n"
        "-o<path>   Set Output directory\n"
        "-v         Make some noise\n\n", __DZIP__ / 100, __DZIP__ mod 100 )
    exit( 0 )
    ret

Usage endp


main proc argc:int_t, argv:array_t

   .new a:int_t = 0

    lea rdi,path
    mov ecx,DSIZE/4
    xor eax,eax
    rep stosd
    mov path,&pbuf
    mov mask,&mbuf

    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rdx,argv
        mov rcx,[rdx+rbx*size_t]
        mov eax,[rcx]

        .switch al
ifndef __UNIX__
        .case '/'
endif
        .case '-'
            shr eax,8
            .switch al
            .case '0'..'9'
                sub al,'0'
                movzx eax,al
                mov compresslevel,eax
               .continue
            .case 'x'
                inc option_x
               .continue
            .case 'r'
                inc option_r
               .continue
            .case 'v'
                inc option_v
               .continue
            .case 'o'
                .if ( ah )
                    lea rax,[rcx+2]
                .else
                    inc ebx
                    mov rax,[rdx+rbx*size_t]
                .endif
                mov outp,rax
               .continue
            .endsw
        .case 'h'
ifndef __UNIX__
        .case '?'
endif
            Usage()
        .default
            .if ( a == 0 )
                Open(rcx)
                inc a
            .elseif ( option_x == 0 )
                AddFile(rcx)
            .endif
            .break .if eax
        .endsw
    .endf
    .if ( a == 0 )
        Usage()
    .endif
    Release()
    ret

main endp

    end
