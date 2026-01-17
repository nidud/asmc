; ASMC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include signal.inc
ifdef __UNIX__
include direct.inc
include sys/syscall.inc
define __USE_GNU
include ucontext.inc
else
include winbase.inc
include process.inc
endif
include asmc.inc
include memalloc.inc
include input.inc

.enum LNK_OPTIONS {
    O_EXENAME       = 0x01,
    O_DEFAULTLIB    = 0x02,
    O_NODEFAULTLIB  = 0x04,
ifdef __UNIX__
    O_STATIC        = 0x08,
    O_STRIP         = 0x10,
else
    O_MACHINE       = 0x08,
    O_NOLOGO        = 0x10,
    O_SUBSYSTEM     = 0x20,
    O_LINK          = 0x40,
    O_LIB           = 0x80,
    O_LINKW         = 0x100,
    O_LIBW          = 0x200,
endif
    }

init_win64 proto

.data
 _pgmptr string_t 0
 my_environ array_t 0

.code

;
; v2.34.41 - set OBJ name -Fo _*_
;
setoname proc __ccall private uses rsi rdi rbx file:string_t, newo:string_t

   .new optr:string_t = NULL
   .new name[_MAX_PATH]:char_t

    mov rbx,Options.global_options.names[TOBJ]
    .if ( rbx )

        .if ( tstrchr( rbx, '*' ) )

            .if ( tstrrchr( tstrcpy(&name, file), '.' ) )
                mov byte ptr [rax],0
            .endif

            mov optr,rbx
            mov rdx,newo
            mov Options.global_options.names[TOBJ],rdx

            .while 1

                mov al,[rbx]
                .if ( al == '*' )

                    lea rcx,name
                    .while 1

                        mov al,[rcx]
                        .break .if ( al == 0 )

                        mov [rdx],al
                        inc rcx
                        inc rdx
                    .endw

                .else

                    mov [rdx],al
                    inc rdx
                   .break .if ( al == 0 )
                .endif
                inc rbx
            .endw
        .endif
    .endif
    .return( optr )

setoname endp

ifdef __UNIX__

cmpwarg proc fastcall uses rsi rdi wild:string_t, path:string_t

    mov rdi,rcx
    mov rsi,rdx
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

    ldr rbx,directory
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

    .new optr:string_t
    .new newo[_MAX_PATH]:char_t
    .new rc:int_t = 0
    .new files:SourceFile = {0}
    .new cnt:int_t = ReadFiles( directory, wild, &files )

    .for ( rbx = files.next : rbx : )

        mov optr,setoname(&[rbx].SourceFile.file, &newo)
        .if AssembleModule( &[rbx].SourceFile.file )
            mov rc,eax
        .endif
        mov rax,optr
        .if ( rax )
            mov Options.global_options.names[TOBJ],rax
        .endif
        mov rcx,rbx
        mov rbx,[rbx].SourceFile.next
        MemFree(rcx)
    .endf
    .return( rc )

AssembleSubdir endp


else


strfcat proc __ccall private uses rsi rdi buffer:string_t, path:string_t, file:string_t

    ldr rsi,path
    ldr rdx,buffer

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

        .if ( !( al == BSLASH || al == '/' ) )

            mov al,BSLASH
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

   .new optr:string_t
   .new newo[_MAX_PATH]:char_t
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

                mov optr,setoname(rbx, &newo)
                mov rc,AssembleModule( strfcat( rsi, directory, rbx ) )
                mov rax,optr
                .if ( rax )
                    mov Options.global_options.names[TOBJ],rax
                .endif
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

if defined(_WIN64) or not defined(__UNIX__)

ifdef __UNIX__
        assume rbx:ptr mcontext_t
else
        assume rbx:ptr CONTEXT
endif

ifdef _WIN64
        lea rdi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "\tRAX: %p R8:  %p\n"
            "\tRBX: %p R9:  %p\n"
            "\tRCX: %p R10: %p\n"
            "\tRDX: %p R11: %p\n"
            "\tRSI: %p R12: %p\n"
            "\tRDI: %p R13: %p\n"
            "\tRBP: %p R14: %p\n"
            "\tRSP: %p R15: %p\n"
            "\tRIP: %p %p\n"
            "\t     %p %p\n\n"
            "\tEFL: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
else
        lea edi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "\tEAX: %p EDX: %p\n"
            "\tEBX: %p ECX: %p\n"
            "\tESI: %p EDI: %p\n"
            "\tESP: %p EBP: %p\n"
            "\tEIP: %p %p%p\n"
            "\t     %p %p\n\n"
            "\tEFL: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )
endif


ifdef __UNIX__
        mov rbx,rdx
        add rbx,ucontext_t.uc_mcontext
        mov rax,[rbx].gregs[REG_EFL*8]
else
        mov rcx,__pxcptinfoptrs()
        mov rbx,[rcx].EXCEPTION_POINTERS.ContextRecord
        mov rsi,[rcx].EXCEPTION_POINTERS.ExceptionRecord
        mov eax,[rbx].EFlags
endif
        mov ecx,16
        .repeat
            shr eax,1
            adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
        .untilcxz

ifdef __UNIX__
        mov rcx,[rbx].gregs[REG_RIP*8]
        mov rdx,[rcx]
        mov r10,[rcx-8]
        mov r11,[rcx+8]
        tprintf( rdi,
                [rbx].gregs[REG_RAX*8], [rbx].gregs[REG_R8*8],
                [rbx].gregs[REG_RBX*8], [rbx].gregs[REG_R9*8],
                [rbx].gregs[REG_RCX*8], [rbx].gregs[REG_R10*8],
                [rbx].gregs[REG_RDX*8], [rbx].gregs[REG_R11*8],
                [rbx].gregs[REG_RSI*8], [rbx].gregs[REG_R12*8],
                [rbx].gregs[REG_RDI*8], [rbx].gregs[REG_R13*8],
                [rbx].gregs[REG_RBP*8], [rbx].gregs[REG_R14*8],
                [rbx].gregs[REG_RSP*8], [rbx].gregs[REG_R15*8],
                rcx, rdx, r10, r11 )
elseifdef _WIN64
        mov rdx,[rbx]._Rip
        mov rcx,[rdx]
        mov r10,[rdx-8]
        mov r11,[rdx+8]
        tprintf( rdi,
                [rbx]._Rax, [rbx]._R8,
                [rbx]._Rbx, [rbx]._R9,
                [rbx]._Rcx, [rbx]._R10,
                [rbx]._Rdx, [rbx]._R11,
                [rbx]._Rsi, [rbx]._R12,
                [rbx]._Rdi, [rbx]._R13,
                [rbx]._Rbp, [rbx]._R14,
                [rbx]._Rsp, [rbx]._R15,
                rdx, rcx, r10, r11 )
else
        mov edx,[ebx]._Eip
        tprintf( edi,
                [ebx]._Eax, [ebx]._Edx,
                [ebx]._Ebx, [ebx]._Ecx,
                [ebx]._Esi, [ebx]._Edi,
                [ebx]._Esp, [ebx]._Ebp,
                edx, [edx+4], [edx], [edx-4], [edx+8] )
endif
        assume rbx:nothing
endif
        asmerr( 1901 )
    .endif
    close_files()
    exit(1)

GeneralFailure endp


main proc argc:int_t, argv:array_t, environ:array_t

   .new rc:int_t = 0
   .new numArgs:int_t = 0
   .new numFiles:int_t = 0
    mov my_environ,environ

ifdef __UNIX__
   .new buffer[_MAX_PATH]:char_t
   .new path:string_t = &buffer
ifdef _LIN64
   .new action:sigaction_t
endif
else
  .new ff:WIN32_FIND_DATA
  .new path:string_t = &ff.cFileName
endif

    MemInit()

ifdef _LIN64
    mov action.sa_sigaction,&GeneralFailure
    mov action.sa_flags,SA_SIGINFO
    sigaction(SIGSEGV, &action, NULL)
else
ifndef DEBUG
    signal(SIGSEGV, &GeneralFailure)
endif
ifndef __UNIX__
    signal(SIGBREAK, &GeneralFailure)
else
    signal(SIGTERM, &GeneralFailure)
endif
endif
ifdef ASMC64
    init_win64()
endif

    .if !tgetenv( "ASMC" )     ; v2.21 -- getenv() error..
        lea rax,@CStr( "" )
    .endif
    mov rcx,argv
    mov rdx,[rcx]
    mov _pgmptr,rdx
    mov [rcx],rax
ifdef _WIN64
    lea r14,ModuleInfo
    lea r15,_ltype
endif

    .while ParseCmdline(argv, &numArgs)

        write_logo()

        inc numFiles
        mov rbx,Options.names[TASM]
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

ifdef _EXEC_LINK

ifdef __UNIX__
    .elseif ( rc == 1 && !Options.no_linking && Options.output_format == OFORMAT_ELF )
else
    .elseif ( rc == 1 && !Options.no_linking && ( Options.link_linker || Options.link_exename ||
        Options.link_options || Options.output_format == OFORMAT_ELF ||
        ( Options.output_format == OFORMAT_COFF && MODULE._model == MODEL_FLAT ) ) )
endif

       .new args:array_t
ifdef __UNIX__
       .new pid:pid_t
       .new exitcode:int_t = -1
endif
       .new flags:LNK_OPTIONS

        mov rbx,Options.link_options

        .for ( ecx = 0, rbx = Options.link_options : rbx : rbx = [rbx].anode.next )

            mov eax,dword ptr [rbx].anode.name[1]
            or  eax,0x20202020

            .switch al
ifdef __UNIX__
            .case 'o'
                .if ( ax == ' o' )
                    or ecx,O_EXENAME
                .endif
                .endc
            .case 's'
                .if ( eax == 'tats' )
                    or ecx,O_STATIC
                .elseif ( ax == ' s' || ax == ' g' )
                    or ecx,O_STRIP
                .endif
            .case 'l'
                .if ( ax == ':l' )
                    or ecx,O_DEFAULTLIB
                .endif
                .endc
            .case 'n'
                .if ( eax == 'tson' )
                    or ecx,O_NODEFAULTLIB
                .endif
                .endc
else
            .case 'o'
                .if ( eax == ':tuo' || ax == ':o' )
                    or ecx,O_EXENAME
                .endif
                .endc
            .case 'm'
                .if ( eax == 'hcam' || eax == ':cam' )
                    or ecx,O_MACHINE
                .endif
                .endc
            .case 'd'
                .if ( eax == 'afed' || ax == ':d' )
                    or ecx,O_DEFAULTLIB
                .endif
                .endc
            .case 'n'
                .if ( eax == 'olon' )
                    or ecx,O_NOLOGO
                .elseif ( eax == 'edon' )
                    or ecx,O_NODEFAULTLIB
                .endif
                .endc
            .case 's'
                .if ( eax == 'sbus' )
                    or ecx,O_SUBSYSTEM
                .endif
endif
            .endsw
        .endf

ifndef __UNIX__

        mov eax,O_LINK or O_LINKW
        mov rdx,Options.link_linker
        .if ( rdx )

            xor eax,eax
            mov edx,[rdx]
            or  edx,0x20202020
            .if ( edx == 'knil' )
                mov eax,O_LINK
            .elseif ( edx == 'wbil' )
                mov eax,O_LIB or O_LIBW
            .elseif ( edx == ' bil' )
                mov eax,O_LIB
            .endif
        .endif
        or ecx,eax
endif
        mov flags,ecx

ifdef __UNIX__

        .if ( Options.link_linker == NULL )

            ; gcc [-m32 -static] [-nostdlib] [-s] -o <name> *.o [-l:[x86/]libasmc.a]

            .if ( Options.fctype != FCT_ELF64 )
                CollectLinkOption("-m32")
                mov ecx,flags
            .endif
            .if ( Options.link_mt || Options.nopic || ( Options.pic == 0 && Options.fPIC == 0 ) )

                .if ( !( ecx & ( O_DEFAULTLIB or O_NODEFAULTLIB ) ) )

                    .if ( !( ecx & O_STATIC ) )
                        CollectLinkOption("-static")
                    .endif
                    CollectLinkOption("-nostdlib")
                    .if ( Options.fctype == FCT_ELF64 )
                        CollectLinkObject("-l:libasmc.a")
                    .else
                        CollectLinkObject("-l:x86/libasmc.a")
                    .endif
                .endif
            .elseif ( !( ecx & ( O_DEFAULTLIB or O_NODEFAULTLIB ) ) && !Options.line_numbers )
                CollectLinkOption("-Wl,-z,noexecstack")
            .endif

            .if ( !( flags & O_STRIP ) && !Options.line_numbers )
                CollectLinkOption("-s")
            .endif
            .if ( !( flags & O_EXENAME ) )

                CollectLinkOption("-o")
                mov rcx,Options.link_exename
                .if ( rcx == NULL )
                    mov rcx,Options.link_objects
                    .if tstrrchr(tstrcpy(&buffer[32], &[rcx].anode.name), '.')
                        mov byte ptr [rax],0
                    .endif
                    lea rcx,buffer[32]
                .endif
                CollectLinkOption(rcx)
            .endif
        .endif

else

        ; insert options

        lea rdi,ff
        mov rbx,Options.link_options
        mov Options.link_options,NULL

        .if ( flags & O_LINK or O_LIB )

            .if ( Options.quiet && !( flags & O_NOLOGO ) )
                CollectLinkOption("-nologo")
            .endif

            .if ( !( flags & O_MACHINE ) )

                .if ( MODULE.Ofssize == USE64 )
                    CollectLinkOption("-machine:x64")
                .elseif ( MODULE.Ofssize == USE32 )
                    CollectLinkOption("-machine:x86")
                .else
                    CollectLinkOption("-machine:dos")
                .endif
            .endif

            .if ( flags & O_LINK )

                .if ( !( flags & O_SUBSYSTEM ) )

                    tstrcpy(rdi, "-subsystem:")
                    .if ( Options.output_format == OFORMAT_ELF )
                        tstrcat(rdi, "linux")
                        .if ( !( flags & O_DEFAULTLIB ) )
                            CollectLinkOption("-d:libc.a")
                            CollectLinkOption("-nor")
                        .endif
                    .elseif ( Options.output_format == OFORMAT_COFF && MODULE._model == MODEL_FLAT )
                        .if ( Options.main_found )
                            tstrcat(rdi, "console")
                        .else
                            tstrcat(rdi, "windows")
                        .endif
                    .else
                        tstrcat(rdi, "dos")
                    .endif
                    CollectLinkOption(rdi)
                .endif

                .if ( ( Options.output_format == OFORMAT_COFF && MODULE._model == MODEL_FLAT ) ||
                      ( Options.output_format == OFORMAT_ELF ) )

                    .if ( Options.link_mt )
                        .if !( Options.float_used )
                            lea rcx,@CStr("noflt.obj")
                            .if ( Options.output_format == OFORMAT_ELF )
                                lea rcx,@CStr("noflt.o")
                            .endif
                            CollectLinkObject(rcx)
                        .endif
                        .if ( Options.main_found && !( Options.argv_used ) )
                            .if ( Options.output_format != OFORMAT_ELF )
                                CollectLinkObject("noarg.obj")
                            .endif
                        .endif
                    .endif
                .endif
            .endif
        .endif

        .if ( !( flags & O_EXENAME ) )

            ; Masm use a (Unicode) response file here (mllink$.lnk)
            ; /OUT:name.exe *.obj

            .if ( Options.link_exename )

                CollectLinkOption(tstrcat(tstrcpy(rdi, "-out:"), Options.link_exename))
            .elseif ( Options.output_format == OFORMAT_ELF && flags & O_LINK )
                tstrcpy(rdi, "-out:")
                mov rcx,Options.link_objects
                .if tstrrchr(tstrcat(rdi, &[rcx].anode.name), '.')
                    mov byte ptr [rax],0
                .endif
                CollectLinkOption(tstrcat(rdi, "."))
            .endif
        .endif

        mov rcx,Options.link_options
        .if ( rcx )
            .while ( [rcx].anode.next )
                mov rcx,[rcx].anode.next
            .endw
            mov [rcx].anode.next,rbx
        .else
            mov Options.link_options,rbx
        .endif

        .if ( MODULE.Ofssize == USE16 && flags & O_LINKW &&
             !( flags & ( O_SUBSYSTEM or O_MACHINE or O_DEFAULTLIB or O_NODEFAULTLIB ) ) )

            xor ebx,ebx
            mov eax,Options._model
            .switch eax
            .case MODEL_TINY
                mov ebx,'t'
               .endc
            .case MODEL_SMALL
                mov ebx,'s'
               .endc
            .case MODEL_COMPACT
                mov ebx,'c'
               .endc
            .case MODEL_MEDIUM
                mov ebx,'m'
               .endc
            .case MODEL_LARGE
                mov ebx,'l'
            .endsw
            .if ( ebx )
                tsprintf( rdi, "-d:libc%c", ebx )
                CollectLinkOption(rdi)
                tsprintf( rdi, "crt0%c.obj", ebx )
                CollectLinkOption(rdi)
            .endif
        .endif

endif

        lea rbx,@CStr(_ASMC_LINK)
        .if ( Options.link_linker )
            mov rbx,Options.link_linker
        .endif
        tstrcpy(path, rbx)

ifdef __UNIX__

        .if ( !Options.quiet )
else
        .new linker[_MAX_PATH]:char_t

        tstrcpy(&linker, rbx)
        .if ( Options.link_linker )
            .if ( !tstrchr( rax, '.' ) )
                tstrcat( &linker, ".exe" )
            .endif
        .endif
        .ifd ( SearchPathA( 0, &linker, 0, _MAX_PATH, path, 0 ) == 0 )
            mov path,&linker
        .endif

        .if ( !Options.quiet && !( flags & O_NOLOGO ) )

endif
            tprintf( "    Linking:" )
            .for ( rbx = Options.link_options : rbx : rbx = [rbx].anode.next )
                tprintf( " %s", &[rbx].anode.name )
            .endf
            tprintf( "\n" )
        .endif

        .for ( ebx = 2, rcx = Options.link_options : rcx : rcx = [rcx].anode.next, ebx++ )
        .endf
        .for ( rcx = Options.link_objects : rcx : rcx = [rcx].anode.next, ebx++ )
        .endf
        mov args,MemAlloc( &[rbx*string_t] )

ifdef __UNIX__
        .for ( rcx = path, [rax] = rcx, rbx = &[rax+string_t],
               rcx = Options.link_objects : rcx : rcx = [rcx].anode.next, rbx+=string_t )
            mov [rbx],&[rcx].anode.name
        .endf
        .for ( rcx = Options.link_options : rcx : rcx = [rcx].anode.next, rbx+=string_t )
            mov [rbx],&[rcx].anode.name
        .endf
else
        .for ( rcx = path, [rax] = rcx, rbx = &[rax+string_t],
               rcx = Options.link_options : rcx : rcx = [rcx].anode.next, rbx+=string_t )
            mov [rbx],&[rcx].anode.name
        .endf
        .for ( rcx = Options.link_objects : rcx : rcx = [rcx].anode.next, rbx+=string_t )
            mov [rbx],&[rcx].anode.name
        .endf
endif
        xor eax,eax
        mov [rbx],rax

ifdef __UNIX__

        mov pid,sys_fork()
        .if ( pid == 0 )

            ; child process

            sys_execve(path, args, environ)
            sys_exit(EXIT_SUCCESS)

        .elseif ( pid > 0 )

            ; parent process
ifdef _WIN64
            sys_wait4(pid, &exitcode, 0, NULL)
else
            sys_waitpid(pid, &exitcode, 0)
endif
            .ifs ( eax < 0 )
                mov eax,-1
            .else
                mov eax,exitcode
            .endif
        .else
            mov eax,-1
        .endif
else
        _spawnve(P_WAIT, path, args, environ)
endif
        .if ( eax == -1 )

            asmerr( 2018, path )
            mov rc,0
        .endif
endif
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
        mov rax,[rsi]
        add rsi,string_t

        .while rax

            .ifd !tmemicmp(rax, rbx, edi)

                mov rax,[rsi-string_t]
                add rax,rdi

                .if ( byte ptr [rax] == '=' )

                    .return( &[rax+1] )
                .endif
            .endif
            mov rax,[rsi]
            add rsi,string_t
        .endw
    .endif
    ret

tgetenv endp

    end
