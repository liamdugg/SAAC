#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QMediaPlayer>
#include <QUrl>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString auxColor;
    QString auxfColor;
    QString auxbgColor;
    QString frameColor;
    bool okUpper;
private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void btnClicked();

    void on_colorFondo_clicked();

    void on_colorLetra_clicked();

    void on_colorMarco_clicked();

    //void on_lineEdit_7_textEdited(const QString &arg1);

    void on_checkMayuscula_stateChanged(int arg1);

    //void on_plainTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
