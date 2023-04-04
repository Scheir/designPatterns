#include <memory>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

class command{
public:
   virtual ~command() = default;
   virtual int execute(int i) const = 0;
   virtual int undo(int i) const = 0;
};

class add : public command{
public:
   add(int n) : num(n) {}
   int execute(int i) const override{
      cout << "calling add" << endl;
      return i+num;
   }
   int undo(int i) const override{
      cout << "calling add undo" << endl;
      return i-num;
   }

private:
   int num;
};

class sub : public command{
public:
   sub(int n) : num(n) {}
   int execute(int i) const override{
      cout << "calling sub" << endl;
      return i-num;
   }
   int undo(int i) const override{
      cout << "calling sub undo" << endl;
      return i+num;
   }

private:
   int num;
};


class calculator{
private:
   int sum;
   stack<unique_ptr<command>> commandStack;
public:
      void compute(unique_ptr<command> c){
         sum = c->execute(sum);
         commandStack.push(move(c));
      }
      void undoLast(){
         if(commandStack.empty()){
            return;
         }
         auto command = move(commandStack.top());
         commandStack.pop();
         sum = command->undo(sum);
      }
      int getSum(){return sum;}
};

int main(){
   calculator calc{};
   calc.compute(make_unique<add>(2));
   calc.compute(make_unique<sub>(1));
   calc.undoLast();
   cout << "calculator sum is: " << calc.getSum() << endl;
}
