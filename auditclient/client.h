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

#if !defined(_CLIENT_H_)
#define _CLIENT_H_

#define _GNU_SOURCE

#include <assert.h>
#define NOT_FOUND_PREFIX "/__not_exists"

extern int use_ldcs;
extern int ldcsid;

typedef unsigned long ElfX_Addr;

/**
 * Used by by client_call_binding to redirect interesting
 * calls to our wrapper functions.
 **/
ElfX_Addr redirect_open(const char *symname, ElfX_Addr value);
ElfX_Addr redirect_exec(const char *symname, ElfX_Addr value);

/**
 * These functions are called by the audit hooks to do the major
 * pieces of work.
 **/
ElfX_Addr client_call_binding(const char *symname, ElfX_Addr symvalue);
char *client_library_load(const char *libname);
int client_init();
int client_done();

/**
 * Helper functions used throughout the client
 **/
void set_errno(int newerrno);
void patch_on_load_success(const char *rewritten_name, const char *orig_name);
void sync_cwd();
void check_for_fork();

#endif
