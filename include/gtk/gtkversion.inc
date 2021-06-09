if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

ifndef __GTK_VERSION_H__
__GTK_VERSION_H__ equ <>

GTK_MAJOR_VERSION	equ (3)
GTK_MINOR_VERSION	equ (18)
GTK_MICRO_VERSION	equ (9)
GTK_BINARY_AGE		equ (1809)
GTK_INTERFACE_AGE	equ (9)

GTK_CHECK_VERSION macro major,minor,micro
    if (GTK_MAJOR_VERSION gt (major))
	exitm<1>
    endif
    if (GTK_MAJOR_VERSION eq (major) and GTK_MINOR_VERSION gt (minor))
	exitm<1>
    endif
    if (GTK_MAJOR_VERSION eq (major) and GTK_MINOR_VERSION eq (minor) and GTK_MICRO_VERSION ge (micro))
	exitm<1>
    endif
    exitm<0>
    endm

endif
