ifndef FTBDF_H_
define FTBDF_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

.enum BDF_PropertyType {
    BDF_PROPERTY_TYPE_NONE     = 0,
    BDF_PROPERTY_TYPE_ATOM     = 1,
    BDF_PROPERTY_TYPE_INTEGER  = 2,
    BDF_PROPERTY_TYPE_CARDINAL = 3
    }

BDF_PropertyRec		STRUC
type			BDF_PropertyType ?
UNION u
atom			ptr char_t ?
integer			FT_Int32 ?
cardinal		FT_UInt32 ?
ENDS
BDF_PropertyRec		ENDS
BDF_Property		typedef ptr BDF_PropertyRec

FT_Get_BDF_Charset_ID proto \
		  face: FT_Face,
     acharset_encoding: ptr char_t,
     acharset_registry: ptr char_t

FT_Get_BDF_Property proto \
		  face: FT_Face,
	     prop_name: ptr char_t,
	     aproperty: ptr BDF_PropertyRec

endif
