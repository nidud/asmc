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

ifndef __windows2Edata2Ejson_h__
define __windows2Edata2Ejson_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CData__CJson__CIJsonValue, "189eb512-5a20-5ec6-9866-60af96f0d23b")

.comdef __FIIterator_1_Windows__CData__CJson__CIJsonValue : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CData__CJson__CIJsonValue, "cb0492b6-4113-55cf-b2c5-99eb428ba493")

.comdef __FIIterable_1_Windows__CData__CJson__CIJsonValue : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue, "4deecc89-b0b8-5ee8-a51d-1c25ad9a5b01")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue, "f948eac5-33eb-50f5-b5af-e7cecf0e4501")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue, "dfabb6e1-0411-5a8f-aa87-354e7110f099")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue, "eecd690c-1ff3-529f-923f-9b1c31fd3d0f")

.comdef __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :ptr
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue, "c9d9a725-786b-5113-b4b7-9b61764c220b")

.comdef __FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :ptr
    HasKey		proc :HSTRING, :ptr
    GetView		proc :ptr
    Insert		proc :HSTRING, :ptr, :ptr
    Remove		proc :HSTRING
    Clear		proc
   .ends

endif

ifndef ____FIVectorView_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CData__CJson__CIJsonValue, "cffabb0f-6bc4-5ff6-9b9e-7a9df6c687c8")

.comdef __FIVectorView_1_Windows__CData__CJson__CIJsonValue : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CData__CJson__CIJsonValue, "d44662bc-dce3-59a8-9272-4b210f33908b")

.comdef __FIVector_1_Windows__CData__CJson__CIJsonValue : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace Data
.namespace Json

.enum JsonValueType {
    JsonValueType_Null	= 0,
    JsonValueType_Boolean	= 1,
    JsonValueType_Number	= 2,
    JsonValueType_String	= 3,
    JsonValueType_Array = 4,
    JsonValueType_Object	= 5
    }

.enum JsonErrorStatus {
    JsonErrorStatus_Unknown	= 0,
    JsonErrorStatus_InvalidJsonString	= 1,
    JsonErrorStatus_InvalidJsonNumber	= 2,
    JsonErrorStatus_JsonValueNotFound	= 3,
    JsonErrorStatus_ImplementationLimit = 4
    }

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonValue <L"Windows.Data.Json.IJsonValue">
DEFINE_IIDX(IJsonValue, "A3219ECB-F0B3-4DCD-BEEE-19D48CD3ED1E")

.comdef IJsonValue : public IInspectable

    get_ValueType	proc :ptr
    Stringify		proc :ptr
    GetString		proc :ptr
    GetNumber		proc :ptr
    GetBoolean		proc :ptr
    GetArray		proc :ptr
    GetObject		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonValueStatics <L"Windows.Data.Json.IJsonValueStatics">
DEFINE_IIDX(IJsonValueStatics, "5F6B544A-2F53-48E1-91A3-F78B50A6345C")

.comdef IJsonValueStatics : public IInspectable

    Parse		proc :HSTRING, :ptr
    TryParse		proc :HSTRING, :ptr, :ptr
    CreateBooleanValue	proc :boolean, :ptr
    CreateNumberValue	proc :DOUBLE, :ptr
    CreateStringValue	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonObject_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonObject_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonObject <L"Windows.Data.Json.IJsonObject">
DEFINE_IIDX(IJsonObject, "064E24DD-29C2-4F83-9AC1-9EE11578BEB3")

.comdef IJsonObject : public IInspectable

    GetNamedValue	proc :HSTRING, :ptr
    SetNamedValue	proc :HSTRING, :ptr
    GetNamedObject	proc :HSTRING, :ptr
    GetNamedArray	proc :HSTRING, :ptr
    GetNamedString	proc :HSTRING, :ptr
    GetNamedNumber	proc :HSTRING, :ptr
    GetNamedBoolean	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonObjectWithDefaultValues_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonObjectWithDefaultValues_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonObjectWithDefaultValues <L"Windows.Data.Json.IJsonObjectWithDefaultValues">
DEFINE_IIDX(IJsonObjectWithDefaultValues, "D960D2A2-B7F0-4F00-8E44-D82CF415EA13")

.comdef IJsonObjectWithDefaultValues : public IInspectable

    GetNamedValueOrDefault proc :HSTRING, :ptr, :ptr
    GetNamedObjectOrDefault proc :HSTRING, :ptr, :ptr
    GetNamedStringOrDefault proc :HSTRING, :HSTRING, :ptr
    GetNamedArrayOrDefault proc :HSTRING, :ptr, :ptr
    GetNamedNumberOrDefault proc :HSTRING, :DOUBLE, :ptr
    GetNamedBooleanOrDefault proc :HSTRING, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonObjectStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonObjectStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonObjectStatics <L"Windows.Data.Json.IJsonObjectStatics">
DEFINE_IIDX(IJsonObjectStatics, "2289F159-54DE-45D8-ABCC-22603FA066A0")

.comdef IJsonObjectStatics : public IInspectable

    Parse		proc :HSTRING, :ptr
    TryParse		proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonArray_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonArray_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonArray <L"Windows.Data.Json.IJsonArray">
DEFINE_IIDX(IJsonArray, "08C1DDB6-0CBD-4A9A-B5D3-2F852DC37E81")

.comdef IJsonArray : public IInspectable

    GetObjectAt		proc :UINT32, :ptr
    GetArrayAt		proc :UINT32, :ptr
    GetStringAt		proc :UINT32, :ptr
    GetNumberAt		proc :UINT32, :ptr
    GetBooleanAt	proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonArrayStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonArrayStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonArrayStatics <L"Windows.Data.Json.IJsonArrayStatics">
DEFINE_IIDX(IJsonArrayStatics, "DB1434A9-E164-499F-93E2-8A8F49BB90BA")

.comdef IJsonArrayStatics : public IInspectable

    Parse		proc :HSTRING, :ptr
    TryParse		proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonErrorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonErrorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonErrorStatics <L"Windows.Data.Json.IJsonErrorStatics">
DEFINE_IIDX(IJsonErrorStatics, "FE616766-BF27-4064-87B7-6563BB11CE2E")

.comdef IJsonErrorStatics : public IInspectable

    GetStatus		proc :INT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CJson_CIJsonErrorStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CJson_CIJsonErrorStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Json_IJsonErrorStatics2 <L"Windows.Data.Json.IJsonErrorStatics2">
DEFINE_IIDX(IJsonErrorStatics2, "404030DA-87D0-436C-83AB-FC7B12C0CC26")

.comdef IJsonErrorStatics2 : public IInspectable

    GetJsonStatus	proc :INT32, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Data_Json_JsonArray_DEFINED
define RUNTIMECLASS_Windows_Data_Json_JsonArray_DEFINED
define RuntimeClass_Windows_Data_Json_JsonArray <L"Windows.Data.Json.JsonArray">
endif
ifndef RUNTIMECLASS_Windows_Data_Json_JsonObject_DEFINED
define RUNTIMECLASS_Windows_Data_Json_JsonObject_DEFINED
define RuntimeClass_Windows_Data_Json_JsonObject <L"Windows.Data.Json.JsonObject">
endif
ifndef RUNTIMECLASS_Windows_Data_Json_JsonValue_DEFINED
define RUNTIMECLASS_Windows_Data_Json_JsonValue_DEFINED
define RuntimeClass_Windows_Data_Json_JsonValue <L"Windows.Data.Json.JsonValue">
endif
ifndef RUNTIMECLASS_Windows_Data_Json_JsonError_DEFINED
define RUNTIMECLASS_Windows_Data_Json_JsonError_DEFINED
define RuntimeClass_Windows_Data_Json_JsonError <L"Windows.Data.Json.JsonError">
endif

endif
