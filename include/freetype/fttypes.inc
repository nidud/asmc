ifndef FTTYPES_H_
define FTTYPES_H_

include ft2build.inc
%include FT_CONFIG_CONFIG_H
include freetype/ftsystem.inc
include freetype/ftimage.inc

include stddef.inc


FT_BEGIN_HEADER

FT_Bool			typedef byte
FT_FWord		typedef sword
FT_UFWord		typedef word
FT_Char			typedef sbyte
FT_Byte			typedef byte
FT_Bytes		typedef ptr FT_Byte
FT_Tag			typedef FT_UInt32
FT_String		typedef sbyte
FT_Short		typedef sword
FT_UShort		typedef word
FT_Int			typedef sdword
FT_UInt			typedef dword
FT_Long			typedef sdword
FT_ULong		typedef dword
FT_F2Dot14		typedef sword
FT_F26Dot6		typedef sdword
FT_Fixed		typedef sdword
FT_Error		typedef sdword
FT_Pointer		typedef ptr
FT_Offset		typedef size_t
FT_PtrDist		typedef ft_ptrdiff_t
FT_UnitVector		STRUC
x			FT_F2Dot14 ?
y			FT_F2Dot14 ?
FT_UnitVector		ENDS

FT_Matrix		STRUC
xx			FT_Fixed ?
xy			FT_Fixed ?
yx			FT_Fixed ?
yy			FT_Fixed ?
FT_Matrix		ENDS

FT_Data			STRUC
pointer			ptr FT_Byte ?
length			FT_UInt ?
FT_Data			ENDS


CALLBACKC(FT_Generic_Finalizer, :ptr)

FT_Generic		STRUC
data			ptr ?
finalizer		FT_Generic_Finalizer ?
FT_Generic		ENDS

FT_MAKE_TAG macro _x1, _x2, _x3, _x4
	exitm<.err>
	endm

FT_ListNode		typedef ptr FT_ListNodeRec_
FT_List			typedef ptr FT_ListRec_


FT_ListNodeRec		STRUC
prev			FT_ListNode ?
next			FT_ListNode ?
data			ptr ?
FT_ListNodeRec		ENDS

FT_ListRec		STRUC
head			FT_ListNode ?
tail			FT_ListNode ?
FT_ListRec		ENDS



FT_IS_EMPTY macro list
	exitm<( list.head EQ 0 )>
	endm
FT_BOOL macro x
	exitm<FT_STATIC_CAST( FT_Bool, (x) NOT = 0 )>
	endm

FT_ERR_XCAT macro x, y
	exitm<&x&&y&>
	endm
FT_ERR_CAT macro x, y
	exitm<FT_ERR_XCAT( x, y )>
	endm


FT_ERR macro e
	exitm<FT_ERR_CAT( FT_ERR_PREFIX, e )>
	endm

FT_ERROR_BASE macro x
	exitm<( (x) AND 0xFF )>
	endm
FT_ERROR_MODULE macro x
	exitm<( (x) AND 0xFF00 )>
	endm

FT_ERR_EQ macro x, e
	exitm<(FT_ERROR_BASE( x ) == FT_ERROR_BASE( FT_ERR( e ) ) )>
	endm
FT_ERR_NEQ macro x, e
	exitm<(FT_ERROR_BASE( x ) != FT_ERROR_BASE( FT_ERR( e ) ) )>
	endm



FT_END_HEADER

endif



