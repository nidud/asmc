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

ifndef __windows2Efoundation_h__
define __windows2Efoundation_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include IVectorChangedEventArgs.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_byte_INTERFACE_DEFINED__
define ____FIIterator_1_byte_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_byte, "40556131-a2a1-5fab-aaee-5f35268ca26b")

.comdef __FIIterator_1_byte : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_byte_INTERFACE_DEFINED__
define ____FIIterable_1_byte_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_byte, "88318266-f3fd-50fc-8f08-b823a41b60c1")

.comdef __FIIterable_1_byte : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_double_INTERFACE_DEFINED__
define ____FIIterator_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_double, "638a2cf4-f474-5318-9055-141cb909ac4b")

.comdef __FIIterator_1_double : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_double_INTERFACE_DEFINED__
define ____FIIterable_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_double, "c738964e-9c64-5bce-b5ce-61e9a282ec4a")

.comdef __FIIterable_1_double : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_float_INTERFACE_DEFINED__
define ____FIIterator_1_float_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_float, "42614e61-b0aa-5e72-9354-2771db20b7a8")

.comdef __FIIterator_1_float : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_float_INTERFACE_DEFINED__
define ____FIIterable_1_float_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_float, "b01bee51-063a-5fda-bd72-d76637bb8cb8")

.comdef __FIIterable_1_float : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_HSTRING_INTERFACE_DEFINED__
define ____FIIterator_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_HSTRING, "8c304ebb-6615-50a4-8829-879ecd443236")

.comdef __FIIterator_1_HSTRING : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_HSTRING_INTERFACE_DEFINED__
define ____FIIterable_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_HSTRING, "e2fcc7c1-3bfc-5a0b-b2b0-72e769d1cb7e")

.comdef __FIIterable_1_HSTRING : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_IInspectable_INTERFACE_DEFINED__
define ____FIIterator_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_IInspectable, "44a94f2d-04f8-5091-b336-be7892dd10be")

.comdef __FIIterator_1_IInspectable : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_IInspectable_INTERFACE_DEFINED__
define ____FIIterable_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_IInspectable, "092b849b-60b1-52be-a44a-6fe8e933cbe4")

.comdef __FIIterable_1_IInspectable : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_UINT32_INTERFACE_DEFINED__
define ____FIIterator_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_UINT32, "f06a2739-9443-5ef0-b284-dc5aff3e7d10")

.comdef __FIIterator_1_UINT32 : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_UINT32_INTERFACE_DEFINED__
define ____FIIterable_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_UINT32, "421d4b91-b13b-5f37-ae54-b5249bd80539")

.comdef __FIIterable_1_UINT32 : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CFoundation__CPoint, "c602b59e-0a8e-5e99-b478-2b564585278d")

.comdef __FIIterator_1_Windows__CFoundation__CPoint : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CFoundation__CPoint, "c192280d-3a09-5423-9dc5-67b83ebde41d")

.comdef __FIIterable_1_Windows__CFoundation__CPoint : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIIterable_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__
define ____FIIterator_1___FIIterable_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIIterable_1_Windows__CFoundation__CPoint, "377f6162-6e4d-574e-bf01-77f4fd021d0e")

.comdef __FIIterator_1___FIIterable_1_Windows__CFoundation__CPoint : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIIterable_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__
define ____FIIterable_1___FIIterable_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIIterable_1_Windows__CFoundation__CPoint, "ae44597e-d411-5b7f-bbec-6a96c94a107a")

.comdef __FIIterable_1___FIIterable_1_Windows__CFoundation__CPoint : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_GUID_IInspectable_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_GUID_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIKeyValuePair_2_GUID_IInspectable, "3bda1540-d089-5a1a-8f0d-94eba8068e58")

.comdef __FIKeyValuePair_2_GUID_IInspectable : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_GUID_IInspectable_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_GUID_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_GUID_IInspectable, "4f25059a-0b9a-5f25-9b9e-4b9f1d22ff65")

.comdef __FIIterator_1___FIKeyValuePair_2_GUID_IInspectable : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_GUID_IInspectable_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_GUID_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_GUID_IInspectable, "f3b20528-e3b3-5331-b2d0-0c2623aee785")

.comdef __FIIterable_1___FIKeyValuePair_2_GUID_IInspectable : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_HSTRING, "60310303-49c5-52e6-abc6-a9b36eccc716")

.comdef __FIKeyValuePair_2_HSTRING_HSTRING : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING, "05eb86f1-7140-5517-b88d-cbaebe57e6b1")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING, "e9bdaaf0-cbf6-5c72-be90-29cbf3a1319b")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_IInspectable, "09335560-6c6b-5a26-9348-97b781132b20")

.comdef __FIKeyValuePair_2_HSTRING_IInspectable : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_IInspectable, "5db5fa32-707c-5849-a06b-91c8eb9d10e8")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_IInspectable : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_IInspectable, "fe2f3d47-5d47-5499-8374-430c7cda0204")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_IInspectable : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_HSTRING_INTERFACE_DEFINED__
define ____FIVectorView_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_HSTRING, "2f13c006-a03a-5f69-b090-75a43e33423e")

.comdef __FIVectorView_1_HSTRING : public IInspectable

    GetAt		proc :UINT32, :ptr HSTRING
    get_Size		proc :ptr UINT32
    IndexOf		proc :HSTRING, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_HSTRING, "98b9acc1-4b56-532e-ac73-03d5291cca90")

.comdef __FIVector_1_HSTRING : public IInspectable

    GetAt		proc :UINT32, :ptr HSTRING
    get_Size		proc :ptr UINT32
    GetView		proc :ptr ptr __FIVectorView_1_HSTRING
    IndexOf		proc :HSTRING, :dword, :ptr
    SetAt		proc :SINT, :HSTRING
    InsertAt		proc :SINT, :HSTRING
    RemoveAt		proc :SINT
    Append		proc :HSTRING
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :dword
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING, "174f26c7-79ea-5f7c-bd70-ac4457f2cac8")

.comdef __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING, "a11824c9-e458-502a-afd8-ce3ce0abd6fe")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING, "4fed2669-d0d3-59f6-91d9-95902d728d6a")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_IInspectable_IInspectable_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_IInspectable_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIKeyValuePair_2_IInspectable_IInspectable, "59e7ae0c-c29d-5ad6-bef5-dedb52a198e1")

.comdef __FIKeyValuePair_2_IInspectable_IInspectable : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable, "31e55e8a-0f05-52fd-90d3-b04aa331aaa4")

.comdef __FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable, "33ac68f0-1084-529a-8a17-4e7c8adb7a0c")

.comdef __FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapView_2_HSTRING_IInspectable, "bb78502a-f79d-54fa-92c9-90c5039fdf7e")

.comdef __FIMapView_2_HSTRING_IInspectable : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIIterator_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIIterator_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIMapView_2_HSTRING_IInspectable, "53a2e825-9bf1-5083-8a7b-9d94f312dade")

.comdef __FIIterator_1___FIMapView_2_HSTRING_IInspectable : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIIterable_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIMapView_2_HSTRING_IInspectable, "e1670fae-49cd-5c47-a8c8-f6fa2c650c6c")

.comdef __FIIterable_1___FIMapView_2_HSTRING_IInspectable : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry, "32e54295-373c-50cb-80a1-468a990ca780")

.comdef __FIIterator_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry, "876be83b-7218-5bfb-a169-83152ef7e146")

.comdef __FIIterable_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CFoundation__CUri, "1c157d0f-5efe-5cec-bbd6-0c6ce9af07a5")

.comdef __FIIterator_1_Windows__CFoundation__CUri : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CFoundation__CUri, "b0d63b78-78ad-5e31-b6d8-e32a0e16c447")

.comdef __FIIterable_1_Windows__CFoundation__CUri : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapChangedEventArgs_1_HSTRING_INTERFACE_DEFINED__
define ____FIMapChangedEventArgs_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapChangedEventArgs_1_HSTRING, "60141efb-f2f9-5377-96fd-f8c60d9558b5")

.comdef __FIMapChangedEventArgs_1_HSTRING : public IInspectable

    get_CollectionChange proc :ptr
    get_Key		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_GUID_IInspectable_INTERFACE_DEFINED__
define ____FIMapView_2_GUID_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapView_2_GUID_IInspectable, "e4d2c732-bbc1-5ef4-869f-5007ceb55f6e")

.comdef __FIMapView_2_GUID_IInspectable : public IInspectable

    Lookup		proc :GUID, :ptr
    get_Size		proc :dword
    HasKey		proc :GUID, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapView_2_HSTRING_HSTRING, "ac7f26f2-feb7-5b2a-8ac4-345bc62caede")

.comdef __FIMapView_2_HSTRING_HSTRING : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapView_2_HSTRING___FIVector_1_HSTRING, "153f9c9c-d22a-5c9e-9c74-8b85c908b000")

.comdef __FIMapView_2_HSTRING___FIVector_1_HSTRING : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMapView_2_IInspectable_IInspectable_INTERFACE_DEFINED__
define ____FIMapView_2_IInspectable_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapView_2_IInspectable_IInspectable, "efe76d10-cb60-50ad-8a4f-6885cd6212a1")

.comdef __FIMapView_2_IInspectable_IInspectable : public IInspectable

    Lookup		proc :ptr, :ptr
    get_Size		proc :dword
    HasKey		proc :ptr, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMap_2_GUID_IInspectable_INTERFACE_DEFINED__
define ____FIMap_2_GUID_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMap_2_GUID_IInspectable, "5ee3189c-7dbf-5998-ad07-5414fb82567c")

.comdef __FIMap_2_GUID_IInspectable : public IInspectable

    Lookup		proc :GUID, :ptr
    get_Size		proc :dword
    HasKey		proc :GUID, :ptr
    GetView		proc :ptr
    Insert		proc :GUID, :ptr, :ptr
    Remove		proc :GUID
    Clear		proc
   .ends

endif

ifndef ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__
define ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMap_2_HSTRING_HSTRING, "f6d1f700-49c2-52ae-8154-826f9908773c")

.comdef __FIMap_2_HSTRING_HSTRING : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    GetView		proc :ptr
    Insert		proc :HSTRING, :HSTRING, :ptr
    Remove		proc :HSTRING
    Clear		proc
   .ends

endif

ifndef ____FIMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMap_2_HSTRING_IInspectable, "1b0d3570-0877-5ec2-8a2c-3b9539506aca")

.comdef __FIMap_2_HSTRING_IInspectable : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    GetView		proc :ptr
    Insert		proc :HSTRING, :ptr, :ptr
    Remove		proc :HSTRING
    Clear		proc
   .ends

endif

ifndef ____FIMap_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIMap_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMap_2_HSTRING___FIVector_1_HSTRING, "e475ca9d-6afb-5992-993e-53e6ef7a9ecd")

.comdef __FIMap_2_HSTRING___FIVector_1_HSTRING : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    GetView		proc :ptr
    Insert		proc :HSTRING, :ptr, :ptr
    Remove		proc :HSTRING
    Clear		proc
   .ends

endif

ifndef ____FIMap_2_IInspectable_IInspectable_INTERFACE_DEFINED__
define ____FIMap_2_IInspectable_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMap_2_IInspectable_IInspectable, "f5f69427-55ed-5512-8429-d4f6626dfcdd")

.comdef __FIMap_2_IInspectable_IInspectable : public IInspectable

    Lookup		proc :ptr, :ptr
    get_Size		proc :dword
    HasKey		proc :ptr, :ptr
    GetView		proc :ptr
    Insert		proc :ptr, :ptr, :ptr
    Remove		proc :ptr
    Clear		proc
   .ends

endif

ifndef ____FMapChangedEventHandler_2_HSTRING_HSTRING_INTERFACE_DEFINED__
define ____FMapChangedEventHandler_2_HSTRING_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FMapChangedEventHandler_2_HSTRING_HSTRING, "e2663f37-2e1b-500c-ad68-c3ed7a8f74c8")

.comdef __FMapChangedEventHandler_2_HSTRING_HSTRING : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FIObservableMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__
define ____FIObservableMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIObservableMap_2_HSTRING_HSTRING, "1e036276-2f60-55f6-b7f3-f86079e6900b")

.comdef __FIObservableMap_2_HSTRING_HSTRING : public IInspectable

    add_MapChanged	proc :ptr, :ptr
    remove_MapChanged	proc :EventRegistrationToken
   .ends

endif

ifndef ____FMapChangedEventHandler_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FMapChangedEventHandler_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FMapChangedEventHandler_2_HSTRING_IInspectable, "24f981e5-ddca-538d-aada-a59906084cf1")

.comdef __FMapChangedEventHandler_2_HSTRING_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FIObservableMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIObservableMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIObservableMap_2_HSTRING_IInspectable, "236aac9d-fb12-5c4d-a41c-9e445fb4d7ec")

.comdef __FIObservableMap_2_HSTRING_IInspectable : public IInspectable

    add_MapChanged	proc :ptr, :ptr
    remove_MapChanged	proc :EventRegistrationToken
   .ends

endif

ifndef ____FIVectorView_1_IInspectable_INTERFACE_DEFINED__
define ____FIVectorView_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_IInspectable, "a6487363-b074-5c60-ab16-866dce4ee54d")

.comdef __FIVectorView_1_IInspectable : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVector_1_IInspectable_INTERFACE_DEFINED__
define ____FIVector_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_IInspectable, "b32bdca4-5e52-5b27-bc5d-d66a1a268c2a")

.comdef __FIVector_1_IInspectable : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    GetView		proc :ptr
    IndexOf		proc :ptr, :dword, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :dword
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FVectorChangedEventHandler_1_IInspectable_INTERFACE_DEFINED__
define ____FVectorChangedEventHandler_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FVectorChangedEventHandler_1_IInspectable, "b423a801-d35e-56b9-813b-00889536cb98")

.comdef __FVectorChangedEventHandler_1_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FIObservableVector_1_IInspectable_INTERFACE_DEFINED__
define ____FIObservableVector_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIObservableVector_1_IInspectable, "7b81c56a-0985-518d-baa9-0da9ae009f65")

.comdef __FIObservableVector_1_IInspectable : public IInspectable

    add_VectorChanged	proc :ptr, :ptr
    remove_VectorChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____FIVectorView_1_byte_INTERFACE_DEFINED__
define ____FIVectorView_1_byte_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_byte, "6d05fb29-7885-544e-9382-a1ad391a3fa4")

.comdef __FIVectorView_1_byte : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :byte, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_double_INTERFACE_DEFINED__
define ____FIVectorView_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_double, "af7586a8-6b21-5f61-bff1-1b682293ad96")

.comdef __FIVectorView_1_double : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :real8, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_float_INTERFACE_DEFINED__
define ____FIVectorView_1_float_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_float, "7bca64fd-150c-5d50-b56b-9f4f474c5930")

.comdef __FIVectorView_1_float : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :real4, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_UINT32_INTERFACE_DEFINED__
define ____FIVectorView_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_UINT32, "e5ce1a07-8d33-5007-ba64-7d2508ccf85c")

.comdef __FIVectorView_1_UINT32 : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :UINT32, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIVectorView_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1___FIMapView_2_HSTRING_IInspectable, "172a655b-b3b8-5eae-bc2e-a6a1f1708b4b")

.comdef __FIVectorView_1___FIMapView_2_HSTRING_IInspectable : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry, "b1f00d3b-1f06-5117-93ea-2a0d79116701")

.comdef __FIVectorView_1_Windows__CFoundation__CIWwwFormUrlDecoderEntry : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CFoundation__CPoint, "0b7b4c9d-182f-582a-bddb-42b1aac30cad")

.comdef __FIVectorView_1_Windows__CFoundation__CPoint : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CFoundation__CUri, "4b8385bd-a2cd-5ff1-bf74-7ea580423e50")

.comdef __FIVectorView_1_Windows__CFoundation__CUri : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVector_1_double_INTERFACE_DEFINED__
define ____FIVector_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_double, "f452d23c-bf05-5f3e-88e7-d17a6716b911")

.comdef __FIVector_1_double : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    GetView		proc :ptr
    IndexOf		proc :real8, :dword, :ptr
    SetAt		proc :SINT, :real8
    InsertAt		proc :SINT, :real8
    RemoveAt		proc :SINT
    Append		proc :real8
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :dword
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_float_INTERFACE_DEFINED__
define ____FIVector_1_float_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_float, "61cf693f-db4c-579f-b905-5dd3d23cfd4d")

.comdef __FIVector_1_float : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    GetView		proc :ptr
    IndexOf		proc :real4, :dword, :ptr
    SetAt		proc :SINT, :real4
    InsertAt		proc :SINT, :real4
    RemoveAt		proc :SINT
    Append		proc :real4
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :dword
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CFoundation__CPoint, "c0d513a9-ec4a-5a5d-b6d5-b707defdb9f7")

.comdef __FIVector_1_Windows__CFoundation__CPoint : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    GetView		proc :ptr
    IndexOf		proc :ptr, :dword, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :dword
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CFoundation__CUri, "0d82bd8d-fe62-5d67-a7b9-7886dd75bc4e")

.comdef __FIVector_1_Windows__CFoundation__CUri : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    GetView		proc :ptr
    IndexOf		proc :ptr, :dword, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :dword
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__
define ____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIEventHandler_1_IInspectable, "c50898f6-c536-5f47-8583-8b2c2438a13b")

.comdef __FIEventHandler_1_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FIAsyncActionProgressHandler_1_double_INTERFACE_DEFINED__
define ____FIAsyncActionProgressHandler_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncActionProgressHandler_1_double, "44825c7c-0da9-5691-b2b4-914f231eeced")

.comdef __FIAsyncActionProgressHandler_1_double : public IUnknown

    _Invoke		proc :ptr, :real8
    .ends

endif

ifndef ____FIAsyncActionWithProgressCompletedHandler_1_double_INTERFACE_DEFINED__
define ____FIAsyncActionWithProgressCompletedHandler_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncActionWithProgressCompletedHandler_1_double, "94d64ac6-4491-53ef-8be8-36481f3ff1e8")

.comdef __FIAsyncActionWithProgressCompletedHandler_1_double : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncActionWithProgress_1_double_INTERFACE_DEFINED__
define ____FIAsyncActionWithProgress_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncActionWithProgress_1_double, "4f1430a6-a825-56ca-b047-1a9bad52ba67")

.comdef __FIAsyncActionWithProgress_1_double : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc
   .ends

endif

ifndef ____FIAsyncActionProgressHandler_1_UINT64_INTERFACE_DEFINED__
define ____FIAsyncActionProgressHandler_1_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncActionProgressHandler_1_UINT64, "55e233ca-f243-5ae2-853b-f9cc7c0ae0cf")

.comdef __FIAsyncActionProgressHandler_1_UINT64 : public IUnknown

    _Invoke		proc :ptr, :UINT64
    .ends

endif

ifndef ____FIAsyncActionWithProgressCompletedHandler_1_UINT64_INTERFACE_DEFINED__
define ____FIAsyncActionWithProgressCompletedHandler_1_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncActionWithProgressCompletedHandler_1_UINT64, "e6ff857b-f160-571a-a934-2c61f98c862d")

.comdef __FIAsyncActionWithProgressCompletedHandler_1_UINT64 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncActionWithProgress_1_UINT64_INTERFACE_DEFINED__
define ____FIAsyncActionWithProgress_1_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncActionWithProgress_1_UINT64, "43f713d0-c49d-5e55-aebf-af395768351e")

.comdef __FIAsyncActionWithProgress_1_UINT64 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_HSTRING_UINT64_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_HSTRING_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_HSTRING_UINT64, "14da7de7-40df-5d4c-823f-cf310625ad39")

.comdef __FIAsyncOperationProgressHandler_2_HSTRING_UINT64 : public IUnknown

    _Invoke		proc :ptr, :UINT64
    .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_UINT64_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_UINT64, "bd75eebe-e7b5-5af6-8415-a4b9c9045202")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_UINT64 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_HSTRING_UINT64_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_HSTRING_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgress_2_HSTRING_UINT64, "c8bbcb29-6b64-5ce2-a831-038f6e02199e")

.comdef __FIAsyncOperationWithProgress_2_HSTRING_UINT64 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_UINT32_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_UINT32_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_UINT32_UINT32, "ea0fe405-d432-5ac7-9ef8-5a65e1f97d7e")

.comdef __FIAsyncOperationProgressHandler_2_UINT32_UINT32 : public IUnknown

    _Invoke		proc :ptr, :UINT32
    .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_UINT32_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_UINT32_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_UINT32_UINT32, "1e466dc5-840f-54f9-b877-5e3a9f4b6c74")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_UINT32_UINT32 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_UINT32_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_UINT32_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgress_2_UINT32_UINT32, "eccb574a-c684-5572-a679-6b0842cfb57f")

.comdef __FIAsyncOperationWithProgress_2_UINT32_UINT32 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif


ifndef ____FIAsyncOperationProgressHandler_2_UINT64_UINT64_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_UINT64_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_UINT64_UINT64, "ffb2b65d-4120-5d13-826d-107851e6bb1c")

.comdef __FIAsyncOperationProgressHandler_2_UINT64_UINT64 : public IUnknown

    _Invoke		proc :ptr, :UINT64
    .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_UINT64_UINT64_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_UINT64_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_UINT64_UINT64, "d2024e41-5500-5b5a-ba46-cb7009596a2f")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_UINT64_UINT64 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_UINT64_UINT64_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_UINT64_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgress_2_UINT64_UINT64, "8f1db6e3-6556-5516-825c-1021ee27cd0c")

.comdef __FIAsyncOperationWithProgress_2_UINT64_UINT64 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_GUID_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_GUID_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_GUID, "5233899b-ba7e-504f-bb83-ceebac62decf")

.comdef __FIAsyncOperationCompletedHandler_1_GUID : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_GUID_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_GUID_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_GUID, "6607bc41-294b-5975-9c3f-4b49836d0916")

.comdef __FIAsyncOperation_1_GUID : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_HSTRING_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_HSTRING, "b79a741f-7fb5-50ae-9e99-911201ec3d41")

.comdef __FIAsyncOperationCompletedHandler_1_HSTRING : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_HSTRING_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_HSTRING, "3e1fe603-f897-5263-b328-0806426b8a79")

.comdef __FIAsyncOperation_1_HSTRING : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_IInspectable, "3f08262e-a2e1-5134-9297-e9211f481a2d")

.comdef __FIAsyncOperationCompletedHandler_1_IInspectable : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_IInspectable, "abf53c57-ee50-5342-b52a-26e3b8cc024f")

.comdef __FIAsyncOperation_1_IInspectable : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_UINT32, "9343b6e7-e3d2-5e4a-ab2d-2bce4919a6a4")

.comdef __FIAsyncOperationCompletedHandler_1_UINT32 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_UINT32, "ef60385f-be78-584b-aaef-7829ada2b0de")

.comdef __FIAsyncOperation_1_UINT32 : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_IInspectable, "89981889-1207-5ae6-9b28-ccc58f3aac6e")

.comdef __FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_IInspectable : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIMapView_2_HSTRING_IInspectable, "5dcbee48-9965-51da-a461-177c885be7e5")

.comdef __FIAsyncOperation_1___FIMapView_2_HSTRING_IInspectable : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIMap_2_HSTRING_IInspectable, "7344f356-8399-5756-a2f8-abd50c4146ff")

.comdef __FIAsyncOperationCompletedHandler_1___FIMap_2_HSTRING_IInspectable : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIMap_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIMap_2_HSTRING_IInspectable, "127e39c7-07c1-58e5-b48e-3a4729839fec")

.comdef __FIAsyncOperation_1___FIMap_2_HSTRING_IInspectable : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_UINT32, "55772f29-da64-5c87-871c-074337a84573")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_UINT32 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_UINT32, "52c56f3c-713a-5162-9e62-362ce7ed53be")

.comdef __FIAsyncOperation_1___FIVectorView_1_UINT32 : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable, "a782a13a-16a0-5326-b985-c4ca49e54e77")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable,"fc227365-219d-5d59-8b5b-58eb0a91ca0a")

.comdef __FIAsyncOperation_1___FIVectorView_1___FIMapView_2_HSTRING_IInspectable : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVector_1_HSTRING, "fae4b396-97c8-5cc3-bf88-ea3098edf6b2")

.comdef __FIAsyncOperationCompletedHandler_1___FIVector_1_HSTRING : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVector_1_HSTRING_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVector_1_HSTRING_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVector_1_HSTRING, "92b02cd3-aa6e-573d-bc03-8d2309cba3eb")

.comdef __FIAsyncOperation_1___FIVector_1_HSTRING : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CFoundation__CUri, "ad46f1cc-2bb0-585c-9885-03c2780d4d58")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CFoundation__CUri : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CFoundation__CUri, "641cb9dd-a28d-59e2-b8db-a227eda6cf2e")

.comdef __FIAsyncOperation_1_Windows__CFoundation__CUri : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_boolean_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_boolean_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_boolean, "c1d3d1a2-ae17-5a5f-b5a2-bdcc8844889a")

.comdef __FIAsyncOperationCompletedHandler_1_boolean : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_boolean_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_boolean_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_boolean, "cdb5efb3-5788-509d-9be1-71ccb8a3362a")

.comdef __FIAsyncOperation_1_boolean : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIReference_1_byte_INTERFACE_DEFINED__
define ____FIReference_1_byte_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_byte, "e5198cc8-2873-55f5-b0a1-84ff9e4aad62")

.comdef __FIReference_1_byte : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_double_INTERFACE_DEFINED__
define ____FIReference_1_double_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_double, "2f2d6c29-5473-5f3e-92e7-96572bb990e2")

.comdef __FIReference_1_double : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_float_INTERFACE_DEFINED__
define ____FIReference_1_float_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_float, "719cc2ba-3e76-5def-9f1a-38d85a145ea8")

.comdef __FIReference_1_float : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_GUID_INTERFACE_DEFINED__
define ____FIReference_1_GUID_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_GUID, "7d50f649-632c-51f9-849a-ee49428933ea")

.comdef __FIReference_1_GUID : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_int_INTERFACE_DEFINED__
define ____FIReference_1_int_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_int, "548cefbd-bc8a-5fa0-8df2-957440fc8bf4")

.comdef __FIReference_1_int : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1___z__zint64_INTERFACE_DEFINED__
define ____FIReference_1___z__zint64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1___z__zint64, "4dda9e24-e69f-5c6a-a0a6-93427365af2a")

.comdef __FIReference_1___z__zint64 : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_UINT32_INTERFACE_DEFINED__
define ____FIReference_1_UINT32_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_UINT32, "513ef3af-e784-5325-a91e-97c2b8111cf3")

.comdef __FIReference_1_UINT32 : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_UINT64_INTERFACE_DEFINED__
define ____FIReference_1_UINT64_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_UINT64, "6755e376-53bb-568b-a11d-17239868309e")

.comdef __FIReference_1_UINT64 : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_Windows__CFoundation__CDateTime_INTERFACE_DEFINED__
define ____FIReference_1_Windows__CFoundation__CDateTime_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_Windows__CFoundation__CDateTime, "5541d8a7-497c-5aa4-86fc-7713adbf2a2c")

.comdef __FIReference_1_Windows__CFoundation__CDateTime : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__
define ____FIReference_1_Windows__CFoundation__CPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_Windows__CFoundation__CPoint, "84f14c22-a00a-5272-8d3d-82112e66df00")

.comdef __FIReference_1_Windows__CFoundation__CPoint : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_Windows__CFoundation__CRect_INTERFACE_DEFINED__
define ____FIReference_1_Windows__CFoundation__CRect_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_Windows__CFoundation__CRect, "80423f11-054f-5eac-afd3-63b6ce15e77b")

.comdef __FIReference_1_Windows__CFoundation__CRect : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_Windows__CFoundation__CTimeSpan_INTERFACE_DEFINED__
define ____FIReference_1_Windows__CFoundation__CTimeSpan_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_Windows__CFoundation__CTimeSpan, "604d0c4c-91de-5c2a-935f-362f13eaf800")

.comdef __FIReference_1_Windows__CFoundation__CTimeSpan : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____FIReference_1_boolean_INTERFACE_DEFINED__
define ____FIReference_1_boolean_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_boolean, "3c00fd60-2950-5939-a21a-2d12c5a01b8a")

.comdef __FIReference_1_boolean : public IInspectable

    get_Value		proc :ptr
   .ends

endif

.namespace Windows
.namespace Foundation

.enum PropertyType {
    PropertyType_Empty		= 0,
    PropertyType_UInt8		= 1,
    PropertyType_Int16		= 2,
    PropertyType_UInt16		= 3,
    PropertyType_Int32		= 4,
    PropertyType_UInt32		= 5,
    PropertyType_Int64		= 6,
    PropertyType_UInt64		= 7,
    PropertyType_Single		= 8,
    PropertyType_Double		= 9,
    PropertyType_Char16		= 10,
    PropertyType_Boolean	= 11,
    PropertyType_String		= 12,
    PropertyType_Inspectable	= 13,
    PropertyType_DateTime	= 14,
    PropertyType_TimeSpan	= 15,
    PropertyType_Guid		= 16,
    PropertyType_Point		= 17,
    PropertyType_Size		= 18,
    PropertyType_Rect		= 19,
    PropertyType_OtherType	= 20,
    PropertyType_UInt8Array	= 1025,
    PropertyType_Int16Array	= 1026,
    PropertyType_UInt16Array	= 1027,
    PropertyType_Int32Array	= 1028,
    PropertyType_UInt32Array	= 1029,
    PropertyType_Int64Array	= 1030,
    PropertyType_UInt64Array	= 1031,
    PropertyType_SingleArray	= 1032,
    PropertyType_DoubleArray	= 1033,
    PropertyType_Char16Array	= 1034,
    PropertyType_BooleanArray	= 1035,
    PropertyType_StringArray	= 1036,
    PropertyType_InspectableArray = 1037,
    PropertyType_DateTimeArray	= 1038,
    PropertyType_TimeSpanArray	= 1039,
    PropertyType_GuidArray	= 1040,
    PropertyType_PointArray	= 1041,
    PropertyType_SizeArray	= 1042,
    PropertyType_RectArray	= 1043,
    PropertyType_OtherTypeArray = 1044
    }

.template Point
    X			FLOAT ?
    Y			FLOAT ?
   .ends

.template Size
    Width		FLOAT ?
    Height		FLOAT ?
   .ends

.template Rect
   X			FLOAT ?
   Y			FLOAT ?
   Width		FLOAT ?
   Height		FLOAT ?
  .ends

.template DateTime
    UniversalTime	INT64 ?
   .ends

.template TimeSpan
    Duration		INT64 ?
   .ends

ifndef ____x_ABI_CWindows_CFoundation_CIAsyncActionCompletedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIAsyncActionCompletedHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncActionCompletedHandler, "A4ED5C81-76C9-40BD-8BE6-B1D90FB20AE7")

.comdef IAsyncActionCompletedHandler : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IUriRuntimeClass <L"Windows.Foundation.IUriRuntimeClass">

DEFINE_IIDX(IUriRuntimeClass, "9E365E57-48B2-4160-956F-C7385120BBFC")

.comdef IUriRuntimeClass : public IInspectable

    get_AbsoluteUri	proc :ptr HSTRING
    get_DisplayUri	proc :ptr HSTRING
    get_Domain		proc :ptr HSTRING
    get_Extension	proc :ptr HSTRING
    get_Fragment	proc :ptr HSTRING
    get_Host		proc :ptr HSTRING
    get_Password	proc :ptr HSTRING
    get_Path		proc :ptr HSTRING
    get_Query		proc :ptr HSTRING
    get_QueryParsed	proc :ptr ptr
    get_RawUri		proc :ptr HSTRING
    get_SchemeName	proc :ptr HSTRING
    get_UserName	proc :ptr HSTRING
    get_Port		proc :ptr INT32
    get_Suspicious	proc :ptr boolean
    Equals		proc :ptr, :ptr
    CombineUri		proc :HSTRING, :ptr ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClassWithAbsoluteCanonicalUri_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClassWithAbsoluteCanonicalUri_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IUriRuntimeClassWithAbsoluteCanonicalUri <L"Windows.Foundation.IUriRuntimeClassWithAbsoluteCanonicalUri">

DEFINE_IIDX(IUriRuntimeClassWithAbsoluteCanonicalUri, "758D9661-221C-480F-A339-50656673F46F")

.comdef IUriRuntimeClassWithAbsoluteCanonicalUri : public IInspectable

    get_AbsoluteCanonicalUri proc :ptr
    get_DisplayIri	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIUriEscapeStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIUriEscapeStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IUriEscapeStatics <L"Windows.Foundation.IUriEscapeStatics">

DEFINE_IIDX(IUriEscapeStatics, "C1D432BA-C824-4452-A7FD-512BC3BBE9A1")

.comdef IUriEscapeStatics : public IInspectable

    UnescapeComponent	proc :HSTRING, :ptr
    EscapeComponent	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClassFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClassFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IUriRuntimeClassFactory <L"Windows.Foundation.IUriRuntimeClassFactory">

DEFINE_IIDX(IUriRuntimeClassFactory, "44A9796F-723E-4FDF-A218-033E75B0C084")

.comdef IUriRuntimeClassFactory : public IInspectable

    CreateUri		proc :HSTRING, :ptr ptr
    CreateWithRelativeUri proc :HSTRING, :HSTRING, :ptr ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIWwwFormUrlDecoderEntry_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IWwwFormUrlDecoderEntry <L"Windows.Foundation.IWwwFormUrlDecoderEntry">

DEFINE_IIDX(IWwwFormUrlDecoderEntry, "125E7431-F678-4E8E-B670-20A9B06C512D")

.comdef IWwwFormUrlDecoderEntry : public IInspectable

    get_Name		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIWwwFormUrlDecoderRuntimeClass_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIWwwFormUrlDecoderRuntimeClass_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IWwwFormUrlDecoderRuntimeClass <L"Windows.Foundation.IWwwFormUrlDecoderRuntimeClass">

DEFINE_IIDX(IWwwFormUrlDecoderRuntimeClass, "D45A0451-F225-4542-9296-0E1DF5D254DF")

.comdef IWwwFormUrlDecoderRuntimeClass : public IInspectable

    GetFirstValueByName proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIWwwFormUrlDecoderRuntimeClassFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIWwwFormUrlDecoderRuntimeClassFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IWwwFormUrlDecoderRuntimeClassFactory <L"Windows.Foundation.IWwwFormUrlDecoderRuntimeClassFactory">

DEFINE_IIDX(IWwwFormUrlDecoderRuntimeClassFactory, "5B8C6B3D-24AE-41B5-A1BF-F0C3D544845B")

.comdef IWwwFormUrlDecoderRuntimeClassFactory : public IInspectable

    CreateWwwFormUrlDecoder proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIGetActivationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIGetActivationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IGetActivationFactory <L"Windows.Foundation.IGetActivationFactory">

DEFINE_IIDX(IGetActivationFactory, "4EDB8EE2-96DD-49A7-94F7-4607DDAB8E3C")

.comdef IGetActivationFactory : public IInspectable

    GetActivationFactory proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIClosable_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIClosable_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IClosable <L"Windows.Foundation.IClosable">

DEFINE_IIDX(IClosable, "30D5A829-7FA4-4026-83BB-D75BAE4EA99E")

.comdef IClosable : public IInspectable

    Close		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIPropertyValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IPropertyValue <L"Windows.Foundation.IPropertyValue">

DEFINE_IIDX(IPropertyValue, "4BD682DD-7554-40E9-9A9B-82654EDE7E62")

.comdef IPropertyValue : public IInspectable

    get_Type		proc :ptr
    get_IsNumericScalar proc :ptr
    GetUInt8		proc :ptr
    GetInt16		proc :ptr
    GetUInt16		proc :ptr
    GetInt32		proc :ptr
    GetUInt32		proc :ptr
    GetInt64		proc :ptr
    GetUInt64		proc :ptr
    GetSingle		proc :ptr
    GetDouble		proc :ptr
    GetChar16		proc :ptr
    GetBoolean		proc :ptr
    GetString		proc :ptr
    GetGuid		proc :ptr
    GetDateTime		proc :ptr
    GetTimeSpan		proc :ptr
    GetPoint		proc :ptr
    GetSize		proc :ptr
    GetRect		proc :ptr
    GetUInt8Array	proc :ptr, :ptr
    GetInt16Array	proc :ptr, :ptr
    GetUInt16Array	proc :ptr, :ptr
    GetInt32Array	proc :ptr, :ptr
    GetUInt32Array	proc :ptr, :ptr
    GetInt64Array	proc :ptr, :ptr
    GetUInt64Array	proc :ptr, :ptr
    GetSingleArray	proc :ptr, :ptr
    GetDoubleArray	proc :ptr, :ptr
    GetChar16Array	proc :ptr, :ptr
    GetBooleanArray	proc :ptr, :ptr
    GetStringArray	proc :ptr, :ptr
    GetInspectableArray proc :ptr, :ptr
    GetGuidArray	proc :ptr, :ptr
    GetDateTimeArray	proc :ptr, :ptr
    GetTimeSpanArray	proc :ptr, :ptr
    GetPointArray	proc :ptr, :ptr
    GetSizeArray	proc :ptr, :ptr
    GetRectArray	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIPropertyValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IPropertyValueStatics <L"Windows.Foundation.IPropertyValueStatics">

DEFINE_IIDX(IPropertyValueStatics, "629BDBC8-D932-4FF4-96B9-8D96C5C1E858")

.comdef IPropertyValueStatics : public IInspectable

    CreateEmpty		proc :ptr
    CreateUInt8		proc :BYTE, :ptr
    CreateInt16		proc :INT16, :ptr
    CreateUInt16	proc :UINT16, :ptr
    CreateInt32		proc :INT32, :ptr
    CreateUInt32	proc :UINT32, :ptr
    CreateInt64		proc :INT64, :ptr
    CreateUInt64	proc :UINT64, :ptr
    CreateSingle	proc :FLOAT, :ptr
    CreateDouble	proc :DOUBLE, :ptr
    CreateChar16	proc :WCHAR, :ptr
    CreateBoolean	proc :boolean, :ptr
    CreateString	proc :HSTRING, :ptr
    CreateInspectable	proc :ptr, :ptr
    CreateGuid		proc :ptr GUID, :ptr
    CreateDateTime	proc :ptr, :ptr
    CreateTimeSpan	proc :ptr, :ptr
    CreatePoint		proc :ptr, :ptr
    CreateSize		proc :ptr, :ptr
    CreateRect		proc :ptr, :ptr
    CreateUInt8Array	proc :UINT32
    CreateInt16Array	proc :UINT32
    CreateUInt16Array	proc :UINT32
    CreateInt32Array	proc :UINT32
    CreateUInt32Array	proc :UINT32
    CreateInt64Array	proc :UINT32
    CreateUInt64Array	proc :UINT32
    CreateSingleArray	proc :UINT32
    CreateDoubleArray	proc :UINT32
    CreateChar16Array	proc :UINT32
    CreateBooleanArray	proc :UINT32
    CreateStringArray	proc :UINT32
    CreateInspectableArray proc :UINT32
    CreateGuidArray	proc :UINT32
    CreateDateTimeArray proc :UINT32
    CreateTimeSpanArray proc :UINT32
    CreatePointArray	proc :UINT32
    CreateSizeArray	proc :UINT32
    CreateRectArray	proc :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CIStringable_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIStringable_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IStringable <L"Windows.Foundation.IStringable">

DEFINE_IIDX(IStringable, "96369F54-8EB6-48F0-ABCE-C1B211E627C3")

.comdef IStringable : public IInspectable

    ToString		proc :ptr
   .ends

endif

.namespace Collections

ifndef ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Collections_IPropertySet <L"Windows.Foundation.Collections.IPropertySet">

DEFINE_IIDX(IPropertySet, "8A43ED9F-F4E6-4421-ACF9-1DAB2986820C")

.comdef IPropertySet : public IInspectable

    .ends

endif

.endn

ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CIAsyncAction_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_IAsyncAction <L"Windows.Foundation.IAsyncAction">

DEFINE_IIDX(IAsyncAction, "5A648006-843A-4DA9-865B-9D26E5DFAD7B")

.comdef IAsyncAction : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc
   .ends

endif

.endn
.endn

define RuntimeClass_Windows_Foundation_WwwFormUrlDecoder <L"Windows.Foundation.WwwFormUrlDecoder">
define RuntimeClass_Windows_Foundation_Uri <L"Windows.Foundation.Uri">
define RuntimeClass_Windows_Foundation_WwwFormUrlDecoderEntry <L"Windows.Foundation.WwwFormUrlDecoderEntry">
define RuntimeClass_Windows_Foundation_PropertyValue <L"Windows.Foundation.PropertyValue">
define RuntimeClass_Windows_Foundation_Collections_PropertySet <L"Windows.Foundation.Collections.PropertySet">

HSTRING_UserSize	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr ULONG, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr ULONG, :ptr HSTRING

endif
