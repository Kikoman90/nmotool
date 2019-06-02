// 42 header //

#include "fileinf.h"

static t_file_info file_info = { NULL, { NULL, NULL, NULL } };

void	*get_safe(size_t offset, size_t size, t_boxgrade grade)
{
	struct s_bbox	*bbox;

	if (offset + size < offset)
		return (NULL);
	if (GGRADE(grade))
	{
		if (!(bbox = file_info.boundaries[grade]))
			return (log_error(ERR_THROW, \
				"provided bounds are invalid", FROM));
		if (offset + size > bbox->size)
			return (log_error(ERR_THROW, \
				"requested pointer out of bounds", FROM));
		while (bbox)
		{
			if (offset + bbox->offset < offset)
				return (NULL);
			offset += bbox->offset;
			bbox = bbox->next;
		}
		return ((void*)(file_info.ptr + offset));
	}
	return (log_error(ERR_THROW, "bad grade !", FROM));
}


void	pop_bounds(t_boxgrade grade)
{
	struct s_bbox	*pop;

	if (GGRADE(grade) && (pop = file_info.bounds[grade]))
	{
		if (grade == TOP)
			TOP_BOUNDS = (pop->next != MACHO_BOUNDS) ? pop->next : NULL;
		else if (grade == MACHO)
		{
			while (TOP_BOUNDS)
				pop_bounds(TOP);
			MACHO_BOUNDS = NULL;
		}
		else if (grade == FILE)
		{
			pop_bounds(MACHO);
			FILE_BOUNDS = NULL;
		}
		free(pop);
	}
}

bool	push_bounds(size_t offset, size_t size, t_boxgrade grade)
{
	struct s_bbox	*newt, next;

	if (offset + size < offset)
		return (NULL);
	if (GGRADE(grade))
	{
		if ((grade == TOP && !MACHO_BOUNDS) || (grade == MACHO && !FILE_BOUNDS))
			return (log_error(ERR_THROW, "missing file or macho bounds !"));
		if ((next = file_info.bbounds[grade]->next) \
			&& offset + size > next->size)
			return (log_error(ERR_THROW, "invalid bounds", FROM));
		if (!(newt = (struct s_bbox*)malloc(sizeof(*newt))))
			return (log_error(ERR_MALLOC, strerror(errno), FROM));
		newt->offset = offset;
		newt->size = size;
		newt->next = next;
		if (grade != TOP)
			pop_bounds(grade);
		file_info.bbounds[grade] = newt;
		return (true);
	}
	return (log_error(ERR_THROW, "bad grade !", FROM));
}

// cleanup required
bool	load_file(char const *path)
{
	int			fd;
	struct stat	file_stat;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (log_error(ERR_FILE, strerror(errno), FROM));
	if (fstat(fd, &file_stat) == -1)
	{
		close(fd); // close can fail
		return (log_error(ERR_FILE, strerror(errno), FROM));
	}
	// check (file_stat.st_mode & S_IFDIR) -> is directory !
	if (file_stat.st_size <= 0)
	{
		close(fd); // close can fail
		return (log_error(ERR_FILE, "invalid size", FROM));
	}
	if (!push_bounds(FILE, 0, (size_t)file_stat.st_size))
	{
		close(fd); // close can fail
		return (log_error(ERR_THROW, "failed to set file boundaries", FROM));
	}
	if ((file_info.ptr = mmap(NULL, (size_t)file_stat.st_size, \
		PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		close(fd); // close can fail
		return (log_error(ERR_MMAP, strerror(errno), FROM));
	}
	close(fd); // close can fail
	return (true);
}

// cleanup required
bool	unload_file(void)
{
	if (file_info.ptr && file_info.ptr != MAP_FAILED)
	{
		if (munmap(file_info.ptr, file_info.file->size) == -1)
			return (log_error(ERR_MUNMAP, strerror(errno), FROM));
		file_info.ptr = NULL;
	}
	while (file_info.boundaries)
		pop_bounds();
	return (true);
}
