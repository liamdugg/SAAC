#ifndef SAACEDITOR_H
#define SAACEDITOR_H

#include <QWidget>
#include "SAACWidget.h"

class SAACEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SAACEditor(QWidget *parent = 0);

    unsigned int GetFilas(unsigned int cat);
    unsigned int GetColumnas(unsigned int cat);
    void AgregarPlantilla(unsigned int f, unsigned int c, unsigned int numCategorias);
    void BorrarPlantilla(void);
    void CambiarCategoria(unsigned int cat);
    void AgregarColumna(unsigned int numCol);
    void AgregarFila(unsigned int numFil);
    void SeleccionarColumna(unsigned int col);
    void SeleccionarFila(unsigned int fil);
    void EliminarFila(unsigned int fila);
    void EliminarColumna(unsigned int columna);
    void ConfigurarFila(unsigned int fila);
    void ConfigurarColumna(unsigned int columna);
    void FuenteGlobal(QFont);

    SAACWidget *boton;
    QGridLayout *plantilla;
    unsigned int cantBotones;

private:
    unsigned int *filas;
    unsigned int *columnas;
    unsigned int numCategorias;
    unsigned int catActual;
    unsigned int filaActual;
    unsigned int columnaActual;
    unsigned int colDragged;
    unsigned int filDragged;
    bool flagPresionado;

    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:
};

#endif // SAACEDITOR_H
