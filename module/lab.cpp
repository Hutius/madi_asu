#include "lab.h"



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
