#include "lab.h"


int main()
{
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