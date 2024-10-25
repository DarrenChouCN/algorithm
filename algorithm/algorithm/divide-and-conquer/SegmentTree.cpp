#include <vector>

using namespace std;

class SegmentTree {

private:
	int MAXN;
	vector<int> arr;
	vector<int> sum;
	vector<int> lazy;
	vector<int> change;
	vector<bool> update;

	void pushUp(int rt) {
		sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	}

	void pushDown(int rt, int ln, int rn) {
		if (update[rt]) {
			update[rt << 1] = true;
			update[rt << 1 | 1] = true;

			change[rt << 1] = change[rt];
			change[rt << 1 | 1] = change[rt];

			lazy[rt << 1] = 0;
			lazy[rt << 1 | 1] = 0;

			sum[rt << 1] = change[rt] * ln;
			sum[rt << 1 | 1] = change[rt] * rn;

			update[rt] = false;
		}

		if (lazy[rt] != 0) {
			lazy[rt << 1] += lazy[rt];
			lazy[rt << 1 | 1] += lazy[rt];

			sum[rt << 1] += lazy[rt] * ln;
			sum[rt << 1 | 1] += lazy[rt] * rn;

			lazy[rt] = 0;
		}
	}

public:
	SegmentTree(const vector<int>& origin) {
		MAXN = origin.size() + 1;
		arr.resize(MAXN);
		for (int i = 1; i < MAXN; i++)
			arr[i] = origin[i - 1];

		sum.resize(MAXN << 2);
		lazy.resize(MAXN << 2, 0);
		change.resize(MAXN << 2);
		update.resize(MAXN << 2, false);
	}

	void build(int l, int r, int rt) {
		if (l == r) {
			sum[rt] = arr[l];
			return;
		}

		int mid = (l + r) >> 1;
		build(l, mid, rt << 1);
		build(mid + 1, r, rt << 1 | 1);
		pushUp(rt);
	}

	void updateRange(int L, int R, int C, int l, int r, int rt) {
		if (L <= l && r < R) {
			update[rt] = true;
			change[rt] = C;
			sum[rt] = C * (r - 1 + 1);
			lazy[rt] = 0;
			return;
		}
		int mid = (l + r) >> 1;
		pushDown(rt, mid - l + 1, r - mid);

		if (L <= mid)
			updateRange(L, R, C, l, mid, rt << 1);
		if (R > mid)
			updateRange(L, R, C, mid + 1, r, rt << 1 | 1);

		pushUp(rt);
	}

	void addRange(int L, int R, int C, int l, int r, int rt) {
		if (L <= l && r <= R) {
			sum[rt] += C * (r - l + 1);
			lazy[rt] += C;
			return;
		}
		int mid = (l + r) >> 1;
		pushDown(rt, mid - l + 1, r - mid);
		if (L <= mid) {
			addRange(L, R, C, l, mid, rt << 1);
		}
		if (R > mid) {
			addRange(L, R, C, mid + 1, r, rt << 1 | 1);
		}
		pushUp(rt);
	}

	long long queryRange(int L, int R, int l, int r, int rt) {
		if (L <= l && r <= R) {
			return sum[rt];
		}
		int mid = (l + r) >> 1;
		pushDown(rt, mid - l + 1, r - mid);
		long long ans = 0;
		if (L <= mid) {
			ans += queryRange(L, R, l, mid, rt << 1);
		}
		if (R > mid) {
			ans += queryRange(L, R, mid + 1, r, rt << 1 | 1);
		}
		return ans;
	}

};