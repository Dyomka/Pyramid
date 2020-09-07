#ifndef PYRAM_H
#define PYRAM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class pyram; }
QT_END_NAMESPACE

class pyram : public QMainWindow
{
    Q_OBJECT

public:
    pyram(QWidget *parent = nullptr);
    ~pyram();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::pyram *ui;
};
#endif // PYRAM_H
