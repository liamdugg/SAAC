#include "printscreen.h"
#include "ui_printscren.h"
#include <QFileDialog>
#include <QMessageBox>
PrintScreen::PrintScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintScren)
{
    ui->setupUi(this);
}

PrintScreen::~PrintScreen()
{
    delete ui;
}

void PrintScreen::on_buttonBox_accepted()
{
    this->fileName = ui->lineEdit_fileName->text();
    this->filePath = ui->lineEdit_filePath->text();
    this->orientationIdx = ui->comboBox->currentIndex();
    this->printReady = true;
}

void PrintScreen::on_buttonBox_rejected()
{
    this->printReady = false;
}

void PrintScreen::on_pushButton_Explorar_clicked()
{
    this->filePath = QFileDialog::getExistingDirectory(this, "Seleccionar directorio", "C://");
    ui->lineEdit_filePath->setText(this->filePath);
}
