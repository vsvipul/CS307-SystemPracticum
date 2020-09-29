#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define pb push_back
using namespace std;

vector<string> allCommands{"cd", "clr", "dir", "environ", "echo", "pause", "help", "quit", "history", ""};
vector<string> history;


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
	if (args.size() != 1) {
		cout << "cd requires exactly one argument - the directory\n";
		return;
	}
	if (chdir(args[0].c_str()) != 0) {
        cout<<"Error: Specified directory does not exists.\n";
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

// 3 dir
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
	if (directory != NULL)
	{
		while ((curFile = readdir(directory)) !=NULL)
		{
			cout << std::string(curFile->d_name) << "\n";
		}
		closedir(directory);
	}
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
void printHistory()
{
	for (int i=0; i<history.size(); ++i)
	{
		cout << i+1 << " " << history[i] << "\n";
	}
}

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
    } else if (cmd == "history") {
	    printHistory();
    } else {
        cout<<"Command "<<cmd<<": Definition not found.\n";
    }
}

int main(int argc, char* argv[]) {

	if (argc==2)
	{
		if (freopen(argv[1], "r", stdin)==NULL)
		{
			cout << "Error reading file\n";
			return 0;
		}
	}

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
