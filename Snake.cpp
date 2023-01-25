#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
bool GameOver;
const int height = 20, width = 40;// Size of field
int x, y, fruit_x, fruit_y;//coordination of snake and fruit
int tailX[50], tailY[50];// Array with snake body coordinates
int nTail; // For number of elements in the tail of the snake
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void SetColor(int text, int bg);
void hidecursor();
void draw();
void logic();
int main() {
	hidecursor();
    GameOver = false;
    x = width / 2 ;   // setting the snake at the center of the field
    y = height / 2;
    while(!GameOver){
        draw();
        logic();
    }
    system("pause"); 
}
void SetColor(int text, int bg){
    SetConsoleTextAttribute(console, (WORD)((bg << 4) | text));
}
void hidecursor(){ 				//setting the size and visibility of the cursor
	CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(console, &info);
}
void draw() { 					// draws the field, borders and its elements (fruit and snake), draws a new snake body element if the fruit is eaten
COORD coord; 
coord.X = 0; 
coord.Y = 0; 
SetConsoleCursorPosition(console, coord); 
// drawing top line of field
    for (int i = 0; i < width+1; i++){ 
    	SetColor(6, 0);
        cout << ".";
    }
    cout << endl;
// drawing Side lines of field
    for (int i = 0; i < height-1; i++){
        for (int j = 0; j < width; j++){
            if (j == 0 || j == width - 1){
        	SetColor(6, 0);
            cout << ".";
        }
// Drawing the head of snake
        if (i == y && j == x){
        	SetColor(9, 0);
            cout << char(1);
        }
// Drawing the fruit
        else if (i == fruit_y && j == fruit_x){
        	SetColor(2, 0);
            cout << char(254);
        }
// Checking if the snake eat the fruit, if it's true drawing a new element of the snake
        else{
        	bool print = false;
        	for(int k = 0; k < nTail; k++){
        		if ( tailX[k] == j && tailY[k] == i){
        			print = true;
        			SetColor(6, 0);
        			cout<< char(3);
				}	
			}
        	if (!print)
            cout << " ";
        }
    }
    cout << endl;
    }
// drawing botom line of field
    for (int i = 0; i < width+1; i++){ 
    	SetColor(6, 0);
        cout << ".";
    }
    cout << endl;
    SetColor(2, 0);
    cout<< "Score:" << nTail << endl;
}
void logic() {					/*reads the selected direction, moves the elements of the snake one by one in the specified direction, 
								checks whether the snake hit the wall or itself, increases the points and generates a new fruit;*/
//overwrite the coordinates of each element of the snake in the previous position when moving
	int prevX= tailX[0];
	int prevY= tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for(int i=1; i<nTail; i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	int code;
	int temp_code;// key what was hit first.
	Sleep(100);   // speed of snake
        if(_kbhit()){
        temp_code = _getch();
        if(temp_code=='w'|| temp_code=='s'|| temp_code=='a'|| temp_code=='d')
            code=temp_code;
       }
     	if(_kbhit()){
            code = _getch();
        }
    else{
            cout << ' ' ;
            if(code=='w')
				y--;
            else if(code=='s')
				y++;
            else if(code=='a')
				x--;
            else if(code=='d')
				x++;
        }	
//Checking if you hit a bord so its Game Over
     if( x > width-2 || x < 0 || y > height-1 || y < 0){
	 GameOver=true;
	 SetColor(4, 0);
	 cout<<"Game Over"<<endl;	 
	 }	
//Checking if you hit the tail so its Game Over 		
    for(int i=0; i < nTail; i++){ 
    	if(tailX[i]== x && tailY[i] == y){
    		GameOver = true;
    		cout<<"Game Over"<<endl;
		}
	} 
// Eating the fruit and adding the score and random fruit on field
    if (x == fruit_x && y == fruit_y){
    	fruit_x = rand() % (width-2);  
    	fruit_y = rand() % (height-2);
    	nTail++;
	}
	
}

