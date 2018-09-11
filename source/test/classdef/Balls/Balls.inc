ifndef __GRAPHICS_INC
__GRAPHICS_INC equ <>
include wingdi.inc

MAXBALLS equ 11

.classdef Balls

    sx          SINT ?
    sy          SINT ?
    ex          SINT ?
    ey          SINT ?
    xpos        SINT ?
    ypos        SINT ?
    prevx       SINT ?
    prevy       SINT ?
    rad         SINT ?
    color       SINT ?
    speed       SINT ?
    setcolor    SINT ?

    Hide        proc
    Show        proc
    Move        proc

    .ends

_G_UPDATE       equ 0x01
_G_SUSPENDED    equ 0x02

.classdef Graphics

    flags       dd ?
    bmi         BITMAPINFO <>
    winptr      PVOID ?
    palett      RGBQUAD 256 dup(<>)
    balls       LPBALLS MAXBALLS dup(?)

    Setsize     proc :UINT, :UINT
    Update      proc
    Getmaxx     proc
    Getmaxy     proc
    Setrgb      proc :UINT, :UINT, :UINT
    Initpal     proc
    Circle      proc :UINT, :UINT, :UINT, :UINT
    Initballs   proc
    Moveballs   proc
    Hideballs   proc
    Suspend     proc
    Resume      proc

    .ends

externdef g:LPGRAPHICS

endif
