#ifndef __RTCROOMUTIL_H__
#define __RTCROOMUTIL_H__

#include <vector>
#include <string>
#include <assert.h>

/**
* \brief��Auth��Ȩ��Ϣ
*/
struct RTCAuthData
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
* \brief����Ա��Ϣ
*/
struct RTCMemberData
{
    std::string userID;
    std::string userName;
    std::string userAvatar;
    std::string accelerateURL;
};

/**
* \brief��������Ϣ
*/
struct RTCRoomData
{
    std::string roomID;
    std::string roomInfo;
    std::string roomCreator;
    std::vector<RTCMemberData> members;
};

/**
* \brief��������
*/
enum RTCErrorCode
{
    RTCROOM_SUCCESS = 0, // �ɹ�
    RTCROOM_FAILED = -1, // ʧ��

    // ҵ���߼�
    RTCROOM_ERR_SYSTEM_ERROR = -1001, // ϵͳ����
    RTCROOM_ERR_REQUEST_TIMEOUT = -1002, // ����ʱ
    RTCROOM_ERR_WRONG_JSON = -1003, // ����json��
    RTCROOM_ERR_IM_LOGIN = -1004, // IM��¼ʧ��
    RTCROOM_ERR_CREATE_ROOM = -1005, // ��������ʧ��
    RTCROOM_ERR_ENTER_ROOM = -1006, // ���뷿��ʧ��
    RTCROOM_ERR_PUSH_DISCONNECT = -1007, // �������ӶϿ�
    RTCROOM_ERR_CAMERA_OCCUPY = -1008, // ����ͷռ��
	RTCROOM_ERR_CAMERA_REMOVED = -1009, // ����ͷ���γ�
    RTCROOM_ERR_CAMERA_MISSED = -1010, // �޿�������ͷ
    RTCROOM_ERR_PLAY_DISCONNECT = -1011, // �������ӶϿ�

    // CGI
    RTCROOM_ERR_WRONG_PARAMETER = -2001, // ��������
    RTCROOM_ERR_AUTH_INVALID = -2002, // ��Ȩʧ�� - ����sign����
    RTCROOM_ERR_DECOMPRESS_FAILED = -2003, // ��ѹʧ��
    RTCROOM_ERR_DECODE_FAILED = -2004, // ����ʧ��
    RTCROOM_ERR_FIELD_MISS = -2005, // �ֶ�ȱʧ
    RTCROOM_ERR_FIELD_INVALID = -2006, // �ֶ���Ч
    RTCROOM_ERR_UNKWON_CODE = -2007, // δ֪������
};

// CGI���������ת��ΪLRErrorCode������
static RTCErrorCode adaptRTCErrorCode(int cgiErrorCode)
{
    RTCErrorCode ec = RTCROOM_FAILED;
    switch (cgiErrorCode)
    {
    case -1:
        ec = RTCROOM_FAILED;
        break;
    case 0:
        ec = RTCROOM_SUCCESS;
        break;
    case 1:
        ec = RTCROOM_ERR_WRONG_PARAMETER;
        break;
    case 2:
        ec = RTCROOM_ERR_AUTH_INVALID;
        break;
    case 3:
        ec = RTCROOM_ERR_DECOMPRESS_FAILED;
        break;
    case 4:
        ec = RTCROOM_ERR_DECODE_FAILED;
        break;
    case 5:
        ec = RTCROOM_ERR_FIELD_MISS;
        break;
    case 6:
        ec = RTCROOM_ERR_FIELD_INVALID;
        break;
    case 7:
        ec = RTCROOM_ERR_AUTH_INVALID;
        break;
    default:
        ec = RTCROOM_ERR_UNKWON_CODE;
        break;
    }

    return ec;
}

struct RTCResult
{
    RTCErrorCode ec;     // ������
    std::string msg;    // ��������
};

/**
* \brief����Ƶ��߱�
*/
enum RTCAspectRatio
{
    RTCROOM_ASPECT_RATIO_4_3 = 0,
    RTCROOM_ASPECT_RATIO_16_9 = 1,
    RTCROOM_ASPECT_RATIO_9_16 = 2,
};

/**
* \brief������Ԥ��ѡ��
*/
enum RTCVideoQuality
{
    RTCROOM_VIDEO_QUALITY_STANDARD_DEFINITION = 1,         // ���壺����׷�������ԵĿͻ�ʹ�ø�ѡ��
    RTCROOM_VIDEO_QUALITY_HIGH_DEFINITION = 2,             // ���壺�������������Ҫ��Ŀͻ�ʹ�ø�ѡ��
    RTCROOM_VIDEO_QUALITY_SUPER_DEFINITION = 3,            // ���壺������Ǵ����ۿ������Ƽ�ʹ��
};

/**
* \brief���������շ��
*/
enum RTCBeautyStyle
{
    RTCROOM_BEAUTY_STYLE_SMOOTH = 0,        // �⻬
    RTCROOM_BEAUTY_STYLE_NATURE = 1,        // ��Ȼ
    RTCROOM_BEAUTY_STYLE_BLUR = 2,          // ����
};

class ILoginRTCCallback
{
public:
	virtual ~ILoginRTCCallback() {}

    /**
    * \brief��login��¼
    * \param��res - ִ�н�����ο� RTCRoomUtil.h �ж���� RTCResult �ṹ��
    * \param��authData - RoomService�ṩ�ĵ�¼��Ϣ������IM��ص������ֶΣ���login�ɹ��󣬻�ȡ��token�ֶ�
    */
	virtual void onLogin(const RTCResult& res, const RTCAuthData& authData) = 0;
};

class IGetRTCRoomListCallback
{
public:
    virtual ~IGetRTCRoomListCallback() {}

    /**
    * \brief����ȡ�����б�
    * \param��res - ִ�н�����ο� RTCRoomUtil.h �ж���� RTCResult �ṹ��
    * \param��rooms - ������Ϣ���б�
    */
    virtual void onGetRoomList(const RTCResult& res, const std::vector<RTCRoomData>& rooms) = 0;
};

class IRTCRoomCallback
{
public:
    virtual ~IRTCRoomCallback() {}

    /**
    * \brief����������Ļص�
    * \param��res - ִ�н�����ο� RTCRoomUtil.h �ж���� RTCResult �ṹ��
    * \param��roomID - ����ID
    */
    virtual void onCreateRoom(const RTCResult& res, const std::string& roomID) = 0;

    /**
    * \brief�����뷿��Ļص�
    * \param��res - ִ�н�����ο� RTCRoomUtil.h �ж���� RTCResult �ṹ��
    */
    virtual void onEnterRoom(const RTCResult& res) = 0;

    /**
    * \brief��������Ϣ����Ļص�
    * \param��res - ִ�н�����ο� RTCRoomUtil.h �ж���� RTCResult �ṹ��
    * \param��roomData - ������Ϣ���ο� RTCRoomUtil.h �ж���� LRRoomData �ṹ��
    */
    virtual void onUpdateRoomData(const RTCResult& res, const RTCRoomData& roomData) = 0;

    /**
    * \brief����Ա���뷿��Ļص�
    * \param��member - ��Ա��Ϣ���ο� RTCRoomUtil.h �ж���� LRMemberData �ṹ��
    */
    virtual void onPusherJoin(const RTCMemberData& member) = 0;

    /**
    * \brief����Ա�˳�����Ļص�
    * \param��member - ��Ա��Ϣ���ο� RTCRoomUtil.h �ж���� LRMemberData �ṹ��
    */
    virtual void onPusherQuit(const RTCMemberData& member) = 0;

    /**
    * \brief�������ɢ�Ļص�
    * \param��roomID - ����ID
    */
	virtual void onRoomClosed(const std::string& roomID) = 0;

	/**
	* \brief���յ���ͨ�ı���Ϣ
	* \param��roomID - ����ID
	* \param userID - ������ID
	* \param userName - �������ǳ�
	* \param userAvatar - ������ͷ��
	* \param message - �ı���Ϣ����
	*/
	virtual void onRecvRoomTextMsg(const char * roomID, const char * userID, const char * userName, const char * userAvatar, const char * msg) = 0;

	/**
	* \brief���յ������Զ�����Ϣ
	* \param��roomID - ����ID
	* \param userID - ������ID
	* \param userName - �������ǳ�
	* \param userAvatar - ������ͷ��
	* \param cmd - �Զ���cmd
	* \param message - �Զ�����Ϣ����
	*/
	virtual void onRecvRoomCustomMsg(const char * roomID, const char * userID, const char * userName, const char * userAvatar, const char * cmd, const char * msg) = 0;

    /**
    * \brief���յ�C2C�Զ�����Ϣ
    * \param��roomID - ����ID
    * \param userID - ������ID
    * \param userName - �������ǳ�
    * \param userAvatar - ������ͷ��
    * \param cmd - �Զ���cmd
    * \param message - �Զ�����Ϣ����
    */
    virtual void onRecvC2CCustomMsg(const char * userID, const char * userName, const char * userAvatar, const char * cmd, const char * msg) = 0;

    /**
    * \brief��ͬһ���˺��ظ���¼���ߺ�̨ǿ�����ߣ����ᴥ�����¼�
    */
    virtual void onTIMKickOffline() = 0;

    /**
    * \brief��LiveRoom�ڲ����������֪ͨ
    * \param��res - ִ�н�����ο� RTCRoomUtil.h �ж���� RTCResult �ṹ��
    * \param��userID - �û�ID
    */
    virtual void onError(const RTCResult& res, const std::string& userID) = 0;
};

#endif
