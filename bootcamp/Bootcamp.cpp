#include "DPrint.h"
#include<functional>
#include "APTaskFactory.h"
#include "Callback.h"
#include "ProtoToMarkup.h"

using namespace std::placeholders; 

#include <unistd.h>

DPrint s_logger( "Bootcamp" );

class Worker
{
public:
    Worker( NotifyTargetTaskIF* pTask ) :
     m_pTask( pTask )
    {
    }

 	void Work( const std::string& name, uint32_t t )
    {
        s_logger.LogInfo( "Work - %s is sleeping for %d seconds", name.c_str(), t );
        sleep( t );
        s_logger.LogInfo( "Work - %s is done sleeping for %d seconds", name.c_str(), t );
    }

    Callback<> GetBrian1()
    {
		 auto fn = std::bind(&Worker::Work,this,"Brian",1);
		 return fn;
		//return Callback<>();
    }

    Callback<uint32_t> GetJohnX()
    {
		 auto fn = std::bind(&Worker::Work,this,"John",_1);
		 return fn;
        //return Callback<uint32_t>();
    }

    Callback<std::string> GetX5()
    {
        // BOOTCAMP STEP - return a callback to Work, with placeholder 1 for name and 5 for t
		 auto fn = std::bind(&Worker::Work,this,_1,5);
		 return fn;
        //return Callback<std::string>();
    }

    Callback<std::string, uint32_t> GetXX()
    {
        // BOOTCAMP STEP - return a callback to Work, with placeholder 1 for name and placeholder 2 for t
		 auto fn = std::bind(&Worker::Work,this,_1,_2);
		return fn;
        //return Callback<std::string, uint32_t>();
    }

    // BOOTCAMP STEP - Use AsyncCallback instead of Callback for these 4 types for functions
private:
    NotifyTargetTaskIF* m_pTask;
};

int main()
{
    DPrint::SetPrintToStdout();

    NotifyTargetTaskIF* pTask = IL::CreateTask( "Bootcamp" );

    Worker w( pTask );
    w.Work( "Jack", 1 );
    w.Work( "Jill", 2 );
    {
        auto cb = w.GetBrian1();
		cb();
    }
    {
        auto cb = w.GetJohnX();
		cb(1);	
        // BOOTCAMP STEP - call cb with right parameter(s)
    }
    {
        auto cb = w.GetX5();
		cb("randon_name");
        // BOOTCAMP STEP - call cb with right parameter(s)
    }
    {
        auto cb = w.GetXX();
		cb("name_awesome",3);
        // BOOTCAMP STEP - call cb with right parameter(s)
    }
	while( true )
    {
        sleep( 10 );
    }
}
