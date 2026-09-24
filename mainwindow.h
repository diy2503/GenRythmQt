#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qabstractbutton.h>

#include "CBar.hpp"
#include "QBar.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void updateTempo(void);

private slots:
    void on_BtnPlay_clicked();
    void on_BtnStop_clicked();
    void on_BtnGenerate_clicked();
    void on_BtnLoad_clicked();
    void on_BtnSave_clicked();
    void on_ChkLoop_checkStateChanged(const Qt::CheckState &arg1);
    void on_SbTempo_valueChanged(int arg1);
    void on_Rd8Notes_toggled(bool checked);
    void on_Rd16Notes_toggled(bool checked);
    void on_ChkLinear_checkStateChanged(const Qt::CheckState &arg1);

    void updateWidgets();

private:
    Ui::MainWindow* ui;
    CBarPtr         m_pbar;
    QBarPtr         m_pBarView;
};
#endif // MAINWINDOW_H
