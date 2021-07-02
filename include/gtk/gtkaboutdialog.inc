ifndef __GTK_ABOUT_DIALOG_H__
__GTK_ABOUT_DIALOG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc

GTK_TYPE_ABOUT_DIALOG	equ <gtk_about_dialog_get_type>
GTK_ABOUT_DIALOG macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_ABOUT_DIALOG, GtkAboutDialog))>
	endm
GTK_ABOUT_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ABOUT_DIALOG, GtkAboutDialogClass))>
	endm
GTK_IS_ABOUT_DIALOG macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_ABOUT_DIALOG))>
	endm
GTK_IS_ABOUT_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ABOUT_DIALOG))>
	endm
GTK_ABOUT_DIALOG_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ABOUT_DIALOG, GtkAboutDialogClass))>
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
  GTK_LICENSE_LGPL_3_0_ONLY
}


GtkAboutDialog		STRUC
parent_instance		GtkDialog <>
priv			ptr_t ?
GtkAboutDialog		ENDS

GtkAboutDialogClass	STRUC
parent_class		GtkDialogClass <>
activate_link		proc :ptr GtkAboutDialog, :ptr gchar
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkAboutDialogClass	ENDS

;GType
gtk_about_dialog_get_type proto __cdecl
;GtkWidget
gtk_about_dialog_new proto __cdecl
;void
gtk_show_about_dialog proto _CDecl \
		parent: ptr GtkWindow,
   first_property_name: ptr gchar,
		      : vararg

;const
gtk_about_dialog_get_program_name proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_program_name proto __cdecl \
		 about: ptr GtkAboutDialog,
		  name: ptr gchar

;const
gtk_about_dialog_get_version proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_version proto __cdecl \
		 about: ptr GtkAboutDialog,
	       version: ptr gchar

;const
gtk_about_dialog_get_copyright proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_copyright proto __cdecl \
		 about: ptr GtkAboutDialog,
	     copyright: ptr gchar

;const
gtk_about_dialog_get_comments proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_comments proto __cdecl \
		 about: ptr GtkAboutDialog,
	      comments: ptr gchar

;const
gtk_about_dialog_get_license proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_license proto __cdecl \
		 about: ptr GtkAboutDialog,
	       license: ptr gchar

;void
gtk_about_dialog_set_license_type proto __cdecl \
		 about: ptr GtkAboutDialog,
	  license_type: GtkLicense

;GtkLicense
gtk_about_dialog_get_license_type proto __cdecl \
		 about: ptr GtkAboutDialog


;gboolean
gtk_about_dialog_get_wrap_license proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_wrap_license proto __cdecl \
		 about: ptr GtkAboutDialog,
	  wrap_license: gboolean


;const
gtk_about_dialog_get_website proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_website proto __cdecl \
		 about: ptr GtkAboutDialog,
	       website: ptr gchar

;const
gtk_about_dialog_get_website_label proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_website_label proto __cdecl \
		 about: ptr GtkAboutDialog,
	 website_label: ptr gchar

;const
gtk_about_dialog_get_authors proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_authors proto __cdecl \
		 about: ptr GtkAboutDialog,
	       authors: ptr gchar

;const
gtk_about_dialog_get_documenters proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_documenters proto __cdecl \
		 about: ptr GtkAboutDialog,
	   documenters: ptr gchar

;const
gtk_about_dialog_get_artists proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_artists proto __cdecl \
		 about: ptr GtkAboutDialog,
	       artists: ptr gchar

;const
gtk_about_dialog_get_translator_credits proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_translator_credits proto __cdecl \
		 about: ptr GtkAboutDialog,
    translator_credits: ptr gchar

;GdkPixbuf
gtk_about_dialog_get_logo proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_logo proto __cdecl \
		 about: ptr GtkAboutDialog,
		  logo: ptr GdkPixbuf

;const
gtk_about_dialog_get_logo_icon_name proto __cdecl \
		 about: ptr GtkAboutDialog

;void
gtk_about_dialog_set_logo_icon_name proto __cdecl \
		 about: ptr GtkAboutDialog,
	     icon_name: ptr gchar

;void
gtk_about_dialog_add_credit_section proto __cdecl \
		 about: ptr GtkAboutDialog,
	  section_name: ptr gchar,
		people: ptr gchar


endif


