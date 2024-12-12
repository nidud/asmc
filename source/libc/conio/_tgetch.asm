; _TGETCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include malloc.inc
include tchar.inc
ifdef __UNIX__
include sys/ioctl.inc
elseifdef __TTY__
include winnls.inc
endif

define EOF (-1)

ifdef __TTY__

.data
 inbuf db 32 dup(0)
 chptr string_t 0
 count int_t 0

;
; This is the one character push-back buffer used by _getch(), _getche()
; and _ungetch().
;
chbuf int_t EOF

.code

_gettch proc

    .if ( chbuf != EOF )

        movzx eax,byte ptr chbuf
        mov chbuf,EOF
       .return
    .endif

    .if ( count == 0 )

        .if ( _coninpfd == -1 )

            .return( EOF )
        .endif
        lea rcx,inbuf
        mov chptr,rcx
ifdef __UNIX__
        mov count,_read(_coninpfd, rcx, sizeof(inbuf))
else
        .new wc[sizeof(inbuf)/2-1]:wchar_t
        .new n:int_t
        .ifd ReadConsoleW( _coninpfh, &wc, lengthof(wc), &n, NULL)
            mov count,WideCharToMultiByte(CP_UTF8, 0, &wc, n, chptr, sizeof(inbuf), NULL, NULL)
        .endif
endif
        .if ( eax == 0 )

            .return( EOF )
        .endif
    .endif
    dec count
    mov rdx,chptr
    movzx eax,byte ptr [rdx]
    inc rdx
    mov chptr,rdx
    ret

_gettch endp

_kbhit proc

    .new NumPending:DWORD

    .if ( count || chbuf != EOF )

        .return( 1 )
    .endif
ifdef __UNIX__
    .ifd !ioctl( _coninpfd, FIONREAD, &NumPending )
else
    .ifd GetNumberOfConsoleInputEvents( _coninpfh, &NumPending )
endif
        .if ( NumPending )

            .return( 1 )
        .endif
    .endif
    xor eax,eax
    ret

_kbhit endp

else

_getextendedkeycode proto private :ptr KEY_EVENT_RECORD

.template CharPair
    LeadChar    db ?
    SecondChar  db ?
   .ends

.template EnhKeyVals
    ScanCode    dw ?
    RegChars    CharPair <>
    ShiftChars  CharPair <>
    CtrlChars   CharPair <>
    AltChars    CharPair <>
   .ends

.template NormKeyVals
    RegChars    CharPair <>
    ShiftChars  CharPair <>
    CtrlChars   CharPair <>
    AltChars    CharPair <>
   .ends

.data

;
; Table of key values for enhanced keys
;
EnhancedKeys EnhKeyVals \
        { 28, {  13,   0 }, {  13,   0 }, {  10,   0 }, {   0, 166 } }, ; Enter
        { 53, {  47,   0 }, {  63,   0 }, {   0, 149 }, {   0, 164 } }, ; /
        { 71, { 224,  71 }, { 224,  71 }, { 224, 119 }, {   0, 151 } }, ; Home
        { 72, { 224,  72 }, { 224,  72 }, { 224, 141 }, {   0, 152 } }, ; Up
        { 73, { 224,  73 }, { 224,  73 }, { 224, 134 }, {   0, 153 } }, ; PgUp
        { 75, { 224,  75 }, { 224,  75 }, { 224, 115 }, {   0, 155 } }, ; Left
        { 77, { 224,  77 }, { 224,  77 }, { 224, 116 }, {   0, 157 } }, ; Right
        { 79, { 224,  79 }, { 224,  79 }, { 224, 117 }, {   0, 159 } }, ; End
        { 80, { 224,  80 }, { 224,  80 }, { 224, 145 }, {   0, 160 } }, ; Down
        { 81, { 224,  81 }, { 224,  81 }, { 224, 118 }, {   0, 161 } }, ; PgDn
        { 82, { 224,  82 }, { 224,  82 }, { 224, 146 }, {   0, 162 } }, ; Ins
        { 83, { 224,  83 }, { 224,  83 }, { 224, 147 }, {   0, 163 } }  ; Del

;
; macro for the number of elements of in EnhancedKeys[]
;
define NUM_EKA_ELTS  lengthof(EnhancedKeys)

;
; Table of key values for normal keys. Note that the table is padded so
; that the key scan code serves as an index into the table.
;
NormalKeys NormKeyVals \
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; 0
        {  {  27,   0 }, {  27,   0 }, {  27,   0 }, {   0,   1 } },
        {  {  49,   0 }, {  33,   0 }, {   0,   0 }, {   0, 120 } },
        {  {  50,   0 }, {  64,   0 }, {   0,   3 }, {   0, 121 } },
        {  {  51,   0 }, {  35,   0 }, {   0,   0 }, {   0, 122 } },
        {  {  52,   0 }, {  36,   0 }, {   0,   0 }, {   0, 123 } },
        {  {  53,   0 }, {  37,   0 }, {   0,   0 }, {   0, 124 } },
        {  {  54,   0 }, {  94,   0 }, {  30,   0 }, {   0, 125 } },
        {  {  55,   0 }, {  38,   0 }, {   0,   0 }, {   0, 126 } },
        {  {  56,   0 }, {  42,   0 }, {   0,   0 }, {   0, 127 } },
        {  {  57,   0 }, {  40,   0 }, {   0,   0 }, {   0, 128 } },    ; 10
        {  {  48,   0 }, {  41,   0 }, {   0,   0 }, {   0, 129 } },
        {  {  45,   0 }, {  95,   0 }, {  31,   0 }, {   0, 130 } },
        {  {  61,   0 }, {  43,   0 }, {   0,   0 }, {   0, 131 } },
        {  {   8,   0 }, {   8,   0 }, { 127,   0 }, {   0,  14 } },
        {  {   9,   0 }, {   0,  15 }, {   0, 148 }, {   0,  15 } },
        {  { 113,   0 }, {  81,   0 }, {  17,   0 }, {   0,  16 } },
        {  { 119,   0 }, {  87,   0 }, {  23,   0 }, {   0,  17 } },
        {  { 101,   0 }, {  69,   0 }, {   5,   0 }, {   0,  18 } },
        {  { 114,   0 }, {  82,   0 }, {  18,   0 }, {   0,  19 } },
        {  { 116,   0 }, {  84,   0 }, {  20,   0 }, {   0,  20 } },    ; 20
        {  { 121,   0 }, {  89,   0 }, {  25,   0 }, {   0,  21 } },
        {  { 117,   0 }, {  85,   0 }, {  21,   0 }, {   0,  22 } },
        {  { 105,   0 }, {  73,   0 }, {   9,   0 }, {   0,  23 } },
        {  { 111,   0 }, {  79,   0 }, {  15,   0 }, {   0,  24 } },
        {  { 112,   0 }, {  80,   0 }, {  16,   0 }, {   0,  25 } },
        {  {  91,   0 }, { 123,   0 }, {  27,   0 }, {   0,  26 } },
        {  {  93,   0 }, { 125,   0 }, {  29,   0 }, {   0,  27 } },
        {  {  13,   0 }, {  13,   0 }, {  10,   0 }, {   0,  28 } },
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {  97,   0 }, {  65,   0 }, {   1,   0 }, {   0,  30 } },    ; 30
        {  { 115,   0 }, {  83,   0 }, {  19,   0 }, {   0,  31 } },
        {  { 100,   0 }, {  68,   0 }, {   4,   0 }, {   0,  32 } },
        {  { 102,   0 }, {  70,   0 }, {   6,   0 }, {   0,  33 } },
        {  { 103,   0 }, {  71,   0 }, {   7,   0 }, {   0,  34 } },
        {  { 104,   0 }, {  72,   0 }, {   8,   0 }, {   0,  35 } },
        {  { 106,   0 }, {  74,   0 }, {  10,   0 }, {   0,  36 } },
        {  { 107,   0 }, {  75,   0 }, {  11,   0 }, {   0,  37 } },
        {  { 108,   0 }, {  76,   0 }, {  12,   0 }, {   0,  38 } },
        {  {  59,   0 }, {  58,   0 }, {   0,   0 }, {   0,  39 } },
        {  {  39,   0 }, {  34,   0 }, {   0,   0 }, {   0,  40 } },    ; 40
        {  {  96,   0 }, { 126,   0 }, {   0,   0 }, {   0,  41 } },
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {  92,   0 }, { 124,   0 }, {  28,   0 }, {   0,   0 } },
        {  { 122,   0 }, {  90,   0 }, {  26,   0 }, {   0,  44 } },
        {  { 120,   0 }, {  88,   0 }, {  24,   0 }, {   0,  45 } },
        {  {  99,   0 }, {  67,   0 }, {   3,   0 }, {   0,  46 } },
        {  { 118,   0 }, {  86,   0 }, {  22,   0 }, {   0,  47 } },
        {  {  98,   0 }, {  66,   0 }, {   2,   0 }, {   0,  48 } },
        {  { 110,   0 }, {  78,   0 }, {  14,   0 }, {   0,  49 } },
        {  { 109,   0 }, {  77,   0 }, {  13,   0 }, {   0,  50 } },    ; 50
        {  {  44,   0 }, {  60,   0 }, {   0,   0 }, {   0,  51 } },
        {  {  46,   0 }, {  62,   0 }, {   0,   0 }, {   0,  52 } },
        {  {  47,   0 }, {  63,   0 }, {   0,   0 }, {   0,  53 } },
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {  42,   0 }, {   0,   0 }, { 114,   0 }, {   0,   0 } },
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {  32,   0 }, {  32,   0 }, {  32,   0 }, {  32,   0 } },
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {   0,  59 }, {   0,  84 }, {   0,  94 }, {   0, 104 } },
        {  {   0,  60 }, {   0,  85 }, {   0,  95 }, {   0, 105 } },    ; 60
        {  {   0,  61 }, {   0,  86 }, {   0,  96 }, {   0, 106 } },
        {  {   0,  62 }, {   0,  87 }, {   0,  97 }, {   0, 107 } },
        {  {   0,  63 }, {   0,  88 }, {   0,  98 }, {   0, 108 } },
        {  {   0,  64 }, {   0,  89 }, {   0,  99 }, {   0, 109 } },
        {  {   0,  65 }, {   0,  90 }, {   0, 100 }, {   0, 110 } },
        {  {   0,  66 }, {   0,  91 }, {   0, 101 }, {   0, 111 } },
        {  {   0,  67 }, {   0,  92 }, {   0, 102 }, {   0, 112 } },
        {  {   0,  68 }, {   0,  93 }, {   0, 103 }, {   0, 113 } },
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; 70
        {  {   0,  71 }, {  55,   0 }, {   0, 119 }, {   0,   0 } },
        {  {   0,  72 }, {  56,   0 }, {   0, 141 }, {   0,   0 } },
        {  {   0,  73 }, {  57,   0 }, {   0, 132 }, {   0,   0 } },
        {  {   0,   0 }, {  45,   0 }, {   0,   0 }, {   0,   0 } },
        {  {   0,  75 }, {  52,   0 }, {   0, 115 }, {   0,   0 } },
        {  {   0,   0 }, {  53,   0 }, {   0,   0 }, {   0,   0 } },
        {  {   0,  77 }, {  54,   0 }, {   0, 116 }, {   0,   0 } },
        {  {   0,   0 }, {  43,   0 }, {   0,   0 }, {   0,   0 } },
        {  {   0,  79 }, {  49,   0 }, {   0, 117 }, {   0,   0 } },
        {  {   0,  80 }, {  50,   0 }, {   0, 145 }, {   0,   0 } },    ; 80
        {  {   0,  81 }, {  51,   0 }, {   0, 118 }, {   0,   0 } },
        {  {   0,  82 }, {  48,   0 }, {   0, 146 }, {   0,   0 } },
        {  {   0,  83 }, {  46,   0 }, {   0, 147 }, {   0,   0 } },
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  { 224, 133 }, { 224, 135 }, { 224, 137 }, { 224, 139 } },
        {  { 224, 134 }, { 224, 136 }, { 224, 138 }, { 224, 140 } }     ; 88


 ;
 ; This is the one character push-back buffer used by _getch(), _getche()
 ; and _ungetch().
 ;
 chbuf int_t EOF

.code

_gettch proc uses rbx

    .new ConInpRec:INPUT_RECORD
    .new c:int_t = 0
    .new oldstate:DWORD
    .new NumRead:DWORD

    .if ( chbuf != EOF )

        movzx eax,TCHAR ptr chbuf
        mov chbuf,EOF
       .return
    .endif

    .if ( _coninpfd == -1 )
        .return EOF
    .endif

    ; Switch to raw mode (no line input, no echo input)

    GetConsoleMode(_coninpfh, &oldstate)
    SetConsoleMode(_coninpfh, 0)

    .for ( : : )

        .ifd ( ReadConsoleInput( _coninpfh, &ConInpRec, 1, &NumRead ) == 0 || NumRead == 0 )

            mov c,EOF
           .break
        .endif

        .if ( ConInpRec.EventType == KEY_EVENT && ConInpRec.Event.KeyEvent.bKeyDown )

            movzx eax,TCHAR ptr ConInpRec.Event.KeyEvent.uChar.UnicodeChar
            .if ( eax )

                mov c,eax
               .break
            .endif

            .if _getextendedkeycode( &ConInpRec.Event.KeyEvent )

                movzx ecx,[rax].CharPair.LeadChar
                movzx eax,[rax].CharPair.SecondChar
                mov chbuf,eax
                mov c,ecx
               .break
            .endif
        .endif
    .endf
    SetConsoleMode(_coninpfh, oldstate)
   .return( c )

_gettch endp


_gettche proc

    .new c:int_t

    .if ( chbuf != EOF )

        mov eax,chbuf
        mov chbuf,EOF
       .return
    .endif

    mov c,_gettch()
    .if ( c != EOF )
        .if ( _puttch(c) != EOF )
            .return( c )
        .endif
    .endif
    .return EOF

_gettche endp


_kbhit proc uses rbx
ifdef __UNIX__
    .return( FALSE )
else
    .new NumPending:DWORD
    .new NumPeeked:DWORD
    .new retval:int_t = FALSE
    .new pIRBuf:PINPUT_RECORD = NULL

    .if ( chbuf != -1 )
        .return TRUE
    .endif

    GetNumberOfConsoleInputEvents( _coninpfh, &NumPending )

    .if ( ( _coninpfh == -1 ) || !eax || ( NumPending == 0 ) )

        .return FALSE
    .endif

    mov pIRBuf,_calloca(NumPending, sizeof(INPUT_RECORD))

    .if ( rax == NULL )

        .return FALSE
    .endif

    mov ecx,PeekConsoleInput( _coninpfh, pIRBuf, NumPending, &NumPeeked )

    .if ( ecx && ( NumPeeked != 0 ) && ( NumPeeked <= NumPending ) )

        assume rbx:PINPUT_RECORD
        .for ( rbx = pIRBuf : NumPeeked > 0 : NumPeeked--, rbx += INPUT_RECORD )

            .if ( [rbx].EventType == KEY_EVENT && [rbx].Event.KeyEvent.bKeyDown )

                .if ( [rbx].Event.KeyEvent.uChar.AsciiChar )
                    mov retval,TRUE
                    .break
                .elseifd _getextendedkeycode( &[rbx].Event.KeyEvent )
                    mov retval,TRUE
                    .break
                .endif
            .endif
        .endf
    .endif
    _freea( pIRBuf )
    .return retval
endif
_kbhit endp

_getextendedkeycode proc private pKE:ptr KEY_EVENT_RECORD

   .new i:int_t
    ldr rcx,pKE

    assume rcx:ptr KEY_EVENT_RECORD

    .if ( [rcx].dwControlKeyState & ENHANCED_KEY )

        assume rdx:ptr EnhKeyVals
        lea rdx,EnhancedKeys

        .for ( i = 0 : i < NUM_EKA_ELTS : i++, rdx += EnhKeyVals )

            .if ( [rdx].ScanCode == [rcx].wVirtualScanCode )

                mov eax,[rcx].dwControlKeyState
                .switch
                .case ( eax & ( LEFT_ALT_PRESSED or RIGHT_ALT_PRESSED ) )
                    lea rax,[rdx].AltChars
                   .endc
                .case ( eax & ( LEFT_CTRL_PRESSED or RIGHT_CTRL_PRESSED ) )
                    lea rax,[rdx].CtrlChars
                   .endc
                .case ( eax & SHIFT_PRESSED )
                    lea rax,[rdx].ShiftChars
                   .endc
                .default
                    lea rax,[rdx].RegChars
                .endsw
                .break
            .endif
            xor eax,eax
        .endf

    .else

        mov     edx,[rcx].dwControlKeyState
        movzx   ecx,[rcx].wVirtualScanCode
        imul    eax,ecx,NormKeyVals
        lea     rcx,NormalKeys
        add     rcx,rax
        assume  rcx:ptr NormKeyVals

        .switch
        .case ( edx & ( LEFT_ALT_PRESSED or RIGHT_ALT_PRESSED ) )
            lea rax,[rcx].AltChars
           .endc
        .case ( edx & (LEFT_CTRL_PRESSED or RIGHT_CTRL_PRESSED) )
            lea rax,[rcx].CtrlChars
           .endc
        .case ( edx & SHIFT_PRESSED )
            lea rax,[rcx].ShiftChars
           .endc
        .default
            lea rax,[rcx].RegChars
        .endsw
        .if ( ( [rax].CharPair.LeadChar != 0 && [rax].CharPair.LeadChar != 224 ) ||
                [rax].CharPair.SecondChar == 0 )
            xor eax,eax
        .endif
    .endif
    ret

_getextendedkeycode endp

endif

_ungettch proc c:int_t

    ldr ecx,c

    mov eax,EOF
    .if ( eax != ecx && eax == chbuf )

        movzx eax,cl
        mov chbuf,eax
    .endif
    ret

_ungettch endp


_kbflush proc

    mov chbuf,EOF
ifdef __TTY__
    mov count,0
endif
    ret

_kbflush endp

    end
