ifndef __PANGO_GRAVITY_H__
define __PANGO_GRAVITY_H__

include glib.inc

.enum PangoGravity {
    PANGO_GRAVITY_SOUTH,
    PANGO_GRAVITY_EAST,
    PANGO_GRAVITY_NORTH,
    PANGO_GRAVITY_WEST,
    PANGO_GRAVITY_AUTO
    }

.enum PangoGravityHint {
    PANGO_GRAVITY_HINT_NATURAL,
    PANGO_GRAVITY_HINT_STRONG,
    PANGO_GRAVITY_HINT_LINE
    }

include pango/pango-matrix.inc
include pango/pango-script.inc

pango_gravity_to_rotation proto __cdecl :PangoGravity
pango_gravity_get_for_matrix proto __cdecl :ptr
pango_gravity_get_for_script proto __cdecl :PangoScript, :PangoGravity, :PangoGravityHint
pango_gravity_get_for_script_and_width proto __cdecl :PangoScript, :gboolean, :PangoGravity, :PangoGravityHint

endif
