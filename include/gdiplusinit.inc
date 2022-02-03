ifndef _GDIPLUSINIT_H
define _GDIPLUSINIT_H

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

.template GdiplusStartupInput fastcall

    GdiplusVersion              UINT ?              ;; Must be 1  (or 2 for the Ex version)
    DebugEventCallback          DebugEventProc ?    ;; Ignored on free builds
    SuppressBackgroundThread    BOOL ?              ;; FALSE unless you're prepared to call
                                                    ;; the hook/unhook functions properly
    SuppressExternalCodecs      BOOL ?              ;; FALSE unless you want GDI+ only to use
                                                    ;; its internal image codecs.

    .inline GdiplusStartupInput {
        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !malloc(GdiplusStartupInput)
            .endif
            mov [rax].GdiplusStartupInput.GdiplusVersion,1
            mov [rax].GdiplusStartupInput.DebugEventCallback,NULL
            mov [rax].GdiplusStartupInput.SuppressBackgroundThread,FALSE
            mov [rax].GdiplusStartupInput.SuppressExternalCodecs,FALSE
        .until 1
        retm <rax>
        }
    .inline Release { free(this) }
    .ends


if (GDIPVER GE 0x0110)

.template GdiplusStartupInputEx fastcall : public GdiplusStartupInput

    StartupParameters SINT ?

    .inline GdiplusStartupInputEx {
        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !malloc(GdiplusStartupInputEx)
            .endif
            mov [rax].GdiplusStartupInputEx.GdiplusVersion,2
            mov [rax].GdiplusStartupInputEx.DebugEventCallback,NULL
            mov [rax].GdiplusStartupInputEx.SuppressBackgroundThread,FALSE
            mov [rax].GdiplusStartupInputEx.SuppressExternalCodecs,FALSE
        .until 1
        retm <rax>
        }
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


.template GdiPlus fastcall

    GdiplusVersion              UINT ?
    DebugEventCallback          DebugEventProc ?
    SuppressBackgroundThread    BOOL ?
    SuppressExternalCodecs      BOOL ?
    StartupParameters           SINT ?
    Token                       ULONG_PTR ?

    .static GdiPlus Version:abs=<2> {

        mov this.GdiplusVersion,Version
        mov this.DebugEventCallback,NULL
        mov this.SuppressBackgroundThread,FALSE
        mov this.SuppressExternalCodecs,FALSE
        mov this.StartupParameters,0
        GdiplusStartup(addr this.Token, addr this, NULL)
        }
    .static Release {
        GdiplusShutdown(this.Token)
        }
    .ends

endif
