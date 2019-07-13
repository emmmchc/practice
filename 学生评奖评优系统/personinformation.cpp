#include "personinformation.h"
#include "ui_personinformation.h"

PersonInformation::PersonInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonInformation)
{
    ui->setupUi(this);
}

PersonInformation::~PersonInformation()
{
    delete ui;
}

