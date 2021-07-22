#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h> 
#include "Gallows.h" 
#include "File.h" 

using namespace std;
void CheckInput(string&, char&, vector <char>&, int, vector <char>); // �������� ������ ������������ ���
bool CheckLetter(char&, string, vector <char>&, int&); // ��������, �� ����� � �������� ��������� �����
void PrintFields(vector <char>); // ����� ������.
void PrintInfo(vector <char>, int, vector <char>); // ����� ������� �����, ������� ����� � ��� �������� �����.
bool Exit();

int main()
{
	srand(time(NULL));
	do
	{
		string word, input;
		char letter = ' ';
		int mistakes = 0;
		bool wordFound = false;
		word = RequiredWord(); // �����, ��� ������� ������ ��� �������� � ��.
		vector <char> tempWord; // ������, ���� ������ ������� �� �� ������� (_) ����� ��������� �����.
		vector <char> tempLetters; // ������, ���� ���� �� ������ ������������ �����.
		for (int i = 0; i < word.size(); i++)
		{
			tempWord.push_back('_');
		}
		system("cls");
		cout << "Welcome to the game of Gallows! The point of the game is to find the required word to win by inputting one letter at a time. Good luck!" << endl << "Press any key to continue." << endl;
		_getch();
		PrintInfo(tempWord, mistakes, tempLetters);
		while (1)
		{
			cout << "Input a letter: ";
			getline(cin, input);
			CheckInput(input, letter, tempLetters, mistakes, tempWord);
			wordFound = CheckLetter(letter, word, tempWord, mistakes);
			PrintInfo(tempWord, mistakes, tempLetters);
			Gallows(mistakes);
			if (wordFound)
			{
				cout << "Congratulations! You have won the game!" << endl;
				break;
			}
			if (mistakes == 8) // ʳ������ ����� �� ��������� ���.
			{
				cout << "You have lost the game, better luck next time!" << endl;
				break;
			}
		}
	} while (Exit());
}

void CheckInput(string& input, char& letter, vector <char>& tempLetters, int mistakes, vector <char> tempWord)
{
	bool duplicate = false;
	while (input.size() > 1 || (!(input[0] >= 'a' && input[0] <= 'z') && !(input[0] >= 'A' && input[0] <= 'Z'))) //Input has to be a single letter from a-z.
	{
		PrintInfo(tempWord, mistakes, tempLetters);
		Gallows(mistakes);
		cout << "Wrong input, please input a single letter a-z: ";
		getline(cin, input);
	}
	if (input[0] >= 'A' && input[0] <= 'Z') // ���������� ������ ����� �� ����.
		letter = input[0] + 32;
	else
		letter = input[0];
	for (int i = 0; i < tempLetters.size(); i++) // ��������, �� ������� ����� ��� ���� ������� �����.
	{
		if (letter == tempLetters[i])
		{
			duplicate = true;
		}
	}
	if (duplicate == true)
	{
		PrintInfo(tempWord, mistakes, tempLetters);
		Gallows(mistakes);
		cout << "You have already inputted this letter, please try another: ";
		getline(cin, input);
		CheckInput(input, letter, tempLetters, mistakes, tempWord);
	}
	else
		tempLetters.push_back(letter); // �������� �� ���� ���������, ���� ���� ���������� � ������, ���� ������ �� ������ ������������ �����.
}

bool CheckLetter(char& letter, string word, vector <char>& tempWord, int& mistakes)
{
	bool letterFound = false;
	for (int i = 0; i < word.size(); i++) // ��������, �� � ����� � ��������� ����.
	{
		if (letter == word[i])
		{
			tempWord[i] = letter;
			letterFound = true;
		}
	}
	if (letterFound == false) // ��������� ������� �������
	{
		mistakes++;
		return false;
	}
	else
	{
		for (int i = 0; i < tempWord.size(); i++) // ���� � tempWord ���� _, �� ������, �� �� ����� �������, ������� ������.
		{
			if (tempWord[i] == '_')
			{
				return false;
			}
		}
		return true;
	}
}

void PrintFields(vector <char> vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}

bool Exit()
{
	string input;
	cout << "Would you like to play again? Y/y for yes or any other key for no." << endl;
	getline(cin, input);
	if (input[0] == 'Y' || input[0] == 'y')
		return true;
	else
		return false;
}

void PrintInfo(vector <char> tempWord, int mistakes, vector <char> tempLetters)
{
	system("cls");
	cout << "Required word: ";
	PrintFields(tempWord);
	cout << "Your inputted letters: ";
	PrintFields(tempLetters);
	cout << "Number of tries left: " << 8 - mistakes << endl;
}
