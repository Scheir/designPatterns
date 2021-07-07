#include <iostream>
#include <string>

using namespace std;

class Singleton{
private:
    // Only used for demoing
    string id;

protected:
    Singleton(string id_) : id(id_){}
    // Static, only one of these will ever exist
    static Singleton* instance;

public:
    // No cpy constructor or cpy assignment
    Singleton(Singleton& s) = delete;
    Singleton& operator=(const Singleton& s) = delete;

    // The method used to grab the instance if it exists, otherwise create
    // static Singleton* getInstance(); <- This is how it should look like
    // Statics are defined outside of class declaration now when we dont use
    // header files.
    static Singleton* getInstance(const string id);
    
    string getId(){
        return id;
    }
};

Singleton* Singleton::instance = nullptr;

Singleton* Singleton::getInstance(const string id){
    if(!instance){
        cout << "Creating new instance " << endl;
        instance = new Singleton(id);
    }
    else
        cout << "Instance allready exists " << endl;
    return instance;
}

int main(){
    Singleton* s = Singleton::getInstance("SINGLETON");
    Singleton* s2 = Singleton::getInstance("SINGLETON CPY");

    cout << "s->id() = " << s->getId() << endl;
    cout << "s2->id() = " << s2->getId() << endl;

    cout << "adress of s = " << s << endl;
    cout << "adress of s2 = " << s2 << endl;

    return 0;
}

