#include "MainDialog.h"
#include "Application.h"
#include "jsoncpp/json.h"

#include <QMouseEvent>
#include <ctime>

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , m_csLiveSetting(nullptr)
    , m_liveRoomList(nullptr)
    , m_RTCRoomList(nullptr)
{
    ui.setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

MainDialog::~MainDialog()
{
    if (nullptr != m_csLiveSetting)
    {
        m_csLiveSetting->close();
        delete m_csLiveSetting;
        m_csLiveSetting = nullptr;
    }

    if (nullptr != m_liveRoomList)
    {
        m_liveRoomList->close();
        delete m_liveRoomList;
        m_liveRoomList = nullptr;
    }

    if (nullptr != m_RTCRoomList)
    {
        m_RTCRoomList->close();
        delete m_RTCRoomList;
        m_RTCRoomList = nullptr;
    }
}

void MainDialog::mousePressEvent(QMouseEvent *e)
{
    mousePressedPosition = e->globalPos();
    windowPositionAsDrag = pos();
}

void MainDialog::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

    // ���ſ�ʼ������갴�µ�λ��Ϊ null����ʾ���û�б�����
    mousePressedPosition = QPoint();
}

void MainDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (!mousePressedPosition.isNull())
    {
        // ��갴�²����ƶ�ʱ���ƶ�����, �������갴��ʱ��λ�ü��㣬��Ϊ�˷�ֹ����ۻ�
        QPoint delta = e->globalPos() - mousePressedPosition;
        move(windowPositionAsDrag + delta);
    }
}

void MainDialog::on_btn_close_clicked()
{
    this->close();
}

void MainDialog::on_btn_video_clicked()
{
    // ��׼ֱ��

    this->close();

    Json::Value root;
    root["type"] = "NormalLive";
    root["action"] = "";
    root["port"] = ((::time(NULL) % 15000) + 50000);    // ���鷶Χ����[50000, 65535]

    Json::FastWriter writer;
    std::string jsonUTF8 = writer.write(root);

    Application::instance().openAndWait(jsonUTF8);
}

void MainDialog::on_btn_cslive_clicked()
{
    this->hide();

    // �ͷ�ͨ��

    if (nullptr == m_csLiveSetting)
    {
        m_csLiveSetting = new CSLiveSetting(this);
    }

    m_csLiveSetting->show();
}

void MainDialog::on_btn_liveroom_clicked()
{
    this->hide();

    if (nullptr == m_liveRoomList)
    {
        m_liveRoomList = new LiveRoomList(this);
    }

    m_liveRoomList->show();
}

void MainDialog::on_btn_custom_clicked()
{
    this->hide();

    if (nullptr == m_RTCRoomList)
    {
        m_RTCRoomList = new RTCRoomList(this);
    }

    m_RTCRoomList->setMulti(false);
    m_RTCRoomList->show();
}

void MainDialog::on_btn_multiroom_clicked()
{
    this->hide();

    if (nullptr == m_RTCRoomList)
    {
        m_RTCRoomList = new RTCRoomList(this);
    }

    m_RTCRoomList->setMulti(true);
    m_RTCRoomList->show();
}