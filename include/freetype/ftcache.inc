ifndef FTCACHE_H_
define FTCACHE_H_

include freetype/ftglyph.inc

FTC_FaceID		typedef FT_Pointer

CALLBACKC(FTC_Face_Requester, :FTC_FaceID, :FT_Library, :FT_Pointer, :ptr FT_Face)

FTC_Manager		typedef ptr FTC_ManagerRec
FTC_Node		typedef ptr FTC_NodeRec

FTC_Manager_New proto :FT_Library, :FT_UInt, :FT_UInt, :FT_ULong, :FTC_Face_Requester, :FT_Pointer, :ptr
FTC_Manager_Reset proto :FTC_Manager
FTC_Manager_Done proto :FTC_Manager
FTC_Manager_LookupFace proto :FTC_Manager, :FTC_FaceID, :ptr

FTC_ScalerRec		STRUC
face_id			FTC_FaceID ?
width			FT_UInt ?
height			FT_UInt ?
pixel			FT_Int ?
x_res			FT_UInt ?
y_res			FT_UInt ?
FTC_ScalerRec		ENDS
FTC_Scaler		typedef ptr FTC_ScalerRec

FTC_Manager_LookupSize proto :FTC_Manager, :FTC_Scaler, :ptr
FTC_Node_Unref proto :FTC_Node, :FTC_Manager
FTC_Manager_RemoveFaceID proto :FTC_Manager, :FTC_FaceID

FTC_CMapCache		typedef ptr FTC_CMapCacheRec

FTC_CMapCache_New proto :FTC_Manager, :ptr
FTC_CMapCache_Lookup proto :FTC_CMapCache, :FTC_FaceID, :FT_Int, :FT_UInt32

FTC_ImageTypeRec	STRUC
face_id			FTC_FaceID ?
width			FT_UInt ?
height			FT_UInt ?
flags			FT_Int32 ?
FTC_ImageTypeRec	ENDS
FTC_ImageType		typedef ptr FTC_ImageTypeRec

FTC_IMAGE_TYPE_COMPARE macro d1, d2
	exitm<.err>
	endm

FTC_ImageCache		typedef ptr FTC_ImageCacheRec

FTC_ImageCache_New proto :FTC_Manager, :ptr
FTC_ImageCache_Lookup proto :FTC_ImageCache, :FTC_ImageType, :FT_UInt, :ptr, :ptr
FTC_ImageCache_LookupScaler proto :FTC_ImageCache, :FTC_Scaler, :FT_ULong, :FT_UInt, :ptr, :ptr

FTC_SBitRec		STRUC
width			FT_Byte ?
height			FT_Byte ?
left			FT_Char ?
top			FT_Char ?
format			FT_Byte ?
max_grays		FT_Byte ?
pitch			FT_Short ?
xadvance		FT_Char ?
yadvance		FT_Char ?
buffer			ptr FT_Byte ?
FTC_SBitRec		ENDS
FTC_SBit		typedef ptr FTC_SBitRec

FTC_SBitCache		typedef ptr FTC_SBitCacheRec

FTC_SBitCache_New proto :FTC_Manager, :ptr
FTC_SBitCache_Lookup proto :FTC_SBitCache, :FTC_ImageType, :FT_UInt, :ptr, :ptr
FTC_SBitCache_LookupScaler proto :FTC_SBitCache, :FTC_Scaler, :FT_ULong, :FT_UInt, :ptr, :ptr

endif
