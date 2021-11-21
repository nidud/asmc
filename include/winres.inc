ifndef _INC_WINDOWS
include windows.inc
endif
;.pragma list(push, 0)

IDC_STATIC  equ -1

LANGID_DE   equ 0x0407
LANGID_US   equ 0x0409
LANGID_FR   equ 0x040C
LANGID_ES   equ 0x040A
LANGID_RU   equ 0x0423
LANGID_SE   equ 0x041D
LANGID_IT   equ 0x0410
LANGID_UK   equ 0x044B
LANGID_NO   equ 0x0414
LANGID_NN   equ 0x0814

RC_BUTTON   equ 0x0080
RC_EDIT     equ 0x0081
RC_STATIC   equ 0x0082
RC_LISTBOX  equ 0x0083
RC_SCROLLB  equ 0x0084
RC_COMPOBOX equ 0x0085

RCENUM1     = 0
RCENUM2     = 0
RCENUM3     = 0

RCBEGIN macro
    option dotname
    option wstring:on
    .rsrc segment dword read flat public 'RSRC'
    endm

RCTYPES macro num
    IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,num>
    RCENUM1 = 0
    RCENUM2 = 0
    RCENUM3 = 0
    endm

RCENTRY macro type
    IMAGE_RESOURCE_DIRECTORY_ENTRY < <type>, <SECTIONREL @CatStr(<@>, %RCENUM1) + 0x80000000> >
    RCENUM1 = RCENUM1 + 1
    endm

RCENUMN macro count
@CatStr(<@>, %RCENUM2) IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,count>
    RCENUM2 = RCENUM2 + 1
    RCENUM1 = 0
    endm

RCENUMX macro id
    IMAGE_RESOURCE_DIRECTORY_ENTRY < <id>, <SECTIONREL @CatStr(<@@>, %RCENUM3) + 0x80000000> >
    RCENUM3 = RCENUM3 + 1
    endm

RCLANGX macro lang
@CatStr(<@@>, %RCENUM1) IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,1>
    IMAGE_RESOURCE_DIRECTORY_ENTRY < <lang>, <SECTIONREL @CatStr(<$>, %RCENUM1)> >
    RCENUM1 = RCENUM1 + 1
    RCENUM2 = 0
    endm

MENUBEGIN macro
    @CatStr(<$>, %RCENUM2) IMAGE_RESOURCE_DATA_ENTRY <IMAGEREL @CatStr(<$$>, %RCENUM2), @CatStr(<size_$>, %RCENUM2), 0, 0>
    @CatStr(<$$>, %RCENUM2) dw 0,0
    endm
MENUNAME macro name, flags:=<0>
    dw flags or MF_POPUP,name,0
    endm
MENUITEM macro idm, name, flags:=<0>
    dw flags, idm, name,0
    endm
SEPARATOR macro
    dw 0, 0, 0
    endm
MENUEND macro
    @CatStr(@CatStr(<size_$>, %RCENUM2, < equ $ - >),<$$>, %RCENUM2)
    RCENUM2 = RCENUM2 + 1
    endm

RCDIALOG macro CodePage:=<0>
    align 4
    @CatStr(<$>, %RCENUM2) IMAGE_RESOURCE_DATA_ENTRY <IMAGEREL @CatStr(<$$>, %RCENUM2), @CatStr(<size_$>, %RCENUM2), CodePage, 0>
    @CatStr(<$$>, %RCENUM2) label byte
    endm

DLGBEGIN macro flags,items,x,y,w,h,exflags:=<0>,menu:=<0>,CodePage:=<0>
    RCDIALOG CodePage
    if exflags
     dd 0xFFFF0001, 0x00000000
     dd exflags, flags
     RCENUM3 = 1
    else
     dd flags, 0
     RCENUM3 = 0
    endif
    dw items,x,y,w,h
    if menu
     dw -1
     dd menu
    else
     dd 0
    endif
    endm

CAPTION macro name
    dw name,0
    endm

FONT macro size, name, b1:=<0>, b2:=<1>, b3:=<0>
    dw size
    if b3 ne 0
     dw b1
     db b2,b3
    elseif b2 eq 0
     dd 0
    endif
    dw name,0
    endm

RCBITMAP macro name, CodePage:=<0>
    align 4
    @CatStr(<$>, %RCENUM2) IMAGE_RESOURCE_DATA_ENTRY <IMAGEREL @CatStr(<$$>, %RCENUM2), @CatStr(<size_$>, %RCENUM2), CodePage, 0>
    @CatStr(<$$>, %RCENUM2) label byte
    incbin <name>,14
    MENUEND
    endm

RCBINARY macro name, CodePage:=<0>
    align 4
    @CatStr(<$>, %RCENUM2) IMAGE_RESOURCE_DATA_ENTRY <IMAGEREL @CatStr(<$$>, %RCENUM2), @CatStr(<size_$>, %RCENUM2), CodePage, 0>
    @CatStr(<$$>, %RCENUM2) label byte
    incbin <name>
    MENUEND
    endm

DLGITEM macro x,y,w,h,idc,name,flags,exflags:=<0>,class:=<RC_BUTTON>
    align 4
    if RCENUM3
     dd 0,exflags,flags or WS_CHILD
    else
     dd flags or WS_CHILD,0
    endif
    dw x,y,w,h,idc
    if RCENUM3
     dw 0,-1,class,name,0
    else
     dw -1,class,name,0,0
    endif
    endm

PUSHBUTTON macro name,idc,x,y,w,h,flags:=<0>
    DLGITEM x,y,w,h,idc,name,WS_VISIBLE or WS_TABSTOP or flags
    endm

DEFPUSHBUTTON macro name,idc,x,y,w,h,flags:=<0>
    PUSHBUTTON name,idc,x,y,w,h,flags or BS_DEFPUSHBUTTON
    endm

GROUPBOX macro name,idc,x,y,w,h,flags:=<0>
    DLGITEM x,y,w,h,idc,name,flags or WS_VISIBLE or BS_GROUPBOX
    endm

LTEXT macro name,idc,x,y,w,h,flags:=<0>
    DLGITEM x,y,w,h,idc,name,flags or WS_VISIBLE or WS_GROUP,0,RC_STATIC
    endm

CTEXT macro name,idc,x,y,w,h,flags:=<0>,flags2:=<0>
    DLGITEM x,y,w,h,idc,name,flags or WS_VISIBLE or WS_GROUP,0,RC_STATIC
    endm

RTEXT macro name,idc,x,y,w,h,flags:=<0>,flags2:=<0>
    DLGITEM x,y,w,h,idc,name,flags or WS_VISIBLE or WS_GROUP,0,RC_STATIC
    endm

EDITTEXT macro idc,x,y,w,h,flags:=<0>,exflags:=<0>
    DLGITEM x,y,w,h,idc,0,flags or WS_VISIBLE or WS_BORDER or WS_TABSTOP or DS_MODALFRAME,exflags,RC_EDIT
    endm

CONTROL macro name,idc,class,flags,x,y,w,h
    DLGITEM x,y,w,h,idc,name,flags or WS_VISIBLE,0,class
    endm

DLGEND macro
    MENUEND
    endm

RCEND macro
    .rsrc ends
ifdef __PE__
    .hdr$2 segment dword flat public 'HDR'
    org 0x5C
    dw 2
    .hdr$2 ends
endif
    endm

;.pragma list(pop)
