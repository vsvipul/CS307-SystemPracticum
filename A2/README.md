# Lab Assignment 2 
### by Vipul B17069 and Swapnil B17104

## Problem 1
- Compile both approaches and the script using ```make```. This will generate 2 executable for approaches - ```main``` and ```main2```, and also the script executable ```script```.
- Run both the approaches using```timeout 30m ./main > filename.txt``` .
- Run the script on previously generated file using ```./script filename.txt``` to get the results.
- We have used 2 approaches to prevent deadlock and starvation. You can read more about those in the ```Report.pdf``` file.

## Problem 2

- Run `make all` to generate both sequential and parallel programs.
- Use `./parallel value_of_n` and `./sequential value_of_n` to execute.
- For example, `./parallel 5` for 5x5 matrix.


## Problem 3

### Kernel modules

- Built modules are given, but to re-compile, command ```make -C /lib/modules/\`uname -r\`/build M=$PWD``` can be used when inside the directory of the module source (`NULLdereference` directory or `panic` directory). But Linux kernel 5.9.1 headers must be installed on the system for compilation.
