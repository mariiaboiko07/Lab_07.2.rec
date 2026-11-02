// Lab_07.2.rec.cpp
// Лабораторна робота № 07.2.rec
// Опрацювання багатовимірних масивів ітераційними способами.
// Варіант 1

#include <iostream> 
#include <iomanip>  
#include <time.h>   

using namespace std; 

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo);
void CreateRows(int** a, const int N, const int Low, const int High, int rowNo);

void PrintRow(int** a, const int rowNo, const int N, int colNo);
void PrintRows(int** a, const int N, int rowNo);


void TransposeRow(int** a, const int rowNo, const int N, int colNo);
void TransposeRows(int** a, const int N, int rowNo);

int main()
{
    
    srand((unsigned)time(NULL));

    int N; 
    cout << "N = ";
    cin >> N; 

    // Динамічне виділення пам'яті під масив вказівників (рядків)
    int** a = new int* [N];
    for (int i = 0; i < N; i++)
        a[i] = new int[N]; 

    
    int Low = -10;
    int High = 10;

    // Рекурсивний виклик формування початкової матриці 
    CreateRows(a, N, Low, High, 0);

    
    cout << "\nInitial matrix:" << endl;
    PrintRows(a, N, 0);

    // Рекурсивний виклик транспонування матриці 
    TransposeRows(a, N, 0);

    
    cout << "Transposed matrix:" << endl;
    PrintRows(a, N, 0);

    // Звільнення виділеної динамічної пам'яті
    for (int i = 0; i < N; i++)
        delete[] a[i]; 
    delete[] a;        

    return 0; 
}


// Рекурсивна функція заповнення одного рядка (рух по стовпчиках colNo)
void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo)
{
    
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1); 
}

// Рекурсивна функція обходу всіх рядків для створення всієї матриці
void CreateRows(int** a, const int N, const int Low, const int High, int rowNo)
{
    // Запускаємо заповнення поточного рядка rowNo починаючи з 0-го стовпчика
    CreateRow(a, rowNo, N, Low, High, 0);
    if (rowNo < N - 1)
        CreateRows(a, N, Low, High, rowNo + 1); 
}



// Рекурсивна функція друку одного рядка (рух по стовпчиках colNo)
void PrintRow(int** a, const int rowNo, const int N, int colNo)
{
    cout << setw(5) << a[rowNo][colNo];

    
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1); 
    else
        cout << endl; 
}

// Рекурсивна функція обходу всіх рядків для друку всієї матриці
void PrintRows(int** a, const int N, int rowNo)
{
    PrintRow(a, rowNo, N, 0);

    if (rowNo < N - 1)
        PrintRows(a, N, rowNo + 1); 
    else
        cout << endl; 
}

// Рекурсивна функція транспонування елементів у межах одного рядка rowNo
void TransposeRow(int** a, const int rowNo, const int N, int colNo)
{
    
    if (colNo < N)
    {
        
        int tmp = a[rowNo][colNo];       
        a[rowNo][colNo] = a[colNo][rowNo]; 
        a[colNo][rowNo] = tmp;             

        
        TransposeRow(a, rowNo, N, colNo + 1);
    }
}

// Рекурсивна функція обходу всіх рядків для транспонування всієї матриці
void TransposeRows(int** a, const int N, int rowNo)
{
    
    if (rowNo < N - 1)
    {
        // colNo передається як (rowNo + 1), 
        // щоб обробляти ТІЛЬКИ елементи ВИЩЕ головної діагоналі!
        TransposeRow(a, rowNo, N, rowNo + 1);
        TransposeRows(a, N, rowNo + 1);
    }
}