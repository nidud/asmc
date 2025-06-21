ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
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

ifndef __windows2Eai2Emachinelearning2Enative_h__
define __windows2Eai2Emachinelearning2Enative_h__

include oaidl.inc
include ocidl.inc
include d3d12.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __ITensorNative_INTERFACE_DEFINED__
define __ITensorNative_INTERFACE_DEFINED__

DEFINE_IIDX(ITensorNative, "52f547ef-5b03-49b5-82d6-565f1ee0dd49")

.comdef ITensorNative : public IUnknown
    GetBuffer           proc :ptr, :ptr
    GetD3D12Resource    proc :ptr
   .ends

endif

ifndef __ITensorStaticsNative_INTERFACE_DEFINED__
define __ITensorStaticsNative_INTERFACE_DEFINED__

DEFINE_IIDX(ITensorStaticsNative, "39d055a4-66f6-4ebc-95d9-7a29ebe7690a")

.comdef ITensorStaticsNative : public IUnknown
    CreateFromD3D12Resource proc :ptr, :ptr, :int_t, :ptr
   .ends

endif

ifndef __ILearningModelDeviceFactoryNative_INTERFACE_DEFINED__
define __ILearningModelDeviceFactoryNative_INTERFACE_DEFINED__

DEFINE_IIDX(ILearningModelDeviceFactoryNative, "1e9b31a1-662e-4ae0-af67-f63bb337e634")

.comdef ILearningModelDeviceFactoryNative : public IUnknown
    CreateFromD3D12CommandQueue proc :ptr, :ptr
   .ends

endif

endif

endif
