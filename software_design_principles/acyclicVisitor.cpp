#include <iostream>
using namespace std;

// Visitor base(abstract) classes
template<typename T>
class visitor{
public:
   ~visitor() = default;
   virtual void visit(const T&) const = 0;
};

class abstractVisitor{
public:
   virtual ~abstractVisitor(){};
};

// Shapes implementations
class shape{
public:
   virtual void accept(const abstractVisitor& visitor) const = 0;
   virtual ~shape(){}
};

class circle : public shape{
public:
   int radius;
   circle(const int r) : radius(r) {}
   void accept(const abstractVisitor& v) const{
      if(const auto* visitPtr = dynamic_cast<visitor<circle> const*>(&v)){
         visitPtr->visit(*this);
      }
      else{
         // We end up here if there are no implementation of the current visitor
         cout << "No implementation of this visitor for circle!" << endl;
      }
   }
   ~circle(){}
};

class square : public shape{
public:
   double side;
   square(const double s) : side(s) {}
   void accept(const abstractVisitor& v) const{
      if(const auto* visitPtr = dynamic_cast<visitor<square>const *>(&v)){
         visitPtr->visit(*this);
      }
      else{
         // We end up here if there is no implementation of the current visitor
         cout << "No implementations of this visitor for square" << endl;
      }
   }
   ~square(){}
};


// Play and draw implementations
// There are implemenations of draw for both shapes
// For play there is only a circle implementation
class draw : public abstractVisitor,
             public visitor<circle>,
             public visitor<square>{
public:
   void visit(const circle& c) const{
      cout << "Visiting circle, radius: " << c.radius << endl;
   }
   void visit(const square& s) const{
      cout << "Visiting square, side: " << s.side << endl;
   }
   ~draw() = default;
};

class play : public abstractVisitor,
             public visitor<circle>{
public:
   void visit(const circle& c) const{
      cout << "Playing with circle!" << endl;
   }
   ~play() = default;
};

int main(){
   square sq(1.1);
   circle c(2);
   draw drawVisitor;
   play playVisitor; // Only derives from circle, so no implementation for square

   c.accept(drawVisitor);
   c.accept(playVisitor);
   sq.accept(drawVisitor);
   // No implementation for this one, so visit will never be called
   sq.accept(playVisitor);
   return 0;
};
