#include <iostream>
using namespace std;

int* maxwell(int* a, int* b)
{
    if (*a > *b)
        return a;
    else
        return b;
}

void swap1(int* a, int* b)
{
    int* temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int array[6] = { 5, 3, 4, 17, 22, 19 };

    int* ptr = maxwell(array, &array[2]); // returns a pointer to which 5, because 5 is greater than 4 which is *(&array[2])
    cout << *ptr << endl;
    *ptr = -1; // *ptr pointed to array[0], which was equal to 5. Now array[0] is equal to 4.
    ptr += 2; // move the pointer ahead 2 spaces, so now the pointer points to 
    ptr[1] = 9;
    *(array+1) = 79;

    cout << &array[5] - ptr << endl;

    swap1(&array[0], &array[1]);
    swap2(array, &array[2]);

    for (int i = 0; i < 6; i++)
        cout << array[i] << endl;
} 