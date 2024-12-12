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

UpdateStackBase  proto fastcall :ptr asym, :ptr
UpdateProcStatus proto fastcall :ptr asym, :ptr

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
    lea rdx,ModuleInfo
    mov [rdx].module_info.basereg[rax*4],ecx

    .if ( !ModuleInfo.StackBase )

        mov ModuleInfo.StackBase,CreateVariable( "@StackBase", 0 )
        mov rcx,rax
        or  [rcx].asym.flags,S_PREDEFINED
        mov [rcx].asym.sfunc_ptr,&UpdateStackBase
        mov ModuleInfo.ProcStatus,CreateVariable( "@ProcStatus", 0 )
        mov rcx,rax
        mov [rcx].asym.flags,S_PREDEFINED
        mov [rcx].asym.sfunc_ptr,&UpdateProcStatus
    .endif
    ret

InitStackBase endp


    assume rbx:ptr asm_tok

SetAlignment proc __ccall private i:ptr int_t, tokenarray:ptr asm_tok, max:int_t, dest:ptr byte

  local opnd:expr

    .ifd ( EvalOperand( i, tokenarray, TokenCount, &opnd, EXPF_NOUNDEF ) == ERROR )
        .return
    .endif
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
        mov rdx,dest
        mov [rdx],al
    .endif
    .return( NOT_ERROR )

SetAlignment endp


OptionDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

   .new opnd:expr
   .new idx:int_t = -1
   .new p:line_status

    inc i ; skip OPTION directive
    mov rbx,tokenarray.tokptr(i)

    .while ( [rbx].token != T_FINAL )

        mov rsi,[rbx].string_ptr
        tstrupr( rsi )

        .for ( edi = 0 : edi < TABITEMS : edi++ )

            lea rdx,optiontab
            .break .ifd ( !tstrcmp( rsi, [rdx+rdi*string_t] ) )
        .endf
        .break .if ( edi >= TABITEMS )

        mov idx,edi
        inc i
        add rbx,asm_tok
        ;
        ; v2.06: check for colon separator here
        ;
        .if ( edi >= NOARGOPTS )

            .if ( [rbx].token != T_COLON )
                .return( asmerr( 2065, "" ) )
            .endif

            inc i
            add rbx,asm_tok
            ;
            ; there must be something after the colon
            ;
            .if ( [rbx].token == T_FINAL )
                sub rbx,asm_tok*2 ;; position back to option identifier
                .break
            .endif
            ;
            ; reject option if -Zne is set
            ;
            .if ( edi >= MASMOPTS && Options.strict_masm_compat )
                sub rbx,asm_tok*2
                .break
            .endif
        .endif

        mov rsi,[rbx].string_ptr
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
            ;
            ; default, nothing to do
            ;
        .case OP_NOSIGNEXTEND
            mov ModuleInfo.NoSignExtend,TRUE
        .case OP_CASEMAP
            .break .if ( [rbx].token != T_ID )
            .ifd ( !tstricmp( rsi, "NONE" ) )
                mov ModuleInfo.case_sensitive,TRUE                 ;; -Cx
                mov ModuleInfo.convert_uppercase,FALSE
            .elseifd ( !tstricmp( rsi, "NOTPUBLIC" ) )
                mov ModuleInfo.case_sensitive,FALSE                ;; -Cp
                mov ModuleInfo.convert_uppercase,FALSE
            .elseifd ( !tstricmp( rsi, "ALL" ) )
                mov ModuleInfo.case_sensitive,FALSE                ;; -Cu
                mov ModuleInfo.convert_uppercase,TRUE
            .else
                .break
            .endif
            inc i
            SymSetCmpFunc()
        .case OP_PROC ; PRIVATE | PUBLIC | EXPORT
            .switch ( [rbx].token )
            .case T_ID
                .ifd ( !tstricmp( rsi, "PRIVATE" ) )
                    mov ModuleInfo.procs_private,TRUE
                    mov ModuleInfo.procs_export,FALSE
                    inc i
                .elseifd ( !tstricmp( rsi, "EXPORT" ) )
                    mov ModuleInfo.procs_private,FALSE
                    mov ModuleInfo.procs_export,TRUE
                    inc i
                .endif
                .endc
            .case T_DIRECTIVE ; word PUBLIC is a directive
                .if ( [rbx].tokval == T_PUBLIC )
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
            .if ( [rbx].token != T_ID )
                .return( asmerr(2008, [rbx].tokpos ) )
            .endif
            .if ( ModuleInfo.proc_prologue )
                mov ModuleInfo.proc_prologue,NULL
            .endif
            .ifd ( !tstricmp( rsi, "NONE" ) )
                mov ModuleInfo.prologuemode,PEM_NONE
            .elseifd ( !tstricmp( rsi, "PROLOGUEDEF" ) )
                mov ModuleInfo.prologuemode,PEM_DEFAULT
            .else
                mov ModuleInfo.prologuemode,PEM_MACRO
                mov ModuleInfo.proc_prologue,LclDup( rsi )
            .endif
            inc i
        .case OP_EPILOGUE
            .if ( [rbx].token != T_ID )
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif
            mov ModuleInfo.proc_epilogue,NULL
            .ifd ( !tstricmp( rsi, "NONE" ) )
                mov ModuleInfo.epiloguemode,PEM_NONE
            .elseifd ( !tstricmp( rsi, "EPILOGUEDEF" ) )
                mov ModuleInfo.epiloguemode,PEM_DEFAULT
            .else
                mov ModuleInfo.epiloguemode,PEM_MACRO
                mov ModuleInfo.proc_epilogue,LclDup( rsi )
            .endif
            inc i
        .case OP_LANGUAGE
            .if ( [rbx].token == T_ID )
                mov eax,[rsi]
                or  al,0x20
                .if ( ax == 'c' )
                    mov [rbx].token,T_RES_ID
                    mov [rbx].tokval,T_CCALL
                    mov [rbx].bytval,1
                .endif
            .endif
            .if ( [rbx].token == T_RES_ID )
                .ifd ( GetLangType( &i, tokenarray, &ModuleInfo.langtype ) == NOT_ERROR )
ifndef ASMC64
                    ;
                    ; update @Interface assembly time variable
                    ;
                    .if ( ModuleInfo._model != MODEL_NONE && sym_Interface )
                        mov rcx,sym_Interface
                        mov [rcx].asym.value,ModuleInfo.langtype
                    .endif
endif
                    .endc
                .endif
            .endif
            .break
        .case OP_NOKEYWORD
            .if ( Parse_Pass != PASS_1 )
                .while ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )
                    inc i
                    add rbx,asm_tok
                .endw
                .endc
            .endif
            .break .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            .for ( : byte ptr [rsi] : )
                .while ( islspace( [rsi] ) )
                    inc rsi
                .endw
                .if ( byte ptr [rsi] )
                    mov rdi,rsi
                    .for ( : byte ptr [rsi] : rsi++ )
                        .break .if ( islspace( [rsi] ) || byte ptr [rsi] == ',' )
                    .endf
                    mov rcx,rsi
                    sub rcx,rdi
                    ;
                    ; todo: if MAX_ID_LEN can be > 255, then check size,
                    ; since a reserved word's size must be <= 255
                    ;
                    .if ( FindResWord( rdi, ecx ) != 0 )
                        DisableKeyword( eax )
                    .else
                        mov rcx,rsi
                        sub rcx,rdi
                        .if ( IsKeywordDisabled( rdi, ecx ) )
                            .return( asmerr( 2086 ) )
                        .endif
                    .endif
                .endif
                .while ( islspace( [rsi] ) )
                    inc rsi
                .endw
                .if ( byte ptr [rsi] == ',' )
                    inc rsi
                .endif
            .endf
            inc i
        .case OP_SETIF2
            .ifd ( !tstricmp( rsi, "TRUE" ) )
                mov ModuleInfo.setif2,TRUE
                inc i
            .elseifd ( !tstricmp( rsi, "FALSE" ) )
                mov ModuleInfo.setif2,FALSE
                inc i
            .endif
        .case OP_OFFSET ;; GROUP | FLAT | SEGMENT
            ;
            ; default is GROUP.
            ; determines result of OFFSET operator fixups if .model isn't set.
            ;
            .ifd ( !tstricmp( rsi, "GROUP" ) )
                mov ModuleInfo.offsettype,OT_GROUP
            .elseifd ( !tstricmp( rsi, "FLAT" ) )
                mov ModuleInfo.offsettype,OT_FLAT
            .elseifd ( !tstricmp( rsi, "SEGMENT" ) )
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
            .if ( [rbx].token == T_RES_ID && [rbx].tokval == T_FLAT )
                mov eax,ModuleInfo.curr_cpu
                and eax,P_CPU_MASK
                .if ( eax >= P_64 )
                    mov ModuleInfo.defOfssize,USE64
                .else
                    mov ModuleInfo.defOfssize,USE32
                .endif
            .elseif ( [rbx].token == T_ID )
                .ifd ( tstricmp( rsi, "USE16" ) == 0 )
                    mov ModuleInfo.defOfssize,USE16
                .elseifd ( tstricmp( rsi, "USE32" ) == 0 )
                    mov ModuleInfo.defOfssize,USE32
                .elseifd ( tstricmp( rsi, "USE64" ) == 0 )
                    mov ModuleInfo.defOfssize,USE64
                .else
                    .break
                .endif
            .else
                .break
            .endif
            inc i
        .case OP_AVXENCODING ; : PREFER_FIRST, PREFER_VEX, PREFER_VEX3, PREFER_EVEX, NO_EVEX
            .ifd ( !tstricmp( rsi, "PREFER_FIRST" ) )
                mov ModuleInfo.avxencoding,PREFER_FIRST
            .elseif ( !tstricmp( rsi, "PREFER_VEX" ) )
                mov ModuleInfo.avxencoding,PREFER_VEX
            .elseif ( !tstricmp( rsi, "PREFER_VEX3" ) )
                mov ModuleInfo.avxencoding,PREFER_VEX3
            .elseif ( !tstricmp( rsi, "PREFER_EVEX" ) )
                mov ModuleInfo.avxencoding,PREFER_EVEX
            .elseif ( !tstricmp( rsi, "NO_EVEX" ) )
                mov ModuleInfo.avxencoding,NO_EVEX
            .else
                .break
            .endif
            inc i

        .case OP_FIELDALIGN ;; 1|2|4|8|16|32
            .return .ifd SetAlignment( &i, tokenarray, MAX_STRUCT_ALIGN, &ModuleInfo.fieldalign ) == ERROR
        .case OP_PROCALIGN ;; 1|2|4|8|16|32
            .return .ifd SetAlignment( &i, tokenarray, MAX_STRUCT_ALIGN, &ModuleInfo.procalign ) == ERROR
        .case OP_MZ
            .new j:int_t
            .for ( j = 0, rdi = &ModuleInfo.mz_ofs_fixups : j < 4 : j++ )
                .for ( ecx = i, rdx = rbx: [rdx].asm_tok.token != T_FINAL: ecx++, rdx += asm_tok )
                    .break .if ( [rdx].asm_tok.token == T_COMMA ||
                                 [rdx].asm_tok.token == T_COLON ||
                                 [rdx].asm_tok.token == T_DBL_COLON )
                .endf
                .return .ifd ( EvalOperand( &i, tokenarray, ecx, &opnd, 0 ) == ERROR )
                mov rbx,tokenarray.tokptr(i)
                .if ( opnd.kind == EXPR_EMPTY )
                .elseif ( opnd.kind == EXPR_CONST )
                    .if ( opnd.value > 0xFFFF )
                        .return EmitConstError()
                    .endif
                    .if ( ModuleInfo.sub_format == SFORMAT_MZ )
                        mov eax,opnd.value
                        mov ecx,j
                        mov [rdi+rcx*2],ax
                    .endif
                .else
                    .return( asmerr( 2026 ) )
                .endif
                .if ( [rbx].token == T_COLON )
                    inc i
                    add rbx,asm_tok
                .elseif ( [rbx].token == T_DBL_COLON )
                    inc i
                    add rbx,asm_tok
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
            .ifd ( !tstricmp( rsi, "AUTO" ) )
                or ModuleInfo.frame_auto,1
            .elseif ( [rbx].tokval == T_ADD )
                mov ModuleInfo.frame_auto,3
            .elseif ( !tstricmp( rsi, "NOAUTO" ) )
                mov ModuleInfo.frame_auto,0
            .else
                .break
            .endif
            inc i
        .case OP_ELF
            .return .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFF )
                    .return EmitConstError()
                .endif
                .if ( Options.output_format == OFORMAT_ELF )
                    mov ModuleInfo.elf_osabi,opnd.value
                .endif
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_RENAMEKEYWORD ; <keyword>,new_name
            .break .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            inc i
            add rbx,asm_tok
            .break .if ( [rbx].token != T_DIRECTIVE || [rbx].dirtype != DRT_EQUALSGN )
            inc i
            add rbx,asm_tok
            .break .if ( [rbx].token != T_ID )
            ;
            ; todo: if MAX_ID_LEN can be > 255, then check size,
            ; since a reserved word's size must be <= 255
            ;
            mov esi,FindResWord( rsi, tstrlen( rsi ) )
            .if ( esi == 0 )
                .return( asmerr( 2086 ) )
            .endif
            RenameKeyword( esi, [rbx].string_ptr, tstrlen( [rbx].string_ptr ) )
            inc i
        .case OP_WIN64
            ;
            ; if -win64 isn't set, skip the option
            ; v2.09: skip option if Ofssize != USE64
            ;
            .if ( ModuleInfo.defOfssize != USE64 )
                .while ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )
                    inc i
                    add rbx,asm_tok
                .endw
                .endc
            .endif
            .if ( [rbx].token == T_NUM )
                .return .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
                .if ( opnd.kind == EXPR_CONST )
                    .if ( opnd.uvalue & ( not W64F_ALL ) )
                        .return EmitConstError()
                    .endif
                    mov ModuleInfo.win64_flags,opnd.value
                .endif
            .else
                .while ( [rbx].token != T_FINAL )
                    .if ( [rbx].token != T_COLON && [rbx].token != T_COMMA )
                        mov rsi,[rbx].string_ptr
                        mov edi,[rbx].tokval
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
                        .elseifd ( !tstricmp( rsi, "NOALIGN" ) )
                            and ModuleInfo.win64_flags,not W64F_STACKALIGN16
                        .elseifd ( !tstricmp( rsi, "SAVE" ) )
                            or  ModuleInfo.win64_flags,W64F_SAVEREGPARAMS
                        .elseifd ( !tstricmp( rsi, "NOSAVE" ) )
                            and ModuleInfo.win64_flags,not W64F_SAVEREGPARAMS
                        .elseifd ( !tstricmp( rsi, "AUTO" ) )
                            or  ModuleInfo.win64_flags,W64F_AUTOSTACKSP
                        .elseifd ( !tstricmp( rsi, "NOAUTO" ) )
                            and ModuleInfo.win64_flags,not W64F_AUTOSTACKSP
                        .elseif ( edi == T_FRAME )
                            mov ModuleInfo.frame_auto,3
                        .elseifd ( !tstricmp( rsi, "NOFRAME" ) )
                            mov ModuleInfo.frame_auto,0
                        .else
                            .return( asmerr( 2026 ) )
                        .endif
                    .endif
                    inc i
                    add rbx,asm_tok
                .endw
            .endif
        .case OP_DLLIMPORT
            .if ( [rbx].token == T_ID )
                .ifd ( tstricmp( rsi, "NONE" ) == 0 )
                    mov ModuleInfo.CurrDll,NULL
                .endif
            .elseif ( [rbx].token == T_STRING && [rbx].string_delim == '<' )
                .if ( Parse_Pass == PASS_1 )
                    ;
                    ; allow a zero-sized name!
                    ;
                    .if ( byte ptr [rsi] == NULLC )
                        xor esi,esi
                    .else
                        .repeat
                            .for ( rdi = &ModuleInfo.DllQueue: dlldesc_t ptr [rdi] : rdi = [rdi] )
                                mov rcx,[rdi]
                                .ifd ( tstricmp( &[rcx].dll_desc.name, rsi ) == 0 )
                                    mov rsi,[rdi]
                                    .break(1)
                                .endif
                            .endf
                            add tstrlen( rsi ),sizeof( dll_desc )
                            mov [rdi],LclAlloc( eax )
                            mov rdi,rax
                            mov [rdi].dll_desc.next,NULL
                            mov [rdi].dll_desc.cnt,0
                            tstrcpy( &[rdi].dll_desc.name, rsi )
                            lea rax,@CStr( "__imp_" )
                            .if ( ModuleInfo.defOfssize != USE64 )
                                inc rax
                            .endif
                            mov ModuleInfo.imp_prefix,rax
                            mov rsi,rdi
                        .until 1
                    .endif
                    mov ModuleInfo.CurrDll,rsi
                .endif
            .endif
            inc i
        .case OP_CODEVIEW
            .return .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                mov ModuleInfo.cv_opt,opnd.value
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_STACKBASE
            .break .if ( [rbx].token != T_REG )
            .if ( !( GetSflagsSp( [rbx].tokval ) & SFR_IREG ) )
                .return( asmerr( 2031 ) )
            .endif
            InitStackBase( [rbx].tokval )
            inc i
        .case OP_CSTACK ;; ON | OFF
            .ifd ( !tstricmp( rsi, "ON" ) )
                or  ModuleInfo.xflag,OPT_CSTACK
            .elseifd ( !tstricmp( rsi, "OFF" ) )
                and ModuleInfo.xflag,not OPT_CSTACK
            .else
                .break
            .endif
            inc i
        .case OP_DOTNAMEX ;; ON | OFF
            .ifd ( !tstricmp( rsi, "ON" ) )
                mov ModuleInfo.dotnamex,1
            .elseifd ( !tstricmp( rsi, "OFF" ) )
                mov ModuleInfo.dotnamex,0
            .else
                .break
            .endif
            inc i
        .case OP_SWITCH ;; C | PASCAL | TABLE | NOTABLE | REGAX | NOREGS
            .ifd ( !tstricmp( rsi, "C" ) )
                and ModuleInfo.xflag,not OPT_PASCAL
            .elseifd ( !tstricmp( rsi, "PASCAL" ) )
                or  ModuleInfo.xflag,OPT_PASCAL
            .elseifd ( !tstricmp( rsi, "TABLE" ) )
                and ModuleInfo.xflag,not OPT_NOTABLE
            .elseifd ( !tstricmp( rsi, "NOTABLE" ) )
                or  ModuleInfo.xflag,OPT_NOTABLE
            .elseifd ( !tstricmp( rsi, "REGAX" ) )
                or  ModuleInfo.xflag,OPT_REGAX
            .elseifd ( !tstricmp( rsi, "NOREGS" ) )
                and ModuleInfo.xflag,not OPT_REGAX
            .else
                .break
            .endif
            inc i
        .case OP_LOOPALIGN ;; 0|1|2|4|8|16
            .return .ifd SetAlignment( &i, tokenarray, MAX_LOOP_ALIGN, &ModuleInfo.loopalign ) == ERROR
        .case OP_CASEALIGN ;; 0|1|2|4|8|16
            .return .ifd SetAlignment( &i, tokenarray, MAX_CASE_ALIGN, &ModuleInfo.casealign ) == ERROR
        .case OP_WSTRING ;; ON | OFF
            .ifd ( !tstricmp( rsi, "ON" ) )
                or  ModuleInfo.xflag,OPT_WSTRING
            .elseifd ( !tstricmp( rsi, "OFF" ) )
                and ModuleInfo.xflag,not OPT_WSTRING
            .else
                .break
            .endif
            inc i
        .case OP_CODEPAGE ;; <value>
            .return .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFFFF )
                    .return EmitConstError()
                .endif
                mov ModuleInfo.codepage,opnd.value
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_FLOATFORMAT ; : <e|f|g>
            .ifd ( !tstricmp( rsi, "E" ) )
                mov ModuleInfo.floatformat,'e'
            .elseifd ( !tstricmp( rsi, "F" ) )
                mov ModuleInfo.floatformat,0
            .elseifd ( !tstricmp( rsi, "G" ) )
                mov ModuleInfo.floatformat,'g'
            .elseifd ( !tstricmp( rsi, "X" ) )
                mov ModuleInfo.floatformat,'x'
            .else
                .break
            .endif
            inc i
        .case OP_FLOAT ; : <value>
            .return .if ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value != 4 && opnd.value != 8 )
                    .return EmitConstError()
                .endif
                mov ModuleInfo.flt_size,opnd.value
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_FLOATDIGITS ; : <value>
            .return .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFF )
                    .return EmitConstError()
                .endif
                mov ModuleInfo.floatdigits,opnd.value
            .else
                .return( asmerr( 2026 ) )
            .endif
        .case OP_LINESIZE ; : <value>
            .return .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .if ( opnd.kind == EXPR_CONST )
                .if ( opnd.value > 0xFFFF )
                    .return EmitConstError()
                .endif
                mov p.input,CurrSource
                mov p.start,rax
                mov p.tokenarray,TokenArray
                mov p.outbuf,StringBuffer
                mov p.output,rax
                mov p.index,0
                mov esi,MaxLineLength
                .while ( esi < opnd.value )
                    .ifd ( InputExtend( &p ) == 0 )
                        .return( asmerr( 1009 ) )
                    .endif
                    .if ( esi == MaxLineLength )
                        .return( asmerr( 1901 ) )
                    .endif
                    mov esi,MaxLineLength
                .endw
            .else
                .return( asmerr( 2026 ) )
            .endif
        .endsw
        mov rbx,tokenarray.tokptr(i)
        .break .if ( [rbx].token != T_COMMA )
        inc i
        add rbx,asm_tok
    .endw
    .if ( idx >= TABITEMS  || [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].tokpos ) )
    .endif
    .return( NOT_ERROR )
OptionDirective endp

    end
