

/*Дан массив С1, С2... С24.
  В массиве есть два элемента равные 0. Заменить все элементы, стоящие между ними, на единицы*/



#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
using namespace std;

typedef int elemType;

elemType n = 0;

int getch() {
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

int main(){

    elemType *arr = nullptr;
    char number;
    string name;

    while(true)
    {
        system("clear");
        cout << "1.Upload data to a file\n" <<
                "2.Load an array from a file\n" <<
                "3.Display an array\n" <<
                "4.Display the processed array\n" <<
                "5.Exit\n";

        number = getch();
        fstream file;
        string name;
        elemType ind1, ind2, k=0;
        switch (number)
        {
        case '1':
            system("clear");
            while(true)
            {
                cout<<"input size: ";
                while(true)
                {
                    
                    cin >> n;
                    char c;
                    if ((cin.fail() || (c = cin.peek(), c !=' ' and c!='\t' and c!='\n' and c!=EOF)) || n <= 0)
                    {
                        cin.clear(); cin.ignore();
                        cout<<"error, input size: "<<endl;
                        continue;
                    }
                    break;
                }
                delete[] arr;
                try{
                    arr = new elemType[n];
                }
                catch (...) {
                    cout <<"error when allocating memory for an array"<<endl;
                    continue;
                }
                
                cout << "input: " << endl;
                while(true)
                {
                    for (elemType i=0; i<n; i++){
                        char c;
                        cin >> arr[i];
                        if(cin.fail() || (c = cin.peek(), c !=' ' and c!='\t' and c!='\n' and c!=EOF)){/////////////////////////////////
                            cin.clear(); cin.ignore();
                            cout<<"error, input elements: "<<endl;
                            continue;
                        }
                    }
                    break;    
                }

                while(true)
                {
                    cout << "input file name or * to exit: " ;
                    getline(cin >> ws, name);

                    if (name == "*"){
                        break;
                    }
                    
                    file.open(name, ios::in | ios::binary);
                    if (file.is_open()){
                        file.close();
                        cout << "Press 1 to overwrite or 2 to exit: "<<endl;
                        char choice = getchar();
                        if(choice != '1'){
                            continue;;
                        }
                        
                    }
                    file.open(name, ios::out | ios::binary);
                    if (!file.is_open()){
                        cout<<"Error: " << errno << " When opening a file: \"" << name << "\"\n";
                        perror("Error");
                        //system("pause");
                        cout << "Press enter to continue!\n";
                        cin.ignore();
                        continue;
                    }
                    break;
                }
                
                file.write((char*)&n, sizeof(elemType));
                file.write((char*)arr, n * sizeof(elemType));
                file.close();
                break;                
            }
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            break;
        case '2':
            system("clear");
            while (true) 
            {
                cout << "input file name or * to exit: " << endl;
                getline(cin, name);
                if (name == "*"){
                    break;
                }

                file.open(name, ios::binary | ios::in);

                if (!file.is_open()){
                    cout<<"Error: " << errno << " When opening a file: \"" << name << "\"\n";
                    perror("Error");
                    //system("pause");
                    cout << "Press enter to continue!\n";
                    cin.ignore();
                    continue;
                }


                file.seekg(0, ios::end);
                n = file.tellg();

                if (n % sizeof(elemType)){/////
                    file.close();
                    cout << "error data" << endl;
                    break;
                }
                file.clear();
                file.seekg(0);
                //проверка n
                //ElempType
                file.read((char*)&n, sizeof(elemType));
                cout << "numbers in arr " << n << endl;
                delete[]arr;
                try
                {
                    arr = new elemType[n];
                }
                catch (...)
                {
                    file.close();
                    cerr << "error when allocating memory for an array" << endl;
                    continue;

                }

                file.read((char*)arr, n * sizeof(elemType));
                file.close();
                break;
            }
                    
            
        case '3':
            system("clear");
    
            if(n==0){
                cout<<"there is no loaded array"<<endl;
                //system("pause");
                cout << "Press enter to continue!\n";
                cin.ignore();
                break;
            }
            
            cout<<"Numbers: ";
                
            for(elemType i=1; i<=n; i++)
                cout << setw(8) << i;
                
            cout << endl << "Elements:";
                
            for (elemType i = 0; i < n; i++)                         
                cout << setw(8) << arr[i];
            cout << endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            break;

        case '4':
            system("clear");

            if(n==0){
                cout<<"there is no loaded array"<<endl;
                //system("pause");
                cout << "Press enter to continue!\n";
                cin.ignore();
                break;
            }

            for(elemType i=0; i<n; i++)
            {
                file>>arr[i];

                if(arr[i]==0){
                    ind2=i;
                    k++;
                }
            }
            
            cout<<"Source array"<<endl;
            cout<<"Numbers: ";
                
            for(elemType i=1; i<=n; i++)
                cout << setw(8) << i;
                
            cout << endl << "Elements:";
                
            for (elemType i = 0; i < n; i++)                         
                cout << setw(8) << arr[i];
            cout << endl;

            for(elemType i=n; i>=0; i--)
                if(arr[i]==0) ind1=i;
            
            if (k<2)
            {
                cout<<"There are no two zeros in the file: \""<<name<<"\".\n";
                //system("pause");
                cout << "Press enter to continue!\n";
                cin.ignore();
                continue;
            }

            cout<<"Resulting array"<<endl;
            cout<<"Numbers: ";
                
            for(elemType i=1; i<=n; i++)
                cout << setw(8) << i;

            cout << endl << "Elements:";  
                
            for(elemType i=0; i<n; i++)
            {
                if(i>ind1 and i<ind2) 

                    arr[i]=1;
                
                cout<<setw(8)<<arr[i];
            }
            cout<<endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            break;
        case '5':
            system("clear");
            delete[]arr;
            exit(0);

        default:
            system("clear");
            cout << "Incorrect, select from 1 to 5" << endl;
            //system("pause");
            cout << "Press enter to continue!\n";
            cin.ignore();
            break;
        }
    }
}
