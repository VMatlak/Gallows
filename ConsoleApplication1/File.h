#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

string RequiredWord() // Повернення необхідного слова з файлу word.txt.
{
	string word;
	int maxWords = 0, wordPos;
	ifstream file("words.txt");
	if (file.is_open())
	{
		while (file.good())
		{
			while (getline(file, word))
			{
				maxWords++; // Загальна кількість слів у файлі word.txt.
			}
		}
		file.close();
	}
	else
	{
		cout << "Unable to open \"words.txt\" file" << endl;
	}

	wordPos = rand() % maxWords + 1; // Приймає випадкову позицію слова у файлі word.txt від 1 до maxWords.

	file.open("words.txt");
	if (file.is_open())
	{
		int i = 0;
		while (file.good())
		{
			while (i < wordPos)
			{
				getline(file, word); // Бере слово із випадкової позиції та відправляє назад для гри.
				i++;
			}
			break;
		}
		file.close();
	}
	else
	{
		cout << "Unable to open \"words.txt\" file" << endl;
	}
	return word;
}
