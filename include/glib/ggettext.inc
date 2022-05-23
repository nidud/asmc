ifndef __G_GETTEXT_H__
define __G_GETTEXT_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;const
g_strip_context proto __cdecl \
                 msgid: ptr gchar,
                msgval: ptr gchar

;const
g_dgettext proto __cdecl \
                domain: ptr gchar,
                 msgid: ptr gchar

;const
g_dcgettext proto __cdecl \
                domain: ptr gchar,
                 msgid: ptr gchar,
              category: gint

;const
g_dngettext proto __cdecl \
                domain: ptr gchar,
                 msgid: ptr gchar,
          msgid_plural: ptr gchar,
                     n: gulong

;const
g_dpgettext proto __cdecl \
                domain: ptr gchar,
             msgctxtid: ptr gchar,
           msgidoffset: gsize

;const
g_dpgettext2 proto __cdecl \
                domain: ptr gchar,
               context: ptr gchar,
                 msgid: ptr gchar

endif
