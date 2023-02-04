#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
bool gameOver;
const int HEIGHT = 20, WIDTH = 40;// Size of field
int x, y, fruitX, fruitY;//coordination of snake and fruit
int tailX[50], tailY[50];// Array with snake body coordinates
int nTail; // For number of elements in the tail of the snake
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(int text, int bg);
void hidecursor();
void draw();
void logic();
int main() {
	hidecursor();
    gameOver = false;
    x = WIDTH / 2 ;   // setting the snake at the center of the field
    y = HEIGHT / 2;
    while(!gameOver){
        draw();
        logic();
    }
    system("pause"); 
}
void setColor(int text, int bg){
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
    for (int i = 0; i < WIDTH+1; i++){ 
    	setColor(6, 0);
        cout << ".";
    }
    cout << endl;
// drawing Side lines of field
    for (int i = 0; i < HEIGHT-1; i++){
        for (int j = 0; j < WIDTH; j++){
            if (j == 0 || j == WIDTH - 1){
        	setColor(6, 0);
            cout << ".";
        }
// Drawing the head of snake
        if (i == y && j == x){
        	setColor(9, 0);
            cout << char(1);
        }
// Drawing the fruit
        else if (i == fruitY && j == fruitX){
        	setColor(2, 0);
            cout << char(254);
        }
// Checking if the snake eat the fruit, if it's true drawing a new element of the snake
        else{
        	bool print = false;
        	for(int k = 0; k < nTail; k++){
        		if ( tailX[k] == j && tailY[k] == i){
        			print = true;
        			setColor(6, 0);
        			cout<< char(3);
				}	
			}
        	if (!print)
            cout << " ";
        }
    }
    cout << endl;
    }
// Drawing botom line of field
    for (int i = 0; i < WIDTH+1; i++){ 
    	setColor(6, 0);
        cout << ".";
    }
    cout << endl;
    setColor(2, 0);
    cout<< "Score:" << nTail << endl;
}
void logic() {					/*Reads the selected direction, moves the elements of the snake one by one in the specified direction, 
								checks whether the snake hit the wall or itself, increases the points and generates a new fruit;*/
//Overwrite the coordinates of each element of the snake in the previous position when moving
	int prevX= tailX[0];
	int prevY= tailY[0];
	int tempX, tempY;
	tailX[0] = x;
	tailY[0] = y;
	for(int i=1; i<nTail; i++){
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
	}
	int code;
	int tempCode;// key what was hit first.
	Sleep(100);   // speed of snake
        if(kbhit()){
        tempCode = getch();
        if(tempCode=='w'|| tempCode=='s'|| tempCode=='a'|| tempCode=='d')
            code=tempCode;
       }
     	if(_kbhit()){
            code = getch();
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
     if( x > WIDTH-2 || x < 0 || y > HEIGHT-1 || y < 0){
	 gameOver=true;
	 setColor(4, 0);
	 cout<<"Game Over"<<endl;	 
	 }	
//Checking if you hit the tail so its Game Over 		
    for(int i=0; i < nTail; i++){ 
    	if(tailX[i]== x && tailY[i] == y){
    		gameOver = true;
    		cout<<"Game Over"<<endl;
		}
	} 
// Eating the fruit and adding the score and random fruit on field
    if (x == fruitX && y == fruitY){
    	fruitX = rand() % (WIDTH-2);  
    	fruitY = rand() % (HEIGHT-2);
    	nTail++;
	}
	
}

