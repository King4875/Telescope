/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon May 2 01:37:37 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionIM;
    QAction *actionExit;
    QAction *actionSwitch;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuTool;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(595, 445);
        MainWindow->setMinimumSize(QSize(380, 285));
        actionIM = new QAction(MainWindow);
        actionIM->setObjectName(QString::fromUtf8("actionIM"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSwitch = new QAction(MainWindow);
        actionSwitch->setObjectName(QString::fromUtf8("actionSwitch"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 595, 23));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QString::fromUtf8("menuTool"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuTool->addAction(actionIM);
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionIM->setText(QApplication::translate("MainWindow", "IM", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        actionSwitch->setText(QApplication::translate("MainWindow", "Switch", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSwitch->setToolTip(QApplication::translate("MainWindow", "Switch", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuTool->setTitle(QApplication::translate("MainWindow", "&Tool", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
