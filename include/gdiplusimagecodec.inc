ifndef _GDIPLUSIMAGECODEC_H
define _GDIPLUSIMAGECODEC_H
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Codec Management APIs
;;--------------------------------------------------------------------------

GetImageDecodersSize proto fastcall :abs, :abs {
    GdipGetImageDecodersSize(_1, _2)
    }

GetImageDecoders proto fastcall :abs, :abs, :abs {
    GdipGetImageDecoders(_1, _2, _3)
    }

GetImageEncodersSize proto fastcall :abs, :abs {
    GdipGetImageEncodersSize(_1, _2)
    }

GetImageEncoders proto fastcall :abs, :abs, :abs {
    GdipGetImageEncoders(_1, _2, _3)
    }

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif  ;; _GDIPLUSIMAGECODEC_H
