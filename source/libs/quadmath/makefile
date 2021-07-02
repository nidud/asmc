!include srcpath

flags = -nologo -nolib
win32 = $(lib_dir)\quadmath.lib
win64 = $(lib_dir)\x64\quadmath.lib
elf32 = $(lib_dir)\elf\quadmath.lib

all: $(win32) $(win64) $(elf32)

base32 = \
    $(src_dir)\libs\lib32\quadmath\__cvtq_h.asm \
    $(src_dir)\libs\lib32\quadmath\__cvtq_ss.asm \
    $(src_dir)\libs\lib32\quadmath\__cvtq_sd.asm \
    $(src_dir)\libs\lib32\quadmath\__cvtq_ld.asm \
    $(src_dir)\libs\lib32\quadmath\__cvth_q.asm \
    $(src_dir)\libs\lib32\quadmath\__cvtss_q.asm \
    $(src_dir)\libs\lib32\quadmath\__cvtsd_q.asm \
    $(src_dir)\libs\lib32\quadmath\__cvtld_q.asm \
    $(src_dir)\libs\lib32\quadmath\__cvta_q.asm \
    $(src_dir)\libs\lib32\quadmath\__mulq.asm \
    $(src_dir)\libs\lib32\quadmath\__divq.asm \
    $(src_dir)\libs\lib32\quadmath\__addq.asm \
    $(src_dir)\libs\lib32\quadmath\__subq.asm \
    $(src_dir)\libs\lib32\quadmath\__cmpq.asm \
    $(src_dir)\libs\lib32\quadmath\__addo.asm \
    $(src_dir)\libs\lib32\quadmath\__mulo.asm \
    $(src_dir)\libs\lib32\quadmath\__divo.asm \
    $(src_dir)\libs\lib32\quadmath\__shlo.asm \
    $(src_dir)\libs\lib32\quadmath\__shro.asm \
    $(src_dir)\libs\lib32\quadmath\__saro.asm \
    $(src_dir)\libs\lib32\quadmath\__subo.asm \
    $(src_dir)\libs\lib32\fltintrn\_flttostr.asm \
    $(src_dir)\libs\lib32\fltintrn\_strtoflt.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltunpack.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltscale.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltadd.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltmul.asm \
    $(src_dir)\libs\lib32\fltintrn\_flttoi64.asm \
    $(src_dir)\libs\lib32\fltintrn\_i64toflt.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltpowtable.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltpackfp.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltdiv.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltsetflags.asm \
    $(src_dir)\libs\lib32\fltintrn\_destoflt.asm \
    $(src_dir)\libs\lib32\fltintrn\_fltround.asm

base64 = \
    $(src_dir)\libs\lib64\quadmath\__cvtq_h.asm \
    $(src_dir)\libs\lib64\quadmath\__cvtq_ss.asm \
    $(src_dir)\libs\lib64\quadmath\__cvtq_sd.asm \
    $(src_dir)\libs\lib64\quadmath\__cvtq_ld.asm \
    $(src_dir)\libs\lib64\quadmath\__cvth_q.asm \
    $(src_dir)\libs\lib64\quadmath\__cvtss_q.asm \
    $(src_dir)\libs\lib64\quadmath\__cvtsd_q.asm \
    $(src_dir)\libs\lib64\quadmath\__cvtld_q.asm \
    $(src_dir)\libs\lib64\quadmath\__cvta_q.asm \
    $(src_dir)\libs\lib64\quadmath\__mulq.asm \
    $(src_dir)\libs\lib64\quadmath\__divq.asm \
    $(src_dir)\libs\lib64\quadmath\__addq.asm \
    $(src_dir)\libs\lib64\quadmath\__subq.asm \
    $(src_dir)\libs\lib64\quadmath\__cmpq.asm \
    $(src_dir)\libs\lib64\quadmath\__addo.asm \
    $(src_dir)\libs\lib64\quadmath\__subo.asm \
    $(src_dir)\libs\lib64\quadmath\__mulo.asm \
    $(src_dir)\libs\lib64\quadmath\__divo.asm \
    $(src_dir)\libs\lib64\quadmath\__shlo.asm \
    $(src_dir)\libs\lib64\quadmath\__shro.asm \
    $(src_dir)\libs\lib64\quadmath\__saro.asm \
    $(src_dir)\libs\lib64\fltintrn\_flttostr.asm \
    $(src_dir)\libs\lib64\fltintrn\_strtoflt.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltunpack.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltscale.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltadd.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltmul.asm \
    $(src_dir)\libs\lib64\fltintrn\_flttoi64.asm \
    $(src_dir)\libs\lib64\fltintrn\_i64toflt.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltpowtable.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltpackfp.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltdiv.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltsetflags.asm \
    $(src_dir)\libs\lib64\fltintrn\_destoflt.asm \
    $(src_dir)\libs\lib64\fltintrn\_fltround.asm

$(win32):
    asmc $(flags) -Cs -coff -safeseh -Zi $(base32)
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(elf32):
    if not exist $(lib_dir)\elf md $(lib_dir)\elf
    asmc -nologo -elf -nolib $(base32)
    libw -q -b -n -c -ie $@ *.obj
    del *.obj

$(win64):
    asmc $(flags) -Cs -win64 $(base64)
    libw -q -b -n -c -fac $@ *.obj
    del *.obj
