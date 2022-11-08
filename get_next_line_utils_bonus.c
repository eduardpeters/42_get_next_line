/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epeters- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:27:56 by epeters-          #+#    #+#             */
/*   Updated: 2022/07/08 18:27:37 by epeters-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;
	size_t	substrlen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (len > (slen - start))
		substrlen = slen - start;
	else if (start > slen)
		substrlen = 0;
	else
		substrlen = len;
	str = (char *)(malloc(sizeof(*str) * (substrlen + 1)));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, (substrlen + 1));
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)(malloc(sizeof(*str) * (len_s1 + len_s2 + 1)));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len_s1 + 1);
	ft_strlcat(str, s2, (len_s1 + len_s2 + 1));
	return (str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;

	i = 0;
	j = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (j < (dstsize - 1) && dstsize > 0)
	{
		while (src[i] && j < (dstsize - 1))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0;
	}
	if (j > dstsize)
		j = dstsize;
	return (src_len + j - i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)(malloc(sizeof(*str) * (ft_strlen(s1) + 1)));
	if (str)
	{
		i = 0;
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = 0;
	}
	return (str);
}
