/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:07:12 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/08 13:23:55 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char const delimiter)
{
	size_t	word_count;

	word_count = 0;
	while (*str)
	{
		while (*str == delimiter)
			str++;
		if (*str)
		{
			word_count++;
			while (*str && *str != delimiter)
				str++;
		}
	}
	return (word_count);
}

static char	*get_next_word(const char **str, const char delimiter)
{
	const char	*start;
	const char	*end;

	start = *str;
	while (*start == delimiter)
		start++;
	if (!*start)
	{
		*str = start;
		return (NULL);
	}
	end = start;
	while (*end && *end != delimiter)
		end++;
	*str = end;
	return (ft_strndup(start, end - start));
}

char	**ft_split(char const *str, const char delimiter)
{
	size_t	word_count;
	char	**result;
	size_t	i;

	if (!str)
		return (NULL);
	word_count = count_words(str, delimiter);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = get_next_word(&str, delimiter);
		if (!result[i])
		{
			ft_free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
