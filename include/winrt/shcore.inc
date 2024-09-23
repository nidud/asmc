if (NTDDI_VERSION GE NTDDI_WIN8)

include objidl.inc

CreateRandomAccessStreamOnFile proto WINAPI :PCWSTR, :DWORD, :REFIID, :ptr

.enum BSOS_OPTIONS {
    BSOS_DEFAULT = 0,
    BSOS_PREFERDESTINATIONSTREAM
    }

CreateRandomAccessStreamOverStream proto WINAPI :ptr, :BSOS_OPTIONS, :REFIID, :ptr
CreateStreamOverRandomAccessStream proto WINAPI :ptr, :REFIID, :ptr

Windows::Storage::Streams::CreateStreamOverRandomAccessStream proto \
    randomAccessStream: ptr Windows::Storage::Streams::IRandomAccessStream,
                  riid: REFIID,
                   ppv: ptr ptr {
    CreateStreamOverRandomAccessStream(randomAccessStream, riid, ppv)
    }

endif
