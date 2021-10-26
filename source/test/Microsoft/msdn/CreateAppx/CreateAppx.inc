;
; This is a simple application which uses the Appx packaging APIs to produce
; an Appx package from a list of files on disk.
;
;
; Function to create a readable IStream over the file whose name is the
; concatenation of the path and fileName parameters.  For simplicity, file
; names including path are assumed to be 100 characters or less.  A real
; application should be able to handle longer names and allocate the
; necessary buffer dynamically.
;
GetFileStream proto :LPCWSTR, :LPCWSTR, :ptr ptr IStream

;
; Function to create an Appx package writer with default settings, given the
; output file name.
;
GetPackageWriter proto :PCWSTR, :ptr ptr IAppxPackageWriter

define T <@CStr>
