#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define pb push_back
using namespace std;

vector<string> allCommands{"cd", "clr", "dir", "environ", "echo", "pause", "help", "quit", "history", "", "pwd", "ls", "export"};
map<string, string> environmentVars;
vector<string> history;

extern char** environ;

void printPrompt() {
    cout<<"myshell>> ";
}

string readLine(){
    string str;
    getline(cin, str);
    return str;
}

string parseCommand(string cmdline) {
    string str;
    istringstream ss(cmdline);
    ss>>str;
    return str;
}

vector<string> getArgs(string cmdline) {
    vector<string> res;
    istringstream ss(cmdline);
    int i=0;
    do {
        string word;
        ss>>word;
        if (i && word.size()) {
            res.pb(word);
        }
        i++;
    } while(ss);
    return res;
}

bool isBuiltIn(string cmd) {
    vector<string>::iterator it = find(allCommands.begin(), allCommands.end(), cmd);
    return (it != allCommands.end());
}

void insertEnvironmentVar(string var) {
    int j=0;
    for (j=0;j<var.size();j++) {
        if (var[j] == '='){
            break;
        }
    }
    string keyvar = var.substr(0,j);
    string keyval = var.substr(j+1,var.size()-j-1);
    environmentVars[keyvar] = keyval;
}

void initializeEnvironmentVars() {
    char *s = *environ;
    int i=0;
    while (s) {
        insertEnvironmentVar(std::string(s));
        i++;
        s = *(environ+i);
    }
}

string getCurrentDir(){
    char path[4096];
    getcwd(path, 4096);
    return std::string(path);
}

// 1 cd
void changeDir(vector <string> args)
{
    if (args.size() != 1) {
        cout << "cd requires exactly one argument - the directory\n";
        return;
    }
    if (chdir(args[0].c_str()) != 0) {
        cout<<"Error: Specified directory does not exists.\n";
    } else {
        string curDir = getCurrentDir();
        setenv("PWD", curDir.c_str(), 1);
        environmentVars["PWD"] = curDir;
    }
}

// 2 clr
void clearExec(){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    system("cls");
    #else
    system("clear");
    #endif
}

// 3 dir (or ls)
void listDirContents(vector <string> args)
{
    if (args.size() > 1) {
        cout << "dir requires exactly one argument - the directory\n";
        return;
    }
    DIR* directory;
    if (args.size() == 0) {
        directory = opendir(".");
    } else {
        directory = opendir(args[0].c_str());
    }
    struct dirent * curFile;
    if (directory != NULL) {
        while ((curFile = readdir(directory)) !=NULL) {
            cout << std::string(curFile->d_name) << "\n";
        }
        closedir(directory);
    }
}

// 4 environ
void printEnvironVars()
{
    for (auto it: environmentVars) {
        cout<<(it.first)<<"="<<(it.second)<<"\n";
    }
}

// 5 echo
void echoExec(vector<string> args) {
    for (int i=0;i<args.size();i++){
        cout<<args[i]<<" ";
    }
    cout<<"\n";
}

// 6 pause
void pauseExec() {
    cout<<"Execution paused. Press enter to continue.\n";
    while (cin.get()!='\n');
}

// 7 help
void helpExec() {
    cout<<"\nmyshell\n\nNAME\n\tmyshell - Custom Made Shell from scratch\n\nDESCRIPTION\n\t";
    cout<<"Supports the commands- cd, clr, dir, ls, environ, echo, pause, help, quit, history, pwd, export.\n";
    cout<<"\tAlso, inherits the environment vars of the shell it is opened from.\n";
    cout<<"\tCan run scripts from a file using the command 'myshell batchfilename'.\n\n";
}

// 8 quit
void quitExec() {
    exit(1);
}

// 9 history
void printHistory()
{
    for (int i=0; i<history.size(); ++i) {
        cout << i+1 << " " << history[i] << "\n";
    }
}

// 10 set SHELL environment variable
void setShellEnvironmentVar(char* execName) {
    char path[4096];
    readlink("/proc/self/exe", path, 4096);
    environmentVars["SHELL"] = string(path);
}

// 11 pwd
void pwdExec(){
    string curDir = getCurrentDir();
    cout<<curDir<<"\n";
}

// 12 export
void exportExec(vector<string> args) {
    if (args.size() > 1) {
        cout << "export requires exactly one argument in the format: 'VARNAME=VALUE'\n";
        return;
    }
    insertEnvironmentVar(args[0]); 
}

void executeBuiltIn(string cmd, vector<string> args) {
    if (cmd == "") {
        // Do nothing if just enter is pressed without any input.   
    } else if (cmd == "cd") {
        changeDir(args);
    } else if (cmd == "clr") {
        clearExec();
    } else if (cmd == "dir" || cmd == "ls") {
        listDirContents(args);
    } else if (cmd == "environ") {
        printEnvironVars();
    } else if (cmd == "echo") {
        echoExec(args);
    } else if (cmd == "pause") {
        pauseExec();
    } else if (cmd == "help") {
        helpExec();
    } else if (cmd == "quit") {
        quitExec();
    } else if (cmd == "history") {
        printHistory();
    } else if (cmd == "pwd") {
        pwdExec();
    } else if (cmd == "export") {
        exportExec(args);
    } else {
        cout<<"Command "<<cmd<<": Definition not found.\n";
    }
}

int main(int argc, char* argv[]) {

    if (argc==2) {
        if (freopen(argv[1], "r", stdin)==NULL)
        {
            cout << "Error reading file\n";
            return 0;
        }
    }

    initializeEnvironmentVars();
    setShellEnvironmentVar(argv[0]);

    while (1){
        string cmd, cmdline;
        if (argc==1) printPrompt();
        cmdline = readLine();
        history.pb(cmdline);
        cmd = parseCommand(cmdline);
        vector<string> args = getArgs(cmdline);
        if (isBuiltIn(cmd)) {
            executeBuiltIn(cmd, args);
        } else {
            cout<<"Command "<<cmd<<": does not exist.\n";
        }
        if (cin.eof()) break;
    }
    return 0;
}
