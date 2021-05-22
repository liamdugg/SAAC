#include "seleccion.h"
#include "ui_seleccion.h"

Seleccion::Seleccion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Seleccion)
{
    ui->setupUi(this);
    fila = 0;
    columna = 0;
    booleanoC = false;
    booleanoF = false;
    setMouseTracking(true);
}

Seleccion::~Seleccion()
{
    delete ui;
}

void Seleccion::SetCantidad(unsigned int f,unsigned int c)
{
    fila = f;
    columna = c;
    unsigned int auxBoton = 0;
    boton = new QToolButton[f*c];
    imagen = new QString[f*c];

    for(unsigned int i=0 ; i<f ; i++)
    {
        for(unsigned int j=0 ; j<c ; j++)
        {
            ui->gridLayout->addWidget(&boton[auxBoton],i,j);
            boton[auxBoton].setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            boton[auxBoton].setMouseTracking(true);
            boton[auxBoton].setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            QObject::connect(&(boton[auxBoton]),SIGNAL(pressed()),this,SLOT(BotonClick()));
            auxBoton++;
        }
    }
    setLayout(ui->gridLayout);
}

void Seleccion::BotonClick()
{
    for(unsigned int i=0 ; i < (fila*columna) ; i++)
    {
        if(boton[i].isDown())
        {
            colSel = i%columna;
            filSel = i/columna;
        }
    }
    delete []boton;
    this->close();
}

void Seleccion::mouseMoveEvent(QMouseEvent *)
{
    unsigned int auxNum;
    unsigned int auxBoton = 0;

    if(booleanoC)
    {
        auxNum = ( (mapFromGlobal((cursor().pos())).x())) / (this->boton[0].width());
    }
    else
    {
        auxNum = ( (mapFromGlobal((cursor().pos())).y())) / (this->boton[0].height());
    }

    for(unsigned int i=0 ; i < fila ; i++)
    {
        for(unsigned int j=0 ; j < columna ; j++)
        {
            if((booleanoC && (auxNum == j)) || (booleanoF && (auxNum == i)))
                boton[auxBoton].setStyleSheet("border-width: 5px; border-style: solid; border-color: red; image:url("+this->imagen[auxBoton]+");");
            else
                boton[auxBoton].setStyleSheet("border-width: 5px; border-style: solid; border-color: black; image:url("+this->imagen[auxBoton]+");");

            auxBoton++;
        }
    }
}
