#include <bits/stdc++.h>
#include <time.h>
using namespace std;
#define ll long long int
ll pinf = 1e12, inf = 999999, sizefib = 0;
map<ll, ll> mp;
vector<ll> h(2005), dist(2005);
vector<pair<ll, ll>> adj[2006];
//------Fibonacci starts
struct node
{
    pair<ll, ll> val;
    ll degree;
    node *parent, *child, *left, *right;
};
node *minnode = NULL;
node *newnode(pair<ll, ll> n)
{
    node *temp = new node;
    temp->val = n;
    temp->degree = 0;
    temp->child = NULL;
    temp->parent = NULL;
    temp->left = temp->right = temp;
    return temp;
}
void insertinfibonacci(pair<ll, ll> n)
{
    node *f = newnode(n);
    if (minnode == NULL)
    {
        minnode = f;
        sizefib++;
        return;
    }
    node *temp = minnode->left;
    temp->right = f;
    f->right = minnode;
    f->left = temp;
    minnode->left = f;
    if ((minnode->val).first > (f->val).first)
        minnode = f;
    sizefib++;
}
void consolidate()
{
    vector<node *> A(sizefib + 1, NULL);
    node *t = minnode;
    ll count = 0;
    while (count != 1)
    {
        node *x = t;
        ll d = x->degree;
        while (A[d] != NULL)
        {
            node *y = A[d];
            if (x->val.first > y->val.first)
            {
                swap(x, y);
            }
            x->child = y;
            x->degree++;
            d++;
            A[d - 1] = NULL;
        }
        A[d] = x;
        t = t->left;
        if (t == minnode)
        {
            count = 1;
        }
    }
    minnode = NULL;
}
void extractmin(node *f)
{
    if (minnode == NULL)
        return;
    node *t1 = minnode, *t2 = minnode->left, *t3 = minnode->right, *t4 = minnode->child;
    node *ptr = t4;
    sizefib--;
    ll count = 0;
    node *t = t4->left;
    t3->left = t;
    t->right = t3;
    t2->right = t4;
    t4->left = t2;
    minnode = t4;
    ptr = t4->right;
    while (count != 1)
    {
        ptr->parent = NULL;
        ptr = ptr->right;
        if (ptr == t4)
        {
            count = 1;
        }
    }
    ptr = t4->right;
    while (ptr != t4)
    {
        if ((minnode->val).first > (ptr->val).first)
        {
            minnode = ptr;
        }
        ptr = ptr->left;
    }
    if (t1 == t1->right)
        minnode = NULL;
    else
        consolidate();
}
//------Fibonacci ends
//------Binomial starts
struct node2
{
    pair<ll, ll> val;
    ll degree;
    node2 *child, *sibling, *parent;
};
node2 *root = NULL;
node2 *createnode2(pair<ll, ll> n)
{
    node2 *temp = new node2;
    temp->val = n;
    temp->parent = temp->sibling = temp->child = NULL;
    temp->degree = 0;
    return temp;
}
node2 *mergebinomial2(node2 *h, node2 *t)
{
    node2 *lptr = NULL;
    if ((h == NULL) || (t == NULL))
    {
        if (h == NULL)
            return t;
        return h;
    }
    node2 *temp = NULL, *ans1 = h, *ans2 = t;
    if (h->degree <= t->degree)
        temp = h, lptr = h, ans1 = ans1->sibling;
    else
        temp = t, lptr = t, ans2 = ans2->sibling;
    lptr->sibling = NULL;
    while (ans1 && ans2)
    {
        if (ans1->degree > ans2->degree)
        {
            lptr->sibling = ans2;
            ans2 = ans2->sibling;
        }
        else if (ans1->degree <= ans2->degree)
        {
            lptr->sibling = ans1;
            ans1 = ans1->sibling;
        }
        lptr = lptr->sibling;
        lptr->sibling = NULL;
    }
    if (ans1 != NULL)
    {
        while (ans1)
        {
            lptr->sibling = ans1;
            lptr = lptr->sibling;
            ans1 = ans1->sibling;
            lptr->sibling = NULL;
        }
    }
    else if (ans2 != NULL)
    {
        while (ans2)
        {
            lptr->sibling = ans2;
            lptr = lptr->sibling;
            ans2 = ans2->sibling;
            lptr->sibling = NULL;
        }
    }
    return temp;
}
node2 *unionbinomial2(node2 *h, node2 *t)
{
    node2 *temp = NULL;
    if (h || t)
        temp = mergebinomial2(h, t);
    else
        return NULL;
    node2 *cur = temp;
    node2 *prev = NULL;
    node2 *next = temp->sibling;
    while (next)
    {
        if (cur->degree != next->degree)
        {
            prev = cur;
            cur = next;
        }
        else if (((next->sibling) && (next->sibling)->degree == cur->degree))
        {
            prev = cur;
            cur = next;
        }
        else
        {
            if ((next->val).first >= (cur->val).first)
            {
                cur->sibling = next->sibling;
                next->parent = cur;
                next->sibling = cur->child;
                cur->child = next;
                cur->degree++;
            }
            else if ((next->val).first < (cur->val).first)
            {
                if (prev)
                    prev->sibling = next;
                else
                    temp = next;
                cur->parent = next;
                cur->sibling = next->child;
                next->child = cur;
                next->degree++;
                cur = next;
            }
        }
        next = next->sibling;
    }
    return temp;
}
node2 *findminimumnode2(node2 *h) //Function to find the node with the minmum first value
{
    if (h == NULL)
        return h;
    node2 *toreturn = NULL;
    node2 *temp = h;
    ll min = inf;
    while (temp)
    {
        if (min > (temp)->val.first)
        {
            toreturn = temp;
            min = ((temp)->val).first;
        }
        temp = temp->sibling;
    }
    return toreturn;
}
node2 *newheapmaker(node2 *h)
{
    if (h == NULL)
        return NULL;
    node2 *newhead = NULL, *temp = NULL;
    do
    {
        temp = h;
        h = h->sibling;
        temp->sibling = newhead;
        newhead = temp;
    } while (h);
    return newhead;
}
node2 *extractmin2(node2 *h)
{
    if (h == NULL)
        return h;
    if (root->sibling == NULL && (root->degree == 0))
        root = NULL;
    node2 *prev = NULL, *min = h, *temp_heap = NULL;
    node2 *curr = h;
    ll min2 = h->val.first;
    while (curr->sibling != NULL)
    {
        if ((curr->sibling)->val.first < min2)
        {
            min2 = (curr->sibling)->val.first;
            prev = curr;
            min = curr->sibling;
        }
        curr = curr->sibling;
    }
    if ((prev == NULL) && (min->sibling) == NULL)
        h = NULL;
    else if (!(prev))
        h = min->sibling;
    else
        prev->sibling = min->sibling;
    if (min && (min->child))
    {
        temp_heap = newheapmaker(min->child);
        min->child->sibling = NULL;
    }
    if (h != temp_heap)
        return unionbinomial2(h, temp_heap);
    return root;
}
void insert2(pair<ll, ll> n)
{
    node2 *temp = createnode2(n);
    root = unionbinomial2(root, temp);
}
//------Binomial ends
//------Binary starts
struct minheap
{
    ll size;
    vector<pair<ll, ll>> heap;
    ll cap;
};
void minheapify1(minheap *h, ll n)
{
    ll l = 2 * n + 1, r = 2 * n + 2, s = n;
    if (h->heap[l].first < h->heap[n].first && l < h->size)
        s = l;
    if (r < h->size && h->heap[r].first < h->heap[s].first)
        s = r;
    if (s != n)
    {
        swap(h->heap[n], h->heap[s]);
        swap(mp[h->heap[n].second], mp[h->heap[s].second]);
        minheapify1(h, s);
    }
}
void insert1(minheap *h, pair<ll, ll> n)
{
    h->size++;
    ll i = h->size - 1;
    mp[n.second] = h->size - 1;
    h->heap[i] = n;
    while (i != 0 && h->heap[(i - 1) / 2].first > h->heap[(i)].first)
    {
        swap(h->heap[(i - 1) / 2], h->heap[i]);
        swap(mp[h->heap[i].second], mp[h->heap[(i - 1) / 2].second]);
        i = (i - 1) / 2;
    }
}
void decreasekey2(minheap *h, ll i, ll j)
{
    h->heap[mp[i]] = {j, i};
    int temp = mp[i];
    while (temp && (h->heap[temp].first < h->heap[(temp - 1) / 2].first))
    {
        swap(h->heap[temp], h->heap[(temp - 1) / 2]);
        swap(mp[h->heap[temp].second], mp[h->heap[(temp - 1) / 2].second]);
        temp = (temp - 1) / 2;
    }
}
pair<ll, ll> extractmin1(minheap *h)
{
    pair<int, int> pai = {0, 0};
    if (h->size == 1)
    {
        pai = h->heap[0];
        h->size--;
        mp.clear();
    }
    else
    {
        pai = h->heap[0];
        h->size--;
        swap(h->heap[0], h->heap[h->size]);
        swap(mp[h->heap[0].second], mp[h->heap[h->size].second]);
        minheapify1(h, 0);
    }
    return pai;
}
//------Binary ends
bool bellman(ll node, ll n)
{
    h[node] = 0;
    queue<ll> q;
    q.push(node);
    vector<ll> ispresent(20005, 0), count(20005, 0);
    ispresent[node] = 1;
    while (!q.empty())
    {
        ll temp = q.front();
        q.pop();
        ispresent[temp] = 0;
        for (ll i = 0; i < adj[temp].size(); i++)
        {
            ll k1 = adj[temp][i].first;
            ll w = adj[temp][i].second;
            if (h[k1] > h[temp] + w)
            {
                h[k1] = h[temp] + w;
                if (ispresent[k1] == 0)
                {
                    ispresent[k1] = 1;
                    q.push(k1);
                    if (count[k1] >= n)
                        return 0;
                    count[k1]++;
                }
            }
        }
    }
    return 1;
}
void dijkstrabinary(ll node, ll n)
{
    minheap h;
    vector<pair<ll, ll>> v(2005);
    h.cap = 2005;
    h.size = 0;
    h.heap = v;
    int vis[n + 1] = {0};
    dist[node] = 0;
    vis[node] = 1;
    insert1(&h, {0, node});
    while (h.size > 0)
    {
        pair<ll, ll> it = extractmin1(&h);
        ll temp1 = it.second;
        ll temp2 = it.first;
        vis[temp1] = 0;
        for (auto x : adj[temp1])
        {
            if (x.second + temp2 < dist[x.first])
            {
                dist[x.first] = x.second + temp2;
                if (vis[x.first] == 0)
                {
                    insert1(&h, {dist[x.first], x.first});
                }
                else
                    decreasekey2(&h, x.first, dist[x.first]);
                vis[x.first] = 1;
            }
        }
    }
}
void dijkstraarray(ll node, ll n)
{
    vector<pair<ll, ll>> s;
    s.push_back({0, node});
    dist[node] = 0;
    while (!s.empty())
    {
        ll count = 0, min_count = 0;
        ll min_ele = pinf;
        pair<ll, ll> ans;
        for (auto it : s)
        {
            if (it.first < min_ele)
            {
                ans = it;
                min_count = count;
                min_ele = it.first;
            }
            count++;
        }
        ll temp1 = ans.second;
        ll temp2 = ans.first;
        s.erase(s.begin() + min_count);
        for (auto x : adj[temp1])
        {
            if (x.second + temp2 < dist[x.first])
            {
                dist[x.first] = x.second + temp2;
                s.push_back({dist[x.first], x.first});
            }
        }
    }
}
void dijkstrabinomial(ll node, ll n)
{
    dist[node] = 0;
    insert2({0, node});
    ll count = 0;
    while (root)
    {
        count++;
        node2 *it = findminimumnode2(root);
        if (it == NULL)
        {
            it = root;
        }
        ll temp1 = (it->val).second;
        ll temp2 = (it->val).first;
        if (root->sibling == NULL && (root->degree == 0))
            root = NULL;
        else
            root = extractmin2(root);
        for (auto x : adj[temp1])
        {
            if (x.second + temp2 < dist[x.first])
            {
                dist[x.first] = x.second + temp2;
                insert2({dist[x.first], x.first});
            }
        }
    }
}
void dijkstrafibonacci(ll node, ll n)
{
    dist[node] = 0;
    insertinfibonacci({0, node});
    ll count = 0;
    while (minnode)
    {
        count++;
        ll temp1 = (minnode->val).second;
        ll temp2 = (minnode->val).first;
        extractmin(minnode);
        for (auto x : adj[temp1])
        {
            if (x.second + temp2 < dist[x.first])
            {
                dist[x.first] = x.second + temp2;
                insertinfibonacci({dist[x.first], x.first});
            }
        }
    }
}
signed main(int argc, char *argv[])
{
    ll t;
    cin >> t;
    vector<double> times;
    while (t--)
    {
        clock_t timer;
        timer = clock();
        ll n, d, i, j;
        cin >> n >> d;
        if (n == 1)
        {
            cin >> d;
            cout << "0\n";
            continue;
        }
        for (i = 1; i <= n; i++)
        {
            adj[0].push_back({i, 0});
            for (j = 1; j <= n; j++)
            {
                ll x;
                cin >> x;
                if (x == inf)
                    continue;
                if (i == j)
                    continue;
                adj[i].push_back({j, x});
            }
        }
        for (ll i = 1; i <= n; i++)
            h[i] = pinf;
        ll z = bellman(0, n + 1);
        if (z == 0)
        {
            cout << -1 << '\n';
            goto label;
        }
        for (i = 1; i <= n; i++)
            for (auto it : adj[i])
                it.second += h[i] - h[it.first];
        for (ll i = 0; i <= n; i++)
        {
            dist[i] = inf;
        }
        for (i = 1; i <= n; i++)
        {
            if (*argv[1] == '4')
                dijkstrafibonacci(i, n);
            else if (*argv[1] == '3')
                dijkstrabinomial(i, n);
            else if (*argv[1] == '2')
                dijkstrabinary(i, n);
            else
                dijkstraarray(i, n);
            root = NULL;
            for (ll j = 1; j <= n; j++)
            {
                cout << dist[j] << " ";
                dist[j] = inf;
            }
            cout << '\n';
        }
    label:
        root = NULL;
        for (i = 0; i <= n; i++)
            adj[i].clear();
        sizefib = 0;
        mp.clear();
        timer = clock() - timer;
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        times.push_back(time_taken);
    }
    for (double i : times)
    {
        cout << i << " ";
    }
    return 0;
}