#include "roomstm.h"

static QString path= "/home/greg/Bureau/Domotique_Client_Integrated/images/";

RoomStm::RoomStm(QString name, QObject *parent) : QObject(parent)
{
    serial = new MySerialPort(name);

    //Envoie les données reçu du stm32 à l'interface graphique.
    QObject::connect(serial, SIGNAL(sendDataChambre(RoomStmModel*)), this, SLOT(setChambre(RoomStmModel*)));

    widget = new QWidget();
    //Création du layout
    hbox = new QVBoxLayout();
    hbox->setDirection(QBoxLayout::TopToBottom);
    //Création du layout Top
    lTop = new QHBoxLayout();
    lTop->setDirection(QBoxLayout::LeftToRight);

    //Création du layout Bottom
    lBottom = new QHBoxLayout();
    lBottom->setDirection(QBoxLayout::TopToBottom);

    //Création du contenu du layout Top
    lblName = new QLabel("name");
    lblName->setAlignment(Qt::AlignCenter);
    QFont f = lblName->font();
    f.setPixelSize(50);
    f.setWeight(QFont::Black);

    lblName->setFont(f);
    lblName->setMaximumHeight(60);
    lblName->setAlignment(Qt::AlignCenter);
    lTop->addWidget(lblName);

    //Création du contenu d'affichage de température
    lTemp = new QHBoxLayout();
    lTemp->setDirection(QBoxLayout::LeftToRight);
    //Image Thermometre
    iTemp = new QPixmap(path + "temperature.png");
    iLbl = new QLabel();
    iLbl->setPixmap(*iTemp);
    iLbl->setMaximumWidth(150);
    iLbl->setStyleSheet("background-color: gray;" "border: 1px solid black");
    iLbl->setMaximumHeight(120);
    lTemp->addWidget(iLbl);

    //Création de l'afficheur LCD
    lcdTemp = new QLCDNumber();
    lcdTemp->setStyleSheet("background-color: gray;"  "border: 1px solid black");
    lcdTemp->setMaximumHeight(120);
    lTemp->addWidget(lcdTemp);

    //Création du contenu de l'unité °C
    iTemp = new QPixmap(path + "C.png");
    iLbl = new QLabel();
    iLbl->setPixmap(*iTemp);
    iLbl->setMaximumWidth(150);
    iLbl->setStyleSheet("background-color: gray;" "border: 1px solid black");
    iLbl->setMaximumHeight(120);
    lTemp->addWidget(iLbl);
    lTemp->setSpacing(0);
    lBottom->addLayout(lTemp);

    //Création du contenu d'affichage de pression
    lPress = new QHBoxLayout();
    lPress->setDirection(QBoxLayout::LeftToRight);
    //Image Thermometre
    iPress = new QPixmap(path + "pression.png");
    iLbl = new QLabel();
    iLbl->setPixmap(*iPress);
    iLbl->setMaximumWidth(150);
    iLbl->setStyleSheet("background-color: gray;" "border: 1px solid black");
    iLbl->setMaximumHeight(120);
    lPress->addWidget(iLbl);

    //Création de l'afficheur LCD
    lcdPress = new QLCDNumber();
    lcdPress->setStyleSheet("background-color: gray;"  "border: 1px solid black");
    lcdPress->setMaximumHeight(120);
    lPress->addWidget(lcdPress);

    //Création du contenu de l'unité °C
    iPress = new QPixmap(path + "hPa.png");
    iLbl = new QLabel();
    iLbl->setPixmap(*iPress);
    iLbl->setMaximumWidth(150);
    iLbl->setStyleSheet("background-color: gray;" "border: 1px solid black");
    iLbl->setMaximumHeight(120);
    lPress->addWidget(iLbl);
    lPress->setSpacing(0);

    lBottom->addLayout(lPress);

    //Création du contenu du layout
    hbox->addLayout(lTop);
    hbox->addLayout(lBottom);
    hbox->setAlignment(Qt::AlignTop);
    widget->setLayout(hbox);
}

RoomStm::~RoomStm()
{

}


QWidget* RoomStm::getWidget()
{
    return widget;
}


MySerialPort* RoomStm::getSerialPort()
{
    return serial;
}

QString RoomStm::getName()
{
    QString name = lblName->text();
    return name;
}

void RoomStm::setChambre(RoomStmModel* chambre)
{
    lblName->setText(chambre->name());
    lcdTemp->setProperty("value", chambre->temp());
    lcdPress->setProperty("value", chambre->pressure());
}
