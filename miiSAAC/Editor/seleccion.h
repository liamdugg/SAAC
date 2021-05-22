#ifndef SELECCION_H
#define SELECCION_H

#include <QDialog>
#include <QToolButton>
#include <QObject>
#include <iostream>

using namespace std;

namespace Ui {
class Seleccion;
}

class Seleccion : public QDialog
{
    Q_OBJECT

public:
    explicit Seleccion(QWidget *parent = 0);
    ~Seleccion();

    QToolButton *boton;

    unsigned int fila;
    unsigned int columna;
    unsigned int colSel;
    unsigned int filSel;
    bool booleanoF;
    bool booleanoC;
    QString *imagen;

    void SetCantidad(unsigned int,unsigned int);

protected:
    void mouseMoveEvent(QMouseEvent *);

private:
    Ui::Seleccion *ui;

public slots:
    void BotonClick(void);
};

#endif // SELECCION_H
