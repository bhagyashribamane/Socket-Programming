#ifndef LEARNDIALOG_H
#define LEARNDIALOG_H

#include <QDialog>
#include<QTabWidget>

namespace Ui {
class LearnDialog;
}

class LearnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LearnDialog(QWidget *parent = nullptr);
    ~LearnDialog();
signals:
    void learnValueChanged(QString value);
public slots:
    void IncomingValue(QString value);

private slots:
    void TeachClicked();
    void ClearClicked();
    void closeClicked();

private:
    Ui::LearnDialog *ui;
    QString taughtValue;
     int goodCount = 0;
     int badCount = 0;
     int totalCount = 0;

     void updateCounters();
     void addToHistory(QString value, bool isMatch);
};

#endif // LEARNDIALOG_H
