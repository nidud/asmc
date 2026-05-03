ifndef __GTK_ABOUT_DIALOG_H__
define __GTK_ABOUT_DIALOG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

define GTK_TYPE_ABOUT_DIALOG <gtk_about_dialog_get_type ()>
GTK_ABOUT_DIALOG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_ABOUT_DIALOG, GtkAboutDialog))>
  endm
GTK_IS_ABOUT_DIALOG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_ABOUT_DIALOG))>
  endm

.enum GtkLicense {
  GTK_LICENSE_UNKNOWN,
  GTK_LICENSE_CUSTOM,
  GTK_LICENSE_GPL_2_0,
  GTK_LICENSE_GPL_3_0,
  GTK_LICENSE_LGPL_2_1,
  GTK_LICENSE_LGPL_3_0,
  GTK_LICENSE_BSD,
  GTK_LICENSE_MIT_X11,
  GTK_LICENSE_ARTISTIC,
  GTK_LICENSE_GPL_2_0_ONLY,
  GTK_LICENSE_GPL_3_0_ONLY,
  GTK_LICENSE_LGPL_2_1_ONLY,
  GTK_LICENSE_LGPL_3_0_ONLY,
  GTK_LICENSE_AGPL_3_0,
  GTK_LICENSE_AGPL_3_0_ONLY,
  GTK_LICENSE_BSD_3,
  GTK_LICENSE_APACHE_2_0,
  GTK_LICENSE_MPL_2_0
}


gtk_about_dialog_get_type proto
gtk_about_dialog_new proto
gtk_show_about_dialog proto :ptr, :ptr, :vararg
gtk_about_dialog_get_program_name proto :ptr
gtk_about_dialog_set_program_name proto :ptr, :ptr
gtk_about_dialog_get_version proto :ptr
gtk_about_dialog_set_version proto :ptr, :ptr
gtk_about_dialog_get_copyright proto :ptr
gtk_about_dialog_set_copyright proto :ptr, :ptr
gtk_about_dialog_get_comments proto :ptr
gtk_about_dialog_set_comments proto :ptr, :ptr
gtk_about_dialog_get_license proto :ptr
gtk_about_dialog_set_license proto :ptr, :ptr
gtk_about_dialog_set_license_type proto :ptr, :GtkLicense
gtk_about_dialog_get_license_type proto :ptr

gtk_about_dialog_get_wrap_license proto :ptr
gtk_about_dialog_set_wrap_license proto :ptr, :gboolean

gtk_about_dialog_get_system_information proto :ptr
gtk_about_dialog_set_system_information proto :ptr, :ptr
gtk_about_dialog_get_website proto :ptr
gtk_about_dialog_set_website proto :ptr, :ptr
gtk_about_dialog_get_website_label proto :ptr
gtk_about_dialog_set_website_label proto :ptr, :ptr
gtk_about_dialog_get_authors proto :ptr
gtk_about_dialog_set_authors proto :ptr, :ptr
gtk_about_dialog_get_documenters proto :ptr
gtk_about_dialog_set_documenters proto :ptr, :ptr
gtk_about_dialog_get_artists proto :ptr
gtk_about_dialog_set_artists proto :ptr, :ptr
gtk_about_dialog_get_translator_credits proto :ptr
gtk_about_dialog_set_translator_credits proto :ptr, :ptr
gtk_about_dialog_get_logo proto :ptr
gtk_about_dialog_set_logo proto :ptr, :ptr
gtk_about_dialog_get_logo_icon_name proto :ptr
gtk_about_dialog_set_logo_icon_name proto :ptr, :ptr
gtk_about_dialog_add_credit_section proto :ptr, :ptr, :ptr

endif


