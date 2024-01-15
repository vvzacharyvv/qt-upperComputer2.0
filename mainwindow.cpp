#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
void cmdSystem(const std::string& cmdLine) {
    system(cmdLine.c_str());

}
QString signedDatatoHex(QString data)
{   QString str;
    char temp=(char)data.toInt();
    int bit=temp&0x0f;
    int decade=(temp&0xf0)>>4;
    if(decade<10) str=QString("%1").arg(decade);
    if(decade==10) str="A";
    if(decade==11) str="B";
    if(decade==12) str="C";
    if(decade==13) str="D";
    if(decade==14) str="E";
    if(decade==15) str="F";
    if(bit<10) str+=QString("%1").arg(bit);
    if(bit==10) str+="A";
    if(bit==11) str+="B";
    if(bit==12) str+="C";
    if(bit==13) str+="D";
    if(bit==14) str+="E";
    if(bit==15) str+="F";
    return str;

}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CameraThread *thread1=new CameraThread(this);
   // CameraThread *thread2=new CameraThread(this);
    //init url
    connect(ui->btn_videoSet,&QPushButton::clicked,this,[=](){
         thread1->geturl(ui->video_cmb->currentText());

    });

    //thread1->geturl("http://192.168.1.102:8080/?action=stream?dummy=param.mjpg");
   // thread2->geturl("rtsp://admin:password507@192.168.1.105:554/11");
  //  thread1->geturl("http://192.168.50.64:8080");
    //启动子线程
    connect(ui->PBT_Open,&QPushButton::clicked,this,[=](){
        thread1->flag=1;
        thread1->start();
        //thread2->flag=1;
        //thread2->start();
    });
    //接受子线程的数据, 收到一张图更新一次画布
    connect(thread1,&CameraThread::sendimg,this,[=](){
        ui->label_1->setPixmap(QPixmap::fromImage(thread1->img1));
        ui->label_15->setText(QString::number(thread1->m_Fps));
    });
    //关闭子线
    connect(ui->PBT_Close,&QPushButton::clicked,this,[=](){
        thread1->flag=0;
        thread1->exit();
        thread1-> timeOfVideo=((double)cv::getTickCount()- thread1->timeOfVideo)/1000000000;
        qDebug()<<"timeOfVideo"<< thread1->timeOfVideo;
       // thread1-> wri.release();
        int sizeofvideo=(int)(2.5* thread1->timeOfVideo);
       //std::string cmdLine=QString("ffmpeg  -i  E:/video/wri2.mp4  -b:v %1M  E:/video/wri_qt2.mp4").arg(sizeofvideo).toStdString();
       // cmdSystem(cmdLine);
         qDebug()<<"sizeofvideo"<< sizeofvideo;
        ui->label_1->clear();
        //        thread2->flag=0;
        //        thread2->exit();

        ui->label_15->clear();
    });


    //图标设置
    ui->tab->setWindowTitle("初始化界面");
    ui->btn_motion->setIcon(QIcon(":/run.png"));
    ui->btn_connect->setIcon(QIcon(":/lianjie.png"));
    ui->btn_refresh->setIcon(QIcon(":/shuaxin.png"));
    ui->PBT_Open->setIcon(QIcon(":/bofang.png"));
    ui->PBT_Open->setToolTip("播放");
    ui->PBT_Close->setIcon(QIcon(":/tingzhi.png"));
    ui->PBT_Close->setToolTip("停止");
    ui->btn_motion->setToolTip("启动");
    ui->progressBar->setOrientation(Qt::Horizontal);// 水平方向
    ui->progressBar->setMinimum(0); // 最小值
    ui->progressBar->setMaximum(100); // 最大值
    ui->progressBar->setValue(0);
    setLED(ui->led_lf,1,16);
    setLED(ui->led_rf,1,16);
    setLED(ui->led_lh,1,16);
    setLED(ui->led_rh,1,16);
    setLED(ui->led_lf_ad,1,16);
    setLED(ui->led_rf_ad,1,16);
    setLED(ui->led_lh_ad,1,16);
    setLED(ui->led_rh_ad,1,16);
    ui->VZ_edit->setMinimum(-10.00);
    ui->VZ_edit->setMaximum(10.00);
    ui->VZ_edit->setSingleStep(0.01);
    ui->d_edit->setMinimum(-10.00);
    ui->d_edit->setMaximum(10.00);
    ui->d_edit->setSingleStep(0.1);
    ui->v_edit->setMinimum(-10.00);
    ui->v_edit->setMaximum(10.00);
    ui->v_edit->setSingleStep(0.1);
    //init serial port and timer,scan available port.
    serialport=new QSerialPort(this);
    timer=new QTimer(this);
    scanSerialPort();
    connect(serialport,SIGNAL(readyRead()),this,
                              SLOT(serialPortReadyRead()));
    connect(this,&MainWindow::closetheconnect,this,[=](){
        ui->textEdit_status->append("连接已断开!");
    });
    //config
        initConfig();
        ui->widget_14->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scanSerialPort()
{
    //search available port info.
    ui->cbx_setPortName->clear();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {

        {
            //add port to combox
            ui->cbx_setPortName->addItem(info.portName());
        }
        qDebug()<<"串口名称:"<<ui->cbx_setPortName->currentText();
    }


}
void MainWindow::serialPortInit()
{
    //设置串口名称
    serialport->setPortName(ui->cbx_setPortName->currentText());
   qDebug()<<"串口名称:"<<serialport->portName();

   if (!serialport->open(QIODevice::ReadWrite))
   {
        qDebug()<<"cuowu";
        ui->textEdit_status->append("连接失败");
        QMessageBox::about(this,"wrong","wrong");
        serialport->close();

        return ;
   }
   else
   {
       ui->textEdit_status->append("连接成功！");
   }

   //波特率
   serialport->setBaudRate(ui->cbx_setBaudRate->currentText().toInt());
   qDebug()<<"波特率："<<ui->cbx_setBaudRate->currentText().toInt();
   //停止位
   switch (ui->cbx_setStopBits->currentText().toInt())
   {
   case 1 :  serialport->setStopBits(QSerialPort::OneStop); break;
   case 2 :  serialport->setStopBits(QSerialPort::TwoStop); break;
   default: break;
   }
   qDebug()<<"停止位:"<<serialport->stopBits();
   //数据位
   switch (ui->cbx_setDataBits->currentText().toInt())
   {
   case 5 :  serialport->setDataBits(QSerialPort::Data5); break;
   case 6 :  serialport->setDataBits(QSerialPort::Data6); break;
   case 7 :  serialport->setDataBits(QSerialPort::Data7); break;
   case 8 :  serialport->setDataBits(QSerialPort::Data8); break;
   default: break;
   }
   //奇偶位
   switch (ui->cbx_setParity->currentIndex())
   {
   case 0 :  serialport->setParity(QSerialPort::NoParity); break;
   case 1 :  serialport->setParity(QSerialPort::OddParity); break;
   case 2 :  serialport->setParity(QSerialPort::EvenParity); break;
   default: break;
   }
   qDebug()<<"奇偶位:"<<serialport->parity();

   serialport->setFlowControl(QSerialPort::NoFlowControl) ;


}


void MainWindow::on_btn_open_close_clicked()
{
    if (btn_on_off == 0)
    {

        ui->cbx_setPortName->setEnabled(false);
        ui->cbx_setBaudRate->setEnabled(false);
        ui->cbx_setDataBits->setEnabled(false);
        ui->cbx_setStopBits->setEnabled(false);
        ui->cbx_setParity->setEnabled(false);
        ui->btn_open_close->setText("close serialport");
         ui->btn_connect->setIcon(QIcon(":/duankailianjie.png"));
            ui->btn_connect->setToolTip("断开连接");
        qDebug()<<"打开串口:";
        serialPortInit();
    }

   if (btn_on_off == 1)
   {

       serialport->close();
       ui->cbx_setPortName->setEnabled(true);
       ui->cbx_setBaudRate->setEnabled(true);
       ui->cbx_setDataBits->setEnabled(true);
       ui->cbx_setStopBits->setEnabled(true);
       ui->cbx_setParity->setEnabled(true);
       ui->btn_open_close->setText("open serialport");
        ui->btn_connect->setIcon(QIcon(":/lianjie.png"));
        ui->btn_connect->setToolTip("连接");
        emit closetheconnect();
   }
   btn_on_off = !btn_on_off;
}

void MainWindow::serialPortReadyRead()
{
//    QByteArray temp = serialport->readAll();
    //     QString str = ui->textEdit_rx->toPlainText();
    //     str +=  QString::fromLocal8Bit(temp);//显示中文
    //      ui->textEdit_rx->append(str);
    QByteArray temp = serialport->readAll();
    //状态显示栏代码
    QString str;
    str=QString::fromLocal8Bit(temp);
    QString ledStr=str.mid(0,3);
    if(ledStr=="lfN") setLED(ui->led_lf,2,16);
    if(ledStr=="rfN") setLED(ui->led_rf,2,16);
    if(ledStr=="lhN") setLED(ui->led_lh,2,16);
    if(ledStr=="rhN") setLED(ui->led_rh,2,16);
    if(ledStr=="lfP") setLED(ui->led_lf,1,16);
    if(ledStr=="rfP") setLED(ui->led_rf,1,16);
    if(ledStr=="lhP") setLED(ui->led_lh,1,16);
    if(ledStr=="rhP") setLED(ui->led_rh,1,16);
    if(ledStr=="lfC") setLED(ui->led_lf,0,16);
    if(ledStr=="rfC") setLED(ui->led_rf,0,16);
    if(ledStr=="lhC") setLED(ui->led_lh,0,16);
    if(ledStr=="rhC") setLED(ui->led_rh,0,16);
    if(ledStr=="LFON") setLED(ui->led_lf_ad,2,16);
    if(ledStr=="RFON") setLED(ui->led_rf_ad,2,16);
    if(ledStr=="LHON") setLED(ui->led_lh_ad,2,16);
    if(ledStr=="RHON") setLED(ui->led_rh_ad,2,16);
    for(int i=0;i<str.length()-6;i++)
    {
        if(str[i]=='w')
        {QString newStr=str.mid(i,8);
            qDebug()<<newStr;
            if(newStr=="waiting1")
            {
                initParameters1();
                ui->textEdit_status->clear();
                ui->textEdit_status->append("检测到机器人启动，正在初始化......");
                ui->progressBar->setValue(0);
                initNum=0;
            }

            else if(newStr=="waiting2")
                initParameters2();
            else if(newStr=="waiting3")
                 initParameters3();
        }
        else if(str[i]=="r")
        {
            QString newStr=str.mid(i,8);
             qDebug()<<newStr;
             if(newStr=="receive1")
             {
             qDebug()<<"接收完成1";
             ui->progressBar->setValue(33);
             initNum=1;
             }
             if(newStr=="receive2")
             {
              qDebug()<<"接收完成2";
              ui->progressBar->setValue(66);
              initNum=2;
             }
             if(newStr=="receive3")
            {
             qDebug()<<"全部完成";
             ui->progressBar->setValue(100);
             ui->textEdit_status->append("初始化完成");
             initNum=3;
             }
        }

    }
    //串口助手部分代码
    //qDebug()<<"readdatais："<<QString::fromLocal8Bit(temp);
    if(ui->checkBox_HexShow->isChecked())
    {
        str=QString::fromLocal8Bit(temp.toHex());
        ui->textEdit_rx->append(str);
    }
    else
    {
    str =QString::fromLocal8Bit(temp);
    ui->textEdit_rx->append(str);
    }


}

void MainWindow::serialPortWrite()
{
    QByteArray buff;
    QString str;
    //判断是否非空
    if(!ui->textEdit_tx->toPlainText().isEmpty())
    {
        if(ui->checkBox_HexSend->isChecked())
        {
           str=ui->textEdit_tx->toPlainText();
           buff=dd->convertStringToHex(str);
          // qDebug()<<buff;
           serialport->write(buff);
        }
        else
        {
        buff = ui->textEdit_tx->toPlainText().toLocal8Bit();//可以写中文
        //buff+="\r\n";
        serialport->write(buff);
        //qDebug()<<"writedatais："<<serialport->write(buff);
        }
    }
}


void MainWindow::on_btn_clear_rx_clicked()
{
    ui->textEdit_rx->clear();
}

void MainWindow::on_btn_clear_tx_clicked()
{
    ui->textEdit_tx->clear();
}

void MainWindow::on_btn_send_clicked()
{
    serialPortWrite();
}
//机器人运动控制函数
void MainWindow::on_btn_motion_clicked()
{
    QString str;
    QByteArray buff;
    if(motion_state==0)
    { str="23020000000001aa";
                buff=dd->convertStringToHex(str);
         //buff+="\r\n";
        motion_state=1;
    ui->btn_motion->setIcon(QIcon(":/stop.png"));
       ui->btn_motion->setToolTip("停止");
    serialport->write(buff);

}
    else
    {
//        buff.resize(4);
//        buff[0]='=';
//        buff[1]='2';
//        buff[2]='5';
//        buff[3]='4';
         //buff+="\r\n";
        str="23020000000000aa";
                        buff=dd->convertStringToHex(str);
                motion_state=0;
            ui->btn_motion->setIcon(QIcon(":/run.png"));
               ui->btn_motion->setToolTip("启动");
            serialport->write(buff);

    }

}






void MainWindow::on_btn_vset_clicked()//Y速度
{

    QString str,str_set;
    QByteArray buff;

    str="230202";
    str_set=ui->v_edit->text();
    m_fl=str_set.toFloat();
    //qDebug()<<"fl="<<fl;
    uint f_uint = *(uint*)&m_fl;
    QString f_hex = QString("%1").arg(f_uint, 4, 16, QLatin1Char('0'));	// 4是生成字符串的长度
   // qDebug() << f_hex;

    QString temp;
    temp.resize(8);
    temp[0]=f_hex[6];
    temp[1]=f_hex[7];
    temp[2]=f_hex[4];
    temp[3]=f_hex[5];
    temp[4]=f_hex[2];
    temp[5]=f_hex[3];
    temp[6]=f_hex[0];
    temp[7]=f_hex[1];
    str+=temp;
    qDebug()<<temp;
    str+="aa";
   // qDebug()<<"str="<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);


}

void MainWindow::on_btn_dset_clicked()//X速度
{
    QString str,str_set;
    QByteArray buff;
//    float fl;
    str="230201";
    str_set=ui->d_edit->text();
    //buff=


    m_fl=str_set.toFloat();
    //qDebug()<<"fl="<<fl;
    uint f_uint = *(uint*)&m_fl;
    QString f_hex = QString("%1").arg(f_uint, 4, 16, QLatin1Char('0'));	// 4是生成字符串的长度
   // qDebug() << f_hex;

    QString temp;
    temp.resize(8);
    temp[0]=f_hex[6];
    temp[1]=f_hex[7];
    temp[2]=f_hex[4];
    temp[3]=f_hex[5];
    temp[4]=f_hex[2];
    temp[5]=f_hex[3];
    temp[6]=f_hex[0];
    temp[7]=f_hex[1];
    str+=temp;
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);

}

void MainWindow::on_btn_gmset_clicked()//步态模式
{
    QString str,str_set;
    QByteArray buff;
//    float fl;
    str="230206";
    str+="000000";
   // str_set=ui->gm_edit->text();
    if(ui->cmb_GaitMode->currentIndex()==0) str_set="00";
    else if(ui->cmb_GaitMode->currentIndex()==1) str_set="01";
    else if(ui->cmb_GaitMode->currentIndex()==2) str_set="02";
    else if(ui->cmb_GaitMode->currentIndex()==3) str_set="03";
    else if(ui->cmb_GaitMode->currentIndex()==4) str_set="05";
    else if(ui->cmb_GaitMode->currentIndex()==5) str_set="08";
    else if(ui->cmb_GaitMode->currentIndex()==6) str_set="09";
    else if(ui->cmb_GaitMode->currentIndex()==7) str_set="0C";
    else if(ui->cmb_GaitMode->currentIndex()==8) str_set="0D";
    if(ui->cmb_GaitMode->currentIndex()==0||ui->cmb_GaitMode->currentIndex()==2) ui->spb_tgu->setValue(4);
    if(ui->cmb_GaitMode->currentIndex()==1||ui->cmb_GaitMode->currentIndex()==3) ui->spb_tgu->setValue(8);
    str+=str_set;
    m_fl=str_set.toFloat();
    //buff=
//    float fl;
//    fl=str_set.toFloat();
//    //qDebug()<<"fl="<<fl;
//    uint f_uint = *(uint*)&fl;
//    QString f_hex = QString("%1").arg(f_uint, 4, 16, QLatin1Char('0'));	// 4是生成字符串的长度
//   // qDebug() << f_hex;

//    QString temp;
//    temp.resize(8);
//    temp[0]=f_hex[6];
//    temp[1]=f_hex[7];
//    temp[2]=f_hex[4];
//    temp[3]=f_hex[5];
//    temp[4]=f_hex[2];
//    temp[5]=f_hex[3];
//    temp[6]=f_hex[0];
//    temp[7]=f_hex[1];
//    str+=temp;
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}


void MainWindow::on_btn_tguset_clicked()//周期
{
    QString str,str_set;
    QByteArray buff;
//    float fl;
    str="230204";
    //str_set=ui->tgu_edit->text();
    str_set=ui->spb_tgu->text();
    //buff=

    m_fl=str_set.toFloat();
    //qDebug()<<"fl="<<fl;
    uint f_uint = *(uint*)&m_fl;
    QString f_hex = QString("%1").arg(f_uint, 4, 16, QLatin1Char('0'));	// 4是生成字符串的长度
   // qDebug() << f_hex;

    QString temp;
    temp.resize(8);
    temp[0]=f_hex[6];
    temp[1]=f_hex[7];
    temp[2]=f_hex[4];
    temp[3]=f_hex[5];
    temp[4]=f_hex[2];
    temp[5]=f_hex[3];
    temp[6]=f_hex[0];
    temp[7]=f_hex[1];
    str+=temp;
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_pset_clicked()//下压
{
    QString str,str_set;
    QByteArray buff;
//    float fl;
    str="230205";
    //str_set=ui->p_edit->text();
    str_set=ui->p_edit1->text()+ui->p_edit2->text()+ui->p_edit3->text()+ui->p_edit4->text();
    str+=str_set;
    m_pset=str_set;
    //buff=
//    float fl;
//    fl=str_set.toFloat();

//    uint f_uint = *(uint*)&fl;
//    QString f_hex = QString("%1").arg(f_uint, 4, 16, QLatin1Char('0'));	// 4是生成字符串的长度


//    QString temp;
//    temp.resize(8);
//    temp[0]=f_hex[6];
//    temp[1]=f_hex[7];
//    temp[2]=f_hex[4];
//    temp[3]=f_hex[5];
//    temp[4]=f_hex[2];
//    temp[5]=f_hex[3];
//    temp[6]=f_hex[0];
//    temp[7]=f_hex[1];
//    str+=temp;
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_checkBox_HexSend_stateChanged(int arg1)
{
    if(ui->checkBox_HexSend->isChecked())
    {
        QString str = ui->textEdit_tx->toPlainText().toLocal8Bit().toHex();
        ui->textEdit_tx->clear();
        ui->textEdit_tx->append(str);

    }
    else
    {
        QString str =ui->textEdit_tx->toPlainText().toLocal8Bit();
        QByteArray buff = dd->convertStringToHex(str);
        str.clear();
        str.prepend(buff);
        ui->textEdit_tx->clear();
        ui->textEdit_tx->append(str);


    }
}

void MainWindow::on_checkBox_HexShow_stateChanged(int arg1)
{
    if(ui->checkBox_HexShow->isChecked())
    {
        QString str = ui->textEdit_rx->toPlainText().toLocal8Bit().toHex();
        ui->textEdit_rx->clear();
        ui->textEdit_rx->append(str);

    }
    else
    {
        QString str =ui->textEdit_rx->toPlainText().toLocal8Bit();
        QByteArray buff = dd->convertStringToHex(str);
        str.clear();
        str.prepend(buff);
        ui->textEdit_rx->clear();
        ui->textEdit_rx->append(str);


    }
}


//bool MainWindow::event(QEvent *event)
//{
//    if(event->type() == QEvent::NonClientAreaMouseButtonRelease)
//    {
//        update_size(); //调用绘制窗口大小的函数
//        return true;  //返回true该事件在此处被处理后，不用传到父类
//    }
//    else if(event->type() == QEvent::Resize)
//    {

//        /*更新此时的页面宽度和长度*/
//        screen_width[0] = this->geometry().width();
//        screen_height[0] = this->geometry().height();
//        return true;
//    }
//    else
//    {

//        return QWidget::event(event);
//    }

//}


//void MainWindow::update_size()
//{
//     //设置一个大小为2的数组，一个用来存新值，一个用来存旧值，通过比较判断为页面放大操作还是缩小操作
//     if(screen_height[0]>screen_height[1] || screen_width[0]>screen_width[1])
//     {
//        this->resize((screen_height[0]>screen_width[0]?screen_height[0]:screen_width[0])-10,(screen_height[0]>screen_width[0]?screen_height[0]:screen_width[0])-10);

//     }
//     if(screen_height[0]<screen_height[1] || screen_width[0]<screen_width[1])
//     {
//         this->resize((screen_height[0]<screen_width[0]?screen_height[0]:screen_width[0])-10,(screen_height[0]<screen_width[0]?screen_height[0]:screen_width[0])-10);

//     }
//     screen_width[1] = screen_width[0];
//     screen_height[1] = screen_height[0];

//}

void MainWindow::on_btn_connect_clicked()
{
    if (btn_on_off == 0)
    {

        ui->cbx_setPortName->setEnabled(false);
        ui->cbx_setBaudRate->setEnabled(false);
        ui->cbx_setDataBits->setEnabled(false);
        ui->cbx_setStopBits->setEnabled(false);
        ui->cbx_setParity->setEnabled(false);
        ui->btn_open_close->setText("close serialport");
        ui->btn_connect->setIcon(QIcon(":/duankailianjie.png"));
             ui->btn_connect->setToolTip("断开连接");
        qDebug()<<"打开串口:";
        ui->textEdit_status->clear();
        serialPortInit();
    }

   if (btn_on_off == 1)
   {

       serialport->close();
       ui->cbx_setPortName->setEnabled(true);
       ui->cbx_setBaudRate->setEnabled(true);
       ui->cbx_setDataBits->setEnabled(true);
       ui->cbx_setStopBits->setEnabled(true);
       ui->cbx_setParity->setEnabled(true);
       ui->btn_open_close->setText("open serialport");
         ui->btn_connect->setIcon(QIcon(":/lianjie.png"));
              ui->btn_connect->setToolTip("连接");
              emit closetheconnect();
   }
   btn_on_off = !btn_on_off;
}

void MainWindow::on_btn_refresh_clicked()
{
     scanSerialPort();
}

//void MainWindow::on_PBT_Open_clicked()
//{
//    if(video_flag==0)
//    {
//            thread1->flag=1;
//            thread1->start();
//            thread2->flag=1;
//            thread2->start();
//            ui->PBT_Open->setIcon(QIcon(":/tingzhi.png"));
//             ui->PBT_Open->setToolTip("停止");
//             video_flag=1;
//    }
//    if(video_flag==1)
//    {
//        thread1->flag=0;
//        thread1->exit();
//        ui->label_1->clear();
//        thread2->flag=0;
//        thread2->exit();
//        ui->label_2->clear();
//        ui->PBT_Open->setIcon(QIcon(":/bofang.png"));
//        ui->PBT_Open->setToolTip("播放");
//        video_flag=0;
//    }
//}

void MainWindow::on_btn_vsetZ_clicked()
{
    QString str,str_set;
    QByteArray buff;

    str="230203";
    str_set=ui->VZ_edit->text();
    m_fl=str_set.toFloat();
    //qDebug()<<"fl="<<fl;
    uint f_uint = *(uint*)&m_fl;
    QString f_hex = QString("%1").arg(f_uint, 4, 16, QLatin1Char('0'));	// 4是生成字符串的长度
   // qDebug() << f_hex;

    QString temp;
    temp.resize(8);
    temp[0]=f_hex[6];
    temp[1]=f_hex[7];
    temp[2]=f_hex[4];
    temp[3]=f_hex[5];
    temp[4]=f_hex[2];
    temp[5]=f_hex[3];
    temp[6]=f_hex[0];
    temp[7]=f_hex[1];
    str+=temp;
    qDebug()<<temp;
    str+="aa";
   // qDebug()<<"str="<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_pumpset_clicked()
{
    QString data;
    QByteArray buff;
    if(ui->cmb_PumpMode->currentIndex()==0) data="23020900000001AA";
    if(ui->cmb_PumpMode->currentIndex()==1) data="23020900000000AA";
    if(ui->cmb_PumpMode->currentIndex()==2) data="23020900000002AA";
    buff=dd->convertStringToHex(data);
    serialport->write(buff);
}

void MainWindow::on_btn_imdset_clicked()
{
    QString str,str_set;
    QByteArray buff;
//    float fl;
    str="230207";
    str+="000000";
   // str_set=ui->gm_edit->text();
    if(ui->cmb_GaitMode->currentIndex()==0) str_set="00";
    else if(ui->cmb_GaitMode->currentIndex()==1) str_set="01";
    else if(ui->cmb_GaitMode->currentIndex()==2) str_set="02";
    else if(ui->cmb_GaitMode->currentIndex()==3) str_set="03";
    else if(ui->cmb_GaitMode->currentIndex()==4) str_set="05";
    else if(ui->cmb_GaitMode->currentIndex()==5) str_set="08";
    else if(ui->cmb_GaitMode->currentIndex()==6) str_set="09";
    else if(ui->cmb_GaitMode->currentIndex()==7) str_set="0C";
    if(ui->cmb_GaitMode->currentIndex()==0||ui->cmb_GaitMode->currentIndex()==2) ui->spb_tgu->setValue(4);
    if(ui->cmb_GaitMode->currentIndex()==1||ui->cmb_GaitMode->currentIndex()==3) ui->spb_tgu->setValue(8);
    str+=str_set;
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_reset_clicked()
{
     QString data="230207000000ffAA";
     QByteArray buff;
     buff=dd->convertStringToHex(data);
     serialport->write(buff);
}

void MainWindow::on_PBT_Open_clicked()
{

}


void MainWindow::initConfig()
{
//0
    ui->edit_ZeroSet_xLF->setText(AppConfig::ZeroSet_x_lf);
    connect(ui->edit_ZeroSet_xLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_xRF->setText(AppConfig::ZeroSet_x_rf);
    connect(ui->edit_ZeroSet_xRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_xLH->setText(AppConfig::ZeroSet_x_lh);
    connect(ui->edit_ZeroSet_xLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_xRH->setText(AppConfig::ZeroSet_x_rh);
    connect(ui->edit_ZeroSet_xRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_yLF->setText(AppConfig::ZeroSet_y_lf);
    connect(ui->edit_ZeroSet_yLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_yRF->setText(AppConfig::ZeroSet_y_rf);
    connect(ui->edit_ZeroSet_yRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_yLH->setText(AppConfig::ZeroSet_y_lh);
    connect(ui->edit_ZeroSet_yLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_yRH->setText(AppConfig::ZeroSet_y_rh);
    connect(ui->edit_ZeroSet_yRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_zLF->setText(AppConfig::ZeroSet_z_lf);
    connect(ui->edit_ZeroSet_zLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_zRF->setText(AppConfig::ZeroSet_z_rf);
    connect(ui->edit_ZeroSet_zRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_zLH->setText(AppConfig::ZeroSet_z_lh);
    connect(ui->edit_ZeroSet_zLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_ZeroSet_zRH->setText(AppConfig::ZeroSet_z_rh);
    connect(ui->edit_ZeroSet_zRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
 //90
    ui->edit_90Set_xLF->setText(AppConfig::_90Set_x_lf);
    connect(ui->edit_90Set_xLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_xRF->setText(AppConfig::_90Set_x_rf);
    connect(ui->edit_90Set_xRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_xLH->setText(AppConfig::_90Set_x_lh);
    connect(ui->edit_90Set_xLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_xRH->setText(AppConfig::_90Set_x_rh);
    connect(ui->edit_90Set_xRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_yLF->setText(AppConfig::_90Set_y_lf);
    connect(ui->edit_90Set_yLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_yRF->setText(AppConfig::_90Set_y_rf);
    connect(ui->edit_90Set_yRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_yLH->setText(AppConfig::_90Set_y_lh);
    connect(ui->edit_90Set_yLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_yRH->setText(AppConfig::_90Set_y_rh);
    connect(ui->edit_90Set_yRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_zLF->setText(AppConfig::_90Set_z_lf);
    connect(ui->edit_90Set_zLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_zRF->setText(AppConfig::_90Set_z_rf);
    connect(ui->edit_90Set_zRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_zLH->setText(AppConfig::_90Set_z_lh);
    connect(ui->edit_90Set_zLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Set_zRH->setText(AppConfig::_90Set_z_rh);
    connect(ui->edit_90Set_zRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
//180
    ui->edit_180Set_xLF->setText(AppConfig::_180Set_x_lf);
    connect(ui->edit_180Set_xLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_xRF->setText(AppConfig::_180Set_x_rf);
    connect(ui->edit_180Set_xRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_xLH->setText(AppConfig::_180Set_x_lh);
    connect(ui->edit_180Set_xLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_xRH->setText(AppConfig::_180Set_x_rh);
    connect(ui->edit_180Set_xRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_yLF->setText(AppConfig::_180Set_y_lf);
    connect(ui->edit_180Set_yLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_yRF->setText(AppConfig::_180Set_y_rf);
    connect(ui->edit_180Set_yRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_yLH->setText(AppConfig::_180Set_y_lh);
    connect(ui->edit_180Set_yLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_yRH->setText(AppConfig::_180Set_y_rh);
    connect(ui->edit_180Set_yRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_zLF->setText(AppConfig::_180Set_z_lf);
    connect(ui->edit_180Set_zLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_zRF->setText(AppConfig::_180Set_z_rf);
    connect(ui->edit_180Set_zRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_zLH->setText(AppConfig::_180Set_z_lh);
    connect(ui->edit_180Set_zLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Set_zRH->setText(AppConfig::_180Set_z_rh);
    connect(ui->edit_180Set_zRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
//180turn
    ui->edit_180TurnSet_xLF->setText(AppConfig::_180TurnSet_x_lf);
    connect(ui->edit_180TurnSet_xLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_xRF->setText(AppConfig::_180TurnSet_x_rf);
    connect(ui->edit_180TurnSet_xRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_xLH->setText(AppConfig::_180TurnSet_x_lh);
    connect(ui->edit_180TurnSet_xLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_xRH->setText(AppConfig::_180TurnSet_x_rh);
    connect(ui->edit_180TurnSet_xRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_yLF->setText(AppConfig::_180TurnSet_y_lf);
    connect(ui->edit_180TurnSet_yLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_yRF->setText(AppConfig::_180TurnSet_y_rf);
    connect(ui->edit_180TurnSet_yRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_yLH->setText(AppConfig::_180TurnSet_y_lh);
    connect(ui->edit_180TurnSet_yLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_yRH->setText(AppConfig::_180TurnSet_y_rh);
    connect(ui->edit_180TurnSet_yRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_zLF->setText(AppConfig::_180TurnSet_z_lf);
    connect(ui->edit_180TurnSet_zLF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_zRF->setText(AppConfig::_180TurnSet_z_rf);
    connect(ui->edit_180TurnSet_zRF,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_zLH->setText(AppConfig::_180TurnSet_z_lh);
    connect(ui->edit_180TurnSet_zLH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TurnSet_zRH->setText(AppConfig::_180TurnSet_z_rh);
    connect(ui->edit_180TurnSet_zRH,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

//下压
  //  offset of initial position	in 90 degrees	; Trot
    ui->edit_90Trot_pressSet_lf->setText(AppConfig::_90Trot_pressSet_lf);
    connect(ui->edit_90Trot_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Trot_pressSet_rf->setText(AppConfig::_90Trot_pressSet_rf);
    connect(ui->edit_90Trot_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Trot_pressSet_lh->setText(AppConfig::_90Trot_pressSet_lh);
    connect(ui->edit_90Trot_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Trot_pressSet_rh->setText(AppConfig::_90Trot_pressSet_rh);
    connect(ui->edit_90Trot_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    // //offset of initial position	in 90 degrees	; Amble
    ui->edit_90Amble_pressSet_lf->setText(AppConfig::_90Amble_pressSet_lf);
    connect(ui->edit_90Amble_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Amble_pressSet_rf->setText(AppConfig::_90Amble_pressSet_rf);
    connect(ui->edit_90Amble_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Amble_pressSet_lh->setText(AppConfig::_90Amble_pressSet_lh);
    connect(ui->edit_90Amble_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90Amble_pressSet_rh->setText(AppConfig::_90Amble_pressSet_rh);
    connect(ui->edit_90Amble_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    //offset of initial position	in 180 degrees	; Tort
    ui->edit_180Trot_pressSet_lf->setText(AppConfig::_180Trot_pressSet_lf);
    connect(ui->edit_180Trot_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Trot_pressSet_rf->setText(AppConfig::_180Trot_pressSet_rf);
    connect(ui->edit_180Trot_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Trot_pressSet_lh->setText(AppConfig::_180Trot_pressSet_lh);
    connect(ui->edit_180Trot_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Trot_pressSet_rh->setText(AppConfig::_180Trot_pressSet_rh);
    connect(ui->edit_180Trot_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    //offset of initial position	in 180 degrees	; Amble
    ui->edit_180Amble_pressSet_lf->setText(AppConfig::_180Amble_pressSet_lf);
    connect(ui->edit_180Amble_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Amble_pressSet_rf->setText(AppConfig::_180Amble_pressSet_rf);
    connect(ui->edit_180Amble_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Amble_pressSet_lh->setText(AppConfig::_180Amble_pressSet_lh);
    connect(ui->edit_180Amble_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180Amble_pressSet_rh->setText(AppConfig::_180Amble_pressSet_rh);
    connect(ui->edit_180Amble_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    //outer curved surface with 90 degrees	; Tort
    ui->edit_90OuterTrot_pressSet_lf->setText(AppConfig::_90OuterTrot_pressSet_lf);
    connect(ui->edit_90OuterTrot_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90OuterTrot_pressSet_rf->setText(AppConfig::_90OuterTrot_pressSet_rf);
    connect(ui->edit_90OuterTrot_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90OuterTrot_pressSet_lh->setText(AppConfig::_90OuterTrot_pressSet_lh);
    connect(ui->edit_90OuterTrot_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90OuterTrot_pressSet_rh->setText(AppConfig::_90OuterTrot_pressSet_rh);
    connect(ui->edit_90OuterTrot_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    //outer curved surface with 90 degrees	; Amble
    ui->edit_90OuterAmble_pressSet_lf->setText(AppConfig::_90OuterAmble_pressSet_lf);
    connect(ui->edit_90OuterAmble_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90OuterAmble_pressSet_rf->setText(AppConfig::_90OuterAmble_pressSet_rf);
    connect(ui->edit_90OuterAmble_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90OuterAmble_pressSet_lh->setText(AppConfig::_90OuterAmble_pressSet_lh);
    connect(ui->edit_90OuterAmble_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90OuterAmble_pressSet_rh->setText(AppConfig::_90OuterAmble_pressSet_rh);
    connect(ui->edit_90OuterTrot_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    //inner curved surface	; Tort
    ui->edit_90innerTrot_pressSet_lf_3->setText(AppConfig::_90innerTrot_pressSet_lf_3);
    connect(ui->edit_90innerTrot_pressSet_lf_3,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerTrot_pressSet_rf_3->setText(AppConfig::_90innerTrot_pressSet_rf_3);
    connect(ui->edit_90innerTrot_pressSet_rf_3,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerTrot_pressSet_lh_3->setText(AppConfig::_90innerTrot_pressSet_lh_3);
    connect(ui->edit_90innerTrot_pressSet_lh_3,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerTrot_pressSet_rh_3->setText(AppConfig::_90innerTrot_pressSet_rh_3);
    connect(ui->edit_90innerTrot_pressSet_rh_3,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    qDebug()<<"initext"<<AppConfig::_90innerTrot_pressSet_lf_2;
    ui->edit_90innerTrot_pressSet_lf_2->setText(AppConfig::_90innerTrot_pressSet_lf_2);
    connect(ui->edit_90innerTrot_pressSet_lf_2,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerTrot_pressSet_rf_2->setText(AppConfig::_90innerTrot_pressSet_rf_2);
    connect(ui->edit_90innerTrot_pressSet_rf_2,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerTrot_pressSet_lh_2->setText(AppConfig::_90innerTrot_pressSet_lh_2);
    connect(ui->edit_90innerTrot_pressSet_lh_2,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerTrot_pressSet_rh_2->setText(AppConfig::_90innerTrot_pressSet_rh_2);
    connect(ui->edit_90innerTrot_pressSet_rh_2,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    //inner curved surface ; Amble

    ui->edit_90innerAmble_pressSet_lf->setText(AppConfig::_90innerAmble_pressSet_lf);
    connect(ui->edit_90innerAmble_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerAmble_pressSet_rf->setText(AppConfig::_90innerAmble_pressSet_rf);
    connect(ui->edit_90innerAmble_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerAmble_pressSet_lh->setText(AppConfig::_90innerAmble_pressSet_lh);
    connect(ui->edit_90innerAmble_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90innerAmble_pressSet_rh->setText(AppConfig::_90innerAmble_pressSet_rh);
    connect(ui->edit_90innerAmble_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    //90 degrees	; Amble ; back
    ui->edit_90back_pressSet_lf->setText(AppConfig::_90back_pressSet_lf);
    connect(ui->edit_90back_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90back_pressSet_rf->setText(AppConfig::_90back_pressSet_rf);
    connect(ui->edit_90back_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90back_pressSet_lh->setText(AppConfig::_90back_pressSet_lh);
    connect(ui->edit_90back_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_90back_pressSet_rh->setText(AppConfig::_90back_pressSet_rh);
    connect(ui->edit_90back_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    //180 degrees	; Tort	;	turn
    ui->edit_180TrotTurn_pressSet_lf->setText(AppConfig::_180TrotTurn_pressSet_lf);
    connect(ui->edit_180TrotTurn_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TrotTurn_pressSet_rf->setText(AppConfig::_180TrotTurn_pressSet_rf);
    connect(ui->edit_180TrotTurn_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TrotTurn_pressSet_lh->setText(AppConfig::_180TrotTurn_pressSet_lh);
    connect(ui->edit_180TrotTurn_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180TrotTurn_pressSet_rh->setText(AppConfig::_180TrotTurn_pressSet_rh);
    connect(ui->edit_180TrotTurn_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
    //180 degrees	; Amble	;	turn
    ui->edit_180AmbleTurn_pressSet_lf->setText(AppConfig::_180AmbleTurn_pressSet_lf);
    connect(ui->edit_180AmbleTurn_pressSet_lf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180AmbleTurn_pressSet_rf->setText(AppConfig::_180AmbleTurn_pressSet_rf);
    connect(ui->edit_180AmbleTurn_pressSet_rf,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180AmbleTurn_pressSet_lh->setText(AppConfig::_180AmbleTurn_pressSet_lh);
    connect(ui->edit_180AmbleTurn_pressSet_lh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_180AmbleTurn_pressSet_rh->setText(AppConfig::_180AmbleTurn_pressSet_rh);
    connect(ui->edit_180AmbleTurn_pressSet_rh,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    //poseture attitude
    ui->edit_StancePullHight->setText(AppConfig::StancePullHight);
    connect(ui->edit_StancePullHight,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_StancePullHightDiag->setText(AppConfig::StancePullHightDiag);
    connect(ui->edit_StancePullHightDiag,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));

    ui->edit_transferForceX->setText(AppConfig::transferForceX);
    connect(ui->edit_transferForceX,SIGNAL(textChanged(QString)),this,SLOT(saveConfig()));
}

void MainWindow::saveConfig()
{

    AppConfig::ZeroSet_x_lf= ui->edit_ZeroSet_xLF->text().trimmed();
    AppConfig::ZeroSet_x_rf=ui->edit_ZeroSet_xRF->text().trimmed();
    AppConfig::ZeroSet_x_lh=ui->edit_ZeroSet_xLH->text().trimmed();
    AppConfig::ZeroSet_x_rh=ui->edit_ZeroSet_xRH->text().trimmed();
    AppConfig::ZeroSet_y_lf=ui->edit_ZeroSet_yLF->text().trimmed();
    AppConfig::ZeroSet_y_rf=ui->edit_ZeroSet_yRF->text().trimmed();
    AppConfig::ZeroSet_y_lh=ui->edit_ZeroSet_yLH->text().trimmed();
    AppConfig::ZeroSet_y_rh= ui->edit_ZeroSet_yRH->text().trimmed();
    AppConfig::ZeroSet_z_lf=ui->edit_ZeroSet_zLF->text().trimmed();
    AppConfig::ZeroSet_z_rf=ui->edit_ZeroSet_zRF->text().trimmed();
    AppConfig::ZeroSet_z_lh=ui->edit_ZeroSet_zLH->text().trimmed();
    AppConfig::ZeroSet_z_rh=ui->edit_ZeroSet_zRH->text().trimmed();

    //90
    AppConfig::_90Set_x_lf= ui->edit_90Set_xLF->text().trimmed();
    AppConfig::_90Set_x_rf=ui->edit_90Set_xRF->text().trimmed();
    AppConfig::_90Set_x_lh=ui->edit_90Set_xLH->text().trimmed();
    AppConfig::_90Set_x_rh=ui->edit_90Set_xRH->text().trimmed();
    AppConfig::_90Set_y_lf=ui->edit_90Set_yLF->text().trimmed();
    AppConfig::_90Set_y_rf=ui->edit_90Set_yRF->text().trimmed();
    AppConfig::_90Set_y_lh=ui->edit_90Set_yLH->text().trimmed();
    AppConfig::_90Set_y_rh= ui->edit_90Set_yRH->text().trimmed();
    AppConfig::_90Set_z_lf=ui->edit_90Set_zLF->text().trimmed();
    AppConfig::_90Set_z_rf=ui->edit_90Set_zRF->text().trimmed();
    AppConfig::_90Set_z_lh=ui->edit_90Set_zLH->text().trimmed();
    AppConfig::_90Set_z_rh=ui->edit_90Set_zRH->text().trimmed();

    //180
    AppConfig::_180Set_x_lf= ui->edit_180Set_xLF->text().trimmed();
    AppConfig::_180Set_x_rf=ui->edit_180Set_xRF->text().trimmed();
    AppConfig::_180Set_x_lh=ui->edit_180Set_xLH->text().trimmed();
    AppConfig::_180Set_x_rh=ui->edit_180Set_xRH->text().trimmed();
    AppConfig::_180Set_y_lf=ui->edit_180Set_yLF->text().trimmed();
    AppConfig::_180Set_y_rf=ui->edit_180Set_yRF->text().trimmed();
    AppConfig::_180Set_y_lh=ui->edit_180Set_yLH->text().trimmed();
    AppConfig::_180Set_y_rh= ui->edit_180Set_yRH->text().trimmed();
    AppConfig::_180Set_z_lf=ui->edit_180Set_zLF->text().trimmed();
    AppConfig::_180Set_z_rf=ui->edit_180Set_zRF->text().trimmed();
    AppConfig::_180Set_z_lh=ui->edit_180Set_zLH->text().trimmed();
    AppConfig::_180Set_z_rh=ui->edit_180Set_zRH->text().trimmed();

    //180turn
    AppConfig::_180TurnSet_x_lf=ui->edit_180TurnSet_xLF->text().trimmed();
    AppConfig::_180TurnSet_x_rf=ui->edit_180TurnSet_xRF->text().trimmed();
    AppConfig::_180TurnSet_x_lh=ui->edit_180TurnSet_xLH->text().trimmed();
    AppConfig::_180TurnSet_x_rh=ui->edit_180TurnSet_xRH->text().trimmed();
    AppConfig::_180TurnSet_y_lf=ui->edit_180TurnSet_yLF->text().trimmed();
    AppConfig::_180TurnSet_y_rf=ui->edit_180TurnSet_yRF->text().trimmed();
    AppConfig::_180TurnSet_y_lh=ui->edit_180TurnSet_yLH->text().trimmed();
    AppConfig::_180TurnSet_y_rh= ui->edit_180TurnSet_yRH->text().trimmed();
    AppConfig::_180TurnSet_z_lf=ui->edit_180TurnSet_zLF->text().trimmed();
    AppConfig::_180TurnSet_z_rf=ui->edit_180TurnSet_zRF->text().trimmed();
    AppConfig::_180TurnSet_z_lh=ui->edit_180TurnSet_zLH->text().trimmed();
    AppConfig::_180TurnSet_z_rh=ui->edit_180TurnSet_zRH->text().trimmed();

    //下压
    //offset of initial position	in 90 degrees	; Trot
    AppConfig::_90Trot_pressSet_lf=ui->edit_90Trot_pressSet_lf->text().trimmed();
    AppConfig::_90Trot_pressSet_rf=ui->edit_90Trot_pressSet_rf->text().trimmed();
    AppConfig::_90Trot_pressSet_lh=ui->edit_90Trot_pressSet_lh->text().trimmed();
    AppConfig::_90Trot_pressSet_rh=ui->edit_90Trot_pressSet_rh->text().trimmed();

    //offset of initial position	in 90 degrees	; Amble
    AppConfig::_90Amble_pressSet_lf=ui->edit_90Amble_pressSet_lf->text().trimmed();
    AppConfig::_90Amble_pressSet_rf=ui->edit_90Amble_pressSet_rf->text().trimmed();
    AppConfig::_90Amble_pressSet_lh=ui->edit_90Amble_pressSet_lh->text().trimmed();
    AppConfig::_90Amble_pressSet_rh=ui->edit_90Amble_pressSet_rh->text().trimmed();

    //offset of initial position	in 180 degrees	; Tort
    AppConfig::_180Trot_pressSet_lf=ui->edit_180Trot_pressSet_lf->text().trimmed();
    AppConfig::_180Trot_pressSet_rf=ui->edit_180Trot_pressSet_rf->text().trimmed();
    AppConfig::_180Trot_pressSet_lh=ui->edit_180Trot_pressSet_lh->text().trimmed();
    AppConfig::_180Trot_pressSet_rh=ui->edit_180Trot_pressSet_rh->text().trimmed();

    //offset of initial position	in 180 degrees	; Amble
    AppConfig::_180Amble_pressSet_lf=ui->edit_180Amble_pressSet_lf->text().trimmed();
    AppConfig::_180Amble_pressSet_rf=ui->edit_180Amble_pressSet_rf->text().trimmed();
    AppConfig::_180Amble_pressSet_lh=ui->edit_180Amble_pressSet_lh->text().trimmed();
    AppConfig::_180Amble_pressSet_rh=ui->edit_180Amble_pressSet_rh->text().trimmed();

    //outer curved surface with 90 degrees	; Tort
    AppConfig::_90OuterTrot_pressSet_lf=ui->edit_90OuterTrot_pressSet_lf->text().trimmed();
    AppConfig::_90OuterTrot_pressSet_rf=ui->edit_90OuterTrot_pressSet_rf->text().trimmed();
    AppConfig::_90OuterTrot_pressSet_lh=ui->edit_90OuterTrot_pressSet_lh->text().trimmed();
    AppConfig::_90OuterTrot_pressSet_rh=ui->edit_90OuterTrot_pressSet_rh->text().trimmed();

    //outer curved surface with 90 degrees	; Amble
    AppConfig::_90OuterAmble_pressSet_lf=ui->edit_90OuterAmble_pressSet_lf->text().trimmed();
    AppConfig::_90OuterAmble_pressSet_rf=ui->edit_90OuterAmble_pressSet_rf->text().trimmed();
    AppConfig::_90OuterAmble_pressSet_lh=ui->edit_90OuterAmble_pressSet_lh->text().trimmed();
    AppConfig::_90OuterAmble_pressSet_rh=ui->edit_90OuterAmble_pressSet_rh->text().trimmed();

    //inner curved surface	; Tort
    AppConfig::_90innerTrot_pressSet_lf_3=ui->edit_90innerTrot_pressSet_lf_3->text().trimmed();
    AppConfig::_90innerTrot_pressSet_rf_3=ui->edit_90innerTrot_pressSet_rf_3->text().trimmed();
    AppConfig::_90innerTrot_pressSet_lh_3=ui->edit_90innerTrot_pressSet_lh_3->text().trimmed();
    AppConfig::_90innerTrot_pressSet_rh_3=ui->edit_90innerTrot_pressSet_rh_3->text().trimmed();

    AppConfig::_90innerTrot_pressSet_lf_2=ui->edit_90innerTrot_pressSet_lf_2->text().trimmed();
    AppConfig::_90innerTrot_pressSet_rf_2=ui->edit_90innerTrot_pressSet_rf_2->text().trimmed();
    AppConfig::_90innerTrot_pressSet_lh_2=ui->edit_90innerTrot_pressSet_lh_2->text().trimmed();
    AppConfig::_90innerTrot_pressSet_rh_2=ui->edit_90innerTrot_pressSet_rh_2->text().trimmed();

    //inner curved surface ; Amble
    AppConfig::_90innerAmble_pressSet_lf=ui->edit_90innerAmble_pressSet_lf->text().trimmed();
    AppConfig::_90innerAmble_pressSet_rf=ui->edit_90innerAmble_pressSet_rf->text().trimmed();
    AppConfig::_90innerAmble_pressSet_lh=ui->edit_90innerAmble_pressSet_lh->text().trimmed();
    AppConfig::_90innerAmble_pressSet_rh=ui->edit_90innerAmble_pressSet_rh->text().trimmed();

    //90 degrees	; Amble ; back
    AppConfig::_90back_pressSet_lf=ui->edit_90back_pressSet_lf->text().trimmed();
    AppConfig::_90back_pressSet_rf=ui->edit_90back_pressSet_rf->text().trimmed();
    AppConfig::_90back_pressSet_lh=ui->edit_90back_pressSet_lh->text().trimmed();
    AppConfig::_90back_pressSet_rh=ui->edit_90back_pressSet_rh->text().trimmed();

    //180 degrees	; Tort	;	turn
    AppConfig::_180TrotTurn_pressSet_lf=ui->edit_180TrotTurn_pressSet_lf->text().trimmed();
    AppConfig::_180TrotTurn_pressSet_rf=ui->edit_180TrotTurn_pressSet_rf->text().trimmed();
    AppConfig::_180TrotTurn_pressSet_lh=ui->edit_180TrotTurn_pressSet_lh->text().trimmed();
    AppConfig::_180TrotTurn_pressSet_rh=ui->edit_180TrotTurn_pressSet_rh->text().trimmed();

    //180 degrees	; Amble	;	turn
    AppConfig::_180AmbleTurn_pressSet_lf=ui->edit_180AmbleTurn_pressSet_lf->text().trimmed();
    AppConfig::_180AmbleTurn_pressSet_rf=ui->edit_180AmbleTurn_pressSet_rf->text().trimmed();
    AppConfig::_180AmbleTurn_pressSet_lh=ui->edit_180AmbleTurn_pressSet_lh->text().trimmed();
    AppConfig::_180AmbleTurn_pressSet_rh=ui->edit_180AmbleTurn_pressSet_rh->text().trimmed();

    //poseture attitude
    AppConfig::StancePullHight=ui->edit_StancePullHight->text().trimmed();
    AppConfig::StancePullHightDiag=ui->edit_StancePullHightDiag->text().trimmed();
    AppConfig::transferForceX=ui->edit_transferForceX->text().trimmed();
    AppConfig::writeConfig();

}


void MainWindow::initParameters1()
{
    QByteArray buff;
    QString press_lf,press_rf,press_lh,press_rh;
    QString str_xLF=signedDatatoHex(ui->edit_ZeroSet_xLF->text());
    QString str_xRF=signedDatatoHex(ui->edit_ZeroSet_xRF->text());
    QString str_xLH=signedDatatoHex(ui->edit_ZeroSet_xLH->text());
    QString str_xRH=signedDatatoHex(ui->edit_ZeroSet_xRH->text());
    QString str_yLF=signedDatatoHex(ui->edit_ZeroSet_yLF->text());
    QString str_yRF=signedDatatoHex(ui->edit_ZeroSet_yRF->text());
    QString str_yLH=signedDatatoHex(ui->edit_ZeroSet_yLH->text());
    QString str_yRH=signedDatatoHex(ui->edit_ZeroSet_yRH->text());
    QString str_zLF=signedDatatoHex(ui->edit_ZeroSet_zLF->text());
    QString str_zRF=signedDatatoHex(ui->edit_ZeroSet_zRF->text());
    QString str_zLH=signedDatatoHex(ui->edit_ZeroSet_zLH->text());
    QString str_zRH=signedDatatoHex(ui->edit_ZeroSet_zRH->text());
    QString data1="2302A0"+str_xLF+str_xRF+str_xLH+str_xRH+"AA";
    QString data2="2302A1"+str_yLF+str_yRF+str_yLH+str_yRH+"AA";
    QString data3="2302A2"+str_zLF+str_zRF+str_zLH+str_zRH+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
    buff=dd->convertStringToHex(data2);
    serialport->write(buff);
    buff=dd->convertStringToHex(data3);
    serialport->write(buff);
    delay_ms(100);
     str_xLF=signedDatatoHex(ui->edit_90Set_xLF->text());
     str_xRF=signedDatatoHex(ui->edit_90Set_xRF->text());
     str_xLH=signedDatatoHex(ui->edit_90Set_xLH->text());
     str_xRH=signedDatatoHex(ui->edit_90Set_xRH->text());
     str_yLF=signedDatatoHex(ui->edit_90Set_yLF->text());
     str_yRF=signedDatatoHex(ui->edit_90Set_yRF->text());
     str_yLH=signedDatatoHex(ui->edit_90Set_yLH->text());
     str_yRH=signedDatatoHex(ui->edit_90Set_yRH->text());
     str_zLF=signedDatatoHex(ui->edit_90Set_zLF->text());
     str_zRF=signedDatatoHex(ui->edit_90Set_zRF->text());
     str_zLH=signedDatatoHex(ui->edit_90Set_zLH->text());
     str_zRH=signedDatatoHex(ui->edit_90Set_zRH->text());
     data1="2302A3"+str_xLF+str_xRF+str_xLH+str_xRH+"AA";
     data2="2302A4"+str_yLF+str_yRF+str_yLH+str_yRH+"AA";
     data3="2302A5"+str_zLF+str_zRF+str_zLH+str_zRH+"AA";
     buff=dd->convertStringToHex(data1);
     serialport->write(buff);
     buff=dd->convertStringToHex(data2);
     serialport->write(buff);
     buff=dd->convertStringToHex(data3);
     serialport->write(buff);
 delay_ms(100);
     str_xLF=signedDatatoHex(ui->edit_180Set_xLF->text());
     str_xRF=signedDatatoHex(ui->edit_180Set_xRF->text());
     str_xLH=signedDatatoHex(ui->edit_180Set_xLH->text());
     str_xRH=signedDatatoHex(ui->edit_180Set_xRH->text());
     str_yLF=signedDatatoHex(ui->edit_180Set_yLF->text());
     str_yRF=signedDatatoHex(ui->edit_180Set_yRF->text());
     str_yLH=signedDatatoHex(ui->edit_180Set_yLH->text());
     str_yRH=signedDatatoHex(ui->edit_180Set_yRH->text());
     str_zLF=signedDatatoHex(ui->edit_180Set_zLF->text());
     str_zRF=signedDatatoHex(ui->edit_180Set_zRF->text());
     str_zLH=signedDatatoHex(ui->edit_180Set_zLH->text());
     str_zRH=signedDatatoHex(ui->edit_180Set_zRH->text());
     data1="2302A6"+str_xLF+str_xRF+str_xLH+str_xRH+"AA";
     data2="2302A7"+str_yLF+str_yRF+str_yLH+str_yRH+"AA";
     data3="2302A8"+str_zLF+str_zRF+str_zLH+str_zRH+"AA";
     buff=dd->convertStringToHex(data1);
     serialport->write(buff);
     buff=dd->convertStringToHex(data2);
     serialport->write(buff);
     buff=dd->convertStringToHex(data3);
     serialport->write(buff);
    qDebug()<<"1over";

}

void MainWindow::initParameters2()
{
    QByteArray buff;
    QString press_lf,press_rf,press_lh,press_rh;
    QString str_xLF=signedDatatoHex(ui->edit_180TurnSet_xLF->text());
    QString str_xRF=signedDatatoHex(ui->edit_180TurnSet_xRF->text());
    QString str_xLH=signedDatatoHex(ui->edit_180TurnSet_xLH->text());
    QString str_xRH=signedDatatoHex(ui->edit_180TurnSet_xRH->text());
    QString str_yLF=signedDatatoHex(ui->edit_180TurnSet_yLF->text());
    QString str_yRF=signedDatatoHex(ui->edit_180TurnSet_yRF->text());
    QString str_yLH=signedDatatoHex(ui->edit_180TurnSet_yLH->text());
    QString str_yRH=signedDatatoHex(ui->edit_180TurnSet_yRH->text());
    QString str_zLF=signedDatatoHex(ui->edit_180TurnSet_zLF->text());
    QString str_zRF=signedDatatoHex(ui->edit_180TurnSet_zRF->text());
    QString str_zLH=signedDatatoHex(ui->edit_180TurnSet_zLH->text());
    QString str_zRH=signedDatatoHex(ui->edit_180TurnSet_zRH->text());
    QString data1="2302A9"+str_xLF+str_xRF+str_xLH+str_xRH+"AA";
    QString data2="2302AA"+str_yLF+str_yRF+str_yLH+str_yRH+"AA";
    QString data3="2302AB"+str_zLF+str_zRF+str_zLH+str_zRH+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
    buff=dd->convertStringToHex(data2);
    serialport->write(buff);
    buff=dd->convertStringToHex(data3);
    serialport->write(buff);
    delay_ms(100);
    //press
    press_lf=signedDatatoHex(ui->edit_90Trot_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_90Trot_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_90Trot_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_90Trot_pressSet_rh->text());
    data1="2302AC"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);

    press_lf=signedDatatoHex(ui->edit_90Amble_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_90Amble_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_90Amble_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_90Amble_pressSet_rh->text());
    data1="2302AD"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
 delay_ms(100);
    press_lf=signedDatatoHex(ui->edit_180Trot_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_180Trot_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_180Trot_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_180Trot_pressSet_rh->text());
    data1="2302AE"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);

    press_lf=signedDatatoHex(ui->edit_180Amble_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_180Amble_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_180Amble_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_180Amble_pressSet_rh->text());
    data1="2302AF"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
   // delay_ms(100);
    qDebug()<<"2over";

}
void MainWindow::initParameters3()
{
    QString press_lf,press_rf,press_lh,press_rh;
    press_lf=signedDatatoHex(ui->edit_90OuterTrot_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_90OuterTrot_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_90OuterTrot_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_90OuterTrot_pressSet_rh->text());
    QString data1="2302B0"+press_lf+press_rf+press_lh+press_rh+"AA";
    QByteArray buff=dd->convertStringToHex(data1);
    serialport->write(buff);
  delay_ms(200);
    press_lf=signedDatatoHex(ui->edit_90OuterAmble_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_90OuterAmble_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_90OuterAmble_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_90OuterAmble_pressSet_rh->text());
    data1="2302B1"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
    delay_ms(200);
    press_lf=signedDatatoHex(ui->edit_90innerTrot_pressSet_lf_3->text());
    press_rf=signedDatatoHex(ui->edit_90innerTrot_pressSet_rf_3->text());
    press_lh=signedDatatoHex(ui->edit_90innerTrot_pressSet_lh_3->text());
    press_rh=signedDatatoHex(ui->edit_90innerTrot_pressSet_rh_3->text());
    data1="2302B2"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
   delay_ms(200);

    press_lf=signedDatatoHex(ui->edit_90innerAmble_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_90innerAmble_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_90innerAmble_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_90innerAmble_pressSet_rh->text());
    data1="2302B3"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
   delay_ms(200);
    press_lf=signedDatatoHex(ui->edit_90back_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_90back_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_90back_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_90back_pressSet_rh->text());
    data1="2302B4"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
   delay_ms(200);
    press_lf=signedDatatoHex(ui->edit_180TrotTurn_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_180TrotTurn_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_180TrotTurn_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_180TrotTurn_pressSet_rh->text());
    data1="2302B5"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);
     delay_ms(200);
    press_lf=signedDatatoHex(ui->edit_180AmbleTurn_pressSet_lf->text());
    press_rf=signedDatatoHex(ui->edit_180AmbleTurn_pressSet_rf->text());
    press_lh=signedDatatoHex(ui->edit_180AmbleTurn_pressSet_lh->text());
    press_rh=signedDatatoHex(ui->edit_180AmbleTurn_pressSet_rh->text());
    data1="2302B6"+press_lf+press_rf+press_lh+press_rh+"AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);

    QString StancePullHight=signedDatatoHex(ui->edit_StancePullHight->text());
    QString StancePullHightDiag=signedDatatoHex(ui->edit_StancePullHightDiag->text());
    QString transferForceX=signedDatatoHex(ui->edit_transferForceX->text());
    data1="2302B7"+StancePullHight+StancePullHightDiag+transferForceX+"00AA";
    buff=dd->convertStringToHex(data1);
    serialport->write(buff);

    qDebug()<<"3over";
}
void MainWindow::delay_ms(int time)
{
    QTime Time;
    Time.start();
    while(Time.elapsed() < time)
    {
        QCoreApplication::processEvents();
    }

}
void MainWindow::readMessage(QByteArray buff)
{


}



void MainWindow::on_btn_iniPositionSet1_clicked()
{
    initParameters1();
}

void MainWindow::on_btn_iniPositionSet2_clicked()
{
    initParameters2();
}

void MainWindow::on_btn_iniPositionSet3_clicked()
{
    initParameters3();
}

void MainWindow::on_btn_copy_clicked()
{
    int i=0;
    dataStore[i++]=AppConfig::ZeroSet_x_lf;
    dataStore[i++]=AppConfig::ZeroSet_x_rf;
    dataStore[i++]=AppConfig::ZeroSet_x_lh;
    dataStore[i++]=AppConfig::ZeroSet_x_rh;
    dataStore[i++]=AppConfig::ZeroSet_y_lf;
    dataStore[i++]=AppConfig::ZeroSet_y_rf;
    dataStore[i++]=AppConfig::ZeroSet_y_lh;
    dataStore[i++]=AppConfig::ZeroSet_y_rh;
    dataStore[i++]=AppConfig::ZeroSet_z_lf;
    dataStore[i++]=AppConfig::ZeroSet_z_rf;
    dataStore[i++]=AppConfig::ZeroSet_z_lh;
    dataStore[i++]=AppConfig::ZeroSet_z_rh;

     dataStore[i++]=AppConfig::_90Set_x_lf;
     dataStore[i++]=AppConfig::_90Set_x_rf;
     dataStore[i++]=AppConfig::_90Set_x_lh;
    dataStore[i++]= AppConfig::_90Set_x_rh;
     dataStore[i++]=AppConfig::_90Set_y_lf;
     dataStore[i++]=AppConfig::_90Set_y_rf;
     dataStore[i++]=AppConfig::_90Set_y_lh;
     dataStore[i++]=AppConfig::_90Set_y_rh;
     dataStore[i++]=AppConfig::_90Set_z_lf;
    dataStore[i++]= AppConfig::_90Set_z_rf;
    dataStore[i++]= AppConfig::_90Set_z_lh;
     dataStore[i++]=AppConfig::_90Set_z_rh;

    dataStore[i++]= AppConfig::_180Set_x_lf;
    dataStore[i++]= AppConfig::_180Set_x_rf;
    dataStore[i++]= AppConfig::_180Set_x_lh;
    dataStore[i++]= AppConfig::_180Set_x_rh;
    dataStore[i++]= AppConfig::_180Set_y_lf;
    dataStore[i++]= AppConfig::_180Set_y_rf;
    dataStore[i++]= AppConfig::_180Set_y_lh;
     dataStore[i++]=AppConfig::_180Set_y_rh;
    dataStore[i++]= AppConfig::_180Set_z_lf;
     dataStore[i++]=AppConfig::_180Set_z_rf;
     dataStore[i++]=AppConfig::_180Set_z_lh;
     dataStore[i++]=AppConfig::_180Set_z_rh;

     dataStore[i++]=AppConfig::_180TurnSet_x_lf;
    dataStore[i++]= AppConfig::_180TurnSet_x_rf;
    dataStore[i++]= AppConfig::_180TurnSet_x_lh;
    dataStore[i++]= AppConfig::_180TurnSet_x_rh;
    dataStore[i++]= AppConfig::_180TurnSet_y_lf;
    dataStore[i++]= AppConfig::_180TurnSet_y_rf;
    dataStore[i++]= AppConfig::_180TurnSet_y_lh;
    dataStore[i++]= AppConfig::_180TurnSet_y_rh;
     dataStore[i++]=AppConfig::_180TurnSet_z_lf;
     dataStore[i++]=AppConfig::_180TurnSet_z_rf;
     dataStore[i++]=AppConfig::_180TurnSet_z_lh;
     dataStore[i++]=AppConfig::_180TurnSet_z_rh;

    //下压
     dataStore[i++]=AppConfig::_90Trot_pressSet_lf;
     dataStore[i++]= AppConfig::_90Trot_pressSet_rf;
     dataStore[i++]= AppConfig::_90Trot_pressSet_lh;
     dataStore[i++]= AppConfig::_90Trot_pressSet_rh;

      dataStore[i++]=AppConfig::_90Amble_pressSet_lf;
     dataStore[i++]= AppConfig::_90Amble_pressSet_rf;
      dataStore[i++]=AppConfig::_90Amble_pressSet_lh;
      dataStore[i++]=AppConfig::_90Amble_pressSet_rh;

      dataStore[i++]=AppConfig::_180Trot_pressSet_lf;
      dataStore[i++]=AppConfig::_180Trot_pressSet_rf;
      dataStore[i++]=AppConfig::_180Trot_pressSet_lh;
      dataStore[i++]=AppConfig::_180Trot_pressSet_rh;


      dataStore[i++]=AppConfig::_180Amble_pressSet_lf;
     dataStore[i++]= AppConfig::_180Amble_pressSet_rf;
     dataStore[i++]= AppConfig::_180Amble_pressSet_lh;
     dataStore[i++]= AppConfig::_180Amble_pressSet_rh;

      dataStore[i++]=AppConfig::_90OuterTrot_pressSet_lf;
      dataStore[i++]=AppConfig::_90OuterTrot_pressSet_rf;
     dataStore[i++]= AppConfig::_90OuterTrot_pressSet_lh;
      dataStore[i++]=AppConfig::_90OuterTrot_pressSet_rh;

      dataStore[i++]=AppConfig::_90OuterAmble_pressSet_lf;
      dataStore[i++]=AppConfig::_90OuterAmble_pressSet_rf;
      dataStore[i++]=AppConfig::_90OuterAmble_pressSet_lh;
      dataStore[i++]=AppConfig::_90OuterAmble_pressSet_rh;

      dataStore[i++]=AppConfig::_90innerTrot_pressSet_lf_3;
      dataStore[i++]=AppConfig::_90innerTrot_pressSet_rf_3;
      dataStore[i++]=AppConfig::_90innerTrot_pressSet_lh_3;
      dataStore[i++]=AppConfig::_90innerTrot_pressSet_rh_3;


      dataStore[i++]=AppConfig::_90innerAmble_pressSet_lf;
      dataStore[i++]=AppConfig::_90innerAmble_pressSet_rf;
      dataStore[i++]=AppConfig::_90innerAmble_pressSet_lh;
      dataStore[i++]=AppConfig::_90innerAmble_pressSet_rh;

      dataStore[i++]=AppConfig::_90back_pressSet_lf;
      dataStore[i++]=AppConfig::_90back_pressSet_rf;
      dataStore[i++]=AppConfig::_90back_pressSet_lh;
      dataStore[i++]=AppConfig::_90back_pressSet_rh;

      dataStore[i++]=AppConfig::_180TrotTurn_pressSet_lf;
      dataStore[i++]=AppConfig::_180TrotTurn_pressSet_rf;
      dataStore[i++]=AppConfig::_180TrotTurn_pressSet_lh;
      dataStore[i++]=AppConfig::_180TrotTurn_pressSet_rh;

      dataStore[i++]=AppConfig::_180AmbleTurn_pressSet_lf;
      dataStore[i++]=AppConfig::_180AmbleTurn_pressSet_rf;
      dataStore[i++]=AppConfig::_180AmbleTurn_pressSet_lh;
      dataStore[i++]=AppConfig::_180AmbleTurn_pressSet_rh;

      dataStore[i++]=AppConfig::StancePullHight;
      dataStore[i++]=AppConfig::StancePullHightDiag;
      dataStore[i++]=AppConfig::transferForceX;

}

void MainWindow::on_btn_recover_clicked()
{
    int i=0;
    ui->edit_ZeroSet_xLF->setText(dataStore[i++]);
    ui->edit_ZeroSet_xRF->setText(dataStore[i++]);
    ui->edit_ZeroSet_xLH->setText(dataStore[i++]);
    ui->edit_ZeroSet_xRH->setText(dataStore[i++]);
    ui->edit_ZeroSet_yLF->setText(dataStore[i++]);
    ui->edit_ZeroSet_yRF->setText(dataStore[i++]);
    ui->edit_ZeroSet_yLH->setText(dataStore[i++]);
    ui->edit_ZeroSet_yRH->setText(dataStore[i++]);
    ui->edit_ZeroSet_zLF->setText(dataStore[i++]);
    ui->edit_ZeroSet_zRF->setText(dataStore[i++]);
    ui->edit_ZeroSet_zLH->setText(dataStore[i++]);
    ui->edit_ZeroSet_zRH->setText(dataStore[i++]);
    //90
    ui->edit_90Set_xLF->setText(dataStore[i++]);
    ui->edit_90Set_xRF->setText(dataStore[i++]);
    ui->edit_90Set_xLH->setText(dataStore[i++]);
    ui->edit_90Set_xRH->setText(dataStore[i++]);
    ui->edit_90Set_yLF->setText(dataStore[i++]);
    ui->edit_90Set_yRF->setText(dataStore[i++]);
    ui->edit_90Set_yLH->setText(dataStore[i++]);
    ui->edit_90Set_yRH->setText(dataStore[i++]);
    ui->edit_90Set_zLF->setText(dataStore[i++]);
    ui->edit_90Set_zRF->setText(dataStore[i++]);
    ui->edit_90Set_zLH->setText(dataStore[i++]);
    ui->edit_90Set_zRH->setText(dataStore[i++]);
    //180
    ui->edit_180Set_xLF->setText(dataStore[i++]);
    ui->edit_180Set_xRF->setText(dataStore[i++]);
    ui->edit_180Set_xLH->setText(dataStore[i++]);
    ui->edit_180Set_xRH->setText(dataStore[i++]);
    ui->edit_180Set_yLF->setText(dataStore[i++]);
    ui->edit_180Set_yRF->setText(dataStore[i++]);
    ui->edit_180Set_yLH->setText(dataStore[i++]);
    ui->edit_180Set_yRH->setText(dataStore[i++]);
    ui->edit_180Set_zLF->setText(dataStore[i++]);
    ui->edit_180Set_zRF->setText(dataStore[i++]);
    ui->edit_180Set_zLH->setText(dataStore[i++]);
    ui->edit_180Set_zRH->setText(dataStore[i++]);
    //180turn
    ui->edit_180TurnSet_xLF->setText(dataStore[i++]);
    ui->edit_180TurnSet_xRF->setText(dataStore[i++]);
    ui->edit_180TurnSet_xLH->setText(dataStore[i++]);
    ui->edit_180TurnSet_xRH->setText(dataStore[i++]);
    ui->edit_180TurnSet_yLF->setText(dataStore[i++]);
    ui->edit_180TurnSet_yRF->setText(dataStore[i++]);
    ui->edit_180TurnSet_yLH->setText(dataStore[i++]);
    ui->edit_180TurnSet_yRH->setText(dataStore[i++]);
    ui->edit_180TurnSet_zLF->setText(dataStore[i++]);
    ui->edit_180TurnSet_zRF->setText(dataStore[i++]);
    ui->edit_180TurnSet_zLH->setText(dataStore[i++]);
    ui->edit_180TurnSet_zRH->setText(dataStore[i++]);
//下压
  //  offset of initial position	in 90 degrees	; Trot
    ui->edit_90Trot_pressSet_lf->setText(dataStore[i++]);
    ui->edit_90Trot_pressSet_rf->setText(dataStore[i++]);
    ui->edit_90Trot_pressSet_lh->setText(dataStore[i++]);
    ui->edit_90Trot_pressSet_rh->setText(dataStore[i++]);
    // //offset of initial position	in 90 degrees	; Amble
    ui->edit_90Amble_pressSet_lf->setText(dataStore[i++]);
    ui->edit_90Amble_pressSet_rf->setText(dataStore[i++]);
    ui->edit_90Amble_pressSet_lh->setText(dataStore[i++]);
    ui->edit_90Amble_pressSet_rh->setText(dataStore[i++]);
    //offset of initial position	in 180 degrees	; Tort
    ui->edit_180Trot_pressSet_lf->setText(dataStore[i++]);
    ui->edit_180Trot_pressSet_rf->setText(dataStore[i++]);
    ui->edit_180Trot_pressSet_lh->setText(dataStore[i++]);
    ui->edit_180Trot_pressSet_rh->setText(dataStore[i++]);
    //offset of initial position	in 180 degrees	; Amble
    ui->edit_180Amble_pressSet_lf->setText(dataStore[i++]);
    ui->edit_180Amble_pressSet_rf->setText(dataStore[i++]);
    ui->edit_180Amble_pressSet_lh->setText(dataStore[i++]);
    ui->edit_180Amble_pressSet_rh->setText(dataStore[i++]);
    //outer curved surface with 90 degrees	; Tort
    ui->edit_90OuterTrot_pressSet_lf->setText(dataStore[i++]);
    ui->edit_90OuterTrot_pressSet_rf->setText(dataStore[i++]);
    ui->edit_90OuterTrot_pressSet_lh->setText(dataStore[i++]);
    ui->edit_90OuterTrot_pressSet_rh->setText(dataStore[i++]);
    //outer curved surface with 90 degrees	; Amble
    ui->edit_90OuterAmble_pressSet_lf->setText(dataStore[i++]);
    ui->edit_90OuterAmble_pressSet_rf->setText(dataStore[i++]);
    ui->edit_90OuterAmble_pressSet_lh->setText(dataStore[i++]);
    ui->edit_90OuterAmble_pressSet_rh->setText(dataStore[i++]);
    //inner curved surface	; Tort
    ui->edit_90innerTrot_pressSet_lf_3->setText(dataStore[i++]);
    ui->edit_90innerTrot_pressSet_rf_3->setText(dataStore[i++]);
    ui->edit_90innerTrot_pressSet_lh_3->setText(dataStore[i++]);
    ui->edit_90innerTrot_pressSet_rh_3->setText(dataStore[i++]);

    //inner curved surface ; Amble
    ui->edit_90innerAmble_pressSet_lf->setText(dataStore[i++]);
    ui->edit_90innerAmble_pressSet_rf->setText(dataStore[i++]);
    ui->edit_90innerAmble_pressSet_lh->setText(dataStore[i++]);
    ui->edit_90innerAmble_pressSet_rh->setText(dataStore[i++]);
    //90 degrees	; Amble ; back
    ui->edit_90back_pressSet_lf->setText(dataStore[i++]);
    ui->edit_90back_pressSet_rf->setText(dataStore[i++]);
    ui->edit_90back_pressSet_lh->setText(dataStore[i++]);
    ui->edit_90back_pressSet_rh->setText(dataStore[i++]);
    //180 degrees	; Tort	;	turn
    ui->edit_180TrotTurn_pressSet_lf->setText(dataStore[i++]);
    ui->edit_180TrotTurn_pressSet_rf->setText(dataStore[i++]);
    ui->edit_180TrotTurn_pressSet_lh->setText(dataStore[i++]);
    ui->edit_180TrotTurn_pressSet_rh->setText(dataStore[i++]);
    //180 degrees	; Amble	;	turn
    ui->edit_180AmbleTurn_pressSet_lf->setText(dataStore[i++]);
    ui->edit_180AmbleTurn_pressSet_rf->setText(dataStore[i++]);
    ui->edit_180AmbleTurn_pressSet_lh->setText(dataStore[i++]);
    ui->edit_180AmbleTurn_pressSet_rh->setText(dataStore[i++]);

    //poseture attitude
    ui->edit_StancePullHight->setText(dataStore[i++]);
    ui->edit_StancePullHightDiag->setText(dataStore[i++]);
    ui->edit_transferForceX->setText(dataStore[i++]);
}

void MainWindow::on_btn_initRepeat_clicked()
{
    switch (initNum) {
    case 0:
        initParameters1();
        break;
    case 1:
        initParameters2();
        break;
    case 2:
        initParameters3();
        break;
    default:
        ui->textEdit_status->setText("初始化已完成！");
        break;
    }
}


void MainWindow::setLED(QLabel* label, int color, int size)
{
    // 将label中的文字清空
    label->setText("");
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);

}

void MainWindow::on_pushButton_clicked()
{
    ui->d_edit->setValue(3.0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->d_edit->setValue(0.0);
}

void MainWindow::on_pushButton_5_clicked()
{
     ui->v_edit->setValue(2.5);
}

void MainWindow::on_pushButton_6_clicked()
{
     ui->v_edit->setValue(0.0);
}


void MainWindow::on_pushButton_3_clicked()
{
         ui->d_edit->setValue(1.0);
}

void MainWindow::on_pushButton_4_clicked()
{
  ui->VZ_edit->setValue(0.01);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->VZ_edit->setValue(-0.01);
}

void MainWindow::on_btn_lfControl_clicked()
{
    ui->btn_rfControl->setStyleSheet("background-color:white");
    ui->btn_rhControl->setStyleSheet("background-color:white");
    ui->btn_lhControl->setStyleSheet("background-color:white");
    ui->btn_lfControl->setStyleSheet("background-color:red");
    chosendLeg=0;
}



void MainWindow::on_btn_rfControl_clicked()
{
    ui->btn_rfControl->setStyleSheet("background-color:red");
    ui->btn_rhControl->setStyleSheet("background-color:white");
    ui->btn_lhControl->setStyleSheet("background-color:white");
    ui->btn_lfControl->setStyleSheet("background-color:white");
    chosendLeg=1;
}

void MainWindow::on_btn_lhControl_clicked()
{
    ui->btn_rfControl->setStyleSheet("background-color:white");
    ui->btn_rhControl->setStyleSheet("background-color:white");
    ui->btn_lhControl->setStyleSheet("background-color:red");
    ui->btn_lfControl->setStyleSheet("background-color:white");
    chosendLeg=2;
}

void MainWindow::on_btn_rhControl_clicked()
{
    ui->btn_rfControl->setStyleSheet("background-color:white");
    ui->btn_rhControl->setStyleSheet("background-color:red");
    ui->btn_lhControl->setStyleSheet("background-color:white");
    ui->btn_lfControl->setStyleSheet("background-color:white");
    chosendLeg=3;
}

void MainWindow::on_btn_forward_clicked()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="000100";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}


void MainWindow::on_btn_forward_pressed()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="000100";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}


void MainWindow::on_btn_back_clicked()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="000001";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_back_pressed()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="000001";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_left_clicked()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="010100";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}



void MainWindow::on_btn_left_pressed()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="010100";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_right_clicked()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="010001";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_right_pressed()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="010001";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}


void MainWindow::on_btn_up_clicked()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="020100";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_up_pressed()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="020100";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_down_clicked()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="020001";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}

void MainWindow::on_btn_down_pressed()
{
    QString str;
    QByteArray buff;
//    float fl;
    str="23020A";
    QString leg=QString("0%1").arg(chosendLeg);
    str+=leg;
    str+="020001";
    str+="aa";
    qDebug()<<str;
    buff=dd->convertStringToHex(str);
    serialport->write(buff);
}
