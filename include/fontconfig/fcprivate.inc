ifndef _FCPRIVATE_H_
define _FCPRIVATE_H_

FcPatternVapBuild macro result, orig, va
	exitm<.err>
	endm

FcObjectSetVapBuild macro __ret__, __first__, __va__
	exitm<.err>
	endm

ifndef FC_ATTRIBUTE_VISIBILITY_HIDDEN
FC_ATTRIBUTE_VISIBILITY_HIDDEN equ <__attribute((visibility("hidden")))>
endif

ifndef FC_ATTRIBUTE_VISIBILITY_EXPORT
FC_ATTRIBUTE_VISIBILITY_EXPORT equ <__attribute((visibility("default")))>
endif

endif
