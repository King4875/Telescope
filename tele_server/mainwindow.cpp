#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resource/icon/telescope.png"));
    this->setWindowTitle(tr("Telescope"));

    //Common initialisation
    moveModel = true;   //��ʼΪ�ƶ�ģʽ
    server=new Server(this);   //��ʼ��IM

    connect(&net,SIGNAL(hideIMSignal()),this,SLOT(hideIM()));
    connect(server,SIGNAL(showIMSignal()),this,SLOT(showIM()));

    //For exit Tool
    ui->actionExit->setIcon(QIcon(":/resource/icon/exit.png"));
    ui->actionExit->setStatusTip(tr("Exit from Telescope."));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    //For IM Tool
    ui->actionIM->setIcon(QIcon(":/resource/icon/chat2.png"));
    ui->actionIM->setStatusTip(tr("Open the IM Dialog."));
    ui->actionIM->setCheckable(true);            //�����󱣳ְ���״̬
    connect(ui->actionIM,SIGNAL(triggered()),this,SLOT(showIM()));
    ui->menuBar->hide();   //�Ѳ˵�����������

    //For IM Tool
    ui->actionSwitch->setIcon(QIcon(":/resource/icon/switch.png"));
    ui->actionSwitch->setStatusTip(tr("Switch View Mode"));
    connect(ui->actionSwitch,SIGNAL(triggered()),this,SLOT(switchMode()));

    //For ToolBar
    ui->mainToolBar->addAction(ui->actionSwitch);
    ui->mainToolBar->addAction(ui->actionIM);
    ui->mainToolBar->addAction(ui->actionExit);
    ui->mainToolBar->setMovable(false);          //�̶�������
    ui->mainToolBar->setIconSize(QSize(50,45));  //���ù�����ͼ���С


    //For Actions
    actionMax = new QAction(tr("Maximize"), this);
    connect(actionMax, SIGNAL(triggered()), this, SLOT(showMaximized()));

    actionMin = new QAction(tr("Minimize"), this);
    connect(actionMin, SIGNAL(triggered()), this, SLOT(showMinimized()));

    actionNormal = new QAction(tr("Normalize"), this);
    connect(actionNormal, SIGNAL(triggered()), this, SLOT(showNormal()));


    //For the mainwindow
    setAttribute(Qt::WA_TranslucentBackground);   //���ڰ�͸��
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);   //ʹ���ڴ�����ǰ
    background=QImage(":/resource/icon/telescope.png"); //���ڵı���ͼƬ

    //For tray icon
    creatTrayIcon();

    //For timer
    //����һ��QTimer�Ķ�����м�ʱ�����ˢ�´���
    //������ʹ��update()
    //��repaint�����������SLOT���Ա�������
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(screenShot()));
    timer->start(200);

    //For central widget
    shPic = new ShowPic(this);
    this->setCentralWidget(shPic);
    //shPic->setMinimumSize(QSize(80,60));
    shPic->setAttribute(Qt::WA_TranslucentBackground);

    //net.setUpUdpSocket(QString("127.0.0.1"), QString("54321"));//�󶨶˿�
    net.setParent(this);
    net.setParentWidget(this);
    net.setTrayIcon(&trayIcon);
    net.setUpTcpSocket(QString("12345"));   //Customized port needed������
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatTrayIcon()
{
    //For tray icon
    trayIcon.setIcon(QIcon(":/resource/icon/telescope.png"));

    //For tray icon menu
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(actionMax);
    trayIconMenu->addAction(actionMin);
    trayIconMenu->addAction(actionNormal);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui->actionExit);

    trayIcon.setContextMenu(trayIconMenu);

    trayIcon.show();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter pb(&bmp);
    pb.setPen(Qt::NoPen);
    pb.setBrush(Qt::black);
    pb.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);//���ô������֣��γ�Բ�Ǵ���Ч��

    if (moveModel == true)
    {
        p.fillRect(rect(), QColor(8, 46, 84, 100));    //��͸������ɫ
        //p.drawImage(QPoint(this->width()-background.width(),this->height()-background.height()),background);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(7);
        pen.setColor(QColor("#DCDCDC"));
        p.setPen(pen);
        ui->mainToolBar->resize(ui->mainToolBar->width(),45);
        p.fillRect(ui->mainToolBar->rect(), QColor(8, 46, 84, 30));
        p.drawRoundedRect(rect(),10,10);
    }
    else
    {
        p.fillRect(rect(), QColor(0, 0, 0, 0));     //͸��
        //p.drawImage(QPoint(this->width()-background.width(),this->height()-background.height()),background);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(7);
        pen.setColor(QColor("#7CFC00"));
        p.setPen(pen);
        ui->mainToolBar->resize(ui->mainToolBar->width(),45);
        p.fillRect(ui->mainToolBar->rect(), QColor(124, 252, 0, 130));
        p.drawRoundedRect(rect(),10,10);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - dragPoint);   //�ƶ�������
        server->move(this->pos().x()+this->width(),this->pos().y()+45);  //IM�����������ƶ�
        e->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        dragPoint = e->globalPos() - frameGeometry().topLeft();
        e->accept();    //��ʾ���ø�����¼���Ӧ���������ˣ��൱�ڰ��¼��ػ�
    }
}

void MainWindow::moveEvent(QMoveEvent *e)
{
    topLeftPoint = QPoint(mapToGlobal(shPic->pos()));
    winSize = QRect(topLeftPoint, QSize(shPic->geometry().width(), shPic->geometry().height()));

    QMainWindow::moveEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_S))
    {
        if (moveModel == true)
            moveModel = false;
        else
            moveModel = true;

        update();   //ˢ�½���
    }
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    topLeftPoint = QPoint(mapToGlobal(shPic->pos()));
    winSize = QRect(topLeftPoint, QSize(shPic->geometry().width(), shPic->geometry().height()));
    server->move(this->pos().x()+this->width(),this->pos().y()+45);  //IM�����������ƶ�
}

void MainWindow::screenShot()
{
    QPixmap pm;
    pm = QPixmap::grabWindow(QApplication::desktop()->winId(),
                             topLeftPoint.x()+4, topLeftPoint.y(),
                             winSize.width()-8, winSize.height());  //�Ӽ���ֵ��Ϊ�˲���ȡ�������˵ı߿�
    if (net.hasClientConnection) net.sendPicToClient(&pm);//����Pixmap
}

void MainWindow::showIM()          //��ʾ������IM
{
    server->move(this->pos().x()+this->width(),this->pos().y()+45);   //IM�������������Ա�
    if(server->isHidden()){server->show();ui->actionIM->setChecked(true);}
    else server->hide();
}

void MainWindow::switchMode()
{
    if (moveModel == true)
        moveModel = false;
    else
        moveModel = true;

    update();   //ˢ�½���
}

void MainWindow::hideIM()
{
    server->clearShowText();
    server->hide();
    ui->actionIM->setChecked(false);
}
