// Dining Philosophers Problem
// Vipul B17069
// Swapnil B17104

/*
Problem Statement - 
5 Philosophers sit around a table and eat maggi using pair of forks. Each philosopher has a
left fork and a right fork (A total of 5 forks on the table). Job of philosophers is to eat and
think repeatedly but one can eat only when both of his left and right forks are available. A
philosopher can’t eat for more than 1 sec at a time and then he must release both of his forks to
the table and think for some random time and then again try to eat.
Use threads with locks to simulate the philosophers’ eat think lifecycle. Print state of each
philosopher (thinking/eating/forks acquired etc.) after each change. Does your solution allow for fair and even eating by each philosopher? (Keywords : dining philosophers problem,
deadlock, starvation)
*/


// In circular fashion order is 
// P0 F1 P1 F2 P2 F3 P3 F4 P4 F0 

#include <bits/stdc++.h>

using namespace std;

const int n = 5;

thread philo[n];
mutex philo_forks[n];

void philo_func(int i) {
    while (1){
        if (i%2){
            philo_forks[i].lock();
            printf("P%d picked up left fork: F%d\n", i, i);
            philo_forks[(i+1)%n].lock();
            printf("P%d picked up right fork: F%d \n", i, (i+1)%n);
        } else {
            philo_forks[(i+1)%n].lock();
            printf("P%d picked up right fork: F%d \n", i, (i+1)%n);
            philo_forks[i].lock();
            printf("P%d picked up left fork: F%d\n", i, i);
        }  
        printf("P%d started eating.\n", i);
        this_thread::sleep_for(chrono::seconds(1));
        printf("P%d stopped eating.\n", i);
        philo_forks[i].unlock();
        printf("P%d dropped left fork: F%d\n", i, i);
        philo_forks[(i+1)%n].unlock();
        printf("P%d dropped right fork: F%d \n", i, (i+1)%n);
        
        // Think for random time between 1s and 5s.
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 10);
        int rand_sleep = dis(gen);
        printf("P%d thinking for %ds.\n", i, rand_sleep);
        this_thread::sleep_for(chrono::seconds(rand_sleep));
    }
    
}

int main() {
    int i = 0;
    while (i<n){
        philo[i] = thread(philo_func, i);
        i++;
    }
    i = 0;
    while (i<5){
        philo[i].join();
        i++;
    }
    return 0;
}