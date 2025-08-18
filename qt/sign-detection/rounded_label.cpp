#include "rounded_label.h"
#include <QPainter>
#include <QPainterPath>


rounded_label::rounded_label(QWidget *parent)
    : QLabel(parent), m_radius(30) {}

void rounded_label::set_round_pixmap(const QPixmap &pixmap, int radius) {
    m_pixmap = pixmap;
    m_radius = radius;
    update();
}

void rounded_label::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (m_pixmap.isNull()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPixmap scaled = m_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QRect targetRect(0, 0, width(), height());
    QRect sourceRect = QRect(
        (scaled.width() - width()) / 2,
        (scaled.height() - height()) / 2,
         width(),
         height()
        );

    QPainterPath path;
    path.addRoundedRect(targetRect, m_radius, m_radius);
    painter.setClipPath(path);

    painter.drawPixmap(targetRect, scaled, sourceRect);
}
