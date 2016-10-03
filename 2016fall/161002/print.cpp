
int fa()
{
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			ans += arr[i] > arr[j];
		}
	}
	return ans;
}

int fb()
{
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		if (arr[i] < arr[i - 1])
			++ans;
	}
	return ans;
}

int fc()
{
	int ans = 1;
	lis[0] = 1;
	for (int i = 1; i < n; ++i) {
		lis[i] = 1;
		for (int j = 0; j < i; ++j) {
			if (arr[i] > arr[j])
				lis[i] = std::max(lis[i], lis[j] + 1);
		}
		ans = std::max(ans, lis[i]);
	}
	return ans;
}

int fd()
{
	int ans = 1;
	int bns = 1;
	for (int i = 1; i < n; ++i) {
		if (arr[i] > arr[i - 1])
			++bns;
		else
			bns = 1;
		ans = std::max(ans, bns);
	}
	return ans;
}

int fe()
{
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (arr[i] == i + 1)
			++ans;
	}
	return ans;
}


