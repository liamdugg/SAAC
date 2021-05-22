#ifndef CAMBIO_H
#define CAMBIO_H

#include <QDialog>
#include <QString>
#include <QColorDialog>
#include <QFileDialog>
#ifdef Q_OS_WINDOWS
#include "..\SAACWidget.h"
#else
#include "../SAACWidget.h"
#endif

namespace Ui {
class Cambio;
}

class Cambio : public QDialog
{
    Q_OBJECT

public:
    explicit Cambio(QWidget *parent = 0);
    void SetParametros(QString, QString, QString, QString, QFont);
    void SetCuadro(bool min, bool neg, bool it, bool sub, QString ancMar, QString tamLet);
    ~Cambio();

    QString image;
    QString label;
    QString frame;
    QString fontColor;
    QFont font;

    QString auxColor;
    QString auxfColor;
    QString auxbgColor;
    QString frameColor;

    QString anchoMarco;
    QString tamanioLetra;

    bool okUpper;
    bool negrita, italica, subrayado;

private slots:

    void btnClicked();

    void on_botAceptar_clicked();

    void on_botCancelar_clicked();

    void on_UpdateBoton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkMayuscula_stateChanged(int arg1);

    void on_colorFondo_clicked();

    void on_colorLetra_clicked();

    void on_colorMarco_clicked();

    void on_UpdateBoton_2_clicked();

private:
    Ui::Cambio *ui;
};

#endif // CAMBIO_H
