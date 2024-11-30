include io.inc
include direct.inc
include stdio.inc
include string.inc
include malloc.inc
ifndef __INIX__
include winbase.inc
endif
include tchar.inc

define BUFSIZE 4096 ; Size of line buffer

.data
file_count  dd 0
do_subdir   dd 0
print_line  dd 0

.code

print_usage proc

    printf(
        "Usage: brackets [-option] [file(s)]\n\n"
        "-l Print Line context\n"
        "-r Recurse subdirectories\n\n"
        )
   .return( 0 )

print_usage endp


scanfile proc uses rsi rdi rbx name:string_t

  .new fp:LPFILE = fopen(name, "r")
  .new buffer:string_t = alloca(BUFSIZE)
  .new line:long_t = 0

    .if ( fp == NULL )

        perror(name)
       .return( 0 )
    .endif

    .while fgets(buffer, BUFSIZE, fp)

        .while 1

            inc line
            .if strchr(buffer, ';')

                mov byte ptr [rax],0
            .endif

            lea rbx,[strlen(buffer)-1]
            add rbx,buffer

            .while ( rbx > buffer )

                movzx eax,byte ptr [rbx]
                .if ( al <= ' ' )

                    mov byte ptr [rbx],0
                    dec rbx
                .else
                    .break
                .endif
            .endw
            .break .if ( al != '\' )

            mov rdx,rbx
            sub rdx,buffer
            mov ecx,BUFSIZE
            sub ecx,edx

           .break .if !fgets(rbx, ecx, fp)
        .endw

        mov rsi,buffer
        xor edi,edi
        xor ebx,ebx
        lodsb

        .while al

            .if ( al == '(' )

                inc edi
                .if ( rbx == NULL )
                    lea rbx,[rsi-1]
                .endif

            .elseif ( al == ')' )

                dec edi
                .if ( rbx == NULL )
                    lea rbx,[rsi-1]
                .endif
            .endif
            lodsb
        .endw

        .if ( edi )
            .if ( print_line )
                printf("%s(%d)[%s]\n", name, line, rbx)
            .else
                printf("%s(%d)\n", name, line)
            .endif
        .endif
    .endw
    fclose(fp)
   .return( line )

scanfile endp


scanfiles proc uses rbx directory:string_t, fmask:string_t

    .new path[_MAX_PATH]:char_t
    .new ff:_finddata_t

    mov rcx,strfcat(&path, directory, fmask)
    .ifd _findfirst(rcx, &ff) != -1

        mov rbx,rax
        .repeat
            .if !( ff.attrib & _F_SUBDIR )

                scanfile(strfcat(&path, directory, &ff.name))
                inc file_count
            .endif
        .until _findnext(rbx, &ff)
        _findclose(rbx)
    .endif

    .if do_subdir

        mov rcx,strfcat(&path, directory, "*.*")
        .ifd ( _findfirst(rcx, &ff) != -1 )

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

   .new path[_MAX_PATH]:char_t = 0
   .new fmask[_MAX_PATH]:char_t = 0

    .if ( argc == 1 )

        .return print_usage()
    .endif

    mov rbx,argv
    dec argc

    .while ( argc )

        add rbx,string_t
        mov rcx,[rbx]
        mov eax,[rcx]

        .switch al
ifndef __UNIX__
        .case '?'
endif
        .case 'h'
            .return( print_usage() )

ifndef __UNIX__
        .case '/'
endif
        .case '-'

            shr eax,8
            .if ( al == 'r' )

                inc do_subdir
               .endc

            .elseif ( al == 'l' )

                inc print_line
               .endc
            .endif
            .gotosw('h')

        .default

            strcpy(&fmask, strfn(strcpy(&path, rcx)))
            strfn(&path)
            lea rcx,path
ifdef __UNIX__
            mov edx,'/'
else
            mov edx,'\'
endif
            .if ( rax > rcx && dl == [rax-1] )
                mov [rax-1],dh
            .else
                mov [rax],dh
            .endif
        .endsw
        dec argc
    .endw

    .if ( fmask == 0 )

        perror("Nothing to do..")
       .return( 0 )
    .endif
    .if ( path == 0 )

        mov word ptr path,'.'
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
