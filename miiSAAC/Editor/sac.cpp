#include "sac.h"
#include "ui_sac.h"
#include <QPainter>
#include <QPrinter>
#include "printscreen.h"

SAC::SAC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SAC)
{
    ui->setupUi(this);
    ui->actionCerrar->setEnabled(false);
    ui->actionAgregar_columna->setEnabled(false);
    ui->actionAgregar_fila->setEnabled(false);
    ui->actionGuardar->setEnabled(false);
    ui->actionGuardar_como->setEnabled(false);
    ui->actionImprimir_pantalla->setEnabled(false);
    ui->actionInsertar_columna->setEnabled(false);
    ui->actionInsertar_fila->setEnabled(false);
    ui->actionSeleccionar_columna->setEnabled(false);
    ui->actionSeleccionar_fila->setEnabled(false);
    ui->actionConfigurar_columna->setEnabled(false);
    ui->actionConfigurar_fila->setEnabled(false);

    connect(ui->actionSalir,SIGNAL(triggered(bool)),this,SLOT(Salir()));
    connect(ui->actionNuevo,SIGNAL(triggered(bool)),this,SLOT(NuevoArchivo()));
    connect(ui->actionAgregar_columna,SIGNAL(triggered(bool)),this,SLOT(NuevaColumna()));
    connect(ui->actionAgregar_fila,SIGNAL(triggered(bool)),this,SLOT(NuevaFila()));
    connect(ui->actionSeleccionar_columna,SIGNAL(triggered(bool)),this,SLOT(SelColumna()));
    connect(ui->actionSeleccionar_fila,SIGNAL(triggered(bool)),this,SLOT(SelFila()));
    connect(ui->actionCerrar,SIGNAL(triggered(bool)),this,SLOT(Cerrar()));
    connect(ui->actionInsertar_columna,SIGNAL(triggered(bool)),this,SLOT(InsertarColumna()));
    connect(ui->actionInsertar_fila,SIGNAL(triggered(bool)),this,SLOT(InsertarFila()));
    connect(ui->actionImprimir_pantalla,SIGNAL(triggered(bool)),this,SLOT(ImprimirPantalla()));

    columnas = 0;
    filas = 0;
    barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));
    ui->statusBar->addWidget(&barraEstado);

    ui->mainToolBar->setVisible(false);
    this->setWindowTitle("Sistema Aumentativo de Comunicación");
}

SAC::~SAC()
{
    delete ui;
}

void SAC::NuevoArchivo(void)
{
    Nuevo ventana;
    ventana.exec();

    if(ventana.GetAceptar())
    {
        ui->actionCerrar->setEnabled(true);
        ui->actionAgregar_columna->setEnabled(true);
        ui->actionAgregar_fila->setEnabled(true);
        ui->actionGuardar->setEnabled(true);
        ui->actionGuardar_como->setEnabled(true);
        ui->actionImprimir_pantalla->setEnabled(true);
        ui->actionSeleccionar_columna->setEnabled(true);
        ui->actionSeleccionar_fila->setEnabled(true);
        ui->actionConfigurar_fila->setEnabled(true);
        ui->actionConfigurar_columna->setEnabled(true);
        ui->actionAbrir->setEnabled(false);
        ui->actionNuevo->setEnabled(false);
        ui->widget->AgregarPlantilla(ventana.GetFilas(),ventana.Getcolumnas(),1);
        filas = ventana.GetFilas();
        columnas = ventana.Getcolumnas();
        filaSel = -1;
        columnaSel = -1;
        barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));

        ui->mainToolBar->setVisible(true);
    }
}

void SAC::NuevaColumna()
{
    ui->widget->AgregarColumna(columnas);
    columnas++;
    barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));
}

void SAC::NuevaFila()
{
    ui->widget->AgregarFila(filas);
    filas++;
    barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));
}

void SAC::InsertarColumna()
{
    Seleccion sel;
    sel.SetCantidad(ui->widget->GetFilas(0),ui->widget->GetColumnas(0) + 1);
    sel.exec();
    ui->widget->AgregarColumna(sel.colSel);
    columnas++;
    barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));
}

void SAC::InsertarFila()
{
    Seleccion sel;
    sel.SetCantidad(ui->widget->GetFilas(0) + 1,ui->widget->GetColumnas(0));
    sel.exec();
    ui->widget->AgregarFila(sel.filSel);
    filas++;
    barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));
}

void SAC::SelColumna()
{
    Seleccion sel;
    sel.SetCantidad(ui->widget->GetFilas(0),ui->widget->GetColumnas(0));
    sel.booleanoC = true;

    for (unsigned int i=0 ; i < ui->widget->cantBotones ; i++)
    {
        sel.boton[i].setStyleSheet("border-width: 5px; border-style:solid; border-color:black; image:url("+ui->widget->boton[i].image+");");
        sel.imagen[i] = ui->widget->boton[i].image;
    }

    sel.exec();
    columnaSel = sel.colSel;
    ui->widget->SeleccionarColumna(sel.colSel);
    ui->widget->EliminarColumna(columnaSel);
    columnas--;
    barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));
}

void SAC::SelFila()
{
    Seleccion sel;
    sel.SetCantidad(ui->widget->GetFilas(0),ui->widget->GetColumnas(0));
    sel.booleanoF = true;

    for (unsigned int i=0 ; i < ui->widget->cantBotones ; i++)
    {
        sel.boton[i].setStyleSheet("border-width: 5px; border-style:solid; border-color:black; image:url("+ui->widget->boton[i].image+");");
        sel.imagen[i] = ui->widget->boton[i].image;
    }

    sel.exec();
    filaSel = sel.filSel;
    ui->widget->SeleccionarFila(sel.filSel);
    ui->widget->EliminarFila(filaSel);
    filas--;
    barraEstado.setText("Filas: " + QString::number(filas) + "; Columnas: " + QString::number(columnas));
}

void SAC::Cerrar()
{
    ui->widget->BorrarPlantilla();
    ui->actionCerrar->setEnabled(false);
    ui->actionAgregar_columna->setEnabled(false);
    ui->actionAgregar_fila->setEnabled(false);
    ui->actionGuardar->setEnabled(false);
    ui->actionGuardar_como->setEnabled(false);
    ui->actionImprimir_pantalla->setEnabled(false);
    ui->actionSeleccionar_columna->setEnabled(false);
    ui->actionSeleccionar_fila->setEnabled(false);
    ui->actionConfigurar_columna->setEnabled(false);
    ui->actionConfigurar_fila->setEnabled(false);
    ui->actionNuevo->setEnabled(true);
    ui->actionAbrir->setEnabled(true);

    barraEstado.clear();
    ui->mainToolBar->setVisible(false);
}

void SAC::ImprimirPantalla()
{
    PrintScreen w;
    w.exec();
    if(w.printReady){
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPagedPaintDevice::A4);
        printer.setPaperSize(QPrinter::A4);
        if(w.orientationIdx)
        {
            printer.setPageOrientation(QPageLayout::Portrait);
        }else{
            printer.setPageOrientation(QPageLayout::Landscape);
        }
        printer.setOutputFileName(w.filePath+"/"+ w.fileName + ".pdf");
        printer.setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);
        printer.setFullPage(false);

        QPainter painter(&printer);

        double xscale = printer.pageRect().width() / double(ui->widget->width());
        double yscale = printer.pageRect().height() / double(ui->widget->height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.paperRect().center());
        painter.scale(scale, scale);
        painter.translate(-ui->widget->width()/ 2, -ui->widget->height()/ 2);

        ui->widget->render(&painter);
    }
}

void SAC::Salir()
{
    ui->widget->BorrarPlantilla();
    this->close();
}

bool SAC::on_actionGuardar_triggered()
{
    if(curFile.isEmpty())
        {
           return on_actionGuardar_como_triggered();
        }
        else
           return saveFile();
}

bool SAC::saveFile()
{
    QFile file (curFile);
    if(file.open(QFile::WriteOnly))
    {
        QTextStream stream(&file);

        stream <<QString::number(ui->widget->GetFilas(0))+";"+ QString::number(ui->widget->GetColumnas(0))+"\n";
        unsigned int contador;

        for(contador= 0; contador < ui->widget->cantBotones; contador++)
        {
            stream <<ui->widget->boton[contador].label+";"
                     +ui->widget->boton[contador].image+";"
                     +ui->widget->boton[contador].audio+";"
                     +ui->widget->boton[contador].frameString
                     +ui->widget->boton[contador].frameSize+";"
                     +ui->widget->boton[contador].frameColour
                     +ui->widget->boton[contador].fontColour
                     +ui->widget->boton[contador].font.family()+";"
                     +ui->widget->boton[contador].mayuscula+";"
                     +ui->widget->boton[contador].font.bold()+";"
                     +ui->widget->boton[contador].font.italic()+";"
                     +ui->widget->boton[contador].font.underline()+";"
                     +ui->widget->boton[contador].tamanioLetra+"\n";
        }
         return true;
    }
    else
    {
        QMessageBox::warning(this,"EjemploEditor",tr("No se pudo escribir archivo %1. \n Error: %2").arg(curFile).arg(file.errorString()));
        return false;
    }
}

bool SAC::on_actionGuardar_como_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"EjemploEditor",QDir::currentPath(),"Text Files (*.txt);;All files (*.*)");
       if(!fileName.isEmpty())
       {
           curFile = fileName;
           return saveFile();
       }
       return false;
}

bool SAC :: maybeSave()
{
    if (wasModified())
    {
        QMessageBox::StandardButton ret =  QMessageBox::warning(this,"EjemploEditor",tr("El documento ha sido modificado""\n ¿Desea guardar los cambios?"), QMessageBox::Yes | QMessageBox::Cancel | QMessageBox::No);
        if(ret ==QMessageBox::Yes)
        {
          return on_actionGuardar_triggered();
        }
        else if (ret == QMessageBox::Cancel)
        {
            return false;
        }
     }
    return true;
}

bool SAC :: wasModified()
{
    if(flag == true)
    {
        flag = false;
        return true;
    }
    else
        return false;
}

void SAC::on_actionAbrir_triggered(){

    if(maybeSave()){

        QString fileName = QFileDialog::getOpenFileName(this,"EjemploEditor",QDir::currentPath(),"Text Files (*.txt);;All files (*.*)");
        if(!fileName.isEmpty()){

            QFile file(fileName);

            if(file.open(QFile::ReadOnly)){

                string cadenaFile;
                ifstream textoFile (fileName.toStdString());

                // Agarro la primera linea del archivo y la guardo en cadenaFile
                getline(textoFile, cadenaFile);

                std::istringstream iss(cadenaFile);
                string token;
                string informacionArchivo[200];
                int i = 0;

                // Guardo en un array cada "item" separado por ";" de esa linea que agarre
                while (std::getline(iss, token,';')){
                    informacionArchivo[i] = token;
                    i++;
                }

                // Se crea plantilla con filas y columnas correspondientes (primer linea del archivo)
                ui->widget->AgregarPlantilla(stoul(informacionArchivo[0],NULL,0),stoul(informacionArchivo[1],NULL,0),1);
                SAACWidget auxiliar[ui->widget->cantBotones];
                unsigned int contAux;
                int contInforArchivo = 2;
                string help;

                for (contAux = 0;contAux< ui->widget->cantBotones; contAux++){

                    // Guardo label del primer boton en un objeto auxiliar ed SAACWidget
                    auxiliar[contAux].label = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    contInforArchivo++;

                    // Chequeo que exista el directorio de la imagen que guarde, si es asi lo guardo.
                    QFileInfo existing(QString::fromStdString(informacionArchivo[contInforArchivo]));
                    if(existing.exists()){
                        auxiliar[contAux].image = QString::fromStdString(informacionArchivo[contInforArchivo]);
                        contInforArchivo++;
                    }

                    else{
                        //Si no hay ninguna imagen, pongo el archivo "reemplazar.png" (me parece innecesario)
                        QString dirImagenCambiar;
                        QDir imagenCambiar = QDir::currentPath();
                        imagenCambiar.cdUp();

                        dirImagenCambiar = imagenCambiar.absolutePath() + "/Img/reemplazar.png";
                        auxiliar[contAux].image = dirImagenCambiar;

                        contInforArchivo++;
                    }

                    // Guarda el audio
                    auxiliar[contAux].audio = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    contInforArchivo++;

                    // Guarda los datos del frame(borde), creo que se puede hacer de otra manera
                    QString aux1 = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    contInforArchivo++;
                    QString aux2 = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    contInforArchivo++;
                    QString aux3 = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    auxiliar[contAux].frameString = aux1 + ";"+aux2+";"+aux3;
                    contInforArchivo++;

                    // Guarda los datos de la fuente
                    aux1 = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    contInforArchivo++;
                    aux2 = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    contInforArchivo++;
                    aux3 = QString::fromStdString(informacionArchivo[contInforArchivo]);
                    contInforArchivo++;
                    auxiliar[contAux].fontColour = aux1 + ";"+aux2+";"+aux3 +";"+QString::fromStdString(informacionArchivo[contInforArchivo]);

                    contInforArchivo++;
                }

                // Resetea el index de cuandos datos leyo de la linea
                contInforArchivo = 2;
                unsigned int  contCantBotones;

                // Paso la informacion del auxiliar a los botones.
                for(contCantBotones = 0;contCantBotones < ui->widget->cantBotones;contCantBotones++){
                    ui->widget->boton[contCantBotones].setLabel(auxiliar[contCantBotones].label);
                    ui->widget->boton[contCantBotones].setAudio(auxiliar[contCantBotones].audio);
                    ui->widget->boton[contCantBotones].setFrame(auxiliar[contCantBotones].frameString);
                    ui->widget->boton[contCantBotones].setFont(auxiliar[contCantBotones].font);
                    ui->widget->boton[contCantBotones].setFontColor(auxiliar[contCantBotones].fontColour);
                    ui->widget->boton[contCantBotones].setIcon(auxiliar[contCantBotones].image);
                }

                // Enable de acciones que estaban bloqueadas
                ui->actionCerrar->setEnabled(true);
                ui->actionGuardar->setEnabled(true);
                ui->actionGuardar_como->setEnabled(true);
                ui->actionImprimir_pantalla->setEnabled(true);
              }

             else{
                      QMessageBox::warning(this,"EjemploEditor",tr("No se pudo leer archivo %1. \nError %2").arg(fileName).arg(file.errorString()));
             }
       }
    }
}

void SAC::on_actionConfigurar_columna_triggered()
{
    Seleccion sel;

    sel.SetCantidad(ui->widget->GetFilas(0),ui->widget->GetColumnas(0));
    sel.booleanoC = true;

    for (unsigned int i=0 ; i < ui->widget->cantBotones ; i++)
    {
        sel.boton[i].setStyleSheet("border-width: 5px; border-style:solid; border-color:black; image:url("+ui->widget->boton[i].image+");");
        sel.imagen[i] = ui->widget->boton[i].image;
    }

    sel.exec();
    columnaSel = sel.colSel;
    ui->widget->SeleccionarColumna(columnaSel);
    ui->widget->ConfigurarColumna(columnaSel);
}

void SAC::on_actionConfigurar_fila_triggered()
{
    Seleccion sel;

    sel.SetCantidad(ui->widget->GetFilas(0),ui->widget->GetColumnas(0));
    sel.booleanoF = true;

    for (unsigned int i=0 ; i < ui->widget->cantBotones ; i++)
    {
        sel.boton[i].setStyleSheet("border-width: 5px; border-style:solid; border-color:black; image:url("+ui->widget->boton[i].image+");");
        sel.imagen[i] = ui->widget->boton[i].image;
    }

    sel.exec();
    filaSel = sel.filSel;
    ui->widget->SeleccionarFila(filaSel);
    ui->widget->ConfigurarFila(filaSel);
}
