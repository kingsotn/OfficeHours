#include <iostream>
#include <string>
using namespace std;

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
class minHeap
{
public:
  int *arr;
  int capacity;
  int heap_size;

  minHeap(int c)
  {
    capacity = c;
    heap_size = 0;
    arr = new int[c];
  }
  int root(int i) { return (i-1)/2; }
  int left(int i) { return (2*i + 1); }
  int right(int i) { return (2*i + 2); }
  void insert(int val) {
    if (heap_size == capacity)
    {
      cout << "empty";
      return;
    }

    //insert new value at the end
    heap_size++;
    int i = heap_size -1;
    arr[i] = val;

//while root > current
    while (i != 0 && arr[root(i)] > arr[i])
    {
      swap(&arr[i], &arr[root(i)]);
      i = root(i);
    }
  }
};

int main()
{
    minHeap h(10);
    h.insert(3);
    h.insert(2);
    h.insert(15);
    h.insert(5);
    h.insert(4);
    h.insert(45);
    h.insert(100);
    h.insert(1);
    h.insert(5);
    h.insert(20);

    for (int i= 0; i < 10; i++)
    {
      cout << h.arr[i] <<" ";
    }
    return 0;
}
