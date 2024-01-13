#ifndef APPCONFIG_H
#define APPCONFIG_H
#include<QtCore>
#include<QtGui>
#include <QtWidgets>
#define TIMEMS qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))
#define STRDATETIME qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
class AppConfig
{
public:
    static QString ConfigFile;          //配置文件路径
    static int CurrentIndex;            //当前索引
    //0偏
    static QString ZeroSet_x_lf;                    //左前腿x初始数据
    static QString ZeroSet_x_rf;                    //右前腿x初始数据
    static QString ZeroSet_x_lh;                    //左后腿x初始数据
    static QString ZeroSet_x_rh;                    //右后腿x初始数据
    static QString ZeroSet_y_lf;                    //左前腿y初始数据
    static QString ZeroSet_y_rf;                    //右前腿y初始数据
    static QString ZeroSet_y_lh;                    //左后腿y初始数据
    static QString ZeroSet_y_rh;                    //右后腿y初始数据
    static QString ZeroSet_z_lf;                    //左前腿z初始数据
    static QString ZeroSet_z_rf;                    //右前腿z初始数据
    static QString ZeroSet_z_lh;                    //左后腿z初始数据
    static QString ZeroSet_z_rh;                    //右后腿z初始数据
    //180度偏置
    static QString _90Set_x_lf;                    //左前腿x初始数据
    static QString _90Set_x_rf;                    //右前腿x初始数据
    static QString _90Set_x_lh;                    //左后腿x初始数据
    static QString _90Set_x_rh;                    //右后腿x初始数据
    static QString _90Set_y_lf;                    //左前腿y初始数据
    static QString _90Set_y_rf;                    //右前腿y初始数据
    static QString _90Set_y_lh;                    //左后腿y初始数据
    static QString _90Set_y_rh;                    //右后腿y初始数据
    static QString _90Set_z_lf;                    //左前腿z初始数据
    static QString _90Set_z_rf;                    //右前腿z初始数据
    static QString _90Set_z_lh;                    //左后腿z初始数据
    static QString _90Set_z_rh;                    //右后腿z初始数据

    //180偏置
    static QString _180Set_x_lf;                    //左前腿x初始数据
    static QString _180Set_x_rf;                    //右前腿x初始数据
    static QString _180Set_x_lh;                    //左后腿x初始数据
    static QString _180Set_x_rh;                    //右后腿x初始数据
    static QString _180Set_y_lf;                    //左前腿y初始数据
    static QString _180Set_y_rf;                    //右前腿y初始数据
    static QString _180Set_y_lh;                    //左后腿y初始数据
    static QString _180Set_y_rh;                    //右后腿y初始数据
    static QString _180Set_z_lf;                    //左前腿z初始数据
    static QString _180Set_z_rf;                    //右前腿z初始数据
    static QString _180Set_z_lh;                    //左后腿z初始数据
    static QString _180Set_z_rh;                    //右后腿z初始数据

    //180转弯偏执
    static QString _180TurnSet_x_lf;                    //左前腿x初始数据
    static QString _180TurnSet_x_rf;                    //右前腿x初始数据
    static QString _180TurnSet_x_lh;                    //左后腿x初始数据
    static QString _180TurnSet_x_rh;                    //右后腿x初始数据
    static QString _180TurnSet_y_lf;                    //左前腿y初始数据
    static QString _180TurnSet_y_rf;                    //右前腿y初始数据
    static QString _180TurnSet_y_lh;                    //左后腿y初始数据
    static QString _180TurnSet_y_rh;                    //右后腿y初始数据
    static QString _180TurnSet_z_lf;                    //左前腿z初始数据
    static QString _180TurnSet_z_rf;                    //右前腿z初始数据
    static QString _180TurnSet_z_lh;                    //左后腿z初始数据
    static QString _180TurnSet_z_rh;                    //右后腿z初始数据

    //下压

    //offset of initial position	in 90 degrees	; Trot
    static QString _90Trot_pressSet_lf;
    static QString _90Trot_pressSet_rf;
    static QString _90Trot_pressSet_lh;
    static QString _90Trot_pressSet_rh;

    //offset of initial position	in 90 degrees	; Amble
    static QString _90Amble_pressSet_lf;
    static QString _90Amble_pressSet_rf;
    static QString _90Amble_pressSet_lh;
    static QString _90Amble_pressSet_rh;

    //offset of initial position	in 180 degrees	; Tort
    static QString _180Trot_pressSet_lf;
    static QString _180Trot_pressSet_rf;
    static QString _180Trot_pressSet_lh;
    static QString _180Trot_pressSet_rh;

    //offset of initial position	in 180 degrees	; Amble
    static QString _180Amble_pressSet_lf;
    static QString _180Amble_pressSet_rf;
    static QString _180Amble_pressSet_lh;
    static QString _180Amble_pressSet_rh;

    //outer curved surface with 90 degrees	; Tort
    static QString _90OuterTrot_pressSet_lf;
    static QString _90OuterTrot_pressSet_rf;
    static QString _90OuterTrot_pressSet_lh;
    static QString _90OuterTrot_pressSet_rh;

    //outer curved surface with 90 degrees	; Amble
    static QString _90OuterAmble_pressSet_lf;
    static QString _90OuterAmble_pressSet_rf;
    static QString _90OuterAmble_pressSet_lh;
    static QString _90OuterAmble_pressSet_rh;

    //inner curved surface	; Tort
    static QString _90innerTrot_pressSet_lf_3;
    static QString _90innerTrot_pressSet_rf_3;
    static QString _90innerTrot_pressSet_lh_3;
    static QString _90innerTrot_pressSet_rh_3;
//USELESS-BUGRECOVERY_2
    static QString _90innerTrot_pressSet_lf_2;
    static QString _90innerTrot_pressSet_rf_2;
    static QString _90innerTrot_pressSet_lh_2;
    static QString _90innerTrot_pressSet_rh_2;
    //inner curved surface ; Amble
    static QString _90innerAmble_pressSet_lf;
    static QString _90innerAmble_pressSet_rf;
    static QString _90innerAmble_pressSet_lh;
    static QString _90innerAmble_pressSet_rh;

    //90 degrees	; Amble ; back
    static QString _90back_pressSet_lf;
    static QString _90back_pressSet_rf;
    static QString _90back_pressSet_lh;
    static QString _90back_pressSet_rh;

    // 180 degrees	; Tort	;	turn
    static QString _180TrotTurn_pressSet_lf;
    static QString _180TrotTurn_pressSet_rf;
    static QString _180TrotTurn_pressSet_lh;
    static QString _180TrotTurn_pressSet_rh;

    //180 degrees	; Amble	;	turn
    static QString _180AmbleTurn_pressSet_lf;
    static QString _180AmbleTurn_pressSet_rf;
    static QString _180AmbleTurn_pressSet_lh;
    static QString _180AmbleTurn_pressSet_rh;

    //poseture attitude
    static QString StancePullHight;
    static QString StancePullHightDiag;
    static QString transferForceX;
    //读取配置参数
    static void readConfig();           //读取配置参数
    static void writeConfig();          //写入配置参数
   // bool checkIniFile(const QString &iniFile); //检测参数写入是否成功
};

#endif // APPCONFIG_H
