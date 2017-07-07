; CMSYSTEMINFO.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include alloc.inc
include crtl.inc
include string.inc
include stdlib.inc
include winbase.inc

ifdef _WIN95

externdef kernel32_dll:BYTE
endif
externdef IDD_DZSystemInfo:DWORD

    .data
    idleh   dd 0
    count   dd 0
    format  db "%17s",0;"%13I64d",0

    .code

UpdateMemoryStatus PROC PRIVATE USES esi edi ebx dialog
ifdef _WIN95
  local M:MEMORYSTATUS
endif
  local MS:MEMORYSTATUSEX, value[32]:BYTE

    lea edi,MS
    mov ecx,sizeof( MEMORYSTATUSEX )
    xor eax,eax
    rep stosb
    mov MS.dwLength,sizeof( MEMORYSTATUSEX )

ifdef _WIN95
    .if GetModuleHandle( addr kernel32_dll )

        .if GetProcAddress(eax, "GlobalMemoryStatusEx")

            lea  ecx,MS
            push ecx
            call eax
        .else
            GlobalMemoryStatus(addr M)

            mov eax,M.dwMemoryLoad
            mov MS.dwMemoryLoad,eax
            mov eax,M.dwTotalPhys
            mov DWORD PTR MS.ullTotalPhys,eax
            mov eax,M.dwAvailPhys
            mov DWORD PTR MS.ullAvailPhys,eax
            mov eax,M.dwTotalPageFile
            mov DWORD PTR MS.ullTotalPageFile,eax
            mov eax,M.dwAvailPageFile
            mov DWORD PTR MS.ullAvailPageFile,eax
            mov eax,M.dwTotalVirtual
            mov DWORD PTR MS.ullTotalVirtual,eax
            mov eax,M.dwAvailVirtual
            mov DWORD PTR MS.ullAvailVirtual,eax
        .endif
    .endif
else
    GlobalMemoryStatusEx(addr MS) ; min WinXP
endif
    mov esi,dialog
    mov ebx,[esi].S_DOBJ.dl_rect
    add ebx,00000D03h
    movzx edi,bh
    movzx ebx,bl
    mkbstring( addr value, MS.ullTotalPhys )
    scputf( ebx, edi, 0, 0, addr format, addr value )

    inc edi
    mov eax,DWORD PTR MS.ullTotalPhys
    mov edx,DWORD PTR MS.ullTotalPhys[4]
    sub eax,DWORD PTR MS.ullAvailPhys
    sbb edx,DWORD PTR MS.ullAvailPhys[4]
    mkbstring( addr value, edx::eax )
    scputf(ebx, edi, 0, 0, addr format, addr value)

    sub edi,1
    add ebx,18
    mkbstring( addr value, MS.ullTotalPageFile )
    scputf(ebx, edi, 0, 0, addr format, addr value)

    inc edi
    mov eax,DWORD PTR MS.ullTotalPageFile
    mov edx,DWORD PTR MS.ullTotalPageFile[4]
    sub eax,DWORD PTR MS.ullAvailPageFile
    sbb edx,DWORD PTR MS.ullAvailPageFile[4]
    mkbstring( addr value, edx::eax )
    scputf( ebx, edi, 0, 0, addr format, addr value )
    ret

UpdateMemoryStatus ENDP

sysinfoidle PROC PRIVATE

    .if count == 156

        UpdateMemoryStatus(tdialog)
        mov count,0
    .endif
    inc count
    idleh()
    ret

sysinfoidle ENDP

cmsysteminfo PROC USES esi edi ebx

  local CPU[80]:BYTE, MinorVersion, MajorVersion

    mov edi,sselevel
    GetSSELevel()
    mov sselevel,edi
    mov ebx,eax
    xor edi,edi
    mov count,edi

    .if rsopen(IDD_DZSystemInfo)

        mov esi,eax
        mov edx,[esi].S_DOBJ.dl_wp
        mov cl,'x'
        mov eax,ebx

        .if eax & SSE_AVXOS
            mov [edx+906+252],cl
        .endif
        .if eax & SSE_AVX2
            mov [edx+982+252],cl
        .endif
        .if eax & SSE_AVX
            mov [edx+856+252],cl
        .endif
        .if eax & SSE_SSE42
            mov [edx+730+252],cl
        .endif
        .if eax & SSE_SSE41
            mov [edx+604+252],cl
        .endif
        .if eax & SSE_SSSE3
            mov [edx+960+252],cl
        .endif
        .if eax & SSE_SSE3
            mov [edx+834+252],cl
        .endif
        .if eax & SSE_SSE2
            mov [edx+708+252],cl
        .endif
        .if eax & SSE_SSE
            mov [edx+582+252],cl
        .endif

        dlshow(esi)
        .if GetModuleHandle("kernel32.dll")
            add     eax,[eax].IMAGE_DOS_HEADER.e_lfanew
            movzx   ecx,[eax].IMAGE_NT_HEADERS.OptionalHeader.MajorOperatingSystemVersion
            movzx   edx,[eax].IMAGE_NT_HEADERS.OptionalHeader.MinorOperatingSystemVersion
            mov     MajorVersion,ecx
            mov     MinorVersion,edx
            mov     dh,cl
            .switch edx
              .case _WIN32_WINNT_NT4:     mov eax,@CStr( "NT4" ):   .endc
              .case _WIN32_WINNT_WIN2K:   mov eax,@CStr( "2K" ):    .endc
              .case _WIN32_WINNT_WINXP:   mov eax,@CStr( "XP" ):    .endc
              .case _WIN32_WINNT_WS03:    mov eax,@CStr( "WS03" ):  .endc
              .case _WIN32_WINNT_VISTA:   mov eax,@CStr( "VISTA" ): .endc
              .case _WIN32_WINNT_WIN7:    mov eax,@CStr( "7" ):     .endc
              .case _WIN32_WINNT_WIN8:    mov eax,@CStr( "8" ):     .endc
              .case _WIN32_WINNT_WINBLUE: mov eax,@CStr( "BLUE" ):  .endc
              .case _WIN32_WINNT_WIN10:   mov eax,@CStr( "10" ):    .endc
              .default
                mov eax,@CStr( "10+" )
            .endsw
            movzx   ecx,[esi].S_DOBJ.dl_rect.rc_x
            movzx   edx,[esi].S_DOBJ.dl_rect.rc_y
            add     ecx,4
            add     edx,2
            scputf( ecx, edx, 0, 0, "Windows %s Version %d.%d", eax, MajorVersion, MinorVersion)
        .endif

        .if ebx

            .686
            .xmm

            push esi
            lea  edi,CPU
            xor  esi,esi
            .repeat
                lea eax,[esi+80000002h]
                cpuid
                mov [edi],eax
                mov [edi+4],ebx
                mov [edi+8],ecx
                mov [edi+12],edx
                add edi,16
                inc esi
            .until esi == 3
            lea edi,CPU
            mov esi,edi
            mov ecx,3*16
            lodsb
            .repeat
                .if !(al == ' ' && al == [esi])
                    stosb
                .endif
                lodsb
            .untilcxz
            mov [edi],cl
            pop esi
            mov ebx,[esi].S_DOBJ.dl_rect
            mov cl,bh
            add bl,4
            add cl,4
            scputs(ebx, ecx, 0, 0, &CPU)
        .endif

        UpdateMemoryStatus(esi)
        __coreleft()

        mov edi,ecx
        sub ecx,eax
        mov ebx,ecx
        xor eax,eax
        mkbstring(addr CPU, eax::edi)
        mov ecx,[esi].S_DOBJ.dl_rect
        mov dl,ch
        add cl,39
        add dl,13
        scputf(ecx, edx, 0, 0, "%15s", addr CPU)

        xor eax,eax
        mkbstring(addr CPU, eax::ebx)
        mov ecx,[esi].S_DOBJ.dl_rect
        mov dl,ch
        add cl,39
        add dl,14
        scputf(ecx, edx, 0, 0, "%15s", addr CPU)

        mov eax,tdidle
        mov tdidle,sysinfoidle
        mov idleh,eax
        dlmodal(esi)
        mov ecx,idleh
        mov tdidle,ecx
    .endif
    ret

cmsysteminfo ENDP

    END
