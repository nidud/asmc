include d3d11.inc

ifndef __D3DX11GPGPU_H__
define __D3DX11GPGPU_H__

D3DCSX_DLL_W		equ <L"d3dcsx_47.dll">
D3DCSX_DLL_A		equ <"d3dcsx_47.dll">

ifdef _UNICODE
D3DCSX_DLL		equ <D3DCSX_DLL_W>
else
D3DCSX_DLL		equ <D3DCSX_DLL_A>
endif

.enum D3DX11_SCAN_DATA_TYPE {
    D3DX11_SCAN_DATA_TYPE_FLOAT = 1,
    D3DX11_SCAN_DATA_TYPE_INT,
    D3DX11_SCAN_DATA_TYPE_UINT,
    }

.enum D3DX11_SCAN_OPCODE {
    D3DX11_SCAN_OPCODE_ADD = 1,
    D3DX11_SCAN_OPCODE_MIN,
    D3DX11_SCAN_OPCODE_MAX,
    D3DX11_SCAN_OPCODE_MUL,
    D3DX11_SCAN_OPCODE_AND,
    D3DX11_SCAN_OPCODE_OR,
    D3DX11_SCAN_OPCODE_XOR,
    }

.enum D3DX11_SCAN_DIRECTION {
    D3DX11_SCAN_DIRECTION_FORWARD = 1,
    D3DX11_SCAN_DIRECTION_BACKWARD,
    }

DEFINE_GUID(IID_ID3DX11Scan, 0x5089b68f, 0xe71d, 0x4d38, 0xbe, 0x8e, 0xf3, 0x63, 0xb9, 0x5a, 0x94, 0x05);

.comdef ID3DX11Scan : public IUnknown

    SetScanDirection	proc :D3DX11_SCAN_DIRECTION
    Scan		proc :D3DX11_SCAN_DATA_TYPE, :D3DX11_SCAN_OPCODE, :UINT, :ptr ID3D11UnorderedAccessView, :ptr ID3D11UnorderedAccessView
    Multiscan		proc :D3DX11_SCAN_DATA_TYPE, :D3DX11_SCAN_OPCODE, :UINT, :UINT, :UINT, :ptr ID3D11UnorderedAccessView, :ptr ID3D11UnorderedAccessView
    .ENDS


D3DX11CreateScan proto WINAPI :ptr, :UINT, :UINT, :ptr

DEFINE_GUID(IID_ID3DX11SegmentedScan, 0xa915128c, 0xd954, 0x4c79, 0xbf, 0xe1, 0x64, 0xdb, 0x92, 0x31, 0x94, 0xd6);

.comdef ID3DX11SegmentedScan : public IUnknown

    SetScanDirection	proc :D3DX11_SCAN_DIRECTION
    SegScan		proc :D3DX11_SCAN_DATA_TYPE, :D3DX11_SCAN_OPCODE, :UINT, :ptr ID3D11UnorderedAccessView, :ptr ID3D11UnorderedAccessView, :ptr ID3D11UnorderedAccessView
    .ENDS

D3DX11CreateSegmentedScan proto WINAPI :ptr, :UINT, :ptr

D3DX11_FFT_MAX_PRECOMPUTE_BUFFERS equ 4
D3DX11_FFT_MAX_TEMP_BUFFERS equ 4
D3DX11_FFT_MAX_DIMENSIONS equ 32

DEFINE_GUID(IID_ID3DX11FFT, 0xb3f7a938, 0x4c93, 0x4310, 0xa6, 0x75, 0xb3, 0x0d, 0x6d, 0xe5, 0x05, 0x53)

.comdef ID3DX11FFT : public IUnknown

    SetForwardScale	proc :FLOAT
    GetForwardScale	proc
    SetInverseScale	proc :FLOAT
    GetInverseScale	proc
    AttachBuffersAndPrecompute proc :ptr ID3D11UnorderedAccessView, :UINT, :ptr ID3D11UnorderedAccessView
    ForwardTransform	proc :ID3D11UnorderedAccessView, :ptr ptr ID3D11UnorderedAccessView
    InverseTransform	proc :ID3D11UnorderedAccessView, :ptr ptr ID3D11UnorderedAccessView
    .ENDS

.enum D3DX11_FFT_DATA_TYPE {
    D3DX11_FFT_DATA_TYPE_REAL,
    D3DX11_FFT_DATA_TYPE_COMPLEX,
    }

.enum D3DX11_FFT_DIM_MASK {
    D3DX11_FFT_DIM_MASK_1D   = 0x1,
    D3DX11_FFT_DIM_MASK_2D   = 0x3,
    D3DX11_FFT_DIM_MASK_3D   = 0x7,
    }

D3DX11_FFT_DESC		STRUC
NumDimensions		UINT ?
ElementLengths		UINT D3DX11_FFT_MAX_DIMENSIONS dup(?)
DimensionMask		UINT ?
Type			D3DX11_FFT_DATA_TYPE ?
D3DX11_FFT_DESC		ENDS

D3DX11_FFT_BUFFER_INFO	STRUC
NumTempBufferSizes	UINT ?
TempBufferFloatSizes	UINT D3DX11_FFT_MAX_TEMP_BUFFERS dup(?)
NumPrecomputeBufferSizes UINT ?
PrecomputeBufferFloatSizes UINT D3DX11_FFT_MAX_PRECOMPUTE_BUFFERS dup(?)
D3DX11_FFT_BUFFER_INFO	ENDS


.enum D3DX11_FFT_CREATE_FLAG {
    D3DX11_FFT_CREATE_FLAG_NO_PRECOMPUTE_BUFFERS = 0x01,
    }

D3DX11CreateFFT proto WINAPI :ptr, :ptr, :UINT, :ptr, :ptr
D3DX11CreateFFT1DReal proto WINAPI :ptr, :UINT, :UINT, :ptr, :ptr
D3DX11CreateFFT1DComplex proto WINAPI :ptr, :UINT, :UINT, :ptr, :ptr
D3DX11CreateFFT2DReal proto WINAPI :ptr, :UINT, :UINT, :UINT, :ptr, :ptr
D3DX11CreateFFT2DComplex proto WINAPI :ptr, :UINT, :UINT, :UINT, :ptr, :ptr
D3DX11CreateFFT3DReal proto WINAPI :ptr, :UINT, :UINT, :UINT, :UINT, :ptr, :ptr
D3DX11CreateFFT3DComplex proto WINAPI :ptr, :UINT, :UINT, :UINT, :UINT, :ptr, :ptr

endif
