;
; http://masm32.com/board/index.php?topic=6887.msg73738#msg73738
;
include windows.inc
ifdef __PE__
option dllimport:none	; to force proto below local..
endif

ParseCmdLine	    PROTO :DWORD
EnumWndProc	    PROTO STDCALL :DWORD,:DWORD
EnumChildWndProc    PROTO STDCALL :DWORD,:DWORD

WM_REFRESH	    equ 28931

.data

class	 db 'SHELLDLL_DefView',0
subKey	 db 'Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced',0
valName1 db 'ShowSuperHidden',0
valName2 db 'SuperHidden',0
valName3 db 'Hidden',0
data1	 dd 1
data2	 dd 0
data3	 dd 1

.data?

buffer	 db 512 dup(?)

.code

start:

    call    main
    invoke  ExitProcess,0

main PROC uses esi

LOCAL key:DWORD

    mov	    esi,OFFSET buffer
    invoke  ParseCmdLine,esi
    cmp	    eax,2
    jz	    @f
    ret
@@:
    mov	    edx,DWORD PTR [esi+4]
    cmp	    DWORD PTR [edx],'wohs'
    je	    disp

    cmp	    DWORD PTR [edx],'edih'
    je	    @f
    ret
@@:
    mov	    data1,0
    mov	    data2,1
    mov	    data3,2

disp:

    invoke  RegOpenKeyEx,HKEY_CURRENT_USER,\
	    ADDR subKey,0,KEY_WRITE,ADDR key

    invoke  RegSetValueEx,key,ADDR valName1,0,\
	    REG_DWORD,ADDR data1,sizeof(DWORD)

    invoke  RegSetValueEx,key,ADDR valName2,0,\
	    REG_DWORD,ADDR data2,sizeof(DWORD)

    invoke  RegSetValueEx,key,ADDR valName3,0,\
	    REG_DWORD,ADDR data3,sizeof(DWORD)

    invoke  RegCloseKey,key

    invoke  EnumWindows,ADDR EnumWndProc,\
	    ADDR class
    ret

main ENDP


EnumWndProc PROC STDCALL hWnd:DWORD,lParam:DWORD

    invoke  EnumChildWindows,hWnd,\
	    ADDR EnumChildWndProc,0

    mov	    eax,1
    ret

EnumWndProc ENDP


EnumChildWndProc PROC STDCALL hWnd,lParam:DWORD

LOCAL buff[128]:BYTE

    invoke  GetClassName,hWnd,ADDR buff,128
    invoke  strcmp,ADDR buff,ADDR class
    test    eax,eax
    jnz	    @f

    invoke  SendMessage,hWnd,WM_COMMAND,\
	    WM_REFRESH,0
@@:
    mov	    eax,1
    ret

EnumChildWndProc ENDP


ParseCmdLine PROC uses esi edi ebx _buffer:DWORD

    invoke  GetCommandLine
    lea	    edx,[eax-1]
    xor	    eax,eax
    mov	    esi,_buffer
    lea	    edi,[esi+256]
    mov	    ch,32
    mov	    bl,9

scan:

    inc	    edx
    mov	    cl,BYTE PTR [edx]
    test    cl,cl
    jz	    finish
    cmp	    cl,32
    je	    scan
    cmp	    cl,9
    je	    scan
    inc	    eax
    mov	    DWORD PTR [esi],edi
    add	    esi,4

restart:

    mov	    cl,BYTE PTR [edx]
    test    cl,cl
    jne	    @f
    mov	    BYTE PTR [edi],cl
    ret
@@:
    cmp	    cl,ch
    je	    end_of_line
    cmp	    cl,bl
    je	    end_of_line
    cmp	    cl,34
    jne	    @f
    xor	    ch,32
    xor	    bl,9
    jmp	    next_char
@@:
    mov	    BYTE PTR [edi],cl
    inc	    edi

next_char:

    inc	    edx
    jmp	    restart

end_of_line:

    mov	    BYTE PTR [edi],0
    inc	    edi
    jmp	    scan

finish:

    ret

ParseCmdLine ENDP

END start
