ifndef FTCACHE_H_
define FTCACHE_H_

include freetype/ftglyph.inc

FTC_FaceID		typedef FT_Pointer

CALLBACKC(FTC_Face_Requester, :FTC_FaceID, :FT_Library, :FT_Pointer, :ptr FT_Face)

FTC_Manager		typedef ptr FTC_ManagerRec
FTC_Node		typedef ptr FTC_NodeRec

FTC_Manager_New proto \
	       library: FT_Library,
	     max_faces: FT_UInt,
	     max_sizes: FT_UInt,
	     max_bytes: FT_ULong,
	     requester: FTC_Face_Requester,
	      req_data: FT_Pointer,
	      amanager: ptr FTC_Manager

FTC_Manager_Reset proto \
	       manager: FTC_Manager

FTC_Manager_Done proto \
	       manager: FTC_Manager

FTC_Manager_LookupFace proto \
	       manager: FTC_Manager,
	       face_id: FTC_FaceID,
		 aface: ptr FT_Face

FTC_ScalerRec		STRUC
face_id			FTC_FaceID ?
width			FT_UInt ?
height			FT_UInt ?
pixel			FT_Int ?
x_res			FT_UInt ?
y_res			FT_UInt ?
FTC_ScalerRec		ENDS
FTC_Scaler		typedef ptr FTC_ScalerRec


FTC_Manager_LookupSize proto \
	       manager: FTC_Manager,
		scaler: FTC_Scaler,
		 asize: ptr FT_Size

FTC_Node_Unref proto \
		  node: FTC_Node,
	       manager: FTC_Manager

FTC_Manager_RemoveFaceID proto \
	       manager: FTC_Manager,
	       face_id: FTC_FaceID

FTC_CMapCache		typedef ptr FTC_CMapCacheRec

FTC_CMapCache_New proto \
	       manager: FTC_Manager,
		acache: ptr FTC_CMapCache

FTC_CMapCache_Lookup proto \
		 cache: FTC_CMapCache,
	       face_id: FTC_FaceID,
	    cmap_index: FT_Int,
	     char_code: FT_UInt32


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

FTC_ImageCache_New proto \
	       manager: FTC_Manager,
		acache: ptr FTC_ImageCache

FTC_ImageCache_Lookup proto \
		 cache: FTC_ImageCache,
		  type: FTC_ImageType,
		gindex: FT_UInt,
		aglyph: ptr FT_Glyph,
		 anode: ptr FTC_Node

FTC_ImageCache_LookupScaler proto \
		 cache: FTC_ImageCache,
		scaler: FTC_Scaler,
	    load_flags: FT_ULong,
		gindex: FT_UInt,
		aglyph: ptr FT_Glyph,
		 anode: ptr FTC_Node

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

FTC_SBitCache_New proto \
	       manager: FTC_Manager,
		acache: ptr FTC_SBitCache

FTC_SBitCache_Lookup proto \
		 cache: FTC_SBitCache,
		  type: FTC_ImageType,
		gindex: FT_UInt,
		  sbit: ptr FTC_SBit,
		 anode: ptr FTC_Node

FTC_SBitCache_LookupScaler proto \
		 cache: FTC_SBitCache,
		scaler: FTC_Scaler,
	    load_flags: FT_ULong,
		gindex: FT_UInt,
		  sbit: ptr FTC_SBit,
		 anode: ptr FTC_Node

endif
