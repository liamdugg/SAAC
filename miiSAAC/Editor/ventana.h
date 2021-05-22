#ifndef VENTANA_H
#define VENTANA_H

#include <QDialog>

namespace Ui {
class Nuevo;
}

class Nuevo : public QDialog
{
    Q_OBJECT

public:
    explicit Nuevo(QWidget *parent = 0);

    ~Nuevo();
    unsigned int GetFilas();
    unsigned int Getcolumnas();
    bool GetAceptar();

private slots:
    void on_BotonCancelar_clicked();

    void on_BotonAceptar_clicked();

private:
    Ui::Nuevo *ui;
    unsigned int filas;
    unsigned int columnas;
    bool aceptar;
};

#endif // VENTANA_H
