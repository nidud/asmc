include io.inc
include direct.inc
include stdio.inc
include string.inc
include winbase.inc
include tchar.inc

BUFSIZE equ 4096 ; Size of line buffer

.data
file_count  dd 0
do_subdir   dd 0
print_line  dd 0

.code

print_usage proc
    .return printf(
        "Usage: brackets [-option] [file(s)]\n\n"
        "/l Print Line context\n"
        "/r Recurse subdirectories\n\n"
        )
print_usage endp

strfcat proc b:string_t, path:string_t, file:string_t
    .return strcat(strcat(strcpy(rcx, rdx), "\\"), file)
strfcat endp

strfn proc path:string_t
    mov rax,rcx
    .while byte ptr [rcx]
        .if byte ptr [rcx] == '\' && byte ptr [rcx+1]
            lea rax,[rcx+1]
        .endif
        inc rcx
    .endw
    ret
strfn endp

scanfile proc uses rsi rdi rbx name:string_t

  .new buffer[BUFSIZE]:sbyte
  .new fp:LPFILE = fopen(name, "rt")
  .new line:long_t = 0

    .if ( fp == NULL )
        perror(name)
        .return 0
    .endif

    .while fgets(&buffer, BUFSIZE, fp)

        lea rsi,buffer
        .while 1
            inc line
            .if strchr(rsi, ';')
                mov byte ptr [rax],0
            .endif
            lea rbx,[rsi+strlen(rsi)-1]
            .while rbx > rsi
                movzx eax,byte ptr [rbx]
                .if ( al <= ' ' )
                    mov byte ptr [rbx],0
                    dec rbx
                .else
                    .break
                .endif
            .endw
            .break .if al != '\'
            mov rcx,rbx
            sub rcx,rsi
            mov edx,BUFSIZE
            sub edx,ecx
            .break .if !fgets(rbx, edx, fp)
        .endw
        xor edi,edi
        xor ebx,ebx
        lodsb
        .while al
            .if al == '('
                inc edi
                .if ( rbx == NULL )
                    lea rbx,[rsi-1]
                .endif
            .elseif al == ')'
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
    .return line

scanfile endp

scanfiles proc uses rsi rdi rbx directory:string_t, fmask:string_t

  local path[_MAX_PATH]:sbyte, ff:_finddata_t

    .ifd _findfirst(strfcat(&path, directory, fmask), &ff) != -1
        mov rsi,rax
        .repeat
            .if !( ff.attrib & _A_SUBDIR )
                scanfile(strfcat(&path, directory, &ff.name))
                inc file_count
            .endif
        .until _findnext(rsi, &ff)
        _findclose(rsi)
    .endif
    .if do_subdir
        .ifd _findfirst(strfcat(&path, directory, "*.*"), &ff) != -1
            mov rsi,rax
            .repeat
                .if word ptr ff.name == '.'
                    .break .if _findnext(rsi, &ff)
                .endif
                .if word ptr ff.name == '..' && ff.name[2] == 0
                    .break .if _findnext(rsi, &ff)
                .endif
                .repeat
                    .if ff.attrib & _A_SUBDIR
                        scanfiles(strfcat(&path, directory, &ff.name), fmask)
                    .endif
                .until _findnext(rsi, &ff)
            .until 1
            _findclose(rsi)
        .endif
    .endif
    ret

scanfiles endp

main proc argc:int_t, argv:array_t

  local path[_MAX_PATH]:sbyte, fmask[_MAX_PATH]:sbyte

    mov edi,ecx
    mov rsi,rdx
    .if edi == 1
        print_usage()
        .return 0
    .endif
    dec edi
    lodsq
    .repeat
        lodsq
        mov rbx,rax
        mov eax,[rbx]
        .switch al
        .case '?'
            print_usage()
            .return 0
        .case '/'
        .case '-'
            shr eax,8
            or  eax,202020h
            .if al == 'r'
                inc do_subdir
                .endc
            .elseif al == 'l'
                inc print_line
                .endc
            .endif
            .gotosw('?')
        .default
            strcpy(&path, rbx)
            mov rbx,strfn(rax)
            strcpy(&fmask, rax)
            lea rcx,path
            .if rbx > rcx  && byte ptr [rbx-1] == '\'
                mov byte ptr [rbx-1],0
            .else
                mov byte ptr [rbx],0
            .endif
        .endsw
        dec edi
    .until !edi

    lea rdi,fmask
    lea rsi,path
    .if byte ptr [rdi] == 0
        perror("Nothing to do..")
        .return 0
    .endif
    .if byte ptr [rsi] == 0
        strcpy(rsi, ".")
    .endif
    GetFullPathName(rsi, _MAX_PATH, rsi, 0)
    printf( "\nFile(s):   %s\nDirectory: %s\n\n", rdi, rsi)
    scanfiles(rsi, rdi)
    printf("Total %d file(s)\n", file_count)
    .return 0

main endp

    end _tstart
