
.class Object

    rc          RECT <>
    pos         POINT <>
    old         POINT <>
    count       UINT ?
    radius      SINT ?
    color       SINT ?
    speed       SINT ?
    random      proc local :UINT

    Object      proc
    Release     proc
    Hide        proc
    Show        proc
    Move        proc
    Init        proc :UINT, :UINT
    Draw        proc :UINT

    .ends


MAXOBJECTS      equ 100
_G_UPDATE       equ 0x01
_G_SUSPENDED    equ 0x02


.class Graphics

    flags       dd ?
    bcount      dd ?
    bmi         BITMAPINFO <>
    winptr      PVOID ?
    palett      RGBQUAD 256 dup(<>)
    object      LPOBJECT MAXOBJECTS dup(?)

    Graphics    proc
    Release     proc
    Setsize     proc :UINT, :UINT
    Update      proc
    Getmaxx     proc
    Getmaxy     proc
    Setrgb      proc :UINT, :UINT, :UINT
    Initpal     proc
    Suspend     proc
    Resume      proc
    Line        proc :UINT, :UINT, :UINT, :UINT, :UINT
    InitObjects proc
    MoveObjects proc
    HideObjects proc

    .ends

externdef g:LPGRAPHICS

