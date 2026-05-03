ifndef _ROPARAMETERIXEDIID_H
define _ROPARAMETERIXEDIID_H

ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
endif
include apiset.inc
include apisetcconv.inc
include rpc.inc
include basetyps.inc

ifndef _APISET_ROPARAMETERIXEDIID_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION GE 0x0100
define _APISET_ROPARAMETERIXEDIID_VER 0x0100
endif
endif
endif

DECLARE_HANDLE(ROPARAMIIDHANDLE)

.comdef IRoSimpleMetaDataBuilder

    SetWinRtInterface   proc :GUID
    SetDelegate         proc :GUID
    SetInterfaceGroupSimpleDefault proc :PCWSTR, :PCWSTR, :ptr
    SetInterfaceGroupParameterizedDefault proc :PCWSTR, :UINT32, :ptr
    SetRuntimeClassSimpleDefault proc :PCWSTR, :PCWSTR, :ptr
    SetRuntimeClassParameterizedDefault proc :PCWSTR, :UINT32, :ptr
    SetStruct           proc :PCWSTR, :UINT32, :ptr
    SetEnum             proc :PCWSTR, :PCWSTR
    SetParameterizedInterface proc :GUID, :UINT32
    SetParameterizedDelegate proc :GUID, :UINT32
   .ends

.comdef IRoMetaDataLocator

    Locate              proc :PCWSTR, :ptr
   .ends

RoGetParameterizedTypeInstanceIID proto WINAPI :UINT32, :ptr, :ptr, :ptr, :ptr
RoFreeParameterizedTypeExtra proto WINAPI :ROPARAMIIDHANDLE
RoParameterizedTypeExtraGetTypeSignature proto WINAPI :ROPARAMIIDHANDLE

endif
