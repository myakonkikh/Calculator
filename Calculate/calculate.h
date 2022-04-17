#ifndef CALCULATE_H
#define CALCULATE_H

#include <QWidget>
#include <QStack>
#include <QLCDNumber>
#include <QPushButton>

class Calculate : public QWidget
{
    Q_OBJECT

private:
    QLCDNumber    *m_plcd;
    QStack<QString> m_stk;
    QString  m_strDisplay;

public:
    explicit Calculate(QWidget *parent = nullptr);
    QPushButton* createButton(const QString &str);
    void calculate();

public slots:
    void slotButtonCLicked();
};

#endif // CALCULATE_H
