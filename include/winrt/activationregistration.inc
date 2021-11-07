ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __activationregistration_h__
define __activationregistration_h__

include Inspectable.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace Foundation

.enum RegistrationScope {
    RegistrationScope_PerMachine,
    RegistrationScope_PerUser,
    RegistrationScope_InboxApp
    }

.enum ActivationType {
    ActivationType_InProcess,
    ActivationType_OutOfProcess
    }

.enum ThreadingType {
    ThreadingType_BOTH,
    ThreadingType_STA,
    ThreadingType_MTA
    }

.enum IdentityType {
    IdentityType_ActivateAsActivator,
    IdentityType_RunAs,
    IdentityType_ActivateAsPackage
    }

.enum InstancingType {
    InstancingType_SingleInstance,
    InstancingType_MultipleInstances
    }

ifndef ____x_ABI_CWindows_CFoundation_CIActivatableClassRegistration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIActivatableClassRegistration_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IActivatableClassRegistration <L"Windows.Foundation.IActivatableClassRegistration">
DEFINE_IIDX(IActivatableClassRegistration, "9BBCAE23-3DD6-49C3-B63C-1C587E7A6A67")

.comdef IActivatableClassRegistration : public IInspectable

    get_ActivatableClassId proc :ptr
    get_ActivationType  proc :ptr
    get_RegistrationScope proc :ptr
    get_RegisteredTrustLevel proc :ptr
    get_Attributes      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIDllServerActivatableClassRegistration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIDllServerActivatableClassRegistration_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IDllServerActivatableClassRegistration <L"Windows.Foundation.IDllServerActivatableClassRegistration">
DEFINE_IIDX(IDllServerActivatableClassRegistration, "C8AA04F6-66C6-46A3-8FE6-F56BE7DDC091")

.comdef IDllServerActivatableClassRegistration : public IInspectable

    get_DllPath         proc :ptr
    get_ThreadingType   proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIExeServerActivatableClassRegistration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIExeServerActivatableClassRegistration_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IExeServerActivatableClassRegistration <L"Windows.Foundation.IExeServerActivatableClassRegistration">
DEFINE_IIDX(IExeServerActivatableClassRegistration, "9308C3C5-C2AC-49D1-A024-660A2BB5D5AC")

.comdef IExeServerActivatableClassRegistration : public IInspectable

    get_ServerRegistration proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIExeServerRegistration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIExeServerRegistration_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IExeServerRegistration <L"Windows.Foundation.IExeServerRegistration">
DEFINE_IIDX(IExeServerRegistration, "EC734A06-0401-4317-BAC1-3B7E207242E3")

.comdef IExeServerRegistration : public IInspectable

    get_ServerName      proc :ptr
    get_ExePath         proc :ptr
    get_CommandLine     proc :ptr
    get_AppUserModelId  proc :ptr
    get_IdentityType    proc :ptr
    get_Identity        proc :ptr
    get_Instancing      proc :ptr
    get_Permissions     proc :ptr
   .ends

endif

.endn
.endn

ifndef RUNTIMECLASS_Windows_Foundation_DllServerActivatableClassRegistration_DEFINED
define RUNTIMECLASS_Windows_Foundation_DllServerActivatableClassRegistration_DEFINED
define RuntimeClass_Windows_Foundation_DllServerActivatableClassRegistration <L"Windows.Foundation.DllServerActivatableClassRegistration">
endif
ifndef RUNTIMECLASS_Windows_Foundation_ExeServerActivatableClassRegistration_DEFINED
define RUNTIMECLASS_Windows_Foundation_ExeServerActivatableClassRegistration_DEFINED
define RuntimeClass_Windows_Foundation_ExeServerActivatableClassRegistration <L"Windows.Foundation.ExeServerActivatableClassRegistration">
endif
ifndef RUNTIMECLASS_Windows_Foundation_ExeServerRegistration_DEFINED
define RUNTIMECLASS_Windows_Foundation_ExeServerRegistration_DEFINED
define RuntimeClass_Windows_Foundation_ExeServerRegistration <L"Windows.Foundation.ExeServerRegistration">
endif

endif
