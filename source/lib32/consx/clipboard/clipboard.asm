include consx.inc
include string.inc
include alloc.inc

.data

clipbsize dd 0
clipboard dd 0

.code

ClipboardFree proc

    free(clipboard)
    xor eax,eax
    mov clipbsize,eax
    mov clipboard,eax
    ret

ClipboardFree endp

ClipboardCopy proc uses esi edi ebx string:LPSTR, len

    mov edi,len
    ClipboardFree()
    mov eax,console
ifdef _WIN95
    and eax,CON_WIN95 or CON_CLIPB
    .if eax == CON_CLIPB
else
    and eax,CON_CLIPB
    .if eax
endif
        .if OpenClipboard(0)

            EmptyClipboard()
            inc edi

            .if GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE, edi)

                dec edi
                mov esi,eax
                mov ebx,memcpy(GlobalLock(eax), string, edi)
                mov byte ptr [ebx+edi],0
                GlobalUnlock(esi)
                SetClipboardData(CF_TEXT, ebx)
                mov eax,edi
            .endif
            push eax
            CloseClipboard()
            pop eax
        .endif
    .else
        inc edi
        .if malloc(edi)

            dec edi
            memcpy(eax, string, edi)
            mov byte ptr [eax+edi],0
            mov clipboard,eax
            mov clipbsize,edi
        .endif
    .endif
    ret

ClipboardCopy endp

ClipboardPaste proc uses ebx
    mov eax,console
ifdef _WIN95
    and eax,CON_WIN95 or CON_CLIPB
    .if eax == CON_CLIPB
else
    and eax,CON_CLIPB
    .if eax
endif
        .if IsClipboardFormatAvailable(CF_TEXT)

            .if OpenClipboard(0)

                .if GetClipboardData(CF_TEXT)

                    mov ebx,eax
                    .if strlen(eax)

                        mov clipbsize,eax
                        inc eax
                        .if malloc(eax)

                            strcpy(eax, ebx)
                            mov clipboard,eax
                        .else
                            xor eax,eax
                        .endif
                    .endif
                .endif

                push eax
                CloseClipboard()
                pop eax
            .endif
        .endif
    .elseif clipbsize
        mov eax,clipboard
    .else
        xor eax,eax
    .endif
    mov ecx,clipbsize
    ret

ClipboardPaste endp

    END
