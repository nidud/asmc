ifndef __D3D10MISC_H__
__D3D10MISC_H__ equ <>

include d3d10.inc

DEFINE_GUID(IID_ID3D10Blob, 0x8ba5fb08, 0x5195, 0x40e2, 0xac, 0x58, 0xd, 0x98, 0x9c, 0x3a, 0x1, 0x2)

.comdef ID3D10Blob
    QueryInterface	proc :REFIID, :PVOID
    AddRef		proc
    Release		proc
    GetBufferPointer	proc
    GetBufferSize	proc
    .ends

D3D10_DRIVER_TYPE	typedef SDWORD
D3D10_DRIVER_TYPE_HARDWARE equ 0
D3D10_DRIVER_TYPE_REFERENCE equ 1
D3D10_DRIVER_TYPE_NULL	equ 2
D3D10_DRIVER_TYPE_SOFTWARE equ 3
D3D10_DRIVER_TYPE_WARP	equ 5

DEFINE_GUID(GUID_DeviceType, 0xd722fb4d, 0x7a68, 0x437a, 0xb2, 0x0c, 0x58, 0x04, 0xee, 0x24, 0x94, 0xa6)

;HRESULT
D3D10CreateDevice proto WINAPI \
	      pAdapter: ptr IDXGIAdapter,
	    DriverType: D3D10_DRIVER_TYPE,
	      Software: HMODULE,
		 Flags: UINT,
	    SDKVersion: UINT,
	      ppDevice: ptr ID3D10Device

;HRESULT
D3D10CreateDeviceAndSwapChain proto WINAPI \
	      pAdapter: ptr IDXGIAdapter,
	    DriverType: D3D10_DRIVER_TYPE,
	      Software: HMODULE,
		 Flags: UINT,
	    SDKVersion: UINT,
	pSwapChainDesc: ptr DXGI_SWAP_CHAIN_DESC,
	   ppSwapChain: ptr IDXGISwapChain,
	      ppDevice: ptr ID3D10Device


;HRESULT
D3D10CreateBlob proto WINAPI \
	      NumBytes: SIZE_T,
	      ppBuffer: ptr LPD3D10BLOB

endif
