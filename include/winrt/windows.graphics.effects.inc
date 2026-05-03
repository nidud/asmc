ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Egraphics2Eeffects_h__
define __windows2Egraphics2Eeffects_h__
ifndef __windows2Egraphics2Eeffects_p_h__
define __windows2Egraphics2Eeffects_p_h__

ifndef SPECIFIC_API_CONTRACT_DEFINITIONS
ifndef WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION
define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
endif
ifndef WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION
define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
endif
endif
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
ifndef __windowscontracts_h__
include windowscontracts.inc
endif

.namespace ABI
.namespace Windows
.namespace Graphics
.namespace Effects

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CGraphics_CEffects_CIGraphicsEffect_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CEffects_CIGraphicsEffect_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Effects_IGraphicsEffect <"Windows.Graphics.Effects.IGraphicsEffect">
DEFINE_IIDX(IGraphicsEffect, "cb51c0ce-8fe6-4636-b202-861faa07d8f3")

.comdef IGraphicsEffect : public IInspectable
    get_Name            proc :ptr
    put_Name            proc :HSTRING
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CGraphics_CEffects_CIGraphicsEffectSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CEffects_CIGraphicsEffectSource_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Effects_IGraphicsEffectSource <"Windows.Graphics.Effects.IGraphicsEffectSource">
DEFINE_IIDX(IGraphicsEffectSource, "2d8f9ddc-4339-4eb9-9216-f9deb75658a2")

.comdef IGraphicsEffectSource : public IInspectable

   .ends

endif
endif

.endn
.endn
.endn
.endn

endif

endif
