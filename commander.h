#ifndef COMMANDER_H
#define COMMANDER_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Commander; }
QT_END_NAMESPACE

class Commander : public QMainWindow
{
    Q_OBJECT

public:
    Commander(QWidget *parent = nullptr);
    ~Commander();

private slots:
    void on_pushButton_clicked();
    void write_output();
    void write_error();
    void command_finished(int exitCode, QProcess::ExitStatus exitStatus);


private:
    Ui::Commander *ui;
    QProcess * proc;

};
#endif // COMMANDER_H
