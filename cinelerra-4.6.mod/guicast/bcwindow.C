
/*
 * CINELERRA
 * Copyright (C) 2008 Adam Williams <broadcast at earthling dot net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "bcdisplayinfo.h"
#include "bcwindow.h"
#include <string.h>



char BC_Window::default_x11_host[BCTEXTLEN] = "";

BC_Window::BC_Window(const char *title,
				int x,
				int y,
				int w,
				int h,
				int minw,
				int minh,
				int allow_resize,
				int private_color,
				int hide,
				int bg_color,
				const char *display_name,
				int group_it,
				int options)
 : BC_WindowBase(options)
{
	create_window(0,
				title,
				x,
				y,
				w,
				h,
				(minw < 0) ? w : minw,
				(minh < 0) ? h : minh,
				allow_resize,
				private_color,
				hide,
				bg_color,
				display_name ? display_name :
					default_x11_host[0] ? default_x11_host :
						0,
				MAIN_WINDOW,
				0,
				group_it);
}


BC_Window::~BC_Window()
{
}

void BC_Window::set_default_x11_host(const char *host)
{
	if( !strcmp(host, default_x11_host) ) return;
	strcpy(default_x11_host, host);
	BC_DisplayInfo::top_border = -1;
}

