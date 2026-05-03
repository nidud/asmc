ifndef __THREADLOCALEINFO_INC
define __THREADLOCALEINFO_INC

.pragma pack(push, size_t)

ifndef LPSHORT
LPSHORT typedef ptr sword
endif
ifndef LPINT
LPINT   typedef ptr sdword
endif

ifndef _THREADLOCALEINFO
define _THREADLOCALEINFO

.template locrefcount
    locale          LPSTR ?
    wlocale         LPWSTR ?
    refcount        LPINT ?
    wrefcount       LPINT ?
   .ends

.template threadlocinfo
    refcount        SINT ?
    lc_codepage     UINT ?
    lc_collate_cp   UINT ?
    lc_time_cp      UINT ?
    lc_category     locrefcount 6 dup(<>)
    lc_clike        SINT ?
    mb_cur_max      SINT ?
    lconv_intl_refcount LPINT ?
    lconv_num_refcount  LPINT ?
    lconv_mon_refcount  LPINT ?
    lconvp          PVOID ?
    ctype1_refcount LPINT ?
    ctype1          LPSHORT ?
    pctype          LPSHORT ?
    pclmap          LPSTR ?
    pcumap          LPSTR ?
    lc_time_curr    PVOID ?
    locale_name     LPWSTR 6 dup(?)
   .ends
    pthreadlocinfo  typedef ptr threadlocinfo

endif

ifndef _THREADMBCINFO
define _THREADMBCINFO

.template threadmbcinfo
    refcount        int_t ?
    mbcodepage      int_t ?
    ismbcodepage    int_t ?
    mbulinfo        dw 6 dup(?)
    mbctype         db 257 dup(?)
    mbcasemap       db 256 dup(?)
    mblocalename    wstring_t ?
   .ends
    pthreadmbcinfo  typedef ptr threadmbcinfo
endif

ifndef _locale_t

.template _locale_tstruct
    locinfo         pthreadlocinfo ?
    mbcinfo         pthreadmbcinfo ?
   .ends
   _locale_t        typedef ptr _locale_tstruct
endif

.pragma pack(pop)

endif
