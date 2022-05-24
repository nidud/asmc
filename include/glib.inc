ifndef __G_LIB_H__
define __G_LIB_H__

.pragma list(push, 0)

define __GLIB_H_INSIDE__

include libc.inc

.pragma comment(lib, "glib-2.0")

include glib/gtypes.inc
include glib/gquark.inc
include glib/gversion.inc
include glib/gversionmacros.inc

include glib/galloca.inc
include glib/garray.inc
include glib/gasyncqueue.inc
include glib/gatomic.inc
include glib/gbacktrace.inc
include glib/gbase64.inc
include glib/gbitlock.inc
include glib/gbookmarkfile.inc
include glib/gbytes.inc
include glib/gcharset.inc
include glib/gchecksum.inc
include glib/gconvert.inc
include glib/gdate.inc
include glib/gdataset.inc
include glib/gdatetime.inc
include glib/gdir.inc
include glib/genviron.inc
include glib/gerror.inc
include glib/gfileutils.inc
include glib/ggettext.inc
include glib/ghash.inc
include glib/ghmac.inc
include glib/ghook.inc
include glib/ghostutils.inc
include glib/giochannel.inc
include glib/gkeyfile.inc
include glib/glist.inc
include glib/gmacros.inc
include glib/gmain.inc
include glib/gmappedfile.inc
include glib/gmarkup.inc
include glib/gmem.inc
include glib/gmessages.inc
include glib/gnode.inc
include glib/goption.inc
include glib/gpattern.inc
include glib/gpoll.inc
include glib/gprimes.inc
include glib/gqsort.inc
include glib/gqueue.inc
include glib/grand.inc
include glib/gregex.inc
include glib/gscanner.inc
include glib/gsequence.inc
include glib/gshell.inc
include glib/gslice.inc
include glib/gslist.inc
include glib/gspawn.inc
include glib/gstrfuncs.inc
include glib/gstring.inc
include glib/gstringchunk.inc
include glib/gtestutils.inc
include glib/gthread.inc
include glib/gthreadpool.inc
include glib/gtimer.inc
include glib/gtimezone.inc
include glib/gtrashstack.inc
include glib/gtree.inc
include glib/gunicode.inc
;include glib/gurifuncs.inc
include glib/gutils.inc
include glib/gvarianttype.inc
include glib/gvariant.inc

ifdef G_PLATFORM_WIN32
include glib/gwin32.inc
endif

ifndef G_DISABLE_DEPRECATED
;include glib/deprecated/gallocator.inc
;include glib/deprecated/gcache.inc
;include glib/deprecated/gcompletion.inc
;include glib/deprecated/gmain.inc
;include glib/deprecated/grel.inc
;include glib/deprecated/gthread.inc
endif

include glib/glib-autocleanups.inc

undef __GLIB_H_INSIDE__

.pragma list(pop)
endif
