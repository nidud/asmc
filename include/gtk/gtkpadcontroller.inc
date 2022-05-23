ifndef __GTK_PAD_CONTROLLER_H__
define __GTK_PAD_CONTROLLER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkeventcontroller.inc

define GTK_TYPE_PAD_CONTROLLER <gtk_pad_controller_get_type>
GTK_PAD_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_PAD_CONTROLLER, GtkPadController))>
  endm
GTK_PAD_CONTROLLER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_PAD_CONTROLLER, GtkPadControllerClass))>
  endm
GTK_IS_PAD_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_PAD_CONTROLLER))>
  endm
GTK_IS_PAD_CONTROLLER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_PAD_CONTROLLER))>
  endm
GTK_PAD_CONTROLLER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_PAD_CONTROLLER, GtkPadControllerClass))>
  endm

;GtkPadController        typedef _GtkPadController
;GtkPadControllerClass   typedef _GtkPadControllerClass


.enum GtkPadActionType {
  GTK_PAD_ACTION_BUTTON,
  GTK_PAD_ACTION_RING,
  GTK_PAD_ACTION_STRIP
}


_GtkPadActionEntry      struct
type                    GtkPadActionType ?
index                   sdword ?
mode                    sdword ?
_label                  ptr sbyte ?
action_name             ptr sbyte ?
_GtkPadActionEntry      ends
GtkPadActionEntry       typedef _GtkPadActionEntry

gtk_pad_controller_get_type proto
gtk_pad_controller_new proto :ptr, :ptr
gtk_pad_controller_set_action_entries proto :ptr, :ptr, :sdword
gtk_pad_controller_set_action proto :ptr, :GtkPadActionType, :sdword, :sdword, :ptr, :ptr

endif
