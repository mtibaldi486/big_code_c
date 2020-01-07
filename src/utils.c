#include "../inc/cool.h"

/****************************************************************************/
/*                        FUNCTION FOR STRING                               */
/****************************************************************************/
char *strjoin(char *s1, char *s2, int f)
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
  if (f)
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

char  *mt_strccpy(char *s1, char *s2, char c)
{
  int i;

  i = 0;
  if (!s2)
    return (NULL);
  while (s2[i] && s2[i] != c)
  {
    s1[i] = s2[i];
    i++;
  }
  s1[i] = 0;
  return (s1);
}
/****************************************************************************/
/*                              ITOA                                        */
/****************************************************************************/
int		len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

const char	*ft_itoa(int nb)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

/****************************************************************************/
/*                              SPLIT                                       */
/****************************************************************************/

static void		free_split(char **strs, int k)
{
	int i;

	i = 0;
	while (i < k)
		free(strs[i]);
	free(strs);
}

static int		count_word(char const *str, char c)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] && str[i])
			nb++;
		while (str[i] != c && str[i])
			i++;
	}
	return (nb);
}

static char		*split_word(char *str, int deb, int fin)
{
	int		i;
	char	*res;
	int		tmp;

	tmp = deb;
	i = 0;
	if (!(res = malloc(sizeof(char) * (fin - deb + 1))))
		return (0);
	while (i < fin - deb)
	{
		res[i] = str[tmp];
		i++;
		tmp++;
	}
	res[i] = 0;
	return (res);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	if ((!s || !c))
		return (NULL);
	i = 0;
	k = -1;
	if (!(res = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1))))
		return (0);
	while (++k < count_word(s, c))
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			j = i;
		while (s[i] != c && s[i])
			i++;
		if (!(res[k] = split_word((char *)s, j, i)))
			free_split(res, k);
	}
	res[k] = 0;
	return (res);
}
