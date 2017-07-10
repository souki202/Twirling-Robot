#include <iostream>
#include <climits>
#include <queue>
#include <functional>
#include <cstring>
int field[30][30] = { 0 };
int m[4][30][30]; //[å¸Ç´][y][x] = ç≈è¨ÉRÉXÉg
int costs[4] = { 0 };
int dx[] = { 1, 0, -1, 0, 1, 0, -1, 0 }, dy[] = {0, 1, 0, -1, 0, 1, 0, -1 };

struct Node{
	int x, y, cost = 0, d;
	bool operator < (const Node& rhs) const {
		return cost < rhs.cost;
	}
	bool operator < (Node&& rhs) const {
		return cost < rhs.cost;
	}
	bool operator > (const Node& rhs) const {
		return cost > rhs.cost;
	}
	bool operator > (Node&& rhs) const {
		return cost > rhs.cost;
	}
};

int main() {
	int w, h;
	while (std::cin >> w >> h && (w || h)) {
		std::memset(m, 0x7f, sizeof(int) * 4 * 30 * 30);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				std::cin >> field[i][j];
			}
		}
		for (int i = 0; i < 4; i++) std::cin >> costs[i];

		std::priority_queue<Node, std::vector<Node>, std::greater<Node>> q;
		q.push({0, 0, 0, 0});
		bool isOk = false;
		int minCost = INT_MAX;
		while (!q.empty() && !isOk) {
			Node node = q.top(); q.pop();
			if (node.x == w - 1 && node.y == h - 1) {
				isOk = true;
				minCost = node.cost;
			}

			for (int i = 0; i < 4; i++) {
				Node next = node;
				if (i == 1) next.d++;
				else if (i == 2) next.d += 2;
				else if (i == 3) next.d--;
				if (next.d < 0) next.d = 4 + next.d;
				else if (next.d >= 4) next.d = next.d - 4;

				next.x += dx[next.d];
				next.y += dy[next.d];
				if (field[node.y][node.x] != i) next.cost += costs[i];

				if (next.x < 0 || next.x >= w || next.y < 0 || next.y >= h) continue;
				if (m[next.d][next.y][next.x] <= next.cost) continue;
				m[next.d][next.y][next.x] = next.cost;
				q.push(next);
			}
		}
		std::cout << minCost << std::endl;
	}
	return 0;
}