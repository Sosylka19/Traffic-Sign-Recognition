#include "imagewindow.h"
#include "rounded_label.h"
#include "ui_imagewindow.h"
#include "../../inference_yolov8n/main_inference.h"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>
#include "../../inference_yolov8n/inference.h"

imagewindow::imagewindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::imagewindow)
{
    ui->setupUi(this);

    //adding to layout widgets
    QVBoxLayout *outter_layout = new QVBoxLayout(this);
    main_widget = new QWidget();
    outter_layout->addWidget(main_widget);
    main_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout = new QVBoxLayout(main_widget);

    QSpacerItem *top_spacer = new QSpacerItem(110, 110, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *label_widget_spacer = new QSpacerItem(20, 35, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *browse_button_spacer = new QSpacerItem(20, 35, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *detect_button_spacer = new QSpacerItem(20, 35, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *detect_down_spacer = new QSpacerItem(20, 5, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *browse_down_spacer = new QSpacerItem(20, 5, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *between_widgets= new QSpacerItem(20, 5, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *left_widgets_spacer= new QSpacerItem(20, 5, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *right_widgets_spacer= new QSpacerItem(20, 5, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *down_spacer= new QSpacerItem(20, 100, QSizePolicy::Fixed, QSizePolicy::Expanding);

    main_layout->addSpacerItem(top_spacer);
    main_layout->addWidget(ui->pick_image_txt, 0, Qt::AlignHCenter);
    main_layout->addSpacerItem(label_widget_spacer);

    ////creating layout for images widgets
    QHBoxLayout *widget_layout = new QHBoxLayout(ui->widget);

    //////creating layout fo browse image
    QVBoxLayout *widget_browser_layout = new QVBoxLayout(ui->widget_browser);
    widget_browser_layout->addWidget(ui->image_browse, 0, Qt::AlignHCenter);
    widget_browser_layout->addSpacerItem(browse_button_spacer);
    widget_browser_layout->addWidget(ui->browse_media_push, 0, Qt::AlignHCenter);
    widget_browser_layout->addSpacerItem(browse_down_spacer);
    widget_browser_layout->setSpacing(0);

    //////creating layout for detect image
    QVBoxLayout *widget_detect_layout = new QVBoxLayout(ui->widget_detect);
    widget_detect_layout->addWidget(ui->image_detect, 0, Qt::AlignHCenter);
    widget_detect_layout->addSpacerItem(detect_button_spacer);
    widget_detect_layout->addWidget(ui->start_detection_push, 0, Qt::AlignHCenter);
    widget_detect_layout->addSpacerItem(detect_down_spacer);
    widget_detect_layout->setSpacing(0);

    widget_layout->addSpacerItem(left_widgets_spacer);
    widget_layout->addWidget(ui->widget_browser, 0, Qt::AlignVCenter);
    widget_layout->addSpacerItem(between_widgets);
    widget_layout->addWidget(ui->widget_detect, 0, Qt::AlignVCenter);
    widget_layout->addSpacerItem(right_widgets_spacer);

    main_layout->addWidget(ui->widget);
    main_layout->addSpacerItem(down_spacer);


}

void imagewindow::on_browse_media_push_clicked()
{
    filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), tr("Image Files(*.png, *.jpg, *.jpeg"));


    ui->image_browse->set_round_pixmap(QPixmap(filename), 30);

}



imagewindow::~imagewindow()
{
    delete ui;
}




void imagewindow::on_start_detection_push_clicked()
{
    std::filesystem::path pth = filename.toStdString();
    cv::Mat img = DetectTest(pth);
    QString output_image_path =
        QCoreApplication::applicationDirPath() + "/imsge_ouput.jpg";
    cv::imwrite(output_image_path.toStdString(), img);
    ui->image_detect->set_round_pixmap(QPixmap(output_image_path), 30);
}

