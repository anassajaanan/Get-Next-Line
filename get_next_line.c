/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:16:04 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/04 19:43:21 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	contains_newline(t_queue *q)
{
	struct s_queue_node	*tmp;

	tmp = q->front;
	while (tmp)
	{
		if (tmp->val == '\n')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*get_line(t_queue *q)
{
	int					i;
	char				*line;
	struct s_queue_node	*tmp;

	i = 0;
	tmp = q->front;
	while (tmp && tmp->val != '\n')
	{
		tmp = tmp->next;
		i++;
	}
	line = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (q->front && q->front->val != '\n')
		line[i++] = dequeue(q);
	line[i++] = dequeue(q);
	line[i] = '\0';
	return (line);
}

char	*get_last_line(t_queue *q)
{
	int					i;
	char				*line;
	struct s_queue_node	*tmp;

	i = 0;
	tmp = q->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (q->front)
		line[i++] = dequeue(q);
	line[i] = '\0';
	return (line);
}

char	*handle_bytes(ssize_t bytes, t_queue *q, char *buffer, int *fd)
{
	ssize_t	i;

	if (bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	else if (bytes == 0)
	{
		free(buffer);
		if (queue_is_empty(q))
			return (NULL);
		else
			return (get_last_line(q));
	}
	else
	{
		i = 0;
		while (i < bytes)
			enqueue(q, buffer[i++]);
		free(buffer);
		return (get_next_line(*fd));
	}
}

char	*get_next_line(int fd)
{
	static t_queue	q;
	ssize_t			bytes;
	char			*buffer;
	static int		flag = 0;

	if (fd == -1)
		return (NULL);
	if (flag == 0)
	{
		init_queue(&q);
		flag = 1;
	}
	if (!queue_is_empty(&q) && contains_newline(&q))
		return (get_line(&q));
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	bytes = read(fd, buffer, BUFFER_SIZE);
	return (handle_bytes(bytes, &q, buffer, &fd));
}
