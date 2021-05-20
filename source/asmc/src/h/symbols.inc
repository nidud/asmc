.pragma list(push, 0)
ifndef __SYMBOLS_INC
__SYMBOLS_INC equ <>

;; defines symbol structures asym and dsym,
;; and prototypes of functions in symbols.c.
;; This file is included by parser.inc

;; SYM_LIB  - library paths are no longer added to the symbol table
;; SYM_LNAME has been removed. It was used for the null-entry in the LNAME table only
;; v2.01: SYM_PROC has been removed.
;; v2.01: SYM_LIB has been removed.

.enum sym_state {
    SYM_UNDEFINED,
    SYM_INTERNAL,       ;;  1 internal label
    SYM_EXTERNAL,       ;;  2 external
    SYM_SEG,            ;;  3 segment
    SYM_GRP,            ;;  4 group
    SYM_STACK,          ;;  5 stack variable - in local symbol tables only
    SYM_STRUCT_FIELD,   ;;  6 struct member - not in symbol table - except record fields
    SYM_TYPE,           ;;  7 structure, union, typedef, record
    SYM_ALIAS,          ;;  8 alias name
    SYM_MACRO,          ;;  9 macro
    SYM_TMACRO,         ;; 10 text macro
    SYM_CLASS_LNAME     ;; 11 lname item for segm class - not in symbol table
}

;; v2.04: MT_SHORT removed
;; v2.07: MT_ABS (0xC2) removed

MT_SIZE_MASK            equ 0x1F ;; if MT_SPECIAL==0 then bits 0-4 = size - 1
MT_FLOAT                equ 0x20 ;; bit 5=1
MT_SIGNED               equ 0x40 ;; bit 6=1
MT_BYTE                 equ 1 - 1
MT_SBYTE                equ MT_BYTE or MT_SIGNED
MT_WORD                 equ 2 - 1
MT_SWORD                equ MT_WORD or MT_SIGNED
MT_REAL2                equ MT_WORD or MT_FLOAT
MT_DWORD                equ 4 - 1
MT_SDWORD               equ MT_DWORD or MT_SIGNED
MT_REAL4                equ MT_DWORD or MT_FLOAT
MT_FWORD                equ 6 - 1
MT_QWORD                equ 8 - 1
MT_SQWORD               equ MT_QWORD or MT_SIGNED
MT_REAL8                equ MT_QWORD or MT_FLOAT
MT_TBYTE                equ 10 - 1
MT_REAL10               equ MT_TBYTE or MT_FLOAT
MT_OWORD                equ 16 - 1
MT_REAL16               equ MT_OWORD or MT_FLOAT
MT_YMMWORD              equ 32 - 1
MT_ZMMWORD              equ 64 - 1
MT_YWORD                equ MT_YMMWORD
MT_ZWORD                equ MT_ZMMWORD
MT_PROC                 equ 0x80 ;; symbol is a TYPEDEF PROTO, state=SYM_TYPE,
                                 ;; typekind=TYPE_TYPEDEF, prototype is stored in target_type
MT_NEAR                 equ 0x81
MT_FAR                  equ 0x82
MT_EMPTY                equ 0xC0
MT_BITS                 equ 0xC1 ;; record field
MT_ABS                  equ 0xC2 ;; v2.31: macro/proto imm param
MT_PTR                  equ 0xC3 ;; v2.05: changed, old value 0x83
MT_TYPE                 equ 0xC4 ;; symbol has user-defined type (struct, union, record)
MT_SPECIAL              equ 0x80 ;; bit 7
MT_SPECIAL_MASK         equ 0xC0 ;; bit 6+7
MT_ADDRESS              equ 0x80 ;; bit 7=1, bit 6 = 0

IS_SIGNED macro x
    mov al,x
    and al,MT_SPECIAL_MASK
    .if al == MT_SIGNED
        mov eax,1
    .else
        xor eax,eax
    .endif
    exitm<eax>
    endm

;; symbols can be
;; - "labels" (data or code, internal, external, stack)
;;   mem_type is MT_BYTE..MT_OWORD, MT_NEAR, MT_FAR, MT_PTR
;; - constants (EQU) or assembly time variables ("="),
;;   mem_type "usually" is MT_EMPTY.
;; - types (STRUCT, UNION, TYPEDEF, RECORD), mem_type = MT_TYPE
;; - preprocessor items (macros and text macros), which have no
;;   mem_type (MT_EMPTY).

fixup_t         typedef ptr fixup
dlldesc_t       typedef ptr dll_desc
segitem_t       typedef ptr seg_item
debug_t         typedef ptr debug_info
dsym_t          typedef ptr dsym
group_t         typedef ptr grp_info
segment_t       typedef ptr seg_info
proc_t          typedef ptr proc_info
mparm_t         typedef ptr mparm_list
macro_t         typedef ptr macro_info
sfield_t        typedef ptr sfield
struct_t        typedef ptr struct_info

debug_info      struct
start_line      dd ?    ;; procs's start line
end_line        dd ?    ;; procs's last line
ln_fileofs      dd ?    ;; file offset to line numbers
line_numbers    dw ?    ;; line numbers in function
file            dw ?    ;; proc's start file
next_proc       dd ?    ;; index next proc
next_file       dd ?    ;; index next file
debug_info      ends

S_USED          equ 0x01 ; flags
S_ISDEFINED     equ 0x02
S_SCOPED        equ 0x04
S_IAT_USED      equ 0x08
S_ISEQUATE      equ 0x10
S_PREDEFINED    equ 0x20
S_VARIABLE      equ 0x40
S_ISPUBLIC      equ 0x80

S_LIST          equ 0x01 ; flag1
S_ISARRAY       equ 0x02
S_ISDATA        equ 0x04
S_ISPROC        equ 0x08
S_ISSAVED       equ 0x10
S_FWDREF        equ 0x20
S_INCLUDED      equ 0x40
S_METHOD        equ 0x80

S_VTABLE        equ 0x01 ; base class - first member = lpVtbl
S_ISVTABLE      equ 0x02 ; vtable struct - classVtbl
S_VMACRO        equ 0x04 ; vtable method is inline - sym->vmacro set
S_ISINLINE      equ 0x08 ; v2.31.24: SYM_EXTERNAL.target_type == SYM_MACRO
S_ISSTATIC      equ 0x10 ; v2.32.26: SYM_EXTERNAL.target_type == SYM_MACRO

S_SEGOFSSIZE    equ 0x03 ; sflags
S_ISCOM         equ 0x04
S_WEAK          equ 0x08
S_ISFAR         equ 0x10
S_ISVARARG      equ 0x20

M_ISVARARG      equ 0x01 ; mac_flag
M_ISFUNC        equ 0x02
M_LABEL         equ 0x04
M_MULTILINE     equ 0x08
M_PURGED        equ 0x10

.template asym watcall
    nextitem        ptr asym ?      ; next symbol in hash line
    name            string_t ?      ; symbol name
    union
     offs           int_t ?         ; used by SYM_INTERNAL (labels), SYM_TYPE, SYM_STACK, SYM_SEG
     value          int_t ?         ; used by SYM_INTERNAL (equates)
     uvalue         uint_t ?        ; v2.01: equates (they are 33-bit!)
     string_ptr     string_t ?      ; used by SYM_TMACRO
     substitute     ptr asym ?      ; v2.04b: used by SYM_ALIAS
     ;
     ; used by SYM_MACRO if predefined==1
     ;
     func_ptr       proc local :ptr macro_instance, :string_t, :ptr asm_tok
     classlnameidx  int_t ?         ; used by SYM_CLASS_LNAME
    ends

    union
     segm           ptr asym ?      ; used by SYM_INTERNAL, SYM_EXTERNAL
     class          ptr asym ?      ; used by SYM_TYPE
     vtable         ptr asym ?      ; used by SYM_TYPE
     vmacro         ptr asym ?      ; used by SYM_TYPE
    ends

    state           uchar_t ?
    mem_type        uchar_t ?
    reserved1       uchar_t ?       ; align..
    reserved2       uchar_t ?

    flags           uchar_t ?       ; bitfield
    flag1           uchar_t ?
    flag2           uchar_t ?
    flag3           uchar_t ?

    union
     ;
     ; for SYM_INTERNAL (data labels, memtype != NEAR|FAR), SYM_STRUCT_FIELD
     ; size of 1st initializer's dimension in bytes
     ;
     first_size     uint_t ?
     ;
     ; for SYM_INTERNAL (memtype == NEAR|FAR),
     ; SYM_GRP (Ofssize),
     ; SYM_EXTERNAL (Ofssize, comm, weak, isfar, is_ptr, ptr_memtype),
     ; SYM_STACK (Ofssize, isfar, is_vararg, is_ptr, ptr_memtype ),
     ; SYM_TYPE, TYPE_TYPEDEF (Ofssize, isfar, is_ptr, ptr_memtype )
     ;
     struct
      Ofssize       uchar_t ?       ; offset size (USE16, USE32)
      is_ptr        uchar_t ?       ; PTR indirection
      union
       ptr_memtype  uchar_t ?       ; pointer target type
       asmpass      uchar_t ?       ; SYM_INTERNAL (mem_type NEAR|FAR)
      ends
     sflags        uchar_t ?
     ends

     mac_flag       uint_t ?        ; for SYM_MACRO -- byte
    ends
    union
     ;
     ; for SYM_INTERNAL (data labels only), SYM_STRUCT_FIELD
     ; size of 1st initializer's dimension in item units
     ;
     first_length   uint_t ?
     ;
     ; SYM_TYPE (TYPEKIND_STRUCT or TYPEKIND_UNION)
     ; max size members
     ;
     max_mbr_size   uint_t ?
     ;
     ; SYM_STACK, SYM_TYPE (TYPEKIND_TYPEDEF), SYM_EXTERNAL,
     ; SYM_INTERNAL (code labels)
     ; set if ptr_memtype is MT_TYPE
     ;
     target_type    ptr asym ?
    ends
    ;
    ; SYM_TMACRO (if it's a register variable for FASTCALL)
    ;
    regist          ushort_t 2 dup(?)
    union
     ;
     ; for SYM_INTERNAL, SYM_STRUCT_FIELD, SYM_TYPE, SYM_STACK, SYM_EXTERNAL (comm=1)
     ; SYM_TMACRO: size of buffer allocated for the text in string_ptr
     ; total number of bytes (sizeof)
     ;
     total_size     uint_t ?
     ;
     ; for SYM_INTERNAL, isequate=1 (numeric equates)
     ; high bits for equates
     ;
     value3264      int_t ?
     dll            dlldesc_t ?     ; SYM_EXTERNAL (isproc=1)
     ;
     ; for SYM_SEG offset field contain "local start offset" (=0)
     ; SYM_INTERNAL, SYM_STRUCT_FIELD, SYM_STACK, SYM_EXTERNAL (comm==1):
     ;
     max_offset     int_t ?
    ends
    union

     total_length   uint_t ?        ; total number of elements (LENGTHOF)
     altname        ptr asym ?      ; SYM_EXTERNAL (comm==0): alternative name
     debuginfo      debug_t ?       ; SYM_INTERNAL (isproc==1): debug info (COFF)
                                    ; SYM_INTERNAL+predefined
     sfunc_ptr      proc local :ptr asym, :ptr
     struct                         ; SYM_TYPE
      cvtyperef     ushort_t ?      ; codeview type index (used after assembly steps)
      typekind      ushort_t ?      ; v2.04: moved from first_length, were it didn't work anymore
     ends                           ; since the addition of field max_mbr_size.
    ends
    name_size       ushort_t ?
    langtype        ushort_t ?
    type            ptr asym ?      ; set if memtype is MT_TYPE
    union                           ; SYM_INTERNAL, SYM_UNDEFINED, SYM_EXTERNAL: backpatching fixup
     bp_fixup       fixup_t ?
     ext_idx        uint_t ?        ; for SYM_EXTERNAL: table index ( for coff and elf )
     struct                         ; omf indices are 16-bit only!
      ext_idx1      ushort_t ?      ; omf: (external definition) index
      ext_idx2      ushort_t ?      ; omf: (external definition) index for weak external
     ends
    ends

    .inline nextitem            { retm<[eax].asym.nextitem> }
    .inline name                { retm<[eax].asym.name> }
    .inline offs                { retm<[eax].asym.offs> }
    .inline value               { retm<[eax].asym.value> }
    .inline uvalue              { retm<[eax].asym.uvalue> }
    .inline string_ptr          { retm<[eax].asym.string_ptr> }
    .inline substitute          { retm<[eax].asym.substitute> }
    .inline classlnameidx       { retm<[eax].asym.classlnameidx> }
    .inline segm                { retm<[eax].asym.segm> }
    .inline class               { retm<[eax].asym.class> }
    .inline vtable              { retm<[eax].asym.vtable> }
    .inline vmacro              { retm<[eax].asym.vmacro> }
    .inline state               { retm<[eax].asym.state> }
    .inline mem_type            { retm<[eax].asym.mem_type> }
    .inline reserved1           { retm<[eax].asym.reserved1> }
    .inline reserved2           { retm<[eax].asym.reserved2> }
    .inline flags               { retm<[eax].asym.flags> }
    .inline flag1               { retm<[eax].asym.flag1> }
    .inline flag2               { retm<[eax].asym.flag2> }
    .inline flag3               { retm<[eax].asym.flag3> }
    .inline first_size          { retm<[eax].asym.first_size> }
    .inline Ofssize             { retm<[eax].asym.Ofssize> }
    .inline is_ptr              { retm<[eax].asym.is_ptr> }
    .inline ptr_memtype         { retm<[eax].asym.ptr_memtype> }
    .inline asmpass             { retm<[eax].asym.asmpass> }
    .inline sflags              { retm<[eax].asym.sflags> }
    .inline mac_flag            { retm<[eax].asym.mac_flag> }
    .inline first_length        { retm<[eax].asym.first_length> }
    .inline max_mbr_size        { retm<[eax].asym.max_mbr_size> }
    .inline target_type         { retm<[eax].asym.target_type> }
    .inline regist0             { retm<[eax].asym.regist[0]> }
    .inline regist1             { retm<[eax].asym.regist[2]> }
    .inline total_size          { retm<[eax].asym.total_size> }
    .inline value3264           { retm<[eax].asym.value3264> }
    .inline dll                 { retm<[eax].asym.dll> }
    .inline max_offset          { retm<[eax].asym.max_offset> }
    .inline total_length        { retm<[eax].asym.total_length> }
    .inline altname             { retm<[eax].asym.altname> }
    .inline debuginfo           { retm<[eax].asym.debuginfo> }
    .inline cvtyperef           { retm<[eax].asym.cvtyperef> }
    .inline typekind            { retm<[eax].asym.typekind> }
    .inline name_size           { retm<[eax].asym.name_size> }
    .inline langtype            { retm<[eax].asym.langtype> }
    .inline type                { retm<[eax].asym.type> }
    .inline bp_fixup            { retm<[eax].asym.bp_fixup> }
    .inline ext_idx             { retm<[eax].asym.ext_idx> }
    .inline ext_idx1            { retm<[eax].asym.ext_idx1> }
    .inline ext_idx2            { retm<[eax].asym.ext_idx2> }


    .inline used            { retm<([eax].asym.flags & S_USED)> }
    .inline isdefined       { retm<([eax].asym.flags & S_ISDEFINED)> }
    .inline scoped          { retm<([eax].asym.flags & S_SCOPED)> }
    .inline iat_used        { retm<([eax].asym.flags & S_IAT_USED)> }
    .inline isequate        { retm<([eax].asym.flags & S_ISEQUATE)> }
    .inline predefined      { retm<([eax].asym.flags & S_PREDEFINED)> }
    .inline variable        { retm<([eax].asym.flags & S_VARIABLE)> }
    .inline ispublic        { retm<([eax].asym.flags & S_ISPUBLIC)> }

    .inline list            { retm<([eax].asym.flag1 & S_LIST)> }
    .inline isarray         { retm<([eax].asym.flag1 & S_ISARRAY)> }
    .inline isdata          { retm<([eax].asym.flag1 & S_ISDATA)> }
    .inline isproc          { retm<([eax].asym.flag1 & S_ISPROC)> }
    .inline issaved         { retm<([eax].asym.flag1 & S_ISSAVED)> }
    .inline fwdref          { retm<([eax].asym.flag1 & S_FWDREF)> }
    .inline included        { retm<([eax].asym.flag1 & S_INCLUDED)> }
    .inline method          { retm<([eax].asym.flag1 & S_METHOD)> }

    .inline vtable          { retm<([eax].asym.flag2 & S_VTABLE)> }
    .inline isvtable        { retm<([eax].asym.flag2 & S_ISVTABLE)> }
    .inline vmacro          { retm<([eax].asym.flag2 & S_VMACRO)> }
    .inline isinline        { retm<([eax].asym.flag2 & S_ISINLINE)> }
    .inline isstatic        { retm<([eax].asym.flag2 & S_ISSTATIC)> }

    .inline seg_ofssize {
        mov al,[eax].asym.sflags
        and eax,S_SEGOFSSIZE
        }
    .inline iscomm          { retm<([eax].asym.sflags & S_ISCOM)> }
    .inline weak            { retm<([eax].asym.sflags & S_WEAK)> }
    .inline isfar           { retm<([eax].asym.sflags & S_ISFAR)> }
    .inline is_vararg       { retm<([eax].asym.sflags & S_ISVARARG)> }

    .inline mac_vararg      { retm<([eax].asym.mac_flag & M_ISVARARG)> }
    .inline isfunc          { retm<([eax].asym.mac_flag & M_ISFUNC)> }
    .inline mlabel          { retm<([eax].asym.mac_flag & M_LABEL)> }
    .inline mac_multiline   { retm<([eax].asym.mac_flag & M_MULTILINE)> }
    .inline purged          { retm<([eax].asym.mac_flag & M_PURGED)> }

    asym_setflag macro flag, pos, val
      if val
        or  [eax].asym.flag,(1 shl pos)
      else
        and [eax].asym.flag,not (1 shl pos)
      endif
      exitm<>
      endm

    .inline set_used        val:abs { asym_setflag(flags, 0, val) }
    .inline set_isdefined   val:abs { asym_setflag(flags, 1, val) }
    .inline set_scoped      val:abs { asym_setflag(flags, 2, val) }
    .inline set_iat_used    val:abs { asym_setflag(flags, 3, val) }
    .inline set_isequate    val:abs { asym_setflag(flags, 4, val) }
    .inline set_predefined  val:abs { asym_setflag(flags, 5, val) }
    .inline set_variable    val:abs { asym_setflag(flags, 6, val) }
    .inline set_ispublic    val:abs { asym_setflag(flags, 7, val) }

    .inline set_list        val:abs { asym_setflag(flag1, 0, val) }
    .inline set_isarray     val:abs { asym_setflag(flag1, 1, val) }
    .inline set_isdata      val:abs { asym_setflag(flag1, 2, val) }
    .inline set_isproc      val:abs { asym_setflag(flag1, 3, val) }
    .inline set_issaved     val:abs { asym_setflag(flag1, 4, val) }
    .inline set_fwdref      val:abs { asym_setflag(flag1, 5, val) }
    .inline set_included    val:abs { asym_setflag(flag1, 6, val) }
    .inline set_method      val:abs { asym_setflag(flag1, 7, val) }

    .inline set_seg_ofssize val:uint_t {
        and [eax].asym.sflags,not S_SEGOFSSIZE
        or  [eax].asym.sflags,dl
        }
    .inline set_iscomm          val:abs { asym_setflag(sflags, 2, val) }
    .inline set_weak            val:abs { asym_setflag(sflags, 3, val) }
    .inline set_isfar           val:abs { asym_setflag(sflags, 4, val) }
    .inline set_is_vararg       val:abs { asym_setflag(sflags, 5, val) }

    .inline set_mac_vararg      val:abs { asym_setflag(mac_flag, 0, val) }
    .inline set_isfunc          val:abs { asym_setflag(mac_flag, 1, val) }
    .inline set_mlabel          val:abs { asym_setflag(mac_flag, 2, val) }
    .inline set_mac_multiline   val:abs { asym_setflag(mac_flag, 3, val) }
    .inline set_purged          val:abs { asym_setflag(mac_flag, 4, val) }

   .ends
    asym_t          typedef ptr asym


;;---------------------------------------------------------------------------
;; Structures for grpdef, segdef, externdef, pubdef, included library,
;; procedure and symbolic integer constants.
;;---------------------------------------------------------------------------

seg_item        struct
next            segitem_t ?
iseg            dsym_t ?
seg_item        ends

grp_info        struct          ;;
seglist         segitem_t ?     ;; list of segments in the group
grp_idx         int_t ?         ;; its group index (OMF)
lname_idx       int_t ?         ;; LNAME index (OMF only)
numseg          uint_t ?        ;; OMF: number of segments in the group
grp_info        ends            ;;

seg_info        struct          ;;
sgroup          asym_t ?        ;; segment's group or NULL
start_loc       uint_t ?        ;; starting offset of current ledata or lidata
union                           ;;
 current_loc    uint_t ?        ;; current offset in current ledata or lidata
 reloc_offset   uint_t ?        ;; ELF: reloc file offset
 start_offset   uint_t ?        ;; BIN: start offset in group
ends                            ;;
CodeBuffer      string_t ?      ;;
bytes_written   uint_t ?        ;; initialized bytes in segment
union                           ;;
 label_list     asym_t ?        ;; linked list of labels in this seg
 flushfunc      proc :ptr dsym, :ptr byte, :dword, :ptr ;; to flush the segment buffer
ends                            ;;
head            fixup_t ?       ;; fixup queue head
tail            fixup_t ?       ;; fixup queue tail
union                           ;;
 LinnumQueue    ptr_t ?         ;; for COFF line numbers
 fileoffset     uint_t ?        ;; used by BIN + ELF
 num_linnums    uint_t ?        ;; used by COFF (after LinnumQueue has been read)
ends                            ;;
num_relocs      uint_t ?        ;; used by COFF/ELF
seg_idx         uint_t ?        ;; segment #; v2.12: changed from short to unsigned
segtype         uint_t ?        ;; segment's type (code, data, ...)
lname_idx       int_t ?         ;; segment's name LNAME index (OMF only)
clsym           asym_t ?        ;; segment's class name (stored in an asym item)
union                           ;;
 abs_frame      uint_t ?        ;; ABS seg, frame number (OMF,BIN)
 comdat_number  uint_t ?        ;; associated COMDAT segno (COFF)
 comdat_idx     uint_t ?        ;; lname index of COMDAT symbol (OMF)
ends
union
 abs_offset     uint_t ?        ;; ABS seg, offset (OMF only)
 aliasname      string_t ?      ;; ALIAS name (COFF/ELF only)
ends
Ofssize         uchar_t ?       ;; segment's offset size
characteristics uchar_t ?       ;; used by COFF/ELF/PE
alignment       uchar_t ?       ;; is value 2^x
readonly        uchar_t ?       ;; if segment is readonly
info            uchar_t ?       ;; if segment is info only (COFF/ELF)
force32         uchar_t ?       ;; force 32bit segdef (OMF only)
data_in_code    uchar_t ?       ;; data items in code segm (OMF only)
internal        uchar_t ?       ;; internal segment with private buffer
written         uchar_t ?       ;; code/data just written
linnum_init     uchar_t ?       ;; v2.10: linnum data emitted for segment?
combine         uchar_t ?       ;; combine type, see omfspec.inc
comdatselection uchar_t ?       ;; if > 0, it's a COMDAT (COFF/OMF)
seg_info        ends            ;;


MAX_SEGALIGNMENT equ 0xFF

;; PROC item

PROC_HAS_VARARG equ 0x01        ; last param is VARARG
PROC_PE_TYPE    equ 0x02        ; prolog-epilog type, 1=use LEAVE
PROC_ISEXPORT   equ 0x04        ; EXPORT attribute set
PROC_FORCEFRAME equ 0x08        ; FORCEFRAME prologuearg?
PROC_LOADDS     equ 0x10        ; LOADDS prologuearg?
PROC_STACKPARAM equ 0x20        ; 1=stack params exists ( not just register params )
PROC_ISFRAME    equ 0x40        ; FRAME attribute set?
PROC_FPO        equ 0x80

.template proc_info watcall

    regslist        ptr word ?      ; list of registers to be saved
    paralist        ptr dsym ?      ; list of parameters
    locallist       ptr dsym ?      ; list of local variables
    labellist       ptr dsym ?      ; list of local labels
    parasize        uint_t ?        ; total no. of bytes used by parameters
    localsize       uint_t ?        ; total no. of bytes used by local variables
    prologuearg     string_t ?      ; prologuearg attribute
    exc_handler     ptr asym ?      ; exc handler set by FRAME
    ReservedStack   int_t ?         ; win64: additional reserved stack
    prolog_list_pos uint_t ?        ; prologue list pos
    flags           uchar_t ?
    size_prolog     uchar_t ?       ; v2.10: prologue size
    basereg         ushort_t ?      ; v2.11: stack base register

    .inline regslist        { retm<[eax].proc_info.regslist> }
    .inline paralist        { retm<[eax].proc_info.paralist> }
    .inline locallist       { retm<[eax].proc_info.locallist> }
    .inline labellist       { retm<[eax].proc_info.labellist> }
    .inline parasize        { retm<[eax].proc_info.parasize> }
    .inline localsize       { retm<[eax].proc_info.localsize> }
    .inline prologuearg     { retm<[eax].proc_info.prologuearg> }
    .inline exc_handler     { retm<[eax].proc_info.exc_handler> }
    .inline ReservedStack   { retm<[eax].proc_info.ReservedStack> }
    .inline prolog_list_pos { retm<[eax].proc_info.prolog_list_pos> }
    .inline flags           { retm<[eax].proc_info.flags> }
    .inline size_prolog     { retm<[eax].proc_info.size_prolog> }
    .inline basereg         { retm<[eax].proc_info.basereg> }

    .inline has_vararg      { retm<([eax].proc_info.flags & PROC_HAS_VARARG)> }
    .inline pe_type         { retm<([eax].proc_info.flags & PROC_PE_TYPE)> }
    .inline isexport        { retm<([eax].proc_info.flags & PROC_ISEXPORT)> }
    .inline forceframe      { retm<([eax].proc_info.flags & PROC_FORCEFRAME)> }
    .inline loadds          { retm<([eax].proc_info.flags & PROC_LOADDS)> }
    .inline stackparam      { retm<([eax].proc_info.flags & PROC_STACKPARAM)> }
    .inline isframe         { retm<([eax].proc_info.flags & PROC_ISFRAME)> }
    .inline fpo             { retm<([eax].proc_info.flags & PROC_FPO)> }

        proc_setflag macro pos, val
          if val
            or  [eax].proc_info.flags,(1 shl pos)
          else
            and [eax].proc_info.flags,not (1 shl pos)
          endif
          exitm<>
          endm

    .inline set_has_vararg  val:abs { proc_setflag(0, val) }
    .inline set_pe_type     val:abs { proc_setflag(1, val) }
    .inline set_isexport    val:abs { proc_setflag(2, val) }
    .inline set_forceframe  val:abs { proc_setflag(3, val) }
    .inline set_loadds      val:abs { proc_setflag(4, val) }
    .inline set_stackparam  val:abs { proc_setflag(5, val) }
    .inline set_isframe     val:abs { proc_setflag(6, val) }
    .inline set_fpo         val:abs { proc_setflag(7, val) }

    .inline add_parasize size:uint_t {
        add [eax].proc_info.parasize,size
        }

    .inline set_export val:uint_t {
        and [eax].proc_info.flags,not PROC_ISEXPORT
        shl edx,2
        or  [eax].proc_info.flags,dl
        }

   .ends


;; macro parameter

mparm_list      struct
deflt           string_t ?      ;; optional default parm
required        uchar_t ?       ;; is parm required (REQ)
mparm_list      ends

;; macro line

srcline         struct
next            ptr srcline ?
ph_count        uchar_t ?       ;; placeholders contained in this line
line            char_t 1 dup(?)
srcline         ends
srcline_t       typedef ptr srcline

;; macro item

macro_info      struct
parmcnt         ushort_t ?      ;; no of params
union
 localcnt       ushort_t ?      ;; no of locals
 autoexp        ushort_t ?      ;; auto-expansion flags if predefined macro
ends
parmlist        mparm_t ?       ;; array of parameter items
lines           srcline_t ?     ;; prepared macro source lines
srcfile         uint_t ?        ;; sourcefile index
macro_info      ends

;; STRUCT field

sfield          struct
sym             asym <>         ;; field symbol ( state=SYM_STRUCT_FIELD )
next            sfield_t ?      ;; next field in STRUCT,UNION,RECORD
ivalue          char_t ?        ;; v2.09: type changed from char * to char[]
sfield          ends

TYPE_NONE       equ 0
TYPE_STRUCT     equ 1
TYPE_UNION      equ 2
TYPE_TYPEDEF    equ 3
TYPE_RECORD     equ 4

SI_ISINLINE     equ 1           ;; STRUCT/UNION: inline (unused)
SI_ISOPEN       equ 2           ;; STRUCT/UNION: set until the matching ENDS is found
SI_ORGINSIDE    equ 4           ;; STRUCT: struct contains an ORG

struct_info     struct
head            ptr sfield ?    ;; STRUCT/UNION/RECORD: start of field list
tail            ptr sfield ?    ;; STRUCT/UNION/RECORD: current/next field
alignment       uchar_t ?       ;; STRUCT: 1,2,4,8,16 or 32
flags           uchar_t ?
struct_info     ends

;; dsym originally was a "directive_node"
;; However, currently all symbols except SYM_STRUCT_FIELDs are allocated as a dsym.
;; the additional 3 fields are used differently depending on symbol's type.

dsym            struct
sym             asym <>
union
 seginfo        segment_t ?     ;; SYM_SEG (segments)
 grpinfo        group_t ?       ;; SYM_GRP (groups)
 procinfo       proc_t ?        ;; SYM_INTERNAL|SYM_EXTERNAL (procs, isproc=1)
 structinfo     struct_t ?      ;; SYM_TYPE (structs, unions, records [, typedefs])
 macroinfo      macro_t ?       ;; SYM_MACRO (macros)
 nextll         dsym_t ?        ;; SYM_STACK, SYM_INTERNAL (code labels, isproc=0)
                                ;; used to save the local hash table (contains
                                ;; PROC locals: params, locals, labels). Details
                                ;; see SymGetLocal(), SymSetLocal() in symbols.asm
ends
next            dsym_t ?        ;; next item in linked lists of certain symbol types.
                                ;; - SYM_UNDEFINED -> TAB_UNDEF
                                ;; - SYM_EXTERNAL  -> TAB_EXT
                                ;; - SYM_SEG       -> TAB_SEG
                                ;; - SYM_GRP       -> TAB_GRP
                                ;; - SYM_ALIAS:    -> TAB_ALIAS
                                ;; for SYM_INTERNAL:
                                ;; linked list of labels for current segment
                                ;; (used for BackPatch)

;; for SYM_UNDEFINED, SYM_EXTERNAL, SYM_ALIAS and SYM_GRP:
;; predecessor of current symbol with the same state, to allow fast removes.
;; Actually, the only symbols which may change the state and thus
;; have a chance to be removed are SYM_UNDEFINED and SYM_EXTERNAL ( weak=TRUE )
;; during pass one.
union
 prev           dsym_t ? ;; used by PROC symbols (SYM_INTERNAL) for linked list, TAB_PROC
 nextproc       dsym_t ? ;; used by PROC locals (SYM_STACK) for linked list
 nextlocal      dsym_t ? ;; used by PROC params (SYM_STACK) for linked list
 nextparam      dsym_t ? ;; used by SYM_EXTERNAL (weak=FALSE) if altname is set
ends
dsym            ends

.pragma list(push, 1)

.template esym watcall : public asym

    info        ptr dsym ?
    next        ptr dsym ?
    list        ptr dsym ?

    .inline seginfo         { retm<[eax].esym.info> }
    .inline grpinfo         { retm<[eax].esym.info> }
    .inline procinfo        { retm<[eax].esym.info> }
    .inline structinfo      { retm<[eax].esym.info> }
    .inline macroinfo       { retm<[eax].esym.info> }
    .inline nextll          { retm<[eax].esym.info> }
    .inline next            { retm<[eax].esym.next> }
    .inline prev            { retm<[eax].esym.list> }
    .inline nextproc        { retm<[eax].esym.list> }
    .inline nextlocal       { retm<[eax].esym.list> }
    .inline nextparam       { retm<[eax].esym.list> }

    .inline get_public {
        movzx eax,[eax].esym.flags
        and al,S_ISPUBLIC
        }

    .ends

.pragma list(pop)

SymAlloc        proto :string_t
SymFree         proto :asym_t
SymCreate       proto :string_t
SymLCreate      proto :string_t
SymAddGlobal    proto :asym_t
SymAddLocal     proto :asym_t, :string_t
SymLookup       proto :string_t
SymLookupLocal  proto :string_t
SymFind         proto fastcall :string_t

SymSearch macro x
    exitm<SymFind(x)>
    endm

SymInit         proto
SymPassInit     proto :int_t
SymMakeAllSymbolsPublic proto
SymGetAll       proto :ptr asym_t
SymEnum         proto :asym_t, :ptr int_t
SymGetCount     proto

CALLBACKC(StrCmpFunc, :ptr, :ptr, :size_t )
externdef       SymCmpFunc:StrCmpFunc

SymSetCmpFunc   proto
SymClearLocal   proto
SymSetLocal     proto :asym_t
SymGetLocal     proto :asym_t

endif
.pragma list(pop)
