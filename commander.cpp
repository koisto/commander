#include "commander.h"
#include "ui_commander.h"

Commander::Commander(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Commander)
{
    ui->setupUi(this);
}

Commander::~Commander()
{
    delete ui;
}

void Commander::write_output()
{
    ui->textEdit->append(proc->readAllStandardOutput());
}

void Commander::on_pushButton_clicked()
{
    proc = new QProcess();
   //proc->setProcessChannelMode();

        QObject::connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(write_output()));

    proc->start(ui->lineEdit->text());


}
