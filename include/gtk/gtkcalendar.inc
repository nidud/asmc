ifndef __GTK_CALENDAR_H__
__GTK_CALENDAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_CALENDAR equ <gtk_calendar_get_type>
GTK_CALENDAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CALENDAR, GtkCalendar))>
	endm
GTK_CALENDAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CALENDAR, GtkCalendarClass))>
	endm
GTK_IS_CALENDAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CALENDAR))>
	endm
GTK_IS_CALENDAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CALENDAR))>
	endm
GTK_CALENDAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CALENDAR, GtkCalendarClass))>
	endm

.enum GtkCalendarDisplayOptions {
  GTK_CALENDAR_SHOW_HEADING		= 1 shl 0,
  GTK_CALENDAR_SHOW_DAY_NAMES		= 1 shl 1,
  GTK_CALENDAR_NO_MONTH_CHANGE		= 1 shl 2,
  GTK_CALENDAR_SHOW_WEEK_NUMBERS	= 1 shl 3,
  GTK_CALENDAR_SHOW_DETAILS		= 1 shl 5
}

CALLBACKC(GtkCalendarDetailFunc, :ptr GtkCalendar, :guint, :guint, :guint, :gpointer)

GtkCalendar		STRUC
widget			GtkWidget <>
priv			ptr_t ?
GtkCalendar		ENDS

GtkCalendarClass	STRUC
parent_class		GtkWidgetClass <>
month_changed		proc :ptr GtkCalendar
day_selected		proc :ptr GtkCalendar
day_selected_double_click proc :ptr GtkCalendar
prev_month		proc :ptr GtkCalendar
next_month		proc :ptr GtkCalendar
prev_year		proc :ptr GtkCalendar
next_year		proc :ptr GtkCalendar
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCalendarClass	ENDS


;GType
gtk_calendar_get_type proto __cdecl
;GtkWidget*
gtk_calendar_new proto __cdecl

;void
gtk_calendar_select_month proto __cdecl \
	      calendar: ptr GtkCalendar,
		 month: guint,
		  year: guint

;void
gtk_calendar_select_day proto __cdecl \
	      calendar: ptr GtkCalendar,
		   day: guint


;void
gtk_calendar_mark_day proto __cdecl \
	      calendar: ptr GtkCalendar,
		   day: guint

;void
gtk_calendar_unmark_day proto __cdecl \
	      calendar: ptr GtkCalendar,
		   day: guint

;void
gtk_calendar_clear_marks proto __cdecl \
	      calendar: ptr GtkCalendar


;void
gtk_calendar_set_display_options proto __cdecl \
	      calendar: ptr GtkCalendar,
		 flags: GtkCalendarDisplayOptions

;GtkCalendarDisplayOptions
gtk_calendar_get_display_options proto __cdecl \
	      calendar: ptr GtkCalendar

;void
gtk_calendar_get_date proto __cdecl \
	      calendar: ptr GtkCalendar,
		  year: ptr guint,
		 month: ptr guint,
		   day: ptr guint

;void
gtk_calendar_set_detail_func proto __cdecl \
	      calendar: ptr GtkCalendar,
		  func: GtkCalendarDetailFunc,
		  data: gpointer,
	       destroy: GDestroyNotify


;void
gtk_calendar_set_detail_width_chars proto __cdecl \
	      calendar: ptr GtkCalendar,
		 chars: gint

;void
gtk_calendar_set_detail_height_rows proto __cdecl \
	      calendar: ptr GtkCalendar,
		  rows: gint

;gint
gtk_calendar_get_detail_width_chars proto __cdecl \
	      calendar: ptr GtkCalendar

;gint
gtk_calendar_get_detail_height_rows proto __cdecl \
	      calendar: ptr GtkCalendar

;gboolean
gtk_calendar_get_day_is_marked proto __cdecl \
	      calendar: ptr GtkCalendar,
		   day: guint

G_END_DECLS

endif
