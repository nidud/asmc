ifndef _IVEC_H_INCLUDED
define _IVEC_H_INCLUDED

include mmintrin.inc

if defined(_M_IX86)

.template M64
    vec __m64 <>
    .ends


.template I64vec1 : public M64
    .ends

.template I32vec2 : public M64

    cmpeq           proc :ptr
    cmpneq          proc :ptr
    unpack_low      proc :ptr
    unpack_high     proc :ptr

    .ends

.template Is32vec2 : public I32vec2

    cmpgt           proc :ptr
    cmplt           proc :ptr
    cmple           proc :ptr
    cmpge           proc :ptr

    .ends

.template Iu32vec2 : public I32vec2
    .ends

.template I16vec4 : public M64

    operator_mul    proc :ptr

    .ends

.template Is16vec4 : public I16vec4

    cmpeq           proc :ptr
    cmpneq          proc :ptr
    cmpgt           proc :ptr
    cmplt           proc :ptr
    cmple           proc :ptr
    cmpge           proc :ptr
    unpack_low      proc :ptr
    unpack_high     proc :ptr

    sat_add         proc :ptr
    sat_sub         proc :ptr
    mul_high        proc :ptr
    mul_add         proc :ptr

    .ends


.template Iu16vec4 : public I16vec4

    cmpeq           proc :ptr
    cmpneq          proc :ptr
    sat_add         proc :ptr
    sat_sub         proc :ptr
    unpack_low      proc :ptr
    unpack_high     proc :ptr

    .ends


.template I8vec8 : public M64

    cmpeq           proc :ptr
    cmpneq          proc :ptr

    unpack_low      proc :ptr
    unpack_high     proc :ptr

    .ends


.template Is8vec8 : public I8vec8

    cmpgt           proc :ptr
    cmplt           proc :ptr
    cmple           proc :ptr
    cmpge           proc :ptr
    sat_add         proc :ptr
    sat_sub         proc :ptr

    .ends


.template Iu8vec8 : public I8vec8

    sat_add         proc :ptr
    sat_sub         proc :ptr
    pack_sat        proc :ptr
    packu_sat       proc :ptr

    .ends

endif ;; defined(_M_IX86)
endif ;; _IVEC_H_INCLUDED
