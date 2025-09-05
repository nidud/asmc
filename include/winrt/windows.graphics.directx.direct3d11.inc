ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Egraphics2Edirectx2Edirect3d11_h__
define __windows2Egraphics2Edirectx2Edirect3d11_h__
ifndef __windows2Egraphics2Edirectx2Edirect3d11_p_h__
define __windows2Egraphics2Edirectx2Edirect3d11_p_h__


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
include Windows.Graphics.DirectX.inc

.namespace Windows
.namespace Graphics
.namespace DirectX
.namespace Direct3D11

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
.enum Direct3DBindings : uint_t {
    Direct3DBindings_VertexBuffer = 0x1,
    Direct3DBindings_IndexBuffer = 0x2,
    Direct3DBindings_ConstantBuffer = 0x4,
    Direct3DBindings_ShaderResource = 0x8,
    Direct3DBindings_StreamOutput = 0x10,
    Direct3DBindings_RenderTarget = 0x20,
    Direct3DBindings_DepthStencil = 0x40,
    Direct3DBindings_UnorderedAccess = 0x80,
    Direct3DBindings_Decoder = 0x200,
    Direct3DBindings_VideoEncoder = 0x400,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
.enum Direct3DUsage {
    Direct3DUsage_Default = 0,
    Direct3DUsage_Immutable = 1,
    Direct3DUsage_Dynamic = 2,
    Direct3DUsage_Staging = 3,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
.template Direct3DMultisampleDescription
    Count                   INT32 ?
    Quality                 INT32 ?
   .ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
.template Direct3DSurfaceDescription
    Width                   INT32 ?
    Height                  INT32 ?
    Format                  Windows::Graphics::DirectX::DirectXPixelFormat ?
    MultisampleDescription  Windows::Graphics::DirectX::Direct3D11::Direct3DMultisampleDescription <>
   .ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_DirectX_Direct3D11_IDirect3DDevice <"Windows.Graphics.DirectX.Direct3D11.IDirect3DDevice">
DEFINE_IIDX(IDirect3DDevice, "a37624ab-8d5f-4650-9d3e-9eae3d9bc670")

.comdef IDirect3DDevice : public IInspectable
    Trim                proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_DirectX_Direct3D11_IDirect3DSurface <"Windows.Graphics.DirectX.Direct3D11.IDirect3DSurface">
DEFINE_IIDX(IDirect3DSurface, "0bf4a146-13c1-4694-bee3-7abf15eaf586")

.comdef IDirect3DSurface : public IInspectable
    get_Description     proc :ptr
   .ends
endif
endif

.endn
.endn
.endn
.endn

endif

endif
