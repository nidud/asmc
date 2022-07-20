
    ; 2.34.14 - align type..

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

.pragma pack(push, 8)

define LF_FACESIZE      32

tagLOGFONTW             struct
lfHeight                SDWORD ?
lfWidth                 SDWORD ?
lfEscapement            SDWORD ?
lfOrientation           SDWORD ?
lfWeight                SDWORD ?
lfItalic                BYTE ?
lfUnderline             BYTE ?
lfStrikeOut             BYTE ?
lfCharSet               BYTE ?
lfOutPrecision          BYTE ?
lfClipPrecision         BYTE ?
lfQuality               BYTE ?
lfPitchAndFamily        BYTE ?
lfFaceName              dw LF_FACESIZE dup(?)
tagLOGFONTW             ends
LOGFONTW                typedef tagLOGFONTW

NONCLIENTMETRICSW       STRUC
cbSize                  DWORD ?
iBorderWidth            SDWORD ?
iScrollWidth            SDWORD ?
iScrollHeight           SDWORD ?
iCaptionWidth           SDWORD ?
iCaptionHeight          SDWORD ?
lfCaptionFont           LOGFONTW <>
iSmCaptionWidth         SDWORD ?
iSmCaptionHeight        SDWORD ?
lfSmCaptionFont         LOGFONTW <>
iMenuWidth              SDWORD ?
iMenuHeight             SDWORD ?
lfMenuFont              LOGFONTW <>
lfStatusFont            LOGFONTW <>
lfMessageFont           LOGFONTW <>
iPaddedBorderWidth      SDWORD ?
NONCLIENTMETRICSW       ENDS

.pragma pack(pop)
.code
    mov eax,LOGFONTW
    mov eax,NONCLIENTMETRICSW
end

