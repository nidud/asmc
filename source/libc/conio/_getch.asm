; _GETCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

define EOF (-1)

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
        { 28, {  13,   0 }, {  13,   0 }, {  10,   0 }, {   0, 166 } },
        { 53, {  47,   0 }, {  63,   0 }, {   0, 149 }, {   0, 164 } },
        { 71, { 224,  71 }, { 224,  71 }, { 224, 119 }, {   0, 151 } },
        { 72, { 224,  72 }, { 224,  72 }, { 224, 141 }, {   0, 152 } },
        { 73, { 224,  73 }, { 224,  73 }, { 224, 134 }, {   0, 153 } },
        { 75, { 224,  75 }, { 224,  75 }, { 224, 115 }, {   0, 155 } },
        { 77, { 224,  77 }, { 224,  77 }, { 224, 116 }, {   0, 157 } },
        { 79, { 224,  79 }, { 224,  79 }, { 224, 117 }, {   0, 159 } },
        { 80, { 224,  80 }, { 224,  80 }, { 224, 145 }, {   0, 160 } },
        { 81, { 224,  81 }, { 224,  81 }, { 224, 118 }, {   0, 161 } },
        { 82, { 224,  82 }, { 224,  82 }, { 224, 146 }, {   0, 162 } },
        { 83, { 224,  83 }, { 224,  83 }, { 224, 147 }, {   0, 163 } }

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
        {  {    0,  0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
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
        {  {    0,  0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; Padding
        {  {    0,  0 }, {   0,   0 }, {   0,   0 }, {   0,   0 } },    ; 70
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

_getextendedkeycode proto private :ptr KEY_EVENT_RECORD


_getch proc

   .new c:int_t

;   _mlock(_CONIO_LOCK)

    mov c,_getch_nolock()

;   _munlock(_CONIO_LOCK)
   .return( c )

_getch endp


_getche proc

   .new c:int_t

;   _mlock(_CONIO_LOCK)

    mov c,_getche_nolock()

;   _munlock(_CONIO_LOCK)
   .return( c )

_getche endp


_getch_nolock proc uses rbx rdi rsi

    .new ConInpRec:INPUT_RECORD
    .new NumRead:DWORD
    .new c:int_t = 0    ; single character buffer
    .new oldstate:DWORD

    ; check pushback buffer (chbuf) a for character

    .if ( chbuf != EOF )

        ; something there, clear buffer and return the character.

        movzx eax,byte ptr chbuf
        mov chbuf,EOF
       .return
    .endif

    ; _coninpfh, the handle to the console input, is created the first
    ; time that either _getch() or _cgets() or _kbhit() is called.

    .if ( _coninpfh == -1 )
        .return EOF
    .endif

    ; Switch to raw mode (no line input, no echo input)

    GetConsoleMode( _coninpfh, &oldstate )
    SetConsoleMode( _coninpfh, 0 )

    .for ( : : )

        ; Get a console input event.

        ReadConsoleInput( _coninpfh, &ConInpRec, 1, &NumRead )

        .if ( !eax || ( NumRead == 0 ) )

            mov c,EOF
            .break
        .endif

        ; Look for, and decipher, key events.

        .if ( ( ConInpRec.EventType == KEY_EVENT ) && ConInpRec.Event.KeyEvent.bKeyDown )

            ; Easy case: if uChar.AsciiChar is non-zero, just stuff it into ch and quit.

            movzx eax,ConInpRec.Event.KeyEvent.uChar.AsciiChar
            .if ( eax )

                mov c,eax
               .break
            .endif

            ; Hard case: either an extended code or an event which should
            ; not be recognized. let _getextendedkeycode() do the work...

            .if _getextendedkeycode( &ConInpRec.Event.KeyEvent )

                movzx ecx,[rax].CharPair.LeadChar
                movzx eax,[rax].CharPair.SecondChar
                mov chbuf,eax
               .break
            .endif
        .endif
    .endf

    ; Restore previous console mode.

    SetConsoleMode( _coninpfh, oldstate )
   .return( c )

_getch_nolock endp


_getche_nolock proc

    .new c:int_t ; character read

    ; check pushback buffer (chbuf) a for character. if found, return
    ; it without echoing.

    .if ( chbuf != EOF )

        ; something there, clear buffer and return the character.

        movzx eax,byte ptr chbuf
        mov chbuf,EOF
       .return
    .endif

    mov c,_getch_nolock() ; read character

    .if ( c != EOF )
        .if ( _putch_nolock(c) != EOF )
            .return( c ) ; if no error, return char
        .endif
    .endif
    .return EOF ; get or put failed, return EOF

_getche_nolock endp


_kbhit proc uses rbx

    .new NumPending:DWORD
    .new NumPeeked:DWORD
    .new retval:int_t = FALSE
    .new pIRBuf:PINPUT_RECORD = NULL

    ; if a character has been pushed back, return TRUE

    .if ( chbuf != -1 )
        .return TRUE
    .endif

    ; Peek all pending console events

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

        ; Scan all of the peeked events to determine if any is a key event
        ; which should be recognized.

        assume rbx:PINPUT_RECORD
        .for ( rbx = pIRBuf : NumPeeked > 0 : NumPeeked--, rbx += INPUT_RECORD )

            .if ( [rbx].EventType == KEY_EVENT && [rbx].Event.KeyEvent.bKeyDown )

                ; Key event corresponding to an ASCII character or an
                ; extended code. In either case, success!

                .if ( [rbx].Event.KeyEvent.uChar.AsciiChar )
                    mov retval,TRUE
                .elseif _getextendedkeycode( &[rbx].Event.KeyEvent )
                    mov retval,TRUE
                .endif
            .endif
        .endf
    .endif
    _freea( pIRBuf )
    .return retval

_kbhit endp


_ungetch proc c:int_t

ifndef _WIN64
    mov ecx,c
endif

    ; Fail if the char is EOF or the pushback buffer is non-empty

    .if ( ( ecx == EOF ) || ( chbuf != EOF ) )
        .return EOF
    .endif
    movzx eax,cl
    mov chbuf,eax
    ret

_ungetch endp


_getextendedkeycode proc private uses rsi rdi rbx pKE:ptr KEY_EVENT_RECORD

    .new CKS:DWORD          ; hold dwControlKeyState value
    .new pCP:ptr CharPair   ; pointer to CharPair containing extended code
    .new i:int_t

ifndef _WIN64
    mov ecx,pKE
endif

    assume rcx:ptr KEY_EVENT_RECORD
    mov edi,[rcx].dwControlKeyState

    .if ( edi & ENHANCED_KEY )

        ; Find the appropriate entry in EnhancedKeys[]

        assume rdx:ptr EnhKeyVals
        lea rdx,EnhancedKeys

        .for ( rsi = NULL, ebx = 0 : ebx < NUM_EKA_ELTS : ebx++, rdx += EnhKeyVals )

            .if ( [rdx].ScanCode == [rcx].wVirtualScanCode )

                .if ( edi & ( LEFT_ALT_PRESSED or RIGHT_ALT_PRESSED ) )

                    lea rsi,[rdx].AltChars

                .elseif ( edi & ( LEFT_CTRL_PRESSED or RIGHT_CTRL_PRESSED ) )

                    lea rsi,[rdx].CtrlChars

                .elseif ( CKS & SHIFT_PRESSED)

                    lea rsi,[rdx].ShiftChars
                .else
                    lea rsi,[rdx].RegChars
                .endif
                .break
            .endif
        .endf

    .else

        ; Regular key or a keyboard event which shouldn't be recognized.
        ; Determine which by getting the proper field of the proper
        ; entry in NormalKeys[], and examining the extended code.

        movzx ecx,[rcx].wVirtualScanCode
        imul eax,ecx,NormKeyVals
        lea rcx,NormalKeys
        add rcx,rax

        assume rcx:ptr NormKeyVals

        .if ( edi & ( LEFT_ALT_PRESSED or RIGHT_ALT_PRESSED ) )

            lea rsi,[rcx].AltChars

        .elseif ( edi & (LEFT_CTRL_PRESSED or RIGHT_CTRL_PRESSED) )

            lea rsi,[rcx].CtrlChars

        .elseif ( edi & SHIFT_PRESSED )

            lea rsi,[rcx].ShiftChars
        .else
            lea rsi,[rcx].RegChars
        .endif

        .if ( ( [rsi].CharPair.LeadChar != 0 && [rsi].CharPair.LeadChar != 224 ) ||
                [rsi].CharPair.SecondChar == 0 )

            ; Must be a keyboard event which should not be recognized
            ; (e.g., shift key was pressed)

            xor esi,esi
        .endif
    .endif
    .return(rsi)

_getextendedkeycode endp

    end
