ifndef __GTK_LINK_BUTTON_H__
define __GTK_LINK_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

define GTK_TYPE_LINK_BUTTON <gtk_link_button_get_type>
GTK_LINK_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LINK_BUTTON, GtkLinkButton))>
  endm
GTK_IS_LINK_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LINK_BUTTON))>
  endm

;GtkLinkButton		 typedef _GtkLinkButton

gtk_link_button_get_type proto
gtk_link_button_new proto :ptr
gtk_link_button_new_with_label proto :ptr, :ptr
gtk_link_button_get_uri proto :ptr
gtk_link_button_set_uri proto :ptr, :ptr
gtk_link_button_get_visited proto :ptr
gtk_link_button_set_visited proto :ptr, :gboolean

endif
