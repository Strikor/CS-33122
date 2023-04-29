# Banker's Algorithm Project

This C++ project implements the Banker's Algorithm, which is used to avoid deadlocks and ensure safe resource allocation in operating systems.

## Requirements

- A C++ compiler, such as g++, is required to compile and run the program.

## Usage

1. Create a text file called `processes.txt` with the following format:

P R
Avail_1 Avail_2 ... Avail_R
Max_1_1 Max_1_2 ... Max_1_R
...
Max_P_1 Max_P_2 ... Max_P_R
Allot_1_1 Allot_1_2 ... Allot_1_R
...
Allot_P_1 Allot_P_2 ... Allot_P_R

Where:

- P: Number of processes
- R: Number of resource types
- Avail_i: Number of available resources of type i
- Max_i_j: Maximum demand of resource type j for process i
- Allot_i_j: Number of resource type j already allocated to process i

2. Compile the C++ code using a C++ compiler:

g++ -o bankers_algorithm main.cpp

3. Run the compiled program:

./bankers_algorithm

4. The program will read the input data from the `processes.txt` file, apply the Banker's Algorithm, and print the result. If the system is in a safe state, the safe sequence will be displayed. Otherwise, the program will indicate that the system is not in a safe state.

## Example

For a `processes.txt` file containing:

5 3
3 3 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

The output should be:

System is in safe state.
Safe sequence is: 1 3 4 0 2