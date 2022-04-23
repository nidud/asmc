ifndef _WRL_IMPLEMENTS_H_
define _WRL_IMPLEMENTS_H_

include inspectable.inc
include roapi.inc
ifdef BUILD_WINDOWS
include winrt.inc
endif
include activation.inc
include winatring.inc

include new.inc
include weakreference.inc
include objbase.inc
include cguid.inc
include intrin.inc

include wrl\def.inc
include wrl\client.inc

if (NTDDI_VERSION GE NTDDI_WINBLUE)
include roerrorapi.inc
endif

ifndef __WRL_NO_DEFAULT_LIB__
.pragma comment(lib, ole32)
endif

.enum RuntimeClassType {
    WinRt		    = 0x0001,
    ClassicCom		    = 0x0002,
    WinRtClassicComMix	    = WinRt or ClassicCom,
    InhibitWeakReference    = 0x0004,
    Delegate		    = ClassicCom,
    InhibitFtmBase	    = 0x0008,
    InhibitRoOriginateError = 0x0010
    }

.template ModuleBase

    moduleLock_ ptr ?
    objectCount_ dd ?
    module_ ptr ModuleBase ?

    ModuleBase		  proc
    Delete		  proc
    IncrementObjectCount  proc
    DecrementObjectCount  proc
    GetObjectCount	  proc
    GetFirstEntryPointer  proc
    GetMidEntryPointer	  proc
    GetLastEntryPointer	  proc
    GetLock		  proc
    RegisterWinRTObject	  proc :ptr wchar_t, :ptr ptr wchar_t,	:ptr RO_REGISTRATION_COOKIE, :dword
    UnregisterWinRTObject proc :ptr wchar_t, :RO_REGISTRATION_COOKIE
    RegisterCOMObject	  proc :ptr wchar_t, :ptr IID, :ptr ptr IClassFactory, :ptr DWORD, :dword
    UnregisterCOMObject	  proc :ptr wchar_t, :ptr DWORD, :dword
   .ends

endif
