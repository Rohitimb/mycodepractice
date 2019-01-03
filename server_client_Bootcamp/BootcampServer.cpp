#include "BootcampServer.h"
#include "APServerSocketListenerFactory.h"
#include "AsyncCallback.h"
#include "BreakThread.h"
#include "IPCMessageRouterFactory.h"
#include<iostream>
#include "BootcampMessageIds.pb.h"
#include <unistd.h>

using namespace std;



BootcampServer::BootcampServer( NotifyTargetTaskIF* pTask ) :
    m_logger( "BootcampServer" ),
    m_pTask( pTask ),
    m_server( IL::CreateServerListener( "BootcampServer", m_pTask ) )
{


    AsyncCallback<APServerSocketListenerIF::SocketPtr> cb( std::bind( &BootcampServer::AcceptService,
                                                                      this,
                                                                      std::placeholders::_1 ),
                                                           m_pTask );
    //socketptr->port and callback
    m_server->Serve( 30060, cb );
    m_router = IPCMessageRouterFactory::CreateRouter( "BootcampServer", m_pTask );

    {

        AsyncCallback<Bootcamp::Void, uint32_t> cb( std::bind( &BootcampServer::HandleVersionRequest,
                                                                  this,
                                                                  std::placeholders::_1,
                                                                  std::placeholders::_2 ),
                                                       m_pTask );

        m_router->AttachForRequest<Bootcamp::Void>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_VERSION, cb );
    }


    {

        AsyncCallback<Bootcamp::Void> cb( std::bind( &BootcampServer::HandleServiceReady,
                                                     this,
                                                     std::placeholders::_1 ),
                                          m_pTask );
        m_router->Attach<Bootcamp::Void>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_READY, cb );
    }

    {
        AsyncCallback<Bootcamp::Void, uint32_t> cb( std::bind( &BootcampServer::HandleDeviceInfoRequest,
                                                                  this,
                                                                  std::placeholders::_1,
                                                                  std::placeholders::_2 ),
                                                       m_pTask );
        m_router->AttachForRequest<Bootcamp::Void>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_DEVICE_INFO, cb );


    }


    {
        AsyncCallback<Bootcamp::Void, uint32_t> cb( std::bind( &BootcampServer::HandleServiceInfoRequest,
                                                                  this,
                                                                  std::placeholders::_1,
                                                                  std::placeholders::_2 ),
                                                       m_pTask );

        m_router->AttachForRequest<Bootcamp::Void>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_INFO, cb );

    }


}


void BootcampServer::AcceptService( APServerSocketListenerIF::SocketPtr socket )
{
    m_logger.LogInfo( "BootcampServer::AcceptService()\n" );
    {
        AsyncCallback<void> cb( std::bind( &BootcampServer::HandleDisconnect, this ), m_pTask );
        m_router->Serve( socket, cb );
    }

    {
        Bootcamp::Version req;

        AsyncCallback<Bootcamp::Version> cb( std::bind( &BootcampServer::HandleVersionResponse,
                                                        this,
                                                        std::placeholders::_1 ),
                                             m_pTask );

        m_logger.LogInfo( "%s === Server­­ VERSION, Version ­­­> Client ===>>\n", __func__);
        m_router->SendRequest<Bootcamp::Version>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_VERSION,
                                                  req,
                                                  cb );
    }



    #if MINE
    /****************************************************/






    AsyncCallback<Bootcamp::ServiceInfo> cb( std::bind( &BootcampServer::HandleServiceInfoResponse,
                                                    this,
                                                    std::placeholders::_1 ),
                                         m_pTask );

    {
//        Bootcamp::ServiceInfo req;

//        req.set_name("set me service info;i am from server");

//        AsyncCallback<Bootcamp::ServiceInfo> cb( std::bind( &BootcampServer::HandleServiceInfoResponse,
//                                                        this,
//                                                        std::placeholders::_1 ),
//                                             m_pTask );

//        m_router->SendRequest<Bootcamp::ServiceInfo>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_INFO,
//                                                  req,
//                                                  cb );
    }
    #endif
    /****************************************************/

}

void BootcampServer::HandleDisconnect()
{

    m_logger.LogInfo( "BootcampServer::HandleDisconnect()\n" );
    auto func = std::bind( &BootcampServer::HandleDisconnectComplete, this );
    IL::BreakThread( func, m_pTask );
}

void BootcampServer::HandleDisconnectComplete()
{

    m_logger.LogInfo( "BootcampServer::HandleDisconnectComplete()\n" );
    if( m_router )
    {
        m_router.reset();
    }
}

void BootcampServer::HandleVersionResponse( const Bootcamp::Version& req )
{
    m_logger.LogInfo( "%s <<=== Server­­ VERSION, Version ­­­> Client ====\n", __func__);
    m_logger.LogInfo( "BootcampServer::HandleVersionResponse(%s)\n", req.version().c_str() );


    /*handle service info now*/
    Bootcamp::Void v;
    AsyncCallback<Bootcamp::ServiceInfo> cb( std::bind( &BootcampServer::HandleServiceInfoResponse,
                                                    this,
                                                    std::placeholders::_1 ),
                                         m_pTask );
    m_logger.LogInfo( "%s === Server­­ SERVICE INFO, Void ­­­> Client ====>>\n", __func__);
    m_router->SendRequest<Bootcamp::ServiceInfo>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_INFO,
                                              v,
                                              cb );
}

#if MINE

void BootcampServer::HandleServiceInfoResponse( const Bootcamp::ServiceInfo& req    )
{

    m_logger.LogInfo( "%s <<=== Server­­ SERVICE INFO, ServiceInfo ­­­> Client ====\n", __func__);
    m_logger.LogInfo( "BootcampServer::HandleServiceInfoResponse(%s)\n", req.name().c_str() );
    m_logger.LogInfo( "%s === Server­­ Network Ready,Void ­­­> Client ====\n", __func__);

    Bootcamp::Void v;
    m_router->SendEvent( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_NETWORK_READY, v );
}

void BootcampServer::HandleDeviceInfoRequest( const Bootcamp::Void& req, int32_t seq )
{
    Bootcamp::DeviceInfo res;
    res.set_id( "001" );
    res.set_ip( "111.111.111.111" );
    m_logger.LogInfo( "BootcampServer::HandleDeviceInfoRequest() - sending response\n" );
    m_router->SendResponse<Bootcamp::DeviceInfo>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_DEVICE_INFO, res, seq );
}

void BootcampServer::HandleServiceInfoRequest( const Bootcamp::Void& req, int32_t seq )
{
    Bootcamp::ServiceInfo res;
    res.set_name( "------service----" );
    m_logger.LogInfo( "BootcampServer::HandleServiceInfoRequest() - sending response\n" );
    m_router->SendResponse<Bootcamp::ServiceInfo>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_INFO, res, seq );
}


void BootcampServer::HandleVersionRequest( const Bootcamp::Void& req, int32_t seq )
{
    Bootcamp::Version res;
    res.set_version( "setting Version info in server" );
    m_logger.LogInfo( "%s - sending response\n", __func__);
    m_router->SendResponse<Bootcamp::Version>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_VERSION, res, seq );
}




#endif


void BootcampServer::HandleServiceReady( const Bootcamp::Void& )
{
    m_logger.LogInfo( "BootcampServer::HandleServiceReady()\n" );
}
