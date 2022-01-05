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

define_name proto __ccall :string_t, :string_t

    .data

     B equ <byte ptr>

ifdef ASMC64

ifdef __UNIX__

Options global_options {
        0,                      ;; .quiet
        0,                      ;; .line_numbers
        0,                      ;; .debug_symbols
        0,                      ;; .debug_ext
        FPO_NO_EMULATION,       ;; .floating_point
        50,                     ;; .error_limit
        0,                      ;; .no_error_disp
        2,                      ;; .warning_level
        0,                      ;; .warning_error
        0,                      ;; .process_subdir
        {0,0,0,0,0,0,0,0,0},    ;; .names
        {0,0,0},                ;; .queues
        0,                      ;; .no_comment_in_code_rec
        0,                      ;; .no_opt_farcall
        0,                      ;; .no_file_entry
        0,                      ;; .no_static_procs
        0,                      ;; .no_section_aux_entry
        0,                      ;; .no_cdecl_decoration
        STDCALL_FULL,           ;; .stdcall_decoration
        0,                      ;; .no_export_decoration
        0,                      ;; .entry_decorated
        0,                      ;; .write_listing
        0,                      ;; .write_impdef
        0,                      ;; .case_sensitive
        0,                      ;; .convert_uppercase
        0,                      ;; .preprocessor_stdout
        0,                      ;; .masm51_compat
        0,                      ;; .strict_masm_compat
        0,                      ;; .masm_compat_gencode
        0,                      ;; .masm8_proc_visibility
        0,                      ;; .listif
        0,                      ;; .list_generated_code
        LM_LISTMACRO,           ;; .list_macro
        0,                      ;; .do_symbol_listing
        0,                      ;; .first_pass_listing
        0,                      ;; .all_symbols_public
        0,                      ;; .safeseh
        OFORMAT_ELF,            ;; .output_format
        SFORMAT_64BIT,          ;; .sub_format
        LANG_SYSCALL,           ;; .langtype
        MODEL_FLAT,             ;; ._model
        P_64 or P_PM,           ;; .cpu
        FCT_ELF64,              ;; .fctype
        0,                      ;; .codepage
        0,                      ;; .ignore_include
        0,                      ;; .fieldalign
        0,                      ;; .syntax_check_only
        OPT_REGAX,              ;; .xflag
        0,                      ;; .loopalign
        0,                      ;; .casealign
        0,                      ;; .epilogueflags
        4,                      ;; .segmentalign
        0,                      ;; .pe_subsystem
        0,                      ;; .win64_flags
        0,                      ;; .chkstack
        0,                      ;; .nolib
        0,                      ;; .masm_keywords
        0,                      ;; .arch
        0,                      ;; .frame_auto
        0,                      ;; .floatformat
        1,                      ;; .floatdigits
        4 }                     ;; .flt_size

else

Options global_options {
        0,                      ;; .quiet
        0,                      ;; .line_numbers
        0,                      ;; .debug_symbols
        0,                      ;; .debug_ext
        FPO_NO_EMULATION,       ;; .floating_point
        50,                     ;; .error_limit
        0,                      ;; .no_error_disp
        2,                      ;; .warning_level
        0,                      ;; .warning_error
        0,                      ;; .process_subdir
        {0,0,0,0,0,0,0,0,0},    ;; .names
        {0,0,0},                ;; .queues
        0,                      ;; .no_comment_in_code_rec
        0,                      ;; .no_opt_farcall
        0,                      ;; .no_file_entry
        0,                      ;; .no_static_procs
        0,                      ;; .no_section_aux_entry
        0,                      ;; .no_cdecl_decoration
        STDCALL_FULL,           ;; .stdcall_decoration
        0,                      ;; .no_export_decoration
        0,                      ;; .entry_decorated
        0,                      ;; .write_listing
        0,                      ;; .write_impdef
        0,                      ;; .case_sensitive
        0,                      ;; .convert_uppercase
        0,                      ;; .preprocessor_stdout
        0,                      ;; .masm51_compat
        0,                      ;; .strict_masm_compat
        0,                      ;; .masm_compat_gencode
        0,                      ;; .masm8_proc_visibility
        0,                      ;; .listif
        0,                      ;; .list_generated_code
        LM_LISTMACRO,           ;; .list_macro
        0,                      ;; .do_symbol_listing
        0,                      ;; .first_pass_listing
        0,                      ;; .all_symbols_public
        0,                      ;; .safeseh
        OFORMAT_COFF,           ;; .output_format
        SFORMAT_64BIT,          ;; .sub_format
        LANG_FASTCALL,          ;; .langtype
        MODEL_FLAT,             ;; ._model
        P_64 or P_PM,           ;; .cpu
        FCT_WIN64,              ;; .fctype
        0,                      ;; .codepage
        0,                      ;; .ignore_include
        0,                      ;; .fieldalign
        0,                      ;; .syntax_check_only
        OPT_REGAX,              ;; .xflag
        0,                      ;; .loopalign
        0,                      ;; .casealign
        0,                      ;; .epilogueflags
        4,                      ;; .segmentalign
        0,                      ;; .pe_subsystem
        0,                      ;; .win64_flags
        0,                      ;; .chkstack
        0,                      ;; .nolib
        0,                      ;; .masm_keywords
        0,                      ;; .arch
        0,                      ;; .frame_auto
        0,                      ;; .floatformat
        1,                      ;; .floatdigits
        4 }                     ;; .flt_size

endif

else

Options global_options {
        0,                      ;; .quiet
        0,                      ;; .line_numbers
        0,                      ;; .debug_symbols
        0,                      ;; .debug_ext
        FPO_NO_EMULATION,       ;; .floating_point
        50,                     ;; .error_limit
        0,                      ;; .no_error_disp
        2,                      ;; .warning_level
        0,                      ;; .warning_error
        0,                      ;; .process_subdir
        {0,0,0,0,0,0,0,0,0},    ;; .names
        {0,0,0},                ;; .queues
        0,                      ;; .no_comment_in_code_rec
        0,                      ;; .no_opt_farcall
        0,                      ;; .no_file_entry
        0,                      ;; .no_static_procs
        0,                      ;; .no_section_aux_entry
        0,                      ;; .no_cdecl_decoration
        STDCALL_FULL,           ;; .stdcall_decoration
        0,                      ;; .no_export_decoration
        0,                      ;; .entry_decorated
        0,                      ;; .write_listing
        0,                      ;; .write_impdef
        0,                      ;; .case_sensitive
        0,                      ;; .convert_uppercase
        0,                      ;; .preprocessor_stdout
        0,                      ;; .masm51_compat
        0,                      ;; .strict_masm_compat
        0,                      ;; .masm_compat_gencode
        0,                      ;; .masm8_proc_visibility
        0,                      ;; .listif
        0,                      ;; .list_generated_code
        LM_LISTMACRO,           ;; .list_macro
        0,                      ;; .do_symbol_listing
        0,                      ;; .first_pass_listing
        0,                      ;; .all_symbols_public
        0,                      ;; .safeseh
        OFORMAT_OMF,            ;; .output_format
        SFORMAT_NONE,           ;; .sub_format
        LANG_NONE,              ;; .langtype
        MODEL_NONE,             ;; ._model
        P_86,                   ;; .cpu
        FCT_MSC,                ;; .fctype
        0,                      ;; .codepage
        0,                      ;; .ignore_include
        0,                      ;; .fieldalign
        0,                      ;; .syntax_check_only
        0,                      ;; .xflag
        0,                      ;; .loopalign
        0,                      ;; .casealign
        0,                      ;; .epilogueflags
        4,                      ;; .segmentalign
        0,                      ;; .pe_subsystem
        0,                      ;; .win64_flags
        0,                      ;; .chkstack
        0,                      ;; .nolib
        0,                      ;; .masm_keywords
        0,                      ;; .arch
        0,                      ;; .frame_auto
        0,                      ;; .floatformat
        1,                      ;; .floatdigits
        4 }                     ;; .flt_size
endif

    align 4

     DefaultDir string_t NUM_FILE_TYPES dup(NULL)
     OptValue   int_t 0

    .code

    option proc:private

;; current cmdline string is done, get the next one!

getnextcmdstring proc fastcall uses rsi rdi cmdline:array_t

    .for ( rdi = rcx,
           rsi = &[rdi+string_t] : string_t ptr [rsi] : )
        movsq
    .endf
    movsq
    .return([rcx])

getnextcmdstring endp

GetNumber proc fastcall p:string_t

    .for( eax = 0,
          edx = 0,
          al = [rcx] : al >= '0' && al <= '9' : rcx++, al = [rcx] )

        imul edx,edx,10
        sub al,'0'
        add edx,eax
    .endf
    mov OptValue,edx
   .return rcx

GetNumber endp


getfilearg proc fastcall uses rsi rdi rbx args:array_t, p:string_t ;; -Fo<file> or -Fo <file>

    mov rsi,rdx
    mov rdi,rcx

    .if ( B[rsi] == 0 )
        mov rbx,getnextcmdstring(rdi)
        .if ( rbx != NULL )
            mov rsi,rbx
        .endif
    .elseif ( B[rsi] == '=' )
        inc rsi
    .endif
    .if ( B[rsi] == 0 )
        asmerr( 1006, [rdi] )
        .return NULL
    .endif
    .return rsi

getfilearg endp


;;
;; queue a text macro, include path or "forced" include files.
;; this is called for cmdline options -D, -I and -Fi
;;

queue_item proc __ccall uses rsi i:int_t, string:string_t

    mov rsi,MemAlloc( &[ tstrlen( string ) + sizeof( qitem )] )
    mov [rsi].qitem.next,NULL
    tstrcpy( &[rsi].qitem.value, string )

    mov ecx,i
    lea rdx,Options
    mov rax,[rdx].global_options.queues[rcx*8]
    .if ( rax )
        .for ( : [rax].qitem.next : rax = [rax].qitem.next )
        .endf
        mov [rax].qitem.next,rsi
    .else
        mov [rdx].global_options.queues[rcx*8],rsi
    .endif
    ret

queue_item endp


get_fname proc __ccall uses rsi rdi rbx r12 type:int_t, token:string_t

  local name[_MAX_PATH]:char_t
  local default:string_t

    .if ( B[rdx] == '=' )
        inc rdx
    .endif
    mov rsi,rdx
    mov ebx,ecx
    mov rdi,GetFNamePart(rdx)
    ;
    ; If name's ending with a '\' (or '/' in Unix), it's supposed
    ; to be a directory name only.
    ;
    lea r12,DefaultDir
    .if ( B[rdi] == 0 )

        .if ( rbx < NUM_FILE_TYPES && B[rsi] )

            mov rcx,[r12+rbx*string_t]
            .if ( rcx )
                MemFree(rcx)
            .endif
            mov [r12+rbx*string_t],tstrcpy(MemAlloc(&[tstrlen(token)+1]), rsi)
        .endif
        .return
    .endif
    mov name[0],0
    mov rdx,[r12+rbx*string_t]
    .if rsi == rdi && ebx < NUM_FILE_TYPES && rdx
        tstrcpy(&name, rdx)
    .endif
    tstrcat(&name, rsi)

    mov eax,type
    lea rdx,Options
    lea rdi,[rdx].global_options.names[rax*8]
    MemFree([rdi])
    mov [rdi],MemAlloc(&[tstrlen(&name)+1])
    tstrcpy([rdi], &name)
    ret

get_fname endp


set_option_n_name proc fastcall uses rsi rdi idx:int_t, name:string_t

    movzx eax,B[rdx]
    .if ( al != '.' )
        .if ( !is_valid_id_char( eax ) )
            xor eax,eax
        .endif
    .endif
    .if al
        mov rdi,rdx
        lea rax,Options
        lea rdi,[rax].global_options.names[rcx*8]
        MemFree( [rsi] )
        mov [rsi],MemAlloc( &[tstrlen( rdi ) + 1] )
        tstrcpy( [rsi], rdi )
    .else
        asmerr( 1006, rdx )
    .endif
    ret

set_option_n_name endp


;;
;; A '@' was found in the cmdline. It's not an environment variable,
;; so check if it is a file and, if yes, read it.
;;

ifdef __UNIX__
ReadParamFile proc fastcall uses rsi rdi rbx r12 r13 name:string_t
else
ReadParamFile proc fastcall uses rbx r12 r13 name:string_t
endif
   .new fp:ptr FILE

    mov r12,rcx
    xor r13,r13
    mov fp,fopen(r12, "rb")

    .if eax == NULL

        asmerr(1000, r12)
        .return(NULL)
    .endif

    xor ebx,ebx
    .if fseek( fp, 0, SEEK_END ) == 0

        mov rbx,ftell( fp )
        rewind( fp )
        mov r13,MemAlloc( &[rbx+1] )
        fread( r13, 1, ebx, fp )
        mov B[r13+rbx],0
    .endif

    fclose(fp)
   .return(NULL) .if ( ebx == 0 )
   .return(r13)

ReadParamFile endp


;
; get a "name"
; type=@ : filename ( -Fd, -Fi, -Fl, -Fo, -Fw, -I )
; type=$ : (macro) identifier [=value] ( -D, -nc, -nd, -nm, -nt )
; type=0 : something else ( -0..-10 )
;

GetNameToken proc __ccall uses rsi rdi rbx dst:string_t, string:string_t, max:int_t, type:char_t

   .new equatefound:int_t = FALSE

    mov rsi,string
    mov rdi,dst

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

            ;; handle the \"" case

            .if al == '\' && ah == '"'

                inc rsi
            .endif
            movsb
        .endf
    .else

        .for( : max: max-- )

            ;; v2.10: don't stop for white spaces

            mov al,[rsi]
            .break .if ( al == 0 )
            .break .if ( al == 13 || al == 10 )

            ;; v2.10: don't stop for white spaces if filename
            ;; is expected and true cmdline is parsed

            .break .if ( ( al == ' ' || al == 9 ) && ( type != '@' ) )

            .if type == 0

                .break .if ( al == '-' || al == '/' )
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
    mov B[rdi],0
    .return(rsi)

GetNameToken endp

ifndef ASMC64

; array for options -0..10

.data
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

endif

ProcessOption proc __ccall uses rsi rdi rbx cmdline:ptr string_t, buffer:string_t

    local i:int_t
    local j:int_t
    local p:string_t

    mov rsi,cmdline
    mov rdi,buffer
    mov rbx,[rsi]
    mov eax,[rbx]

ifndef ASMC64

    ;; numeric option (-0, -1, ... ) handled separately since
    ;; the value can be >= 10.

    .if ( al >= '0' && al <= '9' )

        mov ebx,GetNumber(rbx)

        .if ( OptValue < lengthof(cpu_option) )

            mov rbx,GetNameToken(rdi, rbx, 16, 0) ;; get optional 'p'
            mov [rsi],rbx
            mov ecx,OptValue
            lea rax,cpu_option
            mov eax,[rax+rcx*8]
            and Options.cpu,not ( P_CPU_MASK or P_EXT_MASK or P_PM )
            or  Options.cpu,eax
            .if ( B[rdi+1] == 'p' && Options.cpu >= P_286 )
                or Options.cpu,P_PM
            .endif
            .return
        .endif
        mov rbx,[rsi] ;; v2.11: restore option pointer
    .endif
endif

    .if al == 'D' ;; -D<name>[=text]

        mov [rsi],GetNameToken(rdi, &[rbx+1], 256, '$')
        queue_item(OPTQ_MACRO, rdi)
       .return
    .endif

    .if al == 'I' ;; -I<file>

        mov [rsi],GetNameToken(rdi, &[rbx+1], 256, '@')
        queue_item(OPTQ_INCPATH, rdi)
       .return
    .endif

    mov [rsi],GetNameToken(rdi, rbx, 16, 0)
    mov eax,[rdi]

    .if ah == 0
        and eax,0xFF
    .elseif !( eax & 0xFF0000 )
        and eax,0xFFFF
    .endif

    .switch eax
    .case 'hcra'        ;; -arch:xx
        mov eax,[rdi+4]
        .if al != ':' || ah == 0
            asmerr(1006, rdi)
        .endif
        mov eax,[rdi+5]
        xor ebx,ebx
        .switch pascal eax
        .case '5XVA':  mov ebx,5 ; AVX512
        .case '2XVA':  mov ebx,4 ; AVX2
        .case 'XVA' :  mov ebx,3 ; AVX
        .case '2ESS':  mov ebx,2 ; SSE2
        .case 'ESS' :  mov ebx,1 ; SSE
        .default
            asmerr(1006, rdi)
        .endsw
        .switch ebx
        .case 5
            define_name( "__AVX512BW__", "1" )
            define_name( "__AVX512CD__", "1" )
            define_name( "__AVX512DQ__", "1" )
            define_name( "__AVX512F__",  "1" )
            define_name( "__AVX512VL__", "1" )
        .case 4
            define_name( "__AVX2__", "1" )
        .case 3
            define_name( "__AVX__",  "1" )
        .case 2
            define_name( "__SSE2__", "1" )
        .case 1
            define_name( "__SSE__",  "1" )
        .endsw
        mov Options.arch,bl
        .return
    .case 'essa'            ;; -assert
        or Options.xflag,OPT_ASSERT
        .return
    .case 'otua'            ;; -autostack
        or Options.win64_flags,W64F_AUTOSTACKSP
        .return
    .case 'c'               ;; -c
        .return
    .case 'ffoc'            ;; -coff
        mov Options.output_format,OFORMAT_COFF
        mov Options.sub_format,SFORMAT_NONE
        .return
    .case 'PE'              ;; -EP
        mov Options.preprocessor_stdout,1
    .case 'q'               ;; -q
        mov Options.quiet,1
    .case 'olon'            ;; -nologo
        mov banner_printed,1
        .return
    .case 'nib'             ;; -bin
        mov Options.output_format,OFORMAT_BIN
        mov Options.sub_format,SFORMAT_NONE
        .return
    .case 'pC'              ;; -Cp
        mov Options.case_sensitive,1
        mov Options.convert_uppercase,0
        .return
    .case 'sC'              ;; -Cs
        or Options.xflag,OPT_CSTACK
        .return
    .case 'uC'              ;; -Cu
        mov Options.case_sensitive,0
        mov Options.convert_uppercase,1
        .return
    .case 'iuc'             ;; -cui - subsystem:console
        mov Options.pe_subsystem,0
        .return
    .case 'xC'              ;; -Cx
        mov Options.case_sensitive,0
        mov Options.convert_uppercase,0
        .return
    .case 'qe'              ;; -eq
        mov Options.no_error_disp,1
        .return
    .case '6fle'            ;; -elf64
if defined(ASMC64) and defined(__UNIX__)
else
        or  Options.xflag,OPT_REGAX
        mov Options.output_format,OFORMAT_ELF
        define_name( "_LINUX",   "2" )
        define_name( "__UNIX__", "1" )
ifndef ASMC64
        define_name( "_WIN64",   "1" )
        mov Options.sub_format,SFORMAT_64BIT
else
        mov Options.langtype,LANG_SYSCALL
        mov Options.fctype,FCT_ELF64
endif
endif
        .return
    .case 'orre'            ;; -errorReport:
        mov rbx,[rsi]
        .while B[rbx]
            inc rbx
        .endw
        mov [rsi],rbx
        .return
ifndef ASMC64
    .case 'fle'             ;; -elf
        mov Options.output_format,OFORMAT_ELF
        mov Options.sub_format,SFORMAT_NONE
        define_name( "_LINUX", "1" )
        define_name( "__UNIX__", "1" )
        .return
    .case '8iPF'            ;; -FPi87
        mov Options.floating_point,FPO_NO_EMULATION
        .return
    .case 'iPF'             ;; -Fpi
        mov Options.floating_point,FPO_EMULATION
        .return
    .case '0pf'             ;; -fp0
        mov Options.cpu,P_87
        .return
    .case '2pf'             ;; -fp2
        mov Options.cpu,P_287
        .return
    .case '3pf'             ;; -fp3
        mov Options.cpu,P_387
        .return
    .case 'cpf'             ;; -fpc
        mov Options.cpu,P_NO87
        .return
endif
    .case 'marf'            ;; -frame
        .if ( Options.output_format != OFORMAT_BIN )
            mov Options.frame_auto,3
        .endif
        .return

ifndef ASMC64
    .case 'cG'              ;; -Gc
        mov Options.langtype,LANG_PASCAL
        .return
    .case 'dG'              ;; -Gd
        mov Options.langtype,LANG_C
        .return
endif
    .case 'eG'              ;; -Ge
        mov Options.chkstack,1
        .return
    .case 'rG'              ;; -Gr
        mov Options.langtype,LANG_FASTCALL
        .return
    .case 'vG'              ;; -Gv
        mov Options.langtype,LANG_VECTORCALL
        .return
ifndef ASMC64
    .case 'zG'              ;; -Gz
        mov Options.langtype,LANG_STDCALL
        define_name( "_STDCALL_SUPPORTED", "1" )
        .return
endif
    .case 'iug'             ;; -gui - subsystem:windows
        mov Options.pe_subsystem,1
        define_name( "__GUI__", "1" )
        .return
    .case '?'
    .case 'h'
        write_options()
        exit(1)
    .case 'emoh'            ;; -homeparams
        or Options.win64_flags,W64F_SAVEREGPARAMS
        .return
    .case 'ogol'            ;; -logo
        tprintf("%s\n", &cp_logo)
        exit(0)
ifndef ASMC64
    .case 'zm'              ;; -mz
        mov Options.output_format,OFORMAT_BIN
        mov Options.sub_format,SFORMAT_MZ
        .return
    .case 'cm'              ;; -mc
        mov Options._model,MODEL_COMPACT
        .return
    .case 'fm'              ;; -mf
        mov Options._model,MODEL_FLAT
        .return
    .case 'hm'              ;; -mh
        mov Options._model,MODEL_HUGE
        .return
    .case 'lm'              ;; -ml
        mov Options._model,MODEL_LARGE
        .return
    .case 'mm'              ;; -mm
        mov Options._model,MODEL_MEDIUM
        .return
    .case 'sm'              ;; -ms
        mov Options._model,MODEL_SMALL
        .return
    .case 'tm'              ;; -mt
        mov Options._model,MODEL_TINY
        .return
endif
    .case 'ilon'            ;; -nolib
        mov Options.nolib,TRUE
        define_name( "_MSVCRT", "1" )
        .return
ifndef ASMC64
    .case 'fmo'             ;; -omf
        mov Options.output_format,OFORMAT_OMF
        mov Options.sub_format,SFORMAT_NONE
        .return
endif
    .case 'fp'              ;; -pf
        mov Options.epilogueflags,1
        .return
    .case 'ep'              ;; -pe
        .if ( Options.sub_format != SFORMAT_64BIT )
            mov Options.sub_format,SFORMAT_PE
        .endif
        mov Options.output_format,OFORMAT_BIN
        define_name( "__PE__", "1" )
        .return
    .case 'r'               ;; -r
        mov Options.process_subdir,1
        .return
    .case 'aS'              ;; -Sa
        .return
    .case 'fS'              ;; -Sf
        mov Options.first_pass_listing,1
        .return
    .case 'gS'              ;; -Sg
        mov Options.list_generated_code,1
        .return
    .case 'nS'              ;; -Sn
        mov Options.no_symbol_listing,1
        .return
    .case 'cats'            ;; -stackalign
        or Options.win64_flags,W64F_STACKALIGN16
        .return
    .case 'xS'              ;; -Sx
        mov Options.listif,1
        .return
    .case 'pws'         ;; -swp
        or Options.xflag,OPT_PASCAL
        .return
    .case 'cws'         ;; -swc
        and Options.xflag,not OPT_PASCAL
        .return
    .case 'rws'         ;; -swr
        or Options.xflag,OPT_REGAX
        .return
    .case 'nws'         ;; -swn
        or Options.xflag,OPT_NOTABLE
        .return
    .case 'tws'         ;; -swt
        and Options.xflag,not OPT_NOTABLE
        .return
    .case 'efas'        ;; -safeseh
        mov Options.safeseh,1
        .return
    .case 'w'           ;; -w
        mov Options.warning_level,0
        .return
    .case 'sw'          ;; -ws
        or Options.xflag,OPT_WSTRING
        define_name( "_UNICODE", "1" )
        .return
    .case 'XW'          ;; -WX
        mov Options.warning_error,1
        .return
    .case '6niw'        ;; -win64
ifndef ASMC64
        .if ( Options.output_format != OFORMAT_BIN )
            mov Options.output_format,OFORMAT_COFF
        .else
            mov Options._model,MODEL_FLAT
            .if Options.langtype != LANG_VECTORCALL
                mov Options.langtype,LANG_FASTCALL
            .endif
        .endif
        mov Options.sub_format,SFORMAT_64BIT
        define_name( "_WIN64", "1" )
        or  Options.xflag,OPT_REGAX
endif
        .return
    .case 'X'           ;; -X
        mov Options.ignore_include,1
        .return
ifndef ASMC64
    .case 'mcz'         ;; -zcm
        mov Options.no_cdecl_decoration,0
        .return
    .case 'wcz'         ;; -zcw
        mov Options.no_cdecl_decoration,1
        .return
endif
    .case 'fZ'          ;; -Zf
        mov Options.all_symbols_public,1
        .return
ifndef ASMC64
    .case '0fz'         ;; -zf0
        mov Options.fctype,FCT_MSC
        .return
endif
    .case '1fz'         ;; -zf1
        mov Options.fctype,FCT_WATCOMC
        .return
    .case 'gZ'          ;; -Zg
        mov Options.masm_compat_gencode,1
        .return
    .case 'dZ'          ;; -Zd
        mov Options.line_numbers,1
        .return
    .case 'clz'         ;; -zlc
        mov Options.no_comment_in_code_rec,1
        .return
    .case 'dlz'         ;; -zld
        mov Options.no_opt_farcall,1
        .return
    .case 'flz'         ;; -zlf
        mov Options.no_file_entry,1
        .return
    .case 'plz'         ;; -zlp
        mov Options.no_static_procs,1
        .return
    .case 'slz'         ;; -zls
        mov Options.no_section_aux_entry,1
        .return
ifndef ASMC64
    .case 'mZ'          ;; -Zm
        mov Options.masm51_compat,1
endif
    .case 'enZ'         ;; -Zne
        mov Options.strict_masm_compat,1
        .return
    .case 'knZ'         ;; -Znk
        mov Options.masm_keywords,1
        .return
    .case 'sZ'          ;; -Zs
        mov Options.syntax_check_only,1
        .return
ifndef ASMC64
    .case '0tz'         ;; -zt0
        mov Options.stdcall_decoration,0
        .return
    .case '1tz'         ;; -zt1
        mov Options.stdcall_decoration,1
        .return
    .case '2tz'         ;; -zt2
        mov Options.stdcall_decoration,2
        .return
    .case '8vZ'         ;; -Zv8
        mov Options.masm8_proc_visibility,1
        .return
endif
    .case 'ezz'         ;; -zze
        mov Options.no_export_decoration,1
        .return
    .case 'szz'         ;; -zzs
        mov Options.entry_decorated,1
        .return
    .endsw

    mov [rsi],rbx
    mov eax,[rbx]
    .if al == 'e'       ;; -e<number>
        mov [rsi],GetNumber(&[rbx+1])
        mov Options.error_limit,OptValue
        .return
    .endif
    .if al == 'W'       ;; -W<number>
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
    .case 'sw'          ;; -ws<number>
        mov Options.codepage,OptValue
        or  Options.xflag,OPT_WSTRING
        define_name( "_UNICODE", "1" )
        .return
    .case 'pS'          ;; -Zp<number>
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
    .case 'pZ'          ;; -Zp<number>
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
    .case 'iZ'          ;; -Zi[0|1|2|3]
        define_name( "__DEBUG__", "1" )
        mov Options.line_numbers,1
        mov Options.debug_symbols,1
        mov Options.debug_ext,CVEX_NORMAL
        mov eax,OptValue
        .if eax
            .if eax > CVEX_MAX
                .if B[rbx+3] != 0
                    .if B[rbx+4] != 0
                        asmerr(1006, rbx)
                    .endif
                    movzx eax,B[rbx+3]
                    sub eax,'0'
                    mov Options.debug_ext,al
                .endif
                .if eax == 5
                    mov Options.debug_symbols,2 ;; C11 (vc5.x) 32-bit types
                .elseif eax == 8
                    mov Options.debug_symbols,4 ;; C13 (vc7.x) zero terminated names
                    mov Options.no_file_entry,1
                .else
                    asmerr(1006, rbx)
                .endif
            .else
                mov Options.debug_ext,al
            .endif
        .endif
        .return
    .endsw

    mov [rsi],GetNameToken(rdi, &[rbx+2], 256, '$')
    mov eax,j
    .switch eax
    .case 'cn'          ;; -nc<name>
        .return set_option_n_name(OPTN_CODE_CLASS, rdi)
    .case 'dn'          ;; -nd<name>
        .return set_option_n_name(OPTN_DATA_SEG, rdi)
    .case 'mn'          ;; -nm<name>
        .return set_option_n_name(OPTN_MODULE_NAME, rdi)
    .case 'tn'          ;; -nt<name>
        .return set_option_n_name(OPTN_TEXT_SEG, rdi)
    .endsw

    mov [rsi],GetNameToken( rdi, &[rbx+2], 256, '@' )
    mov eax,j
    .switch eax
    .case 'dF'          ;; -Fd[file]
        mov Options.write_impdef,1
        .return get_fname(OPTN_LNKDEF_FN, rdi)
    .case 'lF'          ;; -Fl[file]
        mov Options.write_listing,1
        .return get_fname(OPTN_LST_FN, rdi)
    .endsw

    .if getfilearg(cmdline, &[rbx+2])
        mov rbx,rax
        mov [rsi],GetNameToken(rdi, rbx, 256, '@')
        mov eax,j
        .if eax == 'iF'         ;; -Fi<file>
            .return queue_item(OPTQ_FINCLUDE, rdi)
        .endif
        .if eax == 'oF'         ;; -Fo<file>
            .return get_fname(OPTN_OBJ_FN, rdi)
        .endif
        .if eax == 'wF'         ;; -Fw<file>
            .return get_fname(OPTN_ERR_FN, rdi)
        .endif
    .endif
    asmerr(1006, &[rbx-3])
    ret

ProcessOption endp

    option proc:public

ParseCmdline proc __ccall uses rsi rdi rbx cmdline:ptr string_t, numargs:ptr int_t

  local paramfile[_MAX_PATH]:char_t

    .for ( edi = 0, ebx = 0: ebx < NUM_FILE_TYPES: ebx++ )

        lea rdx,Options
        mov rcx,[rdx].global_options.names[rbx*8]
        .if rcx
            mov [rdx].global_options.names[rbx*8],rdi
            MemFree(rcx)
        .endif
    .endf

    mov rsi,cmdline
    mov rdi,numargs
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
        .case '-'
ifndef __UNIX__
        .case '/'
endif
            inc rbx
            mov [rsi],rbx
            ProcessOption(rsi, &paramfile)
            inc dword ptr [rdi]
            mov rbx,[rsi]
            .endc
        .case '@'
            inc rbx
            mov [rsi],GetNameToken(&paramfile, rbx, sizeof(paramfile)-1, '@')
            xor ebx,ebx
            .if paramfile[0]
ifdef __UNIX__
                push rsi
                push rdi
endif
                mov rbx,getenv(&paramfile)
ifdef __UNIX__
                pop rdi
                pop rsi
endif
            .endif
            .if !rbx
                mov rbx,ReadParamFile(&paramfile)
            .endif
            .endc
        .default ;; collect  file name
            mov rbx,GetNameToken(&paramfile, rbx, sizeof(paramfile) - 1, '@')
            mov Options.names[ASM*8],MemAlloc(&[tstrlen(&paramfile)+1])
            tstrcpy(Options.names[ASM*8], &paramfile)
            inc dword ptr [rdi]
            mov [rsi],rbx
            .return(Options.names[ASM*8])
        .endsw
    .endf
    mov [rsi],rbx
   .return(NULL)

ParseCmdline endp


CmdlineFini proc __ccall uses r12 r13 rbx

  local q:ptr qitem
  local x:ptr qitem
  local p:ptr char_t

    xor ebx,ebx
    lea r12,DefaultDir
    lea r13,Options

    .while ebx < NUM_FILE_TYPES

        xor eax,eax
        mov rcx,[r12+rbx*8]
        mov [r12+rbx*8],rax
        mov [r13].global_options.names[rbx*8],rax
        free(rcx)
        inc ebx
    .endw

    xor ebx,ebx
    .while ebx < OPTQ_LAST

        lea rdx,Options
        mov r13,[rdx].global_options.queues[rbx*8]
        .while r13
            mov r12,[r13].qitem.next
            free(r13)
            mov r13,r12
        .endw
        lea rdx,Options
        mov [rdx].global_options.queues[rbx*8],NULL
        inc ebx
    .endw
    ret

CmdlineFini endp

    end
