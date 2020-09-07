#include "pyram.h"
#include "./ui_pyram.h"
#include "QtWidgets"


pyram::pyram(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pyram)
{
    ui->setupUi(this);
}

void Pyramid(QPixmap *img, int layer, int finish_layer, double q){
    if(layer<finish_layer){
        layer++;
        int w=img->width();
        w = w/q;
        *img = img->scaledToWidth(w,Qt::SmoothTransformation);
        Pyramid(img,layer,finish_layer,q);
    }
}

pyram::~pyram()
{
    delete ui;
}

int diag(QString filename){
    QImage img;
    img.load(filename);
    return img.width()*img.width()+img.height()*img.height();
}

void pyram::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"), "",tr("images(*.BMP, *.JPEG, *.PNG, *.JPG)"));
    if(QString::compare(filename,QString())!=0){
        QImage img;
        bool valid = img.load(filename);

        int n=0;
        while(diag(filename)<diag(ui->comboBox->itemText(n)))
            n++;

        ui->comboBox->insertItem(n,filename);
        if(valid){
            int w = img.width();
            int h = img.height();
            ui->spinBox->setValue(0);
            ui->lb_img->setGeometry(0,0,w,h);
            ui->lb_img->setPixmap(QPixmap::fromImage(img));
            ui->lb_img_pyr->setPixmap(QPixmap::fromImage(img));
            QString ss = "Size: ";
            ss = ss+QString::number( w )+"x"+QString::number( h );
            ui->lb_size->setText( ss);
            ui->lb_size_pyr->setText( ss);
        }
    }
}

void pyram::on_spinBox_valueChanged(int arg1)
{
    int finish_layer = ui->spinBox->value();
    double q = ui->lb_par->value();
    QPixmap pyr = *ui->lb_img->pixmap();
    int w = pyr.width();
    int h = pyr.height();
    Pyramid(&pyr,0,finish_layer,q);
    ui->lb_img_pyr->setGeometry(0,0,w,h);
    int w1 = pyr.width();
    int h1 = pyr.height();
    pyr = pyr.scaledToWidth(w,Qt::SmoothTransformation);
    ui->lb_img_pyr->setPixmap(pyr);
    QString ss = "Size: ";
    ss = ss+QString::number( w1 )+"x"+QString::number( h1 );
    ui->lb_size_pyr->setText( ss);
}

void pyram::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString filename = ui->comboBox->currentText();
    QImage img;
    bool valid = img.load(filename);
    if(valid){
        int w = img.width();
        int h = img.height();
        ui->spinBox->setValue(0);
        ui->lb_img->setGeometry(0,0,w,h);
        ui->lb_img->setPixmap(QPixmap::fromImage(img));
        ui->lb_img_pyr->setPixmap(QPixmap::fromImage(img));
        QString ss = "Size: ";
        ss = ss+QString::number( w )+"x"+QString::number( h );
        ui->lb_size->setText( ss);
        ui->lb_size_pyr->setText( ss);
    }
}
