; ASMC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)

ifndef ASMC_VERSION
define ASMC_VERSION 237
ifdef SUBVERSION
define ASMC_SUBVER SUBVERSION
else
define ASMC_SUBVER 0
endif
define ASMC_MAJOR (ASMC_VERSION / 100)
define ASMC_MINOR (ASMC_VERSION MOD 100)

option dotname

include stdio.inc
include stdlib.inc
include string.inc
include inttype.inc

ifndef NOSPAWN

define _EXEC_LINK   ; Spawn linker

ifdef __UNIX__
define _ASMC_LINK <"/usr/bin/gcc">
elseifdef MASMCOMPAT
define _ASMC_LINK <"link.exe">
else
define _ASMC_LINK <"linkw.exe">
endif

.template anode
    next ptr anode ?
    name char_t ?
   .ends

CollectLinkOption proto fastcall :string_t
CollectLinkObject proto fastcall :string_t

endif

define NULLC 0

ifndef __ccall
ifdef _WIN64
define __ccall <fastcall>   ; Use fastcall for -elf64
elseifdef __UNIX__
define __ccall <syscall>
else
define __ccall <c>
endif
endif

ifdef _WIN64
define MODULE <[r14]>
assume r14:ptr module_info
ifdef __UNIX__
define _LIN64
endif
else
define MODULE <ModuleInfo>
endif

define USE_COMALLOC
define USE_INDIRECTION

define OLDKEYWORDS          ; NAME, SIZE, ..
define CHEXPREFIX           ; 0x prefix

define MAX_LINE_LEN         2048                ; no restriction for this number
define MAX_STRING_LEN       MAX_LINE_LEN - 32   ; must be < MAX_LINE_LEN
define MAX_ID_LEN           247                 ; must be < MAX_LINE_LEN
define MAX_TOKEN            MAX_LINE_LEN / 4    ; max tokens in one line
define MAX_STRUCT_ALIGN     32
define MAX_SEGMENT_ALIGN    4096

define MAX_IF_NESTING       30   ; IFxx block nesting. Must be <=32, see condasm.asm
define MAX_SEG_NESTING      20   ; limit for segment nesting
define MAX_MACRO_NESTING    100  ; macro call nesting
define MAX_STRUCT_NESTING   32   ; limit for "anonymous structs" only
define MAX_LNAME            255  ; OMF lnames - length must fit in 1 byte
define LNAME_NULL           0    ; OMF first entry in lnames array

CCALLBACK macro id, arguments:VARARG
    ?&id& typedef proto __ccall &arguments
    exitm <id typedef ptr ?&id&>
    endm

include ltype.inc
include token.inc
include symbols.inc
include errmsg.inc      ; must be located AFTER #defines lines

define EMPTY            (-2) ; function return values
define ERROR            (-1)
define NOT_ERROR        0
define STRING_EXPANDED  1

define PASS_1           0
define PASS_2           1

define OPT_CSTACK       0x01
define OPT_WSTRING      0x02 ; convert "string" to unicode
define OPT_LSTRING      0x04 ; L"Unicode" used --> allow dw "string"
define OPT_PASCAL       0x08 ; auto insert break after cases
define OPT_NOTABLE      0x10 ; no indexed jump table
define OPT_REGAX        0x20 ; use [R|E]AX to render jump-code
define OPT_ASSERT       0x40 ; Generate .assert code
define OPT_PUSHF        0x80 ; Push/Pop flags

; enumerations

; output formats. Order must match formatoptions[] in assemble.asm

.enum oformat {
    OFORMAT_BIN,        ; used by -bin, -mz and -pe
    OFORMAT_OMF,
    OFORMAT_COFF,       ; used by -coff, -djgpp and -win64
    OFORMAT_ELF,        ; used by -elf and elf64
    }

.enum sformat {
    SFORMAT_NONE,
    SFORMAT_MZ,         ; MZ binary
    SFORMAT_PE,         ; PE (32- or 64-bit) binary
    SFORMAT_64BIT,      ; 64bit COFF or ELF
    }

.enum fpo {
    FPO_NO_EMULATION,   ; -FPi87 (default)
    FPO_EMULATION       ; -FPi
    }

; language values.
; the order cannot be changed, it's
; returned by OPATTR and used in user-defined prologue/epilogue.

.enum lang_type {
    LANG_NONE       = 0,
    LANG_C          = 1,
    LANG_SYSCALL    = 2,
    LANG_STDCALL    = 3,
    LANG_PASCAL     = 4,
    LANG_FORTRAN    = 5,
    LANG_BASIC      = 6,
    LANG_FASTCALL   = 7,
    LANG_VECTORCALL = 8,
    LANG_WATCALL    = 9,
    LANG_ASMCALL    = 10,
    }

; Memory model type.
; the order cannot be changed, it's
; the value of the predefined @Model symbol.

.enum model_type {
    MODEL_NONE      = 0,
    MODEL_TINY      = 1,
    MODEL_SMALL     = 2,
    MODEL_COMPACT   = 3,
    MODEL_MEDIUM    = 4,
    MODEL_LARGE     = 5,
    MODEL_HUGE      = 6,
    MODEL_FLAT      = 7
    }

define SIZE_DATAPTR 0x68 ; far for COMPACT, LARGE, HUGE
define SIZE_CODEPTR 0x70 ; far for MEDIUM, LARGE, HUGE

.enum seg_order {
    SEGORDER_SEQ,       ; .SEQ (default)
    SEGORDER_DOSSEG,    ; .DOSSEG
    SEGORDER_ALPHA      ; .ALPHA
    }

; .NOLISTMACRO, .LISTMACRO and .LISTMACROALL directives setting

.enum listmacro {
    LM_NOLISTMACRO,
    LM_LISTMACRO,
    LM_LISTMACROALL
    }

; assume values are used as index in codegen.c / invoke.c.
; Order must match the one in special.h. Don't change!

.enum assume_segreg {
    ASSUME_NOTHING = EMPTY,
    ASSUME_ES = 0,
    ASSUME_CS,
    ASSUME_SS,
    ASSUME_DS,
    ASSUME_FS,
    ASSUME_GS
    }

.enum cpu_info {

    ; bit count from left:

    ; bit 0-2:     Math coprocessor
    ; bit 3:       privileged?
    ; bit 4-7:     cpu type
    ; bit 8-15;    extension set

    P_NO87  = 0x0001,         ; no FPU
    P_87    = 0x0002,         ; 8087
    P_287   = 0x0003,         ; 80287
    P_387   = 0x0004,         ; 80387

    P_PM    = 0x0008,         ; privileged opcode

    P_86    = 0x0000,         ; 8086, default
    P_186   = 0x0010,         ; 80186
    P_286   = 0x0020,         ; 80286
    P_386   = 0x0030,         ; 80386
    P_486   = 0x0040,         ; 80486
    P_586   = 0x0050,         ; pentium
    P_686   = 0x0060,         ; ppro
    P_64    = 0x0070,         ; x64 cpu

    P_286p  = P_286 or P_PM,  ; 286, priv mode
    P_386p  = P_386 or P_PM,  ; 386, priv mode
    P_486p  = P_486 or P_PM,  ; 486, priv mode
    P_586p  = P_586 or P_PM,  ; 586, priv mode
    P_686p  = P_686 or P_PM,  ; 686, priv mode
    P_64p   = P_64 or P_PM,   ; x64, priv mode

    P_MMX   = 0x0100,         ; MMX extension instructions
    P_K3D   = 0x0200,         ; 3DNow extension instructions
    P_SSE1  = 0x0400,         ; SSE1 extension instructions
    P_SSE2  = 0x0800,         ; SSE2 extension instructions
    P_SSE3  = 0x1000,         ; SSE3 extension instructions
    P_SSSE3 = 0x2000,         ; SSSE3 extension instructions
    P_SSE4  = 0x4000,         ; SSE4 extension instructions
    P_AVX   = 0x8000,         ; AVX extension instructions

    ; all SSE extension instructions

    P_SSEALL    = P_SSE1 or P_SSE2 or P_SSE3 or P_SSSE3 or P_SSE4 or P_AVX,
    NO_OPPRFX   = P_MMX or P_SSEALL,

    P_FPU_MASK  = 0x0007,
    P_CPU_MASK  = 0x00F0,

    P_EXT_MASK  = P_MMX or P_K3D or P_SSEALL,
    P_EXT_ALL   = P_MMX or P_K3D or P_SSEALL
    }


; option -0..10

.enum cpu_type {
    CPU_86                  ;  0  __P86__
    CPU_186,                ;  1  __P186__
    CPU_286,                ;  2  __P286__
    CPU_386,                ;  3  __P386__
    CPU_486,                ;  4  __P486__
    CPU_586,                ;  5  __P586__
    CPU_686,                ;  6  __P686__
    CPU_MMX,                ;  7  __P686__
    CPU_SSE,                ;  8  __SSE__
    CPU_SSE2,               ;  9  __SSE2__
    CPU_64                  ; 10  __P64__
    }


; option -arch:[IA32|SSE|SSE2|AVX|AVX2|AVX512]

.enum cpu_architecture {
    ARCH_IX86_FP,           ; 0  _M_IX86_FP
    ARCH_SSE,               ; 1  __SSE__
    ARCH_SSE2,              ; 2  __SSE2__
    ARCH_AVX,               ; 3  __AVX__
    ARCH_AVX2,              ; 4  __AVX2__
    ARCH_AVX512             ; 5  __AVX512F__, __AVX512CD__, __AVX512BW__,
    }                       ;    __AVX512DQ__ and __AVX512VL__


; the MASM compatible @CPU value flags:

.enum masm_cpu {
    M_8086      = 0x0001,   ; 8086
    M_186       = 0x0002,   ; 186
    M_286       = 0x0004,   ; 286
    M_386       = 0x0008,   ; 386
    M_486       = 0x0010,   ; 486
    M_586       = 0x0020,   ; Pentium
    M_686       = 0x0040,   ; PPro
    M_CPUMSK    = 0x007F,
    M_PROT      = 0x0080,   ; protected instructions ok
    M_8087      = 0x0100,   ; 8087
    M_287       = 0x0400,   ; 287
    M_387       = 0x0800    ; 387
    }

.enum segofssize {
    USE_EMPTY   = 0xFE,
    USE16       = 0,        ; don't change values of USE16,USE32,USE64!
    USE32       = 1,
    USE64       = 2
    }


; fastcall types. if order is to be changed or entries
; added, also adjust tables in proc.c, mangle.c and probably invoke.c!

define FCT_MSC      0   ; MS 16-/32-bit fastcall (ax,dx,cx / ecx,edx)
define FCT_WATCOMC  1   ; OW register calling convention (eax, ebx, ecx, edx)
define FCT_WIN64    2   ; Win64 fastcall convention (rcx, rdx, r8, r9)
define FCT_ELF64    3   ; Linux 64 syscall
define FCT_VEC32    4
define FCT_VEC64    5

.enum stdcall_decoration {
    STDCALL_FULL,
    STDCALL_NONE,
    STDCALL_HALF
    }

; file extensions. Order must match first entries in enum opt_names!

.enum file_extensions {
    ASM, ; must be first; see SetFilenames() in assembly.asm
    OBJ,
    LST,
    ERR,
    NUM_FILE_TYPES
    }

; first 4 entries must match enum file_extensions!

.enum opt_names {
    OPTN_ASM_FN,
    OPTN_OBJ_FN,          ; -Fo option
    OPTN_LST_FN,          ; -Fl option
    OPTN_ERR_FN,          ; -Fr option
    OPTN_LNKDEF_FN,       ; -Fd option
    OPTN_MODULE_NAME,     ; -nm option
    OPTN_TEXT_SEG,        ; -nt option
    OPTN_DATA_SEG,        ; -nd option
    OPTN_CODE_CLASS,      ; -nc option
    OPTN_LAST
    }

; queues to store multiple cmdline switch values

.enum opt_queues {
    OPTQ_FINCLUDE,  ; -Fi option values
    OPTQ_MACRO,     ; -D option values
    OPTQ_INCPATH,   ; -I option values
    OPTQ_LAST
    }

.enum prologue_epilogue_mode {
    PEM_DEFAULT,    ; must be value 0
    PEM_MACRO,
    PEM_NONE
    }

; Stack distance

.enum dist_type {
    STACK_NEAR,
    STACK_FAR,
    }

; Type of operating system

.enum os_type {
    OPSYS_DOS,
    OPSYS_OS2,
    }

.enum offset_type {
    OT_GROUP    = 0,    ; OFFSET:GROUP (default, must be 0)
    OT_FLAT,            ; OFFSET:FLAT
    OT_SEGMENT          ; OFFSET:SEGMENT
    }

.enum line_output_flags {
    LOF_LISTED  = 1,    ; line written to .LST file
    LOF_SKIPPOS = 2,    ; suppress setting list_pos
    }


; flags for win64_flags

.enum win64_flag_values {
    W64F_SAVEREGPARAMS  = 0x01, ; 1=save register params in shadow space on proc entry
    W64F_AUTOSTACKSP    = 0x02, ; 1=calculate required stack space for arguments of INVOKE
    W64F_STACKALIGN16   = 0x04, ; 1=stack variables are 16-byte aligned; added in v2.12
    W64F_ALL            = 0x07  ; all valid flags
    }

; codeview debug info extend

.enum cvex_values {
    CVEX_MIN        = 0,    ; globals
    CVEX_REDUCED    = 1,    ; globals and locals
    CVEX_NORMAL     = 2,    ; globals, locals and types
    CVEX_MAX        = 3     ; globals, locals, types and constants
    }

; codeview debug info option flags

.enum cvoption_flags {
    CVO_STATICTLS = 1       ; handle static tls
    }

.enum seg_type {
    SEGTYPE_UNDEF,
    SEGTYPE_CODE,
    SEGTYPE_DATA,
    SEGTYPE_BSS,
    SEGTYPE_STACK,
    SEGTYPE_ABS,
    SEGTYPE_HDR,   ; only used in bin.c for better sorting
    SEGTYPE_CODE16,; v2.19: only used in bin.c for better sorting
    SEGTYPE_CDATA, ; only used in bin.c for better sorting
    SEGTYPE_RELOC, ; only used in bin.c for better sorting
    SEGTYPE_RSRC,  ; only used in bin.c for better sorting
    SEGTYPE_ERROR, ; must be last - an "impossible" segment type
    }

define CSF_GRPCHK       1

define CSI_TEXT         0
define CSI_DATA         1
define CSI_CONST        2
define CSI_BSS          3

define BLOCK_ACTIVE     0
define BLOCK_INACTIVE   1
define BLOCK_DONE       2

define SIT_FILE         0
define SIT_MACRO        1

.enum avx_encoding {
    PREFER_FIRST    = 0x00,    ; Use first defined form if possible.
    PREFER_VEX      = 0x01,    ; Use VEX encoding in preference to EVEX encoding.
    PREFER_VEX3     = 0x02,    ; Use 3-byte VEX encoding in preference to EVEX encoding.
    PREFER_EVEX     = 0x04,    ; Use EVEX encoding in preference to VEX encoding.
    NO_EVEX         = 0x08,    ; Don't encode using EVEX.
    }

    qnode_t         typedef ptr qnode
    qdesc_t         typedef ptr qdesc
    qitem_t         typedef ptr qitem
    qditem_t        typedef ptr qditem
    dlldesc_t       typedef ptr dll_desc
    srcitem_t       typedef ptr src_item
    hllitem_t       typedef ptr hll_item
    stritem_t       typedef ptr str_item
    nspace_t        typedef ptr nsp_item


.template hll_item
    next            hllitem_t ?
    caselist        hllitem_t ?
    union
ifdef _WIN64
     value          int64_t ?
else
     struct
      value         int_t ?
      hvalue        int_t ?
     ends
endif
     labels         uint_t 4 dup(?) ; labels for LTEST, LEXIT, LSTART
    ends
    condlines       string_t ?  ; .WHILE/ELSEIF/CASE-blocks only: lines to add after 'test' label
    cmd             int_t ?     ; start cmd (IF, WHILE, REPEAT)
    tokval          int_t ?     ; v2.33.67: added
    union
     flags          dd ?        ; v2.08: added
     record                     ; v2.36.40: added
      ElseOccured   dd : 1 ?
      WhileMode     dd : 1 ?    ; Expression delayed
      Expression    dd : 1 ?    ; Has expression
      DefaultCase   dd : 1 ?    ; Case is .default
      ExpDelayed    dd : 1 ?    ; Expansion delayed - see DelayExpand()
      SwitchJump    dd : 1 ?    ; Direct jump (no test)
      SwitchReg     dd : 1 ?    ; Switch arg is register
      SwitchMem     dd : 1 ?    ; Switch arg is memory
      Switch16      dd : 1 ?    ; Switch Arg size
      Switch32      dd : 1 ?
      Switch64      dd : 1 ?
      Switch3264    dd : 1 ?
      CaseIsConst   dd : 1 ?    ; Case arg is const
      CaseInTable   dd : 1 ?    ; Case is in jump table
      EndOccured    dd : 1 ?    ; Jump exit in .case omitted
      SizeDB        dd : 1 ?    ; Flag Extension B - BYTE
      SizeDW        dd : 1 ?    ; Flag Extension W - WORD
      SizeDD        dd : 1 ?    ; Flag Extension D - DWORD
      Signed        dd : 1 ?    ; Flag Extension S - Signed
      Structured    dd : 1 ?    ; Structured (Pascal) switch where each .CASE is a closed branch
      SwitchTable   dd : 1 ?    ; If SwitchJump direct .case jump
      SwitchTData   dd : 1 ?    ; Jump table in data segment -- SwitchJump
     ends
    ends
   .ends

.template nsp_item
    next            nspace_t ?
    name            string_t ?
   .ends

.template str_item
    string          string_t ?
    next            stritem_t ?
    count           int_t ?
    index           int_t ?
    unicode         db ?
   .ends

.template qditem
    next            qditem_t ?
    size            uint_t ?
   .ends

.template dll_desc
    next            dlldesc_t ?
    cnt             int_t ?
    name            char_t ?
   .ends

.template qitem
    next            qitem_t ?
    value           db ?
   .ends

.template qnode
    next            qnode_t ?
    union
     elmt           qnode_t ?
     sym            asym_t ?
    ends
   .ends

.template qdesc
    head            qdesc_t ?
    tail            qdesc_t ?
   .ends

.template src_item
    next            srcitem_t ?
    type            dw ?        ; item type ( see enum src_item_type )
    srcfile         dw ?        ; index of file in ModuleInfo.FNames
    union
     content        ptr_t ?     ; generic
     file           ptr FILE ?  ; if item is a file
     mi             ptr macro_instance ? ; if item is a macro
    ends
    line_num        uint_t ?    ; current line #
   .ends


.template format_options
    init            proc local
    invalid_fixup_type sword ?
    formatname      char_t 6 dup(?)
   .ends

.template com_item
    cmd             dd ?
    class           string_t ?
    langtype        dd ?
    publsym         asym_t ?  ; .class name : public class
    method          dd ?      ; .INLINE/.OPERATOR/.STATIC
    sym             asym_t ?  ; set by StructDirective()
   .ends

define PE_SUBSYSTEM_NATIVE  0x01
define PE_SUBSYSTEM_GUI     0x02
define PE_SUBSYSTEM_CUI     0x03
define PE_SUBSYSTEM_MASK    0x03
define PE_DLL               0x04

.template global_options
    union
     flags                  dd ?    ; v2.36.40
     record
      case_sensitive        dd: 1 ? ; option casemap
      convert_uppercase     dd: 1 ? ; option casemap
      dotname               dd: 1 ? ; option dotname
      dotnamex              dd: 1 ? ; option dotnamex:<on:off>
      write_listing         dd: 1 ? ; .list/.nolist
      listif                dd: 1 ? ; .listif/.nolistif
      list_generated_code   dd: 1 ? ; .listall, -Sa, -Sg
      pic                   dd: 1 ? ; -fpic | -fno-pic
      endbr                 dd: 1 ? ; -endbr
      masm_compat_gencode   dd: 1 ? ; -Zg option
      cstack                dd: 1 ? ; -Cs
      wstring               dd: 1 ? ; -ws convert "string" to unicode
      lstring               dd: 1 ? ; L"Unicode" used --> allow dw "string"
      switch_structured     dd: 1 ? ; auto insert break after cases
      switch_notable        dd: 1 ? ; no indexed jump table
      switch_regax          dd: 1 ? ; use [R|E]AX to render jump-code
      assert                dd: 1 ? ; -assert Generate .assert code
      assert_pushf          dd: 1 ? ; Push/Pop flags
      ; ----
      mscrt                 dd: 1 ? ; pragma init/exit option
      degbug_frame          dd: 1 ? ; -Z7
     ends
    ends
    record
     quiet                  dd: 1 ? ; -q option
     line_numbers           dd: 1 ? ; -Zd option
     warning_error          dd: 1 ? ; -WX option
     no_error_disp          dd: 1 ? ; -eq option
     process_subdir         dd: 1 ? ; -r option
     no_comment_in_code_rec dd: 1 ? ; -zlc option
     no_opt_farcall         dd: 1 ? ; -zld option
     no_file_entry          dd: 1 ? ; -zlf option
     no_static_procs        dd: 1 ? ; -zlp option
     no_section_aux_entry   dd: 1 ? ; -zls option
     no_cdecl_decoration    dd: 1 ? ; -zcw & -zcm option
     no_export_decoration   dd: 1 ? ; -zze option
     entry_decorated        dd: 1 ? ; -zzs option
     write_impdef           dd: 1 ? ; -Fd option
     preprocessor_stdout    dd: 1 ? ; -EP option
     masm51_compat          dd: 1 ? ; -Zm option
     masm8_proc_visibility  dd: 1 ? ; -Zv8 option
     no_symbol_listing      dd: 1 ? ; -Sn option
     first_pass_listing     dd: 1 ? ; -Sf option
     all_symbols_public     dd: 1 ? ; -Zf option
     safeseh                dd: 1 ? ; -safeseh option
     strict_masm_compat     dd: 1 ? ; -Zne option
     ignore_include         dd: 1 ? ; -X option
     syntax_check_only      dd: 1 ? ; -Zs option
     pe_dll                 dd: 1 ? ; -dll
     chkstack               dd: 1 ? ; _chkstk()
     nolib                  dd: 1 ? ; skip includelib directives
     no_linking             dd: 1 ? ; -c        ; assembles only
     link_mt                dd: 1 ? ; -MT used, -c not used --> use LIBC
     float_used             dd: 1 ? ; float used as :vararg param
     main_found             dd: 1 ? ; [w]main proc defined
     argv_used              dd: 1 ? ; [w]main has params
    ends
    floating_point          dd ?    ; -FPi, -FPi87
    error_limit             dd ?    ; -e option
    names                   string_t OPTN_LAST dup(?) ; char *  4
    queues                  ptr_t OPTQ_LAST dup(?)  ; qitem * 4
    link_exename            string_t ? ; -Fe<exename>
    link_linker             string_t ? ; -link<:linker>
    link_options            string_t ? ; -link <options...>
    link_objects            string_t ? ; -link [options...] <.OBJ files>
    list_macro              dd ?    ; -Sa option
    output_format           dd ?    ; -bin, -omf, -coff, -elf options
    sub_format              dd ?    ; -mz, -pe, -win64, -elf64 options
    langtype                dd ?    ; -Gc|d|z option
    _model                  dd ?    ; -mt|s|m|c|l|h|f option
    cpu                     dd ?    ; -0|1|2|3|4|5|6 & -fp{0|2|3|5|6|c} option
    fctype                  dd ?    ; -zf0 & -zf1 option
    codepage                dd ?    ; Unicode code page
    floatdigits             dd ?    ; option floatdigits:<value>
    frame_auto              db ?    ; win64 only
    debug_symbols           db ?    ; -Zi option
    debug_ext               db ?    ; -Zi option numeric argument
    warning_level           db ?    ; -Wn option
    link                    db ?    ; -link option
    stdcall_decoration      db ?    ; -zt<0|1|2> option
    floatformat             db ?    ; option floatformat:<e|f|g>
    flt_size                db ?    ; option float:<4|8>
    fieldalign              db ?    ; -Zp option
    loopalign               db ?    ; OPTION:LOOPALIGN setting
    casealign               db ?    ; OPTION:CASEALIGN setting
    segmentalign            db ?    ; -Sp[n] Set segment alignment
    pe_subsystem            db ?    ; -cui, -gui
    win64_flags             db ?    ; -homeparams, -autostack, -stackalign
    arch                    db ?    ; -arch:AVX[2|512]
    iddc                    db ?    ; -idd
   .ends


.template module_info
    union
     flags                  dd ?    ; v2.36.40
     record
      case_sensitive        dd: 1 ? ; option casemap
      convert_uppercase     dd: 1 ? ; option casemap
      dotname               dd: 1 ? ; option dotname
      dotnamex              dd: 1 ? ; option dotnamex:<on:off>
      list                  dd: 1 ? ; .list/.nolist
      listif                dd: 1 ? ; .listif/.nolistif
      list_generated_code   dd: 1 ? ; .listall, -Sa, -Sg
      pic                   dd: 1 ? ; -fpic | -fno-pic
      endbr                 dd: 1 ? ; -endbr
      masm_compat_gencode   dd: 1 ? ; -Zg option
      cstack                dd: 1 ? ; -Cs
      wstring               dd: 1 ? ; -ws convert "string" to unicode
      lstring               dd: 1 ? ; L"Unicode" used --> allow dw "string"
      switch_structured     dd: 1 ? ; auto insert break after cases
      switch_notable        dd: 1 ? ; no indexed jump table
      switch_regax          dd: 1 ? ; use [R|E]AX to render jump-code
      assert                dd: 1 ? ; -assert Generate .assert code
      assert_pushf          dd: 1 ? ; Push/Pop flags
      ; ----
      procs_private         dd: 1 ? ; option proc:private
      procs_export          dd: 1 ? ; option proc:export
      ljmp                  dd: 1 ? ; option ljmp
      m510                  dd: 1 ? ; option m510
      scoped                dd: 1 ? ; option scoped
      oldstructs            dd: 1 ? ; option oldstructs
      oldmacros             dd: 1 ? ; v2.19: option oldmacros
      setif2                dd: 1 ? ; option setif2
      cref                  dd: 1 ? ; .cref/.nocref
      StartupDirectiveFound dd: 1 ? ;
      EndDirFound           dd: 1 ? ;
      NoSignExtend          dd: 1 ? ; option nosignextend
     ends
    ends

    Ofssize                 db ?    ; current offset size (USE16,USE32,USE64)
    defOfssize              db ?    ; default segment offset size (16,32 [,64]-bit)
    wordsize                db ?    ; current word size (2,4,8)
    fctype                  db ?    ; fastcall type
    radix                   db ?    ; current .RADIX setting
    langtype                db ?    ; language
    fieldalign              db ?    ; -Zp, OPTION:FIELDALIGN setting
    sub_format              db ?    ; sub-output format
    cpu                     dd ?    ; cpu setting (value @cpu symbol);
    curr_cpu                dd ?    ; cpu setting (OW stylex);
    srcfile                 dd ?    ; main source file - is an index for FNames[]
    hll_label               dd ?    ; hll directive label counter
    _model                  db ?    ; memory model
    line_flags              db ?    ; current line has been printed
    offsettype              db ?    ; OFFSET:GROUP|FLAT|SEGMENT
    inside_comment          db ?    ; v2.10: moved from tokenize.c
    segorder                db ?    ; .alpha, .seq, .dosseg
    distance                db ?    ; stack distance
    procalign               db ?    ; current OPTION:PROCALIGN setting
    ostype                  db ?    ; operating system
    simseg_init             db ?    ; simplified segm dir flags
    simseg_defd             db ?    ; v2.09: flag if seg was defined before simseg dir
    PhaseError              db ?    ; phase error flag
    CommentDataInCode       db ?    ; OMF: emit coment records about data in code segs
    prologuemode            db ?    ; current PEM_ enum value for OPTION PROLOGUE
    epiloguemode            db ?    ; current PEM_ enum value for OPTION EPILOGUE
    invoke_exprparm         db ?    ; flag: forward refs for INVOKE params ok?
    cv_opt                  db ?    ; option codeview
    emulator                db ?    ; option emulator
    frame_auto              db ?    ; win64 only
    loopalign               db ?    ; OPTION:LOOPALIGN setting
    casealign               db ?    ; OPTION:CASEALIGN setting
    floatformat             db ?    ; option floatformat:<e|f|g>
    flt_size                db ?    ; option float:<4|8>
    avxencoding             db ?    ; option avxencoding:<>
    union
     struct
      elf_osabi             db ?    ; for ELF
      win64_flags           db ?    ; for WIN64 + PE(32+)
     ends
     struct
      mz_ofs_fixups         dw ?    ; for MZ
      mz_alignment          dw ?
      mz_heapmin            dw ?
      mz_heapmax            dw ?
     ends
    ends
    currseg                 asym_t ?        ; currently active segment - asym *
    flat_grp                asym_t ?        ; magic FLAT group - asym *
    pCodeBuff               ptr byte ?
    currcomment             string_t ?      ; current comment
    accumulator             int_t ?         ; AX/EAX/RAX
    GeneratedCode           dd ?            ; nesting level generated code
    token_count             int_t ?         ; number of tokens in curr line
    basereg                 dd 3 dup(?)     ; stack base register (16-, 32-, 64-bit
    class_reg               dd ?
    name                    db 260 dup(?)   ; name of module
    assert_proc             string_t ?      ; .assert:<proc/macro name>
    proc_prologue           string_t ?      ; prologue macro if PEM_MACRO
    proc_epilogue           string_t ?      ; epilogue macro if PEM_MACRO
    proc_usescnt            uint_t ?
    proc_usesregs           uint_t 7 dup(?)
    CurrDll                 ptr dll_desc ?  ; OPTION DLLIMPORT dll
    fmtopt                  ptr format_options ? ; v2.07: added
    codepage                dd ?
    class_label             dd ?
    floatdigits             int_t ?         ; option floatdigits:<value>
    list_macro              dd ?            ; current .LISTMACRO setting
;--------
    tokenarray              token_t ?       ; start token buffer
    currsource              string_t ?      ; current source line
    stringbufferend         string_t ?      ; start free space in string buffer
    curr_file               LPFILE NUM_FILE_TYPES dup(?) ; ASM, ERR, OBJ and LST
    curr_fname              string_t NUM_FILE_TYPES dup(?)
    FNames                  array_t ?       ; array of input files
    cnt_fnames              dd ?            ; items in FNames array
    maxlinelen              dd ?
    PubQueue                qdesc <>        ; PUBLIC items
    LnameQueue              qdesc <>        ; LNAME items (segments, groups and classes)
    SafeSEHQueue            qdesc <>        ; list of safeseh handlers
    LibQueue                qdesc <>        ; includelibs
    LinkQueue               qdesc <>        ; .pragma comment(linker,"/..")
    DllQueue                ptr dll_desc ?  ; dlls of OPTION DLLIMPORT
    imp_prefix              string_t ?      ;
    IncludePath             string_t ?      ;
    line_queue              qdesc <>        ; line queue
    src_stack               ptr src_item ?  ; source item (files & macros) stack
    union
     start_fixup            ptr fixup ?     ; OMF only
     start_label            asym_t ?        ; non-OMF only: start label
    ends
    StrStack                stritem_t ?     ; v2.20 String stack
    HllStack                hllitem_t ?     ; for .WHILE, .IF, .REPEAT
    HllFree                 hllitem_t ?     ; v2.06: stack of free <struct hll>-items
    ComStack                ptr com_item ?  ; v2.27: .CLASSDEF, .COMDEF, .ENDS
    RetStack                hllitem_t ?     ; v2.30: .return info
    FltStack                stritem_t ?     ; v2.31 float stack
    NspStack                ptr nsp_item ?  ; v2.33 namespace stack
    ContextStack            ptr byte ?
    ContextFree             ptr byte ?      ; v2.10: "free items" heap implemented.
    SavedContexts           ptr byte ?
    cntSavedContexts        int_t ?
    anonymous_label         uint_t ?        ; "anonymous label" counter
    StackBase               asym_t ?
    ProcStatus              asym_t ?
    WriteModule             proc local
    EndDirHook              proc local
    Pass1Checks             proc local
    pe_flags                uint_t ?
    error_count             uint_t ?        ; total of errors so far
    warning_count           uint_t ?        ; total of warnings so far
    num_segs                uint_t ?        ; number of segments in module
    start_displ             uint_t ?        ; OMF only, optional displ for start label
   .ends

TokenCount              equ <MODULE.token_count>
TokenArray              equ <MODULE.tokenarray>
CurrSource              equ <MODULE.currsource>
CurrWordSize            equ <MODULE.wordsize>
CurrFile                equ <MODULE.curr_file>
CurrSeg                 equ <MODULE.currseg>
CurrFName               equ <MODULE.curr_fname>
StringBufferEnd         equ <MODULE.stringbufferend>
CurrComment             equ <MODULE.currcomment>
MaxLineLength           equ <MODULE.maxlinelen>

externdef               StringBuffer    : string_t
externdef               CommentBuffer   : string_t
externdef               Parse_Pass      : uint_t
externdef               ModuleInfo      : module_info
externdef               Options         : global_options
externdef               write_to_file   : uint_t
externdef               DefaultDir      : string_t      ; * NUM_FILE_TYPES
externdef               MacroLevel      : uint_t
externdef               LinnumQueue     : qdesc
externdef               ModelToken      : string_t
externdef               LastCodeBufSize : int_t
externdef               stackreg        : uint_t
externdef               szDgroup        : char_t        ; DGROUP


AssembleModule          proto __ccall :string_t
close_files             proto __ccall
CmdlineFini             proto __ccall
ParseCmdline            proto __ccall :ptr string_t, :ptr int_t
write_usage             proto __ccall
define_name             proto __ccall :string_t, :string_t
undef_name              proto __ccall :string_t

asmerr                  proto __ccall :int_t, :vararg
DelayExpand             proto fastcall :token_t

write_logo              proto __ccall
SetCPU                  proto __ccall :int_t
OutputByte              proto __ccall :int_t
FillDataBytes           proto __ccall :byte, :int_t
OutputBytes             proto __ccall :ptr byte, :int_t, :ptr fixup
AddLinnumDataRef        proto __ccall :uint_t, :uint_t
myltoa                  proto __ccall :qword, :string_t, :uint_t, :int_t, :int_t
write_options           proto __ccall
ConvertSectionName      proto __ccall :asym_t, :ptr dword, :string_t
SetMasm510              proto __ccall :int_t
GetType                 proto __ccall :string_t, :ptr expr, :string_t, :int_t
RetLineQueue            proto __ccall


tprintf                 proto __ccall :string_t, :vararg
tsprintf                proto __ccall :string_t, :string_t, :vararg
tfprintf                proto __ccall :ptr FILE, :string_t, :vararg
tvsprintf               proto __ccall :string_t, :string_t, :ptr
tvfprintf               proto __ccall :ptr FILE, :string_t, :ptr
tstrupr                 proto fastcall :string_t

tmemcpy                 proto fastcall :ptr, :ptr, :uint_t
tmemmove                proto fastcall :ptr, :ptr, :uint_t
tmemcmp                 proto fastcall :ptr, :ptr, :uint_t
tmemicmp                proto fastcall :ptr, :ptr, :uint_t
tmemset                 proto fastcall :ptr, :int_t, :uint_t
tstrlen                 proto fastcall :string_t
tstrchr                 proto fastcall :string_t, :int_t
tstrrchr                proto fastcall :string_t, :int_t
tstrcpy                 proto fastcall :string_t, :string_t
tstrcat                 proto fastcall :string_t, :string_t
tstrncpy                proto fastcall :string_t, :string_t, :int_t
tstrcmp                 proto fastcall :string_t, :string_t
tstricmp                proto fastcall :string_t, :string_t
tstrstr                 proto fastcall :string_t, :string_t
tgetenv                 proto fastcall :string_t
tstrstart               proto fastcall :string_t

PQSORTCMDT              typedef proto fastcall :ptr, :ptr
PQSORTCMD               typedef ptr PQSORTCMDT

tqsort                  proto __ccall :ptr, :int_t, :int_t, :PQSORTCMD
QEnqueue                proto fastcall :qdesc_t, :ptr
QAddItem                proto fastcall :qdesc_t, :ptr

NameSpace               proto watcall :string_t, :string_t
NameSpaceDirective      proto __ccall :int_t, :token_t

CreateConstant          proto __ccall :token_t
CreateVariable          proto __ccall :string_t, :int_t

Mangle                  proto __ccall :asym_t, :string_t
SetMangler              proto __ccall :asym_t, :int_t, :string_t

endif
.pragma list(pop)
