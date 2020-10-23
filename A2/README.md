System Practicum Lab Assignment 2 
Vipul Sharma B17069
Swapnil Rustagi B17104

Prob 1

- Compile using ```g++ -pthread main.cpp``` and run using ```./a.out``` .
- Our solution does not suffer from deadlock because odd philosophers pickup left fork first and even philosophers pickup right fork first.
- This also ensures that each philoshopher gets a fair chance to eat.