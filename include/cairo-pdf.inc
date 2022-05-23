ifndef CAIRO_PDF_H
define CAIRO_PDF_H

include cairo.inc

if CAIRO_HAS_PDF_SURFACE

.enum _cairo_pdf_version {
    CAIRO_PDF_VERSION_1_4,
    CAIRO_PDF_VERSION_1_5
    }
cairo_pdf_version_t typedef _cairo_pdf_version

cairo_pdf_surface_create proto :ptr, :double, :double
cairo_pdf_surface_create_for_stream proto :cairo_write_func_t, :ptr, :double, :double
cairo_pdf_surface_restrict_to_version proto :ptr cairo_surface_t, :cairo_pdf_version_t
cairo_pdf_get_versions proto :ptr cairo_pdf_version_t, :ptr
cairo_pdf_version_to_string proto :cairo_pdf_version_t
cairo_pdf_surface_set_size proto :ptr cairo_surface_t, :double, :double

.enum _cairo_pdf_outline_flags {
    CAIRO_PDF_OUTLINE_FLAG_OPEN	  = 0x1,
    CAIRO_PDF_OUTLINE_FLAG_BOLD	  = 0x2,
    CAIRO_PDF_OUTLINE_FLAG_ITALIC = 0x4,
    }
cairo_pdf_outline_flags_t typedef _cairo_pdf_outline_flags

define CAIRO_PDF_OUTLINE_ROOT 0

cairo_pdf_surface_add_outline proto :ptr cairo_surface_t, :SINT, :ptr, :ptr, :cairo_pdf_outline_flags_t

.enum _cairo_pdf_metadata {
    CAIRO_PDF_METADATA_TITLE,
    CAIRO_PDF_METADATA_AUTHOR,
    CAIRO_PDF_METADATA_SUBJECT,
    CAIRO_PDF_METADATA_KEYWORDS,
    CAIRO_PDF_METADATA_CREATOR,
    CAIRO_PDF_METADATA_CREATE_DATE,
    CAIRO_PDF_METADATA_MOD_DATE,
    }

cairo_pdf_metadata_t typedef _cairo_pdf_metadata

cairo_pdf_surface_set_metadata proto :ptr cairo_surface_t, :cairo_pdf_metadata_t, :ptr
cairo_pdf_surface_set_page_label proto :ptr cairo_surface_t, :ptr
cairo_pdf_surface_set_thumbnail_size proto :ptr cairo_surface_t, :SINT, :SINT

else
 .err <Cairo was not compiled with support for the pdf backend>
endif

endif
