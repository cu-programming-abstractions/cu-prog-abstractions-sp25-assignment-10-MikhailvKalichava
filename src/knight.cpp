#include "knight.h"
#include <algorithm>
#include <cmath>

using namespace std;


const vector<pair<int, int>> knightDirs = {
    {+2, +1}, {+2, -1}, {-2, +1}, {-2, -1},
    {+1, +2}, {+1, -2}, {-1, +2}, {-1, -2}
};



int minKnightMoves(const Pos& start, const Pos& target) {
    if (start == target) return 0;

    queue<pair<Pos, int>> q;
    unordered_set<Pos, PosHash> visited;

    q.push({start, 0});
    visited.insert(start);

    while (!q.empty()) {
        auto [curr, dist] = q.front();
        q.pop();

        for (const auto& [dr, dc] : knightDirs) {
            Pos next = {curr.row + dr, curr.col + dc};
            if (next == target) return dist + 1;

            if (visited.count(next) == 0) {
                visited.insert(next);
                q.push({next, dist + 1});
            }
        }
    }

    return -1;
}

vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    if (start == target) return {start};

    queue<Pos> q;
    unordered_map<Pos, Pos, PosHash> parent;
    unordered_set<Pos, PosHash> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {

        Pos curr = q.front();
        q.pop();

        for (const auto& [dr, dc] : knightDirs) {
            Pos next = {curr.row + dr, curr.col + dc};

            if (visited.count(next)) continue;

            parent[next] = curr;
            visited.insert(next);

            if (next == target) {

                vector<Pos> path;
                for (Pos p = target; p != start; p = parent[p]) {
                    path.push_back(p);

                }

                path.push_back(start);
                reverse(path.begin(), path.end());
                return path;
            }

            q.push(next);
        }
    }
    
    return {};
}

bool isValidPosition(const Pos& pos, int boardSize) {

    if (boardSize == -1) return true;

    return pos.row >= 0 && pos.row < boardSize && pos.col >= 0 && pos.col < boardSize;
}
