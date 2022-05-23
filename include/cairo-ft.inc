
ifndef CAIRO_FT_H
define CAIRO_FT_H

include cairo.inc

if CAIRO_HAS_FT_FONT

include ft2build.inc
%include FT_FREETYPE_H

if CAIRO_HAS_FC_FONT
include fontconfig/fontconfig.inc
endif

cairo_ft_font_face_create_for_ft_face proto :FT_Face, :SINT

.enum cairo_ft_synthesize_t {
    CAIRO_FT_SYNTHESIZE_BOLD = 1 shl 0,
    CAIRO_FT_SYNTHESIZE_OBLIQUE = 1 shl 1
    }

cairo_ft_font_face_set_synthesize proto :ptr, :uint_t
cairo_ft_font_face_unset_synthesize proto :ptr cairo_font_face_t, :uint_t
cairo_ft_font_face_get_synthesize proto :ptr cairo_font_face_t
cairo_ft_scaled_font_lock_face proto :ptr cairo_scaled_font_t
cairo_ft_scaled_font_unlock_face proto :ptr cairo_scaled_font_t

if CAIRO_HAS_FC_FONT

cairo_ft_font_face_create_for_pattern proto :ptr FcPattern
cairo_ft_font_options_substitute proto :ptr cairo_font_options_t, :ptr FcPattern

endif

else
 .err <Cairo was not compiled with support for the freetype font backend>
endif

endif
