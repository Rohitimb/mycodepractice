#include "BootcampClient.h"
#include "APClientSocketListenerFactory.h"
#include "AsyncCallback.h"
#include "BreakThread.h"
#include "IPCMessageRouterFactory.h"
#include <iostream>
#include "BootcampMessageIds.pb.h"
#include <unistd.h>

using namespace std;
//////////////////////////////////////////////////////////////
BootcampClient::BootcampClient( NotifyTargetTaskIF *pTask,
                                const std::string& ip ) :
    m_logger( "BootcampClient" ),
    m_pTask( pTask ),
    m_client( IL::CreateClientListener( "BootcampClient", IntervalInMs( 100 ) ) )
{



    AsyncCallback< APClientSocketListenerIF::SocketPtr > cb( std::bind( &BootcampClient::Connected,
                                                                        this,
                                                                        std::placeholders::_1 ),
                                                             m_pTask );
    //socketptr->port and callback
    m_client->Connect( ip, 30060, cb );
    m_router = IPCMessageRouterFactory::CreateRouter( "BootcampClient", m_pTask );



    {

        AsyncCallback<Bootcamp::Version, uint32_t> cb( std::bind( &BootcampClient::HandleVersionRequest,
                                                                  this,
                                                                  std::placeholders::_1,
                                                                  std::placeholders::_2 ),
                                                       m_pTask );

        m_router->AttachForRequest<Bootcamp::Version>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_VERSION, cb );
    }

    {
        AsyncCallback<Bootcamp::Void, uint32_t> cb( std::bind( &BootcampClient::HandleServiceInfoRequest,
                                                                  this,
                                                                  std::placeholders::_1,
                                                                  std::placeholders::_2 ),
                                                       m_pTask );

        m_router->AttachForRequest<Bootcamp::Void>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_INFO, cb );

    }

}

//////////////////////////////////////////////////////////////
void BootcampClient::Connected( APClientSocketListenerIF::SocketPtr socket )
{

    m_logger.LogInfo( "BootcampClient::Connected()\n" );



#if CMINE
    {
        AsyncCallback<Bootcamp::Void> cb( std::bind( &BootcampClient::HandleNetworkReady,
                                                     this,
                                                     std::placeholders::_1 ),
                                          m_pTask );
        m_router->Attach<Bootcamp::Void>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_NETWORK_READY, cb );
    }


    {
        AsyncCallback<void> cb( std::bind( &BootcampClient::HandleDisconnect, this ), m_pTask );
        m_router->Serve( socket, cb );
    }


    {
        m_logger.LogInfo( "%s === Client VERSION, Void ­­­> Server ===>>\n", __func__);

        Bootcamp::Void v;
        AsyncCallback<Bootcamp::Version> cb( std::bind( &BootcampClient::HandleVersionResponse,
                                                        this,
                                                        std::placeholders::_1 ),
                                             m_pTask );


        m_router->SendRequest<Bootcamp::Version>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_VERSION,
                                                  v,
                                                  cb );
    }



#endif


}

//////////////////////////////////////////////////////////////
void BootcampClient::HandleDisconnect()
{

    m_logger.LogInfo( "BootcampClient::HandleDisconnect()\n" );
    auto func = std::bind( &BootcampClient::HandleDisconnectComplete, this );
    IL::BreakThread( func, m_pTask );
}

//////////////////////////////////////////////////////////////
void BootcampClient::HandleDisconnectComplete()
{

    m_logger.LogInfo( "BootcampServer::HandleDisconnectComplete()\n" );
    if( m_router )
    {
        m_router.reset();
    }
}


//////////////////////////////////////////////////////////////


#if CMINE
void BootcampClient::HandleServiceInfoRequest( const Bootcamp::Void& req, int32_t seq )
{
    Bootcamp::ServiceInfo res;
    res.set_name( "i have set your Service info" );
    m_logger.LogInfo( "BootcampClient::HandleServiceInfoResponse() - sending response\n" );

    m_router->SendResponse<Bootcamp::ServiceInfo>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_INFO, res, seq );
}

void BootcampClient::HandleDeviceInfoResponse( const Bootcamp::DeviceInfo& req )
{


    m_logger.LogInfo( "BootcampClient::HandleDeviceInfoResponse(id = %s)\n",req.id().c_str());
    m_logger.LogInfo( "BootcampClient::HandleDeviceInfoResponse(ip = %s)\n",req.ip().c_str());

    m_logger.LogInfo( "BootcampClient::HandleVersionResponse() sending service ready event\n" );

    m_logger.LogInfo( "%s <<=== Client Device_Info, Device Info ­­­> Server ====\n", __func__);


    m_logger.LogInfo( "%s === Client service Ready, void ­­­> Server ====>>\n", __func__);
    Bootcamp::Void v;
    m_router->SendEvent( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_READY, v );


    {
        m_logger.LogInfo( "%s === Client Serviceinfo, Void ­­­> Server ===>>\n", __func__);

        Bootcamp::Void v;
        AsyncCallback<Bootcamp::ServiceInfo> cb( std::bind( &BootcampClient::HandleServiceInfoResponse,
                                                        this,
                                                        std::placeholders::_1 ),
                                             m_pTask );


        m_router->SendRequest<Bootcamp::ServiceInfo>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_SERVICE_INFO,
                                                  v,
                                                  cb );
    }

}


void BootcampClient::HandleNetworkReady( const Bootcamp::Void& )
{
    m_logger.LogInfo( "BootcampClient::HandleNetworkReady()\n" );
}



void BootcampClient::HandleVersionResponse( const Bootcamp::Version& req )
{
    m_logger.LogInfo( "%s <<=== Client Version, Version ­­­> Server ====\n", __func__);
    m_logger.LogInfo( "BootcampServer::HandleVersionResponse(%s)\n", req.version().c_str() );



    {
        m_logger.LogInfo( "%s === Client Deviceinfo, Void ­­­> Server ===>>\n", __func__);

        Bootcamp::Void v;
        AsyncCallback<Bootcamp::DeviceInfo> cb( std::bind( &BootcampClient::HandleDeviceInfoResponse,
                                                        this,
                                                        std::placeholders::_1 ),
                                             m_pTask );


        m_router->SendRequest<Bootcamp::DeviceInfo>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_DEVICE_INFO,
                                                  v,
                                                  cb );
    }
}

void BootcampClient::HandleServiceInfoResponse( const Bootcamp::ServiceInfo& req    )
{

    m_logger.LogInfo( "%s <<=== Server­­ SERVICE INFO, ServiceInfo ­­­> Client ====\n", __func__);
    m_logger.LogInfo( "BootcampServer::HandleServiceInfoResponse(%s)\n", req.name().c_str() );

    m_logger.LogInfo( "%s<< === Server­­ Network Ready,Void ­­­> Client ====\n", __func__);
    Bootcamp::Void v;
    m_router->SendEvent( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_NETWORK_READY, v );
}

void BootcampClient::HandleVersionRequest( const Bootcamp::Version& req, int32_t seq )
{
    Bootcamp::Version res;
    res.set_version( "setting Version info in server" );
    m_logger.LogInfo( "%s - sending response\n", __func__);
    m_router->SendResponse<Bootcamp::Version>( Bootcamp::MessageId::BOOTCAMP_MESSAGE_ID_VERSION, res, seq );
}



#endif
