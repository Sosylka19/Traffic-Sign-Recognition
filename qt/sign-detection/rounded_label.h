#ifndef ROUNDED_LABEL_H
#define ROUNDED_LABEL_H

#include <QLabel>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class rounded_label;
}
QT_END_NAMESPACE


class rounded_label : public QLabel {
    Q_OBJECT

public:
    explicit rounded_label(QWidget *parent = nullptr);


    void set_round_pixmap(const QPixmap &pixmap, int radius = 30);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_pixmap;
    int m_radius;
};

#endif // ROUNDED_LABEL_H
