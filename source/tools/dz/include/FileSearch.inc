; FILESEARCH.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

FFMAXHIT equ 9999

.class FileSearch directory:string_t

    dialog      ptr_t ?
    basedir     string_t ?
    cursor      S_CURSOR <>
    ll          S_LOBJ <>
    oldff       ptr_t ?
    oldhelp     ptr_t ?

    Release     proc
    WndProc     proc :uint_t
    Find        proc
    Modal       proc
    PutCellId   proc
    UpdateCell  proc
    CurItem     proc
    CurFile     proc
    List        proc
    ClearList   proc
    SearchPath  proc directory:string_t

    .ends
