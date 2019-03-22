; __CRTCAPTURECURRENTCONTEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

    .code

__crtCaptureCurrentContext proc frame uses rsi rdi rbx pContextRecord:ptr CONTEXT

  local ControlPc:ULONG64
  local EstablisherFrame:ULONG64
  local ImageBase:ULONG64
  local FunctionEntry:PRUNTIME_FUNCTION
  local HandlerData:PVOID

    mov rbx,rcx
    RtlCaptureContext(rcx)
    mov rsi,[rbx].CONTEXT._Rip
    .if RtlLookupFunctionEntry(rsi, &ImageBase, NULL)
        RtlVirtualUnwind(0, ImageBase, rsi, rax, rbx, &HandlerData, &EstablisherFrame, NULL)
    .endif
    ret

__crtCaptureCurrentContext endp

    end
