; OPTION.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

; options without arguments

opt( DOTNAME )
opt( NODOTNAME )
opt( M510 )
opt( NOM510 )
opt( SCOPED )
opt( NOSCOPED )
opt( OLDSTRUCTS )
opt( NOOLDSTRUCTS )
opt( EMULATOR )
opt( NOEMULATOR )
opt( LJMP )
opt( NOLJMP )
opt( READONLY )
opt( NOREADONLY )
opt( OLDMACROS )
opt( NOOLDMACROS )
opt( EXPR16 )
opt( EXPR32 )
opt( NOSIGNEXTEND )

; options with arguments

opt( CASEMAP )          ; : <NONE|..>
opt( PROC )             ; : <PRIVATE|..>
opt( PROLOGUE )         ; : <name>
opt( EPILOGUE )         ; : <name>
opt( LANGUAGE )         ; : <name>
opt( NOKEYWORD )        ; : <id>
opt( SETIF2 )           ; : <value>
opt( OFFSET )           ; ; <GROUP|..>
opt( SEGMENT )          ; : <USE16|..>

; options not compatible with Masm

opt( FIELDALIGN )       ; : <value>
opt( PROCALIGN )        ; : <value>
opt( MZ )               ; : <value>
opt( FRAME )            ; ; <AUTO> | ..
opt( ELF )              ; : <value>
opt( RENAMEKEYWORD )    ; : <id>=<>
opt( WIN64 )            ; : <value> | ..
opt( DLLIMPORT )        ; : <NONE|library>
opt( CODEVIEW )         ; : <value>
opt( STACKBASE )        ; : <reg>
opt( CSTACK )           ; ; <ON|OFF>
opt( SWITCH )           ; ; <REGAX|PASCAL|..>
opt( LOOPALIGN )        ; : <value>
opt( CASEALIGN )        ; : <value>
opt( WSTRING )          ; ; <ON|OFF>
opt( CODEPAGE )         ; : <value>
opt( FLOATFORMAT )      ; : <e|f|g>
opt( FLOATDIGITS )      ; : <value>
opt( LINESIZE )         ; : <value>
opt( FLOAT )            ; : <value>
