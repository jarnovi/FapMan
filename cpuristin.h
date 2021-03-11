#ifndef CPURISTIN_H
#define CPURISTIN_H
#include "QPoint"


class cPuristin
{
public:
    cPuristin();
    cPuristin(int Name,int HeadType,int PlateOrientation,
              int FillPosition,QPoint PlatePosition,
              int PlateSize[],double PlateAngle,
              QPoint HeadPosition,double HeadOffset,
              double HeadAngle,double HandPlated,double Camber,
              double ChordDistance,double ChordAngle
              );
    ~cPuristin();

private:
    int Name;
    int HeadType;
    int PlateOrientation;
    int FillPosition;
    QPoint PlatePosition;
    int PlateSize[2];
    double PlateAngle;
    QPoint HeadPosition;
    double HeadOffset;
    double PlateOffset;
    double HeadAngle;
    double HandPlated;
    double Camber;
    double ChordDistance;
    double ChordAngle;
protected:
    void rotate(QPoint position,double angle);
    QPoint getCoord();
    double getAngle();
    void kirjoita();
};

#endif // CPURISTIN_H
