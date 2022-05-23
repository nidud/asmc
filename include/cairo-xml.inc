ifndef CAIRO_XML_H
define CAIRO_XML_H

include cairo.inc

if CAIRO_HAS_XML_SURFACE

cairo_xml_create proto :ptr
cairo_xml_create_for_stream proto :cairo_write_func_t, :ptr
cairo_xml_surface_create proto :ptr cairo_device_t, :cairo_content_t, :double, :double
cairo_xml_for_recording_surface proto :ptr cairo_device_t, :ptr cairo_surface_t

else
 .err <Cairo was not compiled with support for the XML backend>
endif

endif
