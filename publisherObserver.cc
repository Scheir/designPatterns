#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;


class Subscriber{
public:
    virtual ~Subscriber(){};
    virtual void update(const string newMessage) = 0;
    virtual int getNo() = 0;
};


class Publisher{
public:
    virtual ~Publisher(){};
    virtual void subscribe(Subscriber* sub) = 0;
    virtual void unsubscribe(Subscriber* sub) = 0;
    virtual void notify() = 0;
    virtual void createMessage(string str) = 0;
};

class PublisherImpl : public Publisher{
public:
    virtual ~PublisherImpl(){}
    void subscribe(Subscriber* sub){
        subscriberVec.push_back(sub);
    }

    void unsubscribe(Subscriber* sub){
        auto it = find_if(subscriberVec.begin(), subscriberVec.end(), [&](Subscriber* s){
            return sub->getNo() == s->getNo();
        });
        subscriberVec.erase(it);
    }

    void notify(){
        for(auto it = subscriberVec.begin(); it != subscriberVec.end(); it++){
           (*it)->update(message);
        }
    }

    void createMessage(string newMessage){
        message = newMessage;
    }

private:
    string message;
    vector<Subscriber*> subscriberVec;
};

class SubscriberImpl : public Subscriber{
public:
    SubscriberImpl(PublisherImpl& pub_) : pub(pub_){
        pub.subscribe(this);
        subNo = subCount;
        cout << "Subscriber with no " << subNo << " subscribed! " << endl; 
        subCount++;
    }

    virtual ~SubscriberImpl(){}

    void update(const string newMessage){
        message = newMessage;
        printInfo();
    }

    void unsubscribe(){
        pub.unsubscribe(this);
        cout << "Subscriber with no: " << subNo << " Unsusubscribed" << endl;
    }
    
    void printInfo(){
        cout << "Subscriber no: " << subNo << " Notifed! Message: " << message << endl;
    }

    int getNo(){
        return subNo;
    }


private:
    string message;
    PublisherImpl& pub;
    static int subCount;
    int subNo;
};

int SubscriberImpl::subCount = 1;


class Customer{
public:
    Customer(string n) : name(n){}
    
   ~Customer(){}

    void subscribeToStock(PublisherImpl* pub){
        sub = shared_ptr<Subscriber>(new SubscriberImpl(*pub));
    }

    bool operator==(string n){
        return name == n;
    }

private:
    shared_ptr<Subscriber> sub;
    string name;    
};

class WareHouse : public PublisherImpl{
public:
    WareHouse() : stock(0) {}
    void customerOrder(){
        stock--;
        string message = "";
        if(stock != 0){
            message = "Left in stock: " + to_string(getStock());
        }
        else{
            message = "Stock is empty!";
        }
        createMessage(message);
        notify();
    }
    void fillStock(int amount){
        stock += amount;
        string message = "Filling stock"; 
        createMessage(message);
        notify();
    }
    void printStock(){
        cout << "Current stock: " << stock << endl;
    }

    int getStock(){
        return stock;
    }

    void newCustomer(string name){
        Customer cust(name);
        cust.subscribeToStock(this);
        customerVec.push_back(cust);
    }

    Customer& getCustomer(string name){
        auto it = find(customerVec.begin(), customerVec.end(), name);
        if(it == customerVec.end())
            cout << "FAILED" << endl;
        return *it;
    }

private:
    int stock;
    vector<Customer> customerVec;
};


int main(){
    WareHouse wh;
    wh.newCustomer("Ragnar");
    wh.newCustomer("Lennart");
    // FIll stock and notify customers that there is items available
    wh.fillStock(2);
    // One order is placed, notify customers only one item left
    wh.customerOrder();
    // One order is placed, no items left, notify customers.
    wh.customerOrder();
}
