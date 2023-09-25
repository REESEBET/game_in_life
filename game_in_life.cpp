#define _CRT_SECURE_NO_WARNINGS // для  копировавния строк из фйала
#include <iostream>
#include "windows.h" 
#include <conio.h>  //для цвета и esc
#include <fstream>

HANDLE hConsole;  //для цвета
const int k = 20; // длина ширина drp


char drp_prob[20][20] = {
	{95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,  1},
	{95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,1,  95},
	{95,95,95,95,95,95,95,95,1, 95, 95,95,95,95,95,95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,1,  95,95,95,95,95,95,95,95,95,95},
	{95,95,95,95,95,95,95,1,1,1,95,95,95,95,95,95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,95,95,95,95,95,1,  95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,95,95,95,95,1,95,  95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,95,95,95,1,95,95,  95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,95,95,1,95,95,95,  95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,95,1,95,95,95,95,  95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,   95,95,95,95,95},
	{95,95,95,95,95,95,95,95,1,95,95,95,95,95,95,  95,95,95,95,95},
	{95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,   95,95,95,95},
	{95,95,95,95,95,95,1,95,95,95,95,95,95,95,95,95,  95,95,95,95},
	{95,95,95,95,95,1,95,95,95,95,95,95,95,95,95,95,95,  95,95,95},
	{95,95,95,95,1,95,95,95,95,95,95,95,95,95,95,95,95,  95,95,95},
	{95,1,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,  95,95,95},
	{95,1,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,  95,95,95},
	{95,1,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,  95,95,95},
	{1,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,  95,95,95}
};
char drp_copy[20][20] = {};
//char drp[20][20] = {};
int get(int x)
{
	if (x < 0)
		return 19;
	if (x > 19)
		return 0;
	return x;
}
void life(const char* file_name_count)
{
	int life_count = 0;    //
	int sum = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			//drp_copy[i][j] = drp_prob[i][j];
			if ((drp_prob[get(i - 1)][j] == 1)) //--
				sum++;
			if ((drp_prob[get(i + 1)][j] == 1))
				sum++;
			if ((drp_prob[i][get(j + 1)] == 1))
				sum++;
			if ((drp_prob[i][get(j - 1)] == 1)) //
				sum++;
			if ((drp_prob[get(i + 1)][get(j + 1)] == 1))
				sum++;
			if ((drp_prob[get(i + 1)][get(j - 1)] == 1)) //
				sum++;
			if ((drp_prob[get(i - 1)][get(j + 1)] == 1))
				sum++;
			if ((drp_prob[get(i - 1)][get(j - 1)] == 1)) //--
				sum++;

			if (sum < 2 || sum > 3)
			{
				drp_copy[i][j] = 95;
				sum = 0;
			}

			if (sum == 3)
			{
				drp_copy[i][j] = 1;
				if (drp_prob[i][j] == 95) //если была мертвой м ожила->родилась
					life_count++;
				sum = 0;
			}

			if (sum == 2)
			{
				drp_copy[i][j] = drp_prob[i][j];
				sum = 0;
			}


			if (drp_copy[i][j] == 1)
			{
				SetConsoleTextAttribute(hConsole, 2);
				std::cout << drp_copy[i][j] << "  ";
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 7);
				std::cout << drp_copy[i][j] << "  ";
			}
		}
		std::cout << "\n";
	}

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			drp_prob[i][j] = drp_copy[i][j];

	std::ofstream fout;


	fout.open(file_name_count, std::ios::app);
	if (!fout.is_open())
		std::cout << "error" << '\n';
	else
	{
		fout << "<!DOCTYPE html>"
			<< "<html lang = \"ru\">"
			<< "<head>"
			<< "<meta charset = \"utf-8\"/>"
			<< "<title>game life</title>"
			<< "</head>"
			<< "<body>"
			<< "<div>count born elements :" << life_count << "</div><br>"
			<< "<table>"
			<< "<tbody>";
		for (int i = 0; i < k; i++)
		{

			fout << "<tr>";
			for (int j = 0; j < k; j++)
			{
				if (drp_prob[i][j] == 1)
					drp_prob[i][j] = '&';

				fout << "<td>"
					<< drp_prob[i][j]
					<< "</td>";


				if (drp_prob[i][j] == '&')
					drp_prob[i][j] = 1;
			}
			fout << "</tr>";
			//fout <<"\n";
		}
		fout << "</tbody>"
			<< "</table>"
			<< "</body>"
			<< "</html>";
		fout.close();
	}
}
int main(int argc, char* argv[])
{

	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << '\n';
	}

	
	char file_name1[40];
	char file_name2[40];


	if (argc == 1)
	{ // если в аргументах только имя программы
		std::cout << "no arguments!" << std::endl; // выводим, что нет аргументов
	}
	if (argc != 3)
	{ // если в аргументах слишком мнрого аргументов или мало
		std::cout << "no arguments!" << std::endl; // выводим, что нет аргументов
	}

	if (argc == 3)
	{
		strcpy(file_name1, argv[1]);

		if (argc == 3)
			strcpy(file_name2, argv[2]);
		else
			strcpy(file_name2, "text3.html");

	}

	std::ofstream fout;
	fout.open(file_name2);
	fout.close();

	std::ifstream fin;
	fin.open(file_name1);
	if (!fin.is_open())                           //проверка на существование файла
	{
		std::cout << "ERROR NOT FOUND FILE\n";
		return 0;
	}
	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			fin >> drp_prob[i][j];
			//std::cout << typeid(drp[i][j]).name() << std::endl;
			//break;
			if (drp_prob[i][j] == '0')
				drp_prob[i][j] = 95;
			if (drp_prob[i][j] == '1')
				drp_prob[i][j] = 1;
			//std::cout << drp[i][j] <<" ";
		}
		//std::cout << std::endl;
	}
	fin.close();


	const int KEY_ESC = 27;                      // esc
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //для цвета
	do {
		system("cls");
		life(file_name2);
		//Sleep(100);
	} while (_getch() != KEY_ESC);
	return 0;
}