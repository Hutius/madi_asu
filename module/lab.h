#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <clocale>
 
using namespace std;

typedef int elemType;
 

enum error {
    memore_fail,
    not_rectangular,
    good,
    no_open,
    WrongElem,
    eof,
};


error memory_check(elemType**& matr, elemType m, elemType n);
void Delete(elemType** matr, elemType m);
void in_matr(ifstream& file, elemType**& matr, elemType m, elemType n);
error file_check(ifstream& file,  elemType& m, elemType& n,  elemType**& matr, string& path);
string show_matr(elemType**& matr, elemType m, elemType n);
void processing(elemType**& matr, elemType m, elemType n);