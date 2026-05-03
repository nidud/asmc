ifndef _RPC500_
include rpc500.inc
endif
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace Media
.namespace Render

.enum AudioRenderCategory {
    AudioRenderCategory_Other,
    AudioRenderCategory_ForegroundOnlyMedia,
    AudioRenderCategory_BackgroundCapableMedia,
    AudioRenderCategory_Communications,
    AudioRenderCategory_Alerts,
    AudioRenderCategory_SoundEffects,
    AudioRenderCategory_GameEffects,
    AudioRenderCategory_GameMedia
    }

.endn
.endn
.endn

endif
