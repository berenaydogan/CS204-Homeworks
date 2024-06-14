class LinkedListSet {
  //TO DO: Implement and make it work with the following driver code
  //Submit only this file
};

int main() {

  // Example usage
  LinkedListSet set1;
  set1 + 1 + 2 + 3 + 17; // Insertion
  set1.display();   
  
  set1 - 2; // Deletion
  set1.display(); 
  
  LinkedListSet set2;
  set2 + 3 + 4 + 5; 
  set2.display();   
  
  set2 += set1 + 7 + 3 + 19; //Insertion with multiple right-hand values
  set2.display();
  
  LinkedListSet set3;
  set3 + 3 + 4 + 7 + 17 + 41;
  set3.display();
  
  LinkedListSet set4;
  set4 + 41 + 37+ 7 + 19 + 41;
  set4.display();
  
  // Set Union
  set1 += set2;
  set1.display(); 
  
  // Set Difference
  set1 -= set3;
  set1.display(); 
  
  // Set Intersection
  set1 &= set4;
  set1.display(); 
  
  return 0;
}
