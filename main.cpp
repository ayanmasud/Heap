#include <iostream>
#include <cstring>

void add(int (&heap)[100], int childIndex, int parentIndex);
void del(int (&heap)[100], int parentIndex);

using namespace std;

int main() {
  int size = 100;
  int heap[100];

  for (int i = 0; i < size; i++) {
    heap[i] = -1;
  }
  
  //odd: index*2+1 and even: index*2+2
  char cmd[8];
  while(true) {
    char cmd[8];
    cin.getline(cmd, 8);
    
    if (strcmp(cmd, "ADD") == 0) {
      int num;
      cout << "What number? ";
      cin >> num;

      for (int i = 0; i < size; i++) {
	if (heap[i] == -1) {
	  heap[i] = num;

	  int parentIndex = 0;
	  if (i != 0) {
	    if (i%2 == 0) { // divisible by 2
	      parentIndex = (i-2)/2;
	    }
	    else {
	      parentIndex = (i-1)/2;
	    }
	  }

	  add(heap, i, parentIndex);
	  
	  cout << "pix: " << parentIndex << endl;
	  if (heap[i] > heap[parentIndex]) { // if child is greater than parent, swap
	    int temp = heap[parentIndex];
	    heap[parentIndex] = heap[i];
	    heap[i] = temp;
	  }
	  
	  break;
	}
      }
    }
    else if (strcmp(cmd, "DELETE") == 0) {
      int lastIndex = 0;
      for (int i = 0; i < size; i++) {
	if (heap[i] == -1) {
	  lastIndex = i;
	  break;
	}
      }
      lastIndex--;

      heap[0] = heap[lastIndex];
      heap[lastIndex] = -1;
      
      del(heap, 0);
    }
    else if (strcmp(cmd, "PRINT") == 0) {
      for (int i = 0; i < size; i++) {
	if (heap[i] != -1) {
	  cout << heap[i] << endl;
	}
      }
    }
    else if (strcmp(cmd, "QUIT") == 0) {
      break;
    }
    cout << endl;
  }
  
  return 0;
}

void add(int (&heap)[100], int childIndex, int parentIndex) {
  if (heap[childIndex] > heap[parentIndex]) { // if child is greater than parent\
, swap
    int temp = heap[parentIndex];
    heap[parentIndex] = heap[childIndex];
    heap[childIndex] = temp;

    // the child in now held in heap[parentIndex]
    
    int newParentIndex = 0;
    if (parentIndex != 0) { // not top of the list
      if (parentIndex%2 == 0) { // divisible by 2
	newParentIndex = (parentIndex-2)/2;
      }
      else {
	newParentIndex = (parentIndex-1)/2;
      }
      
      add(heap, parentIndex, newParentIndex);
    } 
  }
}

void del(int (&heap)[100], int parentIndex) {
  if (heap[(parentIndex*2)+1] != -1) {
    if (heap[(parentIndex*2)+1] > heap[(parentIndex*2)]+2) {
      int temp = heap[parentIndex];
      heap[parentIndex] = heap[(parentIndex*2)+1];
      heap[(parentIndex*2)+1] = temp;

      del(heap, (parentIndex*2)+1);
    }
    else {
      int temp = heap[parentIndex];
      heap[parentIndex] = heap[(parentIndex*2)+2];
      heap[(parentIndex*2)+2] = temp;

      del(heap, (parentIndex*2)+2);
    }
  }
}
