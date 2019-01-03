#include "DPrint.h"

#include <unistd.h>

#include "ProtoToMarkup.h"

#include "APTaskFactory.h"
#include "BootcampClient.h"

static DPrint s_logger( "BootcampClient" );

int main()
{
    DPrint::SetPrintToStdout();

    NotifyTargetTaskIF* pTask = IL::CreateTask( "BootcampClient" );
    BootcampClient client( pTask );

    while( true )
    {
       sleep( 10 );
    }
}

