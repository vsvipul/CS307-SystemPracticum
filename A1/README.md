Link to YouTube video: https://youtu.be/y0LMGMe8lnU

The shell is written in C++. To build, simply use

g++ -o myshell myshell.cpp

and then execute 

./myshell

We use standard C++ libraries, and also 3 POSIX API headers available on Linux, "dirent.h", "sys/types.h" and "unistd.h". Some implementation details are given below.

------------------------------------------------------------------------------------------------
The shell funtionality is implemented using calls to POSIX APIs available on Linux systems.

Reading input from file: We use freopen() to redirect the stdin stream to a file. Rest of the program works unchanged. 

Environment variables: At the start of the program, We get the environment variables from Terminal in the form of array of C strings (char**) in the variable "environ". This is declared in unistd.h. We then parse and store them in initializeEnvironmentVars(). Then we replace value of "SHELL" variable with our shell path.

We also implemented an additional command "export" in our shell to add new environment variables. 

cd: Call to chdir() function in unistd.h. We also update the PWD env variable.

clr: call to system("clear") 

dir: The directory structure is obtained from functions defined in "dirent.h" and corresponding data types are in "sys/types.h". We use opendir() to get the directory structure. The contents of the directory are read, one at a time, by calling readdir() and the filenames are printed. We also added an alias "ls" for this command. 

environ: Simply print the variables stored earlier. 

The rest of the functionality does not require POSIX APIs. 

