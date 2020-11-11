ifndef _GDIPLUSPIXELFORMATS_H
_GDIPLUSPIXELFORMATS_H equ <>

ARGB                    typedef DWORD
ARGB64                  typedef DWORDLONG

ALPHA_SHIFT             equ 24
RED_SHIFT               equ 16
GREEN_SHIFT             equ 8
BLUE_SHIFT              equ 0
ALPHA_MASK              equ (0xff SHL ALPHA_SHIFT)

PixelFormat             typedef SDWORD

PixelFormatIndexed      equ 0x00010000
PixelFormatGDI          equ 0x00020000
PixelFormatAlpha        equ 0x00040000
PixelFormatPAlpha       equ 0x00080000
PixelFormatExtended     equ 0x00100000
PixelFormatCanonical    equ 0x00200000

PixelFormatUndefined    equ 0
PixelFormatDontCare     equ 0

PixelFormat1bppIndexed  equ (1 OR ( 1 SHL 8) OR PixelFormatIndexed OR PixelFormatGDI)
PixelFormat4bppIndexed  equ (2 OR ( 4 SHL 8) OR PixelFormatIndexed OR PixelFormatGDI)
PixelFormat8bppIndexed  equ (3 OR ( 8 SHL 8) OR PixelFormatIndexed OR PixelFormatGDI)
PixelFormat16bppGrayScale equ (4 OR (16 SHL 8) OR PixelFormatExtended)
PixelFormat16bppRGB555  equ (5 OR (16 SHL 8) OR PixelFormatGDI)
PixelFormat16bppRGB565  equ (6 OR (16 SHL 8) OR PixelFormatGDI)
PixelFormat16bppARGB1555 equ (7 OR (16 SHL 8) OR PixelFormatAlpha OR PixelFormatGDI)
PixelFormat24bppRGB     equ (8 OR (24 SHL 8) OR PixelFormatGDI)
PixelFormat32bppRGB     equ (9 OR (32 SHL 8) OR PixelFormatGDI)
PixelFormat32bppARGB    equ (10 OR (32 SHL 8) OR PixelFormatAlpha OR PixelFormatGDI OR PixelFormatCanonical)
PixelFormat32bppPARGB   equ (11 OR (32 SHL 8) OR PixelFormatAlpha OR PixelFormatPAlpha OR PixelFormatGDI)
PixelFormat48bppRGB     equ (12 OR (48 SHL 8) OR PixelFormatExtended)
PixelFormat64bppARGB    equ (13 OR (64 SHL 8) OR PixelFormatAlpha OR PixelFormatCanonical OR PixelFormatExtended)
PixelFormat64bppPARGB   equ (14 OR (64 SHL 8) OR PixelFormatAlpha OR PixelFormatPAlpha OR PixelFormatExtended)
PixelFormat32bppCMYK    equ (15 OR (32 SHL 8))
PixelFormatMax          equ 16

GetPixelFormatSize proto format:PixelFormat {
    mov     eax,format
    shr     eax,8
    and     eax,0xff
    }
IsIndexedPixelFormat proto format:PixelFormat {
    mov     eax,format
    and     eax,PixelFormatIndexed
    }
IsAlphaPixelFormat proto :PixelFormat {
    mov     eax,format
    and     eax,PixelFormatAlpha
    }
IsExtendedPixelFormat proto format:PixelFormat {
    mov     eax,format
    and     eax,PixelFormatExtended
    }

if (GDIPVER GE 0x0110)

;;----------------------------------------------------------------------------
;; Color format conversion parameters
;;----------------------------------------------------------------------------

.enum PaletteType {

    ;; Arbitrary custom palette provided by caller.

    PaletteTypeCustom = 0,

    ;; Optimal palette generated using a median-cut algorithm.

    PaletteTypeOptimal = 1,

    ;; Black and white palette.

    PaletteTypeFixedBW = 2,

    ;; Symmetric halftone palettes.
    ;; Each of these halftone palettes will be a superset of the system palette.
    ;; E.g. Halftone8 will have it's 8-color on-off primaries and the 16 system
    ;; colors added. With duplicates removed, that leaves 16 colors.

    PaletteTypeFixedHalftone8   = 3, ;; 8-color, on-off primaries
    PaletteTypeFixedHalftone27  = 4, ;; 3 intensity levels of each color
    PaletteTypeFixedHalftone64  = 5, ;; 4 intensity levels of each color
    PaletteTypeFixedHalftone125 = 6, ;; 5 intensity levels of each color
    PaletteTypeFixedHalftone216 = 7, ;; 6 intensity levels of each color

    ;; Assymetric halftone palettes.
    ;; These are somewhat less useful than the symmetric ones, but are
    ;; included for completeness. These do not include all of the system
    ;; colors.

    PaletteTypeFixedHalftone252 = 8, ;; 6-red, 7-green, 6-blue intensities
    PaletteTypeFixedHalftone256 = 9, ;; 8-red, 8-green, 4-blue intensities
    }

.enum DitherType {

    DitherTypeNone = 0,

    ;; Solid color - picks the nearest matching color with no attempt to
    ;; halftone or dither. May be used on an arbitrary palette.

    DitherTypeSolid = 1,

    ;; Ordered dithers and spiral dithers must be used with a fixed palette.

    ;; NOTE: DitherOrdered4x4 is unique in that it may apply to 16bpp
    ;; conversions also.

    DitherTypeOrdered4x4    = 2,

    DitherTypeOrdered8x8    = 3,
    DitherTypeOrdered16x16  = 4,
    DitherTypeSpiral4x4     = 5,
    DitherTypeSpiral8x8     = 6,
    DitherTypeDualSpiral4x4 = 7,
    DitherTypeDualSpiral8x8 = 8,

    ;; Error diffusion. May be used with any palette.

    DitherTypeErrorDiffusion = 9,

    DitherTypeMax = 10
    }

endif ;;(GDIPVER >= 0x0110)

.enum PaletteFlags {
    PaletteFlagsHasAlpha    = 0x0001,
    PaletteFlagsGrayScale   = 0x0002,
    PaletteFlagsHalftone    = 0x0004
    }

.template ColorPalette

    Flags       UINT ?
    Count       UINT ?
    Entries     ARGB ?

    .operator ColorPalette :abs {
        .if GdipAlloc(ColorPalette + ( ( _1 - 1 ) * ARGB ) )
            mov [rax].ColorPalette.Flags,0
            mov [rax].ColorPalette.Count,_1
        .endif
        }
    .operator Release {
        GdipFree(this)
        }
    .operator GetPalette :abs {
        mov eax,[this].ColorPalette.Entries[_1*ARGB]
        }
    .operator SetPalette :abs, :abs {
        mov [this].ColorPalette.Entries[_1*ARGB],_2
        }

    .ends

endif
