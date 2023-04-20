#include <iostream>
#include <string>
#include <set>
#include <functional>
using namespace std;

template<typename subject, typename tag>
class Observer{
public:
   function<void(tag)> lambda;
   Observer(function<void(tag)> f) : lambda(move(f)) {}
   void update(tag property){
      lambda(property);
   }
};

class Person{
public:
   enum state{
      nameop,
      adressop
   };
   using observer = Observer<Person, state>;
   string name;
   string adress;
   set<observer*> obs;
   Person(string n, string a) : name(n), adress(a) {}
   void attach(observer* o){
      obs.insert(o);
   }
   void detach(observer* o){
      obs.erase(o);
   }
   void notify(state s){
      cout << "Notifying!" << endl;
      for(auto* ptr : obs){
         ptr->update(s);
      }
   }
   void nameChange(string s){
      name = s;
      notify(state::nameop);
   }
   void adressChange(string s){
      adress = s;
      notify(state::adressop);
   }

};

int main(){
   Person p("Some name", "weird_adress");
   Observer<Person,Person::state> obs([](Person::state s){
         if(s == Person::nameop)
            cout << "Name changed!" << endl;}
            );
   p.attach(&obs);
   p.nameChange("My new name");
   p.adressChange("My new adress");

}
