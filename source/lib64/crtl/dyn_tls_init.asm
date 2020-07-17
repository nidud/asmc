include Windows.inc

    .data
     __dyn_tls_init_callback PIMAGE_TLS_CALLBACK 0

    .code

__scrt_get_dyn_tls_init_callback proc

    lea rax,__dyn_tls_init_callback
    ret

__scrt_get_dyn_tls_init_callback endp

    end
