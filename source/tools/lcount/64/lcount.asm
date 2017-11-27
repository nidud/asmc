include io.inc
include fcntl.inc
include direct.inc
include stdio.inc
include string.inc
include winbase.inc
include tchar.inc
include strlib.inc

BUFSIZE     equ 4096    ; Size of read buffer

.data?
buffer      db BUFSIZE dup(?)

.data
file_count  dd 0
line_count  dd 0
do_subdir   dd 0

.code

print_usage proc
    printf(
        "USAGE: LCOUNT [-option] [file]\n\n"
        "/r Recurse subdirectories\n\n"
    )
    xor eax,eax
    ret
print_usage endp

ifdef __PE__
;
; get filename part of path
;
strfn proc path:LPSTR
    mov rax,rcx
    .while byte ptr [rax]
        inc rax
    .endw
    .if rax > rcx
        dec rax
    .endif
    .while 1
        .break .if byte ptr [rax] == '\'
        .break .if byte ptr [rax] == '/'
        dec rax
        .if rax <= rcx
            lea rax,[rcx-1]
            .break
        .endif
    .endw
    inc rax
    ret
strfn endp
;
; add file to path
;
strfcat proc b:LPSTR, path:LPSTR, file:LPSTR

    strcat(strcat(strcpy(rcx, rdx), "\\"), file)
    ret

strfcat endp

endif

scanfiles proc uses rsi rdi rbx directory:LPSTR, fmask:LPSTR
local path[_MAX_PATH]:sbyte
local ff:_finddata_t

    .ifd _findfirst(strfcat(&path, directory, fmask), &ff) != -1
        mov rsi,rax
        .repeat
            .if !( ff.attrib & _A_SUBDIR )
                .ifd _open(strfcat(&path, directory, &ff._name), O_RDONLY or O_BINARY, NULL) != -1
                    mov ebx,eax
                    inc line_count
                    .while _read(ebx, &buffer, BUFSIZE)
                        lea rdi,buffer
                        mov ecx,eax
                        mov eax,10
                        .while 1
                            repnz scasb
                            .break .ifnz
                            inc line_count
                        .endw
                    .endw
                    _close(ebx)
                    inc file_count
                .endif
            .endif
        .until _findnext(rsi, &ff)
        _findclose(rsi)
    .endif

    .if do_subdir
        .ifd _findfirst(strfcat(&path, directory, "*.*"), &ff) != -1
            mov rsi,rax
            .repeat
                .if word ptr ff._name == '.'
                    .break .if _findnext(rsi, &ff)
                .endif
                .if word ptr ff._name == '..' && ff._name[2] == 0
                    .break .if _findnext(rsi, &ff)
                .endif
                .repeat
                    .if ff.attrib & _A_SUBDIR
                        scanfiles(strfcat(&path, directory, &ff._name), fmask)
                    .endif
                .until _findnext(rsi, &ff)
            .until 1
            _findclose(rsi)
        .endif
    .endif
    ret

scanfiles endp

main proc argc:SINT, argv:ptr
local path[_MAX_PATH]:sbyte, fmask[_MAX_PATH]:sbyte

    mov edi,argc
    mov rsi,argv

    .repeat
        .if edi == 1
            print_usage()
            .break
        .endif
        dec edi
        lodsq
        .repeat
            lodsq
            mov rbx,rax
            mov eax,[rbx]
            .if al == '?'
                print_usage()
                .break(1)
            .endif
            .if al == '/' || al == '-'
                shr eax,8
                or  eax,202020h
                .if al == 'r'
                    inc do_subdir
                .else
                    print_usage()
                    .break(1)
                .endif
            .else
                strcpy(&path, rbx)
                mov rbx,strfn(rax)
                strcpy(&fmask, rax)
                lea rcx,path
                .if rbx > rcx  && byte ptr [rbx-1] == '\'
                    mov byte ptr [rbx-1],0
                .else
                    mov byte ptr [rbx],0
                .endif
            .endif
            dec edi
        .until !edi

        lea rdi,fmask
        lea rsi,path
        .if byte ptr [rdi] == 0
            perror("Nothing to do..")
            sub eax,eax
            .break
        .endif
        .if byte ptr [rsi] == 0
            strcpy(rsi, ".")
        .endif
        GetFullPathName(rsi, _MAX_PATH, rsi, 0)
        printf("\nFile(s):   %s\n", rdi)
        printf("Directory: %s\n\n", rsi)
        scanfiles(rsi, rdi)
        printf("Total %d file(s)\n", file_count)
        printf("Total %d line(s)\n", line_count)
        xor eax,eax
    .until 1
    ret

main endp

    end _tstart
