#include"autoptr.h"

int main() {
  
    CustomUniquePtr<int> uniquePtr(new int(42));
    cout << "UniquePtr: " << *uniquePtr << endl;

   
    CustomSharedPtr<int> sharedPtr1(new int(77));
    CustomSharedPtr<int> sharedPtr2 = sharedPtr1;

    cout << "SharedPtr1: " << *sharedPtr1 << ", Use Count: " << sharedPtr1.useCount() << endl;
    cout << "SharedPtr2: " << *sharedPtr2 << ", Use Count: " << sharedPtr2.useCount() << endl;

    return 0;
}