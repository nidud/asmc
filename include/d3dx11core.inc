include d3dx11.inc

ifndef __D3DX11CORE_H__
__D3DX11CORE_H__ equ <>

D3DX11_DLL_W		equ <L"d3dx11_43.dll">
D3DX11_DLL_A		equ <"d3dx11_43.dll">

ifdef _UNICODE
D3DX11_DLL		equ <D3DX11_DLL_W>
else
D3DX11_DLL		equ <D3DX11_DLL_A>
endif

D3DX11_SDK_VERSION	equ 43

ifdef D3D_DIAG_DLL
D3DX11DebugMute proto WINAPI \
		  Mute: BOOL
endif

D3DX11CheckVersion proto WINAPI \
	 D3DSdkVersion: UINT,
      D3DX11SdkVersion: UINT


.comdef ID3DX11DataLoader

    Load		proc
    Decompress		proc :ptr ptr, :ptr SIZE_T
    Destroy		proc
    .ENDS

.comdef ID3DX11DataProcessor

    Process		proc :ptr, :SIZE_T
    CreateDeviceObject	proc :ptr ptr
    Destroy		proc
    .ENDS

DEFINE_GUID(IID_ID3DX11ThreadPump, 0xc93fecfa, 0x6967, 0x478a, 0xab, 0xbc, 0x40, 0x2d, 0x90, 0x62, 0x1f, 0xcb);

.comdef ID3DX11ThreadPump : public IUnknown

    AddWorkItem		proc :ptr ID3DX11DataLoader, :ptr ID3DX11DataProcessor, :ptr HRESULT, :ptr ptr
    GetWorkItemCount	proc
    WaitForAllItems	proc
    ProcessDeviceWorkItems proc :UINT
    PurgeAllItems	proc
    GetQueueStatus	proc :ptr UINT, :ptr UINT, :ptr UINT
    .ENDS

D3DX11CreateThreadPump proto WINAPI \
	    cIoThreads: UINT,
	  cProcThreads: UINT,
	  ppThreadPump: ptr ID3DX11ThreadPump

D3DX11UnsetAllDeviceObjects proto WINAPI \
	      pContext: ptr ID3D11DeviceContext


_FACD3D equ 0x876
MAKE_D3DHRESULT macro code
	exitm<MAKE_HRESULT( 1, _FACD3D, code )>
	endm
MAKE_D3DSTATUS macro code
	exitm<MAKE_HRESULT( 0, _FACD3D, code )>
	endm

D3DERR_INVALIDCALL	equ MAKE_D3DHRESULT(2156)
D3DERR_WASSTILLDRAWING	equ MAKE_D3DHRESULT(540)

endif
