ifndef TTTABLES_H_
define TTTABLES_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

TT_Header		STRUC
Table_Version		FT_Fixed ?
Font_Revision		FT_Fixed ?
CheckSum_Adjust		FT_Long ?
Magic_Number		FT_Long ?
Flags			FT_UShort ?
Units_Per_EM		FT_UShort ?
Created			FT_ULong 2 dup(?)
Modified		FT_ULong 2 dup(?)
xMin			FT_Short ?
yMin			FT_Short ?
xMax			FT_Short ?
yMax			FT_Short ?
Mac_Style		FT_UShort ?
Lowest_Rec_PPEM		FT_UShort ?
Font_Direction		FT_Short ?
Index_To_Loc_Format	FT_Short ?
Glyph_Data_Format	FT_Short ?
TT_Header		ENDS


TT_HoriHeader		STRUC
Version			FT_Fixed ?
Ascender		FT_Short ?
Descender		FT_Short ?
Line_Gap		FT_Short ?
advance_Width_Max	FT_UShort ?
min_Left_Side_Bearing	FT_Short ?
min_Right_Side_Bearing	FT_Short ?
xMax_Extent		FT_Short ?
caret_Slope_Rise	FT_Short ?
caret_Slope_Run		FT_Short ?
caret_Offset		FT_Short ?
Reserved		FT_Short 4 dup(?)
metric_Data_Format	FT_Short ?
number_Of_HMetrics	FT_UShort ?
long_metrics		ptr ?
short_metrics		ptr ?
TT_HoriHeader		ENDS


TT_VertHeader		STRUC
Version			FT_Fixed ?
Ascender		FT_Short ?
Descender		FT_Short ?
Line_Gap		FT_Short ?
advance_Height_Max	FT_UShort ?
min_Top_Side_Bearing	FT_Short ?
min_Bottom_Side_Bearing FT_Short ?
yMax_Extent		FT_Short ?
caret_Slope_Rise	FT_Short ?
caret_Slope_Run		FT_Short ?
caret_Offset		FT_Short ?
Reserved		FT_Short 4 dup(?)
metric_Data_Format	FT_Short ?
number_Of_VMetrics	FT_UShort ?
long_metrics		ptr ?
short_metrics		ptr ?
TT_VertHeader		ENDS

TT_OS2			STRUC
version			FT_UShort ?
xAvgCharWidth		FT_Short ?
usWeightClass		FT_UShort ?
usWidthClass		FT_UShort ?
fsType			FT_UShort ?
ySubscriptXSize		FT_Short ?
ySubscriptYSize		FT_Short ?
ySubscriptXOffset	FT_Short ?
ySubscriptYOffset	FT_Short ?
ySuperscriptXSize	FT_Short ?
ySuperscriptYSize	FT_Short ?
ySuperscriptXOffset	FT_Short ?
ySuperscriptYOffset	FT_Short ?
yStrikeoutSize		FT_Short ?
yStrikeoutPosition	FT_Short ?
sFamilyClass		FT_Short ?
panose			FT_Byte 10 dup(?)
ulUnicodeRange1		FT_ULong ?
ulUnicodeRange2		FT_ULong ?
ulUnicodeRange3		FT_ULong ?
ulUnicodeRange4		FT_ULong ?
achVendID		FT_Char 4 dup(?)
fsSelection		FT_UShort ?
usFirstCharIndex	FT_UShort ?
usLastCharIndex		FT_UShort ?
sTypoAscender		FT_Short ?
sTypoDescender		FT_Short ?
sTypoLineGap		FT_Short ?
usWinAscent		FT_UShort ?
usWinDescent		FT_UShort ?
ulCodePageRange1	FT_ULong ?
ulCodePageRange2	FT_ULong ?
sxHeight		FT_Short ?
sCapHeight		FT_Short ?
usDefaultChar		FT_UShort ?
usBreakChar		FT_UShort ?
usMaxContext		FT_UShort ?
usLowerOpticalPointSize FT_UShort ?
usUpperOpticalPointSize FT_UShort ?
TT_OS2			ENDS

TT_Postscript		STRUC
FormatType		FT_Fixed ?
italicAngle		FT_Fixed ?
underlinePosition	FT_Short ?
underlineThickness	FT_Short ?
isFixedPitch		FT_ULong ?
minMemType42		FT_ULong ?
maxMemType42		FT_ULong ?
minMemType1		FT_ULong ?
maxMemType1		FT_ULong ?
TT_Postscript		ENDS

TT_PCLT			STRUC
Version			FT_Fixed ?
FontNumber		FT_ULong ?
Pitch			FT_UShort ?
xHeight			FT_UShort ?
Style			FT_UShort ?
TypeFamily		FT_UShort ?
CapHeight		FT_UShort ?
SymbolSet		FT_UShort ?
TypeFace		FT_Char 16 dup(?)
CharacterComplement	FT_Char 8 dup(?)
FileName		FT_Char 6 dup(?)
StrokeWeight		FT_Char ?
WidthType		FT_Char ?
SerifStyle		FT_Byte ?
Reserved		FT_Byte ?
TT_PCLT			ENDS

TT_MaxProfile		STRUC
version			FT_Fixed ?
numGlyphs		FT_UShort ?
maxPoints		FT_UShort ?
maxContours		FT_UShort ?
maxCompositePoints	FT_UShort ?
maxCompositeContours	FT_UShort ?
maxZones		FT_UShort ?
maxTwilightPoints	FT_UShort ?
maxStorage		FT_UShort ?
maxFunctionDefs		FT_UShort ?
maxInstructionDefs	FT_UShort ?
maxStackElements	FT_UShort ?
maxSizeOfInstructions	FT_UShort ?
maxComponentElements	FT_UShort ?
maxComponentDepth	FT_UShort ?
TT_MaxProfile		ENDS

.enum FT_Sfnt_Tag {
    FT_SFNT_HEAD,
    FT_SFNT_MAXP,
    FT_SFNT_OS2,
    FT_SFNT_HHEA,
    FT_SFNT_VHEA,
    FT_SFNT_POST,
    FT_SFNT_PCLT,
    FT_SFNT_MAX
    }

define ft_sfnt_head  FT_SFNT_HEAD
define ft_sfnt_maxp  FT_SFNT_MAXP
define ft_sfnt_os2   FT_SFNT_OS2
define ft_sfnt_hhea  FT_SFNT_HHEA
define ft_sfnt_vhea  FT_SFNT_VHEA
define ft_sfnt_post  FT_SFNT_POST
define ft_sfnt_pclt  FT_SFNT_PCLT

FT_Get_Sfnt_Table proto :FT_Face, :FT_Sfnt_Tag
FT_Load_Sfnt_Table proto :FT_Face, :FT_ULong, :FT_Long, :ptr, :ptr
FT_Sfnt_Table_Info proto :FT_Face, :FT_UInt, :ptr, :ptr
FT_Get_CMap_Language_ID proto :FT_CharMap
FT_Get_CMap_Format proto :FT_CharMap

endif
