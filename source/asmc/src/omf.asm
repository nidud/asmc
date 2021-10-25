; OMF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  handle OMF output format.
;

include limits.inc
include time.inc
include sys/stat.inc

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include mangle.inc
include extern.inc
include fixup.inc
include omf.inc
include omfint.inc
include omfspec.inc
include fastpass.inc
include tokenize.inc ;; needed because of StringBufferEnd usage
include input.inc
include linnum.inc

define TRUNCATE 1
define MULTIHDR 1     ;; write muliple THEADR records (Masm compatible)
define WRITEIMPDEF 0  ;; write IMPDEF coment records for OPTION DLLIMPORT

define MANGLE_BYTES 8 ;; extra size required for name decoration
define MAX_ID_LEN_OMF 247
define MAX_LNAME_SIZE 1024
define MAX_EXT_LENGTH 1020 ;; max length ( in chars ) of EXTDEF
define MAX_PUB_LENGTH 1024 ;; max length of PUBDEF record

include io.inc

.enum {
    TIME_SEC_B  = 0,
    TIME_SEC_F  = 0x001f,
    TIME_MIN_B  = 5,
    TIME_MIN_F  = 0x07e0,
    TIME_HOUR_B = 11,
    TIME_HOUR_F = 0xf800
    }

.enum {
    DATE_DAY_B  = 0,
    DATE_DAY_F  = 0x001f,
    DATE_MON_B  = 5,
    DATE_MON_F  = 0x01e0,
    DATE_YEAR_B = 9,
    DATE_YEAR_F = 0xfe00
    }

DOS_DATETIME union
    struct dos
        time dw ?
        date dw ?
    ends
    timet time_t ?
DOS_DATETIME ends


cv_write_debug_tables proto :ptr dsym, :ptr dsym, :ptr
SortSegments proto :int_t

externdef LinnumQueue:qdesc ;; queue of line_num_info items
externdef szNull:char_t

.data

; LastCodeBufSize stores the size of the code buffer AFTER it has been
; written in omf_write_ledata().
; This allows to get the content bytes for the listing.
; This is a rather hackish "design" and is to be improved.

LastCodeBufSize int_t 0

seg_pos         uint_t 0 ; file pos of SEGDEF record(s)
public_pos      uint_t 0 ; file pos of PUBDEF record(s)
end_of_header   uint_t 0 ; file pos of "end of header"

; v2.12: moved from inside omf_write_lnames()

startitem       int_t 0
startext        int_t 0

if MULTIHDR
ln_srcfile      uint_t 0         ; last file for which line numbers have been written
endif
ln_is32         uint_8 0         ; last mode for which line numbers have been written
ln_size         uint_16 0        ; size of line number info

; CodeView symbolic debug info

.enum dbgseg_index {
    DBGS_SYMBOLS,
    DBGS_TYPES,
    DBGS_MAX
    }

.template dbg_section
    name        string_t ?
    cname       string_t ?
   .ends

ifndef __ASMC64__

SymDebParm dbg_section \
    { @CStr("$$SYMBOLS"), @CStr("DEBSYM") },
    { @CStr("$$TYPES"),   @CStr("DEBTYP") }


SymDebSeg dsym_t DBGS_MAX dup(0)
endif

    .code

ifndef __ASMC64__

    assume ecx:ptr omf_rec

omf_InitRec proc fastcall private obj:ptr omf_rec, cmd:byte

    xor eax,eax
    mov [ecx].length,eax
    mov [ecx].curoff,eax
    mov [ecx].pdata,eax
    mov [ecx].command,dl
    mov [ecx].is_32,al
    ret

omf_InitRec endp

    assume ecx:nothing

timet2dostime proc private x:time_t

    .if ( localtime( &x ) )

        mov ecx,eax
        mov eax,[ecx].tm.tm_year
        sub eax,80
        shl eax,DATE_YEAR_B
        mov edx,[ecx].tm.tm_mon
        inc edx
        shl edx,DATE_MON_B
        or  eax,edx
        mov edx,[ecx].tm.tm_mday
        shl edx,DATE_DAY_B
        or  eax,edx
        shl eax,16
        mov edx,[ecx].tm.tm_hour
        shl edx,TIME_HOUR_B
        or  eax,edx
        mov edx,[ecx].tm.tm_min
        shl edx,TIME_MIN_B
        or  eax,edx
        mov edx,[ecx].tm.tm_sec
        shr edx,1
        shl edx,TIME_SEC_B
        or  eax,edx
        .return
    .endif
    .return x
timet2dostime endp

    assume ecx:ptr omf_rec

Put8 proc fastcall private objr:ptr omf_rec, value:byte

    mov eax,[ecx].curoff
    inc [ecx].curoff
    add eax,[ecx].pdata
    mov [eax],dl
    ret

Put8 endp

Put16 proc fastcall private objr:ptr omf_rec, value:dword

    mov eax,[ecx].curoff
    add [ecx].curoff,2
    add eax,[ecx].pdata
    mov [eax],dx
    ret

Put16 endp

Put32 proc fastcall private objr:ptr omf_rec, value:dword

    mov eax,[ecx].curoff
    add [ecx].curoff,4
    add eax,[ecx].pdata
    mov [eax],edx
    ret

Put32 endp

PutIndex proc fastcall private objr:ptr omf_rec, index:dword
    ;
    ; index in OMF is limited to 0-7FFFh
    ; index values 0-7Fh are stored in 1 byte.
    ; index values 80h-7FFFh are stored in 2 bytes, the high
    ; order byte first ( with bit 7=1 ).
    ;
    mov eax,[ecx].curoff
    add eax,[ecx].pdata
    inc [ecx].curoff
    .if ( edx > 0x7f )
        or  dh,0x80
        mov [eax],dh
        inc [ecx].curoff
        inc eax
    .endif
    mov [eax],dl
    ret
PutIndex endp

PutData proc private uses esi edi objr:ptr omf_rec, pdata:ptr byte, len:size_t

    mov eax,len
    mov ecx,objr
    mov edi,[ecx].curoff
    add edi,[ecx].pdata
    add [ecx].curoff,eax
    mov esi,pdata
    mov ecx,eax
    rep movsb
    ret
PutData endp

PutName proc private objr:ptr omf_rec, name:string_t, len:size_t
if MAX_ID_LEN gt MAX_ID_LEN_OMF
    .if ( len > MAX_ID_LEN_OMF )
        asmerr( 2043 )
        mov len,MAX_ID_LEN_OMF
    .endif
endif
    mov eax,len
    mov ecx,objr
    mov edx,[ecx].curoff
    add edx,[ecx].pdata
    inc [ecx].curoff
    mov [edx],al
    PutData( ecx, name, eax )
    ret
PutName endp

AttachData proc private objr:ptr omf_rec, pdata:ptr byte, len:size_t
    mov ecx,objr
    mov [ecx].pdata,pdata
    mov [ecx].length,len
    ret
AttachData endp

TruncRec proto fastcall objr:ptr omf_rec {
    mov [ecx].omf_rec.length,[ecx].omf_rec.curoff
    }

    assume ecx:nothing

; return a group's index

omf_GetGrpIdx proc sym:ptr asym

    mov edx,sym
    xor eax,eax
    .if edx
        mov edx,[edx].dsym.grpinfo
        mov eax,[edx].grp_info.grp_idx
    .endif
    ret
omf_GetGrpIdx endp

endif

;; write OMF comment records about data in code.

omf_OutSelect proc uses esi edi ebx is_data:int_t
ifndef __ASMC64__

  local obj:omf_rec
  local currofs:uint_t
  local sel_idx:int_t
  local buffer[12]:byte ;; max is 11 ( see below )

    .data
     sel_start uint_t 0 ;; start offset of data items
    .code

    mov ebx,CurrSeg
    mov ebx,[ebx].dsym.seginfo

    .if ( is_data )

        ;; do nothing if it isn't the first data item or
        ;; if current segment isn't code

        .if ( [ebx].seg_info.data_in_code || \
            ( [ebx].seg_info.segtype != SEGTYPE_CODE ) )
            .return
        .endif

        mov sel_start,GetCurrOffset()
        mov [ebx].seg_info.data_in_code,TRUE

    .elseif ( [ebx].seg_info.data_in_code ) ;; data items written?

        mov [ebx].seg_info.data_in_code,FALSE

        .if ( write_to_file == TRUE )

            omf_InitRec( &obj, CMD_COMENT )
            mov obj.d.coment.attr,CMT_TNP
            mov obj.d.coment.cmt_class,CMT_DISASM_DIRECTIVE

            mov sel_idx,GetSegIdx( CurrSeg )

            AttachData( &obj, &buffer, 11 ) ; 11 = 1 + 2 + 4 + 4
            mov currofs,GetCurrOffset()

            .if ( ( sel_start > 0xffff ) || ( currofs > 0xffff ) )
                Put8( &obj, DDIR_SCAN_TABLE_32 )
                PutIndex( &obj, sel_idx )
                Put32( &obj, sel_start )
                Put32( &obj, currofs )
            .else
                Put8( &obj, DDIR_SCAN_TABLE )
                PutIndex( &obj, sel_idx )
                Put16( &obj, sel_start )
                Put16( &obj, currofs )
            .endif
            TruncRec( &obj )
            omf_write_record( &obj )
        .endif
    .endif
endif
    ret
omf_OutSelect endp

; write line number debug info.
; since v2.11, it's ensured that the size of this info will be < 1024.
; note the item structure:
;   uint_16 line_number
;   union {
;      uint_16 ofs16
;      uint_32 ofs32
;   }
; v2.11: create 16- or 32-bit data variant here!

ifndef __ASMC64__

omf_write_linnum proc private uses esi edi ebx is32:byte

  local obj:omf_rec

    .for ( esi = LinnumQueue.head, edi = StringBufferEnd: esi: esi = ebx )

        mov ebx,[esi].line_num_info.next
        mov eax,[esi].line_num_info.number
        stosw
        mov eax,[esi].line_num_info.offs
        .if ( is32 )
            stosd
        .else
            stosw
        .endif
    .endf
    mov LinnumQueue.head,NULL
    sub edi,StringBufferEnd
    .if ( edi )
        omf_InitRec( &obj, CMD_LINNUM )
        mov obj.is_32,is32
        AttachData( &obj, StringBufferEnd, edi )
        mov ebx,CurrSeg
        mov edi,[ebx].dsym.seginfo
        omf_GetGrpIdx( GetGroup( ebx ) )
        mov obj.d.linnum.base.grp_idx,ax ;; fixme ?
        mov obj.d.linnum.base.seg_idx,[edi].seg_info.seg_idx
        mov obj.d.linnum.base.frame,0; ;; field not used here
        omf_write_record( &obj )
    .endif
    ret

omf_write_linnum endp

omf_write_fixupp proc private uses esi edi ebx s:ptr dsym, is32:char_t

  local size:dword
  local type:fixgen_types
  local obj:omf_rec

    mov type,FIX_GEN_INTEL
    .if ( is32 )
        mov type,FIX_GEN_MS386
    .endif

    mov ebx,s
    mov esi,[ebx].dsym.seginfo
    mov ebx,[esi].seg_info.head

    .while ( ebx )
        .for ( edi = StringBufferEnd, size = 0: ebx: ebx = [ebx].fixup.nextrlc )
            .switch( [ebx].fixup.type )
            .case FIX_RELOFF32
            .case FIX_OFF32
            .case FIX_PTR32
                .continue .if ( !is32 )
                .endc
            .default
                .continue .if ( is32 )
                .endc
            .endsw
            .break .if ( size > 1020 - FIX_GEN_MAX )
            add edi,OmfFixGenFix( ebx, [esi].seg_info.start_loc, edi, type )
            mov eax,edi
            sub eax,StringBufferEnd
            mov size,eax
        .endf
        .if ( size )
            omf_InitRec( &obj, CMD_FIXUPP )
            mov obj.is_32,is32
            AttachData( &obj, StringBufferEnd, size )
            omf_write_record( &obj )
        .endif
    .endw
    ret

omf_write_fixupp endp

get_omfalign proto private alignment:byte

;; write an LEDATA record, optionally write fixups

omf_write_ledata proc private uses esi edi ebx s:ptr dsym

  local obj:omf_rec
  local size:int_t

    mov ebx,s
    mov esi,[ebx].dsym.seginfo

    mov eax,[esi].seg_info.current_loc
    sub eax,[esi].seg_info.start_loc
    mov size,eax

    .ifs ( eax > 0 && write_to_file == TRUE )

        mov LastCodeBufSize,size

        .if ( [esi].seg_info.comdatselection )

            ;; if the COMDAT symbol has been referenced in a FIXUPP,
            ;; a CEXTDEF has to be written.

            .if ( [ebx].asym.flags & S_USED )

                omf_InitRec( &obj, CMD_CEXTDEF )
                AttachData( &obj, StringBufferEnd, 2 * sizeof( uint_16 ) )
                PutIndex( &obj, [esi].seg_info.comdat_idx ); ;; Index
                PutIndex( &obj, 0 ) ;; Type
                TruncRec( &obj )
                omf_write_record( &obj )
                .if ( [esi].seg_info.seg_idx == 0 )
                    mov [esi].seg_info.seg_idx,startext
                    inc startext
                .endif
            .endif

            omf_InitRec( &obj, CMD_COMDAT )
            AttachData( &obj, [esi].seg_info.CodeBuffer, size )
            .if ( [esi].seg_info.start_loc > 0xffff )
                mov obj.is_32,1
            .endif
            mov obj.d.comdat.flags,0
            ;; low 4-bits is allocation type
            .if ( [esi].seg_info.segtype == SEGTYPE_CODE )
                .if ( ModuleInfo._model == MODEL_FLAT )
                    mov obj.d.comdat.attributes,COMDAT_CODE32
                .else
                    mov obj.d.comdat.attributes,COMDAT_FAR_CODE
                .endif
            .else
                .if ( ModuleInfo._model == MODEL_FLAT )
                    mov obj.d.comdat.attributes,COMDAT_DATA32
                .else
                    mov obj.d.comdat.attributes,COMDAT_FAR_DATA
                .endif
            .endif
            get_omfalign( [esi].seg_info.alignment )
            mov obj.d.comdat._align,al
            mov obj.d.comdat.offs,[esi].seg_info.start_loc
            mov obj.d.comdat.type_idx,0
            mov obj.d.comdat.public_lname_idx,[esi].seg_info.comdat_idx
            ;; todo: error if comdat_idx is 0
        .else
            omf_InitRec( &obj, CMD_LEDATA )
            AttachData( &obj, [esi].seg_info.CodeBuffer, size )
            mov obj.d.ledata.idx,[esi].seg_info.seg_idx
            mov obj.d.ledata.offs,[esi].seg_info.start_loc
            .if( obj.d.ledata.offs > 0xffff )
                mov obj.is_32,1
            .endif
        .endif
        omf_write_record( &obj )

        ;; process Fixup, if any
        .if ( [esi].seg_info.head != NULL )
            omf_write_fixupp( s, 0 )
            omf_write_fixupp( s, 1 )
            mov [esi].seg_info.head,NULL
            mov [esi].seg_info.tail,NULL
        .endif
    .endif
    mov [esi].seg_info.start_loc,[esi].seg_info.current_loc
    ret
omf_write_ledata endp

endif

; flush current segment.
; write_to_file is always TRUE here

omf_FlushCurrSeg proc
ifndef __ASMC64__
    omf_write_ledata( CurrSeg )
    ;; add line numbers if debugging info is desired
    .if ( Options.line_numbers )
        omf_write_linnum( ln_is32 )
        mov ln_size,0
    .endif
endif
    ret
omf_FlushCurrSeg endp

ifndef __ASMC64__

; Write a THEADR record.

omf_write_theadr proc private name:string_t

  local obj:omf_rec
  local len:dword

    omf_InitRec( &obj, CMD_THEADR )

    ; v2.08: use the name given at the cmdline, that's what Masm does.
    ; Masm emits either a relative or a full path, depending on what
    ; was given as filename!

    mov len,strlen( name )
    lea ecx,[eax+1]
    AttachData( &obj, StringBufferEnd, ecx )
    PutName( &obj, name, len )
    omf_write_record( &obj )
    ret

omf_write_theadr endp

endif

; v2.11: check if
; - source file is changing
; - offset magnitude is changing
; - size of line number info exceeds 1024
; if at least one of these conditions are met AND there are linnum items
; in the queue, then flush the current LEDATA buffer.
; If source file changed, write a THEADR record for the new source file.
; ( Masm also emits THEADR records, but more frequently -
; it doesn't care if linnum items are written or have been written. )
;
; This function is called by AddLinnumDataRef(), that is, whenever a linnum
; info is about to be written.


omf_check_flush proc uses esi edi ebx curr:ptr line_num_info

ifndef __ASMC64__

  local is_32:byte
  local size:word

    mov esi,curr

if MULTIHDR

    .if ( [esi].line_num_info.srcfile != ln_srcfile )

        .if ( LinnumQueue.head )
            omf_FlushCurrSeg()
        .endif

        ; todo: for Borland, there's a COMENT ( CMT_SRCFILE ) that could be written
        ; instead of THEADR.

        omf_write_theadr( GetFName( [esi].line_num_info.srcfile ) )
        mov ln_srcfile,[esi].line_num_info.srcfile

        .return
    .endif

endif

    ; if there's a change in offset magnitude ( 16 -> 32 or 32 -> 16 ),
    ; do flush ( Masm compatible ).

    mov eax,FALSE
    .if ( [esi].line_num_info.offs > 0xffff )
        mov eax,TRUE
    .endif
    mov is_32,al
    .if ( ln_is32 != al )
        .if ( LinnumQueue.head )
            omf_FlushCurrSeg()
        .endif
        mov ln_is32,is_32
        .return
    .endif

    ; line number item consists of 16-bit line# and 16- or 32-bit offset

    mov eax,sizeof( uint_16 )
    .if ( is_32 )
        add eax,sizeof( uint_32 )
    .else
        add eax,sizeof( uint_16 )
    .endif
    mov size,ax

    ; if the size of the linnum data exceeds 1016,
    ; do flush ( Masm compatible ).

    add ax,ln_size
    .if ( ax > 1024 - 8 )
        .if ( LinnumQueue.head )
            omf_FlushCurrSeg()
        .endif
    .endif
    add ln_size,size
endif
    ret

omf_check_flush endp

;------------------------------------------------------

; write end of pass 1 record.

ifndef __ASMC64__
omf_end_of_pass1 proc private

  local obj:omf_rec

    omf_InitRec( &obj, CMD_COMENT )
    mov obj.d.coment.attr,0x00
    mov obj.d.coment.cmt_class,CMT_MS_END_PASS_1
    AttachData( &obj, "\x01", 1 )
    omf_write_record( &obj )
    ret
omf_end_of_pass1 endp
endif

;; called when a new path is started
;; the OMF "path 2" records (LEDATA, FIXUP, LINNUM ) are written in all passes.

omf_set_filepos proc

ifndef __ASMC64__
    fseek( CurrFile[OBJ*4], end_of_header, SEEK_SET )
endif
    ret
omf_set_filepos endp

ifndef __ASMC64__
omf_write_dosseg proc private

  local obj:omf_rec

    omf_InitRec( &obj, CMD_COMENT )
    mov obj.d.coment.attr,CMT_TNP
    mov obj.d.coment.cmt_class,CMT_DOSSEG
    AttachData( &obj, "", 0 )
    omf_write_record( &obj )
    ret
omf_write_dosseg endp

omf_write_lib proc private uses esi edi ebx

  local obj:omf_rec

    .for ( esi = ModuleInfo.LibQueue.head: esi: esi = edi )
        mov edi,[esi].qitem.next
        lea ebx,[esi].qitem.value
        omf_InitRec( &obj, CMD_COMENT )
        mov obj.d.coment.attr,CMT_TNP
        mov obj.d.coment.cmt_class,CMT_DEFAULT_LIBRARY
        AttachData( &obj, ebx, strlen( ebx ) )
        omf_write_record( &obj )
    .endf
    ret
omf_write_lib endp

omf_write_export proc private uses esi edi ebx

  local parmcnt:byte
  local obj:omf_rec
  local len:int_t

    .for ( esi = ProcTable: esi != NULL: esi = [esi].dsym.nextproc )

        mov ebx,[esi].dsym.procinfo
        .if ( [ebx].proc_info.flags & PROC_ISEXPORT )

            omf_InitRec( &obj, CMD_COMENT )
            mov obj.d.coment.attr,0x00
            mov obj.d.coment.cmt_class,CMT_OMF_EXT
            mov edi,StringBufferEnd

            ; structure of EXPDEF "comment":
            ; type         db CMT_EXT_EXPDEF (=02)
            ; exported_flag db ?
            ; ex_name_len   db ?
            ; exported_name db ex_name_len dup (?)
            ; int_name_len  db 0     ;always 0
            ; internal_name db int_name_len dup (?)
            ; ordinal       dw ?     ;optional

            .if ( Options.no_export_decoration == FALSE )
                mov len,Mangle( esi, &[edi+3] )
            .else
                strcpy( &[edi+3], [esi].asym.name )
                mov len,[esi].asym.name_size
            .endif
            ; v2.11: case mapping was missing
            .if ( ModuleInfo.convert_uppercase )
                _strupr( &[edi+3] )
            .endif
if MAX_ID_LEN gt 255
            .if ( len > 255 )
                mov len,255 ;; restrict name to 255 chars
            .endif
endif
            mov ecx,len
            add ecx,4
            AttachData( &obj, edi, ecx )
            Put8( &obj, CMT_EXT_EXPDEF )

            ; write the "Exported Flag" byte:
            ; bits 0-4: parameter count
            ; bit 5: no data (entry doesn't use initialized data )
            ; bit 6: resident (name should be kept resident)
            ; bit 7: ordinal ( if 1, 2 byte index must follow name)

            .for ( edx = [ebx].proc_info.paralist, ecx = 0: edx: edx = [edx].dsym.nextparam, ecx++ )
            .endf
            and ecx,0x1F       ; ensure bits 5-7 are still 0
            Put8( &obj, cl )   ; v2.01: changed from fix 0x00
            Put8( &obj, byte ptr len )
            add obj.curoff,len
            Put8( &obj, 0 )
            omf_write_record( &obj )
        .endif
    .endf
    ret
omf_write_export endp

; write OMF GRPDEF records

omf_write_grpdef proc private uses esi edi ebx

    local curr:ptr dsym
    local segminfo:ptr dsym
    local s:ptr seg_item
    local grp:omf_rec

    ; size of group records may exceed 1024!

    .for ( esi = SymTables[TAB_GRP*symbol_queue].head: esi: esi = [esi].dsym.next )

        omf_InitRec( &grp, CMD_GRPDEF )

        mov edi,[esi].dsym.grpinfo
        mov grp.d.grpdef.idx,[edi].grp_info.grp_idx

        ; we might need:
        ; - 1 or 2 bytes for the group name index
        ; - 2 or 3 bytes for each segment in the group

        imul ecx,[edi].grp_info.numseg,3
        add ecx,2
        AttachData( &grp, StringBufferEnd, ecx )

        ; v2.01: the LName index of the group may be > 0xff
        ; v2.03: use the group index directly

        PutIndex( &grp, [edi].grp_info.lname_idx )

        .for ( edi = [edi].grp_info.seglist: edi: edi = [edi].seg_item.next )

            Put8( &grp, GRP_SEGIDX )
            mov ecx,[edi].seg_item.iseg
            mov ecx,[ecx].dsym.seginfo
            PutIndex( &grp, [ecx].seg_info.seg_idx )

            ; truncate the group record if it comes near output buffer limit!

            .if ( grp.curoff > OBJ_BUFFER_SIZE - 10 )

                asmerr( 8018, [esi].asym.name )
                .break
            .endif
        .endf
        TruncRec( &grp )
        omf_write_record( &grp )
    .endf
    ret
omf_write_grpdef endp

get_omfalign proc private alignment:byte

    .switch ( alignment )
    .case 1: .return( SEGDEF_ALIGN_WORD )
    .case 2: .return( SEGDEF_ALIGN_DWORD )
    .case 4: .return( SEGDEF_ALIGN_PARA )
    .case 8: .return( SEGDEF_ALIGN_PAGE )
    .case MAX_SEGALIGNMENT: .return( SEGDEF_ALIGN_ABS )
    .endsw

    ; value 0 is byte alignment, anything elso is "unexpected"

    .return( SEGDEF_ALIGN_BYTE )

get_omfalign endp

; write segment table.
; This is done after pass 1.
; There might exist entries of undefined segments in
; the segment list!

omf_write_segdef proc private uses esi edi ebx

  local curr:ptr dsym
  local obj:omf_rec

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head: esi: esi = [esi].dsym.next )

        mov edi,[esi].dsym.seginfo
        .continue .if ( [edi].seg_info.comdatselection )

        omf_InitRec( &obj, CMD_SEGDEF )

        .if ( [edi].seg_info.Ofssize > USE16 )
            .if ( [edi].seg_info.force32 || ( [esi].asym.max_offset >= 0x10000 ) )
                mov obj.is_32,1
            .else
                mov obj.is_32,0
            .endif
        .else
            mov obj.is_32,0
        .endif

        mov obj.d.segdef.idx,[edi].seg_info.seg_idx
        xor eax,eax
        .if ( [edi].seg_info.Ofssize > USE16 )
            inc eax
        .endif
        mov obj.d.segdef.use_32,al
        get_omfalign( [edi].seg_info.alignment )
        mov obj.d.segdef._align,al
        mov obj.d.segdef.combine,[edi].seg_info.combine
        mov obj.d.segdef.abs.frame,[edi].seg_info.abs_frame
        mov obj.d.segdef.abs.offs,[edi].seg_info.abs_offset
        mov obj.d.segdef.seg_length,[esi].asym.max_offset
        mov obj.d.segdef.seg_lname_idx,[edi].seg_info.lname_idx

        mov eax,1
        mov ecx,[edi].seg_info.clsym
        .if ( ecx )
            mov eax,[ecx].asym.classlnameidx
        .endif
        mov obj.d.segdef.class_lname_idx,ax
        mov obj.d.segdef.ovl_lname_idx,1

        omf_write_record( &obj )

        ; write a comment for the linker.
        ; this is something not done by Masm, it has
        ; been inherited from Wasm.

        .if ( [edi].seg_info.segtype == SEGTYPE_CODE && Options.no_opt_farcall == FALSE )

           .new buffer[4]:byte

            omf_InitRec( &obj, CMD_COMENT )
            mov obj.d.coment.attr,CMT_TNP
            mov obj.d.coment.cmt_class,CMT_LINKER_DIRECTIVE
            AttachData( &obj, &buffer, 3 )
            Put8( &obj, LDIR_OPT_FAR_CALLS )
            PutIndex( &obj, [edi].seg_info.seg_idx )

            ; v2.04: added. cut off the 3. byte if not needed

            TruncRec( &obj )
            omf_write_record( &obj )
        .endif
    .endf
    ret

omf_write_segdef endp

; the lnames are stored in a queue. read
; the items one by one and take care that
; the record size doesn't exceed 1024 bytes.

omf_write_lnames proc private uses esi edi ebx

  local size:int_t
  local items:int_t
  local obj:omf_rec
  local buffer[MAX_LNAME_SIZE]:byte

    mov buffer,NULLC ; start with the NULL entry
    lea edi,buffer[1]
    mov items,1
    mov startitem,1

    .for ( esi = ModuleInfo.LnameQueue.head : : esi = [esi].qnode.next )

        xor ebx,ebx
        xor ecx,ecx
        .if ( esi )
            mov ebx,[esi].qnode.elmt
            mov ecx,[ebx].asym.name_size
        .endif

        lea eax,buffer
        mov edx,edi
        sub edx,eax
        mov size,edx
        lea ecx,[ecx+edx+4]

        .if ( ebx == NULL || ( ecx > MAX_LNAME_SIZE ) )

            .if ( edx )

                omf_InitRec( &obj, CMD_LNAMES )

                ; first_idx and num_names are NOT
                ; written to the LNAMES record!
                ; In fact, they aren't used at all.

                mov obj.d.lnames.first_idx,startitem
                mov obj.d.lnames.num_names,items
                AttachData( &obj, &buffer, size )
                omf_write_record( &obj )
                mov startitem,items
            .endif
            .break .if ( ebx == NULL )
            lea edi,buffer
        .endif

        mov eax,[ebx].asym.name_size
        stosb

        ; copy 1 byte more - the NULLC - for _strupr()
        inc eax
        memcpy( edi, [ebx].asym.name, eax )

        ; lnames are converted for casemaps ALL and NOTPUBLIC

        .if ( ModuleInfo.case_sensitive == FALSE )
            _strupr( edi )
        .endif

        add edi,[ebx].asym.name_size ; overwrite the null char
        inc items

        ; v2.12: lname_idx fields now set in OMF only

        mov eax,items
        .switch ( [ebx].asym.state )
        .case SYM_SEG
            mov ecx,[ebx].dsym.seginfo
            mov [ecx].seg_info.lname_idx,eax
            .endc
        .case SYM_GRP
            mov ecx,[ebx].dsym.grpinfo
            mov [ecx].grp_info.lname_idx,eax
            .endc
        .default
            mov [ebx].asym.classlnameidx,eax
            .endc
        .endsw
    .endf
    ret

omf_write_lnames endp


.template readext
    p       dsym_t ?
    index   dw ?
    method  db ?
   .ends

; read items for EXTDEF records.
; there are 2 sources:
; - the AltQueue of weak externals
; - the TAB_EXT queue of externals
; v2.09: index (ext_idx1, ext_idx2 ) is now set inside this function.

GetExt proc private r:ptr readext

    mov ecx,r
    .if ( [ecx].readext.method == 0 )

        .for ( : [ecx].readext.p : )

            mov edx,[ecx].readext.p
            mov [ecx].readext.p,[edx].dsym.next
            .continue .if ( [edx].asym.sflags & S_ISCOM )

            mov eax,[edx].asym.altname
            .if ( eax && !( [eax].asym.flag1 & S_INCLUDED ) )

                mov dx,[ecx].readext.index
                inc [ecx].readext.index
                mov [eax].asym.ext_idx2,dx
                or  [eax].asym.flag1,S_INCLUDED
               .return
            .endif
        .endf
        inc [ecx].readext.method
        mov [ecx].readext.p,SymTables[TAB_EXT*symbol_queue].head
    .endif

    .for ( : [ecx].readext.p : )

        mov edx,[ecx].readext.p
        mov [ecx].readext.p,[edx].dsym.next
        .continue .if ( [edx].asym.sflags & ( S_ISCOM or S_WEAK ) )

        mov ax,[ecx].readext.index
        inc [ecx].readext.index
        mov [edx].asym.ext_idx1,ax
       .return( edx )
    .endf
    .return( NULL )

GetExt endp

; write EXTDEF records.
; this is done once, after pass 1.
; v2.09: external index is now set here.


omf_write_extdef proc private uses esi edi ebx

  local obj:omf_rec
  local sym:ptr asym
  local symext:ptr dsym
  local rec_size:dword
  local len:dword
  local r:readext
  local data[MAX_EXT_LENGTH]:char_t
  local buffer[MAX_ID_LEN + MANGLE_BYTES + 1]:byte

    mov r.p,SymTables[TAB_EXT*symbol_queue].head
    mov r.index,1
    mov r.method,0
    mov obj.d.extdef.first_idx,0

    ; scan the EXTERN/EXTERNDEF items

    mov sym,GetExt( &r )

    .while ( sym )

        .for ( rec_size = 0, obj.d.extdef.num_names = 0: sym: sym = GetExt( &r ) )

            mov len,Mangle( sym, &buffer )

if MAX_ID_LEN gt 255
            .if ( len > 255 )
                mov len,255 ; length is 1 byte only
            .endif
endif
            .if ( ModuleInfo.convert_uppercase )
                _strupr( &buffer )
            .endif

            mov eax,rec_size
            add eax,len
            add eax,2

            .break .if ( eax >= MAX_EXT_LENGTH )

            inc obj.d.extdef.num_names

            mov ecx,rec_size
            mov eax,len
            mov data[ecx],al
            inc rec_size
            lea edx,data[ecx+1]

            memcpy( edx, &buffer, len )
            add rec_size,len
            mov ecx,rec_size
            mov data[ecx],0 ; for the type index
            inc rec_size
        .endf

        .if ( rec_size )

            omf_InitRec( &obj, CMD_EXTDEF )
            AttachData( &obj, &data, rec_size )
            omf_write_record( &obj )
            add obj.d.extdef.first_idx,obj.d.extdef.num_names
        .endif
    .endw

    ; v2.04: write WKEXT coment records.
    ; those items are defined via "EXTERN (altname)" syntax.
    ; After the records have been written, the indices in
    ; altname are no longer needed.

    .for ( esi = SymTables[TAB_EXT*symbol_queue].head: esi: esi = [esi].dsym.next )

        .if ( !( [esi].asym.sflags & S_ISCOM ) && [esi].asym.altname )

            omf_InitRec( &obj, CMD_COMENT )
            mov obj.d.coment.attr,CMT_TNP
            mov obj.d.coment.cmt_class,CMT_WKEXT
            AttachData( &obj, &buffer, 4 )
            PutIndex( &obj, [esi].asym.ext_idx1 )
            mov ecx,[esi].asym.altname
            PutIndex( &obj, [ecx].asym.ext_idx2 )
            TruncRec( &obj )
            omf_write_record( &obj )
        .endif
    .endf

    ; v2.05: reset the indices - this must be done only after ALL WKEXT
    ; records have been written!

    .for ( esi = SymTables[TAB_EXT*symbol_queue].head: esi: esi = [esi].dsym.next )

        ; v2.09: don't touch the index if the alternate name is an external
        ; - else an invalid object file will be created!

        mov ecx,[esi].asym.altname
        .if ( !( [esi].asym.sflags & S_ISCOM ) && ecx && [ecx].asym.state != SYM_EXTERNAL )
            mov [ecx].asym.ext_idx,0
        .endif
    .endf
    .return( r.index )

omf_write_extdef endp

define THREE_BYTE_MAX ( ( 1 shl 24 ) - 1 )

get_size_of_comdef_number proc private value:dword

    ; The spec allows up to 128 in a one byte size field, but lots
    ; of software has problems with that, so we'll restrict ourselves
    ; to 127.

    mov eax,value
    .if ( eax < 128 )
        .return( 1 )   ;; 1 byte value
    .elseif ( eax <= USHRT_MAX )
        .return( 3 )   ;; 1 byte flag + 2 byte value
    .elseif ( eax <= THREE_BYTE_MAX )
        .return( 4 )   ;; 1 byte flag + 3 byte value
    .else  ;; if ( value <= ULONG_MAX )
        .return( 5 )   ;; 1 byte flag + 4 byte value
    .endif
    ret

get_size_of_comdef_number endp

; for COMDEF: write item size (or number of items)

put_comdef_number proc private uses esi edi ebx buffer:ptr byte, value:dword

    mov edi,buffer
    mov esi,value
    mov ebx,get_size_of_comdef_number( esi )

    .switch( ebx )
    .case 1
        mov eax,esi
        mov [edi],al
        .endc
    .case 3
        mov al,COMDEF_LEAF_2 ; 0x81
        stosb
        .endc
    .case 4
        mov al,COMDEF_LEAF_3 ; 0x84
        stosb
        .endc
    .case 5
        mov al,COMDEF_LEAF_4 ; 0x88
        stosb
        .endc
    .endsw

    .new umax:uint_t = ( UCHAR_MAX + 1 )
    .for ( ecx = 1: ecx < ebx: ecx++ )

        mov eax,esi
        cdq
        div umax
        mov al,dl
        stosb
        shr esi,8
    .endf
    .return( ebx )

put_comdef_number endp

; write OMF COMDEF records.
; this is done once, after pass 1.
; v2.09: external index is now set inside this function.
; important: the size of the communal variables must be known.
; If the size is the difference of two code labels, it might
; change in subsequent passes. Both Masm and JWasm won't adjust
; the size then!


omf_write_comdef proc private uses esi edi ebx index:word

  local obj:omf_rec
  local curr:ptr dsym
  local num:dword
  local recsize:dword
  local numsize:dword
  local symsize:dword
  local varsize:uint_32
  local start:dword ; record's start index (not used)
  local buffer[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t
  local data[MAX_EXT_LENGTH]:char_t
  local number[16]:char_t

    mov start,0
    mov esi,SymTables[TAB_EXT*symbol_queue].head
    .while ( esi )
        .for( num = 0, recsize = 0: esi : esi = [esi].dsym.next )
            .continue .if ( !( [esi].asym.sflags & S_ISCOM ) )

            mov symsize,Mangle( esi, &buffer )
if MAX_ID_LEN gt 255
            .if ( symsize > 255 )
                mov symsize,255; ;; length is 1 byte only
            .endif
endif
            ; v2.11: case mapping was missing

            .if ( ModuleInfo.convert_uppercase )
                _strupr( &buffer )
            .endif

            mov varsize,SizeFromMemtype( [esi].asym.mem_type, ModuleInfo.Ofssize, [esi].asym.type )

            mov [esi].asym.ext_idx,index ; v2.09: set external index here
            inc index

            .if ( varsize == 0 )

                mov eax,[esi].asym.total_size
                cdq
                div [esi].asym.total_length
                mov varsize,eax
            .endif

            mov numsize,1

            .if ( [esi].asym.is_far )

                mov number[0],COMDEF_FAR ; 0x61
                add numsize,put_comdef_number( &number[1], [esi].asym.total_length )
                mov ecx,numsize
                add numsize,put_comdef_number( &number[ecx], varsize )
            .else
                mov number[0],COMDEF_NEAR ; 0x62
                mov eax,[esi].asym.total_length
                mul varsize
                add numsize,put_comdef_number( &number[1], eax )
            .endif

            ; make sure the record's size doesn't exceed 1024.
            ; 2 = 1 (name len) + 1 (type index)

            mov eax,recsize
            add eax,symsize
            add eax,numsize
            add eax,2
            .break .if ( eax > MAX_EXT_LENGTH )

            ; copy name ( including size prefix ), type, number

            lea edi,data
            mov ecx,recsize
            inc recsize
            mov eax,symsize
            mov [edi+ecx],al
            lea ecx,[edi+ecx+1]

            memcpy( ecx, &buffer, symsize )
            add recsize,symsize
            mov ecx,recsize
            inc recsize
            mov byte ptr [edi+ecx],0 ; for the type index
            lea ecx,[edi+ecx+1]
            memcpy( ecx, &number, numsize )
            add recsize,numsize
            inc num
        .endf

        .if ( num > 0 )
            omf_InitRec( &obj, CMD_COMDEF )
            mov obj.d.comdef.first_idx,start ; unused
            AttachData( &obj, &data, recsize )
            mov obj.d.comdef.num_names,num ; unused
            omf_write_record( &obj )
            add start,num
        .endif
    .endw
    .return( index )

omf_write_comdef endp

GetFileTimeStamp proc private filename:string_t

  local statbuf:stat

    .if ( _stat( filename, &statbuf ) != 0 )
        .return( 0 )
    .endif
    .return( statbuf.st_mtime )

GetFileTimeStamp endp

; write COMENT dependency records (CMT_DEPENDENCY) for debugging
; if line numbers are on; this is a Borland/OW thing.

omf_write_autodep proc private uses esi edi ebx

  local obj:omf_rec
  local len:dword

    mov ebx,StringBufferEnd
    .for ( esi = 0: esi < ModuleInfo.cnt_fnames: esi++ )

        omf_InitRec( &obj, CMD_COMENT )

        mov obj.d.coment.attr,CMT_TNP
        mov obj.d.coment.cmt_class,CMT_DEPENDENCY; ;; 0xE9
        mov edx,ModuleInfo.FNames
        mov edi,[edx+esi*4]
        strlen( edi )

if MAX_STRING_LEN gt 255
        .if ( eax > 255 )
            mov eax,255 ; length is 1 byte only
        .endif
endif
        mov len,eax
        timet2dostime( GetFileTimeStamp( edi ) )
        mov [ebx],eax
        mov eax,len
        mov [ebx+4],al
        lea ecx,[ebx+5]
        memcpy( ecx, edi, len )
        mov eax,len
        lea ecx,[eax+5]
        AttachData( &obj, ebx, ecx )
        omf_write_record( &obj )
    .endf
    omf_InitRec( &obj, CMD_COMENT )
    mov obj.d.coment.attr,CMT_TNP
    mov obj.d.coment.cmt_class,CMT_DEPENDENCY
    AttachData( &obj, "", 0 )
    omf_write_record( &obj )
   .return( NOT_ERROR )

omf_write_autodep endp

omf_write_alias proc private uses esi edi ebx

  local obj:omf_rec
  local p:string_t
  local len1:dword
  local len2:dword
  local curr:ptr dsym
  local tmp[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t
  local buff[2*MAX_ID_LEN_OMF + 2]:byte

    .for ( ebx = SymTables[TAB_ALIAS*symbol_queue].head: ebx: ebx = [ebx].dsym.next )

        ; output an alias record for this alias

        lea esi,tmp
        Mangle( ebx, esi )

if MAX_ID_LEN gt MAX_ID_LEN_OMF
        .if ( eax > MAX_ID_LEN_OMF )
            mov eax,MAX_ID_LEN_OMF
        .endif
endif
        mov len1,eax
        lea edi,buff
        stosb
        mov ecx,eax
        mov edx,esi
        rep movsb
        mov esi,edx

        Mangle( [ebx].asym.substitute, esi )
if MAX_ID_LEN gt MAX_ID_LEN_OMF
        .if ( eax > MAX_ID_LEN_OMF )
            mov eax,MAX_ID_LEN_OMF
        .endif
endif
        mov len2,eax
        stosb
        mov ecx,eax
        rep movsb

        omf_InitRec( &obj, CMD_ALIAS )

        mov ecx,len1
        add ecx,len2
        add ecx,2
        AttachData( &obj, &buff, ecx)
        omf_write_record( &obj )
    .endf
    ret

omf_write_alias endp

; the PUBDEF record consists of:
; - base_info ( segment, group, frame ), max size is 4
; - items
;   - 1 byte name len
;   - name[]
;   - offset ( 2/4 bytes )
;   - type ( index field, here always 0 )

omf_write_pubdef proc private uses esi edi ebx

    ; v2.07: pubdef_data has been modified to match
    ; the data to be written to the object module more closely.
    ; This fixed a possible overrun if too many publics were written.
    ; v2.11: now the data matches exactly the OMF PUBDEF record
    ; and is just attached.

    mov esi,ModuleInfo.PubQueue.head

    .while ( esi )

        .new curr_seg:ptr asym
        .new data:ptr byte
        .new size:dword
        .new curr32:uint_8
        .new is32:uint_8

        .for ( size = 0, data = StringBufferEnd: esi: esi = [esi].qnode.next )

            .new recsize:dword
            .new len:dword
            .new sym:ptr asym

            mov sym,[esi].qnode.sym

            ; COMDAT symbol? Then write an LNAME record

            mov ecx,[eax].asym.segm
            .if ( ecx )
                mov edx,[ecx].dsym.seginfo
            .endif
            .if ( ecx && [edx].seg_info.comdatselection )

                .if ( [edx].seg_info.comdat_idx == 0 )

                    .new obj:omf_rec

                    and [ecx].asym.flags,not S_USED
                    .if ( [eax].asym.flags & S_USED )
                        or [ecx].asym.flags,S_USED
                    .endif
                    mov [edx].seg_info.comdat_idx,startitem
                    inc startitem

                    omf_InitRec( &obj, CMD_LNAMES )

                    mov edi,StringBufferEnd
                    inc edi
                    mov len,Mangle( sym, edi )
                    mov [edi-1],al
                    .if ( ModuleInfo.case_sensitive == FALSE )
                        _strupr( edi )
                    .endif
                    mov ecx,len
                    inc ecx
                    AttachData( &obj, StringBufferEnd, ecx )
                    omf_write_record( &obj )
                ;.elseif ( Parse_Pass == PASS_1 )
                    ; ???
                .endif
                .continue
            .endif

            ; for constants, Masm checks if the value will fit in a 16-bit field,
            ; either signed ( -32768 ... 32767 ) or unsigned ( 0 ... 65635 ).
            ; As a result, the following code:
            ; E1 equ 32768
            ; E2 equ -32768
            ; PUBLIC E1, E2
            ; will store both equates with value 8000h in the 16-bit PUBDEF record!!!
            ; JWasm behaves differently, resulting in negative values to be stored as 32-bit.

            xor eax,eax
            mov ebx,sym
            cmp [ebx].asym.offs,0xffff
            seta al
            mov is32,al

            ; check if public fits in current record yet.
            ; 4 bytes omf record overhead, 4 for base info, 1+1+4/2 for name_size, type & offset

            mov ecx,2
            .if ( eax )
                mov ecx,4
            .endif
            mov eax,[ebx].asym.name_size
            add eax,size
            lea eax,[eax+ecx+MANGLE_BYTES+4+4+1+1]
            mov recsize,eax

            ; exit loop if segment or offset magnitude changes, or record becomes too big

            .break .if ( size && ( [ebx].asym.segm != curr_seg || is32 != curr32 || recsize > MAX_PUB_LENGTH ) )

            mov edi,data
            inc edi
            Mangle( ebx, edi )
if MAX_ID_LEN gt MAX_ID_LEN_OMF
            .if ( eax > 255 )
                mov eax,255 ; length is 1 byte only
            .endif
endif
            mov len,eax
            .if ( ModuleInfo.convert_uppercase )
                _strupr( edi )
            .endif
            mov curr_seg,[ebx].asym.segm
            mov curr32,is32
            mov eax,len
            mov [edi-1],al
            add edi,eax
            mov eax,[ebx].asym.offs
            .if ( curr32 )
                stosd
            .else
                stosw
            .endif
            xor eax,eax ; type field
            stosb
            mov data,edi
            sub edi,StringBufferEnd
            mov size,edi
        .endf

        .if ( size )

           .new obj:omf_rec
            omf_InitRec( &obj, CMD_PUBDEF )

            AttachData( &obj, StringBufferEnd, size )
            mov obj.is_32,curr32
            .if ( curr_seg == NULL )  ;; absolute symbol, no segment
                mov obj.d.pubdef.base.grp_idx,0
                mov obj.d.pubdef.base.seg_idx,0
            .else
                GetSegIdx( curr_seg )
                mov obj.d.pubdef.base.seg_idx,ax
                omf_GetGrpIdx( GetGroup( curr_seg ) )
                mov obj.d.pubdef.base.grp_idx,ax
            .endif
            mov obj.d.pubdef.base.frame,0
            omf_write_record( &obj )
        .endif
    .endw

    .return( NOT_ERROR )

omf_write_pubdef endp

omf_write_modend proc private fixp:ptr fixup, displ:uint_32

    local obj:omf_rec
    local buffer[FIX_GEN_MODEND_MAX]:uint_8

    omf_InitRec( &obj, CMD_MODEND )

    mov ecx,fixp
    .if ( ecx == NULL )
        mov obj.d.modend.main_module,FALSE
        mov obj.d.modend.start_addrs,FALSE
    .else
        mov obj.d.modend.start_addrs,TRUE
        mov obj.d.modend.main_module,TRUE
        .if ( GetSymOfssize( [ecx].fixup.sym ) > USE16 )
            mov eax,1 ; USE16 or USE32
        .else
            mov eax,eax
        .endif
        mov obj.is_32,al
        AttachData( &obj, &buffer, 0 )

        mov ecx,FIX_GEN_INTEL
        .if ( obj.is_32 )
            mov ecx,FIX_GEN_MS386
        .endif
        mov obj.length,OmfFixGenFixModend( fixp, &buffer, displ, ecx )
    .endif
    omf_write_record( &obj )
    ret

omf_write_modend endp

; this callback function is called during codeview debug info generation

omf_cv_flushfunc proc private uses esi edi ebx s:ptr dsym, curr:ptr uint_8, size:dword, pv:ptr

    mov edx,s
    mov ecx,[edx].dsym.seginfo
    mov edi,[ecx].seg_info.CodeBuffer

    mov ebx,curr
    sub ebx,edi
    mov eax,ebx
    add eax,size

    .if ( ebx && eax > ( 1024 - 8 ) )
        mov eax,[ecx].seg_info.start_loc
        add eax,ebx
        mov [ecx].seg_info.current_loc,eax
        omf_write_ledata( edx )
        .return( edi )
    .endif
    .return( curr )

omf_cv_flushfunc endp

; If -Zi is set, a comment class
; A1 record (MS extensions present) is written.
;
; Additionally, segments $$SYMBOLS, $$TYPES are added to the segment table

omf_write_header_dbgcv proc private uses ebx

  local obj:omf_rec

    omf_InitRec( &obj, CMD_COMENT )
    mov obj.d.coment.attr,0x00
    mov obj.d.coment.cmt_class,CMT_MS_OMF ; MS extensions present

    AttachData( &obj, "\001CV", 3 )

    omf_write_record( &obj )

    .for ( ebx = 0: ebx < DBGS_MAX: ebx++ )

        CreateIntSegment( SymDebParm[ebx*8].name, SymDebParm[ebx*8].cname, 0, USE32, TRUE )
        mov SymDebSeg[ebx*4],eax

        .if ( eax )

            ; without this a 32-bit segdef is emitted only if segsize > 64kB

            mov ecx,[eax].dsym.seginfo
            mov [ecx].seg_info.force32,TRUE
            mov [ecx].seg_info.flushfunc,omf_cv_flushfunc
        .endif
    .endf
    ret

omf_write_header_dbgcv endp

; write contents of segments $$SYMBOLS and $$TYPES

omf_write_debug_tables proc private uses esi edi ebx

    .if ( SymDebSeg[DBGS_SYMBOLS*4] && SymDebSeg[DBGS_TYPES*4] )

        mov eax,SymDebSeg[DBGS_SYMBOLS*4]
        mov ecx,[eax].dsym.seginfo
        mov [ecx].seg_info.CodeBuffer,CurrSource

        mov edx,SymDebSeg[DBGS_TYPES*4]
        mov ecx,[edx].dsym.seginfo
        add eax,1024
        mov [ecx].seg_info.CodeBuffer,eax

        cv_write_debug_tables( SymDebSeg[DBGS_SYMBOLS*4], SymDebSeg[DBGS_TYPES*4], NULL )
    .endif
    ret

omf_write_debug_tables endp

; write OMF module.
; this is called after the last pass.
; since the OMF records are written "on the fly",
; the "normal" section contents are already written at this time.

omf_write_module proc private modinfo:ptr module_info

if TRUNCATE
  local fh:int_t
  local size:uint_32
endif

    ; -if Zi is set, write symbols and types

    .if ( Options.debug_symbols )
        omf_write_debug_tables()
    .endif
    mov ecx,modinfo
    omf_write_modend( [ecx].module_info.start_fixup, [ecx].module_info.start_displ )

if TRUNCATE

    ; under some very rare conditions, the object
    ; module might become shorter! Hence the file
    ; must be truncated now. The problem is that there
    ; is no stream function for this task.
    ; the final solution will be to save the segment contents
    ; in buffers and write the object module once everything
    ; is done ( as it is done for the other formats already).
    ; v2.03: most likely no longer necessary, since the file
    ; won't become shorter anymore.

    mov size,ftell( CurrFile[OBJ*4] )

ifdef __UNIX__
    mov fh,fileno( CurrFile[OBJ*4] )
    .if ( ftruncate( fh, size ) )
        ;; gcc warns if return value of ftruncate() is "ignored"
    .endif
else
    mov fh,_fileno( CurrFile[OBJ*4] )
    _chsize( fh, size )
endif
endif

    ; write SEGDEF records. Since these reco rds contain the segment's length,
    ; the records have to be written again after the final assembly pass.

    fseek( CurrFile[OBJ*4] , seg_pos, SEEK_SET )
    omf_write_segdef()

    ; write PUBDEF records. Since the final value of offsets isn't known after
    ; the first pass, this has to be called again after the final pass.

    fseek( CurrFile[OBJ*4], public_pos, SEEK_SET)
    omf_write_pubdef()
   .return( NOT_ERROR )

omf_write_module endp

; write OMF header info after pass 1

omf_write_header_initial proc private modinfo:ptr module_info

  local ext_idx:uint_16

    .return( NOT_ERROR ) .if ( write_to_file == FALSE )


    omf_write_theadr( CurrFName[ASM*4] ) ; write THEADR record, main src filename

    ; v2.11: coment record "ms extensions present" now written here

    .if ( Options.debug_symbols ) ; -Zi option set?
        omf_write_header_dbgcv()
    .endif

    ; if( Options.no_dependencies == FALSE )

    .if ( Options.line_numbers )
        omf_write_autodep() ; write dependency COMENT records ( known by Borland & OW )
    .endif
    .if ( ModuleInfo.segorder == SEGORDER_DOSSEG )
        omf_write_dosseg() ; write dosseg COMENT records
    .elseif ( ModuleInfo.segorder == SEGORDER_ALPHA )
        SortSegments( 1 )
    .endif
    omf_write_lib()    ; write default lib COMENT records
    omf_write_lnames() ; write LNAMES records

    ; write SEGDEF records. Since these records contain the segment's length,
    ; the records have to be written again after the final assembly pass.
    ; hence the start position of those records has to be saved.

    mov seg_pos,ftell( CurrFile[OBJ*4] )
    omf_write_segdef()
    omf_write_grpdef() ; write GRPDEF records
    mov ext_idx,omf_write_extdef() ; write EXTDEF records
    mov startext,omf_write_comdef( ext_idx ) ; write COMDEF records
    omf_write_alias() ; write ALIAS records

    ; write PUBDEF records. Since the final value of offsets isn't known after
    ; the first pass, this has to be called again after the final pass.

    mov public_pos,ftell( CurrFile[OBJ*4] )
    omf_write_pubdef()
    omf_write_export() ; write export COMENT records

    ; (optionally) write end-of-pass-one COMENT record
    ; v2.10: don't write record if starting address is present.
    ; the TIS OMF spec v1.1. warns that this
    ; comment record is NOT to be present if
    ; the MODEND record contains a starting address!

    .if ( !ModuleInfo.start_fixup )
        omf_end_of_pass1()
    .endif
    mov end_of_header,ftell( CurrFile[OBJ*4] )
    .return( NOT_ERROR )
omf_write_header_initial endp
endif

; init. called once per module

omf_init proc modinfo:ptr module_info

ifndef __ASMC64__
    mov ecx,modinfo
    mov [ecx].module_info.WriteModule,omf_write_module
    mov [ecx].module_info.Pass1Checks,omf_write_header_initial
    mov SymDebSeg[DBGS_SYMBOLS*4],NULL
    mov SymDebSeg[DBGS_TYPES*4],NULL
if MULTIHDR
    mov ln_srcfile,[ecx].module_info.srcfile
endif
    mov ln_size,0
endif
    ret
omf_init endp

    end
