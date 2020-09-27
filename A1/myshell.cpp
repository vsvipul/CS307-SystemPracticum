#include <bits/stdc++.h>
#define pb push_back
using namespace std;

vector<string> allCommands{"cd", "clr", "dir", "environ", "echo", "pause", "help", "quit", "history"};

void printPrompt(){
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

vector<string> getArgs(string cmdline){
    vector<string> res;
    istringstream ss(cmdline);
    int i=0;
    do {
        string word;
        ss>>word;
        if (i) {
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

void executeBuiltIn(string cmd, vector<string> args){
    cout<<cmd<<" ";
    for (int i=0;i<args.size();i++){
        cout<<args[i]<<"\n";
    }
}

int main(int argc, char* argv[]) {
    while (1){
        int childpid;
        string cmd, cmdline;
        printPrompt();
        cmdline = readLine();
        cmd = parseCommand(cmdline);
        vector<string> args = getArgs(cmdline);
        if (isBuiltIn(cmd)){
            executeBuiltIn(cmd, args);
        } else {
            cout<<"Command does not exist.\n";
        }
    }
    return 0;
}