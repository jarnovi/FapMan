#include "rotatedialog.h"
#include "ui_rotatedialog.h"
#include "mainwindow.h"
#include "QStringList"
#include "QString"
#include <QSettings>

rotateDialog::rotateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rotateDialog)
{
    ui->setupUi(this);
   // setCentralWidget(ui->horizontalLayout);
}

rotateDialog::

rotateDialog::~rotateDialog()
{
    delete ui;
}

void rotateDialog::on_buttonBox_accepted()
{
}
