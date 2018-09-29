
#ifndef TXShareFrameChoose_H
#define TXShareFrameChoose_H

#include <memory>
#include <QtCore/QRect>
#include <QtWidgets/QWidget>

class TXShareFrameChooseCB
{
public:
	virtual ~TXShareFrameChooseCB() {};
	virtual void chooseParam(HWND, QRect) = 0;
	virtual void cancelChoose() = 0;
};


class TXScreen;
class QMenu;
class TXShareFrameChoose : public QWidget {
    Q_OBJECT

signals:

    /**
     * @brief : ����ƶ����źţ�
     * @param : int x�������
     * @param : int y�������
     */
    void cursorPosChange(int, int);

    /**
     * @brief : ˫�����źţ�
     */
    void clickWnd(void);
public:
    /**
     * @brief : ���캯��
     * @note  : ��ǰ�����ĸ����ڣ�һ�㲻�������ڣ�
     */
    explicit TXShareFrameChoose(QWidget *parent = 0);
    ~TXShareFrameChoose(void);

public:
	void start(TXShareFrameChooseCB *cb);
	void stop();
protected:

    /**
     * @brief : ���ش����¼�
     */
    virtual void hideEvent(QHideEvent *);
    /**
     * @brief : �رմ����¼�
     */
    virtual void closeEvent(QCloseEvent *);
    /**
     * @brief : ˫���¼�
     */
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    /**
     * @brief : ��갴���¼�
     */
    virtual void mousePressEvent(QMouseEvent *);
    /**
     * @brief : ����ͷ��¼�
     */
    virtual void mouseReleaseEvent(QMouseEvent *e);
    /**
     * @brief : ����ƶ��¼�
     */
    virtual void mouseMoveEvent(QMouseEvent *e);

    /**
     * @brief : ���������¼�
     */
    virtual void keyPressEvent(QKeyEvent *e);
    /**
     * @brief : �Ի��¼�
     */
    virtual void paintEvent(QPaintEvent *);

    /**
     * @brief : ���µ�ǰ���ѡ���Ĵ���
     */
    void updateMouse(void);

private:
    /**
     * @brief : ��ʼ����������
     * @return: QPixmap ������ɫ�������Ļͼ
     */
    std::shared_ptr<QPixmap> initGlobalScreen(void);


    /**
     * @brief : ��ʼ�����
     * @note  : Ϊ�������Ĭ��״̬�µ�ͼ����ʽ
     * @param : ico ���ͼƬ����Դ�ļ�·��
     * @remark: ������δ��д����ʹ�ñ�����Ĭ�ϵ����Logo
     */
    void initCursor(const QString& ico = "");

    /**
     * @brief : ������ͼ��
     * @note  : ����ͼ���Ѵ��ڣ��򷵻ؽ�ͼ��ʾ���������ظ�������
     * @param : pos ��ͼ������ʼλ�� ������ǰ���λ�ü��ɣ�
     * @remark: ������ͼ��ǰ����Ҫ������ص������(������С��֪�����Ŵ�ȡɫ��)
     */
    std::shared_ptr<TXScreen> createScreen(const QPoint &pos);

    /**
     * @brief : �ݻٽ�ͼ��
     * @note  : ����ͼ���Ѵ��ڣ���ݻ�ʾ����������ʾ��������������Դ
     * @date  : 2017��04��16��
     */
    void destroyScreen(void);


    /**
     * @brief : ��õ�ǰ��Ļ�Ĵ�С
     * @note  : ���������֧�ֶ���Ļ�ģ�ʾ����˫��Ļ QRect��-1920, 0, 3840, 1080��
     * @return: ���� QRect ����
     */
    const QRect& getScreenRect(void);

    /**
     * @brief : �����Ļ��ԭ��
     * @note  : �������ظ������Ļԭ��������У��򷵻�ԭ�е�ԭ��
     * @return: QPixmap* ָ��
     * @date  : 2017��04��15��
     * @remark: �������»����Ļԭ������Ҫ����ԭ����Դ
     */
    std::shared_ptr<QPixmap> getGlobalScreen(void);

private:

    /// ���������Ƿ��Ѿ�չʾ
    bool                        isLeftPressed_;
    /// ���ڼ�������
    QPoint                      startPoint_;
    /// ��ǰ������Ļ�ľ�������
    QRect desktopRect_;
    /// ��Ļ��ɫ����ͼ
    std::shared_ptr<QPixmap>    backgroundScreen_;
    /// ��Ļԭ��
    std::shared_ptr<QPixmap>    originPainting_;
    /// ��ͼ��Ļ
    std::shared_ptr<TXScreen>   screenTool_;

    /// ��ǰ���ѡ����С�ľ��δ���
    QRect                       windowRect_;
    /// �ö���ʱ��
    /// �����
    static bool                 isActivity_;
	HWND					    m_curChooseHwnd;
	bool						m_bChooseWnd;

	TXShareFrameChooseCB		*m_pCB;
public slots:

    /**
     * @brief : Window�°Ե��ö���Ψ�Ҷ���
     * @remark: ʹ�øú���ʱ������ֹ�Ҽ��˵�����Ϊ������ʹ�ã�����BUG
     */
    void onEgoistic(void);

	/**
	* @brief : Window�°Ե��ö���Ψ�Ҷ���
	* @remark: ʹ�øú���ʱ������ֹ�Ҽ��˵�����Ϊ������ʹ�ã�����BUG
	*/
	void clickWndSlot(void);
};

/**
 * @class : TXScreen
 * @brief : ��ͼ��
 * @note  : ��Ҫ�غ�ͼƬ�ı༭�뱣��
*/
class TXScreen : public QWidget {

    Q_OBJECT

signals:


    /**
     * @brief : ��ͼ����С�޸ģ��źţ�
     * @param : int ���
     * @param : int �߶�
     */
    void sizeChange(int,int);

    /**
     * @brief : ��ͼ�����ڵ�λ�ã��źţ�
     * @param : int ���ڵĺ���λ��
	 * @param : int ���ڵ�����λ��
     */
    void postionChange(int,int);

    /**
     * @brief : ˫�� ���źţ�
     */
    void doubleClick(void);

protected:

    /// �ڱ߾࣬������ק�Ĵ�����
    const int PADDING_ = 6;

    /// ��λö��
    enum DIRECTION {
        UPPER=0,
        LOWER=1,
        LEFT,
        RIGHT,
        LEFTUPPER,
        LEFTLOWER,
        RIGHTLOWER,
        RIGHTUPPER,
        NONE
    };

public:

    explicit TXScreen(std::shared_ptr<QPixmap> originPainting, QPoint pos, QWidget *parent = 0);

	~TXScreen();

    /**
     * @brief : ��õ�ǰ��ͼ���Ƿ����
     * @return: true : ����
     */
    static bool state(void) { return isInit_; }
	QRect getWndQRect();
protected:

    /**
     * @brief : �����˵��¼�
     */
    virtual void contextMenuEvent(QContextMenuEvent *);

    /**
     * @brief : ˫���¼�
     */
    virtual void mouseDoubleClickEvent(QMouseEvent *e);

    /**
     * @brief : ��갴���¼�
     */
    virtual void mousePressEvent(QMouseEvent *e);

    /**
     * @brief : ����ͷ��¼�
     */
    virtual void mouseReleaseEvent(QMouseEvent *e);
    /**
     * @brief : ����ƶ��¼�
     */
    virtual void mouseMoveEvent(QMouseEvent *e);

    /**
     * @brief : �����ƶ��¼�
     */
    virtual void moveEvent(QMoveEvent *);

    /**
     * @brief : ���ڴ�С�޸��¼�
     */
    virtual void resizeEvent(QResizeEvent *);


    /**
     * @brief : ������ʾ�¼�
     */
    virtual void showEvent(QShowEvent *);

    /**
     * @brief : ���������¼�
     */
    virtual void hideEvent(QHideEvent *);

    /**
     * @brief : �����봰���¼�
     */
    virtual void enterEvent(QEvent *e);

    /**
     * @brief : ����뿪�����¼�
     */
    virtual void leaveEvent(QEvent *e);

    /**
     * @brief : ���ڹر��¼�
     */
    virtual void closeEvent(QCloseEvent *);

    /**
     * @brief : �����Ի��¼�
     */
    virtual void paintEvent(QPaintEvent *);

public slots:


    /**
     * @brief : �������λ���޸Ĵ��ڴ�С
     * @param : x ���ĺ���λ��
     * @param : y ��������λ��
     */
    void onMouseChange(int x,int y);

    /**
     * @brief : ������Ļ�����а���
     */
    void onChooseWndOrArea(void);

protected slots:
    /**
	 * @brief : �˳���ǰ��ͼ����
     */
    void quitScreenshot(void);

private:

    /// �Ƿ��Ѿ����ó�ʼ��С
    static bool     isInit_;
    /// ���ڴ�С�ı�ʱ����¼�ı䷽��
    DIRECTION       direction_;
    /// ���
    QPoint          originPoint_;
    /// ����Ƿ���
    bool            isPressed_;
    /// �϶��ľ���
    QPoint          movePos_;
    /// ���ê��
    QPolygon        listMarker_;
    /// ��Ļԭ��
    std::shared_ptr<QPixmap> originPainting_;
	/// ��ǰ���ڼ������� ���ڻ��ƽ�ͼ����
	QRect			currentRect_;
    /// �Ҽ��˵�����
    QMenu           *menu_;
};

#endif /// TXShareFrameChoose_H
