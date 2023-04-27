#include <iostream>
#include <string>
#include <memory>

using namespace std;

class engine{
public:
   virtual ~engine() = default;
   virtual void start() = 0;
   virtual void stop() = 0;
   virtual int getSpeed() = 0;
};


class electricEngine : public engine{
public:
   electricEngine(int s) : maxSpeed(s) {}
   void start() override{
      cout << "start engine" << endl;
   }
   void stop() override{
      cout << "engine stop" << endl;
   }
   int getSpeed() override{
      return maxSpeed;
   }

private:
   int maxSpeed;
};

class car{
protected:
   explicit car(unique_ptr<engine> e) : pimpl (move(e)) {}
   engine* getEngine(){
      return pimpl.get();
   }

public:
   virtual ~car() = default;
   virtual void drive() = 0;
   virtual void stop() = 0;

private:
   unique_ptr<engine> pimpl;
};

class electricCar : public car{
public:
   electricCar(int maxSpeed) : car(make_unique<electricEngine>(maxSpeed)) {}
   void drive(){
      const auto ptr = getEngine();
      ptr->start();
      cout << "Driving at: " << ptr->getSpeed() << "km/h!" << endl;
   }
   void stop(){
      getEngine()->stop();
   }

};


int main(){
   electricCar eCar(10);
   eCar.drive();
   eCar.stop();
}
