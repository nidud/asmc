; DEFLATE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __DEFLATE_INC
define __DEFLATE_INC

include stdio.inc

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
define ZIPENDSENTRID    0x06054B50  ; signature end central

.pragma pack(push, 1)

.template ZipLocal

     Signature      dd ?    ; local file header signature
     version        dw ?    ; version needed to extract
     flag           dw ?    ; general purpose bit flag
     method         dw ?    ; compression method
     time           dw ?    ; last mod file time
     date           dw ?    ; last mod file date
     crc            dd ?    ; crc-32
     csize          dd ?    ; compressed size
     fsize          dd ?    ; uncompressed size
     fnsize         dw ?    ; file name length
     extsize        dw ?    ; extra field length
    .ends

.template ZipCentral

     Signature      dd ?    ; central file header signature
     version_made   dw ?    ; version made by
     version_need   dw ?    ; version needed to extract
     bitflag        dw ?    ; general purpose bit flag
     method         dw ?    ; compression method
     time           dw ?    ; last mod file time
     date           dw ?    ; last mod file date
     crc            dd ?    ; crc-32
     csize          dd ?    ; compressed size
     fsize          dd ?    ; uncompressed size
     fnsize         dw ?    ; file name length
     extsize        dw ?    ; extra field length
     cmtsize        dw ?    ; file comment length
     disk           dw ?    ; disk number start
     int_attrib     dw ?    ; internal file attributes
     ext_attrib     dd ?    ; external file attributes
     off_local      dd ?    ; relative offset of local header
    .ends

.template ZipEndCent

     Signature      dd ?    ; end of central dir signature
     disk_cur       dw ?    ; number of this disk
     disk_one       dw ?    ; number at start of the central directory
     entry_cur      dw ?    ; central directory on this disk
     entry_dir      dw ?    ; total entries in the central directory
     size_cent      dd ?    ; size central directory
     off_cent       dd ?    ; offset central directory
     comment_size   dw ?    ; file comment length
    .ends

.pragma pack(pop)

externdef compresslevel:int_t ; 0-9

deflate proto __cdecl :string_t, :ptr FILE, :ptr ZipLocal
inflate proto __cdecl :string_t, :ptr FILE, :ptr ZipLocal

endif
