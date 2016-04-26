#ifndef BARCHART_H
#define BARCHART_H

#include <QMainWindow>
#include <QVector>
#include "qcustomplot.h"

class QWidget;
class QGridLayout;
class QCheckBox;

class barChart : public QMainWindow {
        Q_OBJECT
    public:
        barChart(QWidget *parent = 0);
        ~barChart();
        bool readFromFile(const QString fileName, QVector<double> &m_H);
        quint8 searchValues(int index);

    private:
        QWidget         *m_centralWgt;
        QCustomPlot     *m_ploter;   // Полотно для рисования
        QCPBars         *fossil;
        QGridLayout     *m_hbox;
        QComboBox       *m_cbbox;

        QVector<double> m_H;
        QVector<double> m_n;
        QVector<double> m_pCircumflex;
        QVector<double> m_pStar;    // Висота стовпця гістограми
        QVector<double> m_v;        // Елементи з зчитанні з файлу
        QVector<double> m_numbers;
        QVector<double> m_P;
        QVector<double> m_hi;

        static const int m_CNT_NUMBERS = 1001;
        static const int m_m = 30;
        int m_r;
        bool   m_chkboxIsChecked;
        double m_R;
        double m_a;
        double m_b;
        double m_h;             // Ширина стовпця гістограми
        double m_l;

    private slots:
        void slotPaintHistogram(const QString FILENAME);
};
#endif // BARCHART_H
