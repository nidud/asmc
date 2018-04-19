

;; this ALWAYS GENERATED file contains the definitions for the interfaces 


;; File created by MIDL compiler version 7.00.0555 
;; Compiler settings for activprof.idl:
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

ifndef __activprof_h__
__activprof_h__ equ 1

if defined(_MSC_VER) AND (_MSC_VER GE 1020)
pragma once
endif

;; Forward Declarations 

ifndef __IActiveScriptProfilerControl_FWD_DEFINED__
__IActiveScriptProfilerControl_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptProfilerControl_FWD_DEFINED__ 


ifndef __IActiveScriptProfilerCallback_FWD_DEFINED__
__IActiveScriptProfilerCallback_FWD_DEFINED__ equ 1
endif 	;; __IActiveScriptProfilerCallback_FWD_DEFINED__ 


;; header files for imported files 
include unknwn.inc

ifdef __cplusplus
externdef               
endif


;; interface __MIDL_itf_activprof_0000_0000 
;; [local] 

;;=--------------------------------------------------------------------------=
;; ActivProf.h
;;=--------------------------------------------------------------------------=
;; (C) Copyright 2000 Microsoft Corporation.  All Rights Reserved.
;;
;; THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
;; ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
;; THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
;; PARTICULAR PURPOSE.
;;=--------------------------------------------------------------------------=
;;
pragma comment(lib,"uuid.lib")
;;
;; Declarations for ActiveX Scripting profiling.
;;

;HRESULT
MAKE_HRESULT proto WINAPI \
                      : SEVERITY_ERROR,
                      : FACILITY_ITF,
                      : 0x0200

;HRESULT
MAKE_HRESULT proto WINAPI \
                      : SEVERITY_ERROR,
                      : FACILITY_ITF,
                      : 0x0201

;HRESULT
MAKE_HRESULT proto WINAPI \
                      : SEVERITY_ERROR,
                      : FACILITY_ITF,
                      : 0x0202


ifndef __ActivProf_h
__ActivProf_h equ 1

_MIDL___MIDL_itf_activprof_0000_0000_0001 typedef SDWORD
PROFILER_SCRIPT_TYPE_USER equ 0
PROFILER_SCRIPT_TYPE_DYNAMIC equ ( PROFILER_SCRIPT_TYPE_USER + 1 )
PROFILER_SCRIPT_TYPE_NATIVE equ ( PROFILER_SCRIPT_TYPE_DYNAMIC + 1 )

_MIDL___MIDL_itf_activprof_0000_0000_0002 typedef SDWORD
PROFILER_EVENT_MASK_TRACE_SCRIPT_FUNCTION_CALL equ 0x1
PROFILER_EVENT_MASK_TRACE_NATIVE_FUNCTION_CALL equ 0x2
PROFILER_EVENT_MASK_TRACE_ALL equ ( PROFILER_EVENT_MASK_TRACE_SCRIPT_FUNCTION_CALL | PROFILER_EVENT_MASK_TRACE_NATIVE_FUNCTION_CALL )

PROFILER_TOKEN          typedef LONG 



externdef               __MIDL_itf_activprof_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activprof_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActiveScriptProfilerControl_INTERFACE_DEFINED__
__IActiveScriptProfilerControl_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptProfilerControl 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptProfilerControl:IID


.comdef IActiveScriptProfilerControl

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    StartProfiling      proc :REFCLSID, :DWORD, :DWORD
    SetProfilerEventMask proc :DWORD
    StopProfiling       proc :HRESULT
    .ends

                        ENDS







endif 	;; __IActiveScriptProfilerControl_INTERFACE_DEFINED__ 


ifndef __IActiveScriptProfilerCallback_INTERFACE_DEFINED__
__IActiveScriptProfilerCallback_INTERFACE_DEFINED__ equ 1

;; interface IActiveScriptProfilerCallback 
;; [unique][uuid][object] 


externdef               IID_IActiveScriptProfilerCallback:IID


.comdef IActiveScriptProfilerCallback

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc 
    Release             proc 
    Initialize          proc :DWORD
    Shutdown            proc :HRESULT
    ScriptCompiled      proc :PROFILER_TOKEN, :PROFILER_SCRIPT_TYPE, :ptr
    FunctionCompiled    proc :PROFILER_TOKEN, :PROFILER_TOKEN, :const, :const, :ptr
    OnFunctionEnter     proc :PROFILER_TOKEN, :PROFILER_TOKEN
    OnFunctionExit      proc :PROFILER_TOKEN, :PROFILER_TOKEN
    .ends

                        ENDS







endif 	;; __IActiveScriptProfilerCallback_INTERFACE_DEFINED__ 


;; interface __MIDL_itf_activprof_0000_0002 
;; [local] 


endif  ;; __ActivProf_h



externdef               __MIDL_itf_activprof_0000_0002_v0_0_c_ifspec:RPC_IF_HANDLE
externdef               __MIDL_itf_activprof_0000_0002_v0_0_s_ifspec:RPC_IF_HANDLE

;; Additional Prototypes for ALL interfaces 

;; end of Additional Prototypes 

ifdef __cplusplus
                        ENDS
endif

endif



