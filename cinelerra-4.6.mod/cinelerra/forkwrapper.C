
/*
 * CINELERRA
 * Copyright (C) 2009 Adam Williams <broadcast at earthling dot net>
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



#include "bcsignals.h"
#include "bcwindowbase.inc"
#include "forkwrapper.h"
#include "format.inc"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

#define EXIT_CODE 0x7fff


ForkWrapper::ForkWrapper()
{
	done = 0;
	command_data = 0;
	command_allocated = 0;
	result_data = 0;
	result_allocated = 0;
	parent_fd = 0;
	child_fd = 0;
	pid = 0;
	is_dummy = 0;
}

ForkWrapper::~ForkWrapper()
{
	int status;
	if(!is_dummy && pid) 
	{
		waitpid(pid, &status, 0);
	}

	delete [] command_data;
	if(parent_fd) close(parent_fd);
	if(child_fd) close(child_fd);
}

void ForkWrapper::start()
{
// Create the process & socket pair.
	int sockets[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
	parent_fd = sockets[0];
	child_fd = sockets[1];

	pid = fork();

// Child process
	if(!pid)
	{
//printf("ForkWrapper::start %d %d\n", __LINE__, getpid());
		BC_Signals::reset_locks();
		BC_Signals::set_sighup_exit(1);
		init_child();
		run();
		_exit(0);
	}
}

void ForkWrapper::stop()
{
	send_command(EXIT_CODE, 
		0,
		0);
}

void ForkWrapper::start_dummy(int parent_fd, int pid)
{
	this->parent_fd = parent_fd;
	this->pid = pid;
	is_dummy = 1;
}

void ForkWrapper::init_child()
{
	printf("ForkWrapper::init_child %d\n", __LINE__);
}

int ForkWrapper::handle_command()
{
	printf("ForkWrapper::handle_command %d\n", __LINE__);
	return 0;
}

void ForkWrapper::run()
{
	int result = 0;
	const int debug = 0;

	while(!done)
	{
		if(debug) printf("ForkWrapper::run %d this=%p parent_fd=%d child_fd=%d\n", 
			__LINE__, this, parent_fd, child_fd);

		result = read_command();



		if(debug) printf("ForkWrapper::run %d this=%p result=%d command_token=%d\n", 
			__LINE__, this, result, command_token);

		if(!result && command_token == EXIT_CODE) 
			done = 1;
		else
		if(!result)
		{
			handle_command();
		}
	}
}


int ForkWrapper::send_command(int token, 
		unsigned char *data,
		int bytes)
{
	unsigned char buffer[sizeof(int) * 2];
	this->command_token = token;
	this->command_bytes = bytes;
// printf("ForkWrapper::send_command %d parent_fd=%d token=%d data=%p bytes=%d\n", 
// __LINE__, 
// parent_fd, 
// token,
// data,
// bytes);
	int *ibfr = (int *)buffer;
	ibfr[0] = token;
	ibfr[1] = bytes;
	(void)write(parent_fd, buffer, sizeof(buffer));
	if(data && bytes) (void)write(parent_fd, data, bytes);
	return 0;
}

int ForkWrapper::read_command()
{
	unsigned char buffer[sizeof(int) * 2];
//printf("ForkWrapper::read_command %d child_fd=%d\n", __LINE__, child_fd);
	(void)read(child_fd, buffer, sizeof(buffer));
//printf("ForkWrapper::read_command %d child_fd=%d\n", __LINE__, child_fd);
	int *ibfr = (int *)buffer;
	command_token = ibfr[0];
	command_bytes = ibfr[1];

// 	printf("ForkWrapper::read_command %d command_token=%d command_bytes=%d\n", 
// 		__LINE__, 
// 		command_token, 
// 		command_bytes);
	if(command_bytes && command_allocated < command_bytes)
	{
		delete [] command_data;
		command_data = new unsigned char[command_bytes];
		command_allocated = command_bytes;
	}
	if(command_bytes) (void)read(child_fd, command_data, command_bytes);
	return 0;
}

int ForkWrapper::send_result(int64_t value, unsigned char *data, int data_size)
{
	unsigned char buffer[sizeof(int64_t) + sizeof(int)];
	int64_t *lbfr = (int64_t *)buffer;
	lbfr[0] = value;
	int *ibfr = (int *)&lbfr[1];
	ibfr[0] = data_size;
	(void)write(child_fd, buffer, sizeof(buffer));
	if(data && data_size) (void)write(child_fd, data, data_size);
	return 0;
}

// Return 1 if the child is dead
int ForkWrapper::read_timeout(unsigned char *data, int size)
{
	fd_set rfds;
	struct timeval timeout_struct;
	int bytes_read = 0;

// Poll child status while doing timed reads
	while(bytes_read < size)
	{
		timeout_struct.tv_sec = 1;
		timeout_struct.tv_usec = 0;
		FD_ZERO(&rfds);
		FD_SET(parent_fd, &rfds);
		int result = select(parent_fd + 1, &rfds, 0, 0, &timeout_struct);

		if(result <= 0 && !child_running()) return 1;


		if(result > 0)
		{
			int fragment = read(parent_fd, data + bytes_read, size - bytes_read);
			if(fragment > 0) bytes_read += fragment;
		}
	}

	return 0;
}

int64_t ForkWrapper::read_result()
{
	unsigned char buffer[sizeof(int64_t) + sizeof(int)];
//printf("ForkWrapper::read_result %d  parent_fd=%d\n", __LINE__, parent_fd);

	if(read_timeout(buffer, sizeof(buffer))) return 1;
//printf("ForkWrapper::read_result %d  parent_fd=%d\n", __LINE__, parent_fd);
	int64_t *lbfr = (int64_t *)buffer;
	int64_t result = lbfr[0];
	int *ibfr = (int *)&lbfr[1];
	result_bytes = ibfr[0];

	if(result_bytes && result_allocated < result_bytes)
	{
		delete [] result_data;
		result_data = new unsigned char[result_bytes];
		result_allocated = result_bytes;
	}
//printf("ForkWrapper::read_result %d  parent_fd=%d result=" _LD " result_bytes=%d\n", 
//__LINE__, 
//parent_fd,
//result,
//result_bytes);

	if(result_bytes) 
		if(read_timeout(result_data, result_bytes)) return 1;
//printf("ForkWrapper::read_result %d  parent_fd=%d\n", __LINE__, parent_fd);

	return result;
}

// return 1 if the child is running
int ForkWrapper::child_running()
{
	char string[BCTEXTLEN];
	sprintf(string, "/proc/%d/stat", pid);
	FILE *fd = fopen(string, "r");
	if(fd)
	{
		while(!feof(fd) && fgetc(fd) != ')')
			;

		fgetc(fd);
		int status = fgetc(fd);

//printf("ForkWrapper::child_running '%c'\n", status);
		fclose(fd);
		if(status == 'Z') 
		{
			printf("ForkWrapper::child_running %d: process %d dead\n", __LINE__, pid);
			return 0;
		}
		else
			return 1;
	}
	else
	{
		printf("ForkWrapper::child_running %d: process %d not found\n", __LINE__, pid);
		return 0;
	}
}


// From libancillary
#define ANCIL_FD_BUFFER(n) \
struct { \
	struct cmsghdr h; \
	int fd[n]; \
}

void ForkWrapper::send_fd(int fd)
{
	ANCIL_FD_BUFFER(1) buffer;
    struct msghdr msghdr;
    char nothing = '!';
    struct iovec nothing_ptr;
    struct cmsghdr *cmsg;

    nothing_ptr.iov_base = &nothing;
    nothing_ptr.iov_len = 1;
    msghdr.msg_name = NULL;
    msghdr.msg_namelen = 0;
    msghdr.msg_iov = &nothing_ptr;
    msghdr.msg_iovlen = 1;
    msghdr.msg_flags = 0;
    msghdr.msg_control = &buffer;
    msghdr.msg_controllen = sizeof(struct cmsghdr) + sizeof(int);
    cmsg = CMSG_FIRSTHDR(&msghdr);
    cmsg->cmsg_len = msghdr.msg_controllen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    int *ifd = (int *)CMSG_DATA(cmsg);
    *ifd = fd;
    sendmsg(child_fd, &msghdr, 0);
}

int ForkWrapper::get_fd()
{
	ANCIL_FD_BUFFER(1) buffer;
    struct msghdr msghdr;
    char nothing;
    struct iovec nothing_ptr;
    struct cmsghdr *cmsg;

    nothing_ptr.iov_base = &nothing;
    nothing_ptr.iov_len = 1;
    msghdr.msg_name = NULL;
    msghdr.msg_namelen = 0;
    msghdr.msg_iov = &nothing_ptr;
    msghdr.msg_iovlen = 1;
    msghdr.msg_flags = 0;
    msghdr.msg_control = &buffer;
    msghdr.msg_controllen = sizeof(struct cmsghdr) + sizeof(int);
    cmsg = CMSG_FIRSTHDR(&msghdr);
    cmsg->cmsg_len = msghdr.msg_controllen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    int *ifd = (int *)CMSG_DATA(cmsg);
    *ifd = -1;
    
    if(recvmsg(parent_fd, &msghdr, 0) < 0) return(-1);
    return *ifd;
}



