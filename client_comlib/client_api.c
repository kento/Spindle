/*
  This file is part of Spindle.  For copyright information see the COPYRIGHT 
  file in the top level directory, or at 
  <TODO:URL>.

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

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

#include "ldcs_api.h"
#include "ldcs_api_opts.h"
#include "client_api.h"
#include "client_heap.h"

static struct lock_t comm_lock;

#define COMM_LOCK do { if (lock(&comm_lock) == -1) return -1; } while (0)
#define COMM_UNLOCK unlock(&comm_lock)
   
int send_file_query(int fd, char* path, char** newpath) {
   ldcs_message_t message;
   char buffer[MAX_PATH_LEN+1];
   buffer[MAX_PATH_LEN] = '\0';
   int result;
   int path_len = strlen(path);
    
   if (path_len+1 > MAX_PATH_LEN) {
      err_printf("Path to long for message");
      return -1;
   }

   /* Setup packet */
   message.header.type = LDCS_MSG_FILE_QUERY_EXACT_PATH;
   message.header.len = path_len;
   message.data = buffer;
   strncpy(message.data, path, message.header.len);

   COMM_LOCK;

   debug_printf3("sending message of type: file_query len=%d data='%s' ...(%s)\n",
                 message.header.len, message.data, path);  
   client_send_msg(fd, &message);

   /* get new filename */
   client_recv_msg_static(fd, &message, LDCS_READ_BLOCK);

   COMM_UNLOCK;

   if ((message.header.type==LDCS_MSG_FILE_QUERY_ANSWER) && (message.header.len>0)) {
      *newpath = spindle_strdup(message.data);
      result = 0;
   } 
   else {
      *newpath = NULL;
      result = -1;
   }

   return result;
}

int send_dir_cwd(int fd, char *cwd)
{
   ldcs_message_t message;

   message.header.type = LDCS_MSG_CWD;
   message.header.len = strlen(cwd) + 1;
   message.data = cwd;

   COMM_LOCK;

   client_send_msg(fd, &message);

   COMM_UNLOCK;

   return 0;
}

int send_cwd(int fd)
{
   char buffer[MAX_PATH_LEN+1];
   buffer[MAX_PATH_LEN] = '\0';

   if (!getcwd(buffer, MAX_PATH_LEN)) {
      return -1;
   }

   send_dir_cwd(fd, buffer);

   return 0;
}

int send_pid(int fd) {
   ldcs_message_t message;
   char buffer[16];
   int rc=0;

   snprintf(buffer, 16, "%d", getpid());
   message.header.type = LDCS_MSG_PID;
   message.header.len = 16;
   message.data = buffer;


   COMM_LOCK;

   client_send_msg(fd,&message);

   COMM_UNLOCK;

   return(rc);
}

int send_location(int fd, char *location) {
   ldcs_message_t message;

   message.header.type = LDCS_MSG_LOCATION;
   message.header.len = strlen(location)+1;
   message.data = location;

   COMM_LOCK;

   client_send_msg(fd,&message);

   COMM_UNLOCK;

   return 0;
}

int send_rankinfo_query(int fd, int *mylrank, int *mylsize, int *mymdrank, int *mymdsize) {
   ldcs_message_t message;
   char buffer[MAX_PATH_LEN];
   int *p;

   debug_printf3("Sending rankinfo query\n");

   message.header.type=LDCS_MSG_MYRANKINFO_QUERY;
   message.header.len=0;
   message.data=buffer;

   COMM_LOCK;

   client_send_msg(fd,&message);

   client_recv_msg_static(fd, &message, LDCS_READ_BLOCK);

   COMM_UNLOCK;

   if (message.header.type != LDCS_MSG_MYRANKINFO_QUERY_ANSWER || message.header.len != 4*sizeof(int)) {
      err_printf("Received incorrect response to rankinfo query\n");
      *mylrank = *mylsize = *mymdrank = *mymdsize = -1;
      return -1;
   }

   p = (int *) message.data;
   *mylrank = p[0];
   *mylsize = p[1];
   *mymdrank = p[2];
   *mymdsize = p[3];
   debug_printf3("received rank info: local: %d of %d md: %d of %d\n", *mylrank, *mylsize, *mymdrank, *mymdsize);

   return 0;
}

int send_end(int fd) {
   ldcs_message_t message;
   
   message.header.type = LDCS_MSG_END;
   message.header.len = 0;
   message.data = NULL;
   
   COMM_LOCK;
   
   client_send_msg(fd, &message);
   
   COMM_UNLOCK;
   
   return 0;
}

