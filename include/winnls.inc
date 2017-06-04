ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINDEF_
 include windef.inc
endif

.xlist
if defined(_KERNEL32_) or defined(__PE__)
option dllimport:<kernel32>
endif

ifndef LPSYSTEMTIME
SYSTEMTIME	STRUC
wYear		dw ?
wMonth		dw ?
wDayOfWeek	dw ?
wDay		dw ?
wHour		dw ?
wMinute		dw ?
wSecond		dw ?
wMilliseconds	dw ?
SYSTEMTIME	ENDS
LPSYSTEMTIME	TYPEDEF PTR SYSTEMTIME
endif


MAX_LEADBYTES		  equ 12	; 5 ranges, 2 bytes ea., 0 term.
MAX_DEFAULTCHAR		  equ 2		; single or double byte

MB_PRECOMPOSED		  equ 0x00000001  ; use precomposed chars
MB_COMPOSITE		  equ 0x00000002  ; use composite chars
MB_USEGLYPHCHARS	  equ 0x00000004  ; use glyph chars, not ctrl chars
MB_ERR_INVALID_CHARS	  equ 0x00000008  ; error for invalid chars

WC_COMPOSITECHECK	  equ 0x00000200  ; convert composite to precomposed
WC_DISCARDNS		  equ 0x00000010  ; discard non-spacing chars
WC_SEPCHARS		  equ 0x00000020  ; generate separate chars
WC_DEFAULTCHAR		  equ 0x00000040  ; replace w/ default char
WC_NO_BEST_FIT_CHARS	  equ 0x00000400  ; do not use best fit chars

CT_CTYPE1		  equ 0x00000001  ; ctype 1 information
CT_CTYPE2		  equ 0x00000002  ; ctype 2 information
CT_CTYPE3		  equ 0x00000004  ; ctype 3 information

C1_UPPER		  equ 0x0001	  ; upper case
C1_LOWER		  equ 0x0002	  ; lower case
C1_DIGIT		  equ 0x0004	  ; decimal digits
C1_SPACE		  equ 0x0008	  ; spacing characters
C1_PUNCT		  equ 0x0010	  ; punctuation characters
C1_CNTRL		  equ 0x0020	  ; control characters
C1_BLANK		  equ 0x0040	  ; blank characters
C1_XDIGIT		  equ 0x0080	  ; other digits
C1_ALPHA		  equ 0x0100	  ; any linguistic character

C2_LEFTTORIGHT		  equ 0x0001	  ; left to right
C2_RIGHTTOLEFT		  equ 0x0002	  ; right to left

C2_EUROPENUMBER		  equ 0x0003	  ; European number, digit
C2_EUROPESEPARATOR	  equ 0x0004	  ; European numeric separator
C2_EUROPETERMINATOR	  equ 0x0005	  ; European numeric terminator
C2_ARABICNUMBER		  equ 0x0006	  ; Arabic number
C2_COMMONSEPARATOR	  equ 0x0007	  ; common numeric separator

C2_BLOCKSEPARATOR	  equ 0x0008	  ; block separator
C2_SEGMENTSEPARATOR	  equ 0x0009	  ; segment separator
C2_WHITESPACE		  equ 0x000A	  ; white space
C2_OTHERNEUTRAL		  equ 0x000B	  ; other neutrals

C2_NOTAPPLICABLE	  equ 0x0000	  ; no implicit directionality

C3_NONSPACING		  equ 0x0001	  ; nonspacing character
C3_DIACRITIC		  equ 0x0002	  ; diacritic mark
C3_VOWELMARK		  equ 0x0004	  ; vowel mark
C3_SYMBOL		  equ 0x0008	  ; symbols

C3_KATAKANA		  equ 0x0010	  ; katakana character
C3_HIRAGANA		  equ 0x0020	  ; hiragana character
C3_HALFWIDTH		  equ 0x0040	  ; half width character
C3_FULLWIDTH		  equ 0x0080	  ; full width character
C3_IDEOGRAPH		  equ 0x0100	  ; ideographic character
C3_KASHIDA		  equ 0x0200	  ; Arabic kashida character
C3_LEXICAL		  equ 0x0400	  ; lexical character

C3_ALPHA		  equ 0x8000	  ; any linguistic char (C1_ALPHA)

C3_NOTAPPLICABLE	  equ 0x0000	  ; ctype 3 is not applicable

NORM_IGNORECASE		  equ 0x00000001  ; ignore case
NORM_IGNORENONSPACE	  equ 0x00000002  ; ignore nonspacing chars
NORM_IGNORESYMBOLS	  equ 0x00000004  ; ignore symbols

NORM_IGNOREKANATYPE	  equ 0x00010000  ; ignore kanatype
NORM_IGNOREWIDTH	  equ 0x00020000  ; ignore width


MAP_FOLDCZONE		  equ 0x00000010  ; fold compatibility zone chars
MAP_PRECOMPOSED		  equ 0x00000020  ; convert to precomposed chars
MAP_COMPOSITE		  equ 0x00000040  ; convert to composite chars
MAP_FOLDDIGITS		  equ 0x00000080  ; all digits to ASCII 0-9

MAP_EXPAND_LIGATURES	  equ 0x00002000  ; expand all ligatures

LCMAP_LOWERCASE		  equ 0x00000100  ; lower case letters
LCMAP_UPPERCASE		  equ 0x00000200  ; upper case letters
LCMAP_SORTKEY		  equ 0x00000400  ; WC sort key (normalize)
LCMAP_BYTEREV		  equ 0x00000800  ; byte reversal

LCMAP_HIRAGANA		  equ 0x00100000  ; map katakana to hiragana
LCMAP_KATAKANA		  equ 0x00200000  ; map hiragana to katakana
LCMAP_HALFWIDTH		  equ 0x00400000  ; map double byte to single byte
LCMAP_FULLWIDTH		  equ 0x00800000  ; map single byte to double byte

LCMAP_LINGUISTIC_CASING	  equ 0x01000000  ; use linguistic rules for casing

LCMAP_SIMPLIFIED_CHINESE  equ 0x02000000  ; map traditional chinese to simplified chinese
LCMAP_TRADITIONAL_CHINESE equ 0x04000000  ; map simplified chinese to traditional chinese


LCID_INSTALLED		  equ 0x00000001  ; installed locale ids
LCID_SUPPORTED		  equ 0x00000002  ; supported locale ids
LCID_ALTERNATE_SORTS	  equ 0x00000004  ; alternate sort locale ids


CP_INSTALLED		  equ 0x00000001  ; installed code page ids
CP_SUPPORTED		  equ 0x00000002  ; supported code page ids


SORT_STRINGSORT		  equ 0x00001000  ; use string sort method


CSTR_LESS_THAN		  equ 1		  ; string 1 less than string 2
CSTR_EQUAL		  equ 2		  ; string 1 equal to string 2
CSTR_GREATER_THAN	  equ 3		  ; string 1 greater than string 2


CP_ACP			  equ 0		  ; default to ANSI code page
CP_OEMCP		  equ 1		  ; default to OEM  code page
CP_MACCP		  equ 2		  ; default to MAC  code page
CP_THREAD_ACP		  equ 3		  ; current thread's ANSI code page
CP_SYMBOL		  equ 42	  ; SYMBOL translations

CP_UTF7			  equ 65000	  ; UTF-7 translation
CP_UTF8			  equ 65001	  ; UTF-8 translation


CTRY_DEFAULT		  equ 0

CTRY_ALBANIA		  equ 355	  ; Albania
CTRY_ALGERIA		  equ 213	  ; Algeria
CTRY_ARGENTINA		  equ 54	  ; Argentina
CTRY_AUSTRALIA		  equ 61	  ; Australia
CTRY_AUSTRIA		  equ 43	  ; Austria
CTRY_BAHRAIN		  equ 973	  ; Bahrain
CTRY_BELARUS		  equ 375	  ; Belarus
CTRY_BELGIUM		  equ 32	  ; Belgium
CTRY_BELIZE		  equ 501	  ; Belize
CTRY_BOLIVIA		  equ 591	  ; Bolivia
CTRY_BRAZIL		  equ 55	  ; Brazil
CTRY_BRUNEI_DARUSSALAM	  equ 673	  ; Brunei Darussalam
CTRY_BULGARIA		  equ 359	  ; Bulgaria
CTRY_CANADA		  equ 2		  ; Canada
CTRY_CARIBBEAN		  equ 1		  ; Caribbean
CTRY_CHILE		  equ 56	  ; Chile
CTRY_COLOMBIA		  equ 57	  ; Colombia
CTRY_COSTA_RICA		  equ 506	  ; Costa Rica
CTRY_CROATIA		  equ 385	  ; Croatia
CTRY_CZECH		  equ 420	  ; Czech Republic
CTRY_DENMARK		  equ 45	  ; Denmark
CTRY_DOMINICAN_REPUBLIC	  equ 1		  ; Dominican Republic
CTRY_ECUADOR		  equ 593	  ; Ecuador
CTRY_EGYPT		  equ 20	  ; Egypt
CTRY_EL_SALVADOR	  equ 503	  ; El Salvador
CTRY_ESTONIA		  equ 372	  ; Estonia
CTRY_FAEROE_ISLANDS	  equ 298	  ; Faeroe Islands
CTRY_FINLAND		  equ 358	  ; Finland
CTRY_FRANCE		  equ 33	  ; France
CTRY_GERMANY		  equ 49	  ; Germany
CTRY_GREECE		  equ 30	  ; Greece
CTRY_GUATEMALA		  equ 502	  ; Guatemala
CTRY_HONDURAS		  equ 504	  ; Honduras
CTRY_HONG_KONG		  equ 852	  ; Hong Kong
CTRY_HUNGARY		  equ 36	  ; Hungary
CTRY_ICELAND		  equ 354	  ; Iceland
CTRY_INDIA		  equ 91	  ; India
CTRY_INDONESIA		  equ 62	  ; Indonesia
CTRY_IRAN		  equ 981	  ; Iran
CTRY_IRAQ		  equ 964	  ; Iraq
CTRY_IRELAND		  equ 353	  ; Ireland
CTRY_ISRAEL		  equ 972	  ; Israel
CTRY_ITALY		  equ 39	  ; Italy
CTRY_JAMAICA		  equ 1		  ; Jamaica
CTRY_JAPAN		  equ 81	  ; Japan
CTRY_JORDAN		  equ 962	  ; Jordan
CTRY_KENYA		  equ 254	  ; Kenya
CTRY_KUWAIT		  equ 965	  ; Kuwait
CTRY_LATVIA		  equ 371	  ; Latvia
CTRY_LEBANON		  equ 961	  ; Lebanon
CTRY_LIBYA		  equ 218	  ; Libya
CTRY_LIECHTENSTEIN	  equ 41	  ; Liechtenstein
CTRY_LITHUANIA		  equ 370	  ; Lithuania
CTRY_LUXEMBOURG		  equ 352	  ; Luxembourg
CTRY_MACAU		  equ 853	  ; Macau
CTRY_MACEDONIA		  equ 389	  ; Republic of Macedonia
CTRY_MALAYSIA		  equ 60	  ; Malaysia
CTRY_MEXICO		  equ 52	  ; Mexico
CTRY_MONACO		  equ 33	  ; Principality of Monaco
CTRY_MOROCCO		  equ 212	  ; Morocco
CTRY_NETHERLANDS	  equ 31	  ; Netherlands
CTRY_NEW_ZEALAND	  equ 64	  ; New Zealand
CTRY_NICARAGUA		  equ 505	  ; Nicaragua
CTRY_NORWAY		  equ 47	  ; Norway
CTRY_OMAN		  equ 968	  ; Oman
CTRY_PAKISTAN		  equ 92	  ; Islamic Republic of Pakistan
CTRY_PANAMA		  equ 507	  ; Panama
CTRY_PARAGUAY		  equ 595	  ; Paraguay
CTRY_PERU		  equ 51	  ; Peru
CTRY_PHILIPPINES	  equ 63	  ; Republic of the Philippines
CTRY_POLAND		  equ 48	  ; Poland
CTRY_PORTUGAL		  equ 351	  ; Portugal
CTRY_PRCHINA		  equ 86	  ; People's Republic of China
CTRY_PUERTO_RICO	  equ 1		  ; Puerto Rico
CTRY_QATAR		  equ 974	  ; Qatar
CTRY_ROMANIA		  equ 40	  ; Romania
CTRY_RUSSIA		  equ 7		  ; Russia
CTRY_SAUDI_ARABIA	  equ 966	  ; Saudi Arabia
CTRY_SERBIA		  equ 381	  ; Serbia
CTRY_SINGAPORE		  equ 65	  ; Singapore
CTRY_SLOVAK		  equ 421	  ; Slovak Republic
CTRY_SLOVENIA		  equ 386	  ; Slovenia
CTRY_SOUTH_AFRICA	  equ 27	  ; South Africa
CTRY_SOUTH_KOREA	  equ 82	  ; South Korea
CTRY_SPAIN		  equ 34	  ; Spain
CTRY_SWEDEN		  equ 46	  ; Sweden
CTRY_SWITZERLAND	  equ 41	  ; Switzerland
CTRY_SYRIA		  equ 963	  ; Syria
CTRY_TAIWAN		  equ 886	  ; Taiwan Region
CTRY_THAILAND		  equ 66	  ; Thailand
CTRY_TRINIDAD_Y_TOBAGO	  equ 1		  ; Trinidad y Tobago
CTRY_TUNISIA		  equ 216	  ; Tunisia
CTRY_TURKEY		  equ 90	  ; Turkey
CTRY_UAE		  equ 971	  ; U.A.E.
CTRY_UKRAINE		  equ 380	  ; Ukraine
CTRY_UNITED_KINGDOM	  equ 44	  ; United Kingdom
CTRY_UNITED_STATES	  equ 1		  ; United States
CTRY_URUGUAY		  equ 598	  ; Uruguay
CTRY_VENEZUELA		  equ 58	  ; Venezuela
CTRY_VIET_NAM		  equ 84	  ; Viet Nam
CTRY_YEMEN		  equ 967	  ; Yemen
CTRY_ZIMBABWE		  equ 263	  ; Zimbabwe



LOCALE_NOUSEROVERRIDE	      equ 0x80000000   ; do not use user overrides
LOCALE_USE_CP_ACP	      equ 0x40000000   ; use the system ACP

LOCALE_RETURN_NUMBER	      equ 0x20000000   ; return number instead of string


LOCALE_ILANGUAGE	      equ 0x00000001   ; language id
LOCALE_SLANGUAGE	      equ 0x00000002   ; localized name of language
LOCALE_SENGLANGUAGE	      equ 0x00001001   ; English name of language
LOCALE_SABBREVLANGNAME	      equ 0x00000003   ; abbreviated language name
LOCALE_SNATIVELANGNAME	      equ 0x00000004   ; native name of language

LOCALE_ICOUNTRY		      equ 0x00000005   ; country code
LOCALE_SCOUNTRY		      equ 0x00000006   ; localized name of country
LOCALE_SENGCOUNTRY	      equ 0x00001002   ; English name of country
LOCALE_SABBREVCTRYNAME	      equ 0x00000007   ; abbreviated country name
LOCALE_SNATIVECTRYNAME	      equ 0x00000008   ; native name of country

LOCALE_IDEFAULTLANGUAGE	      equ 0x00000009   ; default language id
LOCALE_IDEFAULTCOUNTRY	      equ 0x0000000A   ; default country code
LOCALE_IDEFAULTCODEPAGE	      equ 0x0000000B   ; default oem code page
LOCALE_IDEFAULTANSICODEPAGE   equ 0x00001004   ; default ansi code page
LOCALE_IDEFAULTMACCODEPAGE    equ 0x00001011   ; default mac code page

LOCALE_SLIST		      equ 0x0000000C   ; list item separator
LOCALE_IMEASURE		      equ 0x0000000D   ; 0 = metric, 1 = US

LOCALE_SDECIMAL		      equ 0x0000000E   ; decimal separator
LOCALE_STHOUSAND	      equ 0x0000000F   ; thousand separator
LOCALE_SGROUPING	      equ 0x00000010   ; digit grouping
LOCALE_IDIGITS		      equ 0x00000011   ; number of fractional digits
LOCALE_ILZERO		      equ 0x00000012   ; leading zeros for decimal
LOCALE_INEGNUMBER	      equ 0x00001010   ; negative number mode
LOCALE_SNATIVEDIGITS	      equ 0x00000013   ; native ascii 0-9

LOCALE_SCURRENCY	      equ 0x00000014   ; local monetary symbol
LOCALE_SINTLSYMBOL	      equ 0x00000015   ; intl monetary symbol
LOCALE_SMONDECIMALSEP	      equ 0x00000016   ; monetary decimal separator
LOCALE_SMONTHOUSANDSEP	      equ 0x00000017   ; monetary thousand separator
LOCALE_SMONGROUPING	      equ 0x00000018   ; monetary grouping
LOCALE_ICURRDIGITS	      equ 0x00000019   ; # local monetary digits
LOCALE_IINTLCURRDIGITS	      equ 0x0000001A   ; # intl monetary digits
LOCALE_ICURRENCY	      equ 0x0000001B   ; positive currency mode
LOCALE_INEGCURR		      equ 0x0000001C   ; negative currency mode

LOCALE_SDATE		      equ 0x0000001D   ; date separator
LOCALE_STIME		      equ 0x0000001E   ; time separator
LOCALE_SSHORTDATE	      equ 0x0000001F   ; short date format string
LOCALE_SLONGDATE	      equ 0x00000020   ; long date format string
LOCALE_STIMEFORMAT	      equ 0x00001003   ; time format string
LOCALE_IDATE		      equ 0x00000021   ; short date format ordering
LOCALE_ILDATE		      equ 0x00000022   ; long date format ordering
LOCALE_ITIME		      equ 0x00000023   ; time format specifier
LOCALE_ITIMEMARKPOSN	      equ 0x00001005   ; time marker position
LOCALE_ICENTURY		      equ 0x00000024   ; century format specifier (short date)
LOCALE_ITLZERO		      equ 0x00000025   ; leading zeros in time field
LOCALE_IDAYLZERO	      equ 0x00000026   ; leading zeros in day field (short date)
LOCALE_IMONLZERO	      equ 0x00000027   ; leading zeros in month field (short date)
LOCALE_S1159		      equ 0x00000028   ; AM designator
LOCALE_S2359		      equ 0x00000029   ; PM designator

LOCALE_ICALENDARTYPE	      equ 0x00001009	  ; type of calendar specifier
LOCALE_IOPTIONALCALENDAR      equ 0x0000100B	  ; additional calendar types specifier
LOCALE_IFIRSTDAYOFWEEK	      equ 0x0000100C	  ; first day of week specifier
LOCALE_IFIRSTWEEKOFYEAR	      equ 0x0000100D	  ; first week of year specifier

LOCALE_SDAYNAME1	      equ 0x0000002A	  ; long name for Monday
LOCALE_SDAYNAME2	      equ 0x0000002B	  ; long name for Tuesday
LOCALE_SDAYNAME3	      equ 0x0000002C	  ; long name for Wednesday
LOCALE_SDAYNAME4	      equ 0x0000002D	  ; long name for Thursday
LOCALE_SDAYNAME5	      equ 0x0000002E	  ; long name for Friday
LOCALE_SDAYNAME6	      equ 0x0000002F	  ; long name for Saturday
LOCALE_SDAYNAME7	      equ 0x00000030	  ; long name for Sunday
LOCALE_SABBREVDAYNAME1	      equ 0x00000031	  ; abbreviated name for Monday
LOCALE_SABBREVDAYNAME2	      equ 0x00000032	  ; abbreviated name for Tuesday
LOCALE_SABBREVDAYNAME3	      equ 0x00000033	  ; abbreviated name for Wednesday
LOCALE_SABBREVDAYNAME4	      equ 0x00000034	  ; abbreviated name for Thursday
LOCALE_SABBREVDAYNAME5	      equ 0x00000035	  ; abbreviated name for Friday
LOCALE_SABBREVDAYNAME6	      equ 0x00000036	  ; abbreviated name for Saturday
LOCALE_SABBREVDAYNAME7	      equ 0x00000037	  ; abbreviated name for Sunday
LOCALE_SMONTHNAME1	      equ 0x00000038	  ; long name for January
LOCALE_SMONTHNAME2	      equ 0x00000039	  ; long name for February
LOCALE_SMONTHNAME3	      equ 0x0000003A	  ; long name for March
LOCALE_SMONTHNAME4	      equ 0x0000003B	  ; long name for April
LOCALE_SMONTHNAME5	      equ 0x0000003C	  ; long name for May
LOCALE_SMONTHNAME6	      equ 0x0000003D	  ; long name for June
LOCALE_SMONTHNAME7	      equ 0x0000003E	  ; long name for July
LOCALE_SMONTHNAME8	      equ 0x0000003F	  ; long name for August
LOCALE_SMONTHNAME9	      equ 0x00000040	  ; long name for September
LOCALE_SMONTHNAME10	      equ 0x00000041	  ; long name for October
LOCALE_SMONTHNAME11	      equ 0x00000042	  ; long name for November
LOCALE_SMONTHNAME12	      equ 0x00000043	  ; long name for December
LOCALE_SMONTHNAME13	      equ 0x0000100E	  ; long name for 13th month (if exists)
LOCALE_SABBREVMONTHNAME1      equ 0x00000044	  ; abbreviated name for January
LOCALE_SABBREVMONTHNAME2      equ 0x00000045	  ; abbreviated name for February
LOCALE_SABBREVMONTHNAME3      equ 0x00000046	  ; abbreviated name for March
LOCALE_SABBREVMONTHNAME4      equ 0x00000047	  ; abbreviated name for April
LOCALE_SABBREVMONTHNAME5      equ 0x00000048	  ; abbreviated name for May
LOCALE_SABBREVMONTHNAME6      equ 0x00000049	  ; abbreviated name for June
LOCALE_SABBREVMONTHNAME7      equ 0x0000004A	  ; abbreviated name for July
LOCALE_SABBREVMONTHNAME8      equ 0x0000004B	  ; abbreviated name for August
LOCALE_SABBREVMONTHNAME9      equ 0x0000004C	  ; abbreviated name for September
LOCALE_SABBREVMONTHNAME10     equ 0x0000004D	  ; abbreviated name for October
LOCALE_SABBREVMONTHNAME11     equ 0x0000004E	  ; abbreviated name for November
LOCALE_SABBREVMONTHNAME12     equ 0x0000004F	  ; abbreviated name for December
LOCALE_SABBREVMONTHNAME13     equ 0x0000100F	  ; abbreviated name for 13th month (if exists)

LOCALE_SPOSITIVESIGN	      equ 0x00000050	  ; positive sign
LOCALE_SNEGATIVESIGN	      equ 0x00000051	  ; negative sign
LOCALE_IPOSSIGNPOSN	      equ 0x00000052	  ; positive sign position
LOCALE_INEGSIGNPOSN	      equ 0x00000053	  ; negative sign position
LOCALE_IPOSSYMPRECEDES	      equ 0x00000054	  ; mon sym precedes pos amt
LOCALE_IPOSSEPBYSPACE	      equ 0x00000055	  ; mon sym sep by space from pos amt
LOCALE_INEGSYMPRECEDES	      equ 0x00000056	  ; mon sym precedes neg amt
LOCALE_INEGSEPBYSPACE	      equ 0x00000057	  ; mon sym sep by space from neg amt

LOCALE_FONTSIGNATURE	      equ 0x00000058	  ; font signature
LOCALE_SISO639LANGNAME	      equ 0x00000059	  ; ISO abbreviated language name
LOCALE_SISO3166CTRYNAME	      equ 0x0000005A	  ; ISO abbreviated country name

LOCALE_IDEFAULTEBCDICCODEPAGE equ 0x00001012	  ; default ebcdic code page
LOCALE_IPAPERSIZE	      equ 0x0000100A	  ; 0 = letter, 1 = a4, 2 = legal, 3 = a3
LOCALE_SENGCURRNAME	      equ 0x00001007	  ; english name of currency
LOCALE_SNATIVECURRNAME	      equ 0x00001008	  ; native name of currency
LOCALE_SYEARMONTH	      equ 0x00001006	  ; year month format string
LOCALE_SSORTNAME	      equ 0x00001013	  ; sort name
LOCALE_IDIGITSUBSTITUTION     equ 0x00001014	  ; 0 = none, 1 = context, 2 = native digit

TIME_NOMINUTESORSECONDS	  equ 0x00000001 ; do not use minutes or seconds
TIME_NOSECONDS		  equ 0x00000002 ; do not use seconds
TIME_NOTIMEMARKER	  equ 0x00000004 ; do not use time marker
TIME_FORCE24HOURFORMAT	  equ 0x00000008 ; always use 24 hour format


DATE_SHORTDATE		  equ 0x00000001 ; use short date picture
DATE_LONGDATE		  equ 0x00000002 ; use long date picture
DATE_USE_ALT_CALENDAR	  equ 0x00000004 ; use alternate calendar (if any)

DATE_YEARMONTH		  equ 0x00000008 ; use year month picture
DATE_LTRREADING		  equ 0x00000010 ; add marks for left to right reading order layout
DATE_RTLREADING		  equ 0x00000020 ; add marks for right to left reading order layout

CAL_ICALINTVALUE	  equ 0x00000001 ; calendar type
CAL_SCALNAME		  equ 0x00000002 ; native name of calendar
CAL_IYEAROFFSETRANGE	  equ 0x00000003 ; starting years of eras
CAL_SERASTRING		  equ 0x00000004 ; era name for IYearOffsetRanges
CAL_SSHORTDATE		  equ 0x00000005 ; short date format string
CAL_SLONGDATE		  equ 0x00000006 ; long date format string
CAL_SDAYNAME1		  equ 0x00000007 ; native name for Monday
CAL_SDAYNAME2		  equ 0x00000008 ; native name for Tuesday
CAL_SDAYNAME3		  equ 0x00000009 ; native name for Wednesday
CAL_SDAYNAME4		  equ 0x0000000a ; native name for Thursday
CAL_SDAYNAME5		  equ 0x0000000b ; native name for Friday
CAL_SDAYNAME6		  equ 0x0000000c ; native name for Saturday
CAL_SDAYNAME7		  equ 0x0000000d ; native name for Sunday
CAL_SABBREVDAYNAME1	  equ 0x0000000e ; abbreviated name for Monday
CAL_SABBREVDAYNAME2	  equ 0x0000000f ; abbreviated name for Tuesday
CAL_SABBREVDAYNAME3	  equ 0x00000010 ; abbreviated name for Wednesday
CAL_SABBREVDAYNAME4	  equ 0x00000011 ; abbreviated name for Thursday
CAL_SABBREVDAYNAME5	  equ 0x00000012 ; abbreviated name for Friday
CAL_SABBREVDAYNAME6	  equ 0x00000013 ; abbreviated name for Saturday
CAL_SABBREVDAYNAME7	  equ 0x00000014 ; abbreviated name for Sunday
CAL_SMONTHNAME1		  equ 0x00000015 ; native name for January
CAL_SMONTHNAME2		  equ 0x00000016 ; native name for February
CAL_SMONTHNAME3		  equ 0x00000017 ; native name for March
CAL_SMONTHNAME4		  equ 0x00000018 ; native name for April
CAL_SMONTHNAME5		  equ 0x00000019 ; native name for May
CAL_SMONTHNAME6		  equ 0x0000001a ; native name for June
CAL_SMONTHNAME7		  equ 0x0000001b ; native name for July
CAL_SMONTHNAME8		  equ 0x0000001c ; native name for August
CAL_SMONTHNAME9		  equ 0x0000001d ; native name for September
CAL_SMONTHNAME10	  equ 0x0000001e ; native name for October
CAL_SMONTHNAME11	  equ 0x0000001f ; native name for November
CAL_SMONTHNAME12	  equ 0x00000020 ; native name for December
CAL_SMONTHNAME13	  equ 0x00000021 ; native name for 13th month (if any)
CAL_SABBREVMONTHNAME1	  equ 0x00000022 ; abbreviated name for January
CAL_SABBREVMONTHNAME2	  equ 0x00000023 ; abbreviated name for February
CAL_SABBREVMONTHNAME3	  equ 0x00000024 ; abbreviated name for March
CAL_SABBREVMONTHNAME4	  equ 0x00000025 ; abbreviated name for April
CAL_SABBREVMONTHNAME5	  equ 0x00000026 ; abbreviated name for May
CAL_SABBREVMONTHNAME6	  equ 0x00000027 ; abbreviated name for June
CAL_SABBREVMONTHNAME7	  equ 0x00000028 ; abbreviated name for July
CAL_SABBREVMONTHNAME8	  equ 0x00000029 ; abbreviated name for August
CAL_SABBREVMONTHNAME9	  equ 0x0000002a ; abbreviated name for September
CAL_SABBREVMONTHNAME10	  equ 0x0000002b ; abbreviated name for October
CAL_SABBREVMONTHNAME11	  equ 0x0000002c ; abbreviated name for November
CAL_SABBREVMONTHNAME12	  equ 0x0000002d ; abbreviated name for December
CAL_SABBREVMONTHNAME13	  equ 0x0000002e ; abbreviated name for 13th month (if any)

CAL_SYEARMONTH		  equ 0x0000002f ; year month format string

ENUM_ALL_CALENDARS	  equ 0xffffffff ; enumerate all calendars


CAL_GREGORIAN		       equ 1	; Gregorian (localized) calendar
CAL_GREGORIAN_US	       equ 2	; Gregorian (U.S.) calendar
CAL_JAPAN		       equ 3	; Japanese Emperor Era calendar
CAL_TAIWAN		       equ 4	; Taiwan Region Era calendar
CAL_KOREA		       equ 5	; Korean Tangun Era calendar
CAL_HIJRI		       equ 6	; Hijri (Arabic Lunar) calendar
CAL_THAI		       equ 7	; Thai calendar
CAL_HEBREW		       equ 8	; Hebrew (Lunar) calendar
CAL_GREGORIAN_ME_FRENCH	       equ 9	; Gregorian Middle East French calendar
CAL_GREGORIAN_ARABIC	       equ 10	; Gregorian Arabic calendar
CAL_GREGORIAN_XLIT_ENGLISH     equ 11	; Gregorian Transliterated English calendar
CAL_GREGORIAN_XLIT_FRENCH      equ 12	; Gregorian Transliterated French calendar


LCTYPE	typedef DWORD

CALTYPE typedef DWORD

CALID	typedef DWORD


WCHAR	typedef WORD

CPINFO			STRUC
MaxCharSize		UINT ?				; max length (in bytes) of a char
DefaultChar		SBYTE MAX_DEFAULTCHAR dup(?)	; default character
LeadByte		SBYTE MAX_LEADBYTES dup(?)	; lead byte ranges
CPINFO			ENDS
LPCPINFO		TYPEDEF PTR CPINFO

CPINFOEXA		STRUC
MaxCharSize		UINT ?				; max length (in bytes) of a char
DefaultChar		SBYTE MAX_DEFAULTCHAR dup(?)	; default character (MB)
LeadByte		SBYTE MAX_LEADBYTES dup(?)	; lead byte ranges
UnicodeDefaultChar	WCHAR ?				; default character (Unicode)
CodePage		UINT ?				; code page id
CodePageName		SBYTE MAX_PATH dup(?)		; code page name (Unicode)
CPINFOEXA		ENDS
LPCPINFOEXA		TYPEDEF PTR CPINFOEXA

CPINFOEXW		STRUC
MaxCharSize		UINT ?				; max length (in bytes) of a char
DefaultChar		SBYTE MAX_DEFAULTCHAR dup(?)	; default character (MB)
LeadByte		SBYTE MAX_LEADBYTES dup(?)	; lead byte ranges
UnicodeDefaultChar	WCHAR ?				; default character (Unicode)
CodePage		UINT ?				; code page id
CodePageName		WCHAR MAX_PATH dup(?)		; code page name (Unicode)
CPINFOEXW		ENDS
LPCPINFOEXW		TYPEDEF PTR CPINFOEXW

ifdef _UNICODE
CPINFOEX	TYPEDEF CPINFOEXW
LPCPINFOEX	TYPEDEF LPCPINFOEXW
else
CPINFOEX	TYPEDEF CPINFOEXA
LPCPINFOEX	TYPEDEF LPCPINFOEXA
endif ; _UNICODE



NUMBERFMTA	STRUC
NumDigits	UINT ?	       ; number of decimal digits
LeadingZero	UINT ?	       ; if leading zero in decimal fields
Grouping	UINT ?	       ; group size left of decimal
lpDecimalSep	LPSTR ?	       ; ptr to decimal separator string
lpThousandSep	LPSTR ?	       ; ptr to thousand separator string
NegativeOrder	UINT ?	       ; negative number ordering
NUMBERFMTA	ENDS
LPNUMBERFMTA	TYPEDEF PTR NUMBERFMTA

NUMBERFMTW	STRUC
NumDigits	UINT ?	       ; number of decimal digits
LeadingZero	UINT ?	       ; if leading zero in decimal fields
Grouping	UINT ?	       ; group size left of decimal
lpDecimalSep	LPWSTR ?       ; ptr to decimal separator string
lpThousandSep	LPWSTR ?       ; ptr to thousand separator string
NegativeOrder	UINT ?	       ; negative number ordering
NUMBERFMTW	ENDS
LPNUMBERFMTW	TYPEDEF PTR NUMBERFMTW

ifdef _UNICODE
NUMBERFMT	TYPEDEF NUMBERFMTW
LPNUMBERFMT	TYPEDEF LPNUMBERFMTW
else
NUMBERFMT	TYPEDEF NUMBERFMTA
LPNUMBERFMT	TYPEDEF LPNUMBERFMTA
endif



CURRENCYFMTA		STRUC
NumDigits		UINT ?	; number of decimal digits
LeadingZero		UINT ?	; if leading zero in decimal fields
Grouping		UINT ?	; group size left of decimal
lpDecimalSep		LPSTR ? ; ptr to decimal separator string
lpThousandSep		LPSTR ? ; ptr to thousand separator string
NegativeOrder		UINT ?	; negative currency ordering
PositiveOrder		UINT ?	; positive currency ordering
lpCurrencySymbol	LPSTR ? ; ptr to currency symbol string
CURRENCYFMTA		ENDS
LPCURRENCYFMTA		TYPEDEF PTR CURRENCYFMTA

CURRENCYFMTW		STRUC
NumDigits		UINT ?
LeadingZero		UINT ?
Grouping		UINT ?
lpDecimalSep		LPWSTR ?
lpThousandSep		LPWSTR ?
NegativeOrder		UINT ?
PositiveOrder		UINT ?
lpCurrencySymbol	LPWSTR ?
CURRENCYFMTW		ENDS
LPCURRENCYFMTW		TYPEDEF PTR CURRENCYFMTW

ifdef _UNICODE
CURRENCYFMT	TYPEDEF CURRENCYFMTW
LPCURRENCYFMT	TYPEDEF LPCURRENCYFMTW
else
CURRENCYFMT	TYPEDEF CURRENCYFMTA
LPCURRENCYFMT	TYPEDEF LPCURRENCYFMTA
endif


CALLBACKA1	TYPEDEF PROTO :LPSTR
CALLBACKA2	TYPEDEF PROTO :LPSTR, :CALID
CALLBACKW1	TYPEDEF PROTO :LPWSTR
CALLBACKW2	TYPEDEF PROTO :LPWSTR, :CALID

LPCALLBACKA1	TYPEDEF PTR CALLBACKA1
LPCALLBACKA2	TYPEDEF PTR CALLBACKA2
LPCALLBACKW1	TYPEDEF PTR CALLBACKW1
LPCALLBACKW2	TYPEDEF PTR CALLBACKW2

LOCALE_ENUMPROCA	TYPEDEF LPCALLBACKA1
CODEPAGE_ENUMPROCA	TYPEDEF LPCALLBACKA1
DATEFMT_ENUMPROCA	TYPEDEF LPCALLBACKA1
DATEFMT_ENUMPROCEXA	TYPEDEF LPCALLBACKA2
TIMEFMT_ENUMPROCA	TYPEDEF LPCALLBACKA1
CALINFO_ENUMPROCA	TYPEDEF LPCALLBACKA1
CALINFO_ENUMPROCEXA	TYPEDEF LPCALLBACKA2

LOCALE_ENUMPROCW	TYPEDEF LPCALLBACKW1
CODEPAGE_ENUMPROCW	TYPEDEF LPCALLBACKW1
DATEFMT_ENUMPROCW	TYPEDEF LPCALLBACKW1
DATEFMT_ENUMPROCEXW	TYPEDEF LPCALLBACKW2
TIMEFMT_ENUMPROCW	TYPEDEF LPCALLBACKW1
CALINFO_ENUMPROCW	TYPEDEF LPCALLBACKW1
CALINFO_ENUMPROCEXW	TYPEDEF LPCALLBACKW2

ifdef _UNICODE
LOCALE_ENUMPROC	    equ LOCALE_ENUMPROCW
CODEPAGE_ENUMPROC   equ CODEPAGE_ENUMPROCW
DATEFMT_ENUMPROC    equ DATEFMT_ENUMPROCW
DATEFMT_ENUMPROCEX  equ DATEFMT_ENUMPROCEXW
TIMEFMT_ENUMPROC    equ TIMEFMT_ENUMPROCW
CALINFO_ENUMPROC    equ CALINFO_ENUMPROCW
CALINFO_ENUMPROCEX  equ CALINFO_ENUMPROCEXW
else
LOCALE_ENUMPROC	    equ LOCALE_ENUMPROCA
CODEPAGE_ENUMPROC   equ CODEPAGE_ENUMPROCA
DATEFMT_ENUMPROC    equ DATEFMT_ENUMPROCA
DATEFMT_ENUMPROCEX  equ DATEFMT_ENUMPROCEXA
TIMEFMT_ENUMPROC    equ TIMEFMT_ENUMPROCA
CALINFO_ENUMPROC    equ CALINFO_ENUMPROCA
CALINFO_ENUMPROCEX  equ CALINFO_ENUMPROCEXA
endif





;BOOL
IsValidCodePage proto WINAPI \
	CodePage:	UINT
;UINT
GetACP proto WINAPI
;UINT
GetOEMCP proto WINAPI
;BOOL
GetCPInfo proto WINAPI \
	CodePage:	UINT,
	lpCPInfo:	LPCPINFO
;BOOL
GetCPInfoExA proto WINAPI \
	CodePage:	UINT,
	dwFlags:	DWORD,
	lpCPInfoEx:	LPCPINFOEXA
;BOOL
GetCPInfoExW proto WINAPI \
	CodePage:	UINT,
	dwFlags:	DWORD,
	lpCPInfoEx:	LPCPINFOEXW
ifdef _UNICODE
GetCPInfoEx  equ <GetCPInfoExW>
else
GetCPInfoEx  equ <GetCPInfoExA>
endif
;BOOL
IsDBCSLeadByte proto WINAPI \
	TestChar:	UINT ; BYTE
;BOOL
IsDBCSLeadByteEx proto WINAPI \
	CodePage:	UINT,
	TestChar:	UINT ; BYTE
;int
MultiByteToWideChar proto WINAPI \
	CodePage:	UINT,
	dwFlags:	DWORD,
	lpMultiByteStr: LPSTR,
	cchMultiByte:	SINT,
	lpWideCharStr:	LPWSTR,
	cchWideChar:	SINT
;int
WideCharToMultiByte proto WINAPI \
	CodePage:		UINT,
	dwFlags:		DWORD,
	lpWideCharStr:		LPWSTR,
	cchWideChar:		SINT,
	lpMultiByteStr:		LPSTR,
	cchMultiByte:		SINT,
	lpDefaultChar:		LPSTR,
	lpUsedDefaultChar:	LPBOOL


;int
CompareStringA proto WINAPI \
	Locale:		LCID,
	dwCmpFlags:	DWORD,
	lpString1:	LPSTR,
	cchCount1:	SINT,
	lpString2:	LPSTR,
	cchCount2:	SINT
;int
CompareStringW proto WINAPI \
	Locale:		LCID,
	dwCmpFlags:	DWORD,
	lpString1:	LPWSTR,
	cchCount1:	SINT,
	lpString2:	LPWSTR,
	cchCount2:	SINT
ifdef _UNICODE
CompareString  equ <CompareStringW>
else
CompareString  equ <CompareStringA>
endif
;int
LCMapStringA proto WINAPI \
	Locale:		LCID,
	dwMapFlags:	DWORD,
	lpSrcStr:	LPSTR,
	cchSrc:		SINT,
	lpDestStr:	LPSTR,
	cchDest:	SINT
;int
LCMapStringW proto WINAPI \
	Locale:		LCID,
	dwMapFlags:	DWORD,
	lpSrcStr:	LPWSTR,
	cchSrc:		SINT,
	lpDestStr:	LPWSTR,
	cchDest:	SINT
ifdef _UNICODE
LCMapString  equ <LCMapStringW>
else
LCMapString  equ <LCMapStringA>
endif
;int
GetLocaleInfoA proto WINAPI \
	Locale:		LCID,
	LCType:		LCTYPE,
	lpLCData:	LPSTR,
	cchData:	SINT
;int
GetLocaleInfoW proto WINAPI \
	Locale:		LCID,
	LCType:		LCTYPE,
	lpLCData:	LPWSTR,
	cchData:	SINT
ifdef _UNICODE
GetLocaleInfo  equ <GetLocaleInfoW>
else
GetLocaleInfo  equ <GetLocaleInfoA>
endif
;BOOL
SetLocaleInfoA proto WINAPI \
	Locale:		LCID,
	LCType:		LCTYPE,
	lpLCData:	LPSTR
;BOOL
SetLocaleInfoW proto WINAPI \
	Locale:		LCID,
	LCType:		LCTYPE,
	lpLCData:	LPWSTR
ifdef _UNICODE
SetLocaleInfo  equ <SetLocaleInfoW>
else
SetLocaleInfo  equ <SetLocaleInfoA>
endif
;int
GetTimeFormatA proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD,
	lpTime:		LPSYSTEMTIME,
	lpFormat:	LPSTR,
	lpTimeStr:	LPSTR,
	cchTime:	SINT
;int
GetTimeFormatW proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD,
	lpTime:		LPSYSTEMTIME,
	lpFormat:	LPWSTR,
	lpTimeStr:	LPWSTR,
	cchTime:	SINT
ifdef _UNICODE
GetTimeFormat  equ <GetTimeFormatW>
else
GetTimeFormat  equ <GetTimeFormatA>
endif

;int
GetDateFormatA proto WINAPI \
	Locale:		LCID,		; (LCID) locale for which date is to be formatted
	dwFlags:	DWORD,		; flags specifying function options
	lpDate:		LPSYSTEMTIME,	; date to be formatted
	lpFormat:	LPSTR,		; date format string
	lpDateStr:	LPSTR,		; buffer for storing formatted string
	cchDate:	SINT		; size of buffer
GetDateFormatW proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD,
	lpDate:		LPSYSTEMTIME,
	lpFormat:	LPWSTR,
	lpDateStr:	LPWSTR,
	cchDate:	SINT
ifdef _UNICODE
GetDateFormat  equ <GetDateFormatW>
else
GetDateFormat  equ <GetDateFormatA>
endif
;int
GetNumberFormatA proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD,
	lpValue:	LPSTR,
	lpFormat:	PTR NUMBERFMTA,
	lpNumberStr:	LPSTR,
	cchNumber:	SINT
;int
GetNumberFormatW proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD,
	lpValue:	LPWSTR,
	lpFormat:	PTR NUMBERFMTW,
	lpNumberStr:	LPWSTR,
	cchNumber:	SINT
ifdef _UNICODE
GetNumberFormat equ <GetNumberFormatW>
else
GetNumberFormat equ <GetNumberFormatA>
endif
;int
GetCurrencyFormatA proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD,
	lpValue:	LPSTR,
	lpFormat:	PTR CURRENCYFMTA,
	lpCurrencyStr:	LPSTR,
	cchCurrency:	SINT
;int
GetCurrencyFormatW proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD,
	lpValue:	LPWSTR,
	lpFormat:	PTR CURRENCYFMTW,
	lpCurrencyStr:	LPWSTR,
	cchCurrency:	SINT
ifdef _UNICODE
GetCurrencyFormat equ <GetCurrencyFormatW>
else
GetCurrencyFormat equ <GetCurrencyFormatA>
endif
;BOOL
EnumCalendarInfoA proto WINAPI \
	lpCalInfoEnumProc:	CALINFO_ENUMPROCA,
	Locale:			LCID,
	Calendar:		CALID,
	CalType:		CALTYPE
;BOOL
EnumCalendarInfoW proto WINAPI \
	lpCalInfoEnumProc:	CALINFO_ENUMPROCW,
	Locale:			LCID,
	Calendar:		CALID,
	CalType:		CALTYPE
ifdef _UNICODE
EnumCalendarInfo equ <EnumCalendarInfoW>
else
EnumCalendarInfo equ <EnumCalendarInfoA>
endif

;if(WINVER >= equ 0x0500)
;BOOL
EnumCalendarInfoExA proto WINAPI \
	lpCalInfoEnumProcEx:	CALINFO_ENUMPROCEXA,
	Locale:			LCID,
	Calendar:		CALID,
	CalType:		CALTYPE
;BOOL
EnumCalendarInfoExW proto WINAPI \
	lpCalInfoEnumProcEx:	CALINFO_ENUMPROCEXW,
	Locale:			LCID,
	Calendar:		CALID,
	CalType:		CALTYPE
ifdef _UNICODE
EnumCalendarInfoEx equ <EnumCalendarInfoExW>
else
EnumCalendarInfoEx equ <EnumCalendarInfoExA>
endif
;endif /* WINVER >= equ 0x0500 */
;BOOL
EnumTimeFormatsA proto WINAPI \
	lpTimeFmtEnumProc:	TIMEFMT_ENUMPROCA,
	Locale:			LCID,
	dwFlags:		DWORD
;BOOL
EnumTimeFormatsW proto WINAPI \
	lpTimeFmtEnumProc:	TIMEFMT_ENUMPROCW,
	Locale:			LCID,
	dwFlags:		DWORD
ifdef _UNICODE
EnumTimeFormats equ <EnumTimeFormatsW>
else
EnumTimeFormats equ <EnumTimeFormatsA>
endif
;BOOL
EnumDateFormatsA proto WINAPI \
	lpDateFmtEnumProc:	DATEFMT_ENUMPROCA,
	Locale:			LCID,
	dwFlags:		DWORD
;BOOL
EnumDateFormatsW proto WINAPI \
	lpDateFmtEnumProc:	DATEFMT_ENUMPROCW,
	Locale:			LCID,
	dwFlags:		DWORD
ifdef _UNICODE
EnumDateFormats equ <EnumDateFormatsW>
else
EnumDateFormats equ <EnumDateFormatsA>
endif

;if(WINVER >= equ 0x0500)
;BOOL
EnumDateFormatsExA proto WINAPI \
	lpDateFmtEnumProcEx:	DATEFMT_ENUMPROCEXA,
	Locale:			LCID,
	dwFlags:		DWORD
;BOOL
EnumDateFormatsExW proto WINAPI \
	lpDateFmtEnumProcEx:	DATEFMT_ENUMPROCEXW,
	Locale:			LCID,
	dwFlags:		DWORD
ifdef _UNICODE
EnumDateFormatsEx equ <EnumDateFormatsExW>
else
EnumDateFormatsEx equ <EnumDateFormatsExA>
endif
;endif /* WINVER >= equ 0x0500 */
;BOOL
IsValidLocale proto WINAPI \
	Locale:		LCID,
	dwFlags:	DWORD
;LCID
ConvertDefaultLocale proto WINAPI \
	Locale:		LCID
;LCID
GetThreadLocale proto WINAPI
;BOOL
SetThreadLocale proto WINAPI \
	Locale:		LCID
;LANGID
GetSystemDefaultLangID proto WINAPI
;LANGID
GetUserDefaultLangID proto WINAPI
;LCID
GetSystemDefaultLCID proto WINAPI
;LCID
GetUserDefaultLCID proto WINAPI


;BOOL
GetStringTypeExA proto WINAPI \
	Locale:		LCID,
	dwInfoType:	DWORD,
	lpSrcStr:	LPSTR,
	cchSrc:		SINT,
	lpCharType:	LPWORD
GetStringTypeExW proto WINAPI \
	Locale:		LCID,
	dwInfoType:	DWORD,
	lpSrcStr:	LPWSTR,
	cchSrc:		SINT,
	lpCharType:	LPWORD
ifdef _UNICODE
GetStringTypeEx equ <GetStringTypeExW>
else
GetStringTypeEx equ <GetStringTypeExA>
endif

;BOOL
GetStringTypeA proto WINAPI \
	Locale:		LCID,	; LCID - locale identifer
	dwInfoType:	DWORD,	; information-type options
	lpSrcStr:	LPCSTR, ; pointer to the source string
	cchSrc:		SINT,	; size, in bytes, of the source string
	lpCharType:	LPWORD	; pointer to the buffer for output

GetStringTypeW proto WINAPI \
	dwInfoType:	DWORD,	; information-type options
	lpSrcStr:	LPCWSTR,; pointer to the source string
	cchSrc:		SINT,	; size, in bytes, of the source string
	lpCharType:	LPWORD	; pointer to the buffer for output
;int
FoldStringA proto WINAPI \
	dwMapFlags:	DWORD,
	lpSrcStr:	LPSTR,
	cchSrc:		SINT,
	lpDestStr:	LPSTR,
	cchDest:	SINT
;int
FoldStringW proto WINAPI \
	dwMapFlags:	DWORD,
	lpSrcStr:	LPWSTR,
	cchSrc:		SINT,
	lpDestStr:	LPWSTR,
	cchDest:	SINT
ifdef _UNICODE
FoldString equ <FoldStringW>
else
FoldString equ <FoldStringA>
endif
;BOOL
EnumSystemLocalesA proto WINAPI \
	lpLocaleEnumProc:	LOCALE_ENUMPROCA,
	dwFlags:		DWORD
;BOOL
EnumSystemLocalesW proto WINAPI \
	lpLocaleEnumProc:	LOCALE_ENUMPROCW,
	dwFlags:		DWORD
ifdef _UNICODE
EnumSystemLocales equ <EnumSystemLocalesW>
else
EnumSystemLocales equ <EnumSystemLocalesA>
endif
;BOOL
EnumSystemCodePagesA proto WINAPI \
	lpCodePageEnumProc:	CODEPAGE_ENUMPROCA,
	dwFlags:		DWORD
;BOOL
EnumSystemCodePagesW proto WINAPI \
	lpCodePageEnumProc:	CODEPAGE_ENUMPROCW,
	dwFlags:		DWORD
ifdef _UNICODE
EnumSystemCodePages equ <EnumSystemCodePagesW>
else
EnumSystemCodePages equ <EnumSystemCodePagesA>
endif

.list
