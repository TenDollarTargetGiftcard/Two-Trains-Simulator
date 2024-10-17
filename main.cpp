#include "Trains.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	// initialize outer and inner tracks
	Segment outerTrack[SIZE] = {};
	Segment innerTrack[SIZE] = {};

	setNext(outerTrack, innerTrack); // set pointers for all Segments
	randomizeTrains(outerTrack, innerTrack); // set random starting positions for trains and set directions
	for (int i = 0; i < numRounds; i++)
	{
		printRound(outerTrack, innerTrack, i + 1); // print the current state of the track
		moveTrains(outerTrack, innerTrack); // move each train once
	}
	return 0;
}
