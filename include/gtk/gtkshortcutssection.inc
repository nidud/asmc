ifndef __GTK_SHORTCUTS_SECTION_H__
define __GTK_SHORTCUTS_SECTION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

define GTK_TYPE_SHORTCUTS_SECTION <gtk_shortcuts_section_get_type>
GTK_SHORTCUTS_SECTION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SHORTCUTS_SECTION, GtkShortcutsSection))>
  endm
GTK_IS_SHORTCUTS_SECTION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SHORTCUTS_SECTION))>
  endm

;GtkShortcutsSection     typedef _GtkShortcutsSection
;GtkShortcutsSectionClass typedef _GtkShortcutsSectionClass

gtk_shortcuts_section_get_type proto

endif
