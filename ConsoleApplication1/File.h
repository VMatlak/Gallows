#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

string RequiredWord() // ���������� ����������� ����� � ����� word.txt.
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
				maxWords++; // �������� ������� ��� � ���� word.txt.
			}
		}
		file.close();
	}
	else
	{
		cout << "Unable to open \"words.txt\" file" << endl;
	}

	wordPos = rand() % maxWords + 1; // ������ ��������� ������� ����� � ���� word.txt �� 1 �� maxWords.

	file.open("words.txt");
	if (file.is_open())
	{
		int i = 0;
		while (file.good())
		{
			while (i < wordPos)
			{
				getline(file, word); // ���� ����� �� ��������� ������� �� ��������� ����� ��� ���.
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
