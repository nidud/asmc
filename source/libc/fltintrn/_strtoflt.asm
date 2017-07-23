include ltype.inc
include fltintrn.inc
include crtl.inc

.data
_real dt 0
flt S_STRFLT <0,0,0,_real>

.code

_strtoflt proc public uses esi edi ebx string:LPSTR

  local digits
  local buffer[64]:BYTE

    .repeat

        _fltsetflags(&flt, string, 0)
        .break .if eax & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID
        .if eax & _ST_ISHEX
            _hextoflt(&flt, &buffer)
        .else
            _destoflt(&flt, &buffer)
        .endif
        mov digits,eax
        mov edx,flt.mantissa
        .if !eax
            or flt.flags,_ST_ISZERO
            mov [edx],eax
            mov [edx+4],eax
            mov [edx+8],ax
            .break
        .endif
        mov buffer[eax],0

        .if flt.flags & _ST_ISHEX
            lea ebx,buffer
            mov esi,digits
            xor edi,edi
            xor edx,edx
            .while edi <= 8 && esi
                dec esi
                movzx eax,byte ptr [ebx]
                inc ebx
                and eax,not 30h
                bt  eax,6
                sbb ecx,ecx
                and ecx,55
                sub eax,ecx
                lea ecx,[edi*4-28]
                neg ecx
                shl eax,cl
                or  edx,eax
                add flt.exponent,4
                inc edi
            .endw
            push edx
            xor edi,edi
            xor edx,edx
            .while edi <= 8 && esi
                dec esi
                movzx eax,byte ptr [ebx]
                inc ebx
                and eax,not 30h
                bt  eax,6
                sbb ecx,ecx
                and ecx,55
                sub eax,ecx
                lea ecx,[edi*4-28]
                neg ecx
                shl eax,cl
                or  edx,eax
                add flt.exponent,4
                inc edi
            .endw
            pop eax
            .while !(eax & 0x80000000)
                shl eax,1
                bt  edx,31
                sbb ecx,ecx
                and ecx,1
                or  eax,ecx
                shl edx,1
                dec flt.exponent
            .endw
            dec flt.exponent
            mov ecx,flt.exponent
            add ecx,00003FFFh
            mov edi,flt.mantissa
            mov [edi],edx
            mov [edi+4],eax
            mov [edi+8],cx
        .else
            push ebp
            lea esi,buffer
            xor edx,edx
            xor ecx,ecx
            xor ebp,ebp
            .while byte ptr [esi]
                mov edi,edx ; val = val * 10 + c
                mov ebx,ecx
                mov eax,ebp
                add ebp,ebp
                adc ecx,ecx
                adc edx,edx
                add ebp,ebp
                adc ecx,ecx
                adc edx,edx
                add ebp,eax
                adc ecx,ebx
                adc edx,edi
                add ebp,ebp
                adc ecx,ecx
                adc edx,edx
                mov al,[esi]
                and eax,0x0F
                add ebp,eax
                adc ecx,0
                adc edx,0
                inc esi
            .endw
            mov eax,ecx
            mov edi,16478
            mov esi,eax
            or  esi,edx
            or  esi,ebp
            .ifnz
                .if !edx
                    mov edx,eax
                    mov eax,ebp
                    xor ebp,ebp
                    sub edi,32
                    .if !edx
                        mov edx,eax
                        mov eax,ebp
                        xor ebp,ebp
                        sub edi,32
                    .endif
                .endif
                .while !(edx & 0x80000000)
                    dec edi
                    add ebp,ebp
                    adc eax,eax
                    adc edx,edx
                .endw
                add ebp,ebp
                adc eax,0
                adc edx,0
                .if CARRY?
                    rcr edx,1
                    inc edi
                .endif
                mov esi,edi
            .endif
            pop ebp
            mov ecx,flt.mantissa
            mov [ecx],eax
            mov [ecx+4],edx
            mov [ecx+8],si
            .if flt.exponent != 0
                _fltscale(&flt)
            .endif
        .endif

        .if flt.flags & _ST_NEGNUM
            mov edx,flt.mantissa
            or WORD PTR [edx+8],8000h
        .endif
        mov eax,flt.exponent
        add eax,digits
        dec eax
        .ifs eax > 4932
            or flt.flags,_ST_OVERFLOW
        .endif
        .ifs eax < -4932
            or flt.flags,_ST_UNDERFLOW
        .endif
    .until 1
    lea eax,flt
    ret

_strtoflt ENDP

    END
