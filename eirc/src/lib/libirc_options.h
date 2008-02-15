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
 * $Id: libirc_options.h 2 2004-09-08 11:49:02Z gyunaev $
 */

/*! 
 * \file libirc_options.h
 * \author Georgy Yunaev
 * \version 1.0
 * \date 09.2004
 * \brief This file defines the options used in irc_session_options()
 */

#ifndef INCLUDE_IRC_OPTIONS_H
#define INCLUDE_IRC_OPTIONS_H

/*! 
 * enables additional debug output 
 * \ingroup options
 */
#define LIBIRC_OPTION_DEBUG			(1 << 1)

/*! \brief allows to strip origins automatically.
 *
 * For every IRC server event, the event origin is sent in standard form:
 * nick!host\@ircserver, i.e. like tim!home\@irc.krasnogorsk.ru. Such origins
 * can not be used in IRC commands, and need to be stripped (i.e. host and 
 * server part should be cut off) before using. This can be done either 
 * explicitly, by calling irc_target_get_nick(), or implicitly for all the 
 * events - by setting this option with irc_option_set().
 * \ingroup options
 */
#define LIBIRC_OPTION_STRIPNICKS	(1 << 2)


#endif /* INCLUDE_IRC_OPTIONS_H */
