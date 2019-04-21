ifndef __AMPARSE__
__AMPARSE__ equ <>
.pragma list(push, 0)

DEFINE_GUID(IID_IAMParse, 0xc47a3420, 0x005c, 0x11d2, 0x90, 0x38, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x98)

.comdef IAMParse

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetParseTime	proc :ptr REFERENCE_TIME
    SetParseTime	proc :REFERENCE_TIME
    Flush		proc
    .ends

.pragma list(pop)
endif

