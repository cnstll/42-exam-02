#include "./get_next_line.h"
#include <stdio.h>

static int c_in_s (char c, char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
			i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

static int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char *ft_calloc(int len, int size)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(len * size);
	if (!ret)
		return (NULL);
	while (i < len * size)
		ret[i++] = '\0';
	return (ret);
}

static char *str_append(char *str, char c)
{
	int len;
	int	i;
	char *r;

	i = 0;
	len = ft_strlen(str);
	r = ft_calloc(sizeof(char), (len + 2));
	while (i < len)
	{
		r[i] = str[i];
		i++;
	}
	r[i] = c;
	if (str)
		free(str);
	return (r);
}

static char *ft_strndup(char *str, int start, int len)
{
	int i;
	char *dup;

	i = 0;
	dup = ft_calloc(sizeof(char), len + 1);
	while (str && str[start] && i < len)
	{
		dup[i] = str[start];
		i++;
		start++;
	}
	return (dup);
}

int get_next_line(char **line)
{
	char buf[1];
	static char *leftover;
	char *tmp;
	int n;

	if (!line)
		return (-1);
	leftover = ft_calloc(1, sizeof(char));
	if (!leftover)
		return (-1);
	while(read(0, buf, 1) > 0)
	{
		leftover = str_append(leftover, buf[0]);
		if (buf[0] == '\n')
			break ;
	}
	n = c_in_s('\n', leftover);
	if (n >= 0)
	{
		*line = ft_strndup(leftover, 0, n);
		free(leftover);
		return (1);
	}
	*line = ft_calloc(1, sizeof(char));
	free(leftover);
	return (0);
}
