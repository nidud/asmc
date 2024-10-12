    .486
    .model flat, stdcall

includelib msvcrt0.lib

MessageBoxA proto :ptr, :ptr, :ptr, :sword

    .data
     message sbyte "Win32 gui application", 0
ifdef __ASMC__
     dltitle sbyte "ASMC + LINKW", 0
else
     dltitle sbyte "ML + LINKW", 0
endif
    .code

WinMain proc hInstance:ptr, hPrevInstance:ptr, lpCmdLine:ptr, nShowCmd:sdword

    invoke  MessageBoxA, 0, addr message, addr dltitle, 0
    xor     eax,eax
    ret

WinMain endp

    end
