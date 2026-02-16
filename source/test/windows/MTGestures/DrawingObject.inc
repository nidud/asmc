include windows.inc
include math.inc

define MAX_COLORS 5

.class CDrawingObject

    s_colors        COLORREF MAX_COLORS dup(?)
    _iCx            long_t ?
    _iCy            long_t ?
    _iWidth         int_t ?
    _iHeight        int_t ?
    _dScalingFactor double ?
    _dRotationAngle double ?
    _bDrawDiagonals BOOL ?
    _iColorIndex    int_t ?

    CDrawingObject      proc
    Release             proc
    ResetObject         proc :int_t, :int_t
    Paint               proc :HDC
    Move                proc :long_t, :long_t
    ToggleDrawDiagonals proc
    Zoom                proc :double, :long_t, :long_t
    Rotate              proc :double, :long_t, :long_t
    ShiftColor          proc

    .ends

