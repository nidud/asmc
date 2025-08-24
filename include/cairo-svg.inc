ifndef CAIRO_SVG_H
define CAIRO_SVG_H

include cairo.inc

if CAIRO_HAS_SVG_SURFACE

.enum cairo_svg_version_t {
    CAIRO_SVG_VERSION_1_1,
    CAIRO_SVG_VERSION_1_2
    }

.enum cairo_svg_unit_t {
    CAIRO_SVG_UNIT_USER = 0,
    CAIRO_SVG_UNIT_EM,
    CAIRO_SVG_UNIT_EX,
    CAIRO_SVG_UNIT_PX,
    CAIRO_SVG_UNIT_IN,
    CAIRO_SVG_UNIT_CM,
    CAIRO_SVG_UNIT_MM,
    CAIRO_SVG_UNIT_PT,
    CAIRO_SVG_UNIT_PC,
    CAIRO_SVG_UNIT_PERCENT
    }

cairo_svg_surface_create proto :ptr, :double, :double
cairo_svg_surface_create_for_stream proto :cairo_write_func_t, :ptr, :double, :double
cairo_svg_surface_restrict_to_version proto :ptr cairo_surface_t, :cairo_svg_version_t
cairo_svg_get_versions proto :ptr cairo_svg_version_t, :ptr
cairo_svg_version_to_string proto :ptr cairo_svg_version_t
cairo_svg_surface_set_document_unit proto :ptr cairo_surface_t, :cairo_svg_unit_t
cairo_svg_surface_get_document_unit proto :ptr cairo_surface_t

else
 .err <Cairo was not compiled with support for the svg backend>
endif

endif
