define WINVER 0x0A00
define _WIN32_WINNT 0x0A00

include windows.inc
include objbase.inc
include shobjidl.inc
include stdio.inc
include wrl\client.inc
include wrl\implements.inc
include tchar.inc

ifdef __PE__
.data
 IID_IAppVisibility  GUID _IID_IAppVisibility
 CLSID_AppVisibility GUID _CLSID_AppVisibility
 IID_IAppVisibilityEvents GUID _IID_IAppVisibilityEvents
endif

.code
;
; Simple helper function to turn a MONITOR_APP_VISIBILITY enumeration into a string
;
GetMonitorAppVisibilityString proc monitorAppVisibility:MONITOR_APP_VISIBILITY

    .switch ( ecx )
    .case MAV_NO_APP_VISIBLE
        .return &@CStr( "no apps visible" )
    .case MAV_APP_VISIBLE
        .return &@CStr( "a visible app" )
    .case MAV_UNKNOWN
    .default
        .return &@CStr( "unknown" )
    .endsw
    ret

GetMonitorAppVisibilityString endp

;
; This class will implement the IAppVisibilityEvents interface and will receive notifications
; from the AppVisibility COM object.
;
.class CAppVisibilityNotificationSubscriber : public IAppVisibilityEvents

    RefCount dd ?
    ;
    ; This variable will be used to trigger this program's message loop
    ; to exit. The variable will be incremented when the launcher becomes visible.
    ; When the launcher becomes visible five times, the program will exit.
    ;
    cLauncherChanges dd ?

    CAppVisibilityNotificationSubscriber proc
   .ends

;
; Implementation of IAppVisibilityEvents
;
    assume rcx : ptr CAppVisibilityNotificationSubscriber

CAppVisibilityNotificationSubscriber::QueryInterface proc riid:LPIID, ppv:ptr ptr

    mov rax,[rdx]
    .if ( rax == qword ptr IID_IAppVisibilityEvents || rax == 0 )

        mov [r8],rcx
        inc [rcx].RefCount
        .return NOERROR
    .endif

    xor eax,eax
    mov [r8],rax
   .return E_INVALIDARG

CAppVisibilityNotificationSubscriber::QueryInterface endp


CAppVisibilityNotificationSubscriber::AddRef proc

    lock inc [rcx].RefCount
   .return [rcx].RefCount

CAppVisibilityNotificationSubscriber::AddRef endp


CAppVisibilityNotificationSubscriber::Release proc

    lock dec [rcx].RefCount
   .return [rcx].RefCount

CAppVisibilityNotificationSubscriber::Release endp


CAppVisibilityNotificationSubscriber::AppVisibilityOnMonitorChanged proc hMonitor:HMONITOR,
        previousAppVisibility:MONITOR_APP_VISIBILITY, currentAppVisibility:MONITOR_APP_VISIBILITY

    .new prev:string_t = GetMonitorAppVisibilityString(previousAppVisibility)
    .new curr:string_t = GetMonitorAppVisibilityString(currentAppVisibility)

    _tprintf( "Monitor %p previously had %s and now has %s\n", hMonitor, prev, curr )
    .return S_OK

CAppVisibilityNotificationSubscriber::AppVisibilityOnMonitorChanged endp


CAppVisibilityNotificationSubscriber::LauncherVisibilityChange proc currentVisibleState:BOOL

    lea rdx,@CStr( "not visible" )
    .if ( currentVisibleState )
        lea rdx,@CStr( "visible" )
    .endif
    _tprintf( "The Start menu is now %s\n", rdx )
    .if ( currentVisibleState )

        mov rcx,this
        inc [rcx].cLauncherChanges
        .if ( [rcx].cLauncherChanges == 5 )
            PostQuitMessage(0)
        .endif
    .endif
    .return S_OK

CAppVisibilityNotificationSubscriber::LauncherVisibilityChange endp


CAppVisibilityNotificationSubscriber::CAppVisibilityNotificationSubscriber proc ;v:ptr

    @ComAlloc(CAppVisibilityNotificationSubscriber)
    ret

CAppVisibilityNotificationSubscriber::CAppVisibilityNotificationSubscriber endp

    assume rcx : nothing


DisplayMonitorEnumProc proc hMonitor:HMONITOR,
                            hdcMonitor:HDC,
                            lprcMonitor:LPRECT,
                            dwData:LPARAM

    .new pAppVisibility:ptr IAppVisibility = dwData

    .new monitorAppVisibility:MONITOR_APP_VISIBILITY
    .new hr:HRESULT = pAppVisibility.GetAppVisibilityOnMonitor( hMonitor, &monitorAppVisibility )
    .if (SUCCEEDED(hr))

        _tprintf( "\tMonitor %p has %s\n", hMonitor,
                GetMonitorAppVisibilityString( monitorAppVisibility ) )
    .endif
    .return TRUE

DisplayMonitorEnumProc endp


_tmain proc

    _tprintf( "Toggle Start menu visibility 5 times to exit\n" )
    ;
    ; Initialization of COM is required to use the AppVisibility (CLSID_AppVisibility) object
    ;
    .new hr:HRESULT = CoInitializeEx( NULL, COINIT_APARTMENTTHREADED )
    .if ( SUCCEEDED(hr) )
        ;
        ; Create the App Visibility component
        ;
        .new spAppVisibility:ptr IAppVisibility

        mov hr,CoCreateInstance(
                &CLSID_AppVisibility,
                NULL,
                CLSCTX_INPROC_SERVER,
                &IID_IAppVisibility,
                &spAppVisibility )

        .if ( SUCCEEDED(hr) )

            ;
            ; Enumerate the current display devices and display app visibility status
            ;

            _tprintf( "Current app visibility status is:\n" )
            EnumDisplayMonitors( NULL, NULL, &DisplayMonitorEnumProc, spAppVisibility )
            _tprintf( "\n\n" )

            ;
            ; Display the current launcher visibility
            ;
            .new launcherVisibility:BOOL
            spAppVisibility.IsLauncherVisible( &launcherVisibility )
            .if (SUCCEEDED(eax))

                lea rdx,@CStr( "not visible" )
                .if launcherVisibility
                    lea rdx,@CStr( "visible" )
                .endif
                _tprintf( "The Start menu is currently %s\n", rdx )
            .endif
            ;
            ; Create an object that implements IAppVisibilityEvents that will receive
            ; callbacks when either app visibility or Start menu visibility changes.
            ;
            .new spSubscriber:ptr CAppVisibilityNotificationSubscriber()
            ;
            ; Advise to receive change notifications from the AppVisibility object
            ; NOTE: There must be a reference held on the AppVisibility object in order to continue
            ; NOTE: receiving notifications on the implementation of the IAppVisibilityEvents object
            ;
            .new dwCookie:DWORD

            mov hr,spAppVisibility.Advise( spSubscriber, &dwCookie )

            .if (SUCCEEDED(hr))
                ;
                ; Since the visibility notifications are delivered via COM, a message loop must
                ; be employed in order to receive notifications
                ;
                .new msg:MSG
                .while ( GetMessage( &msg, NULL, 0, 0 ) )

                    DispatchMessage( &msg )
                .endw
                ;
                ; Unadvise from the AppVisibility component to stop receiving notifications
                ;
                spAppVisibility.Unadvise(dwCookie)
            .endif

        .endif
        CoUninitialize()
    .endif
    .return 0

_tmain endp

    end _tstart
