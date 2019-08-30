; ASMC.INC--
; Doszip Macro Assembler
ifndef __ASMC_INC
__ASMC_INC equ <>

include version.inc

include stdio.inc
include stdlib.inc
include string.inc

.pragma list(push, 0)

OLDKEYWORDS         equ 1 ;; NAME, SIZE, ..
CHEXPREFIX          equ 1 ;; 0x prefix

MAX_LINE_LEN        equ 2048                ; no restriction for this number
MAX_STRING_LEN      equ MAX_LINE_LEN - 32   ; must be < MAX_LINE_LEN
MAX_ID_LEN          equ 247                 ; must be < MAX_LINE_LEN
MAX_TOKEN           equ MAX_LINE_LEN / 4    ; max tokens in one line
MAX_STRUCT_ALIGN    equ 32
MAX_SEGMENT_ALIGN   equ 4096

MAX_IF_NESTING      equ 20  ;; IFxx block nesting. Must be <=32, see condasm.asm
MAX_SEG_NESTING     equ 20  ;; limit for segment nesting
MAX_MACRO_NESTING   equ 100 ;; macro call nesting
MAX_STRUCT_NESTING  equ 32  ;; limit for "anonymous structs" only
MAX_LNAME           equ 255 ;; OMF lnames - length must fit in 1 byte
LNAME_NULL          equ 0   ;; OMF first entry in lnames array

option fieldalign:4

include symbols.inc
include errmsg.inc      ;; must be located AFTER #defines lines
include queue.inc
include ltype.inc
include token.inc

EMPTY           equ -2  ;; function return values
ERROR           equ -1
NOT_ERROR       equ 0
STRING_EXPANDED equ 1

PASS_1          equ 0
PASS_2          equ 1

OPT_CSTACK      equ 0x01
OPT_WSTRING     equ 0x02 ; convert "string" to unicode
OPT_LSTRING     equ 0x04 ; L"Unicode" used --> allow dw "string"
OPT_PASCAL      equ 0x08 ; auto insert break after cases
OPT_NOTABLE     equ 0x10 ; no indexed jump table
OPT_REGAX       equ 0x20 ; use [R|E]AX to render jump-code
OPT_ASSERT      equ 0x40 ; Generate .assert code
OPT_PUSHF       equ 0x80 ; Push/Pop flags

;; enumerations

; output formats. Order must match formatoptions[] in assemble.asm

OFORMAT_BIN     equ 0   ; used by -bin, -mz and -pe
OFORMAT_OMF     equ 1
OFORMAT_COFF    equ 2   ; used by -coff, -djgpp and -win64
OFORMAT_ELF     equ 3   ; used by -elf and elf64

SFORMAT_NONE    equ 0
SFORMAT_MZ      equ 1   ; MZ binary
SFORMAT_PE      equ 2   ; PE (32- or 64-bit) binary
SFORMAT_64BIT   equ 3   ; 64bit COFF or ELF

FPO_NO_EMULATION equ 0  ; -FPi87 (default)
FPO_EMULATION   equ 1   ; -FPi

LANG_NONE       equ 0   ; language vaules.
LANG_C          equ 1   ; the order cannot be changed, it's
LANG_SYSCALL    equ 2   ; returned by OPATTR and used in user-defined
LANG_STDCALL    equ 3   ; prologue/epilogue.
LANG_PASCAL     equ 4
LANG_FORTRAN    equ 5
LANG_BASIC      equ 6
LANG_FASTCALL   equ 7
LANG_VECTORCALL equ 8

MODEL_NONE      equ 0   ; Memory model type.
MODEL_TINY      equ 1   ; the order cannot be changed, it's
MODEL_SMALL     equ 2   ; the value of the predefined @Model symbol.
MODEL_COMPACT   equ 3
MODEL_MEDIUM    equ 4
MODEL_LARGE     equ 5
MODEL_HUGE      equ 6
MODEL_FLAT      equ 7

SIZE_DATAPTR    equ 0x68 ;; far for COMPACT, LARGE, HUGE
SIZE_CODEPTR    equ 0x70 ;; far for MEDIUM, LARGE, HUGE

SEGORDER_SEQ    equ 0   ; .SEQ (default)
SEGORDER_DOSSEG equ 1   ; .DOSSEG
SEGORDER_ALPHA  equ 2   ; .ALPHA

LM_NOLISTMACRO  equ 0   ; .NOLISTMACRO, .LISTMACRO and .LISTMACROALL
LM_LISTMACRO    equ 1   ; directives setting
LM_LISTMACROALL equ 2

; assume values are used as index in codegen.c / invoke.c.
; Order must match the one in special.h. Don't change!

ASSUME_NOTHING  equ EMPTY
ASSUME_ES       equ 0
ASSUME_CS       equ 1
ASSUME_SS       equ 2
ASSUME_DS       equ 3
ASSUME_FS       equ 4
ASSUME_GS       equ 5

; bit count from left:
; bit 0-2:        Math coprocessor
; bit 3:          privileged?
; bit 4-7:        cpu type
; bit 8-15;  extension set
;
P_NO87          equ 0x01 ; no FPU
P_87            equ 0x02 ; 8087
P_287           equ 0x03 ; 80287
P_387           equ 0x04 ; 80387
P_PM            equ 0x08 ; privileged opcode
P_86            equ 0x00 ; 8086, default
P_186           equ 0x10 ; 80186
P_286           equ 0x20 ; 80286
P_386           equ 0x30 ; 80386
P_486           equ 0x40 ; 80486
P_586           equ 0x50 ; pentium
P_686           equ 0x60 ; ppro
P_64            equ 0x70 ; x64 cpu

P_286p          equ P_286 or P_PM   ; 286, priv mode
P_386p          equ P_386 or P_PM   ; 386, priv mode
P_486p          equ P_486 or P_PM   ; 486, priv mode
P_586p          equ P_586 or P_PM   ; 586, priv mode
P_686p          equ P_686 or P_PM   ; 686, priv mode
P_64p           equ P_64 or P_PM    ; x64, priv mode
P_MMX           equ 0x0100          ; MMX extension instructions
P_K3D           equ 0x0200          ; 3DNow extension instructions
P_SSE1          equ 0x0400          ; SSE1 extension instructions
P_SSE2          equ 0x0800          ; SSE2 extension instructions
P_SSE3          equ 0x1000          ; SSE3 extension instructions
P_SSSE3         equ 0x2000          ; SSSE3 extension instructions
P_SSE4          equ 0x4000          ; SSE4 extension instructions
P_AVX           equ 0x8000          ; AVX extension instructions

P_SSEALL        equ P_SSE1 or P_SSE2 or P_SSE3 or P_SSSE3 or P_SSE4 or P_AVX
NO_OPPRFX       equ P_MMX or P_SSEALL
P_FPU_MASK      equ 0x07
P_CPU_MASK      equ 0xF0
P_EXT_MASK      equ P_MMX or P_K3D or P_SSEALL
P_EXT_ALL       equ P_MMX or P_K3D or P_SSEALL

; the MASM compatible @CPU value flags:

M_8086          equ 0x01    ; 8086
M_186           equ 0x02    ; 186
M_286           equ 0x04    ; 286
M_386           equ 0x08    ; 386
M_486           equ 0x10    ; 486
M_586           equ 0x20    ; Pentium
M_686           equ 0x40    ; PPro
M_CPUMSK        equ 0x7F    ;
M_PROT          equ 0x80    ; protected instructions ok
M_8087          equ 0x0100  ; 8087
M_287           equ 0x0400  ; 287
M_387           equ 0x0800  ; 387

USE_EMPTY       equ 0xFE    ; don't change values of USE16,USE32,USE64!
USE16           equ 0
USE32           equ 1
USE64           equ 2

; fastcall types. if order is to be changed or entries
; added, also adjust tables in proc.c, mangle.c and probably invoke.c!

FCT_MSC         equ 0       ; MS 16-/32-bit fastcall (ax,dx,cx / ecx,edx)
FCT_WATCOMC     equ 1       ; OW register calling convention (eax, ebx, ecx, edx)
FCT_WIN64       equ 2       ; Win64 fastcall convention (rcx, rdx, r8, r9)
FCT_ELF64       equ 3       ; Linux 64 syscall
FCT_VEC32       equ 4
FCT_VEC64       equ 5

STDCALL_FULL    equ 0
STDCALL_NONE    equ 1
STDCALL_HALF    equ 2

; file extensions. Order must match first entries in enum opt_names!

ASM             equ 0   ; must be first; see SetFilenames() in assembly.asm
OBJ             equ 1
LST             equ 2
ERR             equ 3
NUM_FILE_TYPES  equ 4

OPTN_ASM_FN     equ 0   ; first 4 entries must match enum file_extensions!
OPTN_OBJ_FN     equ 1   ; -Fo option
OPTN_LST_FN     equ 2   ; -Fl option
OPTN_ERR_FN     equ 3   ; -Fr option
OPTN_LNKDEF_FN  equ 4   ; -Fd option
OPTN_MODULE_NAME equ 5  ; -nm option
OPTN_TEXT_SEG   equ 6   ; -nt option
OPTN_DATA_SEG   equ 7   ; -nd option
OPTN_CODE_CLASS equ 8   ; -nc option
OPTN_LAST       equ 9

; queues to store multiple cmdline switch values

OPTQ_FINCLUDE   equ 0   ; -Fi option values
OPTQ_MACRO      equ 1   ; -D option values
OPTQ_INCPATH    equ 2   ; -I option values
OPTQ_LAST       equ 3

PEM_DEFAULT     equ 0   ; must be value 0
PEM_MACRO       equ 1
PEM_NONE        equ 2

STACK_NEAR      equ 0   ; Stack distance
STACK_FAR       equ 1

OPSYS_DOS       equ 0   ; Type of operating system
OPSYS_OS2       equ 1

OT_GROUP        equ 0   ; OFFSET:GROUP (default, must be 0)
OT_FLAT         equ 1   ; OFFSET:FLAT
OT_SEGMENT      equ 2   ; OFFSET:SEGMENT

LOF_LISTED      equ 1   ; line written to .LST file
LOF_SKIPPOS     equ 2   ; suppress setting list_pos

; flags for win64_flags

W64F_SAVEREGPARAMS      equ 1   ; 1=save register params in shadow space on proc entry
W64F_AUTOSTACKSP        equ 2   ; 1=calculate required stack space for arguments of INVOKE
W64F_STACKALIGN16       equ 4   ; 1=stack variables are 16-byte aligned; added in v2.12
W64F_ALL                equ W64F_SAVEREGPARAMS or W64F_AUTOSTACKSP or W64F_STACKALIGN16

; codeview debug info extend

CVEX_MIN        equ 0   ; globals
CVEX_REDUCED    equ 1   ; globals and locals
CVEX_NORMAL     equ 2   ; globals, locals and types
CVEX_MAX        equ 3   ; globals, locals, types and constants

CVO_STATICTLS   equ 1   ; option flags: handle static tls

SEGTYPE_UNDEF   equ 0
SEGTYPE_CODE    equ 1
SEGTYPE_DATA    equ 2
SEGTYPE_BSS     equ 3
SEGTYPE_STACK   equ 4
SEGTYPE_ABS     equ 5
SEGTYPE_HDR     equ 6   ; only used in bin.c for better sorting
SEGTYPE_CDATA   equ 7   ; "
SEGTYPE_RELOC   equ 8   ; "
SEGTYPE_RSRC    equ 9   ; "
SEGTYPE_ERROR   equ 10  ; must be last - an "impossible" segment type

CSF_GRPCHK      equ 1

CSI_TEXT        equ 0
CSI_DATA        equ 1
CSI_CONST       equ 2
CSI_BSS         equ 3

BLOCK_ACTIVE    equ 0
BLOCK_INACTIVE  equ 1
BLOCK_DONE      equ 2

SIT_FILE        equ 0
SIT_MACRO       equ 1

qditem          struct
next            ptr_t ?
size            uint_t ?
qditem          ends

dlldesc_t       typedef ptr dll_desc
dll_desc        struct
next            dlldesc_t ?
cnt             int_t ?
dname           char_t ?
dll_desc        ends

qitem           struct
next            ptr_t ?
value           db ?
qitem           ends

src_item        struct
next            ptr_t ?
type            dw ?    ; item type ( see enum src_item_type )
srcfile         dw ?    ; index of file in ModuleInfo.FNames
union
 content        ptr_t ? ; generic
 file           ptr_t ? ; if item is a file
 mi             ptr_t ? ; if item is a macro
ends
line_num        uint_t ? ; current line #
src_item        ends

format_options  struct
init            proc :ptr module_info
invalid_fixup_type short_t ?
formatname      char_t 6 dup(?)
format_options  ends


global_options          struct
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
global_options          ENDS

M_MODULEVARS            MACRO
error_count             uint_t ?        ; total of errors so far
warning_count           uint_t ?        ; total of warnings so far
num_segs                uint_t ?        ; number of segments in module
PubQueue                qdesc <>        ; PUBLIC items
Lnam                    qdesc <>        ; LNAME items (segments, groups and classes)
SafeSEHQueue            qdesc <>        ; list of safeseh handlers
LibQueue                qdesc <>        ; includelibs
DllQueue                dlldesc_t ?     ; dlls of OPTION DLLIMPORT
imp_prefix              string_t ?              ;
curr_file               LPFILE NUM_FILE_TYPES dup(?) ; ASM, ERR, OBJ and LST
curr_fname              string_t NUM_FILE_TYPES dup(?)
FNames                  array_t ?       ; array of input files
cnt_fnames              uint_t ?        ; items in FNames array
IncludePath             string_t ?              ;
line_queue              qdesc <>        ; line queue
src_stack               ptr_t ?         ; source item (files & macros) stack
union
 start_fixup            ptr_t ?         ; OMF only
 start_label            ptr_t ?         ; non-OMF only: start label
ends
start_displ             dd ?            ; OMF only, optional displ for start label
StrStack                ptr_t ?         ; v2.20 String stack
HllStack                ptr_t ?         ; for .WHILE, .IF, .REPEAT
HllFree                 ptr_t ?         ; v2.06: stack of free <struct hll>-items
ComStack                ptr_t ?         ; v2.27: .CLASSDEF, .COMDEF, .ENDS
RetStack                ptr_t ?         ; v2.30: .return info
ContextStack            ptr_t ?
ContextFree             ptr_t ?         ; v2.10: "free items" heap implemented.
SavedContexts           ptr_t ?
cntSavedContexts        dd ?
anonymous_label         dd ?            ; "anonymous label" counter
StackBase               ptr_t ?
ProcStatus              ptr_t ?
WriteModule             ptr_t ?         ; (*WriteModule)( struct module_info * );
EndDirHook              ptr_t ?         ; (*EndDirHook) ( struct module_info * );
Pass1Checks             ptr_t ?         ; (*Pass1Checks)( struct module_info * );
pe_flags                dd ?            ; for PE
                        ENDM

module_vars             STRUC
M_MODULEVARS
module_vars             ENDS

module_info             STRUC SIZE_T
M_MODULEVARS
proc_prologue           string_t ? ; prologue macro if PEM_MACRO
proc_epilogue           string_t ? ; epilogue macro if PEM_MACRO
CurrDll                 ptr_t ? ; OPTION DLLIMPORT dll
fmtopt                  ptr_t ? ; v2.07: added
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
StartupDirectiveFound   db ?    ;
EndDirFound             db ?    ;
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
simseg_defd             db ?    ; v2.09: flag if seg was defined before simseg dir
PhaseError              db ?    ; phase error flag
CommentDataInCode       db ?    ; OMF: emit coment records about data in code segs
prologuemode            db ?    ; current PEM_ enum value for OPTION PROLOGUE
epiloguemode            db ?    ; current PEM_ enum value for OPTION EPILOGUE
invoke_exprparm         db ?    ; flag: forward refs for INVOKE params ok?
cv_opt                  db ?    ; option codeview
strict_masm_compat      db ?    ; -Zne option
srcfile                 dd ?    ; main source file - is an index for FNames[]
currseg                 dsym_t ?; currently active segment - dsym *
flat_grp                dsym_t ?; magic FLAT group - dsym *
pCodeBuff               ptr_t ? ;
GeneratedCode           dd ?    ; nesting level generated code
currsource              string_t ? ; current source line
CurrComment             string_t ? ; current comment
tokenarray              ptr_t ? ; start token buffer
stringbufferend         string_t ? ; start free space in string buffer
token_count             dd ?    ; number of tokens in curr line
basereg                 dd 3 dup(?)     ; stack base register (16-, 32-, 64-bit
name                    db 260 dup(?)   ; name of module
xflag                   db ?    ; extended option
loopalign               db ?    ; OPTION:LOOPALIGN setting
casealign               db ?    ; OPTION:CASEALIGN setting
epilogueflags           db ?    ; OPTION EPILOGUE: FLAGS
assert_proc             ptr_t ? ; .assert:<proc/macro name>
codepage                dd ?    ;
class_label             dd ?    ;
module_info             ENDS

Token_Count             equ <ModuleInfo.token_count>
CurrSource              equ <ModuleInfo.currsource>
CurrWordSize            equ <ModuleInfo.wordsize>
CurrFile                equ <ModuleInfo.curr_file>
CurrSeg                 equ <ModuleInfo.currseg>
CurrFName               equ <ModuleInfo.curr_fname>

externdef               Parse_Pass      : uint_t
externdef               LineStore       : qdesc
externdef               ModuleInfo      : module_info
externdef               Options         : global_options
externdef               write_to_file   : uint_t
externdef               DefaultDir      : string_t      ; * NUM_FILE_TYPES
externdef               MacroLevel      : uint_t
externdef               LinnumQueue     : qdesc
externdef               ModelToken      : string_t
externdef               LastCodeBufSize : uint_t
externdef               banner_printed  : uint_t
externdef               stackreg        : uint_t
externdef               regax           : uint_t

externdef               szError         : char_t        ; ERROR
externdef               szNothing       : char_t        ; NOTHING
externdef               szDgroup        : char_t        ; DGROUP

asmerr                  proto :int_t, :vararg
DelayExpand             proto fastcall :tok_t
AsmcKeywords            proto :int_t

write_logo              proto
SetCPU                  proto :int_t
OutputByte              proto :int_t
OutputBytes             proto :ptr byte, :int_t, :ptr fixup
AddLinnumDataRef        proto :uint_t, :uint_t
_atoow                  proto :string_t, :string_t, :int_t, :int_t

.pragma list(pop)
endif
