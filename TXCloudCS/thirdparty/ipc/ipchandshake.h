/**************************************************************************
    Copyright:      Copyright ? 1998 - 2018 Tencent. All Rights Reserved
    Created:        2017-4-6 11:30:41
    Filename:       ipchandshake.h

    Description:
***************************************************************************/

#ifndef __IPCHANDSHAKE_H__
#define __IPCHANDSHAKE_H__

#include "ipcconnection.h"

/**************************************************************************/

class IIPCHandShakeCallback
{
public:
    virtual ~IIPCHandShakeCallback() {}

    // �����ฺ�𴴽�IPCConnectionʵ������Ҫȡ�����ӣ��򷵻�NULL
    virtual IPCConnection* onCreateBegin() = 0;

    // connection��onCreateBegin�����õ������������ӳɹ�����success��true������success��false
    virtual void onCreateEnd(bool success, IPCConnection* connection) = 0;

    // ��ӡlog
    virtual void onLog(LogLevel level, const char* content) = 0;
};

class IPCHandShake
    : public IIPCSenderCallback
    , public IIPCRecieverCallback
{
public:
    explicit IPCHandShake(DWORD appID, IIPCHandShakeCallback* callback);    // appID�����ֲ�ͬӦ�õ�IPC
    virtual ~IPCHandShake();

    DWORD listen();                     // �����������ӵ�����
    DWORD connect(DWORD suggestSize);   // ������������, suggestSize��ʾ�Ƽ��Ĺ����ڴ��С����λByte
    DWORD close();
protected:
    virtual void onIPCSenderLog(LogLevel level, const char* content);
    virtual void onIPCSenderClose();

    virtual void onIPCRecieverLog(LogLevel level, const char* content);
    virtual void onIPCRecieverClose();
    virtual DWORD onIPCReciverRecv(const void* data, size_t dataSize);
private:
    DWORD                                   m_appID;
    IIPCHandShakeCallback*                  m_callback;
    IPCRecieverConnection*                  m_listener;
};

/**************************************************************************/
#endif /* __IPCHANDSHAKE_H__ */
