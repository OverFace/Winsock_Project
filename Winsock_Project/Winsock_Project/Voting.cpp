#include "Voting.h"

void voting::check()
{
	Info.bCheck = false;
	Info.iGet_Count = 0;
	
	if (choice != 0) {
		Info.bCheck = true;
		Info.iGet_Count++;
	}

	return;
}

void voting::result()
{
	choice = 0;

	
}

void voting::ResultSendToServer()
{

}
