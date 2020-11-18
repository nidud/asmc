;;----------------------------------------------------------------------------
;; File: VidMemViaDDraw.asm
;;
;; This method queries the DirectDraw 7 interfaces for the amount of available
;; video memory. On a discrete video card, this is often close to the amount
;; of dedicated video memory and usually does not take into account the amount
;; of shared system memory.
;;
;;-----------------------------------------------------------------------------

include windows.inc
include winnls.inc
include string.inc
include stdio.inc
include assert.inc
include ddraw.inc

;;-----------------------------------------------------------------------------
;; Defines, and constants
;;-----------------------------------------------------------------------------
ifndef SAFE_RELEASE
SAFE_RELEASE proto p:abs {
    .if p
        p.Release()
        mov p,NULL
    .endif
    }
endif

CALLBACK(LPDIRECTDRAWCREATE, :ptr GUID, :ptr LPDIRECTDRAW, :ptr IUnknown)
MonitorEnumProc proto :HMONITOR, :HDC, :LPRECT, :LPARAM

DDRAW_MATCH     STRUC
guid            GUID <>
hMonitor        HMONITOR ?
strDriverName   SBYTE 512 dup(?)
bFound          BOOL ?
DDRAW_MATCH     ENDS

.code

DDEnumCallbackEx proc lpGUID:ptr GUID, lpDriverDescription:LPSTR,
        lpDriverName:LPSTR, lpContext:LPVOID, hm:HMONITOR

    .if( [r9].DDRAW_MATCH.hMonitor == hm )

        mov [r9].DDRAW_MATCH.bFound,TRUE
        strcpy_s( &[r9].DDRAW_MATCH.strDriverName, 512, lpDriverName )
        mov rcx,lpContext
        memcpy( &[rcx].DDRAW_MATCH.guid, lpGUID, sizeof( GUID ) )
    .endif
    .return TRUE

DDEnumCallbackEx endp


GetVideoMemoryViaDirectDraw proc hMonitor:HMONITOR, pdwAvailableVidMem:ptr DWORD

    .new pDDraw:LPDIRECTDRAW = NULL
    .new pDirectDrawEnumerateEx:LPDIRECTDRAWENUMERATEEXA = NULL
    .new hr:HRESULT
    .new bGotMemory:BOOL = FALSE

    mov DWORD ptr [rdx],0

    .new pDDCreate:LPDIRECTDRAWCREATE = NULL
    .new hInstDDraw:HINSTANCE = LoadLibrary( "ddraw.dll" )
    .if( rax )

        .new match:DDRAW_MATCH
        ZeroMemory( &match, sizeof( DDRAW_MATCH ) )
        mov match.hMonitor,hMonitor

        mov pDirectDrawEnumerateEx,GetProcAddress( hInstDDraw, "DirectDrawEnumerateExA" )
        .if rax

            mov hr,pDirectDrawEnumerateEx( &DDEnumCallbackEx, &match, DDENUM_ATTACHEDSECONDARYDEVICES )
        .endif

        mov pDDCreate,GetProcAddress( hInstDDraw, "DirectDrawCreate" )
        .if rax

            pDDCreate( &match.guid, &pDDraw, NULL )

           .new pDDraw7:LPDIRECTDRAW7
            pDDraw.QueryInterface( &IID_IDirectDraw7, &pDDraw7 )
            .if( SUCCEEDED( eax ) )

               .new ddscaps:DDSCAPS2
                ZeroMemory( &ddscaps, sizeof( DDSCAPS2 ) )
                mov ddscaps.dwCaps,DDSCAPS_VIDEOMEMORY or DDSCAPS_LOCALVIDMEM
                mov hr,pDDraw7.GetAvailableVidMem( &ddscaps, pdwAvailableVidMem, NULL )
                .if( SUCCEEDED( hr ) )
                    mov bGotMemory,TRUE
                .endif
                pDDraw7.Release()
            .endif
        .endif
        FreeLibrary( hInstDDraw )
    .endif
    xor eax,eax
    mov ecx,E_FAIL
    cmp eax,bGotMemory
    cmove eax,ecx
    ret

GetVideoMemoryViaDirectDraw endp


GetDeviceIDFromHMonitor proc hm:HMONITOR, strDeviceID:ptr WCHAR, cchDeviceID:int_t


    .new hInstDDraw:HINSTANCE = LoadLibrary( "ddraw.dll" )
    .if( rax )

       .new match:DDRAW_MATCH
        ZeroMemory( &match, sizeof( DDRAW_MATCH ) )
        mov match.hMonitor,hm

        .new pDirectDrawEnumerateEx:LPDIRECTDRAWENUMERATEEXA = GetProcAddress( hInstDDraw, "DirectDrawEnumerateExA" )
        .if( rax )
            pDirectDrawEnumerateEx( &DDEnumCallbackEx, &match, DDENUM_ATTACHEDSECONDARYDEVICES )
        .endif

        .if( match.bFound )

            .new iDevice:LONG = 0
            .new dispdev:DISPLAY_DEVICEA

            ZeroMemory( &dispdev, sizeof( dispdev ) )
            mov dispdev.cb,sizeof( dispdev )

            .while( EnumDisplayDevicesA( NULL, iDevice, &dispdev, 0 ) )

                ;; Skip devices that are monitors that echo another display

                .if( dispdev.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER )

                    inc iDevice
                    .continue
                .endif

                ;; Skip devices that aren't attached since they cause problems

                .if( !( dispdev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ) )

                    inc iDevice
                    .continue
                .endif

                .ifd ( _stricmp( &match.strDriverName, &dispdev.DeviceName ) == 0 )

                    MultiByteToWideChar( CP_ACP, 0, &dispdev.DeviceID, -1, strDeviceID, cchDeviceID )
                    .return S_OK
                .endif

                inc iDevice
            .endw
        .endif

        FreeLibrary( hInstDDraw )
    .endif

    .return E_FAIL

GetDeviceIDFromHMonitor endp

    end
