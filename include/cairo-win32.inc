ifndef _CAIRO_WIN32_H_
define _CAIRO_WIN32_H_

include cairo.inc

if CAIRO_HAS_WIN32_SURFACE

include windows.inc

cairo_win32_surface_create proto :HDC
cairo_win32_surface_create_with_format proto :HDC, :cairo_format_t
cairo_win32_printing_surface_create proto :HDC
cairo_win32_surface_create_with_ddb proto :HDC, :cairo_format_t, :SINT, :SINT
cairo_win32_surface_create_with_dib proto :cairo_format_t, :SINT, :SINT
cairo_win32_surface_get_dc proto :ptr cairo_surface_t
cairo_win32_surface_get_image proto :ptr cairo_surface_t

if CAIRO_HAS_WIN32_FONT

cairo_win32_font_face_create_for_logfontw proto :ptr LOGFONTW
cairo_win32_font_face_create_for_hfont proto :HFONT
cairo_win32_font_face_create_for_logfontw_hfont proto :ptr LOGFONTW, :HFONT
cairo_win32_scaled_font_select_font proto :ptr cairo_scaled_font_t, :HDC
cairo_win32_scaled_font_done_font proto :ptr cairo_scaled_font_t
cairo_win32_scaled_font_get_metrics_factor proto :ptr cairo_scaled_font_t
cairo_win32_scaled_font_get_logical_to_device proto :ptr cairo_scaled_font_t, :ptr cairo_matrix_t
cairo_win32_scaled_font_get_device_to_logical proto :ptr cairo_scaled_font_t, :ptr cairo_matrix_t

endif

else
 .err <Cairo was not compiled with support for the win32 backend>
endif

endif
