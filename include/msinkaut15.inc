ifndef _RPC500_
include rpc500.inc
endif
ifndef __msinkaut15_h__
define __msinkaut15_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include msinkaut.inc

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include tpcerror.inc

ifndef __MSINKDIVLib_LIBRARY_DEFINED__
define __MSINKDIVLib_LIBRARY_DEFINED__

.enum InkDivisionType {
	IDT_Segment,
	IDT_Line,
	IDT_Paragraph,
	IDT_Drawing
	}

.enum DISPID_InkDivider {
	DISPID_IInkDivider_Strokes = 1,
	DISPID_IInkDivider_RecognizerContext,
	DISPID_IInkDivider_LineHeight,
	DISPID_IInkDivider_Divide
	}

.enum DISPID_InkDivisionResult {
	DISPID_IInkDivisionResult_Strokes = 1,
	DISPID_IInkDivisionResult_ResultByType
	}

.enum DISPID_InkDivisionUnit {
	DISPID_IInkDivisionUnit_Strokes = 1,
	DISPID_IInkDivisionUnit_DivisionType,
	DISPID_IInkDivisionUnit_RecognizedString,
	DISPID_IInkDivisionUnit_RotationTransform
	}

.enum DISPID_InkDivisionUnits {
	DISPID_IInkDivisionUnits_NewEnum	= DISPID_NEWENUM,
	DISPID_IInkDivisionUnits_Item		= DISPID_VALUE,
	DISPID_IInkDivisionUnits_Count		= 1
	}

DEFINE_GUID(LIBID_MSINKDIVLib, 0x56D04F5D,0x964F,0x4dbf,0x8D,0x23,0xB9,0x79,0x89,0xE5,0x34,0x18)

ifndef __IInkDivider_INTERFACE_DEFINED__
define __IInkDivider_INTERFACE_DEFINED__

DEFINE_IIDX(IInkDivider, "5DE00405-F9A4-4651-B0C5-C317DEFD58B9")

.comdef IInkDivider : public IDispatch
    get_Strokes		proc :ptr ptr
    putref_Strokes	proc :ptr
    get_RecognizerContext proc :ptr ptr
    putref_RecognizerContext proc :ptr
    get_LineHeight	proc :ptr
    put_LineHeight	proc :LONG
    Divide		proc :ptr ptr
   .ends

endif

ifndef __IInkDivisionResult_INTERFACE_DEFINED__
define __IInkDivisionResult_INTERFACE_DEFINED__

DEFINE_IIDX(IInkDivisionResult, "2DBEC0A7-74C7-4B38-81EB-AA8EF0C24900")

.comdef IInkDivisionResult : public IDispatch
    get_Strokes		proc :ptr ptr
    ResultByType	proc :InkDivisionType, :ptr ptr
   .ends

endif

ifndef __IInkDivisionUnit_INTERFACE_DEFINED__
define __IInkDivisionUnit_INTERFACE_DEFINED__

DEFINE_IIDX(IInkDivisionUnit, "85AEE342-48B0-4244-9DD5-1ED435410FAB")

.comdef IInkDivisionUnit : public IDispatch
    get_Strokes		proc :ptr ptr
    get_DivisionType	proc :ptr
    get_RecognizedString proc :ptr
    get_RotationTransform proc :ptr ptr
   .ends

endif

ifndef __IInkDivisionUnits_INTERFACE_DEFINED__
define __IInkDivisionUnits_INTERFACE_DEFINED__

DEFINE_IIDX(IInkDivisionUnits, "1BB5DDC2-31CC-4135-AB82-2C66C9F00C41")

.comdef IInkDivisionUnits : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    Item		proc :LONG, :ptr ptr
   .ends

endif

DEFINE_GUIDS(CLSID_InkDivider, "8854F6A0-4683-4AE7-9191-752FE64612C3")

endif

endif

endif
