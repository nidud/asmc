include io.inc
include stdio.inc
include stdlib.inc
include string.inc
include setjmp.inc
include limits.inc

include asmc.inc

extern	jmpenv:S_JMPBUF

print_source_nesting_structure PROTO
GetCurrOffset PROTO

	.data
;
; Internal error
;
INTER db "Internal Assembler Error",0
;
; Fatal Errors
;
A1000	db "cannot open file : %s",0
A1001	db "I/O error closing file : %s",0
A1002	db "I/O error writing file : %s",0
;A1003	db "I/O error reading file",0
A1005	db "assembler limit : macro parameter name table full",0
A1006	db "invalid command-line option: %s",0
A1007	db "nesting level too deep",0
A1008	db "unmatched macro nesting",0
A1009	db "line too long",0
A1010	db "unmatched block nesting : %s",0
A1011	db "directive must be in control block",0
A1012	db "error count exceeds 100; stopping assembly",0
;A1013	db "invalid numerical command-line argument : %d",0
;A1014	db "too many arguments",0
;A1015	db "statement too complex",0
A1017	db "missing source filename",0
A1901	equ <INTER>
;
; Nonfatal Errors
;
;A2000	db "memory operand not allowed in context",0
;A2001	db "immediate operand not allowed",0
A2002	db "cannot have more than one .ELSE clause per .IF block",0
;A2003	db "extra characters after statement",0
A2004	db "symbol type conflict : %s",0
A2005	db "symbol redefinition : %s",0
A2006	db "undefined symbol : %s",0
A2007	db "non-benign record redefinition %s : %s",0
A2008	db "syntax error : %s",0
A2009	db "syntax error in expression",0
A2010	db "invalid type expression",0
A2011	db "distance invalid for word size of current segment",0
A2012	db "PROC, MACRO, or macro repeat directive must precede LOCAL",0
A2013	db ".MODEL must precede this directive",0
A2014	db "cannot define as public or external : %s",0
A2015	db "segment attributes cannot change : %s",0
A2016	db "expression expected",0
;A2017	db "operator expected",0
A2018	db "invalid use of external symbol : %s",0
A2019	db "operand must be RECORD type or field",0
;A2020	db "identifier not a record : identifier",0
;A2021	db "record constants cannot span line breaks",0
A2022	db "instruction operands must be the same size : %d - %d",0
A2023	db "instruction operand must have size",0
A2024	db "invalid operand size for instruction",0
A2025	db "operands must be in same segment",0
A2026	db "constant expected",0
;A2027	db "operand must be a memory expression",0
A2028	db "expression must be a code address",0
A2029	db "multiple base registers not allowed",0
A2030	db "multiple index registers not allowed",0
A2031	db "must be index or base register",0
A2032	db "invalid use of register",0
A2033	db "invalid INVOKE argument : %d",0
A2034	db "must be in segment block",0
;A2035	db "DUP too complex",0
A2036	db "too many initial values for structure: %s",0
A2037	db "statement not allowed inside structure definition",0
;A2038	db "missing operand for macro operator",0
A2039	equ <A1009>
;A2040	db "segment register not allowed in context",0
A2041	db "string or text literal too long",0
;A2042	db "statement too complex",0
A2043	db "identifier too long",0
;A2044	db "invalid character in file",0
A2045	db "missing angle bracket or brace in literal",0
A2046	db "missing single or double quotation mark in string",0
A2047	db "empty (null) string",0
A2048	db "nondigit in number : %s",0
;A2049	db "syntax error in floating-point constant",0
A2050	db "real or BCD number not allowed",0
A2051	db "text item required",0
A2052	db "forced error : %s",0
A2053	db "forced error : value equal to 0 : %d: %s",0
A2054	db "forced error : value not equal to 0 : %d: %s",0
A2055	db "forced error : symbol not defined : %s",0
A2056	db "forced error : symbol defined : %s",0
A2057	db "forced error : string blank : %s: %s",0
A2058	db "forced error : string not blank : <%s>: %s",0
A2059	db "forced error : strings equal : <%s>: <%s>: %s",0
A2060	db "forced error : strings not equal : <%s>: <%s>: %s",0
A2061	db "[[[ELSE]]]IF2/.ERR2 not allowed : single-pass assembler",0
A2062	db "expression too complex for .UNTILCXZ",0
A2063	db "can ALIGN only to power of 2 : %u",0
A2064	db "struct alignment must be 1, 2, 4, 8, 16 or 32",0
A2065	db "expected : %s",0
A2066	db "incompatible CPU mode and segment size",0
;A2067	db "LOCK must be followed by a memory operation",0
A2068	db "instruction prefix not allowed",0
;A2069	db "no operands allowed for this instruction",0
A2070	db "invalid instruction operands",0
A2071	db "initializer too large for specified size",0
A2072	db "cannot access symbol in given segment or group: %s",0
;A2073	db "operands have different frames",0
A2074	db "cannot access label through segment registers : %s",0
A2075	db "jump destination too far : by %d bytes",0
A2076	db "jump destination must specify a label",0
A2077	db "instruction does not allow NEAR indirect addressing",0
;A2078	db "instruction does not allow FAR indirect addressing",0
A2079	db "instruction does not allow FAR direct addressing",0
A2080	db "jump distance not possible in current CPU mode",0
A2081	db "missing operand after unary operator",0
A2082	db "cannot mix 16- and 32-bit registers",0
A2083	db "invalid scale value",0
A2084	db "constant value too large",0
A2085	db "instruction or register not accepted in current CPU mode",0
A2086	db "reserved word expected",0
A2087	db "instruction form requires 80386/486",0
A2088	db "END directive required at end of file",0
A2089	db "too many bits in RECORD : %s",0
A2090	db "positive value expected",0
A2091	db "index value past end of string",0
A2092	db "count must be positive or zero",0
A2093	db "count value too large",0
A2094	db "operand must be relocatable",0
A2095	db "constant or relocatable label expected",0
A2096	db "segment, group, or segment register expected",0
A2097	db "segment expected : %s",0
A2098	db "invalid operand for OFFSET",0
;A2099	db "invalid use of external absolute",0
A2100	db "segment or group not allowed",0
A2101	db "cannot add two relocatable labels",0
;A2102	db "cannot add memory expression and code label",0
A2103	db "segment exceeds 64K limit: %s",0
A2104	db "invalid type for data declaration : %s",0
A2105	db "HIGH and LOW require immediate operands",0
A2107	db "cannot have implicit far jump or call to near label",0
A2108	db "use of register assumed to ERROR",0
;A2109	db "only white space or comment can follow backslash",0
A2110	db "COMMENT delimiter expected",0
A2111	db "conflicting parameter definition : %s",0
A2112	db "PROC and prototype calling conventions conflict",0
A2113	db "invalid radix tag",0
A2114	db "INVOKE argument type mismatch : %d",0
;A2115	db "invalid coprocessor register",0
;A2116	db "instructions and initialized data not allowed in AT segments",0
;A2117	db "/AT option requires TINY memory model",0
;A2118	db "cannot have segment address references with TINY model",0
A2119	db "language type must be specified",0
A2120	db "PROLOGUE must be macro function",0
A2121	db "EPILOGUE must be macro procedure : %s",0
;A2122	db "alternate identifier not allowed with EXTERNDEF",0
A2123	db "text macro nesting level too deep",0
A2125	db "missing macro argument",0
;A2126	db "EXITM used inconsistently",0
;A2127	db "macro function argument list too long",0
A2129	db "VARARG parameter must be last parameter",0
;A2130	db "VARARG parameter not allowed with LOCAL",0
A2131	db "VARARG parameter requires C calling convention",0
A2132	db "ORG needs a constant or local offset",0
A2133	db "register value overwritten by INVOKE",0
;A2134	db "structure too large to pass with INVOKE : argument number",0
A2136	db "too many arguments to INVOKE",0
;A2137	db "too few arguments to INVOKE",0
;A2138	db "invalid data initializer",0
;A2140	db "RET operand too large",0
A2141	db "too many operands to instruction",0
A2142	equ <A2002>
A2143	db "expected data label",0
A2144	db "cannot nest procedures : %s",0
A2145	db "EXPORT must be FAR : %s",0
;A2146	db "procedure declared with two visibility attributes : %s",0
A2147	db "macro label not defined : %s",0
A2148	db "invalid symbol type in expression : %s",0
;A2149	db "byte register cannot be first operand",0
;A2150	db "word register cannot be first operand",0
A2151	db "special register cannot be first operand",0
;A2152	db "coprocessor register cannot be first operand",0
;A2153	db "cannot change size of expression computations",0
A2154	db "syntax error in control-flow directive",0
;A2155	db "cannot use 16-bit register with a 32-bit address",0
A2156	db "constant value out of range",0
A2157	db "missing right parenthesis",0
;A2158	db "type is wrong size for register",0
A2159	db "structure cannot be instanced",0
;A2160	db "non-benign structure redefinition : label incorrect",0
;A2161	db "non-benign structure redefinition : too few labels",0
;A2162	db "OLDSTRUCT/NOOLDSTRUCT state cannot be changed",0
;A2163	db "non-benign structure redefinition : incorrect initializers",0
;A2164	db "non-benign structure redefinition : too few initializers",0
;A2165	db "non-benign structure redefinition : label has incorrect offset",0
A2166	db "structure field expected",0
A2167	db "unexpected literal found in expression : %s",0
A2169	db "divide by zero in expression",0
A2170	db "directive must appear inside a macro",0
;A2171	db "cannot expand macro function",0
A2172	db "too few bits in RECORD : %s",0
;A2173	db "macro function cannot redefine itself",0
A2175	db "invalid qualified type",0
;A2176	db "floating point initializer on an integer variable",0
;A2177	db "nested structure improperly initialized",0
A2178	db "invalid use of FLAT",0
A2179	db "structure improperly initialized",0
;A2180	db "improper list initialization",0
A2181	db "initializer must be a string or single item",0
;A2182	db "initializer must be a single item",0
;A2183	db "initializer must be a single byte",0
;A2184	db "improper use of list initializer",0
;A2185	db "improper literal initialization",0
;A2186	db "extra characters in literal initialization",0
A2187	db "must use floating point initializer",0
;A2188	db "cannot use .EXIT for OS_OS2 with .8086",0
A2189	db "invalid combination with segment alignment : %d",0
A2190	db "INVOKE requires prototype for procedure",0
;A2191	db "cannot include structure in self",0
A2192	db "symbol language attribute conflict : %s",0
;A2193	db "non-benign COMM redefinition",0
;A2194	db "COMM variable exceeds 64K",0
;A2195	db "parameter or local cannot have void type",0
;A2196	db "cannot use TINY model with OS_OS2",0
;A2197	db "expression size must be 32-bits",0
;A2198	db ".EXIT does not work with 32-bit segments",0
A2199	db ".STARTUP does not work with 32-bit segments",0
A2200	db "ORG directive not allowed in unions",0
;A2201	db "scope state cannot be changed",0
A2202	db "illegal use of segment register",0
;A2203	db "cannot declare scoped code label as PUBLIC",0
;A2204	db ".MSFLOAT directive is obsolete : ignored",0
;A2205	db "ESC instruction is obsolete : ignored",0
A2206	db "missing operator in expression",0
;A2207	db "missing right parenthesis in expression",0
;A2208	db "missing left parenthesis in expression",0
;A2209	db "reference to forward macro redefinition",0
A2214	db "GROUP directive not allowed with /coff option",0
A2217	db "must be public or external : %s",0
;A2219	db "bad alignment for offset in unwind code",0
;
; Nonfatal Errors -- ASMC
;
A3000	db "assembly passes reached: %u",0
A3001	db "invalid fixup type for %s : %s",0
A3002	db "/PE option requires FLAT memory model",0
A3003	db "/bin: invalid start label",0
A3004	db "cannot use TR%u-TR%u with current CPU setting",0
A3005	db "no segment information to create fixup: %s",0
A3006	db "not supported with current output format: %s",0
A3007	db "missing .ENDPROLOG: %s",0
A3008	db ".ENDPROLOG found before EH directives",0
A3009	db "missing FRAME in PROC, no unwind code will be generated",0
A3010	db "size of prolog too big, must be < 256 bytes",0
A3011	db "too many unwind codes in FRAME procedure",0
A3012	db "registers AH-DH may not be used with SPL-DIL or R8-R15",0
A3013	db "multiple overrides",0
A3014	db "unknown fixup type: %u at %s.%lX",0
A3015	db "filename parameter must be enclosed in <> or quotes",0
A3016	db "literal expected after '='",0
A3017	db ".SAFESEH argument must be a PROC",0
A3018	db "invalid operand for %s : %s",0
A3019	db "invalid fixup type for %s : %u at location %s:%lX",0
A3020	equ <A1000>
A3021	equ <A1001>
A3022	db ".CASE redefinition : %s(%d) : %s(%d)",0

;
; Warnings -- MASM
;
;A4000	db "cannot modify READONLY segment",0
;A4002	db "non-unique STRUCT/UNION field used without qualification",0
A4003	db "start address on END directive ignored with .STARTUP",0
;A4004	db "cannot ASSUME CS",0
A4005	db "unknown default prologue argument",0
A4006	db "too many arguments in macro call : %s",0
A4007	db "option untranslated, directive required : %s",0
A4008	db "invalid command-line option value, default is used : %s",0
;A4009	db "insufficient memory for /EP : /EP ignored",0
;A4010	db "expected '>' on text literal",0
A4011	db "multiple .MODEL directives found : .MODEL ignored",0
A4012	db "line number information for segment without class 'CODE' : %s",0
;A4013	db "instructions and initialized data not supported in AT segments",0
;A4015	db "directive ignored with /coff switch",0
A4910	equ <A1000> ; cannot open file
;
; Warnings -- ASMC
;
A8000	equ <A1006>
A8001	equ <A2167>
A8002	equ <A2189>
A8003	equ <A2103>
A8004	equ <A2004>
A8005	db "IF[n]DEF expects a plain symbol as argument : %s",0
A8006	db "instructions and initialized data not supported in %s segments",0
A8007	db "16bit fixup for 32bit label : %s",0
A8008	db "displacement out of range: 0x%I64X",0
A8009	db "no start label defined",0
A8010	db "no stack defined",0
A8011	db "for -coff leading underscore required for start label: %s",0
A8012	db "library name is missing",0
A8013	db "ELF GNU extensions (8/16-bit relocations) used",0
A8014	db "LOADDS ignored in flat model",0
A8015	db "directive ignored without -%s switch",0
;A8016	db "text macro used prior to definition: %s",0
A8017	db "ignored: %s",0
A8018	db "group definition too large, truncated : %s",0
A8019	db "size not specified, assuming: %s",0
A8020	db "constant expected",0
;
; warning level 3 -- MASM
;
;A5000	db "@@: label defined but not referenced",0
;A5001	db "expression expected, assume value 0",0
;A5002	db "externdef previously assumed to be external",0
;A5003	db "length of symbol previously assumed to be different",0
;A5004	db "symbol previously assumed to not be in a group",0
;A5005	db "types are different",0
;A6001	db "no return from procedure",0
A6003	db "conditional jump lengthened",0
A6004	db "procedure argument or local not referenced : %s",0
A6005	db "expression condition may be pass-dependent: %s",0
;
; warning level 3 -- ASMC
;
A7000	equ <A2192>
A7001	equ <A2090>
A7002	equ <A2133>
A7003	db "far call is converted to near call.",0
A7004	db "floating-point initializer ignored",0
A7005	db "directive ignored: %s",0
A7006	db "parameter/local name is reserved word: %s",0
A7007	db ".CASE without .ENDC: assumed fall through",0
A7008	db "cannot delay macro function: %s",0

	ALIGN	4

E0	dd A1000,A1001,A1002,INTER,INTER,A1005,A1006,A1007,A1008,A1009
	dd A1010,A1011,A1012,INTER,INTER,INTER,INTER,A1017
MAX_E0 equ ($ - E0) / 4
E1	dd INTER,INTER,INTER,INTER,A2004,A2005,A2006,A2007,A2008,A2009
	dd A2010,A2011,A2012,A2013,A2014,A2015,A2016,INTER,A2018,A2019
	dd INTER,INTER,A2022,A2023,A2024,A2025,A2026,INTER,A2028,A2029
	dd A2030,A2031,A2032,A2033,A2034,INTER,A2036,A2037,INTER,A2039
	dd INTER,A2041,INTER,A2043,INTER,A2045,A2046,A2047,A2048,INTER
	dd A2050,A2051,A2052,A2053,A2054,A2055,A2056,A2057,A2058,A2059
	dd A2060,A2061,A2062,A2063,A2064,A2065,A2066,INTER,A2068,INTER
	dd A2070,A2071,A2072,INTER,A2074,A2075,A2076,A2077,INTER,A2079
	dd A2080,A2081,A2082,A2083,A2084,A2085,A2086,A2087,A2088,A2089
	dd A2090,A2091,A2092,A2093,A2094,A2095,A2096,A2097,A2098,INTER
	dd A2100,A2101,INTER,A2103,A2104,A2105,INTER,A2107,A2108,INTER
	dd A2110,A2111,A2112,A2113,A2114,INTER,INTER,INTER,INTER,A2119
	dd A2120,A2121,INTER,A2123,INTER,A2125,INTER,INTER,INTER,A2129
	dd INTER,A2131,A2132,A2133,INTER,INTER,A2136,INTER,INTER,INTER
	dd INTER,A2141,A2142,A2143,A2144,A2145,INTER,A2147,A2148,INTER
	dd INTER,A2151,INTER,INTER,A2154,INTER,A2156,A2157,INTER,A2159
	dd INTER,INTER,INTER,INTER,INTER,INTER,A2166,A2167,INTER,A2169
	dd A2170,INTER,A2172,INTER,INTER,A2175,INTER,INTER,A2178,A2179
	dd INTER,A2181,INTER,INTER,INTER,INTER,INTER,A2187,INTER,A2189
	dd A2190,INTER,INTER,INTER,INTER,INTER,INTER,INTER,INTER,A2199
	dd A2200,INTER,A2202,INTER,INTER,INTER,A2206,INTER,INTER,INTER
	dd INTER,INTER,INTER,INTER,A2214,INTER,INTER,A2217,INTER,INTER
MAX_E1 equ ($ - E1) / 4
E2	dd A3000,A3001,A3002,A3003,A3004,A3005,A3006,A3007,A3008,A3009
	dd A3010,A3011,A3012,A3013,A3014,A3015,A3016,A3017,A3018,A3019
	dd A3020,A3021,A3022
MAX_E2 equ ($ - E2) / 4
W1	dd INTER,INTER,INTER,A4003,INTER,A4005,A4006,A4007,A4008,INTER
	dd INTER,A4011,A4012,INTER,A4910
MAX_W1	equ ($ - W1) / 4
W2	dd INTER
MAX_W2	equ ($ - W2) / 4
W3	dd INTER,INTER,INTER,A6003,A6004,A6005
MAX_W3	equ ($ - W3) / 4
W4	dd A7000,A7001,A7002,A7003,A7004,A7005,A7006,A7007,A7008
MAX_W4	equ ($ - W4) / 4
W5	dd A8000,A8001,A8002,A8003,A8004,A8005,A8006,A8007,A8008,A8009
	dd A8010,A8011,A8012,A8013,A8014,A8015,INTER,A8017,A8018,A8019
	dd A8020
MAX_W5 equ ($ - W5) / 4

table	dd E0,E1,E2,W1,W2,W3,W4,W5
maxid	dd MAX_E0,MAX_E1,MAX_E2,MAX_W1,MAX_W2,MAX_W3,MAX_W4,MAX_W5

MIN_ID	equ 1000
MAX_ID	equ 8020

;
; Notes
;
N0000	db "%*s%s(%u): Included by",0
N0001	db "%*s%s(%u)[%s]: Macro called from",0
N0002	db "%*s%s(%u): iteration %u: Macro called from",0
N0003	db "%*s%s(%u): Main line code",0
NOTE	dd N0000,N0001,N0002,N0003

	.code

print_err PROC PRIVATE USES esi edi ebx erbuf, format, args
  local iob:_iobuf
	write_logo()
	mov esi,erbuf
	mov iob._flag,_IOWRT or _IOSTRG
	mov iob._cnt,INT_MAX
	mov iob._ptr,esi
	mov iob._base,esi
	_output( addr iob, format, args )
	mov eax,iob._ptr
	mov byte ptr [eax],0
	;
	; v2.05: new option -eq
	;
	.if !Options.no_error_disp
		_print( "%s\n", esi )
	.endif
	;
	; open .err file if not already open and a name is given
	;
	mov ebx,ModuleInfo.curr_fname[ERR*4]
	mov edi,ModuleInfo.curr_file[ERR*4]
	.if !edi && ebx
		.if fopen( ebx, "w" )
			mov ModuleInfo.curr_file[ERR*4],eax
		.else
			;
			; v2.06: no fatal error anymore if error file cannot be written
			; set to NULL before asmerr()!
			;
			mov ModuleInfo.curr_fname[ERR*4],eax
			;
			; disable -eq!
			;
			mov Options.no_error_disp,al
			asmerr( 4910, ebx )
		.endif
	.endif
	mov edi,ModuleInfo.curr_file[ERR*4]
	.if edi
		fwrite( esi, 1, strlen( esi ), edi )
		fwrite( "\n", 1, 1, edi )
		.if Parse_Pass == PASS_1 && ModuleInfo.curr_file[LST*4]
			GetCurrOffset()
			LstWrite( LSTTYPE_DIRECTIVE, eax, 0 )
			LstPrintf( "                           %s", esi )
			LstNL()
		.endif
	.endif
	ret
print_err ENDP


asmerr	PROC C USES esi edi ebx edx ecx value, args:VARARG
  local format[512]:BYTE,erbuf[512]:BYTE

	lea edi,format
	mov ebx,value
	cmp ebx,MIN_ID
	jb  error
	cmp ebx,MAX_ID
	ja  error

	.if ebx >= 4000 && !Options.warning_error && !Options.warning_level
		jmp toend
	.endif
	.if ebx >= 5000 && ebx < 8000 && Options.warning_level < 3
		jmp toend
	.endif

	strcpy( edi, "ASMC : " )
	mov edx,ModuleInfo.src_stack
	.while edx
		movzx eax,[edx].src_item.srcfile
		mov ecx,ModuleInfo.FNames
		mov ecx,[ecx+eax*4]
		mov eax,[edx].src_item.line_num
		cmp [edx].src_item._type,SIT_FILE
		mov edx,[edx].src_item.next
		.if ZERO?
			.if ModuleInfo.EndDirFound
				sprintf( edi, "%s : ", ecx )
			.else
				sprintf( edi, "%s(%u) : ", ecx, eax )
			.endif
			.break
		.endif
	.endw

	.if ebx < 2000
		strcat( edi, "fatal error" )
	.elseif ebx < 4000
		strcat( edi,"error" )
	.else
		strcat( edi, "warning" )
	.endif

	strlen( edi )
	add edi,eax
	sprintf( edi, " A%04u: ", ebx )
	xor ecx,ecx
	lea eax,[ebx-1000]
	.while eax > 1000
		add ecx,1
		sub eax,1000
	.endw
	.if eax == 910
		mov eax,14
	.endif
	cmp eax,maxid[ecx*4]
	jnb error
	mov esi,table[ecx*4]
	mov esi,[esi+eax*4]
	cmp esi,offset INTER
	je  error

	lea edi,format
	strcat( edi, esi )
	print_err( addr erbuf, edi, addr args )
	lea esi,erbuf

	mov ebx,value
	cmp ebx,1012
	je  quit

	.if ebx >= 4000
		.if !Options.warning_error
			inc ModuleInfo.warning_count
		.else
			inc ModuleInfo.error_count
		.endif
	.else
		inc ModuleInfo.error_count
	.endif
	mov eax,Options.error_limit
	.if eax != -1
		inc eax
		.if ModuleInfo.error_count >= eax
			asmerr( 1012 )
		.endif
	.endif
	.if ebx >= 2000
		print_source_nesting_structure()
	.else
		jmp quit
	.endif
toend:
	mov eax,-1
	ret
error:
	_print( "ASMC : fatal error A1901: %s\n", addr INTER )
quit:
	.if ModuleInfo.curr_fname[ASM*4]
		longjmp( addr jmpenv, 3 )
	.endif
	mov eax,ModuleInfo.curr_file[OBJ*4]
	.if eax
		fclose( eax )
		remove( ModuleInfo.curr_fname[OBJ*4] )
	.endif

	exit( 1 )

asmerr	ENDP

WriteError PROC
	asmerr( 1002, ModuleInfo.curr_fname[OBJ*4] )
	ret
WriteError ENDP

PrintNote PROC C value, args:VARARG
  local erbuf[512]:BYTE
	mov eax,value
	mov edx,NOTE[eax*4]
	print_err( addr erbuf, edx, addr args )
	ret
PrintNote ENDP

	END
