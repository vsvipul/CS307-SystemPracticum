#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define pb push_back
using namespace std;

vector<string> allCommands{"cd", "clr", "dir", "environ", "echo", "pause", "help", "quit", "history", ""};

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

// 1 cd

void changeDir(vector <string> args)
{
	if (args.size()!=1)
	{
		cout << "Invalid arguments to cd\n";
		return;
	}
	chdir(args[0].c_str());
}

// 2 clr
void clearExec(){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    system("cls");
    #else
    system("clear");
    #endif
}

// 3 dir

void listDirContents(vector <string> args)
{
	if (args.size()!=1)
	{
		cout << "Invalid arguments to dir\n";
		return;
	}
	DIR * directory = opendir(args[0].c_str());
	struct dirent * curFile;
	if (directory!=NULL)
	{
		while ((curFile = readdir(directory)) !=NULL)
		{
			cout << std::string(curFile->d_name) << "\n";
		}
	}
	closedir(directory);
}


// 4 environ

void printEnvironVars()
{
	char path[4096];
	if (getcwd(path, 4096)) {
		cout << "PWD = " << std::string(path) << "\n";
	} else {
		cout << "Error fetching directory\n";
	}
	// More to be added.
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
// 8 quit
void quitExec() {
    exit(1);
}

// 9 history

void executeBuiltIn(string cmd, vector<string> args) {
    if (cmd == "") {
        // Do nothing if just enter is pressed without any input.   
    } else if (cmd == "cd") {
		changeDir(args);
    } else if (cmd == "dir") {
		listDirContents(args);
    } else if (cmd == "echo") {
        echoExec(args);
    } else if (cmd == "quit") {
        quitExec();
    } else if (cmd == "clr") {
        clearExec();
    } else if (cmd == "pause") {
        pauseExec();
    } else if (cmd == "environ") {
		printEnvironVars();
    } else {
        cout<<"Command "<<cmd<<": Definition not found.\n";
    }
}

int main(int argc, char* argv[]) {
    while (1){
        string cmd, cmdline;
        printPrompt();
        cmdline = readLine();
        cmd = parseCommand(cmdline);
        vector<string> args = getArgs(cmdline);
        if (isBuiltIn(cmd)){
            executeBuiltIn(cmd, args);
        } else {
            cout<<"Command "<<cmd<<": does not exist.\n";
        }
    }
    return 0;
}
