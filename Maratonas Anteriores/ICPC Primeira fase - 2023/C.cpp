#include <iostream>
#include <vector>
#include <unordered_map>


void dfs(
    int node,
    std::vector<int>& v,
    std::unordered_map<int, std::vector<int>>& adj_list,
    std::vector<int>& ans,
    std::vector<bool>& visited,
    std::vector<int>& lis
) {
    visited[node] = true;
    int n = lis.back();
    if (v[node] > lis.back()) {

        lis.push_back(v[node]);
        ans[node - 1] = lis.size();

        for (auto& child : adj_list[node]) {
            if (visited[child])
                continue;

            dfs(child, v, adj_list, ans, visited, lis);
        }
        lis.pop_back();
    }
    else {
        int idx = std::lower_bound(lis.begin(), lis.end(), v[node]) - lis.begin();
        int value = lis[idx];

        ans[node - 1] = lis.size();
        lis[idx] = v[node];
        for (auto& child : adj_list[node]) {
            if (visited[child])
                continue;

            dfs(child, v, adj_list, ans, visited, lis);
        }
        lis[idx] = value;
    }
}

void solution(
    std::vector<int>& v,
    std::unordered_map<int, std::vector<int>>& adj_list,
    std::vector<int>& ans
) {
    std::vector<bool> visited(v.size(), false);
    std::vector<int> lis;

    visited[0] = true;
    lis.push_back(v[0]);
    for (auto& child : adj_list[0])
        dfs(child, v, adj_list, ans, visited, lis);
}

int main() {
    int n;
    std::vector<int> v, ans;
    std::unordered_map<int, std::vector<int>> adj_list;

    while (std::cin >> n) {
        v.resize(n);
        ans.resize(n - 1);
        adj_list.reserve(n);

        // Lê input
        for (int i = 1; i < n; i++) {
            int j;
            std::cin >> j;
            j--;
            adj_list[i].push_back(j);
            adj_list[j].push_back(i);
        }
        for (int i = 0; i < n; i++)
            std::cin >> v[i];

        // Resolve o problema
        solution(v, adj_list, ans);

        // Imprime a resposta
        std::cout << ans[0];
        for (int i = 1; i < n - 1; i++) {
            std::cout << " " << ans[i];
        }
        std::cout << std::endl;
    }

    return 0;
}