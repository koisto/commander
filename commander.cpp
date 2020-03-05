#include "commander.h"
#include "ui_commander.h"

Commander::Commander(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Commander)
    , proc(new QProcess(parent))
{
    ui->setupUi(this);

    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(write_output()));
    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(write_error()));
    connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(command_finished(int, QProcess::ExitStatus)));
}

Commander::~Commander()
{
    delete ui;
}

void Commander::command_finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->textEdit->setTextColor(Qt::black);

    if (exitStatus == QProcess::NormalExit)
    {
        QString txt = "Exit code: ";
        txt += QString::number(exitCode);
        ui->textEdit->append(txt);
    }
    else
    {
        ui->textEdit->append("Command crashed.");
    }

    ui->pushButton->setEnabled(true);
    ui->lineEdit->setEnabled(true);
}

void Commander::write_output()
{
    ui->textEdit->setTextColor(Qt::black);
    ui->textEdit->insertPlainText(proc->readAllStandardOutput());
}

void Commander::write_error()
{
    ui->textEdit->setTextColor(Qt::red);
    ui->textEdit->insertPlainText(proc->readAllStandardError());
}

void Commander::on_pushButton_clicked()
{
    QString cmd = ui->lineEdit->text();
    if (!cmd.isEmpty())
    {
        ui->textEdit->clear();
        ui->pushButton->setEnabled(false);
        ui->lineEdit->setEnabled(false);

        proc->start(cmd);
    }
}
