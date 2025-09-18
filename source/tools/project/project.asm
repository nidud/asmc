; PROJECT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Creates a default project directory <name>
;  - <name>\makefile
;  - <name>\<name>.asm
;  - <name>\<name>.vcxproj - Visual Studio 2022
;
include io.inc
include direct.inc
include stdio.inc
include stdlib.inc
include time.inc
include string.inc
include tchar.inc

.code

CreateProject proc path:string_t, name:string_t, Unicode:int_t, Windows:int_t, iddc:int_t

   .new lpWindows[2]:string_t = { "Console", "Windows" }
   .new lpUnicode[2]:string_t = { "false", "true" }
   .new file[_MAX_PATH]:char_t
   .new iddc_props:string_t   = { "    <Import Project=\"$(AsmcDir)\\bin\\iddc.props\" />\n" }
   .new iddc_targets:string_t = { "    <Import Project=\"$(AsmcDir)\\bin\\iddc.targets\" />\n" }

    .if ( iddc == 0 )

        mov iddc_props,&@CStr("")
        mov iddc_targets,rax
    .endif

    sprintf(&file, "%s/%s.vcxproj", path, name)
    .if ( fopen(&file, "wt") == NULL )

        perror(&file)
        exit(1)
    .endif
    .new fp:LPFILE = rax

    mov ecx,Unicode
    mov edx,Windows
    mov rcx,lpUnicode[rcx*string_t]
    mov rdx,lpWindows[rdx*string_t]

    fprintf(fp,
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
        "<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n"
        "  <ItemGroup Label=\"ProjectConfigurations\">\n"
        "    <ProjectConfiguration Include=\"Debug|X64\">\n"
        "      <Configuration>Debug</Configuration>\n"
        "      <Platform>X64</Platform>\n"
        "    </ProjectConfiguration>\n"
        "    <ProjectConfiguration Include=\"Debug|win32\">\n"
        "      <Configuration>Debug</Configuration>\n"
        "      <Platform>win32</Platform>\n"
        "    </ProjectConfiguration>\n"
        "  </ItemGroup>\n"
        "  <PropertyGroup Label=\"Globals\">\n"
        "    <AsmcDir>$(AsmcDir)</AsmcDir>\n"
        "    <RootNamespace>%s</RootNamespace>\n"
        "    <VCProjectVersion>16.0</VCProjectVersion>\n"
        "    <Keyword>Win32Proj</Keyword>\n"
        "    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>\n"
        "  </PropertyGroup>\n"
        "  <Import Project=\"$(VCTargetsPath)\Microsoft.Cpp.Default.props\" />\n"
        "  <PropertyGroup Label=\"Configuration\">\n"
        "    <ConfigurationType>Application</ConfigurationType>\n"
        "    <UseDebugLibraries>true</UseDebugLibraries>\n"
        "    <PlatformToolset>v143</PlatformToolset>\n"
        "  </PropertyGroup>\n"
        "  <Import Project=\"$(VCTargetsPath)\Microsoft.Cpp.props\" />\n"
        "  <ImportGroup Label=\"ExtensionSettings\">\n"
        "    <Import Project=\"$(AsmcDir)\\bin\\asmc.props\" />\n%s"
        "  </ImportGroup>\n"
        "  <ImportGroup Label=\"Shared\">\n"
        "  </ImportGroup>\n"
        "  <ImportGroup Label=\"PropertySheets\">\n"
        "    <Import Project=\"$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />\n"
        "  </ImportGroup>\n"
        "  <PropertyGroup Label=\"UserMacros\" />\n"
        "  <PropertyGroup>\n"
        "    <LinkIncremental>true</LinkIncremental>\n"
        "  </PropertyGroup>\n"
        "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|X64'\">\n"
        "    <Link>\n"
        "      <SubSystem>%s</SubSystem>\n"
        "      <GenerateMapFile>true</GenerateMapFile>\n"
        "      <TargetMachine>MachineX64</TargetMachine>\n"
        "      <AdditionalLibraryDirectories>$(AsmcDir)\\lib\\X64</AdditionalLibraryDirectories>\n"
        "      <AdditionalOptions>/merge:.CRT=.rdata %%(AdditionalOptions)</AdditionalOptions>\n"
        "    </Link>\n"
        "    <ASMC>\n"
        "      <UnicodeCharacterSet>%s</UnicodeCharacterSet>\n"
        "      <GenerateCStackFrame>true</GenerateCStackFrame>\n"
        "    </ASMC>\n"
        "  </ItemDefinitionGroup>\n"
        "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|win32'\">\n"
        "    <Link>\n"
        "      <SubSystem>%s</SubSystem>\n"
        "      <GenerateDebugInformation>true</GenerateDebugInformation>\n"
        "      <GenerateMapFile>true</GenerateMapFile>\n"
        "      <AdditionalLibraryDirectories>$(AsmcDir)\\lib\\x86</AdditionalLibraryDirectories>\n"
        "      <AdditionalOptions>/merge:.CRT=.rdata %%(AdditionalOptions)</AdditionalOptions>\n"
        "    </Link>\n"
        "    <ASMC>\n"
        "      <UnicodeCharacterSet>%s</UnicodeCharacterSet>\n"
        "      <GenerateCStackFrame>true</GenerateCStackFrame>\n"
        "      <ObjectFileTypeCOFF>true</ObjectFileTypeCOFF>\n"
        "    </ASMC>\n"
        "  </ItemDefinitionGroup>\n"
        "  <ItemGroup>\n"
        "    <ASMC Include=\"%s.asm\" />\n"
        "  </ItemGroup>\n"
        "  <Import Project=\"$(VCTargetsPath)\Microsoft.Cpp.targets\" />\n"
        "  <ImportGroup Label=\"ExtensionTargets\">\n"
        "    <Import Project=\"$(AsmcDir)\\bin\\asmc.targets\" />\n%s"
        "  </ImportGroup>\n"
        "</Project>", name, iddc_props, rdx, rcx, rdx, rcx, name, iddc_targets )
    ret

CreateProject endp


CreateMakefile proc name:string_t, Unicode:int_t, Windows:int_t, Static:int_t, pe:int_t

   .new W:string_t = ""
   .new ws:string_t = ""
   .new gui:string_t = ""
   .new sys:string_t = "con"
   .new ltime:time_t

   .new file[_MAX_PATH]:char_t

    sprintf(&file, "%s/makefile", name)
    .if ( fopen(&file, "wt") == NULL )

        perror(&file)
        exit(1)
    .endif
    .new fp:LPFILE = rax

    _time( &ltime )
    fprintf(fp, "# Makefile for %s\n", name)
    fprintf(fp, "# %s\n", asctime(gmtime( &ltime )))

    fprintf(fp, "flags = -q\nifdef YACC\n")
    .if ( !Static )
        fprintf(fp, "flags += -fpic\n")
    .endif
    fprintf(fp, "else\n")
    .if ( Unicode )
        fprintf(fp, "flags += -ws\n")
    .endif
    .if ( pe )
        .if ( Windows )
            fprintf(fp, "flags += -peg\n")
        .else
            fprintf(fp, "flags += -pe\n")
        .endif
    .endif
    mov rcx,name
    fprintf(fp,
        "endif\n"
        "\n"
        "all: %s clean\n"
        "\n"
        "%s:\n"
        "\tasmc64 $(flags) $@.asm\n"
        "ifdef YACC\n"
        "\t./$@\n"
        "else\n"
        "\t$@\n"
        "endif\n"
        "\t@pause\n"
        "\n"
        "clean:\n"
        "ifdef YACC\n"
        "\trm ./%s.o\n"
        "\trm ./%s\n"
        "else\n"
        "\tdel %s.exe\n", rcx, rcx, rcx, rcx, rcx )
    .if ( pe == 0 )
        fprintf(fp, "\tdel %s.obj\n", name)
    .endif
    fprintf(fp, "endif\n\nvs:\n\tproject -p ")

    .if ( pe )
        fprintf(fp, "-pe ")
    .endif
    .if ( Unicode )
        fprintf(fp, "-u ")
    .endif
    .if ( Windows )
        fprintf(fp, "-w ")
    .endif
    .if ( Static )
        fprintf(fp, "-s ")
    .endif
    fprintf(fp, "%s\n", name)
    ret

CreateMakefile endp


CreateSource proc name:string_t, Windows:int_t

   .new file[_MAX_PATH]:char_t
    sprintf(&file, "%s/%s.asm", name, name)
    .ifd ( _access(&file, 0) == 0 )

        perror(&file)
        exit(1)
    .endif
    .if ( fopen(&file, "wt") == NULL )

        perror(&file)
        exit(1)
    .endif
    .new fp:LPFILE = rax

    .new uname[_MAX_PATH]:char_t
    strupr(strcpy(&uname, name))
    fprintf(fp,
        "; %s.ASM--\n"
        ";\n"
        "; Copyright (c) The Asmc Contributors. All rights reserved.\n"
        "; Consult your license regarding permissions and restrictions.\n"
        ";\n"
        "\n", &uname)

    .if ( Windows )

        fprintf(fp,
            "include windows.inc\n"
            "include tchar.inc\n"
            "\n"
            "define CLASSNAME <\"%s\">\n"
            "\n"
            ".code\n"
            "\n"
            "WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM\n"
            "\n"
            "    .switch uMsg\n"
            "    .case WM_PAINT\n"
            "       .new ps:PAINTSTRUCT\n"
            "       .new hdc:HDC = BeginPaint(hWnd, &ps)\n"
            "        EndPaint(hWnd, &ps)\n"
            "       .return( 0 )\n"
            "    .case WM_CHAR\n"
            "        .endc .if dword ptr wParam != VK_ESCAPE\n"
            "    .case WM_DESTROY\n"
            "        PostQuitMessage(0)\n"
            "       .return( 0 )\n"
            "    .endsw\n"
            "    .return DefWindowProc(hWnd, uMsg, wParam, lParam)\n"
            "\n"
            "WndProc endp\n"
            "\n"
            "\n"
            "_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT\n"
            "\n"
            "   .new wc:WNDCLASSEX = {\n"
            "        WNDCLASSEX,                      ; .cbSize\n"
            "        CS_HREDRAW or CS_VREDRAW,        ; .style\n"
            "        &WndProc,                        ; .lpfnWndProc\n"
            "        0,                               ; .cbClsExtra\n"
            "        sizeof(LONG_PTR),                ; .cbWndExtra\n"
            "        hInstance,                       ; .hInstance\n"
            "        LoadIcon(NULL, IDI_APPLICATION), ; .hIcon\n"
            "        LoadCursor(NULL, IDC_ARROW),     ; .hCursor\n"
            "        GetStockObject(BLACK_BRUSH),     ; .hbrBackground\n"
            "        NULL,                            ; .lpszMenuName\n"
            "        CLASSNAME,                       ; .lpszClassName\n"
            "        LoadIcon(NULL, IDI_APPLICATION)  ; .hIconSm\n"
            "        }\n"
            "\n"
            "    .ifd RegisterClassEx(&wc)\n"
            "\n"
            "        .if CreateWindowEx(0, CLASSNAME, CLASSNAME,\n"
            "                WS_OVERLAPPEDWINDOW or WS_VISIBLE,\n"
            "                100, 100, 250, 200, NULL, NULL, hInstance, NULL)\n"
            "\n"
            "            .new msg:MSG\n"
            "            .while GetMessage(&msg, 0, 0, 0)\n"
            "\n"
            "                TranslateMessage(&msg)\n"
            "                DispatchMessage(&msg)\n"
            "            .endw\n"
            "            .return msg.wParam\n"
            "        .endif\n"
            "    .endif\n"
            "    .return( 1 )\n"
            "\n"
            "_tWinMain endp\n"
            "\n"
            "end _tstart\n", &uname)
    .else
        fprintf(fp,
            "include stdio.inc\n"
            "include tchar.inc\n"
            "\n"
            ".code\n"
            "\n"
            "_tmain proc argc:int_t, argv:array_t\n"
            "\n"
            "    _tprintf(\"The %s project\\n\")\n"
            "   .return(0)\n"
            "\n"
            "_tmain endp\n"
            "\n"
            "    end _tstart\n", &uname)
    .endif

    ret

CreateSource endp

_tmain proc argc:int_t, argv:array_t

   .new name:string_t = 0
   .new Unicode:int_t = 0
   .new Windows:int_t = 0
   .new Static:int_t = 0
   .new Project:int_t = 0
   .new iddc:int_t = 0
   .new pe:int_t = 0

    .for ( rdx = argv, ecx = 1 : ecx < argc : ecx++ )

        mov rax,[rdx+rcx*string_t]
        mov eax,[rax]
        .if ( al == '-' || al == '/' )
            .if ( ah == 'w' )
                mov Windows,1
            .elseif ( ah == 'u' )
                mov Unicode,1
            .elseif ( ah == 's' )
                mov Static,1
            .elseif ( ah == 'p' )
                shr eax,16
                .if ( al == 'e' )
                    mov pe,1
                .else
                    mov Project,1
                .endif
            .elseif ( ah == 'c' )
                mov iddc,1
            .else
                perror([rdx+rcx*string_t])
                exit(1)
            .endif
        .else
            mov name,[rdx+rcx*string_t]
        .endif
    .endf
    .if ( name == NULL )

        printf(
            "Usage: project [ options ] name\n"
            "\n"
            "-w     -- Windows (default is Console)\n"
            "-u     -- Unicode\n"
            "-s     -- Static\n"
            "-c     -- Add iddc.targets\n"
            "-p     -- Create <name>.vcxproj\n"
            "-pe    -- Generate PE binary file\n"
            "\n"
            "If the -p option is not given a directory is created:\n"
            " - <name>\makefile\n"
            " - <name>\<name>.asm\n"
            " - <name>\<name>.vcxproj - Visual Studio 2022\n"
            "\n"
            )
        exit(0)
    .endif
    .if ( Project )
        CreateProject(".", name, Unicode, Windows, iddc)
    .else
        .if ( _mkdir(name) )

            perror(name)
            exit(1)
        .endif
        CreateProject(name, name, Unicode, Windows, iddc)
        CreateMakefile(name, Unicode, Windows, Static, pe)
        CreateSource(name, Windows)
    .endif
    xor eax,eax
    ret

_tmain endp

    end _tstart
