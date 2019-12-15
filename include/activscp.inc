.pragma list(push, 0)

ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
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
ifndef __activscp_h__
__activscp_h__ equ <>

ifndef __IActiveScriptSite_FWD_DEFINED__
__IActiveScriptSite_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptError_FWD_DEFINED__
__IActiveScriptError_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptError64_FWD_DEFINED__
__IActiveScriptError64_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptSiteWindow_FWD_DEFINED__
__IActiveScriptSiteWindow_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptSiteUIControl_FWD_DEFINED__
__IActiveScriptSiteUIControl_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptSiteInterruptPoll_FWD_DEFINED__
__IActiveScriptSiteInterruptPoll_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScript_FWD_DEFINED__
__IActiveScript_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParse32_FWD_DEFINED__
__IActiveScriptParse32_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParse64_FWD_DEFINED__
__IActiveScriptParse64_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParseProcedureOld32_FWD_DEFINED__
__IActiveScriptParseProcedureOld32_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParseProcedureOld64_FWD_DEFINED__
__IActiveScriptParseProcedureOld64_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParseProcedure32_FWD_DEFINED__
__IActiveScriptParseProcedure32_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParseProcedure64_FWD_DEFINED__
__IActiveScriptParseProcedure64_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParseProcedure2_32_FWD_DEFINED__
__IActiveScriptParseProcedure2_32_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptParseProcedure2_64_FWD_DEFINED__
__IActiveScriptParseProcedure2_64_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptEncode_FWD_DEFINED__
__IActiveScriptEncode_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptHostEncode_FWD_DEFINED__
__IActiveScriptHostEncode_FWD_DEFINED__ equ 1
endif
ifndef __IBindEventHandler_FWD_DEFINED__
__IBindEventHandler_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptStats_FWD_DEFINED__
__IActiveScriptStats_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptProperty_FWD_DEFINED__
__IActiveScriptProperty_FWD_DEFINED__ equ 1
endif
ifndef __ITridentEventSink_FWD_DEFINED__
__ITridentEventSink_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptGarbageCollector_FWD_DEFINED__
__IActiveScriptGarbageCollector_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptSIPInfo_FWD_DEFINED__
__IActiveScriptSIPInfo_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptSiteTraceInfo_FWD_DEFINED__
__IActiveScriptSiteTraceInfo_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptTraceInfo_FWD_DEFINED__
__IActiveScriptTraceInfo_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptStringCompare_FWD_DEFINED__
__IActiveScriptStringCompare_FWD_DEFINED__ equ 1
endif

include ocidl.inc
ifndef __ActivScp_h
__ActivScp_h equ <>

ifndef _NO_SCRIPT_GUIDS
DEFINE_GUID(CATID_ActiveScript, 0xf0b7a1a1, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(CATID_ActiveScriptParse, 0xf0b7a1a2, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(CATID_ActiveScriptEncode, 0xf0b7a1a3, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(IID_IActiveScript, 0xbb1a2ae1, 0xa4f9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(IID_IActiveScriptParse32, 0xbb1a2ae2, 0xa4f9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(IID_IActiveScriptParse64, 0xc7ef7658, 0xe1ee, 0x480e, 0x97, 0xea, 0xd5, 0x2c, 0xb4, 0xd7, 0x6d, 0x17);
DEFINE_GUID(IID_IActiveScriptEncode, 0xbb1a2ae3, 0xa4f9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(IID_IActiveScriptHostEncode, 0xbee9b76e, 0xcfe3, 0x11d1, 0xb7, 0x47, 0x00, 0xc0, 0x4f, 0xc2, 0xb0, 0x85);
DEFINE_GUID(IID_IActiveScriptParseProcedureOld32, 0x1cff0050, 0x6fdd, 0x11d0, 0x93, 0x28, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);
DEFINE_GUID(IID_IActiveScriptParseProcedureOld64, 0x21f57128, 0x08c9, 0x4638, 0xba, 0x12, 0x22, 0xd1, 0x5d, 0x88, 0xdc, 0x5c);
DEFINE_GUID(IID_IActiveScriptParseProcedure32, 0xaa5b6a80, 0xb834, 0x11d0, 0x93, 0x2f, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);
DEFINE_GUID(IID_IActiveScriptParseProcedure64, 0xc64713b6, 0xe029, 0x4cc5, 0x92, 0x00, 0x43, 0x8b, 0x72, 0x89, 0x0b, 0x6a);
DEFINE_GUID(IID_IActiveScriptParseProcedure2_32, 0x71ee5b20, 0xfb04, 0x11d1, 0xb3, 0xa8, 0x00, 0xa0, 0xc9, 0x11, 0xe8, 0xb2);
DEFINE_GUID(IID_IActiveScriptParseProcedure2_64, 0xfe7c4271, 0x210c, 0x448d, 0x9f, 0x54, 0x76, 0xda, 0xb7, 0x04, 0x7b, 0x28);
DEFINE_GUID(IID_IActiveScriptSite, 0xdb01a1e3, 0xa42b, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(IID_IActiveScriptSiteTraceInfo, 0x4b7272ae, 0x1955, 0x4bfe, 0x98, 0xb0, 0x78, 0x6, 0x21, 0x88, 0x85, 0x69);
DEFINE_GUID(IID_IActiveScriptSiteWindow, 0xd10f6761, 0x83e9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(IID_IActiveScriptSiteInterruptPoll, 0x539698a0, 0xcdca, 0x11cf, 0xa5, 0xeb, 0x00, 0xaa, 0x00, 0x47, 0xa0, 0x63);
DEFINE_GUID(IID_IActiveScriptSiteUIControl, 0xaedae97e, 0xd7ee, 0x4796, 0xb9, 0x60, 0x7f, 0x9, 0x2a, 0xe8, 0x44, 0xab);
DEFINE_GUID(IID_IActiveScriptError,   0xeae1ba61, 0xa4ed, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
DEFINE_GUID(IID_IActiveScriptError64, 0xb21fb2a1, 0x5b8f, 0x4963, 0x8c, 0x21, 0x21, 0x45, 0x0f, 0x84, 0xed, 0x7f);
DEFINE_GUID(IID_IBindEventHandler, 0x63cdbcb0, 0xc1b1, 0x11d0, 0x93, 0x36, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);
DEFINE_GUID(IID_IActiveScriptStats, 0xb8da6310, 0xe19b, 0x11d0, 0x93, 0x3c, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);
DEFINE_GUID(IID_IActiveScriptProperty, 0x4954E0D0, 0xFBC7, 0x11D1, 0x84, 0x10, 0x00, 0x60, 0x08, 0xC3, 0xFB, 0xFC);
DEFINE_GUID(IID_ITridentEventSink, 0x1dc9ca50, 0x6ef, 0x11d2, 0x84, 0x15, 0x00, 0x60, 0x08, 0xc3, 0xfb, 0xfc);
DEFINE_GUID(IID_IActiveScriptGarbageCollector, 0x6aa2c4a0, 0x2b53, 0x11d4, 0xa2, 0xa0, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);
DEFINE_GUID(IID_IActiveScriptSIPInfo, 0x764651d0, 0x38de, 0x11d4, 0xa2, 0xa3, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);
DEFINE_GUID(IID_IActiveScriptTraceInfo, 0xC35456E7, 0xBEBF, 0x4a1b, 0x86, 0xA9, 0x24, 0xD5, 0x6B, 0xE8, 0xB3, 0x69);
DEFINE_GUID(OID_VBSSIP, 0x1629f04e, 0x2799, 0x4db5, 0x8f, 0xe5, 0xac, 0xe1, 0x0f, 0x17, 0xeb, 0xab);
DEFINE_GUID(OID_JSSIP,	0x6c9e010, 0x38ce, 0x11d4, 0xa2, 0xa3, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);
DEFINE_GUID(OID_WSFSIP, 0x1a610570, 0x38ce, 0x11d4, 0xa2, 0xa3, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);
DEFINE_GUID(IID_IActiveScriptStringCompare, 0x58562769, 0xED52, 0x42f7, 0x84, 0x03, 0x49, 0x63, 0x51, 0x4E, 0x1F, 0x11);

endif ;; _NO_SCRIPT_GUIDS

SCRIPTITEM_ISVISIBLE	equ 0x00000002
SCRIPTITEM_ISSOURCE	equ 0x00000004
SCRIPTITEM_GLOBALMEMBERS equ 0x00000008
SCRIPTITEM_ISPERSISTENT equ 0x00000040
SCRIPTITEM_CODEONLY	equ 0x00000200
SCRIPTITEM_NOCODE	equ 0x00000400

SCRIPTITEM_ALL_FLAGS	equ (SCRIPTITEM_ISSOURCE OR SCRIPTITEM_ISVISIBLE OR SCRIPTITEM_ISPERSISTENT OR \
			SCRIPTITEM_GLOBALMEMBERS OR SCRIPTITEM_NOCODE

SCRIPTTYPELIB_ISCONTROL equ 0x00000010
SCRIPTTYPELIB_ISPERSISTENT equ 0x00000040
SCRIPTTYPELIB_ALL_FLAGS equ (SCRIPTTYPELIB_ISCONTROL OR SCRIPTTYPELIB_ISPERSISTENT)

SCRIPTTEXT_DELAYEXECUTION equ 0x00000001
SCRIPTTEXT_ISVISIBLE	equ 0x00000002
SCRIPTTEXT_ISEXPRESSION equ 0x00000020
SCRIPTTEXT_ISPERSISTENT equ 0x00000040
SCRIPTTEXT_HOSTMANAGESSOURCE equ 0x00000080
SCRIPTTEXT_ISXDOMAIN	equ 0x00000100
SCRIPTTEXT_ALL_FLAGS	equ (SCRIPTTEXT_DELAYEXECUTION OR SCRIPTTEXT_ISVISIBLE OR SCRIPTTEXT_ISEXPRESSION OR \
			SCRIPTTEXT_ISPERSISTENT OR SCRIPTTEXT_HOSTMANAGESSOURCE

SCRIPTPROC_ISEXPRESSION equ 0x00000020
SCRIPTPROC_HOSTMANAGESSOURCE equ 0x00000080
SCRIPTPROC_IMPLICIT_THIS equ 0x00000100
SCRIPTPROC_IMPLICIT_PARENTS equ 0x00000200
SCRIPTPROC_ISXDOMAIN	equ 0x00000400
SCRIPTPROC_ALL_FLAGS	equ SCRIPTPROC_HOSTMANAGESSOURCE OR \
			    SCRIPTPROC_ISEXPRESSION OR \
			    SCRIPTPROC_IMPLICIT_THIS OR \
			    SCRIPTPROC_IMPLICIT_PARENTS OR \
			    SCRIPTPROC_ISXDOMAIN

SCRIPTINFO_IUNKNOWN	equ 0x00000001
SCRIPTINFO_ITYPEINFO	equ 0x00000002
SCRIPTINFO_ALL_FLAGS	equ SCRIPTINFO_IUNKNOWN OR SCRIPTINFO_ITYPEINFO

SCRIPTINTERRUPT_DEBUG	equ 0x00000001
SCRIPTINTERRUPT_RAISEEXCEPTION equ 0x00000002
SCRIPTINTERRUPT_ALL_FLAGS equ SCRIPTINTERRUPT_DEBUG OR SCRIPTINTERRUPT_RAISEEXCEPTION

SCRIPTSTAT_STATEMENT_COUNT equ 1
SCRIPTSTAT_INSTRUCTION_COUNT equ 2
SCRIPTSTAT_INTSTRUCTION_TIME equ 3
SCRIPTSTAT_TOTAL_TIME	equ 4

SCRIPT_ENCODE_SECTION	equ 0x00000001

SCRIPT_ENCODE_DEFAULT_LANGUAGE equ 0x00000001
SCRIPT_ENCODE_NO_ASP_LANGUAGE equ 0x00000002

SCRIPTPROP_NAME		equ 0x00000000
SCRIPTPROP_MAJORVERSION equ 0x00000001
SCRIPTPROP_MINORVERSION equ 0x00000002
SCRIPTPROP_BUILDNUMBER	equ 0x00000003

SCRIPTPROP_DELAYEDEVENTSINKING equ 0x00001000
SCRIPTPROP_CATCHEXCEPTION equ 0x00001001
SCRIPTPROP_CONVERSIONLCID equ 0x00001002
SCRIPTPROP_HOSTSTACKREQUIRED equ 0x00001003

SCRIPTPROP_DEBUGGER	equ 0x00001100
SCRIPTPROP_JITDEBUG	equ 0x00001101

SCRIPTPROP_GCCONTROLSOFTCLOSE equ 0x00002000

SCRIPTPROP_INTEGERMODE	equ 0x00003000
SCRIPTPROP_STRINGCOMPAREINSTANCE equ 0x00003001

SCRIPTPROP_INVOKEVERSIONING equ 0x00004000

SCRIPTPROP_HACK_FIBERSUPPORT equ 0x70000000
SCRIPTPROP_HACK_TRIDENTEVENTSINK equ 0x70000001
SCRIPTPROP_ABBREVIATE_GLOBALNAME_RESOLUTION equ 0x70000002

SCRIPTLANGUAGEVERSION typedef SDWORD
SCRIPTLANGUAGEVERSION_DEFAULT equ 0
SCRIPTLANGUAGEVERSION_5_7 equ 1
SCRIPTLANGUAGEVERSION_5_8 equ 2
SCRIPTLANGUAGEVERSION_MAX equ 255

SCRIPTSTATE	     typedef SDWORD
SCRIPTSTATE_UNINITIALIZED equ 0
SCRIPTSTATE_INITIALIZED equ 5
SCRIPTSTATE_STARTED	equ 1
SCRIPTSTATE_CONNECTED	equ 2
SCRIPTSTATE_DISCONNECTED equ 3
SCRIPTSTATE_CLOSED	equ 4

SCRIPTTRACEINFO	     typedef SDWORD
SCRIPTTRACEINFO_SCRIPTSTART equ 0
SCRIPTTRACEINFO_SCRIPTEND equ 1
SCRIPTTRACEINFO_COMCALLSTART equ 2
SCRIPTTRACEINFO_COMCALLEND equ 3
SCRIPTTRACEINFO_CREATEOBJSTART equ 4
SCRIPTTRACEINFO_CREATEOBJEND equ 5
SCRIPTTRACEINFO_GETOBJSTART equ 6
SCRIPTTRACEINFO_GETOBJEND equ 7

SCRIPTTHREADSTATE    typedef SDWORD
SCRIPTTHREADSTATE_NOTINSCRIPT equ 0
SCRIPTTHREADSTATE_RUNNING equ 1

SCRIPTGCTYPE	     typedef SDWORD
SCRIPTGCTYPE_NORMAL	equ 0
SCRIPTGCTYPE_EXHAUSTIVE equ 1

SCRIPTUICITEM	     typedef SDWORD
SCRIPTUICITEM_INPUTBOX	equ 1
SCRIPTUICITEM_MSGBOX	equ 2

SCRIPTUICHANDLING    typedef SDWORD
SCRIPTUICHANDLING_ALLOW equ 0
SCRIPTUICHANDLING_NOUIERROR equ 1
SCRIPTUICHANDLING_NOUIDEFAULT equ 2

SCRIPTTHREADID		typedef DWORD

SCRIPTTHREADID_CURRENT	equ (-1)
SCRIPTTHREADID_BASE	equ (-2)
SCRIPTTHREADID_ALL	equ (-3)

ifndef __IActiveScriptSite_INTERFACE_DEFINED__
__IActiveScriptSite_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptSite : public IUnknown

    GetLCID		proc :ptr
    GetItemInfo		proc :LPCOLESTR, :DWORD, :ptr, :ptr
    GetDocVersionString proc :ptr
    OnScriptTerminate	proc :ptr, :ptr
    OnStateChange	proc :SCRIPTSTATE
    OnScriptError	proc :ptr
    OnEnterScript	proc
    OnLeaveScript	proc

    .ends

endif

ifndef __IActiveScriptError_INTERFACE_DEFINED__
__IActiveScriptError_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptError : public IUnknown

    GetExceptionInfo	proc :ptr
    GetSourcePosition	proc :ptr, :ptr, :ptr
    GetSourceLineText	proc :ptr

    .ends

endif

ifndef __IActiveScriptError64_INTERFACE_DEFINED__
__IActiveScriptError64_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptError64 : public IActiveScriptError

    GetSourcePosition64 proc :ptr, :ptr, :ptr

    .ends

endif

ifndef __IActiveScriptSiteWindow_INTERFACE_DEFINED__
__IActiveScriptSiteWindow_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptSiteWindow : public IUnknown

    GetWindow		proc :ptr
    EnableModeless	proc :BOOL

    .ends

endif

ifndef __IActiveScriptSiteUIControl_INTERFACE_DEFINED__
__IActiveScriptSiteUIControl_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptSiteUIControl : public IUnknown

    GetUIBehavior	proc :SCRIPTUICITEM, :ptr

    .ends

endif

ifndef __IActiveScriptSiteInterruptPoll_INTERFACE_DEFINED__
__IActiveScriptSiteInterruptPoll_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptSiteInterruptPoll : public IUnknown

    QueryContinue	proc

    .ends

endif

ifndef __IActiveScript_INTERFACE_DEFINED__
__IActiveScript_INTERFACE_DEFINED__ equ 1

.comdef IActiveScript : public IUnknown

    SetScriptSite	proc :ptr
    GetScriptSite	proc :REFIID, :ptr
    SetScriptState	proc :SCRIPTSTATE
    GetScriptState	proc :ptr
    Close		proc
    AddNamedItem	proc :LPCOLESTR, :DWORD
    AddTypeLib		proc :REFGUID, :DWORD, :DWORD, :DWORD
    GetScriptDispatch	proc :LPCOLESTR, :ptr
    GetCurrentScriptThreadID proc :ptr
    GetScriptThreadID	proc :DWORD, :ptr
    GetScriptThreadState proc :SCRIPTTHREADID, :ptr
    InterruptScriptThread proc :SCRIPTTHREADID, :ptr, :DWORD
    Clone		proc :ptr

    .ends

endif

ifndef __IActiveScriptParse32_INTERFACE_DEFINED__
__IActiveScriptParse32_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParse32 : public IUnknown

    InitNew		proc
    AddScriptlet	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr, :ptr
    ParseScriptText	proc :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr, :ptr

    .ends

endif

ifndef __IActiveScriptParse64_INTERFACE_DEFINED__
__IActiveScriptParse64_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParse64 : public IUnknown

    InitNew		proc
    AddScriptlet	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr, :ptr
    ParseScriptText	proc :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr, :ptr

    .ends

endif

ifdef _WIN64
IActiveScriptParse	equ <IActiveScriptParse64>
IID_IActiveScriptParse	equ <IID_IActiveScriptParse64>
else
IActiveScriptParse	equ <IActiveScriptParse32>
IID_IActiveScriptParse	equ <IID_IActiveScriptParse32>
endif
PIActiveScriptParse	typedef ptr IActiveScriptParse

ifndef __IActiveScriptParseProcedureOld32_INTERFACE_DEFINED__
__IActiveScriptParseProcedureOld32_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParseProcedureOld32 : public IUnknown

    ParseProcedureText	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr

    .ends

endif

ifndef __IActiveScriptParseProcedureOld64_INTERFACE_DEFINED__
__IActiveScriptParseProcedureOld64_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParseProcedureOld64 : public IUnknown

    ParseProcedureText	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr

    .ends

endif

ifdef _WIN64
IActiveScriptParseProcedureOld equ <IActiveScriptParseProcedureOld64>
IID_IActiveScriptParseProcedureOld equ <IID_IActiveScriptParseProcedureOld64>
else
IActiveScriptParseProcedureOld equ <IActiveScriptParseProcedureOld32>
IID_IActiveScriptParseProcedureOld equ <IID_IActiveScriptParseProcedureOld32>
endif
PIActiveScriptParseProcedureOld typedef ptr IActiveScriptParseProcedureOld

ifndef __IActiveScriptParseProcedure32_INTERFACE_DEFINED__
__IActiveScriptParseProcedure32_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParseProcedure32 : public IUnknown

    ParseProcedureText	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr

    .ends

endif

ifndef __IActiveScriptParseProcedure64_INTERFACE_DEFINED__
__IActiveScriptParseProcedure64_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParseProcedure64 : public IUnknown

    ParseProcedureText	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr

    .ends

endif

ifdef _WIN64
IActiveScriptParseProcedure equ <IActiveScriptParseProcedure64>
IID_IActiveScriptParseProcedure equ <IID_IActiveScriptParseProcedure64>
else
IActiveScriptParseProcedure equ <IActiveScriptParseProcedure32>
IID_IActiveScriptParseProcedure equ <IID_IActiveScriptParseProcedure32>
endif
PIActiveScriptParseProcedure typedef ptr IActiveScriptParseProcedure

ifndef __IActiveScriptParseProcedure2_32_INTERFACE_DEFINED__
__IActiveScriptParseProcedure2_32_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParseProcedure2_32 : public IActiveScriptParseProcedure32

    .ends

endif

ifndef __IActiveScriptParseProcedure2_64_INTERFACE_DEFINED__
__IActiveScriptParseProcedure2_64_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptParseProcedure2_64 : public IActiveScriptParseProcedure64

    .ends

endif

ifdef _WIN64
IActiveScriptParseProcedure2 equ <IActiveScriptParseProcedure2_64>
IID_IActiveScriptParseProcedure2 equ <IID_IActiveScriptParseProcedure2_64>
else
IActiveScriptParseProcedure2 equ <IActiveScriptParseProcedure2_32>
IID_IActiveScriptParseProcedure2 equ <IID_IActiveScriptParseProcedure2_32>
endif
PIActiveScriptParseProcedure2 typedef ptr IActiveScriptParseProcedure2

ifndef __IActiveScriptEncode_INTERFACE_DEFINED__
__IActiveScriptEncode_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptEncode : public IUnknown

    EncodeSection	proc :LPCOLESTR, :DWORD, :LPOLESTR, :DWORD, :ptr
    DecodeScript	proc :LPCOLESTR, :DWORD, :LPOLESTR, :DWORD, :ptr
    GetEncodeProgId	proc :ptr

    .ends

endif

ifndef __IActiveScriptHostEncode_INTERFACE_DEFINED__
__IActiveScriptHostEncode_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptHostEncode : public IUnknown

    EncodeScriptHostFile proc :BSTR, :ptr, :sdword, :BSTR

    .ends

endif

ifndef __IBindEventHandler_INTERFACE_DEFINED__
__IBindEventHandler_INTERFACE_DEFINED__ equ 1

.comdef IBindEventHandler : public IUnknown

    BindHandler		proc :LPCOLESTR, :ptr

    .ends

endif

ifndef __IActiveScriptStats_INTERFACE_DEFINED__
__IActiveScriptStats_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptStats : public IUnknown

    GetStat		proc :DWORD, :ptr, :ptr
    GetStatEx		proc :REFGUID, :ptr, :ptr
    ResetStats		proc

    .ends

endif

ifndef __IActiveScriptProperty_INTERFACE_DEFINED__
__IActiveScriptProperty_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptProperty : public IUnknown

    GetProperty		proc :DWORD, :ptr, :ptr
    SetProperty		proc :DWORD, :ptr, :ptr

    .ends

endif

ifndef __ITridentEventSink_INTERFACE_DEFINED__
__ITridentEventSink_INTERFACE_DEFINED__ equ 1

.comdef ITridentEventSink : public IUnknown

    FireEvent		proc :LPCOLESTR, :ptr, :ptr, :ptr

    .ends

endif

ifndef __IActiveScriptGarbageCollector_INTERFACE_DEFINED__
__IActiveScriptGarbageCollector_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptGarbageCollector : public IUnknown

    CollectGarbage	proc :SCRIPTGCTYPE

    .ends

endif

ifndef __IActiveScriptSIPInfo_INTERFACE_DEFINED__
__IActiveScriptSIPInfo_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptSIPInfo : public IUnknown

    GetSIPOID		proc :ptr

    .ends

endif

ifndef __IActiveScriptSiteTraceInfo_INTERFACE_DEFINED__
__IActiveScriptSiteTraceInfo_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptSiteTraceInfo : public IUnknown

    SendScriptTraceInfo proc :SCRIPTTRACEINFO, :GUID, :DWORD, :LONG, :LONG, :DWORD64

    .ends

endif

ifndef __IActiveScriptTraceInfo_INTERFACE_DEFINED__
__IActiveScriptTraceInfo_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptTraceInfo : public IUnknown

    StartScriptTracing	proc :ptr, :GUID
    StopScriptTracing	proc

    .ends

endif

ifndef __IActiveScriptStringCompare_INTERFACE_DEFINED__
__IActiveScriptStringCompare_INTERFACE_DEFINED__ equ 1

.comdef IActiveScriptStringCompare : public IUnknown

    StrComp		proc :BSTR, :BSTR, :ptr

    .ends

endif

endif  ;; __ActivScp_h

;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HWND_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND


;DWORD
VARIANT_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr VARIANT

;LPSTR
VARIANT_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;LPSTR
VARIANT_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr VARIANT


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HWND_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND


;DWORD
VARIANT_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr VARIANT

;LPSTR
VARIANT_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;LPSTR
VARIANT_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr VARIANT

endif
.pragma list(pop)
