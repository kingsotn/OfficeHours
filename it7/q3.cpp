#include <iostream>

using namespace std;

void swap(int a, int b)
{
        int temp;
        temp = a;
        a = b;
        b = temp;
}



int main()
{
        int arr[] = {1,7,8,5,3,6,4,2};
        int i, key, j;
        for (int i = 1; i < 8; i++) {
                key = arr[i];
                j = i-1;

                while (arr[j] > key && j >= 0) {            //swap part
                        arr[j+1] = arr[j];
                        j--;
                }
                arr[j+1] = key;

                cout << "Iteration " << i << ": \n";
                for (int k = 0; k < 8; k++) {
                        cout << arr[k] << ", ";
                }
                cout << endl;
        }
}
