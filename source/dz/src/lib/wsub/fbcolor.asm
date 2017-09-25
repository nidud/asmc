include consx.inc
include io.inc
include cfini.inc
include string.inc
include stdlib.inc
include wsub.inc
include strlib.inc

    .code

fbcolor proc uses esi edi edx ecx fp:ptr S_FBLK

    mov esi,fp

    .while  1

        .if !([esi].S_FBLK.fb_flag & _A_SUBDIR)

            lea edi,[esi].S_FBLK.fb_name
            .if strext(edi)

                lea edi,[eax+1]
            .endif

            .if CFGetSection("FileColor")

                .if INIGetEntry(eax, edi)

                    .if strtolx(eax) <= 15

                        shl eax,4
                        .if al != at_background[B_Panel]

                            shr eax,4
                            .break
                        .endif
                    .endif
                .endif
            .endif
        .endif

        mov eax,[esi].S_FBLK.fb_flag
        .switch
          .case eax & _FB_SELECTED
            mov al,at_foreground[F_Panel]
            .break
          .case eax & _FB_UPDIR
            mov al,7
            .break
          .case eax & _FB_ROOTDIR
          .case eax & _A_SYSTEM
            mov al,at_foreground[F_System]
            .break
          .case eax & _A_HIDDEN
            mov al,at_foreground[F_Hidden]
            .break
          .case eax & _A_SUBDIR
            mov al,at_foreground[F_Subdir]
            .break
          .default
            mov al,at_foreground[F_Files]
            .break
        .endsw
    .endw
    or  al,at_background[B_Panel]
    movzx   eax,al
    ret

fbcolor endp

    END
