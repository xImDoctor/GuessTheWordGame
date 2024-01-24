#include <iostream>
#include <string>
//for randomizer
#include <cstdlib>
#include <ctime>

//for color changing
#include <Windows.h>
#include <WinBase.h>
#define SET_DEFAULT_COLOR SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define YELLOW_COLOR FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY

using namespace std;

void SetConsoleTextColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void StartMenu() {
	char action;

	while (true) {
		cout << "\n=== Guess the word by ImDoctor ===\n\n�������� �������� ��������:\ns - ������ ����\nr - �������\ne - ����� �� ����\n" << endl;
		cin >> action;

		switch (action) {
		case 's': case 'S':
			cout << "�����!\n\n";
			break;
		case 'r': case 'R':
			cout << "��������� ������� ����� ������ �����, � ��� ������� ������� � �� ����, ���� ������ - ������� ����� �� 5 �������." << endl;
			cout << "���� �� ������� ����� �� ����������� �����, � ��� ������������� � ��� �� �����, ��� � � �����, �� ��� ����� ���������� ";
			SetConsoleTextColor(FOREGROUND_GREEN); cout << " ������ ������"; SET_DEFAULT_COLOR;
			cout << ".\n���� �� ������� ����� �� ����������� �����, �� ��� ����������� � ������ �����, �� ��� ����� ���������� ";
			SetConsoleTextColor(YELLOW_COLOR); cout << "������ ������"; SET_DEFAULT_COLOR; cout << '.' << endl << endl;
			continue;
		case 'e': case 'E':
			cout << "�� �������!" << endl;
			exit(0);
		default:
			cout << "������ �������� ���� - ���������� �����!" << endl;
			continue;
		}
		break; //exit the loop only if 's': first break ends switch, the second one - while 
	}

}

void InGameCycle(const string* words, const short wordCount) {

	string wordly = words[rand() % wordCount], guess;
	const short wordLenght = wordly.length();
	const unsigned short maxAttempts = 6;
	unsigned short attempts = maxAttempts;

	cout << "� ���������� ����� " << wordLenght << " ����(-�)." << endl;

	//VS macro for debug build
#ifdef _DEBUG
	cout << "���������� �����: " << wordly << endl;
#endif

	do {
		cout << "������� �������������� �����: "; cin >> guess;

		for (int i = 0; i < wordLenght; ++i) {

			if (guess[i] == wordly[i])
				SetConsoleTextColor(FOREGROUND_GREEN);
			else if (wordly.find(guess[i]) != string::npos)
				SetConsoleTextColor(YELLOW_COLOR);

			cout << guess[i];
			SET_DEFAULT_COLOR;
		}
		cout << endl;
		--attempts;

	} while (guess != wordly && attempts);

	if (attempts)
		cout << "\n�����������! �� ������� ����� " << wordly << " �� " << (maxAttempts - attempts) << " �������.";
	else cout << "\n�� ��������� :(\n���� �������� ����� " << wordly << '.';
}

int main() {

	// gathering of info and changing of color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	COORD startPos = consoleInfo.dwCursorPosition;
	SetConsoleCursorPosition(hConsole, startPos);
	SET_DEFAULT_COLOR;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(static_cast<unsigned int>(time(0)));

	//words dictionary with hand-made input, can be improved
	const string words[] = {
		"����", "�����", "���", "������", "����", "�����", "�����", "�����", "�����", "�����", "�����", "������", "�����", "�������", "����������", "������", "���", "���", "�����",
		"������", "������", "������", "������", "�������", "����", "����", "�����", "������", "������", "�����", "����", "������", "�����", "����", "�����������", "��������",
		"�����", "����", "�����", "���", "��������", "�����", "�������", "����", "����", "����", "����", "��", "���", "����", "���", "����", "������", "������", "����������",
		"�����", "�����", "����", "����", "���������", "����", "�����", "����", "����", "��������", "�������", "��������", "������", "����������", "�����", "������", "�����",
		"�����", "��������", "�����", "�������", "������", "����", "����", "�����", "������", "����", "����", "�������", "���", "���", "�����", "��������", "������", "������",
		"�����", "����", "�����", "��������", "�������", "�����", "���������", "���������", "����������", "������"
	};
	const short wordCount = 100;

	StartMenu();
	InGameCycle(words, wordCount);

	char restart;
	cout << "\n������ ������� ���?(y/n) "; cin >> restart; cout << endl;
	if (restart == 'y')
		InGameCycle(words, wordCount);
	else cout << "\n�� �������!" << endl;

	system("pause>nul");
	return 0;
}