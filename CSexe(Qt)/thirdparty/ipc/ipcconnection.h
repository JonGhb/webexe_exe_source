/**************************************************************************
    Copyright:      Copyright ? 1998 - 2017 Tencent. All Rights Reserved
    Created:        2017-4-6 11:30:41
    Filename:       ipcconnection.h

    Description:
***************************************************************************/

#ifndef __IPCCONNECTION_H__
#define __IPCCONNECTION_H__

#include "ipcchannel.h"

/**************************************************************************/

class IPCConnection;

class IIPCConnectionCallback
{
public:
    virtual ~IIPCConnectionCallback() {}

    // ���ӵ���һ�������˳������쳣crash�����ᴥ���ûص�
    // ע�⣬��Ҫ��onClose�ص����ͷ�IPCConnection����������������Ҳ����ǧ��Ҫ��onClose�ص���delete connection
    virtual void onClose(IPCConnection* connection) = 0;

    // ���յ����ݣ���Ҫ����ʱ����
    virtual DWORD onRecv(IPCConnection* connection, const void* data, size_t dataSize) = 0;

    // ��ӡlog
    virtual void onLog(LogLevel level, const char* content) = 0;
};

class IPCConnection
    : public IIPCSenderCallback
    , public IIPCRecieverCallback
{
    friend class IPCHandShake;
public:
    explicit IPCConnection(IIPCConnectionCallback* callback);
    virtual ~IPCConnection();

    DWORD send(const void* data, size_t dataSize, DWORD timeout);   // ��������
    DWORD close();
protected:
    DWORD openReciever(DWORD appID, DWORD aRecieverPid, DWORD aSenderPid, DWORD timestamp, DWORD suggestSize);
    DWORD closeReciever();

    DWORD openSender(DWORD appID, DWORD aRecieverPid, DWORD aSenderPid, DWORD timestamp, DWORD suggestSize);
    DWORD closeSender(bool notifyPeer);

    virtual void onIPCSenderLog(LogLevel level, const char* content);
    virtual void onIPCSenderClose();

    virtual void onIPCRecieverLog(LogLevel level, const char* content);
    virtual void onIPCRecieverClose();
    virtual DWORD onIPCReciverRecv(const void* data, size_t dataSize);
private:
    IIPCConnectionCallback*                 m_callback;
    IPCSenderConnection*                    m_sender;
    IPCRecieverConnection*                  m_reciver;
};

/**************************************************************************/
#endif /* __IPCCONNECTION_H__ */
