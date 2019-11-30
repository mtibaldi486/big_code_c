#include "../inc/cool.h"

char *strjoin(char *s1, char *s2)
{
  int		len1;
	int		len2;
	int		i;
	int		j;
	char		*newstr;

	i = 0;
	j = 0;
	len1 = strlen((char *)s1);
	len2 = strlen((char *)s2);
	if (!(newstr = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	while (i < len1)
	{
		newstr[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		newstr[i++] = s2[j];
		j++;
	}
	free(s1);
	newstr[i] = 0;
	return (newstr);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t			i;
	size_t			srclen;

	if (*s2 == 0)
		return ((char *)s1);
	i = 0;
	srclen = strlen((char *)s2);
	while (i < len && s1[i] && len >= srclen + i)
	{
		if (s1[i] == s2[0] &&
			memcmp((const void *)s1 + i, (const void *)s2, srclen) == 0)
		{
			return ((char *)s1 + i);
		}
		i++;
	}
	return (NULL);
}
