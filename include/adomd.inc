.pragma list(push, 0)

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

ifndef __adomd_h__
define __adomd_h__

TARGET_IS_NT40_OR_LATER equ 1

ifndef __ADOMD_LIBRARY_DEFINED__
define __ADOMD_LIBRARY_DEFINED__

.enum MemberTypeEnum {
    adMemberUnknown = 0,
    adMemberRegular = 0x1,
    adMemberAll = 0x2,
    adMemberMeasure = 0x3,
    adMemberFormula = 0x4
    }

.enum SchemaObjectTypeEnum {
    adObjectTypeDimension = 1,
    adObjectTypeHierarchy = 2,
    adObjectTypeLevel	= 3,
    adObjectTypeMember	= 4
    }

externdef LIBID_ADOMD:IID

ifndef __ICatalog_INTERFACE_DEFINED__
define __ICatalog_INTERFACE_DEFINED__

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
define __ICellset_INTERFACE_DEFINED__

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
define __Cell_INTERFACE_DEFINED__

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
define __Axis_INTERFACE_DEFINED__

DEFINE_IIDX(Axis, "22813732-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Axis : public IDispatch

    get_Name		proc :ptr
    get_DimensionCount	proc :ptr
    get_Positions	proc :ptr
    get_Properties	proc :ptr
   .ends

endif

ifndef __Position_INTERFACE_DEFINED__
define __Position_INTERFACE_DEFINED__

DEFINE_IIDX(Position, "22813734-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Position : public IDispatch

    get_Ordinal		proc :ptr
    get_Members		proc :ptr
   .ends

endif

ifndef __Member_INTERFACE_DEFINED__
define __Member_INTERFACE_DEFINED__

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
define __Level_INTERFACE_DEFINED__

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
define __CubeDef25_INTERFACE_DEFINED__

DEFINE_IIDX(CubeDef25, "2281373E-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef CubeDef25 : public IDispatch

    get_Name		proc :ptr
    get_Description	proc :ptr
    get_Properties	proc :ptr
    get_Dimensions	proc :ptr
   .ends

endif

ifndef __CubeDef_INTERFACE_DEFINED__
define __CubeDef_INTERFACE_DEFINED__

DEFINE_IIDX(CubeDef, "DA16A34A-7B7A-46fd-AD9D-66DF1E699FA1")

.comdef CubeDef : public CubeDef25

    GetSchemaObject	proc :SchemaObjectTypeEnum, :BSTR, :ptr
   .ends

endif

ifndef __Dimension_INTERFACE_DEFINED__
define __Dimension_INTERFACE_DEFINED__

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
define __Hierarchy_INTERFACE_DEFINED__

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
define __MD_Collection_INTERFACE_DEFINED__

DEFINE_IIDX(MD_Collection, "22813751-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef MD_Collection : public IDispatch

    Refresh		proc
    NewEnum		proc :ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __Members_INTERFACE_DEFINED__
define __Members_INTERFACE_DEFINED__

DEFINE_IIDX(Members, "22813757-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Members : public MD_Collection

    get_Item		proc :VARIANT, :ptr
   .ends

endif

ifndef __Levels_INTERFACE_DEFINED__
define __Levels_INTERFACE_DEFINED__

DEFINE_IIDX(Levels, "22813758-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Levels : public MD_Collection

    get_Item		proc :VARIANT, :ptr
   .ends

endif

ifndef __Axes_INTERFACE_DEFINED__
define __Axes_INTERFACE_DEFINED__

DEFINE_IIDX(Axes, "22813759-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Axes : public MD_Collection

    get_Item		proc :VARIANT, :ptr
   .ends

endif

ifndef __Positions_INTERFACE_DEFINED__
define __Positions_INTERFACE_DEFINED__

DEFINE_IIDX(Positions, "2281375A-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Positions : public MD_Collection

    get_Item		proc :VARIANT, :ptr
   .ends

endif

ifndef __Hierarchies_INTERFACE_DEFINED__
define __Hierarchies_INTERFACE_DEFINED__

DEFINE_IIDX(Hierarchies, "2281375B-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Hierarchies : public MD_Collection

    get_Item		proc :VARIANT, :ptr
   .ends

endif

ifndef __Dimensions_INTERFACE_DEFINED__
define __Dimensions_INTERFACE_DEFINED__

DEFINE_IIDX(Dimensions, "2281375C-8BD3-11D0-B4EF-00A0C9138CA4")

.comdef Dimensions : public MD_Collection

    get_Item		proc :VARIANT, :ptr
   .ends

endif

ifndef __CubeDefs_INTERFACE_DEFINED__
define __CubeDefs_INTERFACE_DEFINED__

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
