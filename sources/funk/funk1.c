// 42 header //

#include "funk.h"

t_header_funk	header32(void)
{
	return ((t_header_funk)\
		{ sizeof(struct mach_header), &ncmds32, &sizeofcmds32 });
}

t_segment_funk	segment32(void)
{
	return ((t_segment_funk)\
		{ sizeof(struct segment_command), &cmdsize32, &nsects32, LC_SEGMENT });
}

t_section_funk	section32(void)
{
	return ((t_section_funk)\
		{ sizeof(struct section), &sectname32, &segname32 });
}

t_nlist_funk	nlist32(void)
{
	return ((t_nlist_funk){ sizeof(struct nlist) });
}