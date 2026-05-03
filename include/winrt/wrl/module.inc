ifndef _WRL_MODULE_H_
define _WRL_MODULE_H_

include roapi.inc
ifdef BUILD_WINDOWS
include winrt.inc
endif
include activation.inc
include WinString.inc
include intrin.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

include wrl\def.inc
include wrl\internal.inc
include wrl\client.inc
include wrl\implements.inc
include wrl\ftm.inc
include wrl\wrappers\corewrappers.inc

.enum ModuleType {
    InProc		     = 0x1,
    OutOfProc		     = 0x2,
    DisableCaching	     = 0x4,
    InProcDisableCaching     = InProc or DisableCaching,
    OutOfProcDisableCaching  = OutOfProc or DisableCaching
    }

.enum FactoryCacheFlags {
    FactoryCacheDefault,
    FactoryCacheEnabled,
    FactoryCacheDisabled
    }

.template FactoryCache
    factory		ptr IUnknown ?
    union cookie
     winrt		RO_REGISTRATION_COOKIE ?
     com		dd ?
    ends
   .ends

.template CreatorMap
    factoryCreator	proc local :ptr dword, :ptr, :REFIID, :ptr ptr IUnknown
    union activationId
     clsid ptr		IID ?
     getRuntimeName	proc local
    ends
    getTrustLevel	proc local
    factoryCache	ptr FactoryCache ?
    serverName		ptr wchar_t ?
   .ends

.class FactoryBase
   .ends


IsServerNameEqual proto entry:ptr CreatorMap, serverName:ptr wchar_t


.class Module : public ModuleBase

    Module		 proc
    Release		 proc
    Create		 proc :ModuleType
    GetActivationFactory proc :HSTRING, :ptr ptr IActivationFactory, :ptr wchar_t
    GetClassObject	 proc :REFCLSID, :REFIID, :ptr ptr, :ptr wchar_t
    Terminate		 proc :ptr wchar_t, :BOOL
   .ends

endif
