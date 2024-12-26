; DEFLATE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __DEFLATE_INC
define __DEFLATE_INC

include stdio.inc

ifndef __ccall
ifdef _WIN64
define __ccall <fastcall>   ; Use fastcall for -elf64
ifdef __UNIX__
define _LIN64
endif
elseifdef __UNIX__
define __ccall <syscall>
else
define __ccall <c>
endif
endif

define ER_ZIP           2
define ER_BADERR        3
define ER_MEM           4
define ER_CRCERR        5
define ER_NOZIP         9
define ER_FIND          11
define ER_OPEN          12
define ER_DISK          50
define ER_USERABORT     66
define ER_READARCH      (-2)

define ZIPLOCALID       0x04034B50  ; signature local file
define ZIPCENTRALID     0x02014B50  ; signature central file
define ZIPDIGITALID     0x05054B50  ; digital signature
define ZIPENDCENTRALID  0x06054B50  ; signature end central

;
; Huffman code lookup table entry--this entry is four bytes for machines
;   that have 16-bit pointers (e.g. PC's in the small or medium model).
;   Valid extra bits are 0..13.  e == 15 is EOB (end of block), e == 16
;   means that v is a literal, 16 < e < 32 means that v is a pointer to
;   the next table, which codes e - 16 bits, and lastly e == 99 indicates
;   an unused code.  If a code with e == 99 is looked up, this implies an
;   error in the data.
;
HUFT            struct size_t
e               db ?    ; number of extra bits or operation
b               db ?    ; number of bits in this code or subcode
union
 n              dd ?    ; literal, length base, or distance base
 t              ptr_t ? ; pointer to next level of table
ends
HUFT            ends
PHUFT           typedef ptr HUFT

ZIPLOCAL        struct 1
Signature       dd ?    ; local file header signature
version         dw ?    ; version needed to extract
flag            dw ?    ; general purpose bit flag
method          dw ?    ; compression method
time            dw ?    ; last mod file time
date            dw ?    ; last mod file date
crc             dd ?    ; crc-32
csize           dd ?    ; compressed size
fsize           dd ?    ; uncompressed size
fnsize          dw ?    ; file name length
extsize         dw ?    ; extra field length
ZIPLOCAL        ends
PZIPLOCAL       typedef ptr ZIPLOCAL

ZIPCENTRAL      struct 1
Signature       dd ?    ; central file header signature
version_made    dw ?    ; version made by
version_need    dw ?    ; version needed to extract
bitflag         dw ?    ; general purpose bit flag
method          dw ?    ; compression method
time            dw ?    ; last mod file time
date            dw ?    ; last mod file date
crc             dd ?    ; crc-32
csize           dd ?    ; compressed size
fsize           dd ?    ; uncompressed size
fnsize          dw ?    ; file name length
extsize         dw ?    ; extra field length
cmtsize         dw ?    ; file comment length
disk            dw ?    ; disk number start
int_attrib      dw ?    ; internal file attributes
ext_attrib      dd ?    ; external file attributes
off_local       dd ?    ; relative offset of local header
ZIPCENTRAL      ends

ZIPENDCENTRAL   struct 1
Signature       dd ?    ; end of central dir signature
disk_cur        dw ?    ; number of this disk
disk_one        dw ?    ; number at start of the central directory
entry_cur       dw ?    ; central directory on this disk
entry_dir       dw ?    ; total entries in the central directory
size_cent       dd ?    ; size central directory
off_cent        dd ?    ; offset central directory
comment_size    dw ?    ; file comment length
ZIPENDCENTRAL   ends


externdef compresslevel:int_t ; 0-9

deflate proto __cdecl :string_t, :LPFILE, :PZIPLOCAL
inflate proto __cdecl :string_t, :LPFILE, :PZIPLOCAL
explode proto __cdecl :string_t, :LPFILE, :PZIPLOCAL

huft_free proto __ccall :PHUFT
huft_build proto __ccall :ptr DWORD, :DWORD, :DWORD, :ptr WORD, :ptr WORD, :PHUFT, :ptr SDWORD

endif
