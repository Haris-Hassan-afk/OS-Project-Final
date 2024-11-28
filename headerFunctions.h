//#pragma once
#include "headerVars.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib> // For system calls

using namespace std;

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;

}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;

}

void sortArrival(process arr[], int n)
{
    process key;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].arrival_time > key.arrival_time)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

}

void sortID(process arr[], int n)
{

    process key;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].pid > key.pid)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

}

void display()
{

    cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;

    for (int i = 0; i < n; i++)
        cout << i << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t" << "\n" << endl;

    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << "Throughput = " << throughput << " process/unit time" << endl << endl;

}

