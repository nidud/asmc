
; CR/LF to LF -- for files copied from Windows to Linux

include io.inc
include direct.inc
include stdio.inc
include stdlib.inc
include string.inc
include tchar.inc

define BUFSIZE 4096 ; Size of buffer

.data
bin_count   dd 0
txt_count   dd 0
do_subdir   dd 0
print_line  dd 0

.code

include pe/_tcsfn.asm
include pe/_tcsfcat.asm

print_usage proc
    printf(
        "Usage: tounix [-r] [file(s)]\n"
        "\n"
        "-r Recurse subdirectories\n"
        )
   .return(0)
print_usage endp

scanfile proc uses rbx name:string_t

  .new buffer[BUFSIZE]:sbyte
  .new fp:LPFILE = fopen(name, "rb")
  .new fo:LPFILE
  .new rc:int_t
  .new bin:int_t = 0
  .new cr:int_t = 0

    .if ( fp == NULL )

        perror(name)
       .return(0)
    .endif
    .if !fopen("convert.$$$", "wb")

        fclose(fp)
        perror("convert.$$$")
       .return(0)
    .endif
    mov fo,rax

    .while fread(&buffer, 1, BUFSIZE-1, fp)

        mov rc,eax
        mov buffer[rax],0

        .for ( ebx = 0 : ebx < rc : ebx++ )

            .if ( buffer[rbx] < 9 )

                inc bin
               .break( 1 )

            .elseif ( buffer[rbx] == 13 )

                strcpy(&buffer[rbx], &buffer[rbx+1])
                dec rc
                inc cr
            .endif
        .endf
        fwrite(&buffer, 1, rc, fo)
    .endw

    fclose(fp)
    fclose(fo)
    .if ( bin || cr == 0 )

        inc bin_count
        remove("convert.$$$")
    .else
        inc txt_count
        remove(name)
        rename("convert.$$$", name)
    .endif
    ret

scanfile endp


scanfiles proc uses rbx directory:string_t, fmask:string_t

  local path[_MAX_PATH]:sbyte, ff:_finddata_t

    .ifd _findfirst(strfcat(&path, directory, fmask), &ff) != -1
        mov rbx,rax
        .repeat
            .if !( ff.attrib & _F_SUBDIR )
                scanfile(strfcat(&path, directory, &ff.name))
            .endif
        .until _findnext(rbx, &ff)
        _findclose(rbx)
    .endif

    .if do_subdir

        .ifd _findfirst(strfcat(&path, directory, "*.*"), &ff) != -1

            mov rbx,rax
            .repeat

                mov eax,dword ptr ff.name
                and eax,0x00FFFFFF
                .if ( ax != '.' && eax != '..' && ff.attrib & _F_SUBDIR )

                    scanfiles(strfcat(&path, directory, &ff.name), fmask)
                .endif
            .until _findnext(rbx, &ff)
            _findclose(rbx)
        .endif
    .endif
    ret

scanfiles endp


main proc argc:int_t, argv:array_t

    .new path[_MAX_PATH]:char_t
    .new fmask[_MAX_PATH]:char_t
    .new i:int_t

    .if ( argc == 1 )
        .return print_usage()
    .endif

    .for ( i = 1 : i < argc : i++ )

        mov ecx,i
        mov rdx,argv
        mov rbx,[rdx+rcx*size_t]
        mov eax,[rbx]

        .switch al
ifndef __UNIX__
        .case '/'
endif
        .case '-'
            shr eax,8
            or  eax,202020h
            .if al == 'r'
                inc do_subdir
               .endc
            .endif
ifndef __UNIX__
        .case '?'
endif
            .return print_usage()
        .default
            .if !_fullpath(&path, rbx, _MAX_PATH)

                perror(rbx)
               .endc
            .endif
            mov rbx,strfn(rax)
            strcpy(&fmask, rax)
            lea rcx,path
ifdef __UNIX__
            mov eax,'/'
else
            mov eax,'\'
endif
            .if ( rbx > rcx && [rbx-1] == al )
                mov [rbx-1],ah
            .else
                mov [rbx],ah
            .endif
            .endc .if ( fmask == 0 )
            printf( "%s\n", &fmask )
            scanfiles(&path, &fmask)
        .endsw
    .endf

    mov ecx,txt_count
    add ecx,bin_count
    printf("%d file(s) %d ignored\n", ecx, bin_count)
    xor eax,eax
    ret

main endp

    end _tstart
