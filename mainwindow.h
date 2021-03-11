#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QFile>
#include <QtGui>
#include <QGraphicsScene>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString settingsFile;
    QString outFile;
    QString inFile;
    QSettings globalSettings;
public slots:

private slots:
    void on_actionExit_triggered();

    void on_actionLoad_triggered();

    void on_actionAbout_triggered();

    void on_actionK_nn_triggered();

    void on_pushButton_clicked();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QVector< QVector< QPoint > > MemArray;


    double memlowx =7500;
    double memhighx=7500;
    double memlowy=7500;
    double memhighy=7500;
    double trussWidth=0;

    int    membercount=0;

    //QGraphicsView *view = new QGraphicsView();
    QGraphicsSimpleTextItem *pressNo;
    QGraphicsScene scene;
    QGraphicsTextItem *text;
    double kulmaarvo=0;


protected:
    void rotatePress(int origo,double angle);
    void updateWidth();
    void AddPress();
    void MemberAdded(QPolygon poly,int type);
    void process_line(QString line);
    void paintmember(QPolygon poly);
    void message(QString line);
    void addMembers();
    void addScene();
    void removeScene();
    QPoint rotateCoord(QPoint xy, double a);

};


#endif // MAINWINDOW_H
