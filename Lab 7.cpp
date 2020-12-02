// Dale Weaver
// C++ Fall 2020
// Due 12/2/2020
// Lab 7 Battleship
// The object of this lab is to re create the game battleship where the user can guess cordinates
// and the computer will randomly place 5 ships. They can not overlap or go off the board and should
// display hit or miss.

#include<cassert> //allows for assert function
#include<iostream> //library 
#include<stdlib.h> //for random numbers
#include<time.h> //needed for random number   
#include<iomanip> //for set width
using namespace std;
struct ship                  
{	
	int dir; //assigns the direction
	int hs; //assings the number of hits
	unsigned int s; //assigns the size
	unsigned int x; //assigns the x cord
	unsigned int y; //assigns the y cord
};
struct board          
{
	const char s = '#'; //this assigns # to s or sunk
	const char m = 'M'; //this assigns M to m or miss
	const char h = 'H'; //this assigns H to h or hit
	const char w = '~'; //this assigns ~ to w or water
};
void start(board type, ship american[5], ship russain[5], char american1[][10],char american2[][10], 
	char russain1[][10], char russain2[][10]);
void outputtoscreen(char first[][10], char second[][10]);
void placement(board type, ship ship[5], char first[][10], char second[][10], bool& playerInput);
void dirValid(board type, ship ship[5], char first[][10], bool direction[4], int i, char X, char Y);
void assign(board type, ship ship[5], char first[][10], bool direction[4], bool& val, int i,
	int X, int Y, int dirin);
void attack(board type, ship american[5], ship russian[5], char american1[][10], char american2[][10],
	char russain1[][10], char russain2[][10], int& winnum, int& losenum, bool& playerInput);
void hORm(board type, ship ship[5], char first[][10], char second[][10],char dgrid1[][10], 
	char dgrid2[][10], int& playerScore, bool& playerInput);
void hit(board type, char first[][10], char second[][10], bool& error, bool playerInput,int& score, 
	int X, int Y);
void sink(ship ship[5], bool playerIn, int X, int Y);
void continueOrQuit(bool& surrender);
void inputValid();
//main
int main()                 
{
	board type; //delares board
	ship american[5]; //declares american ships
	ship russain[5]; //declares russain ships
	char american1[10][10]; //declares array for americans
	char american2[10][10];  
	char russain1[10][10]; //declares array for russains
	char russain2[10][10];
	char againInput; //declares what the user enters as a character
	int winnum = 0; //sets winnum to 0
	int losenum = 0; //sets losenum to 0
	srand(unsigned int(time(NULL))); //randomizes
	cout << "Cold War Battleship" << endl; // displays to screen
	do                              
	{                              
		bool playerInput = true; //validates that user wants to play again   
		start(type, american, russain, american1, american2, russain1, russain2); //declares the start of the game
		outputtoscreen(american1, american2); //outputs boards for americans
		cout << "Choose an x coordinate and a y coordinate then choose a direction to place a ship" << endl;
		placement(type, american, american1, american2, playerInput); //declares placement for americans
		placement(type, russain, russain1, russain2, playerInput); //declares placement for russains
		outputtoscreen(russain1, russain2); //outputs boards for russains
		attack(type, american, russain, american1, american2, russain1, russain2, winnum, losenum, playerInput); //declares the player and computer attacking
		cout << "Want to play again? Press 1 to quitor 2 to play again" << endl; //asks user if they want to play again
		cin >> againInput; //assigns what the user input to againinput                      

	} while (againInput == '2'); //if user enters 2, the game displays wins and losses them closes
	cout << "Wins: " << winnum << endl;
	cout << "Losses: " << losenum << endl;
	abort();
}
//places ships on grids
void placement(board type, ship ship[5], char first[][10], char second[][10], bool& playerInput)
{                
	int Y; //asigns the y cordinate as an integer
	int X; //assings the x cordinate as an integer  
	int dInput; //asigns the direction of ship for integer
	bool valid; //validates user input
	bool direction[4]; //assings only 4 directions

	for (int i = 0; i <= 6; i++) //checks to see if input is = to 0 or < or = to 6
	{
		int n1 = 0; //sets n1 to 0
		do
		{
			for (int i = 0; i < 4; i++) //this is for users direction of ship
			{
				direction[i] = true; //validates the number isnt 0 and < than 4
			}
			if (playerInput)
			{
				do
				{
					if (n1 > 0)
					{
						cout << endl << "Invalid coordinates. Try again\n" << endl; //displays to screen
						outputtoscreen(first, second); //loops back to outputtoscreen                                   
					}
					switch (i) //goes from 0 to 4
					{
					case 0: cout << "Where would you like the carrier? (5)\n" << endl; //asks user where they want the carrier
						break;
					case 1: cout << "Where would you like the battleship? (4)\n" << endl; //asks user where they want the battleship
						break;
					case 2: cout << "Where would you like the cruiser? (3)\n" << endl; //asks user where they want the cruiser
						break;
					case 3: cout << "Where would you like the submarine? (3)\n" << endl; //asks user where they want the submarine
						break;
					case 4: cout << "Where would you like the destroyer? (2)\n" << endl; //asks user where they want the destroyer
						break;
					}
					cout << "X: "; //asks user where they want the x cordinate
					cin >> X; //assigns the user input to 'x'
					inputValid(); //calls inputvalid()
					cout << "Y: "; //asks where the user wants the y cordinate
					cin >> Y; //assigns the user input to 'y'
					inputValid(); //calls inputvalid()  
					X = X - 1; //sets x-1 to x
					Y = Y - 1; //sets y-1 to y
					n1++; //adds 1 to n1
				} while ((X < 0 || X > 9) || (Y < 0 || Y > 9)); //checks to validate
			}
			else
			{
				X = rand() % 10 + 0; //randomizes computers choosing of x cordinate  
				Y = rand() % 10 + 0; //randomizes computers choosing of y cordinate
			}
			ship[i].x = X; //assigns the random number for x to x
			ship[i].y = Y; //assigns the random number for y to y
			dirValid(type, ship, first, direction, i, X, Y); //calls dirValid()
		} while ((first[Y][X] == type.s) || (!direction[0] && !direction[1] && !direction[2] && !direction[3]));

		do
		{
			valid = true; //validates to make sure its true
			if (playerInput)
			{
				cout << endl << "What direction?" << endl; //asks user what direction they want to place the ship
				if (direction[0])
					cout << "Right: 1" << endl; //right is 1
				if (direction[1])
					cout << "Left: 2" << endl; //left is 2
				if (direction[2])
					cout << "Down: 3" << endl; //down is 3
				if (direction[3])
					cout << "Up: 4" << endl; //up is 4
				cin >> dInput; //assigns users choice to dInput          
				inputValid(); //calls inputvalid()
			}
			else
			{
				dInput = rand() % 5 + 1; //randomizes dirction for computer
			}
			ship[i].dir = dInput; //asigns random number to dInput
			assign(type, ship, first, direction, valid, i, X, Y, dInput); //calls place() function
			if (valid == false && playerInput) // checks for validity
			{
				cout << endl << "Please choose from one of the options." << endl; //outputs if not valid
				outputtoscreen(first, second); //calls outputtoscreen()
			}
		} while (!valid);
		if (playerInput)
		{
			outputtoscreen(first, second); //calls outputtoscreen()
		}
	}
	if (playerInput)
		playerInput = false;
	else
		playerInput = true;
}
//outputs grids to screen
void outputtoscreen(char first[][10], char second[][10]) //this function actually outputs to screen
{
	cout << "\n          Americans                   Russians" << endl << "     "; //header
	for (int i = 1; i <= 2; i++)
	{
		for (int i = 1; i <= 10; i++)
			cout << " " << i; //adds a space between the numbers for one asix
		cout << setw(11); //sets width to 11 (but actually 10)
	}
	cout << endl;
	for (int i = 0; i < 10; i++)           
	{
		cout << setw(5) << (i + 1) << " "; //sets width between the arrays as 5
		for (int j = 0; j < 10; j++) //adds space between numbers on one axis
		{
			cout << first[i][j] << " "; //displays grid
		}
		cout << setw(10) << (i + 1) << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << second[i][j] << " "; //displays grid
		}
		cout << endl;
	}
	cout << endl;
}
//starts the game
void start(board type, ship american[5], ship russain[5], char american1[][10],
	char american2[][10], char russain1[][10], char russain2[][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			american1[i][j] = type.w; //initalizes american grid with 'w's 
			american2[i][j] = type.w; //initalizes american grid with 'w's 
			russain1[i][j] = type.w; //initalizes russain grid with 'w's 
			russain2[i][j] = type.w; //initalizes russain grid with 'w's 
		}
	}
	for (int i = 0; i < 5; i++)
	{
		american[i].x = 0; russain[i].x = 0; //initalizes loop
		american[i].y = 0; russain[i].y = 0; //initalizes loop
		american[i].dir = 0; russain[i].dir = 0; //initalizes loop
		american[i].hs = 0; russain[i].hs = 0; //initalizes loop

		switch (i) //goes from 0 to 4
		{
		case 0: american[i].s = 5; russain[i].s = 5; break; // asigns russain and american carrier to 5
		case 1: american[i].s = 4; russain[i].s = 4; break; // asigns russain and american battleship to 4
		case 2: american[i].s = 3; russain[i].s = 3; break; // asigns russain and american cruiser to 3
		case 3: american[i].s = 3; russain[i].s = 3; break; // assigns russain and american submarine to 3
		case 4: american[i].s = 2; russain[i].s = 2; break; // assigns russain and american destroyer to 2
		}
	}
}
//assigns the ships direction
void assign(board type, ship ship[5], char first[][10], bool direction[4], bool& val, int i,
	int X, int Y, int dirin)
{
	int S = ship[i].s - 1; //assings ship size -1

	for (S; S >= 0; S--) 
	{
		switch (dirin) 
		{
		case 1: //asigns ship to the right                          
			if (direction[0])
				first[Y][X + S] = type.s;
			else
				val = false;
			break;
		case 2: //asigns ship to the left
			if (direction[1])
				first[Y][X + (S / -1)] = type.s;
			else
				val = false;
			break;
		case 3: //asigns ship downward
			if (direction[2])
				first[Y + S][X] = type.s;
			else
				val = false;
			break;
		case 4: //asigns ship upward
			if (direction[3])
				first[Y - S][X] = type.s;
			else
				val = false;
			break;
		default: val = false;
		}
	}
}

void inputValid() //checks for valid input
{
	if (!cin) //if not valid
		cout << "Invlaid input. Must restart program"; //outputs to screen
	assert(cin); //closes program
}
//determines which direction the ship can be places
void dirValid(board type, ship ship[5], char first[][10], bool direction[4], int i, char X,
	char Y)
{
	int S = ship[i].s - 1;
	for (S; S >= 0; S--)
	{ // essentailly takes the size of the ship and the x or y cordinate and adds the size to see if its less than 1 or greater than 10
		if (first[Y][X + S] != type.w || X + S > 9)
			direction[0] = false; //place ship to the right

		if (first[Y][X + (S / -1)] != type.w || X - S < 0)
			direction[1] = false; //place ship to the left

		if (first[Y + S][X] != type.w || Y + S > 9)
			direction[2] = false; //places ship downward

		if (first[Y - S][X] != type.w || Y - S < 0)
			direction[3] = false; //places ship upward
	}
}
//allows for user and computer to attack the other
void attack(board type, ship american[5], ship russain[5], char american1[][10], char american2[][10],
	char russain1[][10], char russain2[][10], int& winnum, int& losenum, bool& playerInput)
{
	int playerScore = 0; //asings to 0
	int enemyScore = 0; //asigns to 0
	bool surrender = false;

	cout << "Sink all the Russain ships to win!" << endl; //displays to screen
	do
	{
		continueOrQuit(surrender); //calls continueOrQuit()
		if (!surrender)
		{   
			hORm(type, russain, russain1, american2, american1, american2, playerScore, playerInput);//calls hORm
			if (playerScore < 17)//if player has more than 17 hits
			{
				continueOrQuit(surrender);//calls continueOrQuit
				if (!surrender)
					hORm(type, american, american1, russain2, american1, american2, enemyScore, playerInput);//calls hORm
			}
		}
	} while (enemyScore < 17 && playerScore < 17 && surrender == false);//essentially continues 

	if (surrender)//if player surrenders
	{
		cout << endl << "You threw in the towel. You lose." << endl;//out puts to screen
		losenum++; //adds 1 to losenum
	}
	else if (playerScore == 17)//if player has 17 hits
	{
		cout << "You destroyed the Russains! You win!" << endl;// outputs to screen
		winnum++; //adds 1 to winnum
	}
	else
	{
		cout << "The Russains sank all your ships! You lose!" << endl; //outputs to screen
		losenum++; //adds 1 to losenum
	}
}
// checks to see if input was a hit
void hit(board type, char first[][10], char second[][10], bool& error, bool playerInput, int& Score,
	int X, int Y)
{
	if (X < 0 || X > 9 || Y < 0 || Y > 9) //checks input validity
	{
		error = false;
		if (playerInput)
			cout << "Coordinates between 1-10 only." << endl; //outputs to screen
	}
	else if (first[Y][X] == type.h || first[Y][X] == type.m) //if user inputs cordinates twice
	{
		error = false;
		if (playerInput)
			cout << "\nLighting doesn't strike in the same place twice, why should you? Try again." << endl; //outputs to screen
	}
	else if (first[Y][X] == type.s)
	{
		first[Y][X] = type.h; //if choosen 1st cordinate = where ship
		second[Y][X] = type.h; //and if second choosen cordinate = where ship
		Score++; //adds 1 to score
	}
	else if (first[Y][X] == type.w)
	{
		first[Y][X] = type.m; //if theres no ship at first choosen cordinate
		second[Y][X] = type.m; //and no ship at second choosen cordinate, continue
	}
}
//gets users input to check to see of its a hit or miss
void hORm(board type, ship ship[5], char first[][10], char second[][10],
	char dgrid1[][10], char dgrid2[][10], int& score, bool& playerInput)
{
	int X;
	int Y;
	bool error;
	if (!playerInput)
		cout << endl <<"Incoming!" << endl; //outputs to screen
	do
	{
		error = true;
		if (playerInput)
		{
			outputtoscreen(dgrid1, dgrid2);
			cout << "It's our turn to attack! Choose wisely" << endl; //outputs to screen 
			cout << "X: "; //outputs to screen 
			cin >> X; //takes in users x input and assigns it to x
			inputValid(); //calls inputValid()                           
			cout << "Y: ";  //outputs to screen 
			cin >> Y; //tkaes in users input and assigns it to y
			inputValid(); //calls inputValid()
			X = X - 1; //subtracts 1 from x
			Y = Y - 1; //subtracts 1 from y
		}
		else
		{
			X = rand() % 10 + 0; //gets a random number for the computer
			Y = rand() % 10 + 0; //gets a random number for the computer            
		}

		hit(type, first, second, error, playerInput, score, X, Y); //calls hit()

	} while (!error);

	//if (playerInput)
		//cout << "\nBombs away\n";

	outputtoscreen(dgrid1, dgrid2); //calls outputtoscreen()

	if (playerInput)
	{
		if (first[Y][X] == type.h) //if cordinates are a hit
			cout << "Hit!"; //outputs to screen 
		if (first[Y][X] == type.m) //if cordinates are a miss
			cout << "Miss!"; //outputs to screen 
	}
	else
	{
		if (first[Y][X] == type.h) //if computer cordinates are a hit
			cout << "We've been hit!" << endl << endl; //outputs to screen 
		if (first[Y][X] == type.m) //if computer cordinates are a miss
			cout << "We were missed!" << endl << endl; //outputs to screen 
	}
	sink(ship, playerInput, X, Y);
	if (playerInput)
		playerInput = false;
	else
		playerInput = true;
}
//checks to see if the players attack sank the ship
void sink(ship ship[5], bool playerInput, int X, int Y)
{
	for (int i = 0; i < 5; i++)
	{
		int S = ship[i].s - 1;
		for (S; S >= 0; S--)
		{
			switch (ship[i].dir)
			{
			case 1:
				if (ship[i].y == Y && ship[i].x + S == X)
					ship[i].hs++; // right
				break;
			case 2:
				if (ship[i].y == Y && ship[i].x - S == X)
					ship[i].hs++; // left
				break;
			case 3:
				if (ship[i].y + S == Y && ship[i].x == X)
					ship[i].hs++; // down
				break;
			case 4:
				if (ship[i].y - S == Y && ship[i].x == X)
					ship[i].hs++; // up
				break;
			}
		}
		if (playerInput)
		{
			if (ship[i].hs == ship[i].s) //if the number of hits a ship has = the size of ship
			{
				cout << "Sunk!\n\n"; //outputs to screen 
				ship[i].hs++;
			}
		}
		else
		{
			if (ship[i].hs == ship[i].s)
			{
				switch (i)
				{
				case 0: cout << "Your Carrier has been sunk!\n"; //outputs to screen   
					break;
				case 1: cout << "Your Battleship has been sunk!\n"; //outputs to screen 
					break;
				case 2: cout << "Your Cruiser has been sunk!\n"; //outputs to screen    
					break;
				case 3: cout << "Your Submarine has been sunk!\n"; //outputs to screen   
					break;
				case 4: cout << "Your Destroyer has been sunk!\n"; //outputs to screen   
					break;
				}
				ship[i].hs++;
			}
		}
	}
}
// this part sees if the user wants to continue or quit
void continueOrQuit(bool& surrender)
{
	char input; //assings input as a character
	do
	{
		cout << "Would you like to continue? " << endl; //asks user if they want to continue
		cout << "Enter Y for yes or enter N to wave the white flag." << endl; //outputs to screen 
		cin >> input; //takes users input and assigns it to input

	} while (input != 'Y' && input != 'N' && input != 'y' && input != 'n'); //checks users input

	if (input == 'N' || input == 'n') //if users input is N or n
		surrender = true; //surrender
}