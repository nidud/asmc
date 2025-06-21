; ASMERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include stdlib.inc
include string.inc
include limits.inc
include setjmp.inc

include asmc.inc
include symbols.inc
include input.inc
include listing.inc

warning_disable proto __ccall :int_t
GetCurrOffset   proto __ccall
print_source_nesting_structure proto __ccall

externdef jmpenv:byte

;; Internal error

    INTER equ <"Internal Assembler Error">

;; Fatal Errors

    A1000 equ <"cannot open file : %s">
    A1001 equ <"I/O error closing file : %s">
    A1002 equ <"I/O error writing file : %s">
    A1003 equ <"I/O error reading file">
    A1005 equ <"assembler limit : macro parameter name table full">
    A1006 equ <"invalid command-line option: %s">
    A1007 equ <"nesting level too deep">
    A1008 equ <"unmatched macro nesting">
    A1009 equ <"line too long">
    A1010 equ <"unmatched block nesting : %s">
    A1011 equ <"directive must be in control block">
    A1012 equ <"error count exceeds 100; stopping assembly">
    A1013 equ <"invalid numerical command-line argument : %d">
    A1014 equ <"too many arguments">
    A1015 equ <"statement too complex">
    A1017 equ <"missing source filename">
    A1018 equ <"Not enough space">

;; Nonfatal Errors

    A2000 equ <"memory operand not allowed in context">
    A2001 equ <"immediate operand not allowed">
    A2002 equ <"cannot have more than one .ELSE clause per .IF block">
    A2003 equ <"extra characters after statement">
    A2004 equ <"symbol type conflict : %s">
    A2005 equ <"symbol redefinition : %s">
    A2006 equ <"undefined symbol : %s">
    A2007 equ <"non-benign record redefinition %s : %s">
    A2008 equ <"syntax error : %s">
    A2009 equ <"syntax error in expression">
    A2010 equ <"invalid type expression">
    A2011 equ <"distance invalid for word size of current segment">
    A2012 equ <"PROC, MACRO, or macro repeat directive must precede LOCAL">
    A2013 equ <".MODEL must precede this directive">
    A2014 equ <"cannot define as public or external : %s">
    A2015 equ <"segment attributes cannot change : %s (%s)">
    A2016 equ <"expression expected">
    A2017 equ <"operator expected">
    A2018 equ <"invalid use of external symbol : %s">
    A2019 equ <"operand must be RECORD type or field">
    A2020 equ <"identifier not a record : identifier">
    A2021 equ <"record constants cannot span line breaks">
    A2022 equ <"instruction operands must be the same size : %d - %d">
    A2023 equ <"instruction operand must have size">
    A2024 equ <"invalid operand size for instruction">
    A2025 equ <"operands must be in same segment">
    A2026 equ <"constant expected">
    A2027 equ <"operand must be a memory expression">
    A2028 equ <"expression must be a code address">
    A2029 equ <"multiple base registers not allowed">
    A2030 equ <"multiple index registers not allowed">
    A2031 equ <"must be index or base register">
    A2032 equ <"invalid use of register">
    A2033 equ <"invalid INVOKE argument : %d">
    A2034 equ <"must be in segment block">
    A2035 equ <"DUP too complex">
    A2036 equ <"too many initial values for structure: %s">
    A2037 equ <"statement not allowed inside structure definition">
    A2038 equ <"missing operand for macro operator">
    A2039 equ <"line too long">
    A2040 equ <"segment register not allowed in context">
    A2041 equ <"string or text literal too long">
    A2042 equ <"statement too complex">
    A2043 equ <"identifier too long">
    A2044 equ <"invalid character in file">
    A2045 equ <"missing angle bracket or brace in literal">
    A2046 equ <"missing single or double quotation mark in string">
    A2047 equ <"empty (null) string">
    A2048 equ <"nondigit in number : %s">
    A2049 equ <"syntax error in floating-point constant">
    A2050 equ <"real or BCD number not allowed">
    A2051 equ <"text item required">
    A2052 equ <"forced error : %s">
    A2053 equ <"forced error : value equal to 0 : %d: %s">
    A2054 equ <"forced error : value not equal to 0 : %d: %s">
    A2055 equ <"forced error : symbol not defined : %s">
    A2056 equ <"forced error : symbol defined : %s">
    A2057 equ <"forced error : string blank : %s: %s">
    A2058 equ <"forced error : string not blank : <%s>: %s">
    A2059 equ <"forced error : strings equal : <%s>: <%s>: %s">
    A2060 equ <"forced error : strings not equal : <%s>: <%s>: %s">
    A2061 equ <"[[[ELSE]]]IF2/.ERR2 not allowed : single-pass assembler">
    A2062 equ <"expression too complex for .UNTILCXZ">
    A2063 equ <"can ALIGN only to power of 2 : %u">
    A2064 equ <"struct alignment must be 1, 2, 4, 8, 16 or 32">
    A2065 equ <"expected : %s">
    A2066 equ <"incompatible CPU mode and segment size">
    A2067 equ <"LOCK must be followed by a memory operation">
    A2068 equ <"instruction prefix not allowed">
    A2069 equ <"no operands allowed for this instruction">
    A2070 equ <"invalid instruction operands">
    A2071 equ <"initializer too large for specified size">
    A2072 equ <"cannot access symbol in given segment or group: %s">
    A2073 equ <"operands have different frames">
    A2074 equ <"cannot access label through segment registers : %s">
    A2075 equ <"jump destination too far : by %d bytes">
    A2076 equ <"jump destination must specify a label">
    A2077 equ <"instruction does not allow NEAR indirect addressing">
    A2078 equ <"instruction does not allow FAR indirect addressing">
    A2079 equ <"instruction does not allow FAR direct addressing">
    A2080 equ <"jump distance not possible in current CPU mode">
    A2081 equ <"missing operand after unary operator">
    A2082 equ <"cannot mix 16- and 32-bit registers">
    A2083 equ <"invalid scale value">
    A2084 equ <"constant value too large">
    A2085 equ <"instruction or register not accepted in current CPU mode">
    A2086 equ <"reserved word expected">
    A2087 equ <"instruction form requires 80386/486">
    A2088 equ <"END directive required at end of file">
    A2089 equ <"too many bits in RECORD : %s">
    A2090 equ <"positive value expected">
    A2091 equ <"index value past end of string">
    A2092 equ <"count must be positive or zero">
    A2093 equ <"count value too large">
    A2094 equ <"operand must be relocatable">
    A2095 equ <"constant or relocatable label expected">
    A2096 equ <"segment, group, or segment register expected">
    A2097 equ <"segment expected : %s">
    A2098 equ <"invalid operand for OFFSET">
    A2099 equ <"invalid use of external absolute">
    A2100 equ <"segment or group not allowed : %s %s">
    A2101 equ <"cannot add two relocatable labels">
    A2102 equ <"cannot add memory expression and code label">
    A2103 equ <"segment exceeds 64K limit: %s">
    A2104 equ <"invalid type for data declaration : %s">
    A2105 equ <"HIGH and LOW require immediate operands">
    A2107 equ <"cannot have implicit far jump or call to near label">
    A2108 equ <"use of register assumed to ERROR">
    A2109 equ <"only white space or comment can follow backslash">
    A2110 equ <"COMMENT delimiter expected">
    A2111 equ <"conflicting parameter definition : %s">
    A2112 equ <"PROC and prototype calling conventions conflict">
    A2113 equ <"invalid radix tag">
    A2114 equ <"INVOKE argument type mismatch : %d">
    A2115 equ <"invalid coprocessor register">
    A2116 equ <"instructions and initialized data not allowed in AT segments">
    A2117 equ <"/AT option requires TINY memory model">
    A2118 equ <"cannot have segment address references with TINY model">
    A2119 equ <"language type must be specified">
    A2120 equ <"PROLOGUE must be macro function">
    A2121 equ <"EPILOGUE must be macro procedure : %s">
    A2122 equ <"alternate identifier not allowed with EXTERNDEF">
    A2123 equ <"text macro nesting level too deep">
    A2125 equ <"missing macro argument">
    A2126 equ <"EXITM used inconsistently">
    A2127 equ <"macro function argument list too long">
    A2129 equ <"VARARG parameter must be last parameter">
    A2130 equ <"VARARG parameter not allowed with LOCAL">
    A2131 equ <"VARARG parameter requires C calling convention">
    A2132 equ <"ORG needs a constant or local offset">
    A2133 equ <"register value overwritten by INVOKE">
    A2134 equ <"structure too large to pass with INVOKE : argument number">
    A2136 equ <"too many arguments to INVOKE">
    A2137 equ <"too few arguments to INVOKE">
    A2138 equ <"invalid data initializer">
    A2140 equ <"RET operand too large">
    A2141 equ <"too many operands to instruction">
    A2142 equ <"cannot have more than one .ELSE clause per .IF block">
    A2143 equ <"expected data label">
    A2144 equ <"cannot nest procedures : %s">
    A2145 equ <"EXPORT must be FAR : %s">
    A2146 equ <"procedure declared with two visibility attributes : %s">
    A2147 equ <"macro label not defined : %s">
    A2148 equ <"invalid symbol type in expression : %s">
    A2149 equ <"byte register cannot be first operand">
    A2150 equ <"word register cannot be first operand">
    A2151 equ <"special register cannot be first operand">
    A2152 equ <"coprocessor register cannot be first operand">
    A2153 equ <"cannot change size of expression computations">
    A2154 equ <"syntax error in control-flow directive">
    A2155 equ <"cannot use 16-bit register with a 32-bit address">
    A2156 equ <"constant value out of range">
    A2157 equ <"missing right parenthesis">
    A2158 equ <"type is wrong size for register">
    A2159 equ <"structure cannot be instanced">
    A2160 equ <"non-benign structure redefinition : label incorrect">
    A2161 equ <"non-benign structure redefinition : too few labels">
    A2162 equ <"OLDSTRUCT/NOOLDSTRUCT state cannot be changed">
    A2163 equ <"non-benign structure redefinition : incorrect initializers">
    A2164 equ <"non-benign structure redefinition : too few initializers">
    A2165 equ <"non-benign structure redefinition : label has incorrect offset">
    A2166 equ <"structure field expected">
    A2167 equ <"unexpected literal found in expression : %s">
    A2169 equ <"divide by zero in expression">
    A2170 equ <"directive must appear inside a macro">
    A2171 equ <"cannot expand macro function">
    A2172 equ <"too few bits in RECORD : %s">
    A2173 equ <"macro function cannot redefine itself">
    A2175 equ <"invalid qualified type">
    A2176 equ <"floating point initializer on an integer variable">
    A2177 equ <"nested structure improperly initialized">
    A2178 equ <"invalid use of FL    AT">
    A2179 equ <"structure improperly initialized">
    A2180 equ <"improper list initialization">
    A2181 equ <"initializer must be a string or single item">
    A2182 equ <"initializer must be a single item">
    A2183 equ <"initializer must be a single byte">
    A2184 equ <"improper use of list initializer">
    A2185 equ <"improper literal initialization">
    A2186 equ <"extra characters in literal initialization">
    A2187 equ <"must use floating point initializer">
    A2188 equ <"cannot use .EXIT for OS_OS2 with .8086">
    A2189 equ <"invalid combination with segment alignment : %d">
    A2190 equ <"INVOKE requires prototype for procedure">
    A2191 equ <"cannot include structure in self">
    A2192 equ <"symbol language attribute conflict : %s">
    A2193 equ <"non-benign COMM redefinition">
    A2194 equ <"COMM variable exceeds 64K">
    A2195 equ <"parameter or local cannot have void type">
    A2196 equ <"cannot use TINY model with OS_OS2">
    A2197 equ <"expression size must be 32-bits">
    A2198 equ <".EXIT does not work with 32-bit segments">
    A2199 equ <".STARTUP does not work with 32-bit segments">
    A2200 equ <"ORG directive not allowed in unions">
    A2201 equ <"scope state cannot be changed">
    A2202 equ <"illegal use of segment register">
    A2203 equ <"cannot declare scoped code label as PUBLIC">
    A2204 equ <".MSFLOAT directive is obsolete : ignored">
    A2205 equ <"ESC instruction is obsolete : ignored">
    A2206 equ <"missing operator in expression">
    A2207 equ <"missing right parenthesis in expression">
    A2208 equ <"missing left parenthesis in expression">
    A2209 equ <"reference to forward macro redefinition">
    A2214 equ <"GROUP directive not allowed with /coff option">
    A2217 equ <"must be public or external : %s">
    A2219 equ <"bad alignment for offset in unwind code">

;; Nonfatal Errors -- ASMC

    A3000 equ <"assembly passes reached: %u">
    A3001 equ <"invalid fixup type for %s : %s">
    A3002 equ <"/PE option requires FLAT memory model">
    A3003 equ <"/bin: invalid start label">
    A3004 equ <"cannot use TR%u-TR%u with current CPU setting">
    A3005 equ <"no segment information to create fixup: %s">
    A3006 equ <"not supported with current output format: %s">
    A3007 equ <"missing .ENDPROLOG: %s">
    A3008 equ <".ENDPROLOG found before EH directives">
    A3009 equ <"missing FRAME in PROC, no unwind code will be generated">
    A3010 equ <"size of prolog too big, must be < 256 bytes">
    A3011 equ <"too many unwind codes in FRAME procedure">
    A3012 equ <"registers AH-DH may not be used with SPL-DIL or R8-R15">
    A3013 equ <"multiple overrides">
    A3014 equ <"unknown fixup type: %u at %s.%x">
    A3015 equ <"filename parameter must be enclosed in <> or quotes">
    A3016 equ <"literal expected after '='">
    A3017 equ <".SAFESEH argument must be a PROC">
    A3018 equ <"invalid operand for %s : %s">
    A3019 equ <"invalid fixup type for %s : %u at location %s:%x">
    A3020 equ <"cannot open file : %s">
    A3021 equ <"I/O error closing file : %s">
    A3022 equ <".CASE redefinition : %s(%d) : %s(%d)">


;; Warnings -- MASM

    A4000 equ <"cannot modify READONLY segment">
    A4002 equ <"non-unique STRUCT/UNION field used without qualification">
    A4003 equ <"start address on END directive ignored with .STARTUP">
    A4004 equ <"cannot ASSUME CS">
    A4005 equ <"unknown default prologue argument">
    A4006 equ <"too many arguments in macro call : %s">
    A4007 equ <"option untranslated, directive required : %s">
    A4008 equ <"invalid command-line option value, default is used : %s">
    A4009 equ <"insufficient memory for /EP : /EP ignored">
    A4010 equ <"expected '!>' on text literal">
    A4011 equ <"multiple .MODEL directives found : .MODEL ignored">
    A4012 equ <"line number information for segment without class 'CODE' : %s">
    A4013 equ <"instructions and initialized data not supported in AT segments">
    A4015 equ <"directive ignored with /coff switch">
    A4910 equ <"cannot open file : %s">

;; Warnings -- ASMC

    A8000 equ <"invalid command-line option: %s">
    A8001 equ <"unexpected literal found in expression : %s">
    A8002 equ <"invalid combination with segment alignment : %d">
    A8003 equ <"segment exceeds 64K limit: %s">
    A8004 equ <"symbol type conflict : %s">
    A8005 equ <"IF[n]DEF expects a plain symbol as argument : %s">
    A8006 equ <"instructions and initialized data not supported in %s segments">
    A8007 equ <"16bit fixup for 32bit label : %s">
    A8008 equ <"displacement out of range: 0x%lX">
    A8009 equ <"no start label defined">
    A8010 equ <"no stack defined">
    A8011 equ <"for -coff leading underscore required for start label: %s">
    A8012 equ <"library name is missing">
    A8013 equ <"ELF GNU extensions (8/16-bit relocations) used">
    A8014 equ <"LOADDS ignored in flat model">
    A8015 equ <"directive ignored without -%s switch">
    A8016 equ <"text macro used prior to definition: %s">
    A8017 equ <"ignored: %s">
    A8018 equ <"group definition too large, truncated : %s">
    A8019 equ <"size not specified, assuming: %s">
    A8020 equ <"constant expected">
    A8021 equ <"opcode size suffix ignored for segment registers">
    A8022 equ <"INVOKE argument type mismatch : %d">

;; warning level 3 -- MASM

    A5000 equ <"@@: label defined but not referenced">
    A5001 equ <"expression expected, assume value 0">
    A5002 equ <"externdef previously assumed to be external">
    A5003 equ <"length of symbol previously assumed to be different">
    A5004 equ <"symbol previously assumed to not be in a group">
    A5005 equ <"types are different">
    A6001 equ <"no return from procedure">
    A6003 equ <"conditional jump lengthened">
    A6004 equ <"procedure argument or local not referenced : %s">
    A6005 equ <"expression condition may be pass-dependent: %s">

;; warning level 3 -- ASMC

    A7000 equ <"symbol language attribute conflict : %s">
    A7001 equ <"positive value expected">
    A7002 equ <"register value overwritten by INVOKE">
    A7003 equ <"far call is converted to near call.">
    A7004 equ <"floating-point initializer ignored">
    A7005 equ <"directive ignored: %s">
    A7006 equ <"parameter/local name is reserved word: %s">
    A7007 equ <".CASE without .ENDC: assumed fall through">
    A7008 equ <"cannot delay macro function: %s">
    A7009 equ <"magnitude of offset exceeds 16 bit">

E macro string
    exitm<@CStr(string)>
    endm

    .data

    align 8

E0 string_t E(A1000),E(A1001),E(A1002),E(INTER),E(INTER),E(A1005),E(A1006),E(A1007),E(A1008),E(A1009),
            E(A1010),E(A1011),E(A1012),E(INTER),E(INTER),E(INTER),E(INTER),E(A1017),E(A1018)
E1 string_t E(INTER),E(INTER),E(INTER),E(INTER),E(A2004),E(A2005),E(A2006),E(A2007),E(A2008),E(A2009),
            E(A2010),E(A2011),E(A2012),E(A2013),E(A2014),E(A2015),E(A2016),E(INTER),E(A2018),E(A2019),
            E(INTER),E(INTER),E(A2022),E(A2023),E(A2024),E(A2025),E(A2026),E(INTER),E(A2028),E(A2029),
            E(A2030),E(A2031),E(A2032),E(A2033),E(A2034),E(INTER),E(A2036),E(A2037),E(INTER),E(A2039),
            E(INTER),E(A2041),E(INTER),E(A2043),E(INTER),E(A2045),E(A2046),E(A2047),E(A2048),E(INTER),
            E(A2050),E(A2051),E(A2052),E(A2053),E(A2054),E(A2055),E(A2056),E(A2057),E(A2058),E(A2059),
            E(A2060),E(A2061),E(A2062),E(A2063),E(A2064),E(A2065),E(A2066),E(INTER),E(A2068),E(INTER),
            E(A2070),E(A2071),E(A2072),E(INTER),E(A2074),E(A2075),E(A2076),E(A2077),E(INTER),E(A2079),
            E(A2080),E(A2081),E(A2082),E(A2083),E(A2084),E(A2085),E(A2086),E(A2087),E(A2088),E(A2089),
            E(A2090),E(A2091),E(A2092),E(A2093),E(A2094),E(A2095),E(A2096),E(A2097),E(A2098),E(INTER),
            E(A2100),E(A2101),E(INTER),E(A2103),E(A2104),E(A2105),E(INTER),E(A2107),E(A2108),E(INTER),
            E(A2110),E(A2111),E(A2112),E(A2113),E(A2114),E(INTER),E(INTER),E(INTER),E(INTER),E(A2119),
            E(A2120),E(A2121),E(INTER),E(A2123),E(INTER),E(A2125),E(INTER),E(INTER),E(INTER),E(A2129),
            E(INTER),E(A2131),E(A2132),E(A2133),E(INTER),E(INTER),E(A2136),E(INTER),E(INTER),E(INTER),
            E(INTER),E(A2141),E(A2142),E(A2143),E(A2144),E(A2145),E(INTER),E(A2147),E(A2148),E(INTER),
            E(INTER),E(A2151),E(INTER),E(INTER),E(A2154),E(A2155),E(A2156),E(A2157),E(INTER),E(A2159),
            E(INTER),E(INTER),E(INTER),E(INTER),E(INTER),E(INTER),E(A2166),E(A2167),E(INTER),E(A2169),
            E(A2170),E(INTER),E(A2172),E(INTER),E(INTER),E(A2175),E(INTER),E(INTER),E(A2178),E(A2179),
            E(INTER),E(A2181),E(INTER),E(INTER),E(INTER),E(INTER),E(INTER),E(A2187),E(INTER),E(A2189),
            E(A2190),E(INTER),E(INTER),E(INTER),E(INTER),E(INTER),E(INTER),E(INTER),E(INTER),E(A2199),
            E(A2200),E(INTER),E(A2202),E(INTER),E(INTER),E(INTER),E(A2206),E(INTER),E(INTER),E(INTER),
            E(INTER),E(INTER),E(INTER),E(INTER),E(A2214),E(INTER),E(INTER),E(A2217),E(INTER),E(INTER)

MAX_E1 equ ($ - E1) / string_t
E2 string_t E(A3000),E(A3001),E(A3002),E(A3003),E(A3004),E(A3005),E(A3006),E(A3007),E(A3008),E(A3009),
            E(A3010),E(A3011),E(A3012),E(A3013),E(A3014),E(A3015),E(A3016),E(A3017),E(A3018),E(A3019),
            E(A3020),E(A3021),E(A3022)
W1 string_t E(INTER),E(INTER),E(INTER),E(A4003),E(INTER),E(A4005),E(A4006),E(A4007),E(A4008),E(INTER),
            E(INTER),E(A4011),E(A4012),E(INTER),E(A4910)
W2 string_t E(INTER)
W3 string_t E(INTER),E(INTER),E(INTER),E(A6003),E(A6004),E(A6005)
W4 string_t E(A7000),E(A7001),E(A7002),E(A7003),E(A7004),E(A7005),E(A7006),E(A7007),E(A7008),E(A7009)
W5 string_t E(A8000),E(A8001),E(A8002),E(A8003),E(A8004),E(A8005),E(A8006),E(A8007),E(A8008),E(A8009),
            E(A8010),E(A8011),E(A8012),E(A8013),E(A8014),E(A8015),E(INTER),E(A8017),E(A8018),E(A8019),
            E(A8020),E(A8021),E(A8022)

if 0
MS string_t E("name"),E("page"),E("title"),E("low"),E("high"),E("size"),
            E("length"),E("this"),E("mask"),E("width"),E("type"),0
endif
define MAX_E0 lengthof(E0)
define MAX_E2 lengthof(E2)
define MAX_W1 lengthof(W1)
define MAX_W2 lengthof(W2)
define MAX_W3 lengthof(W3)
define MAX_W4 lengthof(W4)
define MAX_W5 lengthof(W5)

table string_t  E0,E1,E2,W1,W2,W3,W4,W5
maxid uint_t    MAX_E0,MAX_E1,MAX_E2,MAX_W1,MAX_W2,MAX_W3,MAX_W4,MAX_W5

define MIN_ID 1000
define MAX_ID (8000+MAX_W5)

;
; Notes
;
N0000   db "%*s%s(%u): Included by",0
N0001   db "%*s%s(%u)[%s]: Macro called from",0
N0002   db "%*s%s(%u): iteration %u: Macro called from",0
N0003   db "%*s%s(%u): Main line code",0
NOTE    string_t N0000,N0001,N0002,N0003

    .code

print_err proc __ccall private uses rsi rdi rbx erbuf:string_t, format:string_t, args:ptr string_t

    write_logo()
    tvsprintf( erbuf, format, args )
    ;
    ; v2.05: new option -eq
    ;
    .if ( !Options.no_error_disp )
        tprintf( "%s\n", erbuf )
    .endif
    ;
    ; open .err file if not already open and a name is given
    ;
    mov rbx,MODULE.curr_fname[ERR*string_t]
    mov rcx,MODULE.curr_file[ERR*string_t]

    .if ( !rcx && rbx )

        .if fopen( rbx, "w" )

            mov MODULE.curr_file[ERR*string_t],rax
        .else
            ;
            ; v2.06: no fatal error anymore if error file cannot be written
            ; set to NULL before asmerr()!
            ;
            mov MODULE.curr_fname[ERR*string_t],rax
            ;
            ; disable -eq!
            ;
            mov Options.no_error_disp,0
            asmerr( 4910, rbx )
        .endif
    .endif

    mov rbx,MODULE.curr_file[ERR*string_t]
    .if rbx

        fwrite( erbuf, 1, tstrlen(erbuf), rbx )
        fwrite( "\n", 1, 1, rbx )

        .if ( Parse_Pass == PASS_1 && MODULE.curr_file[LST*string_t] )

            GetCurrOffset()
            LstWrite( LSTTYPE_DIRECTIVE, eax, 0 )
            LstPrintf( "                           %s", erbuf )
            LstNL()
        .endif
    .endif
    ret

print_err endp


errexit proc __ccall private

    .if MODULE.curr_fname[ASM*string_t]

        longjmp( &jmpenv, 3 )
    .endif

    mov rcx,MODULE.curr_file[OBJ*string_t]
    .if rcx

        fclose( rcx )
        remove( MODULE.curr_fname[OBJ*string_t] )
    .endif
    exit(1)

errexit endp


asmerr proc __ccall uses rsi rdi rbx value:int_t, args:vararg

   .new erbuf[512]:char_t
   .new format[512]:char_t

    lea rdi,format
    ldr ebx,value

    .repeat

        .repeat

            .break .if ( ebx < MIN_ID )
            .break .if ( ebx > MAX_ID )

            .if ( ebx >= 4000 )

                .break(1) .if ( !Options.warning_error && !Options.warning_level )
                .break(1) .if ( ebx >= 5000 && ebx < 8000 && Options.warning_level < 3 )
                .break(1) .if warning_disable(ebx)

            .endif

            tstrcpy( rdi, "ASMC : " )
            mov rdx,MODULE.src_stack

            .while rdx

                movzx   eax,[rdx].src_item.srcfile
                mov     rcx,MODULE.FNames
                mov     rcx,[rcx+rax*string_t]
                mov     eax,[rdx].src_item.line_num
                cmp     [rdx].src_item.type,SIT_FILE
                mov     rdx,[rdx].src_item.next
                .ifz
                    .if ( MODULE.EndDirFound )
                        tsprintf( rdi, "%s : ", rcx )
                    .else
                        tsprintf( rdi, "%s(%u) : ", rcx, eax )
                    .endif
                    .break
                .endif
            .endw

            .if ( ebx < 2000 )
                lea rax,@CStr("fatal error")
            .elseif ( ebx < 4000 )
                lea rax,@CStr("error")
            .else
                lea rax,@CStr("warning")
            .endif
            tstrcat(rdi, rax)

            add rdi,tstrlen(rdi)
            tsprintf(rdi, " A%04u: ", ebx)

            xor ecx,ecx
            lea eax,[rbx-1000]
            .while ( eax >= 1000 )

                add ecx,1
                sub eax,1000
            .endw
            .if ( eax == 910 )

                mov eax,14
            .endif
            lea rdx,maxid
            .break .if eax >= [rdx+rcx*4]

            lea rsi,table
            mov rsi,[rsi+rcx*string_t]
            mov rsi,[rsi+rax*string_t]

            lea rdx,E(INTER)
            .break .if ( rsi == rdx )

            lea rdi,format
            tstrcat( rdi, rsi )
if 0
            .new masm[64]:char_t
            .if ( ebx == 2006 )

                mov rbx,args
                lea rsi,MS

                .while 1

                    .lodsd
                    .break .if !rax

                    .ifd ( tstricmp( rax, rbx ) == 0 )

                        tstrcpy( &masm, rbx )
                        mov args,tstrcat( rax, " -- use option /Zne for Masm keywords" )
                       .break
                    .endif
                .endw
            .endif
endif
            print_err( &erbuf, rdi, &args )

            lea rsi,erbuf
            mov ebx,value

            .if ( ebx == 1012 )

                errexit()
            .endif

            .if ( ebx >= 4000 )

                .if ( !Options.warning_error )
                    inc MODULE.warning_count
                .else
                    inc MODULE.error_count
                .endif
            .else
                inc MODULE.error_count
            .endif

            mov eax,Options.error_limit
            .if ( eax != -1 )
                inc eax
                .if ( MODULE.error_count >= eax )
                    asmerr( 1012 )
                .endif
            .endif
            .if ( ebx >= 2000 )
                print_source_nesting_structure()
            .else
                errexit()
            .endif
            .break(1)
        .until 1

        tprintf( "ASMC : fatal error A1901: %s\n", INTER )
        errexit()
    .until 1
    .return( ERROR )

asmerr endp


WriteError proc __ccall

    .return( asmerr( 1002, MODULE.curr_fname[OBJ*string_t] ) )

WriteError endp


PrintNote proc __ccall value:int_t, args:vararg

   .new erbuf[512]:byte

    ldr ecx,value
    lea rdx,NOTE
   .return( print_err( &erbuf, [rdx+rcx*string_t], &args ) )

PrintNote endp

    END
