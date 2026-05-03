ifndef __G_WIN32_H__
define __G_WIN32_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

ifdef G_PLATFORM_WIN32

ifndef MAXPATHLEN
define MAXPATHLEN 1024
endif

ifdef G_OS_WIN32
g_win32_ftruncate proto :gint, :guint
endif

g_win32_getlocale proto
g_win32_error_message proto :gint
g_win32_get_package_installation_directory proto :ptr, :ptr
g_win32_get_package_installation_subdirectory proto :ptr, :ptr, :ptr
g_win32_get_package_installation_directory_of_module proto :gpointer
g_win32_get_windows_version proto
g_win32_locale_filename_from_utf8 proto :ptr
g_win32_get_command_line proto


G_WIN32_IS_NT_BASED macro
  exitm<TRUE>
  endm
G_WIN32_HAVE_WIDECHAR_API macro
  exitm<TRUE>
  endm

.enum GWin32OSType {
  G_WIN32_OS_ANY,
  G_WIN32_OS_WORKSTATION,
  G_WIN32_OS_SERVER,
}

g_win32_check_windows_version proto :gint, :gint, :gint, :GWin32OSType

endif

endif
