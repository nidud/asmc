; _EOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_eof proc handle:SINT

   .new current_offset:qword

    _lseeki64( handle, 0, SEEK_CUR )
ifdef _WIN64

    .if ( rax != -1 )

        mov current_offset,rax

        .if ( _lseeki64( handle, 0, SEEK_END ) != -1 )

            .if ( rax != current_offset )
else
    .if !( eax == -1 && edx == -1 )

        mov dword ptr current_offset[0],eax
        mov dword ptr current_offset[4],edx

        _lseeki64( handle, 0, SEEK_END )

        .if !( eax == -1 && edx == -1 )

            .if ( eax != dword ptr current_offset[0] ||
                  edx != dword ptr current_offset[4] )
endif

                _lseeki64( handle, current_offset, SEEK_SET )
                xor eax,eax
            .else
                mov eax,1
            .endif
        .endif
    .endif
    ret

_eof endp

    end
