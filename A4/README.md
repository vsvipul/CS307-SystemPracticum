# Lab Assignment 3
### by Vipul B17069 and Swapnil B17104

## Problem 1
- Compile using ```make```. This will generate 3 executables - ```script```, ```server``` and ```client```.
- If you just want to test manually on 2 VMs run ```./server``` on your server VM and run ```./client YOUR_SERVER_IP``` on your client VM.
- Both can run simultaneously on both the VMs. Just take care of the server IP you put as the command line argument.
- To run automated script tests on client, run ```./script YOUR_SERVER_IP``` on your client VM. This script will perform 3 tasks-
    - Generate random input strings in ```input/``` directory.
    - Generate corresponding outputs in ```expected_output/``` directory.
    - Run the test case using client program by sending requests to server and generate the output in ```output``` directory.
    - Compare the test cases in ```output/``` and ```expected_output/``` directory to see if the cases pass or fail.


## Problem 2

## Problem 3
