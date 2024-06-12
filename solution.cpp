#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <climits>
#include <queue>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void BFS(vector<int> adj[], vector<int> &par, vector<int> &dist, vector<bool> visited, int n, int start)
{
    for (int i = 0; i < n; i++)
    {
        par[i] = -1;
        dist[i] = -1;
    }
    queue<int> q;
    dist[start] = 0;
    q.push(start); // Initialize Q
    visited[start] = true;
    while (!q.empty())
    { // Process all vertices on Q
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
                par[v] = u;
            }
        }
    }
}

bool canBeFired(vector<string> grid, int sourceR, int sourceC, int targetR, int targetC)
{

    if (sourceR == targetR)
    {
        bool flag = false;
        for (int i = min(sourceC, targetC); i <= max(sourceC, targetC); i++)
        {
            if (grid[sourceR][i] == '#')
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            // cerr << sourceR << " " << sourceC << " " << targetR << " " << targetC << endl;
            return true;
        }
    }

    if (sourceC == targetC)
    {
        bool flag = false;
        for (int i = min(sourceR, targetR); i <= max(sourceR, targetR); i++)
        {
            if (grid[i][sourceC] == '#')
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            // cerr << sourceR << " " << sourceC << " " << targetR << " " << targetC << endl;
            return true;
        }
    }
    return false;
}

bool canKillEnemies(vector<string> grid, int r, int c, vector<pair<int, int>> visible_minions)
{
    // map<pair<int, int>, bool> my_minions;
    for (int i = 0; i < 5; i++)
    {
        if (visible_minions[i].first != -1)
        {
            if (canBeFired(grid, r, c, visible_minions[i].first, visible_minions[i].second))
            {
                return true;
            }
        }
    }
    return false;
}

bool isSafeToFire(vector<string> grid, int id, vector<pair<int, int>> minions)
{
    // map<pair<int, int>, bool> my_minions;
    for (int i = 0; i < 5; i++)
    {
        if (minions[i].first != -1 && id != i)
        {
            if (canBeFired(grid, minions[id].first, minions[id].second, minions[i].first, minions[i].second))
            {
                return false;
            }
        }
    }
    return true;
}

pair<int, int> bestCell(vector<string> grid, int id, vector<pair<int, int>> minions, vector<vector<bool>> visible_coins)
{
    int r = minions[id].first;
    int c = minions[id].second;
    int left = 0, right = 0, up = 0, down = 0;
    pair<int, int> leftEnd = {-1, -1}, rightEnd = {-1, -1}, upEnd = {-1, -1}, downEnd = {-1, -1};
    for (int i = c; grid[r][i] == '.'; i++)
    {
        if (visible_coins[r][i])
        {
            right++;
            rightEnd = {r, i};
        }
    }
    for (int i = c; grid[r][i] == '.'; i--)
    {
        if (visible_coins[r][i])
        {
            left++;
            leftEnd = {r, i};
        }
    }
    for (int i = r; grid[i][c] == '.'; i++)
    {
        if (visible_coins[i][c])
        {
            down++;
            downEnd = {i, c};
        }
    }
    for (int i = r; grid[i][c] == '.'; i--)
    {
        if (visible_coins[i][c])
        {
            up++;
            upEnd = {i, c};
        }
    }
    if (left > right && left > up && left > down)
    {
        return leftEnd;
    }
    else if (right > left && right > up && right > down)
    {
        return rightEnd;
    }
    else if (down > left && down > up && down > right)
    {
        return downEnd;
    }
    else
    {
        // cerr << "ERROR" << up << endl;
        return upEnd;
    }
}
int main()
{
    // ios::sync_with_stdio(0), cin.tie(nullptr);
    srand(time(NULL));
    int height;
    int width;
    cin >> height >> width;
    cin.ignore();
    vector<string> grid(height);
    for (int i = 0; i < height; i++)
    {
        string row;
        cin >> row;
        grid[i] = row;
        cin.ignore();
    }
    int n = height * width;
    vector<int> adj[n];
    vector<bool> visited(n, false);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int idx = width * i + j;
            if (j > 0)
            {
                adj[idx].push_back(idx - 1);
            }
            if (j < width - 1)
            {
                adj[idx].push_back(idx + 1);
            }
            if (i > 0)
            {
                adj[idx].push_back(idx - height);
            }
            if (i < height - 1)
            {
                adj[idx].push_back(idx + height);
            }
            if (grid[i][j] == '#')
            {
                visited[idx] = true;
            }
        }
    }
    int matrix[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = -1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        vector<int> dist(n);
        vector<int> par(n);
        BFS(adj, par, dist, visited, n, i);
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = dist[j];
        }
    }
    int my_flag_base_r;
    int my_flag_base_c;
    cin >> my_flag_base_r >> my_flag_base_c;
    cin.ignore();
    int opponent_flag_base_r;
    int opponent_flag_base_c;
    cin >> opponent_flag_base_r >> opponent_flag_base_c;
    cin.ignore();
    string fire_name;
    int fire_price;
    int fire_damage;
    cin >> fire_name >> fire_price >> fire_damage;
    cin.ignore();
    string freeze_name;
    int freeze_price;
    int freeze_damage;
    cin >> freeze_name >> freeze_price >> freeze_damage;
    cin.ignore();
    string mine_name;
    int mine_price;
    int mine_damage;
    cin >> mine_name >> mine_price >> mine_damage;
    cin.ignore();

    // game loop
    bool chasing = false;
    // map<int, int> chased;
    // map<int, int> running;
    vector<pair<int, int>> get_coin(5, {-1, -1});
    int captain = -1;
    int vice_captain = -1;
    int vice_captain_2 = -1;
    int power = 0;
    while (1)
    {
        int my_score;
        int opponent_score;
        cin >> my_score >> opponent_score;
        cin.ignore();
        int my_flag_pos_r;
        int my_flag_pos_c;
        int my_flag_carrier;
        cin >> my_flag_pos_r >> my_flag_pos_c >> my_flag_carrier;
        cin.ignore();
        int opponent_flag_pos_r;
        int opponent_flag_pos_c;
        int opponent_flag_carrier;
        cin >> opponent_flag_pos_r >> opponent_flag_pos_c >> opponent_flag_carrier;
        cin.ignore();
        int my_alive_minion_cnt;
        cin >> my_alive_minion_cnt;
        cin.ignore();
        vector<pair<int, int>> minions(5, {-1, -1});

        int cap_idx = -1, min_dist = INT_MAX;
        for (int i = 0; i < my_alive_minion_cnt; i++)
        {
            int id;
            int pos_r;
            int pos_c;
            int health;
            int timeout;
            // cerr << id << endl;
            cin >> id >> pos_r >> pos_c >> health >> timeout;
            cin.ignore();
            minions[id] = {pos_r, pos_c};
            int idx1 = width * opponent_flag_pos_r + opponent_flag_base_c;
            int idx2 = width * pos_r + pos_c;
            int d = matrix[idx1][idx2];
            if (d != -1 && d < min_dist)
            {
                min_dist = d;
                min_dist = i;
            }
            // int tmp = abs(opponent_flag_pos_r - pos_r) + abs(opponent_flag_base_c - pos_c);
            if (d < min_dist)
            {
                cap_idx = id;
            }
        }
        if (captain == -1 || minions[captain].first == -1)
        {
            captain = cap_idx;
        }

        int vice_idx = -1, vice_dist = INT_MAX;
        for (int i = 0; i < 5; i++)
        {
            if (minions[i].first != -1)
            {
                if (i != captain)
                {
                    int idx1 = width * my_flag_pos_r + my_flag_pos_c;
                    int idx2 = width * minions[i].first + minions[i].second;
                    int d = matrix[idx1][idx2];
                    if (d != -1 && d < vice_dist)
                    {
                        vice_dist = d;
                        vice_idx = i;
                    }
                }
            }
        }
        int visible_minion_cnt;
        cin >> visible_minion_cnt;
        cin.ignore();
        vector<pair<int, int>> visible_minions(5, {-1, -1});
        for (int i = 0; i < visible_minion_cnt; i++)
        {
            int id;
            int pos_r;
            int pos_c;
            int health;
            int timeout;
            cin >> id >> pos_r >> pos_c >> health >> timeout;
            cin.ignore();
            visible_minions[id] = {pos_r, pos_c};
        }
        int visible_coin_cnt;
        cin >> visible_coin_cnt;
        cin.ignore();
        vector<pair<int, int>> coins(visible_coin_cnt);
        vector<vector<bool>> visible_coins(height, vector<bool>(width, false));
        for (int i = 0; i < visible_coin_cnt; i++)
        {
            int pos_r;
            int pos_c;
            cin >> pos_r >> pos_c;
            coins[i] = {pos_r, pos_c};
            visible_coins[pos_r][pos_c] = true;
            cin.ignore();
        }
        bool isPrinted = false;
        cerr << "START" << endl;
        int fire = 0;
        if (captain != -1 && minions[captain].first == -1)
        {
            captain = -1;
            vice_captain = -1;
            vice_captain_2 = -1;
        }
        if (vice_captain != -1 && minions[vice_captain].first == -1)
        {
            vice_captain = -1;
            vice_captain_2 = -1;
        }
        if (vice_captain_2 != -1 && minions[vice_captain_2].first == -1)
        {
            vice_captain_2 = -1;
        }
        for (int i = 0; i < 5; i++)
        {
            if (minions[i].first == -1)
            {
                continue;
            }
            if (isPrinted)
            {
                cout << " | ";
            }
            int id = i;
            if (captain == -1 || minions[captain].first == -1)
            {
                captain = id;
            }
            else if (vice_captain == -1 || minions[vice_captain].first == -1)
            {
                if (id != captain)
                    vice_captain = id;
            }
            else if (vice_captain_2 == -1 || minions[vice_captain_2].first == -1)
            {
                if (id != vice_captain)
                    vice_captain_2 = id;
            }
            if (id == captain)
            {
                if (my_flag_carrier != -1 && fire_price <= my_score && canBeFired(grid, minions[id].first, minions[id].second, my_flag_pos_r, my_flag_pos_c) && isSafeToFire(grid, id, minions))
                {
                    cout << "FIRE " << id;
                }
                // else if (fire_price <= my_score && isSafeToFire(grid, id, minions) && canKillEnemies(grid, minions[id].first, minions[id].second, visible_minions))
                // {
                //     cout << "FIRE " << id;
                //     break;
                // }
                else if (opponent_flag_carrier != captain)
                {
                    cout << "MOVE " << captain << " " << opponent_flag_pos_r << " " << opponent_flag_pos_c;
                }
                else
                {
                    cout << "MOVE " << captain << " " << my_flag_base_r << " " << my_flag_base_c;
                }
            }
            else if (id == vice_captain)
            {
                if (my_flag_carrier != -1)
                {
                    if (my_flag_carrier != -1 && fire_price <= my_score && canBeFired(grid, minions[id].first, minions[id].second, my_flag_pos_r, my_flag_pos_c) && isSafeToFire(grid, id, minions))
                    {
                        cout << "FIRE " << id;
                    }
                    else
                    {
                        cout << "MOVE " << id << " " << my_flag_pos_r << " " << my_flag_pos_c;
                    }
                }
                else
                {
                    if (fire_price <= my_score && isSafeToFire(grid, id, minions) && canKillEnemies(grid, minions[id].first, minions[id].second, visible_minions))
                    {
                        cout << "FIRE " << id;
                        break;
                    }
                    else if (get_coin[id].first == -1 || !visible_coins[get_coin[id].first][get_coin[id].second])
                    {
                        if (visible_coin_cnt != 0)
                        {
                            get_coin[id] = bestCell(grid, id, minions, visible_coins);
                            cerr << get_coin[id].first << " " << get_coin[id].second << endl;
                        }
                    }
                    if (get_coin[id].first != -1)
                    {
                        cout << "MOVE " << id << " " << get_coin[id].first << " " << get_coin[id].second;
                    }
                    else
                    {
                        cout << "MOVE " << id << " " << opponent_flag_base_r << " " << opponent_flag_base_c;
                    }
                }
            }
            else if (id == vice_captain_2)
            {
                // if (my_flag_carrier != -1 && fire_price <= my_score)
                // {
                //     if (abs(minions[id].first - my_flag_pos_r) + abs(minions[id].second - my_flag_pos_c) < 3 && ((minions[id].first == my_flag_pos_r) || (minions[id].second == my_flag_pos_c)))
                //     {
                //         cout << "FIRE " << id;
                //     }
                //     else
                //     {
                //         cout << "MOVE " << id << " " << opponent_flag_base_r << " " << opponent_flag_base_r;
                //     }
                // }
                // else
                {
                    if (my_flag_carrier != -1 && fire_price <= my_score && canBeFired(grid, minions[id].first, minions[id].second, my_flag_pos_r, my_flag_pos_c) && isSafeToFire(grid, id, minions))
                    {
                        cout << "FIRE " << id;
                        break;
                    }
                    // else if (fire_price <= my_score && isSafeToFire(grid, id, minions) && canKillEnemies(grid, minions[id].first, minions[id].second, visible_minions))
                    // {
                    //     cout << "FIRE " << id;
                    //     break;
                    // }
                    else if (get_coin[id].first == -1 || !visible_coins[get_coin[id].first][get_coin[id].second])
                    {
                        if (visible_coin_cnt != 0)
                        {
                            get_coin[id] = bestCell(grid, id, minions, visible_coins);
                            cerr << get_coin[id].first << " " << get_coin[id].second << endl;
                        }
                    }
                    if (get_coin[id].first != -1)
                    {
                        cout << "MOVE " << id << " " << get_coin[id].first << " " << get_coin[id].second;
                    }
                    else
                    {
                        cout << "MOVE " << id << " " << opponent_flag_base_r << " " << opponent_flag_base_c;
                    }
                }
            }
            else
            {
                // if (my_flag_carrier != -1 && fire_price <= my_score && abs(my_flag_pos_r - opponent_flag_base_r) + abs(my_flag_pos_c - opponent_flag_base_c) < width)
                // {
                //     if (abs(minions[id].first - my_flag_pos_r) + abs(minions[id].second - my_flag_pos_c) < 3 && ((minions[id].first == my_flag_pos_r) || (minions[id].second == my_flag_pos_c)))
                //     {
                //         cout << "FIRE " << id;
                //     }
                //     else
                //     {
                //         cout << "MOVE " << id << " " << opponent_flag_base_r << " " << opponent_flag_base_c;
                //     }
                // }
                // else if (my_flag_carrier != -1 && fire_price <= my_score && abs(minions[id].first - my_flag_pos_r) + abs(minions[id].second - my_flag_pos_c) < 2)
                // {
                //     cout << "FIRE " << id;
                // }
                // else
                {
                    if (my_flag_carrier != -1 && fire_price <= my_score && canBeFired(grid, minions[id].first, minions[id].second, my_flag_pos_r, my_flag_pos_c) && isSafeToFire(grid, id, minions))
                    {
                        cout << "FIRE " << id;
                        break;
                    }
                    // else if (fire_price <= my_score && isSafeToFire(grid, id, minions) && canKillEnemies(grid, minions[id].first, minions[id].second, visible_minions))
                    // {
                    //     cout << "FIRE " << id;
                    //     break;
                    // }
                    else if (get_coin[id].first == -1 || !visible_coins[get_coin[id].first][get_coin[id].second])
                    {
                        if (visible_coin_cnt != 0)
                        {
                            get_coin[id] = bestCell(grid, id, minions, visible_coins);
                        }
                    }
                    if (get_coin[id].first != -1)
                    {
                        cout << "MOVE " << id << " " << get_coin[id].first << " " << get_coin[id].second;
                    }
                    else
                    {
                        cout << "MOVE " << id << " " << opponent_flag_base_r << " " << opponent_flag_base_c;
                    }
                }
            }
            if (!isPrinted)
            {
                isPrinted = true;
            }
        }
        cout << endl;
    }
}
