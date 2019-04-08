#ifndef ADAPTER_H_
#define ADAPTER_H_

#include <string>
using namespace std;

#define    ADAPTER_OK    0

#ifdef __cplusplus
extern "C"  //C++
{
#endif

    short connect_to_server(const string &ipAddr,unsigned short port, const string &user, const string &password, long timeout,void **handle);

    short read_param_val(void *handle, const string &itemName, string &itemValue);

    short write_param_val(void *handle, const string &itemName, const string &itemValue);

    short disconnect(void **handle);

    bool is_connect(void *handle);

    bool needReconnect();

#ifdef __cplusplus
}
#endif

#endif /* ADAPTER_H_ */

