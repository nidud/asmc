.pragma list(push, 0)

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

DEFINE_IIDX(ICatalog, "228136B1-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef ICatalog : public IDispatch

    get_Name		proc :ptr
    putref_ActiveConnection proc :ptr
    put_ActiveConnection proc :BSTR
    get_ActiveConnection proc :ptr
    get_CubeDefs	proc :ptr

    .ends
endif

ifndef __ICellset_INTERFACE_DEFINED__
__ICellset_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICellset, "2281372A-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef ICellset : public IDispatch

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

DEFINE_IIDX(Cell, "2281372E-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Cell : public IDispatch

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

DEFINE_IIDX(Axis, "22813732-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Axis : public IDispatch

    get_Name		proc :ptr
    get_DimensionCount	proc :ptr
    get_Positions	proc :ptr
    get_Properties	proc :ptr

    .ends
endif

ifndef __Position_INTERFACE_DEFINED__
__Position_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Position, "22813734-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Position : public IDispatch

    get_Ordinal		proc :ptr
    get_Members		proc :ptr

    .ends
endif

ifndef __Member_INTERFACE_DEFINED__
__Member_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Member, "22813736-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Member : public IDispatch

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

DEFINE_IIDX(Level, "2281373A-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Level : public IDispatch

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

DEFINE_IIDX(CubeDef25, "2281373E-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef CubeDef25 : public IDispatch

    get_Name		proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Dimensions	proc :ptr

    .ends
endif

ifndef __CubeDef_INTERFACE_DEFINED__
__CubeDef_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(CubeDef, "DA16A34A-7B7A-46fd-AD9D-66DF1E699FA1")

.comdef CubeDef : public CubeDef25

    GetSchemaObject	proc :SchemaObjectTypeEnum, :BSTR, :ptr

    .ends
endif

ifndef __Dimension_INTERFACE_DEFINED__
__Dimension_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Dimension, "22813742-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Dimension : public IDispatch

    get_Name		proc :ptr
    get_UniqueName	proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Hierarchies	proc :ptr

    .ends
endif

ifndef __Hierarchy_INTERFACE_DEFINED__
__Hierarchy_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Hierarchy, "22813746-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Hierarchy : public IDispatch

    get_Name		proc :ptr
    get_UniqueName	proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Levels		proc :ptr

    .ends
endif

ifndef __MD_Collection_INTERFACE_DEFINED__
__MD_Collection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(MD_Collection, "22813751-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef MD_Collection : public IDispatch

    Refresh		proc
    NewEnum		proc :ptr
    get_Count		proc :ptr

    .ends
endif

ifndef __Members_INTERFACE_DEFINED__
__Members_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Members, "22813757-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Members : public MD_Collection

    get_Item		proc :VARIANT, :ptr

    .ends
endif

ifndef __Levels_INTERFACE_DEFINED__
__Levels_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Levels, "22813758-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Levels : public MD_Collection

    get_Item		proc :VARIANT, :ptr

    .ends

endif

ifndef __Axes_INTERFACE_DEFINED__
__Axes_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Axes, "22813759-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Axes : public MD_Collection

    get_Item		proc :VARIANT, :ptr

    .ends
endif

ifndef __Positions_INTERFACE_DEFINED__
__Positions_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Positions, "2281375A-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Positions : public MD_Collection

    get_Item		proc :VARIANT, :ptr

    .ends
endif

ifndef __Hierarchies_INTERFACE_DEFINED__
__Hierarchies_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Hierarchies, "2281375B-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Hierarchies : public MD_Collection

    get_Item		proc :VARIANT, :ptr

    .ends

endif

ifndef __Dimensions_INTERFACE_DEFINED__
__Dimensions_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Dimensions, "2281375C-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Dimensions : public MD_Collection

    get_Item		proc :VARIANT, :ptr

    .ends

endif

ifndef __CubeDefs_INTERFACE_DEFINED__
__CubeDefs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(CubeDefs, "2281375D-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef CubeDefs : public MD_Collection

    get_Item		proc :VARIANT, :ptr

    .ends
endif

DEFINE_GUIDS(CLSID_Catalog, "228136B0-8BD3-11D0-B4EF-00A0C9138CA4")
DEFINE_GUIDS(CLSID_Cellset, "228136B8-8BD3-11D0-B4EF-00A0C9138CA4")

endif

endif
.pragma list(pop)
