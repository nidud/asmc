; COUT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdlib.inc

    ostream typedef ptr
    cout    equ <ostream::>
    endl    equ <"\n">

.template ostream

    .inline ostreamDWORD :dword {

        .new convbuf[64]:char_t

        _ultoa( ecx, &convbuf, 10 )
        _cputs( &convbuf )
        }

    .inline ostreamQWORD :qword {

        .new convbuf[64]:char_t

        _ui64toa( rcx, &convbuf, 10 )
        _cputs( &convbuf )
        }

    .inline ostreamSDWORD :sdword {

        .new convbuf[64]:char_t

        _itoa( ecx, &convbuf, 10 )
        _cputs( &convbuf )
        }

    .inline ostreamSQWORD :sqword {

        .new convbuf[64]:char_t

        _i64toa( rcx, &convbuf, 10 )
        _cputs( &convbuf )
        }

    .inline ostreamSBYTE :sbyte {
        movsx   ecx,_1
        ostream::ostreamSDWORD(ecx)
        }
    .inline ostreamSWORD :sword {
        movsx   ecx,_1
        ostream::ostreamSDWORD(ecx)
        }
    .inline ostreamBYTE :byte {
        movzx   ecx,_1
        ostream::ostreamDWORD(ecx)
        }
    .inline ostreamWORD :word {
        movzx   ecx,_1
        ostream::ostreamDWORD(ecx)
        }

    .inline ostreamREG8  :abs { ostream::ostreamBYTE(_1) }
    .inline ostreamREG16 :abs { ostream::ostreamWORD(_1) }
    .inline ostreamREG32 :abs { ostream::ostreamDWORD(_1) }
    .inline ostreamREG64 :abs { ostream::ostreamQWORD(_1) }

    .inline ostreamPSBYTE :abs { _cputs(_1) }
    .inline ostreamPWORD :abs { _cputws(_1) }

    .operator << :abs {
        cout typeid(ostream, _1)(_1)
        }
    .ends
