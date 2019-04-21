
; set the local path and use guidgen.exe to create the two GUIDs below.
; then remove this..
.err <GUIDs not created -- see locals.inc>

dll_path    equ <"D:\\Asmc\\source\\test\\comdll\\IConfig.dll">
dll_clsid   equ <"{09BE7B0C-2275-474D-9405-24AAB891614F}">

DEFINE_GUIDS(IID_IConfig,   "7BF9D277-13A2-4815-B3E9-CDE77C5906C3")
DEFINE_GUIDS(CLSID_IConfig, "09BE7B0C-2275-474D-9405-24AAB891614F")

