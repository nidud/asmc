; ASMC.ASM--
; Copyright (C) 2017 Asmc Developers

include io.inc
include stdlib.inc
include signal.inc
include winbase.inc
include asmc.inc

CATCHBREAK      equ 1

AssembleModule  proto :dword
close_files     proto
CmdlineFini     proto
ParseCmdline    proto :ptr, :ptr
write_usage     proto
ifdef __ASMC64__
define_name     proto :string_t, :string_t
endif
.code

strfcat proc uses esi edi ecx edx buffer:string_t, path:string_t, file:string_t

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
    .if edi != edx      ; add slash if missing
        mov al,[edi-1]
        .if !( al == '\' || al == '/' )
            mov al,'\'
            stosb
        .endif
    .endif

    mov esi,file        ; add file name
    .repeat
        lodsb
        stosb
    .until !eax
    mov eax,edx
    ret

strfcat endp

AssembleSubdir proc uses esi edi ebx directory, wild

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

GeneralFailure proc signo

    mov eax,signo
    .if eax != SIGTERM
        mov eax,pCurrentException
        PrintContext(
            [eax].EXCEPTION_POINTERS.ContextRecord,
            [eax].EXCEPTION_POINTERS.ExceptionRecord)
        asmerr( 1901 )
    .endif
    close_files()
    exit(1)
    ret

GeneralFailure endp

main proc c

  local rc, numArgs, numFiles, ff:WIN32_FIND_DATA

ifndef DEBUG
    signal(SIGSEGV, GeneralFailure)
endif
if CATCHBREAK
    signal(SIGBREAK, GeneralFailure)
else
    signal(SIGTERM, GeneralFailure)
endif
ifdef __ASMC64__
    define_name( "_WIN64", "1" )
endif

    xor eax,eax
    mov rc,eax
    mov numArgs,eax
    mov numFiles,eax
    .if !getenv("ASMC")     ; v2.21 -- getenv() error..
        lea eax,@CStr("")
    .endif
    mov ecx,__argv
    mov [ecx],eax

    .while ParseCmdline(__argv, &numArgs)

        inc numFiles
        write_logo()
        lea edi,ff.cFileName
        mov esi,Options.names[ASM*4]

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

