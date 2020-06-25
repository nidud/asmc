ifndef __ICONFIG_INC
__ICONFIG_INC equ <>

include crtdefs.inc

C_BASE          equ 0x01
C_SECTION       equ 0x02
C_ENTRY         equ 0x04
C_COMMENT       equ 0x08

config_t        typedef ptr IConfig

.class IConfig

    name        string_t ?
    next        config_t ?
    list        intptr_t ?
    type        uint_t ?

    IConfig     proc
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
