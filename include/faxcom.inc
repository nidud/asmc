ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __faxcom_h__
define __faxcom_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IFaxTiff_INTERFACE_DEFINED__
define __IFaxTiff_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxTiff, "b19bb45f-b91c-11d1-83e1-00c04fb6e984")

.comdef IFaxTiff : public IDispatch
    get_ReceiveTime     proc :ptr
    get_Image           proc :ptr
    put_Image           proc :BSTR
    get_RecipientName   proc :ptr
    get_SenderName      proc :ptr
    get_Routing         proc :ptr
    get_CallerId        proc :ptr
    get_Csid            proc :ptr
    get_Tsid            proc :ptr
    get_RecipientNumber proc :ptr
    get_RawReceiveTime  proc :ptr
    get_TiffTagString   proc :int_t, :ptr
   .ends

endif

ifndef __IFaxServer_INTERFACE_DEFINED__
define __IFaxServer_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxServer, "D73733C7-CC80-11D0-B225-00C04FB6C2F5")

.comdef IFaxServer : public IDispatch
    Connect             proc :BSTR
    Disconnect          proc
    GetPorts            proc :ptr
    CreateDocument      proc :BSTR, :ptr
    GetJobs             proc :ptr
    get_Retries         proc :ptr
    put_Retries         proc :LONG
    get_RetryDelay      proc :ptr
    put_RetryDelay      proc :LONG
    get_DirtyDays       proc :ptr
    put_DirtyDays       proc :LONG
    get_Branding        proc :ptr
    put_Branding        proc :BOOL
    get_UseDeviceTsid   proc :ptr
    put_UseDeviceTsid   proc :BOOL
    get_ServerCoverpage proc :ptr
    put_ServerCoverpage proc :BOOL
    get_PauseServerQueue proc :ptr
    put_PauseServerQueue proc :BOOL
    get_ArchiveOutboundFaxes proc :ptr
    put_ArchiveOutboundFaxes proc :BOOL
    get_ArchiveDirectory proc :ptr
    put_ArchiveDirectory proc :BSTR
    get_ServerMapiProfile proc :ptr
    put_ServerMapiProfile proc :BSTR
    get_DiscountRateStartHour proc :ptr
    put_DiscountRateStartHour proc :short_t
    get_DiscountRateStartMinute proc :ptr
    put_DiscountRateStartMinute proc :short_t
    get_DiscountRateEndHour proc :ptr
    put_DiscountRateEndHour proc :short_t
    get_DiscountRateEndMinute proc :ptr
    put_DiscountRateEndMinute proc :short_t
   .ends

endif

ifndef __IFaxPort_INTERFACE_DEFINED__
define __IFaxPort_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxPort, "D73733CC-CC80-11D0-B225-00C04FB6C2F5")

.comdef IFaxPort : public IDispatch
    get_Name            proc :ptr
    get_DeviceId        proc :ptr
    get_Rings           proc :ptr
    put_Rings           proc :LONG
    get_Csid            proc :ptr
    put_Csid            proc :BSTR
    get_Tsid            proc :ptr
    put_Tsid            proc :BSTR
    get_Send            proc :ptr
    put_Send            proc :BOOL
    get_Receive         proc :ptr
    put_Receive         proc :BOOL
    get_Priority        proc :ptr
    put_Priority        proc :LONG
    GetRoutingMethods   proc :ptr
    get_CanModify       proc :ptr
    GetStatus           proc :ptr
   .ends

endif

ifndef __IFaxPorts_INTERFACE_DEFINED__
define __IFaxPorts_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxPorts, "D73733D5-CC80-11D0-B225-00C04FB6C2F5")

.comdef IFaxPorts : public IDispatch
    get_Count           proc :ptr
    get_Item            proc :LONG, :ptr
   .ends

endif

ifndef __IFaxRoutingMethod_INTERFACE_DEFINED__
define __IFaxRoutingMethod_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxRoutingMethod, "2199F5F3-CEFC-11D0-A341-0000F800E68D")

.comdef IFaxRoutingMethod : public IDispatch
    get_DeviceId        proc :ptr
    get_Enable          proc :ptr
    put_Enable          proc :BOOL
    get_DeviceName      proc :ptr
    get_Guid            proc :ptr
    get_FunctionName    proc :ptr
    get_ImageName       proc :ptr
    get_FriendlyName    proc :ptr
    get_ExtensionName   proc :ptr
    get_RoutingData     proc :ptr
   .ends

endif

ifndef __IFaxRoutingMethods_INTERFACE_DEFINED__
define __IFaxRoutingMethods_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxRoutingMethods, "2199F5F5-CEFC-11D0-A341-0000F800E68D")

.comdef IFaxRoutingMethods : public IDispatch
    get_Count           proc :ptr
    get_Item            proc :LONG, :ptr
   .ends

endif

ifndef __IFaxStatus_INTERFACE_DEFINED__
define __IFaxStatus_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxStatus, "8B97E605-D054-11D0-B226-00C04FB6C2F5")

.comdef IFaxStatus : public IDispatch
    get_CallerId        proc :ptr
    get_Csid            proc :ptr
    get_CurrentPage     proc :ptr
    get_DeviceId        proc :ptr
    get_DeviceName      proc :ptr
    get_DocumentName    proc :ptr
    get_Send            proc :ptr
    get_Receive         proc :ptr
    get_Address         proc :ptr
    get_RoutingString   proc :ptr
    get_SenderName      proc :ptr
    get_RecipientName   proc :ptr
    get_DocumentSize    proc :ptr
    get_Description     proc :ptr
    get_PageCount       proc :ptr
    get_Tsid            proc :ptr
    get_StartTime       proc :ptr
    get_SubmittedTime   proc :ptr
    get_ElapsedTime     proc :ptr
    Refresh             proc
   .ends

endif

ifndef __IFaxDoc_INTERFACE_DEFINED__
define __IFaxDoc_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxDoc, "FA21F4C5-5C4C-11D1-83CF-00C04FB6E984")

.comdef IFaxDoc : public IDispatch
    get_FileName        proc :ptr
    put_FileName        proc :BSTR
    get_CoverpageName   proc :ptr
    put_CoverpageName   proc :BSTR
    get_SendCoverpage   proc :ptr
    put_SendCoverpage   proc :BOOL
    get_ServerCoverpage proc :ptr
    put_ServerCoverpage proc :BOOL
    get_DiscountSend    proc :ptr
    put_DiscountSend    proc :BOOL
    get_RecipientName   proc :ptr
    put_RecipientName   proc :BSTR
    get_RecipientCompany proc :ptr
    put_RecipientCompany proc :BSTR
    get_RecipientAddress proc :ptr
    put_RecipientAddress proc :BSTR
    get_RecipientCity   proc :ptr
    put_RecipientCity   proc :BSTR
    get_RecipientState  proc :ptr
    put_RecipientState  proc :BSTR
    get_RecipientZip    proc :ptr
    put_RecipientZip    proc :BSTR
    get_RecipientCountry proc :ptr
    put_RecipientCountry proc :BSTR
    get_RecipientTitle  proc :ptr
    put_RecipientTitle  proc :BSTR
    get_RecipientDepartment proc :ptr
    put_RecipientDepartment proc :BSTR
    get_RecipientOffice proc :ptr
    put_RecipientOffice proc :BSTR
    get_RecipientHomePhone proc :ptr
    put_RecipientHomePhone proc :BSTR
    get_RecipientOfficePhone proc :ptr
    put_RecipientOfficePhone proc :BSTR
    get_SenderName      proc :ptr
    put_SenderName      proc :BSTR
    get_SenderCompany   proc :ptr
    put_SenderCompany   proc :BSTR
    get_SenderAddress   proc :ptr
    put_SenderAddress   proc :BSTR
    get_SenderTitle     proc :ptr
    put_SenderTitle     proc :BSTR
    get_SenderDepartment proc :ptr
    put_SenderDepartment proc :BSTR
    get_SenderOffice    proc :ptr
    put_SenderOffice    proc :BSTR
    get_SenderHomePhone proc :ptr
    put_SenderHomePhone proc :BSTR
    get_SenderOfficePhone proc :ptr
    put_SenderOfficePhone proc :BSTR
    get_CoverpageNote   proc :ptr
    put_CoverpageNote   proc :BSTR
    get_CoverpageSubject proc :ptr
    put_CoverpageSubject proc :BSTR
    get_Tsid            proc :ptr
    put_Tsid            proc :BSTR
    get_BillingCode     proc :ptr
    put_BillingCode     proc :BSTR
    get_EmailAddress    proc :ptr
    put_EmailAddress    proc :BSTR
    get_DisplayName     proc :ptr
    put_DisplayName     proc :BSTR
    Send                proc :ptr
    get_FaxNumber       proc :ptr
    put_FaxNumber       proc :BSTR
    putref_ConnectionObject proc :ptr
    get_CallHandle      proc :ptr
    put_CallHandle      proc :LONG
    get_SenderFax       proc :ptr
    put_SenderFax       proc :BSTR
   .ends

endif

ifndef __IFaxJobs_INTERFACE_DEFINED__
define __IFaxJobs_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxJobs, "55DABFD3-5C9E-11D1-B791-000000000000")

.comdef IFaxJobs : public IDispatch
    get_Count           proc :ptr
    get_Item            proc :LONG, :ptr
   .ends

endif

ifndef __IFaxJob_INTERFACE_DEFINED__
define __IFaxJob_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxJob, "55DABFD5-5C9E-11D1-B791-000000000000")

.comdef IFaxJob : public IDispatch
    get_JobId           proc :ptr
    get_Type            proc :ptr
    get_UserName        proc :ptr
    get_QueueStatus     proc :ptr
    get_DeviceStatus    proc :ptr
    get_PageCount       proc :ptr
    get_FaxNumber       proc :ptr
    get_RecipientName   proc :ptr
    get_Tsid            proc :ptr
    get_SenderName      proc :ptr
    get_SenderCompany   proc :ptr
    get_SenderDept      proc :ptr
    get_BillingCode     proc :ptr
    get_DisplayName     proc :ptr
    get_DiscountSend    proc :ptr
    SetStatus           proc :LONG
    Refresh             proc
   .ends

endif

ifndef __FAXCOMLib_LIBRARY_DEFINED__
define __FAXCOMLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_FAXCOMLib,        0x87099223,0xC7AF,0x11D0,0xB2,0x25,0x00,0xC0,0x4F,0xB6,0xC2,0xF5)
DEFINE_GUID(CLSID_FaxTiff,          0x87099231,0xC7AF,0x11D0,0xB2,0x25,0x00,0xC0,0x4F,0xB6,0xC2,0xF5)
DEFINE_GUID(CLSID_FaxServer,        0xD73733C8,0xCC80,0x11D0,0xB2,0x25,0x00,0xC0,0x4F,0xB6,0xC2,0xF5)
DEFINE_GUID(CLSID_FaxPort,          0xD73733CD,0xCC80,0x11D0,0xB2,0x25,0x00,0xC0,0x4F,0xB6,0xC2,0xF5)
DEFINE_GUID(CLSID_FaxPorts,         0xD73733D6,0xCC80,0x11D0,0xB2,0x25,0x00,0xC0,0x4F,0xB6,0xC2,0xF5)
DEFINE_GUID(CLSID_FaxRoutingMethod, 0x2199F5F4,0xCEFC,0x11D0,0xA3,0x41,0x00,0x00,0xF8,0x00,0xE6,0x8D)
DEFINE_GUID(CLSID_FaxRoutingMethods,0x2199F5F6,0xCEFC,0x11D0,0xA3,0x41,0x00,0x00,0xF8,0x00,0xE6,0x8D)
DEFINE_GUID(CLSID_FaxStatus,        0x8B97E606,0xD054,0x11D0,0xB2,0x26,0x00,0xC0,0x4F,0xB6,0xC2,0xF5)
DEFINE_GUID(CLSID_FaxDoc,           0xFA21F4C6,0x5C4C,0x11D1,0x83,0xCF,0x00,0xC0,0x4F,0xB6,0xE9,0x84)
DEFINE_GUID(CLSID_FaxJobs,          0x55DABFD4,0x5C9E,0x11D1,0xB7,0x91,0x00,0x00,0x00,0x00,0x00,0x00)
DEFINE_GUID(CLSID_FaxJob,           0x55DABFD6,0x5C9E,0x11D1,0xB7,0x91,0x00,0x00,0x00,0x00,0x00,0x00)

endif

endif

endif
