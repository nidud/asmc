ifndef __D3DX11ASYNC_H__
define __D3DX11ASYNC_H__

include d3dx11.inc

D3DX11CompileFromFileA proto WINAPI \
              pSrcFile: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX11ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX11CompileFromFileW proto WINAPI \
              pSrcFile: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX11ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11CompileFromFile   equ <D3DX11CompileFromFileW>
else
D3DX11CompileFromFile   equ <D3DX11CompileFromFileA>
endif

D3DX11CompileFromResourceA proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCSTR,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX11ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX11CompileFromResourceW proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCWSTR,
          pSrcFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX11ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11CompileFromResource equ <D3DX11CompileFromResourceW>
else
D3DX11CompileFromResource equ <D3DX11CompileFromResourceA>
endif

D3DX11CompileFromMemory proto WINAPI \
              pSrcData: LPCSTR,
            SrcDataLen: SIZE_T,
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX11ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX11PreprocessShaderFromFileA proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX11ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX11PreprocessShaderFromFileW proto WINAPI \
             pFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX11ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX11PreprocessShaderFromMemory proto WINAPI \
              pSrcData: LPCSTR,
           SrcDataSize: SIZE_T,
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX11ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX11PreprocessShaderFromResourceA proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCSTR,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX11ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX11PreprocessShaderFromResourceW proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCWSTR,
          pSrcFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX11ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11PreprocessShaderFromFile equ <D3DX11PreprocessShaderFromFileW>
D3DX11PreprocessShaderFromResource equ <D3DX11PreprocessShaderFromResourceW>
else
D3DX11PreprocessShaderFromFile equ <D3DX11PreprocessShaderFromFileA>
D3DX11PreprocessShaderFromResource equ <D3DX11PreprocessShaderFromResourceA>
endif

D3DX11CreateAsyncCompilerProcessor proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
      ppCompiledShader: ptr ID3D10Blob,
         ppErrorBuffer: ptr ID3D10Blob,
           ppProcessor: ptr ID3DX11DataProcessor

D3DX11CreateAsyncShaderPreprocessProcessor proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
          ppShaderText: ptr ptr ID3D10Blob,
         ppErrorBuffer: ptr ID3D10Blob,
           ppProcessor: ptr ID3DX11DataProcessor


D3DX11CreateAsyncFileLoaderW proto WINAPI \
             pFileName: LPCWSTR,
          ppDataLoader: ptr ID3DX11DataLoader

D3DX11CreateAsyncFileLoaderA proto WINAPI \
             pFileName: LPCSTR,
          ppDataLoader: ptr ID3DX11DataLoader

D3DX11CreateAsyncMemoryLoader proto WINAPI \
                 pData: LPCVOID,
                cbData: SIZE_T,
          ppDataLoader: ptr ID3DX11DataLoader

D3DX11CreateAsyncResourceLoaderW proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCWSTR,
          ppDataLoader: ptr ID3DX11DataLoader

D3DX11CreateAsyncResourceLoaderA proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCSTR,
          ppDataLoader: ptr ID3DX11DataLoader


ifdef _UNICODE
D3DX11CreateAsyncFileLoader equ <D3DX11CreateAsyncFileLoaderW>
D3DX11CreateAsyncResourceLoader equ <D3DX11CreateAsyncResourceLoaderW>
else
D3DX11CreateAsyncFileLoader equ <D3DX11CreateAsyncFileLoaderA>
D3DX11CreateAsyncResourceLoader equ <D3DX11CreateAsyncResourceLoaderA>
endif

D3DX11CreateAsyncTextureProcessor proto WINAPI \
               pDevice: ptr ID3D11Device,
             pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
       ppDataProcessor: ptr ID3DX11DataProcessor

D3DX11CreateAsyncTextureInfoProcessor proto WINAPI \
            pImageInfo: ptr D3DX11_IMAGE_INFO,
       ppDataProcessor: ptr ID3DX11DataProcessor

D3DX11CreateAsyncShaderResourceViewProcessor proto WINAPI \
               pDevice: ptr ID3D11Device,
             pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
       ppDataProcessor: ptr ID3DX11DataProcessor

endif
