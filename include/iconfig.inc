ifndef __ICONFIG_INC
__ICONFIG_INC equ <>

include crtdefs.inc

_I_BASE         equ 0x01
_I_SECTION      equ 0x02
_I_ENTRY        equ 0x04
_I_COMMENT      equ 0x08

config_t        typedef ptr IConfig

.class IConfig

    Flags       uint_t ?
    Name        string_t ?
    Next        config_t ?
    List        intptr_t ?

    Release     proc
    Read        proc :string_t
    Write       proc :string_t
    Find        proc :string_t
    GetEntry    proc :string_t, :string_t
    Create      proc :string_t, :vararg
    Delete      proc :string_t
    Unlink      proc :config_t

    .ends

endif
