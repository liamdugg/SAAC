#ifndef SAACWIDGET_H
#define SAACWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QGridLayout>
#include <QFont>
#include <QMediaPlayer>
#include <QDrag>
#include <QMimeData>
#include <QUrl>
#include <iostream>
#include "Editor/cambio.h"

using namespace std;

class SAACWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SAACWidget(QWidget *parent = nullptr);
    ~SAACWidget();

    QFont font;
    QString color;
    QFrame *frame;
    QToolButton *button;
    QLabel *text;
    QGridLayout *outerLayout, *innerLayout;
    QMediaPlayer *player;


    void setIcon(QString image);
    void setLabel(QString label);
    void setAudio(QString audio);
    void setFont(QFont font);
    void setFontColor(QString fontColor);
    void setFrame(QString frameType);
    void sintesisDeVoz(QString label);

    QString getIcon();
    QString getLabel();
    QString getAudio();
    QString getFontColour();
    int getLetterSize();
    QString getFrameSize();
    QString getLetterColour();

    QString anchoMarco, tamanioLetra;
    QString image, label, audio, fontColour, frameString,frameSize,letterColour,frameColour;
    int letterSize;
    bool audioEnable, mayuscula, negrita, italica, subrayado;

public slots:
    void BotonPresionado(void);
};

#endif // SAACWIDGET_H
