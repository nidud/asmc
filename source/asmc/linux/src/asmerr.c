//#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <limits.h>
#include <stdarg.h>

#include <globals.h>
#include <listing.h>
#include <input.h>

extern jmp_buf jmpenv;

void print_source_nesting_structure(void);
int GetCurrOffset(void);


/* Internal error */

static char INTER[] = "Internal Assembler Error";

/* Fatal Errors */

static char A1000[] = "cannot open file : %s";
static char A1001[] = "I/O error closing file : %s";
static char A1002[] = "I/O error writing file : %s";
//static char A1003[] = "I/O error reading file";
static char A1005[] = "assembler limit : macro parameter name table full";
static char A1006[] = "invalid command-line option: %s";
static char A1007[] = "nesting level too deep";
static char A1008[] = "unmatched macro nesting";
static char A1009[] = "line too long";
static char A1010[] = "unmatched block nesting : %s";
static char A1011[] = "directive must be in control block";
static char A1012[] = "error count exceeds 100; stopping assembly";
//static char A1013[] = "invalid numerical command-line argument : %d";
//static char A1014[] = "too many arguments";
//static char A1015[] = "statement too complex";
static char A1017[] = "missing source filename";
#define A1901 INTER

/* Nonfatal Errors */

//static char A2000[] = "memory operand not allowed in context";
//static char A2001[] = "immediate operand not allowed";
static char A2002[] = "cannot have more than one .ELSE clause per .IF block";
//static char A2003[] = "extra static characters after statement";
static char A2004[] = "symbol type conflict : %s";
static char A2005[] = "symbol redefinition : %s";
static char A2006[] = "undefined symbol : %s";
static char A2007[] = "non-benign record redefinition %s : %s";
static char A2008[] = "syntax error : %s";
static char A2009[] = "syntax error in expression";
static char A2010[] = "invalid type expression";
static char A2011[] = "distance invalid for word size of current segment";
static char A2012[] = "PROC, MACRO, or macro repeat directive must precede LOCAL";
static char A2013[] = ".MODEL must precede this directive";
static char A2014[] = "cannot define as public or external : %s";
static char A2015[] = "segment attributes cannot change : %s (%s)";
static char A2016[] = "expression expected";
//static char A2017[] = "operator expected";
static char A2018[] = "invalid use of external symbol : %s";
static char A2019[] = "operand must be RECORD type or field";
//static char A2020[] = "identifier not a record : identifier";
//static char A2021[] = "record constants cannot span line breaks";
static char A2022[] = "instruction operands must be the same size : %d - %d";
static char A2023[] = "instruction operand must have size";
static char A2024[] = "invalid operand size for instruction";
static char A2025[] = "operands must be in same segment";
static char A2026[] = "constant expected";
//static char A2027[] = "operand must be a memory expression";
static char A2028[] = "expression must be a code address";
static char A2029[] = "multiple base registers not allowed";
static char A2030[] = "multiple index registers not allowed";
static char A2031[] = "must be index or base register";
static char A2032[] = "invalid use of register";
static char A2033[] = "invalid INVOKE argument : %d";
static char A2034[] = "must be in segment block";
//static char A2035[] = "DUP too complex";
static char A2036[] = "too many initial values for structure: %s";
static char A2037[] = "statement not allowed inside structure definition";
//static char A2038[] = "missing operand for macro operator";
#define A2039 A1009
//static char A2040[] = "segment register not allowed in context";
static char A2041[] = "string or text literal too long";
//static char A2042[] = "statement too complex";
static char A2043[] = "identifier too long";
//static char A2044[] = "invalid static character in file";
static char A2045[] = "missing angle bracket or brace in literal";
static char A2046[] = "missing single or double quotation mark in string";
static char A2047[] = "empty (null) string";
static char A2048[] = "nondigit in number : %s";
//static char A2049[] = "syntax error in floating-point constant";
static char A2050[] = "real or BCD number not allowed";
static char A2051[] = "text item required";
static char A2052[] = "forced error : %s";
static char A2053[] = "forced error : value equal to 0 : %d: %s";
static char A2054[] = "forced error : value not equal to 0 : %d: %s";
static char A2055[] = "forced error : symbol not defined : %s";
static char A2056[] = "forced error : symbol defined : %s";
static char A2057[] = "forced error : string blank : %s: %s";
static char A2058[] = "forced error : string not blank : <%s>: %s";
static char A2059[] = "forced error : strings equal : <%s>: <%s>: %s";
static char A2060[] = "forced error : strings not equal : <%s>: <%s>: %s";
static char A2061[] = "[[[ELSE]]]IF2/.ERR2 not allowed : single-pass assembler";
static char A2062[] = "expression too complex for .UNTILCXZ";
static char A2063[] = "can ALIGN only to power of 2 : %u";
static char A2064[] = "struct alignment must be 1, 2, 4, 8, 16 or 32";
static char A2065[] = "expected : %s";
static char A2066[] = "incompatible CPU mode and segment size";
//static char A2067[] = "LOCK must be followed by a memory operation";
static char A2068[] = "instruction prefix not allowed";
//static char A2069[] = "no operands allowed for this instruction";
static char A2070[] = "invalid instruction operands";
static char A2071[] = "initializer too large for specified size";
static char A2072[] = "cannot access symbol in given segment or group: %s";
//static char A2073[] = "operands have different frames";
static char A2074[] = "cannot access label through segment registers : %s";
static char A2075[] = "jump destination too far : by %d bytes";
static char A2076[] = "jump destination must specify a label";
static char A2077[] = "instruction does not allow NEAR indirect addressing";
//static char A2078[] = "instruction does not allow FAR indirect addressing";
static char A2079[] = "instruction does not allow FAR direct addressing";
static char A2080[] = "jump distance not possible in current CPU mode";
static char A2081[] = "missing operand after unary operator";
static char A2082[] = "cannot mix 16- and 32-bit registers";
static char A2083[] = "invalid scale value";
static char A2084[] = "constant value too large";
static char A2085[] = "instruction or register not accepted in current CPU mode";
static char A2086[] = "reserved word expected";
static char A2087[] = "instruction form requires 80386/486";
static char A2088[] = "END directive required at end of file";
static char A2089[] = "too many bits in RECORD : %s";
static char A2090[] = "positive value expected";
static char A2091[] = "index value past end of string";
static char A2092[] = "count must be positive or zero";
static char A2093[] = "count value too large";
static char A2094[] = "operand must be relocatable";
static char A2095[] = "constant or relocatable label expected";
static char A2096[] = "segment, group, or segment register expected";
static char A2097[] = "segment expected : %s";
static char A2098[] = "invalid operand for OFFSET";
//static char A2099[] = "invalid use of external absolute";
static char A2100[] = "segment or group not allowed";
static char A2101[] = "cannot add two relocatable labels";
//static char A2102[] = "cannot add memory expression and code label";
static char A2103[] = "segment exceeds 64K limit: %s";
static char A2104[] = "invalid type for data declaration : %s";
static char A2105[] = "HIGH and LOW require immediate operands";
static char A2107[] = "cannot have implicit far jump or call to near label";
static char A2108[] = "use of register assumed to ERROR";
//static char A2109[] = "only white space or comment can follow backslash";
static char A2110[] = "COMMENT delimiter expected";
static char A2111[] = "conflicting parameter definition : %s";
static char A2112[] = "PROC and prototype calling conventions conflict";
static char A2113[] = "invalid radix tag";
static char A2114[] = "INVOKE argument type mismatch : %d";
//static char A2115[] = "invalid coprocessor register";
//static char A2116[] = "instructions and initialized data not allowed in AT segments";
//static char A2117[] = "/AT option requires TINY memory model";
//static char A2118[] = "cannot have segment address references with TINY model";
static char A2119[] = "language type must be specified";
static char A2120[] = "PROLOGUE must be macro function";
static char A2121[] = "EPILOGUE must be macro procedure : %s";
//static char A2122[] = "alternate identifier not allowed with EXTERNDEF";
static char A2123[] = "text macro nesting level too deep";
static char A2125[] = "missing macro argument";
//static char A2126[] = "EXITM used inconsistently";
//static char A2127[] = "macro function argument list too long";
static char A2129[] = "VARARG parameter must be last parameter";
//static char A2130[] = "VARARG parameter not allowed with LOCAL";
static char A2131[] = "VARARG parameter requires C calling convention";
static char A2132[] = "ORG needs a constant or local offset";
static char A2133[] = "register value overwritten by INVOKE";
//static char A2134[] = "structure too large to pass with INVOKE : argument number";
static char A2136[] = "too many arguments to INVOKE";
//static char A2137[] = "too few arguments to INVOKE";
//static char A2138[] = "invalid data initializer";
//static char A2140[] = "RET operand too large";
static char A2141[] = "too many operands to instruction";
#define A2142 A2002
static char A2143[] = "expected data label";
static char A2144[] = "cannot nest procedures : %s";
static char A2145[] = "EXPORT must be FAR : %s";
//static char A2146[] = "procedure declared with two visibility attributes : %s";
static char A2147[] = "macro label not defined : %s";
static char A2148[] = "invalid symbol type in expression : %s";
//static char A2149[] = "byte register cannot be first operand";
//static char A2150[] = "word register cannot be first operand";
static char A2151[] = "special register cannot be first operand";
//static char A2152[] = "coprocessor register cannot be first operand";
//static char A2153[] = "cannot change size of expression computations";
static char A2154[] = "syntax error in control-flow directive";
//static char A2155[] = "cannot use 16-bit register with a 32-bit address";
static char A2156[] = "constant value out of range";
static char A2157[] = "missing right parenthesis";
//static char A2158[] = "type is wrong size for register";
static char A2159[] = "structure cannot be instanced";
//static char A2160[] = "non-benign structure redefinition : label incorrect";
//static char A2161[] = "non-benign structure redefinition : too few labels";
//static char A2162[] = "OLDSTRUCT/NOOLDSTRUCT state cannot be changed";
//static char A2163[] = "non-benign structure redefinition : incorrect initializers";
//static char A2164[] = "non-benign structure redefinition : too few initializers";
//static char A2165[] = "non-benign structure redefinition : label has incorrect offset";
static char A2166[] = "structure field expected";
static char A2167[] = "unexpected literal found in expression : %s";
static char A2169[] = "divide by zero in expression";
static char A2170[] = "directive must appear inside a macro";
//static char A2171[] = "cannot expand macro function";
static char A2172[] = "too few bits in RECORD : %s";
//static char A2173[] = "macro function cannot redefine itself";
static char A2175[] = "invalid qualified type";
//static char A2176[] = "floating point initializer on an integer variable";
//static char A2177[] = "nested structure improperly initialized";
static char A2178[] = "invalid use of FLAT";
static char A2179[] = "structure improperly initialized";
//static char A2180[] = "improper list initialization";
static char A2181[] = "initializer must be a string or single item";
//static char A2182[] = "initializer must be a single item";
//static char A2183[] = "initializer must be a single byte";
//static char A2184[] = "improper use of list initializer";
//static char A2185[] = "improper literal initialization";
//static char A2186[] = "extra static characters in literal initialization";
static char A2187[] = "must use floating point initializer";
//static char A2188[] = "cannot use .EXIT for OS_OS2 with .8086";
static char A2189[] = "invalid combination with segment alignment : %d";
static char A2190[] = "INVOKE requires prototype for procedure";
//static char A2191[] = "cannot include structure in self";
static char A2192[] = "symbol language attribute conflict : %s";
//static char A2193[] = "non-benign COMM redefinition";
//static char A2194[] = "COMM variable exceeds 64K";
//static char A2195[] = "parameter or local cannot have void type";
//static char A2196[] = "cannot use TINY model with OS_OS2";
//static char A2197[] = "expression size must be 32-bits";
//static char A2198[] = ".EXIT does not work with 32-bit segments";
static char A2199[] = ".STARTUP does not work with 32-bit segments";
static char A2200[] = "ORG directive not allowed in unions";
//static char A2201[] = "scope state cannot be changed";
static char A2202[] = "illegal use of segment register";
//static char A2203[] = "cannot declare scoped code label as PUBLIC";
//static char A2204[] = ".MSFLOAT directive is obsolete : ignored";
//static char A2205[] = "ESC instruction is obsolete : ignored";
static char A2206[] = "missing operator in expression";
//static char A2207[] = "missing right parenthesis in expression";
//static char A2208[] = "missing left parenthesis in expression";
//static char A2209[] = "reference to forward macro redefinition";
static char A2214[] = "GROUP directive not allowed with /coff option";
static char A2217[] = "must be public or external : %s";
//static char A2219[] = "bad alignment for offset in unwind code";

/* Nonfatal Errors -- ASMC */

static char A3000[] = "assembly passes reached: %u";
static char A3001[] = "invalid fixup type for %s : %s";
static char A3002[] = "/PE option requires FLAT memory model";
static char A3003[] = "/bin: invalid start label";
static char A3004[] = "cannot use TR%u-TR%u with current CPU setting";
static char A3005[] = "no segment information to create fixup: %s";
static char A3006[] = "not supported with current output format: %s";
static char A3007[] = "missing .ENDPROLOG: %s";
static char A3008[] = ".ENDPROLOG found before EH directives";
static char A3009[] = "missing FRAME in PROC, no unwind code will be generated";
static char A3010[] = "size of prolog too big, must be < 256 bytes";
static char A3011[] = "too many unwind codes in FRAME procedure";
static char A3012[] = "registers AH-DH may not be used with SPL-DIL or R8-R15";
static char A3013[] = "multiple overrides";
static char A3014[] = "unknown fixup type: %u at %s.%lX";
static char A3015[] = "filename parameter must be enclosed in <> or quotes";
static char A3016[] = "literal expected after '='";
static char A3017[] = ".SAFESEH argument must be a PROC";
static char A3018[] = "invalid operand for %s : %s";
static char A3019[] = "invalid fixup type for %s : %u at location %s:%lX";
#define A3020 A1000
#define A3021 A1001
static char A3022[] = ".CASE redefinition : %s(%d) : %s(%d)";


/* Warnings -- MASM */

//static char A4000[] = "cannot modify READONLY segment";
//static char A4002[] = "non-unique STRUCT/UNION field used without qualification";
static char A4003[] = "start address on END directive ignored with .STARTUP";
//static char A4004[] = "cannot ASSUME CS";
static char A4005[] = "unknown default prologue argument";
static char A4006[] = "too many arguments in macro call : %s";
static char A4007[] = "option untranslated, directive required : %s";
static char A4008[] = "invalid command-line option value, default is used : %s";
//static char A4009[] = "insufficient memory for /EP : /EP ignored";
//static char A4010[] = "expected '>' on text literal";
static char A4011[] = "multiple .MODEL directives found : .MODEL ignored";
static char A4012[] = "line number information for segment without class 'CODE' : %s";
//static char A4013[] = "instructions and initialized data not supported in AT segments";
//static char A4015[] = "directive ignored with /coff switch";
#define A4910 A1000 // cannot open file

/* Warnings -- ASMC */

#define A8000 A1006
#define A8001 A2167
#define A8002 A2189
#define A8003 A2103
#define A8004 A2004
static char A8005[] = "IF[n]DEF expects a plain symbol as argument : %s";
static char A8006[] = "instructions and initialized data not supported in %s segments";
static char A8007[] = "16bit fixup for 32bit label : %s";
static char A8008[] = "displacement out of range: 0x%I64X";
static char A8009[] = "no start label defined";
static char A8010[] = "no stack defined";
static char A8011[] = "for -coff leading underscore required for start label: %s";
static char A8012[] = "library name is missing";
static char A8013[] = "ELF GNU extensions (8/16-bit relocations) used";
static char A8014[] = "LOADDS ignored in flat model";
static char A8015[] = "directive ignored without -%s switch";
//static char A8016[] = "text macro used prior to definition: %s";
static char A8017[] = "ignored: %s";
static char A8018[] = "group definition too large, truncated : %s";
static char A8019[] = "size not specified, assuming: %s";
static char A8020[] = "constant expected";

/* warning level 3 -- MASM */

//static char A5000[] = "@@: label defined but not referenced";
//static char A5001[] = "expression expected, assume value 0";
//static char A5002[] = "externdef previously assumed to be external";
//static char A5003[] = "length of symbol previously assumed to be different";
//static char A5004[] = "symbol previously assumed to not be in a group";
//static char A5005[] = "types are different";
//static char A6001[] = "no return from procedure";
static char A6003[] = "conditional jump lengthened";
static char A6004[] = "procedure argument or local not referenced : %s";
static char A6005[] = "expression condition may be pass-dependent: %s";

/* warning level 3 -- ASMC */

#define A7000 A2192
#define A7001 A2090
#define A7002 A2133
static char A7003[] = "far call is converted to near call.";
static char A7004[] = "floating-point initializer ignored";
static char A7005[] = "directive ignored: %s";
static char A7006[] = "parameter/local name is reserved word: %s";
static char A7007[] = ".CASE without .ENDC: assumed fall through";
static char A7008[] = "cannot delay macro function: %s";


static char * E0[] = {
	A1000,A1001,A1002,INTER,INTER,A1005,A1006,A1007,A1008,A1009,
	A1010,A1011,A1012,INTER,INTER,INTER,INTER,A1017 };
#define MAX_E0 (sizeof(E0)/sizeof(char*))
static char * E1[] = {
	INTER,INTER,INTER,INTER,A2004,A2005,A2006,A2007,A2008,A2009,
	A2010,A2011,A2012,A2013,A2014,A2015,A2016,INTER,A2018,A2019,
	INTER,INTER,A2022,A2023,A2024,A2025,A2026,INTER,A2028,A2029,
	A2030,A2031,A2032,A2033,A2034,INTER,A2036,A2037,INTER,A2039,
	INTER,A2041,INTER,A2043,INTER,A2045,A2046,A2047,A2048,INTER,
	A2050,A2051,A2052,A2053,A2054,A2055,A2056,A2057,A2058,A2059,
	A2060,A2061,A2062,A2063,A2064,A2065,A2066,INTER,A2068,INTER,
	A2070,A2071,A2072,INTER,A2074,A2075,A2076,A2077,INTER,A2079,
	A2080,A2081,A2082,A2083,A2084,A2085,A2086,A2087,A2088,A2089,
	A2090,A2091,A2092,A2093,A2094,A2095,A2096,A2097,A2098,INTER,
	A2100,A2101,INTER,A2103,A2104,A2105,INTER,A2107,A2108,INTER,
	A2110,A2111,A2112,A2113,A2114,INTER,INTER,INTER,INTER,A2119,
	A2120,A2121,INTER,A2123,INTER,A2125,INTER,INTER,INTER,A2129,
	INTER,A2131,A2132,A2133,INTER,INTER,A2136,INTER,INTER,INTER,
	INTER,A2141,A2142,A2143,A2144,A2145,INTER,A2147,A2148,INTER,
	INTER,A2151,INTER,INTER,A2154,INTER,A2156,A2157,INTER,A2159,
	INTER,INTER,INTER,INTER,INTER,INTER,A2166,A2167,INTER,A2169,
	A2170,INTER,A2172,INTER,INTER,A2175,INTER,INTER,A2178,A2179,
	INTER,A2181,INTER,INTER,INTER,INTER,INTER,A2187,INTER,A2189,
	A2190,INTER,INTER,INTER,INTER,INTER,INTER,INTER,INTER,A2199,
	A2200,INTER,A2202,INTER,INTER,INTER,A2206,INTER,INTER,INTER,
	INTER,INTER,INTER,INTER,A2214,INTER,INTER,A2217,INTER,INTER };
#define MAX_E1 (sizeof(E1)/sizeof(char*))
static char * E2[] = {
	A3000,A3001,A3002,A3003,A3004,A3005,A3006,A3007,A3008,A3009,
	A3010,A3011,A3012,A3013,A3014,A3015,A3016,A3017,A3018,A3019,
	A3020,A3021,A3022 };
#define MAX_E2 (sizeof(E2)/sizeof(char*))
static char * W1[] = {
	INTER,INTER,INTER,A4003,INTER,A4005,A4006,A4007,A4008,INTER,
	INTER,A4011,A4012,INTER,A4910 };
#define MAX_W1 (sizeof(W1)/sizeof(char*))
static char * W2[] = {
	INTER };
#define MAX_W2 (sizeof(W2)/sizeof(char*))
static char * W3[] = {
	INTER,INTER,INTER,A6003,A6004,A6005 };
#define MAX_W3 (sizeof(W3)/sizeof(char*))
static char * W4[] = {
	A7000,A7001,A7002,A7003,A7004,A7005,A7006,A7007,A7008 };
#define MAX_W4 (sizeof(W4)/sizeof(char*))
static char * W5[] = {
	A8000,A8001,A8002,A8003,A8004,A8005,A8006,A8007,A8008,A8009,
	A8010,A8011,A8012,A8013,A8014,A8015,INTER,A8017,A8018,A8019,
	A8020 };
#define MAX_W5 (sizeof(W5)/sizeof(char*))

static char **table[] = { E0,E1,E2,W1,W2,W3,W4,W5 };
static int maxid[] = { MAX_E0,MAX_E1,MAX_E2,MAX_W1,MAX_W2,MAX_W3,MAX_W4,MAX_W5 };

#define MIN_ID	1000
#define MAX_ID	8020

/* Notes */

static char N0000[] = "%*s%s(%u): Included by";
static char N0001[] = "%*s%s(%u)[%s]: Macro called from";
static char N0002[] = "%*s%s(%u): iteration %u: Macro called from";
static char N0003[] = "%*s%s(%u): Main line code";
static char *NOTE[] = {
	N0000,N0001,N0002,N0003 };

void write_logo(void);

static void print_err(char *erbuf, char *format, va_list args)
{
	char *p;

	write_logo();
	vsprintf( erbuf, format, args );

	/* v2.05: new option -eq */

	if ( Options.no_error_disp == 0 )
	    printf( "%s\n", erbuf );

	/* open .err file if not already open and a name is given */

	if ( !CurrFile[ERR] && CurrFName[ERR] ) {
	    if ( !(CurrFile[ERR] = fopen( CurrFName[ERR], "w" )) ) {

		/* v2.06: no fatal error anymore if error file cannot be written */
		/* set to NULL before asmerr()! */

		p = CurrFName[ERR];
		CurrFName[ERR] = NULL;

		/* disable -eq! */

		Options.no_error_disp = 0;
		asmerr( 4910, p );
	    }
	}
	if ( CurrFile[ERR] ) {
	    fwrite( erbuf, 1, strlen( erbuf ), CurrFile[ERR] );
	    fwrite( "\n", 1, 1, CurrFile[ERR] );
	    if ( Parse_Pass == PASS_1 && CurrFile[LST] ) {
		LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
		LstPrintf( "                           %s", erbuf );
		LstNL();
	    }
	}
}

int asmerr( int value, ... )
{
	char format[512];
	char erbuf[512];
	char **pp, *p;
	va_list args;
	int i, x;

	va_start( args, value );
	if ( value < MIN_ID || value > MAX_ID )
	    goto error;

	if ( value >= 4000 && !Options.warning_error && !Options.warning_level )
	    return -1;
	if ( value >= 5000 && value < 8000 && Options.warning_level < 3 )
	    return -1;

	if ( GetCurrSrcPos( format ) == 0 )
	    strcpy( format, "ASMC : " );

	if ( value < 2000 )
	    strcat( format, "fatal error" );
	else if ( value < 4000 )
	    strcat( format,"error" );
	else
	    strcat( format, "warning" );
	sprintf( format + strlen( format ), " A%04u: ", value );

	x = 0;
	i = value - 1000;
	while ( i > 1000 ) {
	    x++;
	    i -= 1000;
	}
	if ( i == 910 )
	    i = 14;
	if ( i >= maxid[x] )
	    goto error;

	pp = table[x];
	p  = pp[i];
	if ( p == INTER )
	    goto error;

	strcat( format, p );
	print_err( erbuf, format, args );

	if ( value == 1012 )
	    goto quit;

	if ( value >= 4000 ) {
	    if ( !Options.warning_error )
		ModuleInfo.g.warning_count++;
	    else
		ModuleInfo.g.error_count++;
	} else {
	    ModuleInfo.g.error_count++;
	}
	if ( Options.error_limit != -1 ) {
	    if ( ModuleInfo.g.error_count >= Options.error_limit + 1 )
		asmerr( 1012 );
	}
	if ( value >= 2000 )
	    print_source_nesting_structure();
	else
	    goto quit;

	return -1;

error:
	printf( "ASMC : fatal error A1901: %s\n", INTER );
quit:
	if ( CurrFName[ASM] )
	    longjmp( jmpenv, 3 );
	if ( CurrFile[OBJ] ) {
	    fclose( CurrFile[OBJ] );
	    remove( CurrFName[OBJ] );
	}
	exit( 1 );
	return -1; /*.*/
}

void WriteError(void)
{
    asmerr( 1002, CurrFName[OBJ] );
}

void PrintNote( int value, ... )
{
	char erbuf[512];
	va_list args;

	va_start( args, value );
	print_err( erbuf, NOTE[value], args );
	va_end( args );
}
