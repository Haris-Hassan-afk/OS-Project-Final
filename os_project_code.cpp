#include "headerFunctions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib> // For optional system calls

using namespace std;

void LRTF() {
    int current_time = 0;
    bool task_found = false;

    // Assuming burst_remaining and other arrays are set up similarly to your SRTF implementation.
    while (completed != n) {
        int idx = -1;
        int max_remaining_time = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !is_completed[i] && burst_remaining[i] > max_remaining_time) {
                max_remaining_time = burst_remaining[i];
                idx = i;
            }
        }

        if (idx != -1) {
            if (burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - previous;
            }

            burst_remaining[idx]--;
            current_time++;
            previous = current_time;

            if (burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        } else 
		{
            current_time++;
        }
    }

    // Updating the statistics to be used in visualization
    for (int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);
}

void LJF() {
    int current_time = 0;
    bool task_found = false;

    // Initialize variables similar to your existing structure.
    while (completed != n) {
        int idx = -1;
        int max_burst_time = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !is_completed[i] && p[i].burst_time > max_burst_time) {
                max_burst_time = p[i].burst_time;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].start_time = current_time;
            if (idx > 0) {
                total_idle_time += max(0, p[idx].start_time - previous);
            }
            
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            previous = current_time;
        } else {
            current_time++;
        }
    }

    // Calculate average values for display and comparison
    for (int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);
}
void SRTF()
{
    while (completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                if (burst_remaining[i] < mn)
                {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if (burst_remaining[i] == mn)
                {
                    if (p[i].arrival_time < p[idx].arrival_time)
                    {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            if (burst_remaining[idx] == p[idx].burst_time)
            {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - previous;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            previous = current_time;

            if (burst_remaining[idx] == 0)
            {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);

}
void HRRN() {
    int current_time = 0;
    bool task_found = false;

    // Initialize is_completed[] if not already in your structure, indicating whether each process has been completed.
    while (completed != n) {
        int idx = -1;
        float highest_rr = -1;  // Initialize the highest response ratio to a very low number.

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !is_completed[i]) {
                float waiting_time = current_time - p[i].arrival_time;
                float response_ratio = 1 + (waiting_time / p[i].burst_time);
                if (response_ratio > highest_rr) {
                    highest_rr = response_ratio;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].start_time = current_time;
            if (idx > 0) {
                total_idle_time += max(0, p[idx].start_time - previous);
            }

            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            previous = current_time;
        } else {
            current_time++;  // Increment current_time if no process is found.
        }
    }

    // Update average statistics for the display and comparison.
    for (int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);
}




void saveData(const vector<float>& data, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for output: " << filename << endl;
        return;
    }
    for (size_t i = 0; i < data.size(); ++i) {
        outFile << i << " " << data[i] << endl;
    }
    outFile.close();
}

void generateGnuplotScript(const string& dataFileName, const string& outputFileName, const string& title, const string& xlabel, const vector<string>& names) {
    ofstream scriptFile("plot_script.gp");
    if (!scriptFile) {
        cerr << "Error opening script file for output." << endl;
        return;
    }

    scriptFile << "set terminal png size 800,600\n";
    scriptFile << "set output '" << outputFileName << "'\n";
    scriptFile << "set title '" << title << "'\n";
    scriptFile << "set xlabel '" << xlabel << "'\n";
    scriptFile << "set ylabel 'Values'\n";
    scriptFile << "set boxwidth 0.5\n";
    scriptFile << "set yrange [0:*]\n";
    scriptFile << "set style fill solid\n";
    scriptFile << "plot '" << dataFileName << "' using 1:2:xtic(3) with boxes notitle\n";
    scriptFile.close();
}



int main() {
	
	
    vector<string> names = { "LRTF", "LJF", "SRTF", "HRRN" };


	cout << "Enter the number of processes: ";
    cin >> n;



    for (int i = 0; i < n; ++i) {
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> p[i].arrival_time;

        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> p[i].burst_time;

        burst_remaining[i] = p[i].burst_time;  // Initialize burst remaining
    }


    for (int i = 0; i < n; ++i)
    {
        p_copy[i].arrival_time = p[i].arrival_time;
        p_copy[i].burst_time = p[i].burst_time;
        burst_remaining_copy[i] = burst_remaining[i];
    }
    

      cout << "LRTF\n\n";
    LRTF();
    display();
    avg_turnaround_time_all.push_back(avg_turnaround_time);
    avg_response_time_all.push_back(avg_response_time);
    avg_waiting_time_all.push_back(avg_waiting_time);
    cpu_utilisation_all.push_back(cpu_utilisation);
    throughput_all.push_back(throughput);
    reset_vars();

    cout << "LJF\n\n";
    LJF();
    display();
    avg_turnaround_time_all.push_back(avg_turnaround_time);
    avg_response_time_all.push_back(avg_response_time);
    avg_waiting_time_all.push_back(avg_waiting_time);
    cpu_utilisation_all.push_back(cpu_utilisation);
    throughput_all.push_back(throughput);
    reset_vars();

    cout << "SRTF\n\n";
    SRTF();
    display();
    avg_turnaround_time_all.push_back(avg_turnaround_time);
    avg_response_time_all.push_back(avg_response_time);
    avg_waiting_time_all.push_back(avg_waiting_time);
    cpu_utilisation_all.push_back(cpu_utilisation);
    throughput_all.push_back(throughput);
    reset_vars();

    cout << "HRRN\n\n";
    HRRN();
    display();
    avg_turnaround_time_all.push_back(avg_turnaround_time);
    avg_response_time_all.push_back(avg_response_time);
    avg_waiting_time_all.push_back(avg_waiting_time);
    cpu_utilisation_all.push_back(cpu_utilisation);
    throughput_all.push_back(throughput);
    reset_vars();
    
    saveData(avg_turnaround_time_all, "turnaround_time.dat");
    saveData(avg_response_time_all, "response_time.dat");
    saveData(avg_waiting_time_all, "waiting_time.dat");
    saveData(cpu_utilisation_all, "cpu_utilisation.dat");
    saveData(throughput_all, "throughput.dat");

    generateGnuplotScript("turnaround_time.dat", "turnaround_time.png", "Average Turnaround Time", "Scheduling Algorithms", names);
    system("gnuplot plot_script.gp");
    generateGnuplotScript("response_time.dat", "response_time.png", "Average Response Time", "Scheduling Algorithms", names);
    system("gnuplot plot_script.gp");
    generateGnuplotScript("waiting_time.dat", "waiting_time.png", "Average waiting Time", "Scheduling Algorithms", names);
    system("gnuplot plot_script.gp");
    generateGnuplotScript("cpu_utilisation.dat", "cpu_utilisation.png", "Average cpu_utilisation ", "Scheduling Algorithms", names);
    system("gnuplot plot_script.gp");
    generateGnuplotScript("throughput.dat", "throughput.png", "Average throughput", "Scheduling Algorithms", names);
    system("gnuplot plot_script.gp");

    return 0;
}
