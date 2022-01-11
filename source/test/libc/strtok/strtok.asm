include io.inc
include fcntl.inc
include direct.inc
include stdio.inc
include string.inc
include winbase.inc
include stdlib.inc
include tchar.inc

BUFSIZE     equ 4096    ; Size of read buffer

token       struct
count       int_t ?
tname       string_t ?
token       ends

.data

buffer      char_t BUFSIZE+4 dup(0)
file_count  int_t 0
line_count  int_t 0
do_subdir   int_t 0

P macro id
  local a
    .const
    a db "&id&",0
    .data
    exitm<a>
    endm

res macro tok, string, type, value, bytval, flags, cpu, sflags
    token <0, P(string)>
    endm
insa macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    token <0, P(string)>
    endm
insx macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs
    token <0, P(string)>
    endm
insv macro tok, string, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex, flgs, rex
    token <0, P(string)>
    endm
insn macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
insm macro tok, suffix, opcls, byte1_info, op_dir, rm_info, opcode, rm_byte, cpu, prefix, evex
    endm
avxins macro op, tok, string, cpu, flgs
    token <0, P(string)>
    endm
OpCls macro op1, op2, op3
    exitm<0>
    endm


table label token
include ../../../asmc/inc/directve.inc
include ../../../asmc/inc/instruct.inc

TOKENCOUNT equ ($ - table) / sizeof(token)

.code

print_usage proc

    printf(
        "USAGE: strtok [-option] [file]\n"
        "\n"
        " -r Recurse subdirectories\n"
        "\n"
    )
    xor eax,eax
    ret

print_usage endp


; get filename part of path

strfn proc path:string_t

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

; add file to path

strfcat proc b:string_t, path:string_t, file:string_t

    strcat(strcat(strcpy(rcx, rdx), "\\"), file)
    ret

strfcat endp

compare proc a:ptr, b:ptr

    xor eax,eax

    mov ecx,[rcx]
    mov edx,[rdx]

    .if edx > ecx

        inc eax

    .elseif !ZERO?

        dec eax
    .endif
    ret

compare endp

    assume rsi:ptr token

tally proc uses rsi rdi rbx string:string_t

    .if strtok(rcx, "\n\r\t ,!&")

        .while 1

            .for ( rdi = rax,
                   rsi = &table,
                   ebx = 0 : ebx < TOKENCOUNT : ebx++, rsi += sizeof(token) )

                .if !_stricmp([rsi].tname, rdi)

                    inc [rsi].count
                    .break
                .endif
            .endf
            .break .if !strtok(NULL, "\n\r\t ,!&")
        .endw
    .endif
    ret

tally endp

scanfiles proc uses rsi rdi rbx directory:string_t, fmask:string_t

  local path[_MAX_PATH]:sbyte, ff:_finddata_t

    .ifd _findfirst(strfcat(&path, directory, fmask), &ff) != -1

        mov rsi,rax

        .repeat

            .if !( ff.attrib & _A_SUBDIR )

                .ifd _open(
                        strfcat(&path, directory, &ff.name),
                        O_RDONLY or O_BINARY, NULL) != -1

                    mov ebx,eax
                    inc line_count

                    .while _read(ebx, &buffer, BUFSIZE)

                        lea rdi,buffer
                        mov ecx,eax
                        mov eax,10
                        mov byte ptr [rdi+rcx],0

                        .while 1

                            repnz scasb
                            .break .ifnz

                            inc line_count
                        .endw

                        tally(&buffer)
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

            .switch al

              .case '?'

                print_usage()
                .break(1)

              .case '/'
              .case '-'

                shr eax,8
                or  eax,202020h

                .if al == 'r'

                    inc do_subdir
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

            xor eax,eax
            .break

        .endif

        .if byte ptr [rsi] == 0

            strcpy(rsi, ".")
        .endif

        GetFullPathName(rsi, _MAX_PATH, rsi, 0)
        printf("\nFile(s):   %s\nDirectory: %s\n\n", rdi, rsi)

        scanfiles(rsi, rdi)
        printf("Total %d file(s), %d line(s)\n\n", file_count, line_count)

        lea rsi,table
        qsort(rsi, TOKENCOUNT, sizeof(token), &compare)
        .for ( ebx = 0 : ebx < TOKENCOUNT && [rsi].count : ebx++, rsi += sizeof(token) )

            printf("%6d %s\n", [rsi].count, [rsi].tname)
        .endf
        xor eax,eax
    .until 1
    ret

main endp

    end _tstart
