// import of libGame 
import libGame;

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace NavigatorSpace;
//command line argumenst 
int main(int argc, char **argv) {
    srand(time(nullptr));
// checks if the number of arguments is enough 
    if (argc != NUM_ARGS) {
        cerr << "Wrong number of arguments" << endl;
        exit(-1);
    }
//initialisation of global varibales using command line arguments 
    int rows = convToInt(argv[1]);
    int cols = convToInt(argv[2]);
    int numtraps = convToInt(argv[3]);
    int numobstacle = convToInt(argv[4]);
    int numenergy = convToInt(argv[5]);
	
//allocation of array 
    twodarray arr = alloc(rows, cols);
	
//placing of gameitems in the array 
    makegame(arr, rows, cols, numtraps, numobstacle, numenergy);
	
// loops until game is won or option selected is Q  
    do {
		system("cls");
        displayarray(arr, rows, cols);
        cout << endl;
		//input of option
        cin >> option;

        switch (toupper(option)) {
            case 'W':
            case 'A':
            case 'S':
            case 'D': {
				//use of function moveplayer to move player 
                moveplayer(arr, cols, rows, energylevel, option);
                break;
            }
            case 'Q': {
                cout << "Good Bye !!!" << endl;
                blncontinue = false;
                break;
            }
			//invalid inputs 
            default: {
                cerr << "invalid input" << endl;
                cin.clear();
                cin.ignore();
                break;  
            }
        }
//stops game 
        if (gamewin) {
            blncontinue = false;
        }
        if (energylevel <= 0 && !gamewin) {
            cout << "Deafeat" << endl;
            blncontinue = false;
        }
      //loops   
    } while (blncontinue);
//deallocation of arr 
    dealloc(arr, rows);
    return 0;
}