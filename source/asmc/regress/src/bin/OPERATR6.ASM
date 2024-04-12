
;--- forward references in argument of TYPEOF/SIZEOF/LENGTHOF/.SIZE/.LENGTH
;--- was a problem if the operator's result was used as divisor
;--- fixed in v2.10

    .386
    .model flat, stdcall

    .DATA

E1 = size_xarray / typeof xarray
E1 = size_xarray / sizeof xarray
E1 = size_xarray / lengthof xarray
E1 = size_xarray / SIZE xarray
E1 = size_xarray / LENGTH xarray   ;actually, LENGTH operator was ok

xarray label word
    dw 1,2
size_xarray equ $ - xarray

    END
