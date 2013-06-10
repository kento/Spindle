/*
  This file is part of Spindle.  For copyright information see the COPYRIGHT 
  file in the top level directory, or at 
  https://github.com/hpc/Spindle/blob/master/COPYRIGHT

  This program is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License (as published by the Free Software
  Foundation) version 2.1 dated February 1999.  This program is distributed in the
  hope that it will be useful, but WITHOUT ANY WARRANTY; without even the IMPLIED
  WARRANTY OF MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the terms 
  and conditions of the GNU General Public License for more details.  You should 
  have received a copy of the GNU Lesser General Public License along with this 
  program; if not, write to the Free Software Foundation, Inc., 59 Temple
  Place, Suite 330, Boston, MA 02111-1307 USA
*/

#if !defined(CLIENT_API_H_)
#define CLIENT_API_H_

#include "ldcs_api.h"

/**
 * Communication functions for sending messages to the server
 **/
int send_file_query(int fd, char* path, char **newpath);
int send_dir_cwd(int fd, char *cwd);
int send_cwd(int fd);
int send_pid(int fd);
int send_location(int fd, char *location);
int send_rankinfo_query(int fd, int *mylrank, int *mylsize, int *mymdrank, int *mymdsize);
int send_end(int fd);

/* client */
int client_open_connection(char* location, int number);
int client_close_connection(int connid);
int client_register_connection(char *connection_str);
char *client_get_connection_string(int fd);
int client_send_msg(int connid, ldcs_message_t * msg);
int client_recv_msg_static(int fd, ldcs_message_t *msg, ldcs_read_block_t block);

#endif