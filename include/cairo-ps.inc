ifndef CAIRO_PS_H
define CAIRO_PS_H

include cairo.inc

if CAIRO_HAS_PS_SURFACE

include stdio.inc

.enum cairo_ps_level_t {
    CAIRO_PS_LEVEL_2,
    CAIRO_PS_LEVEL_3
    }

cairo_ps_surface_create proto :ptr, :double, :double
cairo_ps_surface_create_for_stream proto :cairo_write_func_t, :ptr, :double, :double
cairo_ps_surface_restrict_to_level proto :ptr cairo_surface_t, :cairo_ps_level_t
cairo_ps_get_levels proto :ptr cairo_ps_level_t, :ptr
cairo_ps_level_to_string proto :cairo_ps_level_t
cairo_ps_surface_set_eps proto :ptr cairo_surface_t, :cairo_bool_t
cairo_ps_surface_get_eps proto :ptr cairo_surface_t
cairo_ps_surface_set_size proto :ptr cairo_surface_t, :double, :double
cairo_ps_surface_dsc_comment proto :ptr cairo_surface_t, :ptr
cairo_ps_surface_dsc_begin_setup proto :ptr cairo_surface_t
cairo_ps_surface_dsc_begin_page_setup proto :ptr cairo_surface_t

else
 .err <Cairo was not compiled with support for the ps backend>
endif

endif
