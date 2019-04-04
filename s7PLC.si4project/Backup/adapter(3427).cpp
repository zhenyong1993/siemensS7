#include "adapter.h"
#include <stdlib.h>
#include <stdio.h>
#include "nodavesimple.h"
#include "openSocket.h"

short connect_to_server(const string &ipAddr,unsigned short port, const string &user, const string &password, long timeout,void **handle)
{
	short ret = -1;
    daveInterface * di = NULL;
    daveConnection * dc = NULL;
    _daveOSserialType fds;
    daveSetDebug(daveDebugPrintErrors);
    
    
    fds.rfd=openSocket(102, (char*)ipAddr.c_str());
    	
	if(fds.rfd)
	{
		fds.wfd=fds.rfd;
		di =daveNewInterface(fds,"IF1",0, daveProtoISOTCP, daveSpeed187k);
		daveSetTimeout(di,timeout*1000);
		dc =daveNewConnection(di,2,0, 2); 		
	}
	return ret;
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

