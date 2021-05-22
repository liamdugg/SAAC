#include "SAACWidget.h"
#include <QLayout>
#include <QFrame>
#include <QDebug>
#include <QResizeEvent>
#include <QPushButton>
#include <QFontMetricsF>
#include <QDebug>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

SAACWidget::SAACWidget(QWidget *parent) : QWidget(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    this->outerLayout = new QGridLayout(this);
    this->frame = new QFrame(this);
    this->frame->setFrameShape(QFrame::StyledPanel);
    this->frame->setFrameShadow(QFrame::Raised);

    this->innerLayout = new QGridLayout(this->frame);
    this->button = new QToolButton(this->frame);
    sizePolicy.setHeightForWidth(this->button->sizePolicy().hasHeightForWidth());
    this->button->setSizePolicy(sizePolicy);
    this->innerLayout->addWidget(this->button, 0, 0, 1, 1);

    this->text = new QLabel(this->frame);
    this->innerLayout->addWidget(this->text, 1, 0, 1, 1, Qt::AlignHCenter);

    this->outerLayout->addWidget(this->frame, 0, 0, 1, 1);


    this->player = new QMediaPlayer(this);


    /*default*/
    this->setStyleSheet(" background-color: rgb(230,230,230) ");
    this->setAudio("qrc:/Audio/audio_3");

    /*InitFont*/
    this->font.setStretch(QFont::UltraExpanded);

    this->button->setMouseTracking(true);
    connect(this->button,SIGNAL(clicked()),this,SLOT(BotonPresionado()));
}

SAACWidget::~SAACWidget(void)
{
    delete this->button;
    delete this->text;
    delete this->player;
    delete this->innerLayout;
    delete this->frame;
    delete this->outerLayout;
}

void SAACWidget::setFont(QFont font)
{
    this->text->setFont(font);
    this->font = font;
}

void SAACWidget::setFontColor(QString fontColor)
{
    this->fontColour = fontColor;
    this->text->setStyleSheet(fontColor);
}

void SAACWidget::setIcon(QString image)
{
    this->image = image;
    this->button->setStyleSheet("border-image:url("+image+");");
}

void SAACWidget::setLabel(QString label)
{
    this->text->setText(label);
    this->label = label;
}

void SAACWidget::setAudio(QString audio)
{
    this->audio = audio;
}

QString SAACWidget::getLabel()
{
    return this->label;
}

QString SAACWidget::getAudio()
{
    return this->audio;
}

int SAACWidget:: getLetterSize()
{
    return this->letterSize;
}

QString SAACWidget::getFrameSize()
{
    std::cout<<"aca "<<this->frameSize.toStdString()<<endl;
    return this->frameSize;
}

QString SAACWidget::getLetterColour()
{
    return this->letterColour;
}

QString SAACWidget::getIcon()
{
    return this->image;
}

QString SAACWidget :: getFontColour()
{
    return this->fontColour;
}

void SAACWidget::sintesisDeVoz(QString label)
{
    this->player->setMedia(QUrl(label));
    this->player->setVolume(100);
    this->player->play();
}

void SAACWidget::setFrame(QString frameType)
{
    this->frameString = frameType;
    this->frame->setStyleSheet(frameType);
}

void SAACWidget::BotonPresionado(void)
{
    Cambio evento;
    evento.SetParametros(this->label, this->image, this->frameString, this->fontColour, this->font);
    evento.SetCuadro(this->mayuscula, this->negrita, this->italica, this->subrayado, this->anchoMarco, this->tamanioLetra);

    if(evento.exec() == QDialog::Accepted)
    {
        this->anchoMarco = evento.anchoMarco;
        this->tamanioLetra = evento.tamanioLetra;

        if(evento.okUpper)
        {
            evento.label = evento.label.toUpper();
            this->mayuscula = true;
        }
        else
        {
            evento.label = evento.label.toLower();
            evento.label[0] = evento.label[0].toUpper();
            this->mayuscula = false;
        }

        if(evento.negrita)
        {
            this->font.setWeight(QFont::Bold);
            this->negrita = true;
        }
        else
        {
            this->font.setWeight(0);
            this->negrita = false;
        }

        if(evento.subrayado)
        {
            this->font.setUnderline(true);
            this->subrayado = true;
        }
        else
        {
            this->font.setUnderline(false);
            this->subrayado = false;
        }

        if(evento.italica)
        {
            this->font.setStyle(QFont::StyleOblique);
            this->italica = true;
        }
        else
        {
            this->font.setStyle(QFont::StyleNormal);
            this->italica = false;
        }
        setLabel(evento.label);
        setIcon(evento.image);
        setFont(evento.font);
        setFontColor(evento.fontColor);
        setFrame(evento.frame);
    }
}
