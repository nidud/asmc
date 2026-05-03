ifndef CAIRO_TEE_H
define CAIRO_TEE_H

include cairo.inc

if CAIRO_HAS_TEE_SURFACE

cairo_tee_surface_create proto :ptr cairo_surface_t
cairo_tee_surface_add proto :ptr cairo_surface_t, :ptr cairo_surface_t
cairo_tee_surface_remove proto :ptr cairo_surface_t, :ptr cairo_surface_t
cairo_tee_surface_index proto :ptr cairo_surface_t, :uint_t

else
 .err <Cairo was not compiled with support for the TEE backend>
endif

endif
