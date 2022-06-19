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

init_options proto

.data
ifdef __UNIX__
ifdef __WATCOM__
extern _cstart_: byte
endif
_pgmptr string_t 0
endif
my_environ array_t 0

.code

ifdef __UNIX__

cmpwarg proc __ccall uses rsi rdi wild:string_t, path:string_t

    mov rdi,wild
    mov rsi,path
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


ReadFiles proc __ccall uses rsi rdi rbx directory:string_t, wild:string_t, files:ptr SourceFile

    mov rbx,directory
    .if ( byte ptr [rbx] == 0 )
        mov word ptr [rbx],'.'
    .endif

    .new file:string_t = &[rbx+tstrlen(rbx)]

    .if ( opendir( directory ) != NULL )

        .new dir:ptr DIR = rax
        .new cnt:int_t = 0

        .while ( readdir( dir ) )

            mov rbx,rax

            .if ( [rbx].dirent.d_type != DT_DIR )

                .if ( cmpwarg( wild, &[rbx].dirent.d_name ) )

                    mov rcx,file
                    mov word ptr [rcx],'/'
                    tstrcat( rcx, &[rbx].dirent.d_name )

                    add tstrlen( directory ),SourceFile
                    .if MemAlloc( eax )

                        mov rcx,files
                        mov [rcx].SourceFile.next,rax
                        mov files,rax

                        mov [rax].SourceFile.next,NULL
                        tstrcpy( &[rax].SourceFile.file, directory )
                        inc cnt
                    .endif
                    mov rcx,file
                    mov byte ptr [rcx],0
                .endif

            .elseif ( Options.process_subdir )

                mov eax,dword ptr [rbx].dirent.d_name
                and eax,0x00FFFFFF

                .if ( ax != '.' && eax != '..' )

                    mov rcx,file
                    mov word ptr [rcx],'/'
                    tstrcat( rcx, &[rbx].dirent.d_name )

                    ReadFiles( directory, wild, files )

                    add cnt,eax
                    mov rcx,file
                    mov byte ptr [rcx],0

                    mov rcx,files
                    .while ( [rcx].SourceFile.next )

                        mov rcx,[rcx].SourceFile.next
                    .endw
                    mov files,rcx
                .endif
            .endif
        .endw
        closedir( dir )
    .endif
    .return( cnt )

ReadFiles endp


AssembleSubdir proc uses rbx directory:string_t, wild:string_t

    .new rc:int_t = 0
    .new files:SourceFile = {0}
    .new cnt:int_t = ReadFiles( directory, wild, &files )

    .for ( rbx = files.next : rbx : )

        .if AssembleModule( &[rbx].SourceFile.file )
            mov rc,eax
        .endif
        mov rcx,rbx
        mov rbx,[rbx].SourceFile.next
        MemFree(rcx)
    .endf
    .return( rc )

AssembleSubdir endp


else


strfcat proc __ccall private uses rsi rdi buffer:string_t, path:string_t, file:string_t

    mov rdx,buffer
    mov rsi,path

    xor eax,eax
    mov ecx,-1

    .if ( rsi )

        mov   rdi,rsi ; overwrite buffer
        repne scasb
        mov   rdi,rdx
        not   ecx
        rep   movsb
    .else
        mov   rdi,rdx ; length of buffer
        repne scasb
    .endif
    dec rdi

    .if ( rdi != rdx ) ; add slash if missing

        mov al,[rdi-1]

        .if ( !( al == '\' || al == '/' ) )

            mov al,'\'
            stosb
        .endif
    .endif

    mov rsi,file    ; add file name
    .repeat
        lodsb
        stosb
    .until !eax
    .return(rdx)

strfcat endp


AssembleSubdir proc private uses rsi rdi rbx directory:string_t, wild:string_t

   .new path[_MAX_PATH]:char_t
   .new ff:WIN32_FIND_DATA
   .new rc:int_t = 0
   .new h:HANDLE

    lea rsi,path
    lea rdi,ff
    lea rbx,ff.cFileName

    .if ( FindFirstFile( strfcat( rsi, directory, wild ), rdi ) != -1 )

        mov h,rax

        .repeat

            .if !( byte ptr ff.dwFileAttributes & _A_SUBDIR )

                mov rc,AssembleModule( strfcat( rsi, directory, rbx ) )
            .endif
        .until !FindNextFile( h, rdi )

        FindClose( h )
    .endif

    .if ( Options.process_subdir )

        .if ( FindFirstFile( strfcat( rsi, directory, "*.*" ), rdi ) != -1 )

            mov h,rax

            .repeat

                mov eax,[rbx]
                and eax,0x00FFFFFF

                .if ( ff.dwFileAttributes & _A_SUBDIR && ax != '.' && eax != '..' )

                    .if AssembleSubdir( strfcat( rsi, directory, rbx ), wild )

                        mov rc,eax
                    .endif
                .endif
            .until !FindNextFile( h, rdi )

            FindClose( h )
        .endif
    .endif
    .return( rc )

AssembleSubdir endp

endif


GeneralFailure proc private signo:int_t

    .if ( signo != SIGTERM )

ifndef __UNIX__

        mov rcx,pCurrentException
        mov rbx,[rcx].EXCEPTION_POINTERS.ContextRecord
        mov rsi,[rcx].EXCEPTION_POINTERS.ExceptionRecord

ifdef _WIN64

        lea rdi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "Exception:   Segment violation\n"
            "\n"
            "Code: \t     %08X\n"
            "Flags:\t     %08X\n"
            "\n"
            "\tRAX: %p R8:  %p\n"
            "\tRBX: %p R9:  %p\n"
            "\tRCX: %p R10: %p\n"
            "\tRDX: %p R11: %p\n"
            "\tRSI: %p R12: %p\n"
            "\tRDI: %p R13: %p\n"
            "\tRBP: %p R14: %p\n"
            "\tRSP: %p R15: %p\n"
            "\tRIP: %p *--: %p\n"
            "   Dispatch: %p *--: %p\n"
            "     EFlags: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
else

        lea edi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "Exception: Segment violation\n"
            "\n"
            "Code:\t%08X\n"
            "Flags:  %08X\n"
            "\n"
            "\tEAX: %08X EDX: %08X\n"
            "\tEBX: %08X ECX: %08X\n"
            "\tESI: %08X EDI: %08X\n"
            "\tESP: %08X EBP: %08X\n"
            "\tEIP: %08X\n\n"
            "    Content: %08X%08X%08X%08X\n\n"
            "     EFlags: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
endif

        mov eax,[rbx].CONTEXT.EFlags
        mov ecx,16
        .repeat
            shr eax,1
            adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
        .untilcxz

ifdef _WIN64

        mov rdx,[rbx].CONTEXT._Rip
        mov rcx,[rdx]
        xor r8,r8
        .if ( r9 )
            mov r8,[r9]
            mov r9,[r8]
        .endif

        tprintf(
            rdi,
            [rsi].EXCEPTION_RECORD.ExceptionCode,
            [rsi].EXCEPTION_RECORD.ExceptionFlags,
            [rbx].CONTEXT._Rax, [rbx].CONTEXT._R8,
            [rbx].CONTEXT._Rbx, [rbx].CONTEXT._R9,
            [rbx].CONTEXT._Rcx, [rbx].CONTEXT._R10,
            [rbx].CONTEXT._Rdx, [rbx].CONTEXT._R11,
            [rbx].CONTEXT._Rsi, [rbx].CONTEXT._R12,
            [rbx].CONTEXT._Rdi, [rbx].CONTEXT._R13,
            [rbx].CONTEXT._Rbp, [rbx].CONTEXT._R14,
            [rbx].CONTEXT._Rsp, [rbx].CONTEXT._R15,
            rdx, rcx, r8, r9)
else
        mov edx,[ebx].CONTEXT._Eip
        tprintf(
            edi,
            [esi].EXCEPTION_RECORD.ExceptionCode,
            [esi].EXCEPTION_RECORD.ExceptionFlags,
            [ebx].CONTEXT._Eax, [ebx].CONTEXT._Edx,
            [ebx].CONTEXT._Ebx, [ebx].CONTEXT._Ecx,
            [ebx].CONTEXT._Esi, [ebx].CONTEXT._Edi,
            [ebx].CONTEXT._Esp, [ebx].CONTEXT._Ebp,
            edx, [edx+12], [edx+8], [edx+4], [edx] )
endif

endif
        asmerr( 1901 )
    .endif
    close_files()
    exit(1)

GeneralFailure endp


ifdef _LIN64
main proc _argc:int_t, _argv:array_t, environ:array_t
   .new argc:int_t   = _argc
   .new argv:array_t = _argv
elseifdef _WIN64
main proc frame:ExceptionHandler argc:int_t, argv:array_t, environ:array_t
else
main proc argc:int_t, argv:array_t, environ:array_t
endif

   .new rc:int_t = 0
   .new numArgs:int_t = 0
   .new numFiles:int_t = 0
    mov my_environ,environ

ifdef __UNIX__
  .new buffer[_MAX_PATH]:char_t
  .new path:string_t = &buffer
else
  .new ff:WIN32_FIND_DATA
  .new path:string_t = &ff.cFileName
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

    .if !tgetenv( "ASMC" )     ; v2.21 -- getenv() error..
        lea rax,@CStr( "" )
    .endif
    mov rcx,argv

ifdef __UNIX__
    mov rdx,[rcx]
    mov _pgmptr,rdx
endif
    mov [rcx],rax
ifdef _WIN64
    lea r15,_ltype
endif

    .while ParseCmdline(argv, &numArgs)

        write_logo()

        inc numFiles
        mov rbx,Options.names[ASM*string_t]
ifndef __UNIX__

        .if ( !Options.process_subdir )

            .ifd ( FindFirstFile( rbx, &ff ) == -1 )

                asmerr( 1000, rbx )
               .break
            .endif
            FindClose(rax)
        .endif
endif
        .if !tstrchr( tstrcpy(path, rbx ), '*' )
            tstrchr( path, '?' )
        .endif
        .if rax
            .if GetFNamePart( path ) > path
                dec rax
            .endif
            mov byte ptr [rax],0
            mov rc,AssembleSubdir( path, GetFNamePart( rbx ) )
        .else
            mov rc,AssembleModule( path )
        .endif
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
        mov rsi,my_environ
        .lodsd

        .while rax

            .ifd !tmemicmp(rax, rbx, edi)

                mov rax,[rsi-string_t]
                add rax,rdi

                .if ( byte ptr [rax] == '=' )

                    .return( &[rax+1] )
                .endif
            .endif
            .lodsd
        .endw
    .endif
    ret

tgetenv endp

    end

