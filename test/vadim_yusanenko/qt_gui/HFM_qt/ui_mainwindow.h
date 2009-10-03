/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Fri Oct 2 19:33:55 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionAccounts;
    QAction *actionOptions;
    QAction *actionExit;
    QAction *actionContents;
    QAction *actionAbout;
    QWidget *centralWidget;
    QListWidget *listWidget;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QCheckBox *checkBox;
    QMenuBar *menuBar;
    QMenu *menuHFM;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(250, 400);
        MainWindowClass->setDockNestingEnabled(false);
        actionAccounts = new QAction(MainWindowClass);
        actionAccounts->setObjectName(QString::fromUtf8("actionAccounts"));
        actionOptions = new QAction(MainWindowClass);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionContents = new QAction(MainWindowClass);
        actionContents->setObjectName(QString::fromUtf8("actionContents"));
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(5, 3, 240, 281));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 320, 230, 27));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setBold(false);
        font.setWeight(50);
        font.setStyleStrategy(QFont::PreferDefault);
        comboBox->setFont(font);
        comboBox->setMouseTracking(false);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setGeometry(QRect(200, 290, 40, 27));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 290, 40, 27));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(10, 290, 121, 27));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 250, 25));
        menuHFM = new QMenu(menuBar);
        menuHFM->setObjectName(QString::fromUtf8("menuHFM"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuHFM->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHFM->addAction(actionAccounts);
        menuHFM->addAction(actionOptions);
        menuHFM->addAction(actionExit);
        menuHelp->addAction(actionContents);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "HFM", 0, QApplication::UnicodeUTF8));
        actionAccounts->setText(QApplication::translate("MainWindowClass", "Accounts", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("MainWindowClass", "Options", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionContents->setText(QApplication::translate("MainWindowClass", "Contents", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindowClass", "About", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "\320\235\320\260 \320\274\320\265\321\201\321\202\320\265...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\232\320\260\321\202\320\260\321\216\321\201\321\214 \320\275\320\260 \320\274\320\260\321\210\320\270\320\275\320\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\221\321\200\320\276\321\201\320\260\321\216 \320\272\321\203\321\200\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\223\320\276\320\273\321\213\320\271...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\232\320\276\320\277\320\260\321\216 \320\272\320\260\321\200\321\202\320\276\321\210\320\272\321\203", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\240\320\265\320\272\320\276\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\237\321\200\320\276\320\263\320\260\321\216...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\223\320\276\321\202\320\276\320\262\320\273\321\216 \320\277\321\200\320\265\320\267\320\265\320\275\321\202\320\260\321\206\320\270\321\216", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\235\320\260\320\277\320\270\320\273\321\201\321\217 (\320\270\320\267\320\267\320\260 \320\266\320\265\320\275\321\211\320\270\320\275\321\213)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\235\320\260\320\277\320\270\320\273\321\201\321\217 (\321\201\320\264\320\260\320\273 \321\215\320\272\320\267\320\260\320\274\320\265\320\275)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\235\320\260\320\277\320\270\320\273\321\201\321\217 (\320\275\320\265 \320\267\320\275\320\260\321\216 \320\267\320\260\321\207\320\265\320\274)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\320\227\320\260\320\275\321\217\321\202...", 0, QApplication::UnicodeUTF8)
        );
        pushButton->setText(QApplication::translate("MainWindowClass", "Del", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindowClass", "Add", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindowClass", "Show all users", 0, QApplication::UnicodeUTF8));
        menuHFM->setTitle(QApplication::translate("MainWindowClass", "Program", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindowClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
