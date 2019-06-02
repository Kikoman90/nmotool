// 42 header //

#include "funk.h"

uint32_t	n_strx32(t_nlist *ptr_nlist)
{
	return (swap32(ptr_nlist->nlist32.n_un.n_strx));
}

uint8_t		n_type32(t_nlist *ptr_nlist)
{
	return (ptr_nlist->nlist32.n_type);
}

uint8_t		n_sect32(t_nlist *ptr_nlist)
{
	return (ptr_nlist->nlist32.n_sect);
}

int16_t		n_desc32(t_nlist *ptr_nlist)
{
	return (swap16(ptr_nlist->nlist32.n_desc));
}

uint64_t	n_value32(t_nlist *ptr_nlist)
{
	return ((uint64_t)swap32(ptr_nlist->nlist32.n_value));
}
