

/*Определить номер строки с минимальным количеством нулевых элементов
		и сложить элементы этой строки с соответствующими элементами всех нечетных
	 строк.*/

#include <clocale>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

typedef int elemType;

enum error {
	good,
	memore_fail,
	not_rectangular,
	no_open,
	WrongElem,
	eof,
};

void Delete(elemType** matr, int m) {
	for (int k = 0; k < m; k++)

		delete[] matr[k];

	delete[] matr;
}

error memory_check(elemType**& matr, int m, int n) {
	matr = new (nothrow) elemType *[m];
	if (matr) {

		for (int i = 0; i < m; i++) {

			matr[i] = new (nothrow) elemType[n];

			if (!matr[i]) {

				Delete(matr, i);

				matr = NULL;
				break;
			}
		}
	}
	if (!matr)
		return memore_fail;

	return good;
}

void in_matr(ifstream& file, elemType**& matr, int m, int n) {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) 
			file >> matr[i][j];
		
	}
}

error file_check(ifstream& file, int& m, int& n, elemType**& matr, string& path) {


	file.open(path);

	if (!file.is_open()) return no_open;


	bool b = true;
	elemType d;
	elemType k = 0;
	string s;

	while (b) {

		file >> ws;
		if (file.eof()) {
			file.close();
			return eof;
		}
		int position = file.tellg();
		file >> d;

		char s;
		if (file.fail() ||
				(s = file.peek(), s != EOF && s != '\n' && s != '\t' && s != ' ')) {
			return WrongElem;
		}

		n++;
		char c = 0;
		while (c != EOF) {

			c = file.get();
			switch (c) {
			case ' ':
			case '\t':
				break;

			case EOF:
				b = false;

			case '\n':
				if (n != 0) {
					if (m == 0) {
						k = n;
					}
					if (k != n) {
						b = false;
						file.close();
						return not_rectangular;
					}
					m++;
					n = 0;
				}
				break;

			default:
				file.unget();
				c = EOF;
			}
		}
	}

	file.clear();
	file.seekg(0);

	n = k;

	memory_check(matr, m, n);

	in_matr(file, matr, m, n);
	return good;
}

string show_matr(elemType**& matr, int m, int n) {
	ostringstream os;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			os << setw(8) << matr[i][j];
		}
		os << "\n";
	}
	return os.str();
}

void processing(elemType **&matr, int m, int n) {
	int line = 0;
	int kmin = n;
	for (int i = 0; i < m; i++) {
		int s = 0;
		for (int j = 0; j < n; j++)
			if (matr[i][j] == 0)
				s++;
		if (s != 0 && s < kmin) {
			kmin = s;
			line = i;
		}
	}

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i += 2)
			if (i < line)
				matr[line][j] += matr[i][j];
	}
}

int main() {
	system("clear");
	setlocale(LC_ALL, "ru");

	elemType **matr = nullptr;

	while (true) {
		ifstream file;
		string path;
		elemType m = 0;
		elemType n = 0;
		string elem;
		error flag;

		cout << "Enter the file name or * to close:"
				 << "\t";
		getline(cin >> ws, path);
		if (path == "*") {
			break;
		}

		flag = file_check(file, m, n, matr, path);

		switch (flag) {

		case eof:
			// file.close();
			cout << "the file is empty" << endl;
			continue;

		case no_open:
			cout << "Error: " << errno << " When opening a file: \"" << path
					 << "\"\n";
			perror("Error");
			continue;

		case WrongElem:
			file.clear();
			file >> elem;
			file.close();
			cout << "Element \"" << elem << " \" arr in [" << m + 1 << ";" << n + 1
					 << "]" << endl;
			continue;

		case not_rectangular:
			// file.close();
			cout << "not rectangular" << endl;
			continue;

		case memore_fail:
			//file.close();
			cout << "error when allocating memory for an array" << endl;
			continue;

		default:
			break;
		}

		cout << "m = " << m << "\n"
				 << "n = " << n << "\n";

		file.close();

		cout << "Source array" << endl;

		cout << show_matr(matr, m, n) << endl;

		processing(matr, m, n);

		cout << "Resulting array" << endl;

		cout << show_matr(matr, m, n) << endl;

		Delete(matr, m);

		// system("pause");
		cout << "Press enter to continue!\n";
		cin.ignore();
		system("clear");
	}

	return 0;
}