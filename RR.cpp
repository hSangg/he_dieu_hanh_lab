#include <iostream>
#include <queue>
using namespace std;
struct Process
{
    int name;
    int burst_time;
    int arrival_time;
};

static queue<int> pStart_time;
static double ave_turnaround_time = 0;
static double ave_waiting_time = 0;
static int waiting_time[100];

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
            if (p[i].arrival_time > p[j].arrival_time)
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

int check(int flag[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (flag[i] == 1)
            return 1;
    }
    return 0;
}

queue<Process> SelectionFunction(Process *p, int n, int quantum_time)
{
    int time_current = 0;
    int flag_c = 1;
    queue<Process> pQueue;
    int flag[100];
    sortByArrivalTime(p, n);
    for (int i = 0; i < n; i++)
    {
        flag[i] = 1;
        waiting_time[i] = p[i].arrival_time;
    }
    while (check(flag, n))
    {
        // Duyệt qua hết 1 lượt các process
        for (int i = 0; i < n; i++)
        {
            // process nào đã đến & còn burst time mới được xét
            if (time_current >= p[i].arrival_time && flag[i] == 1)
            {
                pQueue.push(p[i]);
                if (flag_c == 1)
                {
                    time_current = p[i].arrival_time;
                    flag_c = 0;
                }
                pStart_time.push(time_current);
                p[i].burst_time -= quantum_time;
                if (p[i].burst_time <= 0)
                {
                    flag[i] = 0;
                    ave_turnaround_time += time_current + (p[i].burst_time + quantum_time) - p[i].arrival_time;
                }
                ave_waiting_time += (time_current - waiting_time[i]);
                if (p[i].burst_time < 0)
                {
                    time_current += p[i].burst_time + quantum_time;
                }
                else
                {
                    time_current += quantum_time;
                }
                waiting_time[i] = time_current;
            }
        }
    }
    return pQueue;
}

void Print(queue<Process> &pQueue)
{
    while (pQueue.empty() == 0)
    {
        cout << pQueue.front().name << " -- ";
        pQueue.pop();
    }
    cout << endl;
    while (pStart_time.empty() == 0)
    {

        cout << pStart_time.front() << " -- ";
        pStart_time.pop();
    }
    cout << endl;
}

int main()
{
    Process *p = new Process[100];
    queue<Process> pQueue;
    int n, quantum_time;
    cout << "Nhap so luong process: ";
    cin >> n;
    cout << "Nhap quantum time: ";
    cin >> quantum_time;
    Input(p, n);
    int total_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_time += p[i].burst_time;
    }
    int quantum_step = total_time / n;
    if (quantum_step * n < total_time)
        quantum_step++;
    pQueue = SelectionFunction(p, n, quantum_time);
    Print(pQueue);
    cout << "Thoi gian cho trung binh: " << ave_waiting_time / n << endl;
    cout << "Thoi gian hoan thanh trung binh: " << ave_turnaround_time / n << endl;
    system("pause");
    return 0;
}
