/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	handle the line queue.
*		this queue is used for "generated code".
*
****************************************************************************/

#include <stdarg.h>

#include <globals.h>
#include <memalloc.h>
#include <reswords.h>
#include <input.h>
#include <parser.h>
#include <preproc.h>

extern struct ReservedWord  ResWordTable[];

/* item of a line queue */
struct lq_line {
    struct lq_line *next;
    char line[1];
};

#define line_queue  ModuleInfo.g.line_queue

/* free items of current line queue */

void DeleteLineQueue( void )
/**************************/
{
    struct qitem *curr;
    struct qitem *next;
    for( curr = line_queue.head; curr; curr = next ) {
	next = curr->next;
	MemFree( curr );
    }
    line_queue.head = NULL;
}

void NewLineQueue( void )
/***********************/
{
}

/* Add a line to the current line queue. */

void AddLineQueue( const char *line )
/***********************************/
{
    unsigned i = strlen( line );
    struct lq_line   *new;

    new = (struct lq_line *)MemAlloc( sizeof( struct lq_line ) + i );
    new->next = NULL;
    memcpy( new->line, line, i + 1 );

    if( line_queue.head == NULL ) {
	line_queue.head = new;
    } else {
	/* insert at the tail */
	((struct qnode *)line_queue.tail)->next = new;
    }
    line_queue.tail = new;
    return;
}

/* Add a line to the current line queue, "printf" format. */

void AddLineQueueX( const char *fmt, ... )
/****************************************/
{
    va_list args;
    char *d;
    int i;
    int_32 l;
    const char *s;
    const char *p;
    char buffer[MAX_LINE_LEN];

    va_start( args, fmt );
    for ( s = fmt, d = buffer; *s; s++ ) {
	if ( *s == '%' ) {
	    s++;
	    switch ( *s ) {
	    case 'r':
		i = va_arg( args, int );
		GetResWName( i , d );
		d += ResWordTable[i].len;
		break;
#if 0
	    case 'c':
		ch = va_arg( args, char );
		*d++ = ch;
		*d = NULLC;
		break;
#endif
	    case 's':
		p = va_arg( args, char * );
		i = strlen( p );
		memcpy( d, p, i );
		d += i;
		*d = NULLC;
		break;
	    case 'd':
	    case 'u':
	    case 'x':
		l = va_arg( args, int );
		if ( *s == 'x' ) {
		    myltoa( l, d, 16, FALSE, FALSE );
		    d += strlen( d );
		} else {
		    myltoa( l, d, 10, l < 0, FALSE );
		    d += strlen( d );
		    /* v2.07: add a 't' suffix if radix is != 10 */
		    if ( ModuleInfo.radix != 10 )
			*d++ = 't';
		}
		break;
	    default:
		*d++ = *s;
	    }
	} else
	    *d++ = *s;
    }
    *d = NULLC;
    va_end( args );
    AddLineQueue( buffer );
    return;
}

/*
 * RunLineQueue() is called whenever generated code is to be assembled. It
 * - saves current input status
 * - processes the line queue
 * - restores input status
 */

void RunLineQueue( void )
/***********************/
{
    struct input_status oldstat;
    struct asm_tok *tokenarray;
    struct lq_line *currline = line_queue.head;

    /* v2.03: ensure the current source buffer is still aligned */
    tokenarray = PushInputStatus( &oldstat );
    ModuleInfo.GeneratedCode++;

    /* v2.11: line queues are no longer pushed onto the file stack.
     * Instead, the queue is processed directly here.
     */
    line_queue.head = NULL;

    for ( ; currline; ) {
	struct lq_line *nextline = currline->next;
	strcpy( CurrSource, currline->line );
	MemFree( currline );
	if ( PreprocessLine( CurrSource, tokenarray ) )
	    ParseLine( tokenarray );
	currline = nextline;
    }

    ModuleInfo.GeneratedCode--;
    PopInputStatus( &oldstat );
    return;
}

void InsertLineQueue(void)
{
    struct input_status oldstat;
    struct asm_tok *tokenarray;
    struct lq_line *currline = line_queue.head;
    int codestate = ModuleInfo.GeneratedCode;

    tokenarray = PushInputStatus( &oldstat );
    ModuleInfo.GeneratedCode = 0;

    line_queue.head = NULL;

    for ( ; currline; ) {
	struct lq_line *nextline = currline->next;
	strcpy( CurrSource, currline->line );
	MemFree( currline );
	if ( PreprocessLine( CurrSource, tokenarray ) )
	    ParseLine( tokenarray );
	currline = nextline;
    }
    ModuleInfo.GeneratedCode = codestate;
    PopInputStatus( &oldstat );
}

char *GetLineQueue( char *buffer )
{
    struct lq_line *curr = line_queue.head;

    if ( curr == NULL )
	return NULL;
    line_queue.head = curr->next;
    strcpy( buffer, curr->line );
    MemFree( curr );
    return buffer;
}
