#include <string>
#include <list>
#include <iostream>
using namespace std;
#pragma once

class ILoggable
{
    private:

    public:
        //Default constructor
        // ILoggable();

        //Destructor
        // ~ILoggable();

        virtual string stringToLog() = 0;//pure virtual function
};

class Observer
{
    private:

    public:
        //Default constructor
        Observer();

        //Destructor
        ~Observer();

        virtual void Update(ILoggable *ilog) = 0;//pure virtual function
};

class Subject
{
    // protected:
    //     list<Observer*> *observers;

    public:
        list<Observer*> *observers;
        //Default constructor
        Subject();
        
        //Copy constructor
        Subject(const Subject& s);

        //Destructor
        ~Subject();

        //CHECK IF NECESSARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Subject& operator=(const Subject& s);

        virtual void Attach(Observer *o);
        virtual void Detach(Observer *o);
        virtual void Notify(ILoggable *ilog);

        friend ostream& operator<<(ostream&, const Subject&);

};


class LogObserver: public Observer
{
    private:
        Subject *subject;

    public:
        //Default constructor
        LogObserver();

        //Parameterirzed constructor
        LogObserver(Subject *s);

        //Copy constructor
        LogObserver(const LogObserver& lob);

        //Destructor
        ~LogObserver();

        void Update(ILoggable* ilog);

        friend ostream& operator<<(ostream&, const LogObserver&);
};