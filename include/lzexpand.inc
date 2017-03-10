ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;; Public interface to LZEXP?.LIB.
;;
ifndef _LZEXPAND_
_LZEXPAND_ equ 1

;;
;;* Error Return Codes
;;

LZERROR_BADINHANDLE	equ -1	;; invalid input handle
LZERROR_BADOUTHANDLE	equ -2	;; invalid output handle
LZERROR_READ		equ -3	;; corrupt compressed file format
LZERROR_WRITE		equ -4	;; out of space for output file
LZERROR_GLOBALLOC	equ -5	;; insufficient memory for LZFile struct
LZERROR_GLOBLOCK	equ -6	;; bad global handle
LZERROR_BADVALUE	equ -7	;; input parameter out of acceptable range
LZERROR_UNKNOWNALG	equ -8	;; compression algorithm not recognized


;;
;;* Prototypes
;;

;INT
LZStart proto _CType

;VOID
LZDone proto _CType

;LONG
CopyLZFile proto _CType \
		      : SINT,
		      : SINT

;LONG
LZCopy proto _CType \
		      : SINT,
		      : SINT

;INT
LZInit proto _CType \
		      : SINT

;INT
GetExpandedNameA proto _CType \
		      : LPSTR,
		      : LPSTR
GetExpandedNameW proto _CType \
		      : LPWSTR,
		      : LPWSTR

ifdef _UNICODE
GetExpandedName		equ <GetExpandedNameW>
else
GetExpandedName		equ <GetExpandedNameA>
endif ;; NOT UNICODE

;INT
LZOpenFileA proto _CType \
		      : LPSTR,
		      : LPOFSTRUCT,
		      : WORD
LZOpenFileW proto _CType \
		      : LPWSTR,
		      : LPOFSTRUCT,
		      : WORD
ifdef _UNICODE
LZOpenFile		equ <LZOpenFileW>
else
LZOpenFile		equ <LZOpenFileA>
endif ;; NOT UNICODE

;LONG
LZSeek proto _CType \
		      : SINT,
		      : LONG,
		      : SINT

;INT
LZRead proto _CType \
		      : SINT,
		      : LPSTR,
		      : SINT

;VOID
LZClose proto _CType \
		      : SINT

endif ;; _LZEXPAND_

.list
