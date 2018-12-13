
#include "testFederate.h"

#include <SDKDDKVer.h>

#include "socketConfig.h"
#include "simType.h"
#include "ExampleCPPFederate.h"

// 创建联邦成员
ExampleCPPFederate *federate;
TestFederate *testFederate;

void federationRun(char* federateName, char* testFederateName)
{
	federate->rtiamb = new RTI::RTIambassador();

	try
	{
		federate->rtiamb->createFederationExecution( "ExampleFederation", "testfom.fed" );
		cout << "Created Federation" << endl;
	}
	catch( RTI::FederationExecutionAlreadyExists exists )
	{
		cout << "Didn't create federation, it already existed" << endl;
	}

	federate->fedamb = new ExampleFedAmb();
	federate->rtiamb->joinFederationExecution( federateName, "ExampleFederation", federate->fedamb );
	cout << "Joined Federation as " << federateName << endl;
	
	federate->initializeHandles();

    federate->rtiamb->registerFederationSynchronizationPoint( READY_TO_RUN, "" );
	while( federate->fedamb->isAnnounced == false )
	{
		federate->rtiamb->tick();
	}

	cout<<"begin to add test federate"<<endl;

    testFederate->rtiamb = new RTI::RTIambassador();

	testFederate->fedamb = new testFedAmb();

	testFederate->rtiamb->joinFederationExecution( testFederateName, "ExampleFederation", testFederate->fedamb);
	cout << "Joined Federation as " << testFederateName << endl;

	testFederate->initializeHandles();

	//testFederate->rtiamb->registerFederationSynchronizationPoint( READY_TO_RUN, "" );
	while( testFederate->fedamb->isAnnounced == false )
	{
		testFederate->rtiamb->tick();
	}

	federate->waitForUser();

	testFederate->rtiamb->synchronizationPointAchieved( READY_TO_RUN );
	cout << "Achieved sync point: " << READY_TO_RUN << ", waiting for federation..." << endl;

	federate->rtiamb->synchronizationPointAchieved( READY_TO_RUN );
	cout << "Achieved sync point: " << READY_TO_RUN << ", waiting for federation..." << endl;
	while( federate->fedamb->isReadyToRun == false )
	{
		federate->rtiamb->tick();
	}




	//federate作为时间控制成员
	federate->enableTimePolicy();
	cout << "Time Policy Enabled" << endl;

	federate->publishAndSubscribe();
	cout << "Published and Subscribed" << endl;

	// package the information into a handle set
	RTI::AttributeHandleSet *attributes = RTI::AttributeHandleSetFactory::create( 3 );
	attributes->add( testFederate->aaHandle );
	attributes->add( testFederate->abHandle );
	attributes->add( testFederate->acHandle );



	federate->rtiamb->subscribeObjectClassAttributes( testFederate->aHandle, *attributes );

	federate->rtiamb->subscribeInteractionClass( testFederate->xHandle );

	delete attributes;

	testFederate->publishAndSubscribe();
	cout << "Published and Subscribed" << endl;
	/*

	RTI::AttributeHandleSet *attributes = RTI::AttributeHandleSetFactory::create( 3 );
	attributes->add( federate->aaHandle );
	attributes->add( federate->abHandle );
	attributes->add( federate->acHandle );

	testFederate->rtiamb->subscribeObjectClassAttributes( federate->aHandle, *attributes );


	try
	{
		cout<<" subscribed interatction"<<federate->xHandle<<endl;
		testFederate->rtiamb->subscribeInteractionClass( federate->xHandle );
	}
	catch(RTI::Exception& e)
	{
		cout<<&e<<endl;
		exit(1);
	}
	*/


	
	

	RTI::ObjectHandle objectHandle = federate->registerObject();
	cout << "Registered Object, handle=" << objectHandle << endl;

	RTI::ObjectHandle testObjectHandle = testFederate->registerObject();
	cout << "Registered testObject, handle=" << testObjectHandle << endl;

	int i;
	for( i = 0; i < 10; i++ )
	{		
		// 9.1 update the attribute values of the instance //
		testFederate->updateAttributeValues( testObjectHandle );

		// 9.2 send an interaction
		testFederate->sendInteraction();

		// 9.3 request a time advance and wait until we get it
		testFederate->advanceTime( 10.0 );
		federate->advanceTime( 10.0 );
		cout << "Time Advanced to " << testFederate->fedamb->federateTime << endl;
        

	}


	federate->deleteObject( objectHandle );
	cout << "Deleted Object, handle=" << objectHandle << endl;

	testFederate->deleteObject( testObjectHandle );
	cout << "Deleted Object, handle=" << testObjectHandle << endl;



}

int main( int argc, char *argv[] )
{
	globleSimData.dataInit();
    socketInit();
	
	//定义联邦成员名字
	char* federateName = "exampleFederate";
	char* testName = "testFederate";



	testFederate = new TestFederate();
	federate = new ExampleCPPFederate();
	
	//testFederate->runFederate(testName);
	//federate->runFederate(federateName);
	federationRun(federateName, testName);
	
	testFederate->overFederate();
	federate->overFederate();
    

	// clean up
	delete testFederate;
	delete federate;
	

	return 0;
}
