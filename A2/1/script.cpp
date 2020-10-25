#include <bits/stdc++.h>
#define pb push_back

using namespace std;

void updateArr(string line, int arr[5][3]) {
    vector<string> res;
    istringstream ss(line);
    int i=0;
    string first, second;
    ss>>first>>second;
    if (second == "thinking"){
        arr[first[1]-'0'][0]++;
    } else if (second == "eating"){
        arr[first[1]-'0'][1]++;
    } else if (second == "1forkacquired"){
        arr[first[1]-'0'][2]++;
    }
}

int main(int argc, char* argv[]) {
    if (argc<2){
        printf("Enter name of input file as argument.\n");
        exit(1);
    }
    ifstream inFile;
    inFile.open(argv[1]);
    string str;
    // 1 column - thinking
    // 2 column - eating
    // 3 column - 1 fork acquired
    // 5 rows represent
    int arr[5][3]={0};
    while (getline(inFile, str)) {
        updateArr(str, arr);
    }
    cout<<"\tThinking\tEating\t\t1ForkAcquired\n";
    for (int i=0;i<5;i++){
        cout<<"P"<<i<<"\t";
        for (int j=0;j<3;j++){
            cout<<arr[i][j]<<"\t\t"; 
        }
        cout<<"\n";
    }
    return 0;
}