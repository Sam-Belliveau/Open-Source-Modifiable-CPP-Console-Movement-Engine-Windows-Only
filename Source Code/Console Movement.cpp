// Console Movement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

// ESTABLISHING VARIABLES //

int i;
int h;

const int frameWidth = 80;
const int frameHeight = 30;

int playerX = 40;
int playerY = 11;

int stoneX = 10;
int stoneY = 11;

int randomCharX = 1;
int randomCharY = 1;

// SELF MADE FUNCTIONS //

void showConsoleCursor(bool showFlag){
	// Removes the cursor from the console.
	// This is good as is is less flickery.
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int difference(int(numA), int(numB)) {
	// Takes the ABS of the difference between two numbers.
	// This is for telling how far appart two things are.
	if ((numA - numB) < 0) { // ABS function
		return ((numA - numB)*(-1));
	}
	else {
		return (numA - numB);
	}
}

void goTo(int(one), int(two)){
	// This is for moving the cursor to the top.
	// I use this instead of "system("CLS")" because it removes the flickering.
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = one;
	Position.Y = two;
	SetConsoleCursorPosition(hOut, Position); // Moves cursor to an X, and Y.
}

void printXY(string(ch), int(one), int(two)) {
	// Goes to a spot and prints letter.
	goTo(one, two);
	cout << ch << flush;
}

void drawCaps(int(width)) {
	// This just draws the top and bottom frame.
	i = 1;
	cout << "+";
	while (i <= width) { // This loop makes the top as long as it needs to be.
		cout << "-";
		i++;
	};
	cout << "+" << endl;
}

void drawBlank(int(width)) {
	i = 1;
	cout << "|" << flush;
	while (i <= width) { // Prints the right amount of spaces.
		cout << " ";
		i++;
	}
	cout << "|" << endl;
}

void drawChar(int(h), int(x), int(y), string(let)) {
	if ((h - 1) == y) {
		printXY(let, x, y);
		goTo(0, h);
	}
}

void drawPack() {
	drawChar(h, randomCharX, randomCharY, "?");
	drawChar(h, playerX, playerY, "#"); // Draws charcter after it passes the line it is on to remove flicker.
	drawChar(h, stoneX, stoneY, "$");
}

void drawInfo() {
	cout << "Players:" << endl;
	cout << "# = You" << endl;
	cout << "$ = Bot that follows you" << endl;
	cout << "? = Average of you and the bot" << endl;
	cout << "" << endl;
	cout << "Controls:" << endl;
	cout << "W = Up" << endl;
	cout << "S = Down" << endl;
	cout << "A = Left" << endl;
	cout << "D = Right" << endl;
}

void drawWorld(int(width), int(height), int(px), int(py), int(sx), int(sy)) {
	goTo(0,0); // Clears screen.
	drawCaps(width); // Draws top at the right length.
	showConsoleCursor(false); // Removes Cursor
	h = 1;
	while (h <= height){ // Goes through each line.
		drawPack();
		drawBlank(width);
		h++;
	};
	drawPack();
	drawCaps(width); // Draws bottom at the right length.
	drawInfo();
}

void movePlayer(int(width), int(height)) {
	// This moves the player and will not let the player move if something is in that direction.
	int key = _getch(); // Gets witch key is being pressed

	if (key == 119 && playerY != 1 && !(playerX == stoneX && playerY == (stoneY + 1))){ // Tells if something is above it when the W key is pressed.
		playerY--; // The Y is fliped because it renders top to bottom.
	}
	else if(key == 119 && !(playerY != 1 && !(playerX == stoneX && playerY == (stoneY + 1)))){ 
		cout << "\a" << flush; // Plays error sound if something is in the way.
	}
	if (key == 100 && playerX != width && !(playerY == stoneY && playerX == (stoneX - 1))) { // Tells if something is to the right it when the D key is pressed.
		playerX++;
	}
	else if(key == 100 && !(playerX != width && !(playerY == stoneY && playerX == (stoneX - 1)))){
		cout << "\a" << flush; // Plays error sound if something is in the way.
	}
	if (key == 115 && playerY != height && !(playerX == stoneX && playerY == (stoneY - 1))) { // Tells if something is below it when the S key is pressed.
		playerY++; // The Y is fliped because it renders top to bottom.
	}
	else if(key == 115 && !(playerY != height && !(playerX == stoneX && playerY == (stoneY - 1)))){
		cout << "\a" << flush; // Plays error sound if something is in the way.
	}
	if (key == 97 && playerX != 1 && !(playerY == stoneY && playerX == (stoneX + 1))) { // Tells if something is to the left of it when the A key is pressed.
		playerX--;
	}
	else if (key == 97 && !(playerX != 1 && !(playerY == stoneY && playerX == (stoneX + 1)))){
		cout << "\a" << flush; // Plays error sound if something is in the way.
	}
}

void moveRandom() {
	randomCharX = round(((playerX + stoneX)/2));
	randomCharY = round(((playerY + stoneY)/2));
}

void moveStone(int(px), int(py)) {
	// Moves the stone toards the player if it is 1 away from the player.
	if (!(difference(stoneX, playerX) <= 1 && difference(stoneY, playerY) <= 1)) { // Test to see if the player is one away.
		// Moves stone toards the player.
		if (stoneX < playerX) {
			stoneX++;
		}
		if (stoneX > playerX) {
			stoneX--;
		}
		if (stoneY < playerY) {
			stoneY++;
		}
		if (stoneY > playerY) {
			stoneY--;
		}
	}
}

// ORDER OF EVENTS //

void events() {
	// Executes functions in correct order.
	drawWorld(frameWidth, frameHeight, playerX, playerY, stoneX, stoneY); // Draws world.
	movePlayer(frameWidth, frameHeight); // Moves player. Frame height makes sure the player does not move off the screen.
	moveRandom();
	drawWorld(frameWidth, frameHeight, playerX, playerY, stoneX, stoneY);
	movePlayer(frameWidth, frameHeight);
	moveStone(frameWidth, frameWidth); // Stone moves every other player move so the player can escape the stone.
	moveRandom();
}

// MAIN LOOP //

int main(){
	showConsoleCursor(false);
	while (1){
		events(); // Loops the actions
	}
    return 0;
}