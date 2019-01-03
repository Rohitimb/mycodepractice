#include "DPrint.h"

#include <unistd.h>

#include "ProtoToMarkup.h"

#include "APTaskFactory.h"
#include "BootcampServer.h"

static DPrint s_logger( "BootcampServer" );

int main()
{
    DPrint::SetPrintToStdout();

    NotifyTargetTaskIF* pTask = IL::CreateTask( "BootcampServer" );
    BootcampServer server( pTask );

    while( true )
    {
       sleep( 10 );
    }
}

