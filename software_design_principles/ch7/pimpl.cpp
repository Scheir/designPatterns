#include <memory>
#include <iostream>
#include <string>

using namespace std;

class person{
public:
   person(string n, int a, string mn, string sn) : name(move(n)),
                                                   age(a),
                                                   pimpl(make_unique<impl>(sn,mn)) {}
private:
   string name;
   int age;

   struct impl;
   unique_ptr<impl> pimpl;
};

struct person::impl{
   impl(string mn, string sn) : middleName(mn), secondName(sn) {}
   string middleName;
   string secondName;
};

int main(){
   person p("Firstname", 10, "middleName", "secondName");
   return 0;
}
