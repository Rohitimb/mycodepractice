#pragma once

#include "APClientSocketListenerIF.h"
#include "DPrint.h"
#include "IPCMessageRouterIF.h"

#include "BootcampDeviceInfo.pb.h"
#include "BootcampMisc.pb.h"
#include "BootcampServiceInfo.pb.h"
#include "BootcampVersion.pb.h"

#define CMINE 1
class NotifyTargetTaskIF;

class BootcampClient
{
public:
    BootcampClient( NotifyTargetTaskIF *pTask,
                    const std::string& ip = "127.0.0.1" );
    ~BootcampClient() {}

private:
    void Connected( APClientSocketListenerIF::SocketPtr socket );
    void HandleDisconnect();
    void HandleDisconnectComplete();

#if CMINE
    void HandleServiceInfoRequest( const Bootcamp::Void&, int32_t seq );

    void HandleDeviceInfoResponse( const Bootcamp::DeviceInfo& req );
    void HandleNetworkReady( const Bootcamp::Void& );
    void HandleServiceInfoResponse( const Bootcamp::ServiceInfo& req);
    void HandleVersionResponse( const Bootcamp::Version& req );

    void HandleVersionRequest( const Bootcamp::Version& req, int32_t seq );
#endif

private:
    DPrint m_logger;
    NotifyTargetTaskIF* m_pTask;
    IPCMessageRouterIF::IPCMessageRouterPtr m_router;
    APClientSocketListenerIF::SocketPtr m_socket;
    APClientSocketListenerIF::ListenerPtr m_client;
};

