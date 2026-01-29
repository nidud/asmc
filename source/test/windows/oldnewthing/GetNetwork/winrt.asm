; WINRT.ASM--
;
; https://devblogs.microsoft.com/oldnewthing/20221013-00/?p=107285
;

include windows.inc
include roapi.inc
include stdio.inc
include winrt/Windows.Networking.Connectivity.inc
include wrl/wrappers/corewrappers.inc
include tchar.inc

.data
 IID_IActivationFactory IID {0x00000035,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
 IID_INetworkInformationStatics IID {0x5074F851,0x950D,0x4165,{0x9C,0x15,0x36,0x56,0x19,0x48,0x1E,0xEA}}

.code

_tmain proc


   .new hr:HRESULT = CoInitializeEx(nullptr, COINIT_MULTITHREADED)

    .if (SUCCEEDED(hr))

       .new interfaceName:HString(RuntimeClass_Windows_Networking_Connectivity_NetworkInformation)
       .new classFactory:ptr IActivationFactory = NULL
        mov hr,RoGetActivationFactory(interfaceName, &IID_IActivationFactory, &classFactory)
        interfaceName.Release()

        .if (SUCCEEDED(hr))

           .new netStatics:ptr Windows::Networking::Connectivity::INetworkInformationStatics = NULL
            mov hr,classFactory.QueryInterface(&IID_INetworkInformationStatics, &netStatics)

            .if (SUCCEEDED(hr))

               .new connection:ptr Windows::Networking::Connectivity::IConnectionProfile = NULL
                mov hr,netStatics.GetInternetConnectionProfile(&connection)

                .if (SUCCEEDED(hr))

                   .new cost:ptr Windows::Networking::Connectivity::IConnectionCost
                    mov hr,connection.GetConnectionCost(&cost)

                    .if (SUCCEEDED(hr))

                       .new connectivityLevel:int_t = 0
                       .new connectivityCost:int_t = 0
                       .new approachingDataLimit:int_t = 0
                       .new overDataLimit:int_t = 0
                       .new roaming:int_t = 0

                        connection.GetNetworkConnectivityLevel(&connectivityLevel)

                        cost.get_NetworkCostType(&connectivityCost)
                        cost.get_Roaming(&roaming)
                        cost.get_OverDataLimit(&overDataLimit)
                        cost.get_ApproachingDataLimit(&approachingDataLimit)

                         _tprintf(
                            " ConnectivityLevel:     %d\n"
                            " ConnectivityCost:      %d\n"
                            " ApproachingDataLimit:  %d\n"
                            " OverDataLimit:         %d\n"
                            " Roaming:               %d\n",
                            connectivityLevel,
                            connectivityCost,
                            approachingDataLimit,
                            overDataLimit,
                            roaming)

                        cost.Release()
                    .endif
                    connection.Release()
                .endif
                netStatics.Release()
            .endif
            classFactory.Release()
        .endif
        CoUninitialize()
    .endif
    .return(hr)

_tmain endp

    end _tstart
