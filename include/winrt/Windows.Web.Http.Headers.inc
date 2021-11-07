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

ifndef __windows2Eweb2Ehttp2Eheaders_h__
define __windows2Eweb2Ehttp2Eheaders_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Globalization.inc
include Windows.Networking.inc
include Windows.Storage.Streams.inc
include Windows.Web.Http.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue, "6bc05705-2c6f-57e8-bf96-56a761e90e8f")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue, "17847e58-f0cf-52e7-81c0-9d06a081569f")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue, "e95057be-e8bd-53df-a2f6-865a66a07c6b")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue, "1afc512f-dfa2-5528-8aef-6e6a37789b3c")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue, "e21ad0b2-c893-5360-a4fe-f083b308a9cd")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue, "0e8960c2-76e5-56c1-9fe6-8cd9018a6786")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue, "3780c808-8b98-5327-84c7-055363fe32ad")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue, "916e6271-cef6-53b8-b93f-dc8dca559e50")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue, "ed3b6323-b1c3-558b-9917-0826c4a9e8c0")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue, "16773244-5011-5244-bb00-14db4cf71005")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue, "6b72326a-46b1-5d80-a162-c5f45be02e2b")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue, "0a391c2b-13c3-59b8-8662-13affb9d1754")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue, "a25503de-4aef-5ef4-9f06-5df4094051be")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue, "0c5a4a0d-dbb7-5abf-a5fd-c3b98d9c1487")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue, "6a2084a3-941a-5528-a2ec-28cf1ff9b1a9")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue, "ffc7dfde-58b8-51e9-b33b-65a5d6a4e24c")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue, "3bb0c8fa-5f1f-5c70-9950-5d1d1a703dd4")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue, "5838a126-b617-5417-b32e-ded2d27d40a3")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue, "4f785951-b59c-5108-b0cd-1437578af49c")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue, "bf97cf99-e614-5765-bad7-161ae3a93ae9")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue, "49e58dec-b5cd-5ba4-a603-365d1588ad4c")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue, "57402048-38bf-5055-acb6-5c4da765e388")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue, "8b79423f-b4a3-501d-bac2-b88e78e13a21")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue, "1beae481-9d30-5ac8-942c-49a5f8737adf")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue, "dcdf2620-b6d0-5835-8bec-d3b946a50f55")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue, "eb18569b-a7ab-58bb-8880-dd022f755b51")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue, "ad89192d-6ef8-56b5-a4dc-e48d0e85d569")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue, "71a22f32-a3c0-574b-87b4-127199cc7d5e")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue, "551fb7fb-ce42-5ffd-a2e0-2a6ce1698070")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue, "f1c1e9bd-01a6-5bd3-af7b-c14220a645c0")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue, "1ef903c8-8eef-5e9e-b938-b9e428a77672")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue, "82fef9f0-e283-5279-aa50-f0b3e5726a86")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue, "25c1a8d6-229b-5421-b3b3-b7ef078fad7f")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue, "3737fc5e-0b27-52a3-9e40-cbb9844e6ab7")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpChallengeHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue, "c312da8d-c82f-51c9-b705-5a26d52fbee6")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpConnectionOptionHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue, "b94e539f-44b6-54c6-9ad4-e2844b3e0be1")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue, "33f9653d-0eed-5368-a51e-98385191f86f")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpContentCodingWithQualityHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue, "bc196ace-8a56-5fd0-9878-c807edd8645a")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpCookiePairHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue, "18e138ee-fec7-527d-8693-deebca4f3dcd")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpExpectationHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue, "b6df6da2-8d92-5270-9584-d6a9a931586d")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpLanguageRangeWithQualityHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue, "c18538f7-c256-5666-8868-2225af3574b6")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpMediaTypeWithQualityHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue, "2cf800d4-35d0-545c-ab82-f6793be74cba")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpNameValueHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue, "69392060-6c0f-5de6-8ced-f14fc1b83376")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpProductInfoHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue, "38e72562-e17c-5d68-aad1-8e8a860b8969")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHeaders__CHttpTransferCodingHeaderValue : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :SINT, :ptr
    InsertAt            proc :SINT, :ptr
    RemoveAt            proc :SINT
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace Web
.namespace Http
.namespace Headers

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentHeaderCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentHeaderCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentHeaderCollection <L"Windows.Web.Http.Headers.IHttpContentHeaderCollection">
DEFINE_IIDX(IHttpContentHeaderCollection, "40612A44-47AE-4B7E-9124-69628B64AA18")

.comdef IHttpContentHeaderCollection : public IInspectable

    get_ContentDisposition proc :ptr
    put_ContentDisposition proc :ptr
    get_ContentEncoding proc :ptr
    get_ContentLanguage proc :ptr
    get_ContentLength   proc :ptr
    put_ContentLength   proc :ptr
    get_ContentLocation proc :ptr
    put_ContentLocation proc :ptr
    get_ContentMD5      proc :ptr
    put_ContentMD5      proc :ptr
    get_ContentRange    proc :ptr
    put_ContentRange    proc :ptr
    get_ContentType     proc :ptr
    put_ContentType     proc :ptr
    get_Expires         proc :ptr
    put_Expires         proc :ptr
    get_LastModified    proc :ptr
    put_LastModified    proc :ptr
    Append              proc :HSTRING, :HSTRING
    TryAppendWithoutValidation proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpRequestHeaderCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpRequestHeaderCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpRequestHeaderCollection <L"Windows.Web.Http.Headers.IHttpRequestHeaderCollection">
DEFINE_IIDX(IHttpRequestHeaderCollection, "AF40329B-B544-469B-86B9-AC3D466FEA36")

.comdef IHttpRequestHeaderCollection : public IInspectable

    get_Accept          proc :ptr
    get_AcceptEncoding  proc :ptr
    get_AcceptLanguage  proc :ptr
    get_Authorization   proc :ptr
    put_Authorization   proc :ptr
    get_CacheControl    proc :ptr
    get_Connection      proc :ptr
    get_Cookie          proc :ptr
    get_Date            proc :ptr
    put_Date            proc :ptr
    get_Expect          proc :ptr
    get_From            proc :ptr
    put_From            proc :HSTRING
    get_Host            proc :ptr
    put_Host            proc :ptr
    get_IfModifiedSince proc :ptr
    put_IfModifiedSince proc :ptr
    get_IfUnmodifiedSince proc :ptr
    put_IfUnmodifiedSince proc :ptr
    get_MaxForwards     proc :ptr
    put_MaxForwards     proc :ptr
    get_ProxyAuthorization proc :ptr
    put_ProxyAuthorization proc :ptr
    get_Referer         proc :ptr
    put_Referer         proc :ptr
    get_TransferEncoding proc :ptr
    get_UserAgent       proc :ptr
    Append              proc :HSTRING, :HSTRING
    TryAppendWithoutValidation proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpResponseHeaderCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpResponseHeaderCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpResponseHeaderCollection <L"Windows.Web.Http.Headers.IHttpResponseHeaderCollection">
DEFINE_IIDX(IHttpResponseHeaderCollection, "7A990969-FA3F-41ED-AAC6-BF957975C16B")

.comdef IHttpResponseHeaderCollection : public IInspectable

    get_Age             proc :ptr
    put_Age             proc :ptr
    get_Allow           proc :ptr
    get_CacheControl    proc :ptr
    get_Connection      proc :ptr
    get_Date            proc :ptr
    put_Date            proc :ptr
    get_Location        proc :ptr
    put_Location        proc :ptr
    get_ProxyAuthenticate proc :ptr
    get_RetryAfter      proc :ptr
    put_RetryAfter      proc :ptr
    get_TransferEncoding proc :ptr
    get_WwwAuthenticate proc :ptr
    Append              proc :HSTRING, :HSTRING
    TryAppendWithoutValidation proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCacheDirectiveHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCacheDirectiveHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCacheDirectiveHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpCacheDirectiveHeaderValueCollection">
DEFINE_IIDX(IHttpCacheDirectiveHeaderValueCollection, "9A586B89-D5D0-4FBE-BD9D-B5B3636811B4")

.comdef IHttpCacheDirectiveHeaderValueCollection : public IInspectable

    get_MaxAge          proc :ptr
    put_MaxAge          proc :ptr
    get_MaxStale        proc :ptr
    put_MaxStale        proc :ptr
    get_MinFresh        proc :ptr
    put_MinFresh        proc :ptr
    get_SharedMaxAge    proc :ptr
    put_SharedMaxAge    proc :ptr
    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpChallengeHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpChallengeHeaderValueStatics">
DEFINE_IIDX(IHttpChallengeHeaderValueStatics, "F3D38A72-FC01-4D01-A008-FCB7C459D635")

.comdef IHttpChallengeHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpChallengeHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpChallengeHeaderValueFactory">
DEFINE_IIDX(IHttpChallengeHeaderValueFactory,  "C452C451-D99C-40AA-9399-90EEB98FC613")

.comdef IHttpChallengeHeaderValueFactory : public IInspectable

    CreateFromScheme    proc :HSTRING, :ptr
    CreateFromSchemeWithToken proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpChallengeHeaderValue <L"Windows.Web.Http.Headers.IHttpChallengeHeaderValue">
DEFINE_IIDX(IHttpChallengeHeaderValue, "393361AF-0F7D-4820-9FDD-A2B956EEAEAB")

.comdef IHttpChallengeHeaderValue : public IInspectable

    get_Parameters      proc :ptr
    get_Scheme          proc :ptr
    get_Token           proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpChallengeHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpChallengeHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpChallengeHeaderValueCollection">
DEFINE_IIDX(IHttpChallengeHeaderValueCollection, "CA9E5F81-AEE0-4353-A10B-E625BABD64C2")

.comdef IHttpChallengeHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCredentialsHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpCredentialsHeaderValueStatics">
DEFINE_IIDX(IHttpCredentialsHeaderValueStatics, "A69B2BE6-CE8C-4443-A35A-1B727B131036")

.comdef IHttpCredentialsHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCredentialsHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpCredentialsHeaderValueFactory">
DEFINE_IIDX(IHttpCredentialsHeaderValueFactory, "F21D9E91-4D1C-4182-BFD1-34470A62F950")

.comdef IHttpCredentialsHeaderValueFactory : public IInspectable

    CreateFromScheme    proc :HSTRING, :ptr
    CreateFromSchemeWithToken proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCredentialsHeaderValue <L"Windows.Web.Http.Headers.IHttpCredentialsHeaderValue">
DEFINE_IIDX(IHttpCredentialsHeaderValue, "C34CC3CB-542E-4177-A6C7-B674CE193FBF")

.comdef IHttpCredentialsHeaderValue : public IInspectable

    get_Parameters      proc :ptr
    get_Scheme          proc :ptr
    get_Token           proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpConnectionOptionHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpConnectionOptionHeaderValueStatics">
DEFINE_IIDX(IHttpConnectionOptionHeaderValueStatics, "AAA75D37-A946-4B1F-85AF-48B68B3C50BD")

.comdef IHttpConnectionOptionHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpConnectionOptionHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpConnectionOptionHeaderValueFactory">
DEFINE_IIDX(IHttpConnectionOptionHeaderValueFactory, "D93CCC1E-0B7D-4C3F-A58D-A2A1BDEABC0A")

.comdef IHttpConnectionOptionHeaderValueFactory : public IInspectable

    Create              proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpConnectionOptionHeaderValue <L"Windows.Web.Http.Headers.IHttpConnectionOptionHeaderValue">
DEFINE_IIDX(IHttpConnectionOptionHeaderValue, "CB4AF27A-4E90-45EB-8DCD-FD1408F4C44F")

.comdef IHttpConnectionOptionHeaderValue : public IInspectable

    get_Token           proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpConnectionOptionHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpConnectionOptionHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpConnectionOptionHeaderValueCollection">
DEFINE_IIDX(IHttpConnectionOptionHeaderValueCollection, "E4F56C1D-5142-4E00-8E0F-019509337629")

.comdef IHttpConnectionOptionHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpContentCodingHeaderValueStatics">
DEFINE_IIDX(IHttpContentCodingHeaderValueStatics, "94D8602E-F9BF-42F7-AA46-ED272A41E212")

.comdef IHttpContentCodingHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpContentCodingHeaderValueFactory">
DEFINE_IIDX(IHttpContentCodingHeaderValueFactory, "C53D2BD7-332B-4350-8510-2E67A2289A5A")

.comdef IHttpContentCodingHeaderValueFactory : public IInspectable

    Create              proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingHeaderValue <L"Windows.Web.Http.Headers.IHttpContentCodingHeaderValue">
DEFINE_IIDX(IHttpContentCodingHeaderValue, "BCF7F92A-9376-4D85-BCCC-9F4F9ACAB434")

.comdef IHttpContentCodingHeaderValue : public IInspectable

    get_ContentCoding   proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpContentCodingHeaderValueCollection">
DEFINE_IIDX(IHttpContentCodingHeaderValueCollection, "7D221721-A6DB-436E-8E83-91596192819C")

.comdef IHttpContentCodingHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentDispositionHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentDispositionHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentDispositionHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpContentDispositionHeaderValueStatics">
DEFINE_IIDX(IHttpContentDispositionHeaderValueStatics, "29C56067-5A37-46E4-B074-C5177D69CA66")

.comdef IHttpContentDispositionHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentDispositionHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentDispositionHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentDispositionHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpContentDispositionHeaderValueFactory">
DEFINE_IIDX(IHttpContentDispositionHeaderValueFactory, "9915BBC4-456C-4E81-8295-B2AB3CBCF545")

.comdef IHttpContentDispositionHeaderValueFactory : public IInspectable

    Create              proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentDispositionHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentDispositionHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentDispositionHeaderValue <L"Windows.Web.Http.Headers.IHttpContentDispositionHeaderValue">
DEFINE_IIDX(IHttpContentDispositionHeaderValue, "F2A2EEDC-2629-4B49-9908-96A168E9365E")

.comdef IHttpContentDispositionHeaderValue : public IInspectable

    get_DispositionType proc :ptr
    put_DispositionType proc :HSTRING
    get_FileName        proc :ptr
    put_FileName        proc :HSTRING
    get_FileNameStar    proc :ptr
    put_FileNameStar    proc :HSTRING
    get_Name            proc :ptr
    put_Name            proc :HSTRING
    get_Parameters      proc :ptr
    get_Size            proc :ptr
    put_Size            proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentRangeHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentRangeHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentRangeHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpContentRangeHeaderValueStatics">
DEFINE_IIDX(IHttpContentRangeHeaderValueStatics, "80A346CA-174C-4FAE-821C-134CD294AA38")

.comdef IHttpContentRangeHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentRangeHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentRangeHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentRangeHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpContentRangeHeaderValueFactory">
DEFINE_IIDX(IHttpContentRangeHeaderValueFactory, "3F5BD691-A03C-4456-9A6F-EF27ECD03CAE")

.comdef IHttpContentRangeHeaderValueFactory : public IInspectable

    CreateFromLength    proc :UINT64, :ptr
    CreateFromRange     proc :UINT64, :UINT64, :ptr
    CreateFromRangeWithLength proc :UINT64, :UINT64, :UINT64, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentRangeHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentRangeHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentRangeHeaderValue <L"Windows.Web.Http.Headers.IHttpContentRangeHeaderValue">
DEFINE_IIDX(IHttpContentRangeHeaderValue, "04D967D3-A4F6-495C-9530-8579FCBA8AA9")

.comdef IHttpContentRangeHeaderValue : public IInspectable

    get_FirstBytePosition proc :ptr
    get_LastBytePosition proc :ptr
    get_Length          proc :ptr
    get_Unit            proc :ptr
    put_Unit            proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCookiePairHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpCookiePairHeaderValueStatics">
DEFINE_IIDX(IHttpCookiePairHeaderValueStatics, "6E866D48-06AF-4462-8158-99388D5DCA81")

.comdef IHttpCookiePairHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCookiePairHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpCookiePairHeaderValueFactory">
DEFINE_IIDX(IHttpCookiePairHeaderValueFactory, "635E326F-146F-4F56-AA21-2CB7D6D58B1E")

.comdef IHttpCookiePairHeaderValueFactory : public IInspectable

    CreateFromName      proc :HSTRING, :ptr
    CreateFromNameWithValue proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCookiePairHeaderValue <L"Windows.Web.Http.Headers.IHttpCookiePairHeaderValue">
DEFINE_IIDX(IHttpCookiePairHeaderValue, "CBD46217-4B29-412B-BD90-B3D814AB8E1B")

.comdef IHttpCookiePairHeaderValue : public IInspectable

    get_Name            proc :ptr
    get_Value           proc :ptr
    put_Value           proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCookiePairHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpCookiePairHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpCookiePairHeaderValueCollection">
DEFINE_IIDX(IHttpCookiePairHeaderValueCollection, "F3F44350-581E-4ECC-9F59-E507D04F06E6")

.comdef IHttpCookiePairHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpDateOrDeltaHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpDateOrDeltaHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpDateOrDeltaHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpDateOrDeltaHeaderValueStatics">
DEFINE_IIDX(IHttpDateOrDeltaHeaderValueStatics, "7C2659A8-6672-4E90-9A9A-F39766F7F576")

.comdef IHttpDateOrDeltaHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpDateOrDeltaHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpDateOrDeltaHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpDateOrDeltaHeaderValue <L"Windows.Web.Http.Headers.IHttpDateOrDeltaHeaderValue">
DEFINE_IIDX(IHttpDateOrDeltaHeaderValue, "EAFCAA6A-C4DC-49E2-A27D-043ADF5867A3")

.comdef IHttpDateOrDeltaHeaderValue : public IInspectable

    get_Date            proc :ptr
    get_Delta           proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpExpectationHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpExpectationHeaderValueStatics">
DEFINE_IIDX(IHttpExpectationHeaderValueStatics, "3019ABE2-CFE5-473B-A57F-FBA5B14EB257")

.comdef IHttpExpectationHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpExpectationHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpExpectationHeaderValueFactory">
DEFINE_IIDX(IHttpExpectationHeaderValueFactory, "4EA275CB-D53E-4868-8856-1E21A5030DC0")

.comdef IHttpExpectationHeaderValueFactory : public IInspectable

    CreateFromName      proc :HSTRING, :ptr
    CreateFromNameWithValue proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpExpectationHeaderValue <L"Windows.Web.Http.Headers.IHttpExpectationHeaderValue">
DEFINE_IIDX(IHttpExpectationHeaderValue, "4CE585CD-3A99-43AF-A2E6-EC232FEA9658")

.comdef IHttpExpectationHeaderValue : public IInspectable

    get_Name            proc :ptr
    get_Value           proc :ptr
    put_Value           proc :HSTRING
    get_Parameters      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpExpectationHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpExpectationHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpExpectationHeaderValueCollection">
DEFINE_IIDX(IHttpExpectationHeaderValueCollection, "E78521B3-A0E2-4AC4-9E66-79706CB9FD58")

.comdef IHttpExpectationHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpLanguageHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpLanguageHeaderValueCollection">
DEFINE_IIDX(IHttpLanguageHeaderValueCollection, "9EBD7CA3-8219-44F6-9902-8C56DFD3340C")

.comdef IHttpLanguageHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpLanguageRangeWithQualityHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpLanguageRangeWithQualityHeaderValueStatics">
DEFINE_IIDX(IHttpLanguageRangeWithQualityHeaderValueStatics, "2541E146-F308-46F5-B695-42F54024EC68")

.comdef IHttpLanguageRangeWithQualityHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpLanguageRangeWithQualityHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpLanguageRangeWithQualityHeaderValueFactory">
DEFINE_IIDX(IHttpLanguageRangeWithQualityHeaderValueFactory, "7BB83970-780F-4C83-9FE4-DC3087F6BD55")

.comdef IHttpLanguageRangeWithQualityHeaderValueFactory : public IInspectable

    CreateFromLanguageRange proc :HSTRING, :ptr
    CreateFromLanguageRangeWithQuality proc :HSTRING, :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpLanguageRangeWithQualityHeaderValue <L"Windows.Web.Http.Headers.IHttpLanguageRangeWithQualityHeaderValue">
DEFINE_IIDX(IHttpLanguageRangeWithQualityHeaderValue, "7256E102-0080-4DB4-A083-7DE7B2E5BA4C")

.comdef IHttpLanguageRangeWithQualityHeaderValue : public IInspectable

    get_LanguageRange   proc :ptr
    get_Quality         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpLanguageRangeWithQualityHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpLanguageRangeWithQualityHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpLanguageRangeWithQualityHeaderValueCollection">
DEFINE_IIDX(IHttpLanguageRangeWithQualityHeaderValueCollection, "885D5ABD-4B4F-480A-89CE-8AEDCEE6E3A0")

.comdef IHttpLanguageRangeWithQualityHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMediaTypeHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpMediaTypeHeaderValueStatics">
DEFINE_IIDX(IHttpMediaTypeHeaderValueStatics, "E04D83DF-1D41-4D8C-A2DE-6FD2ED87399B")

.comdef IHttpMediaTypeHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMediaTypeHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpMediaTypeHeaderValueFactory">
DEFINE_IIDX(IHttpMediaTypeHeaderValueFactory, "BED747A8-CD17-42DD-9367-AB9C5B56DD7D")

.comdef IHttpMediaTypeHeaderValueFactory : public IInspectable

    Create              proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMediaTypeHeaderValue <L"Windows.Web.Http.Headers.IHttpMediaTypeHeaderValue">
DEFINE_IIDX(IHttpMediaTypeHeaderValue, "16B28533-E728-4FCB-BDB0-08A431A14844")

.comdef IHttpMediaTypeHeaderValue : public IInspectable

    get_CharSet         proc :ptr
    put_CharSet         proc :HSTRING
    get_MediaType       proc :ptr
    put_MediaType       proc :HSTRING
    get_Parameters      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMediaTypeWithQualityHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpMediaTypeWithQualityHeaderValueStatics">
DEFINE_IIDX(IHttpMediaTypeWithQualityHeaderValueStatics, "5B070CD9-B560-4FC8-9835-7E6C0A657B24")

.comdef IHttpMediaTypeWithQualityHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMediaTypeWithQualityHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpMediaTypeWithQualityHeaderValueFactory">
DEFINE_IIDX(IHttpMediaTypeWithQualityHeaderValueFactory, "4C6D20F4-9457-44E6-A323-D122B958780B")

.comdef IHttpMediaTypeWithQualityHeaderValueFactory : public IInspectable

    CreateFromMediaType proc :HSTRING, :ptr
    CreateFromMediaTypeWithQuality proc :HSTRING, :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMediaTypeWithQualityHeaderValue <L"Windows.Web.Http.Headers.IHttpMediaTypeWithQualityHeaderValue">
DEFINE_IIDX(IHttpMediaTypeWithQualityHeaderValue, "188D5E32-76BE-44A0-B1CD-2074BDED2DDE")

.comdef IHttpMediaTypeWithQualityHeaderValue : public IInspectable

    get_CharSet         proc :ptr
    put_CharSet         proc :HSTRING
    get_MediaType       proc :ptr
    put_MediaType       proc :HSTRING
    get_Parameters      proc :ptr
    get_Quality         proc :ptr
    put_Quality         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMediaTypeWithQualityHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMediaTypeWithQualityHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpMediaTypeWithQualityHeaderValueCollection">
DEFINE_IIDX(IHttpMediaTypeWithQualityHeaderValueCollection, "3C0C6B73-1342-4587-A056-18D02FF67165")

.comdef IHttpMediaTypeWithQualityHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMethodHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpMethodHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpMethodHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpMethodHeaderValueCollection">
DEFINE_IIDX(IHttpMethodHeaderValueCollection, "43BC3FF4-6119-4ADF-938C-34BFFFCF92ED")

.comdef IHttpMethodHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpNameValueHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpNameValueHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpNameValueHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpNameValueHeaderValueStatics">
DEFINE_IIDX(IHttpNameValueHeaderValueStatics, "FFD4030F-1130-4152-8659-256909A9D115")

.comdef IHttpNameValueHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpNameValueHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpNameValueHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpNameValueHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpNameValueHeaderValueFactory">
DEFINE_IIDX(IHttpNameValueHeaderValueFactory, "770E2267-CBF8-4736-A925-93FBE10C7CA8")

.comdef IHttpNameValueHeaderValueFactory : public IInspectable

    CreateFromName      proc :HSTRING, :ptr
    CreateFromNameWithValue proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpNameValueHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpNameValueHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpNameValueHeaderValue <L"Windows.Web.Http.Headers.IHttpNameValueHeaderValue">
DEFINE_IIDX(IHttpNameValueHeaderValue, "D8BA7463-5B9A-4D1B-93F9-AA5B44ECFDDF")

.comdef IHttpNameValueHeaderValue : public IInspectable

    get_Name            proc :ptr
    get_Value           proc :ptr
    put_Value           proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpProductHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpProductHeaderValueStatics">
DEFINE_IIDX(IHttpProductHeaderValueStatics, "90C33E29-BEFC-4337-BE62-49F097975F53")

.comdef IHttpProductHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpProductHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpProductHeaderValueFactory">
DEFINE_IIDX(IHttpProductHeaderValueFactory, "611AA4F5-82BC-42FB-977B-DC00536E5E86")

.comdef IHttpProductHeaderValueFactory : public IInspectable

    CreateFromName      proc :HSTRING, :ptr
    CreateFromNameWithVersion proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpProductHeaderValue <L"Windows.Web.Http.Headers.IHttpProductHeaderValue">
DEFINE_IIDX(IHttpProductHeaderValue, "F4FEEE03-EBD4-4160-B9FF-807C5183B6E6")

.comdef IHttpProductHeaderValue : public IInspectable

    get_Name            proc :ptr
    get_Version         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpProductInfoHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpProductInfoHeaderValueStatics">
DEFINE_IIDX(IHttpProductInfoHeaderValueStatics, "DB7FD857-327A-4E73-81E5-7059A302B042")

.comdef IHttpProductInfoHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpProductInfoHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpProductInfoHeaderValueFactory">
DEFINE_IIDX(IHttpProductInfoHeaderValueFactory, "24220FBE-EABE-4464-B460-EC010B7C41E2")

.comdef IHttpProductInfoHeaderValueFactory : public IInspectable

    CreateFromComment   proc :HSTRING, :ptr
    CreateFromNameWithVersion proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpProductInfoHeaderValue <L"Windows.Web.Http.Headers.IHttpProductInfoHeaderValue">
DEFINE_IIDX(IHttpProductInfoHeaderValue, "1B1A8732-4C35-486A-966F-646489198E4D")

.comdef IHttpProductInfoHeaderValue : public IInspectable

    get_Product         proc :ptr
    get_Comment         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpProductInfoHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpProductInfoHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpProductInfoHeaderValueCollection">
DEFINE_IIDX(IHttpProductInfoHeaderValueCollection, "877DF74A-D69B-44F8-AD4F-453AF9C42ED0")

.comdef IHttpProductInfoHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingWithQualityHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpContentCodingWithQualityHeaderValueStatics">
DEFINE_IIDX(IHttpContentCodingWithQualityHeaderValueStatics, "E8C9357C-8F89-4801-8E75-4C9ABFC3DE71")

.comdef IHttpContentCodingWithQualityHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingWithQualityHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpContentCodingWithQualityHeaderValueFactory">
DEFINE_IIDX(IHttpContentCodingWithQualityHeaderValueFactory, "C45EEE1A-C553-46FC-ADE2-D75C1D53DF7B")

.comdef IHttpContentCodingWithQualityHeaderValueFactory : public IInspectable

    CreateFromValue     proc :HSTRING, :ptr
    CreateFromValueWithQuality proc :HSTRING, :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingWithQualityHeaderValue <L"Windows.Web.Http.Headers.IHttpContentCodingWithQualityHeaderValue">
DEFINE_IIDX(IHttpContentCodingWithQualityHeaderValue, "94531CD5-8B13-4D73-8651-F76B38F88495")

.comdef IHttpContentCodingWithQualityHeaderValue : public IInspectable

    get_ContentCoding   proc :ptr
    get_Quality         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpContentCodingWithQualityHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpContentCodingWithQualityHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpContentCodingWithQualityHeaderValueCollection">
DEFINE_IIDX(IHttpContentCodingWithQualityHeaderValueCollection, "7C0D753E-E899-4378-B5C8-412D820711CC")

.comdef IHttpContentCodingWithQualityHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValueStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValueStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpTransferCodingHeaderValueStatics <L"Windows.Web.Http.Headers.IHttpTransferCodingHeaderValueStatics">
DEFINE_IIDX(IHttpTransferCodingHeaderValueStatics, "6AB8892A-1A98-4D32-A906-7470A9875CE5")

.comdef IHttpTransferCodingHeaderValueStatics : public IInspectable

    Parse               proc :HSTRING, :ptr
    TryParse            proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpTransferCodingHeaderValueFactory <L"Windows.Web.Http.Headers.IHttpTransferCodingHeaderValueFactory">
DEFINE_IIDX(IHttpTransferCodingHeaderValueFactory, "BB62DFFC-E361-4F08-8E4F-C9E723DE703B")

.comdef IHttpTransferCodingHeaderValueFactory : public IInspectable

    Create              proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpTransferCodingHeaderValue <L"Windows.Web.Http.Headers.IHttpTransferCodingHeaderValue">
DEFINE_IIDX(IHttpTransferCodingHeaderValue, "436F32F9-3DED-42BD-B38A-5496A2511CE6")

.comdef IHttpTransferCodingHeaderValue : public IInspectable

    get_Parameters      proc :ptr
    get_Value           proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValueCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpTransferCodingHeaderValueCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Headers_IHttpTransferCodingHeaderValueCollection <L"Windows.Web.Http.Headers.IHttpTransferCodingHeaderValueCollection">
DEFINE_IIDX(IHttpTransferCodingHeaderValueCollection, "202C8C34-2C03-49B8-9665-73E27CB2FC79")

.comdef IHttpTransferCodingHeaderValueCollection : public IInspectable

    ParseAdd            proc :HSTRING
    TryParseAdd         proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentHeaderCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentHeaderCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpContentHeaderCollection <L"Windows.Web.Http.Headers.HttpContentHeaderCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpRequestHeaderCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpRequestHeaderCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpRequestHeaderCollection <L"Windows.Web.Http.Headers.HttpRequestHeaderCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpResponseHeaderCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpResponseHeaderCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpResponseHeaderCollection <L"Windows.Web.Http.Headers.HttpResponseHeaderCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentDispositionHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentDispositionHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpContentDispositionHeaderValue <L"Windows.Web.Http.Headers.HttpContentDispositionHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpContentCodingHeaderValueCollection <L"Windows.Web.Http.Headers.HttpContentCodingHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpLanguageHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpLanguageHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpLanguageHeaderValueCollection <L"Windows.Web.Http.Headers.HttpLanguageHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentRangeHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentRangeHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpContentRangeHeaderValue <L"Windows.Web.Http.Headers.HttpContentRangeHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpMediaTypeHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpMediaTypeHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpMediaTypeHeaderValue <L"Windows.Web.Http.Headers.HttpMediaTypeHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpMediaTypeWithQualityHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpMediaTypeWithQualityHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpMediaTypeWithQualityHeaderValueCollection <L"Windows.Web.Http.Headers.HttpMediaTypeWithQualityHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingWithQualityHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingWithQualityHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpContentCodingWithQualityHeaderValueCollection <L"Windows.Web.Http.Headers.HttpContentCodingWithQualityHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpLanguageRangeWithQualityHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpLanguageRangeWithQualityHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpLanguageRangeWithQualityHeaderValueCollection <L"Windows.Web.Http.Headers.HttpLanguageRangeWithQualityHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpCredentialsHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpCredentialsHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpCredentialsHeaderValue <L"Windows.Web.Http.Headers.HttpCredentialsHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpCacheDirectiveHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpCacheDirectiveHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpCacheDirectiveHeaderValueCollection <L"Windows.Web.Http.Headers.HttpCacheDirectiveHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpConnectionOptionHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpConnectionOptionHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpConnectionOptionHeaderValueCollection <L"Windows.Web.Http.Headers.HttpConnectionOptionHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpCookiePairHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpCookiePairHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpCookiePairHeaderValueCollection <L"Windows.Web.Http.Headers.HttpCookiePairHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpExpectationHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpExpectationHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpExpectationHeaderValueCollection <L"Windows.Web.Http.Headers.HttpExpectationHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpTransferCodingHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpTransferCodingHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpTransferCodingHeaderValueCollection <L"Windows.Web.Http.Headers.HttpTransferCodingHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpProductInfoHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpProductInfoHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpProductInfoHeaderValueCollection <L"Windows.Web.Http.Headers.HttpProductInfoHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpMethodHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpMethodHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpMethodHeaderValueCollection <L"Windows.Web.Http.Headers.HttpMethodHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpChallengeHeaderValueCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpChallengeHeaderValueCollection_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpChallengeHeaderValueCollection <L"Windows.Web.Http.Headers.HttpChallengeHeaderValueCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpDateOrDeltaHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpDateOrDeltaHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpDateOrDeltaHeaderValue <L"Windows.Web.Http.Headers.HttpDateOrDeltaHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpNameValueHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpNameValueHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpNameValueHeaderValue <L"Windows.Web.Http.Headers.HttpNameValueHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpChallengeHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpChallengeHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpChallengeHeaderValue <L"Windows.Web.Http.Headers.HttpChallengeHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpConnectionOptionHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpConnectionOptionHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpConnectionOptionHeaderValue <L"Windows.Web.Http.Headers.HttpConnectionOptionHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpContentCodingHeaderValue <L"Windows.Web.Http.Headers.HttpContentCodingHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpCookiePairHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpCookiePairHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpCookiePairHeaderValue <L"Windows.Web.Http.Headers.HttpCookiePairHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpExpectationHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpExpectationHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpExpectationHeaderValue <L"Windows.Web.Http.Headers.HttpExpectationHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpLanguageRangeWithQualityHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpLanguageRangeWithQualityHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpLanguageRangeWithQualityHeaderValue <L"Windows.Web.Http.Headers.HttpLanguageRangeWithQualityHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpMediaTypeWithQualityHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpMediaTypeWithQualityHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpMediaTypeWithQualityHeaderValue <L"Windows.Web.Http.Headers.HttpMediaTypeWithQualityHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpProductHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpProductHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpProductHeaderValue <L"Windows.Web.Http.Headers.HttpProductHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpProductInfoHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpProductInfoHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpProductInfoHeaderValue <L"Windows.Web.Http.Headers.HttpProductInfoHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingWithQualityHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpContentCodingWithQualityHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpContentCodingWithQualityHeaderValue <L"Windows.Web.Http.Headers.HttpContentCodingWithQualityHeaderValue">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Headers_HttpTransferCodingHeaderValue_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Headers_HttpTransferCodingHeaderValue_DEFINED
define RuntimeClass_Windows_Web_Http_Headers_HttpTransferCodingHeaderValue <L"Windows.Web.Http.Headers.HttpTransferCodingHeaderValue">
endif

endif
