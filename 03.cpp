#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int recursive(int n, int W, int wt[], int val[])
{
    if (n == 0 || W == 0)
    {
        return 0;
    }
    if (wt[n - 1] <= W)
    {
        return max(recursive(n - 1, W, wt, val), val[n - 1] + recursive(n - 1, W - wt[n - 1], wt, val));
    }
    else
    {
        return recursive(n - 1, W, wt, val);
    }
}

int tabulation(int n, int W, int wt[], int val[])
{
    int t[n + 1][W + 1];
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < W + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                t[i][j] = 0;
            }
        }
    }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < W + 1; j++)
        {
            if (wt[i - 1] <= j)
            {
                t[i][j] = max(t[i - 1][j], val[i - 1] + t[i - 1][j - wt[i - 1]]);
            }
            else
            {
                t[i][j] = t[i - 1][j];
            }
        }
    }
    return t[n][W];
}

struct item
{
    int wt;
    int val;
    double ratio;
};
struct node
{
    int level;
    int profit;
    int wt;
    double bound;
};

bool compare(item a, item b)
{
    return a.ratio > b.ratio;
}

double bound(node &u, vector<item> Items, int W, int n)
{
    if (u.wt >= W)
    {
        return 0;
    }
    int j = u.level + 1;
    int totalwt = u.wt;
    int totalprofit = u.profit;

    while (j < n && totalwt + Items[j].wt <= W)
    {
        totalprofit += Items[j].val;
        totalwt += Items[j].wt;
        j++;
    }
    return totalprofit;
}

int buildTree(vector<item> Items, int W)
{
    sort(Items.begin(), Items.end(), compare);
    node u, v;
    int n = Items.size();
    queue<node> q;
    u = {-1, 0, 0, 0};
    q.push(u);

    int totalprofit = 0;

    while (!q.empty())
    {
        u = q.front();
        q.pop();

        if (u.level == -1)
        {
            v.level = 0;
        }
        if (u.level == n - 1)
        {
            continue;
        }
        v.level = u.level + 1;
        v.wt = u.wt + Items[v.level].wt;
        v.profit = u.profit + Items[v.level].val;

        if (totalprofit < v.profit && v.wt <= W)
        {
            totalprofit = v.profit;
        }

        v.bound = bound(v, Items, W, n);

        if (v.bound > totalprofit)
        {
            q.push(v);
        }

        v.wt = u.wt;
        v.profit = u.profit;
        v.bound = bound(v, Items, W, n);

        if (v.bound > totalprofit)
        {
            q.push(v);
        }
    }
    return totalprofit;
}

int main()
{
    int val[] = {1, 2, 3};
    int wt[] = {4, 5, 1};
    int W = 4;
    int ans = recursive(3, W, wt, val);
    cout << ans << endl;

    int ans2 = tabulation(3, W, wt, val);
    cout << ans2 << endl;

    vector<item> items = {{4, 1, 0.25},
                          {5, 2, 0.4},
                          {1, 3, 3}};

    int ans4 = buildTree(items, W);
    cout << ans4 << endl;
}