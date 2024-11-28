//#pragma once
#include <iostream>
#include <climits>
#include <string>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

char hold;

int n = 5;
float avg_turnaround_time;
float avg_waiting_time;
float avg_response_time;
float cpu_utilisation;
int total_turnaround_time = 0;
int total_waiting_time = 0;
int total_response_time = 0;
int total_idle_time = 0;
float throughput;
struct process p[5];
struct process p_copy[5];

std::vector<float> avg_turnaround_time_all;
std::vector<float> avg_response_time_all;
std::vector<float> avg_waiting_time_all;
std::vector<float> cpu_utilisation_all;
std::vector<float> throughput_all;

//Priority Non Preemptive, SJF, SRTF
int is_completed[100] = { 0 };
int current_time = 0;
int completed = 0;
int previous = 0;
int min_arrival_time = 10000000;
int max_completion_time = -1;

int burst_remaining[100];
int burst_remaining_copy[100];

int idx;
int mark[100] = { 0 };

void reset_vars()
{

    total_turnaround_time = 0;
    total_waiting_time = 0;
    total_response_time = 0;
    total_idle_time = 0;
    current_time = 0;
    completed = 0;
    previous = 0;
    min_arrival_time = INT_MAX;
    max_completion_time = INT_MIN;

    for (int i = 0; i < 100; i++) {
        mark[i] = 0;
        is_completed[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].arrival_time = p_copy[i].arrival_time;
        p[i].burst_time = p_copy[i].burst_time;
        burst_remaining[i] = burst_remaining_copy[i];
    }

}