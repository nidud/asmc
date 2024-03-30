ifndef __ICONFIG_INC
define __ICONFIG_INC

.enum { C_BASE, C_SECTION, C_ENTRY }

config_t typedef ptr IConfig

.class IConfig

    type        uint_t ?
    next        config_t ?
    prev        config_t ?
    name        string_t ?
    union
     entry      config_t ?
     value      string_t ?
    ends

    IConfig     proc :string_t

    Release     proc
    Read        proc
    ReadFile    proc :string_t
    Write       proc
    Find        proc :string_t
    GetID       proc :int_t
    GetEntry    proc :string_t
    Append      proc :string_t, :vararg
    Remove      proc :string_t
    Clear       proc
    Update      proc
    Unlink      proc
   .ends


IConfig::IConfig    proto __cdecl :string_t
IConfig::Release    proto __cdecl
IConfig::Read       proto __cdecl
IConfig::ReadFile   proto __cdecl :string_t
IConfig::Write      proto __cdecl
IConfig::Find       proto __cdecl :string_t
IConfig::FindID     proto __cdecl :int_t
IConfig::Append     proto __cdecl :string_t, :vararg
IConfig::Remove     proto __cdecl :string_t
IConfig::Clear      proto __cdecl
IConfig::Update     proto __cdecl
IConfig::Unlink     proto __cdecl

endif
