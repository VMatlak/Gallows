#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h> 
#include "Gallows.h" 
#include "File.h" 
#include <Windows.h>

using namespace std;
void CheckInput(string&, char&, vector <char>&, int, vector <char>); // Перевіряє введені користувачем дані
bool CheckLetter(char&, string, vector <char>&, int&); // Перевіряє, чи буква є частиною потрібного слова
void PrintFields(vector <char>); // Друкує вектор.
void PrintInfo(vector <char>, int, vector <char>); // Друкує потрібне слово, кількість спроб і вже вставлені літери.
bool Exit();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	do
	{
		string word, input;
		char letter = ' ';
		int mistakes = 0;
		bool wordFound = false;
		word = RequiredWord(); // Слово, яке потрібно знайти для перемоги у грі.
		vector <char> tempWord; // Вектор, який містить знайдені та не знайдені (_) літери потрібного слова.
		vector <char> tempLetters; // Вектор, який вміщує всі введені користувачем літери.
		for (int i = 0; i < word.size(); i++)
		{
			tempWord.push_back('_');
		}
		system("cls");
		cout << "\t\tЛаскаво просимо до гри Шибениця!\n\t Суть гри полягає в тому, щоб знайти потрібне слово для перемоги,\n\t\t вводячи по одній букві за раз. \n\t\t\t   Удачі!" << endl << "\n\n\t   Натисніть будь-яку кнопку, щоб продовжити." << endl;
		_getch();
		PrintInfo(tempWord, mistakes, tempLetters);
		while (1)
		{
			cout << "Введіть літеру: ";
			getline(cin, input);
			CheckInput(input, letter, tempLetters, mistakes, tempWord);
			wordFound = CheckLetter(letter, word, tempWord, mistakes);
			PrintInfo(tempWord, mistakes, tempLetters);
			Gallows(mistakes);
			if (wordFound)
			{
				cout << "Вітаємо! Ви виграли!" << endl;
				break;
			}
			if (mistakes == 8) // Кількість спроб до закінчення гри.
			{
				cout << "Ви програли гру, пощастить наступного разу!" << endl;
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
		cout << "Неправильне введення. Будь ласка, введіть одну букву a-z:";
		getline(cin, input);
	}
	if (input[0] >= 'A' && input[0] <= 'Z') // перетворює велику літеру на малу.
		letter = input[0] + 32;
	else
		letter = input[0];
	for (int i = 0; i < tempLetters.size(); i++) // Перевіряє, чи введена буква вже була введена раніше.
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
		cout << "Ви вже вводили цю, спробуйте іншу:";
		getline(cin, input);
		CheckInput(input, letter, tempLetters, mistakes, tempWord);
	}
	else
		tempLetters.push_back(letter); // Введення не було дублікатом, тому воно переходить у вектор, який містить усі введені користувачем літери.
}

bool CheckLetter(char& letter, string word, vector <char>& tempWord, int& mistakes)
{
	bool letterFound = false;
	for (int i = 0; i < word.size(); i++) // Перевіряє, чи є буква в потрібному слові.
	{
		if (letter == word[i])
		{
			tempWord[i] = letter;
			letterFound = true;
		}
	}
	if (letterFound == false) // Збільшення кількості помилок
	{
		mistakes++;
		return false;
	}
	else
	{
		for (int i = 0; i < tempWord.size(); i++) // Якщо у tempWord немає _, це означає, що всі літери знайдені, гравець виграв.
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
	cout << "Бажаєте зіграти ще раз? Натисніть Y / y, якщо так  або будь-яку іншу кнопку, якщо ні." << endl;
	getline(cin, input);
	if (input[0] == 'Y' || input[0] == 'y')
		return true;
	else
		return false;
}

void PrintInfo(vector <char> tempWord, int mistakes, vector <char> tempLetters)
{
	system("cls");
	cout << "Загадане слово слово: ";
	PrintFields(tempWord);
	cout << "Введені літери: ";
	PrintFields(tempLetters);
	cout << "Кількість спроб, що залишились: " << 8 - mistakes << endl;
}
