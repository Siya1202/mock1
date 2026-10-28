#include <iostream>
using namespace std;

int referenceString[100], RS, FR;

void show(int f[], int n)
{
    cout << " Frames: ";
    for (int i = 0; i < n; i++)
    {
        if (f[i] == -1)
            cout << "- ";
        else
            cout << f[i] << " ";
    }
    cout << "\n";
}

void fifo()
{
    int f[100], ptr = 0, faults = 0;

    for (int i = 0; i < FR; i++)
        f[i] = -1;

    cout << "\n===== FIFO =====\n";

    for (int i = 0; i < RS; i++)
    {
        int hit = 0;

        for (int j = 0; j < FR; j++)
            if (f[j] == referenceString[i])
                hit = 1;

        if (!hit)
        {
            f[ptr] = referenceString[i];
            ptr = (ptr + 1) % FR;
            faults++;
            cout << "Ref " << referenceString[i] << " -> FAULT";
        }
        else
        {
            cout << "Ref " << referenceString[i] << " -> hit ";
        }

        show(f, FR);
    }

    cout << "Total Page Faults (FIFO) = " << faults << "\n";
}

void lru()
{
    int f[100], last[100], faults = 0;

    for (int i = 0; i < FR; i++)
    {
        f[i] = -1;
        last[i] = -1;
    }

    cout << "\n===== LRU =====\n";

    for (int i = 0; i < RS; i++)
    {
        int hit = -1;

        for (int j = 0; j < FR; j++)
            if (f[j] == referenceString[i])
                hit = j;

        if (hit == -1)
        {
            int pos = 0;

            for (int j = 1; j < FR; j++)
                if (last[j] < last[pos])
                    pos = j;

            f[pos] = referenceString[i];
            last[pos] = i;
            faults++;
            cout << "Ref " << referenceString[i] << " -> FAULT";
        }
        else
        {
            last[hit] = i;
            cout << "Ref " << referenceString[i] << " -> hit ";
        }

        show(f, FR);
    }

    cout << "Total Page Faults (LRU) = " << faults << "\n";
}

void optimal()
{
    int f[100], faults = 0;

    for (int i = 0; i < FR; i++)
        f[i] = -1;

    cout << "\n===== Optimal =====\n";

    for (int i = 0; i < RS; i++)
    {
        int hit = 0;

        for (int j = 0; j < FR; j++)
            if (f[j] == referenceString[i])
                hit = 1;

        if (!hit)
        {
            int pos = -1, farthest = -1;

            for (int j = 0; j < FR; j++)
            {
                if (f[j] == -1)
                {
                    pos = j;
                    break;
                }

                int k;
                for (k = i + 1; k < RS; k++)
                    if (f[j] == referenceString[k])
                        break;

                if (k == RS)
                {
                    pos = j;
                    break;
                }

                if (k > farthest)
                {
                    farthest = k;
                    pos = j;
                }
            }

            f[pos] = referenceString[i];
            faults++;
            cout << "Ref " << referenceString[i] << " -> FAULT";
        }
        else
        {
            cout << "Ref " << referenceString[i] << " -> hit ";
        }

        show(f, FR);
    }

    cout << "Total Page Faults (Optimal) = " << faults << "\n";
}

int main()
{
    cout << "Enter number of frames: ";
    cin >> FR;

    if (FR <= 0 || FR > 100)
    {
        cout << "Invalid number of frames\n";
        return 0;
    }

    cout << "Enter length of reference string: ";
    cin >> RS;

    if (RS <= 0 || RS > 100)
    {
        cout << "Invalid reference string length\n";
        return 0;
    }

    cout << "Enter reference string: ";
    for (int i = 0; i < RS; i++)
        cin >> referenceString[i];

    fifo();
    lru();
    optimal();

    return 0;
}