ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Ehosting2Ereferencetracker_h__
define __windows2Eui2Examl2Ehosting2Ereferencetracker_h__

ifndef __oaidl_h__
include oaidl.inc
endif

if (NTDDI_VERSION ge NTDDI_WIN8)

ifndef __IReferenceTrackerTarget_INTERFACE_DEFINED__
define __IReferenceTrackerTarget_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceTrackerTarget, "64bd43f8-bfee-4ec4-b7eb-2935158dae21")

.comdef IReferenceTrackerTarget : public IUnknown
    AddRefFromReferenceTracker proc
    ReleaseFromReferenceTracker proc
    Peg			proc
    Unpeg		proc
   .ends

endif

ifndef __IReferenceTracker_INTERFACE_DEFINED__
define __IReferenceTracker_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceTracker, "11d3b13a-180e-4789-a8be-7712882893e6")

.comdef IReferenceTracker : public IUnknown
    ConnectFromTrackerSource proc
    DisconnectFromTrackerSource proc
    FindTrackerTargets	proc :ptr
    GetReferenceTrackerManager proc :ptr
    AddRefFromTrackerSource proc
    ReleaseFromTrackerSource proc
    PegFromTrackerSource proc
   .ends

endif

ifndef __IReferenceTrackerManager_INTERFACE_DEFINED__
define __IReferenceTrackerManager_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceTrackerManager, "3cf184b4-7ccb-4dda-8455-7e6ce99a3298")

.comdef IReferenceTrackerManager : public IUnknown
    ReferenceTrackingStarted proc
    FindTrackerTargetsCompleted proc :boolean
    ReferenceTrackingCompleted proc
    SetReferenceTrackerHost proc :ptr
   .ends

endif

ifndef __IFindReferenceTargetsCallback_INTERFACE_DEFINED__
define __IFindReferenceTargetsCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IFindReferenceTargetsCallback, "04b3486c-4687-4229-8d14-505ab584dd88")

.comdef IFindReferenceTargetsCallback : public IUnknown
    FoundTrackerTarget	proc :ptr
   .ends

endif

.enum XAML_REFERENCETRACKER_DISCONNECT {
	XAML_REFERENCETRACKER_DISCONNECT_DEFAULT	= 0,
	XAML_REFERENCETRACKER_DISCONNECT_SUSPEND	= 1
    }

ifndef __IReferenceTrackerHost_INTERFACE_DEFINED__
define __IReferenceTrackerHost_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceTrackerHost, "29a71c6a-3c42-4416-a39d-e2825a07a773")

.comdef IReferenceTrackerHost : public IUnknown
    DisconnectUnusedReferenceSources proc :XAML_REFERENCETRACKER_DISCONNECT
    ReleaseDisconnectedReferenceSources proc
    NotifyEndOfReferenceTrackingOnThread proc
    GetTrackerTarget	proc :ptr, :ptr
    AddMemoryPressure	proc :UINT64
    RemoveMemoryPressure proc :UINT64
   .ends

endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS2)

ifndef __IReferenceTrackerExtension_INTERFACE_DEFINED__
define __IReferenceTrackerExtension_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceTrackerExtension, "4e897caa-59d5-4613-8f8c-f7ebd1f399b0")

.comdef IReferenceTrackerExtension : public IUnknown
   .ends

endif

TrackerHandle__		struct
unused			sdword ?
TrackerHandle__		ends

TrackerHandle		typedef ptr TrackerHandle__

ifndef __ITrackerOwner_INTERFACE_DEFINED__
define __ITrackerOwner_INTERFACE_DEFINED__

DEFINE_IIDX(ITrackerOwner, "eb24c20b-9816-4ac7-8cff-36f67a118f4e")

.comdef ITrackerOwner : public IUnknown
    CreateTrackerHandle proc :ptr
    DeleteTrackerHandle proc :TrackerHandle
    SetTrackerValue	proc :TrackerHandle, :ptr
    TryGetSafeTrackerValue proc :TrackerHandle, :ptr
   .ends

endif

endif
endif

endif
