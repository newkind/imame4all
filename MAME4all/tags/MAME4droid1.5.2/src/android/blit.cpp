#include "driver.h"
#include "dirty.h"

/* from video.c */
extern char *dirty_old;
extern char *dirty_new;
extern int gfx_xoffset;
extern int gfx_yoffset;
extern int gfx_display_lines;
extern int gfx_display_columns;
extern int gfx_width;
extern int gfx_height;
extern int skiplines;
extern int skipcolumns;

#define SCREEN8 gp2x_screen8
#define SCREEN16 gp2x_screen15
#define FLIP_VIDEO gp2x_video_flip()

#include "minimal.h"

UINT32 *palette_16bit_lookup;

void blitscreen_dirty1_color8(struct osd_bitmap *bitmap)
{
	int x, y;
	int width=(bitmap->line[1] - bitmap->line[0]);
	unsigned char *lb=bitmap->line[skiplines] + skipcolumns;
	unsigned short *address=SCREEN16 + gfx_xoffset + (gfx_yoffset * gfx_width);

	for (y = 0; y < gfx_display_lines; y += 16)
	{
		for (x = 0; x < gfx_display_columns; )
		{
			int w = 16;
			if (ISDIRTY(x,y))
			{
				int h;
				unsigned char *lb0 = lb + x;
				unsigned short *address0 = address + x;
				while (x + w < gfx_display_columns && ISDIRTY(x+w,y))
                    			w += 16;
				if (x + w > gfx_display_columns)
                    			w = gfx_display_columns - x;
				for (h = 0; ((h < 16) && ((y + h) < gfx_display_lines)); h++)
				{
					int wx;
					for (wx=0;wx<w;wx++)
					{
						address0[wx] = gp2x_palette[lb0[wx]];
					}
					lb0 += width;
					address0 += gfx_width;
				}
			}
			x += w;
        	}
		lb += 16 * width;
		address += 16 * gfx_width;
	}
	
	FLIP_VIDEO;
}

void blitscreen_dirty0_color8(struct osd_bitmap *bitmap)
{
	int x,y;
	int width=(bitmap->line[1] - bitmap->line[0]);
	int columns=gfx_display_columns;
	unsigned char *lb = bitmap->line[skiplines] + skipcolumns;
	unsigned short *address = SCREEN16 + gfx_xoffset + (gfx_yoffset * gfx_width);

	for (y = 0; y < gfx_display_lines; y++)
	{
		for (x = 0; x < columns; x++)
		{
			address[x] = gp2x_palette[lb[x]];
		}
		lb+=width;
		address+=gfx_width;
	}
	
	FLIP_VIDEO;
}

void blitscreen_dirty1_palettized16(struct osd_bitmap *bitmap)
{
	int x, y;
	int width=(bitmap->line[1] - bitmap->line[0])>>1;
	unsigned short *lb=((unsigned short*)(bitmap->line[skiplines])) + skipcolumns;
	unsigned short *address=SCREEN16 + gfx_xoffset + (gfx_yoffset * gfx_width);

	for (y = 0; y < gfx_display_lines; y += 16)
	{
		for (x = 0; x < gfx_display_columns; )
		{
			int w = 16;
			if (ISDIRTY(x,y))
			{
				int h;
				unsigned short *lb0 = lb + x;
				unsigned short *address0 = address + x;
				while (x + w < gfx_display_columns && ISDIRTY(x+w,y))
                    			w += 16;
				if (x + w > gfx_display_columns)
                    			w = gfx_display_columns - x;
				for (h = 0; ((h < 16) && ((y + h) < gfx_display_lines)); h++)
				{
					int wx;
					for (wx=0;wx<w;wx++)
					{
						address0[wx] = palette_16bit_lookup[lb0[wx]];
					}
					lb0 += width;
					address0 += gfx_width;
				}
			}
			x += w;
        	}
		lb += 16 * width;
		address += 16 * gfx_width;
	}
	
	FLIP_VIDEO;
}

void blitscreen_dirty0_palettized16(struct osd_bitmap *bitmap)
{
	int x,y;
	int width=(bitmap->line[1] - bitmap->line[0])>>1;
	int columns=gfx_display_columns;
	unsigned short *lb = ((unsigned short*)(bitmap->line[skiplines])) + skipcolumns;
	unsigned short *address = SCREEN16 + gfx_xoffset + (gfx_yoffset * gfx_width);

	for (y = 0; y < gfx_display_lines; y++)
	{
		for (x = 0; x < columns; x++)
		{
			address[x] = palette_16bit_lookup[lb[x]];
		}
		lb+=width;
		address+=gfx_width;
	}
	
	FLIP_VIDEO;
}

void blitscreen_dirty1_color16(struct osd_bitmap *bitmap)
{
	int x, y;
	int width=(bitmap->line[1] - bitmap->line[0])>>1;
	unsigned short *lb=((unsigned short*)(bitmap->line[skiplines])) + skipcolumns;
	unsigned short *address=SCREEN16 + gfx_xoffset + (gfx_yoffset * gfx_width);

	for (y = 0; y < gfx_display_lines; y += 16)
	{
		for (x = 0; x < gfx_display_columns; )
		{
			int w = 16;
			if (ISDIRTY(x,y))
			{
				int h;
				unsigned short *lb0 = lb + x;
				unsigned short *address0 = address + x;
				while (x + w < gfx_display_columns && ISDIRTY(x+w,y))
                    			w += 16;
				if (x + w > gfx_display_columns)
                    			w = gfx_display_columns - x;
				for (h = 0; ((h < 16) && ((y + h) < gfx_display_lines)); h++)
				{
					int wx;
					for (wx=0;wx<w;wx++)
					{
						address0[wx] = lb0[wx]&0xFFDF;
					}
					lb0 += width;
					address0 += gfx_width;
				}
			}
			x += w;
        	}
		lb += 16 * width;
		address += 16 * gfx_width;
	}
	
	FLIP_VIDEO;
}

void blitscreen_dirty0_color16(struct osd_bitmap *bitmap)
{
	int x,y;
	int width=(bitmap->line[1] - bitmap->line[0])>>1;
	int columns=gfx_display_columns;
	unsigned short *lb = ((unsigned short*)(bitmap->line[skiplines])) + skipcolumns;
	unsigned short *address = SCREEN16 + gfx_xoffset + (gfx_yoffset * gfx_width);

	for (y = 0; y < gfx_display_lines; y++)
	{
		for (x = 0; x < columns; x++)
		{
			address[x] = lb[x]&0xFFDF;
		}
		lb+=width;
		address+=gfx_width;
	}
	
	FLIP_VIDEO;
}
