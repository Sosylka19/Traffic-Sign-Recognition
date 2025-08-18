#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QUrl>
#include <stdbool.h>

loginwindow::loginwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginwindow)
{
    ui->setupUi(this);

    //window for switching
    img_window = new imagewindow();

    //creating newtowk manager
    manager = new QNetworkAccessManager(this);

    ui->email_text->setMaxLength(60);
    ui->password_text->setMaxLength(60);

    //setting password hiden
    ui->password_text->setEchoMode(QLineEdit::Password);

    //loginwindow_layout
    QVBoxLayout *outer_layout = new QVBoxLayout(this);
    main_widget = new QWidget(this);
    outer_layout->addWidget(main_widget);
    main_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout = new QVBoxLayout(main_widget);
    main_layout->setSpacing(0);
    QSpacerItem *top_spacer = new QSpacerItem(20, 110, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *box_label_spacer = new QSpacerItem(20, 100, QSizePolicy::Fixed, QSizePolicy::Fixed);
    spacer_box_2 = new QWidget();
    spacer_box_2->setFixedHeight(15);
    QSpacerItem *spacer_box_3 = new QSpacerItem(20, 25, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *spacer_button_label = new QSpacerItem(20, 5, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *down_spacer = new QSpacerItem(20, 200, QSizePolicy::Expanding, QSizePolicy::Expanding);

    main_layout->addSpacerItem(top_spacer);
    main_layout->addWidget(ui->create_account, 0, Qt::AlignHCenter);
    main_layout->addSpacerItem(box_label_spacer);
    main_layout->addWidget(ui->email_text, 0, Qt::AlignHCenter);
    main_layout->addWidget(spacer_box_2, 0, Qt::AlignHCenter);
    main_layout->addWidget(ui->password_text, 0, Qt::AlignHCenter);
    main_layout->addSpacerItem(spacer_box_3);
    main_layout->addWidget(ui->sign_up_button_reg, 0, Qt::AlignHCenter);
    main_layout->addSpacerItem(spacer_button_label);

    ////Widget for Sign in
    sign_in_layout = new QHBoxLayout();
    sign_in_layout->setContentsMargins(0, 0, 0, 0);
    sign_in_layout->addWidget(ui->having_acc, 0, Qt::AlignTop);
    sign_in_layout->addWidget(ui->sign_in_button_reg, 0, Qt::AlignTop);
    ui->widget_creating_acc->setLayout(sign_in_layout);

    main_layout->addWidget(ui->widget_creating_acc, 0, Qt::AlignHCenter);
    main_layout->addSpacerItem(down_spacer);
    main_widget->setLayout(main_layout);
    //



}

void loginwindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int window_height = this->height();
    int min_window_height = 800;
    int max_window_height = 1000;

    int window_width = this->width();
    int min_window_width = 1100;
    int max_window_width = 1300;

    int new_height, new_width, new_font_size;
    //conditions on height
    if (window_height <= min_window_height)
    {
        new_height = 50;
    }
    else if (window_height >= max_window_height)
    {
        new_height = 60;
    }
    else
    {
        float ratio = float(window_height - min_window_height) / (max_window_height - min_window_height);
        new_height = 50 + ratio * 10;
    }

    //conditions on width
    if (window_width <= min_window_width)
    {
        new_width = 700;
    }
    else if (window_width >= max_window_width)
    {
        new_width= 900;
    }
    else
    {
        float ratio = float(window_width - min_window_width) / (max_window_width - min_window_width);
        new_width = 700 + ratio * 200;

    }
    //changing height
    ui->email_text->setFixedHeight(new_height);
    ui->password_text->setFixedHeight(new_height);

    //changing width
    ui->email_text->setFixedWidth(new_width);
    ui->password_text->setFixedWidth(new_width);
}

loginwindow::~loginwindow()
{
    delete ui;
}


void loginwindow::on_sign_in_button_reg_clicked()
{
    //replacing
    main_layout->replaceWidget(ui->sign_up_button_reg, ui->sign_in_button_auth);
    ui->sign_up_button_reg->hide();
    ui->sign_in_button_auth->show();
    sign_in_layout->replaceWidget(ui->sign_in_button_reg, ui->sign_up_button_auth);

    //overriding previous widgets
    main_layout->setSpacing(0);
    ui->having_acc->setText("Don't have an account yet?");
    ui->create_account->setText("AUTHORIZATION");

    //clearing text lines
    ui->password_text->clear();
    ui->email_text->clear();


}

void loginwindow::creating_message_box(QString &str)
{
    QMessageBox msg(this);
    QString s = "QLabel{ color: black; }";
    QString style_button_string = ui->sign_up_button_reg->styleSheet() + s;
    msg.setStyleSheet(style_button_string);
    msg.setText(str);
    msg.setWindowTitle("Error");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setDefaultButton(QMessageBox::Ok);
    msg.exec();
}


void loginwindow::on_sign_up_button_auth_clicked()
{
    //replacing
    main_layout->replaceWidget(ui->sign_in_button_auth, ui->sign_up_button_reg);
    ui->sign_in_button_auth->hide();
    ui->sign_up_button_reg->show();
    sign_in_layout->replaceWidget(ui->sign_up_button_auth, ui->sign_in_button_reg);

    //overriding
    main_layout->setSpacing(0);
    ui->having_acc->setText("Have an account?");
    ui->create_account->setText("CREATE ACCOUNT");


    //clearing text lines
    ui->password_text->clear();
    ui->email_text->clear();
}


void loginwindow::on_sign_up_button_reg_clicked()
{
    //send request
    sendAuthRequest("http://127.0.0.1:8000/register", [this](bool permission_to_exit) {
    if (permission_to_exit)
    {
        //replacing
        main_layout->replaceWidget(ui->sign_up_button_reg, ui->sign_in_button_auth);
        ui->sign_up_button_reg->hide();
        ui->sign_in_button_auth->show();
        sign_in_layout->replaceWidget(ui->sign_in_button_reg, ui->sign_up_button_auth);

        //overriding previous widgets
        main_layout->setSpacing(0);
        ui->having_acc->setText("Don't have an account yet?");
        ui->create_account->setText("AUTHORIZATION");

        //clearing text lines
        ui->password_text->clear();
        ui->email_text->clear();
    }
    });
}


void loginwindow::on_sign_in_button_auth_clicked()
{
    //send request
    sendAuthRequest("http://127.0.0.1:8000/login", [this](bool permission_to_exit) {
    if (permission_to_exit)
    {
        img_window->show();
        this->hide();
    }
    });

}

void loginwindow::sendAuthRequest(const QString &url, std::function<void(bool)> callback)
{
    QString email = ui->email_text->text();
    QString password = ui->password_text->text();

    if (email.isEmpty() || password.isEmpty())
    {
        QString str = "Email and password can not be empty";
        creating_message_box(str);
        callback(false);
        return;
    }

    QJsonObject json;
    json["email"] = email;
    json["password"] = password;

    QNetworkRequest request{QUrl(url)};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callback]() {
        reply->deleteLater();


        QByteArray response_data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response_data);

        if (reply->error() != QNetworkReply::NoError)
        {
            if (doc.isObject())
            {
                QString str = doc.object().value("detail").toString();
                creating_message_box(str);
                callback(false);
            }
            return;
        }

        callback(true);
    });

}



