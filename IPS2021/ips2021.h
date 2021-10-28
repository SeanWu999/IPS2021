#ifndef IPS2021_H
#define IPS2021_H

#include <src/myinclude.h>
#include <src/maincontroller.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IPS2021; }
QT_END_NAMESPACE

class IPS2021 : public QMainWindow
{
    Q_OBJECT

public:
    IPS2021(QWidget *parent = nullptr);
    ~IPS2021();

public slots:
    void clickStartButton();
    void clickStopButton();

private:
    Ui::IPS2021 *ui;
    void init();
    void initForm();
    void initConnect();
    void deleteConnect();

    MainController *controller;
};
#endif // IPS2021_H
