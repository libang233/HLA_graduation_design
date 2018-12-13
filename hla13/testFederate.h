#ifndef TESTFEDERATE_H_
#define TESTFEDERATE_H_

#include "RTI.hh"
#include "testFedAmb.h"




class TestFederate
{
	public:
		RTI::RTIambassador *rtiamb;
		testFedAmb      *fedamb;

		// fom handles //
		RTI::ObjectClassHandle      aHandle;
		RTI::AttributeHandle        aaHandle;
		RTI::AttributeHandle        abHandle;
		RTI::AttributeHandle        acHandle;
		RTI::InteractionClassHandle xHandle;
		RTI::ParameterHandle        xaHandle;
		RTI::ParameterHandle        xbHandle;

		// public methods //
		TestFederate();
		virtual ~TestFederate();
		void runFederate( char* federateName );
		void overFederate();


	//private:
		void initializeHandles();
		void waitForUser();
		void enableTimePolicy();
		void publishAndSubscribe();
		RTI::ObjectHandle registerObject();
		void updateAttributeValues( RTI::ObjectHandle objectHandle );
		void sendInteraction();
		void advanceTime( double timestep );
		void deleteObject( RTI::ObjectHandle objectHandle );
		double getLbts();
};


#endif /*TESTFEDERATE_H_*/