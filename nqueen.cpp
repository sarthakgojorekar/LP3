#include <iostream>
#include <vector>
using namespace std;

class solution
{
public:
    bool issafe(int **arr, int x, int y, int n)
    {
        for (int row = 0; row < n; row++)
        {
            if (arr[row][y] == 1)
            {
                return false;
            }
        }
        int row = x;
        int col = y;

        while (row >= 0 && col >= 0)
        {
            if (arr[row][col] == 1)
            {
                return false;
            }
            row--;
            col--;
        }

        row = x;
        col = y;

        while (row >= 0 && col < n)
        {
            if (arr[row][col] == 1)
            {
                return false;
            }
            row--;
            col++;
        }

        return true;
    }

    bool nqueen(int **arr, int row, int n)
    {

        if (row >= n)
        {
            printsol(arr, n);
            cout << endl;
            return true;
        }
        bool res = false;
        for (int col = 0; col < n; col++)
        {
            if (issafe(arr, row, col, n))
            {
                arr[row][col] = 1;

                res = nqueen(arr, row + 1, n) | res; // exploring more solutions.

                arr[row][col] = 0; // backtracking.
            }
        }
        return res;
    }

    void printsol(int **arr, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }

    void branch_bound(int **arr, int row, vector<bool> &cols, vector<bool> &ndiag, vector<bool> &rdiag, int n)
    {
        if (row >= n)
        {
            printsol(arr, n);
            cout << endl;
            return;
        }

        for (int col = 0; col < n; col++)
        {
            if (cols[col] == false && ndiag[row + col] == false && rdiag[row - col + n - 1] == false)
            {
                arr[row][col] = 1;
                cols[col] = true;
                rdiag[row - col + n - 1] = true;
                ndiag[row + col] = true;
                branch_bound(arr, row + 1, cols, ndiag, rdiag, n);
                arr[row][col] = 0;
                cols[col] = false;
                rdiag[row - col + n - 1] = false;
                ndiag[row + col] = false;
            }
        }
    }
};

int main()
{
    solution s;

    int **arr;
    int **arr1;
    int n;
    cout << "enter size of chessboard: ";
    cin >> n;

    arr = new int *[n];
    arr1 = new int *[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
        arr1[i] = new int[n];

        for (int j = 0; j < n; j++)
        {
            arr[i][j] = 0;
            arr1[i][j] = 0;
        }
    }

    if (!s.nqueen(arr, 0, n))
    {
        cout << "No solution exists. " << endl;
    }

    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    cout << endl;

    vector<bool> ndiag((2 * n) - 1);
    vector<bool> rdiag((2 * n) - 1);
    vector<bool> cols(n);

    s.branch_bound(arr1, 0, cols, ndiag, rdiag, n);
}
