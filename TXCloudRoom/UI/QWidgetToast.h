#pragma once
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QTimer>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class QWidgetToast : public QWidget
{
	Q_OBJECT
public:
	explicit QWidgetToast(QWidget *parent = 0);
	~QWidgetToast();

	//Ĭ����ʾ3�룬�޽��������Ч�������������ӿڿ��Ը������ã�����Ҫ��setText֮ǰʹ�á�
	//��ʾʱ�������Ϊ[1000,10000]����
	void setDuration(int nMSecond);
	void setCloseOut(bool closeOut);

	void setText(const QString & text);

protected:
	void paintEvent(QPaintEvent *e);
	void showEvent(QShowEvent *e);
signals:

private slots :
	void onTimerStayOut();
	void onTimerCloseOut();//���������
private:
	QLabel* m_pLabel;
	QTimer * m_pTimer;
	QTimer * m_pCloseTimer;
	qreal m_dTransparent;
	RECT m_parentRect;

	int m_nMSecond;
	bool m_bCloseOut;
};