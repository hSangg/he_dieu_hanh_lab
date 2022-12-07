#include <iostream>
#include <queue>
using namespace std;
struct Process
{
    int name;
    int burst_time;
    int arrival_time;
};
static double ave_turnaround_time = 0;
static double ave_waiting_time = 0;
void swap(Process &p1, Process &p2)
{
    Process tmp;
    tmp = p1;
    p1 = p2;
    p2 = tmp;
}
void sortByArrivalTime(Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time < p[j].arrival_time)
            {
                swap(p[i], p[j]);
            }
            else
            {
                if (p[i].arrival_time == p[j].arrival_time)
                {
                    if (p[i].burst_time < p[j].burst_time)
                    {
                        swap(p[i], p[j]);
                    }
                }
            }
        }
    }
}

void sortByBurstTime(Process *p, int n, int time_current)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].burst_time < p[j].burst_time && p[i].arrival_time <= time_current)
            {
                swap(p[i], p[j]);
            }
        }
    }
}

void Input(Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "-----------------" << endl;
        cout << "Nhap ID process: ";
        cin >> p[i].name;
        cout << "Nhap burst time: ";
        cin >> p[i].burst_time;
        cout << "Nhap arrival time: ";
        cin >> p[i].arrival_time;
    }
}

void SelectionFunction(Process *p, int n)
{
    int time_current;
    int flag = 1;
    // Sort theo thứ tự arrival time trước đã
    sortByArrivalTime(p, n);
    // Hàm lựa chọn quyết định xem process nào vào queue trước
    for (int i = 0; i < n; n--)
    {
        // pQueue.push(p[n - 1]);
        if (flag == 1)
        {
            time_current = p[n - 1].arrival_time;
            flag = 0;
        }
        time_current += p[n - 1].burst_time;
        ave_waiting_time += time_current - p[n - 1].arrival_time - p[n - 1].burst_time;
        ave_turnaround_time += (time_current - p[n - 1].arrival_time);
        cout << p[n - 1].name << "            " << time_current - p[n - 1].arrival_time - p[n - 1].burst_time << "               " << time_current - p[n - 1].arrival_time - p[n - 1].burst_time << "            " << (time_current - p[n - 1].arrival_time) << endl;
        sortByBurstTime(p, n - 1, time_current);
    }
}

int main()
{
    Process *p = new Process[100];
    queue<Process> pQueue;
    int n;
    cout << "Nhap so luong process: ";
    cin >> n;
    Input(p, n);
    cout << "Process   Response-time   Waiting-time   Turn around-time" << endl;
    SelectionFunction(p, n);
    cout << "Thoi gian dap ung trung binh: " << ave_waiting_time / n << endl;
    cout << "Thoi gian hoan thanh trung binh: " << ave_turnaround_time / n << endl;
    system("pause");
    return 0;
}
