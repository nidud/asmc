ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef __adomd_h__
__adomd_h__ equ <>

ifndef __ICatalog_FWD_DEFINED__
__ICatalog_FWD_DEFINED__ equ 1
endif
ifndef __ICellset_FWD_DEFINED__
__ICellset_FWD_DEFINED__ equ 1
endif
ifndef __Cell_FWD_DEFINED__
__Cell_FWD_DEFINED__ equ 1
endif
ifndef __Axis_FWD_DEFINED__
__Axis_FWD_DEFINED__ equ 1
endif
ifndef __Position_FWD_DEFINED__
__Position_FWD_DEFINED__ equ 1
endif
ifndef __Member_FWD_DEFINED__
__Member_FWD_DEFINED__ equ 1
endif
ifndef __Level_FWD_DEFINED__
__Level_FWD_DEFINED__ equ 1
endif
ifndef __CubeDef25_FWD_DEFINED__
__CubeDef25_FWD_DEFINED__ equ 1
endif
ifndef __CubeDef_FWD_DEFINED__
__CubeDef_FWD_DEFINED__ equ 1
endif
ifndef __Dimension_FWD_DEFINED__
__Dimension_FWD_DEFINED__ equ 1
endif
ifndef __Hierarchy_FWD_DEFINED__
__Hierarchy_FWD_DEFINED__ equ 1
endif
ifndef __MD_Collection_FWD_DEFINED__
__MD_Collection_FWD_DEFINED__ equ 1
endif
ifndef __Members_FWD_DEFINED__
__Members_FWD_DEFINED__ equ 1
endif
ifndef __Levels_FWD_DEFINED__
__Levels_FWD_DEFINED__ equ 1
endif
ifndef __Axes_FWD_DEFINED__
__Axes_FWD_DEFINED__ equ 1
endif
ifndef __Positions_FWD_DEFINED__
__Positions_FWD_DEFINED__ equ 1
endif
ifndef __Hierarchies_FWD_DEFINED__
__Hierarchies_FWD_DEFINED__ equ 1
endif
ifndef __Dimensions_FWD_DEFINED__
__Dimensions_FWD_DEFINED__ equ 1
endif
ifndef __CubeDefs_FWD_DEFINED__
__CubeDefs_FWD_DEFINED__ equ 1
endif
ifndef __Catalog_FWD_DEFINED__
__Catalog_FWD_DEFINED__ equ 1
endif
ifndef __Cellset_FWD_DEFINED__
__Cellset_FWD_DEFINED__ equ 1
endif

TARGET_IS_NT40_OR_LATER equ 1

externdef		__MIDL_itf_adomd_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_adomd_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ADOMD_LIBRARY_DEFINED__
__ADOMD_LIBRARY_DEFINED__ equ 1

DECLSPEC_UUID("000002AE-0000-0010-8000-00AA006D2EA4")
DECLSPEC_UUID("C23BBD43-E494-4d00-B4D1-6C9A2CE17CE3")

MemberTypeEnum		typedef SDWORD
adMemberUnknown		equ 0
adMemberRegular		equ 0x1
adMemberAll		equ 0x2
adMemberMeasure		equ 0x3
adMemberFormula		equ 0x4

SchemaObjectTypeEnum	typedef SDWORD
adObjectTypeDimension	equ 1
adObjectTypeHierarchy	equ 2
adObjectTypeLevel	equ 3
adObjectTypeMember	equ 4


externdef		LIBID_ADOMD:IID

ifndef __ICatalog_INTERFACE_DEFINED__
__ICatalog_INTERFACE_DEFINED__ equ 1

externdef		IID_ICatalog:IID

.comdef ICatalog

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    putref_ActiveConnection proc :ptr
    put_ActiveConnection proc :BSTR
    get_ActiveConnection proc :ptr
    get_CubeDefs	proc :ptr
    .ends

endif

ifndef __ICellset_INTERFACE_DEFINED__
__ICellset_INTERFACE_DEFINED__ equ 1

externdef		IID_ICellset:IID

.comdef ICellset

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Item		proc :ptr, :ptr
    Open		proc :VARIANT, :VARIANT
    Close		proc
    putref_Source	proc :ptr
    put_Source		proc :BSTR
    get_Source		proc :ptr
    putref_ActiveConnection proc :ptr
    put_ActiveConnection proc :BSTR
    get_ActiveConnection proc :ptr
    get_State		proc :ptr
    get_Axes		proc :ptr
    get_FilterAxis	proc :ptr
    get_Properties	proc :ptr
    .ends

endif

ifndef __Cell_INTERFACE_DEFINED__
__Cell_INTERFACE_DEFINED__ equ 1

externdef		IID_Cell:IID

.comdef Cell

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Value		proc :ptr
    put_Value		proc :VARIANT
    get_Positions	proc :ptr
    get_Properties	proc :ptr
    get_FormattedValue	proc :ptr
    put_FormattedValue	proc :BSTR
    get_Ordinal		proc :ptr
    .ends

endif

ifndef __Axis_INTERFACE_DEFINED__
__Axis_INTERFACE_DEFINED__ equ 1

externdef		IID_Axis:IID

.comdef Axis

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_DimensionCount	proc :ptr
    get_Positions	proc :ptr
    get_Properties	proc :ptr
    .ends

endif

ifndef __Position_INTERFACE_DEFINED__
__Position_INTERFACE_DEFINED__ equ 1

externdef		IID_Position:IID

.comdef Position

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Ordinal		proc :ptr
    get_Members		proc :ptr
    .ends

endif

ifndef __Member_INTERFACE_DEFINED__
__Member_INTERFACE_DEFINED__ equ 1

externdef		IID_Member:IID

.comdef Member

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_UniqueName	proc :ptr
    get_Caption		proc :ptr
    get_Description	proc :ptr
    get_Parent		proc :ptr
    get_LevelDepth	proc :ptr
    get_LevelName	proc :ptr
    get_Properties	proc :ptr
    get_Type		proc :ptr
    get_ChildCount	proc :ptr
    get_DrilledDown	proc :ptr
    get_ParentSameAsPrev proc :ptr
    get_Children	proc :ptr
    .ends

endif

ifndef __Level_INTERFACE_DEFINED__
__Level_INTERFACE_DEFINED__ equ 1

externdef		IID_Level:IID

.comdef Level

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_UniqueName	proc :ptr
    get_Caption		proc :ptr
    get_Description	proc :ptr
    get_Depth		proc :ptr
    get_Properties	proc :ptr
    get_Members		proc :ptr
    .ends

endif

ifndef __CubeDef25_INTERFACE_DEFINED__
__CubeDef25_INTERFACE_DEFINED__ equ 1

externdef		IID_CubeDef25:IID

.comdef CubeDef25

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Dimensions	proc :ptr
    .ends

endif

ifndef __CubeDef_INTERFACE_DEFINED__
__CubeDef_INTERFACE_DEFINED__ equ 1

externdef		IID_CubeDef:IID

.comdef CubeDef

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Dimensions	proc :ptr
    GetSchemaObject	proc :SchemaObjectTypeEnum, :BSTR, :ptr
    .ends

endif

ifndef __Dimension_INTERFACE_DEFINED__
__Dimension_INTERFACE_DEFINED__ equ 1

externdef		IID_Dimension:IID

.comdef Dimension

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_UniqueName	proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Hierarchies	proc :ptr
    .ends

endif

ifndef __Hierarchy_INTERFACE_DEFINED__
__Hierarchy_INTERFACE_DEFINED__ equ 1

externdef		IID_Hierarchy:IID

.comdef Hierarchy

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_UniqueName	proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Levels		proc :ptr
    .ends

endif

ifndef __MD_Collection_INTERFACE_DEFINED__
__MD_Collection_INTERFACE_DEFINED__ equ 1

externdef		IID_MD_Collection:IID

.comdef MD_Collection

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    .ends

endif

ifndef __Members_INTERFACE_DEFINED__
__Members_INTERFACE_DEFINED__ equ 1

externdef		IID_Members:IID

.comdef Members

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    .ends

endif

ifndef __Levels_INTERFACE_DEFINED__
__Levels_INTERFACE_DEFINED__ equ 1

externdef		IID_Levels:IID

.comdef Levels

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    .ends

endif

ifndef __Axes_INTERFACE_DEFINED__
__Axes_INTERFACE_DEFINED__ equ 1

externdef		IID_Axes:IID

.comdef Axes

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    .ends

endif

ifndef __Positions_INTERFACE_DEFINED__
__Positions_INTERFACE_DEFINED__ equ 1

externdef		IID_Positions:IID

.comdef Positions

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    .ends

endif

ifndef __Hierarchies_INTERFACE_DEFINED__
__Hierarchies_INTERFACE_DEFINED__ equ 1

externdef		IID_Hierarchies:IID

.comdef Hierarchies

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    .ends

endif

ifndef __Dimensions_INTERFACE_DEFINED__
__Dimensions_INTERFACE_DEFINED__ equ 1

externdef		IID_Dimensions:IID

.comdef Dimensions

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    .ends

endif

ifndef __CubeDefs_INTERFACE_DEFINED__
__CubeDefs_INTERFACE_DEFINED__ equ 1

externdef		IID_CubeDefs:IID

.comdef CubeDefs

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    .ends

endif

externdef		CLSID_Catalog:CLSID

ifdef __cplusplus
DECLSPEC_UUID("228136B0-8BD3-11D0-B4EF-00A0C9138CA4")
endif
externdef		CLSID_Cellset:CLSID
ifdef __cplusplus
DECLSPEC_UUID("228136B8-8BD3-11D0-B4EF-00A0C9138CA4")
endif
endif

endif
