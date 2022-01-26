ifndef __usp10__
define __usp10__

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include windows.inc
include specstrings.inc

define SCRIPT_UNDEFINED	 0

define USP_E_SCRIPT_NOT_IN_FONT MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x200)

.pragma comment(lib, usp10)

SCRIPT_CACHE typedef ptr

ScriptFreeCache proto WINAPI :ptr SCRIPT_CACHE

SCRIPT_CONTROL		STRUC
RECORD
uDefaultLanguage	dd :16 ?
fContextDigits		dd : 1 ?
fInvertPreBoundDir	dd : 1 ?
fInvertPostBoundDir	dd : 1 ?
fLinkStringBefore	dd : 1 ?
fLinkStringAfter	dd : 1 ?
fNeutralOverride	dd : 1 ?
fNumericOverride	dd : 1 ?
fLegacyBidiClass	dd : 1 ?
fMergeNeutralItems	dd : 1 ?
fUseStandardBidi	dd : 1 ?
fReserved		dd : 6 ?
ENDS
SCRIPT_CONTROL		ENDS

SCRIPT_STATE		STRUC
RECORD
uBidiLevel		dw : 5 ?
fOverrideDirection	dw : 1 ?
fInhibitSymSwap		dw : 1 ?
fCharShape		dw : 1 ?
fDigitSubstitute	dw : 1 ?
fInhibitLigate		dw : 1 ?
fDisplayZWG		dw : 1 ?
fArabicNumContext	dw : 1 ?
fGcpClusters		dw : 1 ?
fReserved		dw : 1 ?
fEngineReserved		dw : 2 ?
ENDS
SCRIPT_STATE		ENDS

SCRIPT_ANALYSIS		STRUC
RECORD
eScript			dw :10 ?
fRTL			dw : 1 ?
fLayoutRTL		dw : 1 ?
fLinkBefore		dw : 1 ?
fLinkAfter		dw : 1 ?
fLogicalOrder		dw : 1 ?
fNoGlyphIndex		dw : 1 ?
ENDS
s			SCRIPT_STATE <>
SCRIPT_ANALYSIS		ENDS

SCRIPT_ITEM		STRUC
iCharPos		SINT ?
a			SCRIPT_ANALYSIS <>
SCRIPT_ITEM		ENDS


ScriptItemize proto WINAPI \
	    pwcInChars: ptr WCHAR,
	      cInChars: SINT,
	     cMaxItems: SINT,
	     psControl: ptr SCRIPT_CONTROL,
	       psState: ptr SCRIPT_STATE,
		pItems: ptr SCRIPT_ITEM,
	       pcItems: ptr SINT


ScriptLayout proto WINAPI \
		 cRuns: SINT,
	       pbLevel: ptr BYTE,
     piVisualToLogical: ptr SINT,
     piLogicalToVisual: ptr SINT


.enum SCRIPT_JUSTIFY {
    SCRIPT_JUSTIFY_NONE		  = 0,
    SCRIPT_JUSTIFY_ARABIC_BLANK	  = 1,
    SCRIPT_JUSTIFY_CHARACTER	  = 2,
    SCRIPT_JUSTIFY_RESERVED1	  = 3,
    SCRIPT_JUSTIFY_BLANK	  = 4,
    SCRIPT_JUSTIFY_RESERVED2	  = 5,
    SCRIPT_JUSTIFY_RESERVED3	  = 6,
    SCRIPT_JUSTIFY_ARABIC_NORMAL  = 7,
    SCRIPT_JUSTIFY_ARABIC_KASHIDA = 8,
    SCRIPT_JUSTIFY_ARABIC_ALEF	  = 9,
    SCRIPT_JUSTIFY_ARABIC_HA	  = 10,
    SCRIPT_JUSTIFY_ARABIC_RA	  = 11,
    SCRIPT_JUSTIFY_ARABIC_BA	  = 12,
    SCRIPT_JUSTIFY_ARABIC_BARA	  = 13,
    SCRIPT_JUSTIFY_ARABIC_SEEN	  = 14,
    SCRIPT_JUSTIFY_ARABIC_SEEN_M  = 15,
    }


SCRIPT_VISATTR		STRUC
RECORD
uJustification		dw : 4 ?
fClusterStart		dw : 1 ?
fDiacritic		dw : 1 ?
fZeroWidth		dw : 1 ?
fReserved		dw : 1 ?
fShapeReserved		dw : 8 ?
ENDS
SCRIPT_VISATTR		ENDS


ScriptShape proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
	      pwcChars: ptr WCHAR,
		cChars: SINT,
	    cMaxGlyphs: SINT,
		   psa: ptr SCRIPT_ANALYSIS,
	   pwOutGlyphs: ptr WORD,
	    pwLogClust: ptr WORD,
		  psva: ptr SCRIPT_VISATTR,
	      pcGlyphs: ptr SINT

ifndef LSDEFS_DEFINED
GOFFSET			STRUC
du			LONG ?
dv			LONG ?
GOFFSET			ENDS
endif


ScriptPlace proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
	      pwGlyphs: ptr WORD,
	       cGlyphs: SINT,
		  psva: ptr SCRIPT_VISATTR,
		   psa: ptr SCRIPT_ANALYSIS,
	     piAdvance: ptr SINT,
	      pGoffset: ptr GOFFSET,
		  pABC: ptr ABC

ScriptTextOut proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		     x: SINT,
		     y: SINT,
	     fuOptions: UINT,
		  lprc: ptr RECT,
		   psa: ptr SCRIPT_ANALYSIS,
	   pwcReserved: ptr WCHAR,
	     iReserved: SINT,
	      pwGlyphs: ptr WORD,
	       cGlyphs: SINT,
	     piAdvance: ptr SINT,
	     piJustify: ptr SINT,
	      pGoffset: ptr GOFFSET

ScriptJustify proto WINAPI \
		  psva: ptr SCRIPT_VISATTR,
	     piAdvance: ptr SINT,
	       cGlyphs: SINT,
		   iDx: SINT,
	   iMinKashida: SINT,
	     piJustify: ptr SINT


SCRIPT_LOGATTR		STRUC
RECORD
fSoftBreak		db : 1 ?
fWhiteSpace		db : 1 ?
fCharStop		db : 1 ?
fWordStop		db : 1 ?
fInvalid		db : 1 ?
fReserved		db : 3 ?
ENDS
SCRIPT_LOGATTR		ENDS


ScriptBreak proto WINAPI \
	      pwcChars: ptr WCHAR,
		cChars: SINT,
		   psa: ptr SCRIPT_ANALYSIS,
		  psla: ptr SCRIPT_LOGATTR

ScriptCPtoX proto WINAPI \
		   iCP: SINT,
	     fTrailing: BOOL,
		cChars: SINT,
	       cGlyphs: SINT,
	    pwLogClust: ptr WORD,
		  psva: ptr SCRIPT_VISATTR,
	     piAdvance: ptr SINT,
		   psa: ptr SCRIPT_ANALYSIS,
		   piX: SINT


ScriptXtoCP proto WINAPI \
		    iX: SINT,
		cChars: SINT,
	       cGlyphs: SINT,
	    pwLogClust: ptr WORD,
		  psva: ptr SCRIPT_VISATTR,
	     piAdvance: ptr SINT,
		   psa: ptr SCRIPT_ANALYSIS,
		  piCP: ptr SINT,
	    piTrailing: ptr SINT


ScriptGetLogicalWidths proto WINAPI \
		   psa: ptr SCRIPT_ANALYSIS,
		cChars: SINT,
	       cGlyphs: SINT,
	  piGlyphWidth: ptr SINT,
	    pwLogClust: ptr WORD,
		  psva: ptr SCRIPT_VISATTR,
		  piDx: ptr SINT


ScriptApplyLogicalWidth proto WINAPI \
		  piDx: ptr SINT,
		cChars: SINT,
	       cGlyphs: SINT,
	    pwLogClust: ptr WORD,
		  psva: ptr SCRIPT_VISATTR,
	     piAdvance: ptr SINT,
		   psa: ptr SCRIPT_ANALYSIS,
		  pABC: ptr ABC,
	     piJustify: ptr SINT


define SGCM_RTL	 0x00000001

ScriptGetCMap proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
	    pwcInChars: ptr WCHAR,
		cChars: SINT,
	       dwFlags: DWORD,
	   pwOutGlyphs: ptr WORD

ScriptGetGlyphABCWidth proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		wGlyph: WORD,
		  pABC: ptr ABC


SCRIPT_PROPERTIES	STRUC
RECORD
langid			dd :16 ?
fNumeric		dd : 1 ?
fComplex		dd : 1 ?
fNeedsWordBreaking	dd : 1 ?
fNeedsCaretInfo		dd : 1 ?
bCharSet		dd : 8 ?
fControl		dd : 1 ?
fPrivateUseArea		dd : 1 ?
fNeedsCharacterJustify	dd : 1 ?
fInvalidGlyph		dd : 1 ?
fInvalidLogAttr		dd : 1 ?
fCDM			dd : 1 ?
fAmbiguousCharSet	dd : 1 ?
fClusterSizeVaries	dd : 1 ?
fRejectInvalid		dd : 1 ?
ENDS
SCRIPT_PROPERTIES	ENDS

ScriptGetProperties proto WINAPI \
		  ppSp: ptr ptr SCRIPT_PROPERTIES,
	  piNumScripts: ptr SINT

SCRIPT_FONTPROPERTIES	STRUC
cBytes			SINT ?
wgBlank			dw ?
wgDefault		dw ?
wgInvalid		dw ?
wgKashida		dw ?
iKashidaWidth		SINT ?
SCRIPT_FONTPROPERTIES	ENDS


ScriptGetFontProperties proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   sfp: ptr SCRIPT_FONTPROPERTIES


ScriptCacheGetHeight proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
	      tmHeight: ptr LONG

define SSA_PASSWORD	    0x00000001
define SSA_TAB		    0x00000002
define SSA_CLIP		    0x00000004
define SSA_FIT		    0x00000008
define SSA_DZWG		    0x00000010
define SSA_FALLBACK	    0x00000020
define SSA_BREAK	    0x00000040
define SSA_GLYPHS	    0x00000080
define SSA_RTL		    0x00000100
define SSA_GCP		    0x00000200
define SSA_HOTKEY	    0x00000400
define SSA_METAFILE	    0x00000800
define SSA_LINK		    0x00001000
define SSA_HIDEHOTKEY	    0x00002000
define SSA_HOTKEYONLY	    0x00002400

define SSA_FULLMEASURE	    0x04000000
define SSA_LPKANSIFALLBACK  0x08000000
define SSA_PIDX		    0x10000000
define SSA_LAYOUTRTL	    0x20000000
define SSA_DONTGLYPH	    0x40000000
define SSA_NOKASHIDA	    0x80000000


SCRIPT_TABDEF		STRUC
cTabStops		SINT ?
iScale			SINT ?
pTabStops		LPINT ?
iTabOrigin		SINT ?
SCRIPT_TABDEF		ENDS

SCRIPT_STRING_ANALYSIS	typedef ptr

ScriptStringAnalyse proto WINAPI \
		   hdc: HDC,
	       pString: ptr,
	       cString: SINT,
	       cGlyphs: SINT,
	      iCharset: SINT,
	       dwFlags: DWORD,
	     iReqWidth: SINT,
	     psControl: ptr SCRIPT_CONTROL,
	       psState: ptr SCRIPT_STATE,
		  piDx: ptr SINT,
	       pTabdef: ptr SCRIPT_TABDEF,
	     pbInClass: LPBYTE,
		  pssa: ptr SCRIPT_STRING_ANALYSIS



ScriptStringFree proto WINAPI \
		  pssa: ptr SCRIPT_STRING_ANALYSIS


ScriptString_pSize proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS


ScriptString_pcOutChars proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS


ScriptString_pLogAttr proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS


ScriptStringGetOrder proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS,
	       puOrder: LPUINT

ScriptStringCPtoX proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS,
		   icp: SINT,
	     fTrailing: BOOL,
		    pX: ptr SINT


ScriptStringXtoCP proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS,
		    iX: SINT,
		  piCh: ptr SINT,
	    piTrailing: ptr SINT


ScriptStringGetLogicalWidths proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS,
		  piDx: ptr SINT


ScriptStringValidate proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS

ScriptStringOut proto WINAPI \
		   ssa: SCRIPT_STRING_ANALYSIS,
		    iX: SINT,
		    iY: SINT,
	      uOptions: UINT,
		   prc: ptr RECT,
	       iMinSel: SINT,
	       iMaxSel: SINT,
	     fDisabled: BOOL


define SIC_COMPLEX     1
define SIC_ASCIIDIGIT  2
define SIC_NEUTRAL     4


ScriptIsComplex proto WINAPI \
	    pwcInChars: ptr WCHAR,
	      cInChars: SINT,
	       dwFlags: DWORD

SCRIPT_DIGITSUBSTITUTE	STRUC
NationalDigitLanguage	dw ?  ; :16 ?
TraditionalDigitLanguage dw ? ; :16 ?
DigitSubstitute		db ?  ; :8 ?
dwReserved		dd ?
SCRIPT_DIGITSUBSTITUTE	ENDS


ScriptRecordDigitSubstitution proto WINAPI \
		Locale: LCID,
		  psds: ptr SCRIPT_DIGITSUBSTITUTE


define SCRIPT_DIGITSUBSTITUTE_CONTEXT	   0
define SCRIPT_DIGITSUBSTITUTE_NONE	   1
define SCRIPT_DIGITSUBSTITUTE_NATIONAL	   2
define SCRIPT_DIGITSUBSTITUTE_TRADITIONAL  3


ScriptApplyDigitSubstitution proto WINAPI \
		  psds: ptr SCRIPT_DIGITSUBSTITUTE,
		   psc: ptr SCRIPT_CONTROL,
		   pss: ptr SCRIPT_STATE


ifndef UNISCRIBE_OPENTYPE
if (_WIN32_WINNT GE 0x0600)
define UNISCRIBE_OPENTYPE 0x0100
endif
endif

if (UNISCRIBE_OPENTYPE GE 0x0100)

OPENTYPE_TAG typedef ULONG

define SCRIPT_TAG_UNKNOWN   0x00000000

OPENTYPE_FEATURE_RECORD STRUC
tagFeature		OPENTYPE_TAG ?
lParameter		LONG ?
OPENTYPE_FEATURE_RECORD ENDS

TEXTRANGE_PROPERTIES	STRUC
potfRecords		ptr OPENTYPE_FEATURE_RECORD ?
cotfRecords		SINT ?
TEXTRANGE_PROPERTIES	ENDS

SCRIPT_CHARPROP		STRUC
RECORD
fCanGlyphAlone		dw :  1 ?
reserved		dw : 15 ?
ENDS
SCRIPT_CHARPROP		ENDS

SCRIPT_GLYPHPROP	STRUC
sva			SCRIPT_VISATTR <>
reserved		dw ?
SCRIPT_GLYPHPROP	ENDS

ScriptShapeOpenType proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	     tagScript: OPENTYPE_TAG,
	    tagLangSys: OPENTYPE_TAG,
	  rcRangeChars: ptr SINT,
     rpRangeProperties: ptr ptr TEXTRANGE_PROPERTIES,
	       cRanges: SINT,
	      pwcChars: ptr WCHAR,
		cChars: SINT,
	    cMaxGlyphs: SINT,
	    pwLogClust: ptr WORD,
	    pCharProps: ptr SCRIPT_CHARPROP,
	   pwOutGlyphs: ptr WORD,
	pOutGlyphProps: ptr SCRIPT_GLYPHPROP,
	      pcGlyphs: ptr SINT

ScriptPlaceOpenType proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	     tagScript: OPENTYPE_TAG,
	    tagLangSys: OPENTYPE_TAG,
	  rcRangeChars: ptr SINT,
     rpRangeProperties: ptr ptr TEXTRANGE_PROPERTIES,
	       cRanges: SINT,
	      pwcChars: ptr WCHAR,
	    pwLogClust: ptr WORD,
	    pCharProps: ptr SCRIPT_CHARPROP,
		cChars: SINT,
	      pwGlyphs: ptr WORD,
	   pGlyphProps: ptr SCRIPT_GLYPHPROP,
	       cGlyphs: SINT,
	     piAdvance: ptr SINT,
	      pGoffset: ptr GOFFSET,
		  pABC: ptr ABC

ScriptItemizeOpenType proto WINAPI \
	    pwcInChars: ptr WCHAR,
	      cInChars: SINT,
	     cMaxItems: SINT,
	     psControl: ptr SCRIPT_CONTROL,
	       psState: ptr SCRIPT_STATE,
		pItems: ptr SCRIPT_ITEM,
	   pScriptTags: ptr OPENTYPE_TAG,
	       pcItems: ptr SINT


ScriptGetFontScriptTags proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	      cMaxTags: SINT,
	   pScriptTags: ptr OPENTYPE_TAG,
		pcTags: ptr SINT


ScriptGetFontLanguageTags proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	     tagScript: OPENTYPE_TAG,
	      cMaxTags: SINT,
	  pLangsysTags: ptr OPENTYPE_TAG,
		pcTags: ptr SINT


ScriptGetFontFeatureTags proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	     tagScript: OPENTYPE_TAG,
	    tagLangSys: OPENTYPE_TAG,
	      cMaxTags: SINT,
	  pFeatureTags: ptr OPENTYPE_TAG,
		pcTags: ptr SINT

ScriptGetFontAlternateGlyphs proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	     tagScript: OPENTYPE_TAG,
	    tagLangSys: OPENTYPE_TAG,
	    tagFeature: OPENTYPE_TAG,
	      wGlyphId: WORD,
	cMaxAlternates: SINT,
      pAlternateGlyphs: ptr WORD,
	  pcAlternates: ptr SINT


ScriptSubstituteSingleGlyph proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	     tagScript: OPENTYPE_TAG,
	    tagLangSys: OPENTYPE_TAG,
	    tagFeature: OPENTYPE_TAG,
	    lParameter: LONG,
	      wGlyphId: WORD,
	  pwOutGlyphId: ptr WORD


ScriptPositionSingleGlyph proto WINAPI \
		   hdc: HDC,
		   psc: ptr SCRIPT_CACHE,
		   psa: ptr SCRIPT_ANALYSIS,
	     tagScript: OPENTYPE_TAG,
	    tagLangSys: OPENTYPE_TAG,
	    tagFeature: OPENTYPE_TAG,
	    lParameter: LONG,
	      wGlyphId: WORD,
	      iAdvance: SINT,
	       GOffset: GOFFSET,
	  piOutAdvance: ptr SINT,
	   pOutGoffset: ptr GOFFSET

endif
endif
endif
