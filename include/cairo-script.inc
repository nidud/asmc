ifndef CAIRO_SCRIPT_H
define CAIRO_SCRIPT_H

include cairo.inc

if CAIRO_HAS_SCRIPT_SURFACE

.enum cairo_script_mode_t {
    CAIRO_SCRIPT_MODE_ASCII,
    CAIRO_SCRIPT_MODE_BINARY
    }

cairo_script_create proto :ptr
cairo_script_create_for_stream proto :cairo_write_func_t, :ptr
cairo_script_write_comment proto :ptr cairo_device_t, :ptr, :SINT
cairo_script_set_mode proto :ptr cairo_device_t, :cairo_script_mode_t
cairo_script_get_mode proto :ptr cairo_device_t
cairo_script_surface_create proto :ptr cairo_device_t, :cairo_content_t, :double, :double
cairo_script_surface_create_for_target proto :ptr cairo_device_t, :ptr cairo_surface_t
cairo_script_from_recording_surface proto :ptr cairo_device_t, :ptr cairo_surface_t

else
 .err <Cairo was not compiled with support for the CairoScript backend>
endif

endif
