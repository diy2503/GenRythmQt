#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QPlayer.hpp"
#include "QBar.hpp"
#include <fstream>
#include <QTimer>
#include <QFileDialog>

#define LABEL_PLAY          "Play"
#define LABEL_PAUSE         "Pause"
#define LABEL_GENERATE      "Generate"

#define FILE_DIALOG_CAPTION_SAVE    "Save Rythm"
#define FILE_DIALOG_CAPTION_LOAD    "Load Rythm"
#define FILE_DIALOG_FILTER          "*.genrythm"

#define TEMPO_TIMER_TIMEOUT    1000     // Tempo value change timeout


#define QNOTE(instr, idx) static_cast<QNote*>(ui->instr##_##idx)


using Qt::CheckState::Checked;
using Qt::CheckState::Unchecked;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pbar(nullptr)
    , m_pBarView(nullptr)
{
    // CBar allocation
    m_pbar = make_shared<CBar>();

    ui->setupUi(this);

    // UI connections
    connect(ui->btnPlay,        SIGNAL(clicked()),                          this,   SLOT(on_BtnPlay_clicked()));
    connect(ui->btnStop,        SIGNAL(clicked()),                          this,   SLOT(on_BtnStop_clicked()));
    connect(ui->btnGenerate,    SIGNAL(clicked()),                          this,   SLOT(on_BtnGenerate_clicked()));
    connect(ui->btnLoad,        SIGNAL(clicked()),                          this,   SLOT(on_BtnLoad_clicked()));
    connect(ui->btnSave,        SIGNAL(clicked()),                          this,   SLOT(on_BtnSave_clicked()));
    connect(ui->chkLoop,        SIGNAL(checkStateChanged(Qt::CheckState)),  this,   SLOT(on_ChkLoop_checkStateChanged(const Qt::CheckState &)));
    connect(ui->sbTempo,        SIGNAL(valueChanged(int)),                  this,   SLOT(on_SbTempo_valueChanged(int)));
    connect(ui->rd8Notes,       SIGNAL(toggled(bool)),                      this,   SLOT(on_Rd8Notes_toggled(bool)));
    connect(ui->rd16Notes,      SIGNAL(toggled(bool)),                      this,   SLOT(on_Rd16Notes_toggled(bool)));
    connect(ui->chkLinear,      SIGNAL(checkStateChanged(Qt::CheckState)),  this,   SLOT(on_ChkLinear_checkStateChanged(const Qt::CheckState)));


    //// UI state initialization
    // Checkbox loop
    ui->chkLoop->setCheckState(QPlayer::getInstance().getLoop()? Checked : Unchecked);

    // Spinbox tempo
    ui->sbTempo->setValue(CPlayer::getInstance().getTempo());

    // QPlayer connections
    qRegisterMetaType<QPlayer>();
    connect(&QPlayer::getInstance(),    SIGNAL(statusChanged(ePlayStatus)), this,   SLOT(updateWidgets()));

    // CH Pattern
    ChPattern pattern = m_pbar->getChPattern();
    ui->rd8Notes->setChecked((pattern == ChPattern::HEIGHT_NOTES) || (pattern == ChPattern::LINEAR_HEIGHT));
    ui->rd16Notes->setChecked((pattern == ChPattern::SIXTEEN_NOTES) || (pattern == ChPattern::LINEAR_SIXTEEN));
    ui->chkLinear->setCheckState(((pattern == ChPattern::LINEAR_HEIGHT) || (pattern == ChPattern::LINEAR_SIXTEEN))? Checked : Unchecked);

    // Bar view
    m_pBarView = make_shared<QBar>(ui->layoutBar);

    updateWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateWidgets()
{
    auto playerStatus = QPlayer::getInstance().getStatus();

    // Buttons text and enabling
    ui->btnPlay->setText((playerStatus == ePlayStatus_play)? LABEL_PAUSE : LABEL_PLAY);
    ui->btnPlay->setEnabled(! m_pbar->isEmpty());
    ui->btnStop->setEnabled(playerStatus != ePlayStatus_stop);
    // ui->btnLoad->setEnabled(playerStatus == ePlayStatus_stop);

    // Display bar
    string str;
    m_pbar->toString(str);
    ui->lbBar->setText(QString(str.c_str()));

    m_pBarView->Display(m_pbar);
}

void MainWindow::on_BtnPlay_clicked()
{
    QPlayer &player = QPlayer::getInstance();

    switch (player.getStatus())
    {
    case ePlayStatus_play:
    {
        player.Pause();
        break;
    }
    case ePlayStatus_pause:
    {
        player.Resume();
        break;
    }
    default:
    case ePlayStatus_stop:
    {
        if (m_pbar->isEmpty())
        {
            m_pbar->Fill();
        }

        player.Play(m_pbar);
        break;
    }

    }
}


void MainWindow::on_BtnStop_clicked()
{
    QPlayer::getInstance().Stop();
}


void MainWindow::on_BtnGenerate_clicked()
{
    // Stop playback
    QPlayer::getInstance().Stop();

    // Generate a new bar
    m_pbar->Fill();

    // Automatic playback restart
    on_BtnPlay_clicked();
}

void MainWindow::on_BtnLoad_clicked()
{
    // Open File dialog box
    QString filename = QFileDialog::getOpenFileName(this,
                                                    FILE_DIALOG_CAPTION_LOAD,
                                                    nullptr,
                                                    FILE_DIALOG_FILTER);

    if (!filename.isNull() && !filename.isEmpty())
    {
        // Stop playback
        QPlayer::getInstance().Stop();

        // Read file
        ifstream inFile(filename.toStdString(), ios::binary);
        m_pbar->Deserialize(inFile);
        inFile.close();

        // Start playback
        QPlayer::getInstance().Play(m_pbar);
    }
}

void MainWindow::on_BtnSave_clicked()
{
    // Save File dialog box
    QString filename = QFileDialog::getSaveFileName(this,
                                                    FILE_DIALOG_CAPTION_SAVE,
                                                    nullptr,
                                                    FILE_DIALOG_FILTER);

    if (!filename.isNull() && !filename.isEmpty())
    {
        // Serialize Bar
        ofstream outFile(filename.toStdString(), ios::binary);
        m_pbar->Serialize(outFile);
        outFile.close();
    }
}



void MainWindow::on_ChkLoop_checkStateChanged(const Qt::CheckState &arg1)
{
    bool bLoop = (arg1 == Checked);
    QPlayer::getInstance().setLoop(bLoop);
}


void MainWindow::updateTempo()
{
    QPlayer::getInstance().setTempo(ui->sbTempo->value());
}


void MainWindow::on_SbTempo_valueChanged(int arg1)
{
    if (arg1 > 0)
    {
        QTimer::singleShot(TEMPO_TIMER_TIMEOUT, this, &MainWindow::updateTempo);
    }
}


void MainWindow::on_Rd8Notes_toggled(bool checked)
{
    if (checked == true)
    {
        ChPattern pattern = ChPattern::HEIGHT_NOTES;

        if (ui->chkLinear->checkState() == Checked)
        {
            pattern = ChPattern::LINEAR_HEIGHT;
        }

        // Pause playback before change the CH pattern
        QPlayer::getInstance().Pause();

        // Change pattern
        m_pbar->setChPattern(pattern);

        // Resume playback
        QPlayer::getInstance().Resume();
    }
}


void MainWindow::on_Rd16Notes_toggled(bool checked)
{
    if (checked == true)
    {
        ChPattern pattern = ChPattern::SIXTEEN_NOTES;

        if (ui->chkLinear->checkState() == Checked)
        {
            pattern = ChPattern::LINEAR_SIXTEEN;
        }

        // Pause playback before change the CH pattern
        QPlayer::getInstance().Pause();

        // Change pattern
        m_pbar->setChPattern(pattern);

        // Resume playback
        QPlayer::getInstance().Resume();
    }
}


void MainWindow::on_ChkLinear_checkStateChanged(const Qt::CheckState &arg1)
{
    bool        linear  = (arg1 == Checked);
    ChPattern   pattern = m_pbar->getChPattern();

    switch (pattern)
    {
    case ChPattern::HEIGHT_NOTES:
    case ChPattern::LINEAR_HEIGHT:
    {
        pattern = (linear == true)? ChPattern::LINEAR_HEIGHT : ChPattern::HEIGHT_NOTES;
        break;
    }
    case ChPattern::SIXTEEN_NOTES:
    case ChPattern::LINEAR_SIXTEEN:
    {
        pattern = (linear == true)? ChPattern::LINEAR_SIXTEEN : ChPattern::SIXTEEN_NOTES;
        break;
    }
    default:
        break;
    }

    // Pause playback before change the CH pattern
    QPlayer::getInstance().Pause();

    // Change pattern
    m_pbar->setChPattern(pattern);

    // Resume playback
    QPlayer::getInstance().Resume();
}


