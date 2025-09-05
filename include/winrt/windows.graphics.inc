ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Egraphics_h__
define __windows2Egraphics_h__

ifndef __windows2Egraphics_p_h__
define __windows2Egraphics_p_h__

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

.namespace Windows
.namespace Graphics

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
.template DisplayAdapterId
    LowPart	UINT32 ?
    HighPart	INT32 ?
   .ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
.template DisplayId
    Value	UINT64 ?
   .ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
.template PointInt32
    X		INT32 ?
    Y		INT32 ?
   .ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
.template RectInt32
    X		INT32 ?
    Y		INT32 ?
    Width	INT32 ?
    Height	INT32 ?
   .ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
.template SizeInt32
    Width	INT32 ?
    Height	INT32 ?
   .ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CIGeometrySource2D_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CIGeometrySource2D_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_IGeometrySource2D <"Windows.Graphics.IGeometrySource2D">
DEFINE_IIDX(IGeometrySource2D, "caff7902-670c-4181-a624-da977203b845")

.comdef IGeometrySource2D : public IInspectable

   .ends

endif
endif

.endn
.endn

endif

endif
