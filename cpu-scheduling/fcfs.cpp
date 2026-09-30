#include<iostream>
#include<fstream>
using namespace std;
int chart_times[200];
int chart_pids[200];
struct Process{
    int id;
    int arrival_time;
    int burst;
    int rem_burst;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    Process(){
        id = 0;
        arrival_time = 0;
        burst = 0;
        rem_burst = 0;
        completion_time = 0;
        turnaround_time = 0;
        waiting_time = 0;
    }
};
void draw_final_results(Process *p, int intervals, int n){
    cout << "\n--- Gantt Chart ---\n";

    // Process blocks
    cout << "|";
    for (int i = 0; i < intervals; i++)
        cout << "  P" << chart_pids[i] << "  |";
    
    cout << "\n";

    // Timeline numbers
    cout << "0";
    for (int i = 0; i < intervals; i++) {
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
}
void algorithm(Process *p, int n, int &intervals){
    int curr_time = 0;
    int completed = 0;
    cout << "\n--- Execution Steps ---\n";
    while(completed < n){
        bool progress = false;
        for(int i = 0; i < n; ++i){
            if(p[i].rem_burst > 0){
                progress = true;

                cout << "[Time " << curr_time << "] Process " << p[i].id << " starts execution.\n";
                curr_time += p[i].burst;
                p[i].rem_burst = 0;

                //record for Gantt Chart
                chart_pids[intervals] = p[i].id;
                chart_times[intervals] = curr_time;
                intervals++;
                p[i].completion_time = curr_time;
                cout << "[Time " << curr_time << "] Process " << p[i].id << " finishes execution.\n" ;
                completed++;
            }
        }
        if(!progress){
            break;
        }
    }
}
int main(){
    ifstream fin("input.txt");
    int n;
    fin >> n;
    Process *p = new Process[n];
    for(int i = 0; i <n ; ++i){
        fin >> p[i].id >> p[i].burst;
        p[i].rem_burst = p[i].burst;
        p[i].arrival_time = 0;
    }
    int intervals = 0;
    algorithm(p, n, intervals);
    draw_final_results(p, intervals, n);
    delete[] p;
}
