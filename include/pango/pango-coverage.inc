ifndef __PANGO_COVERAGE_H__
define __PANGO_COVERAGE_H__

include glib-object.inc

include pango/pango-version-macros.inc
;include hb.inc

;PangoCoverage           typedef _PangoCoverage

.enum PangoCoverageLevel {
  PANGO_COVERAGE_NONE,
  PANGO_COVERAGE_FALLBACK,
  PANGO_COVERAGE_APPROXIMATE,
  PANGO_COVERAGE_EXACT
}

pango_coverage_get_type proto

pango_coverage_new proto
pango_coverage_ref proto :ptr
pango_coverage_unref proto :ptr
pango_coverage_copy proto :ptr
pango_coverage_get proto :ptr, :sdword
pango_coverage_set proto :ptr, :sdword, :PangoCoverageLevel
pango_coverage_max proto :ptr, :ptr

pango_coverage_to_bytes proto :ptr, :ptr, :ptr
pango_coverage_from_bytes proto :ptr, :sdword

endif
