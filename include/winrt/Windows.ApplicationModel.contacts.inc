ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eapplicationmodel2Econtacts_h__
define __windows2Eapplicationmodel2Econtacts_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include Windows.UI.Popups.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContact, "a572c173-800a-58bb-ab24-179959df2813")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContact : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContact, "63319996-7e0f-552e-872b-7b9adb1f4997")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContact : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactAddress, "d9003f84-63df-5c0c-bd1e-2ccdea55e717")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactAddress : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactAddress, "e783287c-e920-5540-9182-c1a6a5f2ad36")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactAddress : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount, "3ef1863f-c859-5b9d-8e35-20adf102a40d")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount, "35e203b2-5138-5967-80fa-a477ed4c7ddc")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactDate, "5004bf96-5349-5b10-87c6-c76f21f2a1d5")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactDate : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactDate, "96045d0b-b38b-5d91-8311-4fbc7ad4337d")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactDate : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactEmail, "d64ce66d-2936-5a1e-b8f5-080bb1356022")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactEmail : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactEmail, "37d0d55f-e136-5b07-8a3a-8110bde33917")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactEmail : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactField_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactField, "aa226af5-faa5-5353-871c-538099b7c836")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactField : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactField_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactField, "3b012111-c82b-541e-a0c1-37713ed83541")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactField : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactFieldType, "2f6d856a-50d4-5173-abea-db6c6b8fc530")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactFieldType : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactFieldType, "384b8b1b-ce8e-5781-b3dc-0776d684f658")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactFieldType : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactInformation, "7b77b895-abee-5501-94db-ce4e48a9a34f")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactInformation : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactInformation, "352762af-17e3-55e0-8be1-6a598a44b5b4")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactInformation : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField, "65e069e6-28d1-5d57-9fe1-80ff64850e67")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField, "810533b2-28bb-5ed3-ac19-fec8059d7b3c")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactJobInfo, "0873df73-ac99-50ef-8673-e78f8a540e2e")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactJobInfo : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactJobInfo, "17c1cead-56a3-5d93-abf2-14d34d4b9356")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactJobInfo : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactLocationField_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactLocationField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactLocationField, "a20407d7-6980-5c4f-b993-f1da03994105")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactLocationField : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactLocationField_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactLocationField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactLocationField, "2a0a41a6-da96-50a5-b8df-e4a8c4fcf86b")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactLocationField : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactPhone, "603b190e-1fb6-5762-bd8a-f59e952726f7")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactPhone : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactPhone, "4abd089c-49a1-5ba9-80df-53b72dd691ce")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactPhone : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactSignificantOther, "2051d4fa-bd46-52eb-b2d0-4eb5dac12157")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactSignificantOther : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactSignificantOther, "ae12bd35-93d6-53d8-87c0-49d84c5c6a83")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactSignificantOther : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CContactWebsite, "91a59fa2-5cc1-564d-bb1d-f52daec136ad")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CContactWebsite : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CContactWebsite, "4b03c203-989e-5b97-8fcb-67d661defe76")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CContactWebsite : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CContacts__CIContactField, "c501c1b3-171b-5320-8d84-c3a89a3d4034")

.comdef __FIIterator_1_Windows__CApplicationModel__CContacts__CIContactField : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CContacts__CIContactField, "e065edc5-1d23-5be5-9998-2736cd4d5297")

.comdef __FIIterable_1_Windows__CApplicationModel__CContacts__CIContactField : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContact, "9bca75b8-b0fa-5761-b959-381927a5f9d0")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContact : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactAddress, "e7fabc7d-79c2-5862-859e-959002d7b955")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactAddress : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount, "2687a6f4-5f99-50a1-88d1-5d7cc7c7f236")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactDate, "2743425d-b197-598d-bb80-14fdf0eaa823")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactDate : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactEmail, "8c3e5f9e-825a-5164-90d3-f97f7f88ecb0")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactEmail : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactField_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactField, "9c1b3046-f16a-57d7-87a7-eaa2e880d9a9")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactField : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactFieldType, "39d6abda-a00a-5777-8611-82d7c326c18d")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactFieldType : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation, "b9e80b52-02cb-5824-95ab-5cca3de394d3")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField, "b65efa04-cda8-597a-8abb-a6e1fe34c00f")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInstantMessageField : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactJobInfo, "f1f1bdc5-7ffe-5254-89fc-c01559020f9d")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactJobInfo : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactLocationField_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactLocationField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactLocationField, "1febf4ca-48dd-5faf-a2d3-74770d8aa330")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactLocationField : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactPhone, "145e78a9-e7f9-5998-802a-dbfc914ccf36")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactPhone : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactSignificantOther, "33c5edf9-c1de-528b-aa48-ceb6a1905cc0")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactSignificantOther : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CContactWebsite, "f677e62f-39c5-57c0-b642-26b143309871")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CContactWebsite : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CContacts__CIContactField, "1a4c5b35-7ef5-5eea-94c7-fdf1f617aa7e")

.comdef __FIVectorView_1_Windows__CApplicationModel__CContacts__CIContactField : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContact, "945779db-01d2-5839-8a92-7905ec92b28f")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContact : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactAddress_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactAddress, "d0c298ee-1520-539e-84b3-a25909717d20")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactAddress : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount, "2c55fb80-a759-5fae-bc29-9907e0976048")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactConnectedServiceAccount : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactDate_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactDate, "3135d944-d914-5a4f-843e-a6d6cb69bcb1")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactDate : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactEmail_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactEmail, "4ce06787-dea1-559f-a70a-fcbe59dbd3a4")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactEmail : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactFieldType_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactFieldType, "6fdc2115-1649-54a4-8faa-3049cefb05a4")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactFieldType : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactJobInfo_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactJobInfo, "ea148f90-bb89-5604-9757-ecd1e7ce5311")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactJobInfo : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactPhone_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactPhone, "6d1f883a-1f30-5a87-b54a-8e2245ed1001")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactPhone : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactSignificantOther_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactSignificantOther, "cec34450-8143-56e3-933a-d33051b74437")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactSignificantOther : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CContactWebsite_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CContactWebsite, "1931848e-e794-5775-b393-4a4518d63b09")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CContactWebsite : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CContacts__CIContactField_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CContacts__CIContactField, "f9dd472b-4f50-583a-a3aa-b73af54806be")

.comdef __FIVector_1_Windows__CApplicationModel__CContacts__CIContactField : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContact, "a1d09bee-c181-5419-bd14-8223b95f29a1")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContact : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContact, "857db963-f62c-53c4-a3a0-f6bf0c8fd3d3")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContact : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContactInformation, "c94b8021-508b-589b-93b3-2556cbc73a2f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CContacts__CContactInformation : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContactInformation, "0e51c030-27aa-561f-bbd8-2f57c08fef83")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CContacts__CContactInformation : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation, "059f51aa-64c6-53d5-bd28-76d0e88e3b8f")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation, "eab8500a-6a6f-5b05-89c2-8dcd66023b3d")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CContacts__CContactInformation : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact, "589b0543-eeae-5ca2-a63b-76010c64fccb")

.comdef __FIAsyncOperationCompletedHandler_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact, "0f0ff4e8-d25d-53a8-ba87-1a6b23e4315c")

.comdef __FIAsyncOperation_1___FIVector_1_Windows__CApplicationModel__CContacts__CContact : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace ApplicationModel
.namespace Contacts

.enum ContactFieldType {
    ContactFieldType_Email,
    ContactFieldType_PhoneNumber,
    ContactFieldType_Location,
    ContactFieldType_InstantMessage,
    ContactFieldType_Custom,
    ContactFieldType_ConnectedServiceAccount,
    ContactFieldType_ImportantDate,
    ContactFieldType_Address,
    ContactFieldType_SignificantOther,
    ContactFieldType_Notes,
    ContactFieldType_Website,
    ContactFieldType_JobInfo
    }

.enum ContactFieldCategory {
    ContactFieldCategory_None,
    ContactFieldCategory_Home,
    ContactFieldCategory_Work,
    ContactFieldCategory_Mobile,
    ContactFieldCategory_Other
    }

.enum ContactSelectionMode {
    ContactSelectionMode_Contacts,
    ContactSelectionMode_Fields
    }

.enum ContactEmailKind {
    ContactEmailKind_Personal,
    ContactEmailKind_Work,
    ContactEmailKind_Other
    }

.enum ContactPhoneKind {
    ContactPhoneKind_Home,
    ContactPhoneKind_Mobile,
    ContactPhoneKind_Work,
    ContactPhoneKind_Other
    }

.enum ContactAddressKind {
    ContactAddressKind_Home,
    ContactAddressKind_Work,
    ContactAddressKind_Other
    }

.enum ContactDateKind {
    ContactDateKind_Birthday,
    ContactDateKind_Anniversary,
    ContactDateKind_Other
    }

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactManagerStatics <L"Windows.ApplicationModel.Contacts.IContactManagerStatics">

DEFINE_IIDX(IContactManagerStatics, "81F21AC0-F661-4708-BA4F-D386BD0D622E")

.comdef IContactManagerStatics : public IInspectable

    ShowContactCard	proc :ptr, :ptr
    ShowContactCardWithPlacement proc :ptr, :ptr, :ptr
    ShowDelayLoadedContactCard proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactLaunchActionVerbsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactLaunchActionVerbsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactLaunchActionVerbsStatics <L"Windows.ApplicationModel.Contacts.IContactLaunchActionVerbsStatics">

DEFINE_IIDX(IContactLaunchActionVerbsStatics, "FB1232D6-EE73-46E7-8761-11CD0157728F")

.comdef IContactLaunchActionVerbsStatics : public IInspectable

    get_Call		proc :ptr
    get_Message		proc :ptr
    get_Map		proc :ptr
    get_Post		proc :ptr
    get_VideoCall	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactField_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactField_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactField <L"Windows.ApplicationModel.Contacts.IContactField">

DEFINE_IIDX(IContactField, "B176486A-D293-492C-A058-DB575B3E3C0F")

.comdef IContactField : public IInspectable

    get_Type		proc :ptr
    get_Category	proc :ptr
    get_Name		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactLocationField_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactLocationField_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactLocationField <L"Windows.ApplicationModel.Contacts.IContactLocationField">

DEFINE_IIDX(IContactLocationField, "9EC00F82-AB6E-4B36-89E3-B23BC0A1DACC")

.comdef IContactLocationField : public IInspectable

    get_UnstructuredAddress proc :ptr
    get_Street		proc :ptr
    get_City		proc :ptr
    get_Region		proc :ptr
    get_Country		proc :ptr
    get_PostalCode	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactInstantMessageField_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactInstantMessageField_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactInstantMessageField <L"Windows.ApplicationModel.Contacts.IContactInstantMessageField">

DEFINE_IIDX(IContactInstantMessageField, "CCE33B37-0D85-41FA-B43D-DA599C3EB009")

.comdef IContactInstantMessageField : public IInspectable

    get_UserName	proc :ptr
    get_Service		proc :ptr
    get_DisplayText	proc :ptr
    get_LaunchUri	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIKnownContactFieldStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIKnownContactFieldStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IKnownContactFieldStatics <L"Windows.ApplicationModel.Contacts.IKnownContactFieldStatics">

DEFINE_IIDX(IKnownContactFieldStatics, "2E0E1B12-D627-4FCA-BAD4-1FAF168C7D14")

.comdef IKnownContactFieldStatics : public IInspectable

    get_Email		proc :ptr
    get_PhoneNumber	proc :ptr
    get_Location	proc :ptr
    get_InstantMessage	proc :ptr
    ConvertNameToType	proc :HSTRING, :ptr
    ConvertTypeToName	proc :LONG, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactInformation <L"Windows.ApplicationModel.Contacts.IContactInformation">

DEFINE_IIDX(IContactInformation, "275EB6D4-6A2E-4278-A914-E460D5F088F6")

.comdef IContactInformation : public IInspectable

    get_Name		proc :ptr
    GetThumbnailAsync	proc :ptr
    get_Emails		proc :ptr
    get_PhoneNumbers	proc :ptr
    get_Locations	proc :ptr
    get_InstantMessages proc :ptr
    get_CustomFields	proc :ptr
    QueryCustomFields	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactPicker_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactPicker_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactPicker <L"Windows.ApplicationModel.Contacts.IContactPicker">

DEFINE_IIDX(IContactPicker, "0E09FD91-42F8-4055-90A0-896F96738936")

.comdef IContactPicker : public IInspectable

    get_CommitButtonText proc :ptr
    put_CommitButtonText proc :HSTRING
    get_SelectionMode	proc :ptr
    put_SelectionMode	proc :Windows::ApplicationModel::Contacts::ContactSelectionMode
    get_DesiredFields	proc :ptr
    PickSingleContactAsync proc :ptr
    PickMultipleContactsAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactPicker2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactPicker2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactPicker2 <L"Windows.ApplicationModel.Contacts.IContactPicker2">

DEFINE_IIDX(IContactPicker2, "B35011CF-5CEF-4D24-AA0C-340C5208725D")

.comdef IContactPicker2 : public IInspectable

    get_DesiredFieldsWithContactFieldType proc :ptr
    PickContactAsync	proc :ptr
    PickContactsAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactFieldFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactFieldFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactFieldFactory <L"Windows.ApplicationModel.Contacts.IContactFieldFactory">

DEFINE_IIDX(IContactFieldFactory, "85E2913F-0E4A-4A3E-8994-406AE7ED646E")

.comdef IContactFieldFactory : public IInspectable

    CreateField_Default proc :HSTRING, :LONG, :ptr
    CreateField_Category proc :HSTRING, :LONG, :LONG, :ptr
    CreateField_Custom	proc :HSTRING, :HSTRING, :LONG, :LONG, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactLocationFieldFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactLocationFieldFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactLocationFieldFactory <L"Windows.ApplicationModel.Contacts.IContactLocationFieldFactory">

DEFINE_IIDX(IContactLocationFieldFactory, "F79932D7-2FDF-43FE-8F18-41897390BCFE")

.comdef IContactLocationFieldFactory : public IInspectable

    CreateLocation_Default proc :HSTRING, :ptr
    CreateLocation_Category proc :HSTRING, :LONG, :ptr
    CreateLocation_All	proc :HSTRING, :LONG, :HSTRING, :HSTRING, :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactInstantMessageFieldFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactInstantMessageFieldFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactInstantMessageFieldFactory <L"Windows.ApplicationModel.Contacts.IContactInstantMessageFieldFactory">

DEFINE_IIDX(IContactInstantMessageFieldFactory, "BA0B6794-91A3-4BB2-B1B9-69A5DFF0BA09")

.comdef IContactInstantMessageFieldFactory : public IInspectable

    CreateInstantMessage_Default proc :HSTRING, :ptr
    CreateInstantMessage_Category proc :HSTRING, :LONG, :ptr
    CreateInstantMessage_All proc :HSTRING, :LONG, :HSTRING, :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactSignificantOther_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactSignificantOther_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactSignificantOther <L"Windows.ApplicationModel.Contacts.IContactSignificantOther">

DEFINE_IIDX(IContactSignificantOther, "8873B5AB-C5FB-46D8-93FE-DA3FF1934054")

.comdef IContactSignificantOther : public IInspectable

    get_Name		proc :ptr
    put_Name		proc :HSTRING
    get_Description	proc :ptr
    put_Description	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactWebsite_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactWebsite_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactWebsite <L"Windows.ApplicationModel.Contacts.IContactWebsite">

DEFINE_IIDX(IContactWebsite, "9F130176-DC1B-4055-AD66-652F39D990E8")

.comdef IContactWebsite : public IInspectable

    get_Uri		proc :ptr
    put_Uri		proc :ptr
    get_Description	proc :ptr
    put_Description	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactEmail_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactEmail_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactEmail <L"Windows.ApplicationModel.Contacts.IContactEmail">

DEFINE_IIDX(IContactEmail, "90A219A9-E3D3-4D63-993B-05B9A5393ABF")

.comdef IContactEmail : public IInspectable

    get_Address		proc :ptr
    put_Address		proc :HSTRING
    get_Kind		proc :ptr
    put_Kind		proc :Windows::ApplicationModel::Contacts::ContactEmailKind
    get_Description	proc :ptr
    put_Description	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactPhone_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactPhone_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactPhone <L"Windows.ApplicationModel.Contacts.IContactPhone">

DEFINE_IIDX(IContactPhone, "467DAB65-2712-4F52-B783-9EA8111C63CD")

.comdef IContactPhone : public IInspectable

    get_Number		proc :ptr
    put_Number		proc :HSTRING
    get_Kind		proc :ptr
    put_Kind		proc :LONG
    get_Description	proc :ptr
    put_Description	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactAddress_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactAddress_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactAddress <L"Windows.ApplicationModel.Contacts.IContactAddress">

DEFINE_IIDX(IContactAddress, "9739D39A-42CE-4872-8D70-3063AA584B70")

.comdef IContactAddress : public IInspectable

    get_StreetAddress	proc :ptr
    put_StreetAddress	proc :HSTRING
    get_Locality	proc :ptr
    put_Locality	proc :HSTRING
    get_Region		proc :ptr
    put_Region		proc :HSTRING
    get_Country		proc :ptr
    put_Country		proc :HSTRING
    get_PostalCode	proc :ptr
    put_PostalCode	proc :HSTRING
    get_Kind		proc :ptr
    put_Kind		proc :LONG
    get_Description	proc :ptr
    put_Description	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactConnectedServiceAccount_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactConnectedServiceAccount_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactConnectedServiceAccount <L"Windows.ApplicationModel.Contacts.IContactConnectedServiceAccount">

DEFINE_IIDX(IContactConnectedServiceAccount, "F6F83553-AA27-4731-8E4A-3DEC5CE9EEC9")

.comdef IContactConnectedServiceAccount : public IInspectable

    get_Id		proc :ptr
    put_Id		proc :HSTRING
    get_ServiceName	proc :ptr
    put_ServiceName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactDate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactDate_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactDate <L"Windows.ApplicationModel.Contacts.IContactDate">

DEFINE_IIDX(IContactDate, "FE98AE66-B205-4934-9174-0FF2B0565707")

.comdef IContactDate : public IInspectable

    get_Day		proc :ptr
    put_Day		proc :ptr
    get_Month		proc :ptr
    put_Month		proc :ptr
    get_Year		proc :ptr
    put_Year		proc :ptr
    get_Kind		proc :ptr
    put_Kind		proc :LONG
    get_Description	proc :ptr
    put_Description	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactName_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactName_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactName <L"Windows.ApplicationModel.Contacts.IContactName">

DEFINE_IIDX(IContactName, "F404E97B-9034-453C-8EBF-140A38C86F1D")

.comdef IContactName : public IInspectable

    get_FirstName	proc :ptr
    put_FirstName	proc :HSTRING
    get_LastName	proc :ptr
    put_LastName	proc :HSTRING
    get_MiddleName	proc :ptr
    put_MiddleName	proc :HSTRING
    get_YomiGivenName	proc :ptr
    put_YomiGivenName	proc :HSTRING
    get_YomiFamilyName	proc :ptr
    put_YomiFamilyName	proc :HSTRING
    get_HonorificNameSuffix proc :ptr
    put_HonorificNameSuffix proc :HSTRING
    get_HonorificNamePrefix proc :ptr
    put_HonorificNamePrefix proc :HSTRING
    get_DisplayName	proc :ptr
    get_YomiDisplayName proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactJobInfo_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactJobInfo_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactJobInfo <L"Windows.ApplicationModel.Contacts.IContactJobInfo">

DEFINE_IIDX(IContactJobInfo, "6D117B4C-CE50-4B43-9E69-B18258EA5315")

.comdef IContactJobInfo : public IInspectable

    get_CompanyName	proc :ptr
    put_CompanyName	proc :HSTRING
    get_CompanyYomiName proc :ptr
    put_CompanyYomiName proc :HSTRING
    get_Department	proc :ptr
    put_Department	proc :HSTRING
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Manager		proc :ptr
    put_Manager		proc :HSTRING
    get_Office		proc :ptr
    put_Office		proc :HSTRING
    get_CompanyAddress	proc :ptr
    put_CompanyAddress	proc :HSTRING
    get_Description	proc :ptr
    put_Description	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContact_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContact_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContact <L"Windows.ApplicationModel.Contacts.IContact">

DEFINE_IIDX(IContact, "EC0072F3-2118-4049-9EBC-17F0AB692B64")

.comdef IContact : public IInspectable

    get_Name		proc :ptr
    put_Name		proc :HSTRING
    get_Thumbnail	proc :ptr
    put_Thumbnail	proc :ptr
    get_Fields		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContact2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContact2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContact2 <L"Windows.ApplicationModel.Contacts.IContact2">

DEFINE_IIDX(IContact2, "F312F365-BB77-4C94-802D-8328CEE40C08")

.comdef IContact2 : public IInspectable

    get_Id		proc :ptr
    put_Id		proc :HSTRING
    get_Notes		proc :ptr
    put_Notes		proc :HSTRING
    get_Phones		proc :ptr
    get_Emails		proc :ptr
    get_Addresses	proc :ptr
    get_ConnectedServiceAccounts proc :ptr
    get_ImportantDates	proc :ptr
    get_DataSuppliers	proc :ptr
    get_JobInfo		proc :ptr
    get_SignificantOthers proc :ptr
    get_Websites	proc :ptr
    get_ProviderProperties proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactCardDelayedDataLoader_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CIContactCardDelayedDataLoader_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_IContactCardDelayedDataLoader  <L"Windows.ApplicationModel.Contacts.IContactCardDelayedDataLoader">

DEFINE_IIDX(IContactCardDelayedDataLoader, "B60AF902-1546-434D-869C-6E3520760EF3")

.comdef IContactCardDelayedDataLoader : public IInspectable

    SetData		proc :ptr
   .ends

endif

.endn
.endn
.endn

define RuntimeClass_Windows_ApplicationModel_Contacts_ContactCardDelayedDataLoader <L"Windows.ApplicationModel.Contacts.ContactCardDelayedDataLoader">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactManager <L"Windows.ApplicationModel.Contacts.ContactManager">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactLaunchActionVerbs<L"Windows.ApplicationModel.Contacts.ContactLaunchActionVerbs">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactField <L"Windows.ApplicationModel.Contacts.ContactField">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactLocationField <L"Windows.ApplicationModel.Contacts.ContactLocationField">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactInstantMessageField <L"Windows.ApplicationModel.Contacts.ContactInstantMessageField">
define RuntimeClass_Windows_ApplicationModel_Contacts_KnownContactField <L"Windows.ApplicationModel.Contacts.KnownContactField">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactInformation <L"Windows.ApplicationModel.Contacts.ContactInformation">
define RuntimeClass_Windows_ApplicationModel_Contacts_Contact <L"Windows.ApplicationModel.Contacts.Contact">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactPicker <L"Windows.ApplicationModel.Contacts.ContactPicker">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactFieldFactory <L"Windows.ApplicationModel.Contacts.ContactFieldFactory">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactSignificantOther <L"Windows.ApplicationModel.Contacts.ContactSignificantOther">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactWebsite <L"Windows.ApplicationModel.Contacts.ContactWebsite">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactEmail <L"Windows.ApplicationModel.Contacts.ContactEmail">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactPhone <L"Windows.ApplicationModel.Contacts.ContactPhone">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactAddress <L"Windows.ApplicationModel.Contacts.ContactAddress">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactConnectedServiceAccount  <L"Windows.ApplicationModel.Contacts.ContactConnectedServiceAccount">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactDate <L"Windows.ApplicationModel.Contacts.ContactDate">
define RuntimeClass_Windows_ApplicationModel_Contacts_ContactJobInfo <L"Windows.ApplicationModel.Contacts.ContactJobInfo">

HSTRING_UserSize	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif
