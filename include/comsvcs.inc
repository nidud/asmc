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

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __autosvcs_h__
__autosvcs_h__ equ <>

ifndef __ISecurityIdentityColl_FWD_DEFINED__
__ISecurityIdentityColl_FWD_DEFINED__ equ 1
endif
ifndef __ISecurityCallersColl_FWD_DEFINED__
__ISecurityCallersColl_FWD_DEFINED__ equ 1
endif
ifndef __ISecurityCallContext_FWD_DEFINED__
__ISecurityCallContext_FWD_DEFINED__ equ 1
endif
ifndef __IGetSecurityCallContext_FWD_DEFINED__
__IGetSecurityCallContext_FWD_DEFINED__ equ 1
endif
ifndef __SecurityProperty_FWD_DEFINED__
__SecurityProperty_FWD_DEFINED__ equ 1
endif
ifndef __ContextInfo_FWD_DEFINED__
__ContextInfo_FWD_DEFINED__ equ 1
endif
ifndef __ContextInfo2_FWD_DEFINED__
__ContextInfo2_FWD_DEFINED__ equ 1
endif
ifndef __ObjectContext_FWD_DEFINED__
__ObjectContext_FWD_DEFINED__ equ 1
endif
ifndef __ITransactionContextEx_FWD_DEFINED__
__ITransactionContextEx_FWD_DEFINED__ equ 1
endif
ifndef __ITransactionContext_FWD_DEFINED__
__ITransactionContext_FWD_DEFINED__ equ 1
endif
ifndef __ICreateWithTransactionEx_FWD_DEFINED__
__ICreateWithTransactionEx_FWD_DEFINED__ equ 1
endif
ifndef __ICreateWithLocalTransaction_FWD_DEFINED__
__ICreateWithLocalTransaction_FWD_DEFINED__ equ 1
endif
ifndef __ICreateWithTipTransactionEx_FWD_DEFINED__
__ICreateWithTipTransactionEx_FWD_DEFINED__ equ 1
endif
ifndef __IComLTxEvents_FWD_DEFINED__
__IComLTxEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComUserEvent_FWD_DEFINED__
__IComUserEvent_FWD_DEFINED__ equ 1
endif
ifndef __IComThreadEvents_FWD_DEFINED__
__IComThreadEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComAppEvents_FWD_DEFINED__
__IComAppEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComInstanceEvents_FWD_DEFINED__
__IComInstanceEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComTransactionEvents_FWD_DEFINED__
__IComTransactionEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComMethodEvents_FWD_DEFINED__
__IComMethodEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComObjectEvents_FWD_DEFINED__
__IComObjectEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComResourceEvents_FWD_DEFINED__
__IComResourceEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComSecurityEvents_FWD_DEFINED__
__IComSecurityEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComObjectPoolEvents_FWD_DEFINED__
__IComObjectPoolEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComObjectPoolEvents2_FWD_DEFINED__
__IComObjectPoolEvents2_FWD_DEFINED__ equ 1
endif
ifndef __IComObjectConstructionEvents_FWD_DEFINED__
__IComObjectConstructionEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComActivityEvents_FWD_DEFINED__
__IComActivityEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComIdentityEvents_FWD_DEFINED__
__IComIdentityEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComQCEvents_FWD_DEFINED__
__IComQCEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComExceptionEvents_FWD_DEFINED__
__IComExceptionEvents_FWD_DEFINED__ equ 1
endif
ifndef __ILBEvents_FWD_DEFINED__
__ILBEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComCRMEvents_FWD_DEFINED__
__IComCRMEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComMethod2Events_FWD_DEFINED__
__IComMethod2Events_FWD_DEFINED__ equ 1
endif
ifndef __IComTrackingInfoEvents_FWD_DEFINED__
__IComTrackingInfoEvents_FWD_DEFINED__ equ 1
endif
ifndef __IComTrackingInfoCollection_FWD_DEFINED__
__IComTrackingInfoCollection_FWD_DEFINED__ equ 1
endif
ifndef __IComTrackingInfoObject_FWD_DEFINED__
__IComTrackingInfoObject_FWD_DEFINED__ equ 1
endif
ifndef __IComTrackingInfoProperties_FWD_DEFINED__
__IComTrackingInfoProperties_FWD_DEFINED__ equ 1
endif
ifndef __IComApp2Events_FWD_DEFINED__
__IComApp2Events_FWD_DEFINED__ equ 1
endif
ifndef __IComTransaction2Events_FWD_DEFINED__
__IComTransaction2Events_FWD_DEFINED__ equ 1
endif
ifndef __IComInstance2Events_FWD_DEFINED__
__IComInstance2Events_FWD_DEFINED__ equ 1
endif
ifndef __IComObjectPool2Events_FWD_DEFINED__
__IComObjectPool2Events_FWD_DEFINED__ equ 1
endif
ifndef __IComObjectConstruction2Events_FWD_DEFINED__
__IComObjectConstruction2Events_FWD_DEFINED__ equ 1
endif
ifndef __ISystemAppEventData_FWD_DEFINED__
__ISystemAppEventData_FWD_DEFINED__ equ 1
endif
ifndef __IMtsEvents_FWD_DEFINED__
__IMtsEvents_FWD_DEFINED__ equ 1
endif
ifndef __IMtsEventInfo_FWD_DEFINED__
__IMtsEventInfo_FWD_DEFINED__ equ 1
endif
ifndef __IMTSLocator_FWD_DEFINED__
__IMTSLocator_FWD_DEFINED__ equ 1
endif
ifndef __IMtsGrp_FWD_DEFINED__
__IMtsGrp_FWD_DEFINED__ equ 1
endif
ifndef __IMessageMover_FWD_DEFINED__
__IMessageMover_FWD_DEFINED__ equ 1
endif
ifndef __IEventServerTrace_FWD_DEFINED__
__IEventServerTrace_FWD_DEFINED__ equ 1
endif
ifndef __IGetAppTrackerData_FWD_DEFINED__
__IGetAppTrackerData_FWD_DEFINED__ equ 1
endif
ifndef __IDispenserManager_FWD_DEFINED__
__IDispenserManager_FWD_DEFINED__ equ 1
endif
ifndef __IHolder_FWD_DEFINED__
__IHolder_FWD_DEFINED__ equ 1
endif
ifndef __IDispenserDriver_FWD_DEFINED__
__IDispenserDriver_FWD_DEFINED__ equ 1
endif
ifndef __ITransactionProxy_FWD_DEFINED__
__ITransactionProxy_FWD_DEFINED__ equ 1
endif
ifndef __IContextSecurityPerimeter_FWD_DEFINED__
__IContextSecurityPerimeter_FWD_DEFINED__ equ 1
endif
ifndef __ITxProxyHolder_FWD_DEFINED__
__ITxProxyHolder_FWD_DEFINED__ equ 1
endif
ifndef __IObjectContext_FWD_DEFINED__
__IObjectContext_FWD_DEFINED__ equ 1
endif
ifndef __IObjectControl_FWD_DEFINED__
__IObjectControl_FWD_DEFINED__ equ 1
endif
ifndef __IEnumNames_FWD_DEFINED__
__IEnumNames_FWD_DEFINED__ equ 1
endif
ifndef __ISecurityProperty_FWD_DEFINED__
__ISecurityProperty_FWD_DEFINED__ equ 1
endif
ifndef __ObjectControl_FWD_DEFINED__
__ObjectControl_FWD_DEFINED__ equ 1
endif
ifndef __ISharedProperty_FWD_DEFINED__
__ISharedProperty_FWD_DEFINED__ equ 1
endif
ifndef __ISharedPropertyGroup_FWD_DEFINED__
__ISharedPropertyGroup_FWD_DEFINED__ equ 1
endif
ifndef __ISharedPropertyGroupManager_FWD_DEFINED__
__ISharedPropertyGroupManager_FWD_DEFINED__ equ 1
endif
ifndef __IObjectConstruct_FWD_DEFINED__
__IObjectConstruct_FWD_DEFINED__ equ 1
endif
ifndef __IObjectConstructString_FWD_DEFINED__
__IObjectConstructString_FWD_DEFINED__ equ 1
endif
ifndef __IObjectContextActivity_FWD_DEFINED__
__IObjectContextActivity_FWD_DEFINED__ equ 1
endif
ifndef __IObjectContextInfo_FWD_DEFINED__
__IObjectContextInfo_FWD_DEFINED__ equ 1
endif
ifndef __IObjectContextInfo2_FWD_DEFINED__
__IObjectContextInfo2_FWD_DEFINED__ equ 1
endif
ifndef __ITransactionStatus_FWD_DEFINED__
__ITransactionStatus_FWD_DEFINED__ equ 1
endif
ifndef __IObjectContextTip_FWD_DEFINED__
__IObjectContextTip_FWD_DEFINED__ equ 1
endif
ifndef __IPlaybackControl_FWD_DEFINED__
__IPlaybackControl_FWD_DEFINED__ equ 1
endif
ifndef __IGetContextProperties_FWD_DEFINED__
__IGetContextProperties_FWD_DEFINED__ equ 1
endif
ifndef __IContextState_FWD_DEFINED__
__IContextState_FWD_DEFINED__ equ 1
endif
ifndef __IPoolManager_FWD_DEFINED__
__IPoolManager_FWD_DEFINED__ equ 1
endif
ifndef __ISelectCOMLBServer_FWD_DEFINED__
__ISelectCOMLBServer_FWD_DEFINED__ equ 1
endif
ifndef __ICOMLBArguments_FWD_DEFINED__
__ICOMLBArguments_FWD_DEFINED__ equ 1
endif
ifndef __ICrmLogControl_FWD_DEFINED__
__ICrmLogControl_FWD_DEFINED__ equ 1
endif
ifndef __ICrmCompensatorVariants_FWD_DEFINED__
__ICrmCompensatorVariants_FWD_DEFINED__ equ 1
endif
ifndef __ICrmCompensator_FWD_DEFINED__
__ICrmCompensator_FWD_DEFINED__ equ 1
endif
ifndef __ICrmMonitorLogRecords_FWD_DEFINED__
__ICrmMonitorLogRecords_FWD_DEFINED__ equ 1
endif
ifndef __ICrmMonitorClerks_FWD_DEFINED__
__ICrmMonitorClerks_FWD_DEFINED__ equ 1
endif
ifndef __ICrmMonitor_FWD_DEFINED__
__ICrmMonitor_FWD_DEFINED__ equ 1
endif
ifndef __ICrmFormatLogRecords_FWD_DEFINED__
__ICrmFormatLogRecords_FWD_DEFINED__ equ 1
endif
ifndef __IServiceIISIntrinsicsConfig_FWD_DEFINED__
__IServiceIISIntrinsicsConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceComTIIntrinsicsConfig_FWD_DEFINED__
__IServiceComTIIntrinsicsConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceSxsConfig_FWD_DEFINED__
__IServiceSxsConfig_FWD_DEFINED__ equ 1
endif
ifndef __ICheckSxsConfig_FWD_DEFINED__
__ICheckSxsConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceInheritanceConfig_FWD_DEFINED__
__IServiceInheritanceConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceThreadPoolConfig_FWD_DEFINED__
__IServiceThreadPoolConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceTransactionConfigBase_FWD_DEFINED__
__IServiceTransactionConfigBase_FWD_DEFINED__ equ 1
endif
ifndef __IServiceTransactionConfig_FWD_DEFINED__
__IServiceTransactionConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceSysTxnConfig_FWD_DEFINED__
__IServiceSysTxnConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceSynchronizationConfig_FWD_DEFINED__
__IServiceSynchronizationConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceTrackerConfig_FWD_DEFINED__
__IServiceTrackerConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServicePartitionConfig_FWD_DEFINED__
__IServicePartitionConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServiceCall_FWD_DEFINED__
__IServiceCall_FWD_DEFINED__ equ 1
endif
ifndef __IAsyncErrorNotify_FWD_DEFINED__
__IAsyncErrorNotify_FWD_DEFINED__ equ 1
endif
ifndef __IServiceActivity_FWD_DEFINED__
__IServiceActivity_FWD_DEFINED__ equ 1
endif
ifndef __IThreadPoolKnobs_FWD_DEFINED__
__IThreadPoolKnobs_FWD_DEFINED__ equ 1
endif
ifndef __IComStaThreadPoolKnobs_FWD_DEFINED__
__IComStaThreadPoolKnobs_FWD_DEFINED__ equ 1
endif
ifndef __IComMtaThreadPoolKnobs_FWD_DEFINED__
__IComMtaThreadPoolKnobs_FWD_DEFINED__ equ 1
endif
ifndef __IComStaThreadPoolKnobs2_FWD_DEFINED__
__IComStaThreadPoolKnobs2_FWD_DEFINED__ equ 1
endif
ifndef __IProcessInitializer_FWD_DEFINED__
__IProcessInitializer_FWD_DEFINED__ equ 1
endif
ifndef __IServicePoolConfig_FWD_DEFINED__
__IServicePoolConfig_FWD_DEFINED__ equ 1
endif
ifndef __IServicePool_FWD_DEFINED__
__IServicePool_FWD_DEFINED__ equ 1
endif
ifndef __IManagedPooledObj_FWD_DEFINED__
__IManagedPooledObj_FWD_DEFINED__ equ 1
endif
ifndef __IManagedPoolAction_FWD_DEFINED__
__IManagedPoolAction_FWD_DEFINED__ equ 1
endif
ifndef __IManagedObjectInfo_FWD_DEFINED__
__IManagedObjectInfo_FWD_DEFINED__ equ 1
endif
ifndef __IAppDomainHelper_FWD_DEFINED__
__IAppDomainHelper_FWD_DEFINED__ equ 1
endif
ifndef __IAssemblyLocator_FWD_DEFINED__
__IAssemblyLocator_FWD_DEFINED__ equ 1
endif
ifndef __IManagedActivationEvents_FWD_DEFINED__
__IManagedActivationEvents_FWD_DEFINED__ equ 1
endif
ifndef __ISendMethodEvents_FWD_DEFINED__
__ISendMethodEvents_FWD_DEFINED__ equ 1
endif
ifndef __ITransactionResourcePool_FWD_DEFINED__
__ITransactionResourcePool_FWD_DEFINED__ equ 1
endif
ifndef __IMTSCall_FWD_DEFINED__
__IMTSCall_FWD_DEFINED__ equ 1
endif
ifndef __IContextProperties_FWD_DEFINED__
__IContextProperties_FWD_DEFINED__ equ 1
endif
ifndef __IObjPool_FWD_DEFINED__
__IObjPool_FWD_DEFINED__ equ 1
endif
ifndef __ITransactionProperty_FWD_DEFINED__
__ITransactionProperty_FWD_DEFINED__ equ 1
endif
ifndef __IMTSActivity_FWD_DEFINED__
__IMTSActivity_FWD_DEFINED__ equ 1
endif
ifndef __SecurityIdentity_FWD_DEFINED__
__SecurityIdentity_FWD_DEFINED__ equ 1
endif
ifndef __SecurityCallers_FWD_DEFINED__
__SecurityCallers_FWD_DEFINED__ equ 1
endif
ifndef __SecurityCallContext_FWD_DEFINED__
__SecurityCallContext_FWD_DEFINED__ equ 1
endif
ifndef __GetSecurityCallContextAppObject_FWD_DEFINED__
__GetSecurityCallContextAppObject_FWD_DEFINED__ equ 1
endif
ifndef __IContextState_FWD_DEFINED__
__IContextState_FWD_DEFINED__ equ 1
endif
ifndef __Dummy30040732_FWD_DEFINED__
__Dummy30040732_FWD_DEFINED__ equ 1
endif
ifndef __ContextInfo_FWD_DEFINED__
__ContextInfo_FWD_DEFINED__ equ 1
endif
ifndef __ContextInfo2_FWD_DEFINED__
__ContextInfo2_FWD_DEFINED__ equ 1
endif
ifndef __ObjectControl_FWD_DEFINED__
__ObjectControl_FWD_DEFINED__ equ 1
endif
ifndef __TransactionContext_FWD_DEFINED__
__TransactionContext_FWD_DEFINED__ equ 1
endif
ifndef __TransactionContextEx_FWD_DEFINED__
__TransactionContextEx_FWD_DEFINED__ equ 1
endif
ifndef __ByotServerEx_FWD_DEFINED__
__ByotServerEx_FWD_DEFINED__ equ 1
endif
ifndef __CServiceConfig_FWD_DEFINED__
__CServiceConfig_FWD_DEFINED__ equ 1
endif
ifndef __ServicePool_FWD_DEFINED__
__ServicePool_FWD_DEFINED__ equ 1
endif
ifndef __ServicePoolConfig_FWD_DEFINED__
__ServicePoolConfig_FWD_DEFINED__ equ 1
endif
ifndef __SharedProperty_FWD_DEFINED__
__SharedProperty_FWD_DEFINED__ equ 1
endif
ifndef __SharedPropertyGroup_FWD_DEFINED__
__SharedPropertyGroup_FWD_DEFINED__ equ 1
endif
ifndef __SharedPropertyGroupManager_FWD_DEFINED__
__SharedPropertyGroupManager_FWD_DEFINED__ equ 1
endif
ifndef __COMEvents_FWD_DEFINED__
__COMEvents_FWD_DEFINED__ equ 1
endif
ifndef __CoMTSLocator_FWD_DEFINED__
__CoMTSLocator_FWD_DEFINED__ equ 1
endif
ifndef __MtsGrp_FWD_DEFINED__
__MtsGrp_FWD_DEFINED__ equ 1
endif
ifndef __ComServiceEvents_FWD_DEFINED__
__ComServiceEvents_FWD_DEFINED__ equ 1
endif
ifndef __ComSystemAppEventData_FWD_DEFINED__
__ComSystemAppEventData_FWD_DEFINED__ equ 1
endif
ifndef __CRMClerk_FWD_DEFINED__
__CRMClerk_FWD_DEFINED__ equ 1
endif
ifndef __CRMRecoveryClerk_FWD_DEFINED__
__CRMRecoveryClerk_FWD_DEFINED__ equ 1
endif
ifndef __LBEvents_FWD_DEFINED__
__LBEvents_FWD_DEFINED__ equ 1
endif
ifndef __MessageMover_FWD_DEFINED__
__MessageMover_FWD_DEFINED__ equ 1
endif
ifndef __DispenserManager_FWD_DEFINED__
__DispenserManager_FWD_DEFINED__ equ 1
endif
ifndef __PoolMgr_FWD_DEFINED__
__PoolMgr_FWD_DEFINED__ equ 1
endif
ifndef __EventServer_FWD_DEFINED__
__EventServer_FWD_DEFINED__ equ 1
endif
ifndef __TrackerServer_FWD_DEFINED__
__TrackerServer_FWD_DEFINED__ equ 1
endif
ifndef __AppDomainHelper_FWD_DEFINED__
__AppDomainHelper_FWD_DEFINED__ equ 1
endif
ifndef __ClrAssemblyLocator_FWD_DEFINED__
__ClrAssemblyLocator_FWD_DEFINED__ equ 1
endif

include unknwn.inc
include oaidl.inc
include ocidl.inc
include comadmin.inc
include transact.inc
include txdtc.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include objbase.inc
ifndef DECLSPEC_UUID
if (_MSC_VER GE 1100) AND defined (__cplusplus)
DECLSPEC_UUID macro x
	exitm<__declspec(uuid(x))>
	endm
else
DECLSPEC_UUID macro x
	exitm<>
	endm
endif
endif

ifndef __ISecurityIdentityColl_INTERFACE_DEFINED__
__ISecurityIdentityColl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISecurityIdentityColl, "CAFC823C-B441-11d1-B82B-0000F8757E2A")

.comdef ISecurityIdentityColl : public IDispatch

    get_Count		proc :ptr LONG
    get_Item		proc :BSTR, :ptr VARIANT
    get__NewEnum	proc :ptr ptr IUnknown
    .ends

endif

ifndef __ISecurityCallersColl_INTERFACE_DEFINED__
__ISecurityCallersColl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISecurityCallersColl, "CAFC823D-B441-11d1-B82B-0000F8757E2A")

.comdef ISecurityCallersColl : public IDispatch

    get_Count		proc :ptr LONG
    get_Item		proc :LONG, :ptr ptr ISecurityIdentityColl
    get__NewEnum	proc :ptr ptr IUnknown
    .ends

endif

ifndef __ISecurityCallContext_INTERFACE_DEFINED__
__ISecurityCallContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISecurityCallContext, "CAFC823E-B441-11d1-B82B-0000F8757E2A")

.comdef ISecurityCallContext : public IDispatch

    get_Count		proc :ptr LONG
    get_Item		proc :BSTR, :ptr VARIANT
    get__NewEnum	proc :ptr ptr IUnknown
    IsCallerInRole	proc :BSTR, :ptr VARIANT_BOOL
    IsSecurityEnabled	proc :ptr VARIANT_BOOL
    IsUserInRole	proc :ptr VARIANT, :BSTR, :ptr VARIANT_BOOL
    .ends

endif

ifndef __IGetSecurityCallContext_INTERFACE_DEFINED__
__IGetSecurityCallContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IGetSecurityCallContext, "CAFC823F-B441-11d1-B82B-0000F8757E2A")

.comdef IGetSecurityCallContext : public IDispatch

    GetSecurityCallContext proc :ptr ptr ISecurityCallContext
    .ends

endif

ifndef __SecurityProperty_INTERFACE_DEFINED__
__SecurityProperty_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(SecurityProperty, "E74A7215-014D-11d1-A63C-00A0C911B4E0")

.comdef SecurityProperty : public IDispatch

    GetDirectCallerName proc :ptr BSTR
    GetDirectCreatorName proc :ptr BSTR
    GetOriginalCallerName proc :ptr BSTR
    GetOriginalCreatorName proc :ptr BSTR
    .ends

endif

ifndef __ContextInfo_INTERFACE_DEFINED__
__ContextInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ContextInfo, "19A5A02C-0AC8-11d2-B286-00C04F8EF934")

.comdef ContextInfo : public IDispatch

    IsInTransaction	proc :ptr VARIANT_BOOL
    GetTransaction	proc :ptr ptr IUnknown
    GetTransactionId	proc :ptr BSTR
    GetActivityId	proc :ptr BSTR
    GetContextId	proc :ptr BSTR
    .ends

endif

ifndef __ContextInfo2_INTERFACE_DEFINED__
__ContextInfo2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ContextInfo2, "c99d6e75-2375-11d4-8331-00c04f605588")

.comdef ContextInfo2 : public ContextInfo

    GetPartitionId	proc :ptr BSTR
    GetApplicationId	proc :ptr BSTR
    GetApplicationInstanceId proc :ptr BSTR
    .ends

endif

ifndef __ObjectContext_INTERFACE_DEFINED__
__ObjectContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ObjectContext, "74C08646-CEDB-11CF-8B49-00AA00B8A790")

.comdef ObjectContext : public IDispatch

    CreateInstance	proc :BSTR, :ptr VARIANT
    SetComplete		proc
    SetAbort		proc
    EnableCommit	proc
    DisableCommit	proc
    IsInTransaction	proc :ptr VARIANT_BOOL
    IsSecurityEnabled	proc :ptr VARIANT_BOOL
    IsCallerInRole	proc :BSTR, :ptr VARIANT_BOOL
    get_Count		proc :ptr LONG
    get_Item		proc :BSTR, :ptr VARIANT
    get__NewEnum	proc :ptr ptr IUnknown
    get_Security	proc :ptr ptr SecurityProperty
    get_ContextInfo	proc :ptr ptr ContextInfo
    .ends

endif

ifndef __ITransactionContextEx_INTERFACE_DEFINED__
__ITransactionContextEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransactionContextEx, "7999FC22-D3C6-11CF-ACAB-00A024A55AEF")

.comdef ITransactionContextEx : public IUnknown

    CreateInstance	proc :REFCLSID, :REFIID, :ptr ptr
    Commit		proc
    Abort		proc
    .ends

endif

ifndef __ITransactionContext_INTERFACE_DEFINED__
__ITransactionContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransactionContext, "7999FC21-D3C6-11CF-ACAB-00A024A55AEF")

.comdef ITransactionContext : public IDispatch

    CreateInstance	proc :BSTR, :ptr VARIANT
    Commit		proc
    Abort		proc
    .ends

endif

ifndef __ICreateWithTransactionEx_INTERFACE_DEFINED__
__ICreateWithTransactionEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICreateWithTransactionEx, "455ACF57-5345-11d2-99CF-00C04F797BC9")

.comdef ICreateWithTransactionEx : public IUnknown

    CreateInstance	proc :ptr ITransaction, :REFCLSID, :REFIID, :ptr ptr
    .ends

endif

ifndef __ICreateWithLocalTransaction_INTERFACE_DEFINED__
__ICreateWithLocalTransaction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICreateWithLocalTransaction, "227AC7A8-8423-42ce-B7CF-03061EC9AAA3")

.comdef ICreateWithLocalTransaction : public IUnknown

    CreateInstanceWithSysTx proc :ptr IUnknown, :REFCLSID, :REFIID, :ptr ptr
    .ends

endif

ifndef __ICreateWithTipTransactionEx_INTERFACE_DEFINED__
__ICreateWithTipTransactionEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICreateWithTipTransactionEx, "455ACF59-5345-11d2-99CF-00C04F797BC9")

.comdef ICreateWithTipTransactionEx : public IUnknown

    CreateInstance	proc :BSTR, :REFCLSID, :REFIID, :ptr ptr
    .ends

endif

MTS_OBJID		typedef qword
MTS_RESID		typedef qword
ULONG64			typedef qword

ifndef _COMSVCSEVENTINFO_
_COMSVCSEVENTINFO_ equ <>

COMSVCSEVENTINFO	STRUC
cbSize			dd ?
dwPid			dd ?
lTime			LONGLONG ?
lMicroTime		LONG ?
perfCount		LONGLONG ?
guidApp			GUID <>
sMachineName		LPOLESTR ?
COMSVCSEVENTINFO	ENDS

endif

ifndef __IComLTxEvents_INTERFACE_DEFINED__
__IComLTxEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComLTxEvents, "605CF82C-578E-4298-975D-82BABCD9E053")

.comdef IComLTxEvents : public IUnknown

    OnLtxTransactionStart proc :ptr, :GUID, :GUID, :BOOL, :int_t
    OnLtxTransactionPrepare proc :ptr, :GUID, :BOOL
    OnLtxTransactionAbort proc :ptr, :GUID
    OnLtxTransactionCommit proc :ptr, :GUID
    OnLtxTransactionPromote proc :ptr, :GUID, :GUID
    .ends

endif

ifndef __IComUserEvent_INTERFACE_DEFINED__
__IComUserEvent_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComUserEvent, "683130A4-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComUserEvent : public IUnknown

    OnUserEvent		proc :ptr, :ptr
    .ends

endif

ifndef __IComThreadEvents_INTERFACE_DEFINED__
__IComThreadEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComThreadEvents, "683130A5-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComThreadEvents : public IUnknown

    OnThreadStart	proc :ptr, :ULONG64, :DWORD, :DWORD
    OnThreadTerminate	proc :ptr, :ULONG64, :DWORD, :DWORD
    OnThreadBindToApartment proc :ptr, :ULONG64, :ULONG64, :DWORD, :DWORD
    OnThreadUnBind	proc :ptr, :ULONG64, :ULONG64, :DWORD
    OnThreadWorkEnque	proc :ptr, :ULONG64, :ULONG64, :DWORD
    OnThreadWorkPrivate proc :ptr, :ULONG64, :ULONG64
    OnThreadWorkPublic	proc :ptr, :ULONG64, :ULONG64, :DWORD
    OnThreadWorkRedirect proc :ptr, :ULONG64, :ULONG64, :DWORD, :ULONG64
    OnThreadWorkReject	proc :ptr, :ULONG64, :ULONG64, :DWORD
    OnThreadAssignApartment proc :ptr, :REFGUID, :ULONG64
    OnThreadUnassignApartment proc :ptr, :ULONG64
    .ends

endif

ifndef __IComAppEvents_INTERFACE_DEFINED__
__IComAppEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComAppEvents, "683130A6-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComAppEvents : public IUnknown

    OnAppActivation	proc :ptr, :GUID
    OnAppShutdown	proc :ptr, :GUID
    OnAppForceShutdown	proc :ptr, :GUID
    .ends

endif

ifndef __IComInstanceEvents_INTERFACE_DEFINED__
__IComInstanceEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComInstanceEvents, "683130A7-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComInstanceEvents : public IUnknown

    OnObjectCreate	proc :ptr, :REFGUID, :REFCLSID, :REFGUID, :ULONG64, :ULONG64
    OnObjectDestroy	proc :ptr, :ULONG64
    .ends

endif

ifndef __IComTransactionEvents_INTERFACE_DEFINED__
__IComTransactionEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComTransactionEvents, "683130A8-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComTransactionEvents : public IUnknown

    OnTransactionStart	proc :ptr, :REFGUID, :REFGUID, :BOOL
    OnTransactionPrepare proc :ptr, :REFGUID, :BOOL
    OnTransactionAbort	proc :ptr, :REFGUID
    OnTransactionCommit proc :ptr, :REFGUID
    .ends

endif

ifndef __IComMethodEvents_INTERFACE_DEFINED__
__IComMethodEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComMethodEvents, "683130A9-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComMethodEvents : public IUnknown

    OnMethodCall	proc :ptr, :ULONG64, :REFCLSID, :REFIID, :ULONG
    OnMethodReturn	proc :ptr, :ULONG64, :REFCLSID, :REFIID, :ULONG, :HRESULT
    OnMethodException	proc :ptr, :ULONG64, :REFCLSID, :REFIID, :ULONG
    .ends

endif

ifndef __IComObjectEvents_INTERFACE_DEFINED__
__IComObjectEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComObjectEvents, "683130AA-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComObjectEvents : public IUnknown

    OnObjectActivate	proc :ptr, :ULONG64, :ULONG64
    OnObjectDeactivate	proc :ptr, :ULONG64, :ULONG64
    OnDisableCommit	proc :ptr, :ULONG64
    OnEnableCommit	proc :ptr, :ULONG64
    OnSetComplete	proc :ptr, :ULONG64
    OnSetAbort		proc :ptr, :ULONG64
    .ends

endif

ifndef __IComResourceEvents_INTERFACE_DEFINED__
__IComResourceEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComResourceEvents, "683130AB-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComResourceEvents : public IUnknown

    OnResourceCreate	proc :ptr, :ULONG64, :LPCOLESTR, :ULONG64, :BOOL
    OnResourceAllocate	proc :ptr, :ULONG64, :LPCOLESTR, :ULONG64, :BOOL, :DWORD, :DWORD
    OnResourceRecycle	proc :ptr, :ULONG64, :LPCOLESTR, :ULONG64
    OnResourceDestroy	proc :ptr, :ULONG64, :HRESULT, :LPCOLESTR, :ULONG64
    OnResourceTrack	proc :ptr, :ULONG64, :LPCOLESTR, :ULONG64, :BOOL
    .ends

endif

ifndef __IComSecurityEvents_INTERFACE_DEFINED__
__IComSecurityEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComSecurityEvents, "683130AC-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComSecurityEvents : public IUnknown

    OnAuthenticate	proc :ptr, :REFGUID, :ULONG64, :REFGUID, :ULONG, :ULONG, :ptr, :BOOL
    OnAuthenticateFail	proc :ptr, :REFGUID, :ULONG64, :REFGUID, :ULONG, :ULONG, :ptr, :BOOL
    .ends

endif

ifndef __IComObjectPoolEvents_INTERFACE_DEFINED__
__IComObjectPoolEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComObjectPoolEvents, "683130AD-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComObjectPoolEvents : public IUnknown

    OnObjPoolPutObject	proc :ptr, :REFGUID, :int_t, :DWORD, :ULONG64
    OnObjPoolGetObject	proc :ptr, :REFGUID, :REFGUID, :DWORD, :ULONG64
    OnObjPoolRecycleToTx proc :ptr, :REFGUID, :REFGUID, :REFGUID, :ULONG64
    OnObjPoolGetFromTx	proc :ptr, :REFGUID, :REFGUID, :REFGUID, :ULONG64
    .ends

endif

ifndef __IComObjectPoolEvents2_INTERFACE_DEFINED__
__IComObjectPoolEvents2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComObjectPoolEvents2, "683130AE-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComObjectPoolEvents2 : public IUnknown

    OnObjPoolCreateObject proc :ptr, :REFGUID, :DWORD, :ULONG64
    OnObjPoolDestroyObject proc :ptr, :REFGUID, :DWORD, :ULONG64
    OnObjPoolCreateDecision proc :ptr, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
    OnObjPoolTimeout	proc :ptr, :REFGUID, :REFGUID, :DWORD
    OnObjPoolCreatePool proc :ptr, :REFGUID, :DWORD, :DWORD, :DWORD
    .ends

endif

ifndef __IComObjectConstructionEvents_INTERFACE_DEFINED__
__IComObjectConstructionEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComObjectConstructionEvents, "683130AF-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComObjectConstructionEvents : public IUnknown

    OnObjectConstruct	proc :ptr, :REFGUID, :LPCOLESTR, :ULONG64
    .ends

endif

ifndef __IComActivityEvents_INTERFACE_DEFINED__
__IComActivityEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComActivityEvents, "683130B0-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComActivityEvents : public IUnknown

    OnActivityCreate	proc :ptr, :REFGUID
    OnActivityDestroy	proc :ptr, :REFGUID
    OnActivityEnter	proc :ptr, :REFGUID, :REFGUID, :DWORD
    OnActivityTimeout	proc :ptr, :REFGUID, :REFGUID, :DWORD, :DWORD
    OnActivityReenter	proc :ptr, :REFGUID, :DWORD, :DWORD
    OnActivityLeave	proc :ptr, :REFGUID, :REFGUID
    OnActivityLeaveSame proc :ptr, :REFGUID, :DWORD
    .ends

endif

ifndef __IComIdentityEvents_INTERFACE_DEFINED__
__IComIdentityEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComIdentityEvents, "683130B1-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComIdentityEvents : public IUnknown

    OnIISRequestInfo	proc :ptr, :ULONG64, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR
    .ends

endif

ifndef __IComQCEvents_INTERFACE_DEFINED__
__IComQCEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComQCEvents, "683130B2-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComQCEvents : public IUnknown

    OnQCRecord		proc :ptr, :ULONG64
    OnQCQueueOpen	proc :ptr
    OnQCReceive		proc :ptr, :ULONG64, :REFGUID, :REFGUID, :HRESULT
    OnQCReceiveFail	proc :ptr, :ULONG64, :HRESULT
    OnQCMoveToReTryQueue proc :ptr, :REFGUID, :REFGUID, :ULONG
    OnQCMoveToDeadQueue proc :ptr, :REFGUID, :REFGUID
    OnQCPlayback	proc :ptr, :ULONG64, :REFGUID, :REFGUID, :HRESULT
    .ends

endif

ifndef __IComExceptionEvents_INTERFACE_DEFINED__
__IComExceptionEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComExceptionEvents, "683130B3-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComExceptionEvents : public IUnknown

    OnExceptionUser	proc :ptr, :ULONG, :ULONG64, :LPCOLESTR
    .ends

endif

ifndef __ILBEvents_INTERFACE_DEFINED__
__ILBEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ILBEvents, "683130B4-2E50-11d2-98A5-00C04F8EE1C4")

.comdef ILBEvents : public IUnknown

    TargetUp		proc :BSTR, :BSTR
    TargetDown		proc :BSTR, :BSTR
    EngineDefined	proc :BSTR, :ptr VARIANT, :BSTR
    .ends

endif

ifndef __IComCRMEvents_INTERFACE_DEFINED__
__IComCRMEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComCRMEvents, "683130B5-2E50-11d2-98A5-00C04F8EE1C4")

.comdef IComCRMEvents : public IUnknown

    OnCRMRecoveryStart	proc :ptr, :ptr GUID
    OnCRMRecoveryDone	proc :ptr, :ptr GUID
    OnCRMCheckpoint	proc :ptr, :ptr GUID
    OnCRMBegin		proc :ptr, :ptr GUID, :ptr GUID, :ptr GUID, :ptr WCHAR, :ptr WCHAR
    OnCRMPrepare	proc :ptr, :ptr GUID
    OnCRMCommit		proc :ptr, :ptr GUID
    OnCRMAbort		proc :ptr, :ptr GUID
    OnCRMIndoubt	proc :ptr, :ptr GUID
    OnCRMDone		proc :ptr, :ptr GUID
    OnCRMRelease	proc :ptr, :ptr GUID
    OnCRMAnalyze	proc :ptr, :ptr GUID, :DWORD, :DWORD
    OnCRMWrite		proc :ptr, :ptr GUID, :BOOL, :DWORD
    OnCRMForget		proc :ptr, :ptr GUID
    OnCRMForce		proc :ptr, :ptr GUID
    OnCRMDeliver	proc :ptr, :ptr GUID, :BOOL, :DWORD
    .ends

endif

ifndef __IComMethod2Events_INTERFACE_DEFINED__
__IComMethod2Events_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComMethod2Events, "FB388AAA-567D-4024-AF8E-6E93EE748573")

.comdef IComMethod2Events : public IUnknown

    OnMethodCall2	proc :ptr, :ULONG64, :REFCLSID, :REFIID, :DWORD, :ULONG
    OnMethodReturn2	proc :ptr, :ULONG64, :REFCLSID, :REFIID, :DWORD, :ULONG, :HRESULT
    OnMethodException2	proc :ptr, :ULONG64, :REFCLSID, :REFIID, :DWORD, :ULONG
    .ends

endif

ifndef __IComTrackingInfoEvents_INTERFACE_DEFINED__
__IComTrackingInfoEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComTrackingInfoEvents, "4e6cdcc9-fb25-4fd5-9cc5-c9f4b6559cec")

.comdef IComTrackingInfoEvents : public IUnknown

    OnNewTrackingInfo	proc :ptr
    .ends

endif

.enum TRACKING_COLL_TYPE {
    TRKCOLL_PROCESSES	= 0,
    TRKCOLL_APPLICATIONS = ( TRKCOLL_PROCESSES + 1 ),
    TRKCOLL_COMPONENTS	= ( TRKCOLL_APPLICATIONS + 1 )
    }

ifndef __IComTrackingInfoCollection_INTERFACE_DEFINED__
__IComTrackingInfoCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComTrackingInfoCollection, "c266c677-c9ad-49ab-9fd9-d9661078588a")

.comdef IComTrackingInfoCollection : public IUnknown

    Type		proc :ptr
    Count		proc :ptr
    Item		proc :ULONG, :REFIID, :ptr
    .ends

endif

ifndef __IComTrackingInfoObject_INTERFACE_DEFINED__
__IComTrackingInfoObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComTrackingInfoObject, "116e42c5-d8b1-47bf-ab1e-c895ed3e2372")

.comdef IComTrackingInfoObject : public IUnknown

    GetValue		proc :LPOLESTR, :ptr
    .ends

endif

ifndef __IComTrackingInfoProperties_INTERFACE_DEFINED__
__IComTrackingInfoProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComTrackingInfoProperties, "789b42be-6f6b-443a-898e-67abf390aa14")

.comdef IComTrackingInfoProperties : public IUnknown

    PropCount		proc :ptr
    GetPropName		proc :ULONG, :ptr
    .ends

endif

ifndef __IComApp2Events_INTERFACE_DEFINED__
__IComApp2Events_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComApp2Events, "1290BC1A-B219-418d-B078-5934DED08242")

.comdef IComApp2Events : public IUnknown

    OnAppActivation2	proc :ptr, :GUID, :GUID
    OnAppShutdown2	proc :ptr, :GUID
    OnAppForceShutdown2 proc :ptr, :GUID
    OnAppPaused2	proc :ptr, :GUID, :BOOL
    OnAppRecycle2	proc :ptr, :GUID, :GUID, :LONG
    .ends

endif

ifndef __IComTransaction2Events_INTERFACE_DEFINED__
__IComTransaction2Events_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComTransaction2Events, "A136F62A-2F94-4288-86E0-D8A1FA4C0299")

.comdef IComTransaction2Events : public IUnknown

    OnTransactionStart2 proc :ptr, :REFGUID, :REFGUID, :BOOL, :int_t
    OnTransactionPrepare2 proc :ptr, :REFGUID, :BOOL
    OnTransactionAbort2 proc :ptr, :REFGUID
    OnTransactionCommit2 proc :ptr, :REFGUID
    .ends

endif

ifndef __IComInstance2Events_INTERFACE_DEFINED__
__IComInstance2Events_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComInstance2Events, "20E3BF07-B506-4ad5-A50C-D2CA5B9C158E")

.comdef IComInstance2Events : public IUnknown

    OnObjectCreate2	proc :ptr, :REFGUID, :REFCLSID, :REFGUID, :ULONG64, :ULONG64, :REFGUID
    OnObjectDestroy2	proc :ptr, :ULONG64
    .ends

endif

ifndef __IComObjectPool2Events_INTERFACE_DEFINED__
__IComObjectPool2Events_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComObjectPool2Events, "65BF6534-85EA-4f64-8CF4-3D974B2AB1CF")

.comdef IComObjectPool2Events : public IUnknown

    OnObjPoolPutObject2 proc :ptr, :REFGUID, :int_t, :DWORD, :ULONG64
    OnObjPoolGetObject2 proc :ptr, :REFGUID, :REFGUID, :DWORD, :ULONG64, :REFGUID
    OnObjPoolRecycleToTx2 proc :ptr, :REFGUID, :REFGUID, :REFGUID, :ULONG64
    OnObjPoolGetFromTx2 proc :ptr, :REFGUID, :REFGUID, :REFGUID, :ULONG64, :REFGUID
    .ends

endif

ifndef __IComObjectConstruction2Events_INTERFACE_DEFINED__
__IComObjectConstruction2Events_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComObjectConstruction2Events, "4B5A7827-8DF2-45c0-8F6F-57EA1F856A9F")

.comdef IComObjectConstruction2Events : public IUnknown

    OnObjectConstruct2	proc :ptr, :REFGUID, :LPCOLESTR, :ULONG64, :REFGUID
    .ends

endif

ifndef __ISystemAppEventData_INTERFACE_DEFINED__
__ISystemAppEventData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISystemAppEventData, "D6D48A3C-D5C5-49E7-8C74-99E4889ED52F")

.comdef ISystemAppEventData : public IUnknown

    Startup		proc
    OnDataChanged	proc :DWORD, :DWORD, :DWORD, :BSTR, :DWORD, :ULONG64
    .ends

endif

ifndef __IMtsEvents_INTERFACE_DEFINED__
__IMtsEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMtsEvents, "BACEDF4D-74AB-11D0-B162-00AA00BA3258")

.comdef IMtsEvents : public IDispatch

    get_PackageName	proc :ptr BSTR
    get_PackageGuid	proc :ptr BSTR
    PostEvent		proc :ptr VARIANT
    get_FireEvents	proc :ptr VARIANT_BOOL
    GetProcessID	proc :ptr LONG
    .ends

endif

ifndef __IMtsEventInfo_INTERFACE_DEFINED__
__IMtsEventInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMtsEventInfo, "D56C3DC1-8482-11d0-B170-00AA00BA3258")

.comdef IMtsEventInfo : public IDispatch

    get_Names		proc :ptr ptr IUnknown
    get_DisplayName	proc :ptr BSTR
    get_EventID		proc :ptr BSTR
    get_Count		proc :ptr LONG
    get_Value		proc :BSTR, :ptr VARIANT
    .ends

endif

ifndef __IMTSLocator_INTERFACE_DEFINED__
__IMTSLocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMTSLocator, "D19B8BFD-7F88-11D0-B16E-00AA00BA3258")

.comdef IMTSLocator : public IDispatch

    GetEventDispatcher	proc :ptr ptr IUnknown
    .ends

endif

ifndef __IMtsGrp_INTERFACE_DEFINED__
__IMtsGrp_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMtsGrp, "4B2E958C-0393-11D1-B1AB-00AA00BA3258")

.comdef IMtsGrp : public IDispatch

    get_Count		proc :ptr LONG
    Item		proc :LONG, :ptr ptr IUnknown
    Refresh		proc
    .ends

endif

ifndef __IMessageMover_INTERFACE_DEFINED__
__IMessageMover_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMessageMover, "588A085A-B795-11D1-8054-00C04FC340EE")

.comdef IMessageMover : public IDispatch

    get_SourcePath	proc :ptr BSTR
    put_SourcePath	proc :BSTR
    get_DestPath	proc :ptr BSTR
    put_DestPath	proc :BSTR
    get_CommitBatchSize proc :ptr LONG
    put_CommitBatchSize proc :LONG
    MoveMessages	proc :ptr LONG
    .ends

endif

ifndef __IEventServerTrace_INTERFACE_DEFINED__
__IEventServerTrace_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEventServerTrace, "9A9F12B8-80AF-47ab-A579-35EA57725370")

.comdef IEventServerTrace : public IDispatch

    StartTraceGuid	proc :BSTR, :BSTR, :LONG
    StopTraceGuid	proc :BSTR, :BSTR, :LONG
    EnumTraceGuid	proc :ptr LONG, :ptr BSTR
    .ends

endif

RECYCLE_INFO		STRUC
guidCombaseProcessIdentifier GUID <>
ProcessStartTime	LONGLONG ?
dwRecycleLifetimeLimit	dd ?
dwRecycleMemoryLimit	dd ?
dwRecycleExpirationTimeout dd ?
RECYCLE_INFO		ENDS

.enum DUMPTYPE {
    DUMPTYPE_FULL	= 0,
    DUMPTYPE_MINI	= ( DUMPTYPE_FULL + 1 ) ,
    DUMPTYPE_NONE	= ( DUMPTYPE_MINI + 1 )
    }

HANG_INFO		STRUC
fAppHangMonitorEnabled	BOOL ?
fTerminateOnHang	BOOL ?
DumpType		DUMPTYPE ?
dwHangTimeout		dd ?
dwDumpCount		dd ?
dwInfoMsgCount		dd ?
HANG_INFO		ENDS

.enum COMPLUS_APPTYPE {
    APPTYPE_UNKNOWN	= 0xffffffff,
    APPTYPE_SERVER	= 1,
    APPTYPE_LIBRARY	= 0,
    APPTYPE_SWC = 2
    }


TRACKER_STARTSTOP_EVENT equ <L"Global\\COM+ Tracker Push Event">
TRACKER_INIT_EVENT	equ <L"Global\\COM+ Tracker Init Event">


ifndef GUID_STRING_SIZE
GUID_STRING_SIZE	equ 40
endif
APPSTATISTICS		STRUC
m_cTotalCalls		dd ?
m_cTotalInstances	dd ?
m_cTotalClasses		dd ?
m_cCallsPerSecond	dd ?
APPSTATISTICS		ENDS

APPDATA			STRUC
m_idApp			dd ?
m_szAppGuid		WCHAR 40 dup(?)
m_dwAppProcessId	dd ?
m_AppStatistics		APPSTATISTICS <>
APPDATA			ENDS

CLSIDDATA		STRUC
m_clsid			CLSID <>
m_cReferences		dd ?
m_cBound		dd ?
m_cPooled		dd ?
m_cInCall		dd ?
m_dwRespTime		dd ?
m_cCallsCompleted	dd ?
m_cCallsFailed		dd ?
CLSIDDATA		ENDS

CLSIDDATA2		STRUC
m_clsid			CLSID <>
m_appid			GUID <>
m_partid		GUID <>
m_eAppType		COMPLUS_APPTYPE ?
m_cReferences		dd ?
m_cBound		dd ?
m_cPooled		dd ?
m_cInCall		dd ?
m_dwRespTime		dd ?
m_cCallsCompleted	dd ?
m_cCallsFailed		dd ?
CLSIDDATA2		ENDS

ifndef __IGetAppTrackerData_INTERFACE_DEFINED__
__IGetAppTrackerData_INTERFACE_DEFINED__ equ 1

DATA_NOT_AVAILABLE	equ ( 0xffffffff )

.enum GetAppTrackerDataFlags {
    GATD_INCLUDE_PROCESS_EXE_NAME	= 0x1,
    GATD_INCLUDE_LIBRARY_APPS	= 0x2,
    GATD_INCLUDE_SWC	= 0x4,
    GATD_INCLUDE_CLASS_NAME	= 0x8,
    GATD_INCLUDE_APPLICATION_NAME	= 0x10
    }

ApplicationProcessSummary STRUC
PartitionIdPrimaryApplication GUID <>
ApplicationIdPrimaryApplication GUID <>
ApplicationInstanceId	GUID <>
ProcessId		dd ?
Type			COMPLUS_APPTYPE ?
IsService		BOOL ?
IsPaused		BOOL ?
IsRecycled		BOOL ?
ApplicationProcessSummary ENDS

ApplicationProcessStatistics STRUC
NumCallsOutstanding	ULONG ?
NumTrackedComponents	ULONG ?
NumComponentInstances	ULONG ?
AvgCallsPerSecond	ULONG ?
Reserved1		ULONG ?
Reserved2		ULONG ?
Reserved3		ULONG ?
Reserved4		ULONG ?
ApplicationProcessStatistics ENDS

ApplicationProcessRecycleInfo STRUC
IsRecyclable		BOOL ?
IsRecycled		BOOL ?
TimeRecycled		FILETIME <>
TimeToTerminate		FILETIME <>
RecycleReasonCode	LONG ?
IsPendingRecycle	BOOL ?
HasAutomaticLifetimeRecycling BOOL ?
TimeForAutomaticRecycling FILETIME <>
MemoryLimitInKB		ULONG ?
MemoryUsageInKBLastCheck ULONG ?
ActivationLimit		ULONG ?
NumActivationsLastReported ULONG ?
CallLimit		ULONG ?
NumCallsLastReported	ULONG ?
ApplicationProcessRecycleInfo ENDS

ApplicationSummary	STRUC
ApplicationInstanceId	GUID <>
PartitionId		GUID <>
ApplicationId		GUID <>
Type			COMPLUS_APPTYPE ?
NumTrackedComponents	ULONG ?
NumComponentInstances	ULONG ?
ApplicationSummary	ENDS

ComponentSummary	STRUC
ApplicationInstanceId	GUID <>
PartitionId		GUID <>
ApplicationId		GUID <>
Clsid			CLSID <>
ComponentSummary	ENDS

ComponentStatistics	STRUC
NumInstances		ULONG ?
NumBoundReferences	ULONG ?
NumPooledObjects	ULONG ?
NumObjectsInCall	ULONG ?
AvgResponseTimeInMs	ULONG ?
NumCallsCompletedRecent ULONG ?
NumCallsFailedRecent	ULONG ?
NumCallsCompletedTotal	ULONG ?
NumCallsFailedTotal	ULONG ?
Reserved1		ULONG ?
Reserved2		ULONG ?
Reserved3		ULONG ?
Reserved4		ULONG ?
ComponentStatistics	ENDS

ComponentHangMonitorInfo STRUC
IsMonitored		BOOL ?
TerminateOnHang		BOOL ?
AvgCallThresholdInMs	ULONG ?
ComponentHangMonitorInfo ENDS


DEFINE_IIDX(IGetAppTrackerData, "507C3AC8-3E12-4cb0-9366-653D3E050638")

.comdef IGetAppTrackerData : public IUnknown

    GetApplicationProcesses proc :REFGUID, :REFGUID, :DWORD, :ptr ULONG, :ptr ptr ApplicationProcessSummary
    GetApplicationProcessDetails proc :REFGUID, :DWORD, :DWORD, :ptr ApplicationProcessSummary, :ptr ApplicationProcessStatistics, :ptr ApplicationProcessRecycleInfo, :ptr BOOL
    GetApplicationsInProcess proc :REFGUID, :DWORD, :REFGUID, :DWORD, :ptr ULONG, :ptr ptr ApplicationSummary
    GetComponentsInProcess proc :REFGUID, :DWORD, :REFGUID, :REFGUID, :DWORD, :ptr LONG, :ptr ptr ComponentSummary
    GetComponentDetails proc :REFGUID, :DWORD, :REFCLSID, :DWORD, :ptr ComponentSummary, :ptr ComponentStatistics,  :ptr ComponentHangMonitorInfo
    GetTrackerDataAsCollectionObject proc :ptr ptr IUnknown
    GetSuggestedPollingInterval proc :ptr DWORD
    .ends

IGetAppTrackerData_RemoteGetApplicationProcessDetails_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


IGetAppTrackerData_RemoteGetComponentDetails_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef DECLSPEC_UUID
if (_MSC_VER GE 1100) AND defined (__cplusplus)
DECLSPEC_UUID macro x
	exitm<__declspec(uuid(x))>
	endm
else
DECLSPEC_UUID macro x
	exitm<>
	endm
endif
endif
RESTYPID		typedef DWORD_PTR
RESID			typedef DWORD_PTR
SRESID			typedef LPOLESTR
constSRESID		typedef LPCOLESTR
RESOURCERATING		typedef DWORD
TIMEINSECS		typedef LONG
INSTID			typedef DWORD_PTR
TRANSID			typedef DWORD_PTR

MTXDM_E_ENLISTRESOURCEFAILED equ 0x8004E100

ifndef __IDispenserManager_INTERFACE_DEFINED__
__IDispenserManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDispenserManager, "5cb31e10-2b5f-11cf-be10-00aa00a2fa25")

.comdef IDispenserManager : public IUnknown

    RegisterDispenser	proc :ptr, :LPCOLESTR, :ptr
    GetContext		proc :ptr, :ptr
    .ends

endif

ifndef __IHolder_INTERFACE_DEFINED__
__IHolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IHolder, "bf6a1850-2b45-11cf-be10-00aa00a2fa25")

.comdef IHolder : public IUnknown

    AllocResource	proc :RESTYPID, :ptr
    FreeResource	proc :RESID
    TrackResource	proc :RESID
    TrackResourceS	proc :constSRESID
    UntrackResource	proc :RESID, :BOOL
    UntrackResourceS	proc :constSRESID, :BOOL
    Close		proc
    RequestDestroyResource proc :RESID
    .ends

endif

ifndef __IDispenserDriver_INTERFACE_DEFINED__
__IDispenserDriver_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDispenserDriver, "208b3651-2b48-11cf-be10-00aa00a2fa25")

.comdef IDispenserDriver : public IUnknown

    CreateResource	proc :RESTYPID, :ptr, :ptr
    RateResource	proc :RESTYPID, :RESID, :BOOL, :ptr
    EnlistResource	proc :RESID, :TRANSID
    ResetResource	proc :RESID
    DestroyResource	proc :RESID
    DestroyResourceS	proc :constSRESID
    .ends

endif

ifdef USE_UUIDOF_FOR_IID_
IID_IHolder		equ __uuidof(IIHolder)
IID_IDispenserManager	equ __uuidof(IDispenserManager)
IID_IDispenserDriver	equ __uuidof(IDispenserDriver)
endif

CRR_NO_REASON_SUPPLIED	equ 0x00000000
CRR_LIFETIME_LIMIT	equ 0xFFFFFFFF
CRR_ACTIVATION_LIMIT	equ 0xFFFFFFFE
CRR_CALL_LIMIT		equ 0xFFFFFFFD
CRR_MEMORY_LIMIT	equ 0xFFFFFFFC
CRR_RECYCLED_FROM_UI	equ 0xFFFFFFFB

externdef		CLSID_MTSPackage:CLSID
externdef		GUID_DefaultAppPartition:GUID
externdef		GUID_FinalizerCID:GUID
externdef		IID_IEnterActivityWithNoLock:GUID

ifndef __ITransactionProxy_INTERFACE_DEFINED__
__ITransactionProxy_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransactionProxy, "02558374-DF2E-4dae-BD6B-1D5C994F9BDC")

.comdef ITransactionProxy : public IUnknown

    Commit		proc :GUID
    Abort		proc
    Promote		proc :ptr
    CreateVoter		proc :ptr, :ptr
    GetIsolationLevel	proc :ptr
    GetIdentifier	proc :ptr
    IsReusable		proc :ptr
    .ends

endif

ifndef __IContextSecurityPerimeter_INTERFACE_DEFINED__
__IContextSecurityPerimeter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContextSecurityPerimeter, "A7549A29-A7C4-42e1-8DC1-7E3D748DC24A")

.comdef IContextSecurityPerimeter : public IUnknown

    GetPerimeterFlag	proc :ptr
    SetPerimeterFlag	proc :BOOL
    .ends

endif

ifndef __ITxProxyHolder_INTERFACE_DEFINED__
__ITxProxyHolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITxProxyHolder, "13D86F31-0139-41af-BCAD-C7D50435FE9F")

.comdef ITxProxyHolder : public IUnknown

    GetIdentifier	proc :ptr
    .ends

endif

ifndef __IObjectContext_INTERFACE_DEFINED__
__IObjectContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectContext, "51372ae0-cae7-11cf-be81-00aa00a2fa25")

.comdef IObjectContext : public IUnknown

    CreateInstance	proc :REFCLSID, :REFIID, :ptr
    SetComplete		proc
    SetAbort		proc
    EnableCommit	proc
    DisableCommit	proc
    IsInTransaction	proc
    IsSecurityEnabled	proc
    IsCallerInRole	proc :BSTR, :ptr
    .ends

endif

ifndef __IObjectControl_INTERFACE_DEFINED__
__IObjectControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectControl, "51372aec-cae7-11cf-be81-00aa00a2fa25")

.comdef IObjectControl : public IUnknown

    Activate		proc
    Deactivate		proc
    CanBePooled		proc
    .ends

endif

ifndef __IEnumNames_INTERFACE_DEFINED__
__IEnumNames_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumNames, "51372af2-cae7-11cf-be81-00aa00a2fa25")

.comdef IEnumNames : public IUnknown

    Next		proc :LONG, :ptr, :ptr
    Skip		proc :LONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __ISecurityProperty_INTERFACE_DEFINED__
__ISecurityProperty_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISecurityProperty, "51372aea-cae7-11cf-be81-00aa00a2fa25")

.comdef ISecurityProperty : public IUnknown

    GetDirectCreatorSID proc :ptr
    GetOriginalCreatorSID proc :ptr
    GetDirectCallerSID	proc :ptr
    GetOriginalCallerSID proc :ptr
    ReleaseSID		proc :PSID
    .ends

endif

ifndef __ObjectControl_INTERFACE_DEFINED__
__ObjectControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ObjectControl, "7DC41850-0C31-11d0-8B79-00AA00B8A790")

.comdef ObjectControl : public IUnknown

    Activate		proc
    Deactivate		proc
    CanBePooled		proc :ptr VARIANT_BOOL
    .ends

endif

ifndef __ISharedProperty_INTERFACE_DEFINED__
__ISharedProperty_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISharedProperty, "2A005C01-A5DE-11CF-9E66-00AA00A3F464")

.comdef ISharedProperty : public IDispatch

    get_Value		proc :ptr VARIANT
    put_Value		proc :VARIANT
    .ends

endif

ifndef __ISharedPropertyGroup_INTERFACE_DEFINED__
__ISharedPropertyGroup_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISharedPropertyGroup, "2A005C07-A5DE-11CF-9E66-00AA00A3F464")

.comdef ISharedPropertyGroup : public IDispatch

    CreatePropertyByPosition proc :SINT, :ptr VARIANT_BOOL, :ptr ptr ISharedProperty
    get_PropertyByPosition proc :SINT, :ptr ptr ISharedProperty
    CreateProperty	proc :BSTR, :ptr VARIANT_BOOL, :ptr ptr ISharedProperty
    get_Property	proc :BSTR, :ptr ptr ISharedProperty
    .ends

endif

ifndef __ISharedPropertyGroupManager_INTERFACE_DEFINED__
__ISharedPropertyGroupManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISharedPropertyGroupManager, "2A005C0D-A5DE-11CF-9E66-00AA00A3F464")

.comdef ISharedPropertyGroupManager : public IDispatch

    CreatePropertyGroup proc :BSTR, :ptr LONG, :ptr LONG, :ptr VARIANT_BOOL, :ptr ptr ISharedPropertyGroup
    get_Group		proc :BSTR, :ptr ptr ISharedPropertyGroup
    get__NewEnum	proc :ptr ptr IUnknown
    .ends

endif

ifndef __IObjectConstruct_INTERFACE_DEFINED__
__IObjectConstruct_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectConstruct, "41C4F8B3-7439-11D2-98CB-00C04F8EE1C4")

.comdef IObjectConstruct : public IUnknown

    Construct		proc :ptr
    .ends

endif

ifndef __IObjectConstructString_INTERFACE_DEFINED__
__IObjectConstructString_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectConstructString, "41C4F8B2-7439-11D2-98CB-00C04F8EE1C4")

.comdef IObjectConstructString : public IDispatch

    get_ConstructString proc :ptr BSTR
    .ends

endif

ifndef __IObjectContextActivity_INTERFACE_DEFINED__
__IObjectContextActivity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectContextActivity, "51372afc-cae7-11cf-be81-00aa00a2fa25")

.comdef IObjectContextActivity : public IUnknown

    GetActivityId	proc :ptr
    .ends

endif

ifndef __IObjectContextInfo_INTERFACE_DEFINED__
__IObjectContextInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectContextInfo, "75B52DDB-E8ED-11d1-93AD-00AA00BA3258")

.comdef IObjectContextInfo : public IUnknown

    IsInTransaction	proc
    GetTransaction	proc :ptr
    GetTransactionId	proc :ptr
    GetActivityId	proc :ptr
    GetContextId	proc :ptr
    .ends

endif

ifndef __IObjectContextInfo2_INTERFACE_DEFINED__
__IObjectContextInfo2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectContextInfo2, "594BE71A-4BC4-438b-9197-CFD176248B09")

.comdef IObjectContextInfo2 : public IObjectContextInfo

    GetPartitionId	proc :ptr GUID
    GetApplicationId	proc :ptr GUID
    GetApplicationInstanceId proc :ptr GUID
    .ends

endif

ifndef __ITransactionStatus_INTERFACE_DEFINED__
__ITransactionStatus_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransactionStatus, "61F589E8-3724-4898-A0A4-664AE9E1D1B4")

.comdef ITransactionStatus : public IUnknown

    SetTransactionStatus proc :HRESULT
    GetTransactionStatus proc :ptr
    .ends

endif

ifndef __IObjectContextTip_INTERFACE_DEFINED__
__IObjectContextTip_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectContextTip, "92FD41CA-BAD9-11d2-9A2D-00C04F797BC9")

.comdef IObjectContextTip : public IUnknown

    GetTipUrl		proc :ptr
    .ends

endif

ifndef __IPlaybackControl_INTERFACE_DEFINED__
__IPlaybackControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPlaybackControl, "51372afd-cae7-11cf-be81-00aa00a2fa25")

.comdef IPlaybackControl : public IUnknown

    FinalClientRetry	proc
    FinalServerRetry	proc
    .ends

endif

ifndef __IGetContextProperties_INTERFACE_DEFINED__
__IGetContextProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IGetContextProperties, "51372af4-cae7-11cf-be81-00aa00a2fa25")

.comdef IGetContextProperties : public IUnknown

    Count		proc :ptr
    GetProperty		proc :BSTR, :ptr
    EnumNames		proc :ptr
    .ends

endif

.enum TransactionVote {
    TxCommit	= 0,
    TxAbort	= ( TxCommit + 1 )
    }

ifndef __IContextState_INTERFACE_DEFINED__
__IContextState_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContextState, "3C05E54B-A42A-11d2-AFC4-00C04F8EE1C4")

.comdef IContextState : public IUnknown

    SetDeactivateOnReturn proc :VARIANT_BOOL
    GetDeactivateOnReturn proc :ptr
    SetMyTransactionVote proc :TransactionVote
    GetMyTransactionVote proc :ptr
    .ends

endif

ifndef __IPoolManager_INTERFACE_DEFINED__
__IPoolManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPoolManager, "0a469861-5a91-43a0-99b6-d5e179bb0631")

.comdef IPoolManager : public IDispatch

    ShutdownPool	proc :BSTR
    .ends

endif

ifndef __ISelectCOMLBServer_INTERFACE_DEFINED__
__ISelectCOMLBServer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISelectCOMLBServer, "dcf443f4-3f8a-4872-b9f0-369a796d12d6")

.comdef ISelectCOMLBServer : public IUnknown

    Init		proc
    GetLBServer		proc :ptr
    .ends

endif

ifndef __ICOMLBArguments_INTERFACE_DEFINED__
__ICOMLBArguments_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICOMLBArguments, "3a0f150f-8ee5-4b94-b40e-aef2f9e42ed2")

.comdef ICOMLBArguments : public IUnknown

    GetCLSID		proc :ptr
    SetCLSID		proc :ptr
    GetMachineName	proc :ULONG, :ptr WCHAR
    SetMachineName	proc :ULONG, :ptr WCHAR
    .ends

endif

if (_WIN32_WINNT GE 0x0500)
GetObjectContext macro ppIOC
	exitm<(CoGetObjectContext(addr IID_IObjectContext, ppIOC) EQ S_OK ? S_OK : CONTEXT_E_NOCONTEXT)>
	endm
else
GetObjectContext	proto __cdecl :ptr ptr IObjectContext
endif
CoCreateActivity	proto WINAPI :ptr IUnknown, :REFIID, :ptr ptr
CoEnterServiceDomain	proto WINAPI :ptr IUnknown
CoLeaveServiceDomain	proto WINAPI :ptr IUnknown
GetManagedExtensions	proto WINAPI :ptr DWORD
SafeRef			proto __cdecl :REFIID, :ptr IUnknown
RecycleSurrogate	proto __cdecl :LONG

ifndef __ICrmLogControl_INTERFACE_DEFINED__
__ICrmLogControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICrmLogControl, "A0E174B3-D26E-11d2-8F84-00805FC7BCD9")

.comdef ICrmLogControl : public IUnknown

    get_TransactionUOW	proc :ptr BSTR
    RegisterCompensator proc :LPCWSTR, :LPCWSTR, :LONG
    WriteLogRecordVariants proc :ptr VARIANT
    ForceLog		proc
    ForgetLogRecord	proc
    ForceTransactionToAbort proc
    WriteLogRecord	proc
    .ends

endif

ifndef __ICrmCompensatorVariants_INTERFACE_DEFINED__
__ICrmCompensatorVariants_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICrmCompensatorVariants, "F0BAF8E4-7804-11d1-82E9-00A0C91EEDE9")

.comdef ICrmCompensatorVariants : public IUnknown

    SetLogControlVariants proc :ptr ICrmLogControl
    BeginPrepareVariants proc
    PrepareRecordVariants proc :ptr VARIANT, :ptr VARIANT_BOOL
    EndPrepareVariants	proc :ptr VARIANT_BOOL
    BeginCommitVariants proc :VARIANT_BOOL
    CommitRecordVariants proc :ptr VARIANT, :ptr VARIANT_BOOL
    EndCommitVariants	proc
    BeginAbortVariants	proc :VARIANT_BOOL
    AbortRecordVariants proc :ptr VARIANT, :ptr VARIANT_BOOL
    EndAbortVariants	proc
    .ends

endif

ifndef _tagCrmLogRecordRead_
_tagCrmLogRecordRead_ equ 1
CrmLogRecordRead	STRUC
dwCrmFlags		dd ?
dwSequenceNumber	dd ?
blobUserData		BLOB <>
CrmLogRecordRead	ENDS

endif

ifndef __ICrmCompensator_INTERFACE_DEFINED__
__ICrmCompensator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICrmCompensator, "BBC01830-8D3B-11d1-82EC-00A0C91EEDE9")

.comdef ICrmCompensator : public IUnknown

    SetLogControl	proc :ptr
    BeginPrepare	proc
    PrepareRecord	proc :CrmLogRecordRead, :ptr
    EndPrepare		proc :ptr
    BeginCommit		proc :BOOL
    CommitRecord	proc :CrmLogRecordRead, :ptr
    EndCommit		proc
    BeginAbort		proc :BOOL
    AbortRecord		proc :CrmLogRecordRead, :ptr
    EndAbort		proc
    .ends

endif

ifndef _tagCrmTransactionState_
_tagCrmTransactionState_ equ 1
.enum CrmTransactionState {
    TxState_Active	= 0,
    TxState_Committed	= ( TxState_Active + 1 ) ,
    TxState_Aborted	= ( TxState_Committed + 1 ) ,
    TxState_Indoubt	= ( TxState_Aborted + 1 )
    }

endif

ifndef __ICrmMonitorLogRecords_INTERFACE_DEFINED__
__ICrmMonitorLogRecords_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICrmMonitorLogRecords, "70C8E441-C7ED-11d1-82FB-00A0C91EEDE9")

.comdef ICrmMonitorLogRecords : public IUnknown

    get_Count		proc :ptr LONG
    get_TransactionState proc :ptr CrmTransactionState
    get_StructuredRecords proc :ptr VARIANT_BOOL
    GetLogRecord	proc :DWORD, :ptr CrmLogRecordRead
    GetLogRecordVariants proc :VARIANT, :LPVARIANT
    .ends

endif

ifndef __ICrmMonitorClerks_INTERFACE_DEFINED__
__ICrmMonitorClerks_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICrmMonitorClerks, "70C8E442-C7ED-11d1-82FB-00A0C91EEDE9")

.comdef ICrmMonitorClerks : public IDispatch

    Item		proc :VARIANT, :LPVARIANT
    get__NewEnum	proc :ptr LPUNKNOWN
    get_Count		proc :ptr LONG
    ProgIdCompensator	proc :VARIANT, :LPVARIANT
    Description		proc :VARIANT, :LPVARIANT
    TransactionUOW	proc :VARIANT, :LPVARIANT
    ActivityId		proc :VARIANT, :LPVARIANT
    .ends

endif

ifndef __ICrmMonitor_INTERFACE_DEFINED__
__ICrmMonitor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICrmMonitor, "70C8E443-C7ED-11d1-82FB-00A0C91EEDE9")

.comdef ICrmMonitor : public IUnknown

    GetClerks		proc :ptr ptr ICrmMonitorClerks
    HoldClerk		proc :VARIANT, :LPVARIANT
    .ends

endif

ifndef __ICrmFormatLogRecords_INTERFACE_DEFINED__
__ICrmFormatLogRecords_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICrmFormatLogRecords, "9C51D821-C98B-11d1-82FB-00A0C91EEDE9")

.comdef ICrmFormatLogRecords : public IUnknown

    GetColumnCount	proc :ptr LONG
    GetColumnHeaders	proc :VARIANT
    GetColumn		proc :CrmLogRecordRead, :LPVARIANT
    GetColumnVariants	proc :VARIANT, :LPVARIANT
    .ends

endif

.enum CSC_InheritanceConfig {
    CSC_Inherit = 0,
    CSC_Ignore	= ( CSC_Inherit + 1 )
    }

.enum CSC_ThreadPool {
    CSC_ThreadPoolNone	= 0,
    CSC_ThreadPoolInherit = ( CSC_ThreadPoolNone + 1 ) ,
    CSC_STAThreadPool	= ( CSC_ThreadPoolInherit + 1 ) ,
    CSC_MTAThreadPool	= ( CSC_STAThreadPool + 1 )
    }

.enum CSC_Binding {
    CSC_NoBinding	= 0,
    CSC_BindToPoolThread = ( CSC_NoBinding + 1 )
    }

.enum CSC_TransactionConfig {
    CSC_NoTransaction	= 0,
    CSC_IfContainerIsTransactional	= ( CSC_NoTransaction + 1 ) ,
    CSC_CreateTransactionIfNecessary	= ( CSC_IfContainerIsTransactional + 1 ) ,
    CSC_NewTransaction	= ( CSC_CreateTransactionIfNecessary + 1 )
    }

.enum CSC_SynchronizationConfig {
    CSC_NoSynchronization	= 0,
    CSC_IfContainerIsSynchronized	= ( CSC_NoSynchronization + 1 ) ,
    CSC_NewSynchronizationIfNecessary	= ( CSC_IfContainerIsSynchronized + 1 ) ,
    CSC_NewSynchronization	= ( CSC_NewSynchronizationIfNecessary + 1 )
    }

.enum CSC_TrackerConfig {
    CSC_DontUseTracker	= 0,
    CSC_UseTracker	= ( CSC_DontUseTracker + 1 )
    }

.enum CSC_PartitionConfig {
    CSC_NoPartition	= 0,
    CSC_InheritPartition	= ( CSC_NoPartition + 1 ) ,
    CSC_NewPartition	= ( CSC_InheritPartition + 1 )
    }

.enum CSC_IISIntrinsicsConfig {
    CSC_NoIISIntrinsics = 0,
    CSC_InheritIISIntrinsics	= ( CSC_NoIISIntrinsics + 1 )
    }

.enum CSC_COMTIIntrinsicsConfig {
    CSC_NoCOMTIIntrinsics	= 0,
    CSC_InheritCOMTIIntrinsics	= ( CSC_NoCOMTIIntrinsics + 1 )
    }

.enum CSC_SxsConfig {
    CSC_NoSxs	= 0,
    CSC_InheritSxs	= ( CSC_NoSxs + 1 ) ,
    CSC_NewSxs	= ( CSC_InheritSxs + 1 )
    }

ifndef __IServiceIISIntrinsicsConfig_INTERFACE_DEFINED__
__IServiceIISIntrinsicsConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceIISIntrinsicsConfig, "1a0cf920-d452-46f4-bc36-48118d54ea52")

.comdef IServiceIISIntrinsicsConfig : public IUnknown

    IISIntrinsicsConfig proc :CSC_IISIntrinsicsConfig
    .ends

endif

ifndef __IServiceComTIIntrinsicsConfig_INTERFACE_DEFINED__
__IServiceComTIIntrinsicsConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceComTIIntrinsicsConfig, "09e6831e-04e1-4ed4-9d0f-e8b168bafeaf")

.comdef IServiceComTIIntrinsicsConfig : public IUnknown

    ComTIIntrinsicsConfig proc :CSC_COMTIIntrinsicsConfig
    .ends

endif

ifndef __IServiceSxsConfig_INTERFACE_DEFINED__
__IServiceSxsConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceSxsConfig, "c7cd7379-f3f2-4634-811b-703281d73e08")

.comdef IServiceSxsConfig : public IUnknown

    SxsConfig		proc :CSC_SxsConfig
    SxsName		proc :LPCWSTR
    SxsDirectory	proc :LPCWSTR
    .ends

endif

ifndef __ICheckSxsConfig_INTERFACE_DEFINED__
__ICheckSxsConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICheckSxsConfig, "0FF5A96F-11FC-47d1-BAA6-25DD347E7242")

.comdef ICheckSxsConfig : public IUnknown

    IsSameSxsConfig	proc :LPCWSTR, :LPCWSTR, :LPCWSTR
    .ends

endif

ifndef __IServiceInheritanceConfig_INTERFACE_DEFINED__
__IServiceInheritanceConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceInheritanceConfig, "92186771-d3b4-4d77-a8ea-ee842d586f35")

.comdef IServiceInheritanceConfig : public IUnknown

    ContainingContextTreatment proc :CSC_InheritanceConfig
    .ends

endif

ifndef __IServiceThreadPoolConfig_INTERFACE_DEFINED__
__IServiceThreadPoolConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceThreadPoolConfig, "186d89bc-f277-4bcc-80d5-4df7b836ef4a")

.comdef IServiceThreadPoolConfig : public IUnknown

    SelectThreadPool	proc :CSC_ThreadPool
    SetBindingInfo	proc :CSC_Binding
    .ends

endif

ifndef __IServiceTransactionConfigBase_INTERFACE_DEFINED__
__IServiceTransactionConfigBase_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceTransactionConfigBase, "772b3fbe-6ffd-42fb-b5f8-8f9b260f3810")

.comdef IServiceTransactionConfigBase : public IUnknown

    ConfigureTransaction proc :CSC_TransactionConfig
    IsolationLevel	proc :COMAdminTxIsolationLevelOptions
    TransactionTimeout	proc :ULONG
    BringYourOwnTransaction proc :LPCWSTR
    NewTransactionDescription proc :LPCWSTR
    .ends

endif

ifndef __IServiceTransactionConfig_INTERFACE_DEFINED__
__IServiceTransactionConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceTransactionConfig, "59f4c2a3-d3d7-4a31-b6e4-6ab3177c50b9")

.comdef IServiceTransactionConfig : public IServiceTransactionConfigBase

    ConfigureBYOT	proc :ptr
    .ends

endif

ifndef __IServiceSysTxnConfig_INTERFACE_DEFINED__
__IServiceSysTxnConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceSysTxnConfig, "33CAF1A1-FCB8-472b-B45E-967448DED6D8")

.comdef IServiceSysTxnConfig : public IServiceTransactionConfig

    ConfigureBYOTSysTxn proc :ptr
    .ends

endif

ifndef __IServiceSynchronizationConfig_INTERFACE_DEFINED__
__IServiceSynchronizationConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceSynchronizationConfig, "fd880e81-6dce-4c58-af83-a208846c0030")

.comdef IServiceSynchronizationConfig : public IUnknown

    ConfigureSynchronization proc :CSC_SynchronizationConfig
    .ends

endif

ifndef __IServiceTrackerConfig_INTERFACE_DEFINED__
__IServiceTrackerConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceTrackerConfig, "6c3a3e1d-0ba6-4036-b76f-d0404db816c9")

.comdef IServiceTrackerConfig : public IUnknown

    TrackerConfig	proc :CSC_TrackerConfig, :LPCWSTR, :LPCWSTR
    .ends

endif

ifndef __IServicePartitionConfig_INTERFACE_DEFINED__
__IServicePartitionConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServicePartitionConfig, "80182d03-5ea4-4831-ae97-55beffc2e590")

.comdef IServicePartitionConfig : public IUnknown

    PartitionConfig	proc :CSC_PartitionConfig
    PartitionID		proc :REFGUID
    .ends

endif

ifndef __IServiceCall_INTERFACE_DEFINED__
__IServiceCall_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceCall, "BD3E2E12-42DD-40f4-A09A-95A50C58304B")

.comdef IServiceCall : public IUnknown

    OnCall		proc
    .ends

endif

ifndef __IAsyncErrorNotify_INTERFACE_DEFINED__
__IAsyncErrorNotify_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAsyncErrorNotify, "FE6777FB-A674-4177-8F32-6D707E113484")

.comdef IAsyncErrorNotify : public IUnknown

    OnError		proc :HRESULT
    .ends

endif

ifndef __IServiceActivity_INTERFACE_DEFINED__
__IServiceActivity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServiceActivity, "67532E0C-9E2F-4450-A354-035633944E17")

.comdef IServiceActivity : public IUnknown

    SynchronousCall	proc :ptr
    AsynchronousCall	proc :ptr
    BindToCurrentThread proc
    UnbindFromThread	proc
    .ends

endif

ifndef __IThreadPoolKnobs_INTERFACE_DEFINED__
__IThreadPoolKnobs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IThreadPoolKnobs, "51372af7-cae7-11cf-be81-00aa00a2fa25")

.comdef IThreadPoolKnobs : public IUnknown

    GetMaxThreads	proc :ptr
    GetCurrentThreads	proc :ptr
    SetMaxThreads	proc :LONG
    GetDeleteDelay	proc :ptr
    SetDeleteDelay	proc :LONG
    GetMaxQueuedRequests proc :ptr
    GetCurrentQueuedRequests proc :ptr
    SetMaxQueuedRequests proc :LONG
    SetMinThreads	proc :LONG
    SetQueueDepth	proc :LONG
    .ends

endif

ifndef __IComStaThreadPoolKnobs_INTERFACE_DEFINED__
__IComStaThreadPoolKnobs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComStaThreadPoolKnobs, "324B64FA-33B6-11d2-98B7-00C04F8EE1C4")

.comdef IComStaThreadPoolKnobs : public IUnknown

    SetMinThreadCount	proc :DWORD
    GetMinThreadCount	proc :ptr
    SetMaxThreadCount	proc :DWORD
    GetMaxThreadCount	proc :ptr
    SetActivityPerThread proc :DWORD
    GetActivityPerThread proc :ptr
    SetActivityRatio	proc :DOUBLE
    GetActivityRatio	proc :ptr
    GetThreadCount	proc :ptr
    GetQueueDepth	proc :ptr
    SetQueueDepth	proc :LONG
    .ends

endif

ifndef __IComMtaThreadPoolKnobs_INTERFACE_DEFINED__
__IComMtaThreadPoolKnobs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComMtaThreadPoolKnobs, "F9A76D2E-76A5-43eb-A0C4-49BEC8E48480")

.comdef IComMtaThreadPoolKnobs : public IUnknown

    MTASetMaxThreadCount proc :DWORD
    MTAGetMaxThreadCount proc :ptr
    MTASetThrottleValue proc :DWORD
    MTAGetThrottleValue proc :ptr
    .ends

endif

ifndef __IComStaThreadPoolKnobs2_INTERFACE_DEFINED__
__IComStaThreadPoolKnobs2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComStaThreadPoolKnobs2, "73707523-FF9A-4974-BF84-2108DC213740")

.comdef IComStaThreadPoolKnobs2 : public IComStaThreadPoolKnobs

    GetMaxCPULoad	proc :ptr
    SetMaxCPULoad	proc :LONG
    GetCPUMetricEnabled proc :ptr
    SetCPUMetricEnabled proc :BOOL
    GetCreateThreadsAggressively proc :ptr
    SetCreateThreadsAggressively proc :BOOL
    GetMaxCSR		proc :ptr
    SetMaxCSR		proc :LONG
    GetWaitTimeForThreadCleanup proc :ptr
    SetWaitTimeForThreadCleanup proc :LONG
    .ends

endif

ifndef __IProcessInitializer_INTERFACE_DEFINED__
__IProcessInitializer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IProcessInitializer, "1113f52d-dc7f-4943-aed6-88d04027e32a")

.comdef IProcessInitializer : public IUnknown

    Startup		proc :ptr
    Shutdown		proc
    .ends

endif

ifndef __IServicePoolConfig_INTERFACE_DEFINED__
__IServicePoolConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServicePoolConfig, "a9690656-5bca-470c-8451-250c1f43a33e")

.comdef IServicePoolConfig : public IUnknown

    put_MaxPoolSize	proc :DWORD
    get_MaxPoolSize	proc :ptr DWORD
    put_MinPoolSize	proc :DWORD
    get_MinPoolSize	proc :ptr DWORD
    put_CreationTimeout proc :DWORD
    get_CreationTimeout proc :ptr DWORD
    put_TransactionAffinity proc :BOOL
    get_TransactionAffinity proc :ptr BOOL
    put_ClassFactory	proc :ptr IClassFactory
    get_ClassFactory	proc :ptr ptr IClassFactory
    .ends

endif

ifndef __IServicePool_INTERFACE_DEFINED__
__IServicePool_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServicePool, "b302df81-ea45-451e-99a2-09f9fd1b1e13")

.comdef IServicePool : public IUnknown

    Initialize		proc :ptr
    GetObject		proc :REFIID, :ptr
    Shutdown		proc
    .ends

endif

ifndef __IManagedPooledObj_INTERFACE_DEFINED__
__IManagedPooledObj_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IManagedPooledObj, "c5da4bea-1b42-4437-8926-b6a38860a770")

.comdef IManagedPooledObj : public IUnknown

    SetHeld		proc :BOOL
    .ends

endif

ifndef __IManagedPoolAction_INTERFACE_DEFINED__
__IManagedPoolAction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IManagedPoolAction, "da91b74e-5388-4783-949d-c1cd5fb00506")

.comdef IManagedPoolAction : public IUnknown

    LastRelease		proc
    .ends

endif

ifndef __IManagedObjectInfo_INTERFACE_DEFINED__
__IManagedObjectInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IManagedObjectInfo, "1427c51a-4584-49d8-90a0-c50d8086cbe9")

.comdef IManagedObjectInfo : public IUnknown

    GetIUnknown		proc :ptr
    GetIObjectControl	proc :ptr
    SetInPool		proc :BOOL, :ptr
    SetWrapperStrength	proc :BOOL
    .ends

endif

ifndef __IAppDomainHelper_INTERFACE_DEFINED__
__IAppDomainHelper_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAppDomainHelper, "c7b67079-8255-42c6-9ec0-6994a3548780")

.comdef IAppDomainHelper : public IDispatch

    Initialize		proc :ptr
    DoCallback		proc :ptr
    .ends

endif

ifndef __IAssemblyLocator_INTERFACE_DEFINED__
__IAssemblyLocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAssemblyLocator, "391ffbb9-a8ee-432a-abc8-baa238dab90f")

.comdef IAssemblyLocator : public IDispatch

    GetModules		proc :BSTR, :BSTR, :BSTR, :ptr
    .ends

endif

ifndef __IManagedActivationEvents_INTERFACE_DEFINED__
__IManagedActivationEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IManagedActivationEvents, "a5f325af-572f-46da-b8ab-827c3d95d99e")

.comdef IManagedActivationEvents : public IUnknown

    CreateManagedStub	proc :ptr, :BOOL
    DestroyManagedStub	proc :ptr
    .ends

endif

ifndef __ISendMethodEvents_INTERFACE_DEFINED__
__ISendMethodEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISendMethodEvents, "2732fd59-b2b4-4d44-878c-8b8f09626008")

.comdef ISendMethodEvents : public IUnknown

    SendMethodCall	proc :ptr, :REFIID, :DWORD
    SendMethodReturn	proc :ptr, :REFIID, :DWORD, :HRESULT, :HRESULT
    .ends

endif

ifndef __ITransactionResourcePool_INTERFACE_DEFINED__
__ITransactionResourcePool_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransactionResourcePool, "C5FEB7C1-346A-11D1-B1CC-00AA00BA3258")

.comdef ITransactionResourcePool : public IUnknown

    PutResource		proc :ptr, :ptr
    GetResource		proc :ptr, :ptr
    .ends

endif

MTSCreateActivity	proto WINAPI :REFIID, :ptr ptr

ifndef __IMTSCall_INTERFACE_DEFINED__
__IMTSCall_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMTSCall, "51372AEF-CAE7-11CF-BE81-00AA00A2FA25")

.comdef IMTSCall : public IUnknown

    OnCall		proc
    .ends

endif

ifndef __IContextProperties_INTERFACE_DEFINED__
__IContextProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContextProperties, "D396DA85-BF8F-11d1-BBAE-00C04FC2FA5F")

.comdef IContextProperties : public IUnknown

    Count		proc :ptr
    GetProperty		proc :BSTR, :ptr
    EnumNames		proc :ptr
    SetProperty		proc :BSTR, :VARIANT
    RemoveProperty	proc :BSTR
    .ends

endif

ifndef __IObjPool_INTERFACE_DEFINED__
__IObjPool_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjPool, "7D8805A0-2EA7-11D1-B1CC-00AA00BA3258")

.comdef IObjPool : public IUnknown

    Reserved1		proc
    Reserved2		proc
    Reserved3		proc
    Reserved4		proc
    PutEndTx		proc :ptr
    Reserved5		proc
    Reserved6		proc
    .ends

endif

ifndef __ITransactionProperty_INTERFACE_DEFINED__
__ITransactionProperty_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransactionProperty, "788ea814-87b1-11d1-bba6-00c04fc2fa5f")

.comdef ITransactionProperty : public IUnknown

    Reserved1		proc
    Reserved2		proc
    Reserved3		proc
    Reserved4		proc
    Reserved5		proc
    Reserved6		proc
    Reserved7		proc
    Reserved8		proc
    Reserved9		proc
    GetTransactionResourcePool proc :ptr
    Reserved10		proc
    Reserved11		proc
    Reserved12		proc
    Reserved13		proc
    Reserved14		proc
    Reserved15		proc
    Reserved16		proc
    Reserved17		proc
    .ends

endif

ifndef __IMTSActivity_INTERFACE_DEFINED__
__IMTSActivity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMTSActivity, "51372AF0-CAE7-11CF-BE81-00AA00A2FA25")

.comdef IMTSActivity : public IUnknown

    SynchronousCall	proc :ptr
    AsyncCall		proc :ptr
    Reserved1		proc
    BindToCurrentThread proc
    UnbindFromThread	proc
    .ends

endif

ifndef __COMSVCSLib_LIBRARY_DEFINED__
__COMSVCSLib_LIBRARY_DEFINED__ equ 1

.enum Error_Constants {
    mtsErrCtxAborted	= 0x8004e002,
    mtsErrCtxAborting	= 0x8004e003,
    mtsErrCtxNoContext	= 0x8004e004,
    mtsErrCtxNotRegistered	= 0x8004e005,
    mtsErrCtxSynchTimeout	= 0x8004e006,
    mtsErrCtxOldReference	= 0x8004e007,
    mtsErrCtxRoleNotFound	= 0x8004e00c,
    mtsErrCtxNoSecurity = 0x8004e00d,
    mtsErrCtxWrongThread	= 0x8004e00e,
    mtsErrCtxTMNotAvailable	= 0x8004e00f,
    comQCErrApplicationNotQueued	= 0x80110600,
    comQCErrNoQueueableInterfaces	= 0x80110601,
    comQCErrQueuingServiceNotAvailable	= 0x80110602,
    comQCErrQueueTransactMismatch	= 0x80110603,
    comqcErrRecorderMarshalled	= 0x80110604,
    comqcErrOutParam	= 0x80110605,
    comqcErrRecorderNotTrusted	= 0x80110606,
    comqcErrPSLoad	= 0x80110607,
    comqcErrMarshaledObjSameTxn = 0x80110608,
    comqcErrInvalidMessage	= 0x80110650,
    comqcErrMsmqSidUnavailable	= 0x80110651,
    comqcErrWrongMsgExtension	= 0x80110652,
    comqcErrMsmqServiceUnavailable	= 0x80110653,
    comqcErrMsgNotAuthenticated = 0x80110654,
    comqcErrMsmqConnectorUsed	= 0x80110655,
    comqcErrBadMarshaledObject	= 0x80110656
    }

.enum LockModes {
    LockSetGet	= 0,
    LockMethod	= ( LockSetGet + 1 )
    }

.enum ReleaseModes {
    Standard	= 0,
    Process	= ( Standard + 1 )
    }

ifndef _tagCrmFlags_
_tagCrmFlags_ equ 1
.enum CRMFLAGS {
    CRMFLAG_FORGETTARGET	= 0x1,
    CRMFLAG_WRITTENDURINGPREPARE	= 0x2,
    CRMFLAG_WRITTENDURINGCOMMIT = 0x4,
    CRMFLAG_WRITTENDURINGABORT	= 0x8,
    CRMFLAG_WRITTENDURINGRECOVERY	= 0x10,
    CRMFLAG_WRITTENDURINGREPLAY = 0x20,
    CRMFLAG_REPLAYINPROGRESS	= 0x40
    }

endif
ifndef _tagCrmRegFlags_
_tagCrmRegFlags_ equ 1
.enum CRMREGFLAGS {
    CRMREGFLAG_PREPAREPHASE	= 0x1,
    CRMREGFLAG_COMMITPHASE	= 0x2,
    CRMREGFLAG_ABORTPHASE	= 0x4,
    CRMREGFLAG_ALLPHASES	= 0x7,
    CRMREGFLAG_FAILIFINDOUBTSREMAIN	= 0x10
    }

endif

externdef		LIBID_COMSVCSLib:IID

DEFINE_GUIDS(CLSID_SecurityIdentity, "ecabb0a5-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_SecurityCallers, "ecabb0a6-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_SecurityCallContext, "ecabb0a7-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_GetSecurityCallContextAppObject, "ecabb0a8-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_Dummy30040732, "ecabb0a9-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_TransactionContext, "7999FC25-D3C6-11CF-ACAB-00A024A55AEF")
DEFINE_GUIDS(CLSID_TransactionContextEx, "5cb66670-d3d4-11cf-acab-00a024a55aef")
DEFINE_GUIDS(CLSID_ByotServerEx, "ecabb0aa-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_CServiceConfig, "ecabb0c8-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_ServicePool, "ecabb0c9-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_ServicePoolConfig, "ecabb0ca-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_SharedProperty, "2A005C05-A5DE-11CF-9E66-00AA00A3F464")
DEFINE_GUIDS(CLSID_SharedPropertyGroup, "2A005C0B-A5DE-11CF-9E66-00AA00A3F464")
DEFINE_GUIDS(CLSID_SharedPropertyGroupManager, "2A005C11-A5DE-11CF-9E66-00AA00A3F464")
DEFINE_GUIDS(CLSID_COMEvents, "ecabb0ab-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_CoMTSLocator, "ecabb0ac-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_MtsGrp, "4B2E958D-0393-11D1-B1AB-00AA00BA3258")
DEFINE_GUIDS(CLSID_ComServiceEvents, "ecabb0c3-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_ComSystemAppEventData, "ecabb0c6-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_CRMClerk, "ecabb0bd-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_CRMRecoveryClerk, "ecabb0be-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_LBEvents, "ecabb0c1-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_MessageMover, "ecabb0bf-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_DispenserManager, "ecabb0c0-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_PoolMgr, "ecabafb5-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_EventServer, "ecabafbc-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_TrackerServer, "ecabafb9-7f19-11d2-978e-0000f8757e2a")
DEFINE_GUIDS(CLSID_AppDomainHelper, "ef24f689-14f8-4d92-b4af-d7b1f0e70fd4")
DEFINE_GUIDS(CLSID_ClrAssemblyLocator, "458aa3b5-265a-4b75-bc05-9bea4630cf18")

endif
endif

BSTR_UserSize			proto WINAPI :ptr DWORD, :DWORD, :ptr BSTR
BSTR_UserMarshal		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr BSTR
BSTR_UserUnmarshal		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr BSTR
BSTR_UserFree			proto WINAPI :ptr DWORD, :ptr BSTR
LPSAFEARRAY_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr LPSAFEARRAY
LPSAFEARRAY_UserMarshal		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr LPSAFEARRAY
LPSAFEARRAY_UserUnmarshal	proto WINAPI :ptr DWORD, :ptr sbyte, :ptr LPSAFEARRAY
LPSAFEARRAY_UserFree		proto WINAPI :ptr DWORD, :ptr LPSAFEARRAY
VARIANT_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr VARIANT
VARIANT_UserMarshal		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr VARIANT
VARIANT_UserUnmarshal		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr VARIANT
VARIANT_UserFree		proto WINAPI :ptr DWORD, :ptr VARIANT
BSTR_UserSize64			proto WINAPI :ptr DWORD, :DWORD, :ptr BSTR
BSTR_UserMarshal64		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr BSTR
BSTR_UserUnmarshal64		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr BSTR
BSTR_UserFree64			proto WINAPI :ptr DWORD, :ptr BSTR
LPSAFEARRAY_UserSize64		proto WINAPI :ptr DWORD, :DWORD, :ptr LPSAFEARRAY
LPSAFEARRAY_UserMarshal64	proto WINAPI :ptr DWORD, :ptr sbyte, :ptr LPSAFEARRAY
LPSAFEARRAY_UserUnmarshal64	proto WINAPI :ptr DWORD, :ptr sbyte, :ptr LPSAFEARRAY
LPSAFEARRAY_UserFree64		proto WINAPI :ptr DWORD, :ptr LPSAFEARRAY
VARIANT_UserSize64		proto WINAPI :ptr DWORD, :DWORD, :ptr VARIANT
VARIANT_UserMarshal64		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr VARIANT
VARIANT_UserUnmarshal64		proto WINAPI :ptr DWORD, :ptr sbyte, :ptr VARIANT
VARIANT_UserFree64		proto WINAPI :ptr DWORD, :ptr VARIANT

endif
