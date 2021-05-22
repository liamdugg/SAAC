#include "SAACEditor.h"
#include <QGridLayout>

SAACEditor::SAACEditor(QWidget *parent) : QWidget(parent)
{
    plantilla = new QGridLayout();
    numCategorias = 0;
    cantBotones= 0;
    flagPresionado = false;
}

unsigned int SAACEditor::GetColumnas(unsigned int cat)
{
    return columnas[cat];
}

unsigned int SAACEditor::GetFilas(unsigned int cat)
{
    return filas[cat];
}

void SAACEditor::AgregarPlantilla(unsigned int f, unsigned int c, unsigned int cats)
{
    if(cantBotones == 0)
    {
        numCategorias = cats;
        catActual = 0;
        unsigned int auxBoton = 0;

        filas = new unsigned int[numCategorias+1];
        columnas = new unsigned int[numCategorias+1];
        boton = new SAACWidget[f*c*cats];
        cantBotones = f*c*cats;

        for(unsigned int n=0 ; n < cats ; n++)
        {
            filas[n] = f;
            columnas[n] = c;
        }
        for(unsigned int i=0 ; i < numCategorias ; i++)
        {
            for(unsigned int j=0 ; j < filas[0] ; j++)
            {
                for(unsigned int k=0 ; k < columnas[0] ; k++)
                {
                    if(i == 0)
                        plantilla->addWidget(&boton[auxBoton],j,k);
                    auxBoton++;
                }
            }
        }
    }
    setLayout(plantilla);
}

void SAACEditor::BorrarPlantilla()
{
    if(cantBotones > 0)
    {
        for(unsigned int i=0 ; i < (filas[catActual] * columnas[catActual]) ; i++)
            plantilla->removeWidget(&boton[i]);
        numCategorias = 0;
        cantBotones = 0;
        delete []boton;
        delete []filas;
        delete []columnas;
    }
}

void SAACEditor::CambiarCategoria(unsigned int cat)
{
    QGridLayout *auxPlantilla = new QGridLayout();
    unsigned int auxBoton = 0;

    for(unsigned int m=0 ; m < numCategorias ; m++)
    {
        if(m == catActual)
        {
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
            {
                plantilla->removeWidget(&boton[auxBoton]);
                boton[auxBoton].hide();
                auxBoton++;
            }
        }
        else
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
                auxBoton++;
    }

    delete plantilla;
    plantilla = new QGridLayout();
    auxBoton = 0;

    for(unsigned int i=0 ; i < numCategorias ; i++)
    {
        if(i == cat)
        {
            for(unsigned int j=0 ; j < filas[i] ; j++)
            {
                for(unsigned int k=0 ; k < columnas[i] ; k++)
                {
                    auxPlantilla->addWidget(&boton[auxBoton],j,k);
                    if(boton[auxBoton].isHidden())
                        boton[auxBoton].show();
                    auxBoton++;
                }
            }
        }
        else
        {
            for(unsigned int m=0; m < (filas[i])*(columnas[i]) ; m++)
            {
                auxBoton++;
            }
        }
    }

    catActual = cat;
    plantilla = auxPlantilla;
    setLayout(plantilla);
}

void SAACEditor::AgregarColumna(unsigned int numCol)
{
    QGridLayout *auxPlantilla = new QGridLayout();
    unsigned int auxBoton = 0;
    SAACWidget *auxWidget = new SAACWidget[cantBotones];

    for(unsigned int m=0 ; m < numCategorias ; m++)
    {
        if(m == catActual)
        {
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
            {
                plantilla->removeWidget(&boton[auxBoton]);
                boton[auxBoton].hide();
                auxBoton++;
            }
        }
        else
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
                auxBoton++;
    }

    delete plantilla;
    plantilla = new QGridLayout();
    auxBoton = 0;

    for(unsigned int i=0 ; i<numCategorias ; i++)
    {
        for(unsigned int j=0 ; j<filas[i] ; j++)
        {
            for(unsigned int k=0 ; k<columnas[i] ; k++)
            {
                auxWidget[auxBoton].label = boton[auxBoton].label;
                auxWidget[auxBoton].image = boton[auxBoton].image;
                auxWidget[auxBoton].audio = boton[auxBoton].audio;
                auxWidget[auxBoton].audioEnable = boton[auxBoton].audioEnable;
                auxWidget[auxBoton].frameString = boton[auxBoton].frameString;
                auxWidget[auxBoton].font = boton[auxBoton].font;
                auxWidget[auxBoton].fontColour = boton[auxBoton].fontColour;
                auxWidget[auxBoton].anchoMarco = boton[auxBoton].anchoMarco;
                auxWidget[auxBoton].tamanioLetra = boton[auxBoton].tamanioLetra;
                auxWidget[auxBoton].mayuscula = boton[auxBoton].mayuscula;
                auxWidget[auxBoton].italica = boton[auxBoton].italica;
                auxWidget[auxBoton].negrita = boton[auxBoton].negrita;
                auxWidget[auxBoton].subrayado = boton[auxBoton].subrayado;
                auxBoton++;
            }
        }
    }
    auxBoton = 0;
    delete []boton;
    boton = new SAACWidget[cantBotones+filas[catActual]];
    columnas[catActual]++;
    cantBotones += filas[catActual];

    for(unsigned int i=0 ; i < cantBotones ; i++)
    {
        if(i % columnas[catActual] != numCol)
        {
            boton[i].setIcon(auxWidget[auxBoton].image);
            boton[i].setAudio(auxWidget[auxBoton].audio);
            boton[i].audioEnable = auxWidget[auxBoton].audioEnable;
            boton[i].setLabel(auxWidget[auxBoton].label);
            boton[i].setFrame(auxWidget[auxBoton].frameString);
            boton[i].setFont(auxWidget[auxBoton].font);
            boton[i].setFontColor(auxWidget[auxBoton].fontColour);
            boton[i].anchoMarco = auxWidget[auxBoton].anchoMarco;
            boton[i].tamanioLetra = auxWidget[auxBoton].tamanioLetra;
            boton[i].mayuscula = auxWidget[auxBoton].mayuscula;
            boton[i].italica = auxWidget[auxBoton].italica;
            boton[i].negrita = auxWidget[auxBoton].negrita;
            boton[i].subrayado = auxWidget[auxBoton].subrayado;
            auxBoton++;
        }
    }

    auxBoton = 0;
    for(unsigned int i=0 ; i < numCategorias ; i++)
    {
        for(unsigned int j=0 ; j < filas[i] ; j++)
        {
            for(unsigned int k=0 ; k < columnas[i] ; k++)
            {
                auxPlantilla->addWidget(&boton[auxBoton],j,k);
                if(boton[auxBoton].isHidden())
                    boton[auxBoton].show();
                auxBoton++;
            }
        }
    }

    plantilla = auxPlantilla;
    setLayout(plantilla);
}

void SAACEditor::AgregarFila(unsigned int numFil)
{
    QGridLayout *auxPlantilla = new QGridLayout();
    unsigned int auxBoton = 0;
    SAACWidget *auxWidget = new SAACWidget[cantBotones];

    for(unsigned int m=0 ; m < numCategorias ; m++)
    {
        if(m == catActual)
        {
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
            {
                plantilla->removeWidget(&boton[auxBoton]);
                boton[auxBoton].hide();
                auxBoton++;
            }
        }
        else
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
                auxBoton++;
    }

    delete plantilla;
    plantilla = new QGridLayout();
    auxBoton = 0;

    for(unsigned int i=0 ; i<numCategorias ; i++)
    {
        for(unsigned int j=0 ; j<filas[i] ; j++)
        {
            for(unsigned int k=0 ; k<columnas[i] ; k++)
            {
                auxWidget[auxBoton].label = boton[auxBoton].label;
                auxWidget[auxBoton].image = boton[auxBoton].image;
                auxWidget[auxBoton].audio = boton[auxBoton].audio;
                auxWidget[auxBoton].audioEnable = boton[auxBoton].audioEnable;
                auxWidget[auxBoton].frameString = boton[auxBoton].frameString;
                auxWidget[auxBoton].font = boton[auxBoton].font;
                auxWidget[auxBoton].fontColour = boton[auxBoton].fontColour;
                auxWidget[auxBoton].anchoMarco = boton[auxBoton].anchoMarco;
                auxWidget[auxBoton].tamanioLetra = boton[auxBoton].tamanioLetra;
                auxWidget[auxBoton].mayuscula = boton[auxBoton].mayuscula;
                auxWidget[auxBoton].italica = boton[auxBoton].italica;
                auxWidget[auxBoton].negrita = boton[auxBoton].negrita;
                auxWidget[auxBoton].subrayado = boton[auxBoton].subrayado;
                auxBoton++;
            }
        }
    }

    auxBoton = 0;
    delete []boton;
    boton = new SAACWidget[cantBotones+columnas[catActual]];
    filas[catActual]++;
    cantBotones += columnas[catActual];

    for(unsigned int i=0 ; i < cantBotones ; i++)
    {
        if(!(i >= (numFil)*(columnas[catActual]) && i < ((numFil+1)*(columnas[catActual]))))
        {
            boton[i].setIcon(auxWidget[auxBoton].image);
            boton[i].setAudio(auxWidget[auxBoton].audio);
            boton[i].audioEnable = auxWidget[auxBoton].audioEnable;
            boton[i].setLabel(auxWidget[auxBoton].label);
            boton[i].setFrame(auxWidget[auxBoton].frameString);
            boton[i].setFont(auxWidget[auxBoton].font);
            boton[i].setFontColor(auxWidget[auxBoton].fontColour);
            boton[i].anchoMarco = auxWidget[auxBoton].anchoMarco;
            boton[i].tamanioLetra = auxWidget[auxBoton].tamanioLetra;
            boton[i].mayuscula = auxWidget[auxBoton].mayuscula;
            boton[i].italica = auxWidget[auxBoton].italica;
            boton[i].negrita = auxWidget[auxBoton].negrita;
            boton[i].subrayado = auxWidget[auxBoton].subrayado;
            auxBoton++;
        }
    }

    auxBoton = 0;
    for(unsigned int i=0 ; i < numCategorias ; i++)
    {
        for(unsigned int j=0 ; j < filas[i] ; j++)
        {
            for(unsigned int k=0 ; k < columnas[i] ; k++)
            {
                auxPlantilla->addWidget(&boton[auxBoton],j,k);
                if(boton[auxBoton].isHidden())
                    boton[auxBoton].show();
                auxBoton++;
            }
        }
    }
    plantilla = auxPlantilla;
    setLayout(plantilla);
}

void SAACEditor::SeleccionarColumna(unsigned int col)
{
    columnaActual = col;
}

void SAACEditor::SeleccionarFila(unsigned int fil)
{
    filaActual = fil;
}

void SAACEditor::EliminarFila(unsigned int fila)
{

    QGridLayout *auxPlantilla = new QGridLayout();
    unsigned int auxBoton = 0;
    unsigned int auxBot2 = 0 ;
    SAACWidget *auxWidget = new SAACWidget[cantBotones - columnas[catActual]];

    for(unsigned int m=0 ; m < numCategorias ; m++)
    {
        if(m == catActual)
        {
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
            {
                plantilla->removeWidget(&boton[auxBoton]);
                boton[auxBoton].hide();
                auxBoton++;
            }
        }
        else
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
                auxBoton++;
    }

    delete plantilla;
    plantilla = new QGridLayout();
    auxBoton = 0;

    for(unsigned int i=0 ; i<numCategorias ; i++)
    {
        for(unsigned int j=0 ; j<(filas[i]) ; j++)
        {
            for(unsigned int k=0 ; k<columnas[i] ; k++)
            {
                if(j != fila)
                {
                    auxWidget[auxBoton].label = boton[auxBot2].label;
                    auxWidget[auxBoton].image = boton[auxBot2].image;
                    auxWidget[auxBoton].audio = boton[auxBot2].audio;
                    auxWidget[auxBoton].audioEnable = boton[auxBot2].audioEnable;
                    auxWidget[auxBoton].frameString = boton[auxBot2].frameString;
                    auxWidget[auxBoton].font = boton[auxBot2].font;
                    auxWidget[auxBoton].fontColour = boton[auxBot2].fontColour;
                    auxWidget[auxBoton].anchoMarco = boton[auxBot2].anchoMarco;
                    auxWidget[auxBoton].tamanioLetra = boton[auxBot2].tamanioLetra;
                    auxWidget[auxBoton].mayuscula = boton[auxBot2].mayuscula;
                    auxWidget[auxBoton].italica = boton[auxBot2].italica;
                    auxWidget[auxBoton].negrita = boton[auxBot2].negrita;
                    auxWidget[auxBoton].subrayado = boton[auxBot2].subrayado;
                    auxBoton++;
                }
                auxBot2++;
            }
        }
    }

    auxBoton = 0;
    auxBot2 = 0;
    delete []boton;
    boton = new SAACWidget[cantBotones-columnas[catActual]];
    filas[catActual]--;
    cantBotones -= columnas[catActual];

    for(unsigned int i=0 ; i < cantBotones ; i++)
    {
        boton[i].setIcon(auxWidget[auxBoton].image);
        boton[i].setAudio(auxWidget[auxBoton].audio);
        boton[i].audioEnable = auxWidget[auxBoton].audioEnable;
        boton[i].setLabel(auxWidget[auxBoton].label);
        boton[i].setFrame(auxWidget[auxBoton].frameString);
        boton[i].setFont(auxWidget[auxBoton].font);
        boton[i].setFontColor(auxWidget[auxBoton].fontColour);
        boton[i].anchoMarco = auxWidget[auxBoton].anchoMarco;
        boton[i].tamanioLetra = auxWidget[auxBoton].tamanioLetra;
        boton[i].mayuscula = auxWidget[auxBoton].mayuscula;
        boton[i].italica = auxWidget[auxBoton].italica;
        boton[i].negrita = auxWidget[auxBoton].negrita;
        boton[i].subrayado = auxWidget[auxBoton].subrayado;
        auxBoton++;
    }

    auxBoton = 0;
    for(unsigned int i=0 ; i < numCategorias ; i++)
    {
        for(unsigned int j=0 ; j < filas[i] ; j++)
        {
            for(unsigned int k=0 ; k < columnas[i] ; k++)
            {
                auxPlantilla->addWidget(&boton[auxBoton],j,k);
                if(boton[auxBoton].isHidden())
                    boton[auxBoton].show();
                auxBoton++;
            }
        }
    }
    plantilla = auxPlantilla;
    setLayout(plantilla);
}

void SAACEditor::EliminarColumna(unsigned int columna)
{

    QGridLayout *auxPlantilla = new QGridLayout();
    unsigned int auxBoton = 0;
    unsigned int auxBot2 = 0;
    SAACWidget *auxWidget = new SAACWidget[cantBotones-(filas[catActual])];

    for(unsigned int m=0 ; m < numCategorias ; m++)
    {
        if(m == catActual)
        {
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
            {
                plantilla->removeWidget(&boton[auxBoton]);
                boton[auxBoton].hide();
                auxBoton++;
            }
        }
        else
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
                auxBoton++;
    }

    delete plantilla;
    plantilla = new QGridLayout();
    auxBoton = 0;

    for(unsigned int i=0 ; i<numCategorias ; i++)
    {
        for(unsigned int j=0 ; j<filas[i] ; j++)
        {
            for(unsigned int k=0 ; k<columnas[i] ; k++)
            {
                if(k != columna)
                {
                    auxWidget[auxBoton].label = boton[auxBot2].label;
                    auxWidget[auxBoton].image = boton[auxBot2].image;
                    auxWidget[auxBoton].audio = boton[auxBot2].audio;
                    auxWidget[auxBoton].audioEnable = boton[auxBot2].audioEnable;
                    auxWidget[auxBoton].frameString = boton[auxBot2].frameString;
                    auxWidget[auxBoton].font = boton[auxBot2].font;
                    auxWidget[auxBoton].fontColour = boton[auxBot2].fontColour;
                    auxWidget[auxBoton].anchoMarco = boton[auxBot2].anchoMarco;
                    auxWidget[auxBoton].tamanioLetra = boton[auxBot2].tamanioLetra;
                    auxWidget[auxBoton].mayuscula = boton[auxBot2].mayuscula;
                    auxWidget[auxBoton].italica = boton[auxBot2].italica;
                    auxWidget[auxBoton].negrita = boton[auxBot2].negrita;
                    auxWidget[auxBoton].subrayado = boton[auxBot2].subrayado;

                    auxBoton++;
                }
                auxBot2++;
            }
        }
    }

    auxBoton = 0;
    auxBot2 = 0;
    delete []boton;
    boton = new SAACWidget[cantBotones-filas[catActual]];
    columnas[catActual]--;
    cantBotones -= filas[catActual];

    for(unsigned int i=0 ; i < cantBotones ; i++)
    {
        boton[i].setIcon(auxWidget[auxBoton].image);
        boton[i].setAudio(auxWidget[auxBoton].audio);
        boton[i].audioEnable = auxWidget[auxBoton].audioEnable;
        boton[i].setLabel(auxWidget[auxBoton].label);
        boton[i].setFrame(auxWidget[auxBoton].frameString);
        boton[i].setFont(auxWidget[auxBoton].font);
        boton[i].setFontColor(auxWidget[auxBoton].fontColour);
        boton[i].anchoMarco = auxWidget[auxBoton].anchoMarco;
        boton[i].tamanioLetra = auxWidget[auxBoton].tamanioLetra;
        boton[i].mayuscula = auxWidget[auxBoton].mayuscula;
        boton[i].italica = auxWidget[auxBoton].italica;
        boton[i].negrita = auxWidget[auxBoton].negrita;
        boton[i].subrayado = auxWidget[auxBoton].subrayado;
        auxBoton++;
    }

    auxBoton = 0;
    for(unsigned int i=0 ; i < numCategorias ; i++)
    {
        for(unsigned int j=0 ; j < filas[i] ; j++)
        {
            for(unsigned int k=0 ; k < columnas[i] ; k++)
            {
                auxPlantilla->addWidget(&boton[auxBoton],j,k);
                if(boton[auxBoton].isHidden())
                    boton[auxBoton].show();
                auxBoton++;
            }
        }
    }
    plantilla = auxPlantilla;
    setLayout(plantilla);
}

void SAACEditor::ConfigurarFila(unsigned int fila)
{
    Cambio evento;
    unsigned int auxBoton = 0;
    evento.exec();

    for(unsigned int i=0 ; i<numCategorias ; i++)
    {
        if(i==catActual)
        {
            for(unsigned int j=0 ; j<(filas[i]) ; j++)
            {
                for(unsigned int k=0 ; k<columnas[i] ; k++)
                {
                    if(j == fila)
                    {
                        boton[auxBoton].anchoMarco = evento.anchoMarco;
                        boton[auxBoton].tamanioLetra = evento.tamanioLetra;

                        if(evento.okUpper)
                        {
                            evento.label = evento.label.toUpper();
                            boton[auxBoton].mayuscula = true;
                        }
                        else
                        {
                            evento.label = evento.label.toLower();
                            evento.label[0] = evento.label[0].toUpper();
                            boton[auxBoton].mayuscula = false;
                        }

                        if(evento.negrita)
                        {
                            boton[auxBoton].font.setWeight(QFont::Bold);
                            boton[auxBoton].negrita = true;
                        }
                        else
                        {
                            boton[auxBoton].font.setWeight(0);
                            boton[auxBoton].negrita = false;
                        }

                        if(evento.subrayado)
                        {
                            boton[auxBoton].font.setUnderline(true);
                            boton[auxBoton].subrayado = true;
                        }
                        else
                        {
                            boton[auxBoton].font.setUnderline(false);
                            boton[auxBoton].subrayado = false;
                        }

                        if(evento.italica)
                        {
                            boton[auxBoton].font.setStyle(QFont::StyleOblique);
                            boton[auxBoton].italica = true;
                        }
                        else
                        {
                            boton[auxBoton].font.setStyle(QFont::StyleNormal);
                            boton[auxBoton].italica = false;
                        }
                        boton[auxBoton].setLabel(evento.label);
                        boton[auxBoton].setIcon(evento.image);
                        boton[auxBoton].setFont(evento.font);
                        boton[auxBoton].setFontColor(evento.fontColor);
                        boton[auxBoton].setFrame(evento.frame);
                    }
                    auxBoton++;
                }
            }
        }
    }
}

void SAACEditor::ConfigurarColumna(unsigned int columna)
{
    Cambio evento;
    unsigned int auxBoton = 0;
    evento.exec();

    for(unsigned int i=0 ; i<numCategorias ; i++)
    {
        if(i==catActual)
        {
            for(unsigned int j=0 ; j<(filas[i]) ; j++)
            {
                for(unsigned int k=0 ; k<columnas[i] ; k++)
                {
                    if(k == columna)
                    {
                        boton[auxBoton].anchoMarco = evento.anchoMarco;
                        boton[auxBoton].tamanioLetra = evento.tamanioLetra;

                        if(evento.okUpper)
                        {
                            evento.label = evento.label.toUpper();
                            boton[auxBoton].mayuscula = true;
                        }
                        else
                        {
                            evento.label = evento.label.toLower();
                            evento.label[0] = evento.label[0].toUpper();
                            boton[auxBoton].mayuscula = false;
                        }

                        if(evento.negrita)
                        {
                            boton[auxBoton].font.setWeight(QFont::Bold);
                            boton[auxBoton].negrita = true;
                        }
                        else
                        {
                            boton[auxBoton].font.setWeight(0);
                            boton[auxBoton].negrita = false;
                        }

                        if(evento.subrayado)
                        {
                            boton[auxBoton].font.setUnderline(true);
                            boton[auxBoton].subrayado = true;
                        }
                        else
                        {
                            boton[auxBoton].font.setUnderline(false);
                            boton[auxBoton].subrayado = false;
                        }

                        if(evento.italica)
                        {
                            boton[auxBoton].font.setStyle(QFont::StyleOblique);
                            boton[auxBoton].italica = true;
                        }
                        else
                        {
                            boton[auxBoton].font.setStyle(QFont::StyleNormal);
                            boton[auxBoton].italica = false;
                        }
                        boton[auxBoton].setLabel(evento.label);
                        boton[auxBoton].setIcon(evento.image);
                        boton[auxBoton].setFont(evento.font);
                        boton[auxBoton].setFontColor(evento.fontColor);
                        boton[auxBoton].setFrame(evento.frame);
                    }
                    auxBoton++;
                }
            }
        }
    }
}

void SAACEditor::FuenteGlobal(QFont font)
{
    for(unsigned int i=0 ; i<cantBotones ; i++)
    {
        boton[i].font = font;
        boton[i].setFont(font);
    }
}

void SAACEditor::mouseMoveEvent(QMouseEvent *)
{
    if(!flagPresionado)
    {
        colDragged = ( (mapFromGlobal((cursor().pos())).x())) / ((this->width())/columnas[catActual]);
        filDragged = ( (mapFromGlobal((cursor().pos())).y())) / ((this->height())/filas[catActual]);
        flagPresionado = true;
    }
}

void SAACEditor::mouseReleaseEvent(QMouseEvent *)
{
    flagPresionado = false;
    unsigned int auxCol = ( (mapFromGlobal((cursor().pos())).x())) / ((this->width())/columnas[catActual]);
    unsigned int auxFil = ( (mapFromGlobal((cursor().pos())).y())) / ((this->height())/filas[catActual]);
    unsigned int auxDrag = 0;
    unsigned int auxDrop = 0;

    QGridLayout *auxPlantilla = new QGridLayout();
    unsigned int auxBoton = 0;
    SAACWidget *auxWidget = new SAACWidget[cantBotones];

    for(unsigned int m=0 ; m < numCategorias ; m++)
    {
        if(m == catActual)
        {
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
            {
                plantilla->removeWidget(&boton[auxBoton]);
                boton[auxBoton].hide();
                auxBoton++;
            }
        }
        else
            for(unsigned int i=0 ; i < (filas[m]) * (columnas[m]) ; i++)
                auxBoton++;
    }

    delete plantilla;
    plantilla = new QGridLayout();
    auxBoton = 0;

    for(unsigned int i=0 ; i<numCategorias ; i++)
    {
        for(unsigned int j=0 ; j<filas[i] ; j++)
        {
            for(unsigned int k=0 ; k<columnas[i] ; k++)
            {
                auxWidget[auxBoton].label = boton[auxBoton].label;
                auxWidget[auxBoton].image = boton[auxBoton].image;
                auxWidget[auxBoton].audio = boton[auxBoton].audio;
                auxWidget[auxBoton].audioEnable = boton[auxBoton].audioEnable;
                auxWidget[auxBoton].frameString = boton[auxBoton].frameString;
                auxWidget[auxBoton].font = boton[auxBoton].font;
                auxWidget[auxBoton].fontColour = boton[auxBoton].fontColour;
                auxWidget[auxBoton].anchoMarco = boton[auxBoton].anchoMarco;
                auxWidget[auxBoton].tamanioLetra = boton[auxBoton].tamanioLetra;
                auxWidget[auxBoton].mayuscula = boton[auxBoton].mayuscula;
                auxWidget[auxBoton].italica = boton[auxBoton].italica;
                auxWidget[auxBoton].negrita = boton[auxBoton].negrita;
                auxWidget[auxBoton].subrayado = boton[auxBoton].subrayado;
                auxBoton++;
            }
        }
    }
    auxBoton = 0;
    delete []boton;
    boton = new SAACWidget[cantBotones];

    for(unsigned int i=0 ; i<filas[catActual] ; i++)
    {
        for(unsigned int j=0 ; j<columnas[catActual] ; j++)
        {
            if(j == auxCol && i == auxFil)
                auxDrop = auxBoton;
            else if(i == filDragged && j == colDragged)
                auxDrag = auxBoton;
            auxBoton++;
        }
    }
    auxBoton=0;

    for(unsigned int i=0; i<cantBotones ; i++)
    {
        if(i == auxDrop)
        {
            boton[i].setIcon(auxWidget[auxDrag].image);
            boton[i].setAudio(auxWidget[auxDrag].audio);
            boton[i].audioEnable = auxWidget[auxDrag].audioEnable;
            boton[i].setLabel(auxWidget[auxDrag].label);
            boton[i].setFrame(auxWidget[auxDrag].frameString);
            boton[i].setFont(auxWidget[auxDrag].font);
            boton[i].setFontColor(auxWidget[auxDrag].fontColour);
            boton[i].anchoMarco = auxWidget[auxDrag].anchoMarco;
            boton[i].tamanioLetra = auxWidget[auxDrag].tamanioLetra;
            boton[i].negrita = auxWidget[auxDrag].negrita;
            boton[i].italica = auxWidget[auxDrag].italica;
            boton[i].subrayado = auxWidget[auxDrag].subrayado;
            boton[i].mayuscula = auxWidget[auxDrag].mayuscula;
        }
        else if(i == auxDrag)
        {
            boton[i].setIcon(auxWidget[auxDrop].image);
            boton[i].setAudio(auxWidget[auxDrop].audio);
            boton[i].audioEnable = auxWidget[auxDrop].audioEnable;
            boton[i].setLabel(auxWidget[auxDrop].label);
            boton[i].setFrame(auxWidget[auxDrop].frameString);
            boton[i].setFont(auxWidget[auxDrop].font);
            boton[i].setFontColor(auxWidget[auxDrop].fontColour);
            boton[i].anchoMarco = auxWidget[auxDrop].anchoMarco;
            boton[i].tamanioLetra = auxWidget[auxDrop].tamanioLetra;
            boton[i].negrita = auxWidget[auxDrop].negrita;
            boton[i].italica = auxWidget[auxDrop].italica;
            boton[i].subrayado = auxWidget[auxDrop].subrayado;
            boton[i].mayuscula = auxWidget[auxDrop].mayuscula;
        }
        else
        {
            boton[i].setIcon(auxWidget[i].image);
            boton[i].setAudio(auxWidget[i].audio);
            boton[i].audioEnable = auxWidget[i].audioEnable;
            boton[i].setLabel(auxWidget[i].label);
            boton[i].setFrame(auxWidget[i].frameString);
            boton[i].setFont(auxWidget[i].font);
            boton[i].setFontColor(auxWidget[i].fontColour);
            boton[i].anchoMarco = auxWidget[i].anchoMarco;
            boton[i].tamanioLetra = auxWidget[i].tamanioLetra;
            boton[i].negrita = auxWidget[i].negrita;
            boton[i].italica = auxWidget[i].italica;
            boton[i].subrayado = auxWidget[i].subrayado;
            boton[i].mayuscula = auxWidget[i].mayuscula;
        }
    }

    for(unsigned int i=0 ; i < numCategorias ; i++)
    {
        for(unsigned int j=0 ; j < filas[i] ; j++)
        {
            for(unsigned int k=0 ; k < columnas[i] ; k++)
            {
                auxPlantilla->addWidget(&boton[auxBoton],j,k);
                if(boton[auxBoton].isHidden())
                    boton[auxBoton].show();
                auxBoton++;
            }
        }
    }
    plantilla = auxPlantilla;
    setLayout(plantilla);
}
