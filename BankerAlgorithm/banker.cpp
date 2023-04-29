#include <iostream>
#include <fstream>
#include <vector>

const std::string INPUT_FILE = "processes.txt";

int P, R;

void readInputFile(std::string filename, int &P, int &R, std::vector<int> &avail, std::vector<std::vector<int>> &maxm, std::vector<std::vector<int>> &allo) {
    std::ifstream input_file(filename);

    if (input_file.is_open()) {
        input_file >> P >> R;

        avail.resize(R);
        for (int i = 0; i < R; ++i) {
            input_file >> avail[i];
        }

        maxm.resize(P, std::vector<int>(R));
        for (int i = 0; i < P; ++i) {
            for (int j = 0; j < R; ++j) {
                input_file >> maxm[i][j];
            }
        }

        allo.resize(P, std::vector<int>(R));
        for (int i = 0; i < P; ++i) {
            for (int j = 0; j < R; ++j) {
                input_file >> allo[i][j];
            }
        }

        input_file.close();
    } else {
        std::cerr << "Unable to open input file." << std::endl;
        exit(1);
    }
}

//find the need of each process
void calcNeed(std::vector<std::vector<int>> &need, const std::vector<std::vector<int>> &maxm, const std::vector<std::vector<int>> &allo)
{
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
 
            // Need of instance = maxm instance - allocated instance   
            need[i][j] = maxm[i][j] - allo[i][j];
}

//Find if the system is in safe state or not
bool isSafe(const std::vector<int> &processes, const std::vector<int> &avail, const std::vector<std::vector<int>> &maxm, const std::vector<std::vector<int>> &allo) {
    std::vector<std::vector<int>> need;
    need.resize(P, std::vector<int>(R));
 
    //calc need matrix
    calcNeed(need, maxm, allo);
 
    std::vector<bool> finish(P, 0);
 
    std::vector<int> safeSeq(P);
 
    std::vector<int>  work(R);
    for (int i = 0; i < R ; i++) {
        work[i] = avail[i];
    }

    // While all processes are not finished or system is not in safe state.
    int count = 0;
    while (count < P)
    {
        // Find a process which is not finish and whose needs can be satisfied with current work[] resources.
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            // First check if a process is finished, if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of current P need is less than work
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
 
                // If all needs of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of current P to the available/work resources i.e.free the resources
                    for (int k = 0 ; k < R ; k++)
                        work[k] += allo[p][k];
 
                    // Add this process to safe sequence.
                    safeSeq[count++] = p;
 
                    // Mark this p as finished
                    finish[p] = 1;
 
                    found = true;
                }
            }
        }
 
        // If we could not find a next process in safe sequence.
        if (found == false)
        {
            std::cout << "System is not in safe state";
            return false;
        }
    }
 
    // If system is in safe state then safe sequence will be as below
    std::cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < P ; i++)
        std::cout << safeSeq[i] << " ";
 
    return true;
}

int main() {
    std::vector<int> processes, avail;
    std::vector<std::vector<int>> maxm, allo;

    readInputFile(INPUT_FILE, P, R, avail, maxm, allo);

    processes.resize(P);
    for (int i = 0; i < P; ++i) {
        processes[i] = i;
    }

    // Check system is in safe state or not
    isSafe(processes, avail, maxm, allo);

    return 0;
}