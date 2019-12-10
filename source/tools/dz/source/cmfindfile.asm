; CMSEARCH.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include FileSearch.inc

    .code

FindFile proc directory:string_t

    .new this:ptr FileSearch(directory)

    .return .if !eax

    this.Modal()
    this.Release()

    mov eax,1
    ret

FindFile endp

cmsearch proc

    FindFile(&findfilepath)
    ret

cmsearch endp

    end
