#include "../inc/cool.h"

/****************************************************************************/
/*                        FUNCTION FOR STRING                               */
/****************************************************************************/
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

char	*ft_itoa(int nb)
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
