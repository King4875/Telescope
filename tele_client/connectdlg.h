#ifndef CONNECTDLG_H
#define CONNECTDLG_H

#include <QDialog>
#include <QRegExp>

namespace Ui {
    class ConnectDlg;
}

class ConnectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDlg(QWidget *parent = 0);
    ~ConnectDlg();

public: //�������������ó�public��̫��ȫ...���ⲿҪ����..��ʱ������...
    Ui::ConnectDlg *ui;
};

#endif // CONNECTDLG_H
