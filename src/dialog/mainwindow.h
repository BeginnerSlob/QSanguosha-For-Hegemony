#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include "engine.h"
#include "connectiondialog.h"
#include "configdialog.h"
#include "UpdateCheckThread.h"

#include <QMainWindow>
#include <QSettings>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>

namespace Ui {
    class MainWindow;
}

class FitView;
class QGraphicsScene;
class QSystemTrayIcon;
class Server;
class QTextEdit;
class QToolButton;
class QGroupBox;
class RoomItem;

class BroadcastBox: public QDialog {
    Q_OBJECT

public:
    BroadcastBox(Server *server, QWidget *parent = 0);

protected:
    virtual void accept();

private:
    Server *server;
    QTextEdit *text_edit;
};

class BackLoader {
public:
    static void preload();
};

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setBackgroundBrush(bool center_as_origin);

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    FitView *view;
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    ConnectionDialog *connection_dialog;
    ConfigDialog *config_dialog;
    QSystemTrayIcon *systray;
    Server *server;
    UpdateInfoStruct update_info;

    void restoreFromConfig();

public slots:
    void startConnection();

private slots:
    void on_actionAbout_GPLv3_triggered();
    void on_actionAbout_Lua_triggered();
    void on_actionAbout_fmod_triggered();
    void on_actionReplay_file_convert_triggered();
    void on_actionPackaging_triggered();
    void on_actionPC_Console_Start_triggered();
    void on_actionRecord_analysis_triggered();
    void on_actionCard_editor_triggered();
    void on_actionAcknowledgement_triggered();
    void on_actionBroadcast_triggered();
    void on_actionRule_Summary_triggered();
    void on_actionMinimize_to_system_tray_triggered();
    void on_actionShow_Hide_Menu_triggered();
    void on_actionFullscreen_triggered();
    void on_actionReplay_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Us_triggered();
    void on_actionEnable_Hotkey_toggled(bool);
    void on_actionNever_nullify_my_trick_toggled(bool);
    void on_actionCard_Overview_triggered();
    void on_actionGeneral_Overview_triggered();
    void on_actionStart_Server_triggered();
    void on_actionExit_triggered();
    void on_actionCheckUpdate_triggered();

    void checkVersion(const QString &server_version, const QString &server_mod);
    void networkError(const QString &error_msg);
    void enterRoom();
    void gotoScene(QGraphicsScene *scene);
    void gotoStartScene();
    void startGameInAnotherInstance();
    void changeBackground();
    void changeTableBg();
    void on_actionManage_Ban_IP_triggered();

    void storeKeyAndValue(const QString &key, const QString &value);

signals:
    void about_to_close();
};

#endif

