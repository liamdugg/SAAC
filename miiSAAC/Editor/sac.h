#ifndef SAC_H
#define SAC_H

#include <QMainWindow>
#include <QLabel>
#include <QToolBar>
#include <string.h>
#include <stdio.h>
#include <QFile>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "ventana.h"
#include "seleccion.h"
#ifdef Q_OS_WINDOWS
#include "..\SAACEditor.h"
#include "..\SAACWidget.h"
#else
#include "../SAACEditor.h"
#include "../SAACWidget.h"
#endif
#include <QMessageBox>

namespace Ui {
class SAC;
}

class SAC : public QMainWindow
{
    Q_OBJECT

public:
    explicit SAC(QWidget *parent = 0);

    unsigned int filas;
    unsigned int columnas;
    int filaSel;
    int columnaSel;
    int flag;
    QString curFile;
    bool saveFile();
    bool maybeSave();
    bool wasModified();

    ~SAC();

private:
    Ui::SAC *ui;

    QLabel barraEstado;

public slots:
    void NuevoArchivo(void);
    void NuevaColumna(void);
    void NuevaFila(void);
    void InsertarColumna(void);
    void InsertarFila(void);
    void SelColumna(void);
    void SelFila(void);
    void Cerrar(void);
    void ImprimirPantalla(void);
    void Salir(void);

 //  void Eliminar(void);
private slots:
    bool on_actionGuardar_triggered();
    bool on_actionGuardar_como_triggered();
    void on_actionAbrir_triggered();
    void on_actionConfigurar_columna_triggered();
    void on_actionConfigurar_fila_triggered();
};

#endif // SAC_H
