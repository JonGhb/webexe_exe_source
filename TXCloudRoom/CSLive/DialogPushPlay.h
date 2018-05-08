#pragma once

#include <QDialog>
#include "ui_DialogPushPlay.h"
#include "TXLivePlayer.h"
#include "TXLivePusher.h"
#include "TXLiveSDKEventDef.h"
#include <set> 
#include <functional>

typedef std::function<void(void)>     txfunction;

class DialogPushPlay : public QDialog
	, public TXLivePlayerCallback
	, public TXLivePusherCallback
{
	Q_OBJECT

public:
	DialogPushPlay(QWidget *parent = Q_NULLPTR);
	~DialogPushPlay();

	void startPush(QString url);
	void startPlay(QString url);
	void setTitle(QString title);
    void setLogo(QString logo);
    void setProxy(const std::string& ip, unsigned short port);

    void quit();
public:
	virtual void onEventCallback(int eventId, const int paramCount, const char **paramKeys, const char **paramValues, void *pUserData) override;

protected:
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	bool eventFilter(QObject* pObj, QEvent* pEvent) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

signals:
	void update_event(int status);
	void dispatch(txfunction func);

private slots:
	void on_btn_close_clicked();
	void on_btn_min_clicked();
	void on_update_event(int status); //1.��������ʧ�� 2.��������ʧ�� 3.����ͷ��ռ�� 4.������ʼ 5.������ʼ
	void handle(txfunction func);

private:
	void stopPush();
	void stopPlay();

	QPoint mousePressedPosition;
	QPoint windowPositionAsDrag;

	TXLivePlayer m_player;
	TXLivePusher m_pusher;
	bool m_pushing;
	bool m_playing;
	int m_cameraCount;
	bool m_pushBegin;

	bool m_bUserIsResizing;
	Ui::DialogPushPlay ui;
};
