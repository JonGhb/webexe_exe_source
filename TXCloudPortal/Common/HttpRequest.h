#ifndef __RTCRHttpRequest_H__
#define __RTCRHttpRequest_H__

#include "HttpClient.h"
#include "TaskQueue.h"
#include "jsoncpp/json.h"

#include <string>
#include <vector>
#include <functional>

/**
* \brief��Auth��Ȩ��Ϣ
*/
struct AuthData
{
    int sdkAppID;
    std::string accountType;
    std::string userID;
    std::string userSig;
    std::string userName;
    std::string userAvatar;
    std::string token;
};

/**
* \brief��������Ϣ
*/
struct RoomData
{
    std::string roomID;
    std::string roomInfo;
	std::string roomType;
};

/**
* \brief��������
*/
enum ErrorCode
{
    ROOM_SUCCESS = 0, // �ɹ�
    ROOM_FAILED = -1, // ʧ��

    // ҵ���߼�
    ROOM_ERR_SYSTEM_ERROR = -1001, // ϵͳ����
    ROOM_ERR_REQUEST_TIMEOUT = -1002, // ����ʱ
    ROOM_ERR_WRONG_JSON = -1003, // ����json��
    ROOM_ERR_IM_LOGIN = -1004, // IM��¼ʧ��
    ROOM_ERR_CREATE_ROOM = -1005, // ��������ʧ��
    ROOM_ERR_ENTER_ROOM = -1006, // ���뷿��ʧ��
    ROOM_ERR_PUSH_DISCONNECT = -1007, // �������ӶϿ�
    ROOM_ERR_CAMERA_OCCUPY = -1008, // ����ͷռ��
    ROOM_ERR_CAMERA_REMOVED = -1009, // ����ͷ���γ�
    ROOM_ERR_PLAY_DISCONNECT = -1010, // �������ӶϿ�

    // CGI
    ROOM_ERR_WRONG_PARAMETER = -2001, // ��������
    ROOM_ERR_AUTH_INVALID = -2002, // ��Ȩʧ�� - ����sign����
    ROOM_ERR_DECOMPRESS_FAILED = -2003, // ��ѹʧ��
    ROOM_ERR_DECODE_FAILED = -2004, // ����ʧ��
    ROOM_ERR_FIELD_MISS = -2005, // �ֶ�ȱʧ
    ROOM_ERR_FIELD_INVALID = -2006, // �ֶ���Ч
    ROOM_ERR_UNKWON_CODE = -2007, // δ֪������
};

// CGI���������ת��ΪLRErrorCode������
static ErrorCode adaptRTCErrorCode(int cgiErrorCode)
{
    ErrorCode ec = ROOM_FAILED;
    switch (cgiErrorCode)
    {
    case -1:
        ec = ROOM_FAILED;
        break;
    case 0:
        ec = ROOM_SUCCESS;
        break;
    case 1:
        ec = ROOM_ERR_WRONG_PARAMETER;
        break;
    case 2:
        ec = ROOM_ERR_AUTH_INVALID;
        break;
    case 3:
        ec = ROOM_ERR_DECOMPRESS_FAILED;
        break;
    case 4:
        ec = ROOM_ERR_DECODE_FAILED;
        break;
    case 5:
        ec = ROOM_ERR_FIELD_MISS;
        break;
    case 6:
        ec = ROOM_ERR_FIELD_INVALID;
        break;
    case 7:
        ec = ROOM_ERR_AUTH_INVALID;
        break;
    default:
        ec = ROOM_ERR_UNKWON_CODE;
        break;
    }

    return ec;
}

struct Result
{
    ErrorCode ec;     // ������
    std::string msg;    // ��������
};

typedef std::function<void(void)> reqfunction;

class HttpRequest
{
public:
    HttpRequest(const std::string& domain);
    ~HttpRequest();

    void close();

    typedef std::function<void(const Result& res, const AuthData& authData)> getLoginInfoFunc;
    void getLoginInfo(const std::string& userID, getLoginInfoFunc func);

    typedef std::function<void(const Result& res, const std::string& roomID)> createRoomFunc;
    void createRoom(const std::string& roomID, const std::string& userID, const std::string& roomInfo, const std::string& roomType, createRoomFunc func);

    typedef std::function<void(const Result& res)> destroyRoomFunc;
    void destroyRoom(const std::string& roomID, const std::string& roomType, destroyRoomFunc func);   // ͬ���ӿ�

    typedef std::function<void(const Result& res, const std::vector<RoomData>& roomList)> getRoomListFunc;
    void getRoomList(int index, int cnt, const std::string& roomType, getRoomListFunc func);

    typedef std::function<void(const Result& res)> heardbeatFunc;
    void heartbeat(const std::string& roomID, const std::string& roomType, heardbeatFunc func);
private:
    std::string m_domain;
    HttpClient m_httpClient;
    TaskQueue m_taskQueue;
};


#endif /* __RTCRHttpRequest_H__ */
