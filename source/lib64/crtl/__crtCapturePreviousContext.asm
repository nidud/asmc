; __CRTCAPTUREPREVIOUSCONTEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

    .code

__crtCapturePreviousContext proc frame uses rsi rdi rbx pContextRecord:ptr CONTEXT

  local EstablisherFrame:ULONG64
  local ImageBase:ULONG64
  local HandlerData:PVOID

    mov rbx,rcx
    RtlCaptureContext(rcx)

    .for (rdi = [rbx].CONTEXT._Rip, esi = 0: esi < 2: ++esi)

        .if RtlLookupFunctionEntry(rdi, &ImageBase, NULL)

            RtlVirtualUnwind(0, ImageBase, rdi, rax, rbx,
                &HandlerData, &EstablisherFrame, NULL)

        .else
            .break
        .endif
    .endf
    ret

__crtCapturePreviousContext endp

    end
