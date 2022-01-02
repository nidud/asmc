; OMFINT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: OMF internal definitions.
;
ifndef __OMFINT_INC
define __OMFINT_INC

WriteU16 proto watcall p:ptr word, n:word {
    mov [rax],dx
    }
WriteU32 proto watcall p:ptr dword, n:dword {
    mov [rax],edx
    }

; v2.11: max object record size reduced to 0xFF0 so the buffer may
; be located on the stack as a local variable.
; for 8086, size reduced to 1024. This should only affect GRPDEF
; records, since all other record types are already ensured not to
; exceed 1024.

define OBJ_BUFFER_SIZE 0x0FF0


;  A COMENT record needs additional data to be attached.
.template coment_info
    attr        db ?        ; attribute field from coment record
    cmt_class   db ?        ; class field from coment record
   .ends


.template modend_info
    main_module db ?        ; module is a main module
    start_addrs db ?        ; module has start address
   .ends

; LNAMES, EXTDEFs, and COMDEFs all use this structure. The actual
; LNAMES/etc are in the data attached to the record.

.template lnames_info
    first_idx   dw ?        ; index of first name in this record
    num_names   dw ?        ; number of names in this record
   .ends

; the group's segments are attached
.template grpdef_info
    idx         dw ?        ; index of this grpdef record
   .ends


.template physref
    fram        dw ?        ; frame number of physical reference
    offs        dd ?        ; offset into reference
   .ends


.template segdef_info
    idx             dw ?        ; index for this segment
    use_32          db ?        ; use_32 for this segment
    _align          db ?        ; align field (see omfspec.inc)
    combine         db ?        ; combine field (see omfspec.inc)
    abs             physref <>  ; (conditional) absolute physical reference
    seg_length      dd ?        ; length of this segment
    seg_lname_idx   dw ?        ; segment's name lname index
    class_lname_idx dw ?        ; segment's class lname index
    ovl_lname_idx   dw ?        ; segment's overlay lname index
   .ends


; the contents of the LEDATA is attached
.template ledata_info
    idx         dw ?        ; index of segment the data belongs to
    offs        dd ?        ; offset into segment of start of data
   .ends


; base info is supplied by PUBDEF, LINNUM and COMDAT
.template base_info
    grp_idx     dw ?        ; index of the group base
    seg_idx     dw ?        ; index of the segment
    fram        dw ?        ; used if grp_idx == 0 && seg_idx == 0
   .ends


; line number info - the items itself are attached
.template linnum_info
    base        base_info <>
   .ends


; public info - the items itself are attached
.template pubdef_info
    base        base_info <>
   .ends


; the data that comprises the record is attached.
.template comdat_info
    flags               db ?        ; see COMDAT flags in omfspec.h
    attributes          db ?        ; see COMDAT allocation type + selection criteria in omfspec.h
    _align              db ?        ; see COMDAT alignment in omfspec.h
    offs                dd ?        ; may be 16- or 32-bit
    type_idx            dw ?        ; type index field, usually 0
    base                base_info<> ; used only if allocation type is COMDAT_EXPLICIT
    public_lname_idx    dw ?        ; the COMDAT's public name (lname index)
   .ends


; the line number info is attached.
.template linsym_info
    flags               db ?
    public_lname_idx    dw ?        ; the COMDAT's public name (lname index)
   .ends


.template omf_rec
    length          dd ?            ; # of bytes in 'data'    (PRIVATE)
    curoff          dd ?            ; curr. pos in 'data'     (PRIVATE)
    pdata           ptr byte ?      ; data for this record    (PRIVATE)
    command         db ?            ; the command field for this record
    is_32           db ?            ; a Microsoft 32bit record?
    union d                         ; data depending on record type
     coment         coment_info <>  ; CMD_COMENT
     modend         modend_info <>  ; CMD_MODEND
     lnames         lnames_info <>  ; CMD_LNAMES
     extdef         lnames_info <>  ; CMD_EXTDEF
     comdef         lnames_info <>  ; CMD_COMDEF
     grpdef         grpdef_info <>  ; CMD_GRPDEF
     segdef         segdef_info <>  ; CMD_SEGDEF
     ledata         ledata_info <>  ; CMD_LEDATA
     linnum         linnum_info <>  ; CMD_LINNUM
     pubdef         pubdef_info <>  ; CMD_PUBDEF
     comdat         comdat_info <>  ; CMD_COMDAT
     linsym         linsym_info <>  ; CMD_LINSYM
    ends
   .ends

omf_write_record    proto __ccall :ptr omf_rec

define FIX_GEN_MAX          11   ; max size needed for OmfFixGenFix()
define FIX_GEN_MODEND_MAX   9    ; max size needed for OmfFixGenFixModend()

.enum fixgen_types {
    FIX_GEN_INTEL,
    FIX_GEN_MS386
    }

OmfFixGenFix        proto __ccall :ptr fixup, :dword, :ptr byte, :fixgen_types
OmfFixGenFixModend  proto __ccall :ptr fixup, :ptr byte, :dword, :fixgen_types

endif
