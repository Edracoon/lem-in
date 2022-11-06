#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>

# include "lib.h"

# define	BUFFER_SIZE		2048
# define	STDIN			0
# define	STDOUT			1
# define	STDERR			2
# define	RED "\e[1;31m"
# define	RESET "\e[0m"

# define START 1
# define END 2

#define printTime(code) { \
	clock_t before = clock(); \
	code; \
	clock_t now = clock(); \
	fprintf(stderr, #code ": %lfs\n", (double)(now - before) / CLOCKS_PER_SEC); \
}

typedef enum bool {
	false,
	true,
} bool;

typedef struct s_link {
	int				distance;
	struct s_room	*node;

	struct s_link	*next;
	struct s_link	*prev;
}	t_link;

typedef struct s_path {

	struct s_room	**path;
	struct s_path	*next;
	struct s_path	*prev;

}	t_path;

typedef struct s_room {

	char			*name;
	int				id;
	long int		x;
	long int		y;
	int				type;	// 0 = normal, 1 = start, 2 = end
	
	/* For path finding algorithm */
	bool			visited;
	int				currCost;
	t_link			*links;
	t_link			*saveLinks;

	/* For solution output */
	int				idAnt;
	bool			hasAnAnt;

	struct s_room	*prev;
	struct s_room	*next;
}	t_room;

typedef struct s_data {

	t_room			*rooms;

	size_t			nbRooms;
	long int		nbAnts;
	long int		maxX;
	long int		maxY;

	bool			debug;
	bool			time;

}	t_data;

// ===== PARSER ===== //
int		get_next_line(int fd, char **line);
void    freeTab(char **tab);
void	printMap(t_data *anthill);
void    storeNbAnts(char *line, t_data *anthill);
bool	storeRoom(char *line, int type, t_data *anthill);
bool    storeLinks(char *line, t_data *anthill);
void    parseLines(char **lines, t_data *anthill);
char    **readInput();

// ===== ROOM UTILS ===== //
void	exitError(char *error);
void	addRoom(t_room **roomList, t_room *new);
void	browseRooms(t_room *roomList);
void	addLinkForRoom(t_room *r, t_room *roomList, char *link);
int		pathLen(t_room **path);
size_t	roomSizeList(t_room *rooms);
bool	avoidDoubleLink(t_room *room, char *link);
bool	validStartEnd(t_room *roomlist);
bool	avoidDoubleRoom(t_room *roomList, t_room *elt);
t_room	*createRoom(char *name, unsigned int x, unsigned int y, int type);
t_room	*lastRoom(t_room *roomList);
t_room	*findRoomByName(char *name, t_room *rooms);
t_room	*getSpecificRoom(t_room *roomList, int type);
t_room	*findRoomByPos(t_room *roomList, unsigned int x, unsigned int y);
t_room	***addToList(t_room ***pathList, t_room **path, int found);
t_link	*findLinkByName(t_link *links, char *name);

// ===== PATH UTILS ===== //
int		pathLen(t_room **path);
int		nbOfPath(t_path *paths);
t_path	*orderPath(t_path *paths);
void	addPath(t_path **paths, t_path *new);
void	resetCost(t_room *rooms);
t_room	**initPrev(size_t size);
t_path	*initPath(t_room **roomPath);
void	deletePath(t_path *paths);
t_path	*lastPath(t_path *paths);
void	freePaths(t_path *paths);

// ===== ALGORITHM ===== //
t_room	**dijkstra(t_room *start, t_room *end, t_data *anthill);
void	getOptimalPath(t_data *anthill, t_path *pathList, size_t nbOfPath);
void 	letsFuckingGo(t_data *anthill, t_path *pathList, size_t nbOfPath);
t_path	*solve(t_data *anthill);
void	printer(t_data *anthill, t_path *pathList, int *comb);

#endif