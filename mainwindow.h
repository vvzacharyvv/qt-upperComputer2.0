#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"camerathread.h"
#include <QMainWindow>
#include <QSerialPort>			//访问串口的库
#include <QSerialPortInfo>		//查询串口信息的库
#include <QDebug>				//用于调试打印输出的库
#include <QTimer>				//定时器的库
#include <QTime>				//时间的库
#include <QDate>				//日期的库
#include <QMessageBox>			//一个小的弹窗库
#include"datadeal.h"
#include"appconfig.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    CameraThread *thread1=new CameraThread(this);
//    CameraThread *thread2=new CameraThread(this);
    int btn_on_off = 0;
    float m_fl;
    int btn_state = 0;
    bool video_flag=0;
    bool motion_state=0;
    bool hexshow_flag=0;
    bool hexsend_flag=0;
    int initNum=0;
    int chosendLeg;
    QString m_pset;
    DataDeal *dd;
    QString dataStore[100];
    void setLED(QLabel* label, int color, int size);
private slots:
    //config
    void initConfig();
    void saveConfig();
   //btn
    void on_btn_open_close_clicked();

    void serialPortReadyRead();

    void serialPortWrite();

    void on_btn_clear_rx_clicked();

    void on_btn_clear_tx_clicked();

    void on_btn_send_clicked();

    void on_btn_motion_clicked();





    void on_btn_vset_clicked();

    void on_btn_dset_clicked();

    void on_btn_gmset_clicked();

    void on_btn_tguset_clicked();

    void on_btn_pset_clicked();

    void on_checkBox_HexSend_stateChanged(int arg1);

    void on_checkBox_HexShow_stateChanged(int arg1);

    void on_btn_connect_clicked();

    void on_btn_refresh_clicked();

    //void on_PBT_Open_clicked();

    void on_btn_vsetZ_clicked();
    void on_btn_pumpset_clicked();

    void on_btn_imdset_clicked();

    void on_btn_reset_clicked();

    void on_PBT_Open_clicked();

    void on_btn_iniPositionSet1_clicked();

    void on_btn_iniPositionSet2_clicked();

    void on_btn_iniPositionSet3_clicked();

    void on_btn_copy_clicked();

    void on_btn_recover_clicked();

    void on_btn_initRepeat_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_btn_lfControl_clicked();

    void on_btn_rfControl_clicked();

    void on_btn_lhControl_clicked();

    void on_btn_rhControl_clicked();

    void on_btn_forward_clicked();

    void on_btn_back_clicked();

    void on_btn_left_clicked();

    void on_btn_forward_pressed();

    void on_btn_back_pressed();

    void on_btn_left_pressed();

    void on_btn_right_clicked();

    void on_btn_right_pressed();

    void on_btn_up_clicked();

    void on_btn_up_pressed();

    void on_btn_down_clicked();

    void on_btn_down_pressed();

signals:

    void closetheconnect();
private:
    Ui::MainWindow *ui;
    //定时器
    QTimer *timer;
    // 串口对象
    QSerialPort *serialport;
    //扫描串口
    void scanSerialPort();
    //初始化
    void serialPortInit();
    void initParameters1();
    void initParameters2();
    void initParameters3();
    void readMessage(QByteArray buff);
    void delay_ms(int time);
};
#endif // MAINWINDOW_H
