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

ifndef __windows2Eglobalization2Ecollation_h__
define __windows2Eglobalization2Ecollation_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CGlobalization__CCollation__CCharacterGrouping_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CGlobalization__CCollation__CCharacterGrouping_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CGlobalization__CCollation__CCharacterGrouping, "57e89bbc-9220-5df2-844b-ddfe6605db5f")

.comdef __FIIterator_1_Windows__CGlobalization__CCollation__CCharacterGrouping : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CGlobalization__CCollation__CCharacterGrouping_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CGlobalization__CCollation__CCharacterGrouping_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CGlobalization__CCollation__CCharacterGrouping, "82e3abf0-06e3-5609-ba39-c51eb2f5fae6")

.comdef __FIIterable_1_Windows__CGlobalization__CCollation__CCharacterGrouping : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CGlobalization__CCollation__CCharacterGrouping_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CGlobalization__CCollation__CCharacterGrouping_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CGlobalization__CCollation__CCharacterGrouping, "f7cf5a4a-2b7a-5bc9-a0c4-9dce07ff61c9")

.comdef __FIVectorView_1_Windows__CGlobalization__CCollation__CCharacterGrouping : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Globalization
.namespace Collation

ifndef ____x_ABI_CWindows_CGlobalization_CCollation_CICharacterGrouping_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CCollation_CICharacterGrouping_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_Collation_ICharacterGrouping <L"Windows.Globalization.Collation.ICharacterGrouping">
DEFINE_IIDX(ICharacterGrouping, "FAE761BB-805D-4BB0-95BB-C1F7C3E8EB8E")

.comdef ICharacterGrouping : public IInspectable

    get_First           proc :ptr
    get_Label           proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CCollation_CICharacterGroupings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CCollation_CICharacterGroupings_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_Collation_ICharacterGroupings <L"Windows.Globalization.Collation.ICharacterGroupings">
DEFINE_IIDX(ICharacterGroupings, "B8D20A75-D4CF-4055-80E5-CE169C226496")

.comdef ICharacterGroupings : public IInspectable

    Lookup              proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Globalization_Collation_CharacterGrouping_DEFINED
define RUNTIMECLASS_Windows_Globalization_Collation_CharacterGrouping_DEFINED
define RuntimeClass_Windows_Globalization_Collation_CharacterGrouping <L"Windows.Globalization.Collation.CharacterGrouping">
endif
ifndef RUNTIMECLASS_Windows_Globalization_Collation_CharacterGroupings_DEFINED
define RUNTIMECLASS_Windows_Globalization_Collation_CharacterGroupings_DEFINED
define RuntimeClass_Windows_Globalization_Collation_CharacterGroupings <L"Windows.Globalization.Collation.CharacterGroupings">
endif

endif
