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

ifndef __txdtc_h__
define __txdtc_h__

include txcoord.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
XACTTOMSG macro dwXact
	exitm<(dwXact-0x00040000+0x40000000)>
	endm
.enum XACT_DTC_CONSTANTS {
    XACT_E_CONNECTION_REQUEST_DENIED	= 0x8004d100,
    XACT_E_TOOMANY_ENLISTMENTS		= 0x8004d101,
    XACT_E_DUPLICATE_GUID		= 0x8004d102,
    XACT_E_NOTSINGLEPHASE		= 0x8004d103,
    XACT_E_RECOVERYALREADYDONE		= 0x8004d104,
    XACT_E_PROTOCOL			= 0x8004d105,
    XACT_E_RM_FAILURE			= 0x8004d106,
    XACT_E_RECOVERY_FAILED		= 0x8004d107,
    XACT_E_LU_NOT_FOUND			= 0x8004d108,
    XACT_E_DUPLICATE_LU			= 0x8004d109,
    XACT_E_LU_NOT_CONNECTED		= 0x8004d10a,
    XACT_E_DUPLICATE_TRANSID		= 0x8004d10b,
    XACT_E_LU_BUSY			= 0x8004d10c,
    XACT_E_LU_NO_RECOVERY_PROCESS	= 0x8004d10d,
    XACT_E_LU_DOWN			= 0x8004d10e,
    XACT_E_LU_RECOVERING		= 0x8004d10f,
    XACT_E_LU_RECOVERY_MISMATCH		= 0x8004d110,
    XACT_E_RM_UNAVAILABLE		= 0x8004d111,
    XACT_E_LRMRECOVERYALREADYDONE	= 0x8004d112,
    XACT_E_NOLASTRESOURCEINTERFACE	= 0x8004d113,
    XACT_S_NONOTIFY			= 0x4d100,
    XACT_OK_NONOTIFY			= 0x4d101,
    dwUSER_MS_SQLSERVER			= 0xffff
    }

ifndef _XID_T_DEFINED
define _XID_T_DEFINED
XID			STRUC
formatID		LONG ?
gtrid_length		LONG ?
bqual_length		LONG ?
data			sbyte 128 dup(?)
XID			ENDS
endif

ifndef _XA_SWITCH_T_DEFINED
_XA_SWITCH_T_DEFINED equ 1
xa_switch_t		STRUC
name			sbyte 32 dup(?)
flags			LONG ?
version			LONG ?
xa_open_entry		proc :LPSTR, :SINT, :LONG
xa_close_entry		proc :LPSTR, :SINT, :LONG
xa_start_entry		proc :ptr XID, :SINT, :LONG
xa_end_entry		proc :ptr XID, :SINT, :LONG
xa_rollback_entry	proc :ptr XID, :SINT, :LONG
xa_prepare_entry	proc :ptr XID, :SINT, :LONG
xa_commit_entry		proc :ptr XID, :SINT, :LONG
xa_recover_entry	proc :ptr XID, :LONG, :SINT, :LONG
xa_forget_entry		proc :ptr XID, :SINT, :LONG
xa_complete_entry	proc :ptr SINT, :ptr SINT, :SINT, :LONG
xa_switch_t		ENDS
endif

ifndef __IXATransLookup_INTERFACE_DEFINED__
define __IXATransLookup_INTERFACE_DEFINED__

.comdef IXATransLookup : public IUnknown

    Lookup		proc :ptr
   .ends

endif

ifndef __IXATransLookup2_INTERFACE_DEFINED__
define __IXATransLookup2_INTERFACE_DEFINED__

.comdef IXATransLookup2 : public IUnknown

    Lookup		proc :ptr, :ptr
   .ends

endif

ifndef __IResourceManagerSink_INTERFACE_DEFINED__
define __IResourceManagerSink_INTERFACE_DEFINED__

.comdef IResourceManagerSink : public IUnknown

    TMDown		proc
   .ends

endif

ifndef __IResourceManager_INTERFACE_DEFINED__
define __IResourceManager_INTERFACE_DEFINED__

.comdef IResourceManager : public IUnknown

    Enlist		proc :ptr, :ptr, :ptr, :ptr, :ptr
    Reenlist		proc
    ReenlistmentComplete proc
    GetDistributedTransactionManager proc :REFIID, :ptr
   .ends

endif

ifndef __ILastResourceManager_INTERFACE_DEFINED__
define __ILastResourceManager_INTERFACE_DEFINED__

.comdef ILastResourceManager : public IUnknown

    TransactionCommitted proc
    RecoveryDone	proc
   .ends

endif

ifndef __IResourceManager2_INTERFACE_DEFINED__
define __IResourceManager2_INTERFACE_DEFINED__

.comdef IResourceManager2 : public IResourceManager

    Enlist2		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    Reenlist2		proc :ptr, :DWORD, :ptr
   .ends

endif

ifndef __IXAConfig_INTERFACE_DEFINED__
define __IXAConfig_INTERFACE_DEFINED__

.comdef IXAConfig : public IUnknown

    Initialize		proc :GUID
    Terminate		proc
   .ends

endif

ifndef __IRMHelper_INTERFACE_DEFINED__
define __IRMHelper_INTERFACE_DEFINED__

.comdef IRMHelper : public IUnknown

    RMCount		proc :DWORD
    RMInfo		proc :ptr, :BOOL, :ptr, :ptr, :GUID
   .ends

endif

ifndef __IXAObtainRMInfo_INTERFACE_DEFINED__
define __IXAObtainRMInfo_INTERFACE_DEFINED__

.comdef IXAObtainRMInfo : public IUnknown

    ObtainRMInfo	proc :ptr
   .ends

endif

ifndef __IResourceManagerFactory_INTERFACE_DEFINED__
define __IResourceManagerFactory_INTERFACE_DEFINED__

.comdef IResourceManagerFactory : public IUnknown

    Create		proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IResourceManagerFactory2_INTERFACE_DEFINED__
define __IResourceManagerFactory2_INTERFACE_DEFINED__

.comdef IResourceManagerFactory2 : public IResourceManagerFactory

    CreateEx		proc :ptr, :ptr, :ptr, :REFIID, :ptr
   .ends

endif

ifndef __IPrepareInfo_INTERFACE_DEFINED__
define __IPrepareInfo_INTERFACE_DEFINED__

.comdef IPrepareInfo : public IUnknown

    GetPrepareInfoSize	proc :ptr
    GetPrepareInfo	proc :ptr
   .ends

endif

ifndef __IPrepareInfo2_INTERFACE_DEFINED__
define __IPrepareInfo2_INTERFACE_DEFINED__

.comdef IPrepareInfo2 : public IUnknown

    GetPrepareInfoSize	proc :ptr
    GetPrepareInfo	proc :ULONG, :ptr
   .ends

endif

ifndef __IGetDispenser_INTERFACE_DEFINED__
define __IGetDispenser_INTERFACE_DEFINED__

.comdef IGetDispenser : public IUnknown

    GetDispenser	proc :REFIID, :ptr
   .ends

endif

ifndef __ITransactionVoterBallotAsync2_INTERFACE_DEFINED__
define __ITransactionVoterBallotAsync2_INTERFACE_DEFINED__

.comdef ITransactionVoterBallotAsync2 : public IUnknown

    VoteRequestDone	proc :HRESULT, :ptr
   .ends

endif

ifndef __ITransactionVoterNotifyAsync2_INTERFACE_DEFINED__
define __ITransactionVoterNotifyAsync2_INTERFACE_DEFINED__

.comdef ITransactionVoterNotifyAsync2 : public ITransactionOutcomeEvents

    VoteRequest		proc
   .ends

endif

ifndef __ITransactionVoterFactory2_INTERFACE_DEFINED__
define __ITransactionVoterFactory2_INTERFACE_DEFINED__

.comdef ITransactionVoterFactory2 : public IUnknown

    Create		proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __ITransactionPhase0EnlistmentAsync_INTERFACE_DEFINED__
define __ITransactionPhase0EnlistmentAsync_INTERFACE_DEFINED__

.comdef ITransactionPhase0EnlistmentAsync : public IUnknown

    Enable		proc
    WaitForEnlistment	proc
    Phase0Done		proc
    Unenlist		proc
    GetTransaction	proc :ptr
   .ends

endif

ifndef __ITransactionPhase0NotifyAsync_INTERFACE_DEFINED__
define __ITransactionPhase0NotifyAsync_INTERFACE_DEFINED__

.comdef ITransactionPhase0NotifyAsync : public IUnknown

    Phase0Request	proc :BOOL
    EnlistCompleted	proc :HRESULT
   .ends

endif

ifndef __ITransactionPhase0Factory_INTERFACE_DEFINED__
define __ITransactionPhase0Factory_INTERFACE_DEFINED__

.comdef ITransactionPhase0Factory : public IUnknown

    Create		proc :ptr, :ptr
   .ends

endif

ifndef __ITransactionTransmitter_INTERFACE_DEFINED__
define __ITransactionTransmitter_INTERFACE_DEFINED__

.comdef ITransactionTransmitter : public IUnknown

    Set			proc :ptr
    GetPropagationTokenSize proc :ptr
    MarshalPropagationToken proc :ULONG
    UnmarshalReturnToken proc :ULONG, :ptr
    Reset		proc
   .ends

endif

ifndef __ITransactionTransmitterFactory_INTERFACE_DEFINED__
define __ITransactionTransmitterFactory_INTERFACE_DEFINED__

.comdef ITransactionTransmitterFactory : public IUnknown

    Create		proc :ptr
   .ends

endif

ifndef __ITransactionReceiver_INTERFACE_DEFINED__
define __ITransactionReceiver_INTERFACE_DEFINED__

.comdef ITransactionReceiver : public IUnknown

    UnmarshalPropagationToken proc :ULONG
    GetReturnTokenSize	proc :ptr
    MarshalReturnToken	proc :ULONG
    Reset		proc
   .ends

endif

ifndef __ITransactionReceiverFactory_INTERFACE_DEFINED__
define __ITransactionReceiverFactory_INTERFACE_DEFINED__

.comdef ITransactionReceiverFactory : public IUnknown

    Create		proc :ptr
   .ends

endif

PROXY_CONFIG_PARAMS	STRUC
wcThreadsMax		dw ?
PROXY_CONFIG_PARAMS	ENDS

ifndef __IDtcLuConfigure_INTERFACE_DEFINED__
define __IDtcLuConfigure_INTERFACE_DEFINED__

.comdef IDtcLuConfigure : public IUnknown

    _Add		proc
    Delete		proc
   .ends

endif

ifndef __IDtcLuRecovery_INTERFACE_DEFINED__
define __IDtcLuRecovery_INTERFACE_DEFINED__

.comdef IDtcLuRecovery : public IUnknown

   .ends

endif

ifndef __IDtcLuRecoveryFactory_INTERFACE_DEFINED__
define __IDtcLuRecoveryFactory_INTERFACE_DEFINED__

.comdef IDtcLuRecoveryFactory : public IUnknown

    Create		proc
   .ends

endif

.enum DTCINITIATEDRECOVERYWORK {
    DTCINITIATEDRECOVERYWORK_CHECKLUSTATUS	= 1,
    DTCINITIATEDRECOVERYWORK_TRANS	= ( DTCINITIATEDRECOVERYWORK_CHECKLUSTATUS + 1 ) ,
    DTCINITIATEDRECOVERYWORK_TMDOWN	= ( DTCINITIATEDRECOVERYWORK_TRANS + 1 )
    }

.enum DTCLUXLN {
    DTCLUXLN_COLD	= 1,
    DTCLUXLN_WARM	= ( DTCLUXLN_COLD + 1 )
    }

.enum DTCLUXLNCONFIRMATION {
    DTCLUXLNCONFIRMATION_CONFIRM	= 1,
    DTCLUXLNCONFIRMATION_LOGNAMEMISMATCH	= ( DTCLUXLNCONFIRMATION_CONFIRM + 1 ) ,
    DTCLUXLNCONFIRMATION_COLDWARMMISMATCH	= ( DTCLUXLNCONFIRMATION_LOGNAMEMISMATCH + 1 ) ,
    DTCLUXLNCONFIRMATION_OBSOLETE	= ( DTCLUXLNCONFIRMATION_COLDWARMMISMATCH + 1 )
    }

.enum DTCLUXLNRESPONSE {
    DTCLUXLNRESPONSE_OK_SENDOURXLNBACK	= 1,
    DTCLUXLNRESPONSE_OK_SENDCONFIRMATION	= ( DTCLUXLNRESPONSE_OK_SENDOURXLNBACK + 1 ) ,
    DTCLUXLNRESPONSE_LOGNAMEMISMATCH	= ( DTCLUXLNRESPONSE_OK_SENDCONFIRMATION + 1 ) ,
    DTCLUXLNRESPONSE_COLDWARMMISMATCH	= ( DTCLUXLNRESPONSE_LOGNAMEMISMATCH + 1 )
    }

.enum DTCLUXLNERROR {
    DTCLUXLNERROR_PROTOCOL	= 1,
    DTCLUXLNERROR_LOGNAMEMISMATCH	= ( DTCLUXLNERROR_PROTOCOL + 1 ) ,
    DTCLUXLNERROR_COLDWARMMISMATCH	= ( DTCLUXLNERROR_LOGNAMEMISMATCH + 1 )
    }

.enum DTCLUCOMPARESTATE {
    DTCLUCOMPARESTATE_COMMITTED = 1,
    DTCLUCOMPARESTATE_HEURISTICCOMMITTED	= ( DTCLUCOMPARESTATE_COMMITTED + 1 ) ,
    DTCLUCOMPARESTATE_HEURISTICMIXED	= ( DTCLUCOMPARESTATE_HEURISTICCOMMITTED + 1 ) ,
    DTCLUCOMPARESTATE_HEURISTICRESET	= ( DTCLUCOMPARESTATE_HEURISTICMIXED + 1 ) ,
    DTCLUCOMPARESTATE_INDOUBT	= ( DTCLUCOMPARESTATE_HEURISTICRESET + 1 ) ,
    DTCLUCOMPARESTATE_RESET	= ( DTCLUCOMPARESTATE_INDOUBT + 1 )
    }

.enum DTCLUCOMPARESTATESCONFIRMATION {
    DTCLUCOMPARESTATESCONFIRMATION_CONFIRM	= 1,
    DTCLUCOMPARESTATESCONFIRMATION_PROTOCOL	= ( DTCLUCOMPARESTATESCONFIRMATION_CONFIRM + 1 )
    }

.enum DTCLUCOMPARESTATESERROR {
    DTCLUCOMPARESTATESERROR_PROTOCOL	= 1
    }

.enum DTCLUCOMPARESTATESRESPONSE {
    DTCLUCOMPARESTATESRESPONSE_OK	= 1,
    DTCLUCOMPARESTATESRESPONSE_PROTOCOL = ( DTCLUCOMPARESTATESRESPONSE_OK + 1 )
    }


ifndef __IDtcLuRecoveryInitiatedByDtcTransWork_INTERFACE_DEFINED__
define __IDtcLuRecoveryInitiatedByDtcTransWork_INTERFACE_DEFINED__

.comdef IDtcLuRecoveryInitiatedByDtcTransWork : public IUnknown

    GetLogNameSizes	proc :ptr, :ptr
    GetOurXln		proc :ptr, :ptr, :ptr, :ptr
    HandleConfirmationFromOurXln proc :DTCLUXLNCONFIRMATION
    HandleTheirXlnResponse proc :DTCLUXLN, :ptr, :DWORD, :DWORD, :ptr
    HandleErrorFromOurXln proc :DTCLUXLNERROR
    CheckForCompareStates proc :ptr
    GetOurTransIdSize	proc :ptr
    GetOurCompareStates proc :ptr, :ptr
    HandleTheirCompareStatesResponse proc :DTCLUCOMPARESTATE, :ptr
    HandleErrorFromOurCompareStates proc :DTCLUCOMPARESTATESERROR
    ConversationLost	proc
    GetRecoverySeqNum	proc :ptr
    ObsoleteRecoverySeqNum proc :LONG
   .ends

endif

ifndef __IDtcLuRecoveryInitiatedByDtcStatusWork_INTERFACE_DEFINED__
define __IDtcLuRecoveryInitiatedByDtcStatusWork_INTERFACE_DEFINED__

.comdef IDtcLuRecoveryInitiatedByDtcStatusWork : public IUnknown

    HandleCheckLuStatus proc :LONG
   .ends

endif

ifndef __IDtcLuRecoveryInitiatedByDtc_INTERFACE_DEFINED__
define __IDtcLuRecoveryInitiatedByDtc_INTERFACE_DEFINED__

.comdef IDtcLuRecoveryInitiatedByDtc : public IUnknown

    GetWork		proc :ptr, :ptr
   .ends

endif

ifndef __IDtcLuRecoveryInitiatedByLuWork_INTERFACE_DEFINED__
define __IDtcLuRecoveryInitiatedByLuWork_INTERFACE_DEFINED__

.comdef IDtcLuRecoveryInitiatedByLuWork : public IUnknown

    HandleTheirXln	proc :LONG, :DTCLUXLN, :ptr, :DWORD, :ptr, :DWORD, :DWORD, :ptr
    GetOurLogNameSize	proc :ptr
    GetOurXln		proc :ptr, :ptr, :ptr
    HandleConfirmationOfOurXln proc :DTCLUXLNCONFIRMATION
    HandleTheirCompareStates proc :ptr, :DWORD, :DTCLUCOMPARESTATE, :ptr, :ptr
    HandleConfirmationOfOurCompareStates proc :DTCLUCOMPARESTATESCONFIRMATION
    HandleErrorFromOurCompareStates proc :DTCLUCOMPARESTATESERROR
    ConversationLost	proc
   .ends

endif

ifndef __IDtcLuRecoveryInitiatedByLu_INTERFACE_DEFINED__
define __IDtcLuRecoveryInitiatedByLu_INTERFACE_DEFINED__

.comdef IDtcLuRecoveryInitiatedByLu : public IUnknown

    GetObjectToHandleWorkFromLu proc :ptr
   .ends

endif

ifndef __IDtcLuRmEnlistment_INTERFACE_DEFINED__
define __IDtcLuRmEnlistment_INTERFACE_DEFINED__

.comdef IDtcLuRmEnlistment : public IUnknown

    Unplug		proc :BOOL
    BackedOut		proc
    BackOut		proc
    Committed		proc
    Forget		proc
    RequestCommit	proc
   .ends

endif

ifndef __IDtcLuRmEnlistmentSink_INTERFACE_DEFINED__
define __IDtcLuRmEnlistmentSink_INTERFACE_DEFINED__

.comdef IDtcLuRmEnlistmentSink : public IUnknown

    AckUnplug		proc
    TmDown		proc
    SessionLost		proc
    BackedOut		proc
    BackOut		proc
    Committed		proc
    Forget		proc
    Prepare		proc
    RequestCommit	proc
   .ends

endif

ifndef __IDtcLuRmEnlistmentFactory_INTERFACE_DEFINED__
define __IDtcLuRmEnlistmentFactory_INTERFACE_DEFINED__

.comdef IDtcLuRmEnlistmentFactory : public IUnknown

    Create		proc :ptr, :DWORD, :ptr, :ptr, :DWORD, :ptr, :ptr
   .ends

endif

ifndef __IDtcLuSubordinateDtc_INTERFACE_DEFINED__
define __IDtcLuSubordinateDtc_INTERFACE_DEFINED__

.comdef IDtcLuSubordinateDtc : public IUnknown

    Unplug		proc :BOOL
    BackedOut		proc
    BackOut		proc
    Committed		proc
    Forget		proc
    Prepare		proc
    RequestCommit	proc
   .ends

endif

ifndef __IDtcLuSubordinateDtcSink_INTERFACE_DEFINED__
define __IDtcLuSubordinateDtcSink_INTERFACE_DEFINED__

.comdef IDtcLuSubordinateDtcSink : public IUnknown

    AckUnplug		proc
    TmDown		proc
    SessionLost		proc
    BackedOut		proc
    BackOut		proc
    Committed		proc
    Forget		proc
    RequestCommit	proc
   .ends

endif

ifndef __IDtcLuSubordinateDtcFactory_INTERFACE_DEFINED__
define __IDtcLuSubordinateDtcFactory_INTERFACE_DEFINED__

.comdef IDtcLuSubordinateDtcFactory : public IUnknown

    Create		proc :ptr, :DWORD, :ptr, :ISOLEVEL, :ULONG, :ptr, :ptr, :ptr, :DWORD, :ptr, :ptr
   .ends

endif

DEFINE_GUID(IID_IXATransLookup, 0xF3B1F131, 0xEEDA, 0x11ce, 0xAE, 0xD4, 0x00, 0xAA, 0x00, 0x51, 0xE2, 0xC4);
DEFINE_GUID(IID_IXATransLookup2,0xbf193c85, 0xd1a, 0x4290, 0xb8, 0x8f, 0xd2, 0xcb, 0x88, 0x73, 0xd1, 0xe7);
DEFINE_GUID(IID_IResourceManagerSink, 0x0D563181, 0xDEFB, 0x11ce, 0xAE, 0xD1, 0x00, 0xAA, 0x00, 0x51, 0xE2, 0xC4);
DEFINE_GUID(IID_IResourceManager, 0x3741d21, 0x87eb, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_IResourceManager2, 0xd136c69a, 0xf749, 0x11d1, 0x8f, 0x47, 0x0, 0xc0, 0x4f, 0x8e, 0xe5, 0x7d);
DEFINE_GUID(IID_ILastResourceManager, 0x4d964ad4, 0x5b33, 0x11d3, 0x8a, 0x91, 0x00, 0xc0, 0x4f, 0x79, 0xeb, 0x6d);
DEFINE_GUID(IID_IXAConfig, 0xC8A6E3A1, 0x9A8C, 0x11cf, 0xA3, 0x08, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IRMHelper, 0xE793F6D1, 0xF53D, 0x11cf, 0xA6, 0x0D, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXAObtainRMInfo, 0xE793F6D2, 0xF53D, 0x11cf, 0xA6, 0x0D, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXAResourceManager, 0x4131E751, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXAResourceManagerFactory, 0x4131E750, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXATransaction, 0x4131E752, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IResourceManagerFactory, 0x13741d20, 0x87eb, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_IResourceManagerFactory2, 0x6b369c21, 0xfbd2, 0x11d1, 0x8f, 0x47, 0x0, 0xc0, 0x4f, 0x8e, 0xe5, 0x7d);
DEFINE_GUID(IID_IPrepareInfo, 0x80c7bfd0, 0x87ee, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_IPrepareInfo2, 0x5FAB2547, 0x9779, 0x11d1, 0xB8, 0x86, 0x00, 0xC0, 0x4F, 0xB9, 0x61, 0x8A);
DEFINE_GUID(IID_IGetDispenser, 0xc23cc370, 0x87ef, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_ITransactionVoterNotifyAsync2, 0x5433376b, 0x414d, 0x11d3, 0xb2, 0x6, 0x0, 0xc0, 0x4f, 0xc2, 0xf3, 0xef);
DEFINE_GUID(IID_ITransactionVoterBallotAsync2, 0x5433376c, 0x414d, 0x11d3, 0xb2, 0x6, 0x0, 0xc0, 0x4f, 0xc2, 0xf3, 0xef);
DEFINE_GUID(IID_ITransactionVoterFactory2, 0x5433376a, 0x414d, 0x11d3, 0xb2, 0x6, 0x0, 0xc0, 0x4f, 0xc2, 0xf3, 0xef);
DEFINE_GUID(IID_ITransactionPhase0EnlistmentAsync, 0x82DC88E1, 0xA954, 0x11d1, 0x8F, 0x88, 0x00, 0x60, 0x08, 0x95, 0xE7, 0xD5);
DEFINE_GUID(IID_ITransactionPhase0NotifyAsync, 0xEF081809, 0x0C76, 0x11d2, 0x87, 0xA6, 0x00, 0xC0, 0x4F, 0x99, 0x0F, 0x34);
DEFINE_GUID(IID_ITransactionPhase0Factory, 0x82DC88E0, 0xA954, 0x11d1, 0x8F, 0x88, 0x00, 0x60, 0x08, 0x95, 0xE7, 0xD5);
DEFINE_GUID(IID_ITransactionTransmitter, 0x59313E01, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionTransmitterFactory, 0x59313E00, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionReceiver, 0x59313E03, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionReceiverFactory, 0x59313E02, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);

DEFINE_GUID(IID_IDtcLuConfigure, 0x4131E760, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecovery, 0xac2b8ad2, 0xd6f0, 0x11d0, 0xb3, 0x86, 0x0, 0xa0, 0xc9, 0x8, 0x33, 0x65);
DEFINE_GUID(IID_IDtcLuRecoveryFactory, 0x4131E762, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByDtcTransWork, 0x4131E765, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByDtcStatusWork, 0x4131E766, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByDtc, 0x4131E764, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByLuWork, 0xac2b8ad1, 0xd6f0, 0x11d0, 0xb3, 0x86, 0x0, 0xa0, 0xc9, 0x8, 0x33, 0x65);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByLu, 0x4131E768, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRmEnlistment, 0x4131E769, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRmEnlistmentSink, 0x4131E770, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRmEnlistmentFactory, 0x4131E771, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuSubordinateDtc, 0x4131E773, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuSubordinateDtcSink, 0x4131E774, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuSubordinateDtcFactory, 0x4131E775, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);

endif
endif
