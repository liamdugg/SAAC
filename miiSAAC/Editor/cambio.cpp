#include "cambio.h"
#include "ui_cambio.h"

Cambio::Cambio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cambio)
{
    ui->setupUi(this);
    connect(ui->widget->button, SIGNAL(clicked()), this, SLOT(btnClicked()));
    disconnect(ui->widget,SIGNAL(clicked()));
    this->setWindowTitle("Editor de Widget");
    negrita = false;
    italica = false;
    subrayado = false;
    okUpper = false;
}

Cambio::~Cambio()
{
    delete ui;
}

void Cambio::on_UpdateBoton_clicked()
{
    /*Audio stop*/
    ui->widget->player->stop();

    ui->widget->label = ui->plainTextEdit->toPlainText();

    /*Set font type and point size*/
    ui->widget->font = ui->fontComboBox->currentFont();
    ui->widget->font.setPointSize(ui->lineEdit_4->text().toInt());
    ui->widget->letterSize = ui->lineEdit_4->text().toInt();

    if(okUpper)
        ui->widget->label = ui->widget->label.toUpper();
    else
    {
        ui->widget->label = ui->widget->label.toLower();
        ui->widget->label[0] = ui->widget->label[0].toUpper();
    }

    /*Set label font color and background color*/
    this->fontColor = auxbgColor+auxfColor+"border-width: 0px;";
    ui->widget->text->setStyleSheet(fontColor);

    /*Set widget frame width and color*/
    QString frameWAux = "border-width: "+anchoMarco+"px;";
    this->frame = frameWAux+frameColor;
    ui->widget->frame->setStyleSheet(frameWAux+frameColor);

    /*input image*/
    ui->widget->setIcon(ui->lineEdit->text());
    /*input label*/
    ui->widget->setLabel(ui->widget->label);

    /*set audio por default pongo eso audio a modo de ejemplo*/
    ui->widget->setAudio("qrc:/Audio/audio_3.mp3");
    /*se setearía el audio con el nombre de la palabra escrita*/
    //ui->widget->setAudio(ui->lineEdit_7->text());

    if(italica)
        ui->widget->font.setStyle(QFont::StyleOblique);
    else
        ui->widget->font.setStyle(QFont::StyleNormal);

    if(negrita)
        ui->widget->font.setWeight(QFont::Bold);
    else
        ui->widget->font.setWeight(0);

    if(subrayado)
        ui->widget->font.setUnderline(true);
    else
        ui->widget->font.setUnderline(false);

    ui->widget->setFont(ui->widget->font);
    tamanioLetra = ui->lineEdit_4->text();
    anchoMarco = ui->lineEdit_8->text();
}


void Cambio::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
        this->negrita = true;
    else
        this->negrita = false;
}

void Cambio::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1)
        this->italica = true;
    else
        this->italica = false;
}

void Cambio::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1)
        this->subrayado = true;
    else
        this->subrayado = false;
}

void Cambio::on_checkMayuscula_stateChanged(int arg1)
{
    if(arg1)
    {
        this->okUpper = true;
    }
    else
        this->okUpper = false;
}


void Cambio::on_colorFondo_clicked()
{
    QColor bgcolor = QColorDialog::getColor(Qt::yellow,this);

    if (bgcolor.isValid())
    {
        auxColor = bgcolor.name(QColor::HexArgb);
        auxbgColor = "background-color:"+auxColor+";";
    }
}

void Cambio::on_colorLetra_clicked()
{
    QColor fColor = QColorDialog::getColor(Qt::yellow,this);
    if (fColor.isValid())
    {
        auxColor = fColor.name(QColor::HexArgb);
        auxfColor = "color: "+auxColor+";";
    }
}

void Cambio::on_colorMarco_clicked()
{
    QColor frColor = QColorDialog::getColor(Qt::yellow,this);

    if (frColor.isValid())
    {
        auxColor = frColor.name(QColor::HexArgb);
        frameColor = "border-style: solid; border-color: "+auxColor+";";
    }
}


void Cambio::btnClicked()
{

    ui->widget->player->setMedia(QUrl(ui->widget->getAudio()));
    ui->widget->player->setVolume(100);
    ui->widget->player->play();
    /* acá usariamos la funcion sintesis de voz que recibe como parametro la palabra escrita*/
   // ui->widget->sintesisDeVoz(ui->widget->getLabel());
}

void Cambio::on_botCancelar_clicked()
{
    this->reject();
}

void Cambio::on_botAceptar_clicked()
{
    this->label = ui->plainTextEdit->toPlainText();
    this->image = ui->lineEdit->text();
    this->font = ui->widget->font;
    QString frameWAux = "border-width: "+anchoMarco+"px;";
    this->frame = frameWAux+frameColor;
    ui->widget->frame->setStyleSheet(frameWAux+frameColor);

    this->accept();
}

void Cambio::on_UpdateBoton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"EjemploEditor",QDir::currentPath(),"PNG Files (*.png)");
    QFile file(filename);

    file.open(QFile::ReadOnly);
    ui->lineEdit->setText(file.fileName());
}

void Cambio::SetParametros(QString texto, QString imagen, QString marco, QString colorFuente, QFont fuente)
{
    ui->widget->setLabel(texto);
    ui->widget->setFont(fuente);
    ui->widget->setFontColor(colorFuente);
    ui->widget->setIcon(imagen);
    ui->widget->setFrame(marco);
    ui->plainTextEdit->setPlainText(texto);
    ui->lineEdit->setText(imagen);
    this->fontColor = colorFuente;
    this->frameColor = marco;
    this->auxbgColor = colorFuente;
}

void Cambio::SetCuadro(bool min, bool neg, bool it, bool sub, QString ancMar, QString tamLet)
{
    ui->lineEdit_8->setText(ancMar);
    ui->lineEdit_4->setText(tamLet);
    ui->checkBox->setChecked(neg);
    ui->checkBox_2->setChecked(it);
    ui->checkBox_3->setChecked(sub);
    ui->checkMayuscula->setChecked(min);
    this->tamanioLetra = tamLet;
    this->anchoMarco = ancMar;
}
