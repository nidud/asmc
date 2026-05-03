include io.inc
include fcntl.inc
include direct.inc
include stdio.inc
include string.inc
ifndef __UNIX__
include winbase.inc
endif
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

compare proc a:ptr, b:ptr

    ldr rcx,a
    ldr rdx,b

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

    assume rbx:ptr token

tally proc uses rbx string:string_t

    .new i:int_t
    .new p:string_t

    ldr rcx,string

    .if strtok(rcx, "\n\r\t ,!&")

        .while 1

            .for ( p = rax, rbx = &table, i = 0 : i < TOKENCOUNT : i++, rbx += sizeof(token) )

                .if !_stricmp([rbx].tname, p)

                    inc [rbx].count
                   .break
                .endif
            .endf
            .break .if !strtok(NULL, "\n\r\t ,!&")
        .endw
    .endif
    ret

tally endp

scanfiles proc uses rdi rbx directory:string_t, fmask:string_t

  local path[_MAX_PATH]:sbyte, ff:_finddata_t, fd:int_t

    .ifd _findfirst(strfcat(&path, directory, fmask), &ff) != -1

        mov rbx,rax
        .repeat

            .if !( ff.attrib & _F_SUBDIR )

                .ifd _open(strfcat(&path, directory, &ff.name), O_RDONLY or O_BINARY, NULL) != -1

                    mov fd,eax
                    inc line_count

                    .while _read(fd, &buffer, BUFSIZE)

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
                    _close(fd)
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

  local path[_MAX_PATH]:sbyte, fmask[_MAX_PATH]:sbyte, p:string_t, i:int_t

    .if ( argc == 1 )

        .return( print_usage() )
    .endif
    dec argc
    mov rbx,argv
    .repeat

        dec argc
        add rbx,string_t
        mov rcx,[rbx]
        mov eax,[rcx]

        .switch al
ifndef __UNIX__
        .case '/'
endif
        .case '-'
            shr eax,8
            or  eax,202020h
            .if ( al == 'r' )
                inc do_subdir
               .endc
            .endif
ifndef __UNIX__
        .case '?'
endif
        .case 'h'
            .return( print_usage() )
        .default
            strcpy(&path, rcx)
            mov p,strfn(rax)
            strcpy(&fmask, rax)
            lea rcx,path
            mov rdx,p
ifdef __UNIX__
            .if ( rdx > rcx && byte ptr [rdx-1] == '/' )
else
            .if ( rdx > rcx && byte ptr [rdx-1] == '\' )
endif
                mov byte ptr [rdx-1],0
            .else
                mov byte ptr [rdx],0
            .endif
        .endsw
    .until !argc

    lea rbx,path
    .if ( fmask == 0 )

        perror("Nothing to do..")
       .return( 0 )
    .endif
    .if ( path == 0 )

        strcpy(rbx, ".")
    .endif
ifndef __UNIX__
    GetFullPathName(rbx, _MAX_PATH, rbx, 0)
endif
    printf("\nFile(s):   %s\nDirectory: %s\n\n", &fmask, rbx)
    scanfiles(rbx, &fmask)
    printf("Total %d file(s), %d line(s)\n\n", file_count, line_count)
    lea rbx,table
    qsort(rbx, TOKENCOUNT, sizeof(token), &compare)
    .for ( i = 0 : i < TOKENCOUNT && [rbx].count : i++, rbx += sizeof(token) )
        printf("%6d %s\n", [rbx].count, [rbx].tname)
    .endf
    .return( 0 )

main endp

    end _tstart
