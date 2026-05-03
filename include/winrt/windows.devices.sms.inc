ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edevices2Esms_h__
define __windows2Edevices2Esms_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

ifndef ____FIIterator_1_Windows__CDevices__CSms__CISmsBinaryMessage_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CSms__CISmsBinaryMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CSms__CISmsBinaryMessage, "13e60d89-ea0a-5b01-9c2f-0e5b435058e0")

.comdef __FIIterator_1_Windows__CDevices__CSms__CISmsBinaryMessage : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CSms__CISmsBinaryMessage_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CSms__CISmsBinaryMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CSms__CISmsBinaryMessage, "5678a6a5-4d5a-51c2-a133-4b83bf25d987")

.comdef __FIIterable_1_Windows__CDevices__CSms__CISmsBinaryMessage : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CSms__CISmsMessage, "eed04f5c-b2b2-5c83-8b13-c78af6ca3a18")

.comdef __FIIterator_1_Windows__CDevices__CSms__CISmsMessage : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CSms__CISmsMessage, "ecabfd70-9601-5e38-83cf-b1046022a244")

.comdef __FIIterable_1_Windows__CDevices__CSms__CISmsMessage : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CSms__CISmsBinaryMessage_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CSms__CISmsBinaryMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CSms__CISmsBinaryMessage, "6ea176ea-99ea-5c79-876a-f4c437b83df6")

.comdef __FIVectorView_1_Windows__CDevices__CSms__CISmsBinaryMessage : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CSms__CISmsMessage, "d3acc5b1-6f85-507e-b40a-6950749b426f")

.comdef __FIVectorView_1_Windows__CDevices__CSms__CISmsMessage : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int, "3f9d1255-ebf8-569f-91c3-49740d5944ce")

.comdef __FIAsyncOperationProgressHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int : public IUnknown

    _Invoke		proc :ptr, :SINT
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int, "c0454cfc-2f2f-5e0c-8de9-58b9e82a03ba")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int, "12f85589-415d-5b5d-b0d0-fda3b0295adc")

.comdef __FIAsyncOperationWithProgress_2___FIVectorView_1_Windows__CDevices__CSms__CISmsMessage_int : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CISmsMessage, "4e6c4c86-ebe6-55d9-adc0-fecc38c82aa2")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CISmsMessage : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CSms__CISmsMessage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CSms__CISmsMessage, "abf9b459-48c3-5eac-9749-4c6db4d507e6")

.comdef __FIAsyncOperation_1_Windows__CDevices__CSms__CISmsMessage : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CSmsDevice_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CSmsDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CSmsDevice, "44aa5484-43d0-5893-a4ee-7db00113ae60")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSms__CSmsDevice : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CSms__CSmsDevice_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CSms__CSmsDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CSms__CSmsDevice, "ab710de1-fcbb-5bd6-9f2f-285fa9fb44e8")

.comdef __FIAsyncOperation_1_Windows__CDevices__CSms__CSmsDevice : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Sms

.enum SmsMessageClass {
    SmsMessageClass_None	= 0,
    SmsMessageClass_Class0	= 1,
    SmsMessageClass_Class1	= 2,
    SmsMessageClass_Class2	= 3,
    SmsMessageClass_Class3	= 4
    }

.enum SmsDataFormat {
    SmsDataFormat_Unknown	= 0,
    SmsDataFormat_CdmaSubmit	= 1,
    SmsDataFormat_GsmSubmit	= 2,
    SmsDataFormat_CdmaDeliver	= 3,
    SmsDataFormat_GsmDeliver	= 4
    }

.enum SmsEncoding {
    SmsEncoding_Unknown = 0,
    SmsEncoding_Optimal = 1,
    SmsEncoding_SevenBitAscii	= 2,
    SmsEncoding_Unicode = 3,
    SmsEncoding_GsmSevenBit	= 4
    }

.enum SmsMessageFilter {
    SmsMessageFilter_All	= 0,
    SmsMessageFilter_Unread	= 1,
    SmsMessageFilter_Read	= 2,
    SmsMessageFilter_Sent	= 3,
    SmsMessageFilter_Draft	= 4
    }

.enum SmsMessageType {
    SmsMessageType_Binary	= 0,
    SmsMessageType_Text = 1
    }

.enum CellularClass {
    CellularClass_None	= 0,
    CellularClass_Gsm	= 1,
    CellularClass_Cdma	= 2
    }

.enum SmsDeviceStatus {
    SmsDeviceStatus_Off = 0,
    SmsDeviceStatus_Ready	= 1,
    SmsDeviceStatus_SimNotInserted	= 2,
    SmsDeviceStatus_BadSim	= 3,
    SmsDeviceStatus_DeviceFailure	= 4,
    SmsDeviceStatus_SubscriptionNotActivated	= 5,
    SmsDeviceStatus_DeviceLocked	= 6,
    SmsDeviceStatus_DeviceBlocked	= 7
    }

.template SmsEncodedLength
    SegmentCount		UINT32 ?
    CharacterCountLastSegment	UINT32 ?
    CharactersPerSegment	UINT32 ?
    ByteCountLastSegment	UINT32 ?
    BytesPerSegment		UINT32 ?
   .ends

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsMessageReceivedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsMessageReceivedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISmsMessageReceivedEventHandler, "0B7AD409-EC2D-47CE-A253-732BEEEBCACD")

.comdef ISmsMessageReceivedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif
ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceStatusChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceStatusChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISmsDeviceStatusChangedEventHandler, "982B1162-3DD7-4618-AF89-0C272D5D06D8")

.comdef ISmsDeviceStatusChangedEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsMessage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsMessage_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsMessage <L"Windows.Devices.Sms.ISmsMessage">
DEFINE_IIDX(ISmsMessage, "ED3C5E28-6984-4B07-811D-8D5906ED3CEA")

.comdef ISmsMessage : public IInspectable

    get_Id		proc :ptr
    get_MessageClass	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsBinaryMessage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsBinaryMessage_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsBinaryMessage <L"Windows.Devices.Sms.ISmsBinaryMessage">
DEFINE_IIDX(ISmsBinaryMessage, "5BF4E813-3B53-4C6E-B61A-D86A63755650")

.comdef ISmsBinaryMessage : public IInspectable

    get_Format		proc :ptr
    put_Format		proc :Windows::Devices::Sms::SmsDataFormat
    GetData		proc :ptr, :ptr
    SetData		proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsTextMessage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsTextMessage_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsTextMessage <L"Windows.Devices.Sms.ISmsTextMessage">
DEFINE_IIDX(ISmsTextMessage, "D61C904C-A495-487F-9A6F-971548C5BC9F")

.comdef ISmsTextMessage : public IInspectable

    get_Timestamp	proc :ptr
    get_PartReferenceId proc :ptr
    get_PartNumber	proc :ptr
    get_PartCount	proc :ptr
    get_To		proc :ptr
    put_To		proc :HSTRING
    get_From		proc :ptr
    put_From		proc :HSTRING
    get_Body		proc :ptr
    put_Body		proc :HSTRING
    get_Encoding	proc :ptr
    put_Encoding	proc :Windows::Devices::Sms::SmsEncoding
    ToBinaryMessages	proc :Windows::Devices::Sms::SmsDataFormat, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsTextMessageStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsTextMessageStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsTextMessageStatics <L"Windows.Devices.Sms.ISmsTextMessageStatics">
DEFINE_IIDX(ISmsTextMessageStatics, "7F68C5ED-3CCC-47A3-8C55-380D3B010892")

.comdef ISmsTextMessageStatics : public IInspectable

    FromBinaryMessage	proc :ptr, :ptr
    FromBinaryData	proc :Windows::Devices::Sms::SmsDataFormat, :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceMessageStore_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceMessageStore_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsDeviceMessageStore <L"Windows.Devices.Sms.ISmsDeviceMessageStore">
DEFINE_IIDX(ISmsDeviceMessageStore, "9889F253-F188-4427-8D54-CE0C2423C5C1")

.comdef ISmsDeviceMessageStore : public IInspectable

    DeleteMessageAsync	proc :UINT32, :ptr
    DeleteMessagesAsync proc :Windows::Devices::Sms::SmsMessageFilter, :ptr
    GetMessageAsync	proc :UINT32, :ptr
    GetMessagesAsync	proc :Windows::Devices::Sms::SmsMessageFilter, :ptr
    get_MaxMessages	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsMessageReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsMessageReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsMessageReceivedEventArgs <L"Windows.Devices.Sms.ISmsMessageReceivedEventArgs">
DEFINE_IIDX(ISmsMessageReceivedEventArgs, "08E80A98-B8E5-41C1-A3D8-D3ABFAE22675")

.comdef ISmsMessageReceivedEventArgs : public IInspectable

    get_TextMessage	proc :ptr
    get_BinaryMessage	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsDeviceStatics <L"Windows.Devices.Sms.ISmsDeviceStatics">
DEFINE_IIDX(ISmsDeviceStatics, "F88D07EA-D815-4DD1-A234-4520CE4604A4")

.comdef ISmsDeviceStatics : public IInspectable

    GetDeviceSelector	proc :ptr
    FromIdAsync		proc :HSTRING, :ptr
    GetDefaultAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsDeviceStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsDeviceStatics2 <L"Windows.Devices.Sms.ISmsDeviceStatics2">
DEFINE_IIDX(ISmsDeviceStatics2, "2CA11C87-0873-4CAF-8A7D-BD471E8586D1")

.comdef ISmsDeviceStatics2 : public IInspectable

    FromNetworkAccountIdAsync proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsDevice <L"Windows.Devices.Sms.ISmsDevice">
DEFINE_IIDX(ISmsDevice, "091791ED-872B-4EEC-9C72-AB11627B34EC")

.comdef ISmsDevice : public IInspectable

    SendMessageAsync	proc :ptr, :ptr
    CalculateLength	proc :ptr, :ptr
    get_AccountPhoneNumber proc :ptr
    get_CellularClass	proc :ptr
    get_MessageStore	proc :ptr
    get_DeviceStatus	proc :ptr
    add_SmsMessageReceived proc :ptr, :ptr
    remove_SmsMessageReceived proc :EventRegistrationToken
    add_SmsDeviceStatusChanged proc :ptr, :ptr
    remove_SmsDeviceStatusChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsReceivedEventDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsReceivedEventDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsReceivedEventDetails <L"Windows.Devices.Sms.ISmsReceivedEventDetails">
DEFINE_IIDX(ISmsReceivedEventDetails, "5BB50F15-E46D-4C82-847D-5A0304C1D53D")

.comdef ISmsReceivedEventDetails : public IInspectable

    get_DeviceId	proc :ptr
    get_MessageIndex	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSms_CISmsReceivedEventDetails2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSms_CISmsReceivedEventDetails2_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sms_ISmsReceivedEventDetails2 <L"Windows.Devices.Sms.ISmsReceivedEventDetails2">
DEFINE_IIDX(ISmsReceivedEventDetails2, "40E05C86-A7B4-4771-9AE7-0B5FFB12C03A")

.comdef ISmsReceivedEventDetails2 : public IInspectable

    get_MessageClass	proc :ptr
    get_BinaryMessage	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Sms_SmsBinaryMessage_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_SmsBinaryMessage_DEFINED
define RuntimeClass_Windows_Devices_Sms_SmsBinaryMessage <L"Windows.Devices.Sms.SmsBinaryMessage">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_SmsTextMessage_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_SmsTextMessage_DEFINED
define RuntimeClass_Windows_Devices_Sms_SmsTextMessage <L"Windows.Devices.Sms.SmsTextMessage">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_DeleteSmsMessageOperation_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_DeleteSmsMessageOperation_DEFINED
define RuntimeClass_Windows_Devices_Sms_DeleteSmsMessageOperation <L"Windows.Devices.Sms.DeleteSmsMessageOperation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_DeleteSmsMessagesOperation_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_DeleteSmsMessagesOperation_DEFINED
define RuntimeClass_Windows_Devices_Sms_DeleteSmsMessagesOperation <L"Windows.Devices.Sms.DeleteSmsMessagesOperation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_GetSmsMessageOperation_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_GetSmsMessageOperation_DEFINED
define RuntimeClass_Windows_Devices_Sms_GetSmsMessageOperation <L"Windows.Devices.Sms.GetSmsMessageOperation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_GetSmsMessagesOperation_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_GetSmsMessagesOperation_DEFINED
define RuntimeClass_Windows_Devices_Sms_GetSmsMessagesOperation <L"Windows.Devices.Sms.GetSmsMessagesOperation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_SmsDeviceMessageStore_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_SmsDeviceMessageStore_DEFINED
define RuntimeClass_Windows_Devices_Sms_SmsDeviceMessageStore <L"Windows.Devices.Sms.SmsDeviceMessageStore">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_SendSmsMessageOperation_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_SendSmsMessageOperation_DEFINED
define RuntimeClass_Windows_Devices_Sms_SendSmsMessageOperation <L"Windows.Devices.Sms.SendSmsMessageOperation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_SmsMessageReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_SmsMessageReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sms_SmsMessageReceivedEventArgs <L"Windows.Devices.Sms.SmsMessageReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_SmsDevice_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_SmsDevice_DEFINED
define RuntimeClass_Windows_Devices_Sms_SmsDevice <L"Windows.Devices.Sms.SmsDevice">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_GetSmsDeviceOperation_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_GetSmsDeviceOperation_DEFINED
define RuntimeClass_Windows_Devices_Sms_GetSmsDeviceOperation <L"Windows.Devices.Sms.GetSmsDeviceOperation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sms_SmsReceivedEventDetails_DEFINED
define RUNTIMECLASS_Windows_Devices_Sms_SmsReceivedEventDetails_DEFINED
define RuntimeClass_Windows_Devices_Sms_SmsReceivedEventDetails <L"Windows.Devices.Sms.SmsReceivedEventDetails">
endif

endif
