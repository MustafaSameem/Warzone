#pragma once
#include "../GameEngine/GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"
#include <fstream>
using namespace std;

//Forward Declaration
class GameEngine;
// class ILoggable;
// class Subject;

//command Class
class Command : public Subject, public ILoggable{
    string commandPassed;
    string commandEffect;
    string toConcat;
    int commandIndex =-1;


public:

    enum class validCommands{loadmap, validatemap, addplayer, gamestart,replay, quit,gameend};

    Command();
    Command(string);
    Command(validCommands,string);
    Command(const Command& );
    Command& operator= (const Command& );
    ~Command();
    void saveEffect(Command*);
    Command(string commandpassed, string commandEffect);

    string stringToLog();//overriding pure virtual function from ILoggable

    //Getters Accesor
    string getCommandPassed();
    string getCommandEffect();
    //Setters Mutators
    void setCommandPassed();

    friend ostream& operator<<(ostream &out,const Command&);

};


class CommandProcessor : public Subject, public ILoggable{
public:

    CommandProcessor();
    CommandProcessor& operator=(const CommandProcessor&);
    CommandProcessor(const CommandProcessor&);
    ~CommandProcessor();

    void getCommand(GameEngine*, CommandProcessor*);
    bool validate(Command*,GameEngine*);

    bool getExitProgramstatus();
    void setcmdPause(bool);
    bool getcmdPausestatus();
    int commandStrTocommandIndex(string);

    string stringToLog();//overriding pure virtual function from ILoggable

    vector<Command*> getCommandsList();
    vector<Command*> getValidcommands();

    friend ostream& operator<< (ostream &out, const vector<Command*>&);


private:
    vector<Command*> commands;
    vector<Command*> validCommands;

    virtual  Command* readCommand( );
    void saveCommand(Command* );
    void saveValidCommands(Command*);
    bool exitProgram = false;
    bool cmdProPause = false;


    vector<string> validCommVec = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit","gameend"};
};

//FileLineReader class - that reads from a txt file.
class FileLineReader{
public:
    FileLineReader();
    FileLineReader(const FileLineReader&);
    FileLineReader& operator=(const FileLineReader&);
    void readFromFile(string);

    //getter
    vector<string> getContentOfFile();


    friend ostream& operator<<(ostream &out, const vector<string>);
private:
    vector<string> contentOfFile;

};

//FileCommandProcessorAdapter inherits commandProcessor.
class FileCommandProcessorAdapter : public CommandProcessor{
public:

    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(FileLineReader*);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);
    FileCommandProcessorAdapter& operator= (const FileCommandProcessorAdapter&);
    ~FileCommandProcessorAdapter();
    Command* readCommand();

    //getter
    FileLineReader* getFileLineReader();

    friend ostream& operator<< (ostream&, const vector<string>);

private:
    FileLineReader* fileReader;

    //index to keep track of currentLine.
    int indexCurrentLine{ -1 };

    // Vector of all commands read from the file
    vector<string> commands{};
};




