/* 
 * Copyright (C) 2004 Georgy Yunaev tim@krasnogorsk.ru
 *
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public 
 * License for more details.
 *
 * $Id: libirc_params.h 67 2006-08-29 19:02:57Z gyunaev $
 */

#ifndef INCLUDE_IRC_PARAMS_H
#define INCLUDE_IRC_PARAMS_H

#define LIBIRC_VERSION_HIGH			0x0001
#define LIBIRC_VERSION_LOW			0x0002

#define LIBIRC_BUFFER_SIZE			1024
#define LIBIRC_DCC_BUFFER_SIZE		1024

#define LIBIRC_STATE_INIT			0
#define LIBIRC_STATE_LISTENING		1
#define LIBIRC_STATE_CONNECTING		2
#define LIBIRC_STATE_CONNECTED		3
#define LIBIRC_STATE_DISCONNECTED	4
#define LIBIRC_STATE_CONFIRM_SIZE	5	// Used only by DCC send to confirm the amount of sent data
#define LIBIRC_STATE_REMOVED		10	// this state is used only in DCC


#endif /* INCLUDE_IRC_PARAMS_H */
