/*Heap: a binary tree where every node is larger than its child
  Author: Ayan Masud
  Date: 2/16/25
 */
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
  int ranArr[80];
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
    
    if (strcmp(cmd, "ADD") == 0) { // add command
      int num;
      cout << "What number? ";
      cin >> num; // user input

      for (int i = 0; i < size; i++) {
	if (heap[i] == -1) {
	  heap[i] = num; // sets the next available to the added one

	  int parentIndex = 0;
	  if (i != 0) { // find the parent of the added one
	    if (i%2 == 0) { // if divisible by 2, use this formula
	      parentIndex = (i-2)/2;
	    }
	    else { // if its odd, use this formula
	      parentIndex = (i-1)/2;
	    }
	  }

	  add(heap, i, parentIndex); // swaps it with its parent if its bigger
	  
	  break;
	}
      }
    }
    else if (strcmp(cmd, "RANDOM") == 0) { // add a random number 1-1000
      int num = ranArr[(rand() % 81)];

      // copied code from add command
      for (int i = 0; i < size; i++) {
        if (heap[i] == -1) {
          heap[i] = num; // sets next available to the random one added

          int parentIndex = 0;
          if (i != 0) {
            if (i%2 == 0) { // divisible by 2, use this formula
              parentIndex = (i-2)/2;
            }
            else { // odd, use this formula
              parentIndex = (i-1)/2;
            }
          }

          add(heap, i, parentIndex); // swaps it with its parent if its bigger

          break;
        }
      }
    }
    else if (strcmp(cmd, "DELETE") == 0) { // delete the root, swap it with the last, re-settle the list by swapping the new root with whichever of its children are greater
      int lastIndex = 0;
      for (int i = 0; i < size; i++) { // find the index of the last one
	if (heap[i] == -1) {
	  lastIndex = i;
	  break;
	}
      }
      lastIndex--;

      cout << "deleting " << heap[0] << endl; // outputting the root

      heap[0] = heap[lastIndex]; // swap the first and last
      heap[lastIndex] = -1; // remove the last
      
      del(heap, 0); // make the list re-settle
    }
    else if (strcmp(cmd, "DELALL") == 0) { // remove everything in array
      for (int i = 0; i < size; i++) {
	heap[i] = -1;
      }
    }
    else if (strcmp(cmd, "PRINT") == 0) { // print the tree
      int len = 0;
      for (int i = 0; i < size; i++) { // find the size of the array
        if (heap[i] == -1) {
          len = i;
          break;
        }
      }

      print(heap, 0, 0, len); // print it out using this function
    }
    else if (strcmp(cmd, "QUIT") == 0) { // quit command
      break;
    }
    cout << endl;
  }
  
  return 0;
}

void add(int (&heap)[100], int childIndex, int parentIndex) {
  if (heap[childIndex] > heap[parentIndex]) { // if child is greater than parent, swap
    int temp = heap[parentIndex];
    heap[parentIndex] = heap[childIndex];
    heap[childIndex] = temp;

    // the child in now held in heap[parentIndex]
    
    int newParentIndex = 0;
    if (parentIndex != 0) { // not top of the list
      if (parentIndex%2 == 0) { // divisible by 2, use this formula for its new parent
	newParentIndex = (parentIndex-2)/2;
      }
      else { // if its odd, use this formula for its new parent
	newParentIndex = (parentIndex-1)/2;
      }
      
      add(heap, parentIndex, newParentIndex); // recursion
    } 
  }
}

void del(int (&heap)[100], int parentIndex) {
  if (heap[(parentIndex*2)+1] != -1) { // if its left child is not null
    if (heap[(parentIndex*2)+1] > heap[(parentIndex*2)]+2) { // if the left child is greater than the right child, swap with left one
      int temp = heap[parentIndex];
      heap[parentIndex] = heap[(parentIndex*2)+1];
      heap[(parentIndex*2)+1] = temp;

      del(heap, (parentIndex*2)+1); // recursion
    }
    else { // if the right child is greater than the left child, swap with right one
      int temp = heap[parentIndex];
      heap[parentIndex] = heap[(parentIndex*2)+2];
      heap[(parentIndex*2)+2] = temp;

      del(heap, (parentIndex*2)+2); // recursion
    }
  }
}

void print(int (&heap)[100], int position, int depth, int size) {
  if (position >= size || heap[position] == -1) { // it ends when it reaches the end
    return;
  }
  
  if ((position*2)+2 < size && heap[(position*2)+2] != -1) { // printing right children
    print(heap, (position*2)+2, depth + 1, size); // recursion
  }
  for (int a = 0; a < depth; a++) { // print nodes with tabs
    cout << '\t';
  }
  cout << heap[position] << endl; // actually print out the value
  
  if ((position*2)+1 < size && heap[(position*2)+1] != -1) { // printing left children
    print(heap, (position*2)+1, depth + 1, size); // recursion
  }
}
