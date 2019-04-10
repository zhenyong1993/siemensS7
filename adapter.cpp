#include "adapter.h"
#include <stdlib.h>
#include <stdio.h>
#include "nodavesimple.h"
#include "openSocket.h"
#include <sstream>
#include <iostream>

using namespace std;

template <typename T>
void Num2Str(const T &source, string &dest)
{
    stringstream stream;
    stream.precision(3);
    stream << source;
    dest = stream.str();   //�˴�Ҳ������ stream>>dest
}

short readDbFloat(daveConnection* dc,int block,int byteAddr,string& val);
short readDbWord(daveConnection* dc,int block,int byteAddr,string& val);
short readPosFloat(daveConnection* dc,int block,int byteAddr,string& val);

short readPos(daveConnection* dc,const string& paraName,string& val)
{
    short ret = -1;
    int start = 0;
    float f=0.0;
    if(0==daveSetBit(dc, daveDB, 2600, 1, 1))
    {
        if(paraName=="Pos.x")
        {
            start = 5700;
        }
        else if(paraName=="Pos.y")
        {
            start = 5701;
        }
        else
        {
            start = 5702;
        }


        string tmpVal;
        if(0==readPosFloat(dc,start,4,tmpVal))
        {
            cout << "rest Pos is" << tmpVal << endl;
        }

        ret = readPosFloat(dc,start,0,val);

        //daveClrBit(dc, daveDB, 2600, 1, 1);
    }
    else
    {
        cout << "set fail" << endl;
    }
    return ret;
}


void transferGrayCode(const string& itemName, string& value)
{
    int value_int = atoi(value.c_str());
    int num = 0;
    if (itemName.find("spindFeedRate") != string::npos)
    {
        switch (value_int)
        {
        case 0:
            num = 50;
            break;
        case 1:
            num = 55;
            break;
        case 3:
            num = 60;
            break;
        case 2:
            num = 65;
            break;
        case 6:
            num = 70;
            break;
        case 7:
            num = 75;
            break;
        case 5:
            num = 80;
            break;
        case 4:
            num = 85;
            break;
        case 12:
            num = 90;
            break;
        case 13:
            num = 95;
            break;
        case 15:
            num = 100;
            break;
        case 14:
            num = 105;
            break;
        case 10:
            num = 110;
            break;
        case 11:
            num = 115;
            break;
        case 9:
            num = 120;
            break;
        default:
            num = value_int;
            break;
        }
    }
    else if (itemName.find("feedRate") != string::npos)
    {
        switch (value_int)
        {
        case 0:
            num = 0;
            break;
        case 1:
            num = 2;
            break;
        case 3:
            num = 4;
            break;
        case 2:
            num = 6;
            break;
        case 6:
            num = 10;
            break;
        case 7:
            num = 15;
            break;
        case 5:
            num = 30;
            break;
        case 4:
            num = 40;
            break;
        case 12:
            num = 50;
            break;
        case 13:
            num = 60;
            break;
        case 15:
            num = 70;
            break;
        case 14:
            num = 80;
            break;
        case 10:
            num = 90;
            break;
        case 11:
            num = 95;
            break;
        case 9:
            num = 100;
            break;
        case 8:
            num = 105;
            break;
        case 24:
            num = 110;
            break;
        case 25:
            num = 120;
            break;
        default:
            num = value_int;
            break;
        }
    }
    else
    {
        return;
    }

    //char str[8];
    //itoa(num, str, 10);
    value = to_string(num);//str;
}


short readFeedRate(daveConnection* dc,string& val)
{
    short ret = -1;
    int start = 0;
    unsigned short u16Val =0;
    string tmp = "";
    string a;
    ret = readDbWord(dc,3800,0,a);
    if (0==ret)
    {
        u16Val = daveGetU8(dc);
        tmp = to_string(u16Val);
        transferGrayCode("feedRate", tmp);
        val = tmp;
    }

    return ret;
}

short readSpindFeedRate(daveConnection* dc,string& val)
{
    short ret = -1;
    int start = 0;
    unsigned char byteVal =0;
    string tmp = "";
    ret = daveReadBytes(dc,daveDB,3801,0,1,NULL);
    if (0==ret)
    {
        byteVal = daveGetU8(dc);
        tmp = to_string(byteVal);
        transferGrayCode("spindFeedRate", tmp);
        val = tmp;
    }

    return ret;
}

short readDbBit(daveConnection* dc,int block,int byteAddr,int bitIndex,string& val)
{
    short ret = -1;
    unsigned char byteVal =0;
    if(bitIndex>=0 && bitIndex<8)
    {
        ret = daveReadBytes(dc,daveDB,block,byteAddr,1,NULL);
        if(0==ret)
        {
            byteVal = daveGetU8(dc);
            byteVal = (byteVal>>bitIndex) & 0x01;
            val = to_string(byteVal);
        }
    }
    return ret;
}


short readDbByte(daveConnection* dc,int block,int byteAddr,string& val)
{
    short ret = -1;
    unsigned char byteVal =0;
    ret = daveReadBytes(dc,daveDB,block,byteAddr,1,NULL);
    if(0==ret)
    {
        byteVal = daveGetU8(dc);
        val = to_string(byteVal);
    }
    return ret;
}

short readDbDWord(daveConnection* dc,int block,int byteAddr,string& val)
{
    short ret = -1;
    unsigned int u32Val =0;
    ret = daveReadBytes(dc,daveDB,block,byteAddr,4,NULL);
    if(0==ret)
    {
        u32Val = daveGetU32(dc);
        val = to_string(u32Val);
    }
    return ret;
}

short readDbWord(daveConnection* dc,int block,int byteAddr,string& val)
{
    short ret = -1;
    unsigned int u16Val =0;
    ret = daveReadBytes(dc,daveDB,block,byteAddr,2,NULL);
    if(0==ret)
    {
        u16Val = daveGetU16(dc);
        val = to_string(u16Val);
    }
    return ret;
}

short readDbFloat(daveConnection* dc,int block,int byteAddr,string& val)
{
    short ret = -1;
    float fVal =0.0;
    ret = daveReadBytes(dc,daveDB,block,byteAddr,4,NULL);
    if(0==ret)
    {
        fVal = daveGetFloat(dc);
        Num2Str(fVal,val);
    }
    return ret;
}


short readPosFloat(daveConnection* dc,int block,int byteAddr,string& val)
{
    short ret = -1;
    float fVal =0.0;
    ret = daveReadPos(dc,daveDB,block,byteAddr,2,NULL);
    if(0==ret)
    {
        fVal = daveGetFloat(dc);
        Num2Str(fVal,val);
    }
    return ret;
}


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

        printf("dc is %x\n",dc);

        if (0==daveConnectPLC(dc))
        {
            ret = 0;
            *handle = dc;
        }
        else
        {
            closeSocket(fds.rfd);
            fds.rfd = 0;
            fds.wfd = 0;

            if(di)
            {
                daveFree(di);
            }

            if(dc)
            {
                daveFree(dc);
            }
        }
    }
    return ret;
}

short read_param_val(void *handle, const string &itemName, string &itemValue)
{
    short ret = -1;
    string tmp = "";
    unsigned char tmpU8=0;
    if(handle)
    {
        daveConnection * dc = (daveConnection*)handle;
        //if(itemName.find("Pos.")!= string::npos)
        if(itemName.find("/Channel/GeometricAxis/actToolBasePos[u1,1]")!= string::npos)
        {
            ret = readPos(dc, "Pos.x", itemValue);
        }
        if(itemName.find("/Channel/GeometricAxis/actToolBasePos[u1,2]")!= string::npos)
        {
            ret = readPos(dc, "Pos.y", itemValue);
        }
        if(itemName.find("/Channel/GeometricAxis/actToolBasePos[u1,3]")!= string::npos)
        {
            ret = readPos(dc, "Pos.z", itemValue);
        }
        //else if(itemName=="feedRate")
        else if(itemName=="/Channel/MachineAxis/feedRateOvr")
        {
            ret = readFeedRate(dc,itemValue);
        }
        //else if(itemName=="spindFeedRate")
        else if(itemName=="/Channel/MachineAxis/feedRateOvr")
        {
            ret = readSpindFeedRate(dc,itemValue);
        }
        //else if(itemName=="toolNo")
        else if(itemName=="/Channel/State/actTNumber[u1]")
        {
            ret = readDbByte(dc,2500,2000,itemValue);
        }
        else if(itemName=="progNum")
        {
            ret = readDbByte(dc,4900,1000,itemValue);
        }
        else if(itemName=="tempHighAlarm")
        {
            ret = readDbBit(dc,2700,3,0,itemValue);
        }
        else if(itemName=="channelAlarm")
        {
            ret = readDbBit(dc,2700,3,6,itemValue);
        }
        else if(itemName=="ctrlMode")
        {
            ret = readDbByte(dc,3100,0,tmp);
            if(0==ret)
            {
                tmpU8 = atoi((char*)tmp.c_str());
                tmpU8 = tmpU8 & 0x07;
                itemValue = to_string(tmpU8);
            }
        }
        //else if(itemName=="machineStatus")
        else if(itemName=="/Channel/State/progStatus[u1]")
        {
            ret = readDbByte(dc,3300,3,tmp);
            if(0==ret)
            {
                tmpU8 = atoi((char*)tmp.c_str());
                tmpU8 = tmpU8 & 0x1f;
                itemValue = to_string(tmpU8);
            }
        }
        //else if(itemName.find("userAlarm")!= string::npos)
        else if(itemName.find("/Nck/LastAlarm/alarmNo")!= string::npos) ///Nck/LastAlarm/alarmNo[0]
        {
            tmp = itemName;
            tmp=tmp.erase(0,23);
			tmp=tmp.erase(1,1);
            tmpU8 = atoi((char*)tmp.c_str());
            if(tmpU8>=0 && tmpU8<16)
            {
                ret = readDbByte(dc, 1600, tmpU8, itemValue);
            }
        }
        else if(itemName.find("DB")!= string::npos)
        {
            tmp = itemName;
            int index = tmp.find(".");
            int block = 0;
            int byteAddr = 0;
            int bitIndex = 0;
            if(index!=string::npos)
            {
                tmp = itemName.substr(2,index-2);
                block = atoi((char*)tmp.c_str());

                tmp = itemName;
                tmp = tmp.erase(0,index+1);
                if((index=tmp.find("DBB"))!=string::npos)
                {
                    tmp = tmp.erase(0,3);
                    byteAddr = atoi((char*)tmp.c_str());
                    ret = readDbByte(dc, block, byteAddr, itemValue);
                }
                else if((index=tmp.find("DBX"))!=string::npos)
                {
                    tmp = tmp.erase(0,3);
                    index = tmp.find(".");
                    if(index!=string::npos)
                    {
                        string sub = tmp.substr(0,index);
                        byteAddr = atoi((char*)sub.c_str());
                        sub = tmp.substr(index+1);
                        bitIndex = atoi((char*)sub.c_str());
                        ret = readDbBit(dc, block, byteAddr, bitIndex, itemValue);
                    }
                }
                else if((index=tmp.find("DBD"))!=string::npos)
                {
                    tmp = tmp.erase(0,3);
                    byteAddr = atoi((char*)tmp.c_str());
                    if(tmp.find("REAL")!=string::npos || tmp.find("real")!=string::npos)
                    {
                        ret = readDbFloat(dc, block, byteAddr, itemValue);
                    }
                    else
                    {
                        ret = readDbDWord(dc, block, byteAddr, itemValue);
                    }
                }
                else if((index=tmp.find("DBW")) != string::npos)
                {
                    tmp = tmp.erase(0,3);
                    byteAddr = atoi((char*)tmp.c_str());
                    ret = readDbWord(dc, block, byteAddr, itemValue);
                }
            }
        }
    }
    return ret;
}

short write_param_val(void *handle, const string &itemName, const string &itemValue)
{
    short ret = -1;
    return ret;
}

short disconnect(void **handle)
{
    short ret = -1;
    daveInterface* di = NULL;
    daveConnection* dc = NULL;
    _daveOSserialType fds;
    if(handle)
    {
        dc = (daveConnection*)*handle;

        if(dc)
        {
            daveDisconnectPLC(dc);

            di = dc->iface;

            if(di)
            {
                fds = di->fd;
                closeSocket(fds.rfd);
                fds.rfd = 0;
                fds.wfd = 0;
            }

            daveFree(dc);

            daveFree(di);

            *handle = NULL;

            ret = 0;
        }
    }
    return ret;
}

bool is_connect(void *handle)
{
    bool ret = false;
    daveInterface* di = NULL;
    daveConnection* dc = NULL;
    if(handle)
    {
        dc = (daveConnection*)handle;
        if(dc)
        {
            di = dc->iface;
            if(di)
            {
                if(di->fd.rfd)
                {
                    ret = true;
                }
            }
        }
    }
    return ret;
}

bool needReconnect()
{
    return true;
}

