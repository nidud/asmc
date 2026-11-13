; WINRT.ASM--
;
; https://devblogs.microsoft.com/oldnewthing/20221013-00/?p=107285
;

include windows.inc
include winrt/roapi.inc
include stdio.inc
include winrt/Windows.Networking.Connectivity.inc
include winrt/wrl/wrappers/corewrappers.inc
include tchar.inc

.data
 DECLARE_IID(IActivationFactory)
 DECLARE_IID(INetworkInformationStatics)

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
    endp

    end _tstart
