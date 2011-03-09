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

    //For menu File
    ui->actionExit->setIcon(QIcon(":/resource/icon/exit.png"));
    ui->actionExit->setStatusTip(tr("Exit from Telescope."));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    //For menu Tool
    ui->actionIM->setIcon(QIcon(":/resource/icon/im.png"));
    ui->actionIM->setStatusTip(tr("Open the IM Dialog."));


    //For ToolBar
    ui->mainToolBar->addAction(ui->actionIM);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionExit);


    //For the mainwindow
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);   //ʹ���ڴ�����ǰ

    //For timer
    //����һ��QTimer�Ķ�����м�ʱ�����ˢ�´���
    //������ʹ��update()
    //��repaint�����������SLOT���Ա�������
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(screenShot()));
    timer->start(250);

    //For central widget
    shPic = new ShowPic(this);
    this->setCentralWidget(shPic);
    shPic->setAttribute(Qt::WA_TranslucentBackground);

    net.setUpUdpSocket(QString("127.0.0.1"), QString("54321"));//�󶨶˿�

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if (moveModel == true)
        p.fillRect(rect(), QColor(0, 0xff, 0, 30));    //��͸����ɫ
    else
        p.fillRect(rect(), QColor(0, 0, 0, 0));     //͸��
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - dragPoint);   //�ƶ�������
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

void MainWindow::screenShot()
{
    QPixmap pm;
    pm = QPixmap::grabWindow(QApplication::desktop()->winId(),
                             topLeftPoint.x(), topLeftPoint.y(),
                             winSize.width(), winSize.height());
    net.sendPicToClient(&pm);//����Pixmap
}
