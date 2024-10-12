includelib msvcrt0.lib

MessageBoxA proto :ptr, :ptr, :ptr, :sword

    .data
     message sbyte "Win64 gui application", 0
ifdef __ASMC__
     dltitle sbyte "ASMC64 + LINKW", 0
else
     dltitle sbyte "ML64 + LINKW", 0
endif

    .code

WinMain proc hInstance:ptr, hPrevInstance:ptr, lpCmdLine:ptr, nShowCmd:sdword

  local stack[4]:qword

    xor     r9d,r9d
    lea     r8,dltitle
    lea     rdx,message
    xor     ecx,ecx
    call    MessageBoxA
    xor     eax,eax
    ret

WinMain endp

    end
