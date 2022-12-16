

/*Дан массив С1, С2... С24.
  В массиве есть два элемента равные 0. Заменить все элементы, стоящие между ними, на единицы*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <clocale>
#include <iomanip>
using namespace std;

int main()
{   
    //setlocale(LC_ALL, "RUS");
    int n;
    string name;
    ifstream f;
    while (true)
    {
        system("clear");
        cout<<"Enter the file name or * to close:"<< "\t";
        getline(cin, name);

        if (name=="*")
            break;

        f.open(name);
        if (!f.is_open()){
            cout<<"Error: " << errno << " When opening a file: \"" << name << "\"\n";
            perror("Error");
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            continue;
        }

        /*n=0;
        string s;
        bool err = false;
        int p;
        while (true)
        {
            f >> ws;
            if(f.eof()) break;
            p = f.tellg();
            int a;
            f >> a;
            char c;
            if (f.fail() || (c = f.peek(), c !=' ' and c!='\t' and c!='\n' and c!=EOF))
            {
                err = true;
                f.clear();
                f.seekg(p);
                f >> s;
                break;
            }
            n++;
        }

        if (err){
            f.close();
            cout<<"Error entering an element \""<< s << "\" under the number: " << n+1 <<
             " , at the position of the first character " <<
                p << endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            continue;
        }

        if (n == 0){
            f.close();
            cout<<"none"<<endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            continue;
        }*/

        string s; 
        istringstream ss; 
        bool err=false; 
        int n = 0;
        int p;
        while (!(f>>ws).eof()) { 
            f>>s; 
            ss.str(s); ss.clear();
            int e; 
            ss>>e; 
            if (!ss.eof() || ss.fail())  { 
                err=true; 
                break; 
            } 
            n++;
        }

        if (err){
            p = f.tellg();
            f.close();
            cout<<"Error entering an element \""<< s << "\" under the number: " << n+1 <<
             " , at the position of the first character " <<
                p-s.size() << endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            continue;
        }

        if (n == 0){
            f.close();
            cout<<"none"<<endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            continue;
        }

        /*int *arr = new(nothrow) int[n];  //подавление исключений
        if (!arr)
        {
            f.close();
            cout<<"error when allocating memory for an array"<<endl;
            system("pause");
            continue;
        }*/

        
        int *arr;

        try {
           arr = new int[n];
        }
        catch(...) {
            f.close();
            cout<<"error when allocating memory for an array"<<endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            continue;
        }

        f.clear();
        f.seekg(0);

        
        int ind1, ind2, k=0;

        for(int i=0; i<n; i++)
        {
            f>>arr[i];

            if(arr[i]==0){
                ind2=i;
                k++;
            }
        }

        f.close();
        
        cout<<"Source array"<<endl;
        cout<<"Numbers: ";
            
        for(int i=1; i<=n; i++)
            cout << setw(8) << i;
            
        cout << endl << "Elements:";
            
        for (int i = 0; i < n; i++)                         
            cout << setw(8) << arr[i];
        cout << endl;

        for(int i=n; i>=0; i--)
            if(arr[i]==0) ind1=i;
        
        if (k<2)
        {
            delete [] arr;
            cout<<"There are no two zeros in the file: \""<<name<<"\"\n.";
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            continue;
        }

        
        cout<<"Resulting array"<<endl;
        cout<<"Numbers: ";
            
        for(int i=1; i<=n; i++)
            cout << setw(8) << i;

        cout << endl << "Elements:";  
            
        for(int i=0; i<n; i++)
        {
            if(i>ind1 and i<ind2) 

                arr[i]=1;
            
            cout<<setw(8)<<arr[i];
        }
        
        delete [] arr;
        cout<<endl;
        //system("pause");
        cout << "Press enter to continue!\n";
        cin.ignore();

    }
}