#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class circle;
class square;

class DrawCircleStrategy{
public:
   virtual ~DrawCircleStrategy() = default;
   virtual void draw(const circle& c) const = 0;
};

class DrawSquareStrategy{
public:
   virtual ~DrawSquareStrategy() = default;
   virtual void draw(const square& s) const = 0;
};

class shape {
public:
   virtual ~shape() = default;
   virtual void draw() const = 0;
};

class circle : public shape{
private:
   int radius;
   unique_ptr<DrawCircleStrategy> drawer;
public:
   circle(int r, unique_ptr<DrawCircleStrategy> ds)
      : radius(r), drawer(move(ds)) {}
   ~circle() = default;
   void draw() const override{
      drawer->draw(*this);
   }
};

class square: public shape{
private:
   int side;
   unique_ptr<DrawSquareStrategy> drawer;
public:
   square(int s, unique_ptr<DrawSquareStrategy> ds)
      : side(s), drawer(move(ds)) {}
   ~square() = default;
   void draw() const override{
      drawer->draw(*this);
   }
};

class CircleStrategy : public DrawCircleStrategy{
public:
   void draw(const circle& c) const {
      cout << "Calling circle draw from circles strategy " << endl;
   }
};

class SquareStrategy : public DrawSquareStrategy{
public:
   void draw(const square& s) const {
      cout << "Calling square draw from square strategy " << endl;
   }
};

int main(){
   vector<unique_ptr<shape>> vs;
   vs.emplace_back(make_unique<circle>(1, make_unique<CircleStrategy>()));
   vs.emplace_back(make_unique<square>(1, make_unique<SquareStrategy>()));

   for(auto& x : vs){
      x->draw();
   }

}
