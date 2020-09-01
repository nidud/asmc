include internal_shared.inc
include Windows.inc

public _tls_index
public _tls_start
public _tls_end
public __xl_a
public __xl_z

option dotname

.data
_tls_index ULONG 0

.tls SEGMENT ALIGN(8) 'CONST'
_tls_start char_t 0
.tls ENDS

.tls$ZZZ SEGMENT ALIGN(8) 'CONST'
_tls_end char_t 0
.tls$ZZZ ENDS

.CRT$XLA SEGMENT ALIGN(8) 'CONST'
__xl_a PIMAGE_TLS_CALLBACK 0
.CRT$XLA ENDS
.CRT$XLZ SEGMENT ALIGN(8) 'CONST'
__xl_z PIMAGE_TLS_CALLBACK 0
.CRT$XLZ ENDS

.rdata$T SEGMENT ALIGN(8) 'CONST'
_tls_used IMAGE_TLS_DIRECTORY64 { _tls_start, _tls_end, _tls_index, __xl_a+8, 0, 0 }
.rdata$T ENDS

    end
