#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string.h>

using namespace std;

#pragma region enums
enum Majors {
	ComputerScience = 1,
	Informatics,
	MathematicsAndEconomics,
	PhysicsAndInformatics,
	LaborTraining
};
enum Subjects {
	Physics = 1,
	Math,
	Prog,
	Num_methods,
	Pedagogika
};
#pragma endregion enums

#pragma region prototypes
void try_input(const char message[], Majors& a);
void try_input(const char message[], unsigned short& a);
#pragma endregion prototypes

#pragma region student_struct
#pragma pack(push, 1) //less memory using
struct Student {
	string return_prizv() {
		return this->prizv;
	}
	unsigned short return_course() {
		return this->course;
	}
	string return_major_name() {
		switch (this->major) {
		case ComputerScience:
			return "Комп'ютерні науки";
		case Informatics:
			return "Інформатика";
		case MathematicsAndEconomics:
			return "Математика & Економіка";
		case PhysicsAndInformatics:
			return "Фізика & Інформатика";
		case LaborTraining:
			return "Трудове навчання";
		}
	}
	Majors return_major() {
		return this->major;
	}
	unsigned short return_physics() {
		return this->physics;
	}
	unsigned short return_math() {
		return this->math;
	}
	unsigned short return_prog() {
		return this->prog;
	}
	unsigned short return_num_methods() {
		return this->num_methods;
	}
	unsigned short return_pedagogika() {
		return this->pedagogika;
	}
	unsigned short return_third() {
		switch (this->major) {
		case ComputerScience:
			return this->prog;
		case Informatics:
			return this->num_methods;
		default:
			return this->pedagogika;
		}
	}
	void fill_struct(int i) {
		int temp;
		cout << "Студент №" << i + 1 << endl;
		cout << "Прізвище: "; cin >> this->prizv;
		try_input("Курс: ", this->course);
		try_input("Спеціальність \n\n(Комп'ютерні науки = 1, \nІнформатика = 2, \nМатематика & Економіка = 3, \nФізика & Інформатика = 4, \nТрудове навчання = 5)\n\n: ", this->major);
		try_input("Оцінка з фізики: ", this->physics);
		try_input("Оцінка з математики: ", this->math);

		switch (this->major) {
		case ComputerScience:
			try_input("Оцінка з програмування: ", this->prog);
			break;
		case Informatics:
			try_input("Оцінка з чисельних методів: ", this->num_methods);
			break;
		case MathematicsAndEconomics:
		case PhysicsAndInformatics:
		case LaborTraining:
			try_input("Оцінка з педагогіки: ", this->pedagogika);
			break;
		}
	}
private:
	string prizv;
	unsigned short course;
	Majors major;
	unsigned short physics;
	unsigned short math;
	union {
		unsigned short prog;
		unsigned short num_methods;
		unsigned short pedagogika;
	};
};
#pragma pack(pop)    // return old config 
#pragma endregion student_struct

#pragma region functions
void fill_arr(Student* arr, int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = Student();
		arr[i].fill_struct(i);
		cout << endl;
	}
}

void try_input(const char message[], Majors& a) {
	bool fail;
	int var;
	do {
		fail = false;
		cout << message; cin >> var;
		if (var < ComputerScience || var > LaborTraining) {
			fail = true;
		}
		else {
			a = (Majors)var;
		}
		if (cin.fail()) {
			fail = true;
			cout << "Неправильний ввід!\n";
			cin.clear();
			cin.ignore(65535, '\n');
		}
	} while (fail);
}

void try_input(const char message[], unsigned short& a) {
	bool fail;
	do {
		fail = false;
		cout << message; cin >> a;
		if (cin.fail()) {
			fail = true;
			cout << "Неправильний ввід!\n";
			cin.clear();
			cin.ignore(65535, '\n');
		}
	} while (fail);
}

int calc_n(int n) {
	int res = 0;
	while (n != 0) {
		n /= 10;
		res++;
	}
	return res;
}

int lenOfLongestPrizv(Student* arr, int n) {
	int res = -1;
	for (int i = 0; i < n; i++) {
		if (static_cast<int>(arr[i].return_prizv().length()) > res) {
			res = static_cast<int>(arr[i].return_prizv().length());
		}
	}
	return res;
}

void printHeader(Student* arr, int n) {
	int width = lenOfLongestPrizv(arr, n);
	(width <= 8) ? (width = 8) : (NULL);
	int maxDigits = calc_n(n);

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "=";
	}
	cout << endl;

	cout << "|" << setw(maxDigits) << right << "№";
	cout << "|" << setw(width) << left << "Прізвище" << "| Курс |     Спеціальність    | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << "|" << setw(maxDigits) << right << i + 1;
		cout << "|" << setw(width) << left << arr[i].return_prizv();
		cout << "|" << setw(6) << left << arr[i].return_course();
		cout << "|" << setw(22) << left << arr[i].return_major_name();
		cout << "|" << setw(8) << left << arr[i].return_physics();
		cout << "|" << setw(12) << left << arr[i].return_math();
		cout << "|" << setw(15) << left;
		(arr[i].return_major() == ComputerScience ? cout << arr[i].return_prog() : cout << "-");
		cout << "|" << setw(17) << left;
		(arr[i].return_major() == Informatics ? cout << arr[i].return_num_methods() : cout << "-");
		cout << "|" << setw(12) << left;
		(arr[i].return_major() != ComputerScience && arr[i].return_major() != Informatics ? cout << arr[i].return_pedagogika() : cout << "-");
		cout << setw(13) << "|" << endl;
	}

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "-";
	}
	cout << endl;
}

void sort(Student* arr, int n) {
	Student tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j].return_course() > arr[j + 1].return_course() ||
				arr[j].return_course() == arr[j + 1].return_course() && arr[j].return_third() > arr[j + 1].return_third() ||
				arr[j].return_course() == arr[j + 1].return_course() && arr[j].return_third() == arr[j + 1].return_third() && arr[j].return_prizv() < arr[j + 1].return_prizv()) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void make_index_arr(Student* arr, int n, int* mas) {
	for (int i = 0; i < n; i++) {
		mas[i] = i;
	}

	int i, j, value;
	for (int i = 1; i < n; i++) {
		value = mas[i];
		for (j = i - 1; j >= 0; j--) {
			bool should_swap = false;

			if (arr[mas[j]].return_course() > arr[mas[j + 1]].return_course()) {
				should_swap = true;
			}

			else if (arr[mas[j]].return_course() == arr[mas[j + 1]].return_course() &&
				arr[mas[j]].return_third() > arr[mas[j + 1]].return_third()) {
				should_swap = true;
			}

			else if (arr[mas[j]].return_course() == arr[mas[j + 1]].return_course() &&
				arr[mas[j]].return_third() == arr[mas[j + 1]].return_third() &&
				arr[mas[j]].return_prizv() > arr[mas[j + 1]].return_prizv()) {
				should_swap = true;
			}

			if (should_swap) {
				mas[j + 1] = mas[j];
			}
			else {
				break;
			}
		}
		mas[j + 1] = value;
	}
}

void print_index_sorted(Student* arr, int n, int* index_arr) {
	int width = lenOfLongestPrizv(arr, n);
	(width <= 8) ? (width = 8) : (NULL);
	int maxDigits = calc_n(n);
	cout << "Вивід через масив індексів:\n";
	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "=";
	}
	cout << endl;

	cout << "|" << setw(maxDigits) << right << "№";
	cout << "|" << setw(width) << left << "Прізвище" << "| Курс |     Спеціальність    | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << "|" << setw(maxDigits) << right << i + 1;
		cout << "|" << setw(width) << left << arr[index_arr[i]].return_prizv();
		cout << "|" << setw(6) << left << arr[index_arr[i]].return_course();
		cout << "|" << setw(22) << left << arr[index_arr[i]].return_major_name();
		cout << "|" << setw(8) << left << arr[index_arr[i]].return_physics();
		cout << "|" << setw(12) << left << arr[index_arr[i]].return_math();
		cout << "|" << setw(15) << left;
		(arr[i].return_major() == ComputerScience ? cout << arr[i].return_prog() : cout << "-");
		cout << "|" << setw(17) << left;
		(arr[i].return_major() == Informatics ? cout << arr[i].return_num_methods() : cout << "-");
		cout << "|" << setw(12) << left;
		(arr[i].return_major() != ComputerScience && arr[i].return_major() != Informatics ? cout << arr[i].return_pedagogika() : cout << "-");
		cout << setw(13) << "|" << endl;
	}

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "-";
	}
	cout << endl;
}

void print_index_arr(int* arr, int n) {
	cout << "Індексний масив: {";
	for (int i = 0; i < n; i++) {
		cout << setw(2) << arr[i];
	}
	cout << "}\n";
}

int binSearch(Student* arr, int n, string prizv, unsigned short course, unsigned short third) {
	int L = 0, R = n - 1, m;
	do {
		m = (L + R) / 2;
		if (arr[m].return_prizv() == prizv && arr[m].return_course() == course && arr[m].return_third() == third)
			return m;
		if ((arr[m].return_prizv() < prizv) || (arr[m].return_prizv() == prizv && arr[m].return_course() < course) || (arr[m].return_prizv() == prizv && arr[m].return_course() == course && arr[m].return_third() == third))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

void menu(Student* arr, int n, int* index_arr) {
	int option_1, option_2, res;
	string prizv_;
	bool _continue;

	while (true) {
		cout << "[Меню]: \n";
		cout << "[1] Вивести список студентів\n";
		cout << "[2] Сортування списку студентів\n";
		cout << "[3] Пошук студента\n";
		cout << "[4] Вихід\n : ";
		cin >> option_1;

		switch (option_1) {
		case 1:
			cout << "Список студентів:\n";
			printHeader(arr, n);
			break;
		case 2:
			_continue = true;
			while (_continue) {
				cout << "[1] Фізичне впорядкування списку студентів\n";
				cout << "[2] Індексний масив списку\n";
				cout << "[3] Назад\n : ";
				cin >> option_2;

				switch (option_2) {
				case 1:
					sort(arr, n);
					_continue = false;
					break;
				case 2:
					make_index_arr(arr, n, index_arr);
					print_index_arr(index_arr, n);
					print_index_sorted(arr, n, index_arr);
					_continue = false;
					break;
				case 3:
					_continue = false;
					break;
				default:
					cout << "Неправильний ввід\n";
					break;
				}
			}
			break;

		case 3:
			unsigned short course, third;
			bool fail;
			do {
				fail = false;
				cout << "Введіть прізвище: "; cin >> prizv_;
				if (cin.fail()) {
					fail = true;
					cout << "Неправильний ввід!\n";
					cin.clear();
					cin.ignore(65535, '\n');
				}
			} while (fail);
			try_input("Введіть курс: ", course);
			try_input("Введіть оцінку з профільного предмету: ", third);
			sort(arr, n);
			res = binSearch(arr, n, prizv_, course, third);
			(res != -1) ? (cout << "Знайдено студента з індексом " << res) : (cout << "Не знайдено студента");
			cout << endl << endl;
			break;

		case 4:
			cout << "Завершення роботи";
			return;

		default:
			cout << "Неправильний ввід\n";
			break;
		}
	}
}

#pragma endregion functions

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned short n;
	try_input("Введіть кількість студентів: ", n);

	Student* arr = new Student[n];
	int* index_arr = new int[n];

	fill_arr(arr, n);

	menu(arr, n, index_arr);

	delete[] index_arr;
	delete[] arr;
}