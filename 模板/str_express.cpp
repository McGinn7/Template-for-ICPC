bool _min(char a, char b) { // 最小表示
	return a > b;
}
bool _max(char a, char b) { // 最大表示
	return a < b;
}
int str_express(char s[], bool (*cmp)(char, char)) {
	int n = strlen(s);
	int i = 0, j = 1, k;
	while (i < n && j < n) {
		k = 0;
		while (k < n && s[(i + k) % n] == s[(j + k) % n])
			++k;
		if (k >= n)
			break;
		if (cmp(s[(i + k) % n], s[(j + k) % n]))
			i = max(i + k + 1, j + 1);
		else
			j = max(j + k + 1, i + 1);
	}
	return min(i, j);
}
