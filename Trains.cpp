#include "Trains.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
// sets a random starting position for the number of trains determined in main()
// and assigns a forward/backward direction for the trains in a 50/50 ratio
int randomizeTrains(Segment outerTrack[], Segment innerTrack[])
{
	srand(time(NULL));
	
	for (int i = 0; i < numTrains; i++)
	{
		int trainStart = rand() % 10; // random position
		int trackStart = rand() % 2; //random track

		if (trackStart == 0) // outerTrack start
		{
			while (outerTrack[trainStart].trainIndicator != 0) // do not place on existing train
			{
				trainStart = rand() % 10;
			}
			if (i < numTrains / 2) // set direction
				outerTrack[trainStart].trainIndicator = 1;
			else
				outerTrack[trainStart].trainIndicator = -1;
		}
		else // innerTrack start
		{
			while (innerTrack[trainStart].trainIndicator != 0) // do not place on existing train
			{
				trainStart = rand() % 10;
			}
			if (i < numTrains / 2) // set direction
				innerTrack[trainStart].trainIndicator = 1;
			else
				innerTrack[trainStart].trainIndicator = -1;
		}
		
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// prints the round # and the tracks/trains for that round
int printRound(Segment outerTrack[], Segment innerTrack[], int round)
{
	// print top outerTrack
	cout << "Round " << round << ":" << endl;
	cout << "+-";
	for (int i = 0; i < SIZE / 2; i++)
	{
		if (outerTrack[i].trainIndicator == 1)
			cout << "->-";
		else if (outerTrack[i].trainIndicator == -1)
			cout << "-<-";
		else
			cout << "---";
	}
	cout << "-+" << endl;
	// print top switches
	cout << "| ";
	for (int i = 0; i < SIZE / 2; i++)
	{
		cout << " X ";
	}
	cout << " |" << endl;
	// print top innerTrack
	cout << "| ";
	for (int i = 0; i < SIZE / 2; i++)
	{
		if (innerTrack[i].trainIndicator == 1)
			cout << "->-";
		else if (innerTrack[i].trainIndicator == -1)
			cout << "-<-";
		else
			cout << "---";
	}
	cout << " |" << endl;
	// print middle section
	cout << "| |";
	for (int i = 0; i < SIZE / 2 - 1; i++)
	{
		cout << "   ";
	}
	cout << " | |" << endl;
	// print bottom innerTrack
	cout << "| ";
	for (int i = SIZE - 1; i >= SIZE / 2; i--)
	{
		if (innerTrack[i].trainIndicator == -1)
			cout << "->-";
		else if (innerTrack[i].trainIndicator == 1)
			cout << "-<-";
		else
			cout << "---";
	}
	cout << " |" << endl;
	// print bottom switches
	cout << "| ";
	for (int i = SIZE / 2 - 1; i >= 0; i--)
	{
		cout << " X ";
	}
	cout << " |" << endl;
	// print bottom outerTrack
	cout << "+-";
	for (int i = SIZE - 1; i >= SIZE / 2; i--)
	{
		if (outerTrack[i].trainIndicator == -1)
			cout << "->-";
		else if (outerTrack[i].trainIndicator == 1)
			cout << "-<-";
		else
			cout << "---";
	}
	cout << "-+" << endl << endl;
	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// initialize where the pointers point to for the track array
int setNext(Segment outerTrack[], Segment innerTrack[])
{
	for (int i = 0; i < SIZE; i++)
	{
		//set each segment's next segment
		if (i < 9)
		{
			outerTrack[i].nextOuter = &outerTrack[i + 1];
			innerTrack[i].nextInner = &innerTrack[i + 1];
		}
		else
		{
			outerTrack[i].nextOuter = &outerTrack[0];
			innerTrack[i].nextInner = &innerTrack[0];
		}
		// set each segment's preceeding segment
		if (i > 0)
		{
			outerTrack[i].lastOuter = &outerTrack[i - 1];
			innerTrack[i].lastInner = &innerTrack[i - 1];
		}
		else
		{
			outerTrack[i].lastOuter = &outerTrack[9];
			innerTrack[i].lastInner = &innerTrack[9];
		}
		
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// mvoe each train once along its track, and make a train change tracks 
// if two are to collide on the next turn
int moveTrains(Segment outerTrack[], Segment innerTrack[])
{
	// these booleans prevent the for loop from moving the same train twice
	// when it moves from index 0 to index 9 or vice versa
	bool outCrossed = false; 
	bool inCrossed = false; 
	for (int i = SIZE - 1; i >= 0; i--) // track "i" to be tested
	{
		// move trains on outer track
		if (outerTrack[i].trainIndicator == 1)
		{
			if (outerTrack[i].nextOuter->trainIndicator == -1) // Top & Bottom tracks: "->--<-" 
			{
				// change tracks
				outerTrack[i].trainIndicator = 0;
				innerTrack[i].trainIndicator = 1;
			}
			else if (outerTrack[i].nextOuter->trainIndicator == 0) // Top: "->----" Bottom: "----<-"
			{
				if (!(outCrossed) || i != 0) // avoid moving twice PART 1
				{
					// move forward
					outerTrack[i].trainIndicator = 0;
					outerTrack[i].nextOuter->trainIndicator = 1; 
				}
				if (i == 9)
				{
					outCrossed = true; // avoid moving twice PART 2
				}
			}
			else if (outerTrack[i].lastOuter->trainIndicator == 1) // T: "->-->-" " B: "-<--<-"
			{
				outerTrack[i].lastOuter->trainIndicator = 0;
				outerTrack[i].nextOuter->trainIndicator = 1;
			}
		}
		// move trains on inner track
		if (innerTrack[i].trainIndicator == 1)
		{
			if (innerTrack[i].nextInner->trainIndicator == -1) // T & B: "->--<-"
			{
				// change tracks
				innerTrack[i].trainIndicator = 0;
				outerTrack[i].trainIndicator = 1;
			}
			else if (innerTrack[i].nextInner->trainIndicator == 0) // T: "->----" B: "----<-"
			{
				if (!(outCrossed) || i != 0) // avoid moving twice PART 1
				{
					// move forward
					innerTrack[i].trainIndicator = 0;
					innerTrack[i].nextInner->trainIndicator = 1;
				}
				if (i == 9)
				{
					outCrossed = true; // avoid moving twice PART 2
				}
			}
			else if (innerTrack[i].lastInner->trainIndicator == 1) // T: "->-->-" " B: "-<--<-"
			{
				// move forward with a train following
				innerTrack[i].lastInner->trainIndicator = 0;
				innerTrack[i].nextInner->trainIndicator = 1;
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		// move trains on outer track
		if (outerTrack[i].trainIndicator == -1)
		{
			if (outerTrack[i].lastOuter->trainIndicator == 1) // T & B: "->--<-" 
			{
				// change tracks
				outerTrack[i].trainIndicator = 0;
				innerTrack[i].trainIndicator = -1;
			}
			else if (outerTrack[i].lastOuter->trainIndicator == 0) // T: "----<-" B: "->----"
			{
				if (!(inCrossed) || i != 9) // avoid moving twice PART 1
				{
					// move forward (negative direction)
					outerTrack[i].trainIndicator = 0;
					outerTrack[i].lastOuter->trainIndicator = -1;
				}
				if (i == 0) 
				{
					inCrossed = true; // avoid moving twice PART 2
				}
			}
		}
		// move trains on inner track
		if (innerTrack[i].trainIndicator == -1)
		{
			if (innerTrack[i].lastInner->trainIndicator == 1) // T & B: "->--<-" 
			{
				// change tracks
				innerTrack[i].trainIndicator = 0;
				outerTrack[i].trainIndicator = -1;
			}
			else if (innerTrack[i].lastInner->trainIndicator == 0) // T: "----<-" B: "->----"
			{
				if (!(inCrossed) || i != 9) // avoid moving twice PART 1
				{
					// move forward (negative direction)
					innerTrack[i].trainIndicator = 0;
					innerTrack[i].lastInner->trainIndicator = -1;
				}
				if (i == 0)
				{
					inCrossed = true; // avoid moving twice PART 2
				}
			}
		}
	}




	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////