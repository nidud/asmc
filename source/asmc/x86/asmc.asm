; ASMC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdlib.inc
include signal.inc
ifndef __UNIX__
include winbase.inc
endif
include asmc.inc
include symbols.inc
include input.inc

ifdef __UNIX__
ifdef __WATCOM__
extern _cstart_: byte
endif
.data
_pgmptr string_t 0
endif

.code

ifndef __UNIX__

strfcat proc private uses esi edi ecx edx buffer:string_t, path:string_t, file:string_t

    mov edx,buffer
    mov esi,path

    xor eax,eax
    lea ecx,[eax-1]

    .if esi
        mov edi,esi ; overwrite buffer
        repne scasb
        mov edi,edx
        not ecx
        rep movsb
    .else
        mov edi,edx ; length of buffer
        repne scasb
    .endif

    dec edi
    .if edi != edx  ; add slash if missing
        mov al,[edi-1]
        .if !( al == '\' || al == '/' )
            mov al,'\'
            stosb
        .endif
    .endif
    mov esi,file    ; add file name
    .repeat
        lodsb
        stosb
    .until !eax
    mov eax,edx
    ret

strfcat endp

AssembleSubdir proc private uses esi edi ebx directory:string_t, wild:string_t

  local rc, path[_MAX_PATH]:byte, h, ff:WIN32_FIND_DATA

    lea esi,path
    lea edi,ff
    lea ebx,ff.cFileName
    mov rc,0

    .if FindFirstFile(strfcat(esi, directory, wild), edi) != -1
        mov h,eax
        .repeat
            .if !(byte ptr ff.dwFileAttributes & _A_SUBDIR)
                mov rc,AssembleModule(strfcat(esi, directory, ebx))
            .endif
        .until !FindNextFile(h, edi)
        FindClose(h)
    .endif

    .if Options.process_subdir
        .if FindFirstFile(strfcat(esi, directory, "*.*"), edi) != -1
            mov h,eax
            .repeat
                mov eax,[ebx]
                and eax,00FFFFFFh
                .if ff.dwFileAttributes & _A_SUBDIR && ax != '.' && eax != '..'
                    .if AssembleSubdir(strfcat(esi, directory, ebx), wild)
                        mov rc,eax
                    .endif
                .endif
                FindNextFile(h, edi)
            .until !eax
            FindClose(h)
        .endif
    .endif
    mov eax,rc
    ret

AssembleSubdir endp

endif

GeneralFailure proc private signo:int_t

    .if ( signo != SIGTERM )

ifndef __UNIX__

        mov ecx,pCurrentException
        lea edx,@CStr(
            "\n"
            "CONTEXT:\n"
            "\tException Code: %08X\n"
            "\tException Flags %08X\n"
            "\n"
            "\t\tEAX: %08X EDX: %08X\n"
            "\t\tEBX: %08X ECX: %08X\n"
            "\t\tEIP: %08X ESI: %08X\n"
            "\t\tEBP: %08X EDI: %08X\n"
            "\t\tESP: %08X\n"
            "\n"
            "\tFlags:  0000000000000000\n"
            "\t        r n oditsz a p c\n"
            "\n"
            )

        mov eax,[ecx].EXCEPTION_POINTERS.ContextRecord
        assume eax:PCONTEXT

        mov eax,[eax].EFlags
        mov ecx,16
        .repeat
            shr eax,1
            adc byte ptr [edx+ecx+164],0
        .untilcxz

        mov ecx,pCurrentException
        mov eax,[ecx].EXCEPTION_POINTERS.ContextRecord
        mov ecx,[ecx].EXCEPTION_POINTERS.ExceptionRecord
        tprintf(
            edx,
            [ecx].EXCEPTION_RECORD.ExceptionCode,
            [ecx].EXCEPTION_RECORD.ExceptionFlags,
            [eax]._Eax,
            [eax]._Edx,
            [eax]._Ebx,
            [eax]._Ecx,
            [eax]._Eip,
            [eax]._Esi,
            [eax]._Ebp,
            [eax]._Edi,
            [eax]._Esp)
endif
        asmerr( 1901 )
    .endif
    close_files()
    exit(1)
    ret

GeneralFailure endp

main proc uses esi edi argc:int_t, argv:array_t

  .new rc:int_t = 0
  .new numArgs:int_t = 0
  .new numFiles:int_t = 0
ifndef __UNIX__
  .new ff:WIN32_FIND_DATA
endif

ifndef DEBUG
    signal(SIGSEGV, GeneralFailure)
endif
ifndef __UNIX__
    signal(SIGBREAK, GeneralFailure)
else
    signal(SIGTERM, GeneralFailure)
endif

ifdef ASMC64
    define_name( "_WIN64", "1" )
ifdef __UNIX__
    define_name( "__UNIX__", "1" )
    define_name( "_LINUX",   "2" )
endif
endif
    .if !getenv("ASMC")     ; v2.21 -- getenv() error..
        lea eax,@CStr("")
    .endif
    mov ecx,argv
ifdef __UNIX__
    mov edx,[ecx]
    mov _pgmptr,edx
endif
    mov [ecx],eax

    .while ParseCmdline(argv, &numArgs)

        write_logo()

        inc numFiles
        mov esi,Options.names[ASM*4]

ifdef __UNIX__
        AssembleModule(esi)
else
        lea edi,ff.cFileName
        .if !Options.process_subdir
            .if FindFirstFile(esi, &ff) == -1
                asmerr(1000, esi)
                .break
            .endif
            FindClose(eax)
        .endif

        .if !strchr(strcpy(edi, esi), '*')
            strchr(edi, '?')
        .endif
        .if eax
            .if GetFNamePart(edi) > edi
                dec eax
            .endif
            mov byte ptr [eax],0
            AssembleSubdir(edi, GetFNamePart(esi))
        .else
            AssembleModule(edi)
        .endif
endif
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

    end

