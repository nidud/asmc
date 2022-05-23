ifndef __PANGO_MATRIX_H__
define __PANGO_MATRIX_H__

include glib.inc
include glib-object.inc

PangoMatrix		STRUC
xx			double ?
xy			double ?
yx			double ?
yy			double ?
x0			double ?
y0			double ?
PangoMatrix		ENDS

PANGO_TYPE_MATRIX	equ <pango_matrix_get_type>

define PANGO_MATRIX_INIT <{ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 }>

include pango/pango-types.inc

pango_matrix_get_type  proto __cdecl

pango_matrix_copy proto __cdecl \
		matrix: ptr PangoMatrix
;void
pango_matrix_free proto __cdecl \
		matrix: ptr PangoMatrix

;void
pango_matrix_translate proto __cdecl \
		matrix: ptr PangoMatrix,
		    tx: double,
		    ty: double

;void
pango_matrix_scale proto __cdecl \
		matrix: ptr PangoMatrix,
	       scale_x: double,
	       scale_y: double

;void
pango_matrix_rotate proto __cdecl \
		matrix: ptr PangoMatrix,
	       degrees: double

;void
pango_matrix_concat proto __cdecl \
		matrix: ptr PangoMatrix,
	    new_matrix: ptr PangoMatrix

;void
pango_matrix_transform_point proto __cdecl \
		matrix: ptr PangoMatrix,
		     x: ptr double,
		     y: ptr double

;void
pango_matrix_transform_distance proto __cdecl \
		matrix: ptr PangoMatrix,
		     x: ptr double,
		     y: ptr double

;void
pango_matrix_transform_rectangle proto __cdecl \
		matrix: ptr PangoMatrix,
		  rect: ptr PangoRectangle

;void
pango_matrix_transform_pixel_rectangle proto __cdecl \
		matrix: ptr PangoMatrix,
		  rect: ptr PangoRectangle


pango_matrix_get_font_scale_factor proto __cdecl \
		matrix: ptr PangoMatrix

;void
pango_matrix_get_font_scale_factors proto __cdecl \
		matrix: ptr PangoMatrix,
		xscale: ptr double,
		yscale: ptr double


pango_matrix_get_slant_ratio proto __cdecl \
		matrix: ptr PangoMatrix

endif
