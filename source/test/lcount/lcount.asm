include io.inc
include fcntl.inc
include direct.inc
include stdio.inc
include string.inc
include winbase.inc
include tchar.inc
include strlib.inc

BUFSIZE     equ 4096

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
        "/r Process subfolders\n\n"
    )
    xor eax,eax
    ret
print_usage endp

ifdef __PE__
;
; get filename part of path
;
strfn proc uses edi path:LPSTR
    mov edi,path
    lea eax,[edi+strlen(edi)-1]
    .while 1
        .break .if byte ptr [eax] == '\'
        .break .if byte ptr [eax] == '/'
        dec eax
        .if eax <= edi
            lea eax,[edi-1]
            .break
        .endif
    .endw
    inc eax
    ret
strfn endp
;
; add file to path
;
strfcat proc b:LPSTR, path:LPSTR, file:LPSTR

    strcat(strcat(strcpy(b, path), "\\"), file)
    ret

strfcat endp

endif

    assume ebx:ptr _finddata_t

scanfiles proc uses esi edi ebx directory:LPSTR, fmask:LPSTR
local path[_MAX_PATH]:sbyte, ff:_finddata_t, handle:SINT

    lea ebx,ff
    .if _findfirst(strfcat(&path, directory, fmask), ebx) != -1
        mov esi,eax
        .repeat
            .if [ebx]._name == '.' && [ebx]._name[1] == 0
                .break .if _findnext(esi, ebx)
            .endif
            .if [ebx]._name == '.' && [ebx]._name[2] == 0
                .break .if _findnext(esi, ebx)
            .endif
            .repeat
                .if !( [ebx].attrib & _A_SUBDIR )

                    .if _open(strfcat(&path, directory, &[ebx]._name), O_RDONLY or O_BINARY, NULL) != -1
                        mov handle,eax

                        .while _read(handle, &buffer, BUFSIZE)
                            lea edi,buffer
                            mov ecx,eax
                            mov eax,10
                            .repeat
                                inc line_count
                                repnz scasb
                            .untilnz
                        .endw

                        _close(handle)
                        inc file_count
                    .endif

                .endif
            .until _findnext(esi, ebx)
        .until 1
        _findclose(esi)
    .endif

    .if do_subdir
        .if _findfirst(strfcat(&path, directory, "*.*"), ebx) != -1
            mov esi,eax
            .repeat
                .if [ebx]._name == '.' && [ebx]._name[1] == 0
                    .break .if _findnext(esi, ebx)
                .endif
                .if [ebx]._name == '.' && [ebx]._name[2] == 0
                    .break .if _findnext(esi, ebx)
                .endif

                .repeat
                    .if [ebx].attrib & _A_SUBDIR

                        scanfiles(strfcat(&path, directory, &[ebx]._name), fmask)
                    .endif
                .until _findnext(esi, ebx)

            .until 1
            _findclose(esi)
        .endif
    .endif
    ret

scanfiles endp

main proc argc:SINT, argv:ptr
local path[_MAX_PATH]:sbyte
local fmask[_MAX_PATH]:sbyte

    mov edi,argc
    mov esi,argv

    .repeat
        .if edi == 1
            print_usage()
            .break
        .endif

        mov fmask,0
        dec edi
        lodsd
        .repeat
            lodsd
            mov ebx,eax
            mov eax,[ebx]
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
                strcpy(&path, ebx)
                push strfn(eax)
                strcpy(&fmask, eax)
                pop eax
                lea ecx,path
                .if eax > ecx && byte ptr [eax-1] == '\'
                    mov byte ptr [eax-1],0
                .else
                    mov byte ptr [eax],0
                .endif
            .endif
            dec edi
        .until !edi

        .if !fmask
            perror("Nothing to do..")
            xor eax,eax
            .break
        .endif

        .if !path
            strcpy(&path, ".")
        .endif
        GetFullPathName(&path, _MAX_PATH, &path, 0)

        printf("\nFile(s):   %s\n", &fmask)
        printf("Directory: %s\n\n", &path)
        scanfiles(&path, &fmask)
        printf("Total %d files\n", file_count)
        printf("Total %d lines\n", line_count)

        xor eax,eax
    .until 1
    ret

main endp

    end _tstart
