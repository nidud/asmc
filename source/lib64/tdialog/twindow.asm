; TWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include stdio.inc
include twindow.inc
include tconsole.inc

    .data

    virtual_table array_t 0

    .code

    assume rcx: ptr twindow

twindow::Release proc

    .if [rcx].flags & _TW_ISOPEN

        .if [rcx].flags & _TW_VISIBLE

            [rcx].hide()
        .endif

        free([rcx].window)
        console.show()

    .endif

    free(_this)
    ret

twindow::Release endp

twindow::exchange proc private uses rsi rdi

  local rc:TRECT

    .for ( eax = [rcx].rc,
           rc  = eax,
           rsi = [rcx].window : rc.row : rc.row--, rc.y++ )

        .for ( rdi = console.getrcp(rc), cl = rc.col : cl : cl-- )

            mov eax,[rdi]
            movsd
            mov [rsi-4],eax

        .endf
    .endf
    mov rcx,_this
    ret

twindow::exchange endp

twindow::show proc

    .repeat

        mov eax,[rcx].flags
        and eax,_TW_ISOPEN or _TW_VISIBLE
        .break .ifz

        .if !( eax & _TW_VISIBLE )

            [rcx].write([rcx].window)
            twindow::exchange(rcx)

            .if [rcx].flags & _TW_USESHADE

                [rcx].showsh()
            .endif

            or [rcx].flags,_TW_VISIBLE

        .endif

        ;console.show()
        ;mov rcx,_this
        mov eax,1

    .until 1
    ret

twindow::show endp

twindow::hide proc

    xor eax,eax

    .repeat

        mov edx,[rcx].flags

        .break .if !( edx & _TW_ISOPEN )

        .if edx & _TW_VISIBLE

            twindow::exchange(rcx)

            .if [rcx].flags & _TW_USESHADE

                [rcx].hidesh()

            .endif

            and [rcx].flags,not _TW_VISIBLE

        .endif

        mov eax,1

    .until 1
    ret

twindow::hide endp

twindow::move proc x:int_t, y:int_t

    .ifd [rcx].hide()

        mov al,byte ptr x
        mov ah,byte ptr y
        mov word ptr [rcx].rc.x,ax

        [rcx].show()
        mov eax,1
    .endif
    ret

twindow::move endp

if 0

twindow::read proc uses rsi rdi

  local rc:TRECT

    .for ( eax = [rcx].rc,
           rc  = eax,
           rdi = [rcx].window : rc.row : rc.row--, rc.y++ )

        mov     rsi,console.getrcp(rc)
        movzx   ecx,rc.col
        rep     movsd
    .endf
    mov rcx,_this
    ret

twindow::read endp

twindow::write proc uses rsi rdi

  local rc:TRECT

    .for ( eax = [rcx].rc,
           rc  = eax,
           rsi = [rcx].window : rc.row : rc.row--, rc.y++ )

        mov     rdi,console.getrcp(rc)
        movzx   ecx,rc.col
        rep     movsd
    .endf
    mov rcx,_this
    ret

twindow::write endp

endif

getshadeptr proc private

    movzx eax,[rcx].rc.col
    mul [rcx].rc.row
    lea rax,[rax*4]
    add rax,[rcx].window
    ret

getshadeptr endp

twindow::readshade proc private uses rsi rdi

  local rc:TRECT

    .for (  eax = [rcx].rc,
            rc = eax,
            al = rc.col,
            rc.x += al,
            rc.y++,
            rdi = getshadeptr() : rc.row : rc.row--, rc.y++ )

        mov rsi,console.getrcp(rc)
        movsq

    .endf

    movzx   ecx,rc.col
    lea     rax,[rcx*4]
    sub     rsi,rax
    sub     ecx,2
    rep     movsd
    mov     rcx,_this
    ret

twindow::readshade endp

twindow::showsh proc

  local rc:TRECT

    twindow::readshade(rcx)

    .for ( eax  = [rcx].rc,
           rc   = eax,
           al   = rc.col,
           rc.x = al,
           rc.y++ : rc.row : rc.row--, rc.y++ )

        console.getrcp(rc)
        mov byte ptr [rax+3],0x8
        mov byte ptr [rax+7],0x8
    .endf

    movzx ecx,rc.col
    lea rdx,[rcx*4]
    sub rax,rdx

    .for ( rax += 3,
           ecx -= 2 : ecx : ecx--, rax += 4 )

        mov byte ptr [rax],0x8
    .endf
    mov rcx,_this
    ret

twindow::showsh endp

twindow::hidesh proc uses rsi rdi

  local rc:TRECT

    mov eax,[rcx].rc
    mov rc,eax
    mov al,rc.col
    add rc.x,al
    inc rc.y

    .for ( rsi = getshadeptr() : rc.row : rc.row--, rc.y++ )

        mov rdi,console.getrcp(rc)
        movsq
    .endf
    movzx ecx,rc.col
    lea eax,[ecx*4]
    sub rdi,rax
    sub ecx,2
    rep movsd
    mov rcx,_this
    ret

twindow::hidesh endp

if 0

twindow::xyrow proc x:int_t, y:int_t

    mov al,r8b
    mov ah,dl
    mov dl,[rcx].rc.x
    mov dh,[rcx].rc.y

    .repeat

        .if ( ah >= dl && al >= dh )

            add dl,[rcx].rc.col

            .if ( ah < dl )

                mov ah,dh
                add dh,[rcx].rc.row

                .if ( al < dh )

                    sub al,ah
                    inc al
                    movzx eax,al
                    .break

                .endif
            .endif
        .endif

        xor eax,eax

    .until 1
    ret

twindow::xyrow endp

twindow::inside proc rc:TRECT

    xor r8d,r8d
    mov ax,word ptr [rcx].rc[2]
    mov dx,word ptr rc[2]

    .if ( dh > ah || dl > al )

        mov r8d,5

    .else

        add ax,word ptr [rcx].rc
        add dx,word ptr rc

        .if ah < dh

            inc r8d

        .elseif al < dl

            mov r8d,4

        .else

            mov ax,word ptr [rcx].rc
            mov dx,word ptr rc

            .if ah > dh

                mov r8d,2

            .elseif al > dl

                mov r8d,3
            .endif
        .endif
    .endif

    mov eax,r8d
    ret

twindow::inside endp

twindow::getxyo proc x:int_t, y:int_t

    movzx eax,[rcx].rc.col
    imul  eax,r8d
    add   eax,edx
    ret

twindow::getxyo endp

twindow::putw proc uses rdi rcx o:uint_t, l:uint_t, w:uint_t

    lea edi,[edx*4]
    add rdi,[rcx].window
    mov eax,r9d
    mov ecx,r8d

    .if eax & 0xFFFF0000

        rep stosd

    .else

        .repeat

            stosw
            add rdi,2

        .untilcxz

    .endif
    ret

twindow::putw endp

endif

convat proc private uses rsi rdi

    movzx eax,al
    .if [rcx].flags & _TW_USECOLOR

        mov rdi,console
        .if eax

            mov  esi,eax
            and  eax,0x0F
            shr  esi,4
            mov  al,[rdi].tconsole.foreground[rax]
            or   al,[rdi].tconsole.background[rsi]

        .endif
    .endif
    ret

convat endp

twindow::putxyw proc x:int_t, y:int_t, count:int_t, w:uint_t

    movzx eax,[rcx].rc.col
    imul  eax,r8d
    add   eax,edx

    lea r8,[rax*4]
    add r8,[rcx].window
    mov eax,w

    .if eax & 0xFFFF0000

        shr eax,16
        convat()
        shl eax,16
        mov ax,word ptr w

        xchg rdi,r8
        xchg rcx,r9
        rep stosd
        mov rdi,r8
        mov rcx,r9

    .else

        .repeat

            mov [r8],ax
            add r8,4
            dec r9d

        .untilz
    .endif
    ret

twindow::putxyw endp

twindow::putxya proc x:int_t, y:int_t, l:int_t, at:uchar_t

    movzx eax,[rcx].rc.col
    imul eax,r8d
    add eax,edx
    lea r8,[rax*4]
    add r8,[rcx].window
    mov al,at

    convat()

    .repeat

        mov [r8+2],al
        add r8,4
        dec r9d

    .untilz
    ret

twindow::putxya endp

twindow::putxyf proc x:int_t, y:int_t, at:ushort_t, max:int_t, format:string_t, argptr:vararg

  local o:_iobuf
  local w:ptr_t
  local highat:byte
  local attrib:byte

    mov     eax,r9d
    mov     attrib,al
    mov     highat,ah

    movzx   eax,[rcx].rc.col
    imul    eax,r8d
    add     eax,edx
    lea     rax,[rax*4]
    add     rax,[rcx].window
    mov     w,rax

    mov     o._flag,_IOWRT or _IOSTRG
    mov     o._cnt,_INTIOBUF
    mov     _bufin,0
    lea     rax,_bufin
    mov     o._ptr,rax
    mov     o._base,rax

    _output(&o, format, &argptr)

    mov rdx,o._ptr
    mov byte ptr [rdx],0
    mov rcx,_this

    mov al,attrib
    mov attrib,convat()
    mov al,highat
    mov highat,convat()

    mov r11d,max
    .if !r11d

        mov r11b,[rcx].rc.col
        sub r11d,x

    .endif

    .for ( rdx = w,
           r8  = o._base,
           r9d = 0,
           r9b = [rcx].rc.col,
           r9d <<= 2,
           r10 = rdx,
           ah  = attrib,
           al  = [r8] : al, r11d : r8++, al = [r8], r11d-- )

        .if al == 10

            add r10,r9
            mov rdx,r10

        .elseif al == 9

            add rdx,4*4

        .elseif al == '&' && highat

            inc r8
            mov al,highat
            mov [rdx+2],al
            mov al,[r8]
            mov [rdx],al
            add rdx,4

        .else

            mov [rdx],al
            .if ah

                mov [rdx+2],ah
            .endif
            add rdx,4

        .endif
    .endf
    ret

twindow::putxyf endp

twindow::putpath proc uses rsi rdi rbx x:int_t, y:int_t, max:int_t, path:string_t

    movzx   eax,[rcx].rc.col
    imul    eax,r8d
    add     eax,edx
    lea     rdi,[rax*4]
    add     rdi,[rcx].window
    mov     rsi,path
    mov     rbx,r9

    .ifd strlen(rsi) > ebx

        mov edx,[rsi]
        add rsi,rax
        mov eax,ebx
        sub rsi,rax
        add rsi,4

        .if dh == ':'

            mov [rdi],dl
            mov [rdi+4],dh
            shr edx,8
            mov dl,'.'
            add rdi,8
            add rsi,2
            sub eax,2

        .else

            mov dx,'/.'

        .endif

        mov [rdi],dh
        mov [rdi+4],dl
        mov [rdi+8],dl
        mov [rdi+12],dh
        add rdi,16
        sub eax,4

    .endif

    .while eax

        movsb
        add rdi,3
        dec eax
    .endw

    mov rcx,_this
    ret

twindow::putpath endp

if 0

twindow::putfg proc o:uint_t, l:uint_t, a:BYTE

    .for ( r11 = &[rdx*4+2],
           r11 += [rcx].window : r8d : r8d--, r11 += 4 )

        and byte ptr [r11],0xF0
        or  byte ptr [r11],r9b
    .endf
    ret

twindow::putfg endp

twindow::putbg proc o:uint_t, l:uint_t, a:BYTE

    .for ( r11 = &[rdx*4+2],
           r11 += [rcx].window : r8d : r8d--, r11 += 4 )

        and byte ptr [r11],0x0F
        or  byte ptr [r11],r9b
    .endf
    ret

twindow::putbg endp

twindow::puts proc uses rsi rdi rbx o:uint_t, l:uint_t, string:string_t

    .if !r8d

        dec r8d
    .endif

    .for ( rdi = &[rdx*4],
           rdi += [rcx].window,
           rsi = r9,
           edx = 0,
           dl  = [rcx].rc.col,
           edx <<= 2,
           rbx = rdi,
           al  = [rsi] : al, r8d : rsi++, al = [rsi], r8d-- )

        .if al == 10

            add rbx,rdx
            mov rdi,rbx

        .elseif al == 9

            add rdi,4*4

        .else

            mov [rdi],al
            add rdi,4
        .endif

    .endf
    ret

twindow::puts endp

twindow::puts_ex proc uses rsi rdi rbx o:uint_t, l:uint_t, Attrib:BYTE, HighColor:BYTE, string:string_t

    .if !r8d

        dec r8d
    .endif

    .for ( edi = &[edx*4],
           rdi += [rcx].window,
           rsi = string,
           edx = 0,
           dl  = [rcx].rc.col,
           edx <<= 2,
           rbx = rdi,
           ah  = HighColor,
           al  = [rsi] : al, r8d : rsi++, al = [rsi], r8d-- )

        .if al == 10

            add rbx,rdx
            mov rdi,rbx

        .elseif al == 9

            add rdi,4*4

        .elseif al == '&' && HighColor

            mov al,HighColor
            mov [rdi+2],al

        .else

            mov [rdi],al
            add rdi,4

        .endif

    .endf
    ret

twindow::puts_ex endp

twindow::putpath proc uses rsi rdi rbx o:uint_t, l:uint_t, string:string_t

    mov rsi,r9
    mov rbx,r8
    lea rdi,[rdx*4]
    add rdi,[rcx].window

    .ifd strlen(rsi) > ebx

        mov edx,[rsi]
        add rsi,rax
        mov eax,ebx
        sub rsi,rax
        add rsi,4

        .if dh == ':'

            mov [rdi],dl
            mov [rdi+4],dh
            shr edx,8
            mov dl,'.'
            add rdi,8
            add rsi,2
            sub eax,2

        .else

            mov dx,'/.'

        .endif

        mov [rdi],dh
        mov [rdi+4],dl
        mov [rdi+8],dl
        mov [rdi+12],dh
        add rdi,16
        sub eax,4

    .endif

    .while eax

        movsb
        add rdi,3
        dec eax
    .endw

    mov rcx,_this
    ret

twindow::putpath endp

endif

twindow::center proc uses rsi rdi rbx x:int_t, y:int_t, l:int_t, string:string_t

    mov   rsi,string
    mov   rbx,r9
    movzx eax,[rcx].rc.col
    imul  eax,r8d
    add   edx,eax
    lea   rdi,[rdx*4]
    add   rdi,[rcx].window

    strlen(rsi)
    mov r8,rdi

    .if eax > ebx

        mov edx,[rsi]
        add rsi,rax
        mov eax,ebx
        sub rsi,rax
        add rsi,4

        .if dh == ':'

            mov [rdi],dl
            mov [rdi+4],dh
            shr edx,8
            mov dl,'.'
            add rdi,8
            add rsi,2
            sub eax,2

        .else

            mov dx,'/.'

        .endif

        mov [rdi],dh
        mov [rdi+4],dl
        mov [rdi+8],dl
        mov [rdi+12],dh
        add rdi,16
        sub eax,4

    .endif

    .if eax

        .if rdi == r8

            sub ebx,eax
            shr ebx,2
            lea rdi,[rdi+rbx*8]

        .endif

        .repeat

            movsb
            add rdi,3

        .untilaxz

    .endif

    mov rcx,_this
    ret

twindow::center endp

twindow::settitle proc string:string_t

    mov     r8,console
    movzx   eax,[r8].tconsole.foreground[F_Title]
    or      al, [r8].tconsole.background[B_Title]
    shl     eax,16
    mov     al,' '
    mov     r8,rcx
    mov     r9,[rcx].window
    xchg    rdi,r9
    movzx   ecx,[rcx].rc.col
    rep     stosd
    mov     rcx,r8
    mov     rdi,r9
    movzx   r9d,[rcx].rc.col
    mov     rax,rdx

    [rcx].center(0, 0, r9d, rax)
    ret

twindow::settitle endp

twindow::clear proc uses rdi rcx at:uchar_t

    mov al,dl
    convat()

    mov     rdi,[rcx].window
    movzx   edx,[rcx].rc.row
    movzx   ecx,[rcx].rc.col
    imul    ecx,edx
    shl     eax,16
    mov     al,' '
    rep     stosd
    ret

twindow::clear endp

if 0

twindow::memsize proc private

    movzx   eax,[rcx].rc.col
    movzx   edx,[rcx].rc.row
    mov     r8d,eax
    mul     dl
    lea     eax,[eax*4]

    .if [rcx].flags & _TW_USESHADE

        lea r8d,[r8d+edx*4-4]
        add eax,r8d
    .endif
    ret

twindow::memsize endp

twindow::alloc proc

    malloc( twindow::memsize(rcx) )

    mov rcx,_this
    mov [rcx].window,rax
    ret

twindow::alloc endp

endif

twindow::twindow proc uses rbx rc:TRECT, flags:uint_t

    .if malloc( sizeof(twindow) )

        mov     rcx,rax
        mov     rdx,virtual_table
        mov     [rcx].lpVtbl,rdx
        mov     [rcx].flags,_TW_ISOPEN

        mov     eax,rc
        mov     [rcx].rc,eax
        mov     eax,flags
        or      [rcx].flags,eax

        mov     rbx,rcx
        movzx   eax,[rcx].rc.col
        movzx   edx,[rcx].rc.row
        mov     r8d,eax
        mul     dl
        lea     eax,[eax*4]

        .if [rcx].flags & _TW_USESHADE

            lea r8d,[r8d+edx*4-4]
            add eax,r8d
        .endif

        .if malloc( eax )

            mov rcx,rbx
            mov [rcx].window,rax
            mov rax,rcx

        .else
            free( rbx )
        .endif
    .endif

    mov rdx,_this
    .if rdx

        mov [rdx],rax
    .endif
    ret

twindow::twindow endp

Install proc private uses rdi

    .if malloc( sizeof(twindowVtbl) )

        mov virtual_table,rax
        mov rdi,rax

        _method macro entry
            lea rax,twindow_&entry
            exitm<stosq>
            endm

            _method(Release)
            _method(show)
            _method(hide)
            mov rax,console
            mov rdx,[rax]
            mov rax,[rdx].tconsoleVtbl.read
            stosq
            mov rax,[rdx].tconsoleVtbl.write
            stosq
            _method(move)
            _method(showsh)
            _method(hidesh)
            _method(clear)
            _method(center)
            _method(settitle)
            _method(putxyw)
            _method(putxya)
            _method(putxyf)
            _method(putpath)

    .endif
    ret

Install endp

.pragma(init(Install, 60))

    end
