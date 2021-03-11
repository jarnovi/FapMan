#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <QGraphicsView>
#include <QTransform>
#include <QGraphicsTextItem>
#include <QFile>
#include "QtGui"
#include "QPair"
#include <QChar>
#include <math.h>
#include "QtCore"
#include <QPainter>
#include <QRegExp>
#include <QImage>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->membercount=0;

    ui->setupUi(this);
    settingsFile=QString(".\\tempsettings.conf");
    setCentralWidget(ui->mainContainer);
}


QPoint MainWindow::rotateCoord(QPoint xy, double a){
    double cosa=cos(-a*M_PI/180);
    double sina=sin(-a*M_PI/180);

    //return QPoint(int(cosa*xy.rx()-sina*xy.ry()),int(sina*xy.rx()+cosa*xy.ry()));
    return QPoint(cosa*xy.rx()-sina*xy.ry(),sina*xy.rx()+cosa*xy.ry());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();

}

void MainWindow::rotatePress(int origo, double angle){
    QTextStream cerr(stderr);

    QSettings settings(settingsFile,QSettings::IniFormat);
    //settings.setIniCodec("UTF-8LE");
    QString prefix = QString("Joint_%1/HeadPosition").arg(QString::number(origo));
    QStringList opuristin = settings.value(prefix).toStringList();
    int ox = opuristin[0].toInt();
    int  oy = opuristin[1].toInt();

    QString jc=settings.value("TRUSS/JointCount").toString();

    int jointcount=jc.toInt();
    int cnt;
    for (cnt=1;cnt<jointcount+1;cnt++){
       // cerr <<" loopissa: "<< cnt << "\n";

        QString HA=QString("Joint_%1/HeadAngle").arg(QString::number(cnt));
        QString HP=QString("Joint_%1/HeadPosition").arg(QString::number(cnt));
        QString PP=QString("Joint_%1/PlatePosition").arg(QString::number(cnt));
        QString HT=QString("Joint_%1/HeadType").arg(QString::number(cnt));

        double kulma = settings.value(HA).toDouble();

        //headtype 1 on yläpuristin, alapuristimia ei käännetä.

        bool ylapuristin=settings.value(HT).toInt();
        if (ylapuristin){ kulma+=angle; }

        QStringList puristin = settings.value(HP).toStringList();

        // vähennetään origo-puristimen koordinaatit.
        QPoint dst(puristin[0].toDouble()-ox,puristin[1].toDouble()-oy);
        QPoint news=rotateCoord(dst,angle);

        news.setX(news.rx()+ox);
        news.setY(news.ry()+oy);

        // ei sallita väistöä matalempia arvoja.
        if (news.ry()<(-250)){ news.setY(-250); }

        settings.setValue(HA,QString::number(kulma));
        QStringList neus;// = QString("%1,%2").arg(QString::number(news.rx()) ,QString::number(news.ry())  );
        neus << QString::number(news.rx()) << QString::number(news.ry());

        settings.setValue(HP,neus);


        // plate position
        QStringList levy= settings.value(PP).toStringList();
        QPoint ldst(levy[0].toInt()-ox,levy[1].toInt()-oy);
        QPoint lnews=rotateCoord(ldst,angle);

        lnews.setX(lnews.rx()+ox);
        lnews.setY(lnews.ry()+oy);
        QStringList lneus;
        lneus << QString::number(lnews.rx()) << QString::number(lnews.ry());
        settings.setValue(PP,lneus);

        QPolygon poly;
        poly << QPoint( news.rx(),news.ry())+this->rotateCoord(QPoint(-900, 300),kulma);
        poly << QPoint( news.rx(),news.ry())+this->rotateCoord(QPoint( 400, 300),kulma);
        poly << QPoint( news.rx(),news.ry())+this->rotateCoord(QPoint( 400,-300),kulma);
        poly << QPoint( news.rx(),news.ry())+this->rotateCoord(QPoint(-900,-300),kulma);

        if (ylapuristin==1){
            this->MemberAdded(poly,1);
        }
        else{
            this->MemberAdded(poly,2);
        }
    }

    settings.sync();
}

void MainWindow::updateWidth(){
    this->trussWidth=this->memhighx-this->memlowx;
}

void MainWindow::MemberAdded(QPolygon poly,int type){
    QBrush osa(QColor(200,170,140,200));
    QBrush yla(QColor(180,180,255,128));
    QBrush ala(QColor(180,255,180,128));

    QPen kyna(Qt::black);
    kyna.setWidth(12);

    switch (type){
    case 1:
        this->scene.addPolygon(poly,kyna,yla);
        break;
    case 2:
        this->scene.addPolygon(poly,kyna,ala);
        break;
    default:
         this->scene.addPolygon(poly,kyna,osa);
    }
}


void MainWindow::AddPress(){
    QSettings settings(settingsFile,QSettings::IniFormat);

    QString jc=settings.value("TRUSS/JointCount").toString();

    int jointcount=jc.toInt();
    int cnt;
    for (cnt=1;cnt<jointcount+1;cnt++){

        QString prefix = QString("Joint_%1/HeadAngle").arg(QString::number(cnt));
        double kulma = settings.value(prefix).toDouble();

        prefix=QString("Joint_%1/HeadPosition").arg(QString::number(cnt));

        QStringList puristin = settings.value(prefix).toStringList();

        QPolygon poly;
        poly << QPoint( puristin[0].toDouble(),puristin[1].toDouble())+this->rotateCoord(QPoint(-900, 300),kulma);
        poly << QPoint( puristin[0].toDouble(),puristin[1].toDouble())+this->rotateCoord(QPoint( 400, 300),kulma);
        poly << QPoint( puristin[0].toDouble(),puristin[1].toDouble())+this->rotateCoord(QPoint( 400,-300),kulma);
        poly << QPoint( puristin[0].toDouble(),puristin[1].toDouble())+this->rotateCoord(QPoint(-900,-300),kulma);

        this->MemberAdded(poly,1);

        QGraphicsTextItem * io = new QGraphicsTextItem;
        io->setPos( puristin[0].toDouble(),puristin[1].toDouble());
        io->setPlainText(QString::number(cnt));
        io->setFont(QFont("Arial",170));

        this->scene.addItem(io);
 }
}

void MainWindow::addScene(){
    //this->setCentralWidget(ui->view);
    ui->view->resetTransform();
    ui->verticalLayout->property("Width")=400;

    double xscale = (width()-10)/trussWidth;
    double yscale = (height()-10)/memhighy;
    double uniscale = xscale < yscale ? xscale:yscale;
    //ui->view->scale(uniscale,uniscale);
    ui->view->setRenderHints(QPainter::Antialiasing);


    QTransform t = QTransform();
    t.scale(uniscale,-uniscale);
    t.rotate(kulmaarvo,Qt::ZAxis);

    ui->view->setTransform(t);
    ui->view->setScene(&scene);

}

void MainWindow::removeScene(){

}

void MainWindow::addMembers(){
    QRegExp rx;
    QSettings settings(settingsFile,QSettings::IniFormat);
    int mc= settings.value("TRUSS/MemberCount").toInt();
    for (int i=1;i<mc+1;i++){
        QString qrline=QString("MEMBER/Member_%1").arg(QString::number(i));
        QStringList mbr=settings.value(qrline).toStringList();


        //  debug: osan monimutkaisuus
        //message(QString::number(mbr.length()));

    }
/*
    QString mbr=QString("Member_%1").arg(QString::number())

    rx.setPattern("^Member_\\d.*=\\d.*,.*");
        if (rx.exactMatch(line)){
        int limit = line.indexOf(",");
        if (limit > 0){

            line=line.remove(0,limit+1);

           QRegExp rx3(",");
           QStringList query = line.split(rx3);

          QPolygon poly;
          while (query.length()>1){
               poly << QPoint(
                       query[0].toDouble(),
                       query[1].toDouble()
               );
               double xcdr=query[0].toDouble();
               double ycdr=query[1].toDouble();
               this->memlowx =this->memlowx <xcdr? this->memlowx:xcdr;
               this->memhighx=this->memhighx<xcdr? xcdr:this->memhighx;

               this->memlowy =this->memlowy <ycdr? this->memlowy:ycdr;
               this->memhighy=this->memhighy<ycdr? ycdr:this->memhighy;

                query.removeFirst();
                query.removeFirst();
        }
        this->MemberAdded(poly,0);
        this->membercount++;
        this->updateWidth();

        }
    }*/

}



void MainWindow::on_actionLoad_triggered()
{
    inFile=QFileDialog::getOpenFileName(
                this,
                tr("Avaa fappi"),
                "D:\\code\\",
                "Fapit (*.fap);;Kaikki (*.*)"
                );
    if (QFile::exists(settingsFile))
    {
        QFile::remove(settingsFile);
    }
    QFile::copy(inFile, settingsFile);

    QSettings settings(settingsFile, QSettings::IniFormat);
    /*
    QFile file(settingsFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }
    this->scene.clear();
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        process_line(line);
    }
    file.close();
    */

    addMembers();
    QString infoline=QString("Projekti:%1 Osia:%2 Puristimia:%3 Pituus:%4mm").arg(
                   settings.value("TRUSS/TrussMark").toString(),
                   settings.value("TRUSS/MemberCount").toString(),
                   settings.value("TRUSS/JointCount").toString(),
                   QString::number(this->trussWidth));


       ui->statusBar->showMessage(infoline);

       MainWindow::AddPress();
       MainWindow::addScene();
}

void MainWindow::paintmember(QPolygon poly){
    QPainter painter(this);
    painter.drawPolygon(poly);
}

void MainWindow::message(QString line){
    QMessageBox msgBox;
    msgBox.setText(line);
    msgBox.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;

    QLabel * label_img = new QLabel (this);
    label_img->setWindowFlags(Qt::Window);
    label_img->setPixmap(QPixmap(":res/images/fabio.jpg", 0, Qt::AutoColor));
    label_img->show();

    msgBox.setText("Other programs play.\nFapMan Kills!");
    //msgBox.exec();
}



void MainWindow::on_actionK_nn_triggered()
{
   /*rotateDialog rotdiag;
    rotdiag.setModal(true);
    rotdiag.exec();
    */
}

void MainWindow::on_pushButton_clicked()
{
    QString origo=ui->lineEditOrig->text();
    QString angle=ui->lineEditAngle->text();

    angle = angle.replace(',', '.');
    this->rotatePress(origo.toInt(),ui->lineEditAngle->text().toDouble());
}

void MainWindow::on_actionSave_triggered()
{
    QRegExp pattern("/");
    int last= pattern.lastIndexIn(inFile,-1);
    outFile=inFile.insert(last+1,"FM_");

    if (QFile::exists(outFile))
    {
        QFile::remove(outFile);
    }


    QFile readfile(settingsFile);
    QFile writefile(outFile);

    if (!readfile.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::information(this, tr("Unable to open file"),
                readfile.errorString());
            return;
   }
    if (!writefile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"),
            writefile.errorString());
        return;
    }

    QTextStream out(&writefile);


    while (!readfile.atEnd()) {
           QByteArray line = readfile.readLine();

           QString abb = QString::fromLatin1(line);

           abb.remove(" ");
           abb.replace( "%20", " " );
           abb.replace( "%3A", ":" );
             if(line != "\n"){ out << abb;
           }
    }
    readfile.close();
    writefile.close();
    ui->statusBar->showMessage("Tiedosto tallennettu.");

 //   QFile::copy(settingsFile,outFile);
}
