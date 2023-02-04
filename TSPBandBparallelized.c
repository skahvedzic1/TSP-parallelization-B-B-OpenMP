#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

#define INF 10000000
#define MAX 20

int n = 20; 
int g[MAX][MAX]={{2147483647,84,87,16,87,63,27,69,68,94,38,74,47,44,61,2,41,7,24,15},
{84,2147483647,78,94,93,28,41,68,36,57,99,63,30,51,77,98,30,84,19,88},
{87,78,2147483647,36,50,91,27,30,30,12,25,71,14,88,69,3,32,20,46,57},
{16,94,36,2147483647,22,60,73,83,3,43,16,97,58,9,40,18,18,25,47,44},
{87,93,50,22,2147483647,64,37,31,23,30,71,82,25,77,13,93,98,29,52,92},
{63,28,91,60,64,2147483647,12,63,59,74,14,6,96,79,27,53,72,72,22,28},
{27,41,27,73,37,12,2147483647,24,70,22,27,26,83,89,87,57,82,33,56,66},
{69,68,30,83,31,63,24,2147483647,68,20,92,85,46,85,95,2,76,30,80,60},
{68,36,30,3,23,59,70,68,2147483647,85,81,28,15,4,40,81,10,4,89,37},
{94,57,12,43,30,74,22,20,85,2147483647,57,37,68,52,96,87,28,20,65,33},
{38,99,25,16,71,14,27,92,81,57,2147483647,6,35,55,71,42,68,71,29,52},
{74,63,71,97,82,6,26,85,28,37,6,2147483647,65,100,35,66,57,69,42,38},
{47,30,14,58,25,96,83,46,15,68,35,65,2147483647,33,79,90,98,9,51,29},
{44,51,88,9,77,79,89,85,4,52,55,100,33,2147483647,68,45,54,16,94,76},
{61,77,69,40,13,27,87,95,40,96,71,35,79,68,2147483647,20,87,41,1,8},
{2,98,3,18,93,53,57,2,81,87,42,66,90,45,20,2147483647,66,50,35,75},
{41,30,32,18,98,72,82,76,10,28,68,57,98,54,87,66,2147483647,97,65,22},
{7,84,20,25,29,72,33,30,4,20,71,69,9,16,41,50,97,2147483647,25,59},
{24,19,46,47,52,22,56,80,89,65,29,42,51,94,1,35,65,25,2147483647,96},
{15,88,57,44,92,28,66,60,37,33,52,38,29,76,8,75,22,59,96,2147483647}};

int f[MAX][1<<MAX], path[MAX][1<<MAX];

int tsp(int cur, int bitmask) {
    if (f[cur][bitmask] != -1)
        return f[cur][bitmask];
    if (bitmask == (1 << n) - 1)
        return g[cur][0];

    int ans = INF;
    #pragma omp parallel
    {
        int local_ans = INF;
        int local_path = -1;
        #pragma omp for
        for (int next = 0; next < n; next++) {
            if (next == cur || (bitmask & (1 << next)))
                continue;

            int new_cost = g[cur][next] + tsp(next, bitmask | (1 << next));
            if (new_cost < local_ans) {
                local_ans = new_cost;
                local_path = next;
            }
        }
        #pragma omp critical
        {
            if (local_ans < ans) {
                ans = local_ans;
                path[cur][bitmask] = local_path;
            }
        }
    }
    return f[cur][bitmask] = ans;
}

int main() {
    memset(f, -1, sizeof f);

    auto start = high_resolution_clock::now();

    omp_set_num_threads(1); // set number of threads
    int cost = tsp(0, 1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Minimum cost: " << cost << endl;
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}