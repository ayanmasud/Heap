#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>


void add(int (&heap)[100], int childIndex, int parentIndex);
void del(int (&heap)[100], int parentIndex);
void print(int (&heap)[100], int position, int depth, int size);

using namespace std;

int main() {
  srand(time(NULL)); // for random numbers seed

  // reading the file of numbers seperated by spaces into an int array
  int ranArr[50];
  int ranArrI = 0;
  ifstream file("input.txt");
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string word;
      while (ss >> word) { // string stream helps with the splitting by spaces
	ranArr[ranArrI] = stoi(word); // convert the string to int
	//cout << ranArr[ranArrI] << endl;
	ranArrI++;
      }
    }
    file.close();
  } else { // files not there
    cout << "Unable to open file";
  } 

  // information on what commands user can do
  cout << "'ADD' to add a number" << endl;
  cout << "'RANDOM' to add random numbers" << endl;
  cout << "'DELETE' to delete the biggest number" << endl;
  cout << "'DELALL' deletes everything" << endl;
  cout << "'PRINT' to print the tree" << endl;
  cout << "'QUIT' to leave" << endl;
  
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
	  
	  //cout << "pix: " << parentIndex << endl;
	  if (heap[i] > heap[parentIndex]) { // if child is greater than parent, swap
	    int temp = heap[parentIndex];
	    heap[parentIndex] = heap[i];
	    heap[i] = temp;
	  }
	  
	  break;
	}
      }
    }
    else if (strcmp(cmd, "RANDOM") == 0) {
      int num = ranArr[(rand() % 51)];

      // copied code from add command
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

          //cout << "pix: " << parentIndex << endl;
          if (heap[i] > heap[parentIndex]) { // if child is greater than parent\
, swap
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
    else if (strcmp(cmd, "DELALL") == 0) {
      for (int i = 0; i < size; i++) {
	heap[i] = -1;
      }
    }
    else if (strcmp(cmd, "PRINT") == 0) {
      /*for (int i = 0; i < size; i++) {
	if (heap[i] != -1) {
	  cout << heap[i] << endl;
	}
	}*/

      int len = 0;
      for (int i = 0; i < size; i++) {
        if (heap[i] == -1) {
          len = i;
          break;
        }
      }
      //cout << len;

      print(heap, 0, 0, len);
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

// PRINT NOT WORKING YET
void print(int (&heap)[100], int position, int depth, int size) {
  cout << "ran" << endl;
  int temp = 1;
  if (position == 0) {
    cout << "first";
    temp = 0;
    position = 1;
  }
  if ((position*2) <= size && heap[(position*2)] != -1) { // check right not NULL
    cout << "second";
    print(heap, position*2, depth + 1, size); // recurse right
  }
  for (int a = 0; a < depth; a + 1) {
    cout << '\t';
  }

  cout << "break";
  if (temp == 0) {
    cout << heap[temp] << endl;
  }
  else {
    cout << heap[position] << endl;
  }
  
  if ((position*2)-1 < size) { 
    print(heap, (position*2) - 1, depth + 1, size);
    cout << "left";
  }
}
