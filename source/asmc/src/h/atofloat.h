#ifndef ATOFLOAT_H
#define ATOFLOAT_H

extern void atofloat( void *, const char *, unsigned, bool, uint_8 );
#ifdef __LIBC__
extern void _qftod(void *, void *);
extern void _qftold(void *, void *);
#endif
#endif
