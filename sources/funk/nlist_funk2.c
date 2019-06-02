// 42 header //

#include "funk.h"

uint32_t	n_strx64(t_nlist *ptr_nlist)
{
	return (swap32(ptr_nlist->nlist64.n_un.n_strx));
}

uint8_t		n_type64(t_nlist *ptr_nlist)
{
	return (ptr_nlist->nlist64.n_type);
}

uint8_t		n_sect64(t_nlist *ptr_nlist)
{
	return (ptr_nlist->nlist64.n_sect);
}

int16_t		n_desc64(t_nlist *ptr_nlist)
{
	return (swap16(ptr_nlist->nlist64.n_desc));
}

uint64_t	n_value64(t_nlist *ptr_nlist)
{
	return (swap64(ptr_nlist->nlist64.n_value));
}