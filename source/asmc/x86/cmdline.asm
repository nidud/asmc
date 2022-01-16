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

define_name proto :string_t, :string_t

    .data

     B equ <byte ptr>

ifdef ASMC64

ifdef __UNIX__

Options global_options {
        0,                      ; .quiet
        0,                      ; .line_numbers
        0,                      ; .debug_symbols
        0,                      ; .debug_ext
        FPO_NO_EMULATION,       ; .floating_point
        50,                     ; .error_limit
        0,                      ; .no_error_disp
        2,                      ; .warning_level
        0,                      ; .warning_error
        0,                      ; .process_subdir
        {0,0,0,0,0,0,0,0,0},    ; .names
        {0,0,0},                ; .queues
        0,                      ; .no_comment_in_code_rec
        0,                      ; .no_opt_farcall
        0,                      ; .no_file_entry
        0,                      ; .no_static_procs
        0,                      ; .no_section_aux_entry
        0,                      ; .no_cdecl_decoration
        STDCALL_FULL,           ; .stdcall_decoration
        0,                      ; .no_export_decoration
        0,                      ; .entry_decorated
        0,                      ; .write_listing
        0,                      ; .write_impdef
        0,                      ; .case_sensitive
        0,                      ; .convert_uppercase
        0,                      ; .preprocessor_stdout
        0,                      ; .masm51_compat
        0,                      ; .strict_masm_compat
        0,                      ; .masm_compat_gencode
        0,                      ; .masm8_proc_visibility
        0,                      ; .listif
        0,                      ; .list_generated_code
        LM_LISTMACRO,           ; .list_macro
        0,                      ; .do_symbol_listing
        0,                      ; .first_pass_listing
        0,                      ; .all_symbols_public
        0,                      ; .safeseh
        OFORMAT_ELF,            ; .output_format
        SFORMAT_64BIT,          ; .sub_format
        LANG_SYSCALL,           ; .langtype
        MODEL_FLAT,             ; ._model
        P_64 or P_PM,           ; .cpu
        FCT_ELF64,              ; .fctype
        0,                      ; .codepage
        0,                      ; .ignore_include
        0,                      ; .fieldalign
        0,                      ; .syntax_check_only
        OPT_REGAX,              ; .xflag
        0,                      ; .loopalign
        0,                      ; .casealign
        0,                      ; .epilogueflags
        4,                      ; .segmentalign
        0,                      ; .pe_subsystem
        0,                      ; .win64_flags
        0,                      ; .chkstack
        0,                      ; .nolib
        0,                      ; .masm_keywords
        0,                      ; .arch
        0,                      ; .frame_auto
        0,                      ; .floatformat
        1,                      ; .floatdigits
        4 }                     ; .flt_size

else

Options global_options {
        0,                      ; .quiet
        0,                      ; .line_numbers
        0,                      ; .debug_symbols
        0,                      ; .debug_ext
        FPO_NO_EMULATION,       ; .floating_point
        50,                     ; .error_limit
        0,                      ; .no_error_disp
        2,                      ; .warning_level
        0,                      ; .warning_error
        0,                      ; .process_subdir
        {0,0,0,0,0,0,0,0,0},    ; .names
        {0,0,0},                ; .queues
        0,                      ; .no_comment_in_code_rec
        0,                      ; .no_opt_farcall
        0,                      ; .no_file_entry
        0,                      ; .no_static_procs
        0,                      ; .no_section_aux_entry
        0,                      ; .no_cdecl_decoration
        STDCALL_FULL,           ; .stdcall_decoration
        0,                      ; .no_export_decoration
        0,                      ; .entry_decorated
        0,                      ; .write_listing
        0,                      ; .write_impdef
        0,                      ; .case_sensitive
        0,                      ; .convert_uppercase
        0,                      ; .preprocessor_stdout
        0,                      ; .masm51_compat
        0,                      ; .strict_masm_compat
        0,                      ; .masm_compat_gencode
        0,                      ; .masm8_proc_visibility
        0,                      ; .listif
        0,                      ; .list_generated_code
        LM_LISTMACRO,           ; .list_macro
        0,                      ; .do_symbol_listing
        0,                      ; .first_pass_listing
        0,                      ; .all_symbols_public
        0,                      ; .safeseh
        OFORMAT_COFF,           ; .output_format
        SFORMAT_64BIT,          ; .sub_format
        LANG_FASTCALL,          ; .langtype
        MODEL_FLAT,             ; ._model
        P_64 or P_PM,           ; .cpu
        FCT_WIN64,              ; .fctype
        0,                      ; .codepage
        0,                      ; .ignore_include
        0,                      ; .fieldalign
        0,                      ; .syntax_check_only
        OPT_REGAX,              ; .xflag
        0,                      ; .loopalign
        0,                      ; .casealign
        0,                      ; .epilogueflags
        4,                      ; .segmentalign
        0,                      ; .pe_subsystem
        0,                      ; .win64_flags
        0,                      ; .chkstack
        0,                      ; .nolib
        0,                      ; .masm_keywords
        0,                      ; .arch
        0,                      ; .frame_auto
        0,                      ; .floatformat
        1,                      ; .floatdigits
        4 }                     ; .flt_size

endif

else

Options global_options {
        0,                      ; .quiet
        0,                      ; .line_numbers
        0,                      ; .debug_symbols
        0,                      ; .debug_ext
        FPO_NO_EMULATION,       ; .floating_point
        50,                     ; .error_limit
        0,                      ; .no_error_disp
        2,                      ; .warning_level
        0,                      ; .warning_error
        0,                      ; .process_subdir
        {0,0,0,0,0,0,0,0,0},    ; .names
        {0,0,0},                ; .queues
        0,                      ; .no_comment_in_code_rec
        0,                      ; .no_opt_farcall
        0,                      ; .no_file_entry
        0,                      ; .no_static_procs
        0,                      ; .no_section_aux_entry
        0,                      ; .no_cdecl_decoration
        STDCALL_FULL,           ; .stdcall_decoration
        0,                      ; .no_export_decoration
        0,                      ; .entry_decorated
        0,                      ; .write_listing
        0,                      ; .write_impdef
        0,                      ; .case_sensitive
        0,                      ; .convert_uppercase
        0,                      ; .preprocessor_stdout
        0,                      ; .masm51_compat
        0,                      ; .strict_masm_compat
        0,                      ; .masm_compat_gencode
        0,                      ; .masm8_proc_visibility
        0,                      ; .listif
        0,                      ; .list_generated_code
        LM_LISTMACRO,           ; .list_macro
        0,                      ; .do_symbol_listing
        0,                      ; .first_pass_listing
        0,                      ; .all_symbols_public
        0,                      ; .safeseh
        OFORMAT_OMF,            ; .output_format
        SFORMAT_NONE,           ; .sub_format
        LANG_NONE,              ; .langtype
        MODEL_NONE,             ; ._model
        P_86,                   ; .cpu
        FCT_MSC,                ; .fctype
        0,                      ; .codepage
        0,                      ; .ignore_include
        0,                      ; .fieldalign
        0,                      ; .syntax_check_only
        0,                      ; .xflag
        0,                      ; .loopalign
        0,                      ; .casealign
        0,                      ; .epilogueflags
        4,                      ; .segmentalign
        0,                      ; .pe_subsystem
        0,                      ; .win64_flags
        0,                      ; .chkstack
        0,                      ; .nolib
        0,                      ; .masm_keywords
        0,                      ; .arch
        0,                      ; .frame_auto
        0,                      ; .floatformat
        1,                      ; .floatdigits
        4 }                     ; .flt_size
endif

    align 4

     DefaultDir string_t NUM_FILE_TYPES dup(NULL)
     OptValue   int_t 0

    .code

    option proc:private

; current cmdline string is done, get the next one!

getnextcmdstring proc fastcall uses esi edi cmdline:array_t

    .for ( edi = ecx,
           esi = &[edi+string_t] : string_t ptr [esi] : )
        movsd
    .endf
    movsd
    .return([ecx])

getnextcmdstring endp

GetNumber proc fastcall p:string_t

    .for( eax = 0,
          edx = 0,
          al = [ecx] : al >= '0' && al <= '9' : ecx++, al = [ecx] )

        imul edx,edx,10
        sub al,'0'
        add edx,eax
    .endf
    mov OptValue,edx
    .return ecx

GetNumber endp


getfilearg proc fastcall uses esi edi ebx args:array_t, p:string_t ; -Fo<file> or -Fo <file>

    mov esi,edx
    mov edi,ecx

    .if ( B[esi] == 0 )
        mov ebx,getnextcmdstring(edi)
        .if ( ebx != NULL )
            mov esi,ebx
        .endif
    .elseif ( B[esi] == '=' )
        inc esi
    .endif
    .if ( B[esi] == 0 )
        asmerr( 1006, [edi] )
        .return NULL
    .endif
    .return esi

getfilearg endp


;
; queue a text macro, include path or "forced" include files.
; this is called for cmdline options -D, -I and -Fi
;

queue_item proc uses esi i:int_t, string:string_t

    mov esi,MemAlloc( &[ strlen( string ) + sizeof( qitem )] )
    mov [esi].qitem.next,NULL
    strcpy( &[esi].qitem.value, string )

    mov ecx,i
    mov eax,Options.queues[ecx*4]
    .if ( eax )
        .for ( : [eax].qitem.next : eax = [eax].qitem.next )
        .endf
        mov [eax].qitem.next,esi
    .else
        mov Options.queues[ecx*4],esi
    .endif
    ret

queue_item endp


get_fname proc uses esi edi ebx type:int_t, token:string_t

  local name[_MAX_PATH]:char_t
  local default:string_t

    mov edx,token
    .if ( B[edx] == '=' )
        inc edx
    .endif
    mov esi,edx
    mov ebx,type
    mov edi,GetFNamePart(edx)
    ;
    ; If name's ending with a '\' (or '/' in Unix), it's supposed
    ; to be a directory name only.
    ;

    .if ( B[edi] == 0 )

        .if ( ebx < NUM_FILE_TYPES && B[esi] )
            .if ( DefaultDir[ebx*string_t] )
                free( DefaultDir[ebx*string_t] )
            .endif
            mov DefaultDir[ebx*string_t],strcpy(malloc(&[strlen(token)+1]), esi)
        .endif
        .return
    .endif
    mov name[0],0
    mov edx,DefaultDir[ebx*string_t]
    .if esi == edi && ebx < NUM_FILE_TYPES && edx
        strcpy(&name, edx)
    .endif
    strcat(&name, esi)

    mov eax,type
    lea edi,Options.names[eax*4]
    free([edi])
    mov [edi],malloc(&[strlen(&name)+1])
    strcpy([edi], &name)
    ret

get_fname endp


set_option_n_name proc fastcall uses esi edi idx:int_t, name:string_t

    movzx eax,B[edx]
    .if ( al != '.' )
        .if ( !is_valid_id_char( eax ) )
            xor eax,eax
        .endif
    .endif
    .if al
        mov edi,edx
        lea esi,Options.names[ecx*4]
        free( [esi] )
        mov [esi],malloc( &[strlen( edi ) + 1] )
        strcpy( [esi], edi )
    .else
        asmerr( 1006, edx )
    .endif
    ret

set_option_n_name endp


;
; A '@' was found in the cmdline. It's not an environment variable,
; so check if it is a file and, if yes, read it.
;

ReadParamFile proc fastcall uses esi edi ebx name:string_t

   .new fp:ptr FILE

    mov esi,ecx
    xor edi,edi
    mov fp,fopen(esi, "rb")

    .if eax == NULL

        asmerr(1000, esi)
        .return(NULL)
    .endif

    xor ebx,ebx
    .if fseek( fp, 0, SEEK_END ) == 0

        mov ebx,ftell( fp )
        rewind( fp )
        mov edi,MemAlloc( &[ebx+1] )
        fread( edi, 1, ebx, fp )
        mov B[edi+ebx],0
    .endif

    fclose(fp)
    .return(NULL) .if ( ebx == 0 )
    .return(edi)

ReadParamFile endp


;
; get a "name"
; type=@ : filename ( -Fd, -Fi, -Fl, -Fo, -Fw, -I )
; type=$ : (macro) identifier [=value] ( -D, -nc, -nd, -nm, -nt )
; type=0 : something else ( -0..-10 )
;

GetNameToken proc uses esi edi ebx dst:string_t, string:string_t, max:int_t, type:char_t

   .new equatefound:int_t = FALSE

    mov esi,string
    mov edi,dst

is_quote:

    mov al,[esi]
    .if al == '"'

        inc esi
        .for( : max && byte ptr [esi]: max-- )

            mov eax,[esi]
            .if al == '"'

                inc esi
                .break
            .endif

            ; handle the \"" case

            .if al == '\' && ah == '"'

                inc esi
            .endif
            movsb
        .endf
    .else

        .for( : max: max-- )

            ; v2.10: don't stop for white spaces

            mov al,[esi]
            .break .if ( al == 0 )
            .break .if ( al == 13 || al == 10 )

            ; v2.10: don't stop for white spaces if filename
            ; is expected and true cmdline is parsed

            .break .if ( ( al == ' ' || al == 9 ) && ( type != '@' ) )

            .if type == 0

                .break .if ( al == '-' || al == '/' )
            .endif

            .if ( al == '=' && type == '$' && equatefound == FALSE )

                mov equatefound,TRUE
                movsb
                mov al,[esi]

                .if (al == '"')

                    jmp is_quote
                .endif
            .endif
            movsb
        .endf
    .endif
    mov B[edi],0
    .return(esi)

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

ProcessOption proc uses esi edi ebx cmdline:ptr string_t, buffer:string_t

    local i:int_t
    local j:int_t
    local p:string_t

    mov esi,cmdline
    mov edi,buffer
    mov ebx,[esi]
    mov eax,[ebx]

ifndef ASMC64

    ; numeric option (-0, -1, ... ) handled separately since
    ; the value can be >= 10.

    .if ( al >= '0' && al <= '9' )

        mov ebx,GetNumber(ebx)

        .if ( OptValue < lengthof(cpu_option) )

            mov ebx,GetNameToken(edi, ebx, 16, 0) ; get optional 'p'
            mov [esi],ebx
            mov ecx,OptValue
            mov eax,cpu_option[ecx*4]
            and Options.cpu,not ( P_CPU_MASK or P_EXT_MASK or P_PM )
            or  Options.cpu,eax
            .if ( B[edi+1] == 'p' && Options.cpu >= P_286 )
                or Options.cpu,P_PM
            .endif
            .switch ecx
            .case 0: define_name( "__P86__", "1" )  : .endc
            .case 1: define_name( "__P186__", "1" ) : .endc
            .case 2: define_name( "__P286__", "1" ) : .endc
            .case 3: define_name( "__P386__", "1" ) : .endc
            .case 4: define_name( "__P486__", "1" ) : .endc
            .case 5: define_name( "__P586__", "1" ) : .endc
            .case 9
                define_name( "__SSE2__", "1" )
            .case 8
                define_name( "__SSE__", "1" )
            .case 7
            .case 6
                define_name( "__P686__", "1" )
                .endc
            .case 10
                define_name( "__P64__", "1" )
                .endc
            .endsw
            .return
        .endif
        mov ebx,[esi] ; v2.11: restore option pointer
    .endif
endif

    .if al == 'D' ; -D<name>[=text]

        mov [esi],GetNameToken(edi, &[ebx+1], 256, '$')
        queue_item(OPTQ_MACRO, edi)
        .return
    .endif

    .if al == 'I' ; -I<file>

        mov [esi],GetNameToken(edi, &[ebx+1], 256, '@')
        queue_item(OPTQ_INCPATH, edi)
        .return
    .endif

    mov [esi],GetNameToken(edi, ebx, 16, 0)
    mov eax,[edi]

    .if ah == 0
        and eax,0xFF
    .elseif !( eax & 0xFF0000 )
        and eax,0xFFFF
    .endif

    .switch eax
    .case 'hcra'        ; -arch:xx
        mov eax,[edi+4]
        .if al != ':' || ah == 0
            asmerr(1006, edi)
        .endif
        mov eax,[edi+5]
        xor ebx,ebx
        .switch pascal eax
        .case '5XVA':  mov ebx,5 ; AVX512
        .case '2XVA':  mov ebx,4 ; AVX2
        .case 'XVA' :  mov ebx,3 ; AVX
        .case '2ESS':  mov ebx,2 ; SSE2
        .case 'ESS' :  mov ebx,1 ; SSE
        .default
            asmerr(1006, edi)
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
    .case 'essa'            ; -assert
        or Options.xflag,OPT_ASSERT
        .return
    .case 'otua'            ; -autostack
        or Options.win64_flags,W64F_AUTOSTACKSP
        .return
    .case 'c'               ; -c
        .return
    .case 'ffoc'            ; -coff
        mov Options.output_format,OFORMAT_COFF
        mov Options.sub_format,SFORMAT_NONE
        .return
    .case 'PE'              ; -EP
        mov Options.preprocessor_stdout,1
    .case 'q'               ; -q
        mov Options.quiet,1
    .case 'olon'            ; -nologo
        mov banner_printed,1
        .return
    .case 'nib'             ; -bin
        mov Options.output_format,OFORMAT_BIN
        mov Options.sub_format,SFORMAT_NONE
        .return
    .case 'pC'              ; -Cp
        mov Options.case_sensitive,1
        mov Options.convert_uppercase,0
        .return
    .case 'sC'              ; -Cs
        or Options.xflag,OPT_CSTACK
        .return
    .case 'uC'              ; -Cu
        mov Options.case_sensitive,0
        mov Options.convert_uppercase,1
        .return
    .case 'iuc'             ; -cui - subsystem:console
        mov Options.pe_subsystem,0
        .return
    .case 'xC'              ; -Cx
        mov Options.case_sensitive,0
        mov Options.convert_uppercase,0
        .return
    .case 'qe'              ; -eq
        mov Options.no_error_disp,1
        .return
    .case '6fle'            ; -elf64
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
    .case 'orre'            ; -errorReport:
        mov ebx,[esi]
        .while B[ebx]
            inc ebx
        .endw
        mov [esi],ebx
        .return
ifndef ASMC64
    .case 'fle'             ; -elf
        mov Options.output_format,OFORMAT_ELF
        mov Options.sub_format,SFORMAT_NONE
        define_name( "_LINUX", "1" )
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
    .case 'marf'            ; -frame
        .if ( Options.output_format != OFORMAT_BIN )
            mov Options.frame_auto,3
        .endif
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
    .case 'vG'              ; -Gv
        mov Options.langtype,LANG_VECTORCALL
        .return
ifndef ASMC64
    .case 'zG'              ; -Gz
        mov Options.langtype,LANG_STDCALL
        define_name( "_STDCALL_SUPPORTED", "1" )
        .return
endif
    .case 'iug'             ; -gui - subsystem:windows
        mov Options.pe_subsystem,1
        define_name( "__GUI__", "1" )
        .return
    .case '?'
    .case 'h'
        write_options()
        exit(1)
    .case 'emoh'            ; -homeparams
        or Options.win64_flags,W64F_SAVEREGPARAMS
        .return
    .case 'ogol'            ; -logo
        tprintf("%s\n", &cp_logo)
        exit(0)
ifndef ASMC64
    .case 'zm'              ; -mz
        mov Options.output_format,OFORMAT_BIN
        mov Options.sub_format,SFORMAT_MZ
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
    .case 'ilon'            ; -nolib
        mov Options.nolib,TRUE
        define_name( "_MSVCRT", "1" )
        .return
ifndef ASMC64
    .case 'fmo'             ; -omf
        mov Options.output_format,OFORMAT_OMF
        mov Options.sub_format,SFORMAT_NONE
        .return
endif
    .case 'fp'              ; -pf
        mov Options.epilogueflags,1
        .return
    .case 'ep'              ; -pe
        .if ( Options.sub_format != SFORMAT_64BIT )
            mov Options.sub_format,SFORMAT_PE
        .endif
        mov Options.output_format,OFORMAT_BIN
        define_name( "__PE__", "1" )
        .return
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
    .case 'pws'         ; -swp
        or Options.xflag,OPT_PASCAL
        .return
    .case 'cws'         ; -swc
        and Options.xflag,not OPT_PASCAL
        .return
    .case 'rws'         ; -swr
        or Options.xflag,OPT_REGAX
        .return
    .case 'nws'         ; -swn
        or Options.xflag,OPT_NOTABLE
        .return
    .case 'tws'         ; -swt
        and Options.xflag,not OPT_NOTABLE
        .return
    .case 'efas'        ; -safeseh
        mov Options.safeseh,1
        .return
    .case 'w'           ; -w
        mov Options.warning_level,0
        .return
    .case 'sw'          ; -ws
        or Options.xflag,OPT_WSTRING
        define_name( "_UNICODE", "1" )
        .return
    .case 'XW'          ; -WX
        mov Options.warning_error,1
        .return
    .case '6niw'        ; -win64
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
    .case 'X'           ; -X
        mov Options.ignore_include,1
        .return
ifndef ASMC64
    .case 'mcz'         ; -zcm
        mov Options.no_cdecl_decoration,0
        .return
    .case 'wcz'         ; -zcw
        mov Options.no_cdecl_decoration,1
        .return
endif
    .case 'fZ'          ; -Zf
        mov Options.all_symbols_public,1
        .return
ifndef ASMC64
    .case '0fz'         ; -zf0
        mov Options.fctype,FCT_MSC
        .return
endif
    .case '1fz'         ; -zf1
        mov Options.fctype,FCT_WATCOMC
        .return
    .case 'gZ'          ; -Zg
        mov Options.masm_compat_gencode,1
        .return
    .case 'dZ'          ; -Zd
        mov Options.line_numbers,1
        .return
    .case 'clz'         ; -zlc
        mov Options.no_comment_in_code_rec,1
        .return
    .case 'dlz'         ; -zld
        mov Options.no_opt_farcall,1
        .return
    .case 'flz'         ; -zlf
        mov Options.no_file_entry,1
        .return
    .case 'plz'         ; -zlp
        mov Options.no_static_procs,1
        .return
    .case 'slz'         ; -zls
        mov Options.no_section_aux_entry,1
        .return
ifndef ASMC64
    .case 'mZ'          ; -Zm
        mov Options.masm51_compat,1
endif
    .case 'enZ'         ; -Zne
        mov Options.strict_masm_compat,1
        .return
    .case 'knZ'         ; -Znk
        mov Options.masm_keywords,1
        .return
    .case 'sZ'          ; -Zs
        mov Options.syntax_check_only,1
        .return
ifndef ASMC64
    .case '0tz'         ; -zt0
        mov Options.stdcall_decoration,0
        .return
    .case '1tz'         ; -zt1
        mov Options.stdcall_decoration,1
        .return
    .case '2tz'         ; -zt2
        mov Options.stdcall_decoration,2
        .return
    .case '8vZ'         ; -Zv8
        mov Options.masm8_proc_visibility,1
        .return
endif
    .case 'ezz'         ; -zze
        mov Options.no_export_decoration,1
        .return
    .case 'szz'         ; -zzs
        mov Options.entry_decorated,1
        .return
    .endsw

    mov [esi],ebx
    mov eax,[ebx]
    .if al == 'e'       ; -e<number>
        mov [esi],GetNumber(&[ebx+1])
        mov Options.error_limit,OptValue
        .return
    .endif
    .if al == 'W'       ; -W<number>
        mov [esi],GetNumber(&[ebx+1])
        .if OptValue < 0
            asmerr(8000, ebx)
        .elseif OptValue > 3
            asmerr(4008, ebx)
        .else
            mov Options.warning_level,OptValue
        .endif
        .return
    .endif

    and eax,0xFFFF
    mov j,eax
    mov [esi],GetNumber(&[ebx+2])
    .switch j
    .case 'sw'          ; -ws<number>
        mov Options.codepage,OptValue
        or  Options.xflag,OPT_WSTRING
        define_name( "_UNICODE", "1" )
        .return
    .case 'pS'          ; -Zp<number>
        xor ecx,ecx
        .repeat
            mov eax,1
            shl eax,cl
            inc ecx
            .if ( eax > MAX_SEGMENT_ALIGN )
                asmerr(1006, ebx)
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
                asmerr(1006, ebx)
            .endif
        .until ( eax == OptValue )
        dec ecx
        mov Options.fieldalign,cl
        .return
    .case 'iZ'          ; -Zi[0|1|2|3]
        define_name( "__DEBUG__", "1" )
        mov Options.line_numbers,1
        mov Options.debug_symbols,1
        mov Options.debug_ext,CVEX_NORMAL
        mov eax,OptValue
        .if eax
            .if eax > CVEX_MAX
                .if B[ebx+3] != 0
                    .if B[ebx+4] != 0
                        asmerr(1006, ebx)
                    .endif
                    movzx eax,B[ebx+3]
                    sub eax,'0'
                    mov Options.debug_ext,al
                .endif
                .if eax == 5
                    mov Options.debug_symbols,2 ; C11 (vc5.x) 32-bit types
                .elseif eax == 8
                    mov Options.debug_symbols,4 ; C13 (vc7.x) zero terminated names
                    mov Options.no_file_entry,1
                .else
                    asmerr(1006, ebx)
                .endif
            .else
                mov Options.debug_ext,al
            .endif
        .endif
        .return
    .endsw

    mov [esi],GetNameToken(edi, &[ebx+2], 256, '$')
    mov eax,j
    .switch eax
    .case 'cn'          ; -nc<name>
        .return set_option_n_name(OPTN_CODE_CLASS, edi)
    .case 'dn'          ; -nd<name>
        .return set_option_n_name(OPTN_DATA_SEG, edi)
    .case 'mn'          ; -nm<name>
        .return set_option_n_name(OPTN_MODULE_NAME, edi)
    .case 'tn'          ; -nt<name>
        .return set_option_n_name(OPTN_TEXT_SEG, edi)
    .endsw

    mov [esi],GetNameToken( edi, &[ebx+2], 256, '@' )
    mov eax,j
    .switch eax
    .case 'dF'          ; -Fd[file]
        mov Options.write_impdef,1
        .return get_fname(OPTN_LNKDEF_FN, edi)
    .case 'lF'          ; -Fl[file]
        mov Options.write_listing,1
        .return get_fname(OPTN_LST_FN, edi)
    .endsw

    .if getfilearg(cmdline, &[ebx+2])
        mov ebx,eax
        mov [esi],GetNameToken(edi, ebx, 256, '@')
        mov eax,j
        .if eax == 'iF'         ; -Fi<file>
            .return queue_item(OPTQ_FINCLUDE, edi)
        .endif
        .if eax == 'oF'         ; -Fo<file>
            .return get_fname(OPTN_OBJ_FN, edi)
        .endif
        .if eax == 'wF'         ; -Fw<file>
            .return get_fname(OPTN_ERR_FN, edi)
        .endif
    .endif
    asmerr(1006, &[ebx-3])
    ret

ProcessOption endp

    option proc:public

ParseCmdline proc uses esi edi ebx cmdline:ptr string_t, numargs:ptr int_t

  local paramfile[_MAX_PATH]:char_t

    .for ( edi = 0, ebx = 0: ebx < NUM_FILE_TYPES: ebx++ )

        mov eax,Options.names[ebx*4]
        .if eax

            mov Options.names[ebx*4],edi
            MemFree(eax)
        .endif
    .endf

    mov esi,cmdline
    mov edi,numargs
    mov ebx,[esi]

    .for( : ebx : )

        mov eax,[ebx]
        .switch al
        .case 13
        .case 10
        .case 9
        .case ' '
            inc ebx
            .endc
        .case 0
            mov ebx,getnextcmdstring(esi)
            .endc
        .case '-'
ifndef __UNIX__
        .case '/'
endif
            inc ebx
            mov [esi],ebx
            ProcessOption(esi, &paramfile)
            inc dword ptr [edi]
            mov ebx,[esi]
            .endc
        .case '@'
            inc ebx
            mov [esi],GetNameToken(&paramfile, ebx, sizeof(paramfile)-1, '@')
            xor ebx,ebx
            .if paramfile[0]
                mov ebx,getenv(&paramfile)
            .endif
            .if !ebx
                mov ebx,ReadParamFile(&paramfile)
            .endif
            .endc
        .default ; collect  file name
            mov ebx,GetNameToken(&paramfile, ebx, sizeof(paramfile) - 1, '@')
            mov Options.names[ASM*4],MemAlloc(&[strlen(&paramfile)+1])
            strcpy(Options.names[ASM*4], &paramfile)
            inc dword ptr [edi]
            mov [esi],ebx
            .return(Options.names[ASM*4])
        .endsw
    .endf
    mov [esi],ebx
    .return(NULL)
ParseCmdline endp


CmdlineFini proc uses esi edi ebx

  local q:ptr qitem
  local x:ptr qitem
  local p:ptr char_t

    xor ebx,ebx
    lea esi,DefaultDir
    lea edi,Options.names

    .while ebx < NUM_FILE_TYPES

        xor eax,eax
        mov ecx,[esi+ebx*4]
        mov [esi+ebx*4],eax
        mov Options.names[ebx*4],eax
        free(ecx)
        inc ebx
    .endw

    xor ebx,ebx
    .while ebx < OPTQ_LAST

        mov edi,Options.queues[ebx*4]
        .while edi
            mov esi,[edi].qitem.next
            free(edi)
            mov edi,esi
        .endw
        mov Options.queues[ebx*4],NULL
        inc ebx
    .endw
    ret

CmdlineFini endp

    end
