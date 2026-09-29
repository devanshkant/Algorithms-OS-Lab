#include <iostream>
#include<fstream>
using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst;
    int rem_burst;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n;
    ifstream fin("input.txt");
    cout << "Enter number of processes: ";
    fin >> n;
    // cin >> n;

    Process p[50];
    for (int i = 0; i < n; i++) {
        // cout << "Enter ID and Burst Time for process " << (i + 1) << ": ";
        fin >> p[i].id >> p[i].burst;
        p[i].rem_burst = p[i].burst;
        p[i].arrival_time = 0;
    }

    int quantum;
    // cout << "Enter Time Quantum: ";
    fin >> quantum;

    // Parallel primitive arrays to record intervals for the Gantt Chart
    int chart_pids[200];
    int chart_times[200];
    int intervals = 0;

    int current_time = 0;
    int completed = 0;

    cout << "\n--- Execution Steps ---\n";

    // Round Robin loop over basic array
    while (completed < n) {
        bool progress = false;

        for (int i = 0; i < n; i++) {
            if (p[i].rem_burst > 0) {
                progress = true;

                int slice = (p[i].rem_burst > quantum) ? quantum : p[i].rem_burst;

                cout << "[Time " << current_time << "] Process " 
                     << p[i].id << " starts execution.\n";

                current_time += slice;
                p[i].rem_burst -= slice;

                // Record slice for Gantt chart
                chart_pids[intervals] = p[i].id;
                chart_times[intervals] = current_time;
                intervals++;

                if (p[i].rem_burst == 0) {
                    p[i].completion_time = current_time;
                    cout << "[Time " << current_time << "] Process " 
                         << p[i].id << " finishes execution.\n";
                    completed++;
                } else {
                    cout << "[Time " << current_time << "] Process " 
                         << p[i].id << " is preempted (" 
                         << p[i].rem_burst << " remaining).\n";
                }
            }
        }

        if (!progress) {
            break;
        }
    }

    // --- Draw Gantt Chart ---
    cout << "\n--- Gantt Chart ---\n";

    // Line 1: Process blocks
    cout << "|";
    for (int i = 0; i < intervals; i++)
        cout << "  P" << chart_pids[i] << "  |";
    
    cout << "\n";

    // Line 2: Timeline numbers (aligned with the blocks)
    cout << "0";
    for (int i = 0; i < intervals; i++) {
        // Output spacing manually to match the "|  P#  |" block width
        if (chart_times[i] < 10) {
            cout << "      " << chart_times[i];
        } else {
            cout << "     " << chart_times[i];
        }
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst;
    }
    cout << "\n\n--- Final Process Table ---\n";
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" 
            << p[i].arrival_time << "\t" 
            << p[i].burst << "\t" 
            << p[i].completion_time << "\t\t" 
            << p[i].turnaround_time << "\t\t" 
            << p[i].waiting_time << "\n";
    }
    return 0;
}