#include "barchart.h"
#include <QDebug>
#include <QFile>
#include <QGridLayout>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <algorithm>
#include <cmath>

barChart::barChart(QWidget *parent)
    : QMainWindow(parent)
{
    m_chkboxIsChecked = false;

    for (int i = 0; i < 32; i++)
        m_numbers.push_back(i);

    m_centralWgt = new QWidget();
    m_hbox       = new QGridLayout();
    m_ploter     = new QCustomPlot();

    m_cbbox  = new QComboBox();

    m_cbbox->addItem(QString("Lb1_24_1.prn"));
    m_cbbox->addItem(QString("Lb1_24_2.prn"));

    QObject::connect(m_cbbox, SIGNAL(currentIndexChanged(QString)), this, SLOT(slotPaintHistogram(QString)));
    emit slotPaintHistogram(m_cbbox->currentText());

    QLabel *lblChooseFile = new QLabel("Виберіть файл:");

    lblChooseFile->setMaximumSize(100, 15);
    lblChooseFile->setMinimumSize(100, 15);

    m_cbbox->setMaximumSize(110, 25);
    m_cbbox->setMinimumSize(110, 25);

    m_hbox->addWidget(m_ploter     , 0, 0, 26, 1, Qt::AlignTop);
    m_hbox->addWidget(lblChooseFile, 0, 1);
    m_hbox->addWidget(m_cbbox        , 1, 1, 1, 1, Qt::AlignTop);

    m_centralWgt->setLayout(m_hbox);
    this->setCentralWidget(m_centralWgt);

    m_ploter->setFixedSize(700,480);
    this->setFixedSize(850, 500);
}

barChart::~barChart() {
    m_ploter->clearPlottables();
    m_H.clear();
    m_n.clear();
    m_v.clear();
    m_pStar.clear();
    m_numbers.clear();
    m_P.clear();
}

bool barChart::readFromFile(const QString fileName, QVector<double> &m_vnumbers) {
    QFile f(fileName);
    if (!f.exists()) {
        qDebug() << "File not exists;";
        return 0;
    }

    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Error open!";
        return 0;
    }
    QTextStream in(&f);

    int pos = 0;
    while(!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        m_vnumbers[pos++] = line.toDouble();
    }
    return 1;
}

quint8 barChart::searchValues(int index) {
    m_a = *std::min_element(m_v.begin(), m_v.end());    // Мінімальне та максимальне
    m_b = *std::max_element(m_v.begin(), m_v.end());    // значення яке знаходиться в m_x
    m_R = m_b - m_a;     // Розмах варіювання
    m_h = m_R / m_m;     // Інтервал
    m_H[0]  = m_a;
    m_H[m_m] = m_b;

    for (int i = 1; i < m_m; ++i) {
        m_H[i] = m_H[i-1] + m_h;  // Знаходимо дельту
    }

    for (int i = 0; i < m_m; ++i) {
        m_n[i] = 0;
        for (int j = 0; j < m_CNT_NUMBERS; ++j) {
            if( (m_v[j] > m_H[i]) && (m_v[j] <= m_H[i+1]) ) {
                m_n[i] += 1;                // Кількість елементів котрі належать i-му інтервалу
            }
        }
    }
    m_n[m_m-1] += 1;

    for (int i = 0; i < m_m-1; ++i)
        m_pStar[i] = m_n[i] / (m_CNT_NUMBERS * m_h); // Емпірична щільність на кожному з інтервалів "i"


    quint8 s = 0;
    // Параметри гіпотетичних розподілів
    if (index == 1) {
        s = 2;
        for (int i = 0; i < m_m-1; ++i) {
            m_P[i] = m_h / (m_b - m_a);                                 // для рівномірного
        }
    } else {
        s = 1;
        double sum = std::accumulate(m_v.begin(), m_v.end(), 0);
        m_l = m_CNT_NUMBERS / sum;

        for (int i = 0; i < m_m; ++i) {
            m_P[i] = exp(-1 * m_l * m_H[i]) - exp(-1 * m_l * m_H[i+1]); // для експотенційного
        }
    }

    for (int i = 0; i < m_m-1; ++i) {
        m_hi[i] = pow(m_n[i] - m_CNT_NUMBERS * m_P[i], 2)/(m_CNT_NUMBERS * m_P[i]);
    }

    m_r = m_m - s - 1;

    double xi2t = 0.0;
    switch (m_r) {
        case 20:
                xi2t = 31.11;
            break;
        case 22:
                xi2t = 33.92;
            break;
        case 24:
                xi2t = 36.42;
            break;
        case 26:
                xi2t = 38.89;
            break;
        case 27:
                xi2t = 40.11;
            break;
        case 28:
                xi2t = 41.34;
            break;
        case 30:
                xi2t = 43.77;
            break;
    }
    double xi2 = std::accumulate(m_hi.begin(), m_hi.end(), 0);

//    qDebug() << "xi2 = " << xi2 << "; xi2t = " << xi2t;
    if (xi2 == xi2t) {
        return 0;
    } else {
        return 1;
    }
}

void barChart::slotPaintHistogram(const QString FILENAME) {
    m_H.clear();                           // Очищення від попередніх даних
    m_n.clear();
    m_v.clear();
    m_pStar.clear();
    m_P.clear();
    m_pCircumflex.clear();
    m_H.resize(m_m+1);
    m_n.resize(m_m);
    m_v.resize(m_CNT_NUMBERS);
    m_pStar.resize(m_m);
    m_pCircumflex.resize(m_m);
    m_P.resize(m_m);
    m_hi.resize(m_m);
    m_ploter->clearPlottables();            // Очищення полотна на якому буде малюватися гісторамма

    if (!readFromFile(FILENAME, m_v)) {     // Якщо не можливо зчитати файл у вектор, тоді
        return;                             // виходимо із слоту
    }


    QString hypothesis = "";
    if (searchValues(m_cbbox->currentIndex()) == 0) {
        hypothesis = "H0: послідовність чисел має щільність розподілу p(x);";
    } else {
        hypothesis = "H1: послідовність чисел не є розподіленою з щільністю p(x);";
    }

    QCPGraph *graph = m_ploter->addGraph(m_ploter->xAxis, m_ploter->yAxis);
    graph->setData(m_numbers, m_pStar);
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    graph->setPen(QPen(QColor(120, 120, 120), 2));
    graph->setName(hypothesis);
    fossil = new QCPBars(m_ploter->xAxis, m_ploter->yAxis);
    m_ploter->addPlottable(fossil);
    fossil->setWidth(1.0);

    QPen pen;
    pen.setColor(QColor(255, 255, 255));                // Колір контура стовпця
    fossil->setPen(pen);
    fossil->setBrush(QColor(50, 50, 250, 134));         //  Колір стовпця та 4-параметр - прозорість кольору

    // Встановленння значень по осі X
    QVector<QString> labels;
    for (int i = 0; i < m_numbers.size(); ++i)
        labels << QString::number(m_numbers.at(i));

    m_ploter->xAxis->setAutoTicks(false);
    m_ploter->xAxis->setAutoTickLabels(false);
    m_ploter->xAxis->setTickVector(m_numbers);
    m_ploter->xAxis->setTickVectorLabels(labels);
    m_ploter->xAxis->setSubTickCount(0);
    m_ploter->xAxis->setTickLength(0, 4);
    m_ploter->xAxis->grid()->setVisible(true);
    m_ploter->xAxis->setRange(0, m_numbers.size());

    // Встановленння значень по осі X
    m_ploter->xAxis->setLabel("x");
    m_ploter->yAxis->setRange(m_a, m_b);
    m_ploter->yAxis->setPadding(5);
    m_ploter->yAxis->setLabel(QString::fromUtf8("p*(x)"));
    m_ploter->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    m_ploter->xAxis->setLabelColor(Qt::white);
    m_ploter->yAxis->setLabelColor(Qt::white);
    m_ploter->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    m_ploter->yAxis->grid()->setSubGridPen(gridPen);

    fossil->setData(m_numbers, m_pStar);
    fossil->setName(QString::fromUtf8("Гістограмма"));          // Опис легенди

    m_ploter->legend->setVisible(true);                         // Видимість
    m_ploter->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter); // Розміщення
    m_ploter->legend->setBrush(QColor(255, 255, 255, 200));     // Колір закраски
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    m_ploter->legend->setBorderPen(legendPen);                  // Колір границь прямокутника в якому знаходитья легенда
    QFont legendFont = this->font();
    legendFont.setPointSize(10);
    m_ploter->legend->setFont(legendFont);
    m_ploter->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // Дозвіл на маштабування та прокрутку графіка

    // set some pens, brushes and backgrounds:
    m_ploter->xAxis->setBasePen(QPen(Qt::white, 1));
    m_ploter->yAxis->setBasePen(QPen(Qt::white, 1));
    m_ploter->xAxis->setTickPen(QPen(Qt::white, 1));
    m_ploter->yAxis->setTickPen(QPen(Qt::white, 1));
    m_ploter->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_ploter->yAxis->setSubTickPen(QPen(Qt::white, 1));
    m_ploter->xAxis->setTickLabelColor(Qt::white);
    m_ploter->yAxis->setTickLabelColor(Qt::white);
    m_ploter->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_ploter->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_ploter->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_ploter->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_ploter->xAxis->grid()->setSubGridVisible(true);
    m_ploter->yAxis->grid()->setSubGridVisible(true);
    m_ploter->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_ploter->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_ploter->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);   // Стрілки в кінці x
    m_ploter->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);   // y
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    m_ploter->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    m_ploter->axisRect()->setBackground(axisRectGradient);

    m_ploter->rescaleAxes();
    m_ploter->replot();                                         // Оновлення полотна
}
