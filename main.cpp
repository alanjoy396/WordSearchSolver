/*
	This program is designed to search through a word search puzzle and 
	find all the targeted words in them, and print out their locations if they are there.
	This program takes in a 2 arguments: a text file containing a word search, 
	and a text file containing words to search for.

	Note that 0,0 is in the top left of the word search.
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <locale>
#include "Point.h"

using namespace std;

int dx[] = {0,  0, 1, 1,  1,-1,-1, -1};
int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};

// function to check if the current move is valid
bool isValidDirection(const int currentRow, const int currentCol, const int rows, const int cols, const int dir, const int mult)
{
	if (currentRow + dy[dir] * mult >= rows || currentRow + dy[dir] * mult < 0){
		return false;
	}
	if (currentCol + dx[dir] * mult >= cols || currentCol + dx[dir] * mult < 0){
		return false;
	}
	return true;
}

bool isWordOnBoard(const string& thisWord, const vector<string>& puzzle, Line& wordLocation)
{
	int rows = puzzle.size();
	int cols = puzzle[0].size();
	if (thisWord.size() > rows && thisWord.size() > cols){
		return false;
	}
	// the current letter in the word to search for.
	char currentLetter = thisWord[0];
	// increments through dx and dy
	int k = 0;
	Point start;
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			// if the current letter at the current space matches the first letter
			if (puzzle[r][c] == currentLetter){
				start = Point(c, r);
				// go through every direction
				for (int k = 0; k < 8; k++){
					// go through every letter of the word
					for (int i = 1; i < thisWord.size(); i++){
						currentLetter = thisWord[i];
						// if EITHER the direction is invalid or the current character doesn't match the word then...
						if (!isValidDirection(r, c, rows, cols, k, i) || puzzle[r+i*dy[k]][c+i*dx[k]] != currentLetter){
							// ...get out of this loop to try a different direction
							break;
						}
						// if it passes that check, AND it's the last letter, you've found a success
						if (currentLetter == thisWord[thisWord.size()-1]) {
							// save the word location
							wordLocation = Line(start, Point(c+i*dx[k], r+i*dy[k]));
							return true;
						}
					}
					// go back to the start of the word
					currentLetter = thisWord[0];
				}
			}
		}
	}
	
	return false;
}

void printSolution(const vector<string>& words, const vector<string>& puzzle, map<string, Line>& wordLocs)
{
	for (int r = 0; r < puzzle.size(); r++){
		cout << puzzle[r] << endl;
	}
	cout << "\n" << endl;
	Line temp;
	for (int i = 0; i < words.size(); i++){
		std::cout << left << setw(15) << words[i] << ": ";
		temp = wordLocs[words[i]];
		if (temp != Line(-1, -1, -1, -1)){
			cout << setw(25) << temp.print() << endl;
		}
		else {
			cout << setw(25) << "Not found." << endl;
		}
	}
}

string stringUpper(const string& buffer){
	string newBuffer = "";
	for (int i = 0; i < buffer.size(); i++){
		newBuffer += toupper(buffer[i]);
	}
	return newBuffer;
}


int main(int argc, char* argv[]){
	// checks argument count 
	if (argc != 3){
		cout << "ERROR: Incorrect number of arguments." << endl;
		return -1;
	}
	ifstream filePuzzle; 
	filePuzzle.open(argv[1]);
	ifstream fileWords;
	fileWords.open(argv[2]);
	// checks file validity
	if (filePuzzle.fail()){
		cout << "ERROR: Invalid puzzle file." << endl;
		return -1;
	}
	if (fileWords.fail()){
		cout << "ERROR: Invalid word file." << endl;
		return -1;
	}
	vector<string> puzzle;
	vector<string> words;
	
	string buffer;
	// populate the puzzle and then the words
	while (getline(filePuzzle, buffer)){
		buffer = stringUpper(buffer);
		puzzle.push_back(buffer);
	}
	while (getline(fileWords, buffer)){
		buffer = stringUpper(buffer);
		words.push_back(buffer);
	}
	
	// reversed words are necessary to search for the word backwards
	vector<string> reversedWords;
	for (int i = 0; i < words.size(); i++){
		reversedWords.push_back(words[i]);
		reverse(reversedWords[i].begin(), reversedWords[i].end());
	}
	
	// a map representing the point
	map<string, Line> wordLocs;

	for (int i = 0; i < words.size(); i++){
		if (!isWordOnBoard(words[i], puzzle, wordLocs[words[i]])){
			isWordOnBoard(reversedWords[i], puzzle, wordLocs[words[i]]);
		}
	}
	
	printSolution(words, puzzle, wordLocs);
	
	return 0;
}