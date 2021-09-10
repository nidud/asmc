include amsi.inc

.class CAmsiStreamBase : public IAmsiStream

    m_contentSize       ULONGLONG ?
    m_contentName       PWSTR ?
    m_fileHandle        HANDLE ?

    CAmsiStreamBase     proc
    SetContentName      proc :PWSTR
    BaseGetAttribute    proc :AMSI_ATTRIBUTE, :ULONG, :PBYTE, :ptr ULONG
    CopyAttribute       proc :ptr, :size_t, :ULONG, :PBYTE, :ptr ULONG
   .ends

.class CAmsiFileStream : public CAmsiStreamBase

    CAmsiFileStream     proc :LPCWSTR
   .ends

.class CAmsiMemoryStream : public CAmsiStreamBase

    CAmsiMemoryStream   proc
   .ends

