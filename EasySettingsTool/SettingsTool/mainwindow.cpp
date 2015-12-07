#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connect UI
    connect(ui->settingsPathButton, SIGNAL(released()), this, SLOT(chooseSettingsPath()));
    connect(ui->songPathButton, SIGNAL(released()), this, SLOT(chooseSongPath()));
    connect(ui->save, SIGNAL(released()), this, SLOT(save()));
    connect(ui->load, SIGNAL(released()), this, SLOT(load()));
    connect(ui->exit, SIGNAL(released()), this, SLOT(exit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseSettingsPath()
{
    //Open dialog
    const QString path = QFileDialog::getOpenFileName(this, tr("Open settings file"), QString(), tr("Settings File (*.xml)"));

    //Set selected path to line edit
    ui->settingsPath->setText(path);

    //Verify?

    //Enable other group boxes
    ui->groupBox2->setEnabled(true);
    ui->groupBox3->setEnabled(true);
}

void MainWindow::chooseSongPath()
{
    //Open dialog
    QString path = QFileDialog::getOpenFileName(this, tr("Open music file"), QString(), tr("Audio File (*.wav *.mp3 *.aif)"));

    //Get relative path to data folder
    const QFileInfo info(ui->settingsPath->text());
    const QDir dir(info.dir());
    path = dir.relativeFilePath(path);

    //Set selected path to line edit
    ui->songPath->setText(path);
}

void MainWindow::save()
{
    //Get file
    QDomDocument doc("settings");
    QFile file(ui->settingsPath->text());

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Can not open settings file"), tr("Make sure the file exists."));
        return;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        QMessageBox::warning(this, tr("Can not read settings file"), tr("Make sure the file has not been moved."));
        return;
    }

    file.close();

    QDomElement docElem = doc.documentElement();

    //Verify file
    if (docElem.tagName() != QString("PulseSettings"))
    {
        QMessageBox::warning(this, tr("Main node not found"), tr("The main node of the settings file should be 'PulseSettings'. Make sure this a correct settings file."));
        return;
    }

    //Song settings
    {
        QDomElement song = docElem.firstChildElement("song");

        song.setAttribute("path", ui->songPath->text());
        song.setAttribute("tempo", QString::number(ui->tempo->value()));
        song.setAttribute("volume", QString::number(ui->volume->value()));
    }

    //Display settings
    {
        QDomElement display = docElem.firstChildElement("display");

        display.setAttribute("width", QString::number(ui->width->value()));
        display.setAttribute("height", QString::number(ui->height->value()));

        if (ui->displayMode->currentIndex() == 0)
            display.setAttribute("fullscreen", "1");
        else
            display.setAttribute("fullscreen", "0");

        if (ui->background->currentIndex() == 0)
            display.setAttribute("background", "1");
        else
            display.setAttribute("background", "0");
    }

    //Debug settings
    {
        QDomElement debug = docElem.firstChildElement("debug");

        debug.setAttribute("mouse", QString::number(ui->debugSlate->currentIndex()));
        debug.setAttribute("tick", QString::number(ui->debugTempo->currentIndex()));
    }

    //Write file
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Can not open settings file in write mode"), tr("Make sure the file exists."));
        return;
    }

    QTextStream stream(&file);
    stream << doc;
    file.close();

    QMessageBox::information(this, tr("We're all good"), tr("Settings successfully saved."));
}

void MainWindow::load()
{
    //Get file
    QDomDocument doc("settings");
    QFile file(ui->settingsPath->text());

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Can not open settings file"), tr("Make sure the file exists."));
        return;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        QMessageBox::warning(this, tr("Can not read settings file"), tr("Make sure the file has not been moved."));
        return;
    }

    file.close();

    QDomElement docElem = doc.documentElement();

    //Verify file
    if (docElem.tagName() != QString("PulseSettings"))
    {
        QMessageBox::warning(this, tr("Main node not found"), tr("The main node of the settings file should be 'PulseSettings'. Make sure this a correct settings file."));
        return;
    }

    //Song settings
    {
        QDomElement song = docElem.firstChildElement("song");

        const QString path = song.attribute("path");
        const int tempo = song.attribute("tempo").toInt();
        const double volume = song.attribute("volume").toDouble();

        ui->songPath->setText(path);
        ui->tempo->setValue(tempo);
        ui->volume->setValue(volume);
    }

    //Display settings
    {
        QDomElement display = docElem.firstChildElement("display");

        const int width = display.attribute("width").toInt();
        const int height = display.attribute("height").toInt();
        const bool fullscreen = (bool)display.attribute("fullscreen").toInt();
        const bool background = (bool)display.attribute("background").toInt();

        ui->width->setValue(width);
        ui->height->setValue(height);
        fullscreen ? ui->displayMode->setCurrentIndex(0) : ui->displayMode->setCurrentIndex(1);
        background ? ui->background->setCurrentIndex(0) : ui->background->setCurrentIndex(1);
    }

    //Debug settings
    {
        QDomElement debug = docElem.firstChildElement("debug");

        const bool mouse = (bool)debug.attribute("mouse").toInt();
        const bool tick = (bool)debug.attribute("tick").toInt();

        mouse ? ui->debugSlate->setCurrentIndex(1) : ui->debugSlate->setCurrentIndex(0);
        tick ? ui->debugTempo->setCurrentIndex(1) : ui->debugTempo->setCurrentIndex(0);
    }

    QMessageBox::information(this, tr("Settings successfully loaded"), tr("Settings successfully loaded."));
}

void MainWindow::exit()
{
    if (QMessageBox::question(this, tr("Exit?"), tr("Are you sure you want to exit?")) == QMessageBox::Yes)
        QApplication::quit();
}
