ifndef __D3D10MISC_H__
define __D3D10MISC_H__

include d3d10.inc

.enum D3D10_DRIVER_TYPE {
    D3D10_DRIVER_TYPE_HARDWARE  = 0,
    D3D10_DRIVER_TYPE_REFERENCE = 1,
    D3D10_DRIVER_TYPE_NULL      = 2,
    D3D10_DRIVER_TYPE_SOFTWARE  = 3,
    D3D10_DRIVER_TYPE_WARP      = 5,
    }

DEFINE_GUID(GUID_DeviceType, 0xd722fb4d, 0x7a68, 0x437a, 0xb2, 0x0c, 0x58, 0x04, 0xee, 0x24, 0x94, 0xa6)

D3D10CreateDevice proto WINAPI :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :UINT, :ptr
D3D10CreateDeviceAndSwapChain proto WINAPI :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :UINT, :ptr, :ptr, :ptr
D3D10CreateBlob proto WINAPI :size_t, :ptr

endif
