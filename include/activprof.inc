ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __activprof_h__
define __activprof_h__

.pragma list(push, 0)

ifndef __unknwn_h__
include unknwn.inc
endif

ACTIVPROF_E_PROFILER_PRESENT	   equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0200)
ACTIVPROF_E_PROFILER_ABSENT	   equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0201)
ACTIVPROF_E_UNABLE_TO_APPLY_ACTION equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0202)

ifndef __ActivProf_h
define __ActivProf_h

PROFILER_SCRIPT_TYPE typedef SDWORD
PROFILER_SCRIPT_TYPE_USER equ 0
PROFILER_SCRIPT_TYPE_DYNAMIC equ ( PROFILER_SCRIPT_TYPE_USER + 1 )
PROFILER_SCRIPT_TYPE_NATIVE equ ( PROFILER_SCRIPT_TYPE_DYNAMIC + 1 )

PROFILER_EVENT_MASK typedef SDWORD
PROFILER_EVENT_MASK_TRACE_SCRIPT_FUNCTION_CALL equ 0x1
PROFILER_EVENT_MASK_TRACE_NATIVE_FUNCTION_CALL equ 0x2
PROFILER_EVENT_MASK_TRACE_ALL equ ( PROFILER_EVENT_MASK_TRACE_SCRIPT_FUNCTION_CALL | PROFILER_EVENT_MASK_TRACE_NATIVE_FUNCTION_CALL )

PROFILER_TOKEN typedef LONG

ifndef __IActiveScriptProfilerControl_INTERFACE_DEFINED__
define __IActiveScriptProfilerControl_INTERFACE_DEFINED__

DEFINE_IIDX(IActiveScriptProfilerControl, "784b5ff0-69b0-47d1-a7dc-2518f4230e90")

.comdef IActiveScriptProfilerControl : public IUnknown

    StartProfiling proc :REFCLSID, :DWORD, :DWORD
    SetProfilerEventMask proc :DWORD
    StopProfiling proc :HRESULT
   .ends

endif

ifndef __IActiveScriptProfilerCallback_INTERFACE_DEFINED__
define __IActiveScriptProfilerCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IActiveScriptProfilerCallback, "740eca23-7d9d-42e5-ba9d-f8b24b1c7a9b")

.comdef IActiveScriptProfilerCallback : public IUnknown

    Initialize		proc :DWORD
    Shutdown		proc :HRESULT
    ScriptCompiled	proc :PROFILER_TOKEN, :PROFILER_SCRIPT_TYPE, :ptr
    FunctionCompiled	proc :PROFILER_TOKEN, :PROFILER_TOKEN, :ptr, :ptr, :ptr
    OnFunctionEnter	proc :PROFILER_TOKEN, :PROFILER_TOKEN
    OnFunctionExit	proc :PROFILER_TOKEN, :PROFILER_TOKEN
   .ends

endif
endif

.pragma list(pop)
endif
