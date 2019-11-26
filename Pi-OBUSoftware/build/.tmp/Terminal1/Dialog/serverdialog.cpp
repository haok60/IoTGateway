#include "serverdialog.h"
#include "ui_serverdialog.h"
#include "QDebug"
#include "data.h"
#include <QObject>
#include "QHttp"

ServerDialog::ServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    http = new QNetworkAccessManager(this);
    QNetworkAccessManager::connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), SLOT(ketNoi()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(loiSocket(QAbstractSocket::SocketError)));
    kichThuoc = 0;
}

ServerDialog::~ServerDialog()
{
    delete ui;
}
void ServerDialog::replyFinished(QNetworkReply *reply)
{
    QString res = reply->readAll().trimmed();
    qDebug() << "result:   "<< res;
}
void ServerDialog::on_btnConnect_clicked()
{
  QString IP = ui ->lineIP->text();
  QString  port = ui->linePort->text();
  QTextStream text(&port);
  quint16 num =0;
  text >> num;
  socket->abort();
    //socket->connectToHost(QHostAddress(Ip),50885);
  socket->connectToHost(QHostAddress(IP),num);
}

void ServerDialog::on_btnSend_clicked()
{
    int Con = ui->cbxConnect->currentIndex();
    int i=0;
  //DATA::lat = "21.005800";
  //DATA::lng = "105.842128";
//DATA::mac = "04";
//DATA::Ip = "143E";
//   DATA::temp = "30.55";
//   DATA::hump ="50.4567";
    if((!DATA::lat.isEmpty())&&(!DATA::lng.isEmpty())) i+=1;
    if((!DATA::temp.isEmpty())&&(!DATA::hump.isEmpty())) i+=10;
    QString dataSend;   
    QTextStream out(socket);

    switch(i){
    case 1:{
             dataSend = "P" + DATA::mac + DATA::Ip + DATA::lat + DATA::lng;
              break;
        }
    case 10:{
            dataSend = "H" + DATA::mac + DATA::Ip + DATA::temp + DATA::hump;
              break;
        }
    case 11:{
            dataSend = "KP" + DATA::mac + DATA::Ip + DATA::temp + DATA::hump + DATA::lat + DATA::lng;
             break;
        }
    default: break;
    }

   switch(Con)
    {
    case 0:
    {
            qDebug() << "dataSend;  " << dataSend ;
                out << dataSend<< endl;
             ui->txtContent->insertPlainText("\n"+dataSend);
             break;
    }
    case 1:
        {
             QString url = "http://lab411s.esy.es/sg/rx.php?data=";
             url+=dataSend;
             QNetworkRequest request = QNetworkRequest(QUrl(url));
             http->get(request);
             ui->txtContent->insertPlainText("\n"+dataSend);
             break;
         }
    default: break;
  }
}

void ServerDialog::loiSocket(QAbstractSocket::SocketError loi)
{
    switch (loi) {
    case QAbstractSocket::HostNotFoundError:
        ui->txtContent->append("LOI! Khong the ket noi toi may chu, vui long kiem tra lai dia chi IP va cong truy cap");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        ui->txtContent->append("LOI! May chu tu choi truy cap, vui long kiem tra xem may chu da duoc khoi dong chua, dong thoi ca dia chi IP va cong truy cap");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        ui->txtContent->append("LOI! May chu da ngat ket noi");
        break;
    default:
        ui->txtContent->append("LOI! "+socket->errorString());
        break;
    }
    //ui->btnConnect->setEnabled(true);
}

void ServerDialog::ketNoi()
{
    ui->txtContent->append("Ket noi thanh cong");
}

void ServerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ServerDialog::on_btnCancel_clicked()
{
    close();
}
