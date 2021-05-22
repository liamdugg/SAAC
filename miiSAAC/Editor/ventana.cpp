#include "ventana.h"
#include "ui_ventana.h"

Nuevo::Nuevo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nuevo)
{
    ui->setupUi(this);
}

Nuevo::~Nuevo()
{
    delete ui;
}

void Nuevo::on_BotonCancelar_clicked()
{
    this->close();
    this->aceptar = false;
}

void Nuevo::on_BotonAceptar_clicked()
{
    this->close();
    this->aceptar = true;
    this->filas = ui->spinBoxFilas->value();
    this->columnas = ui->spinBoxColumnas->value();
}

unsigned int Nuevo::Getcolumnas()
{
    return columnas;
}

unsigned int Nuevo::GetFilas()
{
    return filas;
}

bool Nuevo::GetAceptar()
{
    return aceptar;
}
