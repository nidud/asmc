ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edevices2Esmartcards_h__
define __windows2Edevices2Esmartcards_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

ifndef ____FIIterator_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CSmartCards__CSmartCard, "86b29903-916e-5817-bc96-df324475e31a")

.comdef __FIIterator_1_Windows__CDevices__CSmartCards__CSmartCard : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CSmartCards__CSmartCard, "a32c5202-d113-535f-880e-50f3e5121ef8")

.comdef __FIIterable_1_Windows__CDevices__CSmartCards__CSmartCard : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard, "4bee6991-3508-5f03-a2f4-90a5ddb26bd8")

.comdef __FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext, "96b172f6-dedb-5f3e-af90-7b0f10219352")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext, "1c650663-3f68-599b-b9d4-c350f13ee4e4")

.comdef __FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardChallengeContext : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning, "7a2e58dc-22ee-5cb8-83cc-a7a61b9dcd2c")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning, "6184fc80-b752-5ce8-a136-f57174bb9309")

.comdef __FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardProvisioning : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReader_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReader_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReader, "20d3244d-375a-5f7d-8944-164fdfed4239")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReader : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReader_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReader_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReader, "036a830d-bbca-5cb9-977f-b29ea3042149")

.comdef __FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReader : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus, "3d7e6ea9-e739-555c-9c02-07396c5321f5")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus, "5ae402fa-1f22-5570-a0c8-b2320adedb81")

.comdef __FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardReaderStatus : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardStatus_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardStatus, "bdaf4a41-3b4a-56b0-aeec-fee71cc7f328")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CSmartCards__CSmartCardStatus : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardStatus_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardStatus, "e2223376-8cf6-51bd-9907-1344aa665e5d")

.comdef __FIAsyncOperation_1_Windows__CDevices__CSmartCards__CSmartCardStatus : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard, "bfea3fad-411e-5721-88f5-92c9b9fbbe14")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard, "3b2691b2-fc5e-59ff-8c6f-e6dd29a967fc")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CDevices__CSmartCards__CSmartCard : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardAddedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardAddedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardAddedEventArgs, "d36f2db9-5674-5f74-9f69-3cdc4559999f")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardAddedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardRemovedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardRemovedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardRemovedEventArgs, "69da07c6-b266-5a1c-937c-d82b4a8232c6")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSmartCards__CSmartCardReader_Windows__CDevices__CSmartCards__CCardRemovedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace SmartCards

.enum SmartCardReaderKind {
    SmartCardReaderKind_Any	= 0,
    SmartCardReaderKind_Generic = 1,
    SmartCardReaderKind_Tpm	= 2,
    SmartCardReaderKind_Nfc	= 3,
    SmartCardReaderKind_Uicc	= 4
    }

.enum SmartCardReaderStatus {
    SmartCardReaderStatus_Disconnected	= 0,
    SmartCardReaderStatus_Ready = 1,
    SmartCardReaderStatus_Exclusive	= 2
    }

.enum SmartCardStatus {
    SmartCardStatus_Disconnected	= 0,
    SmartCardStatus_Ready	= 1,
    SmartCardStatus_Shared	= 2,
    SmartCardStatus_Exclusive	= 3,
    SmartCardStatus_Unresponsive	= 4
    }

.enum SmartCardPinCharacterPolicyOption {
    SmartCardPinCharacterPolicyOption_Allow	= 0,
    SmartCardPinCharacterPolicyOption_RequireAtLeastOne = 1,
    SmartCardPinCharacterPolicyOption_Disallow	= 2
    }

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinResetHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinResetHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISmartCardPinResetHandler, "138D5E40-F3BC-4A5C-B41D-4B4EF684E237")

.comdef ISmartCardPinResetHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardReaderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardReaderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardReaderStatics <L"Windows.Devices.SmartCards.ISmartCardReaderStatics">
DEFINE_IIDX(ISmartCardReaderStatics, "103C04E1-A1CA-48F2-A281-5B6F669AF107")

.comdef ISmartCardReaderStatics : public IInspectable

    GetDeviceSelector	proc :ptr
    GetDeviceSelectorWithKind proc :Windows::Devices::SmartCards::SmartCardReaderKind, :ptr
    FromIdAsync		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardReader_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardReader_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardReader <L"Windows.Devices.SmartCards.ISmartCardReader">
DEFINE_IIDX(ISmartCardReader, "1074B4E0-54C2-4DF0-817A-14C14378F06C")

.comdef ISmartCardReader : public IInspectable

    get_DeviceId	proc :ptr
    get_Name		proc :ptr
    get_Kind		proc :ptr
    GetStatusAsync	proc :ptr
    FindAllCardsAsync	proc :ptr
    add_CardAdded	proc :ptr, :ptr
    remove_CardAdded	proc :EventRegistrationToken
    add_CardRemoved	proc :ptr, :ptr
    remove_CardRemoved	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CICardAddedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CICardAddedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ICardAddedEventArgs <L"Windows.Devices.SmartCards.ICardAddedEventArgs">
DEFINE_IIDX(ICardAddedEventArgs, "18BBEF98-F18B-4DD3-B118-DFB2C8E23CC6")

.comdef ICardAddedEventArgs : public IInspectable

    get_SmartCard	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CICardRemovedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CICardRemovedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ICardRemovedEventArgs <L"Windows.Devices.SmartCards.ICardRemovedEventArgs">
DEFINE_IIDX(ICardRemovedEventArgs, "15331AAF-22D7-4945-AFC9-03B46F42A6CD")

.comdef ICardRemovedEventArgs : public IInspectable

    get_SmartCard	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCard_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCard_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCard <L"Windows.Devices.SmartCards.ISmartCard">
DEFINE_IIDX(ISmartCard, "1B718871-6434-43F4-B55A-6A29623870AA")

.comdef ISmartCard : public IInspectable

    get_Reader		proc :ptr
    GetStatusAsync	proc :ptr
    GetAnswerToResetAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardProvisioningStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardProvisioningStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardProvisioningStatics <L"Windows.Devices.SmartCards.ISmartCardProvisioningStatics">
DEFINE_IIDX(ISmartCardProvisioningStatics, "13882848-0D13-4E70-9735-51DAECA5254F")

.comdef ISmartCardProvisioningStatics : public IInspectable

    FromSmartCardAsync	proc :ptr, :ptr
    RequestVirtualSmartCardCreationAsync proc :HSTRING, :ptr, :ptr, :ptr
    RequestVirtualSmartCardCreationAsyncWithCardId proc :HSTRING, :ptr, :ptr, :GUID, :ptr
    RequestVirtualSmartCardDeletionAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardProvisioning_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardProvisioning_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardProvisioning <L"Windows.Devices.SmartCards.ISmartCardProvisioning">
DEFINE_IIDX(ISmartCardProvisioning, "19EEEDBD-1FAB-477C-B712-1A2C5AF1FD6E")

.comdef ISmartCardProvisioning : public IInspectable

    get_SmartCard	proc :ptr
    GetIdAsync		proc :ptr
    GetNameAsync	proc :ptr
    GetChallengeContextAsync proc :ptr
    RequestPinChangeAsync proc :ptr
    RequestPinResetAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinResetRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinResetRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardPinResetRequest <L"Windows.Devices.SmartCards.ISmartCardPinResetRequest">
DEFINE_IIDX(ISmartCardPinResetRequest, "12FE3C4D-5FB9-4E8E-9FF6-61F475124FEF")

.comdef ISmartCardPinResetRequest : public IInspectable

    get_Challenge	proc :ptr
    get_Deadline	proc :ptr
    GetDeferral		proc :ptr
    SetResponse		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinResetDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinResetDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardPinResetDeferral <L"Windows.Devices.SmartCards.ISmartCardPinResetDeferral">
DEFINE_IIDX(ISmartCardPinResetDeferral, "18C94AAC-7805-4004-85E4-BBEFAC8F6884")

.comdef ISmartCardPinResetDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinPolicy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardPinPolicy_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardPinPolicy <L"Windows.Devices.SmartCards.ISmartCardPinPolicy">
DEFINE_IIDX(ISmartCardPinPolicy, "183CE184-4DB6-4841-AC9E-2AC1F39B7304")

.comdef ISmartCardPinPolicy : public IInspectable

    get_MinLength	proc :ptr
    put_MinLength	proc :UINT32
    get_MaxLength	proc :ptr
    put_MaxLength	proc :UINT32
    get_UppercaseLetters proc :ptr
    put_UppercaseLetters proc :Windows::Devices::SmartCards::SmartCardPinCharacterPolicyOption
    get_LowercaseLetters proc :ptr
    put_LowercaseLetters proc :Windows::Devices::SmartCards::SmartCardPinCharacterPolicyOption
    get_Digits		proc :ptr
    put_Digits		proc :Windows::Devices::SmartCards::SmartCardPinCharacterPolicyOption
    get_SpecialCharacters proc :ptr
    put_SpecialCharacters proc :Windows::Devices::SmartCards::SmartCardPinCharacterPolicyOption
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardChallengeContext_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSmartCards_CISmartCardChallengeContext_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_SmartCards_ISmartCardChallengeContext <L"Windows.Devices.SmartCards.ISmartCardChallengeContext">
DEFINE_IIDX(ISmartCardChallengeContext, "192A5319-C9C4-4947-81CC-44794A61EF91")

.comdef ISmartCardChallengeContext : public IInspectable

    get_Challenge	proc :ptr
    VerifyResponseAsync proc :ptr, :ptr
    ProvisionAsync	proc :ptr, :boolean, :ptr
    ProvisionAsyncWithNewCardId proc :ptr, :boolean, :GUID, :ptr
    ChangeAdministrativeKeyAsync proc :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardReader_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardReader_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_SmartCardReader <L"Windows.Devices.SmartCards.SmartCardReader">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_SmartCard_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_SmartCard_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_SmartCard <L"Windows.Devices.SmartCards.SmartCard">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_CardAddedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_CardAddedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_CardAddedEventArgs <L"Windows.Devices.SmartCards.CardAddedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_CardRemovedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_CardRemovedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_CardRemovedEventArgs <L"Windows.Devices.SmartCards.CardRemovedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardProvisioning_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardProvisioning_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_SmartCardProvisioning <L"Windows.Devices.SmartCards.SmartCardProvisioning">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardPinPolicy_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardPinPolicy_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_SmartCardPinPolicy <L"Windows.Devices.SmartCards.SmartCardPinPolicy">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardChallengeContext_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardChallengeContext_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_SmartCardChallengeContext <L"Windows.Devices.SmartCards.SmartCardChallengeContext">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardPinResetRequest_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardPinResetRequest_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_SmartCardPinResetRequest <L"Windows.Devices.SmartCards.SmartCardPinResetRequest">
endif
ifndef RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardPinResetDeferral_DEFINED
define RUNTIMECLASS_Windows_Devices_SmartCards_SmartCardPinResetDeferral_DEFINED
define RuntimeClass_Windows_Devices_SmartCards_SmartCardPinResetDeferral <L"Windows.Devices.SmartCards.SmartCardPinResetDeferral">
endif

endif

