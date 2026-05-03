ifndef FTMAC_H_
define FTMAC_H_

ifndef FT_DEPRECATED_ATTRIBUTE
if defined( __GNUC__ ) AND ( ( __GNUC__ GE 4 ) OR ( ( __GNUC__ EQ 3 ) AND ( __GNUC_MINOR__ GE 1 ) ) )
define FT_DEPRECATED_ATTRIBUTE <__attribute__(( deprecated ))>
else
define FT_DEPRECATED_ATTRIBUTE
endif
endif

FT_New_Face_From_FOND proto :FT_Library, :Handle, :FT_Long, :ptr
FT_GetFile_From_Mac_Name proto  :ptr, :ptr, :ptr
FT_GetFile_From_Mac_ATS_Name proto :ptr, :ptr, :ptr
FT_GetFilePath_From_Mac_ATS_Name proto :ptr, :ptr, :UInt32, :ptr
FT_New_Face_From_FSSpec proto :FT_Library, :ptr, :FT_Long, :ptr
FT_New_Face_From_FSRef proto :FT_Library, :ptr, :FT_Long, :ptr

endif
