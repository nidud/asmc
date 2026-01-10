; REALPATH.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.code

realpath proc path:string_t, resolved_path:string_t
    _fullpath(resolved_path, ldr(path), _MAX_PATH)
    ret
    endp

    end

