#include <iostream>
#include <memory>

using namespace std;

class animal{
public:
   virtual ~animal() = default;
   virtual unique_ptr<animal> clone() = 0;
   virtual void scream() = 0;
};


class dog : public animal{
public:
   ~dog() = default;
   void scream(){
      cout << "bark" << endl;
   }
   unique_ptr<animal> clone(){
      return make_unique<dog>(*this);
   }
};

class cat: public animal{
public:
   ~cat() = default;
   void scream(){
      cout << "mjaooo" << endl;
   }
   unique_ptr<animal> clone(){
      return make_unique<cat>(*this);
   }
};


int main(){
   unique_ptr<animal> mrD = make_unique<dog>();
   unique_ptr<animal> mrC = make_unique<cat>();

   auto dogCopy = mrD->clone();
   auto catCopy = mrC->clone();

   dogCopy->scream();
   catCopy->scream();

   cout << "Adress of mrD: " << mrD.get() << ", adress of copy: " << dogCopy << endl;

}
