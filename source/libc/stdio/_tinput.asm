; _TINPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include errno.inc
include fltintrn.inc
include winnls.inc
include tchar.inc

DIGIT   union
q       int64_t ?
struct
 l      int_t ?
 h      int_t ?
ends
DIGIT   ends

_hextodec proto watcall :int_t {
    .if ( eax < '0' || eax > '9' )
        and eax,not ('a' - 'A')
        sub eax,'A'
        add eax,10 + '0'
    .endif
    }

_inc proto fastcall fileptr:LPFILE {
    _fgettc(fileptr)
    inc charcount
    }

_un_inc proto fastcall chr:int_t, fileptr:LPFILE {
    .if ( chr != -1 )
        _ungettc(chr, fileptr)
        dec charcount
    .endif
    }

    .code

_va_arg macro ap
if defined(__UNIX__) and defined(_AMD64_)
    dec argcnt
    .ifz
        mov ap,argptr
    .endif
endif
    mov rax,ap
    add ap,size_t
    retm<[rax]>
    endm

    assume rbx:tstring_t

_tinput proc uses rsi rdi rbx stream:LPFILE, format:tstring_t, argptr:ptr

   .new arglist:ptr
if defined(__UNIX__) and defined(_AMD64_)
   .new argxmm:ptr
   .new argcnt:int_t
   .new argcntsave:int_t
endif
   .new floatstring[_CVTBUFSIZE+3]:char_t
   .new number:DIGIT
   .new pointer:ptr
   .new start:ptr
   .new arglistsave:ptr
   .new nFloatStrUsed:int_t
   .new _ch:int_t
   .new tch:int_t
   .new charcount:int_t
   .new comchr:int_t
   .new count:int_t
   .new started:int_t
   .new width:int_t
   .new widthset:int_t
   .new rngch:tuchar_t
   .new last:tuchar_t
   .new prevchar:tuchar_t
   .new done_flag:char_t
   .new longone:char_t
   .new integer64:char_t
   .new widechar:char_t
   .new negative:char_t
   .new suppress:char_t
   .new match:char_t
   .new fl_wchar_arg:char_t

    ldr rbx,format
    .if ( rbx == NULL || ldr(stream) == NULL )
        .return( _set_errno( EINVAL ) )
    .endif

ifdef _WIN64
ifdef __UNIX__
    mov eax,[rdx]
    mov ecx,[rdx+4]
    add rax,[rdx+16]
    add rcx,[rdx+16]
    mov arglist,rax
    mov argxmm,rcx
    mov argptr,[rdx+8]
    mov ecx,7
    mov eax,[rdx]
    shr eax,3
    sub ecx,eax
    mov argcnt,ecx
else
    mov arglist,r8
endif
else
    mov arglist,argptr
endif

    xor eax,eax
    mov count,eax
    mov charcount,eax
    mov match,al
    mov _ch,eax
    mov arglistsave,rax
    mov pointer,rax
    mov nFloatStrUsed,eax

    .while 1

        movzx ecx,[rbx]
        .break .if ( !ecx )

        .ifd _istspace(ecx)

            .while 1

                mov tch,_inc(stream)
                .return .if ( eax == -1 )
                .ifd ( _istspace(eax) == 0 )
                    _un_inc(tch, stream)
                    .break
                .endif
            .endw
            .for ( :: rbx+=tchar_t )

                movzx ecx,[rbx]
                .break .ifd !_istspace(ecx)
            .endf
            .continue
        .endif

        .if ( [rbx] == '%' && [rbx+tchar_t] != '%' )

            xor eax,eax
            mov size_t ptr number.q,rax
ifndef _WIN64
            mov number.h,eax
endif
            mov prevchar,_tal
            mov width,eax
            mov widthset,eax
            mov started,eax
            mov fl_wchar_arg,al
            mov done_flag,al
            mov suppress,al
            mov negative,al
            mov widechar,al
            mov longone,1
            mov integer64,al

            .while ( !done_flag )

                add rbx,tchar_t
                movzx ecx,[rbx]
                mov comchr,ecx

                .ifd _istdigit( ecx )

                    inc     widthset
                    imul    eax,width,10
                    mov     ecx,comchr
                    sub     ecx,'0'
                    add     eax,ecx
                    mov     width,eax

                .else

                    mov eax,comchr
                    .switch eax
                    .case 'F'
                    .case 'N'
                       .endc
                    .case 'h'
                        dec longone
                        dec widechar
                       .endc
                    .case 'I'
                        movzx ecx,[rbx+tchar_t]
                        movzx edx,[rbx+tchar_t*2]
                        .if ( ecx == '6' && edx == '4' )

                            add rbx,2*tchar_t
                            inc integer64
                           .endc

                        .elseif ( ecx == '3' && edx == '2' )

                            add rbx,2*tchar_t
                           .endc

                        .elseif ( ecx == 'd' || ecx == 'i' || ecx == 'o' || ecx == 'x' || ecx == 'X' )
ifdef _WIN64
                            inc integer64
endif
                           .endc
                        .endif
ifdef _WIN64
                        inc integer64
endif
                        jmp DEFAULT_LABEL

                    .case 'L'
                        inc longone
                       .endc

                    .case 'l'
                        .if ( [rbx+tchar_t] == 'l' )
                            add rbx,tchar_t
                            inc integer64
                           .endc
                        .else
                            inc longone
                        .endif
                        ; NOBREAK
                    .case 'w'
                        inc widechar
                       .endc
                    .case '*'
                        inc suppress
                       .endc
                    .default
DEFAULT_LABEL:
                        inc done_flag
                       .endc
                    .endsw
                .endif
            .endw

            .if ( !suppress )
                mov arglistsave,arglist
if defined(__UNIX__) and defined(_AMD64_)
                mov argcntsave,argcnt
endif
                mov pointer,_va_arg(arglist)
            .else
                mov pointer,NULL
            .endif

            mov done_flag,0
            movzx eax,[rbx]

            .if ( !widechar )
                .if ( eax == 'S' || eax == 'C' )
ifdef _UNICODE
                    dec widechar
                .else
                    inc widechar
else
                    inc widechar
                .else
                    dec widechar
endif
                .endif
            .endif

            or eax,( 'a' - 'A' )
            mov comchr,eax

            .if ( eax != 'n' )

                .if ( eax != 'c' )

                    .while 1

                        mov _ch,_inc(stream)
                        .break .if ( eax == -1 )
                        .break .ifd ( _istspace(eax) == 0 )
                    .endw
                .else
                    mov _ch,_inc(stream)
                .endif
            .endif

            .if ( comchr != 'n' )

                .if ( _ch == -1 )
                    jmp error_return
                .endif
            .endif

            .if ( !widthset || width )

                mov eax,comchr
                .switch eax
                .case 'c'
                    .if ( !widthset )
                        inc widthset
                        inc width
                    .endif
                    .if ( widechar > 0 )
                        inc fl_wchar_arg
                    .endif
                    jmp scanit
                .case 's'
                    .if ( widechar > 0 )
                        inc fl_wchar_arg
                    .endif
scanit:
                    mov start,pointer
                    _un_inc(_ch, stream)

                    .while 1

                        mov eax,width
                        .if ( widthset )

                            dec width
                           .break .if ( eax == 0 )
                        .endif

                        mov _ch,_inc(stream)
                        mov ecx,comchr
                        .if ( eax != -1 && ( ecx == 'c' || ( ecx == 's' && ( !( eax >= 9 && eax <= 13 ) && eax != ' ' ) ) ) )

                            .if ( !suppress )

                                mov rcx,pointer
                                mov eax,_ch
                                .if ( fl_wchar_arg )
if not defined(_UNICODE) and not defined(__UNIX__)
                                    mov tch,eax
                                    mov _ch,'?'
                                    .ifd isleadbyte( eax )

                                        _inc(stream)
                                        mov byte ptr tch[1],al
                                        mov ecx,2
                                    .else
                                        mov ecx,1
                                    .endif
                                    MultiByteToWideChar(CP_ACP, 0, &tch, ecx, &_ch, 1)
                                    mov eax,_ch
                                    mov rcx,pointer
endif
                                    mov [rcx],ax
                                    add rcx,2
                                .else
                                    mov [rcx],al
                                    inc rcx
                                .endif
                                mov pointer,rcx
                            .else
                                add start,tchar_t
                            .endif
                        .else
                            _un_inc(_ch, stream)
                            .break
                        .endif
                    .endw

                    mov rcx,pointer
                    .if ( start != rcx )
                        .if ( !suppress )
                            inc count
                            .if ( comchr != 'c' )

                                xor eax,eax
                                .if ( fl_wchar_arg )
                                    mov [rcx],ax
                                .else
                                    mov [rcx],al
                                .endif
                            .endif
                        .else
                            jmp error_return
                        .endif
                    .endif
                    .endc

                .case 'i'
                    mov comchr,'d'
                .case 'x'

                    .if ( _ch == '-' )

                        inc negative
                        jmp x_incwidth

                    .elseif ( _ch == '+' )
x_incwidth:
                        dec width
                        .if ( !width && widthset )
                            inc done_flag
                        .else
                            mov _ch,_inc(stream)
                        .endif
                    .endif

                    .if ( _ch == '0' )

                        mov _ch,_inc(stream)
                        .if ( eax == 'x' || eax == 'X' )

                            mov _ch,_inc(stream)

                            .if ( widthset )
                                sub width,2
                                .if ( width < 1 )
                                    inc done_flag
                                .endif
                            .endif
                            mov comchr,'x'
                        .else
                            inc started
                            .if ( comchr != 'x' )
                                dec width
                                .if ( widthset && !width )
                                    inc done_flag
                                .endif
                                mov comchr,'o'
                            .else
                                _un_inc(_ch, stream)
                                mov _ch,'0'
                            .endif
                        .endif
                    .endif
                    jmp getnum

                .case 'p'
                    mov longone,1
ifdef _WIN64
                    inc integer64
endif
                .case 'o'
                .case 'u'
                .case 'd'

                    .if ( _ch == '-' )

                        inc negative
                        jmp d_incwidth

                    .elseif ( _ch == '+' )
d_incwidth:
                        dec width
                        .if ( !width && widthset )
                            inc done_flag
                        .else
                            mov _ch,_inc(stream)
                        .endif
                    .endif

getnum:
                    .while ( !done_flag )

                        .if ( comchr == 'x' || comchr == 'p' )

                            .ifd _istxdigit(_ch)
ifdef _WIN64
                                shl number.q,4
else
                                mov eax,number.l
                                mov edx,number.h
                                shld edx,eax,4
                                shl eax,4
                                mov number.l,eax
                                mov number.h,edx
endif
                                mov _ch,_hextodec(_ch)
                            .else
                                inc done_flag
                            .endif

                        .elseifd _istdigit(_ch)

                            .if ( comchr == 'o' )
                                .if ( _ch <= '8' )
ifdef _WIN64
                                    shl number.q,3
else
                                    mov eax,number.l
                                    mov edx,number.h
                                    shld edx,eax,3
                                    shl eax,3
                                    mov number.l,eax
                                    mov number.h,edx
endif
                                .else
                                    inc done_flag
                                .endif
                            .else
ifdef _WIN64
                                imul rax,number.q,10
                                mov number.q,rax
else
                                mov eax,number.l
                                mov edx,number.h
                                mov ecx,eax
                                mov edi,edx
                                shld edx,eax,3
                                shl eax,3
                                add eax,ecx
                                adc edx,edi
                                add eax,ecx
                                adc edx,edi
                                mov number.l,eax
                                mov number.h,edx
endif
                            .endif
                        .else
                            inc done_flag
                        .endif

                        .if ( !done_flag )

                            inc started
                            mov eax,_ch
                            sub eax,'0'
                            add size_t ptr number.q,rax
ifndef _WIN64
                            adc number.h,0
endif
                            dec width

                            .if ( widthset && !width )
                                inc done_flag
                            .else
                                mov _ch,_inc(stream)
                            .endif
                        .else
                            _un_inc(_ch, stream)
                        .endif
                    .endw

                    .if ( negative )
ifdef _WIN64
                        neg number.q
else
                        mov eax,number.l
                        mov edx,number.h
                        neg eax
                        adc edx,0
                        neg edx
                        mov number.l,eax
                        mov number.h,edx
endif
                    .endif

                    .if ( comchr == 'F' )
                        mov started,0
                    .endif

                    .if ( started )
                        .if ( !suppress )

                            inc count
assign_num:
                            mov rcx,pointer
                            mov rax,size_t ptr number.q
                            .if ( integer64 )
                                mov [rcx],rax
ifndef _WIN64
                                mov eax,number.h
                                mov [ecx+4],eax
endif
                            .elseif ( longone )
                                mov [rcx],eax
                            .else
                                mov [rcx],ax
                            .endif
                        .endif
                    .else
                        jmp error_return
                    .endif
                    .endc

                .case 'n'
                    mov eax,charcount
                    mov size_t ptr number.q,rax
                    .if ( !suppress )
                        jmp assign_num
                    .endif
                    .endc


                .case 'e'
                .case 'f'
                .case 'g'
                    mov nFloatStrUsed,0
                    mov eax,_ch
                    .if ( eax == '-' )

                        mov ecx,nFloatStrUsed
                        inc nFloatStrUsed
                        mov floatstring[rcx],al
                        jmp f_incwidth

                    .elseif ( eax == '+' )
f_incwidth:
                        dec width
                        mov _ch,_inc(stream)
                    .endif

                    .if ( !widthset )
                        mov width,-1
                    .endif

                    .whiled _istdigit(_ch)

                        mov eax,width
                        dec width
                        .break .if !eax

                        inc started
                        mov ecx,nFloatStrUsed
                        mov eax,_ch
                        inc nFloatStrUsed
                        mov floatstring[rcx],al
                        .if ( ecx >= lengthof(floatstring)-1 )
                            jmp error_return
                        .endif
                        mov _ch,_inc(stream)
                    .endw

                    xor eax,eax
                    .if ( _ch == '.' )

                        mov eax,width
                        dec width
                    .endif

                    .if ( eax )

                        mov _ch,_inc(stream)
                        mov ecx,nFloatStrUsed
                        mov eax,'.'
                        inc nFloatStrUsed
                        mov floatstring[rcx],al
                        .if ( ecx >= lengthof(floatstring)-1 )
                            jmp error_return
                        .endif

                        .whiled _istdigit(_ch)

                            mov eax,width
                            dec width
                            .break .if !eax

                            inc started
                            mov ecx,nFloatStrUsed
                            mov eax,_ch
                            inc nFloatStrUsed
                            mov floatstring[rcx],al
                            .if ( ecx >= lengthof(floatstring)-1 )
                                jmp error_return
                            .endif
                            mov _ch,_inc(stream)
                        .endw
                    .endif

                    xor eax,eax
                    .if ( started && ( _ch == 'e' || _ch == 'E' ) )

                        mov eax,width
                        dec width
                    .endif

                    .if ( eax )

                        mov ecx,nFloatStrUsed
                        mov eax,'e'
                        inc nFloatStrUsed
                        mov floatstring[rcx],al
                        .if ( ecx >= lengthof(floatstring)-1 )
                            jmp error_return
                        .endif
                        mov _ch,_inc(stream)

                        .if ( _ch == '-' )

                            mov ecx,nFloatStrUsed
                            mov eax,'-'
                            inc nFloatStrUsed
                            mov floatstring[rcx],al
                            .if ( ecx >= lengthof(floatstring)-1 )
                                jmp error_return
                            .endif
                            jmp f_incwidth2

                        .elseif ( _ch == '+' )
f_incwidth2:
                            mov eax,width
                            dec width
                            .if ( !eax )
                                inc width
                            .else
                                mov _ch,_inc(stream)
                            .endif
                        .endif

                        .whiled _istdigit(_ch)

                            mov eax,width
                            dec width
                            .break .if !eax
                            inc started
                            mov ecx,nFloatStrUsed
                            mov eax,_ch
                            inc nFloatStrUsed
                            mov floatstring[rcx],al
                            .if ( ecx >= lengthof(floatstring)-1 )
                                jmp error_return
                            .endif
                            mov _ch,_inc(stream)
                        .endw

                    .endif
                    _un_inc(_ch, stream)

                    .if ( started )
                        .if ( !suppress )

                            inc count
                            mov ecx,nFloatStrUsed
                            xor eax,eax
                            mov floatstring[rcx],al
                            .if ( longone > 1 )
                                _atodbl(pointer, &floatstring)
                            .else
                                _atoflt(pointer, &floatstring)
                            .endif
                        .endif
                    .else
                        jmp error_return
                    .endif
                    .endc

                .default
                    movzx eax,[rbx]
                    .if ( eax != _ch )
                        _un_inc(_ch, stream)
                        jmp error_return
                    .else
                        dec match
                    .endif
                    .if ( !suppress )
                        mov arglist,arglistsave
if defined(__UNIX__) and defined(_AMD64_)
                        mov argcnt,argcntsave
endif
                    .endif
                .endsw
                inc match
            .else
                _un_inc(_ch, stream)
                jmp error_return
            .endif
            add rbx,tchar_t

        .else

            .if ( [rbx] == '%' && [rbx+tchar_t] == '%' )
                add rbx,tchar_t
            .endif
            mov _ch,_inc(stream)
            movzx ecx,[rbx]
            add rbx,tchar_t
            .if ( ecx != eax )
                _un_inc(eax, stream)
                jmp error_return
            .endif
if not defined(_UNICODE) and not defined(__UNIX__)
            .ifd isleadbyte( _ch )

                _inc(stream)
                movzx ecx,[rbx]
                add rbx,tchar_t

                .if ( ecx != eax )

                    _un_inc(eax, stream)
                    _un_inc(_ch, stream)
                    jmp error_return
                .endif
                dec charcount
            .endif
endif
        .endif
        .if ( _ch == -1 && ( [rbx] != '%' || [rbx+tchar_t] != 'n' ) )
            .break
        .endif
    .endw

error_return:
    mov eax,count
    .if ( _ch == -1 )
        .if ( !eax && !match )
            mov eax,-1
        .endif
    .endif
    ret

_tinput endp

    end
