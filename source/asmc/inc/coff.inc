; COFF.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; prototypes of functions defined in coff.asm
;
ifndef __COFF_INC
define __COFF_INC

.enum dbgseg_index {
    DBGS_SYMBOLS,
    DBGS_TYPES,
    DBGS_MAX
    }

.template qditem
    next ptr byte ?
    size dd ?
   .ends

.template dbg_section
    s ptr dsym ?
    q qdesc <>
   .ends

; v2.12: all coff global variables replaced by struct coffmod

.template coffmod
    directives      ptr dsym ?  ; .drectve section, contains linker directives
    sxdata          ptr dsym ?  ; section for safe exception handler data
    lastproc        ptr asym ?  ; used if -Zd is set
    dot_file_value  ptr sbyte ? ; value of .file symbol (isn't written by Masm v8+)
    start_data      dd ?        ; file position of start section data
    size_data       dd ?        ; total of section contents (incl relocs + linnums)
    start_files     dd ?        ; symbol table index of first .file entry used by line number info
    sectionstart    dd ?        ; symbol table index of first section
    SymDeb          dbg_section DBGS_MAX dup(<>) ; codeview debug sections
    head            ptr stringitem ?
    tail            ptr stringitem ?
    size            dd ?
   .ends

coff_init proto

endif
