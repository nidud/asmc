
    .x64p
    option casemap:none

_TEXT16 segment use16 para public 'CODE'
    assume ds:FLAT                   ;added in v2.15 (why is this needed?)
    mov word ptr ds:[0B8000h],0720h
_TEXT16 ends

_TEXT32 segment use32 para public 'CODE'
    mov word ptr ds:[0B8000h],0720h
_TEXT32 ends

_TEXT64 segment para use64 public 'CODE'
_TEXT64 ends

    end
