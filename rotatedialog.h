#ifndef ROTATEDIALOG_H
#define ROTATEDIALOG_H

#include <QDialog>

namespace Ui {
class rotateDialog;
}

class rotateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rotateDialog(QWidget *parent = 0);
    ~rotateDialog();
signals:


private slots:


    void on_buttonBox_accepted();

private:
    Ui::rotateDialog *ui;
};

#endif // ROTATEDIALOG_H
