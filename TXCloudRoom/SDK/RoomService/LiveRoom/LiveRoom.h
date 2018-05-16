#ifndef __LIVEROOM_H__
#define __LIVEROOM_H__

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include "LiveRoomUtil.h"

#define MIC_DEVICE_NAME_MAX_SIZE    (512)

class LRBussiness;

class LiveRoom
{
private:
    LiveRoom();
    LiveRoom(const LiveRoom&);
    LiveRoom& operator =(const LiveRoom&);
public:
    virtual ~LiveRoom();

    /**
    * \brief����ȡLiveRoom������ͨ����������LiveRoom�Ľӿ�
    */
    static LiveRoom* instance();

    /**
    * \brief�����ûص� LiveRoom �Ļص��������� LiveRoom ���ڲ�״̬�ͽӿڵ�ִ�н��
    * \param��callback  - ILiveRoomCallback ���͵Ĵ���ָ��
    * \return ��
    */
    void setCallback(ILiveRoomCallback * callback);

    /**
    * \brief�����ô����ַ
    * \param��ip - �����������ip
    * \param��port - ����������Ķ˿�
    * \return ��
    */
    void setProxy(const std::string& ip, unsigned short port);

    /**
    * \brief����¼ҵ�������RoomService����¼����ܹ�����ʹ�������ӿں�ʹ��IM����
    * \param��serverDomain - RoomService��URL��ַ����ȫ������������https��������
    * \param��authData - RoomService�ṩ�ĵ�¼��Ϣ������IM��ص������ֶΣ���login�ɹ��󣬻�ȡ��token�ֶ�
    * \param��callback - ILoginLiveCallback ���͵Ĵ���ָ�룬�ص�login�Ľ��
    */
    void login(const std::string & serverDomain, const LRAuthData & authData, ILoginLiveCallback* callback);

	/**
	* \brief��¼�Ʊ�����Ƶ����ע����startLocalPreview֮ǰ����
	* \param��picture_id - ����ͼˮӡID���������ã�Ĭ��Ϊ - 1������ͼ��ʾΪ��ɫ����
	*/
	void recordVideo(int picture_id = -1);

    /**
    * \brief���ǳ�ҵ�������RoomService����ע����leaveRoom���ú��ٵ���logout������leaveRoom�����ʧ��
    */
    void logout();

    /**
    * \brief����ȡ�����б����������Ƚ϶�ʱ�����Է�ҳ��ȡ
    * \param��index - ��ҳ��ȡ����ʼĬ�Ͽ�����Ϊ0��������ȡΪ��ʼ�������������һ������index=0, cnt=5,��ȡ�ڶ�ҳʱ����index=5��
    * \param��cnt - ÿ�ε��ã���෵�ط��������0��ʾ�������������ķ���
    * \param��callback - IGetLiveRoomListCallback ���͵Ĵ���ָ�룬��ѯ����Ļص�
    */
    void getRoomList(int index, int cnt, IGetLiveRoomListCallback* callback);

    /**
    * \brief����ȡ�����б�ֻ����������뷿��� 30 λ����
    * \param��roomID - ����ID���� getRoomList �ӿڷ����б��в�ѯ�õ�
    */
    void getAudienceList(const std::string& roomID);

    /**
    * \brief���������䣬��̨�ķ����б��л����һ���·��䣬ͬʱ�����˻��������ģʽ
    * \param��roomID - ����ID����������ַ��������̨��Ϊ������roomID�����򣬴����roomID��Ϊ��������ID
    * \param��roomInfo - �Զ������ݣ����ֶΰ����ڷ�����Ϣ�У��Ƽ����� roomInfo ����Ϊ json ��ʽ�����������к�ǿ����չ��
    */
    void createRoom(const std::string& roomID, const std::string& roomInfo);

    /**
    * \brief�����뷿��ۿ���Ƶ
    * \param��roomID - Ҫ����ķ���ID���� getRoomList �ӿڷ����б��в�ѯ�õ�
    * \param��rendHwnd - ����Ԥ������� HWND
    * \param��rect - ָ����Ƶͼ���� HWND �ϵ���Ⱦ����
    */
    void enterRoom(const std::string& roomID, HWND rendHwnd, const RECT & rect);

    /**
    * \brief���뿪���䣬����Ǵ��������������ᱻ��̨���٣������С�������߹��ڣ���Ӱ�������˼����ۿ�
    */
    void leaveRoom();

    /**
    * \brief���ڷ����ڣ�������ͨ�ı���Ϣ������ֱ�������У����͵�Ļ
    * \param��msg - �ı���Ϣ
    */
    void sendRoomTextMsg(const char * msg);

    /**
    * \brief���ڷ����ڣ�������ͨ�Զ�����Ϣ������ֱ�������У����͵��ޡ��ͻ�����Ϣ
    * \param��cmd - �Զ���cmd���շ�˫��Э�̺õ�cmd
    * \param��msg - �Զ�����Ϣ
    */
    void sendRoomCustomMsg(const char * cmd, const char * msg);

    /**
    * \brief������C2C�Զ�����Ϣ
    * \param��cmd - �Զ���cmd���շ�˫��Э�̺õ�cmd
    * \param��msg - �Զ�����Ϣ
    */
    void sendC2CCustomMsg(const char* userID, const char * cmd, const char * msg);

    /**
    * \brief������Ĭ�ϵ�����ͷԤ��
    * \param��rendHwnd - ����Ԥ������� HWND��Ŀǰ SDK �ǲ��� OpenGL �� HWND �ϻ���ͼ���,rendHwnd = nullʱ����Ԥ����Ƶ
    * \param��rect - ָ����Ƶͼ���� HWND �ϵ���Ⱦ����
    */
    void startLocalPreview(HWND rendHwnd, const RECT & rect);

    /**
    * \brief����������ͷԤ�����򣬵���ָ���ı��� HWND �Ĵ��ڳߴ緢���仯ʱ������ͨ������������µ�����Ƶ��Ⱦ����
    * \param��rendHwnd - ����Ԥ������� HWND
    * \param��rect - ָ����Ƶͼ���� HWND �ϵ���Ⱦ����
    * \return ��
    */
    void updateLocalPreview(HWND rendHwnd, const RECT &rect);

    /**
    * \brief���ر�����ͷԤ��
    */
    void stopLocalPreview();

    /**
    * \brief�����ŷ�����������������Ƶ
    * \param��rendHwnd - ����Ԥ������� HWND
    * \param��rect - ָ����Ƶͼ���� HWND �ϵ���Ⱦ����
    * \param��userID - �û�ID
    */
    void addRemoteView(HWND rendHwnd, const RECT & rect, const char * userID);

    /**
    * \brief��ֹͣ����������������Ƶ
    * \param��userID - �û�ID
    */
    void removeRemoteView(const char * userID);

    /**
    * \brief��������Ļ����
    * \param��rendHwnd - ����Ԥ������� HWND��Ŀǰ SDK �ǲ��� OpenGL �� HWND �ϻ���ͼ���,rendHwnd = nullʱ����Ԥ����Ƶ
    * \param��captureHwnd - ָ��¼ȡ���ڣ���ΪNULL���� captureRect ����Ч������¼ȡ������Ļ������ΪNULL����¼ȡ������ڵĻ���
    * \param��renderRect - ָ����Ƶͼ���� rendHwnd �ϵ���Ⱦ����
    * \param��captureRect - ָ��¼ȡ���ڿͻ���������
    * \return �ɹ� or ʧ��
    */
    bool startScreenPreview(HWND rendHwnd, HWND captureHwnd, const RECT & renderRect, const RECT & captureRect);

    /**
    * \brief���ر���Ļ����
    */
    void stopScreenPreview();

    /**
    * \brief�������ӿ�
    * \param��mute - �Ƿ���
    */
    void setMute(bool mute);

    /**
    * \brief�����û�������Ԥ��ѡ��
    * \param��quality - ���ʣ��ο� LiveRoomUtil.h �ж���� LRVideoQuality ö��ֵ
    * \param��ratio - ��߱ȣ��ο� LiveRoomUtil.h �ж���� LRAspectRatio ö��ֵ
    */
    void setVideoQuality(LRVideoQuality quality, LRAspectRatio ratio);

    /**
    * \brief���������պ�����Ч��
    * \param��beautyStyle    - �ο� LiveRoomUtil.h �ж���� LRBeautyStyle ö��ֵ
    * \param��beautyLevel    - ���ռ���ȡֵ��Χ 1 ~ 9�� 0 ��ʾ�رգ�1 ~ 9ֵԽ��Ч��Խ����
    * \param��whitenessLevel - ���׼���ȡֵ��Χ 1 ~ 9�� 0 ��ʾ�رգ�1 ~ 9ֵԽ��Ч��Խ����
    * \return:��
    */
    void setBeautyStyle(LRBeautyStyle beautyStyle, int beautyLevel, int whitenessLevel);

    /**
    * \brief�����ڶ˷�����������
    */
    void requestJoinPusher();

    /**
    * \brief��������������������֪ͨ��������
    * \param��userID - �û�ID
    */
    void acceptJoinPusher(const std::string& userID);

    /**
    * \brief���������ܾ���������֪ͨ��������
    * \param��userID - �û�ID
    * \param��reason - �ܾ���ԭ��
    */
    void rejectJoinPusher(const std::string& userID, const std::string& reason);

    /**
    * \brief���������ߵ�ĳһ��С����
    * \param��userID - �û�ID
    */
    void kickoutSubPusher(const std::string& userID);

	/**
	* \brief��ö�ٵ�ǰ������ͷ�����һ̨Windowsͬʱ��װ�˶������ͷ����ô�˺�����ȡ���õ�����ͷ����������
	* \param��camerasName - ÿ������ͷ������
	* \param: capacity - camerasName ����Ĵ�С
	* \return����ǰWindows���õ� ����ͷ������
	* \attention: �ú������Է����ε��ã���һ�ε������� camerasName Ϊ NULL�����Ի������ͷ�������ڶ��ε���ʱ�Ϳ��Դ���һ����С�ոպ��ʵ� camerasName
	*/
	int enumCameras(wchar_t **camerasName = NULL, size_t capacity = 0);
	
	/**
	* \brief���л�����ͷ��֧���������ж�̬�л���
	* \param��cameraIndex : ����ͷ��Ҫ��ȡֵ���أ�  0 ~ (����ͷ���� - 1)
	* \return:��
	*/
	void switchCamera(int cameraIndex);

	/**
	* \brief����ѯ���õ���˷��豸������
	* \return������ѯ�ɹ����򷵻�ֵ>=0������ѯʧ�ܣ��򷵻�ֵΪ-1
	*/
	int micDeviceCount();

	/**
	* \brief����ѯ��˷��豸������
	* \param��index - ��˷��豸��������Ҫ��indexֵС�� micDeviceCount �ӿڵķ���ֵ
	* \param��name - ���ڴ����˷��豸�����Ƶ��ַ������飬�����СҪ�� <= MIC_DEVICE_NAME_MAX_SIZE����ѯ�õ����ַ������ʽ��UTF-8
	* \return������ѯ�ɹ����򷵻�ֵtrue������ѯʧ�ܻ���index�Ƿ����򷵻�ֵΪfalse
	*/
	bool micDeviceName(unsigned int index, char name[MIC_DEVICE_NAME_MAX_SIZE]);

	/**
	* \brief��ѡ��ָ������˷���Ϊ¼���豸�������øýӿ�ʱ��Ĭ��ѡ������Ϊ0����˷�
	* \param��index - ��˷��豸��������Ҫ��indexֵС�� micDeviceCount �ӿڵķ���ֵ
	*/
	void selectMicDevice(unsigned int index);

	/**
	* \brief����ѯ��ѡ����˷������
	* \return������ֵ����Χ��[0, 65535]
	*/
	unsigned int micVolume();

	/**
	* \brief��������ѡ����˷������
	* \param��volume - ���õ�������С����Χ��[0, 65535]
	*/
	void setMicVolume(unsigned int volume);
protected:
    LRBussiness* m_impl;
};

#endif /* __LIVEROOM_H__ */
