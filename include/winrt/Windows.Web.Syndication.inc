ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eweb2Esyndication_h__
define __windows2Eweb2Esyndication_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Data.Xml.Dom.inc
include Windows.Security.Credentials.inc
include Windows.Web.AtomPub.inc

.namespace Windows
.namespace Web
.namespace Syndication

.enum SyndicationFormat {
    SyndicationFormat_Atom10	= 0,
    SyndicationFormat_Rss20	= 1,
    SyndicationFormat_Rss10	= 2,
    SyndicationFormat_Rss092	= 3,
    SyndicationFormat_Rss091	= 4,
    SyndicationFormat_Atom03	= 5
    }

.enum SyndicationErrorStatus {
    SyndicationErrorStatus_Unknown	= 0,
    SyndicationErrorStatus_MissingRequiredElement	= 1,
    SyndicationErrorStatus_MissingRequiredAttribute	= 2,
    SyndicationErrorStatus_InvalidXml	= 3,
    SyndicationErrorStatus_UnexpectedContent	= 4,
    SyndicationErrorStatus_UnsupportedFormat	= 5
    }

.enum SyndicationTextType {
    SyndicationTextType_Text	= 0,
    SyndicationTextType_Html	= 1,
    SyndicationTextType_Xhtml	= 2
    }

.template RetrievalProgress
    BytesRetrieved		UINT32 ?
    TotalBytesToRetrieve	UINT32 ?
   .ends

.template TransferProgress
    BytesSent			UINT32 ?
    TotalBytesToSend		UINT32 ?
    BytesRetrieved		UINT32 ?
    TotalBytesToRetrieve	UINT32 ?
   .ends

.endn
.endn
.endn

ifndef ____FIIterator_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CSyndication__CISyndicationNode, "2dc8d9d6-0f44-5692-933e-f8902ab7fb94")

.comdef __FIIterator_1_Windows__CWeb__CSyndication__CISyndicationNode : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CSyndication__CISyndicationNode, "b486569a-72b3-57aa-9950-cea0b3e4fc58")

.comdef __FIIterable_1_Windows__CWeb__CSyndication__CISyndicationNode : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CSyndication__CSyndicationAttribute, "a76fcde8-f86f-5b75-aa7d-5787467a319d")

.comdef __FIIterator_1_Windows__CWeb__CSyndication__CSyndicationAttribute : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CSyndication__CSyndicationAttribute, "329eabe1-efcc-539e-96ba-f6a44f221dbd")

.comdef __FIIterable_1_Windows__CWeb__CSyndication__CSyndicationAttribute : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CSyndication__CSyndicationCategory, "2a9228fa-b088-5690-bb38-b7044e0b502b")

.comdef __FIIterator_1_Windows__CWeb__CSyndication__CSyndicationCategory : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CSyndication__CSyndicationCategory, "d151f7d1-eabd-5300-b55c-149eb289cc71")

.comdef __FIIterable_1_Windows__CWeb__CSyndication__CSyndicationCategory : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CSyndication__CSyndicationItem, "d5692aa3-d785-5db4-ac5c-b3832082e629")

.comdef __FIIterator_1_Windows__CWeb__CSyndication__CSyndicationItem : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CSyndication__CSyndicationItem, "55463eef-ecb8-59cd-8d6b-74daacbe7d19")

.comdef __FIIterable_1_Windows__CWeb__CSyndication__CSyndicationItem : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CSyndication__CSyndicationLink, "901642b7-6ca4-5b57-b8f1-73208342ba4a")

.comdef __FIIterator_1_Windows__CWeb__CSyndication__CSyndicationLink : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CSyndication__CSyndicationLink, "c6919f6a-66d9-556a-9632-87d39af14638")

.comdef __FIIterable_1_Windows__CWeb__CSyndication__CSyndicationLink : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CSyndication__CSyndicationPerson, "1745e807-f209-5da6-8855-7f99e25eb1fc")

.comdef __FIIterator_1_Windows__CWeb__CSyndication__CSyndicationPerson : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CSyndication__CSyndicationPerson, "e58e7844-eb34-5284-b09e-de6762d548ca")

.comdef __FIIterable_1_Windows__CWeb__CSyndication__CSyndicationPerson : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CSyndication__CISyndicationNode, "6b4bd4a1-b4f6-5433-afd7-bd2e501a1041")

.comdef __FIVectorView_1_Windows__CWeb__CSyndication__CISyndicationNode : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationAttribute, "c1d6d1cc-69ce-5486-9f35-c87e13111387")

.comdef __FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationAttribute : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationCategory, "a1ac007c-9d94-552e-840e-139f109a9b88")

.comdef __FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationCategory : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationItem, "9496279b-567e-5652-b942-f6fb70c34173")

.comdef __FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationItem : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationLink, "eb8b7ff6-fa64-576a-8be4-a055f7a04a73")

.comdef __FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationLink : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationPerson, "0e450d3d-e750-5787-885b-488abc72b5b9")

.comdef __FIVectorView_1_Windows__CWeb__CSyndication__CSyndicationPerson : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CSyndication__CISyndicationNode_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CSyndication__CISyndicationNode, "f4508afa-9f02-5eb8-a389-14bbe5193ac0")

.comdef __FIVector_1_Windows__CWeb__CSyndication__CISyndicationNode : public IInspectable

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

ifndef ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationAttribute_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CSyndication__CSyndicationAttribute, "2fe84e7b-2350-5941-94b5-a64677b585d1")

.comdef __FIVector_1_Windows__CWeb__CSyndication__CSyndicationAttribute : public IInspectable

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

ifndef ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationCategory_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CSyndication__CSyndicationCategory, "72e456e4-0e52-52cb-b363-f3581327f033")

.comdef __FIVector_1_Windows__CWeb__CSyndication__CSyndicationCategory : public IInspectable

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

ifndef ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CSyndication__CSyndicationItem, "aa01130b-4631-5117-8c48-dc21b0295096")

.comdef __FIVector_1_Windows__CWeb__CSyndication__CSyndicationItem : public IInspectable

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

ifndef ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationLink_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CSyndication__CSyndicationLink, "b8fb25a5-01c3-5207-814e-892b2b5343f7")

.comdef __FIVector_1_Windows__CWeb__CSyndication__CSyndicationLink : public IInspectable

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

ifndef ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CSyndication__CSyndicationPerson_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CSyndication__CSyndicationPerson, "ab772cd6-8ce7-5db9-83ac-0db9e44a1b0c")

.comdef __FIVector_1_Windows__CWeb__CSyndication__CSyndicationPerson : public IInspectable

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

ifndef ____FIAsyncActionProgressHandler_1_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
define ____FIAsyncActionProgressHandler_1_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncActionProgressHandler_1_Windows__CWeb__CSyndication__CTransferProgress, "c1610085-94d0-5706-9ac6-10179d7deb92")

.comdef __FIAsyncActionProgressHandler_1_Windows__CWeb__CSyndication__CTransferProgress : public IUnknown

    _Invoke		proc :ptr, :Windows::Web::Syndication::TransferProgress
   .ends

endif

ifndef ____FIAsyncActionWithProgressCompletedHandler_1_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
define ____FIAsyncActionWithProgressCompletedHandler_1_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncActionWithProgressCompletedHandler_1_Windows__CWeb__CSyndication__CTransferProgress, "f1c031c8-90bf-5cae-adf6-155b4aedfb60")

.comdef __FIAsyncActionWithProgressCompletedHandler_1_Windows__CWeb__CSyndication__CTransferProgress : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncActionWithProgress_1_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
define ____FIAsyncActionWithProgress_1_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncActionWithProgress_1_Windows__CWeb__CSyndication__CTransferProgress, "b7eb83f5-a746-50f2-b91f-31803161ccc7")

.comdef __FIAsyncActionWithProgress_1_Windows__CWeb__CSyndication__CTransferProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress, "6136b327-4152-54e3-aa34-38a0c121dc4d")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :Windows::Web::Syndication::RetrievalProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress, "76772ec1-c26f-5f6e-8d3b-8314107cefeb")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress, "f71cff65-e737-5345-b38f-fd445d2dc7e2")

.comdef __FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CSyndication__CRetrievalProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress, "dd2a6d54-55aa-5d09-b790-9520d4eb4f19")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :Windows::Web::Syndication::RetrievalProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress, "5f03b1d3-470d-5be7-8176-1c9a46010900")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress, "da07abf4-91fa-5c96-84cb-459ea97b934d")

.comdef __FIAsyncOperationWithProgress_2_Windows__CWeb__CAtomPub__CServiceDocument_Windows__CWeb__CSyndication__CRetrievalProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress, "1017bbe0-9d10-543e-8f03-885122a082f3")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :Windows::Web::Syndication::RetrievalProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress, "0e3d7f70-4e8c-5260-a7e5-786e05bded99")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress, "92eaf151-415e-5f87-8095-781623c88998")

.comdef __FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationFeed_Windows__CWeb__CSyndication__CRetrievalProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress, "b670d335-e83b-58b1-ad7b-840396085c65")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :Windows::Web::Syndication::RetrievalProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress, "9de7422b-4bc3-5546-87b8-2eebfd60be48")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress, "44fa5a15-1204-521c-85e5-01259301d527")

.comdef __FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CRetrievalProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress, "1ffb57b2-d2de-5559-8de2-50109c63539b")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress : public IUnknown

    _Invoke		proc :ptr, :Windows::Web::Syndication::TransferProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress, "8a796ea9-ff95-50ef-93ea-711bf7946473")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress, "e57d0717-27c0-561e-b4b3-72aa2b1e3fc9")

.comdef __FIAsyncOperationWithProgress_2_Windows__CWeb__CSyndication__CSyndicationItem_Windows__CWeb__CSyndication__CTransferProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

define InterfaceName_Windows_Web_Syndication_ISyndicationAttribute <L"Windows.Web.Syndication.ISyndicationAttribute">

.namespace Windows
.namespace Web
.namespace Syndication

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationAttribute_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationAttribute_INTERFACE_DEFINED__
DEFINE_IIDX(ISyndicationAttribute, "71E8F969-526E-4001-9A91-E84F83161AB1")

.comdef ISyndicationAttribute : public IInspectable

    get_Name		proc :ptr
    put_Name		proc :HSTRING
    get_Namespace	proc :ptr
    put_Namespace	proc :HSTRING
    get_Value		proc :ptr
    put_Value		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationAttributeFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationAttributeFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationAttributeFactory <L"Windows.Web.Syndication.ISyndicationAttributeFactory">
DEFINE_IIDX(ISyndicationAttributeFactory, "624F1599-ED3E-420F-BE86-640414886E4B")

.comdef ISyndicationAttributeFactory : public IInspectable

    CreateSyndicationAttribute proc :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationNode_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationNode_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationNode <L"Windows.Web.Syndication.ISyndicationNode">
DEFINE_IIDX(ISyndicationNode, "753CEF78-51F8-45C0-A9F5-F1719DEC3FB2")

.comdef ISyndicationNode : public IInspectable

    get_NodeName	proc :ptr
    put_NodeName	proc :HSTRING
    get_NodeNamespace	proc :ptr
    put_NodeNamespace	proc :HSTRING
    get_NodeValue	proc :ptr
    put_NodeValue	proc :HSTRING
    get_Language	proc :ptr
    put_Language	proc :HSTRING
    get_BaseUri		proc :ptr
    put_BaseUri		proc :ptr
    get_AttributeExtensions proc :ptr
    get_ElementExtensions proc :ptr
    GetXmlDocument	proc :Windows::Web::Syndication::SyndicationFormat, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationNodeFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationNodeFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationNodeFactory <L"Windows.Web.Syndication.ISyndicationNodeFactory">
DEFINE_IIDX(ISyndicationNodeFactory, "12902188-4ACB-49A8-B777-A5EB92E18A79")

.comdef ISyndicationNodeFactory : public IInspectable

    CreateSyndicationNode proc :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationGenerator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationGenerator_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationGenerator <L"Windows.Web.Syndication.ISyndicationGenerator">
DEFINE_IIDX(ISyndicationGenerator, "9768B379-FB2B-4F6D-B41C-088A5868825C")

.comdef ISyndicationGenerator : public IInspectable

    get_Text		proc :ptr
    put_Text		proc :HSTRING
    get_Uri		proc :ptr
    put_Uri		proc :ptr
    get_Version		proc :ptr
    put_Version		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationGeneratorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationGeneratorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationGeneratorFactory <L"Windows.Web.Syndication.ISyndicationGeneratorFactory">
DEFINE_IIDX(ISyndicationGeneratorFactory, "A34083E3-1E26-4DBC-BA9D-1AB84BEFF97B")

.comdef ISyndicationGeneratorFactory : public IInspectable

    CreateSyndicationGenerator proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationText_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationText_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationText <L"Windows.Web.Syndication.ISyndicationText">
DEFINE_IIDX(ISyndicationText, "B9CC5E80-313A-4091-A2A6-243E0EE923F9")

.comdef ISyndicationText : public IInspectable

    get_Text		proc :ptr
    put_Text		proc :HSTRING
    get_Type		proc :ptr
    put_Type		proc :HSTRING
    get_Xml		proc :ptr
    put_Xml		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationTextFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationTextFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationTextFactory <L"Windows.Web.Syndication.ISyndicationTextFactory">
DEFINE_IIDX(ISyndicationTextFactory, "EE7342F7-11C6-4B25-AB62-E596BD162946")

.comdef ISyndicationTextFactory : public IInspectable

    CreateSyndicationText proc :HSTRING, :ptr
    CreateSyndicationTextEx proc :HSTRING, :Windows::Web::Syndication::SyndicationTextType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationContent_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationContent_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationContent <L"Windows.Web.Syndication.ISyndicationContent">
DEFINE_IIDX(ISyndicationContent, "4641FEFE-0E55-40D0-B8D0-6A2CCBA9FC7C")

.comdef ISyndicationContent : public IInspectable

    get_SourceUri	proc :ptr
    put_SourceUri	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationContentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationContentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationContentFactory <L"Windows.Web.Syndication.ISyndicationContentFactory">
DEFINE_IIDX(ISyndicationContentFactory, "3D2FBB93-9520-4173-9388-7E2DF324A8A0")

.comdef ISyndicationContentFactory : public IInspectable

    CreateSyndicationContent proc :HSTRING, :Windows::Web::Syndication::SyndicationTextType, :ptr
    CreateSyndicationContentWithSourceUri proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationLink_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationLink_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationLink <L"Windows.Web.Syndication.ISyndicationLink">
DEFINE_IIDX(ISyndicationLink, "27553ABD-A10E-41B5-86BD-9759086EB0C5")

.comdef ISyndicationLink : public IInspectable

    get_Length		proc :ptr
    put_Length		proc :UINT32
    get_MediaType	proc :ptr
    put_MediaType	proc :HSTRING
    get_Relationship	proc :ptr
    put_Relationship	proc :HSTRING
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Uri		proc :ptr
    put_Uri		proc :ptr
    get_ResourceLanguage proc :ptr
    put_ResourceLanguage proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationLinkFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationLinkFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationLinkFactory <L"Windows.Web.Syndication.ISyndicationLinkFactory">
DEFINE_IIDX(ISyndicationLinkFactory, "5ED863D4-5535-48AC-98D4-C190995080B3")

.comdef ISyndicationLinkFactory : public IInspectable

    CreateSyndicationLink proc :ptr, :ptr
    CreateSyndicationLinkEx proc :ptr, :HSTRING, :HSTRING, :HSTRING, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationPerson_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationPerson_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationPerson <L"Windows.Web.Syndication.ISyndicationPerson">
DEFINE_IIDX(ISyndicationPerson, "FA1EE5DA-A7C6-4517-A096-0143FAF29327")

.comdef ISyndicationPerson : public IInspectable

    get_Email		proc :ptr
    put_Email		proc :HSTRING
    get_Name		proc :ptr
    put_Name		proc :HSTRING
    get_Uri		proc :ptr
    put_Uri		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationPersonFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationPersonFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationPersonFactory <L"Windows.Web.Syndication.ISyndicationPersonFactory">
DEFINE_IIDX(ISyndicationPersonFactory, "DCF4886D-229D-4B58-A49B-F3D2F0F5C99F")

.comdef ISyndicationPersonFactory : public IInspectable

    CreateSyndicationPerson proc :HSTRING, :ptr
    CreateSyndicationPersonEx proc :HSTRING, :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationCategory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationCategory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationCategory <L"Windows.Web.Syndication.ISyndicationCategory">
DEFINE_IIDX(ISyndicationCategory, "8715626F-0CBA-4A7F-89FF-ECB5281423B6")

.comdef ISyndicationCategory : public IInspectable

    get_Label		proc :ptr
    put_Label		proc :HSTRING
    get_Scheme		proc :ptr
    put_Scheme		proc :HSTRING
    get_Term		proc :ptr
    put_Term		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationCategoryFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationCategoryFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationCategoryFactory <L"Windows.Web.Syndication.ISyndicationCategoryFactory">
DEFINE_IIDX(ISyndicationCategoryFactory, "AB42802F-49E0-4525-8AB2-AB45C02528FF")

.comdef ISyndicationCategoryFactory : public IInspectable

    CreateSyndicationCategory proc :HSTRING, :ptr
    CreateSyndicationCategoryEx proc :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationItem_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationItem <L"Windows.Web.Syndication.ISyndicationItem">
DEFINE_IIDX(ISyndicationItem, "548DB883-C384-45C1-8AE8-A378C4EC486C")

.comdef ISyndicationItem : public IInspectable

    get_Authors		proc :ptr
    get_Categories	proc :ptr
    get_Contributors	proc :ptr
    get_Content		proc :ptr
    put_Content		proc :ptr
    get_Id		proc :ptr
    put_Id		proc :HSTRING
    get_LastUpdatedTime proc :ptr
    put_LastUpdatedTime proc :Windows::Foundation::DateTime
    get_Links		proc :ptr
    get_PublishedDate	proc :ptr
    put_PublishedDate	proc :Windows::Foundation::DateTime
    get_Rights		proc :ptr
    put_Rights		proc :ptr
    get_Source		proc :ptr
    put_Source		proc :ptr
    get_Summary		proc :ptr
    put_Summary		proc :ptr
    get_Title		proc :ptr
    put_Title		proc :ptr
    get_CommentsUri	proc :ptr
    put_CommentsUri	proc :ptr
    get_EditUri		proc :ptr
    get_EditMediaUri	proc :ptr
    get_ETag		proc :ptr
    get_ItemUri		proc :ptr
    Load		proc :HSTRING
    LoadFromXml		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationItemFactory <L"Windows.Web.Syndication.ISyndicationItemFactory">
DEFINE_IIDX(ISyndicationItemFactory, "251D434F-7DB8-487A-85E4-10D191E66EBB")

.comdef ISyndicationItemFactory : public IInspectable

    CreateSyndicationItem proc :HSTRING, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationFeed_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationFeed_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationFeed <L"Windows.Web.Syndication.ISyndicationFeed">
DEFINE_IIDX(ISyndicationFeed, "7FFE3CD2-5B66-4D62-8403-1BC10D910D6B")

.comdef ISyndicationFeed : public IInspectable

    get_Authors		proc :ptr
    get_Categories	proc :ptr
    get_Contributors	proc :ptr
    get_Generator	proc :ptr
    put_Generator	proc :ptr
    get_IconUri		proc :ptr
    put_IconUri		proc :ptr
    get_Id		proc :ptr
    put_Id		proc :HSTRING
    get_Items		proc :ptr
    get_LastUpdatedTime proc :ptr
    put_LastUpdatedTime proc :Windows::Foundation::DateTime
    get_Links		proc :ptr
    get_ImageUri	proc :ptr
    put_ImageUri	proc :ptr
    get_Rights		proc :ptr
    put_Rights		proc :ptr
    get_Subtitle	proc :ptr
    put_Subtitle	proc :ptr
    get_Title		proc :ptr
    put_Title		proc :ptr
    get_FirstUri	proc :ptr
    get_LastUri		proc :ptr
    get_NextUri		proc :ptr
    get_PreviousUri	proc :ptr
    get_SourceFormat	proc :ptr
    Load		proc :HSTRING
    LoadFromXml		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationFeedFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationFeedFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationFeedFactory <L"Windows.Web.Syndication.ISyndicationFeedFactory">
DEFINE_IIDX(ISyndicationFeedFactory, "23472232-8BE9-48B7-8934-6205131D9357")

.comdef ISyndicationFeedFactory : public IInspectable

    CreateSyndicationFeed proc :HSTRING, :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationClient_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationClient_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationClient <L"Windows.Web.Syndication.ISyndicationClient">
DEFINE_IIDX(ISyndicationClient, "9E18A9B7-7249-4B45-B229-7DF895A5A1F5")

.comdef ISyndicationClient : public IInspectable

    get_ServerCredential proc :ptr
    put_ServerCredential proc :ptr
    get_ProxyCredential proc :ptr
    put_ProxyCredential proc :ptr
    get_MaxResponseBufferSize proc :ptr
    put_MaxResponseBufferSize proc :UINT32
    get_Timeout		proc :ptr
    put_Timeout		proc :UINT32
    get_BypassCacheOnRetrieve proc :ptr
    put_BypassCacheOnRetrieve proc :boolean
    SetRequestHeader	proc :HSTRING, :HSTRING
    RetrieveFeedAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationClientFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationClientFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationClientFactory <L"Windows.Web.Syndication.ISyndicationClientFactory">
DEFINE_IIDX(ISyndicationClientFactory, "2EC4B32C-A79B-4114-B29A-05DFFBAFB9A4")

.comdef ISyndicationClientFactory : public IInspectable

    CreateSyndicationClient proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationErrorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CSyndication_CISyndicationErrorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Syndication_ISyndicationErrorStatics <L"Windows.Web.Syndication.ISyndicationErrorStatics">
DEFINE_IIDX(ISyndicationErrorStatics, "1FBB2361-45C7-4833-8AA0-BE5F3B58A7F4")

.comdef ISyndicationErrorStatics : public IInspectable

    GetStatus		proc :INT32, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationAttribute_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationAttribute_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationAttribute <L"Windows.Web.Syndication.SyndicationAttribute">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationNode_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationNode_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationNode <L"Windows.Web.Syndication.SyndicationNode">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationGenerator_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationGenerator_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationGenerator <L"Windows.Web.Syndication.SyndicationGenerator">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationText_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationText_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationText <L"Windows.Web.Syndication.SyndicationText">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationContent_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationContent_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationContent <L"Windows.Web.Syndication.SyndicationContent">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationLink_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationLink_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationLink <L"Windows.Web.Syndication.SyndicationLink">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationPerson_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationPerson_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationPerson <L"Windows.Web.Syndication.SyndicationPerson">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationCategory_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationCategory_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationCategory <L"Windows.Web.Syndication.SyndicationCategory">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationFeed_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationFeed_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationFeed <L"Windows.Web.Syndication.SyndicationFeed">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationItem_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationItem_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationItem <L"Windows.Web.Syndication.SyndicationItem">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationClient_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationClient_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationClient <L"Windows.Web.Syndication.SyndicationClient">
endif
ifndef RUNTIMECLASS_Windows_Web_Syndication_SyndicationError_DEFINED
define RUNTIMECLASS_Windows_Web_Syndication_SyndicationError_DEFINED
define RuntimeClass_Windows_Web_Syndication_SyndicationError <L"Windows.Web.Syndication.SyndicationError">
endif

endif
