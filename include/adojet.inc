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
ifndef __adojet_h__
__adojet_h__ equ <>

ifndef __IReplica_FWD_DEFINED__
__IReplica_FWD_DEFINED__ equ 1
endif
ifndef __Filter_FWD_DEFINED__
__Filter_FWD_DEFINED__ equ 1
endif
ifndef __Filters_FWD_DEFINED__
__Filters_FWD_DEFINED__ equ 1
endif
ifndef __IJetEngine_FWD_DEFINED__
__IJetEngine_FWD_DEFINED__ equ 1
endif
ifndef __Replica_FWD_DEFINED__
__Replica_FWD_DEFINED__ equ 1
endif
ifndef __JetEngine_FWD_DEFINED__
__JetEngine_FWD_DEFINED__ equ 1
endif

TARGET_IS_NT40_OR_LATER equ 1

ifndef __JRO_LIBRARY_DEFINED__
__JRO_LIBRARY_DEFINED__ equ 1

ReplicaTypeEnum		typedef SDWORD
jrRepTypeNotReplicable	equ 0
jrRepTypeDesignMaster	equ 0x1
jrRepTypeFull		equ 0x2
jrRepTypePartial	equ 0x3

VisibilityEnum		typedef SDWORD
jrRepVisibilityGlobal	equ 0x1
jrRepVisibilityLocal	equ 0x2
jrRepVisibilityAnon	equ 0x4

UpdatabilityEnum	typedef SDWORD
jrRepUpdFull		equ 0
jrRepUpdReadOnly	equ 0x2

SyncTypeEnum		typedef SDWORD
jrSyncTypeExport	equ 0x1
jrSyncTypeImport	equ 0x2
jrSyncTypeImpExp	equ 0x3

SyncModeEnum		typedef SDWORD
jrSyncModeIndirect	equ 0x1
jrSyncModeDirect	equ 0x2
jrSyncModeInternet	equ 0x3

FilterTypeEnum		typedef SDWORD
jrFilterTypeTable	equ 0x1
jrFilterTypeRelationship equ 0x2

externdef		LIBID_JRO:IID

ifndef __IReplica_INTERFACE_DEFINED__
__IReplica_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IReplica, "D2D139E0-B6CA-11d1-9F31-00C04FC29D52")

.comdef IReplica

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    putref_ActiveConnection proc :ptr
    put_ActiveConnection proc :VARIANT
    get_ActiveConnection proc :ptr
    get_ConflictFunction proc :ptr
    put_ConflictFunction proc :BSTR
    get_ConflictTables	proc :ptr
    get_DesignMasterId	proc :ptr
    put_DesignMasterId	proc :VARIANT
    get_Priority	proc :ptr
    get_ReplicaId	proc :ptr
    get_ReplicaType	proc :ptr
    get_RetentionPeriod proc :ptr
    put_RetentionPeriod proc :LONG
    get_Visibility	proc :ptr
    CreateReplica	proc :BSTR, :BSTR, :ReplicaTypeEnum, :VisibilityEnum, :LONG, :UpdatabilityEnum
    GetObjectReplicability proc :BSTR, :BSTR, :ptr
    SetObjectReplicability proc :BSTR, :BSTR, :VARIANT_BOOL
    MakeReplicable	proc :BSTR, :VARIANT_BOOL
    PopulatePartial	proc :BSTR
    Synchronize		proc :BSTR, :SyncTypeEnum, :SyncModeEnum
    get_Filters		proc :ptr
    .ends

endif

ifndef __Filter_INTERFACE_DEFINED__
__Filter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Filter, "D2D139E1-B6CA-11d1-9F31-00C04FC29D52")

.comdef Filter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_TableName	proc :ptr
    get_FilterType	proc :ptr
    get_FilterCriteria	proc :ptr
    .ends

endif

ifndef __Filters_INTERFACE_DEFINED__
__Filters_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Filters, "D2D139E2-B6CA-11d1-9F31-00C04FC29D52")

.comdef Filters

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
    Append		proc :BSTR, :FilterTypeEnum, :BSTR
    Delete		proc :VARIANT
    .ends

endif

ifndef __IJetEngine_INTERFACE_DEFINED__
__IJetEngine_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IJetEngine, "9F63D980-FF25-11D1-BB6F-00C04FAE22DA")

.comdef IJetEngine

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    CompactDatabase	proc :BSTR, :BSTR
    RefreshCache	proc :ptr
    .ends

endif

DEFINE_GUIDS(CLSID_Replica, "D2D139E3-B6CA-11d1-9F31-00C04FC29D52")
DEFINE_GUIDS(CLSID_JetEngine, "DE88C160-FF2C-11D1-BB6F-00C04FAE22DA")

endif

endif
.pragma list(pop)
