
;--- v2.19: fixed address prefix generation if a segment prefix is used

    .386
_DATA segment dword use32 public 'DATA'
_DATA ends
_DATA16 segment word use16 public 'DATA'
_DATA16 ends

_TEXT segment dword use32 public 'CODE'
    assume ds:_DATA
    mov ax, _DATA:[bx]
    mov ax, _DATA:[ebx]
    assume ds:_DATA16
    mov ax, _DATA16:[bx]
    mov ax, _DATA16:[ebx]
    mov ax, [bx]
    mov ax, [ebx]
_TEXT ends
_TEXT16 segment word use16 public 'CODE'
    assume ds:_DATA
    mov ax, _DATA:[bx]
    mov ax, _DATA:[ebx]
    assume ds:_DATA16
    mov ax, _DATA16:[bx]
    mov ax, _DATA16:[ebx]
    mov ax, [bx]
    mov ax, [ebx]
_TEXT16 ends
    end
