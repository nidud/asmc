; ASMC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdlib.inc
include signal.inc
ifdef __UNIX__
include direct.inc
else
include winbase.inc
endif
include asmc.inc
include memalloc.inc
include symbols.inc
include input.inc

init_options proto fastcall

.data
ifdef __UNIX__
_pgmptr string_t 0
endif
environ array_t 0

.code

ifdef __UNIX__

cmpwarg proc wild:string_t, path:string_t

    xor eax,eax
    .while 1

        lodsb
        mov ah,[rdi]
        inc rdi

        .if ah == '*'

            .while 1
                mov ah,[rdi]
                .if !ah
                    mov eax,1
                    .break(1)
                .endif
                inc rdi
                .continue .if ah != '.'
                xor edx,edx
                .while al
                    .if al == ah
                        mov rdx,rsi
                    .endif
                    lodsb
                .endw
                mov rsi,rdx
                .continue(1) .if rdx
                mov ah,[rdi]
                inc rdi
                .continue .if ah == '*'
                test eax,eax
                mov  ah,0
                setz al
                .break(1)
            .endw

        .endif

        mov edx,eax
        xor eax,eax
        .if !dl
            .break .if edx
            inc eax
            .break
        .endif
        .break .if !dh
        .continue .if dh == '?'
        .if dh == '.'
            .continue .if dl == '.'
            .break
        .endif
        .break .if dl == '.'
        or edx,0x2020
        .break .if dl != dh
    .endw
    ret

cmpwarg endp

.template SourceFile
    next ptr SourceFile ?
    file char_t 1 dup(?)
   .ends

ReadFiles proc uses rbx r12 r13 r14 r15 directory:string_t, wild:string_t, files:ptr SourceFile

   .new cnt:int_t = 0
   .new dir:ptr DIR

    mov r12,directory
    mov r13,wild
    mov r15,files

    .if ( byte ptr [r12] == 0 )
        mov word ptr [r12],'.'
    .endif
    lea r14,[r12+tstrlen(r12)]

    .if opendir(r12) != NULL

        mov dir,rax
        .while ( readdir(dir) )

            mov rbx,rax
            .if ( [rbx].dirent.d_type != DT_DIR )

                .if ( cmpwarg(r13, &[rbx].dirent.d_name) )

                    mov word ptr [r14],'/'
                    tstrcat(r14, &[rbx].dirent.d_name)

                    add tstrlen(r12),SourceFile
                    .if MemAlloc( eax )
                        mov [r15].SourceFile.next,rax
                        mov r15,rax
                        mov [r15].SourceFile.next,NULL
                        tstrcpy(&[r15].SourceFile.file, r12)
                        inc cnt
                    .endif
                    mov byte ptr [r14],0
                .endif

            .elseif ( Options.process_subdir )

                mov eax,dword ptr [rbx].dirent.d_name
                and eax,0x00FFFFFF

                .if ( ax != '.' && eax != '..' )

                    mov word ptr [r14],'/'
                    tstrcat(r14, &[rbx].dirent.d_name)
                    ReadFiles(r12, r13, r15)
                    add cnt,eax
                    mov byte ptr [r14],0
                    .while ( [r15].SourceFile.next )
                        mov r15,[r15].SourceFile.next
                    .endw
                .endif
            .endif
        .endw
        closedir(dir)
    .endif
    .return( cnt )

ReadFiles endp

AssembleSubdir proc uses rbx directory:string_t, wild:string_t

    .new rc:int_t = 0
    .new files:SourceFile = {0}
    .new cnt:int_t = ReadFiles(directory, wild, &files)

    .for ( rbx = files.next : rbx : )

        .if AssembleModule(&[rbx].SourceFile.file)
            mov rc,eax
        .endif
        mov rcx,rbx
        mov rbx,[rbx].SourceFile.next
        MemFree(rcx)
    .endf
    .return( rc )

AssembleSubdir endp

else

strfcat proc private buffer:string_t, path:string_t, file:string_t

    mov rax,rcx

    .if rdx
        .for ( : byte ptr [rdx] : r9b=[rdx], [rcx]=r9b, rdx++, rcx++ )

        .endf
    .else
        .for ( : byte ptr [rcx] : rcx++ )

        .endf
    .endif

    lea rdx,[rcx-1]
    .if rdx > rax

        mov dl,[rdx]

        .if !( dl == '\' || dl == '/' )

            mov dl,'\'
            mov [rcx],dl
            inc rcx
        .endif
    .endif

    .for ( dl=[r8] : dl : [rcx]=dl, r8++, rcx++, dl=[r8] )

    .endf
    mov [rcx],dl
    ret

strfcat endp

AssembleSubdir proc private uses rsi rdi rbx directory:string_t, wild:string_t

  local rc, path[_MAX_PATH]:byte, h:HANDLE, ff:WIN32_FIND_DATA

    lea rsi,path
    lea rdi,ff
    lea rbx,ff.cFileName
    mov rc,0

    .ifd FindFirstFile(strfcat(rsi, directory, wild), rdi) != -1
        mov h,rax
        .repeat
            .if !( byte ptr ff.dwFileAttributes & _A_SUBDIR )
                mov rc,AssembleModule(strfcat(rsi, directory, rbx))
            .endif
        .until !FindNextFile(h, rdi)
        FindClose(h)
    .endif

    .if Options.process_subdir
        .ifd FindFirstFile(strfcat(rsi, directory, "*.*"), rdi) != -1
            mov h,rax
            .repeat
                mov eax,[rbx]
                and eax,0x00FFFFFF
                .if ff.dwFileAttributes & _A_SUBDIR && ax != '.' && eax != '..'
                    .if AssembleSubdir(strfcat(rsi, directory, rbx), wild)
                        mov rc,eax
                    .endif
                .endif
                FindNextFile(h, rdi)
            .until !eax
            FindClose(h)
        .endif
    .endif
    .return( rc )

AssembleSubdir endp

endif


GeneralFailure proc private signo:int_t

    .if ( signo != SIGTERM )

ifndef __UNIX__

       .new flags[17]:sbyte

        mov rcx,pCurrentException
        mov r11,[rcx].EXCEPTION_POINTERS.ContextRecord
        mov r10,[rcx].EXCEPTION_POINTERS.ExceptionRecord

        .for ( r8d      = 0,
               rdx      = &flags,
               rax      = '00000000',
               [rdx]    = rax,
               [rdx+8]  = rax,
               [rdx+16] = r8b,
               eax      = [r11].CONTEXT.EFlags,
               ecx      = 16 : ecx : ecx-- )

            shr eax,1
            adc [rdx+rcx-1],r8b
        .endf

        mov rdx,[r11].CONTEXT._Rip
        mov rcx,[rdx]
        bswap rcx
        xor r8,r8
        .if ( r9 )
            mov r8,[r9]
            mov r9,[r8]
            bswap r9
        .endif

        tprintf(
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "\tException:   Segment violation\n"
            "\tCode: \t     %08X\n"
            "\tFlags:\t     %08X\n"
            "\tProcessor:\n"
            "\t\tRAX: %p R8:  %p\n"
            "\t\tRBX: %p R9:  %p\n"
            "\t\tRCX: %p R10: %p\n"
            "\t\tRDX: %p R11: %p\n"
            "\t\tRSI: %p R12: %p\n"
            "\t\tRDI: %p R13: %p\n"
            "\t\tRBP: %p R14: %p\n"
            "\t\tRSP: %p R15: %p\n"
            "\t\tRIP: %p *--: %p\n"
            "\t   Dispatch: %p *--: %p\n"
            "\t     EFlags: %s\n"
            "\t\t     r n oditsz a p c\n\n",
            [r10].EXCEPTION_RECORD.ExceptionCode,
            [r10].EXCEPTION_RECORD.ExceptionFlags,
            [r11].CONTEXT._Rax, [r11].CONTEXT._R8,
            [r11].CONTEXT._Rbx, [r11].CONTEXT._R9,
            [r11].CONTEXT._Rcx, [r11].CONTEXT._R10,
            [r11].CONTEXT._Rdx, [r11].CONTEXT._R11,
            [r11].CONTEXT._Rsi, [r11].CONTEXT._R12,
            [r11].CONTEXT._Rdi, [r11].CONTEXT._R13,
            [r11].CONTEXT._Rbp, [r11].CONTEXT._R14,
            [r11].CONTEXT._Rsp, [r11].CONTEXT._R15,
            rdx, rcx, r8, r9, &flags)

endif
        asmerr( 1901 )
    .endif
    close_files()
    exit(1)
    ret

GeneralFailure endp

ifdef __UNIX__
main proc _argc:int_t, _argv:array_t
   .new argc:int_t = _argc
   .new argv:array_t = _argv
    mov environ,rdx
else
main proc frame:ExceptionHandler argc:int_t, argv:array_t
    mov environ,r8
endif
  .new rc:int_t = 0
  .new numArgs:int_t = 0
  .new numFiles:int_t = 0
ifdef __UNIX__
  .new path[_MAX_PATH]:char_t
else
  .new ff:WIN32_FIND_DATA
endif
    MemInit()
ifndef DEBUG
    signal(SIGSEGV, &GeneralFailure)
endif
ifndef __UNIX__
    signal(SIGBREAK, &GeneralFailure)
else
    signal(SIGTERM, &GeneralFailure)
endif

    init_options()

    .if !tgetenv("ASMC")     ; v2.21 -- getenv() error..
        lea rax,@CStr("")
    .endif
    mov rcx,argv
ifdef __UNIX__
    mov rdx,[rcx]
    mov _pgmptr,rdx
endif
    mov [rcx],rax
    lea r15,_ltype

    .while ParseCmdline(argv, &numArgs)

        write_logo()

        inc numFiles
        mov r12,Options.names[ASM*8]
ifdef __UNIX__
        lea r13,path
else
        lea r13,ff.cFileName
        .if !Options.process_subdir
            .ifd FindFirstFile(r12, &ff) == -1
                asmerr(1000, r12)
                .break
            .endif
            FindClose(rax)
        .endif
endif
        .if !tstrchr(tstrcpy(r13, r12), '*')
            tstrchr(r13, '?')
        .endif
        .if rax
            .if GetFNamePart(r13) > r13
                dec rax
            .endif
            mov byte ptr [rax],0
            AssembleSubdir(r13, GetFNamePart(r12))
        .else
            AssembleModule(r13)
        .endif
        mov rc,eax
    .endw

    CmdlineFini()
    .if !numArgs
        write_usage()
    .elseif !numFiles
        asmerr(1017)
    .endif
    mov eax,1
    sub eax,rc
    ret

main endp

tgetenv proc fastcall uses rsi rdi rbx enval:string_t

    mov rbx,rcx
    .ifd tstrlen(rcx)

        mov edi,eax
        mov rsi,environ
        lodsq

        .while rax

            .ifd !tmemicmp(rax, rbx, edi)

                mov rax,[rsi-8]
                add rax,rdi

                .if ( byte ptr [rax] == '=' )

                    .return( &[rax+1] )
                .endif
            .endif
            lodsq
        .endw
    .endif
    ret

tgetenv endp

    end

