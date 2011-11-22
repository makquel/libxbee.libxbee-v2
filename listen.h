#ifndef __XBEE_LISTEN_H
#define __XBEE_LISTEN_H

/*
  libxbee - a C library to aid the use of Digi's Series 1 XBee modules
            running in API mode (AP=2).

  Copyright (C) 2009  Attie Grande (attie@attie.co.uk)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ll.h"

#define XBEE_LISTEN_RESTART_DELAY 25
#define XBEE_LISTEN_BUFLEN        1024

/* functions are given:
		xbee    the 'master' libxbee struct
		buf     memory containg the entire packet (starting after length, and not including checksum). this memory is calloc'ed and free'd on behalf of the handler
		buflen  the length of memory at buf
		pktList a struct which should be populated with the packets returned. this is calloc'ed and free'd on behalf of the handler
*/
typedef int(*xbee_pktHandlerFunc)(struct xbee *xbee, unsigned char *buf, unsigned char buflen);

/* ADD_HANDLER(packetID, dataStarts, functionName) */
#define ADD_HANDLER(a, b, c) \
	{ (a), (b), (#c), (c), NULL }

/* a NULL handler indicates the end of the list */
struct xbee_pktHandler  {
	unsigned char id;
	unsigned short dataStarts; /* used for debug output, adds  ' <-- data starts' */
	unsigned char *handlerName; /* used for debug output, identifies handler function */
	xbee_pktHandlerFunc handler;
	void *data;
};

void xbee_listen(struct xbee *xbee);

#endif /* __XBEE_LISTEN_H */
