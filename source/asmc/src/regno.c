#include <globals.h>
#include <parser.h>
#include <reswords.h>
#include <memalloc.h>

int get_register( int reg, int size)
{
    int regno;

    if ( GetValueSp(reg) & OP_XMM )
        size = 16;

    regno = GetRegNo(reg);

    switch ( size ) {
    case 1:
        switch ( regno ) {
        case 0:
        case 1:
        case 2:
        case 3:
            return( regno + T_AL );
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return ( regno + T_SPL - 4 );
        }
        break;
    case 2:
        switch ( regno ) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return( regno + T_AX );
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return ( regno + T_R8W - 8 );
        }
        break;
    case 4:
        switch ( regno ) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return( regno + T_EAX );
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return ( regno + T_R8D - 8 );
        }
        break;
    case 8:
        switch ( regno ) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return( regno + T_RAX );
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return ( regno + T_R8 - 8 );
        }
        break;
    }
    return reg;
}

char *get_regname( int reg, int size )
{
    return GetResWName(get_register(reg, size), LclAlloc(8));
}
