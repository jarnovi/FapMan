#include "cpuristin.h"
#include "QString"
#include "QFile"
#include "QTextStream"
#include <QPoint>

cPuristin::cPuristin(){
        this->Name=9;
        this->HeadType=1;
        this->PlateOrientation=1;
        this->FillPosition=0;
        this->PlatePosition=QPoint(4603.4,2783.9);
        this->PlateSize[0] = 150;
        this->PlateSize[1] = 200;
        this->PlateAngle=279.479858;
        this->HeadPosition=QPoint(4579.1,2929.8);
        this->HeadOffset=277.998108;
        this->PlateOffset=0.000000;
        this->HeadAngle=80.520142;
        this->HandPlated=0.000000;
        this->Camber=0.000000;
        this->ChordDistance=0;
        this->ChordAngle=90.000061;
   }

cPuristin::cPuristin(int Name,int HeadType,int PlateOrientation,int FillPosition,
          QPoint PlatePosition,int PlateSize[],double PlateAngle,QPoint HeadPosition,
          double HeadOffset,double HeadAngle,double HandPlated,double Camber,
          double ChordDistance,double ChordAngle)
{
    this->Name=Name;
    this->HeadType=HeadType;
    this->PlateOrientation=PlateOrientation;
    this->FillPosition=FillPosition;
    this->PlatePosition=PlatePosition;
    this->PlateSize[0]=PlateSize[0];
    this->PlateSize[1]=PlateSize[1];
    this->PlateAngle=PlateAngle;
    this->HeadPosition=HeadPosition;
    this->HeadOffset=HeadOffset;
    this->HeadAngle=HeadAngle;
    this->HandPlated=HandPlated;
    this->Camber=Camber;
    this->ChordDistance=ChordDistance;
    this->ChordAngle=ChordAngle;
};


QPoint cPuristin::getCoord() {
    return this->HeadPosition;
};

double cPuristin::getAngle(){
    return this->HeadAngle;
}


void cPuristin::rotate( QPoint control,double angle){
    this->HeadAngle-=angle;

    float dx =this->HeadPosition.rx()-control.rx();
    float dy =this->HeadPosition.ry()-control.ry();

    this->HeadPosition.setX(this->HeadPosition.rx() - dx);
    this->HeadPosition.setY(this->HeadPosition.ry() - dy);

    this->HeadPosition.setX(cos(angle)*dx-sin(angle)*dy);
    this->HeadPosition.setY(sin(angle)*dx+cos(angle)*dy);

    this->HeadPosition.setX(this->HeadPosition.rx() + dx);
    this->HeadPosition.setY(this->HeadPosition.ry() + dy);
}
void cPuristin::kirjoita(){

    QString filename="Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << QString("%1=%2").arg("Name",Name) << endl;
        stream << QString("%1=%2").arg("PlateOrientation",PlateOrientation) << endl;
        stream << QString("%1=%2").arg("FillPosition", FillPosition ) << endl;
        stream << QString("%1=%2,%3").arg("PlatePosition",PlatePosition.rx(),PlatePosition.ry()) << endl;
        stream << QString("%1=%2,%3").arg("PlateSize",PlateSize[0],PlateSize[1]) << endl;
        stream << QString("%1=%2").arg("PlateAngle",PlateAngle) << endl;
        stream << QString("%1=%2,%3").arg("HeadPosition",HeadPosition.rx(),HeadPosition.ry()) << endl;
        stream << QString("%1=%2").arg("HeadOffset",HeadOffset) << endl;
        stream << QString("%1=%2").arg("HeadAngle",HeadAngle) << endl;
        stream << QString("%1=%2").arg("HandPlated",HandPlated) << endl;
        stream << QString("%1=%2").arg("Camber",QString::number(Camber)) << endl;
        stream << QString("%1=%2").arg("ChordDistance",QString::number(ChordDistance)) << endl;
        stream << QString("%1=%2").arg("ChordAngle",QString::number(ChordAngle)) << endl;
     }


}



