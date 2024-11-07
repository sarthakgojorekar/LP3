#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

class node
{
public:
    int freq;
    char ch;
    node *left;
    node *right;
    node(int f, char ch)
    {
        this->freq = f;
        this->ch = ch;
        left = NULL;
        right = NULL;
    }
};

class compare
{
public:
    bool operator()(node *a, node *b)
    {
        return a->freq > b->freq;
    }
};

node *buildTree(unordered_map<char, int> mp)
{
    priority_queue<node *, vector<node *>, compare> pq;

    for (auto i : mp)
    {
        node *n = new node(i.second, i.first);
        pq.push(n);
    }

    while (pq.size() > 1)
    {
        auto *left = pq.top();
        pq.pop();
        auto *right = pq.top();
        pq.pop();

        int f = left->freq + right->freq;
        node *n = new node(f, '\0');

        n->left = left;
        n->right = right;
        pq.push(n);
    }
    return pq.top();
}

void generate_codes(node *root, unordered_map<char, int> mp, string s, unordered_map<char, string> &codes)
{
    if (!root)
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        codes[root->ch] = s;
    }

    generate_codes(root->left, mp, s + '0', codes);
    generate_codes(root->right, mp, s + '1', codes);
}

string code(string txt, unordered_map<char, string> mp)
{
    string ans = "";
    for (int i = 0; i < txt.size(); i++)
    {
        string s = mp[txt[i]];
        ans += s;
    }
    return ans;
}

int main()
{
    unordered_map<char, int> mp;
    unordered_map<char, string> codes;
    string text = "aaabbc";

    for (auto i : text)
    {
        mp[i]++;
    }
    node *root = buildTree(mp);

    generate_codes(root, mp, "", codes);
    cout << "frequecy: " << endl;
    for (auto i : mp)
    {
        cout << i.first << "--->" << i.second << endl;
    }
    cout << "Printing codes : " << endl;

    for (auto i : codes)
    {
        cout << i.first << "---->" << i.second << endl;
    }

    string s = code(text, codes);
    cout << "encoded string is : ";

    for (int i = 0; i < s.length(); i++)
    {
        cout << s[i];
    }
}
