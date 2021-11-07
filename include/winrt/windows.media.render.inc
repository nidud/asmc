ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef __windows2Emedia2Erender_h__
define __windows2Emedia2Erender_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace Media
.namespace Render

.enum AudioRenderCategory {
    AudioRenderCategory_Other   = 0,
    AudioRenderCategory_ForegroundOnlyMedia = 1,
    AudioRenderCategory_BackgroundCapableMedia  = 2,
    AudioRenderCategory_Communications  = 3,
    AudioRenderCategory_Alerts  = 4,
    AudioRenderCategory_SoundEffects    = 5,
    AudioRenderCategory_GameEffects = 6,
    AudioRenderCategory_GameMedia   = 7
    }

.endn
.endn
.endn

endif
