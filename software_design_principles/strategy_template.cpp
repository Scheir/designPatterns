#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class circle;
class square;

template <typename T>
class DrawStrategy{
public:
   virtual ~DrawStrategy() = default;
   virtual void draw(const T&) const = 0;
};

class shape {
public:
   virtual ~shape() = default;
   virtual void draw() const = 0;
};

class circle : public shape{
private:
   int radius;
   unique_ptr<DrawStrategy<circle>> drawer;
public:
   circle(int r, unique_ptr<DrawStrategy<circle>> ds)
      : radius(r), drawer(move(ds)) {}
   ~circle() = default;
   void draw() const override{
      drawer->draw(*this);
   }
};

class square: public shape{
private:
   int side;
   unique_ptr<DrawStrategy<square>> drawer;
public:
   square(int s, unique_ptr<DrawStrategy<square>> ds)
      : side(s), drawer(move(ds)) {}
   ~square() = default;
   void draw() const override{
      drawer->draw(*this);
   }
};

class CircleStrategy : public DrawStrategy<circle>{
public:
   ~CircleStrategy() = default;
   void draw(const circle& c) const {
      cout << "Calling circle draw from circles strategy " << endl;
   }
};

class SquareStrategy : public DrawStrategy<square>{
public:
   ~SquareStrategy() = default;
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
