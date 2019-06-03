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

bool		unload_file(void)
{
	if (file_info.ptr && file_info.ptr != MAP_FAILED && FILE_BOUNDS)
	{
		if (munmap(file_info.ptr, FILE_BOUNDS->size) == -1)
		{
			pop_bounds(FILE);
			return (log_error(ERR_MUNMAP, strerror(errno), FROM));
		}
		file_info.ptr = NULL;
	}
	pop_bounds(FILE);
	return (true);
}

bool		load_file(char const *path)
{
	int			fd;
	bool		ret;
	struct stat	file_stat;

	ret = true;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (log_error(ERR_FILE, strerror(errno), FROM));
	if (fstat(fd, &file_stat) == -1)
		ret = log_error(ERR_FILE, strerror(errno), FROM);
	else if (file_stat.st_mode & S_IFDIR)
		ret = log_error(ERR_FILE, "parameter must not be a directory", FROM);
	else if (file_stat.st_size <= 0)
		ret = log_error(ERR_FILE, "invalid file size", FROM);
	else if (!push_bounds(0, (size_t)file_stat.st_size, FILE))
		ret = log_error(ERR_THROW, "failed to set file boundaries", FROM);
	else if ((file_info.ptr = mmap(NULL, (size_t)file_stat.st_size, \
		PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		ret = log_error(ERR_MMAP, strerror(errno), FROM);
	return ((close(fd) == -1) ? \
		log_error(ERR_FILE, strerror(errno), FROM) : ret);
}
