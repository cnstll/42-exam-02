#include <unistd.h>

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int c_in_s(char c, char *s, int max)
{
	int i;

	i = -1;
	while (s && s[++i] && i < max)
		if (s[i] == c)
			return (1);
	return (0);
}

static void ft_inter(char *s1, char *s2)
{
	int i = -1;

	while (s1 && s1[++i])
		if (c_in_s(s1[i], s2, ft_strlen(s2)) == 1 && c_in_s(s1[i], s1, i) == 0)
			write(1, &s1[i], 1);
}

int main(int argc, char *argv[])
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
}
