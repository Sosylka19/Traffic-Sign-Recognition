#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLayoutItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <stdbool.h>
#include "imagewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class loginwindow;
}
QT_END_NAMESPACE

class loginwindow : public QWidget
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_sign_in_button_reg_clicked();

    void on_sign_up_button_auth_clicked();

    void on_sign_up_button_reg_clicked();

    void on_sign_in_button_auth_clicked();

    void creating_message_box(QString &str);

private:
    Ui::loginwindow *ui;
    imagewindow *img_window;

    QVBoxLayout *main_layout;
    QWidget *main_widget;
    QWidget *spacer_box_2;
    QWidget *new_widget_creating_acc;
    QWidget *new_widget_creating_acc_auth;
    QHBoxLayout *sign_in_layout;
    bool permission_to_exit;

    QNetworkAccessManager *manager;
    void sendAuthRequest(const QString &url, std::function<void(bool)> callback);

};

#endif // LOGINWINDOW_H
