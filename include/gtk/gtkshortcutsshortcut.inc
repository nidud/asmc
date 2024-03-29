ifndef GTK_SHORTCUTS_SHORTCUT_H
define GTK_SHORTCUTS_SHORTCUT_H

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

define GTK_TYPE_SHORTCUTS_SHORTCUT <gtk_shortcuts_shortcut_get_type ()>
GTK_SHORTCUTS_SHORTCUT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SHORTCUTS_SHORTCUT, GtkShortcutsShortcut))>
  endm
GTK_IS_SHORTCUTS_SHORTCUT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SHORTCUTS_SHORTCUT))>
  endm


;GtkShortcutsShortcut    typedef _GtkShortcutsShortcut
;GtkShortcutsShortcutClass typedef _GtkShortcutsShortcutClass


.enum GtkShortcutType {
  GTK_SHORTCUT_ACCELERATOR,
  GTK_SHORTCUT_GESTURE_PINCH,
  GTK_SHORTCUT_GESTURE_STRETCH,
  GTK_SHORTCUT_GESTURE_ROTATE_CLOCKWISE,
  GTK_SHORTCUT_GESTURE_ROTATE_COUNTERCLOCKWISE,
  GTK_SHORTCUT_GESTURE_TWO_FINGER_SWIPE_LEFT,
  GTK_SHORTCUT_GESTURE_TWO_FINGER_SWIPE_RIGHT,
  GTK_SHORTCUT_GESTURE,
  GTK_SHORTCUT_GESTURE_SWIPE_LEFT,
  GTK_SHORTCUT_GESTURE_SWIPE_RIGHT
}

gtk_shortcuts_shortcut_get_type proto

endif
