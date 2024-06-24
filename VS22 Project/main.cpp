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
		cout << "\n=== Guess the word by ImDoctor ===\n\nВыберите желаемое действие:\ns - начать игру\nr - правила\ne - выйти из игры\n" << endl;
		cin >> action;

		switch (action) {
		case 's': case 'S':
			cout << "Начнём!\n\n";
			break;
		case 'r': case 'R':
			cout << "Случайным образом будет задано слово, а вам сказано сколько в нём букв, ваша задача - угадать слово за 5 попыток." << endl;
			cout << "Если вы угадали букву из загаданного слова, и она располагается в том же месте, что и в слове, то она будет подсвечена ";
			SetConsoleTextColor(FOREGROUND_GREEN); cout << " зелёным цветом"; SET_DEFAULT_COLOR;
			cout << ".\nЕсли вы угадали букву из загаданного слова, но она расположена в другом месте, то она будет подсвечена ";
			SetConsoleTextColor(YELLOW_COLOR); cout << "желтым цветом"; SET_DEFAULT_COLOR; cout << '.' << endl << endl;
			continue;
		case 'e': case 'E':
			cout << "До встречи!" << endl;
			exit(0);
		default:
			cout << "Выбран неверный ключ - попробуйте снова!" << endl;
			continue;
		}
		break; //exit the loop only if 's': first break ends switch, the second one - while 
	}

}

void InGameCycle(const string* words, const size_t wordCount) {

	string wordly = words[rand() % wordCount], guess;
	const short wordLenght = wordly.length();
	const unsigned short maxAttempts = 6;
	unsigned short attempts = maxAttempts;

	cout << "В загаданном слове " << wordLenght << " букв(-ы)." << endl;

	//VS macro for debug build
#ifdef _DEBUG
	cout << "Загаданное слово: " << wordly << endl;
#endif

	do {
		cout << "Введите предполагаемое слово: "; cin >> guess;

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
		cout << "\nПоздравляем! Вы угадали слово " << wordly << " за " << (maxAttempts - attempts) << " попыток.";
	else cout << "\nВы проиграли :(\nБыло загадано слово " << wordly << '.';
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
		"день", "месяц", "год", "четыре", "пять", "скала", "сосна", "драма", "драйв", "пушка", "сушка", "бандит", "банда", "лаванда", "пропаганда", "дерево", "фен", "фея", "аниме",
		"дорама", "хентай", "хендай", "жигули", "пингвин", "слон", "дрон", "дятел", "нейрон", "музыка", "фильм", "кино", "артист", "клоун", "чёрт", "полицейский", "пожарный",
		"учёба", "учёт", "схема", "дом", "квартира", "город", "деревня", "тема", "тело", "рука", "нога", "да", "нет", "жаба", "кот", "сова", "собака", "машина", "автомобиль",
		"тепло", "холод", "пляж", "река", "купальник", "море", "океан", "вода", "пиво", "медицина", "техника", "механика", "физика", "шизофрения", "фобия", "мокрый", "сухой",
		"тёплый", "холодный", "тоска", "радость", "печаль", "смех", "слёзы", "конец", "начало", "игра", "лига", "легенда", "бой", "хор", "хурма", "апельсин", "фейхуа", "яблоко",
		"груша", "суши", "лемон", "нектарин", "витамин", "огонь", "нейромант", "некромант", "волшебство", "дружба"
	};
	//const short wordCount = 100;

	StartMenu();
	InGameCycle(words, words->size());

	char restart;
	cout << "\nХотите сыграть ещё?(y/n) "; cin >> restart; cout << endl;
	if (restart == 'y')
		InGameCycle(words, words->size());
	else cout << "\nДо встречи!" << endl;

	system("pause>nul");
	return 0;
}