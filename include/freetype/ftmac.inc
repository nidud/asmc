ifndef FTMAC_H_
define FTMAC_H_

ifndef FT_DEPRECATED_ATTRIBUTE
if defined( __GNUC__ ) AND ( ( __GNUC__ GE 4 ) OR ( ( __GNUC__ EQ 3 ) AND ( __GNUC_MINOR__ GE 1 ) ) )
define FT_DEPRECATED_ATTRIBUTE <__attribute__(( deprecated ))>
else
define FT_DEPRECATED_ATTRIBUTE
endif
endif

FT_New_Face_From_FOND proto \
               library: FT_Library,
                  fond: Handle,
            face_index: FT_Long,
                 aface: ptr FT_Face

FT_GetFile_From_Mac_Name proto \
              fontName: ptr,
              pathSpec: ptr FSSpec,
            face_index: ptr FT_Long

FT_GetFile_From_Mac_ATS_Name proto \
              fontName: ptr,
              pathSpec: ptr FSSpec,
            face_index: ptr FT_Long

FT_GetFilePath_From_Mac_ATS_Name proto \
              fontName: ptr,
                  path: ptr UInt8,
           maxPathSize: UInt32,
            face_index: ptr FT_Long

FT_New_Face_From_FSSpec proto \
               library: FT_Library,
                  spec: ptr FSSpec,
            face_index: FT_Long,
                 aface: ptr FT_Face

FT_New_Face_From_FSRef proto \
               library: FT_Library,
                   ref: ptr FSRef,
            face_index: FT_Long,
                 aface: ptr FT_Face

endif
