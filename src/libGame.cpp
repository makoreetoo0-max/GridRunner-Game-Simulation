module;

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

export module libGame;

using onedarray = int*;
export using twodarray = int**;
// game items array 
const char gameitems[6] = {'P', 'T', '#', 'E', 'G', '.'};
//enum 
enum GAMEITEM {
    PLAYER,
    TRAPS,
    OBSTACLE,
    ENERGY,
    GOAL,
    SPACE
};

// Error codes.
export const int SUCCESS = 0;
export const int NUM_ARGS = 6;
export const int ERROR_ARGV = -2;
export const int ERR_CONV = -3;
export bool blncontinue = true;
export bool gamewin = false;
export int energylevel = 10;
export char option;


// Global variables for player position
int PCol = -1;
int PRow = -1 ;
bool isbound = false;

namespace NavigatorSpace {
    // allocates memory to the array
    export twodarray alloc(int rows, int cols) {
        twodarray arr;
        arr = new onedarray[rows];
        for (int r = 0; r < rows; r++) {
            arr[r] = new int[cols];
        }
        return arr;
    }

    // deallocates memory to the array
    export void dealloc(twodarray& arr, int rows) {
        for (int r = 0; r < rows; r++) {
            delete[] arr[r];
        }
		//deallocation of memory in outer pointer 
        delete[] arr;
        arr = nullptr;
    }

    // random number generator - FIXED
    int GetRandom(int min, int max) {
        return min + rand() % (max - min + 1);
    }
//checks if desired movement is within bounds
    bool Isinbounds(int rows, int cols, int Dcol, int Drow) {
        if (Drow < 0 || Dcol < 0 || Drow >= rows || Dcol >= cols) {
            return false;
        } else {
            return true;
        }
    }
// function display array prints outs array
    export void displayarray(twodarray arr, int rows, int cols) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int index = arr[r][c];
                std::cout << gameitems[index] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        // Display Menu
        std::cout << "Up: W(w)" << std::endl
                  << "Down: S(s)" << std::endl
                  << "Right: D(d)" << std::endl
                  << "Left: A(a)" << std::endl
                  << "Quit: Q(q)" << std::endl
                  << "Energy level : " << energylevel << std::endl
                  << "Enter a move: ";
    }
//converts arguements from char to integer 
    export int convToInt(char* strArg) {
        std::stringstream ssConv(strArg);
        int intResult = 0;
        ssConv >> intResult;
        if (ssConv.fail()) {
            std::cerr << "Failed to convert to int" << std::endl;
            exit(ERR_CONV);
        }
        return intResult;
    }
// function places features in the array 
    void placegameitems(twodarray arr, int rows, int cols, GAMEITEM game, int numgameitems) {
        int FRows = 0;
        int FCols = 0;
        for (int i = 0; i < numgameitems; i++) {
            FRows = GetRandom(0, rows - 1);
            FCols = GetRandom(0, cols - 1);
            while (arr[FRows][FCols] != SPACE) {
                FRows = GetRandom(0, rows - 1);
                FCols = GetRandom(0, cols - 1);
            }
			//imputs gameitems to the array 
            arr[FRows][FCols] = game;
        }
    }
// function places each feature in the array using the converted command arguements
    export void makegame(twodarray arr, int rows, int cols, int numtraps, int numobstacle, int numenergy) {
		
        // Initialize all cells to SPACE
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                arr[r][c] = SPACE;
            }
        }
        
        // players position is chosen randomly 
        PRow = rows;
        PCol = GetRandom(0, cols - 1);
		
		// PUTS THE PLAYER IN A RANDOM COLUMN IN THE bottom ROW 
        arr[PRow-1][PCol] = PLAYER;
		
		// puts the goal int random column in the top row 
        arr[0][PCol]= GOAL;
		
        std::cout << "Player Position at: [" << PRow << "][" << PCol << "]" << std::endl;
        //all game items are placed in the array 
        placegameitems(arr, rows, cols, TRAPS, numtraps);
        placegameitems(arr, rows, cols, OBSTACLE, numobstacle);
        placegameitems(arr, rows, cols, ENERGY, numenergy);
        
    }
// function finds the position of the player 
    int findplayer(twodarray arr, int rows, int cols, int& PRow, int& PCol) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
				//searches for the player
                if (arr[r][c] == PLAYER) {
                    PRow = r;
                    PCol = c;
                    return 0;
                }
            }
        }
        return -1;
    }

    export void moveplayer(twodarray arr, int cols, int rows, int& energylevel,char option) {
        //int PRow;
		//int PCol = -1;
		if (energylevel <= 0) {
            std::cout << "Defeat" << std::endl;
            blncontinue = false;
            return;
        }else {
        
        // Update player position from the array
        findplayer(arr, rows, cols, PRow, PCol);
        int Drow = PRow;
        int Dcol = PCol; 
		//case structure to allow for adjustment for movement of player 
      switch (toupper(option)) {
            case 'W': {
                Drow = Drow - 1; // player moves up 
                break;
            }
            case 'A': {
                Dcol = Dcol - 1;// player moves to the left
                break;
            }
            case 'S': {
                Drow = Drow + 1;// player moves down
                break;
            }
            case 'D': {
                Dcol = Dcol + 1;// player moves to the right 
                break;
            }
        }
        
        if (Isinbounds(rows, cols, Dcol, Drow) ) {
            if (arr[Drow][Dcol] == SPACE) {
                arr[Drow][Dcol] = PLAYER;
                arr[PRow][PCol] = SPACE;
                energylevel -= 1;
            }
            else if (arr[Drow][Dcol] == ENERGY) {
                arr[Drow][Dcol] = PLAYER;
                arr[PRow][PCol] = SPACE;
                energylevel += 5;
				std:: cout<<"More Energy More Moves "<<std::endl;
            }
            else if (arr[Drow][Dcol] == OBSTACLE) {
				//player cant move since there is an onstcle 
                std::cout << "Player Cant go this way find another route" << std::endl;
				
                // Don't move
            }
            else if (arr[Drow][Dcol] == TRAPS) {
                arr[Drow][Dcol] = PLAYER;
                arr[PRow][PCol] = SPACE;
				//player is trapped and loses energy 
                //player loses 3 energy points 
				energylevel -= 3;
                
            }
            else if (arr[Drow][Dcol] == GOAL) {
                arr[Drow][Dcol] = PLAYER;
                arr[PRow][PCol] = SPACE;
                std::cout << "Victory !" << std::endl;
				//game over since palyer reached the goal
                gamewin = true;
            }
        } else {
            std::cout << "Move out of bounds!" << std::endl;
        }
    }
	}    
}