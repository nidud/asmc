; PARSEVEX.C--
; Copyright (C) 2017 Asmc Developers
;
; Change history:
; 2017-11-08 - created
;
include asmc.inc

.code

parsevex proc string:string_t, result:string_t

    mov edx,string
    mov ecx,result
    mov eax,[edx]

    .switch ( al )

      .case 9
      .case ' '
        inc edx
        mov eax,[edx]
        .gotosw

      .case 'k' ; {k1}
        .endc .if ah < '1'
        .endc .if ah > '7'
        .endc .if eax & 0xFF0000
        sub ah,'0'
        or  [ecx],ah
        .return 1

      .case '1' ; {1to2} {1to4} {1to8} {1to16}
        .endc .if ah != 't'
        shr eax,24
        .switch ( al )
          .case '1'
            .endc .if byte ptr [edx+4] != '6'
          .case '2'
          .case '4'
          .case '8'
            or  byte ptr [ecx],0x10
            .return 1
        .endsw
        .endc

      .case 'z' ; {z}
        .endc .if ah
        or byte ptr [ecx],0x80
        .return 1

      .case 'r' ; {rn-sae} {ru-sae} {rd-sae} {rz-sae}
        .endc .if byte ptr [edx+2] != '-'
        .endc .if byte ptr [edx+3] != 's'
        mov edx,0x2000
        .switch ( ah )
          .case 'u'
            or dl,0x50  ; B|L1
            .endc
          .case 'z'
            or dl,0x70  ; B|L0|L1
          .case 'd'
            or dl,0x30  ; B|L0
          .case 'n'
            or dl,0x10  ; B
        .endsw
        .if dl
            or [ecx],dx
            .return 1
        .endif
        .endc

      .case 's' ; {sae}
        .endc .if eax != 'eas'
        mov edx,0x2010  ; B
        or [ecx],dx
        .return 1
    .endsw
    xor eax,eax
    ret

parsevex endp

    end

