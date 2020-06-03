ifndef _GDIPLUSIMAGECODEC_H
_GDIPLUSIMAGECODEC_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Codec Management APIs
;;--------------------------------------------------------------------------

GetImageDecodersSize proto :ptr UINT, :ptr UINT {

    GdipGetImageDecodersSize(this, _1)
}

GetImageDecoders proto :UINT, :UINT, :ptr ImageCodecInfo {

    GdipGetImageDecoders(this, _1, _2)
}

GetImageEncodersSize proto :ptr UINT, :ptr UINT {

    GdipGetImageEncodersSize(this, _1)
}

GetImageEncoders proto :UINT, :UINT, :ptr ImageCodecInfo {

    GdipGetImageEncoders(this, _1, _2)
}

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif  ;; _GDIPLUSIMAGECODEC_H
