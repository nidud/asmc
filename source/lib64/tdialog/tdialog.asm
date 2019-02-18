; TDIALOG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include tdialog.inc

    .data

    Vtbl dq TDialog_Release
         dq TDialog_Open
         dq TDialog_OpenIDD
         dq TDialog_GetBitFlag
         dq TDialog_SetBitFlag

    .code

    assume rcx:ptr TDialog

TDialog::GetBitFlag proc id:UINT, count:UINT, flag:UINT

    .for ( edx <<= 3,
           rdx += [rcx].object,
           eax = 0 : r8d : r8d--, rdx += 8, eax <<= 1 )

        mov r10,[rdx]
        .if r9w & [r10].TObject.flags

            or al,1
        .endif

        shl eax,1
    .endf
    shr eax,1
    ret

TDialog::GetBitFlag endp

TDialog::SetBitFlag proc id:UINT, count:UINT, flag:UINT, bitflag:UINT

    .for ( edx <<= 3,
           eax = bitflag,
           rdx += [rcx].object : r8d : r8d--, rdx += 8 )

        shl eax,1
        .ifc
            mov r10,[rdx]
            or  [r10].TObject.flags,r9w
        .endif
    .endf
    ret

TDialog::SetBitFlag endp

    assume rsi:ptr TDialog
    assume rdi:ptr twindow

TDialog::Open proc uses rsi rdi rbx rc:TRECT, flags:UINT

    mov rsi,rcx
    and r8d,_TW_MOVEABLE or _TW_USESHADE or _TW_USECOLOR
    mov eax,r8d
    and eax,_D_DMOVE or _D_SHADE
    or  eax,_D_DOPEN
    mov [rsi].flags,eax
    twindow::twindow( &[rsi].window, edx, r8d )
    mov rcx,rsi
    ret

TDialog::Open endp


TDialog::OpenIDD proc uses rsi rdi rbx idd:LPIDDOBJ

    mov rsi,rcx
    mov rbx,rdx

    mov r8w,[rdx].IDDOBJ.dialog.flags
    mov edx,[rdx].IDDOBJ.dialog.rc

    [rcx].Open(edx, r8d)

    movzx edi,[rbx].IDDOBJ.dialog.count

    .if edi

        .if malloc( &[rdi*8] )

            .for ( [rsi].object = rax : edi : edi-- )

                lea r10,[rdi*8-8]
                lea rdx,[rbx+r10].IDDOBJ.dialog[8]
                add r10,[rsi].object

                TObject::TObject( r10, rdx )

            .endf

        .endif
    .endif
    ret

TDialog::OpenIDD endp

    assume rdi:nothing

TDialog::TDialog proc uses rsi rdi rbx

    mov rbx,rcx

    .if malloc( sizeof(TDialog) )

        mov rdi,rax
        mov rsi,rax
        mov ecx,sizeof(TDialog) / 8
        xor eax,eax
        rep stosq

        lea rax,Vtbl
        mov [rsi].lpVtbl,rax
        mov rax,rsi

    .endif

    .if rbx

        mov [rbx],rax
    .endif
    ret

TDialog::TDialog endp


TDialog::Release proc uses rsi rdi rbx

    mov rsi,rcx

    .for ( ebx = [rcx].count,
           rdi = [rcx].object : ebx : ebx--, rdi += 8 )

        mov rcx,[rdi]
        [rcx].TObject.Release()
    .endf

    free( [rsi].object )

    mov rcx,[rsi].window
    [rcx].twindow.Release()

    free( rsi )
    ret

TDialog::Release endp

    end
