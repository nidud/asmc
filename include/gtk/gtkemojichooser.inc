ifndef __GTK_EMOJI_CHOOSER_H__
define __GTK_EMOJI_CHOOSER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_EMOJI_CHOOSER <gtk_emoji_chooser_get_type ()>
GTK_EMOJI_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_EMOJI_CHOOSER, GtkEmojiChooser))>
  endm
GTK_EMOJI_CHOOSER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_EMOJI_CHOOSER, GtkEmojiChooserClass))>
  endm
GTK_IS_EMOJI_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_EMOJI_CHOOSER))>
  endm
GTK_IS_EMOJI_CHOOSER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_EMOJI_CHOOSER))>
  endm
GTK_EMOJI_CHOOSER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_EMOJI_CHOOSER, GtkEmojiChooserClass))>
  endm

gtk_emoji_chooser_get_type proto
gtk_emoji_chooser_new proto

endif
