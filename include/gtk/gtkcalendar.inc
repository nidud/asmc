ifndef __GTK_CALENDAR_H__
define __GTK_CALENDAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_CALENDAR <gtk_calendar_get_type ()>
GTK_CALENDAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CALENDAR, GtkCalendar))>
  endm
GTK_IS_CALENDAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CALENDAR))>
  endm

;GtkCalendar             typedef _GtkCalendar

gtk_calendar_get_type proto
gtk_calendar_new proto
gtk_calendar_select_day proto :ptr, :ptr
gtk_calendar_mark_day proto :ptr, :guint
gtk_calendar_unmark_day proto :ptr, :guint
gtk_calendar_clear_marks proto :ptr
gtk_calendar_set_show_week_numbers proto :ptr, :gboolean
gtk_calendar_get_show_week_numbers proto :ptr
gtk_calendar_set_show_heading proto :ptr, :gboolean
gtk_calendar_get_show_heading proto :ptr
gtk_calendar_set_show_day_names proto :ptr, :gboolean
gtk_calendar_get_show_day_names proto :ptr
gtk_calendar_get_date proto :ptr
gtk_calendar_get_day_is_marked proto :ptr, :guint

endif
