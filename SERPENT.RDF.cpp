
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int height = 20;
const int width = 80;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100], nTail;


enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirection dir;

void SetConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    
}

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 3;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;

    // Hide console cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 10;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
  
    
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);
    MoveWindow(console, rect.left, rect.top, width * 8.8, height * 24, TRUE);
    

}

void Draw(int choice) {
	
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    for (int i = 0; i < 82; i++) {
        SetConsoleColor(11); // Set color to white
        cout << "Ы";
    }
    cout << endl;
    
    /*for (int i = 0; i < 82; i++) {
        SetConsoleColor(9); // Set color to white
        cout << "Ы";
    }
    cout << endl;*/
    

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                SetConsoleColor(11); // Set color to white    //wall right left
                cout << "ЫЫ";  //Г   Е  Ж   М  ф
            }
            else if ((i == height/2 - 2 || i == height/2 + 2) && (j >= width/4 && j <= 3*width/4) && choice==2) {
                SetConsoleColor(11); // Set color to white
                cout << "Ы";                  //walls easy mode
            }
            else if ((i == height/4 ) && (j >= width/60 &1& j <= 2*width/4) && choice == 1) {
                SetConsoleColor(11); // Set color to white
                cout << "Ы";                //walls hard mode
            }
            else if ((i == height/2 + 1) && (j >= width/2 ) && choice==1) {
                SetConsoleColor(11); // Set color to white
                cout << "Ы";              //walls hard mode
            }
            
            else if (i == y && j == x) {
                SetConsoleColor(7); // Set color to green for snake
                cout << "й";  //  й
            }
            
            else if (i == fruitY && j == fruitX) {
                SetConsoleColor(4); // Set color to red for fruit
                cout << "•";
            }
            
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (i == tailY[k] && j == tailX[k]) {
                        SetConsoleColor(7); // Set color to green for snake body
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < 82; i++) {
        SetConsoleColor(11); // Set color to white
        cout << "Ы";
    }
    
    cout << endl;
    
    /*for (int i = 0; i < 82; i++) {
        SetConsoleColor(9);
        cout << "Ы";
    }
    cout << endl;*/

    SetConsoleColor(6); // Set color to light cyan
    
    cout << "\t\t\t\t\t\t\t\t      SCORE: " << score << endl;
     for (int i = 0; i < 25; i++) {
     	SetConsoleColor(6);
     	cout<<"-";
     }
     cout<< "\032[S E R P E N T . R D F]\033";
      for (int i = 0; i <32 ; i++) {
     	SetConsoleColor(6);
     	cout<<"-";
     }
    
     cout<<" Press Enter to play again "<<endl;
     
     
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 72: // Up arrow key
            if (dir != DOWN)
                dir = UP;
            break;

        case 75: // Left arrow key
            if (dir != RIGHT)
                dir = LEFT;
            break;

        case 80: // Down arrow key
            if (dir != UP)
                dir = DOWN;
            break;

        case 77: // Right arrow key
            if (dir != LEFT)
                dir = RIGHT;
            break;

        default:
            break;
        }
    }
    
}


void Logic(int choice) {
	
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    default:
        break;
    }
    
    if (choice == 2) {
        if (x < 0)
            x = width - 2;
        else if (x >= width - 0)
            x = 0;
        if (y < 0)
            y = height - 2;
        else if (y >= height - 0)
            y = 0;
    }
    
if (x < 0 || x >= width - 0 || y < 0 || y >= height - 0 || 
        (choice == 1 && ((y == height/4) && (x >= width/60 && x <= 2*width/4)))) {
        SetConsoleColor(4);
        gameOver = true;
    }
    // ((i == height/2) && (j >= width/2 ) && choice==2)
    if (x < 0 || x >= width - 0 || y < 0 || y >= height - 0 || 
        (choice == 1 && ((y == height/2 + 1) && (x >= width/2)))) {
        SetConsoleColor(4);
        gameOver = true;
    }

    if (x < 0 || x >= width - 0 || y < 0 || y > height - 0 || 
        (choice == 2 && ((y == height/2 - 2 || y == height/2 + 2) && (x >= width/4 && x <= 3*width/4)))) {
        SetConsoleColor(4);
        gameOver = true;
    }

    // Check if the fruit falls on a wall position
    if ((fruitY == height/4) && (fruitX >= width/60 && fruitX <= 2*width/4) && choice == 1) {
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    else if ((fruitY == height/2 + 1) && (fruitX >= width/2) && choice == 1) {
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    else if ((fruitY == height/2 - 2 || fruitY == height/2 + 2) && 
             (fruitX >= width/4 && fruitX <= 3*width/4) && choice == 2) {
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    
    if (x < 0 || x >= width || y < 0 || y >= height) {
    SetConsoleColor(4);
        gameOver = true;
    }
    

    for (int i = 0; i < nTail; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            gameOver = true;
        }
    }
	
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    
}
 

int main() {

	HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);
    MoveWindow(console, rect.left, rect.top, width * 8.8, height * 24, TRUE);

    int option;
    int choice;
    SetConsoleColor(6);//49 37  65
    cout << "Welcome to Serpent.RDF!\n" << endl;
    SetConsoleColor(11);
    cout <<"Select Mode:\n";
    SetConsoleColor(4);
    cout << "1 - Hard\n";
    SetConsoleColor(2);
    cout << "2 - Easy\n";

    SetConsoleColor(15);
    cin >> choice;
    
    SetConsoleColor(11);
    cout << "Please select an option:" << endl;
    SetConsoleColor(15);
    cout << "1. Instructions" << endl;
    SetConsoleColor(15);
    cout << "2. Start the Game" << endl;
    
    SetConsoleColor(15);
    cin >> option;

    if (option == 1) {
        // Display instructions
        SetConsoleColor(11);
        cout << "Instructions:" << endl;
        SetConsoleColor(15);
        cout << ">Use the arrow keys to control the snake." << endl;
        cout << ">Snake has to eat the food to get a score." << endl;
        cout << ">The snake must not hit the wall(in hard mode) or its own tail." << endl;
        cout << ">Enter to start the game.\n" <<endl;
        SetConsoleColor(6);
        cout <<"HAVE FUN!:)" <<endl;

        _getch(); // Wait for a key press
    }


    if(gameOver=true){
    	Setup();
	}
    Setup();
    while (true) {
        while (!gameOver) {
            Draw(choice);
            Input();
            Logic(choice);
            Sleep(0);  // Adjust the delay for smoother movement
        }
        char key = _getch();
       if (key == 13) {
            gameOver = false;
            score = 00;
            nTail = 00;
            Setup(); // Reset the game if Enter key is pressed
        }
    }
    return 0;
}
/*
0 - Black
1 - Blue
2 - Green
3 - Cyan
4 - Red
5 - Magenta
6 - Yellow
7 - Light Gray
8 - Dark Gray
9 - Light Blue
10 - Light Green
11 - Light Cyan
12 - Light Red
13 - Light Magenta
14 - Light Yellow
15 - White
*/

/* char key = _getch();
        if (key == 27) {
            break; // Exit the game loop if ESC key is pressed
        }*/
        
        
        
        //Ь   Ы   Э
        
        
        /*if (choice==2){
			
            if ((j == width / 3 || j == 2 * width / 3) && i > height / 4 && i < 3 * height / 4) {
                SetConsoleColor(0); // Set color to white
                cout << "ЫЫ";
            }
        }*/
        
        /*if (choice==2){
	
   if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;};*/
        
       
