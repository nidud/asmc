ifndef __D3DX10ASYNC_H__
__D3DX10ASYNC_H__ equ <>

include d3dx10.inc

D3DX10CompileFromFileA proto WINAPI \
              pSrcFile: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX10ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10CompileFromFileW proto WINAPI \
              pSrcFile: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX10ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT


ifdef _UNICODE
D3DX10CompileFromFile   equ <D3DX10CompileFromFileW>
else
D3DX10CompileFromFile   equ <D3DX10CompileFromFileA>
endif

D3DX10CompileFromResourceA proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCSTR,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX10ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT


D3DX10CompileFromResourceW proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCWSTR,
          pSrcFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX10ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

ifdef _UNICODE
D3DX10CompileFromResource equ <D3DX10CompileFromResourceW>
else
D3DX10CompileFromResource equ <D3DX10CompileFromResourceA>
endif

D3DX10CompileFromMemory proto WINAPI \
              pSrcData: LPCSTR,
            SrcDataLen: SIZE_T,
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
                 pPump: ptr ID3DX10ThreadPump,
              ppShader: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT


D3DX10CreateEffectFromFileA proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
           pEffectPool: ptr ID3D10EffectPool,
                 pPump: ptr ID3DX10ThreadPump,
              ppEffect: ptr ID3D10Effect,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10CreateEffectFromFileW proto WINAPI \
             pFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
           pEffectPool: ptr ID3D10EffectPool,
                 pPump: ptr ID3DX10ThreadPump,
              ppEffect: ptr ID3D10Effect,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10CreateEffectFromMemory proto WINAPI \
                 pData: LPCVOID,
            DataLength: SIZE_T,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
           pEffectPool: ptr ID3D10EffectPool,
                 pPump: ptr ID3DX10ThreadPump,
              ppEffect: ptr ID3D10Effect,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10CreateEffectFromResourceA proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCSTR,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
           pEffectPool: ptr ID3D10EffectPool,
                 pPump: ptr ID3DX10ThreadPump,
              ppEffect: ptr ID3D10Effect,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10CreateEffectFromResourceW proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCWSTR,
          pSrcFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
           pEffectPool: ptr ID3D10EffectPool,
                 pPump: ptr ID3DX10ThreadPump,
              ppEffect: ptr ID3D10Effect,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT



ifdef _UNICODE
D3DX10CreateEffectFromFile equ <D3DX10CreateEffectFromFileW>
D3DX10CreateEffectFromResource equ <D3DX10CreateEffectFromResourceW>
else
D3DX10CreateEffectFromFile equ <D3DX10CreateEffectFromFileA>
D3DX10CreateEffectFromResource equ <D3DX10CreateEffectFromResourceA>
endif

D3DX10CreateEffectPoolFromFileA proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
                 pPump: ptr ID3DX10ThreadPump,
          ppEffectPool: ptr ID3D10EffectPool,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT


D3DX10CreateEffectPoolFromFileW proto WINAPI \
             pFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
                 pPump: ptr ID3DX10ThreadPump,
          ppEffectPool: ptr ID3D10EffectPool,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10CreateEffectPoolFromMemory proto WINAPI \
                 pData: LPCVOID,
            DataLength: SIZE_T,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
                 pPump: ptr ID3DX10ThreadPump,
          ppEffectPool: ptr ID3D10EffectPool,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT


D3DX10CreateEffectPoolFromResourceA proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCSTR,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
                 pPump: ptr ID3DX10ThreadPump,
          ppEffectPool: ptr ID3D10EffectPool,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT


D3DX10CreateEffectPoolFromResourceW proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCWSTR,
          pSrcFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr ID3D10Include,
              pProfile: LPCSTR,
             HLSLFlags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
                 pPump: ptr ID3DX10ThreadPump,
          ppEffectPool: ptr ID3D10EffectPool,
              ppErrors: ptr ID3D10Blob,
              pHResult: ptr HRESULT


ifdef _UNICODE
D3DX10CreateEffectPoolFromFile equ <D3DX10CreateEffectPoolFromFileW>
D3DX10CreateEffectPoolFromResource equ <D3DX10CreateEffectPoolFromResourceW>
else
D3DX10CreateEffectPoolFromFile equ <D3DX10CreateEffectPoolFromFileA>
D3DX10CreateEffectPoolFromResource equ <D3DX10CreateEffectPoolFromResourceA>
endif

D3DX10PreprocessShaderFromFileA proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX10ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10PreprocessShaderFromFileW proto WINAPI \
             pFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX10ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10PreprocessShaderFromMemory proto WINAPI \
              pSrcData: LPCSTR,
           SrcDataSize: SIZE_T,
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX10ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10PreprocessShaderFromResourceA proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCSTR,
          pSrcFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX10ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT

D3DX10PreprocessShaderFromResourceW proto WINAPI \
               hModule: HMODULE,
         pResourceName: LPCWSTR,
          pSrcFileName: LPCWSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
                 pPump: ptr ID3DX10ThreadPump,
          ppShaderText: ptr ptr ID3D10Blob,
           ppErrorMsgs: ptr ptr ID3D10Blob,
              pHResult: ptr HRESULT


ifdef _UNICODE
D3DX10PreprocessShaderFromFile equ <D3DX10PreprocessShaderFromFileW>
D3DX10PreprocessShaderFromResource equ <D3DX10PreprocessShaderFromResourceW>
else
D3DX10PreprocessShaderFromFile equ <D3DX10PreprocessShaderFromFileA>
D3DX10PreprocessShaderFromResource equ <D3DX10PreprocessShaderFromResourceA>
endif


D3DX10CreateAsyncCompilerProcessor proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
         pFunctionName: LPCSTR,
              pProfile: LPCSTR,
                Flags1: UINT,
                Flags2: UINT,
      ppCompiledShader: ptr ID3D10Blob,
         ppErrorBuffer: ptr ID3D10Blob,
           ppProcessor: ptr ID3DX10DataProcessor


D3DX10CreateAsyncEffectCreateProcessor proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
              pProfile: LPCSTR,
                 Flags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
                 pPool: ptr ID3D10EffectPool,
         ppErrorBuffer: ptr ID3D10Blob,
           ppProcessor: ptr ID3DX10DataProcessor


D3DX10CreateAsyncEffectPoolCreateProcessor proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
              pProfile: LPCSTR,
                 Flags: UINT,
               FXFlags: UINT,
               pDevice: ptr ID3D10Device,
         ppErrorBuffer: ptr ID3D10Blob,
           ppProcessor: ptr ID3DX10DataProcessor


D3DX10CreateAsyncShaderPreprocessProcessor proto WINAPI \
             pFileName: LPCSTR,
              pDefines: ptr D3D10_SHADER_MACRO,
              pInclude: ptr D3D10INCLUDE,
          ppShaderText: ptr ptr ID3D10Blob,
         ppErrorBuffer: ptr ID3D10Blob,
           ppProcessor: ptr ID3DX10DataProcessor


D3DX10CreateAsyncFileLoaderW proto WINAPI \
             pFileName: LPCWSTR,
          ppDataLoader: ptr ID3DX10DataLoader

D3DX10CreateAsyncFileLoaderA proto WINAPI \
             pFileName: LPCSTR,
          ppDataLoader: ptr ID3DX10DataLoader

D3DX10CreateAsyncMemoryLoader proto WINAPI \
                 pData: LPCVOID,
                cbData: SIZE_T,
          ppDataLoader: ptr ID3DX10DataLoader

D3DX10CreateAsyncResourceLoaderW proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCWSTR,
          ppDataLoader: ptr ID3DX10DataLoader

D3DX10CreateAsyncResourceLoaderA proto WINAPI \
            hSrcModule: HMODULE,
          pSrcResource: LPCSTR,
          ppDataLoader: ptr ID3DX10DataLoader


ifdef _UNICODE
D3DX10CreateAsyncFileLoader equ <D3DX10CreateAsyncFileLoaderW>
D3DX10CreateAsyncResourceLoader equ <D3DX10CreateAsyncResourceLoaderW>
else
D3DX10CreateAsyncFileLoader equ <D3DX10CreateAsyncFileLoaderA>
D3DX10CreateAsyncResourceLoader equ <D3DX10CreateAsyncResourceLoaderA>
endif

D3DX10CreateAsyncTextureProcessor proto WINAPI \
               pDevice: ptr ID3D10Device,
             pLoadInfo: ptr D3DX10_IMAGE_LOAD_INFO,
       ppDataProcessor: ptr ID3DX10DataProcessor

D3DX10CreateAsyncTextureInfoProcessor proto WINAPI \
            pImageInfo: ptr D3DX10_IMAGE_INFO,
       ppDataProcessor: ptr ID3DX10DataProcessor

D3DX10CreateAsyncShaderResourceViewProcessor proto WINAPI \
               pDevice: ptr ID3D10Device,
             pLoadInfo: ptr D3DX10_IMAGE_LOAD_INFO,
       ppDataProcessor: ptr ID3DX10DataProcessor


endif
