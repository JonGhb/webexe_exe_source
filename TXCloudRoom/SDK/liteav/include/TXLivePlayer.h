#ifndef _TXLivePlayer_h_
#define _TXLivePlayer_h_

#ifdef LITEAV_EXPORTS
#define LITEAV_API __declspec(dllexport)
#else
#define LITEAV_API __declspec(dllimport)
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include "TXLiveSDKTypeDef.h"

#define SPEAKER_DEVICE_NAME_MAX_SIZE    (512)

class TXLivePlayerCallback;
class TXLivePlayerImpl;

class LITEAV_API TXLivePlayer
{
public:
	TXLivePlayer();
	virtual ~TXLivePlayer();

	/**
	* \brief：设置回调 TXLivePlayer 的回调代理，监听播放事件
	* \param：callback  - TXLivePlayerCallback 类型的代理指针
	* \param：pUserData - 透传用户数据到 TXLivePusherCallback 的回调函数,一般情况下传 NULL 就可以了
	* \return 无
	*/
	void setCallback(TXLivePlayerCallback *callback, void *pUserData);

    /**
    * \brief：查询可用的扬声器设备的数量
    * \return：若查询成功，则返回值>=0；若查询失败，则返回值为-1
    */
    int speakerDeviceCount() const;

    /**
    * \brief：查询扬声器设备的名称
    * \param：index - 扬声器设备的索引，要求index值小于 speakerDeviceCount 接口的返回值
    * \param：name - 用于存放扬声器设备的名称的字符串数组，数组大小要求 <= SPEAKER_DEVICE_NAME_MAX_SIZE，查询得到的字符编码格式是UTF-8
    * \return：若查询成功，则返回值true；若查询失败或者index非法，则返回值为false
    */
    bool speakerDeviceName(unsigned int index, char name[SPEAKER_DEVICE_NAME_MAX_SIZE]);

    /**
    * \brief：选择指定的扬声器作为音频播放的设备，不调用该接口时，默认选择索引为0的扬声器
    * \param：index - 扬声器设备的索引，要求index值小于 speakerDeviceCount 接口的返回值
    */
    void selectSpeakerDevice(unsigned int index);

    /**
    * \brief：查询SDK播放的音量，注意查询得到不是系统扬声器的音量大小
    * \return：音量值，范围是[0, 65535]
    */
    unsigned int speakerVolume();

    /**
    * \brief：设置SDK播放的音量，注意设置的不是系统扬声器的音量大小
    * \param：volume - 设置的音量大小，范围是[0, 65535]
    */
    void setSpeakerVolume(unsigned int volume);

	/**
	* \brief：设置视频图像渲染
	* \param：rendHwnd - 承载视频画面的 HWND，目前 SDK 是采用 OpenGL 向 HWND 上绘制图像的
	* \param：rect     - 指定视频图像在 HWND 上的渲染区域，比如 (0，0，width, height) 表示拿整个 HWND 作为渲染画布
	* \return:无
	*/
	void setRenderFrame(HWND hWnd, const RECT &rect);

	/**
	* \brief：重设图像渲染区域，当您指定的 HWND 的窗口尺寸发生变化时，可以通过这个函数重新调整视频渲染区域
	* \param：rendHwnd - 承载视频画面的 HWND
	* \param：rect     - 指定视频图像在 HWND 上的渲染区域，比如 (0，0，width, height) 表示拿整个 HWND 作为渲染画布
	* \return:无
	*/
	void updateRenderFrame(HWND hWnd, const RECT &rect);

	/**
	* \brief：关闭图像渲染
	*/
	void closeRenderFrame();

	/**
	* \brief：开始播放，请在 startPlay 之前 setRenderFrame
    * \param：url   - 视频播放 URL
    * \param：type  - 播放类型，参考 TXLiveSDKTypeDef.h 中定义的 TXEPlayType 枚举值
	* \return：无 
	*/
	void startPlay(const char * url, TXEPlayType type);

	/**
	* \brief：停止播放
	*/
	void stopPlay();

	/**
	* \brief：暂停播放
	*/
	void pause();

	/**
	* \brief：恢复播放
	*/
	void resume();

	/**
	* \brief：是否正在播放
	*/
	bool isPlaying();

	/**
	* \brief：静音接口
	* \param：mute - 是否静音
	* \return:无
	*/
	void setMute(bool mute);

    /**
    * \brief：设置图像的渲染（填充）模式
    * \param：mode - 参考 TXLiveSDKTypeDef.h 中定义的 TXERenderMode 枚举值
    * \return:无
    */
    void setRenderMode(TXERenderMode mode);

    /**
    * \brief：设置图像的顺时针旋转角度
    * \param：rotation - 参考 TXLiveSDKTypeDef.h 中定义的 TXEVideoRotation 枚举值
    * \return:无
    */
    void setRotation(TXEVideoRotation rotation);

	/**
	* \brief：设置渲染的镜像效果
	* \param：mirror - true表示画面左右反转，false表示保持原样
	* \return:无
	*/
	void setRenderYMirror(bool mirror);

    /**
    * \brief：设置视频编码格式，默认格式是TXE_OUTPUT_VIDEO_WITHOUT_OUTPUT
    * \param：format - 视频编码格式，参考 TXLiveSDKTypeDef.h 中定义的 TXEOutputVideoFormat 枚举值
    * \return:无
    */
    void setOutputVideoFormat(TXEOutputVideoFormat format);

	/**
	* \brief：截图当前拉流的图像到本地，
	* \param：filePath - 存储路径，
	* \param: length - 路径大小
	* \return：0成功，非0失败
	* \errorRet:  -1:失败，-2路径非法，-3文件存在，-4未拉流
	*/
	int captureVideoSnapShot(const wchar_t * filePath, unsigned int length);
protected:
    TXLivePlayerImpl* m_impl;
};

#endif
