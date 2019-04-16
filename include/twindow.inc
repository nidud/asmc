ifndef __TWINDOW_INC
__TWINDOW_INC equ <>

include wincon.inc

.pragma list(push, 0)

TRECT       STRUC
x           db ?
y           db ?
col         db ?
row         db ?
TRECT       ENDS

MTRECT macro x, y, col, row
    exitm<(x or (y shl 8) or (col shl 16) or (row shl 24 ))>
    endm

_TW_ISOPEN      equ 0x01
_TW_VISIBLE     equ 0x02
_TW_MOVEABLE    equ 0x04
_TW_USESHADE    equ 0x08
_TW_USECOLOR    equ 0x10

.classdef twindow :TRECT, :uint_t

    flags       uint_t ?
    rc          TRECT <>
    window      PCHAR_INFO ?

    show        proc
    hide        proc
    read        proc :PCHAR_INFO
    write       proc :PCHAR_INFO

    move        proc :int_t, :int_t
    showsh      proc
    hidesh      proc

    clear       proc :uchar_t
    center      proc :int_t, :int_t, :int_t, :string_t
    settitle    proc :string_t

    putxyw      proc :int_t, :int_t, :int_t, :uint_t
    putxya      proc :int_t, :int_t, :int_t, :uchar_t
    putxyf      proc :int_t, :int_t, :ushort_t, :int_t, :string_t, :vararg
    putpath     proc :int_t, :int_t, :int_t, :string_t

    .ends

window_t        typedef ptr twindow

.pragma list(pop)

endif
