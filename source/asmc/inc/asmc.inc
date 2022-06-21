; ASMC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)

ifndef __ASMC_INC
define __ASMC_INC

option dotname

include version.inc
include stdio.inc
include stdlib.inc
include string.inc
include inttype.inc

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
ifdef __UNIX__
define _LIN64
endif
define .lodsd <lodsq>
define .stosd <stosq>
define .movsd <movsq>
.32 macro upc:vararg
    endm
.64 macro upc:vararg
    upc
    endm
.l8 macro mem
    mov rax,mem
    endm
.s8 macro mem
    mov mem,rax
    endm
.z8 macro mem, reg
    mov mem,reg
    endm
else
define .lodsd <lodsd>
define .stosd <stosd>
define .movsd <movsd>
.32 macro upc:vararg
    upc
    endm
.64 macro upc:vararg
    endm
.l8 macro mem
    mov edx,dword ptr mem[4]
    mov eax,dword ptr mem
    endm
.s8 macro mem
    mov dword ptr mem,eax
    mov dword ptr mem[4],edx
    endm
.z8 macro mem, reg
    mov dword ptr mem,reg
    mov dword ptr mem[4],reg
    endm
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

define MAX_IF_NESTING       20   ; IFxx block nesting. Must be <=32, see condasm.asm
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
include queue.inc
include namespace.inc

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
    LANG_WATCALL    = 9
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
    SEGTYPE_CDATA, ; only used in bin.c for better sorting
    SEGTYPE_RELOC, ; only used in bin.c for better sorting
    SEGTYPE_RSRC,  ; only used in bin.c for better sorting
    SEGTYPE_ERROR, ; must be last - an "impossible" segment type
    }

define CSF_GRPCHK      1

define CSI_TEXT        0
define CSI_DATA        1
define CSI_CONST       2
define CSI_BSS         3

define BLOCK_ACTIVE    0
define BLOCK_INACTIVE  1
define BLOCK_DONE      2

define SIT_FILE        0
define SIT_MACRO       1

.template qditem
    next            ptr qditem ?
    size            uint_t ?
   .ends

.template dll_desc
    next            ptr dll_desc ?
    cnt             int_t ?
    name            char_t ?
   .ends
    dlldesc_t       typedef ptr dll_desc

.template qitem
    next            ptr qitem ?
    value           db ?
   .ends

.template src_item
    next            ptr src_item ?
    type            dw ?    ; item type ( see enum src_item_type )
    srcfile         dw ?    ; index of file in ModuleInfo.FNames
    union
     content        ptr_t ? ; generic
     file           ptr_t ? ; if item is a file
     mi             ptr_t ? ; if item is a macro
    ends
    line_num        uint_t ? ; current line #
   .ends
    srcitem_t       typedef ptr src_item


.template format_options
    init            proc local fastcall :ptr module_info
    invalid_fixup_type sword ?
    formatname      char_t 6 dup(?)
   .ends

.template com_item
    cmd         dd ?
    class       string_t ?
    langtype    dd ?
    publsym     ptr asym ?  ; .class name : public class
    method      dd ?        ; .INLINE/.OPERATOR/.STATIC
    sym         ptr asym ?  ; set by StructDirective()
   .ends


.template global_options
    quiet                   db ?    ; -q option
    line_numbers            db ?    ; -Zd option
    debug_symbols           db ?    ; -Zi option
    debug_ext               db ?    ; -Zi option numeric argument
    floating_point          dd ?    ; -FPi, -FPi87
    error_limit             dd ?    ; -e option
    no_error_disp           db ?    ; -eq option
    warning_level           db ?    ; -Wn option
    warning_error           db ?    ; -WX option
    process_subdir          db ?    ; -r option
    names                   string_t OPTN_LAST dup(?) ; char *  4
    queues                  ptr_t OPTQ_LAST dup(?)  ; qitem * 4
    no_comment_in_code_rec  db ?    ; -zlc option
    no_opt_farcall          db ?    ; -zld option
    no_file_entry           db ?    ; -zlf option
    no_static_procs         db ?    ; -zlp option
    no_section_aux_entry    db ?    ; -zls option
    no_cdecl_decoration     db ?    ; -zcw & -zcm option
    stdcall_decoration      db ?    ; -zt<0|1|2> option
    no_export_decoration    db ?    ; -zze option
    entry_decorated         db ?    ; -zzs option
    write_listing           db ?    ; -Fl option
    write_impdef            db ?    ; -Fd option
    case_sensitive          db ?    ; -C<p|x|u> options
    convert_uppercase       db ?    ; -C<p|x|u> options
    preprocessor_stdout     db ?    ; -EP option
    masm51_compat           db ?    ; -Zm option
    strict_masm_compat      db ?    ; -Zne option
    masm_compat_gencode     db ?    ; -Zg option
    masm8_proc_visibility   db ?    ; -Zv8 option
    listif                  db ?    ; -Sx, -Sa option
    list_generated_code     db ?    ; -Sg, -Sa option
    list_macro              dd ?    ; -Sa option
    no_symbol_listing       db ?    ; -Sn option
    first_pass_listing      db ?    ; -Sf option
    all_symbols_public      db ?    ; -Zf option
    safeseh                 db ?    ; -safeseh option
    output_format           dd ?    ; -bin, -omf, -coff, -elf options
    sub_format              dd ?    ; -mz, -pe, -win64, -elf64 options
    langtype                dd ?    ; -Gc|d|z option
    _model                  dd ?    ; -mt|s|m|c|l|h|f option
    cpu                     dd ?    ; -0|1|2|3|4|5|6 & -fp{0|2|3|5|6|c} option
    fctype                  dd ?    ; -zf0 & -zf1 option
    codepage                dd ?    ; Unicode code page
    ignore_include          db ?    ; -X option
    fieldalign              db ?    ; -Zp option
    syntax_check_only       db ?    ; -Zs option
    xflag                   db ?    ; extended option
    loopalign               db ?    ; OPTION:LOOPALIGN setting
    casealign               db ?    ; OPTION:CASEALIGN setting
    epilogueflags           db ?    ; OPTION EPILOGUE: FLAGS
    segmentalign            db ?    ; -Sp[n] Set segment alignment
    pe_subsystem            db ?    ; -cui, -gui
    win64_flags             db ?    ; -homeparams, -autostack, -stackalign
    chkstack                db ?    ; _chkstk()
    nolib                   db ?    ; skip includelib directives
    masm_keywords           db ?    ; -Znk
    arch                    db ?    ; -arch:AVX[2|512]
    frame_auto              db ?    ; -frame
    floatformat             db ?    ; option floatformat:<e|f|g>
    floatdigits             dd ?    ; option floatdigits:<value>
    flt_size                db ?    ; option float:<4|8>
    pic                     db ?    ; -fpic | -fno-pic
    endbr                   db ?    ; -endbr
   .ends

.template module_vars
    error_count             uint_t ?        ; total of errors so far
    warning_count           uint_t ?        ; total of warnings so far
    num_segs                uint_t ?        ; number of segments in module
    PubQueue                qdesc <>        ; PUBLIC items
    LnameQueue              qdesc <>        ; LNAME items (segments, groups and classes)
    SafeSEHQueue            qdesc <>        ; list of safeseh handlers
    LibQueue                qdesc <>        ; includelibs
    LinkQueue               qdesc <>        ; .pragma comment(linker,"/..")
    DllQueue                ptr dll_desc ?  ; dlls of OPTION DLLIMPORT
    imp_prefix              string_t ?              ;
    curr_file               LPFILE NUM_FILE_TYPES dup(?) ; ASM, ERR, OBJ and LST
    curr_fname              string_t NUM_FILE_TYPES dup(?)
    FNames                  array_t ?       ; array of input files
    cnt_fnames              uint_t ?        ; items in FNames array
    IncludePath             string_t ?              ;
    line_queue              qdesc <>        ; line queue
    src_stack               ptr src_item ?  ; source item (files & macros) stack
    union
     start_fixup            ptr fixup ?     ; OMF only
     start_label            ptr asym ?      ; non-OMF only: start label
    ends
    start_displ             uint_t ?        ; OMF only, optional displ for start label
    StrStack                ptr str_item ?  ; v2.20 String stack
    HllStack                ptr hll_item ?  ; for .WHILE, .IF, .REPEAT
    HllFree                 ptr hll_item ?  ; v2.06: stack of free <struct hll>-items
    ComStack                ptr com_item ?  ; v2.27: .CLASSDEF, .COMDEF, .ENDS
    RetStack                ptr hll_item ?  ; v2.30: .return info
    FltStack                ptr flt_item ?  ; v2.31 float stack
    NspStack                ptr nsp_item ?  ; v2.33 namespace stack
    ContextStack            ptr byte ?
    ContextFree             ptr byte ?      ; v2.10: "free items" heap implemented.
    SavedContexts           ptr byte ?
    cntSavedContexts        int_t ?
    anonymous_label         uint_t ?        ; "anonymous label" counter
    StackBase               ptr asym ?
    ProcStatus              ptr asym ?
    WriteModule             proc local __ccall :ptr module_info
    EndDirHook              proc local fastcall :ptr module_info
    Pass1Checks             proc local fastcall :ptr module_info
    pe_flags                uint_t ?
    max_line_len            uint_t ?
   .ends

.template module_info : public module_vars
    proc_prologue           string_t ?      ; prologue macro if PEM_MACRO
    proc_epilogue           string_t ?      ; epilogue macro if PEM_MACRO
    CurrDll                 ptr dll_desc ?  ; OPTION DLLIMPORT dll
    fmtopt                  ptr format_options ? ; v2.07: added
    hll_label               dd ?    ; hll directive label counter
    distance                db ?    ; stack distance
    _model                  db ?    ; memory model
    langtype                db ?    ; language
    ostype                  db ?    ; operating system
    sub_format              db ?    ; sub-output format
    fctype                  db ?    ; fastcall type
    segorder                db ?    ; .alpha, .seq, .dosseg
    offsettype              db ?    ; OFFSET:GROUP|FLAT|SEGMENT
    cpu                     dd ?    ; cpu setting (value @cpu symbol);
    curr_cpu                dd ?    ; cpu setting (OW stylex);
    radix                   db ?    ; current .RADIX setting
    fieldalign              db ?    ; -Zp, OPTION:FIELDALIGN setting
    line_flags              db ?    ; current line has been printed
    procalign               db ?    ; current OPTION:PROCALIGN setting
    list_macro              dd ?    ; current .LISTMACRO setting
    Ofssize                 db ?    ; current offset size (USE16,USE32,USE64)
    defOfssize              db ?    ; default segment offset size (16,32 [,64]-bit)
    wordsize                db ?    ; current word size (2,4,8)
    inside_comment          db ?    ; v2.10: moved from tokenize.c
    case_sensitive          db ?    ; option casemap
    convert_uppercase       db ?    ; option casemap
    procs_private           db ?    ; option proc:private
    procs_export            db ?    ; option proc:export
    dotname                 db ?    ; option dotname
    ljmp                    db ?    ; option ljmp
    m510                    db ?    ; option m510
    scoped                  db ?    ; option scoped
    oldstructs              db ?    ; option oldstructs
    emulator                db ?    ; option emulator
    setif2                  db ?    ; option setif2
    list                    db ?    ; .list/.nolist
    cref                    db ?    ; .cref/.nocref
    listif                  db ?    ; .listif/.nolistif
    list_generated_code     db ?    ; .listall, -Sa, -Sg
    StartupDirectiveFound   db ?
    EndDirFound             db ?
    frame_auto              db ?    ; win64 only
    NoSignExtend            db ?    ; option nosignextend
    simseg_init             db ?    ; simplified segm dir flags
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
    simseg_defd             db ?            ; v2.09: flag if seg was defined before simseg dir
    PhaseError              db ?            ; phase error flag
    CommentDataInCode       db ?            ; OMF: emit coment records about data in code segs
    prologuemode            db ?            ; current PEM_ enum value for OPTION PROLOGUE
    epiloguemode            db ?            ; current PEM_ enum value for OPTION EPILOGUE
    invoke_exprparm         db ?            ; flag: forward refs for INVOKE params ok?
    cv_opt                  db ?            ; option codeview
    strict_masm_compat      db ?            ; -Zne option
    srcfile                 uint_t ?        ; main source file - is an index for FNames[]
    currseg                 ptr dsym ?      ; currently active segment - dsym *
    flat_grp                ptr dsym ?      ; magic FLAT group - dsym *
    pCodeBuff               ptr byte ?
    GeneratedCode           uint_t ?        ; nesting level generated code
    currsource              string_t ?      ; current source line
    CurrComment             string_t ?      ; current comment
    tokenarray              ptr asm_tok ?   ; start token buffer
    stringbufferend         string_t ?      ; start free space in string buffer
    token_count             int_t ?         ; number of tokens in curr line
    basereg                 uint_t 3 dup(?) ; stack base register (16-, 32-, 64-bit
    name                    db 260 dup(?)   ; name of module
    xflag                   db ?            ; extended option
    loopalign               db ?            ; OPTION:LOOPALIGN setting
    casealign               db ?            ; OPTION:CASEALIGN setting
    epilogueflags           db ?            ; OPTION EPILOGUE: FLAGS
    assert_proc             string_t ?      ; .assert:<proc/macro name>
    codepage                uint_t ?
    class_label             uint_t ?
    floatdigits             int_t ?         ; option floatdigits:<value>
    floatformat             db ?            ; option floatformat:<e|f|g>
    flt_size                db ?            ; option float:<4|8>
    pic                     db ?            ; -fpic | -fno-pic
    endbr                   db ?            ; -endbr
   .ends

Token_Count             equ <ModuleInfo.token_count>
CurrSource              equ <ModuleInfo.currsource>
CurrWordSize            equ <ModuleInfo.wordsize>
CurrFile                equ <ModuleInfo.curr_file>
CurrSeg                 equ <ModuleInfo.currseg>
CurrFName               equ <ModuleInfo.curr_fname>
StringBufferEnd         equ <ModuleInfo.stringbufferend>

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
externdef               regax           : uint_t
externdef               szDgroup        : char_t        ; DGROUP


AssembleModule          proto __ccall :string_t
close_files             proto __ccall
CmdlineFini             proto __ccall
ParseCmdline            proto __ccall :ptr string_t, :ptr int_t
write_usage             proto __ccall
define_name             proto __ccall :string_t, :string_t

asmerr                  proto __ccall :int_t, :vararg
DelayExpand             proto fastcall :token_t
AsmcKeywords            proto __ccall :int_t

write_logo              proto __ccall
SetCPU                  proto __ccall :int_t
OutputByte              proto __ccall :int_t
FillDataBytes           proto __ccall :byte, :int_t
OutputBytes             proto __ccall :ptr byte, :int_t, :ptr fixup
AddLinnumDataRef        proto __ccall :uint_t, :uint_t
myltoa                  proto __ccall :qword, :string_t, :uint_t, :int_t, :int_t
write_options           proto __ccall
ConvertSectionName      proto __ccall :ptr asym, :ptr dword, :string_t
SetMasm510              proto __ccall :int_t
GetType                 proto __ccall :string_t, :ptr expr, :string_t, :int_t
RetLineQueue            proto __ccall


tprintf                 proto __ccall :string_t, :vararg
tsprintf                proto __ccall :string_t, :string_t, :vararg
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

endif
.pragma list(pop)
