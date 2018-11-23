#include "ExampleCPPFederate.h"

#include <SDKDDKVer.h>

#include "socketConfig.h"




int main( int argc, char *argv[] )
{
    socketInit();

	// check to see if we have a federate name
	char* federateName = "exampleFederate";
	if( argc > 1 )
		federateName = argv[1];

	// create and run the federate
	ExampleCPPFederate *federate;
	federate = new ExampleCPPFederate();
	federate->runFederate( federateName );
	
    

	// clean up
	delete federate;
	return 0;
}
