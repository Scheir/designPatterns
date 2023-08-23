#include <vector>
#include <iostream>

// Sphere and box have no clue about print.
// no coupling at all
struct Sphere{double radius;};

struct Box{double side;};


struct PrinterInterface{
    void virtual print()=0;
};

template<typename T, typename S>
struct PrinterModel: PrinterInterface{
    T object;
    S strategy;
    PrinterModel(T object_, S strategy_):object(object_), strategy(strategy_){}
    void print() override{
         Print(object, strategy);
    }
};

auto Print(const Box& box, auto& strategy){
    std::cout<<"box is Printed. \n";
    strategy();
}
auto Print(const Sphere& sphere, auto& strategy ){
   std::cout << "Sphere is printed. \n";
   strategy();
}

struct LinearPrinting{
   void operator()(){
      std::cout << "Linear printing" << std::endl;
   }
};

struct CircularPrintingBox{
   void operator()(){
      std::cout << "Circular printing box" << std::endl;
   }
};
struct CircularPrintingSphere{
   void operator()(){
      std::cout << "Circular printing sphere" << std::endl;
   }
};

int main(){
    Sphere s{1};
    Box b{2} ;
    auto sphereModel = PrinterModel{s,LinearPrinting{}};
    auto boxModel = PrinterModel{b, CircularPrintingBox{}};
    std::vector<PrinterInterface*> printerModels{&sphereModel, &boxModel};

    for (auto& model: printerModels)
        model->print();
    return 0;
}
