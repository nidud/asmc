#ifndef _HLLEXT_H_
#define _HLLEXT_H_

#include <memalloc.h>
#include <parser.h>
#include <expreval.h>
#include <segment.h>
#include <listing.h>
#include <lqueue.h>
#include <tokenize.h>
#include <input.h>
#include <reswords.h>

extern int NoLineStore;
extern int GetHllLabel(void);
extern char *GetLabelStr(int, char *);
extern int ExpandLine(char *, struct asm_tok[]);
extern int ExpandCStrings(struct asm_tok tokenarray[]);
extern int EvaluateHllExpression(struct hll_item *, int *, struct asm_tok[], int, int, char *);
extern int ExpandHllProc(char *, int, struct asm_tok[]);
extern int ExpandHllExpression(struct hll_item *, int *, struct asm_tok[], int, int, char *);
extern int QueueTestLines(char *);
extern int HllContinueIf(struct hll_item *, int *, char *, struct asm_tok[], int, struct hll_item *);
extern int GenerateCString( int, struct asm_tok[] );

#define MIN_JTABLE 8
#define LABELSIZE 8
#define LABELSGLOBAL 0 /* make the generated labels global */
#define JMPPREFIX      /* define spaces before "jmp" or "loop" */
#define LABELFMT "@C%04X"

/* v2.10: static variables moved to ModuleInfo */
#define HllStack ModuleInfo.g.HllStack
#define HllFree	 ModuleInfo.g.HllFree

#if LABELSGLOBAL
#define LABELQUAL "::"
#else
#define LABELQUAL ":"
#endif

#define EOLCHAR '\n' /* line termination char in generated source */
#define EOLSTR	"\n"

/* values for struct hll_item.cmd */
enum hll_cmd {
    HLL_IF,
    HLL_WHILE,
    HLL_REPEAT,
    HLL_BREAK,	/* .IF behind .BREAK or .CONTINUE */
    HLL_SWITCH
};

/* index values for struct hll_item.labels[] */
enum hll_label_index {
    LTEST,	/* test (loop) condition */
    LEXIT,	/* block exit		 */
    LSTART,	/* loop start		 */
    LSTARTSW,	/* switch start		 */
};

/* values for struct hll_item.flags */
enum hll_flags {
    HLLF_ELSEOCCURED	= 0x01,
    HLLF_ELSEIF		= 0x02,
    HLLF_WHILE		= 0x04,
    HLLF_EXPRESSION	= 0x08,
    HLLF_DEFAULT	= 0x10,
    HLLF_DELAYED	= 0x20,		// set by DelayExpand()
    HLLF_NOTEST		= 0x40,		// direct jump..
    HLLF_ARGREG		= 0x80,		// register 16/32/64-bit size_t
    HLLF_ARGMEM		= 0x0100,	// memory if set, else register
    HLLF_ARG16		= 0x0200,	// size: 8/16/32/64
    HLLF_ARG32		= 0x0400,
    HLLF_ARG64		= 0x0800,
    HLLF_ARG3264	= 0x1000,	// .switch eax in 64-bit assumend rax
    HLLF_NUM		= 0x2000,	// .case arg is const
    HLLF_TABLE		= 0x4000,	// .case is in jump table
    HLLF_ENDCOCCUR	= 0x8000,	// jmp exit in .case omitted
    HLLF_IFB		= 0x00010000,	// .ifb proc() --> al
    HLLF_IFW		= 0x00020000,	// .ifw proc() --> ax
    HLLF_IFD		= 0x00040000,	// .ifd proc() --> eax
    HLLF_IFS		= 0x00080000,	// Signed compare --> CMP REG,val
    HLLF_PASCAL		= 0x00100000,	// .continue(0) [.if]
    HLLF_JTABLE		= 0x00200000,	// if HLLF_NOTEST direct .case jump
    HLLF_JTDATA		= 0x00400000	// Jump table in data segment -- HLLF_NOTEST

};

/* item for .IF, .WHILE, .REPEAT, ... */
struct hll_item {
union {
    struct hll_item	*next;
    uint_32		index;		/* v2.24 added */
};
    struct hll_item	*caselist;
    uint_32		labels[4];	/* labels for LTEST, LEXIT, LSTART */
    char		*condlines;	/* .WHILE-blocks only: lines to add after 'test' label */
    int			cmd;		/* start cmd (IF, WHILE, REPEAT) */
    int			flags;		/* v2.08: added */
};

/* v2.08: struct added */
struct hll_opnd {
    char    *lastjmp;
    uint_32 lasttruelabel; /* v2.08: new member */
};

#endif
