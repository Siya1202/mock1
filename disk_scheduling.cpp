
#include <iostream>
#include <algorithm>
using namespace std;

int abs_i(int x)
{
    return x < 0 ? -x : x;
}

void fcfs(int req[], int n, int head)
{
    int total = 0, cur = head;

    cout << "\n--- FCFS ---\nSeek order: " << cur;

    for (int i = 0; i < n; i++)
    {
        total += abs_i(req[i] - cur);
        cur = req[i];
        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << "\n";
}

void sstf(int req[], int n, int head)
{
    int r[100], done[100] = {0};
    int cur = head, total = 0;

    for (int i = 0; i < n; i++)
        r[i] = req[i];

    cout << "\n--- SSTF ---\nSeek order: " << cur;

    for (int c = 0; c < n; c++)
    {
        int idx = -1, best = 1000000;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && abs_i(r[i] - cur) < best)
            {
                best = abs_i(r[i] - cur);
                idx = i;
            }
        }

        done[idx] = 1;
        total += best;
        cur = r[idx];
        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << "\n";
}

void scan(int req[], int n, int head, int disk)
{
    int r[102], count = 0, cur = head, total = 0;

    for (int i = 0; i < n; i++)
        r[count++] = req[i];

    r[count++] = 0;
    r[count++] = disk - 1;

    sort(r, r + count);

    int pos = 0;
    while (pos < count && r[pos] < head)
        pos++;

    cout << "\n--- SCAN ---\nSeek order: " << cur;

    for (int i = pos; i < count; i++)
    {
        if (r[i] == cur)
            continue;
        total += abs_i(r[i] - cur);
        cur = r[i];
        cout << " -> " << cur;
    }

    for (int i = pos - 1; i >= 0; i--)
    {
        if (r[i] == cur)
            continue;
        total += abs_i(r[i] - cur);
        cur = r[i];
        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << "\n";
}

void cscan(int req[], int n, int head, int disk)
{
    int r[102], count = 0, cur = head, total = 0;

    for (int i = 0; i < n; i++)
        r[count++] = req[i];

    r[count++] = 0;
    r[count++] = disk - 1;

    sort(r, r + count);

    int pos = 0;
    while (pos < count && r[pos] < head)
        pos++;

    cout << "\n--- C-SCAN ---\nSeek order: " << cur;

    for (int i = pos; i < count; i++)
    {
        if (r[i] == cur)
            continue;
        total += abs_i(r[i] - cur);
        cur = r[i];
        cout << " -> " << cur;
    }

    if (cur != disk - 1)
    {
        total += abs_i((disk - 1) - cur);
        cur = disk - 1;
        cout << " -> " << cur;
    }

    total += disk - 1;
    cur = 0;
    cout << " -> " << cur;

    for (int i = 0; i < pos; i++)
    {
        if (r[i] == 0)
            continue;
        total += abs_i(r[i] - cur);
        cur = r[i];
        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << "\n";
}

int main()
{
    int n, head, disk, req[100];

    cout << "Enter disk size: ";
    cin >> disk;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter request queue: ";
    for (int i = 0; i < n; i++)
        cin >> req[i];

    cout << "Enter initial head position: ";
    cin >> head;

    if (disk <= 0 || n <= 0 || n > 100 || head < 0 || head >= disk)
    {
        cout << "Invalid input\n";
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (req[i] < 0 || req[i] >= disk)
        {
            cout << "Invalid request position\n";
            return 0;
        }
    }

    fcfs(req, n, head);
    sstf(req, n, head);
    scan(req, n, head, disk);
    cscan(req, n, head, disk);

    return 0;
}
