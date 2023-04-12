#include <iostream>
#include <utility>
using namespace std;

template<typename T, typename Tag, template<typename> class... Skills>
struct StrongType : private Skills<StrongType<T,Tag,Skills...>>...{
public:
   using value_type = T;
   explicit StrongType(const T& v) : value(v){}
   T& get() {return value;}
   const T& get() const {return value;}
private:
   T value;
};

template<typename Derived>
struct Addable{
   friend Derived operator+(Derived& lhs, const Derived& rhs){
      return Derived{lhs.get() + rhs.get()};
   }
};

template<typename Derived>
struct Printable{
   friend ostream& operator<<(ostream& os, const Derived& d){
      os << d.get();
      return os;
   }
};

template<typename T>
using Meter = StrongType<T, struct MeterTag, Addable, Printable>;

template<typename T>
using KM = StrongType<T, struct KMTag, Addable>;

int main(){
   auto m1 = Meter<long>{100};
   auto m2 = Meter<long>{50};

   auto km1 = KM<int>{10};
   auto km2 = KM<int>{20};

   auto const m3 = m1+m2;
   auto const km3 = km1+km2;
   cout << m3 << endl;
}
