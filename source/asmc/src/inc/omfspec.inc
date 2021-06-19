.pragma list(push, 0)
ifndef __OMFSPEC_INC
__OMFSPEC_INC equ <>

;; OMF basics

SEGDEF_ALIGN_ABS	equ 0 ;; absolute segment - no alignment
SEGDEF_ALIGN_BYTE	equ 1 ;; relocatable seg  - byte aligned
SEGDEF_ALIGN_WORD	equ 2 ;;		  - word aligned
SEGDEF_ALIGN_PARA	equ 3 ;;		  - para aligned
SEGDEF_ALIGN_PAGE	equ 4 ;;		  - page aligned
SEGDEF_ALIGN_DWORD	equ 5 ;;		  - dword aligned


;;  INTEL Segment Combination Attributes - C field
;;  JWasm uses COMB_INVALID, COMB_ADDOFF, COMB_STACK & COMB_COMMON


COMB_INVALID		equ 0 ;; PRIVATE attribute
COMB_ABOVEALL		equ 1 ;; marked as "reserved"
COMB_ADDOFF		equ 2 ;; PUBLIC attribute
COMB_BAD		equ 3 ;; marked as "reserved"
COMB_FOUR		equ 4 ;; comment: same as 2
COMB_STACK		equ 5 ;; STACK attribute
COMB_COMMON		equ 6 ;; COMMON attribute
COMB_ALIGNTOP		equ 7 ;; comment: same as 2


;;  INTEL Frame Specifiers
;;  FRAME_ABS[WD] not supported according to TIS OMF docs.
;;  FRAME_NONE should never appear in object modules, it's just
;;  a void used by jwasm internally.


FRAME_SEG		equ 0 ;; segment index
FRAME_GRP		equ 1 ;; group index
FRAME_EXT		equ 2 ;; external index
FRAME_LOC		equ 4 ;; segment index of last LEDATA
FRAME_TARG		equ 5 ;; frame same as target
FRAME_NONE		equ 6 ;; no frame


;;  INTEL Target Specifiers
;;  TARGET_ABS[WD] is supported for THREAD sub-records only, according to TIS OMF docs;
;;  Since JWasm won't write THREAD sub-records, those methods are invalid.

TARGET_SEGWD		equ 0	    ;; segment index with displacement
TARGET_GRPWD		equ 1	    ;; group index with displacement
TARGET_EXTWD		equ 2	    ;; external index with displacement
TARGET_SEG		equ 4	    ;; segment index, no displacement
TARGET_GRP		equ 5	    ;; group index, no displacement
TARGET_EXT		equ 6	    ;; external index, no displacement
TARGET_WITH_DISPL	equ not 4   ;; frame with displacement


;;  Bits in FIXUPP records

FIXUPP_FIXUP		equ 0x80
FIXDAT_FTHREAD		equ 0x80
FIXDAT_TTHREAD		equ 8
FIXDAT_PBIT		equ 4
FIXDAT_MBIT		equ 0x40
TRDDAT_DBIT		equ 0x40

;;  INTEL Group Specifiers

GRP_SEGIDX		equ 0xff    ;; group segment index
GRP_EXTIDX		equ 0xfe    ;; group external index
GRP_FULLNAME		equ 0xfd    ;; full name indices
GRP_LTLDATA		equ 0xfb    ;; load time data info
GRP_ADDR		equ 0xfa    ;; load time addr for the group



;;  INTEL Object Record Types

CMD_MIN_CMD		equ 0x80    ;; minimum cmd enum
CMD_THEADR		equ 0x80    ;; translator header
CMD_LHEADR		equ 0x82    ;; library header
CMD_COMENT		equ 0x88    ;; comment record
CMD_MODEND		equ 0x8a    ;; end of module record
CMD_EXTDEF		equ 0x8c    ;; import names record
CMD_TYPDEF		equ 0x8e    ;; type definition record
CMD_PUBDEF		equ 0x90    ;; public names record
CMD_LINNUM		equ 0x94    ;; line number record
CMD_LNAMES		equ 0x96    ;; list of names record
CMD_SEGDEF		equ 0x98    ;; segment definition record
CMD_GRPDEF		equ 0x9a    ;; group definition record
CMD_FIXUPP		equ 0x9c    ;; relocation record
CMD_LEDATA		equ 0xa0    ;; logical enumerated data
CMD_LIDATA		equ 0xa2    ;; logical iterated data
CMD_COMDEF		equ 0xb0    ;; communal definition
CMD_BAKPAT		equ 0xb2    ;; backpatch record (for Quick C)

;; the following types are used to make local names known to the linker

CMD_LEXTDEF		equ 0xb4    ;; local import names record
CMD_STATIC_EXTDEF	equ 0xb4
CMD_LPUBDEF		equ 0xb6    ;; local public names def record
CMD_LCOMDEF		equ 0xb8    ;; local communal names def record
CMD_STATIC_COMDEF	equ 0xb8

CMD_CEXTDEF		equ 0xbc    ;; external reference to a COMDAT
CMD_COMDAT		equ 0xc2    ;; initialized communal data record
CMD_LINSYM		equ 0xc4    ;; symbol line numbers
CMD_ALIAS		equ 0xc6    ;; alias definition record
CMD_NBKPAT		equ 0xc8    ;; named backpatch record (quick c?)
CMD_LLNAMES		equ 0xca    ;; a "local" lnames
CMD_MAX_CMD		equ 0xca    ;; maximum cmd enum

;; OMF fixup types; 4-bit-"location"-field in FIXUP sub-records; see omffixup.c.

LOC_OFFSET_LO		equ 0	;; 8-bit (lowbyte) offset
LOC_OFFSET		equ 1	;; 16-bit offset
LOC_BASE		equ 2	;; segment (always 16-bit)
LOC_BASE_OFFSET		equ 3	;; 16-bit offset & 16-bit segment
LOC_OFFSET_HI		equ 4	;; 8-bit (hibyte) offset
LOC_MS_LINK_OFFSET	equ 5	;; 16-bit "loader-resolved" offset (MS)
LOC_MS_OFFSET_32	equ 9	;; 32-bit offset (MS)
LOC_MS_BASE_OFFSET_32	equ 11	;; 32-bit offset & 16-bit segment (MS)
LOC_MS_LINK_OFFSET_32	equ 13	;; 32-bit "loader-resolved" offset (MS)

;; Comment Type

CMT_TNP			equ 0x80 ;; no purge bit
CMT_TNL			equ 0x40 ;; no list bit

;; Comment classes. JWasm uses:
;; - CMT_DOSSEG		  : dosseg directive
;; - CMT_DEFAULT_LIBRARY  : includelib directive
;; - CMT_OMF_EXT	  : PROC's EXPORT attribute
;; - CMT_MS_OMF		  : codeview debug info version
;; - CMT_MS_END_PASS_1	  : end of pass one
;; - CMT_WKEXT		  : extern directive with altname
;; - CMT_DEPENDENCY	  : include directive, Borland specific
;; - CMT_DISASM_DIRECTIVE : wdis special
;; - CMT_LINKER_DIRECTIVE : wlink specials

CMT_DOSSEG		equ 0x9e ;; DOSSEG directive
CMT_DEFAULT_LIBRARY	equ 0x9f ;; Default library cmd
CMT_OMF_EXT		equ 0xa0 ;; OMF extension
CMT_MS_OMF		equ 0xa1 ;; MS codeview debug info included
CMT_MS_END_PASS_1	equ 0xa2 ;; MS end of linker pass 1
CMT_WKEXT		equ 0xa8 ;; Weak external record
CMT_SRCFILE		equ 0xe8 ;; Borland source file record
CMT_DEPENDENCY		equ 0xe9 ;; Borland dependency record
CMT_DISASM_DIRECTIVE	equ 0xfd ;; Directive to disassemblers
CMT_LINKER_DIRECTIVE	equ 0xfe ;; Linker directive

;; Comment Class Subtype for CMT_OMF_EXT

CMT_EXT_IMPDEF		equ 0x01 ;; Subtype IMPDEF of OMF extension class
CMT_EXT_EXPDEF		equ 0x02 ;; Subtype EXPDEF of OMF extension class
CMT_EXT_INCDEF		equ 0x03 ;; Subtype INCDEF of OMF extension class
CMT_EXT_PMLIB		equ 0x04 ;; Protected Memory Library (OMF extension)
CMT_EXT_LNKDIR		equ 0x05 ;; Subtype LNKDIR of OMF extension class
CMT_EXT_BIGEND		equ 0x06
CMT_EXT_PRECOMP		equ 0x07


;;  Linker directives ( CMT_LINKER_DIRECTIVE - mostly WLINK directives )
;;  JWasm uses LDIR_OPT_FAR_CALLS only


LDIR_SOURCE_LANGUAGE	equ 'D' ;; dbg maj/min and source language
LDIR_DEFAULT_LIBRARY	equ 'L' ;; default library cmd
LDIR_OPT_FAR_CALLS	equ 'O' ;; optimize far calls/jmps for this seg

;;  Disasm directives ( CMT_DISASM_DIRECTIVE )
;;  this is a feature supported by OW WDis.

;;  DDIR_SCAN_TABLE is used by the code generator to indicate data in a
;;  code segment.  i.e., scan tables generated for switch()s, floating point
;;  constants and string constants.  The 'S' is followed by a segment index,
;;  then the start and end+1 offsets into the segment which are 16-bit in
;;  regular object files, and 32-bit in EasyOMF and Microsoft 386.
;;  If the segment index is zero, then it is followed by a LNAME index which
;;  identifies the COMDAT symbol that the scan table belongs to.

DDIR_SCAN_TABLE_32	equ 'S'
DDIR_SCAN_TABLE		equ 's'

;;  COMDEF types

COMDEF_FAR		equ 0x61 ;; FAR variable
COMDEF_NEAR		equ 0x62 ;; NEAR variable
COMDEF_LEAF_SIZE	equ 0x80 ;; bit set if size > 0x7f
COMDEF_LEAF_2		equ 0x81 ;; 2 byte size field
COMDEF_LEAF_3		equ 0x84 ;; 3 byte size field
COMDEF_LEAF_4		equ 0x88 ;; 4 byte size field


;; COMDAT (initialized communal data);
;; record type 0xC2/0xC3;
;; MS extension introduced for MSC 7.

;;  COMDAT flags

COMDAT_CONTINUE		equ 0x01 ;; continuation of previous COMDAT
COMDAT_ITERATED		equ 0x02 ;; LIDATA form of COMDAT
COMDAT_LOCAL		equ 0x04 ;; COMDAT is local to this module
COMDAT_DATAINCODE	equ 0x08 ;; data in code segment

;;  COMDAT allocation type ( low-order 4 bits of attributes field )

COMDAT_ALLOC_MASK	equ 0x0f
COMDAT_EXPLICIT		equ 0x00 ;; in given segment ( base grp, seg and frame )
COMDAT_FAR_CODE		equ 0x01 ;; allocate CODE use16 segment
COMDAT_FAR_DATA		equ 0x02 ;; allocate DATA use16 segment
COMDAT_CODE32		equ 0x03 ;; allocate CODE use32 segment
COMDAT_DATA32		equ 0x04 ;; allocate DATA use32 segment

;;  COMDAT selection criteria ( high-order 4 bits of attributes field )

COMDAT_MATCH_MASK	equ 0xf0
COMDAT_MATCH_NONE	equ 0x00 ;; don't match anyone - only 1 instance allowed
COMDAT_MATCH_ANY	equ 0x10 ;; pick any instance
COMDAT_MATCH_SAME	equ 0x20 ;; must be same size - or linker will emit an error
COMDAT_MATCH_EXACT	equ 0x30 ;; pick any instance - but checksums must match

;;  COMDAT alignment

COMDAT_ALIGN_SEG	equ 0x00 ;; align from SEGDEF
COMDAT_ALIGN_BYTE	equ 0x01
COMDAT_ALIGN_WORD	equ 0x02
COMDAT_ALIGN_PARA	equ 0x03
COMDAT_ALIGN_4K		equ 0x04
COMDAT_ALIGN_DWORD	equ 0x05

endif
.pragma list(pop)
