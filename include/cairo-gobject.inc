
ifndef CAIRO_GOBJECT_H
define CAIRO_GOBJECT_H

include cairo.inc

if CAIRO_HAS_GOBJECT_FUNCTIONS

include glib-object.inc

cairo_gobject_context_get_type proto
cairo_gobject_device_get_type proto
cairo_gobject_matrix_get_type proto
cairo_gobject_pattern_get_type proto
cairo_gobject_surface_get_type proto
cairo_gobject_rectangle_get_type proto
cairo_gobject_scaled_font_get_type proto
cairo_gobject_font_face_get_type proto
cairo_gobject_font_options_get_type proto
cairo_gobject_rectangle_int_get_type proto
cairo_gobject_region_get_type proto
cairo_gobject_status_get_type proto
cairo_gobject_content_get_type proto
cairo_gobject_operator_get_type proto
cairo_gobject_antialias_get_type proto
cairo_gobject_fill_rule_get_type proto
cairo_gobject_line_cap_get_type proto
cairo_gobject_line_join_get_type proto
cairo_gobject_text_cluster_flags_get_type proto
cairo_gobject_font_slant_get_type proto
cairo_gobject_font_weight_get_type proto
cairo_gobject_subpixel_order_get_type proto
cairo_gobject_hint_style_get_type proto
cairo_gobject_hint_metrics_get_type proto
cairo_gobject_font_type_get_type proto
cairo_gobject_path_data_type_get_type proto
cairo_gobject_device_type_get_type proto
cairo_gobject_surface_type_get_type proto
cairo_gobject_format_get_type proto
cairo_gobject_pattern_type_get_type proto
cairo_gobject_extend_get_type proto
cairo_gobject_filter_get_type proto
cairo_gobject_region_overlap_get_type proto

CAIRO_GOBJECT_TYPE_CONTEXT macro
    cairo_gobject_context_get_type()
    endm
CAIRO_GOBJECT_TYPE_DEVICE macro
    cairo_gobject_device_get_type ()
    endm
CAIRO_GOBJECT_TYPE_MATRIX macro
    cairo_gobject_matrix_get_type ()
    endm
CAIRO_GOBJECT_TYPE_PATTERN macro
    cairo_gobject_pattern_get_type ()
    endm
CAIRO_GOBJECT_TYPE_SURFACE macro
    cairo_gobject_surface_get_type ()
    endm
CAIRO_GOBJECT_TYPE_RECTANGLE macro
    cairo_gobject_rectangle_get_type ()
    endm
CAIRO_GOBJECT_TYPE_SCALED_FONT macro
    cairo_gobject_scaled_font_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FONT_FACE macro
    cairo_gobject_font_face_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FONT_OPTIONS macro
    cairo_gobject_font_options_get_type ()
    endm
CAIRO_GOBJECT_TYPE_RECTANGLE_INT macro
    cairo_gobject_rectangle_int_get_type ()
    endm
CAIRO_GOBJECT_TYPE_REGION macro
    cairo_gobject_region_get_type ()
    endm
CAIRO_GOBJECT_TYPE_STATUS macro
    cairo_gobject_status_get_type ()
    endm
CAIRO_GOBJECT_TYPE_CONTENT macro
    cairo_gobject_content_get_type ()
    endm
CAIRO_GOBJECT_TYPE_OPERATOR macro
    cairo_gobject_operator_get_type ()
    endm
CAIRO_GOBJECT_TYPE_ANTIALIAS macro
    cairo_gobject_antialias_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FILL_RULE macro
    cairo_gobject_fill_rule_get_type ()
    endm
CAIRO_GOBJECT_TYPE_LINE_CAP macro
    cairo_gobject_line_cap_get_type ()
    endm
CAIRO_GOBJECT_TYPE_LINE_JOIN macro
    cairo_gobject_line_join_get_type ()
    endm
CAIRO_GOBJECT_TYPE_TEXT_CLUSTER_FLAGS macro
    cairo_gobject_text_cluster_flags_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FONT_SLANT macro
    cairo_gobject_font_slant_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FONT_WEIGHT macro
    cairo_gobject_font_weight_get_type ()
    endm
CAIRO_GOBJECT_TYPE_SUBPIXEL_ORDER macro
    cairo_gobject_subpixel_order_get_type ()
    endm
CAIRO_GOBJECT_TYPE_HINT_STYLE macro
    cairo_gobject_hint_style_get_type ()
    endm
CAIRO_GOBJECT_TYPE_HNT_METRICS macro
    cairo_gobject_hint_metrics_get_type ()
    endm
CAIRO_GOBJECT_TYPE_HINT_METRICS macro
    cairo_gobject_hint_metrics_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FONT_TYPE macro
    cairo_gobject_font_type_get_type ()
    endm
CAIRO_GOBJECT_TYPE_PATH_DATA_TYPE macro
    cairo_gobject_path_data_type_get_type ()
    endm
CAIRO_GOBJECT_TYPE_DEVICE_TYPE macro
    cairo_gobject_device_type_get_type ()
    endm
CAIRO_GOBJECT_TYPE_SURFACE_TYPE macro
    cairo_gobject_surface_type_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FORMAT macro
    cairo_gobject_format_get_type ()
    endm
CAIRO_GOBJECT_TYPE_PATTERN_TYPE macro
    cairo_gobject_pattern_type_get_type ()
    endm
CAIRO_GOBJECT_TYPE_EXTEND macro
    cairo_gobject_extend_get_type ()
    endm
CAIRO_GOBJECT_TYPE_FILTER macro
    cairo_gobject_filter_get_type ()
    endm
CAIRO_GOBJECT_TYPE_REGION_OVERLAP macro
    cairo_gobject_region_overlap_get_type ()
    endm
else
 .err <Cairo was not compiled with support for GObject>
endif

endif
