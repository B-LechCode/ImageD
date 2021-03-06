/************************************************
 *   added:     05.06.2020                      *
 *   author:    David Eilenstein                *
 *   contact:   David.Eilenstein@stud.h-da.de   *
 *   project:   ImageD                          *
 *   facility:  Hochschule Darmstadt, Ger       *
 ************************************************/

#include "d_makro_fouriertransformator.h"
#include "ui_d_makro_fouriertransformator.h"

D_MAKRO_FourierTransformator::D_MAKRO_FourierTransformator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::D_MAKRO_FourierTransformator)
{
    ui->setupUi(this);
}

D_MAKRO_FourierTransformator::~D_MAKRO_FourierTransformator()
{
    delete ui;
}

void D_MAKRO_FourierTransformator::closeEvent(QCloseEvent *event)
{
    if(ClosingPossible)
    {
        delete ui;
        event->accept();
    }
    else
    {
        event->ignore();
        this->showMinimized();
    }
}

void D_MAKRO_FourierTransformator::resizeEvent(QResizeEvent *event)
{
    event->accept();
    //Update_Views();
}

void D_MAKRO_FourierTransformator::Update_Ui()
{
    bool en_in = this->isEnabled();
    if(en_in)
        this->setEnabled(false);

    this->repaint();
    qApp->processEvents();

    if(en_in)
        this->setEnabled(true);
}
