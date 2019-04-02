include windows.inc
include math.inc
include DrawingObject.inc

.classdef CMyGestureEngine :ptr CDrawingObject

    _pcRect             LPCDRAWINGOBJECT ?
    _ptFirst            POINT <>
    _ptSecond           POINT <>
    _dwArguments        DWORD ?

    WndProc             proc :HWND, :WPARAM, :LPARAM
    ProcessPressAndTap  proc
    ProcessTwoFingerTap proc
    ProcessMove         proc :long_t, :long_t
    ProcessZoom         proc :double, :long_t, :long_t
    ProcessRotate       proc :double, :long_t, :long_t

    .ends