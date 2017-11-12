/* PARSEVEX.C--
 * Copyright (C) 2017 Asmc Developers
 *
 * Change history:
 * 2017-11-08 - created
 */
#include <globals.h>
#include <parser.h>

int parsevex( char *string, unsigned char *result )
{

    char *p = string;

    switch ( *p ) {

    case 'k': /* {k1} */
        if ( p[1] < '1' || p[1] > '7' || p[2] )
            break;
        *result |= p[1] - '0';
        return 1;

    case '1': /* {1to2} {1to4} {1to8} {1to16} */
        if ( p[1] != 't' || p[2] != 'o' )
            break;
        switch ( p[3] ) {
        case '1':
            if ( p[4] != '6' )
                break;
        case '4':
        case '8':
            *result |= 0x10; /* B */
            return 1;
        }
        break;
    case 'z': /* {z} */
        if ( p[1] == 0 ) {
            *result |= 0x80; /* Z */
            return 1;
        }
        break;

    case 'r': /* {rn-sae} {ru-sae} {rd-sae} {rz-sae} */
        if ( p[2] != '-' || p[3] != 's' )
            break;
        switch ( p[1] ) {
        case 'z':
            *result |= 0x70; /* B|L0|L1 */
        case 'd':
            *result |= 0x30; /* B|L0 */
        case 'n':
            *result |= 0x10; /* B */
            result[1] |= VX_SAE;
            return 1;
        case 'u':
            *result |= 0x50; /* B|L1 */
            result[1] |= VX_SAE;
            return 1;
        }
        break;
    case 's': /* {sae} */
        if ( p[1] != 'a' || p[2] != 'e' )
            break;
        *result |= 0x10; /* B */
        result[1] |= VX_SAE;
        return 1;
    }
    return 0;
}
