#include <bits/stdc++.h>
using namespace std;

vector < vector <int> > matrix1, matrix2, matrix3;

void multiply(int starti, int endi)
{
    int n=matrix1.size();
    for (int i=starti; i<endi; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            for (int k=0; k<n; ++k)
            {
                matrix3[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }
}

int main(int argc, char ** argv)
{
    if (argc!=2)
    {
        printf("Execution Format: %s <value of n>\n", argv[0]);
        return 0;
    }
    int n=atoi(argv[1]);
    matrix1.assign(n, vector<int>(n));
    matrix2.assign(n, vector<int>(n));
    matrix3.assign(n, vector<int>(n));
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dist(-10, 10);
    for (int i=0;i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            matrix1[i][j]=dist(generator);
            matrix2[i][j]=dist(generator);
        }
    }
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    auto thread1 = thread(multiply, 0, n/4);
    auto thread2 = thread(multiply, n/4, n/2);
    auto thread3 = thread(multiply, n/2, 3*n/4);
    auto thread4 = thread(multiply, 3*n/4, n);
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << fixed << setprecision(8) << elapsed << " seconds\n";
}