; ASSERT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include stdlib.inc
include assert.inc
ifndef __UNIX__
include wchar.inc
endif
include tchar.inc

.assert:on

define BUFSIZE 2048

    .data
     d33_0   real8 33.0
     d33_3e7 real8 33.3e7
     d33_3   real8 33.3
     d3_3    real8 3.3
     d3_33   real8 3.33

    .code

CHECK_PRINTF macro EXPECTED, FMT, ARGS:vararg
    mov ebx,snprintf(p, BUFSIZE, FMT, ARGS)
    .assertd ( strcmp(EXPECTED, p) == 0 )
    .assertd ( strlen(p) == ebx )
    exitm<>
    endm
ifndef __UNIX__
CHECK_WPRINTF macro EXPECTED, FMT, ARGS:vararg
    mov ebx,_snwprintf(p, BUFSIZE/2, FMT, ARGS)
    .assertd ( wcscmp(EXPECTED, p) == 0 )
    .assertd ( wcslen(p) == ebx )
    exitm<>
    endm
endif

main proc

    .new buffer[BUFSIZE]:byte
    .new q:qword = 1123456789ABCDEFh
    .new b:qword = 0xfedcba9987654321
    .new p:string_t = &buffer
    .new fp:LPFILE

    CHECK_PRINTF("hello!",  "hello%c", '!')
    CHECK_PRINTF("1",       "%d", 1)
    CHECK_PRINTF("99",      "%02d", 99)
    CHECK_PRINTF("099",     "%03d", 99)
    CHECK_PRINTF("1",       "%x", 1)
    CHECK_PRINTF("ff",      "%02x", 255)
    CHECK_PRINTF("FE",      "%02X", 254)
    CHECK_PRINTF("ABCD",    "%X", 0xABCD)
    CHECK_PRINTF("89ABCDEF","%X", 0x89ABCDEF)
    CHECK_PRINTF("1123456789ABCDEF", "%016I64X", q)
    CHECK_PRINTF("-1",      "%i", -1)
    CHECK_PRINTF("4294967295", "%u", 0xFFFFFFFF)
ifdef _WIN64
    CHECK_PRINTF("0000000089ABCDEF", "%p", 0x89ABCDEF)
else
    CHECK_PRINTF("89ABCDEF", "%p", 0x89ABCDEF)
endif
    CHECK_PRINTF("0",       "%b", 0)
    CHECK_PRINTF("0",       "%B", 0)
    CHECK_PRINTF("0",       "%#b", 0)
    CHECK_PRINTF("0",       "%#B", 0)
    CHECK_PRINTF("1",       "%b", 1)
    CHECK_PRINTF("1",       "%B", 1)
    CHECK_PRINTF("10",      "%b", 2)
    CHECK_PRINTF("10",      "%B", 2)
    CHECK_PRINTF("11",      "%b", 3)
    CHECK_PRINTF("11",      "%B", 3)
    CHECK_PRINTF("10000111011001010100001100100001", "%b", 0x87654321)
    CHECK_PRINTF("10000111011001010100001100100001", "%B", 0x87654321)
    CHECK_PRINTF("100001100100001", "%hb", 0x87654321)
    CHECK_PRINTF("100001100100001", "%hB", 0x87654321)
    CHECK_PRINTF("100001", "%hhb", 0x87654321)
    CHECK_PRINTF("100001", "%hhB", 0x87654321)
    CHECK_PRINTF("10000111011001010100001100100001", "%lb", 0x87654321)
    CHECK_PRINTF("10000111011001010100001100100001", "%lB", 0x87654321)
    CHECK_PRINTF("1111111011011100101110101001100110000111011001010100001100100001", "%llb", b)
    CHECK_PRINTF("1111111011011100101110101001100110000111011001010100001100100001", "%llB", b)
    CHECK_PRINTF(" 1010", "%5b", 10)
    CHECK_PRINTF(" 1010", "%5B", 10)
    CHECK_PRINTF("01010", "%05b", 10)
    CHECK_PRINTF("01010", "%05B", 10)
    CHECK_PRINTF("1011 ", "%-5b", 11)
    CHECK_PRINTF("1011 ", "%-5B", 11)
    CHECK_PRINTF("0b10011", "%#b", 19)
    CHECK_PRINTF("0B10011", "%#B", 19)
    CHECK_PRINTF("   0b10011", "%#10b", 19)
    CHECK_PRINTF("   0B10011", "%#10B", 19)
    CHECK_PRINTF("0b00010011", "%0#10b", 19)
    CHECK_PRINTF("0B00010011", "%0#10B", 19)
    CHECK_PRINTF("0b00010011", "%#010b", 19)
    CHECK_PRINTF("0B00010011", "%#010B", 19)
    CHECK_PRINTF("0b10011   ", "%#-10b", 19)
    CHECK_PRINTF("0B10011   ", "%#-10B", 19)
    CHECK_PRINTF("00010011", "%.8b", 19)
    CHECK_PRINTF("00010011", "%.8B", 19)
    CHECK_PRINTF("0b00010011", "%#.8b", 19)
    CHECK_PRINTF("0B00010011", "%#.8B", 19)
    CHECK_PRINTF("       00010011", "%15.8b", 19)
    CHECK_PRINTF("       00010011", "%15.8B", 19)
    CHECK_PRINTF("00010011       ", "%-15.8b", 19)
    CHECK_PRINTF("00010011       ", "%-15.8B", 19)
    CHECK_PRINTF("     0b00010011", "%#15.8b", 19)
    CHECK_PRINTF("     0B00010011", "%#15.8B", 19)
    CHECK_PRINTF("0b00010011     ", "%-#15.8b", 19)
    CHECK_PRINTF("0B00010011     ", "%-#15.8B", 19)
    CHECK_PRINTF("1011 ", "%0-5b", 11)
    CHECK_PRINTF("1011 ", "%0-5B", 11)
    CHECK_PRINTF("0b10011   ", "%#0-10b", 19)
    CHECK_PRINTF("0B10011   ", "%#0-10B", 19)
    CHECK_PRINTF("       00010011", "%015.8b", 19)
    CHECK_PRINTF("       00010011", "%015.8B", 19)
    CHECK_PRINTF("     0b00010011", "%0#15.8b", 19)
    CHECK_PRINTF("     0B00010011", "%0#15.8B", 19)

    CHECK_PRINTF("     ",   "%5.s", "xyz")
    CHECK_PRINTF("   33",   "%5.f", d33_0)
    CHECK_PRINTF("  3e+008", "%8.e", d33_3e7)
    CHECK_PRINTF("  3E+008", "%8.E", d33_3e7)
    CHECK_PRINTF("3e+001",  "%.g", d33_3)
    CHECK_PRINTF("3E+001",  "%.G", d33_3)
    CHECK_PRINTF("3",       "%.*g", 0, d3_3)
    CHECK_PRINTF("3",       "%.*G", 0, d3_3)
    CHECK_PRINTF("      3", "%7.*G", 0, d3_33)
    CHECK_PRINTF(" 041",    "%04.*o", 3, 33)
    CHECK_PRINTF("  0000033", "%09.*u", 7, 33)
    CHECK_PRINTF(" 021",    "%04.*x", 3, 33)

ifndef __UNIX__
    wmemset(p, 'x', (BUFSIZE/2) - 1)
    mov word ptr buffer[BUFSIZE-2],0

    .new result[9]:wchar_t
    .assert snprintf(&result, lengthof(result), "%.*ls", BUFSIZE/2-2, p) == BUFSIZE/2 - 2
    .assert !strcmp("xxxxxxxx", &result)
    .assert snprintf(&result, lengthof(result), "%.*ls", BUFSIZE/2, p) == BUFSIZE/2 - 1
    .assert !strcmp("xxxxxxxx", &result)
    .assert snprintf(&result, lengthof(result), "%ls", p) == BUFSIZE/2 - 1
    .assert !strcmp("xxxxxxxx", &result)

    CHECK_WPRINTF(L"hello!",  L"hello%c", '!')
    CHECK_WPRINTF(L"1",       L"%d", 1)
    CHECK_WPRINTF(L"99",      L"%02d", 99)
    CHECK_WPRINTF(L"099",     L"%03d", 99)
    CHECK_WPRINTF(L"1",       L"%x", 1)
    CHECK_WPRINTF(L"ff",      L"%02x", 255)
    CHECK_WPRINTF(L"FE",      L"%02X", 254)
    CHECK_WPRINTF(L"ABCD",    L"%X", 0xABCD)
    CHECK_WPRINTF(L"89ABCDEF",L"%X", 0x89ABCDEF)
    CHECK_WPRINTF(L"1123456789ABCDEF", L"%016I64X", q)
    CHECK_WPRINTF(L"-1",      L"%i", -1)
    CHECK_WPRINTF(L"4294967295", L"%u", 0xFFFFFFFF)
ifdef _WIN64
    CHECK_WPRINTF(L"0000000089ABCDEF", L"%p", 0x89ABCDEF)
else
    CHECK_WPRINTF(L"89ABCDEF", L"%p", 0x89ABCDEF)
endif

    CHECK_WPRINTF(L"0b00010011     ", L"%-#15.8b", 19)
    CHECK_WPRINTF(L"10000111011001010100001100100001", L"%b", 0x87654321)
    CHECK_WPRINTF(L"10000111011001010100001100100001", L"%B", 0x87654321)
    CHECK_WPRINTF(L"100001100100001", L"%hb", 0x87654321)
    CHECK_WPRINTF(L"100001100100001", L"%hB", 0x87654321)
    CHECK_WPRINTF(L"100001", L"%hhb", 0x87654321)
    CHECK_WPRINTF(L"100001", L"%hhB", 0x87654321)
    CHECK_WPRINTF(L"10000111011001010100001100100001", L"%lb", 0x87654321)
    CHECK_WPRINTF(L"10000111011001010100001100100001", L"%lB", 0x87654321)
    CHECK_WPRINTF(L"1111111011011100101110101001100110000111011001010100001100100001", L"%llb", b)
endif

    .assert atol("247") == 247
    .assert fopen("test.fil","w")
    mov fp,rax
    .assert fprintf(rax,"%03u",3) == 3
    .assert !fclose(fp)
    .assert fopen("test.fil","rt") == fp
    .assert fread(p,3,1,fp) == 1
    .assert !fclose(fp)
    .assert !strncmp(p,"003",3)

ifdef __UNIX__
    .assert fopen("../assert/test.fil","rt") == fp
else
    .assert fopen("..\\assert\\test.fil","rt") == fp
endif
    .assert !fclose(fp)

    .assert fopen("test.fil","w")
    mov fp,rax

    .assert fwrite("abcdefghijklmnopqr",2,9,fp) == 9
    .assert !fseek(fp,1,SEEK_SET)
    .assert fwrite("abcdefghijklmnopq",1,17,fp) == 17
    .assert !fclose(fp)
    .assert fopen("test.fil","rb") == fp
    .assert fread(p,2,9,fp) == 9
    .assert !fclose(fp)
    .assert !strncmp(p,"aabcdefghijklmnopq",18)
    .assert !remove("test.fil")
ifndef __UNIX__
    .assert _wtol(L"247") == 247
    .assert _wfopen(L"test.fil",L"w,ccs=UTF-16LE")
    mov fp,rax
    .assert fwprintf(rax,L"%03u",3) == 3
    .assert !fclose(fp)
    .assert _wfopen(L"test.fil",L"rt,ccs=UTF-16LE") == fp
    .assert fread(p,3,2,fp) == 2
    .assert !fclose(fp)
    .assert !wcsncmp(p,L"003",3)
    .assert !_wremove(L"test.fil")
endif
    .return( 0 )

main endp

    end
