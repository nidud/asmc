ifndef _GDIPLUSIMAGECODEC_H
_GDIPLUSIMAGECODEC_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Codec Management APIs
;;--------------------------------------------------------------------------

GetImageDecodersSize proto :ptr UINT, :ptr UINT {

    GdipGetImageDecodersSize(_1, _2)
}

GetImageDecoders proto :UINT, :UINT, :ptr ImageCodecInfo {

    GdipGetImageDecoders(_1, _2, _3)
}

GetImageEncodersSize proto :ptr UINT, :ptr UINT {

    GdipGetImageEncodersSize(_1, _2)
}

GetImageEncoders proto :UINT, :UINT, :ptr ImageCodecInfo {

    GdipGetImageEncoders(_1, _2, _3)
}

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif  ;; _GDIPLUSIMAGECODEC_H
