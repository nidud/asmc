
include stdio.inc

.code

main proc

    printf( "_dos_time()   %X\n", _dos_time() )
    printf( "_dos_date()   %X\n", _dos_date() )
    printf( "_dos_year()   %d\n", _dos_year() )
    printf( "_dos_month()  %d\n", _dos_month() )
    printf( "_dos_day()    %d\n", _dos_day() )
    printf( "_dos_hour()   %d\n", _dos_hour() )
    printf( "_dos_minute() %d\n", _dos_minute() )
    printf( "_dos_second() %d\n", _dos_second() )
    xor ax,ax
    ret

main endp

    end
