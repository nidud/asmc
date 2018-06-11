; PARSEVEX.C--
; Copyright (C) 2017 Asmc Developers
;
; Change history:
; 2017-11-08 - created
;
.code

parsevex::

    .repeat

        mov eax,[rcx]

        .switch ( al )

          .case 9
          .case ' '
            inc rcx
            .continue(0)

          .case 'k'                 ; {k1}
            .endc .if ah < '1'
            .endc .if ah > '7'
            .endc .if eax & 0xFF0000
            sub ah,'0'
            or  [rdx],ah
            mov eax,1
            .break

          .case '1'                 ; {1to2} {1to4} {1to8} {1to16}
            .endc .if ah != 't'
            shr eax,24
            .switch ( al )
              .case '1'
                .endc .if byte ptr [rcx+4] != '6'
              .case '2'
              .case '4'
              .case '8'
                or  byte ptr [rdx],0x10
                mov eax,1
                .break
            .endsw
            .endc

          .case 'z'                 ; {z}
            .endc .if ah
            or  byte ptr [rdx],0x80
            mov eax,1
            .break

          .case 'r'                 ; {rn-sae} {ru-sae} {rd-sae} {rz-sae}
            .endc .if byte ptr [rcx+2] != '-'
            .endc .if byte ptr [rcx+3] != 's'
            mov ecx,0x2000
            .switch ( ah )
              .case 'u'
                or cl,0x50          ; B|L1
                .endc
              .case 'z'
                or cl,0x70          ; B|L0|L1
              .case 'd'
                or cl,0x30          ; B|L0
              .case 'n'
                or cl,0x10          ; B
            .endsw
            .if cl
                or [rdx],cx
                mov eax,1
                .break
            .endif
            .endc

          .case 's'                 ; {sae}
            .endc .if eax != 'eas'
            mov ecx,0x2010          ; B
            or [rdx],cx
            mov eax,1
            .break
        .endsw
        xor eax,eax
    .until 1
    ret

    end

