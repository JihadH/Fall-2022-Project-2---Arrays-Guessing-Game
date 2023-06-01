/* 	Author: Jihad Hamad, Student ID# 11458410, JihadHamad@my.unt.edu
	Date: November 6, 2022
	Instructor: Dr. Shrestha
	Description: A guessing game program that first asks the user to input their email, and returns an error message if 
    the email format is incorrect. Then asks the user how big an array that is visible to the user should be, restrictions being 10,
    and makes an invisible array of the same size that stores random numeber values between 1 and 20. The program asks what
    co-ordinate would they like to reveal first. Then asks what other co-ordinate they would like to match that value with. If 
    the value of the guessed co-ordinate is the same as the first revealed co-ordinate, the user gets 2 points to their point counter, 
    which starts at 10. If the value isn't the same, the point counter is reduced by 1. After Every guess, the program asks the user
    if they'd like to repeat the program, if so, the program repeats after the array size is asked. If not, the program ends and displays
    the user's points and and their email.
*/


#include <iostream>     // included header files are necessary for program compilment
#include <string>
#include <ctime>
#include <cstdio>
#include <array>
#include <cctype>

using namespace std;


const int ROWS = 10;        // global constant integers of the maximum array sizes of the 2 2D arrays in main
const int COLUMNS = 10;


int rows = ROWS;            // declaring and setting the integer variables that will be used in the array size of the 2 2D arrays in main, set equal to the global constant integers
int columns = COLUMNS;


/*
Function Name: display

Parameters: a 2D array representing the 2D array the user intends to display

Return: a displayed array with the sizes of the inputted array size in the function parameter

Description: a void function that displays the inputted array in a square pattern in the size of the inputted array size
*/


void display(int array[][COLUMNS]){

        for(int i = 0; i < rows; ++i){          // nested loop used to display the array entered in the function parameter
            for(int j = 0; j < columns; ++j){

            cout << array[i][j] << "\t";

            }

        cout << endl;

        }

        cout << endl;


}


/*
Function Name: initialize

Parameters: a 2D array representing the 2D array the user wants initialized
            an integer set whose default is set to -1 

Return: an array with initialized values of either -1, or random numbers between 1 and 20

Description: a void function that initializes the values of an inputted array in the function parameter with either -1 or random number values
depending on if the integer value in the function parameter is overwritten from -1 to a different number
*/


void initialize(int array[][COLUMNS], int defaultNum = -1){

        srand(time(NULL));          // seeding for random number generation


        if( defaultNum == -1){              // an if statement that initializes the values of an array with a nested for loop to -1 if the defaultNum is -1 and random numbers if not
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j){

                array[i][j] = -1;

                }
            }
        }
        else{
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j){

                array[i][j] = (rand() % 20 ) + 1;

                }
            }
        }


    }


/*
Function Name: isWrongFormat

Parameters: a string representing the user entered email 

Return: a bool value

Description: a bool function that returns true if the format of the user entered string is not in correct email format, and false if it is in the correct format
*/


bool isWrongFormat(string email){


        int atPosition;         // two integer values that will store the postiion where the '@' and '.' characters are
        int dotPosition;

        int atAmount = 0;       // two integer values that will store the amount of times the '@' and '.' symbols are found in the user string
        int dotAmount = 0;

        int spaceError = 0;     // an integer value that will store if there are no characters between the start of the email string and where the '@' position is

        bool stringError = false;   // a bool value that is automatically true that represents if there is a problem with the email string format


        atPosition = email.find('@');
        dotPosition = email.find('.');


        for(int i = 0; i < atPosition; i++){    // a series of loops that check if there are letters and numbers between the sections of the string between atPosition and dotPosition

            spaceError++;

            if( !(isalnum(email.at(i))) ){

                stringError = true;

            }
        }


        for(int i = atPosition + 1; i < dotPosition; i++){
            if( !(isalnum(email.at(i))) ){

                stringError = true;

            }
        }


        for(int i = dotPosition + 1; i < email.length(); i++){
            if( !(isalnum(email.at(i))) ){

                stringError = true;

            }
        }


        for(int i = 0; i < email.length(); i++){    // a loop that finds how many times the '@' and '.' characters are in the email string
            if(email.at(i) == '@'){

                atAmount += 1;

            }
            else if(email.at(i) == '.'){

                dotAmount += 1;

            }
        }


        // an if statment that finds all the faults of the email string to find if the function will return true or false

        if( atAmount != 1 || dotAmount != 1 || ((dotPosition - atPosition) == 1) || atPosition > dotPosition || stringError == true 
            || ( email.length() == (dotPosition + 1) ) || spaceError == 0 ){

            cout << "Please enter in a valid email address.\n";
            return true;

        }
        else{

            return false;

        }


}


/*
Function Name: checkRepeat

Parameters: four integer values representing the first reveald Co-ordinate from the user, and the second guessed Co-ordinate value 

Return: a bool value

Description: A bool function that return true if the two user entered Co-ordinates are the same, and false if they are different
*/


bool checkRepeat( int revealedRow, int revealedColumn, int guessedRow, int guessedColumn){

        if( (revealedRow == guessedRow) && (revealedColumn == guessedColumn) ){

            cout << "You can not enter in the already revealed Co-ordinate. >:(\n";

            return true;

        }
        else{

            return false;

        }

}


int main(){


        system("clear");    // clearing the terminal to avoid terminal clutter for the program


        int num_array[ROWS][COLUMNS];   // two integer values that establish the the maximum 2D array sizes of the two user 2D arrays,
        int disp_array[ROWS][COLUMNS];  // disp_array is the displayed array, and num_array is the hidden array with all number values

        int points = 10;                // an integer value representing the starting points of the user, initially set to 10

        int firstRow;                   // two integer values used to store the first revealed row and column co-ordinate from the user 
        int firstCol;

        int guessRow;                   // two integer values used to store the guessed row and column co-ordinate from the user    
        int guessColumn;

        char userOption;                // a character variable that will store the character the represents whether the user would like to repeat the game

        bool gameRepeat = false;        // a bool variable that is used if the user would like to repeat the game 
        bool revealError;               // a bool variable that is used if the co-ordinates that the user entered to reveal the displayed array are the same, aka cheating

        string email;                   // a string variable that store the email of the user


            // a do while loop that receives the user's email and repeats if the bool value of the isWrongFunction is true
        do{

            cout << "What is your email address?: "; cin >> email; cout << "\n";

        }while( isWrongFormat(email) == true);


            // a do while loop that asks and reads in the size of the two 2D arrays and repeats if the user entered array size is less than or greater the array limits
        do{

            cout << "How many Rows?: "; cin >> rows; cout << "\n";
            cout << "How many Columns?: "; cin >> columns; cout << "\n";

            if( rows > COLUMNS || rows <= 1 || columns > COLUMNS || columns <= 1 ){

            cout << "Please enter a valid Row or Column size, the size must be less than 10 and greater than 1.\n";

            }

        }while( rows > ROWS || rows <= 1 || columns > COLUMNS || columns <= 1 );


        num_array[rows][columns];       // establishing the array size of the two 2D arrays
        disp_array[rows][columns];


        initialize(num_array, 1);       // using the initialize function to initialize the two 2D arrays, disp_ array is initialized with -1, and num_array is initialized with random numbers between 1 and 20
        initialize(disp_array, -1);

        display(disp_array);            // displaying the disp_array using the display function

                // starting the do while loop that eventuall loops if the user decides to the repeat the game with the same array size from the start of int main()
        do{

                // a do while loop the reads in the first co-ordinate to be revealed with the num_display value and the other disp_array values

                // if the co-ordinate is outside the array size, an error message is displayed and the loop loops with the revealError boolean
            do{

                cout << "Enter the Co-ordinates you would like to reveal first.\nRow: "; cin >> firstRow; cout << "\nColumn: "; cin >> firstCol; 
                cout << endl;

                if( ((firstRow || firstCol) < 0) || firstRow >= rows || firstCol >= columns ){

                cout << "Invalid Co-ordinates.\nPlease enter correct Co-ordinates that are within your array size.\n";

                revealError = true;

                }
                else{

                revealError = false;

                }

            }while( revealError == true );


        disp_array[firstRow][firstCol] = num_array[firstRow][firstCol]; // setting the value of the first co-ordinate in the array disp_array to the value in the array num_array


        display(disp_array);        // displaying the disp_array with the newly revealed index value



            // a do while loop that check if the guessed co-ordinate is in the array size and if it is the same as the first co-ordinate, loops if user cheated and if co-ordinate is outside array sizes
            do{

            cout << "Enter Co-ordinates to try and match.\nRow: "; cin >> guessRow; cout << "\nColumn: "; cin >> guessColumn; cout << endl;

            if( ((guessRow || guessColumn) < 0) || guessRow >= rows || guessColumn >= columns ){

                cout << "Invalid Co-ordinates.\nPlease enter correct Co-ordinates that are within your array size.\n";

                revealError = true;

                }
                else{

                revealError = false;

                }

            }while( (checkRepeat(firstRow, firstCol, guessRow, guessColumn) == true) || revealError == true );


            // an if statement that checks if the value at the second guessed co-ordinate is the same as the first revealed co-ordinate
            if( num_array[firstRow][firstCol] == num_array[guessRow][guessColumn] ){

                disp_array[guessRow][guessColumn] = num_array[guessRow][guessColumn];

                display(disp_array);        // if co-ordinates match, the points is increased by 2, displays the disp_array, and appropriate message is displayed

                points += 2;

                cout << "Current Points Balance: " << points << "\nYou Found a Match!! =)\n\n";

            }
            else if ( num_array[firstRow][firstCol] != num_array[guessRow][guessColumn] ){

                points = points - 1;        // if co-ordinates do not match, points are decreased by 1 and appropriate message is displayed

                cout << "Current Point Balance: " << points << "\nCo-ordinate Does Not Match First Value. =(\n\n";

            }


            // do while loop breaks if points are less or equal to 0
            if(points <= 0){

                cout << "Sorry, You Ran Out Of Points. =(\n\n";

                break;

            }


            // asking if user would like to repeat the game

        cout << "Would you like to play again? (Y for Yes, N for No): "; cin >> userOption; cout << endl;

            // the character variable is made to an uppercase for the switch case

        userOption = toupper(userOption);

            // switch case for if the user would like to repeat or not, and if the character variable doesn't fit the switch case

            switch(userOption){

                case 'Y':
                gameRepeat = true; break;

                case 'N':
                gameRepeat = false; break;

                default:
                cout << "Invalid Option\n\n"; gameRepeat = false; break;

            }



        }while(gameRepeat == true);


        cout << "Thank You for Playing!!\nCurrent Point Balance: " << points << "\nYour Results will be emailed to you at, " << email << "\n\n";


return 0;
}