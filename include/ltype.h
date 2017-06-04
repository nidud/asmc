#ifndef __INC_LTYPE
#define __INC_LTYPE
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#define _LUPPER		0x01	/* upper case letter */
#define _LLOWER		0x02	/* lower case letter */
#define _LDIGIT		0x04	/* digit[0-9] */
#define _LSPACE		0x08	/* tab, carriage return, newline, */
				/* vertical tab or form feed */
#define _LPUNCT		0x10	/* punctuation character */
#define _LCONTROL	0x20	/* control character */
#define _LABEL		0x40	/* UPPER + LOWER + '@' + '_' + '$' + '?' */
#define _LHEX		0x80	/* hexadecimal digit */

extern unsigned char _ltype[]; /* Label type array */

#define islalnum(c)  (_ltype[(unsigned char)(c) + 1] & (_LDIGIT | _LUPPER | _LLOWER))
#define islalpha(c)  (_ltype[(unsigned char)(c) + 1] & (_LUPPER | _LLOWER))
#define islascii(c)  ((unsigned char)(c) < 128)
#define islcntrl(c)  (_ltype[(unsigned char)(c) + 1] & _LCONTROL)
#define isldigit(c)  (_ltype[(unsigned char)(c) + 1] & _LDIGIT)
#define islgraph(c)  ((unsigned char)(c) >= 0x21 && (unsigned char)(c) <= 0x7e)
#define isllower(c)  (_ltype[(unsigned char)(c) + 1] & _LLOWER)
#define islprint(c)  ((unsigned char)(c) >= 0x20 && (unsigned char)(c) <= 0x7e)
#define islpunct(c)  (_ltype[(unsigned char)(c) + 1] & _LPUNCT)
#define islspace(c)  (_ltype[(unsigned char)(c) + 1] & _LSPACE)
#define islupper(c)  (_ltype[(unsigned char)(c) + 1] & _LUPPER)
#define islxdigit(c) (_ltype[(unsigned char)(c) + 1] & _LHEX)

#endif /* __INC_LTYPE */
