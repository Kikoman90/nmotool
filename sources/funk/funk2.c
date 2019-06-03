// 42 header //

#include "funk.h"

t_header_funk	header64(void)
{
	return ((t_header_funk)\
		{ sizeof(struct mach_header_64), &ncmds64, &sizeofcmds64 });
}

t_segment_funk	segment64(void)
{
	return ((t_segment_funk){ sizeof(struct segment_command_64), \
		&cmdsize64, &nsects64, LC_SEGMENT_64 });
}

t_section_funk	section64(void)
{
	return ((t_section_funk)\
	{ sizeof(struct section_64), &sectname64, &segname64 });
}

t_nlist_funk	nlist64(void)
{
	return ((t_nlist_funk) { sizeof(struct nlist_64) });
}