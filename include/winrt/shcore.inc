if (NTDDI_VERSION GE NTDDI_WIN8)

include objidl.inc

CreateRandomAccessStreamOnFile proto WINAPI \
              filePath: PCWSTR,
            accessMode: DWORD,
                  riid: REFIID,
                   ppv: ptr

.enum BSOS_OPTIONS {
    BSOS_DEFAULT = 0,
    BSOS_PREFERDESTINATIONSTREAM
    }

CreateRandomAccessStreamOverStream proto WINAPI \
                stream: ptr IStream,
               options: BSOS_OPTIONS,
                  riid: REFIID,
                   ppv: ptr void

CreateStreamOverRandomAccessStream proto WINAPI \
    randomAccessStream: ptr IUnknown,
                  riid: REFIID,
                   ppv: ptr


Windows::Storage::Streams::CreateStreamOverRandomAccessStream proto \
    randomAccessStream: ptr Windows::Storage::Streams::IRandomAccessStream,
                  riid: REFIID,
                   ppv: ptr ptr {
    CreateStreamOverRandomAccessStream(randomAccessStream, riid, ppv)
    }

endif
