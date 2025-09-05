ifndef _RPC500_
include rpc500.inc
endif
ifndef __adojet_h__
define __adojet_h__

TARGET_IS_NT40_OR_LATER equ 1

ifndef __JRO_LIBRARY_DEFINED__
define __JRO_LIBRARY_DEFINED__

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
define __IReplica_INTERFACE_DEFINED__

DEFINE_IIDX(IReplica, "D2D139E0-B6CA-11d1-9F31-00C04FC29D52")

.comdef IReplica : public IDispatch

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
define __Filter_INTERFACE_DEFINED__

DEFINE_IIDX(Filter, "D2D139E1-B6CA-11d1-9F31-00C04FC29D52")

.comdef Filter : public IDispatch

    get_TableName	proc :ptr
    get_FilterType	proc :ptr
    get_FilterCriteria	proc :ptr
   .ends

endif

ifndef __Filters_INTERFACE_DEFINED__
define __Filters_INTERFACE_DEFINED__

DEFINE_IIDX(Filters, "D2D139E2-B6CA-11d1-9F31-00C04FC29D52")

.comdef Filters : public IDispatch

    Refresh		proc
    _NewEnum		proc :ptr
    get_Count		proc :ptr
    get_Item		proc :VARIANT, :ptr
    Append		proc :BSTR, :FilterTypeEnum, :BSTR
    Delete		proc :VARIANT
   .ends

endif

ifndef __IJetEngine_INTERFACE_DEFINED__
define __IJetEngine_INTERFACE_DEFINED__

DEFINE_IIDX(IJetEngine, "9F63D980-FF25-11D1-BB6F-00C04FAE22DA")

.comdef IJetEngine : public IDispatch

    CompactDatabase	proc :BSTR, :BSTR
    RefreshCache	proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_Replica, "D2D139E3-B6CA-11d1-9F31-00C04FC29D52")
DEFINE_GUIDS(CLSID_JetEngine, "DE88C160-FF2C-11D1-BB6F-00C04FAE22DA")

endif

endif
