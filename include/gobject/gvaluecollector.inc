ifndef __G_VALUE_COLLECTOR_H__
define __G_VALUE_COLLECTOR_H__

include glib-object.inc

.enum {
  G_VALUE_COLLECT_INT		= 'i',
  G_VALUE_COLLECT_LONG		= 'l',
  G_VALUE_COLLECT_INT64		= 'q',
  G_VALUE_COLLECT_DOUBLE	= 'd',
  G_VALUE_COLLECT_POINTER	= 'p'
}

_GTypeCValue		union
v_int			gint ?
v_long			glong ?
v_int64			gint64 ?
v_double		gdouble ?
v_pointer		gpointer ?
_GTypeCValue		ends
GTypeCValue		typedef _GTypeCValue


G_VALUE_COLLECT_INIT macro value, _value_type, var_args, flags, __error
  exitm<.err>
  endm


G_VALUE_COLLECT macro value, var_args, flags, __error
  exitm<.err>
  endm


G_VALUE_COLLECT_SKIP macro _value_type, var_args
  exitm<.err>
  endm


G_VALUE_LCOPY macro value, var_args, flags, __error
  exitm<.err>
  endm

define	G_VALUE_COLLECT_FORMAT_MAX_LENGTH	(8)

endif
