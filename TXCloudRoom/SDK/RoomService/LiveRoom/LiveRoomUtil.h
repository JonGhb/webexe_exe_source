#ifndef __LIVEROOMUTIL_H__
#define __LIVEROOMUTIL_H__

#include <vector>
#include <string>
#include <assert.h>

/**
* \brief��Auth��Ȩ��Ϣ��ͨ��RoomService��̨API�ӿ�����õ�
*/
struct LRAuthData
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
* \brief����ɫ����
*/
enum LRRole
{
    LRNullRole,     // ��ɫδ֪��δ���뷿������˳�����
    LRMainRole,     // ������
    LRSubRole,      // С����
    LRAudience      // ����
};

/**
* \brief����Ա��Ϣ
*/
struct LRMemberData
{
	std::string userID;
	std::string userName;
	std::string userAvatar;
	std::string accelerateURL;
};

/**
* \brief��������Ϣ
*/
struct LRAudienceData
{
    std::string userID;
    std::string userInfo;
};

/**
* \brief��������Ϣ
*/
struct LRRoomData
{
	std::string roomID;
	std::string roomInfo;
	std::string roomCreator;
	std::string mixedPlayURL;
	int audienceCount;
	std::vector<LRMemberData> members;
};

/**
* \brief��������
*/
enum LRErrorCode
{
	LIVEROOM_SUCCESS = 0, // �ɹ�
	LIVEROOM_FAILED = -1, // ʧ��

	// ҵ���߼�
	LIVEROOM_ERR_SYSTEM_ERROR = -1001, // ϵͳ����
	LIVEROOM_ERR_REQUEST_TIMEOUT = -1002, // ����ʱ
	LIVEROOM_ERR_WRONG_JSON = -1003, // ����json��
	LIVEROOM_ERR_IM_LOGIN = -1004, // IM��¼ʧ��
	LIVEROOM_ERR_CREATE_ROOM = -1005, // ��������ʧ��
	LIVEROOM_ERR_ENTER_ROOM = -1006, // ���뷿��ʧ��
	LIVEROOM_ERR_PUSH_DISCONNECT = -1007, // �������ӶϿ�
	LIVEROOM_ERR_CAMERA_OCCUPY = -1008, // ����ͷռ��
	LIVEROOM_ERR_CAMERA_REMOVED = -1009, // ����ͷ���γ�
    LIVEROOM_ERR_CAMERA_MISSED = -1010, // �޿�������ͷ
    LIVEROOM_ERR_PLAY_DISCONNECT = -1011, // �������ӶϿ�

	// CGI
	LIVEROOM_ERR_WRONG_PARAMETER = -2001, // ��������
	LIVEROOM_ERR_AUTH_INVALID = -2002, // ��Ȩʧ�� - ����sign����
	LIVEROOM_ERR_DECOMPRESS_FAILED = -2003, // ��ѹʧ��
	LIVEROOM_ERR_DECODE_FAILED = -2004, // ����ʧ��
	LIVEROOM_ERR_FIELD_MISS = -2005, // �ֶ�ȱʧ
	LIVEROOM_ERR_FIELD_INVALID = -2006, // �ֶ���Ч
	LIVEROOM_ERR_UNKWON_CODE = -2007, // δ֪������
};

// CGI���������ת��ΪLRErrorCode������
static LRErrorCode adaptLiveErrorCode(int cgiErrorCode)
{
	LRErrorCode ec = LIVEROOM_FAILED;
	switch (cgiErrorCode)
	{
	case -1:
		ec = LIVEROOM_FAILED;
		break;
	case 0:
		ec = LIVEROOM_SUCCESS;
		break;
	case 1:
		ec = LIVEROOM_ERR_WRONG_PARAMETER;
		break;
	case 2:
		ec = LIVEROOM_ERR_AUTH_INVALID;
		break;
	case 3:
		ec = LIVEROOM_ERR_DECOMPRESS_FAILED;
		break;
	case 4:
		ec = LIVEROOM_ERR_DECODE_FAILED;
		break;
	case 5:
		ec = LIVEROOM_ERR_FIELD_MISS;
		break;
	case 6:
		ec = LIVEROOM_ERR_FIELD_INVALID;
		break;
	case 7:
		ec = LIVEROOM_ERR_AUTH_INVALID;
		break;
	default:
		ec = LIVEROOM_ERR_UNKWON_CODE;
		break;
	}

	return ec;
}

/**
* \brief��ִ�н��
*/
struct LRResult
{
	LRErrorCode ec;     // ������
	std::string msg;    // ��������
};

/**
* \brief����Ƶ��߱�
*/
enum LRAspectRatio
{
	LIVEROOM_ASPECT_RATIO_4_3 = 0,
	LIVEROOM_ASPECT_RATIO_16_9 = 1,
	LIVEROOM_ASPECT_RATIO_9_16 = 2,
};

/**
* \brief������Ԥ��ѡ��
*/
enum LRVideoQuality
{
	LIVEROOM_VIDEO_QUALITY_STANDARD_DEFINITION = 1,         // ���壺����׷�������ԵĿͻ�ʹ�ø�ѡ��
	LIVEROOM_VIDEO_QUALITY_HIGH_DEFINITION = 2,             // ���壺�������������Ҫ��Ŀͻ�ʹ�ø�ѡ��
	LIVEROOM_VIDEO_QUALITY_SUPER_DEFINITION = 3,            // ���壺������Ǵ����ۿ������Ƽ�ʹ��
};

/**
* \brief���������շ��
*/
enum LRBeautyStyle
{
    LIVEROOM_BEAUTY_STYLE_SMOOTH = 0,       // �⻬
    LIVEROOM_BEAUTY_STYLE_NATURE = 1,       // ��Ȼ
    LIVEROOM_BEAUTY_STYLE_BLUR = 2,         // ����
};

class ILoginLiveCallback
{
public:
	virtual ~ILoginLiveCallback() {}

	/**
	* \brief��login��¼
    * \param��res - ִ�н�����ο� LiveRoomUtil.h �ж���� LRResult �ṹ��
    * \param��authData - RoomService�ṩ�ĵ�¼��Ϣ������IM��ص������ֶΣ���login�ɹ��󣬻�ȡ��token�ֶ�
	*/
	virtual void onLogin(const LRResult& res, const LRAuthData& authData) = 0;
};

class IGetLiveRoomListCallback
{
public:
	virtual ~IGetLiveRoomListCallback() {}

	/**
	* \brief����ȡ�����б�
    * \param��res - ִ�н�����ο� LiveRoomUtil.h �ж���� LRResult �ṹ��
    * \param��rooms - ������Ϣ���б�
	*/
	virtual void onGetRoomList(const LRResult& res, const std::vector<LRRoomData>& rooms) = 0;
};

class ILiveRoomCallback
{
public:
	virtual ~ILiveRoomCallback() {}

	/**
	* \brief����������Ļص�
	* \param��res - ִ�н�����ο� LiveRoomUtil.h �ж���� LRResult �ṹ��
	* \param��roomID - ����ID
	*/
	virtual void onCreateRoom(const LRResult& res, const std::string& roomID) = 0;

	/**
	* \brief�����뷿��Ļص�
	* \param��res - ִ�н�����ο� LiveRoomUtil.h �ж���� LRResult �ṹ��
	*/
	virtual void onEnterRoom(const LRResult& res) = 0;

	/**
	* \brief��������Ϣ����Ļص�
	* \param��res - ִ�н�����ο� LiveRoomUtil.h �ж���� LRResult �ṹ��
	* \param��roomData - ������Ϣ���ο� LiveRoomUtil.h �ж���� LRRoomData �ṹ��
	*/
	virtual void onUpdateRoomData(const LRResult& res, const LRRoomData& roomData) = 0;

    /**
    * \brief����ѯ�����б�Ļص�
    * \param��res - ִ�н�����ο� LiveRoomUtil.h �ж���� LRResult �ṹ��
    * \param��rooms - ������Ϣ���б�
    */
    virtual void onGetAudienceList(const LRResult& res, const std::vector<LRAudienceData>& audiences) = 0;

	/**
	* \brief����Ա���뷿��Ļص�
	* \param��member - ��Ա��Ϣ���ο� LiveRoomUtil.h �ж���� LRMemberData �ṹ��
	*/
	virtual void onPusherJoin(const LRMemberData& member) = 0;

	/**
	* \brief����Ա�˳�����Ļص�
	* \param��member - ��Ա��Ϣ���ο� LiveRoomUtil.h �ж���� LRMemberData �ṹ��
	*/
	virtual void onPusherQuit(const LRMemberData& member) = 0;

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
	* \brief���յ��Զ�����Ϣ
	* \param��roomID - ����ID
	* \param userID - ������ID
	* \param userName - �������ǳ�
	* \param userAvatar - ������ͷ��
	* \param cmd - �Զ���cmd
	* \param message - �Զ�����Ϣ����
	*/
	virtual void onRecvRoomCustomMsg(const char * roomID, const char * userID, const char * userName, const char * userAvatar, const char * cmd, const char * message) = 0;

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
	* \param��res - ִ�н�����ο� LiveRoomUtil.h �ж���� LRResult �ṹ��
	* \param��userID - �û�ID
	*/
	virtual void onError(const LRResult& res, const std::string& userID) = 0;

	/**
	* \brief�����յ���������
	* \param��roomID - ����ID
	* \param userID - ������ID
	* \param userName - �������ǳ�
	* \param userAvatar - ������ͷ��
	*/
	virtual void onRecvJoinPusherRequest(const std::string& roomID, const std::string& userID, const std::string& userName, const std::string& userAvatar) = 0;

	/**
	* \brief�����յ�������������Ļظ�
	* \param��roomID - ����ID
	* \param msg - ��Ϣ
	*/
	virtual void onRecvAcceptJoinPusher(const std::string& roomID, const std::string& msg) = 0;

	/**
	* \brief�����յ��ܾ���������Ļظ�
	* \param��roomID - ����ID
	* \param msg - ��Ϣ
	*/
	virtual void onRecvRejectJoinPusher(const std::string& roomID, const std::string& msg) = 0;

	/**
	* \brief�����մ�������С������֪ͨ
	* \param��roomID - ����ID
	*/
	virtual void onRecvKickoutSubPusher(const std::string& roomID) = 0;
};

#endif /* __LIVEROOMUTIL_H__ */
