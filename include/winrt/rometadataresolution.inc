
;include cor.inc
if (NTDDI_VERSION GE NTDDI_WIN8)
RoGetMetaDataFile proto WINAPI :HSTRING, :ptr, :ptr, :ptr, :ptr
RoParseTypeName proto WINAPI :HSTRING, :ptr, :ptr
RoResolveNamespace proto WINAPI :HSTRING, :HSTRING, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr
endif
