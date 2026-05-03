;
; https://devblogs.microsoft.com/oldnewthing/20180726-00/?p=99345
;
include windows.inc

define CUSTOM_CODE 0x87654321

    .code

CustomFilter proc pointers:ptr EXCEPTION_POINTERS

    mov rcx,[rcx]
    .if ( [rcx].EXCEPTION_RECORD.ExceptionCode == CUSTOM_CODE )

        MessageBox(0, "Handling custom exception", "Inside exception filter", 0)
       .return EXCEPTION_CONTINUE_EXECUTION
    .endif
    MessageBox(0, "Allowing handler to execute", "Inside exception filter", 0)
   .return EXCEPTION_EXECUTE_HANDLER

CustomFilter endp

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE,
        lpCmdLine:LPTSTR, nShowCmd:SINT

    SetUnhandledExceptionFilter(&CustomFilter)
    RaiseException(CUSTOM_CODE, 0, 0, NULL)
    ret

wWinMain endp

wWinStart proc

    ExitProcess(wWinMain(NULL, NULL, NULL, 0))

wWinStart endp

    end wWinStart
