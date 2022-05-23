
ifndef CAIRO_H
define CAIRO_H

include libc.inc

double typedef real8

include cairo-version.inc
include cairo-features.inc
include cairo-deprecated.inc

CAIRO_VERSION_ENCODE macro major, minor, micro
%	exitm<@CatStr(%((major)*10000+(minor)*100+(micro)))>
	endm

define CAIRO_VERSION CAIRO_VERSION_ENCODE(CAIRO_VERSION_MAJOR, CAIRO_VERSION_MINOR, CAIRO_VERSION_MICRO)


CAIRO_VERSION_STRINGIZE_ macro major, minor, micro
%	exitm<@CatStr(<!">, %major, <.>, %minor, <.>, %micro, <!">)>
	endm

CAIRO_VERSION_STRINGIZE macro major, minor, micro
	exitm<CAIRO_VERSION_STRINGIZE_(major, minor, micro)>
	endm

define CAIRO_VERSION_STRING CAIRO_VERSION_STRINGIZE(CAIRO_VERSION_MAJOR, CAIRO_VERSION_MINOR, CAIRO_VERSION_MICRO)


cairo_version		proto
cairo_version_string	proto

cairo_bool_t		typedef int_t
cairo_t			typedef byte ; _cairo
cairo_surface_t		typedef byte ; _cairo_surface
cairo_device_t		typedef byte ; _cairo_device

_cairo_matrix		STRUC
xx			double ?
yx			double ?
xy			double ?
yy			double ?
x0			double ?
y0			double ?
_cairo_matrix		ENDS
cairo_matrix_t		typedef _cairo_matrix

;cairo_pattern_t		typedef _cairo_pattern

CALLBACKC(cairo_destroy_func_t, :ptr)

_cairo_user_data_key	STRUC
unused			SINT ?
_cairo_user_data_key	ENDS
cairo_user_data_key_t	typedef _cairo_user_data_key

.enum _cairo_status {
    CAIRO_STATUS_SUCCESS = 0,
    CAIRO_STATUS_NO_MEMORY,
    CAIRO_STATUS_INVALID_RESTORE,
    CAIRO_STATUS_INVALID_POP_GROUP,
    CAIRO_STATUS_NO_CURRENT_POINT,
    CAIRO_STATUS_INVALID_MATRIX,
    CAIRO_STATUS_INVALID_STATUS,
    CAIRO_STATUS_NULL_POINTER,
    CAIRO_STATUS_INVALID_STRING,
    CAIRO_STATUS_INVALID_PATH_DATA,
    CAIRO_STATUS_READ_ERROR,
    CAIRO_STATUS_WRITE_ERROR,
    CAIRO_STATUS_SURFACE_FINISHED,
    CAIRO_STATUS_SURFACE_TYPE_MISMATCH,
    CAIRO_STATUS_PATTERN_TYPE_MISMATCH,
    CAIRO_STATUS_INVALID_CONTENT,
    CAIRO_STATUS_INVALID_FORMAT,
    CAIRO_STATUS_INVALID_VISUAL,
    CAIRO_STATUS_FILE_NOT_FOUND,
    CAIRO_STATUS_INVALID_DASH,
    CAIRO_STATUS_INVALID_DSC_COMMENT,
    CAIRO_STATUS_INVALID_INDEX,
    CAIRO_STATUS_CLIP_NOT_REPRESENTABLE,
    CAIRO_STATUS_TEMP_FILE_ERROR,
    CAIRO_STATUS_INVALID_STRIDE,
    CAIRO_STATUS_FONT_TYPE_MISMATCH,
    CAIRO_STATUS_USER_FONT_IMMUTABLE,
    CAIRO_STATUS_USER_FONT_ERROR,
    CAIRO_STATUS_NEGATIVE_COUNT,
    CAIRO_STATUS_INVALID_CLUSTERS,
    CAIRO_STATUS_INVALID_SLANT,
    CAIRO_STATUS_INVALID_WEIGHT,
    CAIRO_STATUS_INVALID_SIZE,
    CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED,
    CAIRO_STATUS_DEVICE_TYPE_MISMATCH,
    CAIRO_STATUS_DEVICE_ERROR,
    CAIRO_STATUS_INVALID_MESH_CONSTRUCTION,
    CAIRO_STATUS_DEVICE_FINISHED,
    CAIRO_STATUS_JBIG2_GLOBAL_MISSING,
    CAIRO_STATUS_PNG_ERROR,
    CAIRO_STATUS_FREETYPE_ERROR,
    CAIRO_STATUS_WIN32_GDI_ERROR,
    CAIRO_STATUS_TAG_ERROR,
    CAIRO_STATUS_LAST_STATUS
    }
cairo_status_t		typedef _cairo_status

.enum _cairo_content {
    CAIRO_CONTENT_COLOR		= 0x1000,
    CAIRO_CONTENT_ALPHA		= 0x2000,
    CAIRO_CONTENT_COLOR_ALPHA	= 0x3000
    }
cairo_content_t		typedef _cairo_content

.enum _cairo_format {
    CAIRO_FORMAT_INVALID   = -1,
    CAIRO_FORMAT_ARGB32	   = 0,
    CAIRO_FORMAT_RGB24	   = 1,
    CAIRO_FORMAT_A8	   = 2,
    CAIRO_FORMAT_A1	   = 3,
    CAIRO_FORMAT_RGB16_565 = 4,
    CAIRO_FORMAT_RGB30	   = 5
    }
cairo_format_t		typedef _cairo_format


CALLBACKC(cairo_write_func_t, :ptr, :ptr, :int_t)
CALLBACKC(cairo_read_func_t, :ptr, :ptr, :int_t)

_cairo_rectangle_int	STRUC
x			SINT ?
y			SINT ?
width			SINT ?
height			SINT ?
_cairo_rectangle_int	ENDS
cairo_rectangle_int_t	typedef _cairo_rectangle_int

cairo_create		proto :ptr cairo_surface_t
cairo_reference		proto :ptr cairo_t
cairo_destroy		proto :ptr cairo_t
cairo_get_reference_count proto :ptr cairo_t
cairo_get_user_data	proto :ptr cairo_t, :ptr cairo_user_data_key_t
cairo_set_user_data	proto :ptr cairo_t, :ptr cairo_user_data_key_t, :ptr, :ptr cairo_destroy_func_t
cairo_save		proto :ptr cairo_t
cairo_restore		proto :ptr cairo_t
cairo_push_group	proto :ptr cairo_t
cairo_push_group_with_content proto :ptr cairo_t, :cairo_content_t
cairo_pop_group		proto :ptr cairo_t
cairo_pop_group_to_source proto :ptr cairo_t


.enum _cairo_operator {
    CAIRO_OPERATOR_CLEAR,
    CAIRO_OPERATOR_SOURCE,
    CAIRO_OPERATOR_OVER,
    CAIRO_OPERATOR_IN,
    CAIRO_OPERATOR_OUT,
    CAIRO_OPERATOR_ATOP,
    CAIRO_OPERATOR_DEST,
    CAIRO_OPERATOR_DEST_OVER,
    CAIRO_OPERATOR_DEST_IN,
    CAIRO_OPERATOR_DEST_OUT,
    CAIRO_OPERATOR_DEST_ATOP,
    CAIRO_OPERATOR_XOR,
    CAIRO_OPERATOR_ADD,
    CAIRO_OPERATOR_SATURATE,
    CAIRO_OPERATOR_MULTIPLY,
    CAIRO_OPERATOR_SCREEN,
    CAIRO_OPERATOR_OVERLAY,
    CAIRO_OPERATOR_DARKEN,
    CAIRO_OPERATOR_LIGHTEN,
    CAIRO_OPERATOR_COLOR_DODGE,
    CAIRO_OPERATOR_COLOR_BURN,
    CAIRO_OPERATOR_HARD_LIGHT,
    CAIRO_OPERATOR_SOFT_LIGHT,
    CAIRO_OPERATOR_DIFFERENCE,
    CAIRO_OPERATOR_EXCLUSION,
    CAIRO_OPERATOR_HSL_HUE,
    CAIRO_OPERATOR_HSL_SATURATION,
    CAIRO_OPERATOR_HSL_COLOR,
    CAIRO_OPERATOR_HSL_LUMINOSITY
    }

cairo_operator_t	typedef _cairo_operator

cairo_set_operator	proto :ptr cairo_t, :cairo_operator_t
cairo_set_source	proto :ptr cairo_t, :ptr cairo_pattern_t
cairo_set_source_rgb	proto :ptr cairo_t, :double, :double, :double
cairo_set_source_rgba	proto :ptr cairo_t, :double, :double, :double
cairo_set_source_surface proto :ptr cairo_t, :ptr cairo_surface_t, :double, :double
cairo_set_tolerance	proto :ptr cairo_t, :double

.enum _cairo_antialias {
    CAIRO_ANTIALIAS_DEFAULT,
    CAIRO_ANTIALIAS_NONE,
    CAIRO_ANTIALIAS_GRAY,
    CAIRO_ANTIALIAS_SUBPIXEL,
    CAIRO_ANTIALIAS_FAST,
    CAIRO_ANTIALIAS_GOOD,
    CAIRO_ANTIALIAS_BEST
    }

cairo_antialias_t	typedef _cairo_antialias
cairo_set_antialias	proto :ptr cairo_t, :cairo_antialias_t

.enum _cairo_fill_rule {
    CAIRO_FILL_RULE_WINDING,
    CAIRO_FILL_RULE_EVEN_ODD
    }

cairo_fill_rule_t	typedef _cairo_fill_rule
cairo_set_fill_rule	proto :ptr cairo_t, :cairo_fill_rule_t
cairo_set_line_width	proto :ptr cairo_t, :double

.enum _cairo_line_cap {
    CAIRO_LINE_CAP_BUTT,
    CAIRO_LINE_CAP_ROUND,
    CAIRO_LINE_CAP_SQUARE
    }
cairo_line_cap_t	typedef _cairo_line_cap
cairo_set_line_cap	proto :ptr cairo_t, :cairo_line_cap_t

.enum _cairo_line_join {
    CAIRO_LINE_JOIN_MITER,
    CAIRO_LINE_JOIN_ROUND,
    CAIRO_LINE_JOIN_BEVEL
    }
cairo_line_join_t	typedef _cairo_line_join
cairo_set_line_join	proto :ptr cairo_t, :cairo_line_join_t
cairo_set_dash		proto :ptr cairo_t, :ptr double, :SINT, :double
cairo_set_miter_limit	proto :ptr cairo_t, :double
cairo_translate		proto :ptr cairo_t, :double, :double
cairo_scale		proto :ptr cairo_t, :double, :double
cairo_rotate		proto :ptr cairo_t, :double
cairo_transform		proto :ptr cairo_t, :ptr cairo_matrix_t
cairo_set_matrix	proto :ptr cairo_t, :ptr cairo_matrix_t
cairo_identity_matrix	proto :ptr cairo_t
cairo_user_to_device	proto :ptr cairo_t, :ptr double, :ptr double
cairo_user_to_device_distance proto :ptr cairo_t, :ptr double, :ptr double
cairo_device_to_user	proto :ptr cairo_t, :ptr double, :ptr double
cairo_device_to_user_distance proto :ptr cairo_t, :ptr double, :ptr double

cairo_new_path		proto :ptr cairo_t
cairo_move_to		proto :ptr cairo_t, :double, :double
cairo_new_sub_path	proto :ptr cairo_t

cairo_line_to		proto :ptr cairo_t, :double, :double
cairo_curve_to		proto :ptr cairo_t, :double, :double, :double, :double, :double, :double

cairo_arc		proto :ptr cairo_t, :double, :double, :double, :double, :double
cairo_arc_negative	proto :ptr cairo_t, :double, :double, :double, :double, :double

cairo_rel_move_to	proto :ptr cairo_t, :double, :double
cairo_rel_line_to	proto :ptr cairo_t, :double, :double
cairo_rel_curve_to	proto :ptr cairo_t, :double, :double, :double, :double, :double, :double
cairo_rectangle		proto :ptr cairo_t, :double, :double, :double, :double

cairo_stroke_to_path	proto :ptr cairo_t
cairo_close_path	proto :ptr cairo_t
cairo_path_extents	proto :ptr cairo_t, :ptr double, :ptr double, :ptr double, :ptr double

cairo_paint		proto :ptr cairo_t
cairo_paint_with_alpha	proto :ptr cairo_t, :double
cairo_mask		proto :ptr cairo_t, :ptr cairo_pattern_t
cairo_mask_surface	proto :ptr cairo_t, :ptr cairo_surface_t, :double, :double

cairo_stroke		proto :ptr cairo_t
cairo_stroke_preserve	proto :ptr cairo_t

cairo_fill		proto :ptr cairo_t
cairo_fill_preserve	proto :ptr cairo_t
cairo_copy_page		proto :ptr cairo_t
cairo_show_page		proto :ptr cairo_t


cairo_in_stroke		proto :ptr cairo_t, :double, :double
cairo_in_fill		proto :ptr cairo_t, :double, :double
cairo_in_clip		proto :ptr cairo_t, :double, :double

cairo_stroke_extents	proto :ptr cairo_t, :ptr double, :ptr double, :ptr double, :ptr double
cairo_fill_extents	proto :ptr cairo_t, :ptr double, :ptr double, :ptr double, :ptr double

cairo_reset_clip	proto :ptr cairo_t
cairo_clip		proto :ptr cairo_t
cairo_clip_preserve	proto :ptr cairo_t

cairo_clip_extents	proto :ptr cairo_t, :ptr double, :ptr double, :ptr double, :ptr double

_cairo_rectangle	STRUC
x			double ?
y			double ?
width			double ?
height			double ?
_cairo_rectangle	ENDS
cairo_rectangle_t	typedef _cairo_rectangle

_cairo_rectangle_list	STRUC
status			cairo_status_t ?
rectangles		ptr cairo_rectangle_t ?
num_rectangles		SINT ?
_cairo_rectangle_list	ENDS
cairo_rectangle_list_t	typedef _cairo_rectangle_list

cairo_copy_clip_rectangle_list proto :ptr cairo_t
cairo_rectangle_list_destroy proto :ptr cairo_rectangle_list_t

define CAIRO_TAG_DEST <"cairo.dest">
define CAIRO_TAG_LINK <"Link">

cairo_tag_begin		proto :ptr cairo_t, :ptr, :ptr
cairo_tag_end		proto :ptr cairo_t, :ptr

cairo_scaled_font_t	typedef byte ; _cairo_scaled_font
cairo_font_face_t	typedef byte ; _cairo_font_face

cairo_glyph_t		STRUC
index			dd ?
x			double ?
y			double ?
cairo_glyph_t		ENDS

cairo_glyph_allocate	proto :int_t
cairo_glyph_free	proto :ptr cairo_glyph_t

cairo_text_cluster_t	STRUC
num_bytes		SINT ?
num_glyphs		SINT ?
cairo_text_cluster_t	ENDS

cairo_text_cluster_allocate proto :int_t
cairo_text_cluster_free proto :ptr cairo_text_cluster_t

.enum _cairo_text_cluster_flags {
    CAIRO_TEXT_CLUSTER_FLAG_BACKWARD = 0x00000001
    }
cairo_text_cluster_flags_t typedef _cairo_text_cluster_flags

cairo_text_extents_t	STRUC
x_bearing		double ?
y_bearing		double ?
width			double ?
height			double ?
x_advance		double ?
y_advance		double ?
cairo_text_extents_t	ENDS

cairo_font_extents_t	STRUC
ascent			double ?
descent			double ?
height			double ?
max_x_advance		double ?
max_y_advance		double ?
cairo_font_extents_t	ENDS

.enum _cairo_font_slant {
    CAIRO_FONT_SLANT_NORMAL,
    CAIRO_FONT_SLANT_ITALIC,
    CAIRO_FONT_SLANT_OBLIQUE
    }
cairo_font_slant_t	typedef _cairo_font_slant

.enum _cairo_font_weight {
    CAIRO_FONT_WEIGHT_NORMAL,
    CAIRO_FONT_WEIGHT_BOLD
    }
cairo_font_weight_t	typedef _cairo_font_weight

.enum _cairo_subpixel_order {
    CAIRO_SUBPIXEL_ORDER_DEFAULT,
    CAIRO_SUBPIXEL_ORDER_RGB,
    CAIRO_SUBPIXEL_ORDER_BGR,
    CAIRO_SUBPIXEL_ORDER_VRGB,
    CAIRO_SUBPIXEL_ORDER_VBGR
    }
cairo_subpixel_order_t	typedef _cairo_subpixel_order

.enum _cairo_hint_style {
    CAIRO_HINT_STYLE_DEFAULT,
    CAIRO_HINT_STYLE_NONE,
    CAIRO_HINT_STYLE_SLIGHT,
    CAIRO_HINT_STYLE_MEDIUM,
    CAIRO_HINT_STYLE_FULL
    }
cairo_hint_style_t	typedef _cairo_hint_style

.enum _cairo_hint_metrics {
    CAIRO_HINT_METRICS_DEFAULT,
    CAIRO_HINT_METRICS_OFF,
    CAIRO_HINT_METRICS_ON
    }
cairo_hint_metrics_t	typedef _cairo_hint_metrics
cairo_font_options_t	typedef byte ; _cairo_font_options

cairo_font_options_create proto
cairo_font_options_copy proto :ptr cairo_font_options_t
cairo_font_options_destroy proto :ptr cairo_font_options_t
cairo_font_options_status proto :ptr cairo_font_options_t
cairo_font_options_merge proto :ptr cairo_font_options_t, :ptr cairo_font_options_t
cairo_font_options_equal proto :ptr cairo_font_options_t, :ptr cairo_font_options_t
cairo_font_options_hash proto :ptr cairo_font_options_t
cairo_font_options_set_antialias proto :ptr cairo_font_options_t, :cairo_antialias_t
cairo_font_options_get_antialias proto :ptr cairo_font_options_t
cairo_font_options_set_subpixel_order proto :ptr cairo_font_options_t, :cairo_subpixel_order_t
cairo_font_options_get_subpixel_order proto :ptr cairo_font_options_t

cairo_font_options_set_hint_style proto :ptr cairo_font_options_t, :cairo_hint_style_t
cairo_font_options_get_hint_style proto :ptr cairo_font_options_t

cairo_font_options_set_hint_metrics proto :ptr cairo_font_options_t, :cairo_hint_metrics_t
cairo_font_options_get_hint_metrics proto :ptr cairo_font_options_t
cairo_font_options_get_variations proto :ptr cairo_font_options_t
cairo_font_options_set_variations proto :ptr cairo_font_options_t, :ptr
cairo_select_font_face			proto :ptr cairo_t, :ptr, :cairo_font_slant_t, :cairo_font_weight_t

cairo_set_font_size	proto :ptr cairo_t, :double
cairo_set_font_matrix	proto :ptr cairo_t, :ptr cairo_matrix_t
cairo_get_font_matrix	proto :ptr cairo_t, :ptr cairo_matrix_t
cairo_set_font_options	proto :ptr cairo_t, :ptr cairo_font_options_t
cairo_get_font_options	proto :ptr cairo_t, :ptr cairo_font_options_t
cairo_set_font_face	proto :ptr cairo_t, :ptr cairo_font_face_t
cairo_get_font_face	proto :ptr cairo_t
cairo_set_scaled_font	proto :ptr cairo_t, :ptr cairo_scaled_font_t
cairo_get_scaled_font	proto :ptr cairo_t
cairo_show_text		proto :ptr cairo_t, :ptr
cairo_show_glyphs	proto :ptr cairo_t, :ptr cairo_glyph_t, :int_t

cairo_show_text_glyphs	proto :ptr cairo_t, :ptr, :SINT, :ptr cairo_glyph_t, :SINT, :ptr cairo_text_cluster_t, :SINT, :cairo_text_cluster_flags_t
cairo_text_path		proto :ptr cairo_t, :ptr

cairo_glyph_path	proto :ptr cairo_t, :ptr cairo_glyph_t, :int_t

cairo_text_extents	proto :ptr cairo_t, :ptr, :ptr
cairo_glyph_extents	proto :ptr cairo_t, :ptr cairo_glyph_t, :SINT, :ptr cairo_text_extents_t
cairo_font_extents	proto :ptr cairo_t, :ptr cairo_font_extents_t

cairo_font_face_reference proto :ptr cairo_font_face_t
cairo_font_face_destroy proto :ptr cairo_font_face_t
cairo_font_face_get_reference_count proto :ptr cairo_font_face_t
cairo_font_face_status	proto :ptr cairo_font_face_t


.enum _cairo_font_type {
    CAIRO_FONT_TYPE_TOY,
    CAIRO_FONT_TYPE_FT,
    CAIRO_FONT_TYPE_WIN32,
    CAIRO_FONT_TYPE_QUARTZ,
    CAIRO_FONT_TYPE_USER
    }
cairo_font_type_t typedef _cairo_font_type

cairo_font_face_get_type proto :ptr cairo_font_face_t
cairo_font_face_get_user_data proto :ptr cairo_font_face_t, :ptr cairo_user_data_key_t
cairo_font_face_set_user_data proto :ptr cairo_font_face_t, :ptr cairo_user_data_key_t, :ptr, :cairo_destroy_func_t

cairo_scaled_font_create proto :ptr cairo_font_face_t, :ptr, :ptr, :ptr
cairo_scaled_font_reference proto :ptr cairo_scaled_font_t
cairo_scaled_font_destroy proto :ptr cairo_scaled_font_t
cairo_scaled_font_get_reference_count proto :ptr cairo_scaled_font_t
cairo_scaled_font_status proto :ptr cairo_scaled_font_t
cairo_scaled_font_get_type proto :ptr cairo_scaled_font_t
cairo_scaled_font_get_user_data proto :ptr cairo_scaled_font_t, :ptr cairo_user_data_key_t

cairo_scaled_font_set_user_data proto :ptr cairo_scaled_font_t, :ptr cairo_user_data_key_t, :ptr, :cairo_destroy_func_t
cairo_scaled_font_extents proto :ptr cairo_scaled_font_t, :ptr cairo_font_extents_t
cairo_scaled_font_text_extents proto :ptr cairo_scaled_font_t, :ptr, :ptr cairo_text_extents_t
cairo_scaled_font_glyph_extents proto :ptr cairo_scaled_font_t, :ptr, :SINT, :ptr
cairo_scaled_font_text_to_glyphs proto :ptr, :double, :double, :ptr, :SINT, :ptr, :ptr, :ptr,:ptr, :ptr

cairo_scaled_font_get_font_face proto :ptr cairo_scaled_font_t
cairo_scaled_font_get_font_matrix proto :ptr cairo_scaled_font_t, :ptr cairo_matrix_t
cairo_scaled_font_get_ctm proto :ptr cairo_scaled_font_t, :ptr cairo_matrix_t
cairo_scaled_font_get_scale_matrix proto :ptr cairo_scaled_font_t, :ptr cairo_matrix_t
cairo_scaled_font_get_font_options proto :ptr cairo_scaled_font_t, :ptr cairo_font_options_t

cairo_toy_font_face_create proto :ptr, :cairo_font_slant_t, :cairo_font_weight_t
cairo_toy_font_face_get_family proto :ptr cairo_font_face_t
cairo_toy_font_face_get_slant proto :ptr cairo_font_face_t
cairo_toy_font_face_get_weight proto :ptr cairo_font_face_t

cairo_user_font_face_create proto

CALLBACKC(cairo_user_scaled_font_init_func_t, :ptr, :ptr, :ptr)
CALLBACKC(cairo_user_scaled_font_render_glyph_func_t, :ptr, :dword, :ptr, :ptr)
CALLBACKC(cairo_user_scaled_font_text_to_glyphs_func_t, :ptr cairo_scaled_font_t, :ptr, :int_t, :ptr, :ptr, :ptr ptr, :ptr, :ptr)
CALLBACKC(cairo_user_scaled_font_unicode_to_glyph_func_t, :ptr cairo_scaled_font_t, :dword, :ptr)

cairo_user_font_face_set_init_func proto :ptr cairo_font_face_t, :cairo_user_scaled_font_init_func_t
cairo_user_font_face_set_render_glyph_func proto :ptr cairo_font_face_t, :cairo_user_scaled_font_render_glyph_func_t
cairo_user_font_face_set_text_to_glyphs_func proto :ptr cairo_font_face_t, :cairo_user_scaled_font_text_to_glyphs_func_t
cairo_user_font_face_set_unicode_to_glyph_func proto :ptr cairo_font_face_t, :cairo_user_scaled_font_unicode_to_glyph_func_t

cairo_user_font_face_get_init_func proto :ptr cairo_font_face_t
cairo_user_font_face_get_render_glyph_func proto :ptr cairo_font_face_t
cairo_user_font_face_get_text_to_glyphs_func proto :ptr cairo_font_face_t
cairo_user_font_face_get_unicode_to_glyph_func proto :ptr cairo_font_face_t

cairo_get_operator	proto :ptr cairo_t
cairo_get_source	proto :ptr cairo_t
cairo_get_tolerance	proto :ptr cairo_t
cairo_get_antialias	proto :ptr cairo_t
cairo_has_current_point proto :ptr cairo_t
cairo_get_current_point proto :ptr cairo_t, :ptr double, :ptr double
cairo_get_fill_rule	proto :ptr cairo_t
cairo_get_line_width	proto :ptr cairo_t
cairo_get_line_cap	proto :ptr cairo_t
cairo_get_line_join	proto :ptr cairo_t
cairo_get_miter_limit	proto :ptr cairo_t
cairo_get_dash_count	proto :ptr cairo_t
cairo_get_dash		proto :ptr cairo_t, :ptr double, :ptr double
cairo_get_matrix	proto :ptr cairo_t, :ptr cairo_matrix_t
cairo_get_target	proto :ptr cairo_t
cairo_get_group_target	proto :ptr cairo_t

.enum _cairo_path_data_type {
    CAIRO_PATH_MOVE_TO,
    CAIRO_PATH_LINE_TO,
    CAIRO_PATH_CURVE_TO,
    CAIRO_PATH_CLOSE_PATH
    }
cairo_path_data_type_t	typedef _cairo_path_data_type

_cairo_path_data_t	UNION
STRUC header
 type			cairo_path_data_type_t ?
 length			SINT ?
ENDS
STRUC point
 x			double ?
 y			double ?
ENDS
_cairo_path_data_t	ENDS
cairo_path_data_t	typedef _cairo_path_data_t

cairo_path		STRUC
status			cairo_status_t ?
data			ptr cairo_path_data_t ?
num_data		SINT ?
cairo_path		ENDS
cairo_path_t		typedef cairo_path

cairo_copy_path		proto :ptr cairo_t
cairo_copy_path_flat	proto :ptr cairo_t
cairo_append_path	proto :ptr cairo_t, :ptr cairo_path_t
cairo_path_destroy	proto :ptr cairo_path_t

cairo_status		proto :ptr cairo_t
cairo_status_to_string	proto :cairo_status_t
cairo_device_reference	proto :ptr cairo_device_t

.enum cairo_device_type {
    CAIRO_DEVICE_TYPE_DRM,
    CAIRO_DEVICE_TYPE_GL,
    CAIRO_DEVICE_TYPE_SCRIPT,
    CAIRO_DEVICE_TYPE_XCB,
    CAIRO_DEVICE_TYPE_XLIB,
    CAIRO_DEVICE_TYPE_XML,
    CAIRO_DEVICE_TYPE_COGL,
    CAIRO_DEVICE_TYPE_WIN32,
    CAIRO_DEVICE_TYPE_INVALID = -1
    }

cairo_device_get_type	proto :ptr cairo_device_t
cairo_device_status	proto :ptr cairo_device_t
cairo_device_acquire	proto :ptr cairo_device_t
cairo_device_release	proto :ptr cairo_device_t
cairo_device_flush	proto :ptr cairo_device_t
cairo_device_finish	proto :ptr cairo_device_t
cairo_device_destroy	proto :ptr cairo_device_t
cairo_device_get_reference_count proto :ptr cairo_device_t
cairo_device_get_user_data proto :ptr cairo_device_t, :ptr cairo_user_data_key_t
cairo_device_set_user_data proto :ptr cairo_device_t, :ptr cairo_user_data_key_t, :ptr, :cairo_destroy_func_t

cairo_surface_create_similar proto :ptr cairo_surface_t, :cairo_content_t, :SINT, :SINT
cairo_surface_create_similar_image proto :ptr cairo_surface_t, :cairo_format_t, :SINT, :SINT
cairo_surface_map_to_image proto :ptr cairo_surface_t, :ptr cairo_rectangle_int_t
cairo_surface_unmap_image proto :ptr cairo_surface_t, :ptr cairo_surface_t
cairo_surface_create_for_rectangle proto :ptr cairo_surface_t, :double, :double, :double, :double

.enum cairo_surface_observer_mode_t {
    CAIRO_SURFACE_OBSERVER_NORMAL = 0,
    CAIRO_SURFACE_OBSERVER_RECORD_OPERATIONS = 0x1
    }

cairo_surface_create_observer proto :ptr cairo_surface_t, :cairo_surface_observer_mode_t

CALLBACKC(cairo_surface_observer_callback_t, :ptr cairo_surface_t, :ptr cairo_surface_t, :ptr)

cairo_surface_observer_add_paint_callback proto :ptr cairo_surface_t, :cairo_surface_observer_callback_t, :ptr
cairo_surface_observer_add_mask_callback proto :ptr cairo_surface_t, :cairo_surface_observer_callback_t, :ptr
cairo_surface_observer_add_fill_callback proto :ptr cairo_surface_t, :cairo_surface_observer_callback_t, :ptr
cairo_surface_observer_add_stroke_callback proto :ptr cairo_surface_t, :cairo_surface_observer_callback_t, :ptr
cairo_surface_observer_add_glyphs_callback proto :ptr cairo_surface_t, :cairo_surface_observer_callback_t, :ptr
cairo_surface_observer_add_flush_callback proto :ptr cairo_surface_t, :cairo_surface_observer_callback_t, :ptr
cairo_surface_observer_add_finish_callback proto :ptr cairo_surface_t, :cairo_surface_observer_callback_t, :ptr

cairo_surface_observer_print proto :ptr cairo_surface_t, :cairo_write_func_t, :ptr
cairo_surface_observer_elapsed proto :ptr cairo_surface_t
cairo_device_observer_print proto :ptr cairo_device_t, :cairo_write_func_t, :ptr

cairo_device_observer_elapsed proto :ptr cairo_device_t
cairo_device_observer_paint_elapsed proto :ptr cairo_device_t
cairo_device_observer_mask_elapsed proto :ptr cairo_device_t
cairo_device_observer_fill_elapsed proto :ptr cairo_device_t

cairo_device_observer_stroke_elapsed proto :ptr cairo_device_t
cairo_device_observer_glyphs_elapsed proto :ptr cairo_device_t
cairo_surface_reference proto :ptr cairo_surface_t
cairo_surface_finish	proto :ptr cairo_surface_t
cairo_surface_destroy	proto :ptr cairo_surface_t
cairo_surface_get_device proto :ptr cairo_surface_t
cairo_surface_get_reference_count proto :ptr cairo_surface_t
cairo_surface_status	proto :ptr cairo_surface_t

.enum cairo_surface_type {
    CAIRO_SURFACE_TYPE_IMAGE,
    CAIRO_SURFACE_TYPE_PDF,
    CAIRO_SURFACE_TYPE_PS,
    CAIRO_SURFACE_TYPE_XLIB,
    CAIRO_SURFACE_TYPE_XCB,
    CAIRO_SURFACE_TYPE_GLITZ,
    CAIRO_SURFACE_TYPE_QUARTZ,
    CAIRO_SURFACE_TYPE_WIN32,
    CAIRO_SURFACE_TYPE_BEOS,
    CAIRO_SURFACE_TYPE_DIRECTFB,
    CAIRO_SURFACE_TYPE_SVG,
    CAIRO_SURFACE_TYPE_OS2,
    CAIRO_SURFACE_TYPE_WIN32_PRINTING,
    CAIRO_SURFACE_TYPE_QUARTZ_IMAGE,
    CAIRO_SURFACE_TYPE_SCRIPT,
    CAIRO_SURFACE_TYPE_QT,
    CAIRO_SURFACE_TYPE_RECORDING,
    CAIRO_SURFACE_TYPE_VG,
    CAIRO_SURFACE_TYPE_GL,
    CAIRO_SURFACE_TYPE_DRM,
    CAIRO_SURFACE_TYPE_TEE,
    CAIRO_SURFACE_TYPE_XML,
    CAIRO_SURFACE_TYPE_SKIA,
    CAIRO_SURFACE_TYPE_SUBSURFACE,
    CAIRO_SURFACE_TYPE_COGL
    }

cairo_surface_get_type	proto :ptr cairo_surface_t
cairo_surface_get_content proto :ptr cairo_surface_t

if CAIRO_HAS_PNG_FUNCTIONS
cairo_surface_write_to_png proto :ptr cairo_surface_t, :ptr
cairo_surface_write_to_png_stream proto :ptr cairo_surface_t, :cairo_write_func_t, :ptr
endif

cairo_surface_get_user_data proto :ptr cairo_surface_t, :ptr cairo_user_data_key_t
cairo_surface_set_user_data proto :ptr cairo_surface_t, :ptr cairo_user_data_key_t, :ptr, :cairo_destroy_func_t

define CAIRO_MIME_TYPE_JPEG		<"image/jpeg">
define CAIRO_MIME_TYPE_PNG		<"image/png">
define CAIRO_MIME_TYPE_JP2		<"image/jp2">
define CAIRO_MIME_TYPE_URI		<"text/x-uri">
define CAIRO_MIME_TYPE_UNIQUE_ID	<"application/x-cairo.uuid">
define CAIRO_MIME_TYPE_JBIG2		<"application/x-cairo.jbig2">
define CAIRO_MIME_TYPE_JBIG2_GLOBAL	<"application/x-cairo.jbig2-global">
define CAIRO_MIME_TYPE_JBIG2_GLOBAL_ID	<"application/x-cairo.jbig2-global-id">
define CAIRO_MIME_TYPE_CCITT_FAX	<"image/g3fax">
define CAIRO_MIME_TYPE_CCITT_FAX_PARAMS <"application/x-cairo.ccitt.params">
define CAIRO_MIME_TYPE_EPS		<"application/postscript">
define CAIRO_MIME_TYPE_EPS_PARAMS	<"application/x-cairo.eps.params">

cairo_surface_get_mime_data proto :ptr cairo_surface_t, :ptr, :ptr ptr, :ptr
cairo_surface_set_mime_data proto :ptr cairo_surface_t, :ptr, :ptr, :dword, :cairo_destroy_func_t, :ptr
cairo_surface_supports_mime_type proto :ptr cairo_surface_t, :ptr char_t
cairo_surface_get_font_options proto :ptr cairo_surface_t, :ptr cairo_font_options_t

cairo_surface_flush	proto :ptr cairo_surface_t
cairo_surface_mark_dirty proto :ptr cairo_surface_t
cairo_surface_mark_dirty_rectangle proto :ptr cairo_surface_t, :SINT, :SINT, :SINT, :SINT

cairo_surface_set_device_scale proto :ptr cairo_surface_t, :double, :double
cairo_surface_get_device_scale proto :ptr cairo_surface_t, :ptr double, :ptr double
cairo_surface_set_device_offset proto :ptr cairo_surface_t, :double, :double
cairo_surface_get_device_offset proto :ptr cairo_surface_t, :ptr double, :ptr double
cairo_surface_set_fallback_resolution proto :ptr cairo_surface_t, :double, :double
cairo_surface_get_fallback_resolution proto :ptr cairo_surface_t, :ptr double, :ptr double

cairo_surface_copy_page proto :ptr cairo_surface_t
cairo_surface_show_page proto :ptr cairo_surface_t
cairo_surface_has_show_text_glyphs proto :ptr cairo_surface_t

cairo_image_surface_create proto :cairo_format_t, :SINT, :SINT
cairo_format_stride_for_width proto :cairo_format_t, :SINT
cairo_image_surface_create_for_data proto :ptr, :cairo_format_t, :SINT, :SINT, :SINT

cairo_image_surface_get_data proto :ptr cairo_surface_t
cairo_image_surface_get_format proto :ptr cairo_surface_t

cairo_image_surface_get_width proto :ptr cairo_surface_t
cairo_image_surface_get_height proto :ptr cairo_surface_t
cairo_image_surface_get_stride proto :ptr cairo_surface_t

if CAIRO_HAS_PNG_FUNCTIONS

cairo_image_surface_create_from_png proto :ptr char_t
cairo_image_surface_create_from_png_stream proto :cairo_read_func_t, :ptr

endif

cairo_recording_surface_create proto :cairo_content_t, :ptr cairo_rectangle_t
cairo_recording_surface_ink_extents proto :ptr cairo_surface_t, :ptr double, :ptr double, :ptr double, :ptr double
cairo_recording_surface_get_extents proto :ptr cairo_surface_t, :ptr cairo_rectangle_t


CALLBACKC(cairo_raster_source_acquire_func_t, :ptr cairo_pattern_t, :ptr, :ptr cairo_surface_t, :ptr cairo_rectangle_int_t)
CALLBACKC(cairo_raster_source_release_func_t, :ptr cairo_pattern_t, :ptr, :ptr cairo_surface_t)
CALLBACKC(cairo_raster_source_snapshot_func_t, :ptr cairo_pattern_t, :ptr)
CALLBACKC(cairo_raster_source_copy_func_t, :ptr cairo_pattern_t, :ptr, :ptr cairo_pattern_t)
CALLBACKC(cairo_raster_source_finish_func_t, :ptr cairo_pattern_t, :ptr)

cairo_pattern_create_raster_source proto :ptr, :cairo_content_t, :int_t, :int_t
cairo_raster_source_pattern_set_callback_data proto :ptr cairo_pattern_t, :ptr
cairo_raster_source_pattern_get_callback_data proto :ptr cairo_pattern_t
cairo_raster_source_pattern_set_acquire proto :ptr cairo_pattern_t, :cairo_raster_source_acquire_func_t, :cairo_raster_source_release_func_t

cairo_raster_source_pattern_get_acquire proto :ptr cairo_pattern_t, :ptr cairo_raster_source_acquire_func_t, :ptr cairo_raster_source_release_func_t
cairo_raster_source_pattern_set_snapshot proto :ptr cairo_pattern_t, :cairo_raster_source_snapshot_func_t

cairo_raster_source_pattern_get_snapshot proto :ptr cairo_pattern_t
cairo_raster_source_pattern_set_copy proto :ptr cairo_pattern_t, :cairo_raster_source_copy_func_t
cairo_raster_source_pattern_get_copy proto :ptr cairo_pattern_t
cairo_raster_source_pattern_set_finish proto :ptr cairo_pattern_t, :cairo_raster_source_finish_func_t
cairo_raster_source_pattern_get_finish proto :ptr cairo_pattern_t

cairo_pattern_create_rgb proto :double, :double, :double
cairo_pattern_create_rgba proto :double, :double, :double, :double
cairo_pattern_create_for_surface proto :ptr cairo_surface_t
cairo_pattern_create_linear proto :double, :double, :double, :double
cairo_pattern_create_radial proto :double, :double, :double, :double, :double, :double

cairo_pattern_create_mesh proto
cairo_pattern_reference proto :ptr cairo_pattern_t
cairo_pattern_destroy	proto :ptr cairo_pattern_t
cairo_pattern_get_reference_count proto :ptr cairo_pattern_t
cairo_pattern_status	proto :ptr cairo_pattern_t
cairo_pattern_get_user_data proto :ptr cairo_pattern_t, :ptr cairo_user_data_key_t
cairo_pattern_set_user_data proto :ptr cairo_pattern_t, :ptr cairo_user_data_key_t, :ptr, :cairo_destroy_func_t

.enum _cairo_pattern_type {
    CAIRO_PATTERN_TYPE_SOLID,
    CAIRO_PATTERN_TYPE_SURFACE,
    CAIRO_PATTERN_TYPE_LINEAR,
    CAIRO_PATTERN_TYPE_RADIAL,
    CAIRO_PATTERN_TYPE_MESH,
    CAIRO_PATTERN_TYPE_RASTER_SOURCE
    }
cairo_pattern_type_t	typedef _cairo_pattern_type

cairo_pattern_get_type	proto :ptr cairo_pattern_t
cairo_pattern_add_color_stop_rgb proto :ptr cairo_pattern_t, :double, :double, :double, :double
cairo_pattern_add_color_stop_rgba proto :ptr cairo_pattern_t, :double, :double, :double, :double, :double

cairo_mesh_pattern_begin_patch proto :ptr cairo_pattern_t
cairo_mesh_pattern_end_patch proto :ptr cairo_pattern_t
cairo_mesh_pattern_curve_to proto :ptr cairo_pattern_t, :double, :double, :double, :double, :double, :double
cairo_mesh_pattern_line_to proto :ptr cairo_pattern_t, :double, :double
cairo_mesh_pattern_move_to proto :ptr cairo_pattern_t, :double, :double
cairo_mesh_pattern_set_control_point proto :ptr cairo_pattern_t, :uint_t,:double, :double
cairo_mesh_pattern_set_corner_color_rgb proto :ptr cairo_pattern_t, :uint_t, :double, :double, :double
cairo_mesh_pattern_set_corner_color_rgba proto :ptr cairo_pattern_t, :uint_t, :double, :double, :double, :double
cairo_pattern_set_matrix proto :ptr cairo_pattern_t, :ptr cairo_matrix_t
cairo_pattern_get_matrix proto :ptr cairo_pattern_t, :ptr cairo_matrix_t

.enum _cairo_extend {
    CAIRO_EXTEND_NONE,
    CAIRO_EXTEND_REPEAT,
    CAIRO_EXTEND_REFLECT,
    CAIRO_EXTEND_PAD
    }
cairo_extend_t		typedef _cairo_extend

cairo_pattern_set_extend proto :ptr cairo_pattern_t, :cairo_extend_t
cairo_pattern_get_extend proto :ptr cairo_pattern_t

.enum _cairo_filter {
    CAIRO_FILTER_FAST,
    CAIRO_FILTER_GOOD,
    CAIRO_FILTER_BEST,
    CAIRO_FILTER_NEAREST,
    CAIRO_FILTER_BILINEAR,
    CAIRO_FILTER_GAUSSIAN
    }
cairo_filter_t		typedef _cairo_filter

cairo_pattern_set_filter proto :ptr cairo_pattern_t, :cairo_filter_t
cairo_pattern_get_filter proto :ptr cairo_pattern_t
cairo_pattern_get_rgba	proto :ptr cairo_pattern_t, :ptr double, :ptr double, :ptr double, :ptr double
cairo_pattern_get_surface proto :ptr cairo_pattern_t, :ptr cairo_surface_t

cairo_pattern_get_color_stop_rgba proto :ptr cairo_pattern_t, :SINT, :ptr double, :ptr double, :ptr double, :ptr double, :ptr double
cairo_pattern_get_color_stop_count proto :ptr cairo_pattern_t, :ptr
cairo_pattern_get_linear_points proto :ptr cairo_pattern_t, :ptr double, :ptr double, :ptr double, :ptr double
cairo_pattern_get_radial_circles proto :ptr cairo_pattern_t, :ptr double, :ptr double, :ptr double, :ptr double, :ptr double, :ptr double

cairo_mesh_pattern_get_patch_count proto :ptr cairo_pattern_t, :ptr
cairo_mesh_pattern_get_path proto :ptr cairo_pattern_t, :uint_t
cairo_mesh_pattern_get_corner_color_rgba proto :ptr cairo_pattern_t, :uint_t, :uint_t, :ptr double, :ptr double, :ptr double, :ptr double
cairo_mesh_pattern_get_control_point proto :ptr cairo_pattern_t, :uint_t, :uint_t, :ptr double, :ptr double

cairo_matrix_init	proto :ptr cairo_matrix_t, :double, :double, :double, :double, :double, :double
cairo_matrix_init_identity proto :ptr cairo_matrix_t
cairo_matrix_init_translate proto :ptr cairo_matrix_t, :double, :double
cairo_matrix_init_scale proto :ptr cairo_matrix_t, :double, :double
cairo_matrix_init_rotate proto :ptr cairo_matrix_t, :double
cairo_matrix_translate	proto :ptr cairo_matrix_t, :double, :double
cairo_matrix_scale	proto :ptr cairo_matrix_t, :double, :double
cairo_matrix_rotate	proto :ptr cairo_matrix_t, :double
cairo_matrix_invert	proto :ptr cairo_matrix_t
cairo_matrix_multiply	proto :ptr cairo_matrix_t, :ptr cairo_matrix_t, :ptr cairo_matrix_t
cairo_matrix_transform_distance proto :ptr cairo_matrix_t, :ptr double, :ptr double
cairo_matrix_transform_point proto :ptr cairo_matrix_t, :ptr double, :ptr double

cairo_region_t		typedef byte ; _cairo_region

.enum _cairo_region_overlap {
    CAIRO_REGION_OVERLAP_IN,
    CAIRO_REGION_OVERLAP_OUT,
    CAIRO_REGION_OVERLAP_PART
    }
cairo_region_overlap_t	typedef _cairo_region_overlap

cairo_region_create	proto
cairo_region_create_rectangle proto :ptr cairo_rectangle_int_t
cairo_region_create_rectangles proto :ptr cairo_rectangle_int_t, :SINT
cairo_region_copy	proto :ptr cairo_region_t
cairo_region_reference	proto :ptr cairo_region_t
cairo_region_destroy	proto :ptr cairo_region_t
cairo_region_equal	proto :ptr cairo_region_t, :ptr cairo_region_t
cairo_region_status	proto :ptr cairo_region_t
cairo_region_get_extents proto :ptr cairo_region_t, :ptr cairo_rectangle_int_t
cairo_region_num_rectangles proto :ptr cairo_region_t
cairo_region_get_rectangle proto :ptr cairo_region_t, :SINT, :ptr cairo_rectangle_int_t
cairo_region_is_empty	proto :ptr cairo_region_t
cairo_region_contains_rectangle proto :ptr cairo_region_t, :ptr cairo_rectangle_int_t
cairo_region_contains_point proto :ptr cairo_region_t, :int_t, :int_t
cairo_region_translate	proto :ptr cairo_region_t, :int_t, :int_t
cairo_region_subtract	proto :ptr cairo_region_t, :ptr cairo_region_t
cairo_region_subtract_rectangle proto :ptr cairo_region_t, :ptr cairo_rectangle_int_t
cairo_region_intersect	proto :ptr cairo_region_t, :ptr cairo_region_t
cairo_region_intersect_rectangle proto :ptr cairo_region_t, :ptr cairo_rectangle_int_t
cairo_region_union	proto :ptr cairo_region_t, :ptr cairo_region_t
cairo_region_union_rectangle proto :ptr cairo_region_t, :ptr cairo_rectangle_int_t
cairo_region_xor	proto :ptr cairo_region_t, :ptr cairo_region_t
cairo_region_xor_rectangle proto :ptr cairo_region_t, :ptr cairo_rectangle_int_t
cairo_debug_reset_static_data proto

endif
