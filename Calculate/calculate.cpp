#include "calculate.h"
#include <QGridLayout>
#include <QRegularExpression>

Calculate::Calculate(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Calculator");
    this->resize(230, 200);

    m_plcd = new QLCDNumber(12, this);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);

    QChar aButtons[4][4] = {{'7', '8', '9', '/'},
                            {'4', '5', '6', '*'},
                            {'1', '2', '3', '-'},
                            {'0', '.', '=', '+'}};

    QGridLayout *ptopLayout = new QGridLayout(this);
    ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);
    ptopLayout->addWidget(createButton("CE"), 1, 3);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
          ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
    }

    setLayout(ptopLayout);
}

QPushButton* Calculate::createButton(const QString &str)
{
    QPushButton *pcmd = new QPushButton(str, this);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, &QPushButton::clicked, this, &Calculate::slotButtonCLicked);

    return pcmd;
}

void Calculate::calculate()
{
    qreal fOperand2      = m_stk.pop().toFloat();
    QString strOperation = m_stk.pop();
    qreal fOperand1      = m_stk.pop().toFloat();
    qreal fResult        = 0;

    if (strOperation == "+")
      fResult = fOperand1 + fOperand2;

    else if (strOperation == "-")
      fResult = fOperand1 - fOperand2;

    else if (strOperation == '/')
      fResult = fOperand1 / fOperand2;

    else if (strOperation == "*")
      fResult = fOperand1 * fOperand2;

    m_plcd->display(fResult);
}

void Calculate::slotButtonCLicked()
{
    QString str = static_cast<QPushButton*>(sender())->text();

    if (str == "CE")
    {
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");

        return;
    }

    if (str.contains(QRegularExpression("[0-9]")))
    {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }

    else if (str == ".")
    {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay);
    }

    else
    {
        if (m_stk.count() >= 2)
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            calculate();
            m_stk.clear();
            m_stk.push(QString().setNum(m_plcd->value()));

            if (str != "=")
              m_stk.push(str);
        }

        else
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push(str);
            m_strDisplay = "";
        }
    }
}
