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

ifndef __transact_h__
define __transact_h__

include unknwn.inc
include winerror.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __BasicTransactionTypes_INTERFACE_DEFINED__
define __BasicTransactionTypes_INTERFACE_DEFINED__

BOID			STRUC
rgb			db  16	dup(?)
BOID			ENDS

BOID_NULL		equ IID_NULL
ifndef MAX_TRAN_DESC_DEFINED
define MAX_TRAN_DESC_DEFINED

.enum TX_MISC_CONSTANTS {
    MAX_TRAN_DESC	= 40
    }

endif
XACTUOW			typedef BOID
ISOLEVEL		typedef LONG

.enum ISOLATIONLEVEL {
    ISOLATIONLEVEL_UNSPECIFIED	= 0xffffffff,
    ISOLATIONLEVEL_CHAOS	= 0x10,
    ISOLATIONLEVEL_READUNCOMMITTED	= 0x100,
    ISOLATIONLEVEL_BROWSE	= 0x100,
    ISOLATIONLEVEL_CURSORSTABILITY	= 0x1000,
    ISOLATIONLEVEL_READCOMMITTED	= 0x1000,
    ISOLATIONLEVEL_REPEATABLEREAD	= 0x10000,
    ISOLATIONLEVEL_SERIALIZABLE = 0x100000,
    ISOLATIONLEVEL_ISOLATED	= 0x100000
    }

XACTTRANSINFO		STRUC
uow			XACTUOW <>
isoLevel		ISOLEVEL ?
isoFlags		ULONG ?
grfTCSupported		dd ?
grfRMSupported		dd ?
grfTCSupportedRetaining dd ?
grfRMSupportedRetaining dd ?
XACTTRANSINFO		ENDS

XACTSTATS		STRUC
cOpen			ULONG ?
cCommitting		ULONG ?
cCommitted		ULONG ?
cAborting		ULONG ?
cAborted		ULONG ?
cInDoubt		ULONG ?
cHeuristicDecision	ULONG ?
timeTransactionsUp	FILETIME <>
XACTSTATS		ENDS

.enum ISOFLAG {
    ISOFLAG_RETAIN_COMMIT_DC	= 1,
    ISOFLAG_RETAIN_COMMIT	= 2,
    ISOFLAG_RETAIN_COMMIT_NO	= 3,
    ISOFLAG_RETAIN_ABORT_DC	= 4,
    ISOFLAG_RETAIN_ABORT	= 8,
    ISOFLAG_RETAIN_ABORT_NO	= 12,
    ISOFLAG_RETAIN_DONTCARE	= ( ISOFLAG_RETAIN_COMMIT_DC or ISOFLAG_RETAIN_ABORT_DC ) ,
    ISOFLAG_RETAIN_BOTH = ( ISOFLAG_RETAIN_COMMIT or ISOFLAG_RETAIN_ABORT ) ,
    ISOFLAG_RETAIN_NONE = ( ISOFLAG_RETAIN_COMMIT_NO or ISOFLAG_RETAIN_ABORT_NO ) ,
    ISOFLAG_OPTIMISTIC	= 16,
    ISOFLAG_READONLY	= 32
    }

.enum XACTTC {
    XACTTC_NONE = 0,
    XACTTC_SYNC_PHASEONE	= 1,
    XACTTC_SYNC_PHASETWO	= 2,
    XACTTC_SYNC = 2,
    XACTTC_ASYNC_PHASEONE	= 4,
    XACTTC_ASYNC	= 4
    }

.enum XACTRM {
    XACTRM_OPTIMISTICLASTWINS	= 1,
    XACTRM_NOREADONLYPREPARES	= 2
    }

.enum XACTCONST {
    XACTCONST_TIMEOUTINFINITE	= 0
    }

.enum XACTHEURISTIC {
    XACTHEURISTIC_ABORT = 1,
    XACTHEURISTIC_COMMIT	= 2,
    XACTHEURISTIC_DAMAGE	= 3,
    XACTHEURISTIC_DANGER	= 4
    }

.enum XACTSTAT {
    XACTSTAT_NONE	= 0,
    XACTSTAT_OPENNORMAL = 0x1,
    XACTSTAT_OPENREFUSED	= 0x2,
    XACTSTAT_PREPARING	= 0x4,
    XACTSTAT_PREPARED	= 0x8,
    XACTSTAT_PREPARERETAINING	= 0x10,
    XACTSTAT_PREPARERETAINED	= 0x20,
    XACTSTAT_COMMITTING = 0x40,
    XACTSTAT_COMMITRETAINING	= 0x80,
    XACTSTAT_ABORTING	= 0x100,
    XACTSTAT_ABORTED	= 0x200,
    XACTSTAT_COMMITTED	= 0x400,
    XACTSTAT_HEURISTIC_ABORT	= 0x800,
    XACTSTAT_HEURISTIC_COMMIT	= 0x1000,
    XACTSTAT_HEURISTIC_DAMAGE	= 0x2000,
    XACTSTAT_HEURISTIC_DANGER	= 0x4000,
    XACTSTAT_FORCED_ABORT	= 0x8000,
    XACTSTAT_FORCED_COMMIT	= 0x10000,
    XACTSTAT_INDOUBT	= 0x20000,
    XACTSTAT_CLOSED	= 0x40000,
    XACTSTAT_OPEN	= 0x3,
    XACTSTAT_NOTPREPARED	= 0x7ffc3,
    XACTSTAT_ALL	= 0x7ffff
    }

XACTOPT			STRUC
ulTimeout		ULONG ?
szDescription		sbyte 40 dup(?)
XACTOPT			ENDS

endif

ifndef __ITransaction_INTERFACE_DEFINED__
define __ITransaction_INTERFACE_DEFINED__

DEFINE_GUID(IID_ITransaction, 0x0fb15084, 0xaf41, 0x11ce, 0xbd, 0x2b, 0x20, 0x4c, 0x4f, 0x4f, 0x50, 0x20)

.comdef ITransaction : public IUnknown

    Commit		proc :BOOL, :DWORD, :DWORD
    Abort		proc :ptr, :BOOL, :BOOL
    GetTransactionInfo	proc :ptr
   .ends

endif

ifndef __ITransactionCloner_INTERFACE_DEFINED__
define __ITransactionCloner_INTERFACE_DEFINED__

DEFINE_GUID(IID_ITransactionCloner, 0x02656950, 0x2152, 0x11d0, 0x94, 0x4C, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E)

.comdef ITransactionCloner : public ITransaction

    CloneWithCommitDisabled proc :ptr
   .ends

endif

ifndef __ITransaction2_INTERFACE_DEFINED__
define __ITransaction2_INTERFACE_DEFINED__

DEFINE_GUID(IID_ITransaction2, 0x34021548, 0x0065, 0x11d3, 0xba, 0xc1, 0x00, 0xc0, 0x4f, 0x79, 0x7b, 0xe2)

.comdef ITransaction2 : public ITransactionCloner

    GetTransactionInfo2 proc :ptr
   .ends

endif

ifndef __ITransactionDispenser_INTERFACE_DEFINED__
define __ITransactionDispenser_INTERFACE_DEFINED__

DEFINE_GUID(IID_ITransactionDispenser, 0x3A6AD9E1, 0x23B9, 0x11cf, 0xAD, 0x60, 0x00, 0xAA, 0x00, 0xA7, 0x4C, 0xCD)

.comdef ITransactionDispenser : public IUnknown

    GetOptionsObject	proc :ptr
    BeginTransaction	proc :ptr, :ISOLEVEL, :ULONG, :ptr, :ptr
   .ends

endif

ifndef __ITransactionOptions_INTERFACE_DEFINED__
define __ITransactionOptions_INTERFACE_DEFINED__

DEFINE_GUID(IID_ITransactionOptions, 0x3A6AD9E0, 0x23B9, 0x11cf, 0xAD, 0x60, 0x00, 0xAA, 0x00, 0xA7, 0x4C, 0xCD)

.comdef ITransactionOptions : public IUnknown

    SetOptions		proc :ptr
    GetOptions		proc :ptr
   .ends

endif

ifndef __ITransactionOutcomeEvents_INTERFACE_DEFINED__
define __ITransactionOutcomeEvents_INTERFACE_DEFINED__

DEFINE_GUID(IID_ITransactionOutcomeEvents, 0x3A6AD9E2, 0x23B9, 0x11cf, 0xAD, 0x60, 0x00, 0xAA, 0x00, 0xA7, 0x4C, 0xCD)

.comdef ITransactionOutcomeEvents : public IUnknown

    Committed		proc :BOOL, :ptr, :HRESULT
    Aborted		proc :ptr, :BOOL, :ptr, :HRESULT
    HeuristicDecision	proc :DWORD, :ptr, :HRESULT
    Indoubt		proc
   .ends

endif

ifndef __ITmNodeName_INTERFACE_DEFINED__
define __ITmNodeName_INTERFACE_DEFINED__

DEFINE_GUID(IID_ITmNodeName, 0x30274F88, 0x6EE4, 0x474e, 0x9B, 0x95, 0x78, 0x07, 0xBC, 0x9E, 0xF8, 0xCF)

.comdef ITmNodeName : public IUnknown

    GetNodeNameSize	proc :ptr
    GetNodeName		proc :ULONG, :LPWSTR
   .ends

endif

ifndef __IKernelTransaction_INTERFACE_DEFINED__
define __IKernelTransaction_INTERFACE_DEFINED__

DEFINE_GUID(IID_IKernelTransaction, 0x79427a2b, 0xf895, 0x40e0, 0xbe, 0x79, 0xb5, 0x7d, 0xc8, 0x2e, 0xd2, 0x31)

.comdef IKernelTransaction : public IUnknown

    GetHandle		proc :ptr
   .ends

endif
endif
endif
