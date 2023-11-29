#include "LoggingObserver.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//----------------------------------------------------------------------------------------------
//* Subject *
//----------------------------------------------------------------------------------------------

//Default constructor
Subject::Subject()
{
    observers = new list<Observer*>;
}

//Copy constructor --> DO THIS ONE ASOUSFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
Subject::Subject(const Subject& s){}

//Destructor
Subject::~Subject()
{
    delete observers;
}


void Subject::Attach(Observer *o)
{
     observers->push_back(o);
}

void Subject::Detach(Observer *o)
{
    observers->remove(o);
}

void Subject::Notify(ILoggable *ilog)
{
    std::list<Observer *>::iterator i = observers->begin();
    // std::cout << "   Notified!" << std::endl;
    if(i == observers->end())
    {
        std::cout<<"ILOG IS NULLLLLLLLLL!"<<std::endl;
    }
    // std::cout<<"update before"<<std::endl;
    // (*i)->Update(ilog);

    for (; i!= observers->end() ; i++)
    {
        // std::cout<<"updating"<<std::endl;
        (*i)->Update(ilog);
    }
}

ostream& operator<<(ostream& ostream, const Subject& subject)
{
    ostream << "\nSubject: " << std::endl;
    for(auto i: *subject.observers)
    {
        ostream << i << std::endl;
    }
    return ostream;
}

//----------------------------------------------------------------------------------------------
//* Observer *
//----------------------------------------------------------------------------------------------

 //Default constructor
Observer::Observer(){}

//Destructor
Observer::~Observer(){}

//----------------------------------------------------------------------------------------------
//* LogObserver *
//----------------------------------------------------------------------------------------------

//Default constructor
LogObserver::LogObserver(){}

LogObserver::LogObserver(Subject *s)
{
    subject = s;
    subject->Attach(this);
}


 //Copy constructor
LogObserver::LogObserver(const LogObserver& lob){}

//Destructor
LogObserver::~LogObserver()
{
    subject->Detach(this);//when destructing, detach from LogObserver
};

void LogObserver::Update(ILoggable* ilog)
{
    // std::cout<<"writing to file!"<<std::endl;
	ofstream logfile;
	logfile.open("gamelog.txt", ofstream::app); //if gamelog.txt not found, create it
	logfile << ilog->stringToLog() << endl; //output to file
	logfile.close();
}
