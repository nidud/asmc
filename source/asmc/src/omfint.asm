; OMFINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: OMF low-level output routines.
;

include stddef.inc
include asmc.inc
include omfint.inc
include omfspec.inc

.enum omffiltfuncs {
    OFF_UNEXP,
    OFF_MISC,
    OFF_MISC32,
    OFF_SEGDEF,
    OFF_LEDATA,
    OFF_COMENT,
    OFF_THEADR,
    OFF_MODEND,
    OFF_PUBDEF,
    OFF_LINNUM,
    OFF_COMDAT,
    OFF_LINSYM
    }

; fields cmd, reclen and buffer must be consecutive

.pragma pack( push, 1 )

.template outbuff

    in_buf      dd ? ; number of bytes in buffer
    cmd         db ? ; record cmd
    reclen      dw ? ; record length
    buffer      db OBJ_BUFFER_SIZE dup(?)
   .ends

.pragma pack( pop )

    .data

func_index db \
    OFF_THEADR, 0,          0,          0,         ; 80 THEADR, LHEADR, PEDATA, PIDATA
    OFF_COMENT, OFF_MODEND, OFF_MISC,   0,         ; 88 COMENT, MODEND, EXTDEF, TYPDEF
    OFF_PUBDEF, 0,          OFF_LINNUM, OFF_MISC,  ; 90 PUBDEF, LOCSYM, LINNUM, LNAMES
    OFF_SEGDEF, OFF_MISC,   OFF_MISC32, 0,         ; 98 SEGDEF, GRPDEF, FIXUP,  ???
    OFF_LEDATA, OFF_LEDATA, 0,          0,         ; A0 LEDATA, LIDATA, LIBHED, LIBNAM
    0,          0,          0,          0,         ; A8 LIBLOC, LIBDIC, ???,    ???
    OFF_MISC,   OFF_MISC32, OFF_MISC,   OFF_PUBDEF,; B0 COMDEF, BAKPAT, LEXTDEF,LPUBDEF
    OFF_MISC,   0,          OFF_MISC,   0,         ; B8 LCOMDEF,???,    CEXTDEF,???
    0,          OFF_COMDAT, OFF_LINSYM, OFF_MISC,  ; C0 ???,    COMDAT, LINSYM, ALIAS
    OFF_MISC32, OFF_MISC                           ; C8 NBKPAT, LLNAMES


    .code

    assume rsi:ptr omf_rec, rbx:ptr outbuff

PutByte proto watcall :byte { ; write a byte to the current record
    mov ecx,[rbx].in_buf
    inc [rbx].in_buf
    mov [rbx].buffer[rcx],al
    }

PutWord proto watcall :word { ; write a word to the current record
    mov ecx,[rbx].in_buf
    add [rbx].in_buf,2
    mov word ptr [rbx].buffer[rcx],ax
    }

PutDword proto watcall :dword { ; write a dword to the current record
    mov ecx,[rbx].in_buf
    add [rbx].in_buf,4
    mov dword ptr [rbx].buffer[rcx],eax
    }

PutIndex proc watcall private index:word

    ; write an index - 1|2 byte(s) - to the current record

    mov ecx,[rbx].in_buf
    inc [rbx].in_buf
    .if ( ax > 0x7f )

        or  ah,0x80
        mov [rbx].buffer[rcx],ah
        inc [rbx].in_buf
        inc ecx
    .endif
    mov [rbx].buffer[rcx],al
    ret

PutIndex endp


PutBase proc watcall private uses rdi base:ptr base_info
    ;
    ; write public base field of COMDAT, PUBDEF or LINNUM records
    ;
    mov rdi,base
    PutIndex( [rdi].base_info.grp_idx )
    PutIndex( [rdi].base_info.seg_idx )
    .if ( [rdi].base_info.grp_idx == 0 && [rdi].base_info.seg_idx == 0 )
        PutWord( [rdi].base_info.fram )
    .endif
    ret

PutBase endp


; call a function - bit 0 of command is always 0

omf_write_record proc fastcall uses rsi rdi rbx objr:ptr omf_rec

  local o:outbuff

    mov     o.in_buf,0
    lea     rbx,o
    mov     rsi,rcx
    movzx   ecx,[rsi].command
    sub     ecx,CMD_MIN_CMD
    shr     ecx,1
    lea     rax,func_index
    movzx   eax,byte ptr [rax+rcx]

    .switch eax
    .case OFF_UNEXP
        asmerr( 1901 ) ; Internal Assembler Error
    .case OFF_MISC     ; For 16-bit records which are the same under Intel and MS OMFs
        mov o.cmd,[rsi].command
       .endc
    .case OFF_MISC32   ; For 32-bit records which are the same under Intel and MS OMFs
        mov al,[rsi].command
        or  al,[rsi].is_32
        mov o.cmd,al
       .endc
    .case OFF_SEGDEF
       .new is32:byte
       .new alig:byte
        mov is32,[rsi].is_32
        add al,CMD_SEGDEF
        mov o.cmd,al
        ;
        ; ACBP: bits=AAACCCBP
        ; AAA=alignment
        ; CCC=combination
        ; B=big
        ; P=32bit
        ;
        mov al,[rsi].d.segdef.combine
        shl al,2
        or  al,[rsi].d.segdef.use_32
        mov cl,[rsi].d.segdef._align
        mov alig,cl
        shl cl,5
        or  al,cl
        ;
        ; set BIG bit. should also be done for 32-bit segments
        ; if their size is exactly 4 GB. Currently JWasm won't
        ; support segments with size 4 GB.
        ;
        .if ( is32 == 0 && [rsi].d.segdef.seg_length == 0x10000 )
            or al,0x02
        .endif
        ;
        ; the segdef record is small (16bit: size 6 - 9 ):
        ; - byte acbp
        ; - word (32bit:dword) length
        ; - index seg name
        ; - index class name
        ; - index ovl name
        ; ABS segdefs are 3 bytes longer
        ;
        PutByte( eax )
        .if ( alig == SEGDEF_ALIGN_ABS )
            ;
            ; absolut segment has frame=word and offset=byte
            ; it isn't fixupp physical reference
            ; and doesn't depend on segment size (16/32bit)
            ;
            PutWord( [rsi].d.segdef.abs.fram )
            PutByte( [rsi].d.segdef.abs.offs )
        .endif
        .if ( is32 )
            PutDword( [rsi].d.segdef.seg_length )
        .else
            PutWord( [rsi].d.segdef.seg_length )
        .endif
        PutIndex( [rsi].d.segdef.seg_lname_idx )
        PutIndex( [rsi].d.segdef.class_lname_idx )
        PutIndex( [rsi].d.segdef.ovl_lname_idx )
        jmp write_end

    .case OFF_LEDATA
        ;
        ; Write LEDATA or LIDATA record.
        ; the overhead is:
        ; - 1 byte cmd
        ; - 2 byte len
        ; - 1/2 bytes segment index
        ; - 2/4 bytes starting offset
        ; - 1 byte chksum
        ; so the data size "should" not exceed 1024-10,1014
        ;
        ; For LIDATA, the structure is equal.
        ; The structure of the data block differs, however:
        ; - 2/4: repeat count
        ; - 2: block count
        ; - content
        ;
        mov al,[rsi].command
        add al,[rsi].is_32
        mov o.cmd,al
        PutIndex( [rsi].d.ledata.idx )
        .if ( [rsi].is_32 )
            PutDword( [rsi].d.ledata.offs )
        .else
            PutWord( [rsi].d.ledata.offs )
        .endif
        .endc
    .case OFF_COMENT
        mov o.cmd,CMD_COMENT
        PutByte( [rsi].d.coment.attr )
        PutByte( [rsi].d.coment.cmt_class )
       .endc
    .case OFF_THEADR
        .gotosw(OFF_MISC)
    .case OFF_MODEND
        xor eax,eax
        .if ( [rsi].is_32 && [rsi].d.modend.start_addrs )
            inc eax
        .endif
        add eax,CMD_MODEND
        mov o.cmd,al
        ;
        ; first byte is Module Type:
        ; bit 7: 1=main program module
        ; bit 6: 1=contains start address
        ; bit 5: Segment bit ( according to OMF, this bit should be 1 )
        ; bit 1-4: must be 0
        ; bit 0: start address contains relocatable address
        ; - ( according to OMF, this bit should be 1 )
        ; Masm does set bit 0, but does not set bit 5!
        ;
        xor eax,eax
        .if ( [rsi].d.modend.main_module )
            mov eax,0x80
        .endif
        .if ( [rsi].d.modend.start_addrs )
            or eax,0x41
            PutByte( eax )
            .endc
        .endif
        PutByte( eax )
        jmp write_end
    .case OFF_PUBDEF
        mov al,[rsi].command
        add al,[rsi].is_32
        mov o.cmd,al
        PutBase( &[rsi].d.pubdef.base )
       .endc
    .case OFF_LINNUM
        mov al,CMD_LINNUM
        add al,[rsi].is_32
        mov o.cmd,al
        PutBase( &[rsi].d.linnum.base )
       .endc
    .case OFF_COMDAT
        ;
        ; COMDATs are initialized communal data records.
        ; This isn't used yet for OMF.
        ;
        ; write CMD_COMDAT/CMD_COMD32
        ;
        mov al,[rsi].command
        add al,[rsi].is_32
        mov o.cmd,al
        PutByte( [rsi].d.comdat.flags )
        PutByte( [rsi].d.comdat.attributes )
        PutByte( [rsi].d.comdat._align )
        .if ( [rsi].is_32 )
            PutDword( [rsi].d.comdat.offs )
        .else
            PutWord( [rsi].d.comdat.offs )
        .endif
        PutIndex( [rsi].d.comdat.type_idx )
        mov al,[rsi].d.comdat.attributes
        and eax,COMDAT_ALLOC_MASK
        .if ( eax == COMDAT_EXPLICIT )
            PutBase( &[rsi].d.comdat.base )
        .endif
        PutIndex( [rsi].d.comdat.public_lname_idx )
        ;
        ; record is already in ms omf format
        ;
       .endc
    .case OFF_LINSYM
        ;
        ; LINSYM record types are only used in conjunction with COMDAT.
        ;
        mov al,CMD_LINSYM
        add al,[rsi].is_32
        mov o.cmd,al
        PutByte( [rsi].d.linsym.flags )
        PutIndex( [rsi].d.linsym.public_lname_idx )
       .endc
    .endsw
    ;
    ; write a byte sequence to the current record
    ;
    ; ensure that there is enough free space in the buffer,
    ; and also 1 byte left for the chksum!
    ;
    mov ecx,[rsi].length
    mov eax,OBJ_BUFFER_SIZE - 1
    sub eax,o.in_buf

    .ifs ( ecx <= eax  )

        mov rsi,[rsi].pdata
        lea rdi,o.buffer
        mov eax,o.in_buf
        add rdi,rax
        add o.in_buf,ecx
        rep movsb
    .else
        ; this "shouldn't happen".

        asmerr( 1901 ) ; Internal Assembler Error
    .endif

write_end:
    ;
    ; finish a buffered record.
    ; - calculate checksum
    ; - store checksum behind buffer contents
    ; - writes the contents of the buffer(cmd, length, contents, checksum)
    ;
    mov eax,o.in_buf
    inc eax            ; add 1 for checksum byte
    mov o.reclen,ax
    add al,ah
    add al,o.cmd

    .for ( rdx = &o.buffer,
           ecx = o.in_buf,
           rcx += rdx : rdx < rcx : )
        add al,[rdx]
        inc rdx
    .endf
    neg al
    mov [rdx],al ; store chksum in buffer
    ;
    ; write buffer + 4 extra bytes (1 cmd, 2 length, 1 chksum)
    ;
    mov ebx,o.in_buf
    add ebx,4
    .if ( fwrite( &o.cmd, 1, ebx, CurrFile[OBJ*size_t] ) != rbx )
        WriteError()
    .endif
    ret

omf_write_record endp

    end
