
;include cor.inc
if (NTDDI_VERSION GE NTDDI_WIN8)
RoGetMetaDataFile proto WINAPI \
                  name: HSTRING,
     metaDataDispenser: ptr IMetaDataDispenserEx,
      metaDataFilePath: ptr HSTRING,
        metaDataImport: ptr ptr IMetaDataImport2,
          typeDefToken: ptr mdTypeDef

RoParseTypeName proto WINAPI \
              typeName: HSTRING,
            partsCount: ptr DWORD,
         typeNameParts: ptr HSTRING

RoResolveNamespace proto WINAPI \
                  name: HSTRING,
    windowsMetaDataDir: HSTRING,
 packageGraphDirsCount: DWORD,
      packageGraphDirs: ptr HSTRING,
metaDataFilePathsCount: ptr DWORD,
     metaDataFilePaths: ptr ptr HSTRING,
    subNamespacesCount: ptr DWORD,
         subNamespaces: ptr ptr HSTRING
endif
