#include "appconfig.h"
#include<QDebug>
QString AppConfig::ConfigFile = "config.ini";
int AppConfig::CurrentIndex = 0;
QString AppConfig::ZeroSet_x_lf="0";                    //左前腿x初始数据
QString AppConfig::ZeroSet_x_rf="0";                    //右前腿x初始数据
QString AppConfig::ZeroSet_x_lh="0";                    //左后腿x初始数据
QString AppConfig::ZeroSet_x_rh="0";                    //右后腿x初始数据
QString AppConfig::ZeroSet_y_lf="0";                    //左前腿y初始数据
QString AppConfig::ZeroSet_y_rf="0";                    //右前腿y初始数据
QString AppConfig::ZeroSet_y_lh="0";                    //左后腿y初始数据
QString AppConfig::ZeroSet_y_rh="0";                    //右后腿y初始数据
QString AppConfig::ZeroSet_z_lf="0";                    //左前腿z初始数据
QString AppConfig::ZeroSet_z_rf="0";                    //右前腿z初始数据
QString AppConfig::ZeroSet_z_lh="0";                    //左后腿z初始数据
QString AppConfig::ZeroSet_z_rh="0";                    //右后腿z初始数据

QString AppConfig::_90Set_x_lf="0";                    //左前腿x初始数据
QString AppConfig::_90Set_x_rf="0";                    //右前腿x初始数据
QString AppConfig::_90Set_x_lh="0";                    //左后腿x初始数据
QString AppConfig::_90Set_x_rh="0";                    //右后腿x初始数据
QString AppConfig::_90Set_y_lf="0";                    //左前腿y初始数据
QString AppConfig::_90Set_y_rf="0";                    //右前腿y初始数据
QString AppConfig::_90Set_y_lh="0";                    //左后腿y初始数据
QString AppConfig::_90Set_y_rh="0";                    //右后腿y初始数据
QString AppConfig::_90Set_z_lf="0";                    //左前腿z初始数据
QString AppConfig::_90Set_z_rf="0";                    //右前腿z初始数据
QString AppConfig::_90Set_z_lh="0";                    //左后腿z初始数据
QString AppConfig::_90Set_z_rh="0";                    //右后腿z初始数据

QString AppConfig::_180Set_x_lf="0";                    //左前腿x初始数据
QString AppConfig::_180Set_x_rf="0";                    //右前腿x初始数据
QString AppConfig::_180Set_x_lh="0";                    //左后腿x初始数据
QString AppConfig::_180Set_x_rh="0";                    //右后腿x初始数据
QString AppConfig::_180Set_y_lf="0";                    //左前腿y初始数据
QString AppConfig::_180Set_y_rf="0";                    //右前腿y初始数据
QString AppConfig::_180Set_y_lh="0";                    //左后腿y初始数据
QString AppConfig::_180Set_y_rh="0";                    //右后腿y初始数据
QString AppConfig::_180Set_z_lf="0";                    //左前腿z初始数据
QString AppConfig::_180Set_z_rf="0";                    //右前腿z初始数据
QString AppConfig::_180Set_z_lh="0";                    //左后腿z初始数据
QString AppConfig::_180Set_z_rh="0";                    //右后腿z初始数据

QString AppConfig::_180TurnSet_x_lf="0";                    //左前腿x初始数据
QString AppConfig::_180TurnSet_x_rf="0";                    //右前腿x初始数据
QString AppConfig::_180TurnSet_x_lh="0";                    //左后腿x初始数据
QString AppConfig::_180TurnSet_x_rh="0";                    //右后腿x初始数据
QString AppConfig::_180TurnSet_y_lf="0";                    //左前腿y初始数据
QString AppConfig::_180TurnSet_y_rf="0";                    //右前腿y初始数据
QString AppConfig::_180TurnSet_y_lh="0";                    //左后腿y初始数据
QString AppConfig::_180TurnSet_y_rh="0";                    //右后腿y初始数据
QString AppConfig::_180TurnSet_z_lf="0";                    //左前腿z初始数据
QString AppConfig::_180TurnSet_z_rf="0";                    //右前腿z初始数据
QString AppConfig::_180TurnSet_z_lh="0";                    //左后腿z初始数据
QString AppConfig::_180TurnSet_z_rh="0";                    //右后腿z初始数据

//下压
 QString AppConfig::_90Trot_pressSet_lf="0";
 QString AppConfig::_90Trot_pressSet_rf="0";
 QString AppConfig::_90Trot_pressSet_lh="0";
 QString AppConfig::_90Trot_pressSet_rh="0";

 QString AppConfig::_90Amble_pressSet_lf="0";
 QString AppConfig::_90Amble_pressSet_rf="0";
 QString AppConfig::_90Amble_pressSet_lh="0";
 QString AppConfig::_90Amble_pressSet_rh="0";

 QString AppConfig::_180Trot_pressSet_lf="0";
 QString AppConfig::_180Trot_pressSet_rf="0";
 QString AppConfig::_180Trot_pressSet_lh="0";
 QString AppConfig::_180Trot_pressSet_rh="0";


 QString AppConfig::_180Amble_pressSet_lf="0";
 QString AppConfig::_180Amble_pressSet_rf="0";
 QString AppConfig::_180Amble_pressSet_lh="0";
 QString AppConfig::_180Amble_pressSet_rh="0";

 QString AppConfig::_90OuterTrot_pressSet_lf="0";
 QString AppConfig::_90OuterTrot_pressSet_rf="0";
 QString AppConfig::_90OuterTrot_pressSet_lh="0";
 QString AppConfig::_90OuterTrot_pressSet_rh="0";

 QString AppConfig::_90OuterAmble_pressSet_lf="0";
 QString AppConfig::_90OuterAmble_pressSet_rf="0";
 QString AppConfig::_90OuterAmble_pressSet_lh="0";
 QString AppConfig::_90OuterAmble_pressSet_rh="0";

 QString AppConfig::_90innerTrot_pressSet_lf_3="0";
 QString AppConfig::_90innerTrot_pressSet_rf_3="0";
 QString AppConfig::_90innerTrot_pressSet_lh_3="0";
 QString AppConfig::_90innerTrot_pressSet_rh_3="0";

  QString AppConfig::_90innerTrot_pressSet_lf_2="0";
  QString AppConfig::_90innerTrot_pressSet_rf_2="0";
  QString AppConfig::_90innerTrot_pressSet_lh_2="0";
  QString AppConfig::_90innerTrot_pressSet_rh_2="0";

 QString AppConfig::_90innerAmble_pressSet_lf="0";
 QString AppConfig::_90innerAmble_pressSet_rf="0";
 QString AppConfig::_90innerAmble_pressSet_lh="0";
 QString AppConfig::_90innerAmble_pressSet_rh="0";

 QString AppConfig::_90back_pressSet_lf="0";
 QString AppConfig::_90back_pressSet_rf="0";
 QString AppConfig::_90back_pressSet_lh="0";
 QString AppConfig::_90back_pressSet_rh="0";

 QString AppConfig::_180TrotTurn_pressSet_lf="0";
 QString AppConfig::_180TrotTurn_pressSet_rf="0";
 QString AppConfig::_180TrotTurn_pressSet_lh="0";
 QString AppConfig::_180TrotTurn_pressSet_rh="0";

 QString AppConfig::_180AmbleTurn_pressSet_lf="0";
 QString AppConfig::_180AmbleTurn_pressSet_rf="0";
 QString AppConfig::_180AmbleTurn_pressSet_lh="0";
 QString AppConfig::_180AmbleTurn_pressSet_rh="0";

 QString AppConfig::StancePullHight="0";
 QString AppConfig::StancePullHightDiag="0";
 QString AppConfig::transferForceX="0";
bool checkIniFile(const QString &iniFile)
{
    //如果配置文件大小为0,则以初始值继续运行,并生成配置文件
    QFile file(iniFile);
    if (file.size() == 0) {
        return false;
    }

    //如果配置文件不完整,则以初始值继续运行,并生成配置文件
    if (file.open(QFile::ReadOnly)) {
        bool ok = true;
        while (!file.atEnd()) {
            QString line = file.readLine();
            line.replace("\r", "");
            line.replace("\n", "");
            QStringList list = line.split("=");

            if (list.count() == 2) {
                QString key = list.at(0);
                QString value = list.at(1);
                if (value.isEmpty()) {
                    qDebug() << TIMEMS << "ini node no value" << key;
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            return false;
        }
    } else {
        return false;
    }

    return true;
}
void AppConfig::readConfig()
{
  QSettings set(AppConfig::ConfigFile, QSettings::IniFormat);

  set.beginGroup("AppConfig");
  AppConfig::CurrentIndex = set.value("CurrentIndex").toInt();
  set.endGroup();


  set.beginGroup("OffSetConfig");
  AppConfig::ZeroSet_x_lf=set.value("ZeroSet_x_lf",AppConfig::ZeroSet_x_lf).toString();
  AppConfig::ZeroSet_x_rf=set.value("ZeroSet_x_rf",AppConfig::ZeroSet_x_rf).toString();
  AppConfig::ZeroSet_x_lh=set.value("ZeroSet_x_lh",AppConfig::ZeroSet_x_lh).toString();
  AppConfig::ZeroSet_x_rh=set.value("ZeroSet_x_rh",AppConfig::ZeroSet_x_rh).toString();
  AppConfig::ZeroSet_y_lf=set.value("ZeroSet_y_lf",AppConfig::ZeroSet_y_lf).toString();
  AppConfig::ZeroSet_y_rf=set.value("ZeroSet_y_rf",AppConfig::ZeroSet_y_rf).toString();
  AppConfig::ZeroSet_y_lh=set.value("ZeroSet_y_lh",AppConfig::ZeroSet_y_lh).toString();
  AppConfig::ZeroSet_y_rh=set.value("ZeroSet_y_rh",AppConfig::ZeroSet_y_rh).toString();
  AppConfig::ZeroSet_z_lf=set.value("ZeroSet_z_lf",AppConfig::ZeroSet_z_lf).toString();
  AppConfig::ZeroSet_z_rf=set.value("ZeroSet_z_rf",AppConfig::ZeroSet_z_rf).toString();
  AppConfig::ZeroSet_z_lh=set.value("ZeroSet_z_lh",AppConfig::ZeroSet_z_lh).toString();
  AppConfig::ZeroSet_z_rh=set.value("ZeroSet_z_rh",AppConfig::ZeroSet_z_rh).toString();

  AppConfig::_90Set_x_lf=set.value("_90Set_x_lf",AppConfig::_90Set_x_lf).toString();
  AppConfig::_90Set_x_rf=set.value("_90Set_x_rf",AppConfig::_90Set_x_rf).toString();
  AppConfig::_90Set_x_lh=set.value("_90Set_x_lh",AppConfig::_90Set_x_lh).toString();
  AppConfig::_90Set_x_rh=set.value("_90Set_x_rh",AppConfig::_90Set_x_rh).toString();
  AppConfig::_90Set_y_lf=set.value("_90Set_y_lf",AppConfig::_90Set_y_lf).toString();
  AppConfig::_90Set_y_rf=set.value("_90Set_y_rf",AppConfig::_90Set_y_rf).toString();
  AppConfig::_90Set_y_lh=set.value("_90Set_y_lh",AppConfig::_90Set_y_lh).toString();
  AppConfig::_90Set_y_rh=set.value("_90Set_y_rh",AppConfig::_90Set_y_rh).toString();
  AppConfig::_90Set_z_lf=set.value("_90Set_z_lf",AppConfig::_90Set_z_lf).toString();
  AppConfig::_90Set_z_rf=set.value("_90Set_z_rf",AppConfig::_90Set_z_rf).toString();
  AppConfig::_90Set_z_lh=set.value("_90Set_z_lh",AppConfig::_90Set_z_lh).toString();
  AppConfig::_90Set_z_rh=set.value("_90Set_z_rh",AppConfig::_90Set_z_rh).toString();

  AppConfig::_180Set_x_lf=set.value("_180Set_x_lf",AppConfig::_180Set_x_lf).toString();
  AppConfig::_180Set_x_rf=set.value("_180Set_x_rf",AppConfig::_180Set_x_rf).toString();
  AppConfig::_180Set_x_lh=set.value("_180Set_x_lh",AppConfig::_180Set_x_lh).toString();
  AppConfig::_180Set_x_rh=set.value("_180Set_x_rh",AppConfig::_180Set_x_rh).toString();
  AppConfig::_180Set_y_lf=set.value("_180Set_y_lf",AppConfig::_180Set_y_lf).toString();
  AppConfig::_180Set_y_rf=set.value("_180Set_y_rf",AppConfig::_180Set_y_rf).toString();
  AppConfig::_180Set_y_lh=set.value("_180Set_y_lh",AppConfig::_180Set_y_lh).toString();
  AppConfig::_180Set_y_rh=set.value("_180Set_y_rh",AppConfig::_180Set_y_rh).toString();
  AppConfig::_180Set_z_lf=set.value("_180Set_z_lf",AppConfig::_180Set_z_lf).toString();
  AppConfig::_180Set_z_rf=set.value("_180Set_z_rf",AppConfig::_180Set_z_rf).toString();
  AppConfig::_180Set_z_lh=set.value("_180Set_z_lh",AppConfig::_180Set_z_lh).toString();
  AppConfig::_180Set_z_rh=set.value("_180Set_z_rh",AppConfig::_180Set_z_rh).toString();

  AppConfig::_180TurnSet_x_lf=set.value("_180TurnSet_x_lf",AppConfig::_180TurnSet_x_lf).toString();
  AppConfig::_180TurnSet_x_rf=set.value("_180TurnSet_x_rf",AppConfig::_180TurnSet_x_rf).toString();
  AppConfig::_180TurnSet_x_lh=set.value("_180TurnSet_x_lh",AppConfig::_180TurnSet_x_lh).toString();
  AppConfig::_180TurnSet_x_rh=set.value("_180TurnSet_x_rh",AppConfig::_180TurnSet_x_rh).toString();
  AppConfig::_180TurnSet_y_lf=set.value("_180TurnSet_y_lf",AppConfig::_180TurnSet_y_lf).toString();
  AppConfig::_180TurnSet_y_rf=set.value("_180TurnSet_y_rf",AppConfig::_180TurnSet_y_rf).toString();
  AppConfig::_180TurnSet_y_lh=set.value("_180TurnSet_y_lh",AppConfig::_180TurnSet_y_lh).toString();
  AppConfig::_180TurnSet_y_rh=set.value("_180TurnSet_y_rh",AppConfig::_180TurnSet_y_rh).toString();
  AppConfig::_180TurnSet_z_lf=set.value("_180TurnSet_z_lf",AppConfig::_180TurnSet_z_lf).toString();
  AppConfig::_180TurnSet_z_rf=set.value("_180TurnSet_z_rf",AppConfig::_180TurnSet_z_rf).toString();
  AppConfig::_180TurnSet_z_lh=set.value("_180TurnSet_z_lh",AppConfig::_180TurnSet_z_lh).toString();
  AppConfig::_180TurnSet_z_rh=set.value("_180TurnSet_z_rh",AppConfig::_180TurnSet_z_rh).toString();
   set.endGroup();

     set.beginGroup("PressConfig");
  //下压
  AppConfig::_90Trot_pressSet_lf=set.value("_90Trot_pressSet_lf",AppConfig::_90Trot_pressSet_lf).toString();
  AppConfig::_90Trot_pressSet_rf=set.value("_90Trot_pressSet_rf",AppConfig::_90Trot_pressSet_rf).toString();
  AppConfig::_90Trot_pressSet_lh=set.value("_90Trot_pressSet_lh",AppConfig::_90Trot_pressSet_lh).toString();
  AppConfig::_90Trot_pressSet_rh=set.value("_90Trot_pressSet_rh",AppConfig::_90Trot_pressSet_rh).toString();

  AppConfig::_90Amble_pressSet_lf=set.value("_90Amble_pressSet_lf",AppConfig::_90Amble_pressSet_lf).toString();
  AppConfig::_90Amble_pressSet_rf=set.value("_90Amble_pressSet_rf",AppConfig::_90Amble_pressSet_rf).toString();
  AppConfig::_90Amble_pressSet_lh=set.value("_90Amble_pressSet_lh",AppConfig::_90Amble_pressSet_lh).toString();
  AppConfig::_90Amble_pressSet_rh=set.value("_90Amble_pressSet_rh",AppConfig::_90Amble_pressSet_rh).toString();

  AppConfig::_180Trot_pressSet_lf=set.value("_180Trot_pressSet_lf",AppConfig::_180Trot_pressSet_lf).toString();
  AppConfig::_180Trot_pressSet_rf=set.value("_180Trot_pressSet_rf",AppConfig::_180Trot_pressSet_rf).toString();
  AppConfig::_180Trot_pressSet_lh=set.value("_180Trot_pressSet_lh",AppConfig::_180Trot_pressSet_lh).toString();
  AppConfig::_180Trot_pressSet_rh=set.value("_180Trot_pressSet_rh",AppConfig::_180Trot_pressSet_rh).toString();

  AppConfig::_180Amble_pressSet_lf=set.value("_180Amble_pressSet_lf",AppConfig::_180Amble_pressSet_lf).toString();
  AppConfig::_180Amble_pressSet_rf=set.value("_180Amble_pressSet_rf",AppConfig::_180Amble_pressSet_rf).toString();
  AppConfig::_180Amble_pressSet_lh=set.value("_180Amble_pressSet_lh",AppConfig::_180Amble_pressSet_lh).toString();
  AppConfig::_180Amble_pressSet_rh=set.value("_180Amble_pressSet_rh",AppConfig::_180Amble_pressSet_rh).toString();

  AppConfig::_90OuterTrot_pressSet_lf=set.value("_90OuterTrot_pressSet_lf",AppConfig::_90OuterTrot_pressSet_lf).toString();
  AppConfig::_90OuterTrot_pressSet_rf=set.value("_90OuterTrot_pressSet_rf",AppConfig::_90OuterTrot_pressSet_rf).toString();
  AppConfig::_90OuterTrot_pressSet_lh=set.value("_90OuterTrot_pressSet_lh",AppConfig::_90OuterTrot_pressSet_lh).toString();
  AppConfig::_90OuterTrot_pressSet_rh=set.value("_90OuterTrot_pressSet_rh",AppConfig::_90OuterTrot_pressSet_rh).toString();

  AppConfig::_90OuterAmble_pressSet_lf=set.value("_90OuterAmble_pressSet_lf",AppConfig::_90OuterAmble_pressSet_lf).toString();
  AppConfig::_90OuterAmble_pressSet_rf=set.value("_90OuterAmble_pressSet_rf",AppConfig::_90OuterAmble_pressSet_rf).toString();
  AppConfig::_90OuterAmble_pressSet_lh=set.value("_90OuterAmble_pressSet_lh",AppConfig::_90OuterAmble_pressSet_lh).toString();
  AppConfig::_90OuterAmble_pressSet_rh=set.value("_90OuterAmble_pressSet_rh",AppConfig::_90OuterAmble_pressSet_rh).toString();


AppConfig::_90innerAmble_pressSet_lf=set.value("_90innerAmble_pressSet_lf",AppConfig::_90innerAmble_pressSet_lf).toString();
AppConfig::_90innerAmble_pressSet_rf=set.value("_90innerAmble_pressSet_rf",AppConfig::_90innerAmble_pressSet_rf).toString();
AppConfig::_90innerAmble_pressSet_lh=set.value("_90innerAmble_pressSet_lh",AppConfig::_90innerAmble_pressSet_lh).toString();
AppConfig::_90innerAmble_pressSet_rh=set.value("_90innerAmble_pressSet_rh",AppConfig::_90innerAmble_pressSet_rh).toString();


  AppConfig::_90innerTrot_pressSet_lf_3=set.value("_90innerTrot_pressSet_lf_3",AppConfig::_90innerTrot_pressSet_lf_3).toString();
  AppConfig::_90innerTrot_pressSet_rf_3=set.value("_90innerTrot_pressSet_rf_3",AppConfig::_90innerTrot_pressSet_rf_3).toString();
  AppConfig::_90innerTrot_pressSet_lh_3=set.value("_90innerTrot_pressSet_lh_3",AppConfig::_90innerTrot_pressSet_lh_3).toString();
  AppConfig::_90innerTrot_pressSet_rh_3=set.value("_90innerTrot_pressSet_rh_3",AppConfig::_90innerTrot_pressSet_rh_3).toString();
  qDebug()<<"begin"<<set.value("_90innerTrot_pressSet_lf_2").toString();
  AppConfig::_90innerTrot_pressSet_lf_2=set.value("_90innerTrot_pressSet_lf_2").toString();
  AppConfig::_90innerTrot_pressSet_rf_2=set.value("_90innerTrot_pressSet_rf_2").toString();
  AppConfig::_90innerTrot_pressSet_lh_2=set.value("_90innerTrot_pressSet_lh_2").toString();
  AppConfig::_90innerTrot_pressSet_rh_2=set.value("_90innerTrot_pressSet_rh_2").toString();

  AppConfig::_90back_pressSet_lf=set.value("_90back_pressSet_lf",AppConfig::_90back_pressSet_lf).toString();
  AppConfig::_90back_pressSet_rf=set.value("_90back_pressSet_rf",AppConfig::_90back_pressSet_rf).toString();
  AppConfig::_90back_pressSet_lh=set.value("_90back_pressSet_lh",AppConfig::_90back_pressSet_lh).toString();
  AppConfig::_90back_pressSet_rh=set.value("_90back_pressSet_rh",AppConfig::_90back_pressSet_rh).toString();

  AppConfig::_180TrotTurn_pressSet_lf=set.value("_180TrotTurn_pressSet_lf",AppConfig::_180TrotTurn_pressSet_lf).toString();
  AppConfig::_180TrotTurn_pressSet_rf=set.value("_180TrotTurn_pressSet_rf",AppConfig::_180TrotTurn_pressSet_rf).toString();
  AppConfig::_180TrotTurn_pressSet_lh=set.value("_180TrotTurn_pressSet_lh",AppConfig::_180TrotTurn_pressSet_lh).toString();
  AppConfig::_180TrotTurn_pressSet_rh=set.value("_180TrotTurn_pressSet_rh",AppConfig::_180TrotTurn_pressSet_rh).toString();

  AppConfig::_180AmbleTurn_pressSet_lf=set.value("_180AmbleTurn_pressSet_lf",AppConfig::_180AmbleTurn_pressSet_lf).toString();
  AppConfig::_180AmbleTurn_pressSet_rf=set.value("_180AmbleTurn_pressSet_rf",AppConfig::_180AmbleTurn_pressSet_rf).toString();
  AppConfig::_180AmbleTurn_pressSet_lh=set.value("_180AmbleTurn_pressSet_lh",AppConfig::_180AmbleTurn_pressSet_lh).toString();
  AppConfig::_180AmbleTurn_pressSet_rh=set.value("_180AmbleTurn_pressSet_rh",AppConfig::_180AmbleTurn_pressSet_rh).toString();
  set.endGroup();

  set.beginGroup("PostureConfig");
  AppConfig::StancePullHight=set.value("StancePullHight",AppConfig::StancePullHight).toString();
  AppConfig::StancePullHightDiag=set.value("StancePullHightDiag",AppConfig::StancePullHightDiag).toString();
  AppConfig::transferForceX=set.value("transferForceX",AppConfig::transferForceX).toString();

  set.endGroup();
qDebug()<<"lastini"<<_90innerTrot_pressSet_lf_2;
  //配置文件不存在或者不全则重新生成
  if (!checkIniFile(AppConfig::ConfigFile)) {
      writeConfig();
      return;
  }
  qDebug()<<"lastini2"<<_90innerTrot_pressSet_lf_2;
}


void AppConfig::writeConfig()
{
  QSettings set(AppConfig::ConfigFile, QSettings::IniFormat);

  set.beginGroup("AppConfig");
  set.setValue("CurrentIndex", AppConfig::CurrentIndex);
  set.endGroup();

  set.beginGroup("OffSetConfig");
  set.setValue("ZeroSet_x_lf",AppConfig::ZeroSet_x_lf);
  set.setValue("ZeroSet_x_rf",AppConfig::ZeroSet_x_rf);
  set.setValue("ZeroSet_x_lh",AppConfig::ZeroSet_x_lh);
  set.setValue("ZeroSet_x_rh",AppConfig::ZeroSet_x_rh);
  set.setValue("ZeroSet_y_lf",AppConfig::ZeroSet_y_lf);
  set.setValue("ZeroSet_y_rf",AppConfig::ZeroSet_y_rf);
  set.setValue("ZeroSet_y_lh",AppConfig::ZeroSet_y_lh);
  set.setValue("ZeroSet_y_rh",AppConfig::ZeroSet_y_rh);
  set.setValue("ZeroSet_z_lf",AppConfig::ZeroSet_z_lf);
  set.setValue("ZeroSet_z_rf",AppConfig::ZeroSet_z_rf);
  set.setValue("ZeroSet_z_lh",AppConfig::ZeroSet_z_lh);
  set.setValue("ZeroSet_z_rh",AppConfig::ZeroSet_z_rh);

  set.setValue("_90Set_x_lf",AppConfig::_90Set_x_lf);
  set.setValue("_90Set_x_rf",AppConfig::_90Set_x_rf);
  set.setValue("_90Set_x_lh",AppConfig::_90Set_x_lh);
  set.setValue("_90Set_x_rh",AppConfig::_90Set_x_rh);
  set.setValue("_90Set_y_lf",AppConfig::_90Set_y_lf);
  set.setValue("_90Set_y_rf",AppConfig::_90Set_y_rf);
  set.setValue("_90Set_y_lh",AppConfig::_90Set_y_lh);
  set.setValue("_90Set_y_rh",AppConfig::_90Set_y_rh);
  set.setValue("_90Set_z_lf",AppConfig::_90Set_z_lf);
  set.setValue("_90Set_z_rf",AppConfig::_90Set_z_rf);
  set.setValue("_90Set_z_lh",AppConfig::_90Set_z_lh);
  set.setValue("_90Set_z_rh",AppConfig::_90Set_z_rh);

  set.setValue("_180Set_x_lf",AppConfig::_180Set_x_lf);
  set.setValue("_180Set_x_rf",AppConfig::_180Set_x_rf);
  set.setValue("_180Set_x_lh",AppConfig::_180Set_x_lh);
  set.setValue("_180Set_x_rh",AppConfig::_180Set_x_rh);
  set.setValue("_180Set_y_lf",AppConfig::_180Set_y_lf);
  set.setValue("_180Set_y_rf",AppConfig::_180Set_y_rf);
  set.setValue("_180Set_y_lh",AppConfig::_180Set_y_lh);
  set.setValue("_180Set_y_rh",AppConfig::_180Set_y_rh);
  set.setValue("_180Set_z_lf",AppConfig::_180Set_z_lf);
  set.setValue("_180Set_z_rf",AppConfig::_180Set_z_rf);
  set.setValue("_180Set_z_lh",AppConfig::_180Set_z_lh);
  set.setValue("_180Set_z_rh",AppConfig::_180Set_z_rh);

  set.setValue("_180TurnSet_x_lf",AppConfig::_180TurnSet_x_lf);
  set.setValue("_180TurnSet_x_rf",AppConfig::_180TurnSet_x_rf);
  set.setValue("_180TurnSet_x_lh",AppConfig::_180TurnSet_x_lh);
  set.setValue("_180TurnSet_x_rh",AppConfig::_180TurnSet_x_rh);
  set.setValue("_180TurnSet_y_lf",AppConfig::_180TurnSet_y_lf);
  set.setValue("_180TurnSet_y_rf",AppConfig::_180TurnSet_y_rf);
  set.setValue("_180TurnSet_y_lh",AppConfig::_180TurnSet_y_lh);
  set.setValue("_180TurnSet_y_rh",AppConfig::_180TurnSet_y_rh);
  set.setValue("_180TurnSet_z_lf",AppConfig::_180TurnSet_z_lf);
  set.setValue("_180TurnSet_z_rf",AppConfig::_180TurnSet_z_rf);
  set.setValue("_180TurnSet_z_lh",AppConfig::_180TurnSet_z_lh);
  set.setValue("_180TurnSet_z_rh",AppConfig::_180TurnSet_z_rh);
  set.endGroup();

  set.beginGroup("PressConfig");
  set.setValue("_90Trot_pressSet_lf",AppConfig::_90Trot_pressSet_lf);
  set.setValue("_90Trot_pressSet_rf",AppConfig::_90Trot_pressSet_rf);
  set.setValue("_90Trot_pressSet_lh",AppConfig::_90Trot_pressSet_lh);
  set.setValue("_90Trot_pressSet_rh",AppConfig::_90Trot_pressSet_rh);

  set.setValue("_90Amble_pressSet_lf",AppConfig::_90Amble_pressSet_lf);
  set.setValue("_90Amble_pressSet_rf",AppConfig::_90Amble_pressSet_rf);
  set.setValue("_90Amble_pressSet_lh",AppConfig::_90Amble_pressSet_lh);
  set.setValue("_90Amble_pressSet_rh",AppConfig::_90Amble_pressSet_rh);

  set.setValue("_180Trot_pressSet_lf",AppConfig::_180Trot_pressSet_lf);
  set.setValue("_180Trot_pressSet_rf",AppConfig::_180Trot_pressSet_rf);
  set.setValue("_180Trot_pressSet_lh",AppConfig::_180Trot_pressSet_lh);
  set.setValue("_180Trot_pressSet_rh",AppConfig::_180Trot_pressSet_rh);

  set.setValue("_180Amble_pressSet_lf",AppConfig::_180Amble_pressSet_lf);
  set.setValue("_180Amble_pressSet_rf",AppConfig::_180Amble_pressSet_rf);
  set.setValue("_180Amble_pressSet_lh",AppConfig::_180Amble_pressSet_lh);
  set.setValue("_180Amble_pressSet_rh",AppConfig::_180Amble_pressSet_rh);

  set.setValue("_90OuterTrot_pressSet_lf",AppConfig::_90OuterTrot_pressSet_lf);
  set.setValue("_90OuterTrot_pressSet_rf",AppConfig::_90OuterTrot_pressSet_rf);
  set.setValue("_90OuterTrot_pressSet_lh",AppConfig::_90OuterTrot_pressSet_lh);
  set.setValue("_90OuterTrot_pressSet_rh",AppConfig::_90OuterTrot_pressSet_rh);

set.setValue("_90innerAmble_pressSet_lf",AppConfig::_90innerAmble_pressSet_lf);
set.setValue("_90innerAmble_pressSet_rf",AppConfig::_90innerAmble_pressSet_rf);
set.setValue("_90innerAmble_pressSet_lh",AppConfig::_90innerAmble_pressSet_lh);
set.setValue("_90innerAmble_pressSet_rh",AppConfig::_90innerAmble_pressSet_rh);

  set.setValue("_90OuterAmble_pressSet_lf",AppConfig::_90OuterAmble_pressSet_lf);
  set.setValue("_90OuterAmble_pressSet_rf",AppConfig::_90OuterAmble_pressSet_rf);
  set.setValue("_90OuterAmble_pressSet_lh",AppConfig::_90OuterAmble_pressSet_lh);
  set.setValue("_90OuterAmble_pressSet_rh",AppConfig::_90OuterAmble_pressSet_rh);



  set.setValue("_90innerTrot_pressSet_lf_3",AppConfig::_90innerTrot_pressSet_lf_3);
  set.setValue("_90innerTrot_pressSet_rf_3",AppConfig::_90innerTrot_pressSet_rf_3);
  set.setValue("_90innerTrot_pressSet_lh_3",AppConfig::_90innerTrot_pressSet_lh_3);
  set.setValue("_90innerTrot_pressSet_rh_3",AppConfig::_90innerTrot_pressSet_rh_3);

  set.setValue("_90innerTrot_pressSet_lf_2",AppConfig::_90innerTrot_pressSet_lf_2);
  set.setValue("_90innerTrot_pressSet_rf_2",AppConfig::_90innerTrot_pressSet_rf_2);
  set.setValue("_90innerTrot_pressSet_lh_2",AppConfig::_90innerTrot_pressSet_lh_2);
  set.setValue("_90innerTrot_pressSet_rh_2",AppConfig::_90innerTrot_pressSet_rh_2);



  set.setValue("_90back_pressSet_lf",AppConfig::_90back_pressSet_lf);
  set.setValue("_90back_pressSet_rf",AppConfig::_90back_pressSet_rf);
  set.setValue("_90back_pressSet_lh",AppConfig::_90back_pressSet_lh);
  set.setValue("_90back_pressSet_rh",AppConfig::_90back_pressSet_rh);

  set.setValue("_180TrotTurn_pressSet_lf",AppConfig::_180TrotTurn_pressSet_lf);
  set.setValue("_180TrotTurn_pressSet_rf",AppConfig::_180TrotTurn_pressSet_rf);
  set.setValue("_180TrotTurn_pressSet_lh",AppConfig::_180TrotTurn_pressSet_lh);
  set.setValue("_180TrotTurn_pressSet_rh",AppConfig::_180TrotTurn_pressSet_rh);

  set.setValue("_180AmbleTurn_pressSet_lf",AppConfig::_180AmbleTurn_pressSet_lf);
  set.setValue("_180AmbleTurn_pressSet_rf",AppConfig::_180AmbleTurn_pressSet_rf);
  set.setValue("_180AmbleTurn_pressSet_lh",AppConfig::_180AmbleTurn_pressSet_lh);
  set.setValue("_180AmbleTurn_pressSet_rh",AppConfig::_180AmbleTurn_pressSet_rh);
  set.endGroup();

  set.beginGroup("PostureConfig");
  set.setValue("StancePullHight",AppConfig::StancePullHight);
  set.setValue("StancePullHightDiag",AppConfig::StancePullHightDiag);
  set.setValue("transferForceX",AppConfig::transferForceX);
  set.endGroup();
}
