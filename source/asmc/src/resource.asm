; RESOURCE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Simplistic resource compiler for Windows.
;
; This is a work in progress and is not complete.
;
; Change history:
; 2026-11-04 - added resource output (-res)
;
include asmc.inc
include memalloc.inc
include segment.inc
include listing.inc
include parser.inc
include tokenize.inc
include expreval.inc
include lqueue.inc
include fastpass.inc
include resource.inc

define MAXTYPES     16  ; Max RC_ types
define MAXRESID     256 ; Max ID

define RESID        100 ; First ID
define STRID        384 ; First string ID
define ICOID        800 ; First icon ID

; Labels for resource data

define R0LABEL      <"R$0%03X">
define R1LABEL      <"R$1%03X">
define R2LABEL      <"R$2%03X">
define R3LABEL      <"R$3%03X">

define R_LANGUAGE   0x0409
define R_SUBLANG    0

; Hashing for resource keywords

RHASH macro string
 local FNVHASH
  FNVHASH = FNVBASE
  forc x,<string>
   FNVHASH = (FNVHASH * FNVPRIME) and 0xFFFFFFFF
   FNVHASH = FNVHASH xor '&x&'
   endm
  exitm<FNVHASH>
  endm

; Token values for resource statements

.enum StatementTokens {
    T_ACCELERATORS      = RHASH(ACCELERATORS),
    T_AUTO3STATE        = RHASH(AUTO3STATE),
    T_AUTOCHECKBOX      = RHASH(AUTOCHECKBOX),
    T_AUTORADIOBUTTON   = RHASH(AUTORADIOBUTTON),
    T_AVI               = RHASH(AVI),
    T_BITMAP            = RHASH(BITMAP),
    T_CAPTION           = RHASH(CAPTION),
    T_CHARACTERISTICS   = RHASH(CHARACTERISTICS),
    T_CHECKBOX          = RHASH(CHECKBOX),
    T_CHECKED           = RHASH(CHECKED),
    T_CLASS             = RHASH(CLASS),
    T_COMBOBOX          = RHASH(COMBOBOX),
    T_CONTROL           = RHASH(CONTROL),
    T_CURSOR            = RHASH(CURSOR),
    T_CTEXT             = RHASH(CTEXT),
    T_DEFPUSHBUTTON     = RHASH(DEFPUSHBUTTON),
    T_DIALOG            = RHASH(DIALOG),
    T_DIALOGEX          = RHASH(DIALOGEX),
    T_EDITTEXT          = RHASH(EDITTEXT),
    T_EXSTYLE           = RHASH(EXSTYLE),
    T_FONT              = RHASH(FONT),
    T_GRAYED            = RHASH(GRAYED),
    T_GROUPBOX          = RHASH(GROUPBOX),
    T_HELP              = RHASH(HELP),
    T_HTML              = RHASH(HTML),
    T_ICON              = RHASH(ICON),
    T_INACTIVE          = RHASH(INACTIVE),
    T_LANGUAGE          = RHASH(LANGUAGE),
    T_LISTBOX           = RHASH(LISTBOX),
    T_LTEXT             = RHASH(LTEXT),
    T_MENU              = RHASH(MENU),
    T_MENUBARBREAK      = RHASH(MENUBARBREAK),
    T_MENUBREAK         = RHASH(MENUBREAK),
    T_MENUEX            = RHASH(MENUEX),
    T_MENUITEM          = RHASH(MENUITEM),
    T_MESSAGETABLE      = RHASH(MESSAGETABLE),
    T_POPUP             = RHASH(POPUP),
    T_PUSHBOX           = RHASH(PUSHBOX),
    T_PUSHBUTTON        = RHASH(PUSHBUTTON),
    T_RADIOBUTTON       = RHASH(RADIOBUTTON),
    T_RCDATA            = RHASH(RCDATA),
    T_RTEXT             = RHASH(RTEXT),
    T_SCROLLBAR         = RHASH(SCROLLBAR),
    T_SEPARATOR         = RHASH(SEPARATOR),
    T_STATE3            = RHASH(STATE3),
    T_STRINGTABLE       = RHASH(STRINGTABLE),
    T_STYLE             = RHASH(STYLE),
    T_VERSION           = RHASH(VERSION),

    T_ALT               = RHASH(ALT),
    T_ASCII             = RHASH(ASCII),
    T_NOINVERT          = RHASH(NOINVERT),
    T_VIRTKEY           = RHASH(VIRTKEY),
    T_SHIFT             = RHASH(SHIFT),
    }

.template optional_statements
    characteristics dd ?
    language        dd ?
    sublanguage     dd ?
    version         dd ?
   .ends


ifdef USE_RESOURCE

.data?
 idcounter      dd ?
 dialogex       dd ?
 dotname        dd ?
 g_language     dd ?
.data
 ValidMenuOption dd \
    T_CHECKED,
    T_GRAYED,
    T_HELP,
    T_INACTIVE,
    T_MENUBARBREAK,
    T_MENUBREAK
 ValidDialogOption dd \
    T_CAPTION,              ; "text"
    T_CHARACTERISTICS,      ; dword
    T_CLASS,                ; class
    T_EXSTYLE,              ; extended-styles
    T_FONT,                 ; pointsize, "typeface", weight, italic, charset
    T_HELP,                 ; helpID
    T_LANGUAGE,             ; language, sublanguage
    T_MENU,                 ; menu (integer identifier)
    T_STYLE,                ; styles
    T_VERSION               ; dword
 ValidControlOption dd \
    T_CHARACTERISTICS,
    T_EXSTYLE,
    T_CLASS,
    T_HELP,
    T_STYLE
 ValidAcceleratorOption dd \
    T_ALT,
    T_ASCII,
    T_VIRTKEY,
    T_SHIFT,
    T_NOINVERT,
    T_CONTROL
 ValidOptionalStatements dd \
    T_CHARACTERISTICS,
    T_LANGUAGE,
    T_VERSION

endif

.code

ifdef USE_RESOURCE

; ResourceDir -- create a resource directory

ResourceDir proc __ccall i:int_t, tokenarray:token_t
   .new lpRead:string_t = "read"
    mov eax,MODULE.dotname
    mov dotname,eax
    mov MODULE.dotname,1
    mov idcounter,ICOID
    mov g_language,R_LANGUAGE
    .if ( MODULE.resource )
        mov lpRead,NULL
    .endif
    mov rcx,CurrSeg
    .if ( rcx )
        mov rdx,[rcx].asym.name
        AddLineQueueX( "%s %r", rdx, T_ENDS )
    .endif
    AddLineQueueX( ".rsrc %r %s %r %r 'RSRC'", T_SEGMENT, lpRead, T_DWORD, T_FLAT, T_PUBLIC )
    AddLineQueueX( "%r wstring(%r, 1)", T_DOT_PRAGMA, T_PUSH )
    RunLineQueue()
    mov MODULE.ResourceParsing,1
    .return( NOT_ERROR )
    endp

option proc: private

.enum TokenType {
    RC_NOTYPE,
    RC_RESOURCE,
    RC_CONTROL
    }

GetStatement proc fastcall token:StatementTokens
    xor eax,eax
    .switch ecx
    .case T_CHECKBOX
    .case T_COMBOBOX
    .case T_CONTROL
    .case T_CTEXT
    .case T_DEFPUSHBUTTON
    .case T_EDITTEXT
    .case T_GROUPBOX
    .case T_LISTBOX
    .case T_LTEXT
    .case T_MENUITEM
    .case T_POPUP
    .case T_PUSHBOX
    .case T_PUSHBUTTON
    .case T_RADIOBUTTON
    .case T_RTEXT
    .case T_SCROLLBAR
        inc eax
    .case T_ACCELERATORS
    .case T_AVI
    .case T_BITMAP
    .case T_CURSOR
    .case T_DIALOG
    .case T_DIALOGEX
    .case T_ICON
    .case T_LANGUAGE
    .case T_MENU
    .case T_MENUEX
    .case T_STRINGTABLE
        inc eax
    .endsw
    ret
    endp

GetStatementType proc fastcall token:StatementTokens
    xor eax,eax
    .switch ecx
    .case T_ACCELERATORS
        mov eax,RT_ACCELERATOR
       .endc
    .case T_AVI
        mov eax,RT_RCDATA
       .endc
    .case T_STRINGTABLE
        inc eax
    .case T_DIALOG
    .case T_DIALOGEX
        inc eax
    .case T_MENU
    .case T_MENUEX
        inc eax
    .case T_ICON
        inc eax
    .case T_BITMAP
        inc eax
    .case T_CURSOR
        inc eax
    .endsw
    ret
    endp

; WriteResID -- write a resource identifier

WriteResID proc __ccall ID:size_t
    ldr rcx,ID
    mov edx,0xFFFF
    .if ( rcx > rdx )
        AddLineQueueX( " %r %s, 0", T_DW, rcx )
    .else
        AddLineQueueX( " %r %u, 0", T_DW, ecx )
    .endif
    ret
    endp


AddControl proc __ccall helpID:int_t, extended_style:int_t, style:int_t, name:string_t,
        class:int_t, id:int_t, x:int_t, y:int_t, width:int_t, height:int_t

   .new buffer[2048]:char_t
    AddLineQueueX( " %r 4", T_ALIGN )
    .if ( dialogex )
        AddLineQueueX( " %r %d, 0x%X, 0x%X", T_DD, helpID, extended_style, style )
    .else
        AddLineQueueX( " %r 0x%X, 0x%X", T_DD, style, extended_style )
    .endif
    AddLineQueueX( " %r %d, %d, %d, %d, %d", T_DW, x, y, width, height, id )
    .if ( dialogex )
        AddLineQueueX( " %r 0", T_DW )
    .endif
    AddLineQueueX( " %r -1, %d", T_DW, class )
    mov rcx,name
    mov eax,0xFFFF
    .if ( rcx > rax )
        ExpandCString(&buffer, StringBufferEnd, rcx, 1)
        AddLineQueueX( " %r %s, 0", T_DW, &buffer )
    .else
        AddLineQueueX( " %r %u, 0", T_DW, ecx )
    .endif
    ; optional data..
    AddLineQueueX( " %r 0", T_DW )
    ret
    endp

    assume rbx:token_t, rsi:resource_t, uses rsi rdi rbx

ParseResource proc __ccall public tokenarray:token_t
   .new dir:ICONDIR
   .new fp:LPFILE
   .new rp:resource_t

    ldr rbx,tokenarray
    .ifd ( GetStatement([rbx].hash2) == 0 )
        WriteResource()
       .return ParseLine( rbx )
    .endif
    FStoreLine(0)
    mov rsi,LclAlloc( res_item )
    mov rcx,MODULE.ResStack
    .if !rcx
        mov MODULE.ResStack,rax
    .else
        .while ( [rcx].res_item.next )
            mov rcx,[rcx].res_item.next
        .endw
        mov [rcx].res_item.next,rsi
    .endif
    mov [rsi].hash,[rbx].hash2
    .if ( eax == T_ICON || eax == T_CURSOR )
        mov rp,rsi
        .if ( fopen( [rbx+asm_tok].tokpos, "rb" ) == NULL )
            asmerr( 1000, [rbx+asm_tok].tokpos )
        .endif
        mov fp,rax
        fread( &dir, 1, ICONDIR, rax )
        fclose(fp)
        movzx eax,dir.idCount
        mov ecx,idcounter
        add idcounter,eax
        mov rsi,rp
        mov [rsi].icon[0],ax
        mov [rsi].icon[2],cx
    .endif
    mov [rsi].type,GetStatementType([rbx].hash2)
    .if ( [rbx+asm_tok].token != T_FINAL )
        mov [rsi].line,LclDup([rbx].tokpos)
    .endif
    .return( NOT_ERROR )
    endp

    assume rsi:nothing


; LANGUAGE language, sublang

SetLanguage proc __ccall resource:resource_t, language:pint_t, sublang:pint_t
   .new oldstat:input_status
   .new opnd:expr
   .new i:int_t = 1
    ldr rsi,resource
    mov rbx,PushInputStatus( &oldstat )
    tstrcpy( CurrSource, [rsi].res_item.line )
    mov TokenCount,Tokenize( CurrSource, 0, rbx, TOK_DEFAULT )
    .ifd ( EvalOperand( &i, rbx, TokenCount, &opnd, 0 ) != ERROR )
        mov rdx,language
        mov eax,opnd.value
        mov [rdx],eax
    .endif
    imul ecx,i,asm_tok
    .if ( [rbx+rcx].token == T_COMMA )
        inc i
        .ifd ( EvalOperand( &i, rbx, TokenCount, &opnd, 0 ) != ERROR )
            mov rdx,sublang
            mov eax,opnd.value
            mov [rdx],eax
        .endif
    .endif
    PopInputStatus( &oldstat )
    ret
    endp


; <ICON|CURSOR> <file>

WriteIcon proc __ccall file:string_t, resource:resource_t

   .new iconbuf:ptr ICONDIR
   .new filesize:int_t = 0
   .new i:int_t, entry_count, entry_id, res_id, res_type, j
   .new is_cursor:byte = 0

    ldr rbx,file
    .if ( fopen( rbx, "rb" ) == NULL )
        asmerr( 1000, rbx )
    .endif
    mov rbx,rax
    .if ( fseek( rbx, 0, SEEK_END ) == 0 )
        .if ftell( rbx )
            mov filesize,eax
            mov iconbuf,MemAlloc( rax )
            rewind( rbx )
            fread( iconbuf, 1, filesize, rbx )
        .endif
    .endif
    fclose( rbx )
    .if ( filesize < ICONDIR + ICONDIRENTRY )
        .return ERROR
    .endif
    mov rdi,resource
    movzx eax,[rdi].res_item.icon[0]
    mov entry_count,eax
    movzx eax,[rdi].res_item.icon[2]
    mov entry_id,eax
    mov eax,[rdi].res_item.name
    add eax,RESID
    mov res_id,eax
    mov res_type,[rdi].res_item.type
    mov rax,iconbuf
    .if ( [rax].ICONDIR.idType == 2 )
        inc is_cursor
    .endif
    lea rsi,[rax].ICONDIR.idEntries
    assume rsi:ptr ICONDIRENTRY
    .if ( MODULE.resource == 0 )
        .for ( ebx = entry_id, edi = 0 : edi < entry_count : ebx++, edi++, rsi += ICONDIRENTRY )
            mov eax,[rsi].dwBytesInRes
            .if ( is_cursor )
                add eax,4
            .endif
            AddLineQueueX( R2LABEL " %r %r " R3LABEL ", %u, 0, 0", ebx, T_DD, T_IMAGEREL, ebx, eax )
        .endf
        imul ecx,entry_count,GRPICONDIRENTRY
        add ecx,GRPICONDIR
        AddLineQueueX( R2LABEL " %r %r " R3LABEL ", %u, 0, 0", res_id, T_DD, T_IMAGEREL, res_id, ecx )
    .endif
    imul eax,entry_count,ICONDIRENTRY
    mov rcx,iconbuf
    lea rsi,[rcx].ICONDIR.idEntries
    lea rdi,[rcx+rax+ICONDIR]
    .for ( i = 0 : i < entry_count : i++, rsi += ICONDIRENTRY )
        mov ebx,entry_id
        add ebx,i
        .if ( MODULE.resource )
            AddLineQueueX( " %r 4", T_ALIGN )
            mov ecx,[rsi].dwBytesInRes
            .if ( is_cursor )
                add ecx,4
            .endif
            AddLineQueueX( " %r %u, 32, 0x%XFFFF, 0x%XFFFF", T_DD, ecx, res_type, ebx )
            AddLineQueueX( " %r 0, 0, 0x%X, 0x%X", T_DW, 0x1010, g_language )
            AddLineQueueX( " %r 0, 0", T_DD )
        .endif
        AddLineQueueX( R3LABEL " %r %r", ebx, T_LABEL, T_BYTE )
        .if ( is_cursor )
            AddLineQueueX( " %r 0x%02X, 0x%02X", T_DW, [rsi].wPlanes, [rsi].wBitCount )
        .endif
        .for ( ebx = [rsi].dwBytesInRes : ebx : )
            .if ( ebx >= 16 )
                assume rdi:ptr dword
                AddLineQueueX( " %r 0x%08X, 0x%08X, 0x%08X, 0x%08X", T_DD, [rdi], [rdi+4], [rdi+8], [rdi+12] )
                sub ebx,16
                add rdi,16
            .elseif ( ebx >= 4 )
                AddLineQueueX( " %r 0x%08X", T_DD, [rdi] )
                sub ebx,4
                add rdi,4
            .else
                assume rdi:nothing
                movzx eax,byte ptr [rdi]
                AddLineQueueX( " %r 0x%02X", T_DB, eax )
                dec ebx
                inc rdi
            .endif
        .endf
    .endf
    .if ( MODULE.resource )
        imul ecx,entry_count,GRPICONDIRENTRY
        add ecx,GRPICONDIR
        mov edx,RT_GROUP_CURSOR
        .if ( !is_cursor )
            mov edx,RT_GROUP_ICON
        .endif
        AddLineQueueX( " %r %u, 32, 0x%XFFFF, 0x%XFFFF", T_DD, ecx, edx, res_id )
        AddLineQueueX( " %r 0, 0, 0x%X, 0x%X", T_DW, 0x1030, g_language )
        AddLineQueueX( " %r 0, 0", T_DD )
    .endif
    AddLineQueueX( R3LABEL " %r %r", res_id, T_LABEL, T_BYTE )
    mov rsi,iconbuf
    assume rsi:ptr ICONDIR
    AddLineQueueX( " %r 0, %u, %u", T_DW, [rsi].idType, [rsi].idCount )
    lea rsi,[rsi].idEntries
    assume rsi:ptr ICONDIRENTRY
    .for ( ebx = 0 : ebx < entry_count : ebx++, rsi += ICONDIRENTRY )
        .if ( is_cursor )
            mov [rsi].bHeight,0         ; Win95+ 0=256 pixels
            mov [rsi].bColorCount,64    ; Set by RC -- unused by CURSOR
            mov [rsi].wPlanes,1         ; moved to data
            mov [rsi].wBitCount,1       ; moved to data
            add [rsi].dwBytesInRes,4    ; + wPlanes and wBitCount
        .elseif ( MODULE.resource && [rsi].wPlanes == 0 )
            inc [rsi].wPlanes
        .endif
        AddLineQueueX( " %r %u, %u, %u, 0", T_DB, [rsi].bWidth, [rsi].bHeight, [rsi].bColorCount )
        AddLineQueueX( " %r %u, %u", T_DW, [rsi].wPlanes, [rsi].wBitCount )
        AddLineQueueX( " %r %u", T_DD, [rsi].dwBytesInRes )
        mov ecx,entry_id
        add ecx,ebx
        AddLineQueueX( " %r %u", T_DW, ecx )
    .endf
    .if ( MODULE.resource && !( ebx & 3 ) )
        AddLineQueueX( " %r 0", T_DW )
    .endif
    MemFree(iconbuf)
    ret
    endp

    assume rsi:nothing

; Read an array of integer values.
; - the list may end with a string: x, y, width, height {...}

GetIntParams proc __ccall tokenarray:token_t, i:pint_t, count:int_t, array:pint_t
   .new opnd:expr
    ldr rsi,i
    ldr rdi,array
    .for ( ebx = 0 : ebx < count : ebx++ )
        .ifd ( EvalOperand( rsi, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .return
        .endif
        .ifd ( opnd.kind != EXPR_CONST )
            .return( ERROR )
        .endif
        mov eax,opnd.value
        mov [rdi+rbx*4],eax
        imul ecx,[rsi],asm_tok
        add rcx,tokenarray
        .if ( [rcx].asm_tok.token == T_COMMA )
            inc dword ptr [rsi]
        .elseif ( [rcx].asm_tok.token == T_FINAL && [rcx-asm_tok].asm_tok.token == T_STRING )
            dec dword ptr [rsi] ; make sure we don't eat the string value here..
        .endif
    .endf
    .return( NOT_ERROR )
    endp


GetOptionalNumber proc __ccall tokenarray:token_t, i:pint_t, num:pint_t
    ldr rbx,tokenarray
    ldr rsi,i
    ldr rdi,num
    imul ecx,[rsi],asm_tok
    xor eax,eax
    .if ( [rbx+rcx].token == T_NUM )
        GetIntParams(rbx, rsi, 1, rdi)
    .endif
    ret
    endp


GetValidOption proc __ccall tokenarray:token_t, i:pint_t, count:int_t, array:pbyte_t
   .new opnd:expr
    ldr rbx,tokenarray
    ldr rsi,i
    ldr rdi,array
    imul eax,[rsi],asm_tok
    add rbx,rax
    xor eax,eax
    .if ( [rbx].token == T_ID )
        mov eax,[rbx].hash2
        .for ( ecx = 0 : ecx < count : ecx++ )
            .if ( eax == [rdi+rcx*4] )
                inc dword ptr [rsi]
                .if ( [rbx+asm_tok].token == T_COMMA )
                    inc dword ptr [rsi]
                .endif
                .return
            .endif
        .endf
        xor eax,eax
    .endif
    ret
    endp


GetValidOptionalStatements proc __ccall tokenarray:token_t, i:pint_t, os:ptr optional_statements
    ldr rbx,tokenarray
    ldr rsi,i
    ldr rdi,os
    xor eax,eax
    mov [rdi].optional_statements.characteristics,eax
    mov [rdi].optional_statements.language,R_LANGUAGE
    mov [rdi].optional_statements.sublanguage,eax
    mov [rdi].optional_statements.version,eax
    inc eax
    mov [rsi],eax
    .whiled GetValidOption(rbx, rsi, lengthof(ValidOptionalStatements), &ValidOptionalStatements)
        xor edx,edx
        .switch pascal eax
        .case T_CHARACTERISTICS
            lea rcx,[rdi].optional_statements.characteristics
            inc edx
        .case T_LANGUAGE
            lea rcx,[rdi].optional_statements.language
            mov edx,2
        .case T_VERSION
            lea rcx,[rdi].optional_statements.version
            inc edx
        .endsw
        .if ( edx )
            .ifd ( GetIntParams(rbx, rsi, edx, rcx) == ERROR )
                .return
            .endif
        .endif
    .endw
    .return( NOT_ERROR )
    endp

WriteResourceHeader proc __ccall index:int_t, name:int_t, type:int_t, os:ptr optional_statements
    ldr edi,index
    ldr ebx,name
    ldr rsi,os
    .if ( MODULE.resource )
        AddLineQueueX( " %r size_" R2LABEL ", 32, 0x%XFFFF, 0x%XFFFF", T_DD, edi, type, ebx )
        AddLineQueueX( " %r 0, 0, 0x%X, 0x%X", T_DW, 0x1030, [rsi].optional_statements.language )
        AddLineQueueX( " %r 0x%X, 0x%X", T_DD, [rsi].optional_statements.version, [rsi].optional_statements.characteristics )
    .else
        AddLineQueueX( R2LABEL " %r %r " R3LABEL ", size_" R2LABEL ", 0,0", edi, T_DD, T_IMAGEREL, edi, edi )
    .endif
    AddLineQueueX( R3LABEL " %r %r", edi, T_LABEL, T_DWORD )
    ret
    endp


; AVI <file> - Audio Video Interleave

WriteAvi proc __ccall tokenarray:token_t, index:int_t
    ldr rbx,tokenarray
    ldr edi,index
    .if ( MODULE.resource )
        AddLineQueueX( " %r size_" R2LABEL ", 36", T_DD, edi )
        AddLineQueueX( " %r 'A', 'V', 'I', 0", T_DW )
        AddLineQueueX( " %r -1, 0x%X, 0, 0, 0x30, 0x%X, 0, 0", T_DW, edi, g_language )
        AddLineQueueX( " %r 0", T_DD )
    .else
        asmerr( 2008, "AVI only supported for -res" )
    .endif
    AddLineQueueX( R3LABEL " %r %r", edi, T_LABEL, T_DWORD )
    AddLineQueueX( " %r <%s>", T_INCBIN, [rbx+asm_tok].tokpos )
    AddLineQueueX( " size_" R2LABEL " %r $ - " R3LABEL, edi, T_EQU, edi )
    ret
    endp


; BITMAP <file>

WriteBitmap proc __ccall tokenarray:token_t, index:int_t
   .new os:optional_statements = {0}
    ldr rbx,tokenarray
    ldr edi,index
    WriteResourceHeader( edi, edi, RT_BITMAP, &os )
    AddLineQueueX( " %r <%s>, 14", T_INCBIN, [rbx+asm_tok].tokpos )
    AddLineQueueX( " size_" R2LABEL " %r $ - " R3LABEL, edi, T_EQU, edi )
    ret
    endp


; ACCELERATORS [optional-statements] {event, idvalue, [type] [options]... }

WriteAccelerators proc __ccall tokenarray:token_t, index:int_t

   .new ops:optional_statements
   .new i:int_t, id, flags, key
   .new oldstat:input_status

    ldr rbx,tokenarray
    ldr edi,index

    GetValidOptionalStatements(rbx, &i, &ops)
    PushInputStatus( &oldstat )
    imul ecx,i,asm_tok
    tstrcpy( CurrSource, [rbx+rcx].asm_tok.string_ptr )
    mov TokenCount,Tokenize( CurrSource, 0, rbx, TOK_DEFAULT )
    WriteResourceHeader( edi, edi, RT_ACCELERATOR, &ops )
    .for ( rsi = rbx, edi = 0 : edi < TokenCount : )
        imul ebx,edi,asm_tok
        add rbx,rsi
        .if ( [rbx].token == T_COMMA )
            inc edi
            add rbx,asm_tok
        .endif
        .if ( [rbx].token == T_STRING )
            xor ecx,ecx
            mov rax,[rbx].string_ptr
            mov eax,[rax]
            .if ( al == '"' )
                shr eax,8
            .endif
            .if ( al == '^' )
                mov al,ah
                and al,not 0x20
                sub al,'A'
            .endif
            movzx eax,al
            mov flags,ecx
            mov key,eax
            inc edi
            .if ( [rbx+asm_tok].token == T_COMMA )
                inc edi
            .endif
        .else
            mov i,edi
            mov flags,0
            .ifd ( GetIntParams(rsi, &i, 1, &key) == ERROR )
                jmp error
            .endif
            mov edi,i
        .endif
        mov i,edi
        .ifd ( GetIntParams(rsi, &i, 1, &id) == ERROR )
            jmp error
        .endif
        mov ebx,flags
        .whiled GetValidOption(rsi, &i, lengthof(ValidAcceleratorOption), &ValidAcceleratorOption)
            .switch pascal eax
            .case T_ALT
                or ebx,ACC_ALT
            .case T_ASCII
            .case T_VIRTKEY
                or ebx,ACC_VIRTKEY
            .case T_SHIFT
                or ebx,ACC_SHIFT
            .case T_CONTROL
                or ebx,ACC_CONTROL
            .case T_NOINVERT
                or ebx,ACC_NOINVERT
            .endsw
        .endw
         mov edi,i
         .if ( edi >= TokenCount )
            or ebx,ACC_LAST
         .endif
         AddLineQueueX( " %r 0x%02X, 0x%02X, %d, 0", T_DW, ebx, key, id )
    .endf
    AddLineQueueX( " size_" R2LABEL " %r $ - " R3LABEL, index, T_EQU, index )
toend:
    PopInputStatus( &oldstat )
    ret
error:
    asmerr( 2008, [rbx].string_ptr )
    jmp toend
    endp

; STRINGTABLE [optional-statements] {string  ...} -- 384..n

WriteStringTable proc __ccall tokenarray:token_t, id:int_t, table:int_t

   .new ops:optional_statements
   .new oldstat:input_status
   .new i:int_t
   .new buffer[4096]:char_t

    ldr rbx,tokenarray
    ldr edi,id
    ldr esi,table

    GetValidOptionalStatements(rbx, &i, &ops)
    PushInputStatus( &oldstat )
    imul ecx,i,asm_tok
    tstrcpy( CurrSource, [rbx+rcx].string_ptr )
    mov TokenCount,Tokenize( CurrSource, 0, rbx, TOK_DEFAULT )
    WriteResourceHeader( edi, esi, RT_STRING, &ops )
    .for ( esi = 0, edi = 0 : edi < TokenCount : esi++ )
        .if ( [rbx].token != T_STRING )
            jmp error
        .endif
        ExpandCString(&buffer, StringBufferEnd, [rbx].string_ptr, 1)
        ;
        ; v2.40.10: calculate char-count of string from buffer
        ; - the return value is byte-count: "ab\x0102" = 4
        ;
        AddLineQueueX( " %r " R3LABEL "%uCC", T_DW, id, esi )
        AddLineQueueX( R3LABEL "%u %r %s", id, esi, T_DW, &buffer )
        AddLineQueueX( R3LABEL "%uCC %r (($ - " R3LABEL "%u) / 2)", id, esi, T_EQU, id, esi )
        inc edi
        add rbx,asm_tok
        .if ( [rbx].token == T_COMMA )
            inc edi
            add rbx,asm_tok
        .endif
    .endf
    .for ( : esi < 16 : esi++ )
        AddLineQueueX( " %r 0", T_DW )
    .endf
    AddLineQueueX( " size_" R2LABEL " %r $ - " R3LABEL, id, T_EQU, id )
toend:
    PopInputStatus( &oldstat )
    ret
error:
    asmerr( 2008, [rbx].string_ptr )
    jmp toend
    endp


; MENU {...} or (recursive) POPUP {...}

WriteMenu proc __ccall tokenarray:token_t, index:int_t

   .new ops:optional_statements
   .new i:int_t = 1
   .new result:int_t
   .new text:string_t
   .new oldstat:input_status

    ldr rbx,tokenarray
    ldr edi,index

    .if ( edi )
        GetValidOptionalStatements(rbx, &i, &ops)
        .if ( dialogex )
            inc ops.version
            GetOptionalNumber(rbx, &i, &ops.characteristics)
        .endif
        WriteResourceHeader( edi, edi, RT_MENU, &ops )
        AddLineQueueX( " %r 0", T_DD )
    .endif
    PushInputStatus( &oldstat )
    imul ecx,i,asm_tok
    tstrcpy( CurrSource, [rbx+rcx].string_ptr )
    mov TokenCount,Tokenize( CurrSource, 0, rbx, TOK_DEFAULT )

    .for ( rsi = rbx, edi = 0 : edi < TokenCount : )

        imul ebx,edi,asm_tok
        add rbx,rsi
        .if ( [rbx].token == T_COMMA )
            inc edi
            add rbx,asm_tok
        .endif
        mov eax,[rbx].hash2
        add rbx,asm_tok
        .switch pascal eax
        .case T_MENUITEM

            ; MENUITEM text, result, [optionlist]
            ; MENUITEM SEPARATOR

            .if ( [rbx].token == T_ID )
                .ifd ( [rbx].hash2 == T_SEPARATOR )
                    add edi,2
                    AddLineQueueX( " %r 0,0,0", T_DW )
                   .endc
                .endif
                jmp error
            .endif
            .if ( [rbx].token != T_STRING )
                jmp error
            .endif
            mov text,[rbx].string_ptr
            add edi,2
            .if ( [rbx+asm_tok].token == T_COMMA )
                inc edi
            .endif
            mov i,edi
            .ifd ( GetIntParams(rsi, &i, 1, &result) == ERROR )
                jmp error
            .endif
            xor ebx,ebx
            .whiled GetValidOption(rsi, &i, lengthof(ValidMenuOption), &ValidMenuOption)
                .switch pascal eax
                .case T_CHECKED
                    or ebx,MF_CHECKED
                .case T_GRAYED
                    or ebx,MF_GRAYED
                .case T_HELP
                    or ebx,MF_HELP
                .case T_INACTIVE
                    or ebx,MF_DISABLED ; ?
                .case T_MENUBARBREAK
                    or ebx,MF_MENUBARBREAK
                .case T_MENUBREAK
                    or ebx,MF_MENUBREAK
                .endsw
            .endw
            mov edi,i
            .if ( edi >= TokenCount )
                or ebx,MF_END
            .endif
            AddLineQueueX( " %r %u,%u,%s,0", T_DW, ebx, result, text )
        .case T_POPUP

            ; POPUP <name> [, optionlist] {item-definitions ...}

            .if ( [rbx].token != T_STRING )
                jmp error
            .endif
            mov text,[rbx].string_ptr
            add edi,2
            mov al,[rbx+asm_tok].token
            mov ebx,MF_POPUP
            .if ( al == T_COMMA )
                inc edi
                mov i,edi
                .whiled GetValidOption(rsi, &i, lengthof(ValidMenuOption), &ValidMenuOption)
                    .switch pascal eax
                    .case T_CHECKED
                        or ebx,MF_CHECKED
                    .case T_GRAYED
                        or ebx,MF_GRAYED
                    .case T_HELP
                        or ebx,MF_HELP
                    .case T_INACTIVE
                        or ebx,MF_DISABLED ; ?
                    .case T_MENUBARBREAK
                        or ebx,MF_MENUBARBREAK
                    .case T_MENUBREAK
                        or ebx,MF_MENUBREAK
                    .endsw
                .endw
                mov edi,i
            .endif
            mov edx,ebx
            imul ebx,edi,asm_tok
            add rbx,rsi
            inc edi
            sub rbx,asm_tok
            .if ( edi >= TokenCount )
                or edx,MF_END
            .endif
            AddLineQueueX( " %r %u,%s,0", T_DW, edx, text )
            WriteMenu( rbx, 0 )
            mov TokenCount,Tokenize( CurrSource, 0, rsi, TOK_DEFAULT )
        .default
         error:
            .return asmerr( 2008, [rbx].string_ptr )
        .endsw
    .endf
    .if ( index )
        AddLineQueueX( " size_" R2LABEL " %r $ - " R3LABEL, index, T_EQU, index )
    .endif
    PopInputStatus( &oldstat )
    ret
    endp


; <Control> [text,] id, x, y, width, height [, style [, extended-style]]

ParseControl proc __ccall tokenarray:token_t, i:ptr int_t, flags:int_t,
        default_flags:int_t, use_name:int_t, class:int_t

   .new height:int_t, width, y, x, id
   .new style:int_t = 0
   .new extended_style:int_t = 0
   .new characteristics:int_t = 0
   .new helpID:int_t = 0
   .new name:string_t = NULL

    ldr rbx,tokenarray
    ldr rsi,i
    ldr eax,use_name

    .if ( eax )
        imul ecx,[rsi],asm_tok
        add rcx,rbx
        .if ( [rcx].asm_tok.token != T_STRING )
            .return ERROR
        .endif
        mov name,[rcx].asm_tok.string_ptr
        inc dword ptr [rsi]
        inc dword ptr [rsi]
    .endif
    .ifd ( GetIntParams(rbx, rsi, 5, &id) == ERROR )
        .return
    .endif
    .whiled GetValidOption(rbx, rsi, lengthof(ValidControlOption), &ValidControlOption)
        xor ecx,ecx
        .switch pascal eax
        .case T_CHARACTERISTICS
            lea rcx,characteristics
        .case T_EXSTYLE
            lea rcx,extended_style
        .case T_CLASS
            lea rcx,class
        .case T_HELP
            lea rcx,helpID
        .case T_STYLE
            lea rcx,style
        .endsw
        .if ( rcx )
            .ifd ( GetIntParams(rbx, rsi, 1, rcx) == ERROR )
                .return
            .endif
        .endif
    .endw
    mov ebx,style
    .if ( ebx == 0 )
        mov ebx,default_flags
    .endif
    or ebx,flags
    AddControl(helpID, extended_style, ebx, name, class, id, x, y, width, height)
    .return( NOT_ERROR )
    endp


.pragma aux(ebx, eax, edx, ecx)

WriteControl proto asmcall :int_t, :int_t, :int_t, :int_t { jmp control }

.pragma aux(pop)


; DIALOG x, y, width, height [, helpID] [optional-statements] {...}

WriteDialog proc __ccall tokenarray:token_t, index:int_t

   .new i:int_t = 1
   .new os:optional_statements
   .new extended_style:int_t
   .new caption:string_t
   .new typeface:string_t
   .new pointsize:int_t
   .new helpID:int_t
   .new height:int_t, width, y, x
   .new style:int_t
   .new class:int_t
   .new id:int_t
   .new weight:int_t, italic, charset
   .new menu:int_t
   .new count:int_t

    ldr rbx,tokenarray
    lea rcx,i
    lea rdi,count
    xor eax,eax
    sub rcx,rdi
    rep stosb
    .ifd ( GetIntParams(rbx, &i, 4, &x) == ERROR )
        jmp error
    .endif
    mov rsi,rbx
    .whiled GetValidOption(rsi, &i, lengthof(ValidDialogOption), &ValidDialogOption)
        imul ebx,i,asm_tok
        add rbx,rsi
        xor ecx,ecx
        .switch pascal eax
        .case T_CAPTION
            mov caption,LclDup( [rbx].string_ptr )
            inc i
            .if ( [rbx+asm_tok].token == T_COMMA )
                inc i
            .endif
            xor ecx,ecx
        .case T_CHARACTERISTICS
            lea rcx,os.characteristics
        .case T_CLASS
            lea rcx,class
        .case T_EXSTYLE
            lea rcx,extended_style
        .case T_FONT
            .ifd ( GetIntParams(rsi, &i, 1, &pointsize) == ERROR )
                jmp error
            .endif
            imul ebx,i,asm_tok
            add rbx,rsi
            mov typeface,LclDup( [rbx].string_ptr )
            inc i
            .if ( [rbx+asm_tok].token == T_COMMA )
                inc i
                GetOptionalNumber(rsi, &i, &weight)
                GetOptionalNumber(rsi, &i, &italic)
                GetOptionalNumber(rsi, &i, &charset)
            .endif
            xor ecx,ecx
        .case T_HELP
            lea rcx,helpID
        .case T_LANGUAGE
            .ifd ( GetIntParams(rsi, &i, 2, &os.language) == ERROR )
                jmp error
            .endif
            xor ecx,ecx
        .case T_MENU
            lea rcx,menu
        .case T_STYLE
            lea rcx,style
        .case T_VERSION
            lea rcx,os.version
        .endsw
        .if ( rcx )
            .ifd ( GetIntParams(rsi, &i, 1, rcx) == ERROR )
                jmp error
            .endif
        .endif
    .endw
    WriteResourceHeader( index, index, RT_DIALOG, &os )
    imul ebx,i,asm_tok
    add rbx,rsi
    .if ( [rbx].token != T_STRING )
        jmp error
    .endif
    tstrcpy( CurrSource, [rbx].string_ptr )
    mov TokenCount,Tokenize( CurrSource, 0, rsi, TOK_DEFAULT )
    or  style,WS_DLGFRAME
    .if ( dialogex )
        AddLineQueueX( " %r 0xFFFF0001, 0x%X", T_DD, helpID )
        AddLineQueueX( " %r 0x%X, 0x%X", T_DD, extended_style, style )
    .else
        AddLineQueueX( " %r 0x%X, 0", T_DD, style )
    .endif
    ;
    ; get the element-count
    ;
    .for ( edi = 0, rbx = rsi : edi < TokenCount : edi++, rbx += asm_tok )
        .if ( [rbx].token == T_ID )
            .ifd ( GetStatement([rbx].hash2) == RC_CONTROL )
                inc count
            .endif
        .endif
    .endf
    AddLineQueueX( " %r %u, %u, %u, %u, %u", T_DW, count, x, y, width, height )
    WriteResID(menu)
    WriteResID(caption)
    .if ( style & DS_SETFONT )
        AddLineQueueX( " %r %u", T_DW, pointsize )
        .if ( dialogex )
            AddLineQueueX( " %r %u", T_DW, weight )
            AddLineQueueX( " %r %u, %u", T_DB, italic, charset )
        .endif
        AddLineQueueX( " %r %s, 0", T_DW, typeface )
    .endif

    .for ( edi = 0 : edi < TokenCount : )

        imul ebx,edi,asm_tok
        add rbx,rsi
        .if ( [rbx].token == T_COMMA )
            inc edi
            add rbx,asm_tok
        .endif
        mov eax,[rbx].hash2
        add rbx,asm_tok
        .switch pascal eax
        .case T_CHECKBOX

            ; CHECKBOX text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, BS_CHECKBOX or WS_TABSTOP, 1)
        .case T_COMBOBOX

            ; COMBOBOX id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, CBS_SIMPLE or WS_TABSTOP, 0)
        .case T_CONTROL

            ; CONTROL text, id, class, style, x, y, width, height [, extended-style]

            add edi,3
            mov i,edi
            .ifd ( GetIntParams(rsi, &i, 7, &id) == ERROR )
                .return
            .endif
            .whiled GetValidOption(rsi, &i, lengthof(ValidControlOption), &ValidControlOption)
                xor ecx,ecx
                .switch pascal eax
                .case T_CHARACTERISTICS
                    lea rcx,os.characteristics
                .case T_EXSTYLE
                    lea rcx,extended_style
                .case T_CLASS
                    lea rcx,class
                .case T_HELP
                    lea rcx,helpID
                .case T_STYLE
                    lea rcx,style
                .endsw
                .if ( rcx )
                    .ifd ( GetIntParams(rsi, &i, 1, rcx) == ERROR )
                        .return
                    .endif
                .endif
            .endw
            mov edi,i
            mov ecx,style
            or  ecx,WS_CHILD or WS_VISIBLE
            AddControl(helpID, extended_style, ecx,
                [rbx].string_ptr, class, id, x, y, width, height)
        .case T_CTEXT

            ; CTEXT text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_STATIC, SS_CENTER or WS_GROUP, 1)
        .case T_DEFPUSHBUTTON

            ; DEFPUSHBUTTON text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, BS_DEFPUSHBUTTON or WS_TABSTOP, 1)
        .case T_EDITTEXT

            ; EDITTEXT id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE or DS_MODALFRAME, RC_EDIT, ES_LEFT or WS_BORDER or WS_TABSTOP, 0)
        .case T_GROUPBOX

            ; GROUPBOX text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, BS_GROUPBOX, 1)
        .case T_LISTBOX

            ; LISTBOX id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, LBS_NOTIFY or WS_BORDER, 0)
        .case T_LTEXT

            ; LTEXT text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_STATIC, SS_LEFT or WS_GROUP, 1)
        .case T_PUSHBOX

            ; PUSHBOX text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, BS_PUSHBOX or WS_TABSTOP, 1)
        .case T_PUSHBUTTON

            ; PUSHBUTTON text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, BS_PUSHBUTTON or WS_TABSTOP, 1)
        .case T_RADIOBUTTON

            ; RADIOBUTTON text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_BUTTON, BS_RADIOBUTTON or WS_TABSTOP, 1)
        .case T_RTEXT

            ; RTEXT text, id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_STATIC, SS_RIGHT or WS_GROUP, 1)
        .case T_SCROLLBAR

            ; SCROLLBAR id, x, y, width, height [, style [, extended-style]]

            WriteControl(WS_CHILD or WS_VISIBLE, RC_SCROLLB, SBS_HORZ, 0)
        .default
         error:
            .return asmerr( 2008, [rbx].string_ptr )
         control:
            inc edi
            mov i,edi
            ParseControl(rsi, &i, ebx, edx, ecx, eax)
            mov ecx,edi
            mov edi,i
           .endc .if ( eax != ERROR )
            imul ebx,ecx,asm_tok
            add rbx,rsi
            jmp error
        .endsw
    .endf
    AddLineQueueX( " size_" R2LABEL " %r $ - " R3LABEL, index, T_EQU, index )
    ret
    endp

    assume rsi:resource_t

WriteResource proc public

   .new language:int_t = R_LANGUAGE
   .new sublanguage:int_t = R_SUBLANG
   .new ResIdCount:int_t
   .new StrCounter:int_t = STRID
   .new types[MAXTYPES]:byte = {0}
   .new names[MAXRESID]:word
   .new typei[MAXRESID]:byte
   .new oldstat:input_status

    .for ( rsi = MODULE.ResStack : rsi : rsi = [rsi].next )
        mov eax,[rsi].hash
        .if ( eax == T_LANGUAGE )
            SetLanguage(rsi, &language, &sublanguage)
        .endif
    .endf
    mov g_language,language

    .if ( MODULE.resource )

        ; Write the global dummy header

        AddLineQueueX( " %r 0,32,0xFFFF,0xFFFF", T_DD )
        AddLineQueueX( " %r 0,0,0,0", T_DD )

        .for ( edi = 0, ebx = 0, rsi = MODULE.ResStack : rsi : rsi = [rsi].next )
            mov eax,[rsi].type
            .if ( eax )
                mov [rsi].name,ebx
                inc ebx
            .endif
        .endf

    .else

        ; write main directory and entries for types

        .for ( edi = 0, ebx = 0, rsi = MODULE.ResStack : rsi : rsi = [rsi].next )
            mov eax,[rsi].type
            .if ( eax )
                mov [rsi].name,ebx
                .if ( eax == RT_ICON || eax == RT_CURSOR )
                    movzx edx,[rsi].icon[2]
                    .for ( ecx = 0 : cx < [rsi].icon[0] : ecx++, edx++, edi++ )
                        sub edx,RESID
                        mov names[rdi*2],dx
                        mov typei[rdi],al
                        inc types[rax]
                        add edx,RESID
                    .endf
                    .if ( eax == RT_ICON )
                        inc types[RT_GROUP_ICON]
                        mov eax,RT_GROUP_ICON
                    .else
                        inc types[RT_GROUP_CURSOR]
                        mov eax,RT_GROUP_CURSOR
                    .endif
                .else
                    inc types[rax]
                .endif
                mov names[rdi*2],bx
                mov typei[rdi],al
                inc ebx
                inc edi
            .endif
        .endf
        mov ResIdCount,edi

        .for ( ecx = 0, eax = 1 : eax < MAXTYPES : eax++ )
            .if ( types[rax] )
                inc ecx
            .endif
        .endf
        shl ecx,16
        AddLineQueueX( " %r 0,0,0,0x%X", T_DD, ecx )
        .for ( edi = 1 : edi < MAXTYPES : edi++ )
            .if ( types[rdi] )
                AddLineQueueX( " %r %d, %r " R0LABEL " + 0x80000000", T_DD, edi, T_SECTIONREL, edi )
            .endif
        .endf

        ; write directory and entries for each resource

        .while 1
            .for ( eax = 0 : eax < ResIdCount : eax++ )
                .break .if ( typei[rax] )
            .endf
            .break .if ( eax == ResIdCount )
            movzx ebx,typei[rax]
            .for ( ecx = 0, eax = 0 : eax < ResIdCount : eax++ )
                .if ( bl == typei[rax] )
                    inc ecx
                .endif
            .endf
            shl ecx,16
            AddLineQueueX( R0LABEL " %r 0,0,0,0x%X", ebx, T_DD, ecx )
            .for ( edi = 0 : edi < ResIdCount : edi++ )
                .if ( bl == typei[rdi] )
                    mov typei[rdi],0
                    movsx edx,names[rdi*2]
                    add edx,RESID
                    mov ecx,edx
                    .if ( bl == RT_STRING )
                        mov ecx,StrCounter
                        add StrCounter,16
                        shr ecx,4
                        inc ecx
                    .endif
                    AddLineQueueX( " %r %d, %r " R1LABEL " + 0x80000000", T_DD, ecx, T_SECTIONREL, edx )
                .endif
            .endf
        .endw

        ; write language directory and entries

        .for ( edi = 0 : edi < ResIdCount : edi++ )
            movsx ebx,names[rdi*2]
            add ebx,RESID
            AddLineQueueX( R1LABEL " %r 0,0,0,0x10000", ebx, T_DD )
            AddLineQueueX( " %r 0x%X, %r " R2LABEL, T_DD, language, T_SECTIONREL, ebx )
        .endf
    .endif

    ; write entries

    mov rbx,PushInputStatus( &oldstat )
    .for ( rsi = MODULE.ResStack : rsi : rsi = [rsi].next )
        .if ( [rsi].type )
            mov edi,[rsi].name
            add edi,RESID
            mov dialogex,0
            AddLineQueueX( " %r 4", T_ALIGN )
            mov TokenCount,Tokenize( [rsi].line, 0, rbx, TOK_DEFAULT )
            mov eax,[rsi].hash
            .switch eax
            .case T_AVI
                WriteAvi(rbx, edi)
               .endc
            .case T_BITMAP
                WriteBitmap(rbx, edi)
               .endc
            .case T_DIALOGEX
                inc dialogex
            .case T_DIALOG
                WriteDialog(rbx, edi)
               .endc
            .case T_MENUEX
                inc dialogex
            .case T_MENU
                WriteMenu(rbx, edi)
               .endc
            .case T_CURSOR
            .case T_ICON
                WriteIcon([rbx+asm_tok].tokpos, rsi)
               .endc
            .case T_STRINGTABLE
                mov ecx,StrCounter
                add StrCounter,16
                shr ecx,4
                inc ecx
                WriteStringTable(rbx, edi, ecx)
               .endc
            .case T_ACCELERATORS
                WriteAccelerators(rbx, edi)
               .endc
            .default
                asmerr( 2008, [rbx].string_ptr )
            .endsw
        .endif
    .endf
    PopInputStatus(&oldstat)
    AddLineQueueX( ".rsrc %r", T_ENDS )
    .if ( Options.pe_exe )
        AddLineQueueX( ".hdr$2 %r %r %r 'HDR'", T_SEGMENT, T_DWORD, T_FLAT, T_PUBLIC )
        AddLineQueueX( " %r 0x5C", T_ORG )
        AddLineQueueX( " %r 2", T_DW )
        AddLineQueueX( ".hdr$2 %r", T_ENDS )
    .endif
    AddLineQueueX( "%r wstring(%r)", T_DOT_PRAGMA, T_POP )
    mov MODULE.ResStack,NULL
    mov MODULE.ResourceParsing,0
    RunLineQueue()
    .if ( !dotname )
        mov MODULE.dotname,0
    .endif
    ret
    endp
endif
    end
