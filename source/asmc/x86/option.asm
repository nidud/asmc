; OPTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  Processing of OPTION directive.
;
; syntax:
; OPTION option[:value][,option[:value,...]]
;

include asmc.inc
include memalloc.inc
include parser.inc
include reswords.inc
include expreval.inc
include equate.inc
include tokenize.inc
include input.inc

define MAX_LOOP_ALIGN 16
define MAX_CASE_ALIGN 16

ifndef ASMC64
extern sym_Interface:ptr asym
endif
extern token_stringbuf:ptr

UpdateStackBase  proto :ptr asym, :ptr
UpdateProcStatus proto :ptr asym, :ptr

opt macro value
    exitm<OP_&value&,>
    endm
.enum option_types {
include option.inc
TABITEMS
}
undef opt

define NOARGOPTS OP_CASEMAP      ;; number of options without arguments
define MASMOPTS  OP_FIELDALIGN   ;; number of options compatible with Masm

    .data

optiontab label string_t
opt macro value
    exitm<string_t @CStr("&value&")>
    endm
include option.inc
undef opt

    .code

InitStackBase proc fastcall private reg:int_t

    movzx eax,ModuleInfo.Ofssize
    mov ModuleInfo.basereg[eax*4],reg
    .if ( !ModuleInfo.StackBase )
        mov ModuleInfo.StackBase,CreateVariable( "@StackBase", 0 )
        or  [eax].asym.flags,S_PREDEFINED
        mov [eax].asym.sfunc_ptr,UpdateStackBase
        mov ModuleInfo.ProcStatus,CreateVariable( "@ProcStatus", 0 )
        mov [eax].asym.flags,S_PREDEFINED
        mov [eax].asym.sfunc_ptr,UpdateProcStatus
    .endif
    ret
InitStackBase endp

    assume ebx:ptr asm_tok

SetAlignment proc private i:ptr int_t, tokenarray:ptr asm_tok, max:int_t, dest:ptr byte

  local opnd:expr

    .return .if ( EvalOperand( i, tokenarray, Token_Count, &opnd, EXPF_NOUNDEF ) == ERROR )
    .if ( opnd.kind != EXPR_CONST )
        .return( asmerr( 2026 ) )
    .endif
    .if ( opnd.uvalue > max )
        .return( asmerr( 2064 ) )
    .endif
    .if ( opnd.uvalue )
        .for ( eax = 0, ecx = 1 : ecx < opnd.uvalue : ecx <<= 1, eax++ )
        .endf
        .if ( ecx != opnd.uvalue )
            .return( asmerr( 2063, opnd.value ) )
        .endif
        mov edx,dest
        mov [edx],al
    .endif
    .return( NOT_ERROR )
SetAlignment endp

OptionDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

   .new opnd:expr
   .new idx:int_t = -1
   .new p:line_status

    inc i ;; skip OPTION directive
    mov ebx,tokenarray.tokptr(i)

    .while ( [ebx].token != T_FINAL )
        mov esi,[ebx].string_ptr
        tstrupr( esi )
        .for ( edi = 0 : edi < TABITEMS : edi++ )
            .break .if ( !tstrcmp( esi, optiontab[edi*4] ) )
        .endf
        .break .if ( edi >= TABITEMS )
        mov idx,edi
        inc i
        add ebx,asm_tok
        ;
        ; v2.06: check for colon separator here
        ;
        .if ( edi >= NOARGOPTS )
            .if ( [ebx].token != T_COLON )
                .return( asmerr( 2065, "" ) )
            .endif
            inc i
            add ebx,asm_tok
            ;
            ; there must be something after the colon
            ;
            .if ( [ebx].token == T_FINAL )
                sub ebx,asm_tok*2 ;; position back to option identifier
                .break
            .endif
            ;
            ; reject option if -Zne is set
            ;
            .if ( edi >= MASMOPTS && ModuleInfo.strict_masm_compat )
                sub ebx,asm_tok*2
                .break
            .endif
        .endif
        mov esi,[ebx].string_ptr
        .switch pascal edi
        .case OP_DOTNAME
            mov ModuleInfo.dotname,TRUE
        .case OP_NODOTNAME
            mov ModuleInfo.dotname,FALSE
        .case OP_M510
            SetMasm510( TRUE )
        .case OP_NOM510
            SetMasm510( FALSE )
        .case OP_SCOPED
            mov ModuleInfo.scoped,TRUE
        .case OP_NOSCOPED
            mov ModuleInfo.scoped,FALSE
        .case OP_OLDSTRUCTS
            mov ModuleInfo.oldstructs,TRUE
        .case OP_NOOLDSTRUCTS
            mov ModuleInfo.oldstructs,FALSE
        .case OP_EMULATOR
            mov ModuleInfo.emulator,TRUE
        .case OP_NOEMULATOR
            mov ModuleInfo.emulator,FALSE
        .case OP_LJMP
            mov ModuleInfo.ljmp,TRUE
        .case OP_NOLJMP
            mov ModuleInfo.ljmp,FALSE
        .case OP_READONLY
        .case OP_NOREADONLY
        .case OP_OLDMACROS
        .case OP_NOOLDMACROS
        .case OP_EXPR16
        .case OP_EXPR32
            ;; default, nothing to do
        .case OP_NOSIGNEXTEND
            mov ModuleInfo.NoSignExtend,TRUE
        .case OP_CASEMAP
            .break .if ( [ebx].token != T_ID )
            .if ( !tstricmp( esi, "NONE" ) )
                mov ModuleInfo.case_sensitive,TRUE                 ;; -Cx
                mov ModuleInfo.convert_uppercase,FALSE
            .elseif ( !tstricmp( esi, "NOTPUBLIC" ) )
                mov ModuleInfo.case_sensitive,FALSE                ;; -Cp
                mov ModuleInfo.convert_uppercase,FALSE
            .elseif ( !tstricmp( esi, "ALL" ) )
                mov ModuleInfo.case_sensitive,FALSE                ;; -Cu
                mov ModuleInfo.convert_uppercase,TRUE
            .else
                .break
            .endif
            inc i
            SymSetCmpFunc()
        .case OP_PROC ;; PRIVATE | PUBLIC | EXPORT
            .switch ( [ebx].token )
            .case T_ID
                .if ( !tstricmp( esi, "PRIVATE" ) )
                    mov ModuleInfo.procs_private,TRUE
                    mov ModuleInfo.procs_export,FALSE
                    inc i
                .elseif ( !tstricmp( esi, "EXPORT" ) )
                    mov ModuleInfo.procs_private,FALSE
                    mov ModuleInfo.procs_export,TRUE
                    inc i
                .endif
                .endc
            .case T_DIRECTIVE ;; word PUBLIC is a directive
                .if ( [ebx].tokval == T_PUBLIC )
                    mov ModuleInfo.procs_private,FALSE
                    mov ModuleInfo.procs_export,FALSE
                    inc i
                .endif
                .endc
            .endsw
        .case OP_PROLOGUE
            ;
            ; OPTION PROLOGUE:macroname
            ; the prologue macro must be a macro function with 6 params:
            ; name macro procname, flag, parmbytes, localbytes, <reglist>, userparms
            ; procname: name of procedure
            ; flag: bits 0-2: calling convention
            ; bit 3: undef
            ; bit 4: 1 if caller restores ESP
            ; bit 5: 1 if proc is far
            ; bit 6: 1 if proc is private
            ; bit 7: 1 if proc is export
            ; bit 8: for epilogue: 1 if IRET, 0 if RET
            ; parmbytes: no of bytes for all params
            ; localbytes: no of bytes for all locals
            ; reglist: list of registers to save/restore, separated by commas
            ; userparms: prologuearg specified in PROC
            ;
            .if ( [ebx].token != T_ID )
                .return( asmerr(2008, [ebx].tokpos ) )
            .endif
            .if ( ModuleInfo.proc_prologue )
                mov ModuleInfo.proc_prologue,NULL
            .endif
            .if ( !tstricmp( esi, "NONE" ) )
                mov ModuleInfo.prologuemode,PEM_NONE
            .elseif ( !tstricmp( esi, "PROLOGUEDEF" ) )
                mov ModuleInfo.prologuemode,PEM_DEFAULT
            .else
                mov ModuleInfo.prologuemode,PEM_MACRO
                mov ModuleInfo.proc_prologue,LclAlloc( &[strlen( esi ) + 1] )
                strcpy( ModuleInfo.proc_prologue, esi )
            .endif
            inc i
        .case OP_EPILOGUE
            .if ( [ebx].token != T_ID )
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif
            .if ( !tstricmp( esi, "FLAGS" ) )
                mov ModuleInfo.epilogueflags,1
            .else
                mov ModuleInfo.proc_epilogue,NULL
                .if ( !tstricmp( esi, "NONE" ) )
                    mov ModuleInfo.epiloguemode,PEM_NONE
                .elseif ( !tstricmp( esi, "EPILOGUEDEF" ) )
                    mov ModuleInfo.epiloguemode,PEM_DEFAULT
                .else
                    mov ModuleInfo.epiloguemode,PEM_MACRO
                    mov ModuleInfo.proc_epilogue,LclAlloc( &[strlen( esi ) + 1] )
                    strcpy( ModuleInfo.proc_epilogue, esi )
                .endif
            .endif
            inc i
        .case OP_LANGUAGE
            .if ( [ebx].token == T_ID )
                mov eax,[esi]
                or  al,0x20
                .if ( ax == 'c' )
                    mov [ebx].token,T_RES_ID
                    mov [ebx].tokval,T_CCALL
                    mov [ebx].bytval,1
                .endif
            .endif
            .if ( [ebx].token == T_RES_ID )
                .if ( GetLangType( &i, tokenarray, &ModuleInfo.langtype ) == NOT_ERROR )
ifndef ASMC64
                    ;
                    ; update @Interface assembly time variable
                    ;
                    .if ( ModuleInfo._model != MODEL_NONE && sym_Interface )
                        mov ecx,sym_Interface
                        mov [ecx].asym.value,ModuleInfo.langtype
                    .endif
endif
                    .endc
                .endif
            .endif
            .break
        .case OP_NOKEYWORD
            .if ( Parse_Pass != PASS_1 )
                .while ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )
                    inc i
                    add ebx,asm_tok
                .endw
                .endc
            .endif
            .break .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
            .for ( : byte ptr [esi] : )
                .while ( islspace( [esi] ) )
                    inc esi
                .endw
                .if ( byte ptr [esi] )
                    mov edi,esi
                    .for ( : byte ptr [esi] : esi++ )
                        .break .if ( islspace( [esi] ) || byte ptr [esi] == ',' )
                    .endf
                    mov ecx,esi
                    sub ecx,edi
                    ;
                    ; todo: if MAX_ID_LEN can be > 255, then check size,
                    ; since a reserved word's size must be <= 255
                    ;
                    .if ( FindResWord( edi, ecx ) != 0 )
                        DisableKeyword( eax )
                    .else
                        mov ecx,esi
                        sub ecx,edi
                        .if ( IsKeywordDisabled( edi, ecx ) )
                            .return( asmerr( 2086 ) )
                        .endif
                    .endif
                .endif
                .while ( islspace( [esi] ) )
                    inc esi
                .endw
                .if ( byte ptr [esi] == ',' )
                    inc esi
                .endif
            .endf
            inc i
        .case OP_SETIF2
            .if ( !tstricmp( esi, "TRUE" ) )
                mov ModuleInfo.setif2,TRUE
                inc i
            .elseif ( !tstricmp( esi, "FALSE" ) )
                mov ModuleInfo.setif2,FALSE
                inc i
            .endif
        .case OP_OFFSET ;; GROUP | FLAT | SEGMENT
            ;
            ; default is GROUP.
            ; determines result of OFFSET operator fixups if .model isn't set.
            ;
            .if ( !tstricmp( esi, "GROUP" ) )
                mov ModuleInfo.offsettype,OT_GROUP
            .elseif ( !tstricmp( esi, "FLAT" ) )
                mov ModuleInfo.offsettype,OT_FLAT
            .elseif ( !tstricmp( esi, "SEGMENT" ) )
                mov ModuleInfo.offsettype,OT_SEGMENT
            .else
                .break
            .endif
            inc i
        .case OP_SEGMENT ;; USE16 | USE32 | FLAT
            ;
            ; this option set the default offset size for segments and
            ; externals defined outside of segments.
            ;
            .if ( [ebx].token == T_RES_ID && [ebx].tokval == T_FLAT )
                mov eax,ModuleInfo.curr_cpu
                and eax,P_CPU_MASK
                .if ( eax >= P_64 )
                    mov ModuleInfo.defOfssize,USE64
                .else
                    mov ModuleInfo.defOfssize,USE32
                .endif
            .elseif ( [ebx].token == T_ID && tstricmp( esi, "USE16" ) == 0 )
                mov ModuleInfo.defOfssize,USE16
            .elseif ( [ebx].token == T_ID && tstricmp( esi, "USE32" ) == 0 )
                mov ModuleInfo.defOfssize,USE32
            .elseif ( [ebx].token == T_ID && tstricmp( esi, "USE64" ) == 0 )
                mov ModuleInfo.defOfssize,USE64
            .else
                .break
            .endif
            inc i
        .case OP_FIELDALIGN ;; 1|2|4|8|16|32
            .return .if SetAlignment( &i, tokenarray, MAX_STRUCT_ALIGN, &ModuleInfo.fieldalign ) == ERROR
        .case OP_PROCALIGN ;; 1|2|4|8|16|32
            .return .if SetAlignment( &i, tokenarray, MAX_STRUCT_ALIGN, &ModuleInfo.procalign ) == ERROR
        .case OP_MZ
            .new j:int_t
            .for ( j = 0, edi = &ModuleInfo.mz_ofs_fixups : j < 4 : j++ )
                .for ( ecx = i, edx = ebx: [edx].asm_tok.token != T_FINAL: ecx++, edx += asm_tok )
                    .break .if ( [edx].asm_tok.token == T_COMMA || \
                                 [edx].asm_tok.token == T_COLON || \
                                 [edx].asm_tok.token == T_DBL_COLON )
                .endf
                .return .if ( EvalOperand( &i, tokenarray, ecx, &opnd, 0 ) == ERROR )
                mov ebx,tokenarray.tokptr(i)
                .if ( opnd.kind == EXPR_EMPTY )
                .elseif ( opnd.kind == EXPR_CONST )
                    .if ( opnd.value > 0xFFFF )
                        .return( EmitConstError( &opnd ) )
                    .endif
                    .if ( ModuleInfo.sub_format == SFORMAT_MZ )
                        mov eax,opnd.value
                        mov ecx,j
                        mov [edi+ecx*2],ax
                    .endif
                .else
                    .return( asmerr( 2026 ) )
                .endif
                .if ( [ebx].token == T_COLON )
                    inc i
                    add ebx,asm_tok
                .elseif ( [ebx].token == T_DBL_COLON )
                    inc i
                    add ebx,asm_tok
                    inc j
                .endif
            .endf
            ;
            ; ensure data integrity of the params
            ;
            .if ( ModuleInfo.sub_format == SFORMAT_MZ )
                .if ( ModuleInfo.mz_ofs_fixups < 0x1E )
                    mov ModuleInfo.mz_ofs_fixups,0x1E
                .endif
                .for ( ecx = 16: cx < ModuleInfo.mz_alignment: ecx <<= 1 )
                .endf
                .if ( cx != ModuleInfo.mz_alignment )
                    asmerr( 2189, ecx )
                .endif
                mov ax,ModuleInfo.mz_heapmin
                .if ( ModuleInfo.mz_heapmax < ax )
                    mov ModuleInfo.mz_heapmax,ax
                .endif
            .endif
        .case OP_FRAME ;; AUTO | NOAUTO | ADD -- default is NOAUTO
            .if ( !tstricmp( esi, "AUTO" ) )
                or ModuleInfo.frame_auto,1
            .elseif ( [ebx].tokval == T_ADD )
                mov ModuleInfo.frame_auto,3
            .elseif ( !tstricmp( esi, "NOAUTO" ) )
                mov ModuleInfo.frame_auto,0
            .else
                .break
            .endif
            inc i
        .case OP_ELF
            .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFF )
                    .return( EmitConstError( &opnd ) )
                .endif
                .if ( Options.output_format == OFORMAT_ELF )
                    mov ModuleInfo.elf_osabi,opnd.value
                .endif
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_RENAMEKEYWORD ;; <keyword>,new_name
            .break .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
            inc i
            add ebx,asm_tok
            .break .if ( [ebx].token != T_DIRECTIVE || [ebx].dirtype != DRT_EQUALSGN )
            inc i
            add ebx,asm_tok
            .break .if ( [ebx].token != T_ID )
            ;
            ; todo: if MAX_ID_LEN can be > 255, then check size,
            ; since a reserved word's size must be <= 255
            ;
            mov esi,FindResWord( esi, strlen( esi ) )
            .if ( esi == 0 )
                .return( asmerr( 2086 ) )
            .endif
            RenameKeyword( esi, [ebx].string_ptr, strlen( [ebx].string_ptr ) )
            inc i
        .case OP_WIN64
            ;
            ; if -win64 isn't set, skip the option
            ; v2.09: skip option if Ofssize != USE64
            ;
            .if ( ModuleInfo.defOfssize != USE64 )
                .while ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )
                    inc i
                    add ebx,asm_tok
                .endw
                .endc
            .endif
            .if ( [ebx].token == T_NUM )
                .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
                .if ( opnd.kind == EXPR_CONST )
                    .if ( opnd.uvalue & ( not W64F_ALL ) )
                        .return( EmitConstError( &opnd ) )
                    .endif
                    mov ModuleInfo.win64_flags,opnd.value
                .endif
            .else
                .while ( [ebx].token != T_FINAL )
                    .if ( [ebx].token != T_COLON && [ebx].token != T_COMMA )
                        mov esi,[ebx].string_ptr
                        mov edi,[ebx].tokval
                        .if ( edi == T_RSP )
                            InitStackBase( T_RSP )
                            or ModuleInfo.win64_flags,W64F_AUTOSTACKSP
                        .elseif ( edi == T_RBP )
                            InitStackBase( T_RBP )
                            or ModuleInfo.frame_auto,1
                            or ModuleInfo.win64_flags,(W64F_AUTOSTACKSP or W64F_SAVEREGPARAMS)
                        .elseif ( edi == T_ALIGN )
                            .if ( !ModuleInfo.win64_flags )
                                or ModuleInfo.win64_flags,W64F_AUTOSTACKSP
                            .endif
                            or  ModuleInfo.win64_flags,W64F_STACKALIGN16
                        .elseif ( !tstricmp( esi, "NOALIGN" ) )
                            and ModuleInfo.win64_flags,not W64F_STACKALIGN16
                        .elseif ( !tstricmp( esi, "SAVE" ) )
                            or  ModuleInfo.win64_flags,W64F_SAVEREGPARAMS
                        .elseif ( !tstricmp( esi, "NOSAVE" ) )
                            and ModuleInfo.win64_flags,not W64F_SAVEREGPARAMS
                        .elseif ( !tstricmp( esi, "AUTO" ) )
                            or  ModuleInfo.win64_flags,W64F_AUTOSTACKSP
                        .elseif ( !tstricmp( esi, "NOAUTO" ) )
                            and ModuleInfo.win64_flags,not W64F_AUTOSTACKSP
                        .elseif ( edi == T_FRAME )
                            mov ModuleInfo.frame_auto,3
                        .elseif ( !tstricmp( esi, "NOFRAME" ) )
                            mov ModuleInfo.frame_auto,0
                        .else
                            .return( asmerr( 2026 ) )
                        .endif
                    .endif
                    inc i
                    add ebx,asm_tok
                .endw
            .endif
        .case OP_DLLIMPORT
            .if ( [ebx].token == T_ID && ( tstricmp( esi, "NONE" ) == 0 ) )
                mov ModuleInfo.CurrDll,NULL
            .elseif ( [ebx].token == T_STRING && [ebx].string_delim == '<' )
                .if ( Parse_Pass == PASS_1 )
                    ;
                    ; allow a zero-sized name!
                    ;
                    .if ( byte ptr [esi] == NULLC )
                        xor esi,esi
                    .else
                        .repeat
                            .for ( edi = &ModuleInfo.DllQueue: dlldesc_t ptr [edi] : edi = [edi] )
                                mov ecx,[edi]
                                .if ( tstricmp( &[ecx].dll_desc.name, esi ) == 0 )
                                    mov esi,[edi]
                                    .break(1)
                                .endif
                            .endf
                            add strlen( esi ),sizeof( dll_desc )
                            mov [edi],LclAlloc( eax )
                            mov edi,eax
                            mov [edi].dll_desc.next,NULL
                            mov [edi].dll_desc.cnt,0
                            strcpy( &[edi].dll_desc.name, esi )
                            lea eax,@CStr( "__imp_" )
                            .if ( ModuleInfo.defOfssize != USE64 )
                                inc eax
                            .endif
                            mov ModuleInfo.imp_prefix,eax
                            mov esi,edi
                        .until 1
                    .endif
                    mov ModuleInfo.CurrDll,esi
                .endif
            .endif
            inc i
        .case OP_CODEVIEW
            .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                mov ModuleInfo.cv_opt,opnd.value
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_STACKBASE
            .break .if ( [ebx].token != T_REG )
            .if ( !( GetSflagsSp( [ebx].tokval ) & SFR_IREG ) )
                .return( asmerr( 2031 ) )
            .endif
            InitStackBase( [ebx].tokval )
            inc i
        .case OP_CSTACK ;; ON | OFF
            .if ( !tstricmp( esi, "ON" ) )
                or  ModuleInfo.xflag,OPT_CSTACK
            .elseif ( !tstricmp( esi, "OFF" ) )
                and ModuleInfo.xflag,not OPT_CSTACK
            .else
                .break
            .endif
            inc i
        .case OP_SWITCH ;; C | PASCAL | TABLE | NOTABLE | REGAX | NOREGS
            .if ( !tstricmp( esi, "C" ) )
                and ModuleInfo.xflag,not OPT_PASCAL
            .elseif ( !tstricmp( esi, "PASCAL" ) )
                or  ModuleInfo.xflag,OPT_PASCAL
            .elseif ( !tstricmp( esi, "TABLE" ) )
                and ModuleInfo.xflag,not OPT_NOTABLE
            .elseif ( !tstricmp( esi, "NOTABLE" ) )
                or  ModuleInfo.xflag,OPT_NOTABLE
            .elseif ( !tstricmp( esi, "REGAX" ) )
                or  ModuleInfo.xflag,OPT_REGAX
            .elseif ( !tstricmp( esi, "NOREGS" ) )
                and ModuleInfo.xflag,not OPT_REGAX
            .else
                .break
            .endif
            inc i
        .case OP_LOOPALIGN ;; 0|1|2|4|8|16
            .return .if SetAlignment( &i, tokenarray, MAX_LOOP_ALIGN, &ModuleInfo.loopalign ) == ERROR
        .case OP_CASEALIGN ;; 0|1|2|4|8|16
            .return .if SetAlignment( &i, tokenarray, MAX_CASE_ALIGN, &ModuleInfo.casealign ) == ERROR
        .case OP_WSTRING ;; ON | OFF
            .if ( !tstricmp( esi, "ON" ) )
                or  ModuleInfo.xflag,OPT_WSTRING
            .elseif ( !tstricmp( esi, "OFF" ) )
                and ModuleInfo.xflag,not OPT_WSTRING
            .else
                .break
            .endif
            inc i
        .case OP_CODEPAGE ;; <value>
            .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFFFF )
                    .return( EmitConstError( &opnd ) )
                .endif
                mov ModuleInfo.codepage,opnd.value
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_FLOATFORMAT ; : <e|f|g>
            .if ( !tstricmp( esi, "E" ) )
                mov ModuleInfo.floatformat,'e'
            .elseif ( !tstricmp( esi, "F" ) )
                mov ModuleInfo.floatformat,0
            .elseif ( !tstricmp( esi, "G" ) )
                mov ModuleInfo.floatformat,'g'
            .elseif ( !tstricmp( esi, "X" ) )
                mov ModuleInfo.floatformat,'x'
            .else
                .break
            .endif
            inc i
        .case OP_FLOAT ; : <value>
            mov al,[esi]
            .if ( al == '4' )
                mov ModuleInfo.flt_size,4
            .elseif ( al == '8' )
                mov ModuleInfo.flt_size,8
            .else
                .return( asmerr( 2026 ) )
            .endif
            inc i
        .case OP_FLOATDIGITS ; : <value>
            .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFF )
                    .return( EmitConstError( &opnd ) )
                .endif
                mov ModuleInfo.floatdigits,opnd.value
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_LINESIZE ; : <value>
            .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFFFF )
                    .return( EmitConstError( &opnd ) )
                .endif
                mov p.input,ModuleInfo.currsource
                mov p.start,eax
                mov p.tokenarray,ModuleInfo.tokenarray
                mov p.outbuf,token_stringbuf
                mov p.output,eax
                mov p.index,0
                mov esi,ModuleInfo.max_line_len
                .while ( esi < opnd.value )
                    .if ( InputExtend( &p ) == 0 )
                        .return( asmerr( 1009 ) )
                    .endif
                    .if ( esi == ModuleInfo.max_line_len )
                        .return( asmerr( 1901 ) )
                    .endif
                    mov esi,ModuleInfo.max_line_len
                .endw
            .else
                .return( asmerr( 2026 ) )
            .endif
        .endsw
        mov ebx,tokenarray.tokptr(i)
        .break .if ( [ebx].token != T_COMMA )
        inc i
        add ebx,asm_tok
    .endw
    .if ( idx >= TABITEMS  || [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].tokpos ) )
    .endif
    .return( NOT_ERROR )
OptionDirective endp

    end
