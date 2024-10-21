
; LF to CR/LF -- for files copied from Linux to Windows

include io.inc
include direct.inc
include stdio.inc
include string.inc
ifndef __UNIX__
include winbase.inc
endif
include tchar.inc

define BUFSIZE 4096 ; Size of line buffer

.data
file_count  dd 0
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

  .new buffer[BUFSIZE]:sbyte
  .new fp:LPFILE = fopen(name, "rt")
  .new fo:LPFILE

    .if ( fp == NULL )

        perror(name)
       .return(0)
    .endif
    .if !fopen("convert.$$$", "wt")

        fclose(fp)
        perror("convert.$$$")
       .return(0)
    .endif
    mov fo,rax

    .while fgets(&buffer, BUFSIZE, fp)

        fputs(&buffer, fo)
    .endw
    fclose(fp)
    fclose(fo)
    remove(name)
    rename("convert.$$$", name)
   .return(1)

scanfile endp


scanfiles proc uses rbx directory:string_t, fmask:string_t

  local path[_MAX_PATH]:sbyte, ff:_finddata_t

    .ifd _findfirst(strfcat(&path, directory, fmask), &ff) != -1
        mov rbx,rax
        .repeat
            .if !( ff.attrib & _F_SUBDIR )
                .ifd ( scanfile(strfcat(&path, directory, &ff.name)) == 1 )
                    inc file_count
                .endif
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
            strcpy(&path, rbx)
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
        .endsw
    .endf

    .if ( fmask == 0 )

        perror("Nothing to do..")
       .return( 0 )
    .endif
    .if ( path == 0 )
        strcpy(&path, ".")
    .endif
ifndef __UNIX__
    GetFullPathName(&path, _MAX_PATH, &path, 0)
endif
    printf( "\nFile(s):   %s\nDirectory: %s\n\n", &fmask, &path)
    scanfiles(&path, &fmask)
    printf("Total %d file(s)\n", file_count)
   .return( 0 )

main endp

    end _tstart
