; SYMBOLS.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)

ifndef __SYMBOLS_INC
define __SYMBOLS_INC

; defines symbol structure asym,
; and prototypes of functions in symbols.asm.
; This file is included by parser.inc
;
; v2.36.46 - removed dsym and sfield --> asym

    asym_t          typedef ptr asym
    segment_t       typedef ptr seg_info
    segitem_t       typedef ptr seg_item
    group_t         typedef ptr grp_info
    proc_t          typedef ptr proc_info
    struct_t        typedef ptr struct_info
    macro_t         typedef ptr macro_info
    debug_t         typedef ptr debug_info


; SYM_LIB  - library paths are no longer added to the symbol table
; SYM_LNAME has been removed. It was used for the null-entry in the LNAME table only
; v2.01: SYM_PROC has been removed.
; v2.01: SYM_LIB has been removed.

.enum sym_state {
    SYM_UNDEFINED,
    SYM_INTERNAL,       ;  1 internal label
    SYM_EXTERNAL,       ;  2 external
    SYM_SEG,            ;  3 segment
    SYM_GRP,            ;  4 group
    SYM_STACK,          ;  5 stack variable - in local symbol tables only
    SYM_STRUCT_FIELD,   ;  6 struct member - not in symbol table - except record fields
    SYM_TYPE,           ;  7 structure, union, typedef, record
    SYM_ALIAS,          ;  8 alias name
    SYM_MACRO,          ;  9 macro
    SYM_TMACRO,         ; 10 text macro
    SYM_CLASS_LNAME     ; 11 lname item for segm class - not in symbol table
    }

; v2.04: MT_SHORT removed
; v2.07: MT_ABS (0xC2) removed

MT_SIZE_MASK            equ 0x1F ; if MT_SPECIAL==0 then bits 0-4 = size - 1
MT_FLOAT                equ 0x20 ; bit 5=1
MT_SIGNED               equ 0x40 ; bit 6=1
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
MT_SOWORD               equ MT_OWORD or MT_SIGNED
MT_REAL16               equ MT_OWORD or MT_FLOAT
MT_YMMWORD              equ 32 - 1
MT_YWORD                equ 32 - 1
MT_ZMMWORD              equ 64 - 1
MT_ZWORD                equ 64 - 1
MT_PROC                 equ 0x80 ; symbol is a TYPEDEF PROTO, state=SYM_TYPE,
                                 ; typekind=TYPE_TYPEDEF, prototype is stored in target_type
MT_NEAR                 equ 0x81
MT_FAR                  equ 0x82
MT_EMPTY                equ 0xC0
MT_BITS                 equ 0xC1 ; record field
MT_ABS                  equ 0xC2 ; v2.31: macro/proto imm param
MT_PTR                  equ 0xC3 ; v2.05: changed, old value 0x83
MT_TYPE                 equ 0xC4 ; symbol has user-defined type (struct, union, record)
MT_SPECIAL              equ 0x80 ; bit 7
MT_SPECIAL_MASK         equ 0xC0 ; bit 6+7
MT_ADDRESS              equ 0x80 ; bit 7=1, bit 6 = 0

IS_SIGNED proto watcall :byte {
    and al,MT_SPECIAL_MASK
    retm<(al == MT_SIGNED)>
    }

; symbols can be
; - "labels" (data or code, internal, external, stack)
;   mem_type is MT_BYTE..MT_OWORD, MT_NEAR, MT_FAR, MT_PTR
; - constants (EQU) or assembly time variables ("="),
;   mem_type "usually" is MT_EMPTY.
; - types (STRUCT, UNION, TYPEDEF, RECORD), mem_type = MT_TYPE
; - preprocessor items (macros and text macros), which have no
;   mem_type (MT_EMPTY).

.template debug_info
    start_line      dd ? ; procs's start line
    end_line        dd ? ; procs's last line
    ln_fileofs      dd ? ; file offset to line numbers
    line_numbers    dw ? ; line numbers in function
    file            dw ? ; proc's start file
    next_proc       dd ? ; index next proc
    next_file       dd ? ; index next file
   .ends

.template asym

    nextitem        asym_t ?        ; next symbol in hash line
    name            string_t ?      ; symbol name
    name_size       int_t ?
    record
     used           uint_t : 1 ?    ; symbol has been referenced
     isdefined      uint_t : 1 ?    ; symbol is "defined" in this pass
     scoped         uint_t : 1 ?    ; symbol is local label or SYM_STACK
     iat_used       uint_t : 1 ?    ; v2.07: IAT entry of symbol used (SYM_EXTERNAL + isproc==1 only)
     isequate       uint_t : 1 ?    ; symbol has been defined with EQU
     predefined     uint_t : 1 ?    ; symbol is predefined
     isvariable     uint_t : 1 ?    ; symbol is variable (defined by '=' directive)
     ispublic       uint_t : 1 ?    ; symbol has been added to the publics queue
     list           uint_t : 1 ?    ; symbol is to be listed
     isarray        uint_t : 1 ?    ; symbol is an array (total_length is valid)
     isdata         uint_t : 1 ?    ; field first_size is valid
     isproc         uint_t : 1 ?    ; symbol is PROC or PROTO; has proc_info extension
     issaved        uint_t : 1 ?    ; assembly-time variables only: symbol has been saved
     fwdref         uint_t : 1 ?    ; symbol was forward referenced
     included       uint_t : 1 ?    ; COFF: static symbol added to public queue. ELF:symbol added to symbol table (SYM_INTERNAL)
     method         uint_t : 1 ?    ;
     isclass        uint_t : 1 ?    ;
     hasvtable      uint_t : 1 ?    ; base class - first member = lpVtbl
     isvtable       uint_t : 1 ?    ; vtable struct - classVtbl
     isvmacro       uint_t : 1 ?    ; vtable method is inline - sym->vmacro set
     isinline       uint_t : 1 ?    ; SYM_EXTERNAL.target_type == SYM_MACRO
     isstatic       uint_t : 1 ?    ; SYM_EXTERNAL.target_type == SYM_MACRO
     vparray        uint_t : 1 ?    ; p.p.proc() - nested function call
     operator       uint_t : 1 ?    ;
     regparam       uint_t : 1 ?    ; register param
     regpair        uint_t : 1 ?    ; reg::reg param
     isexport       uint_t : 1 ?    ; v2.19: symbol exported ( SYM_INTERNAL )
     crecord        uint_t : 1 ?    ; v2.36.37: use bitf_* in records
     bitexpr        uint_t : 1 ?    ; v2.36.44: set by GetSimpleExpression() - rec.field == 1
    ends
    state           uchar_t ?
    mem_type        uchar_t ?
    langtype        uchar_t ?
    segoffsize      uchar_t ?
    is_far          uchar_t ?
    sys_rcnt        uchar_t ?       ; syscall: register count
    sys_xcnt        uchar_t ?       ; syscall: SIMD registers
    sys_size        uchar_t ?       ; syscall: max size 8/16/32/64
    type            asym_t ?        ; set if memtype is MT_TYPE

    union
     offs           int_t ?         ; used by SYM_INTERNAL (labels), SYM_TYPE, SYM_STACK, SYM_SEG
     value          int_t ?         ; used by SYM_INTERNAL (equates)
     uvalue         uint_t ?        ; v2.01: equates (they are 33-bit!)
     string_ptr     string_t ?      ; used by SYM_TMACRO
     substitute     asym_t ?        ; v2.04b: used by SYM_ALIAS
     ;
     ; used by SYM_MACRO if predefined==1
     ;
     func_ptr       proc local __ccall :ptr macro_instance, :string_t, :token_t
     classlnameidx  int_t ?         ; used by SYM_CLASS_LNAME
    ends

    union
     segm           asym_t ?        ; used by SYM_INTERNAL, SYM_EXTERNAL
     class          asym_t ?        ; used by SYM_TYPE
     vtable         asym_t ?        ; used by SYM_TYPE
     vmacro         asym_t ?        ; used by SYM_TYPE
    ends

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
      record
       iscomm       uchar_t : 1 ?   ; is communal
       weak         uchar_t : 1 ?   ; 1 if an unused "externdef"
       is_vararg    uchar_t : 1 ?   ; SYM_STACK, VARARG param
       is_vector    uchar_t : 1 ?   ; template is vector
       stkused      uchar_t : 1 ?   ; proc: call stack used
       argused      uchar_t : 1 ?   ; proc: stack arg used
       localgpr     uchar_t : 1 ?   ; proc: xmm reg saved to local stack
      ends
     ends
     record
      mac_vararg    uchar_t : 1 ?   ; accept additional params
      isfunc        uchar_t : 1 ?   ; it's a macro function
      islabel       uchar_t : 1 ?   ; macro is "label-aware"
      multiline     uchar_t : 1 ?   ; v2.11: vararg arguments may be on multiple lines
      purged        uchar_t : 1 ?   ; macro has been PURGEd
     ends
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
     target_type    asym_t ?
    ends
    ;
    ; SYM_TMACRO (if it's a register variable for FASTCALL)
    ;
    union
     regist         ushort_t 2 dup(?)
     struct
      param_reg     uchar_t ?   ; param register token
      param_id      uchar_t ?   ; param index
      param_regs    uchar_t ?   ; number or registers assign to this param
      param_offs    uchar_t ?   ; stack offset used by inline functions
     ends
     struct
      bitf_token    ushort_t ?  ; bit field info for fixed sized records
      bitf_offs     uchar_t ?
      bitf_bits     uchar_t ?
     ends
    ends

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
     dll            ptr dll_desc ?  ; SYM_EXTERNAL (isproc=1)
     ;
     ; for SYM_SEG offset field contain "local start offset" (=0)
     ; SYM_INTERNAL, SYM_STRUCT_FIELD, SYM_STACK, SYM_EXTERNAL (comm==1):
     ;
     max_offset     int_t ?
    ends

    union
     struct                         ; SYM_TYPE
      total_length  uint_t ?        ; total number of elements (LENGTHOF)
      cvtyperef     ushort_t ?      ; codeview type index (used after assembly steps)
      typekind      ushort_t ?      ; v2.04: moved from first_length, were it didn't work anymore
     ends                           ; since the addition of field max_mbr_size.
     altname        asym_t ?        ; SYM_EXTERNAL (comm==0): alternative name
     debuginfo      debug_t ?       ; SYM_INTERNAL (isproc==1): debug info (COFF)
                                    ; SYM_INTERNAL+predefined
     sfunc_ptr      proc local fastcall :asym_t, :ptr
    ends

    union                           ; SYM_INTERNAL, SYM_UNDEFINED, SYM_EXTERNAL: backpatching fixup
     bp_fixup       ptr fixup ?
     ext_idx        uint_t ?        ; for SYM_EXTERNAL: table index ( for coff and elf )
     struct                         ; omf indices are 16-bit only!
      ext_idx1      ushort_t ?      ; omf: (external definition) index
      ext_idx2      ushort_t ?      ; omf: (external definition) index for weak external
     ends
    ends

; dsym originally was a "directive_node"
; However, currently all symbols except SYM_STRUCT_FIELDs are allocated as a dsym.
; the additional 3 fields are used differently depending on symbol's type.

    union
     seginfo        segitem_t ?     ; SYM_SEG (segments)
     grpinfo        group_t ?       ; SYM_GRP (groups)
     procinfo       proc_t ?        ; SYM_INTERNAL|SYM_EXTERNAL (procs, isproc=1)
     structinfo     struct_t ?      ; SYM_TYPE (structs, unions, records [, typedefs])
     macroinfo      macro_t ?       ; SYM_MACRO (macros)
     nextll         asym_t ?        ; SYM_STACK, SYM_INTERNAL (code labels, isproc=0)
    ends                            ; used to save the local hash table (contains
                                    ; PROC locals: params, locals, labels). Details
                                    ; see SymGetLocal(), SymSetLocal() in symbols.asm

    next            asym_t ?        ; next item in linked lists of certain symbol types.
                                    ; - SYM_UNDEFINED -> TAB_UNDEF
                                    ; - SYM_EXTERNAL  -> TAB_EXT
                                    ; - SYM_SEG       -> TAB_SEG
                                    ; - SYM_GRP       -> TAB_GRP
                                    ; - SYM_ALIAS:    -> TAB_ALIAS
                                    ; for SYM_INTERNAL:
                                    ; linked list of labels for current segment
                                    ; (used for BackPatch)
                                    ; next field in STRUCT,UNION,RECORD

; for SYM_UNDEFINED, SYM_EXTERNAL, SYM_ALIAS and SYM_GRP:
; predecessor of current symbol with the same state, to allow fast removes.
; Actually, the only symbols which may change the state and thus
; have a chance to be removed are SYM_UNDEFINED and SYM_EXTERNAL ( weak=TRUE )
; during pass one.

    union
     prev           asym_t ?        ; used by PROC symbols (SYM_INTERNAL) for linked list, TAB_PROC
     nextproc       asym_t ?        ; used by PROC locals (SYM_STACK) for linked list
     nextlocal      asym_t ?        ; used by PROC params (SYM_STACK) for linked list
     nextparam      asym_t ?        ; used by SYM_EXTERNAL (weak=FALSE) if altname is set
     ivalue         char_t ?        ; v2.09: type changed from char * to char[]
    ends
   .ends

;---------------------------------------------------------------------------
; Structures for grpdef, segdef, externdef, pubdef, included library,
; procedure and symbolic integer constants.
;---------------------------------------------------------------------------

.template seg_item
    next            segitem_t ?
    iseg            asym_t ?
   .ends

.template grp_info
    seglist         segitem_t ?     ; list of segments in the group
    grp_idx         int_t ?         ; its group index (OMF)
    lname_idx       int_t ?         ; LNAME index (OMF only)
    numseg          uint_t ?        ; OMF: number of segments in the group
   .ends


.template seg_info
    sgroup          asym_t ?        ; segment's group or NULL
    start_loc       uint_t ?        ; starting offset of current ledata or lidata
    union
     current_loc    uint_t ?        ; current offset in current ledata or lidata
     reloc_offset   uint_t ?        ; ELF: reloc file offset
     start_offset   uint_t ?        ; BIN: start offset in group
    ends
    CodeBuffer      string_t ?      ;
    bytes_written   uint_t ?        ; initialized bytes in segment
    record
     readonly       uchar_t : 1 ?   ; if segment is readonly
     information    uchar_t : 1 ?   ; if segment is info only (COFF/ELF)
     force32        uchar_t : 1 ?   ; force 32bit segdef (OMF only)
     data_in_code   uchar_t : 1 ?   ; data items in code segm (OMF only)
     internal       uchar_t : 1 ?   ; internal segment with private buffer
     written        uchar_t : 1 ?   ; code/data just written
     linnum_init    uchar_t : 1 ?   ; v2.10: linnum data emitted for segment?
     align_rva      uchar_t : 1 ?   ; alignment modifies RVA only, filepos not affected
    ends
    Ofssize         uchar_t ?       ; segment's offset size
    characteristics uchar_t ?       ; used by COFF/ELF/PE
    alignment       uchar_t ?       ; is value 2^x
    union
     label_list     asym_t ?        ; linked list of labels in this seg
     flushfunc      proc local __ccall :asym_t, :ptr byte, :dword, :ptr
    ends
    head            ptr fixup ?     ; fixup queue head
    tail            ptr fixup ?     ; fixup queue tail
    union
     LinnumQueue    ptr_t ?         ; for COFF line numbers
     fileoffset     uint_t ?        ; used by BIN + ELF
     num_linnums    uint_t ?        ; used by COFF (after LinnumQueue has been read)
    ends
    num_relocs      uint_t ?        ; used by COFF/ELF
    seg_idx         uint_t ?        ; segment #; v2.12: changed from short to unsigned
    segtype         uint_t ?        ; segment's type (code, data, ...)
    lname_idx       int_t ?         ; segment's name LNAME index (OMF only)
    clsym           asym_t ?        ; segment's class name (stored in an asym item)
    union
     abs_frame      uint_t ?        ; ABS seg, frame number (OMF,BIN)
     comdat_number  uint_t ?        ; associated COMDAT segno (COFF)
     comdat_idx     uint_t ?        ; lname index of COMDAT symbol (OMF)
    ends
    combine         uchar_t ?       ; combine type, see omfspec.inc
    comdatselection uchar_t ?       ; if > 0, it's a COMDAT (COFF/OMF)
    union
     abs_offset     uint_t ?        ; ABS seg, offset (OMF only)
     aliasname      string_t ?      ; ALIAS name (COFF/ELF only)
    ends
   .ends

MAX_SEGALIGNMENT    equ 0xFF

; PROC item

.template proc_info

    regslist        ptr word ?      ; list of registers to be saved
    paralist        asym_t ?        ; list of parameters
    locallist       asym_t ?        ; list of local variables
    labellist       asym_t ?        ; list of local labels
    parasize        uint_t ?        ; total no. of bytes used by parameters
    localsize       uint_t ?        ; total no. of bytes used by local variables
    prologuearg     string_t ?      ; prologuearg attribute
    exc_handler     asym_t ?        ; exc handler set by FRAME
    ReservedStack   int_t ?         ; win64: additional reserved stack
    prolog_list_pos uint_t ?        ; prologue list pos
    record
     has_vararg     uchar_t : 1 ?   ; last param is VARARG
     pe_type        uchar_t : 1 ?   ; PROC: prolog-epilog type, 1=use LEAVE
     forceframe     uchar_t : 1 ?   ; PROC: FORCEFRAME prologuearg?
     loadds         uchar_t : 1 ?   ; PROC: LOADDS prologuearg?
     stackparam     uchar_t : 1 ?   ; PROC: 1=stack params exists ( not just register params )
     isframe        uchar_t : 1 ?   ; PROC: FRAME attribute set?
     fpo            uchar_t : 1 ?   ;
     usesds         uchar_t : 1 ?   ; PROC: USESDS prologuearg?
    ends
    size_prolog     uchar_t ?       ; v2.10: prologue size
    basereg         ushort_t ?      ; v2.11: stack base register
   .ends

; macro parameter

.template mparm_list
    deflt           string_t ?      ; optional default parm
    required        uchar_t ?       ; is parm required (REQ)
   .ends
    mparm_t         typedef ptr mparm_list

; macro line

    srcline_t       typedef ptr srcline

.template srcline
    next            srcline_t ?
    ph_count        uchar_t ?       ; placeholders contained in this line
    line            char_t 1 dup(?)
   .ends

; macro item

.template macro_info
    parmcnt         ushort_t ?      ; no of params
    union
     localcnt       ushort_t ?      ; no of locals
     autoexp        ushort_t ?      ; auto-expansion flags if predefined macro
    ends
    parmlist        mparm_t ?       ; array of parameter items
    lines           srcline_t ?     ; prepared macro source lines
    srcfile         uint_t ?        ; sourcefile index
   .ends

; STRUCT field

.enum type_kind {
    TYPE_NONE,
    TYPE_STRUCT,
    TYPE_UNION,
    TYPE_TYPEDEF,
    TYPE_RECORD
    }

.template struct_info
    head            asym_t ?        ; STRUCT/UNION/RECORD: start of field list
    tail            asym_t ?        ; STRUCT/UNION/RECORD: current/next field
    alignment       uchar_t ?       ; STRUCT: 1,2,4,8,16 or 32
    record
     isOpen         uchar_t : 1 ?   ; STRUCT/UNION: set until the matching ENDS is found
     OrgInside      uchar_t : 1 ?   ; STRUCT: struct contains an ORG
    ends
   .ends

SymAlloc        proto __ccall :string_t
SymFree         proto __ccall :asym_t
SymCreate       proto __ccall :string_t
SymLCreate      proto __ccall :string_t
SymAddGlobal    proto __ccall :asym_t
SymAddLocal     proto __ccall :asym_t, :string_t
SymLookup       proto __ccall :string_t
SymLookupLocal  proto __ccall :string_t
SymFind         proto fastcall :string_t

SymSearch macro x
    exitm<SymFind(x)>
    endm

SymInit         proto __ccall
SymPassInit     proto __ccall :int_t
SymMakeAllSymbolsPublic proto __ccall
SymGetAll       proto __ccall :ptr asym_t
SymEnum         proto __ccall :asym_t, :ptr int_t
SymGetCount     proto __ccall

StrCmpFunc_t    typedef proto fastcall :ptr, :ptr, :size_t
StrCmpFunc      typedef ptr StrCmpFunc_t

externdef       SymCmpFunc:StrCmpFunc

SymSetCmpFunc   proto __ccall
SymClearLocal   proto __ccall
SymSetLocal     proto __ccall :asym_t
SymGetLocal     proto __ccall :asym_t

endif
.pragma list(pop)
