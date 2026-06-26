
    .x64p
    option casemap:none

_TEXT16 segment use16 para public 'CODE'
    assume ds:_TEXT16
    assume es:_TEXT16
_TEXT16 ends

_TEXT32 segment use32 para public 'CODE'
    assume ss:FLAT
    mov word ptr ss:[0B8000h],0720h
_TEXT32 ends

_TEXT64 segment para use64 public 'CODE'
    assume ds:FLAT, es:FLAT, ss:FLAT
_TEXT64 ends

    end
