/*
 Simplified test and demo program for Libnodave, a free communication libray for Siemens S7.

 **********************************************************************
 * WARNING: This and other test programs overwrite data in your PLC.  *
 * DO NOT use it on PLC's when anything is connected to their outputs.*
 * This is alpha software. Use entirely on your own risk.             *
 **********************************************************************

 (C) Thomas Hergenhahn (thomas.hergenhahn@web.de) 2005.

 This is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Libnodave; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <stdlib.h>
#include <stdio.h>
#include "nodavesimple.h"
#include "openSocket.h"

#if 0
int main(int argc, char **argv) {
    int a,b,c,res;
    float d;
    daveInterface * di;
    daveConnection * dc;
    _daveOSserialType fds;
    int blockNum = 0;
    int dbNum = 0;
    unsigned char byteVal = 0;

    daveSetDebug(daveDebugPrintErrors);

    if (argc<2) {
    printf("Usage: testISO_TCP IP-Address of CP\n");
    exit(-1);
    }

    fds.rfd=openSocket(102, argv[1]);
    fds.wfd=fds.rfd;

    if(argc>3)
    {
        blockNum = atoi(argv[2]);
        dbNum = atoi(argv[3]);
    }
    else
    {
        blockNum = 3300;
        dbNum = 1;
    }

    if (fds.rfd>0) {
    di =daveNewInterface(fds,"IF1",0, daveProtoISOTCP, daveSpeed187k);
    daveSetTimeout(di,5000000);
    dc =daveNewConnection(di,2,0, 2);  // insert your rack and slot here

    if (0==daveConnectPLC(dc)) {
        printf("Connected.\n");


    res=daveReadBytes(dc,daveDB,blockNum,dbNum,1,NULL);
    if (0==res) {
            a=daveGetU8(dc);
        printf("value: %d\n",a);
    }  else
        printf("failed! (%d)\n",res);

    a = 1;

    //
    if(0==daveSetBit(dc, daveDB, 2600, 1, 1))
    {
        printf("set bit ok\n");
    }
    else
    {
        printf("set bit fail\n");
    }

    if(0==daveReadBytes(dc, daveDB, 2600, 1, 1, &byteVal))
    {
        printf("read bit ok,byteVal is %d\n",byteVal);
    }
    else
    {
        printf("read bit fail\n");
    }


    res=daveReadBytes(dc,daveDB,5700,0,2,NULL);
    if (0==res) {
            d=daveGetFloat(dc);
        printf("value: %f\n",d);
    }  else
        printf("failed! (%d)\n",res);

    res=daveReadBytes(dc,daveDB,5701,0,2,NULL);
    if (0==res) {
            d=daveGetFloat(dc);
        printf("value: %f\n",d);
    }  else
        printf("failed! (%d)\n",res);

    res=daveReadBytes(dc,daveDB,5702,0,2,NULL);
    if (0==res) {
            d=daveGetFloat(dc);
        printf("value: %f\n",d);
    }  else
        printf("failed! (%d)\n",res);

    if(0==daveClrBit(dc, daveDB, 2600, 1, 1))
    {
        printf("clr bit ok\n");
    }
    else
    {
        printf("clr bit fail\n");
    }

    if(0==daveReadBytes(dc, daveDB, 2600, 1, 1, &byteVal))
    {
        printf("read bit ok,byteVal is %d\n",byteVal);
    }
    else
    {
        printf("read bit fail\n");
    }


    printf("Finished.\n");
    return 0;
    } else {
        printf("Couldn't connect to PLC.\n");
        return -2;
    }
    } else {
    printf("Couldn't open TCP port. \nPlease make sure a CP is connected and the IP address is ok. \n");
        return -1;
    }
}
#else
#include "adapter.h"
#include <iostream>

using namespace std;

int main()
{
    void* handle = NULL;
    string val="";
    if(0==connect_to_server("192.168.1.3", 102, "", "", 1000, &handle))
    {
        cout<<"connect to server ok"<<endl;
        printf("handle is %x\n",handle);

        if(is_connect(handle))
        {
            cout<<"connected"<<endl;
/*
            if(0==read_param_val( handle, "toolNo", val))
            {
                cout<<"toolNo is "<<val<<endl;
            }
*/

//            if(0==read_param_val( handle, "DB3800.DBB0", val))
            if(0==read_param_val( handle, "feedRate", val))
            {
                cout<<"feedRate is "<<val<<endl;
            }
            else
            {
                cout << "feedRate read fail" << endl;
            }

            if(0==read_param_val( handle, "spindFeedRate", val))
            {
                cout<<"spindFeedRate is "<<val<<endl;
            }
            else
            {
                cout << "spindFeedRate read fail" << endl;
            }

            if(0==read_param_val( handle, "Pos.x", val))
            {
                cout<<"Pos.x is "<<val<<endl;
            }
            else
            {
                cout << "Pos.x read fail" << endl;
            }

            if(0==read_param_val( handle, "Pos.y", val))
            {
                cout<<"Pos.y is "<<val<<endl;
            }
            else
            {
                cout << "Pos.y read fail" << endl;
            }

            if(0==read_param_val( handle, "Pos.z", val))
            {
                cout<<"Pos.z is "<<val<<endl;
            }
            else
            {
                cout << "Pos.z read fail" << endl;
            }

            if(0==read_param_val( handle, "tempHighAlarm", val))
            {
                cout<<"tempHighAlarm is "<<val<<endl;
            }
            else
            {
                cout << "tempHighAlarm read fail!" << endl;
            }

            if(0==read_param_val( handle, "channelAlarm", val))
            {
                cout<<"channelAlarm is "<<val<<endl;
            }
            else
            {
                cout << "channelAlarm read fail!" << endl;
            }

            if(0==read_param_val( handle, "ctrlMode", val))
            {
                cout<<"ctrlMode is "<<val<<endl;
            }
            else
            {
                cout << "ctrlMode read fail!" << endl;
            }

            if(0==read_param_val( handle, "machineStatus", val))
            {
                cout<<"machineStatus is "<<val<<endl;
            }
            else
            {
                cout << "machineStatus read fail!" << endl;
            }

            if(0==read_param_val( handle, "userAlarm", val))
            {
                cout<<"userAlarm is "<<val<<endl;
            }
            else
            {
                cout << "userAlarm read fail!" << endl;
            }

            if(0==read_param_val( handle, "DB3300.DBB2", val)) //加工状态
            {
                cout<<"operation status is "<<val<<endl;
            }
            else
            {
                cout << "operation status fail" << endl;
            }

            if(0==read_param_val( handle, "DB4900.DBB100", val))
            {
                cout<<"F_Speed is "<<val<<endl;
            }
            else
            {
                cout << "F_Speed read fail" << endl;
            }

            if(0==read_param_val( handle, "DB3300.DBX4.6", val))
            {
                cout<<"NCKalarm is "<<val<<endl;
            }
            else
            {
                cout << "NCKalarm read fail" << endl;
            }

            if(0==read_param_val( handle, "DB1400.DBD16", val))
            {
                cout<<"MachineWait is "<<val<<endl;
            }
            else
            {
                cout << "MachineWait read fail" << endl;
            }

            //if(0==read_param_val( handle, "DB4900.DBD1000", val))
            if(0==read_param_val( handle, "progNum", val))
            {
                cout<<"progNum is "<<val<<endl;
            }
            else
            {
                cout << "progNum read fail" << endl;
            }

            if(0==read_param_val( handle, "DB4900.DBW204", val))
            {
                cout<<"progNum is "<<val<<endl;
            }
            else
            {
                cout << "progNum read fail" << endl;
            }

            if(0==read_param_val( handle, "DB4900.DBB201", val))
            {
                cout<<"start is "<<val<<endl;
            }
            else
            {
                cout << "start read fail" << endl;
            }

            if(0==read_param_val( handle, "DB4900.DBB203", val))
            {
                cout<<"end is "<<val<<endl;
            }
            else
            {
                cout << "end read fail" << endl;
            }

        }
        else
        {
            cout<<"dis connected"<<endl;
        }

        disconnect(&handle);
    }
    return 0;
}

#endif
/*
    Changes:
    07/15/05  did this simplified version.
*/
