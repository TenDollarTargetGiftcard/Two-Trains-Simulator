#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//declare size of tracks and number of rounds as constants
const int SIZE = 10;
const int numRounds = 50;
const int numTrains = 4;
// declare a structure of train track Segments
struct Segment
{
	Segment* nextOuter;
	Segment* nextInner;
	Segment* lastOuter;
	Segment* lastInner;
	// 0 = no train; 1 = train in clockwise direction; -1 = train in counter-clokcwise direction
	int trainIndicator;
};

// function prototypes
int randomizeTrains(Segment outerTrack[], Segment innerTrack[]);
int printRound(Segment outerTrack[], Segment innerTrack[], int round);
int setNext(Segment outerTrack[], Segment innerTrack[]);
int moveTrains(Segment outerTrack[], Segment innerTrack[]);