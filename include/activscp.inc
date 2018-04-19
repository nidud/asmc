

;; this ALWAYS GENERATED file contains the definitions for the interfaces 


;; File created by MIDL compiler version 7.00.0555 
;; Compiler settings for activscp.idl:
W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 Oicf, ?
: dce , ms_ext, c_ext, robust protocol ?
checks: allocation ref bounds_check enum stub_data error ?
__declspec() decoration level: VC ?
__declspec(selectany), __declspec(novtable) __declspec(uuid()), ?
MIDL_INTERFACE()        DECLSPEC_UUID(), ?
;;
;; @@MIDL_FILE_HEADING(  ) 

pragma warning( disable: 4049 )  ;; more than 64k source lines 


;; verify that the <rpcndr.h> version is high enough to compile this file
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
endif

;; verify that the <rpcsal.h> version is high enough to compile this file
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
error this stub requires an updated version of LT rpcndr.h GT 
endif ;; __RPCNDR_H_VERSION__

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif ;;COM_NO_WINDOWS_H

ifndef __activscp_h__
__activscp_h__ equ 1

if defined(_MSC_VER) AND (_MSC_VER GE 1020)
pragma once
endif

;; Forward Declarations 

ifndef __IActiveScriptSite_FWD_DEFINED__
__IActiveScriptSite_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptSite_FWD_DEFINED__ 


ifndef __IActiveScriptError_FWD_DEFINED__
__IActiveScriptError_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptError_FWD_DEFINED__ 


ifndef __IActiveScriptError64_FWD_DEFINED__
__IActiveScriptError64_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptError64_FWD_DEFINED__ 


ifndef __IActiveScriptSiteWindow_FWD_DEFINED__
__IActiveScriptSiteWindow_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptSiteWindow_FWD_DEFINED__ 


ifndef __IActiveScriptSiteUIControl_FWD_DEFINED__
__IActiveScriptSiteUIControl_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptSiteUIControl_FWD_DEFINED__ 


ifndef __IActiveScriptSiteInterruptPoll_FWD_DEFINED__
__IActiveScriptSiteInterruptPoll_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptSiteInterruptPoll_FWD_DEFINED__ 


ifndef __IActiveScript_FWD_DEFINED__
__IActiveScript_FWD_DEFINED__ equ 1
endif 	;; __IActiveScript_FWD_DEFINED__ 


ifndef __IActiveScriptParse32_FWD_DEFINED__
__IActiveScriptParse32_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParse32_FWD_DEFINED__ 


ifndef __IActiveScriptParse64_FWD_DEFINED__
__IActiveScriptParse64_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParse64_FWD_DEFINED__ 


ifndef __IActiveScriptParseProcedureOld32_FWD_DEFINED__
__IActiveScriptParseProcedureOld32_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParseProcedureOld32_FWD_DEFINED__ 


ifndef __IActiveScriptParseProcedureOld64_FWD_DEFINED__
__IActiveScriptParseProcedureOld64_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParseProcedureOld64_FWD_DEFINED__ 


ifndef __IActiveScriptParseProcedure32_FWD_DEFINED__
__IActiveScriptParseProcedure32_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParseProcedure32_FWD_DEFINED__ 


ifndef __IActiveScriptParseProcedure64_FWD_DEFINED__
__IActiveScriptParseProcedure64_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParseProcedure64_FWD_DEFINED__ 


ifndef __IActiveScriptParseProcedure2_32_FWD_DEFINED__
__IActiveScriptParseProcedure2_32_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParseProcedure2_32_FWD_DEFINED__ 


ifndef __IActiveScriptParseProcedure2_64_FWD_DEFINED__
__IActiveScriptParseProcedure2_64_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptParseProcedure2_64_FWD_DEFINED__ 


ifndef __IActiveScriptEncode_FWD_DEFINED__
__IActiveScriptEncode_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptEncode_FWD_DEFINED__ 


ifndef __IActiveScriptHostEncode_FWD_DEFINED__
__IActiveScriptHostEncode_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptHostEncode_FWD_DEFINED__ 


ifndef __IBindEventHandler_FWD_DEFINED__
__IBindEventHandler_FWD_DEFINED__ equ 1
endif 	;; __IBindEventHandler_FWD_DEFINED__ 


ifndef __IActiveScriptStats_FWD_DEFINED__
__IActiveScriptStats_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptStats_FWD_DEFINED__ 


ifndef __IActiveScriptProperty_FWD_DEFINED__
__IActiveScriptProperty_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptProperty_FWD_DEFINED__ 


ifndef __ITridentEventSink_FWD_DEFINED__
__ITridentEventSink_FWD_DEFINED__ equ 1
endif 	;; __ITridentEventSink_FWD_DEFINED__ 


ifndef __IActiveScriptGarbageCollector_FWD_DEFINED__
__IActiveScriptGarbageCollector_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptGarbageCollector_FWD_DEFINED__ 


ifndef __IActiveScriptSIPInfo_FWD_DEFINED__
__IActiveScriptSIPInfo_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptSIPInfo_FWD_DEFINED__ 


ifndef __IActiveScriptSiteTraceInfo_FWD_DEFINED__
__IActiveScriptSiteTraceInfo_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptSiteTraceInfo_FWD_DEFINED__ 


ifndef __IActiveScriptTraceInfo_FWD_DEFINED__
__IActiveScriptTraceInfo_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptTraceInfo_FWD_DEFINED__ 


ifndef __IActiveScriptStringCompare_FWD_DEFINED__
__IActiveScriptStringCompare_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptStringCompare_FWD_DEFINED__ 


;; header files for imported files 
include ocidl.inc

ifdef __cplusplus
externdef               
endif


;; interface __MIDL_itf_activscp_0000_0000 
;; [local] 

;;=--------------------------------------------------------------------------=
;; ActivScp.h
;;=--------------------------------------------------------------------------=
;; (C) Copyright Microsoft Corporation.  All Rights Reserved.
;;
;; THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
;; ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
;; THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
;; PARTICULAR PURPOSE.
;;=--------------------------------------------------------------------------=
;;
pragma comment(lib,"uuid.lib")
;;
;; Declarations for ActiveX Scripting host applications and script engines.
;;

ifndef __ActivScp_h
__ActivScp_h equ 1

;; GUIDs
;;******

ifndef _NO_SCRIPT_GUIDS
;; {F0B7A1A1-9847-11cf-8F20-00805F2CD064}
DEFINE_GUID(CATID_ActiveScript, 0xf0b7a1a1, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

;; {F0B7A1A2-9847-11cf-8F20-00805F2CD064}
DEFINE_GUID(CATID_ActiveScriptParse, 0xf0b7a1a2, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

;; {F0B7A1A3-9847-11cf-8F20-00805F2CD064}
DEFINE_GUID(CATID_ActiveScriptEncode, 0xf0b7a1a3, 0x9847, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

;; {BB1A2AE1-A4F9-11cf-8F20-00805F2CD064}
DEFINE_GUID(IID_IActiveScript, 0xbb1a2ae1, 0xa4f9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

;; {BB1A2AE2-A4F9-11cf-8F20-00805F2CD064}
DEFINE_GUID(IID_IActiveScriptParse32, 0xbb1a2ae2, 0xa4f9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
;; {C7EF7658-E1EE-480E-97EA-D52CB4D76D17}
DEFINE_GUID(IID_IActiveScriptParse64, 0xc7ef7658, 0xe1ee, 0x480e, 0x97, 0xea, 0xd5, 0x2c, 0xb4, 0xd7, 0x6d, 0x17);

;; {BB1A2AE3-A4F9-11cf-8F20-00805F2CD064}
DEFINE_GUID(IID_IActiveScriptEncode, 0xbb1a2ae3, 0xa4f9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

;; {BEE9B76E-CFE3-11d1-B747-00C04FC2B085}
DEFINE_GUID(IID_IActiveScriptHostEncode, 0xbee9b76e, 0xcfe3, 0x11d1, 0xb7, 0x47, 0x00, 0xc0, 0x4f, 0xc2, 0xb0, 0x85);

;; {1CFF0050-6FDD-11d0-9328-00A0C90DCAA9}
DEFINE_GUID(IID_IActiveScriptParseProcedureOld32, 0x1cff0050, 0x6fdd, 0x11d0, 0x93, 0x28, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);
;; {21F57128-08C9-4638-BA12-22D15D88DC5C}
DEFINE_GUID(IID_IActiveScriptParseProcedureOld64, 0x21f57128, 0x08c9, 0x4638, 0xba, 0x12, 0x22, 0xd1, 0x5d, 0x88, 0xdc, 0x5c);

;; {AA5B6A80-B834-11d0-932F-00A0C90DCAA9}
DEFINE_GUID(IID_IActiveScriptParseProcedure32, 0xaa5b6a80, 0xb834, 0x11d0, 0x93, 0x2f, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);
;; {C64713B6-E029-4CC5-9200-438B72890B6A}
DEFINE_GUID(IID_IActiveScriptParseProcedure64, 0xc64713b6, 0xe029, 0x4cc5, 0x92, 0x00, 0x43, 0x8b, 0x72, 0x89, 0x0b, 0x6a);

;; {71EE5B20-FB04-11d1-B3A8-00A0C911E8B2}
DEFINE_GUID(IID_IActiveScriptParseProcedure2_32, 0x71ee5b20, 0xfb04, 0x11d1, 0xb3, 0xa8, 0x00, 0xa0, 0xc9, 0x11, 0xe8, 0xb2);
;; {FE7C4271-210C-448D-9F54-76DAB7047B28}
DEFINE_GUID(IID_IActiveScriptParseProcedure2_64, 0xfe7c4271, 0x210c, 0x448d, 0x9f, 0x54, 0x76, 0xda, 0xb7, 0x04, 0x7b, 0x28);

;; {DB01A1E3-A42B-11cf-8F20-00805F2CD064}
DEFINE_GUID(IID_IActiveScriptSite, 0xdb01a1e3, 0xa42b, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

;; {4B7272AE-1955-4bfe-98B0-780621888569}
DEFINE_GUID(IID_IActiveScriptSiteTraceInfo, 0x4b7272ae, 0x1955, 0x4bfe, 0x98, 0xb0, 0x78, 0x6, 0x21, 0x88, 0x85, 0x69);

;; {D10F6761-83E9-11cf-8F20-00805F2CD064}
DEFINE_GUID(IID_IActiveScriptSiteWindow, 0xd10f6761, 0x83e9, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);

;; {539698A0-CDCA-11CF-A5EB-00AA0047A063}
DEFINE_GUID(IID_IActiveScriptSiteInterruptPoll, 0x539698a0, 0xcdca, 0x11cf, 0xa5, 0xeb, 0x00, 0xaa, 0x00, 0x47, 0xa0, 0x63);

;; {AEDAE97E-D7EE-4796-B960-7F092AE844AB}
DEFINE_GUID(IID_IActiveScriptSiteUIControl, 0xaedae97e, 0xd7ee, 0x4796, 0xb9, 0x60, 0x7f, 0x9, 0x2a, 0xe8, 0x44, 0xab);

;; {EAE1BA61-A4ED-11cf-8F20-00805F2CD064}
DEFINE_GUID(IID_IActiveScriptError,   0xeae1ba61, 0xa4ed, 0x11cf, 0x8f, 0x20, 0x00, 0x80, 0x5f, 0x2c, 0xd0, 0x64);
;; {B21FB2A1-5B8F-4963-8C21-21450F84ED7F}
DEFINE_GUID(IID_IActiveScriptError64, 0xb21fb2a1, 0x5b8f, 0x4963, 0x8c, 0x21, 0x21, 0x45, 0x0f, 0x84, 0xed, 0x7f);

;; {63CDBCB0-C1B1-11d0-9336-00A0C90DCAA9}
DEFINE_GUID(IID_IBindEventHandler, 0x63cdbcb0, 0xc1b1, 0x11d0, 0x93, 0x36, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);

;; {B8DA6310-E19B-11d0-933C-00A0C90DCAA9}
DEFINE_GUID(IID_IActiveScriptStats, 0xb8da6310, 0xe19b, 0x11d0, 0x93, 0x3c, 0x00, 0xa0, 0xc9, 0x0d, 0xca, 0xa9);

;; {4954E0D0-FBC7-11D1-8410-006008C3FBFC}
DEFINE_GUID(IID_IActiveScriptProperty, 0x4954E0D0, 0xFBC7, 0x11D1, 0x84, 0x10, 0x00, 0x60, 0x08, 0xC3, 0xFB, 0xFC);

;; {1DC9CA50-06EF-11d2-8415-006008C3FBFC}
DEFINE_GUID(IID_ITridentEventSink, 0x1dc9ca50, 0x6ef, 0x11d2, 0x84, 0x15, 0x00, 0x60, 0x08, 0xc3, 0xfb, 0xfc);

;; {6AA2C4A0-2B53-11d4-A2A0-00104BD35090}
DEFINE_GUID(IID_IActiveScriptGarbageCollector, 0x6aa2c4a0, 0x2b53, 0x11d4, 0xa2, 0xa0, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);

;; {764651D0-38DE-11d4-A2A3-00104BD35090}
DEFINE_GUID(IID_IActiveScriptSIPInfo, 0x764651d0, 0x38de, 0x11d4, 0xa2, 0xa3, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);

;; {C35456E7-BEBF-4a1b-86A9-24D56BE8B369}
DEFINE_GUID(IID_IActiveScriptTraceInfo, 0xC35456E7, 0xBEBF, 0x4a1b, 0x86, 0xA9, 0x24, 0xD5, 0x6B, 0xE8, 0xB3, 0x69);

;; {1629F04E-2799-4db5-8FE5-ACE10F17EBAB}
DEFINE_GUID(OID_VBSSIP, 0x1629f04e, 0x2799, 0x4db5, 0x8f, 0xe5, 0xac, 0xe1, 0x0f, 0x17, 0xeb, 0xab);

;; {06C9E010-38CE-11d4-A2A3-00104BD35090}
DEFINE_GUID(OID_JSSIP,  0x6c9e010, 0x38ce, 0x11d4, 0xa2, 0xa3, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);

;; {1A610570-38CE-11d4-A2A3-00104BD35090}
DEFINE_GUID(OID_WSFSIP, 0x1a610570, 0x38ce, 0x11d4, 0xa2, 0xa3, 0x00, 0x10, 0x4b, 0xd3, 0x50, 0x90);

;; {58562769-ED52-42f7-8403-4963514E1F11}
DEFINE_GUID(IID_IActiveScriptStringCompare, 0x58562769, 0xED52, 0x42f7, 0x84, 0x03, 0x49, 0x63, 0x51, 0x4E, 0x1F, 0x11);

endif ;; _NO_SCRIPT_GUIDS

;; Constants used by ActiveX Scripting:
;;

;; IActiveScript::AddNamedItem() input flags 

SCRIPTITEM_ISVISIBLE    equ 0x00000002
SCRIPTITEM_ISSOURCE     equ 0x00000004
SCRIPTITEM_GLOBALMEMBERS equ 0x00000008
SCRIPTITEM_ISPERSISTENT equ 0x00000040
SCRIPTITEM_CODEONLY     equ 0x00000200
SCRIPTITEM_NOCODE       equ 0x00000400

SCRIPTITEM_ALL_FLAGS    equ (SCRIPTITEM_ISSOURCE OR \
| \                     SCRIPTITEM_ISVISIBLE ?
| \                     SCRIPTITEM_ISPERSISTENT ?
| \                     SCRIPTITEM_GLOBALMEMBERS ?
| \                     SCRIPTITEM_NOCODE ?

;; IActiveScript::AddTypeLib() input flags 

SCRIPTTYPELIB_ISCONTROL equ 0x00000010
SCRIPTTYPELIB_ISPERSISTENT equ 0x00000040
SCRIPTTYPELIB_ALL_FLAGS equ (SCRIPTTYPELIB_ISCONTROL OR SCRIPTTYPELIB_ISPERSISTENT)

;; IActiveScriptParse::AddScriptlet() and IActiveScriptParse::ParseScriptText() input flags 

SCRIPTTEXT_DELAYEXECUTION equ 0x00000001
SCRIPTTEXT_ISVISIBLE    equ 0x00000002
SCRIPTTEXT_ISEXPRESSION equ 0x00000020
SCRIPTTEXT_ISPERSISTENT equ 0x00000040
SCRIPTTEXT_HOSTMANAGESSOURCE equ 0x00000080
SCRIPTTEXT_ISXDOMAIN    equ 0x00000100
SCRIPTTEXT_ALL_FLAGS    equ (SCRIPTTEXT_DELAYEXECUTION OR \
| \                     SCRIPTTEXT_ISVISIBLE ?
| \                     SCRIPTTEXT_ISEXPRESSION ?
| \                     SCRIPTTEXT_ISPERSISTENT ?
| \                     SCRIPTTEXT_HOSTMANAGESSOURCE ?

;; IActiveScriptParseProcedure::ParseProcedureText() input flags 

SCRIPTPROC_ISEXPRESSION equ 0x00000020
SCRIPTPROC_HOSTMANAGESSOURCE equ 0x00000080
SCRIPTPROC_IMPLICIT_THIS equ 0x00000100
SCRIPTPROC_IMPLICIT_PARENTS equ 0x00000200
SCRIPTPROC_ISXDOMAIN    equ 0x00000400
SCRIPTPROC_ALL_FLAGS    equ (SCRIPTPROC_HOSTMANAGESSOURCE OR \
| \                     SCRIPTPROC_ISEXPRESSION ?
| \                     SCRIPTPROC_IMPLICIT_THIS ?
| \                     SCRIPTPROC_IMPLICIT_PARENTS ?

;; IActiveScriptSite::GetItemInfo() input flags 

SCRIPTINFO_IUNKNOWN     equ 0x00000001
SCRIPTINFO_ITYPEINFO    equ 0x00000002
SCRIPTINFO_ALL_FLAGS    equ (SCRIPTINFO_IUNKNOWN OR \

;; IActiveScript::Interrupt() Flags 

SCRIPTINTERRUPT_DEBUG   equ 0x00000001
SCRIPTINTERRUPT_RAISEEXCEPTION equ 0x00000002
SCRIPTINTERRUPT_ALL_FLAGS equ (SCRIPTINTERRUPT_DEBUG OR \

;; IActiveScriptStats::GetStat() values 

SCRIPTSTAT_STATEMENT_COUNT equ 1
SCRIPTSTAT_INSTRUCTION_COUNT equ 2
SCRIPTSTAT_INTSTRUCTION_TIME equ 3
SCRIPTSTAT_TOTAL_TIME   equ 4

;; IActiveScriptEncode::AddSection() input flags 

SCRIPT_ENCODE_SECTION   equ 0x00000001

SCRIPT_ENCODE_DEFAULT_LANGUAGE equ 0x00000001
SCRIPT_ENCODE_NO_ASP_LANGUAGE equ 0x00000002

;; Properties for IActiveScriptProperty 
SCRIPTPROP_NAME         equ 0x00000000
SCRIPTPROP_MAJORVERSION equ 0x00000001
SCRIPTPROP_MINORVERSION equ 0x00000002
SCRIPTPROP_BUILDNUMBER  equ 0x00000003

SCRIPTPROP_DELAYEDEVENTSINKING equ 0x00001000
SCRIPTPROP_CATCHEXCEPTION equ 0x00001001
SCRIPTPROP_CONVERSIONLCID equ 0x00001002
SCRIPTPROP_HOSTSTACKREQUIRED equ 0x00001003

SCRIPTPROP_DEBUGGER     equ 0x00001100
SCRIPTPROP_JITDEBUG     equ 0x00001101

SCRIPTPROP_GCCONTROLSOFTCLOSE equ 0x00002000

SCRIPTPROP_INTEGERMODE  equ 0x00003000
SCRIPTPROP_STRINGCOMPAREINSTANCE equ 0x00003001

SCRIPTPROP_INVOKEVERSIONING equ 0x00004000

;; These properties are defined and available, but are not
;; officially supported.
SCRIPTPROP_HACK_FIBERSUPPORT equ 0x70000000
SCRIPTPROP_HACK_TRIDENTEVENTSINK equ 0x70000001
SCRIPTPROP_ABBREVIATE_GLOBALNAME_RESOLUTION equ 0x70000002


;; script language version values for SCRIPTPROP_INVOKEVERSIONING property 

tagSCRIPTLANGUAGEVERSION typedef SDWORD
SCRIPTLANGUAGEVERSION_DEFAULT equ 0
SCRIPTLANGUAGEVERSION_5_7 equ 1
SCRIPTLANGUAGEVERSION_5_8 equ 2
SCRIPTLANGUAGEVERSION_MAX equ 255

tagSCRIPTSTATE          typedef SDWORD
SCRIPTSTATE_UNINITIALIZED equ 0
SCRIPTSTATE_INITIALIZED equ 5
SCRIPTSTATE_STARTED     equ 1
SCRIPTSTATE_CONNECTED   equ 2
SCRIPTSTATE_DISCONNECTED equ 3
SCRIPTSTATE_CLOSED      equ 4

tagSCRIPTTRACEINFO      typedef SDWORD
SCRIPTTRACEINFO_SCRIPTSTART equ 0
SCRIPTTRACEINFO_SCRIPTEND equ 1
SCRIPTTRACEINFO_COMCALLSTART equ 2
SCRIPTTRACEINFO_COMCALLEND equ 3
SCRIPTTRACEINFO_CREATEOBJSTART equ 4
SCRIPTTRACEINFO_CREATEOBJEND equ 5
SCRIPTTRACEINFO_GETOBJSTART equ 6
SCRIPTTRACEINFO_GETOBJEND equ 7


;; script thread state values 

tagSCRIPTTHREADSTATE    typedef SDWORD
SCRIPTTHREADSTATE_NOTINSCRIPT equ 0
SCRIPTTHREADSTATE_RUNNING equ 1


;; IActiveScriptCollectGarbage constants 

tagSCRIPTGCTYPE         typedef SDWORD
SCRIPTGCTYPE_NORMAL     equ 0
SCRIPTGCTYPE_EXHAUSTIVE equ 1


;; IActiveScriptSiteUIControl constants

tagSCRIPTUICITEM        typedef SDWORD
SCRIPTUICITEM_INPUTBOX  equ 1
SCRIPTUICITEM_MSGBOX    equ 2


tagSCRIPTUICHANDLING    typedef SDWORD
SCRIPTUICHANDLING_ALLOW equ 0
SCRIPTUICHANDLING_NOUIERROR equ 1
SCRIPTUICHANDLING_NOUIDEFAULT equ 2


;; Thread IDs 

SCRIPTTHREADID          typedef DWORD 


SCRIPTTHREADID_CURRENT  equ ((SCRIPTTHREADID)-1)
SCRIPTTHREADID_BASE     equ ((SCRIPTTHREADID)-2)
SCRIPTTHREADID_ALL      equ ((SCRIPTTHREADID)-3)

;; Structures 

;; Interfaces
;;***********




























externdef               __MIDL_itf_activscp_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activscp_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActiveScriptSite_INTERFACE_DEFINED__
__IActiveScriptSite_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptSite 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptSite:IID


.comdef IActiveScriptSite

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetLCID             proc :ptr
    GetItemInfo         proc :LPCOLESTR, :DWORD, :ptr, :ptr
    GetDocVersionString proc :ptr
    OnScriptTerminate   proc :const, :const
    OnStateChange       proc :SCRIPTSTATE
    OnScriptError       proc :ptr
    OnEnterScript       proc 
    OnLeaveScript       proc 
    .ends

                        ENDS







endif 	;; __IActiveScriptSite_INTERFACE_DEFINED__ 


ifndef __IActiveScriptError_INTERFACE_DEFINED__
__IActiveScriptError_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptError 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptError:IID


.comdef IActiveScriptError

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetExceptionInfo    proc :ptr
    GetSourcePosition   proc :ptr, :ptr, :ptr
    GetSourceLineText   proc :ptr
    .ends

                        ENDS






;; [call_as] 
 This,                  LPIActiveScriptError ?
;; [out] 


;void
IActiveScriptError_RemoteGetExceptionInfo_Stub proto WINAPI \
                  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
          _pRpcMessage: PRPC_MESSAGE,
         _pdwStubPhase: ptr DWORD




endif 	;; __IActiveScriptError_INTERFACE_DEFINED__ 


ifndef __IActiveScriptError64_INTERFACE_DEFINED__
__IActiveScriptError64_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptError64 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptError64:IID


.comdef IActiveScriptError64

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetExceptionInfo    proc :ptr
    GetSourcePosition   proc :ptr, :ptr, :ptr
    GetSourceLineText   proc :ptr
    GetSourcePosition64 proc :ptr, :ptr, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptError64_INTERFACE_DEFINED__ 


ifndef __IActiveScriptSiteWindow_INTERFACE_DEFINED__
__IActiveScriptSiteWindow_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptSiteWindow 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptSiteWindow:IID


.comdef IActiveScriptSiteWindow

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetWindow           proc :ptr
    EnableModeless      proc :BOOL
    .ends

                        ENDS







endif 	;; __IActiveScriptSiteWindow_INTERFACE_DEFINED__ 


ifndef __IActiveScriptSiteUIControl_INTERFACE_DEFINED__
__IActiveScriptSiteUIControl_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptSiteUIControl 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptSiteUIControl:IID


.comdef IActiveScriptSiteUIControl

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetUIBehavior       proc :SCRIPTUICITEM, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptSiteUIControl_INTERFACE_DEFINED__ 


ifndef __IActiveScriptSiteInterruptPoll_INTERFACE_DEFINED__
__IActiveScriptSiteInterruptPoll_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptSiteInterruptPoll 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptSiteInterruptPoll:IID


.comdef IActiveScriptSiteInterruptPoll

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    QueryContinue       proc 
    .ends

                        ENDS







endif 	;; __IActiveScriptSiteInterruptPoll_INTERFACE_DEFINED__ 


ifndef __IActiveScript_INTERFACE_DEFINED__
__IActiveScript_INTERFACE_DEFINED__ equ 1

;; interface IActiveScript 
;; [unique][uuid][object] 


externdef               IID_IActiveScript:IID


.comdef IActiveScript

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    SetScriptSite       proc :ptr
    GetScriptSite       proc :REFIID, :ptr
    SetScriptState      proc :SCRIPTSTATE
    GetScriptState      proc :ptr
    Close               proc 
    AddNamedItem        proc :LPCOLESTR, :DWORD
    AddTypeLib          proc :REFGUID, :DWORD, :DWORD, :DWORD
    GetScriptDispatch   proc :LPCOLESTR, :ptr
    GetCurrentScriptThreadID proc :ptr
    GetScriptThreadID   proc :DWORD, :ptr
    GetScriptThreadState proc :SCRIPTTHREADID, :ptr
    InterruptScriptThread proc :SCRIPTTHREADID, :const, :DWORD
    Clone               proc :ptr
    .ends

                        ENDS







endif 	;; __IActiveScript_INTERFACE_DEFINED__ 


ifndef __IActiveScriptParse32_INTERFACE_DEFINED__
__IActiveScriptParse32_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParse32 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParse32:IID


.comdef IActiveScriptParse32

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    InitNew             proc 
    AddScriptlet        proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr, :ptr
    ParseScriptText     proc :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParse32_INTERFACE_DEFINED__ 


ifndef __IActiveScriptParse64_INTERFACE_DEFINED__
__IActiveScriptParse64_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParse64 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParse64:IID


.comdef IActiveScriptParse64

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    InitNew             proc 
    AddScriptlet        proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr, :ptr
    ParseScriptText     proc :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParse64_INTERFACE_DEFINED__ 


;; interface __MIDL_itf_activscp_0000_0009 
;; [local] 

ifdef _WIN64
IActiveScriptParse      equ IActiveScriptParse64
IID_IActiveScriptParse  equ IID_IActiveScriptParse64
else
IActiveScriptParse      equ IActiveScriptParse32
IID_IActiveScriptParse  equ IID_IActiveScriptParse32
endif
PIActiveScriptParse     typedef ptr IActiveScriptParse



externdef               __MIDL_itf_activscp_0000_0009_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activscp_0000_0009_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActiveScriptParseProcedureOld32_INTERFACE_DEFINED__
__IActiveScriptParseProcedureOld32_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParseProcedureOld32 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParseProcedureOld32:IID


.comdef IActiveScriptParseProcedureOld32

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    ParseProcedureText  proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParseProcedureOld32_INTERFACE_DEFINED__ 


ifndef __IActiveScriptParseProcedureOld64_INTERFACE_DEFINED__
__IActiveScriptParseProcedureOld64_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParseProcedureOld64 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParseProcedureOld64:IID


.comdef IActiveScriptParseProcedureOld64

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    ParseProcedureText  proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParseProcedureOld64_INTERFACE_DEFINED__ 


;; interface __MIDL_itf_activscp_0000_0011 
;; [local] 

ifdef _WIN64
IActiveScriptParseProcedureOld equ IActiveScriptParseProcedureOld64
IID_IActiveScriptParseProcedureOld equ IID_IActiveScriptParseProcedureOld64
else
IActiveScriptParseProcedureOld equ IActiveScriptParseProcedureOld32
IID_IActiveScriptParseProcedureOld equ IID_IActiveScriptParseProcedureOld32
endif
PIActiveScriptParseProcedureOld typedef ptr IActiveScriptParseProcedureOld


externdef               __MIDL_itf_activscp_0000_0011_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activscp_0000_0011_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActiveScriptParseProcedure32_INTERFACE_DEFINED__
__IActiveScriptParseProcedure32_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParseProcedure32 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParseProcedure32:IID


.comdef IActiveScriptParseProcedure32

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    ParseProcedureText  proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParseProcedure32_INTERFACE_DEFINED__ 


ifndef __IActiveScriptParseProcedure64_INTERFACE_DEFINED__
__IActiveScriptParseProcedure64_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParseProcedure64 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParseProcedure64:IID


.comdef IActiveScriptParseProcedure64

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    ParseProcedureText  proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParseProcedure64_INTERFACE_DEFINED__ 


;; interface __MIDL_itf_activscp_0000_0013 
;; [local] 

ifdef _WIN64
IActiveScriptParseProcedure equ IActiveScriptParseProcedure64
IID_IActiveScriptParseProcedure equ IID_IActiveScriptParseProcedure64
else
IActiveScriptParseProcedure equ IActiveScriptParseProcedure32
IID_IActiveScriptParseProcedure equ IID_IActiveScriptParseProcedure32
endif
PIActiveScriptParseProcedure typedef ptr IActiveScriptParseProcedure


externdef               __MIDL_itf_activscp_0000_0013_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activscp_0000_0013_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActiveScriptParseProcedure2_32_INTERFACE_DEFINED__
__IActiveScriptParseProcedure2_32_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParseProcedure2_32 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParseProcedure2_32:IID


.comdef IActiveScriptParseProcedure2_32

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    ParseProcedureText  proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORD, :ULONG, :DWORD, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParseProcedure2_32_INTERFACE_DEFINED__ 


ifndef __IActiveScriptParseProcedure2_64_INTERFACE_DEFINED__
__IActiveScriptParseProcedure2_64_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptParseProcedure2_64 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptParseProcedure2_64:IID


.comdef IActiveScriptParseProcedure2_64

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    ParseProcedureText  proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr, :LPCOLESTR, :DWORDLONG, :ULONG, :DWORD, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptParseProcedure2_64_INTERFACE_DEFINED__ 


;; interface __MIDL_itf_activscp_0000_0015 
;; [local] 

ifdef _WIN64
IActiveScriptParseProcedure2 equ IActiveScriptParseProcedure2_64
IID_IActiveScriptParseProcedure2 equ IID_IActiveScriptParseProcedure2_64
else
IActiveScriptParseProcedure2 equ IActiveScriptParseProcedure2_32
IID_IActiveScriptParseProcedure2 equ IID_IActiveScriptParseProcedure2_32
endif
PIActiveScriptParseProcedure2 typedef ptr IActiveScriptParseProcedure2


externdef               __MIDL_itf_activscp_0000_0015_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activscp_0000_0015_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActiveScriptEncode_INTERFACE_DEFINED__
__IActiveScriptEncode_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptEncode 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptEncode:IID


.comdef IActiveScriptEncode

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    EncodeSection       proc :LPCOLESTR, :DWORD, :LPOLESTR, :DWORD, :ptr
    DecodeScript        proc :LPCOLESTR, :DWORD, :LPOLESTR, :DWORD, :ptr
    GetEncodeProgId     proc :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptEncode_INTERFACE_DEFINED__ 


ifndef __IActiveScriptHostEncode_INTERFACE_DEFINED__
__IActiveScriptHostEncode_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptHostEncode 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptHostEncode:IID


.comdef IActiveScriptHostEncode

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    EncodeScriptHostFile proc :BSTR, :ptr, :long, :BSTR
    .ends

                        ENDS







endif 	;; __IActiveScriptHostEncode_INTERFACE_DEFINED__ 


ifndef __IBindEventHandler_INTERFACE_DEFINED__
__IBindEventHandler_INTERFACE_DEFINED__ equ 1

;; interface IBindEventHandler 
;; [unique][uuid][object] 


externdef               IID_IBindEventHandler:IID


.comdef IBindEventHandler

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    BindHandler         proc :LPCOLESTR, :ptr
    .ends

                        ENDS







endif 	;; __IBindEventHandler_INTERFACE_DEFINED__ 


ifndef __IActiveScriptStats_INTERFACE_DEFINED__
__IActiveScriptStats_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptStats 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptStats:IID


.comdef IActiveScriptStats

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetStat             proc :DWORD, :ptr, :ptr
    GetStatEx           proc :REFGUID, :ptr, :ptr
    ResetStats          proc 
    .ends

                        ENDS







endif 	;; __IActiveScriptStats_INTERFACE_DEFINED__ 


ifndef __IActiveScriptProperty_INTERFACE_DEFINED__
__IActiveScriptProperty_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptProperty 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptProperty:IID


.comdef IActiveScriptProperty

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetProperty         proc :DWORD, :ptr, :ptr
    SetProperty         proc :DWORD, :ptr, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptProperty_INTERFACE_DEFINED__ 


ifndef __ITridentEventSink_INTERFACE_DEFINED__
__ITridentEventSink_INTERFACE_DEFINED__ equ 1

;; interface ITridentEventSink 
;; [unique][uuid][object] 


externdef               IID_ITridentEventSink:IID


.comdef ITridentEventSink

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    FireEvent           proc :LPCOLESTR, :ptr, :ptr, :ptr
    .ends

                        ENDS







endif 	;; __ITridentEventSink_INTERFACE_DEFINED__ 


ifndef __IActiveScriptGarbageCollector_INTERFACE_DEFINED__
__IActiveScriptGarbageCollector_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptGarbageCollector 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptGarbageCollector:IID


.comdef IActiveScriptGarbageCollector

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    CollectGarbage      proc :SCRIPTGCTYPE
    .ends

                        ENDS







endif 	;; __IActiveScriptGarbageCollector_INTERFACE_DEFINED__ 


ifndef __IActiveScriptSIPInfo_INTERFACE_DEFINED__
__IActiveScriptSIPInfo_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptSIPInfo 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptSIPInfo:IID


.comdef IActiveScriptSIPInfo

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    GetSIPOID           proc :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptSIPInfo_INTERFACE_DEFINED__ 


ifndef __IActiveScriptSiteTraceInfo_INTERFACE_DEFINED__
__IActiveScriptSiteTraceInfo_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptSiteTraceInfo 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptSiteTraceInfo:IID


.comdef IActiveScriptSiteTraceInfo

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    SendScriptTraceInfo proc :SCRIPTTRACEINFO, :GUID, :DWORD, :LONG, :LONG, :DWORD64
    .ends

                        ENDS







endif 	;; __IActiveScriptSiteTraceInfo_INTERFACE_DEFINED__ 


ifndef __IActiveScriptTraceInfo_INTERFACE_DEFINED__
__IActiveScriptTraceInfo_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptTraceInfo 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptTraceInfo:IID


.comdef IActiveScriptTraceInfo

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    StartScriptTracing  proc :ptr, :GUID
    StopScriptTracing   proc 
    .ends

                        ENDS







endif 	;; __IActiveScriptTraceInfo_INTERFACE_DEFINED__ 


ifndef __IActiveScriptStringCompare_INTERFACE_DEFINED__
__IActiveScriptStringCompare_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptStringCompare 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptStringCompare:IID


.comdef IActiveScriptStringCompare

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    StrComp             proc :BSTR, :BSTR, :ptr
    .ends

                        ENDS







endif 	;; __IActiveScriptStringCompare_INTERFACE_DEFINED__ 


;; interface __MIDL_itf_activscp_0000_0026 
;; [local] 


endif  ;; __ActivScp_h



externdef               __MIDL_itf_activscp_0000_0026_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activscp_0000_0026_v0_0_s_ifspec:RPC_IF_HANDLE

;; Additional Prototypes for ALL interfaces 

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


;; [local] 
 This,                  LPIActiveScriptError ?
;; [out] 


;; [call_as] 
 This,                  LPIActiveScriptError ?
;; [out] 



;; end of Additional Prototypes 

ifdef __cplusplus
                        ENDS
endif

endif



