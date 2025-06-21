ifndef __AMPARSE__
define __AMPARSE__

DEFINE_GUID(IID_IAMParse, 0xc47a3420, 0x005c, 0x11d2, 0x90, 0x38, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x98)

.comdef IAMParse : public IUnknown

    GetParseTime	proc :ptr
    SetParseTime	proc :REFERENCE_TIME
    Flush		proc
   .ends

endif
