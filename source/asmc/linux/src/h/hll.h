/****************************************************************************
*
* Description:	hll constructs .IF, ...
*
****************************************************************************/


#ifndef _HLL_H_
#define _HLL_H_

extern void HllInit( int );    /* reset counter for hll labels */
extern void HllCheckOpen( void );

extern void ClassInit( void );
extern void ClassCheckOpen( void );

extern void PragmaInit( void );
extern void PragmaCheckOpen( void );

#endif
