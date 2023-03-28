#include <vector>
#include <variant>
#include <iostream>

using namespace std;

class circle{
public:
   circle(int r) : radius(r) {}
   int radius;
};

class square{
public:
   square(double s) : side(s) {}
   double side;
};

struct drawShapes{
   variant<int, double> operator()(const circle& c){
      cout << "DRAWING CIRCLE: " << c.radius << endl;
      return c.radius;
   }
   variant<int, double> operator()(const square& s){
      cout << "DRAWING SQUARE: " << s.side << endl;
      return s.side;
   }
};

using shape = variant<circle, square>;
using shapes = vector<shape>;

int main(){
   shapes s;
   s.emplace_back(square {1.1});
   s.emplace_back(circle {2});

   for(auto& v : s){
      auto x = visit(drawShapes{}, v);
      double* d = get_if<double>(&x);
      if(d){
         cout << "Found a double return!" << endl;
      }
      else{
         cout << "Did not found a double return!" << endl;
      }
   }
}
