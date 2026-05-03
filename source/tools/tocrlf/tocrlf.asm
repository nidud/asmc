
; LF to CR/LF -- for files copied from Linux to Windows

include io.inc
include direct.inc
include stdio.inc
include stdlib.inc
include string.inc
include tchar.inc

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
        "Usage: tocrlf [-r] [file(s)]\n"
        "\n"
        "-r Recurse subdirectories\n"
        )
   .return(0)
print_usage endp


scanfile proc uses rbx name:string_t

  .new fp:LPFILE = fopen(name, "rb")
  .new fo:LPFILE
  .new rc:int_t
  .new bin:int_t = 0
  .new cr:int_t = 0
  .new lf:int_t = 0

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

    .whiled ( fgetc(fp) != -1 )

        .if ( eax < 9 )

            inc bin
           .break

        .elseif ( eax == 10 && cr != 13 )

            .ifd ( fputc(13, fo) == -1 )

                inc bin
               .break
            .endif
            inc lf
            mov eax,10
        .endif

        mov cr,eax
        .ifd ( fputc(eax, fo) == -1 )

            inc bin
           .break
        .endif
    .endw

    fclose(fp)
    fclose(fo)
    .if ( bin || lf == 0 )

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
            .if ah == 'r'
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
