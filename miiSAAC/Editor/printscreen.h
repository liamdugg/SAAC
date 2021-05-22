#ifndef PRINTSCREN_H
#define PRINTSCREN_H

#include <QDialog>

namespace Ui {
class PrintScren;
}

class PrintScreen : public QDialog
{
    Q_OBJECT

public:
    explicit PrintScreen(QWidget *parent = nullptr);
    ~PrintScreen();
    QString fileName, filePath;
    int orientationIdx;
    bool printReady;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_Explorar_clicked();

private:
    Ui::PrintScren *ui;
};

#endif // PRINTSCREN_H
