#include <unistd.h>

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int		c_in_s(char c, char *s, int end)
{
	int i;

	i = 0;
	while (s && s[i] && i < end)
		if (s[i++] == c)
			return (1);
	return (0);
}

void	check_str_union(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (c_in_s(s1[i], s1, i) == 0)
			write(1, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (c_in_s(s2[i], s1, ft_strlen(s1)) == 0 && c_in_s(s2[i], s2, i) == 0)
			write(1, &s2[i], 1);
		i++;
	}
}

int main(int argc, char *argv[])
{
	char c = '\n';
	if (argc == 3)
		check_str_union(argv[1], argv[2]);
	write(1, &c, 1);
	return (0);
}
