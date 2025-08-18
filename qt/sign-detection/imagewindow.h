#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class imagewindow;
}
QT_END_NAMESPACE

class imagewindow : public QWidget
{
    Q_OBJECT

public:
    explicit imagewindow(QWidget *parent = nullptr);
    ~imagewindow();

private slots:
    void on_browse_media_push_clicked();

    void on_start_detection_push_clicked();

private:
    Ui::imagewindow *ui;
    QVBoxLayout *main_layout;
    QWidget *main_widget;
    QString filename;

};

#endif // IMAGEWINDOW_H
