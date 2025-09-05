ifndef _RPC500_
include rpc500.inc
endif
ifndef __rendezvoussession_h__
define __rendezvoussession_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define	DISPID_EVENT_ON_STATE_CHANGED	( 5 )
define	DISPID_EVENT_ON_TERMINATION	( 6 )
define	DISPID_EVENT_ON_CONTEXT_DATA	( 7 )
define	DISPID_EVENT_ON_SEND_ERROR	( 8 )

ifndef __RendezvousSessionLib_LIBRARY_DEFINED__
define __RendezvousSessionLib_LIBRARY_DEFINED__

.enum RENDEZVOUS_SESSION_STATE {
	RSS_UNKNOWN,
	RSS_READY,
	RSS_INVITATION,
	RSS_ACCEPTED,
	RSS_CONNECTED,
	RSS_CANCELLED,
	RSS_DECLINED,
	RSS_TERMINATED
	}

.enum RENDEZVOUS_SESSION_FLAGS {
	RSF_NONE			= 0,
	RSF_INVITER			= 0x1,
	RSF_INVITEE			= 0x2,
	RSF_ORIGINAL_INVITER		= 0x4,
	RSF_REMOTE_LEGACYSESSION	= 0x8,
	RSF_REMOTE_WIN7SESSION		= 0x10
	}

externdef LIBID_RendezvousSessionLib:IID

ifndef __IRendezvousSession_INTERFACE_DEFINED__
define __IRendezvousSession_INTERFACE_DEFINED__

DEFINE_IIDX(IRendezvousSession, "9BA4B1DD-8B0C-48B7-9E7C-2F25857C8DF5")

.comdef IRendezvousSession : public IUnknown
    get_State		proc :ptr
    get_RemoteUser	proc :ptr
    get_Flags		proc :ptr
    SendContextData	proc :BSTR
    Terminate		proc :HRESULT, :BSTR
   .ends

endif

ifndef __DRendezvousSessionEvents_DISPINTERFACE_DEFINED__
define __DRendezvousSessionEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(DRendezvousSessionEvents, "3FA19CF8-64C4-4F53-AE60-635B3806ECA6")

.comdef DRendezvousSessionEvents : public IDispatch
   .ends

endif

ifndef __IRendezvousApplication_INTERFACE_DEFINED__
define __IRendezvousApplication_INTERFACE_DEFINED__

DEFINE_IIDX(IRendezvousApplication, "4F4D070B-A275-49FB-B10D-8EC26387B50D")

.comdef IRendezvousApplication : public IUnknown
    SetRendezvousSession proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_RendezvousApplication,  "0B7E019A-B5DE-47fa-8966-9082F82FB192")

endif

endif

endif
