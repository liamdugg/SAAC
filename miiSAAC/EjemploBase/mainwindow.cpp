#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QString>
#include "..\SAACWidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->widget->button, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*Audio stop*/
    ui->widget->player->stop();

    /*Set font type and point size*/
    ui->widget->font = ui->fontComboBox->currentFont();
    ui->widget->font.setPointSize(ui->lineEdit_4->text().toInt());
    ui->widget->setFont(ui->widget->font);

    /*Set label font color and background color*/
    ui->widget->text->setStyleSheet(auxbgColor+auxfColor+"border-width: 0px;");

    /*Set widget frame width and color*/
    QString frameWAux = "border-width: "+ui->lineEdit_8->text()+"px;";
    ui->widget->frame->setStyleSheet(frameWAux+frameColor);

    /*input image*/
    ui->widget->setIcon(ui->comboBox->currentText());
    /*input label*/
    ui->widget->setLabel(ui->plainTextEdit->toPlainText());

    /*set audio por default pongo eso audio a modo de ejemplo*/
    ui->widget->setAudio("qrc:/Audio/audio_3.mp3");
    /*se setearía el audio con el nombre de la palabra escrita*/
    //ui->widget->setAudio(ui->lineEdit_7->text());

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
        ui->widget->font.setWeight(QFont::Bold);
    }else{
        ui->widget->font.setWeight(0);
    }
    ui->widget->setFont(ui->widget->font);
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
        ui->widget->font.setStyle(QFont::StyleOblique);
    }else{
        ui->widget->font.setStyle(QFont::StyleNormal);
    }
    ui->widget->setFont(ui->widget->font);
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
        ui->widget->font.setUnderline(true);
    }else{
        ui->widget->font.setUnderline(false);
    }
    ui->widget->setFont(ui->widget->font);
}

void MainWindow::btnClicked()
{
    /*output image*/
    ui->lineEdit_5->setText(ui->widget->getIcon());
    /*output label*/
    ui->lineEdit_6->setText(ui->widget->getLabel());
    /*play audio*/

    ui->widget->player->setMedia(QUrl(ui->widget->getAudio()));
    ui->widget->player->setVolume(100);
    ui->widget->player->play();
    /* acá usariamos la funcion sintesis de voz que recibe como parametro la palabra escrita*/
   // ui->widget->sintesisDeVoz(ui->widget->getLabel());
}


void MainWindow::on_colorFondo_clicked()
{
    QColor bgcolor = QColorDialog::getColor(Qt::yellow,this);

    if (bgcolor.isValid())
    {
        auxColor = bgcolor.name(QColor::HexArgb);
        auxbgColor = "background-color:"+auxColor+";";
    }
}

void MainWindow::on_colorLetra_clicked()
{
     QColor fColor = QColorDialog::getColor(Qt::yellow,this);
     if (fColor.isValid())
     {
         auxColor = fColor.name(QColor::HexArgb);
         auxfColor = "color: "+auxColor+";";
     }
}

void MainWindow::on_colorMarco_clicked()
{
    QColor frColor = QColorDialog::getColor(Qt::yellow,this);

    if (frColor.isValid())
    {
        auxColor = frColor.name(QColor::HexArgb);
        frameColor = "border-style: solid; border-color: "+auxColor+";";
    }
}

/*
void MainWindow::on_lineEdit_7_textEdited(const QString &arg1)
{
    if(ui->widget->okUpper)
    {
        ui->lineEdit_7->setText(arg1.toUpper());
    }
    else
      ui->lineEdit_7->setText(arg1.toLower());

}
*/
void MainWindow::on_checkMayuscula_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->widget->okUpper = 0;
    }
    else
        ui->widget->okUpper = 1;
}

/*
void MainWindow::on_plainTextEdit_textChanged()
{
    if(ui->widget->okUpper)
    {
        ui->plainTextEdit->setPlainText(arg1.toUpper());
    }
    else
      ui->lineEdit_7->setText(arg1.toLower());
}
*/
