#ifndef IPS2021_H
#define IPS2021_H

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

private:
    Ui::IPS2021 *ui;
};
#endif // IPS2021_H
