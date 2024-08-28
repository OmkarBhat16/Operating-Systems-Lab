#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Process {
private:
    char p_name;
    int arrival;
    int burst;
    int priority;

public:
    // Constructor
    Process(char name, int arr, int burst_time, int prio)
        : p_name(name), arrival(arr), burst(burst_time), priority(prio) {}

    // Getter and Setter for p_name
    char getName() const { return p_name; }
    void setName(char name) { p_name = name; }

    // Getter and Setter for arrival
    int getArrival() const { return arrival; }
    void setArrival(int arr) { arrival = arr; }

    // Getter and Setter for burst
    int getBurst() const { return burst; }
    void setBurst(int burst_time) { burst = burst_time; }

    // Getter and Setter for priority
    int getPriority() const { return priority; }
    void setPriority(int prio) { priority = prio; }

    // Static function to sort processes
    static void roundRobin(vector<Process>& processes) {
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            if (a.getArrival() != b.getArrival())
                return a.getArrival() < b.getArrival();
            return a.getName() < b.getName();
        });
    }

    // Function to display process information
    void display() const {
        cout << "Process Name: " << p_name << ", Arrival Time: " << arrival
                  << ", Burst Time: " << burst << ", Priority: " << priority << endl;
    }

    struct CompareProcess {
        bool operator()(const Process& p1, const Process& p2) {
            if (p1.getArrival() != p2.getArrival()) {
                return p1.getArrival() > p2.getArrival(); // Min-heap based on arrival time
            }
            return p1.getName() > p2.getName(); // Resolve ties based on process name
        }
    }; 
};

void round_robin(vector<Process> processes, int tq){
    priority_queue<Process, vector<Process>, Process::CompareProcess> pq;
	Process::roundRobin(processes);

    // Display sorted processes
    cout << "Sorted Processes:\n";
    for (const auto& process : processes) {
        // process.display();
       	pq.push(process);
    }

    int i = 0;
    while (!pq.empty()) {
        Process p = pq.top();
        p.display(); 
        pq.pop();
        if(p.getBurst() <= tq){
        	p.setBurst(0);
        } else {
        	p.setBurst(p.getBurst()-tq);
        }
        p.setArrival(p.getArrival()+tq);
        if(p.getBurst() != 0)
        	pq.push(p);
    }
    
}

int main() {
    // Create a vector of Process objects
    vector<Process> processes = {
        Process('A', 0, 3, 0),
        Process('B', 2, 1, 0),
        Process('C', 50, 14, 0),
        Process('D', 80, 5, 0)
    };

    // Sort processes using roundRobin method
    
    int choice;
    string menu = "MENU\n1. Preemptive-SJF \n2. Round Robin\n3. Nonpreemptive-SJF\n";
    cout << menu << "Enter your choice here: ";
    cin >> choice;

    switch(choice) {
        case 1:
            // Implement Preemptive-SJF here
            cout << "Preemptive-SJF option selected.\n";
            break;
        case 2:
            // Implement Round Robin here
            cout << "Round Robin option selected.\n";
            round_robin(processes,2);
            break;
        case 3:
            // Implement Nonpreemptive-SJF here
            cout << "Nonpreemptive-SJF option selected.\n";
            break;
        default:
            cout << "Invalid Choice\n";
    }

    return 0;
}
