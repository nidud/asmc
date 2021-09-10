;;
;; https://msdn.microsoft.com/en-us/library/a0w705h5.aspx
;;
;; _lrotl(unsigned value, int times) rotate left
;; _lrotr(unsigned value, int times) rotate right
;;

include stdio.inc
include intrin.inc
include tchar.inc

.code

main proc

  local val

    mov val,0x0fac35791

    printf( "0x%8.8lx rotated left eight times is 0x%8.8lx\n",
            val, _lrotl( val, 8 ) )
    printf( "0x%8.8lx rotated right four times is 0x%8.8lx\n",
            val, _lrotr( val, 4 ) )
    ret
main endp

    end _tstart
