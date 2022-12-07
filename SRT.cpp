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

int minBurstTime(Process *p, int n)
{
    int min = p[0].burst_time;
    int imin = 0;
    for (int i = 0; i < n; i++)
    {
        if (p[i].burst_time < min)
        {
            min = p[i].burst_time;
            imin = i;
        }
    }
    return imin;
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

void ShortestRemainingTimeFirst(Process *p, int n, int time_current, int burst_time)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].burst_time < p[j].burst_time && p[i].arrival_time <= time_current && p[i].burst_time < burst_time)
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

void SelectionFunction(Process *p, int n)
{
    Process *p_temp = new Process[100];
    int time_current = 0; // timeline chương trình
    ///
    int flag_c = 1;           // phòng trừ trường hợp không có process nào tới tại thời điểm 0
    int flag_first_come[100]; // đánh dấu thời điểm được thực thi lần đầu
    int flag_previous;        // vị trí process vừa chạy trước đó
    int flag_current;         // vị trí process hiện đang chạy
    int waiting_time[100];    // tính thời gian chờ mỗi khi bị preemtive đến lúc được thực thi lại
    /// khởi tạo các mảng tạm
    for (int i = 0; i < 100; i++)
    {
        waiting_time[i] = 0;
        flag_first_come[i] = -1; // -1 vì nếu sử dụng 0 để đánh dấu (flag chỉ cập nhật duy nhất 1 lần
                                 // ) thì sẽ có process đầu tiên có arrival time = 0 cập nhật 2 lần
    }
    sortByArrivalTime(p, n); // chọn ra process có burst time min xếp ra phía cuối
    flag_first_come[p[n - 1].name] = p[n - 1].arrival_time;
    // Duyệt từ cuối lên
    while (n > 0)
    {
        p[n - 1].burst_time--; // Xét từ từ chậm rãi
        // tăng waiting time khi process đã đến hàng đợi mà chưa được thực thi
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= time_current)
            {
                waiting_time[p[i].name]++;
            }
        }
        // Chừa thằng đang thực thi ra
        waiting_time[p[n - 1].name]--;
        // Trừ trường hợp ko có process nào đến lúc time_current = 0
        if (flag_c == 1)
        {
            time_current = p[n - 1].arrival_time;
            flag_c = 0;
        }
        time_current++;
        flag_previous = p[n - 1].name; // Lưu tên process sắp rời/ có khả năng rời hàng đợi
        // Nếu đã thực thi hết (không còn burst thì cout trạng thái
        if (p[n - 1].burst_time == 0)
        {
            cout << p[n - 1].name << "            " << flag_first_come[p[n - 1].name] - p[n - 1].arrival_time << "               " << waiting_time[p[n - 1].name] << "            " << (time_current - p[n - 1].arrival_time) << endl;
            ave_waiting_time += waiting_time[p[n - 1].name]; // cộng dồn waiting time đã cộng nãy giờ
            ave_turnaround_time += time_current - p[n - 1].arrival_time;
            n--; // thu hẹp kích thước để xét những thằng còn lại
            if (n == 0)
                return;
        }
        ShortestRemainingTimeFirst(p, n, time_current, p[n - 1].burst_time); // chọn ra thằng có burst < burst còn lại của p[flag_current]
        flag_current = p[n - 1].name;                                        // cập nhập lại nếu có thằng nào đó thỏa cái trên
        // nếu chuyển ngữ cảnh xảy ra
        if (flag_current != flag_previous)
        {
            if (flag_first_come[p[n - 1].name] == -1)
            {
                flag_first_come[p[n - 1].name] = time_current;
            }
        }
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
