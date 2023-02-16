include windows.inc
include p2p.inc
include stdio.inc
include tchar.inc

    .code

main proc argc:int_t, argv:array_t

  local p:PEER_VERSION_DATA

    .ifd PeerGroupStartup( PEER_GROUP_VERSION, &p ) == S_OK

        PeerGroupShutdown()

        printf(
            "\n"
            "\tPeerGroupStartup(P2P.dll)\n"
            "\t\tVersion:\t\t%d\n"
            "\t\tHighest Version:\t%d\n"
            "\n",
            p.wVersion,
            p.wHighestVersion )

    .endif

    .ifd PeerGraphStartup( PEER_GRAPH_VERSION, &p ) == S_OK

        PeerGraphShutdown()

        printf(
            "\n"
            "\tPeerGroupStartup(P2PGraph.dll)\n"
            "\t\tVersion:\t\t%d\n"
            "\t\tHighest Version:\t%d\n"
            "\n",
            p.wVersion,
            p.wHighestVersion )

    .endif
    ret

main endp

    end _tstart
