ifndef _GDIPLUSINIT_H
_GDIPLUSINIT_H equ <>

.enum DebugEventLevel {
    DebugEventLevelFatal,
    DebugEventLevelWarning
}

;; Callback function that GDI+ can call, on debug builds, for assertions
;; and warnings.

CALLBACK(DebugEventProc, :DebugEventLevel, :ptr)

;; Notification functions which the user must call appropriately if
;; "SuppressBackgroundThread" (below) is set.

CALLBACK(NotificationHookProc, :ptr)
CALLBACK(NotificationUnhookProc, :ULONG_PTR)

;; Input structure for GdiplusStartup()

.template GdiplusStartupInput

    GdiplusVersion              UINT ?              ;; Must be 1  (or 2 for the Ex version)
    DebugEventCallback          DebugEventProc ?    ;; Ignored on free builds
    SuppressBackgroundThread    BOOL ?              ;; FALSE unless you're prepared to call
                                                    ;; the hook/unhook functions properly
    SuppressExternalCodecs      BOOL ?              ;; FALSE unless you want GDI+ only to use
                                                    ;; its internal image codecs.

    .operator GdiplusStartupInput {
        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(GdiplusStartupInput)
            .endif
            mov [rax].GdiplusStartupInput.GdiplusVersion,1
            mov [rax].GdiplusStartupInput.DebugEventCallback,NULL
            mov [rax].GdiplusStartupInput.SuppressBackgroundThread,FALSE
            mov [rax].GdiplusStartupInput.SuppressExternalCodecs,FALSE
        .until 1
        retm <rax>
        }
    .operator Release { exitm<GdipFree(this)> }
    .ends


if (GDIPVER GE 0x0110)

.template GdiplusStartupInputEx : public GdiplusStartupInput

    StartupParameters SINT ?

    .operator GdiplusStartupInputEx {
        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(GdiplusStartupInputEx)
            .endif
            mov [rax].GdiplusStartupInputEx.GdiplusVersion,2
            mov [rax].GdiplusStartupInputEx.DebugEventCallback,NULL
            mov [rax].GdiplusStartupInputEx.SuppressBackgroundThread,FALSE
            mov [rax].GdiplusStartupInputEx.SuppressExternalCodecs,FALSE
        .until 1
        retm <rax>
        }
    .operator Release { exitm<GdipFree(this)> }
    .ends

.enum GdiplusStartupParams {
    GdiplusStartupDefault,
    GdiplusStartupNoSetRound,
    GdiplusStartupSetPSValue,
    GdiplusStartupTransparencyMask = 0xFF000000
    }

endif

GdiplusStartupOutput    STRUC
NotificationHook        NotificationHookProc ?
NotificationUnhook      NotificationUnhookProc ?
GdiplusStartupOutput    ENDS

GdiplusStartup proto WINAPI \
                 token: ptr ULONG_PTR,
                 input: ptr GdiplusStartupInput,
                output: ptr GdiplusStartupOutput

GdiplusShutdown proto WINAPI \
                 token: ULONG_PTR

endif
