#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<json-c/json.h>

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

void read_file(FILE *pf, char **str)
{
	char  buff[1024];

  *str = calloc(1, 1);
  if (ftell(pf))
    fseek(pf, 0, SEEK_SET);
  while (fread(buff, 1023, 1, pf), !feof(pf))
  {
    buff[1023] = 0;
    *str = strjoin(*str, buff);
  }
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

char *parse_str(char *str)
{
  char *new;
  char *add_del;
  long  del;
  int  i;

  i = 0;
  while (str[i])
  {
    if (str[i] == ',')
    {
      if (ft_strnstr(&str[i], "\"brands\"", 18))
      {
        str = strchr(str + i, ':');
        add_del = strchr(str + 2, '"');
        del = (add_del - str) - 2;
        new = calloc(1, del);
        strncpy(new, str + 2, del);
        *(new + del) = 0;
      }
    }
    i++;
  }
  free(add_del);
  return new;
}

int get_product_name(FILE *pf)
{
  char               *str;
  char                *res;

  read_file(pf, &str);

  res = parse_str(str);

  printf("res = '%s'\n", res);

  if (res)
    free (res);
  free(str);
  return (0);
}

int main(void)
{
  CURL        *curl;
  CURLcode    res;
  CURLcode    res2;
  FILE        *pf;

  if (!(pf = fopen("text.json", "r+")))
    return (0);
  curl = curl_easy_init();
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "http://fr.openfoodfacts.org/api/v0/product/5449000232311.json");
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    res2 = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)pf);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    else if (res2 != CURLE_OK)
      fprintf(stderr, "curl_easy_setopt() failed: %s\n",
            curl_easy_strerror(res));
    get_product_name(pf);
    /* always cleanup */
    fclose(pf);
    curl_easy_cleanup(curl);
  }
  return 0;
}
