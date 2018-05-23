/* TEST.C--
 * Using cl.exe version 18 (__ImageBase) and lib64
 */
#include <stdio.h>

int main( int argc, char *argv[] )
{
    int dw;

    printf( "argc = %d\n", argc );

    switch ( argc ) {

    case 'a':
            dw = 0x20372C22;
            goto case_format;
    case 'b':
            dw = 0x20382C22;
            goto case_format;
    case 'f':
            dw = 0x32312C22;
            goto case_format;
    case 'n':
            dw = 0x30312C22;
            goto case_format;
    case 't':
            dw = 0x20392C22;

    case_format:

    case 1:
        printf( "argv[1] = %s\n", argv[1] );
    case 0:
        printf( "argv[0] = %s\n", argv[0] );
    }
    return 0;
}
