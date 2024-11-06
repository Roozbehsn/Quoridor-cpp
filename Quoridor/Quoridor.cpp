#include <queue>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <utility>
using namespace std;
//player1 cordination
int x_p1 = 17;
int y_p1 = 17;
//player2 cordination
int x_p2 = 17;
int y_p2 = 1;
//player1 and player2 wall amount
int P1_wall = 10;
int P2_wall = 10;
/* possible horizontal wall placment counter */
int wall_h1 = 9;
int wall_h2 = 9;
int wall_h3 = 9;
int wall_h4 = 9;
int wall_h5 = 9;
int wall_h6 = 9;
int wall_h7 = 9;
int wall_h8 = 9;
/*possible vertical wall placement counter*/
int wall_v1 = 9;
int wall_v2 = 9;
int wall_v3 = 9;
int wall_v4 = 9;
int wall_v5 = 9;
int wall_v6 = 9;
int wall_v7 = 9;
int wall_v8 = 9;
/*show the winner*/
bool winner = true;
bool turn_play = true;

// Vectors to store wall positions
vector<pair<int, int>> horizontal_walls;
vector<pair<int, int>> vertical_walls;

vector<int>P_All_y;
vector<int>P_All_x;
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawHorizontalLine(int length)
{
	for (int i = 1; i < length; ++i)
	{
		cout << "+---";
	}
	cout << "+" << endl;
}
void drawEmptyLine(int length)
{
	for (int i = 1; i < length; ++i)
	{
		cout << "|   ";
	}
	cout << "|" << endl;
}
void board()
{
	const int size = 10;
	for (int i = 1; i < size; ++i)
	{
		drawHorizontalLine(size);
		drawEmptyLine(size);
	}
	drawHorizontalLine(size);
}

void cord_P1()
{
gotoxy(x_p1,y_p1);
 cout << "P1";
}
void cord_P2()
{
	gotoxy(x_p2, y_p2);
	cout << "P2";
}

bool check_Up_P1() {
	for (const auto& wall : horizontal_walls) {
		if (wall.second == y_p1 - 1 && wall.first <= x_p1 && wall.first + 4 > x_p1) {
			return false;
		}
	}
	return y_p1 > 1; // Ensure not moving out of bounds
}
bool check_Down_P1() {
	for (const auto& wall : horizontal_walls) {
		if (wall.second == y_p1 + 1 && wall.first <= x_p1 && wall.first + 4 > x_p1) {
			return false;
		}
	}
	return y_p1 < 17; // Ensure not moving out of bounds
}
bool check_Left_P1() {
	for (const auto& wall : vertical_walls) {
		if (wall.first == x_p1 - 4 && wall.second <= y_p1 && wall.second + 2 > y_p1) {
			return false;
		}
	}
	return x_p1 > 1; // Ensure not moving out of bounds
}
bool check_Right_P1() {
	for (const auto& wall : vertical_walls) {
		if (wall.first == x_p1 + 4 && wall.second <= y_p1 && wall.second + 2 > y_p1) {
			return false;
		}
	}
	return x_p1 < 33; // Ensure not moving out of bounds
}

bool check_Up_P2() {
	for (const auto& wall : horizontal_walls) {
		if (wall.second == y_p2 + 1 && wall.first <= x_p2 && wall.first + 4 > x_p2) {
			return false;
		}
	}
	return true;
}
bool check_Down_P2() {
	for (const auto& wall : horizontal_walls) {
		if (wall.second == y_p2 - 1 && wall.first <= x_p2 && wall.first + 4 > x_p2) {
			return false;
		}
	}
	return y_p2 < 17; // Ensure not moving out of bounds
}
bool check_Left_P2() {
	for (const auto& wall : vertical_walls) {
		if (wall.first == x_p2 - 4 && wall.second <= y_p2 && wall.second + 2 > y_p2) {
			return false;
		}
	}
	return x_p2 > 1; // Ensure not moving out of bounds
}
bool check_Right_P2() {
	for (const auto& wall : vertical_walls) {
		if (wall.first == x_p2 + 4 && wall.second <= y_p2 && wall.second + 2 > y_p2) {
			return false;
		}
	}
	return x_p2 < 33; // Ensure not moving out of bounds
}

void setColor(WORD attributes) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, attributes);
}
	
void drawWalls() {
	for (const auto& wall : horizontal_walls) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		WORD saved_attributes = consoleInfo.wAttributes;
		setColor(FOREGROUND_RED);
		gotoxy(wall.first, wall.second);
		cout << "---";
		setColor(saved_attributes);
	}
	for (const auto& wall : vertical_walls) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		WORD saved_attributes = consoleInfo.wAttributes;
		setColor(FOREGROUND_RED);
		gotoxy(wall.first, wall.second);
		cout << "|";
		setColor(saved_attributes);
	}
}

void Game_Instruction()
{
	cout << "Hello,welcome to Quoridor game.In this game every player try to reach the last row,every one have 10 wall that they can use"<<endl;
	cout << "Good luck and have fun"<<endl;
}
/*void wallplacement_P1()
{
	char placement;
	int cord_wall_x;
	int cord_wall_y;
	//for (int z = 0; z < 20; z++)cout << endl;
	cout << "Enter H for horizontal and V for vertical:"<<endl;
	cin >> placement;
	if (placement == 'H')
	{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD saved_attributes = consoleInfo.wAttributes;
	cout << "Enter x and y:"<<endl;
	cin >>cord_wall_x >>cord_wall_y;
	horizontal_walls.push_back({ cord_wall_x, cord_wall_y });
	P_All_y.push_back(cord_wall_y);
	if (cord_wall_y == 2)
	{
	  while (wall_h1>1)
	{
		  if (P1_wall == 0)
		  {
			  cout << "You dont have any wall left, you can not place one" << endl;
			  break;
		  }
		else if (wall_h1 == 1)
		{
			cout << "You can not place wall here!";
			break

		}
		else
		{
		setColor(FOREGROUND_RED);
		gotoxy(cord_wall_x,cord_wall_y);
		cout << "---";
		setColor(saved_attributes);
		P1_wall--;
		wall_h1--;
		//cin.get();
		//if (wall_h1 == 0)continue;
		}
	}
	}
	else if (cord_wall_y == 4)
	{

	while (wall_h2 > 1)
	{
		if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
		else
		{
			setColor(FOREGROUND_RED);
			gotoxy(cord_wall_x, cord_wall_y);
			cout << "---";
			setColor(saved_attributes);
			P1_wall--;
			wall_h2--;
			//cin.get();
			//if (wall_h2 == 0) continue;
		}
	}
	}
	else if (cord_wall_y == 6)
	{
	while (wall_h3 >= 1)
	{
		if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
		
		else
		{
			setColor(FOREGROUND_RED);
			gotoxy(cord_wall_x, cord_wall_y);
			cout << "---";
			setColor(saved_attributes);
			P1_wall--;
			wall_h3--;
			//cin.get();
			if (wall_h3 == 0)continue;
		}
	}
	}
	else if (cord_wall_y == 8)
	{

	while (wall_h4 >= 1)
	{
		if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
		else
		{
			setColor(FOREGROUND_RED);
			gotoxy(cord_wall_x, cord_wall_y);
			cout << "---";
			setColor(saved_attributes);
			P1_wall--;
			wall_h4--;
			//cin.get();
			if (wall_h4 == 0)continue;
		}
	}
	}
	else if (cord_wall_y == 10)
	{
	while (wall_h5 >= 1)
	{
		if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
		else
		{
			setColor(FOREGROUND_RED);
			gotoxy(cord_wall_x, cord_wall_y);
			cout << "---";
			setColor(saved_attributes);
			P1_wall--;
			wall_h5--;
			//cin.get();
			if (wall_h5 == 0)continue;
		}
	}
	}
	else if (cord_wall_y == 12)
	{
	while (wall_h6 >= 1)
	{
		if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
		else
		{
			setColor(FOREGROUND_RED);
			gotoxy(cord_wall_x, cord_wall_y);
			cout << "---";
			setColor(saved_attributes);
			P1_wall--;
			wall_h6--;
			//cin.get();
			if (wall_h6 == 0)continue;
		}
	}
	}
	else if (cord_wall_y == 14)
	{
	while (wall_h7 >= 1)
	{
		if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
		else
		{
			setColor(FOREGROUND_RED);
			gotoxy(cord_wall_x, cord_wall_y);
			cout << "---";
			setColor(saved_attributes);
			P1_wall--;
			wall_h7--;
			//cin.get();
			if (wall_h7 == 0)continue;
		}
	}
	}
	else if (cord_wall_y == 16)
	{
	while (wall_h8 >= 1)
	{
		if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
		else
		{
			setColor(FOREGROUND_RED);
			gotoxy(cord_wall_x, cord_wall_y);
			cout << "---";
			setColor(saved_attributes);
			P1_wall--;
			wall_h8--;
			//cin.get();
			if (wall_h8 == 0)continue;
		}
	}
	}
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		WORD saved_attributes = consoleInfo.wAttributes;
		cout << "Enter x and y:"<<endl;
		cin >> cord_wall_x >> cord_wall_y;
		P_All_x.push_back(cord_wall_x);
		vertical_walls.push_back({ cord_wall_x, cord_wall_y });
		if (cord_wall_x == 4)
		{
			while (wall_v1 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v1--;
					//cin.get();
					if (wall_v1 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 8)
		{
			while (wall_v2 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v2--;
					cin.get();
					if (wall_v2 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 12)
		{
			while (wall_v3 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v3--;
					cin.get();
					if (wall_v3 == 0)continue;
				}
			}
		}
	    if (cord_wall_x == 16)
		{
			while (wall_v4 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v4--;
					cin.get();
					if (wall_v4 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 20)
		{
			while (wall_v5 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v5--;
					cin.get();
					if (wall_v5 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 24)
		{
			while (wall_v6 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v6--;
					cin.get();
					if (wall_v6 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 28)
		{
			while (wall_v7 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v7--;
					cin.get();
					if (wall_v7 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 32)
		{
			while (wall_v8 >= 1)
			{
				if (P1_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P1_wall--;
					wall_v8--;
					cin.get();
					if (wall_v8 == 0)continue;
				}
			}
		}
	}
}
void wallplacement_P2()
{
	char placement;
	int cord_wall_x;
	int cord_wall_y;
	cout << "Enter H for horizontal and V for vertical:"<<endl;
	cin >> placement;
	if (placement == 'H')
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		WORD saved_attributes = consoleInfo.wAttributes;
		cout << "Enter x and y:"<<endl;
		cin >> cord_wall_x >> cord_wall_y;
		P_All_y.push_back(cord_wall_y);
		horizontal_walls.push_back({ cord_wall_x, cord_wall_y });
		if (cord_wall_y == 2)
		{
			while (wall_h1>1)
			{
				if (P2_wall == 0)
				{
					cout << "You dont have any wall left, you can not place one" << endl;
					break;
				}
				else if (wall_h1 == 1)
				{
					cout << "You can not place wall here!";
					break;
				}
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h1--;
					//cin.get();
					//if (wall_h1 == 0)continue;
				}
			}
		}
		else if (cord_wall_y == 4)
		{

			while (wall_h2 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;

				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h2--;
					//cin.get();
					if (wall_h2 == 0) continue;
				}
			}
		}
		else if (cord_wall_y == 6)
		{
			while (wall_h3 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;

				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h3--;
					//cin.get();
					if (wall_h3 == 0)continue;
				}
			}
		}
		else if (cord_wall_y == 8)
		{

			while (wall_h4 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h4--;
					//cin.get();
					if (wall_h4 == 0)continue;
				}
			}
		}
		else if (cord_wall_y == 10)
		{
			while (wall_h5 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h5--;
					//cin.get();
					if (wall_h5 == 0)continue;
				}
			}
		}
		else if (cord_wall_y == 12)
		{
			while (wall_h6 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h6--;
					//cin.get();
					if (wall_h6 == 0)continue;
				}
			}
		}
		else if (cord_wall_y == 14)
		{
			while (wall_h7 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h7--;
					//cin.get();
					if (wall_h7 == 0)continue;
				}
			}
		}
		else if (cord_wall_y == 16)
		{
			while (wall_h8 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "---";
					setColor(saved_attributes);
					P2_wall--;
					wall_h8--;
					//cin.get();
					if (wall_h8 == 0)continue;
				}
			}
		}
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		WORD saved_attributes = consoleInfo.wAttributes;
		cout << "Enter x and y:";
		cin >> cord_wall_x >> cord_wall_y;
		P_All_x.push_back(cord_wall_x);
		vertical_walls.push_back({ cord_wall_x, cord_wall_y });
		if (cord_wall_x == 4)
		{
			while (wall_v1 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v1--;
					//cin.get();
					if (wall_v1 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 8)
		{
			while (wall_v2 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v2--;
					//cin.get();
					if (wall_v2 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 12)
		{
			while (wall_v3 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v3--;
					//cin.get();
					if (wall_v3 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 16)
		{
			while (wall_v4 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v4--;
					//cin.get();
					if (wall_v4 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 20)
		{
			while (wall_v5 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v5--;
					//cin.get();
					if (wall_v5 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 24)
		{
			while (wall_v6 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v6--;
					//cin.get();
					if (wall_v6 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 28)
		{
			while (wall_v7 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v7--;
					//cin.get();
					if (wall_v7 == 0)continue;
				}
			}
		}
		if (cord_wall_x == 32)
		{
			while (wall_v8 >= 1)
			{
				if (P2_wall == 0) cout << "You dont have any wall left, you can not place one"<<endl;
				else
				{
					setColor(FOREGROUND_RED);
					gotoxy(cord_wall_x, cord_wall_y);
					cout << "|";
					setColor(saved_attributes);
					P2_wall--;
					wall_v8--;
					//cin.get();
					if (wall_v8 == 0)continue;
				}
			}
		}
		}
}*/

/*void wallplacement_P1() {
	char placement;
	int cord_wall_x;
	int cord_wall_y;
	cout << "Enter H for horizontal and V for vertical:" << endl;
	cin >> placement;
	cout << "Enter x and y:" << endl;
	cin >> cord_wall_x >> cord_wall_y;

	// Ensure coordinates are within valid grid boundaries
	if (cord_wall_x < 1 || cord_wall_x > 32 || cord_wall_y < 1 || cord_wall_y > 17) {
		cout << "Invalid position. Out of bounds." << endl;
		return;
	}

	if (placement == 'H') {
		if (cord_wall_y % 2 == 0 && P1_wall > 0) {
			bool canPlace = true;
			for (const auto& wall : horizontal_walls) {
				if (wall.first == cord_wall_x && wall.second == cord_wall_y) {
					canPlace = false;
					break;
				}
			}
			if (canPlace) {
				horizontal_walls.push_back({ cord_wall_x, cord_wall_y });
				P1_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "---";
			}
			else {
				cout << "Cannot place wall here. Overlapping another wall." << endl;
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else if (placement == 'V') {
		if (cord_wall_x % 4 == 0 && cord_wall_y % 2 != 0 && P1_wall > 0) {
			bool canPlace = true;
			for (const auto& wall : vertical_walls) {
				if (wall.first == cord_wall_x && wall.second == cord_wall_y) {
					canPlace = false;
					break;
				}
			}
			if (canPlace) {
				vertical_walls.push_back({ cord_wall_x, cord_wall_y });
				P1_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "|";
			}
			else {
				cout << "Cannot place wall here. Overlapping another wall." << endl;
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else {
		cout << "Invalid input." << endl;
	}
}*/

/*void wallplacement_P2() {
	char placement;
	int cord_wall_x;
	int cord_wall_y;
	cout << "Enter H for horizontal and V for vertical:" << endl;
	cin >> placement;
	cout << "Enter x and y:" << endl;
	cin >> cord_wall_x >> cord_wall_y;

	// Ensure coordinates are within valid grid boundaries
	if (cord_wall_x < 1 || cord_wall_x > 32 || cord_wall_y < 1 || cord_wall_y > 17) {
		cout << "Invalid position. Out of bounds." << endl;
		return;
	}

	if (placement == 'H') {
		if (cord_wall_y % 2 == 0 && P2_wall > 0) {
			bool canPlace = true;
			for (const auto& wall : horizontal_walls) {
				if (wall.first == cord_wall_x && wall.second == cord_wall_y) {
					canPlace = false;
					break;
				}
			}
			if (canPlace) {
				horizontal_walls.push_back({ cord_wall_x, cord_wall_y });
				P2_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "---";
			}
			else {
				cout << "Cannot place wall here. Overlapping another wall." << endl;
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else if (placement == 'V') {
		if (cord_wall_x % 4 == 0 && cord_wall_y % 2 != 0 && P2_wall > 0) {
			bool canPlace = true;
			for (const auto& wall : vertical_walls) {
				if (wall.first == cord_wall_x && wall.second == cord_wall_y) {
					canPlace = false;
					break;
				}
			}
			if (canPlace) {
				vertical_walls.push_back({ cord_wall_x, cord_wall_y });
				P2_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "|";
			}
			else {
				cout << "Cannot place wall here. Overlapping another wall." << endl;
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else {
		cout << "Invalid input." << endl;
	}
}*/



bool bfs_check(int startX, int startY, int goalY, const vector<pair<int, int>>& horizontal_walls, const vector<pair<int, int>>& vertical_walls) {

	const int GRID_WIDTH = 33;
	const int GRID_HEIGHT = 17;

	
	queue<pair<int, int>> q;
	vector<vector<bool>> visited(GRID_HEIGHT + 1, vector<bool>(GRID_WIDTH + 1, false)); 

	q.push({ startX, startY });
	visited[startY][startX] = true;

	int directions[4][2] = { {4, 0}, {-4, 0}, {0, 2}, {0, -2} };

	while (!q.empty()) {
		pair<int, int> current = q.front();
		int x = current.first;
		int y = current.second;

		q.pop();

		if (y == goalY) return true;

		for (int i = 0; i < 4; ++i) {
			int nx = x + directions[i][0];
			int ny = y + directions[i][1];

			if (nx < 1 || nx > GRID_WIDTH || ny < 1 || ny > GRID_HEIGHT) continue;

		
			if (visited[ny][nx]) continue;

			bool blocked = false;
			if (directions[i][0] != 0) { 
				for (const auto& wall : vertical_walls) {
					if (directions[i][0] > 0 && wall.first == x + 4 && wall.second <= y && wall.second + 2 > y) {
						blocked = true;
						break;
					}
					else if (directions[i][0] < 0 && wall.first == x && wall.second <= y && wall.second + 2 > y) {
						blocked = true;
						break;
					}
				}
			}
			else { 
				for (const auto& wall : horizontal_walls) {
					if (directions[i][1] > 0 && wall.second == y + 1 && wall.first <= x && wall.first + 4 > x) {
						blocked = true;
						break;
					}
					else if (directions[i][1] < 0 && wall.second == y - 1 && wall.first <= x && wall.first + 4 > x) {
						blocked = true;
						break;
					}
				}
			}

			
			if (!blocked) {
				q.push({ nx, ny });
				visited[ny][nx] = true;
			}
		}
	}

	return false;
}

void wallplacement_P1() {
	char placement;
	int cord_wall_x, cord_wall_y;

	cout << "Enter H for horizontal and V for vertical:" << endl;
	cin >> placement;
	cout << "Enter x and y:" << endl;
	cin >> cord_wall_x >> cord_wall_y;

	if (placement == 'H') {
		if (cord_wall_y % 2 == 0 && P1_wall > 0) {
			horizontal_walls.push_back({ cord_wall_x, cord_wall_y });
			bool path_for_p1 = bfs_check(x_p1, y_p1, 1, horizontal_walls, vertical_walls);
			bool path_for_p2 = bfs_check(x_p2, y_p2, 17, horizontal_walls, vertical_walls);

			if (!path_for_p1 || !path_for_p2) {
				cout << "Invalid wall placement. It blocks a player." << endl;
				horizontal_walls.pop_back(); 
			}
			else {
			
				P1_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "---";
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else if (placement == 'V') {
		if (cord_wall_x % 4 == 0 && cord_wall_y % 2 != 0 && P1_wall > 0) {
	
			vertical_walls.push_back({ cord_wall_x, cord_wall_y });
			bool path_for_p1 = bfs_check(x_p1, y_p1, 1, horizontal_walls, vertical_walls);
			bool path_for_p2 = bfs_check(x_p2, y_p2, 17, horizontal_walls, vertical_walls);

			if (!path_for_p1 || !path_for_p2) {
				cout << "Invalid wall placement. It blocks a player." << endl;
				vertical_walls.pop_back(); 
			}
			else {
			
				P1_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "|";
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else {
		cout << "Invalid input." << endl;
	}
}

void wallplacement_P2() {
	char placement;
	int cord_wall_x, cord_wall_y;

	cout << "Enter H for horizontal and V for vertical:" << endl;
	cin >> placement;
	cout << "Enter x and y:" << endl;
	cin >> cord_wall_x >> cord_wall_y;

	if (placement == 'H') {
		if (cord_wall_y % 2 == 0 && P2_wall > 0) {
			
			horizontal_walls.push_back({ cord_wall_x, cord_wall_y });

			
			bool path_for_p1 = bfs_check(x_p1, y_p1, 1, horizontal_walls, vertical_walls);
			bool path_for_p2 = bfs_check(x_p2, y_p2, 17, horizontal_walls, vertical_walls);

			if (!path_for_p1 || !path_for_p2) {
				cout << "Invalid wall placement. It blocks a player." << endl;
				horizontal_walls.pop_back(); 
			}
			else {
				
				P2_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "---";
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else if (placement == 'V') {
		if (cord_wall_x % 4 == 0 && cord_wall_y % 2 != 0 && P2_wall > 0) {
		
			vertical_walls.push_back({ cord_wall_x, cord_wall_y });

		
			bool path_for_p1 = bfs_check(x_p1, y_p1, 1, horizontal_walls, vertical_walls);
			bool path_for_p2 = bfs_check(x_p2, y_p2, 17, horizontal_walls, vertical_walls);

			if (!path_for_p1 || !path_for_p2) {
				cout << "Invalid wall placement. It blocks a player." << endl;
				vertical_walls.pop_back(); 
			}
			else {
				
				P2_wall--;
				gotoxy(cord_wall_x, cord_wall_y);
				cout << "|";
			}
		}
		else {
			cout << "Invalid position or no walls left." << endl;
		}
	}
	else {
		cout << "Invalid input." << endl;
	}
}

void play_P1()
{
    board();
	drawWalls();
	cord_P1();
	cord_P2();
	char P1_move;
	while (turn_play)
	{
        for (int z = 0; z < 20; z++)cout << endl;
		cout <<endl<< "Movement or placing wall(choose M or W)" << endl;
		cin >> P1_move;
		if (P1_move == 'M')
		{
			cout << "choose L as left ,R as right , U as up and D as down:" << endl;
			cin >> P1_move;
			if (P1_move == 'L' && check_Left_P1()==true)
			{
				gotoxy(x_p1, y_p1);
				cout << "   ";
				x_p1 -= 4;
				gotoxy(x_p1, y_p1);
				cout << "P1";
				turn_play = false;
			}
			else if (P1_move == 'R' && check_Right_P1() == true)
			{
				gotoxy(x_p1, y_p1);
				cout << "   ";
				//x_p1 += 0.5;
				x_p1 += 4;
				gotoxy(x_p1, y_p1);
				cout << "P1";
				turn_play = false;
			}
			else if (P1_move == 'U' && check_Up_P1() ==true)
			{
				gotoxy(x_p1, y_p1);
				cout << "   ";
				y_p1 -= 2;
				gotoxy(x_p1, y_p1);
				cout << "P1";
				turn_play = false;
			}
			else if(P1_move == 'D' && check_Down_P1() == true)
			{
				if (x_p1 > 1 && x_p1 < 34 && y_p1 == 17 )
				{
					cout << "Choose another move:" << endl;
				
				}
				else
				{
					gotoxy(x_p1, y_p1);
					cout << "   ";
					y_p1 += 2;
					gotoxy(x_p1, y_p1);
					cout << "P1";
					turn_play = false;
				}
			}
				
		}
		else
		{
			wallplacement_P1();
			turn_play = false;
		}	
	}
	if (x_p1 > 1 && x_p1 < 34 && y_p1 == 1)
	{
		cout << "player 1 win!!";
		winner = false;
   }
	
}
void play_P2()
{
	board();
	drawWalls();
	cord_P1();
	cord_P2();
	char P2_move;
	while (turn_play==false)
	{
		for (int z = 0; z < 20; z++)cout << endl;
		cout << "Movement or placing wall(choose M or W)" << endl;
		cin >> P2_move;
		if (P2_move == 'M')
		{
			cout << "choose L as left ,R as right , U as up and D as down:" << endl;
			cin >> P2_move;
			if (P2_move == 'L' && check_Left_P2() == true)
			{
				gotoxy(x_p2, y_p2);
				cout << "   ";
				x_p2 -= 4;
				gotoxy(x_p2, y_p2);
				cout << "P2";
				turn_play = true;
			}
			else if (P2_move == 'R' && check_Right_P2() == true)
			{
				gotoxy(x_p2, y_p2);
				cout << "   ";
				//x_p1 += 0.5;
				x_p2 += 4;
				gotoxy(x_p2, y_p2);
				cout << "P2";
				turn_play = true;
			}
			else if (P2_move == 'U' && check_Up_P2() == true)
			{
				gotoxy(x_p2, y_p2);
				cout << "   ";
				y_p2 += 2;
				gotoxy(x_p2, y_p2);
				cout << "P2";
				turn_play = true;
			}
			else
			{
				if (x_p2 > 1 && x_p2 < 34 && y_p2 == 1  )
				{
					cout << "Choose another move:" << endl;
				}
				else if(check_Down_P2() == true)
				{
					gotoxy(x_p2, y_p2);
					cout << "   ";
					y_p2 -= 2;
					gotoxy(x_p2, y_p2);
					cout << "P2";
					turn_play = true;
				}
				//continue;
			}
			//turn_play = true;
		}
		else
		{
			wallplacement_P2();
			turn_play = true;
		}
	}
	if (x_p2 > 1 && x_p2 < 34 && y_p2 == 17)
	{
		cout << "player 2 win!!";
		winner = false;
	}
}
void play()
{
	bool turn = true;
	while (winner)
	{
		if (turn)
		{
			play_P1();
			turn = false;
			//for (int z = 0; z < 20; z++)cout << endl;
			system("cls");
	    
		}
		else
		{
			play_P2();
			turn = true;
			//for (int z = 0; z < 20; z++)cout << endl;
			system("cls");
		}
}
}
int main(){
	play();
  cin.get();
}




