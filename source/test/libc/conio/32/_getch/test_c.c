#include <conio.h>
#include <ctype.h>

int main(void)
{
    int c;

    _cputs( "Type 'Y' when finished typing keys: " );

    do {

        c = toupper( _getch()  );

    } while ( c != 'Y' );

    _putch( c );
    _putch( 13 ); // Carriage return
    _putch( 10 ); // Line feed

    return 0;
}
