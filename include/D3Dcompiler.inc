ifndef __D3DCOMPILER_H__
__D3DCOMPILER_H__ equ <>
.pragma list(push, 0)
include d3d11shader.inc

.pragma comment(lib, d3dcompiler_47)

D3DCOMPILER_DLL_W       equ <L"d3dcompiler_47.dll">
D3DCOMPILER_DLL_A       equ <"d3dcompiler_47.dll">

D3DCOMPILE_DEBUG        equ 0x00000001
D3DCOMPILE_SKIP_VALIDATION equ 0x00000002
D3DCOMPILE_SKIP_OPTIMIZATION equ 0x00000004
D3DCOMPILE_PACK_MATRIX_ROW_MAJOR equ 0x00000008
D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR equ 0x00000010
D3DCOMPILE_PARTIAL_PRECISION equ 0x00000020
D3DCOMPILE_FORCE_VS_SOFTWARE_NO_OPT equ 0x00000040
D3DCOMPILE_FORCE_PS_SOFTWARE_NO_OPT equ 0x00000080
D3DCOMPILE_NO_PRESHADER equ 0x00000100
D3DCOMPILE_AVOID_FLOW_CONTROL equ 0x00000200
D3DCOMPILE_PREFER_FLOW_CONTROL equ 0x00000400
D3DCOMPILE_ENABLE_STRICTNESS equ 0x00000800
D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY equ 0x00001000
D3DCOMPILE_IEEE_STRICTNESS equ 0x00002000
D3DCOMPILE_OPTIMIZATION_LEVEL0 equ 0x00004000
D3DCOMPILE_OPTIMIZATION_LEVEL1 equ 0x00000000
D3DCOMPILE_OPTIMIZATION_LEVEL2 equ 0x0000c000
D3DCOMPILE_OPTIMIZATION_LEVEL3 equ 0x00008000
D3DCOMPILE_RESERVED16   equ 0x00010000
D3DCOMPILE_RESERVED17   equ 0x00020000
D3DCOMPILE_WARNINGS_ARE_ERRORS equ 0x00040000
D3DCOMPILE_RESOURCES_MAY_ALIAS equ 0x00080000

D3D_DISASM_ENABLE_COLOR_CODE equ 0x00000001
D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS equ 0x00000002
D3D_DISASM_ENABLE_INSTRUCTION_NUMBERING equ 0x00000004
D3D_DISASM_ENABLE_INSTRUCTION_CYCLE equ 0x00000008
D3D_DISASM_DISABLE_DEBUG_INFO equ 0x00000010

;HRESULT
D3DCompileFromFile proto WINAPI \
             pFileName: LPCWSTR,
              pDefines: ptr D3D_SHADER_MACRO,
              pInclude: ptr ID3DInclude,
           pEntrypoint: LPCSTR,
               pTarget: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                ppCode: ptr ID3DBlob,
           ppErrorMsgs: ptr ID3DBlob

;HRESULT
D3DCompile proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
              filename: ptr char,
               defines: ptr D3D_SHADER_MACRO,
              _include: ptr ID3DInclude,
            entrypoint: ptr char,
                target: ptr char,
                sflags: UINT,
                eflags: UINT,
                shader: ptr ID3DBlob,
        error_messages: ptr ID3DBlob

CALLBACK(pD3DCompile, :ptr, :SIZE_T, :ptr, :ptr, :ptr, :ptr, :ptr, :UINT, :UINT, :ptr, :ptr)

D3DCOMPILER_STRIP_FLAGS typedef SDWORD
D3DCOMPILER_STRIP_REFLECTION_DATA equ 1
D3DCOMPILER_STRIP_DEBUG_INFO equ 2
D3DCOMPILER_STRIP_TEST_BLOBS equ 4
D3DCOMPILER_STRIP_FORCE_DWORD equ 0x7fffffff

;HRESULT
D3DStripShader proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                 flags: UINT,
                  blob: ptr ID3DBlob


D3D_BLOB_PART           typedef SDWORD
D3D_BLOB_INPUT_SIGNATURE_BLOB equ 0
D3D_BLOB_OUTPUT_SIGNATURE_BLOB equ 1
D3D_BLOB_INPUT_AND_OUTPUT_SIGNATURE_BLOB equ 2
D3D_BLOB_PATCH_CONSTANT_SIGNATURE_BLOB equ 3
D3D_BLOB_ALL_SIGNATURE_BLOB equ 4
D3D_BLOB_DEBUG_INFO     equ 5
D3D_BLOB_LEGACY_SHADER  equ 6
D3D_BLOB_XNA_PREPASS_SHADER equ 7
D3D_BLOB_XNA_SHADER     equ 8
D3D_BLOB_TEST_ALTERNATE_SHADER equ 0x8000
D3D_BLOB_TEST_COMPILE_DETAILS equ 10
D3D_BLOB_TEST_COMPILE_PERF equ 11

;HRESULT
D3DDisassemble proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                 flags: UINT,
              comments: LPSTR,
           disassembly: ptr ID3DBlob

CALLBACK(pD3DDisassemble, :ptr, :SIZE_T, :UINT, :ptr, :ptr)

D3DGetBlobPart proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                  part: D3D_BLOB_PART,
                 flags: UINT,
                  blob: ptr ID3DBlob

;HRESULT
D3DGetInputSignatureBlob proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                  blob: ptr ID3DBlob

;HRESULT
D3DGetOutputSignatureBlob proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                  blob: ptr ID3DBlob

;HRESULT
D3DGetInputAndOutputSignatureBlob proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                  blob: ptr ID3DBlob

;HRESULT
D3DGetDebugInfo proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                  blob: ptr ID3DBlob

;HRESULT
D3DReadFileToBlob proto WINAPI \
              filename: ptr WCHAR,
              contents: ptr ID3DBlob

;HRESULT
D3DWriteBlobToFile proto WINAPI \
                  blob: ptr ID3DBlob,
              filename: ptr WCHAR,
             overwrite: BOOL

;HRESULT
D3DReflect proto WINAPI \
                 _data: PVOID,
             data_size: SIZE_T,
                  riid: REFIID,
             reflector: PVOID


;HRESULT
D3DCreateBlob proto WINAPI \
             data_size: SIZE_T,
                  blob: ptr ID3DBlob


;HRESULT
D3DPreprocess proto WINAPI \
                 _data: PVOID,
                 _size: SIZE_T,
              filename: LPSTR,
               defines: ptr D3D_SHADER_MACRO,
              _include: ptr ID3DInclude,
                shader: ptr ID3DBlob,
        error_messages: ptr ID3DBlob

CALLBACK(pD3DPreprocess, :ptr, :SIZE_T, :ptr, :ptr, :ptr, :ptr, :ptr)

.pragma list(pop)
endif
