#pragma once

#include "APServerSocketListenerIF.h"
#include "DPrint.h"
#include "IPCMessageRouterIF.h"

#include "BootcampDeviceInfo.pb.h"
#include "BootcampMisc.pb.h"
#include "BootcampServiceInfo.pb.h"
#include "BootcampVersion.pb.h"
#define MINE 1

class NotifyTargetTaskIF;

class BootcampServer
{
public:
    BootcampServer( NotifyTargetTaskIF *pTask );
    ~BootcampServer() {}

private:
    void AcceptService( APServerSocketListenerIF::SocketPtr socket );
    void HandleDisconnect();
    void HandleDisconnectComplete();
    void HandleVersionResponse( const Bootcamp::Version& );


    #if MINE
    void HandleServiceInfoResponse( const Bootcamp::ServiceInfo&);
    void HandleDeviceInfoRequest( const Bootcamp::Void& req, int32_t seq );
    void HandleServiceInfoRequest( const Bootcamp::Void& req, int32_t seq );
    void HandleVersionRequest( const Bootcamp::Void& req, int32_t seq );
	#endif
    void HandleServiceReady( const Bootcamp::Void& );

private:
    DPrint m_logger;
    NotifyTargetTaskIF* m_pTask;
    APServerSocketListenerIF::ListenerPtr m_server;
    IPCMessageRouterIF::IPCMessageRouterPtr m_router;
    APServerSocketListenerIF::SocketPtr m_socket;
};
