; CMDLINE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include memalloc.inc
include input.inc

externdef cp_logo:sbyte
externdef banner_printed:byte

    .data

Options global_options {
        { 0 },                  ; .flags
        { 0 },                  ; .flags(2)
        FPO_NO_EMULATION,       ; .floating_point
        50,                     ; .error_limit
        {0,0,0,0,0,0,0,0,0},    ; .names
        {0,0,0},                ; .queues
        0,                      ; .link_exename
        0,                      ; .link_linker
        0,                      ; .link_options
        0,                      ; .link_objects
        LM_LISTMACRO,           ; .list_macro
        OFORMAT_OMF,            ; .output_format
        SFORMAT_NONE,           ; .sub_format
        LANG_NONE,              ; .langtype
        MODEL_NONE,             ; ._model
        P_86,                   ; .cpu
        FCT_MSC,                ; .fctype
        0,                      ; .codepage
        1,                      ; .floatdigits
        0,                      ; .frame_auto
        0,                      ; .debug_symbols
        0,                      ; .debug_ext
        2,                      ; .warning_level
        0,                      ; .link
        STDCALL_FULL,           ; .stdcall_decoration
        0,                      ; .floatformat
        4,                      ; .flt_size
        0,                      ; .fieldalign
        0,                      ; .loopalign
        0,                      ; .casealign
        4,                      ; .segmentalign
        3,                      ; .pe_subsystem
        0,                      ; .win64_flags
        0,                      ; .arch
        0 }                     ; .iddc

    align size_t

     DefaultDir string_t NUM_FILE_TYPES dup(NULL)
     OptValue   int_t 0

     ; array for options -0..10

     cpu_option int_t \
        P_86,
        P_186,
        P_286,
        P_386,
        P_486,
        P_586,
        P_686,
        P_686 or P_MMX,
        P_686 or P_MMX or P_SSE1,
        P_686 or P_MMX or P_SSE1 or P_SSE2,
        P_64


    .code

    option proc:private

define_cpu proc fastcall cpu:int_t

    .switch ecx
    .case CPU_64    : define_name( "__P64__", "1" )
    .case CPU_SSE2  : define_name( "__SSE2__", "1" )
    .case CPU_SSE   : define_name( "__SSE__", "1" )
    .case CPU_MMX
    .case CPU_686   : define_name( "__P686__", "1" )
    .case CPU_586   : define_name( "__P586__", "1" )
    .case CPU_486   : define_name( "__P486__", "1" )
    .case CPU_386   : define_name( "__P386__", "1" )
    .case CPU_286   : define_name( "__P286__", "1" )
    .case CPU_186   : define_name( "__P186__", "1" )
    .case CPU_86    : define_name( "__P86__", "1" )
    .endsw
    ret

define_cpu endp


set_cpu proc fastcall _cpu:int_t, pm:int_t

    lea rax,cpu_option
    mov eax,[rax+rcx*int_t]

    and Options.cpu,not ( P_CPU_MASK or P_EXT_MASK or P_PM )
    or  Options.cpu,eax
    .if ( edx && Options.cpu >= P_286 )
        or Options.cpu,P_PM
    .endif
    .return define_cpu( ecx )

set_cpu endp


init_win64 proc public

    set_cpu( CPU_64, 1 )
    define_name( "_WIN64", "1" )

    mov Options.sub_format,SFORMAT_64BIT
    mov Options._model,MODEL_FLAT
    mov Options.switch_regax,1

ifdef __UNIX__
    define_name( "__UNIX__", "1" )
    mov Options.output_format,OFORMAT_ELF
    mov Options.langtype,LANG_SYSCALL
    mov Options.fctype,FCT_ELF64
else
    mov Options.output_format,OFORMAT_COFF
    mov Options.langtype,LANG_FASTCALL
    mov Options.fctype,FCT_WIN64
endif
    ret

init_win64 endp


; current cmdline string is done, get the next one!

getnextcmdstring proc fastcall cmdline:array_t

    mov rax,[rcx+string_t]
    .if ( rax )

        .for ( rdx = rax : rdx : rcx += string_t )

            mov [rcx],rdx
            mov rdx,[rcx+string_t*2]
        .endf
        mov [rcx],rdx
    .endif
    ret

getnextcmdstring endp


getfilearg proc fastcall args:array_t, p:string_t ; -Fo<file> or -Fo <file>

    mov rax,rdx
    mov rdx,[rcx]

    .if ( byte ptr [rax] == 0 )
         getnextcmdstring( rcx )
    .elseif ( byte ptr [rax] == '=' )
        inc rax
    .endif
    .if ( !rax || byte ptr [rax] == 0 )
        asmerr( 1006, rdx )
    .endif
    ret

getfilearg endp


GetNumber proc fastcall p:string_t

    .for ( eax = 0, edx = 0, al = [rcx] : al >= '0' && al <= '9' : rcx++, al = [rcx] )

        imul edx,edx,10
        sub al,'0'
        add edx,eax
    .endf
    mov OptValue,edx
   .return rcx

GetNumber endp

;
; queue a text macro, include path or "forced" include files.
; this is called for cmdline options -D, -I and -Fi
;

queue_item proc __ccall uses rsi i:int_t, string:string_t

    mov rsi,MemAlloc( &[ tstrlen( string ) + sizeof( qitem )] )
    mov [rsi].qitem.next,NULL
    tstrcpy( &[rsi].qitem.value, string )

    mov ecx,i
    lea rdx,Options
    mov rax,[rdx].global_options.queues[rcx*string_t]
    .if ( rax )
        .for ( : [rax].qitem.next : rax = [rax].qitem.next )
        .endf
        mov [rax].qitem.next,rsi
    .else
        mov [rdx].global_options.queues[rcx*string_t],rsi
    .endif
    ret

queue_item endp


get_fname proc __ccall uses rsi rdi rbx type:int_t, token:string_t

   .new name[_MAX_PATH]:char_t

    ldr rsi,token
    ldr ebx,type

    .if ( byte ptr [rsi] == '=' )
        inc rsi
    .endif
    mov rdi,GetFNamePart(rsi)
    ;
    ; If name's ending with a BSLASH (or '/' in Unix), it's supposed
    ; to be a directory name only.
    ;
    lea rdx,DefaultDir
    .if ( byte ptr [rdi] == 0 )

        .if ( rbx < NUM_FILE_TYPES && byte ptr [rsi] )

            mov rcx,[rdx+rbx*string_t]
            mov rdi,rdx
            .if ( rcx )
                MemFree(rcx)
            .endif
            mov [rdi+rbx*string_t],MemDup(rsi)
        .endif
        .return
    .endif
    mov name[0],0
    mov rdx,[rdx+rbx*string_t]
    .if ( rsi == rdi && ebx < NUM_FILE_TYPES && rdx )
        tstrcpy(&name, rdx)
    .endif
    tstrcat(&name, rsi)
    lea rdx,Options
    lea rdi,[rdx].global_options.names[rbx*string_t]
    MemFree([rdi])
    mov [rdi],MemDup(&name)
    ret

get_fname endp


set_option_n_name proc fastcall uses rsi rdi idx:int_t, name:string_t

    mov rdi,rdx
    movzx eax,byte ptr [rdi]
    .if ( al != '.' )
        .if ( !islabel( eax ) )
            xor eax,eax
        .endif
    .endif
    .if al
        lea rax,Options
        lea rsi,[rax].global_options.names[rcx*string_t]
        MemFree( [rsi] )
        mov [rsi],MemDup(rdi)
    .else
        asmerr( 1006, rdx )
    .endif
    ret

set_option_n_name endp


;
; A '@' was found in the cmdline. It's not an environment variable,
; so check if it is a file and, if yes, read it.
;

ReadParamFile proc fastcall uses rsi rdi rbx name:string_t

    .new fp:ptr FILE = fopen( rcx, "rb" )

    .if ( rax == NULL )

        asmerr( 1000, name )
       .return( NULL )
    .endif

    .new retval:ptr = NULL
    .if ( fseek( fp, 0, SEEK_END ) == 0 )

        .if ( ftell( fp ) )

            mov rbx,rax
            mov retval,MemAlloc( &[rax+1] )
            mov byte ptr [rax+rbx],0
            rewind( fp )
            fread( retval, 1, ebx, fp )
        .endif
    .endif

    fclose(fp)
   .return( retval )

ReadParamFile endp


;
; get a "name"
; type=@ : filename ( -Fd, -Fi, -Fl, -Fo, -Fw, -I )
; type=$ : (macro) identifier [=value] ( -D, -nc, -nd, -nm, -nt )
; type=0 : something else ( -0..-10 )
;

GetNameToken proc __ccall uses rsi rdi rbx dst:string_t, string:string_t, max:int_t, type:char_t

   .new equatefound:int_t = FALSE

    ldr rsi,string
    ldr rdi,dst

is_quote:

    mov al,[rsi]
    .if al == '"'

        inc rsi
        .for( : max && byte ptr [rsi]: max-- )

            mov eax,[rsi]
            .if al == '"'

                inc rsi
                .break
            .endif

            ; handle the \"" case

            .if al == BSLASH && ah == '"'

                inc rsi
            .endif
            movsb
        .endf
    .else

        .for( : max: max-- )

            ; v2.10: don't stop for white spaces

            mov al,[rsi]
            .break .if ( al == 0 )
            .break .if ( al == 13 || al == 10 )

            ; v2.10: don't stop for white spaces if filename
            ; is expected and true cmdline is parsed

            .break .if ( ( al == ' ' || al == 9 ) && ( type != '@' ) )

            .if type == 0
ifdef __UNIX__
                .break .if ( al == '-' && eax != 'leh-' )
else
                .break .if ( al == '-' || al == '/' )
endif
            .endif

            .if ( al == '=' && type == '$' && equatefound == FALSE )

                mov equatefound,TRUE
                movsb
                mov al,[rsi]

                .if (al == '"')

                    jmp is_quote
                .endif
            .endif
            movsb
        .endf
    .endif
     mov byte ptr [rdi],0
    .return(rsi)

GetNameToken endp

ifdef _EXEC_LINK

CollectLinkNode proc __ccall uses rbx arg:string_t, node:ptr anode

    ldr rbx,arg

    MemAlloc( &[tstrlen(rbx)+anode] )
    mov rdx,node
    mov rcx,[rdx]
    .if ( rcx )
        .for ( : [rcx].anode.next : rcx = [rcx].anode.next )
        .endf
        mov [rcx].anode.next,rax
    .else
        mov [rdx],rax
    .endif
    mov [rax].anode.next,NULL
    tstrcpy( &[rax].anode.name, rbx )
    ret

CollectLinkNode endp

CollectLinkOption proc fastcall public arg:string_t

    CollectLinkNode( rcx, &Options.link_options )
    ret

CollectLinkOption endp

CollectLinkObject proc fastcall public arg:string_t

    CollectLinkNode( rcx, &Options.link_objects )
    ret

CollectLinkObject endp

endif

ProcessOption proc __ccall uses rsi rdi rbx cmdline:ptr string_t, buffer:string_t

   .new i:int_t
   .new j:int_t
   .new p:string_t

    ldr rsi,cmdline
    ldr rdi,buffer
    mov rbx,[rsi]

    mov eax,[rbx]

ifndef ASMC64

    ; numeric option (-0, -1, ... ) handled separately since
    ; the value can be >= 10.

    .if ( al >= '0' && al <= '9' )

        mov rbx,GetNumber( rbx )

        .if ( OptValue < lengthof( cpu_option ) )

            mov rbx,GetNameToken( rdi, rbx, 16, 0 ) ; get optional 'p'
            mov [rsi],rbx
            xor edx,edx
            .if ( byte ptr [rdi+1] == 'p' )
                inc edx
            .endif
            .return set_cpu( OptValue, edx )
        .endif
        mov rbx,[rsi] ; v2.11: restore option pointer
    .endif
endif

    .if ( al == 'D' ) ; -D<name>[=text]

        mov [rsi],GetNameToken(rdi, &[rbx+1], 256, '$')
        queue_item(OPTQ_MACRO, rdi)
       .return
    .endif

    .if ( al == 'I' ) ; -I<file>

        mov [rsi],GetNameToken(rdi, &[rbx+1], 256, '@')
        queue_item(OPTQ_INCPATH, rdi)
       .return
    .endif

    mov [rsi],GetNameToken(rdi, rbx, 16, 0)
    mov eax,[rdi]

    .if ( ah == 0 )
        and eax,0xFF
    .elseif ( !( eax & 0xFF0000 ) )
        and eax,0xFFFF
    .endif

    .switch eax
    .case 'hcra'        ; -arch:xx
        mov eax,[rdi+4]
        .if al != ':' || ah == 0
            asmerr( 1006, rdi )
        .endif
        mov eax,[rdi+5]
        xor ebx,ebx
        .switch eax
        .case '5XVA'    ; -arch:AVX512
            define_name( "__AVX512BW__", "1" )
            define_name( "__AVX512CD__", "1" )
            define_name( "__AVX512DQ__", "1" )
            define_name( "__AVX512F__",  "1" )
            define_name( "__AVX512VL__", "1" )
            inc ebx
        .case '2XVA'    ; -arch:AVX2
            define_name( "__AVX2__", "1" )
            inc ebx
        .case 'XVA'     ; -arch:AVX
            define_name( "__AVX__",  "1" )
            inc ebx
        .case '2ESS'    ; -arch:SSE2
            define_name( "__SSE2__", "1" )
            inc ebx
        .case 'ESS'     ; -arch:SSE
            define_name( "__SSE__",  "1" )
            inc ebx
           .endc
        .case '23AI'    ; -arch:IA32
            define_name( "_M_IX86_FP",  "1" )
           .endc
        .default
            asmerr( 1006, rdi )
        .endsw
        mov Options.arch,bl
        .return
    .case 'essa'            ; -assert
        mov Options.assert,1
        .return
    .case 'otua'            ; -autostack -- v2.35.02 -win64 needs to come first!
        .if ( Options.sub_format == SFORMAT_64BIT )
            or Options.win64_flags,W64F_AUTOSTACKSP
        .endif
        .return
    .case 'c'               ; -c
        mov Options.no_linking,1
        mov Options.link_mt,0
        .return
    .case 'ffoc'            ; -coff
        mov Options.output_format,OFORMAT_COFF
        mov Options.sub_format,SFORMAT_NONE
        .return
    .case 'PE'              ; -EP
        mov Options.no_linking,1
        mov Options.preprocessor_stdout,1
    .case 'q'               ; -q
        mov Options.quiet,1
    .case 'olon'            ; -nologo
        mov banner_printed,1
        .return
    .case 'nib'             ; -bin
        mov Options.no_linking,1
        mov Options.output_format,OFORMAT_BIN
        mov Options.sub_format,SFORMAT_NONE
        .return
    .case 'pC'              ; -Cp
        mov Options.case_sensitive,1
        mov Options.convert_uppercase,0
        .return
    .case 'sC'              ; -Cs
        mov Options.cstack,1
        .return
    .case 'uC'              ; -Cu
        mov Options.case_sensitive,0
        mov Options.convert_uppercase,1
        .return
    .case 'xC'              ; -Cx
        mov Options.case_sensitive,0
        mov Options.convert_uppercase,0
        .return
    .case 'ntod'            ; -dotname
        mov Options.dotname,TRUE
        .return
    .case 'bdne'            ; -endbr
        mov Options.endbr,1
        .return
    .case 'qe'              ; -eq
        mov Options.no_error_disp,1
        .return
    .case '6fle'            ; -elf64
        set_cpu( CPU_64, 1 )
        define_name( "__UNIX__", "1" )
        define_name( "_WIN64",   "1" )
        mov Options.switch_regax,1
        mov Options._model,MODEL_FLAT
        mov Options.output_format,OFORMAT_ELF
        mov Options.sub_format,SFORMAT_64BIT
        mov Options.langtype,LANG_SYSCALL
        mov Options.fctype,FCT_ELF64
       .return
    .case 'orre'            ; -errorReport:
        mov rbx,[rsi]
        .while byte ptr [rbx]
            inc rbx
        .endw
        mov [rsi],rbx
        .return
ifndef ASMC64
    .case 'fle'             ; -elf
        mov Options.output_format,OFORMAT_ELF
        mov Options.sub_format,SFORMAT_NONE
        define_name( "__UNIX__", "1" )
        .return
    .case '8iPF'            ; -FPi87
        mov Options.floating_point,FPO_NO_EMULATION
        .return
    .case 'iPF'             ; -Fpi
        mov Options.floating_point,FPO_EMULATION
        .return
    .case '0pf'             ; -fp0
        mov Options.cpu,P_87
        .return
    .case '2pf'             ; -fp2
        mov Options.cpu,P_287
        .return
    .case '3pf'             ; -fp3
        mov Options.cpu,P_387
        .return
    .case 'cpf'             ; -fpc
        mov Options.cpu,P_NO87
        .return
endif
    .case 'CIPf'            ; -fPIC
        mov Options.plt,0
        mov Options.fPIC,1
        undef_name( "__PIC__" )
        define_name( "__PIC__", "2" )
       .return
    .case 'cipf'            ; -fpic
        mov Options.plt,0
        mov Options.pic,1
        .if ( !Options.fPIC )
            undef_name( "__PIC__" )
            define_name( "__PIC__", "1" )
        .endif
        .return
    .case 'tlpf'            ; -fplt
        mov Options.pic,0
        mov Options.fPIC,0
        undef_name( "__PIC__" )
        mov Options.plt,1
       .return
    .case 'onf'             ; -fno-pic, -fno-plt
        mov rbx,[rsi]
        mov eax,[rbx]
        .while byte ptr [rbx]
            inc rbx
        .endw
        mov [rsi],rbx
        .if ( eax == 'cip-' )
            mov Options.pic,0
            mov Options.fPIC,0
            undef_name( "__PIC__" )
        .else
            mov Options.noplt,1
        .endif
        .return

    .case 'marf'            ; -frame
        mov Options.frame_auto,3
        .return

ifndef ASMC64
    .case 'cG'              ; -Gc
        mov Options.langtype,LANG_PASCAL
        .return
    .case 'dG'              ; -Gd
        mov Options.langtype,LANG_C
        .return
endif
    .case 'eG'              ; -Ge
        mov Options.chkstack,1
        .return
    .case 'rG'              ; -Gr
        mov Options.langtype,LANG_FASTCALL
        .return
    .case 'sG'              ; -Gs
        mov Options.langtype,LANG_SYSCALL
        .return
    .case 'vG'              ; -Gv
        mov Options.langtype,LANG_VECTORCALL
        .return
    .case 'wG'              ; -Gw
        mov Options.langtype,LANG_WATCALL
        .return
ifndef ASMC64
    .case 'zG'              ; -Gz
        mov Options.langtype,LANG_STDCALL
        define_name( "_STDCALL_SUPPORTED", "1" )
        .return
endif
ifdef __UNIX__
    .case 'leh-'            ; --help
else
    .case '?'
endif
    .case 'pleh'
    .case 'h'
        write_options()
        exit(0)
    .case 'emoh'            ; -homeparams
        or Options.win64_flags,W64F_SAVEREGPARAMS
        .return
    .case 'tddi'            ; -iddt
        mov Options.iddc,2
        .return
    .case 'ddi'             ; -idd
        mov Options.iddc,1
        .return
    .case 'knil'            ; -link
        mov Options.link,1
        .return
    .case 'ogol'            ; -logo
        tprintf( &cp_logo, ASMC_MAJOR, ASMC_MINOR, ASMC_SUBVER )
        tprintf( "\n" )
        exit(0)
ifndef ASMC64
    .case 'zm'              ; -mz
        mov Options.output_format,OFORMAT_BIN
        mov Options.sub_format,SFORMAT_MZ
        mov Options.no_linking,1
        .return
    .case 'cm'              ; -mc
        mov Options._model,MODEL_COMPACT
        define_name( "__COMPACT__", "1" )
        .return
    .case 'fm'              ; -mf
        mov Options._model,MODEL_FLAT
        define_name( "__FLAT__", "1" )
        .return
    .case 'hm'              ; -mh
        mov Options._model,MODEL_HUGE
        define_name( "__HUGE__", "1" )
        .return
    .case 'lm'              ; -ml
        mov Options._model,MODEL_LARGE
        define_name( "__LARGE__", "1" )
        .return
    .case 'mm'              ; -mm
        mov Options._model,MODEL_MEDIUM
        define_name( "__MEDIUM__", "1" )
        .return
    .case 'sm'              ; -ms
        mov Options._model,MODEL_SMALL
        define_name( "__SMALL__", "1" )
        .return
    .case 'tm'              ; -mt
        mov Options._model,MODEL_TINY
        define_name( "__TINY__", "1" )
        .return
endif
    .case 'dTM'             ; -MTd
        define_name( "_DEBUG", "1" )
    .case 'TM'              ; -MT
        define_name( "_MT", "1" )
        .if ( Options.no_linking == 0 )
            mov Options.link_mt,1
        .endif
        .return
    .case 'dDM'             ; -MDd
        define_name( "_DEBUG", "1" )
    .case 'ilon'            ; -nolib
        mov Options.nolib,TRUE
       .return ; v2.37.04: added
    .case 'DM'              ; -MD
        define_name( "_MSVCRT", "1" )
       .return
    .case 'rcsm'            ; -mscrt
        mov Options.mscrt,1
        define_name( "__MSCRT__", "1" )
       .return

ifndef ASMC64
    .case 'fmo'             ; -omf
        mov Options.output_format,OFORMAT_OMF
        mov Options.sub_format,SFORMAT_NONE
        .return
endif
    .case 'cep'             ; -pec - subsystem:console
        mov Options.pe_subsystem,3
        define_name( "__CUI__", "1" )
    .case 'ep'              ; -pe
ifdef __UNIX__
        undef_name( "__UNIX__" )
ifdef ASMC64
        mov Options.langtype,LANG_FASTCALL
        mov Options.fctype,FCT_WIN64
endif
endif
        .if ( Options.sub_format != SFORMAT_64BIT )
            mov Options.sub_format,SFORMAT_PE
        .endif
        mov Options.output_format,OFORMAT_BIN
        define_name( "__PE__", "1" )
        mov Options.no_linking,1
        .return
    .case 'gep'             ; -peg - subsystem:windows
        mov Options.pe_subsystem,2
        define_name( "__GUI__", "1" )
        .gotosw('ep')
    .case 'dep'             ; -ped -dll
        mov Options.pe_dll,1
        mov Options.no_export_decoration,1
        define_name( "__DLL__", "1" )
       .gotosw('ep')
    .case 'r'               ; -r
        mov Options.process_subdir,1
        .return
    .case 'aS'              ; -Sa
        .return
    .case 'fS'              ; -Sf
        mov Options.first_pass_listing,1
        .return
    .case 'gS'              ; -Sg
        mov Options.list_generated_code,1
        .return
    .case 'nS'              ; -Sn
        mov Options.no_symbol_listing,1
        .return
    .case 'cats'            ; -stackalign
        or Options.win64_flags,W64F_STACKALIGN16
        .return
    .case 'xS'              ; -Sx
        mov Options.listif,1
        .return
    .case 'efas'            ; -safeseh
        mov Options.safeseh,1
        .return
    .case 'w'               ; -w
        mov Options.warning_level,0
        .return
    .case 'sw'              ; -ws
        mov Options.wstring,1
        define_name( "_UNICODE", "1" )
        .return
    .case 'XW'              ; -WX
        mov Options.warning_error,1
        .return
    .case '6niw'            ; -win64
ifndef ASMC64
        init_win64()
endif
        .return
    .case '7Z'          ; -Z7
        define_name( "__DEBUG__", "1" )
        mov Options.line_numbers,1
        mov Options.debug_symbols,4
        mov Options.no_file_entry,1
        mov Options.debug_ext,CVEX_NORMAL
        mov Options.debug_frame,1
       .return
    .case 'X'               ; -X
        mov Options.ignore_include,1
       .return
ifndef ASMC64
    .case 'mcz'             ; -zcm
        mov Options.no_cdecl_decoration,0
       .return
    .case 'wcz'             ; -zcw
        mov Options.no_cdecl_decoration,1
       .return
endif
    .case 'fZ'              ; -Zf
        mov Options.all_symbols_public,1
       .return
    .case '0fz'             ; -zf0
        mov Options.fctype,FCT_MSC
       .return
    .case '1fz'             ; -zf1
        mov Options.fctype,FCT_WATCOMC
       .return
    .case 'gZ'              ; -Zg
        mov Options.masm_compat_gencode,1
        .return
    .case 'dZ'              ; -Zd
        mov Options.line_numbers,1
        .return
    .case 'clz'             ; -zlc
        mov Options.no_comment_in_code_rec,1
        .return
    .case 'dlz'             ; -zld
        mov Options.no_opt_farcall,1
        .return
    .case 'flz'             ; -zlf
        mov Options.no_file_entry,1
        .return
    .case 'plz'             ; -zlp
        mov Options.no_static_procs,1
        .return
    .case 'slz'             ; -zls
        mov Options.no_section_aux_entry,1
        .return
    .case 'enZ'             ; -Zne
        mov Options.strict_masm_compat,1
        .return
ifndef ASMC64
    .case 'mZ'              ; -Zm
        mov Options.masm51_compat,1
endif
    .case 'sZ'              ; -Zs
        mov Options.syntax_check_only,1
       .return
    .case '0tz'             ; -zt0
        mov Options.stdcall_decoration,STDCALL_NONE
        .return
    .case '1tz'             ; -zt1
        mov Options.stdcall_decoration,STDCALL_HALF
        .return
    .case '2tz'             ; -zt2
        mov Options.stdcall_decoration,STDCALL_FULL
        .return
ifndef ASMC64
    .case '8vZ'             ; -Zv8
        mov Options.masm8_proc_visibility,1
        .return
endif
    .case 'ezz'             ; -zze
        mov Options.no_export_decoration,1
        .return
    .case 'szz'             ; -zzs
        mov Options.entry_decorated,1
        .return
    .endsw

    mov [rsi],rbx
    mov eax,[rbx]
    .if al == 'e'           ; -e<number>
        mov [rsi],GetNumber(&[rbx+1])
        mov Options.error_limit,OptValue
        .return
    .endif
    .if al == 'W'           ; -W<number>
        mov [rsi],GetNumber(&[rbx+1])
        .if OptValue < 0
            asmerr(8000, rbx)
        .elseif OptValue > 3
            asmerr(4008, rbx)
        .else
            mov Options.warning_level,OptValue
        .endif
        .return
    .endif

    and eax,0xFFFF
    mov j,eax
    mov [rsi],GetNumber(&[rbx+2])
    .switch j
    .case 'sw'          ; -ws<number>
        mov Options.codepage,OptValue
        mov Options.wstring,1
        define_name( "_UNICODE", "1" )
        .return
    .case 'pS'          ; -Zp<number>
        xor ecx,ecx
        .repeat
            mov eax,1
            shl eax,cl
            inc ecx
            .if ( eax > MAX_SEGMENT_ALIGN )
                asmerr(1006, rbx)
            .endif
        .until eax == OptValue
        dec ecx
        mov Options.segmentalign,cl
        .return
    .case 'pZ'          ; -Zp<number>
        xor ecx,ecx
        .repeat
            mov eax,1
            shl eax,cl
            inc ecx
            .if ( eax > MAX_STRUCT_ALIGN )
                asmerr(1006, rbx)
            .endif
        .until ( eax == OptValue )
        dec ecx
        mov Options.fieldalign,cl
       .return
    .case 'iZ'          ; -Zi[0|1|2|3]
        define_name( "__DEBUG__", "1" )
        mov Options.line_numbers,1
        mov Options.debug_symbols,4 ; C13 (vc7.x) zero terminated names
        mov Options.no_file_entry,1
        mov Options.debug_ext,CVEX_NORMAL
        mov eax,OptValue
        .if eax
            .if eax > CVEX_MAX
                .if byte ptr [rbx+3] != 0
                    .if ( byte ptr [rbx+4] != 0 )
                        asmerr( 1006, rbx )
                    .endif
                    movzx eax,word ptr [rbx+2]
                    sub eax,'00'
                    mov Options.debug_ext,al
                    shr eax,8
                .endif
                mov Options.no_file_entry,0
                mov Options.debug_symbols,1 ; CV4
                .if ( eax == 5 )
                    mov Options.debug_symbols,2 ; C11 (vc5.x) 32-bit types
                .elseif ( eax != 4 )
                    asmerr( 1006, rbx )
                .endif
            .else
                mov Options.debug_ext,al
            .endif
        .endif
        .return
    .endsw

    mov [rsi],GetNameToken( rdi, &[rbx+2], 256, '$' )
    mov eax,j
    .switch eax
    .case 'cn'          ; -nc<name>
        .return set_option_n_name(OPTN_CODE_CLASS, rdi)
    .case 'dn'          ; -nd<name>
        .return set_option_n_name(OPTN_DATA_SEG, rdi)
    .case 'mn'          ; -nm<name>
        .return set_option_n_name(OPTN_MODULE_NAME, rdi)
    .case 'tn'          ; -nt<name>
        .return set_option_n_name(OPTN_TEXT_SEG, rdi)
    .endsw

    mov [rsi],GetNameToken( rdi, &[rbx+2], 256, '@' )
    mov eax,j
    .switch eax
    .case 'dF'          ; -Fd[file]
        mov Options.write_impdef,1
        .return get_fname(OPTN_LNKDEF_FN, rdi)
    .case 'lF'          ; -Fl[file]
        mov Options.write_listing,1
        .return get_fname(OPTN_LST_FN, rdi)
    .endsw

    .if getfilearg(cmdline, &[rbx+2])

        mov [rsi],GetNameToken( rdi, rax, 256, '@' )
        mov eax,j
        .if eax == 'lB'         ; -Bl<file>
            mov Options.link_linker,MemDup(rdi)
           .return
        .endif
        .if eax == 'eF'         ; -Fe<file>
            mov Options.link_exename,MemDup(rdi)
           .return
        .endif
        .if eax == 'iF'         ; -Fi<file>
            .return queue_item(OPTQ_FINCLUDE, rdi)
        .endif
        .if eax == 'oF'         ; -Fo<file>
            .return get_fname(OPTN_OBJ_FN, rdi)
        .endif
        .if eax == 'wF'         ; -Fw<file>
            .return get_fname(OPTN_ERR_FN, rdi)
        .endif
    .endif
    asmerr( 1006, &[rbx-1] )
    ret

ProcessOption endp


    option proc:public

ParseCmdline proc __ccall uses rsi rdi rbx cmdline:ptr string_t, numargs:ptr int_t

   .new paramfile[_MAX_PATH]:char_t

    ldr rsi,cmdline
    ldr rdi,numargs

    .for ( ebx = 0 : ebx < NUM_FILE_TYPES : ebx++ )

        lea rdx,Options
        mov rcx,[rdx].global_options.names[rbx*string_t]
        .if rcx
            mov [rdx].global_options.names[rbx*string_t],NULL
            MemFree(rcx)
        .endif
    .endf

    mov rbx,[rsi]

    .for( : rbx : )

        mov eax,[rbx]
        .switch al
        .case 13
        .case 10
        .case 9
        .case ' '
            inc rbx
            .endc
        .case 0
            mov rbx,getnextcmdstring(rsi)
            .endc
        .case '@'
            inc rbx
            mov [rsi],GetNameToken(&paramfile, rbx, sizeof(paramfile)-1, '@')
            xor ebx,ebx
            .if paramfile[0]
                mov rbx,tgetenv(&paramfile)
            .endif
            .if !rbx
                mov rbx,ReadParamFile(&paramfile)
            .endif
            .endc

        .case '-'
ifndef __UNIX__
        .case '/'
endif
ifdef _EXEC_LINK
            .if ( !Options.link )
endif
                inc rbx
                mov [rsi],rbx
                ProcessOption(rsi, &paramfile)
                inc dword ptr [rdi]
                mov rbx,[rsi]
               .endc
ifdef _EXEC_LINK
            .endif
endif
        .default ; collect file name
            mov rbx,GetNameToken(&paramfile, rbx, sizeof(paramfile) - 1, '@')
            mov [rsi],rbx
ifdef _EXEC_LINK
            .if ( Options.link )
                CollectLinkOption( &paramfile )
            .else
endif
                mov Options.names[TASM],MemDup(&paramfile)
                inc dword ptr [rdi]
               .return
ifdef _EXEC_LINK
            .endif
endif
        .endsw
    .endf
    mov [rsi],rbx
   .return(NULL)

ParseCmdline endp


CmdlineFini proc __ccall uses rsi rsi rbx

  local q:ptr qitem
  local x:ptr qitem
  local p:ptr char_t

    xor ebx,ebx
    lea rsi,DefaultDir
    lea rdi,Options

    .while ( ebx < NUM_FILE_TYPES )

        xor eax,eax
        mov rcx,[rsi+rbx*string_t]
        mov [rsi+rbx*string_t],rax
        mov [rdi].global_options.names[rbx*string_t],rax
        MemFree(rcx)
        inc ebx
    .endw

    xor ebx,ebx
    .while ebx < OPTQ_LAST

        lea rdx,Options
        mov rdi,[rdx].global_options.queues[rbx*string_t]
        .while rdi
            mov rsi,[rdi].qitem.next
            MemFree(rdi)
            mov rdi,rsi
        .endw
        lea rdx,Options
        mov [rdx].global_options.queues[rbx*string_t],NULL
        inc ebx
    .endw
    ret

CmdlineFini endp

    end
