include string.inc
include wsub.inc
include time.inc
include io.inc
include zip.inc

    .code

wsmkzipdir proc wsub, directory

    mov edx,wsub
    mov eax,__srcfile
    mov byte ptr [eax],0

    strfcat(__outfile, [edx].S_WSUB.ws_path, [edx].S_WSUB.ws_file)
    strfcat(__outpath, [edx].S_WSUB.ws_arch, directory)
    dostounix(strcat(eax, "/"))
    wzipadd(0, clock(), _A_SUBDIR)

    ret
wsmkzipdir endp

    END
