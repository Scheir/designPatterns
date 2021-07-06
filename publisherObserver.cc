#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

// Can also be named Observer, listener
class Subscriber{
public:
    virtual ~Subscriber(){};
    virtual void update(const string newMessage) = 0;
    virtual int getNo() = 0;
};

// Can also be named subject, event manager
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
    
    // use the static number which is delt to the subscriber to search for the element
    // in the vectore and remove from vector.
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
    
    // In its simplest form this is just a string message, can literally be anything
    void createMessage(string newMessage){
        message = newMessage;
    }

private:
    // This can be anything
    string message;
    // The vector that holds all subscribers to the instance of publisher
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
    
    // Not really used, good for debugging
    void printInfo(){
        cout << "Subscriber no: " << subNo << " Notifed! Message: " << message << endl;
    }
    
    int getNo(){
        return subNo;
    }


private:
    string message;
    // Reference to Publisher so all instances of Subscriber refers to the same publisher
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
        // Use the ptr/reference to the publisher instead of a copy
        // So all are subscribed to the same object (this) below
        sub = shared_ptr<Subscriber>(new SubscriberImpl(*pub));
    }

    bool operator==(string n){
        return name == n;
    }

private:
    // Can perhaps be a unique_ptr
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
        // this will notify all subscribers which are subscibed to (this) where parts of
        // this is a publisher
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
        // Here we subscribe to the publisher using the publisher part of this
        cust.subscribeToStock(this);
        customerVec.push_back(cust);
    }
    
    // Not really used at the moment
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
