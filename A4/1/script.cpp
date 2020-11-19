#include <bits/stdc++.h>

using namespace std;

string generateRandomString(){
    string alph="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string res="";
    for (int i=0;i<1000;i++){
        res += alph[rand()%alph.size()];
    }
    res+="\n";
    return res;
}

void toggleCase(string &str)
{
    int i = 0;
    while(i<str.size())
    {
        if (str[i]>='a' && str[i]<='z') {
            str[i] = str[i] - ('a' - 'A');
        }
        else if(str[i]>='A' && str[i]<='Z') {
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}

void generateFile(string filename) {
    FILE* f = fopen(("./input/" + filename).c_str(), "w");
    FILE* fo = fopen(("./expected_output/" + filename).c_str(), "w");
    for (int i=0;i<100;i++){
        string str = generateRandomString();
        fprintf(f, str.c_str());
        toggleCase(str);
        fprintf(fo, str.c_str());
    }
    fprintf(f, "exit\n");
    fprintf(fo, "EXIT\n");
    fclose(f);
    fclose(fo);
}

string convertToString(char* a) { 
    int i; 
    string s = ""; 
    for (i = 0; a[i]!='\0'; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

void generateOutputFiles(string filename, char* str) {
    string ip = convertToString(str);
    system(("./client " + ip + " " + "./input/" + filename + " " + "./output/" + filename).c_str());
}

void testCorrectOutput(string filename) {
    string cmd = "diff ./expected_output/" + filename + " ./output/" + filename;
    int result = system(cmd.c_str());
    if (result!=0){
        cout<<"Test case "+filename+" failed.\n";
    } else {
        cout<<"Test case "+filename+" passed.\n";
    }
}

int main(int argc, char* argv[]){
    if (argc<2){
        printf("Give IP Address of server as argument.\n");
        exit(1);
    }
    srand(time(NULL)); 
    for (int i=1;i<=10;i++){
        generateFile(to_string(i));
    }
    for (int i=1;i<=10;i++){
        generateOutputFiles(to_string(i), argv[1]);
    }
    for (int i=1;i<=10;i++){
        testCorrectOutput(to_string(i));
    }
    return 0;
}