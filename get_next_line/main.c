#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int main()
{
	int fd;
	char *s;
	fd = open("text.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		s = get_next_line(fd);
	}
	close(fd);
	return (0);
}
