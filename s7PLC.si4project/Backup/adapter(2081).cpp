#include "adapter.h"
#include <stdlib.h>
#include <stdio.h>
#include "nodavesimple.h"
#include "openSocket.h"

class s7Communication
{
private:
	int socket;
	
};

short connect_to_server(const string &ipAddr,unsigned short port, const string &user, const string &password, long timeout,void **handle)
{
	
}

short read_param_val(void *handle, const string &itemName, string &itemValue)
{
	
}

short write_param_val(void *handle, const string &itemName, const string &itemValue)
{
	
}

short disconnect(void **handle)
{
	
}

bool is_connect(void *handle)
{
	
}

bool needReconnect()
{
	return true;
}

