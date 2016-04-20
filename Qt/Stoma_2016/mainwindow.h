#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTimer>
#include <vector>
#include <QDateEdit>
#include <QListWidget>
#include <QSortFilterProxyModel>

#include "dialogsearchpacient.h"
#include "dialogadddateview.h"
#include "mysortfilterproxymodel.h"
#include "myqlabel.h"
#include "myqtextedit.h"

struct imageOfTeeth {
    int id_inc;
    int id;
    QDate dateView;
    QString status;
    QByteArray blob;

    imageOfTeeth(int id_i, int i, QDate d, QString s, QByteArray b) {
        id_inc   = id_i;
        id       = i;
        dateView = d;
        status   = s;
        blob     = b;
    }
};

namespace Ui {
class MainWindow;
}


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::vector<MyQLabel *> m_lblWithTeeth;
    std::vector<QImage>     m_imgOfTeeth;

    MySortFilterProxyModel *proxyModel;
    QSqlTableModel         *m_modelClients;
    QSqlTableModel         *modelBlogDoctor;
    QModelIndex             selectedIndexInDataView;
    MyQTextEdit            *textEdit_DateViewMore;
    const QString           m_sNoImage = ":/imgs/imgs/default.png";
    int                     iSelectPacient;

    //
    MyQTextEdit            *m_textEdit_diagnosis;
    MyQTextEdit            *m_textEdit_bite;
    MyQTextEdit            *m_textEdit_zax1;
    MyQTextEdit            *m_textEdit_conditionOfTheOral;

    MyQTextEdit            *m_textEdit_complaints;
    MyQTextEdit            *m_textEdit_zax2;
    MyQTextEdit            *m_textEdit_xrayExam;
    MyQTextEdit            *m_textEdit_Vita;

    MyQTextEdit            *m_lineEdit_sName;
    MyQTextEdit            *m_textEdit_ContactInfo;
    MyQTextEdit            *m_textEdit_status;
    QDateEdit              *m_date_Training;

    dialogsearchpacient    *m_dsp;                      // Діалог пошуку пацієнта
    dialogAddDateView      *m_dlgAddDateView;   //

    QList<imageOfTeeth *>   m_imgsTeeths;

    QListWidget             *m_lwgt;

    void loadInfoIncomboBoxType();
    void loadImgsTeethsInLabels();
    void initComboBoxOfTeeth();
    void loadForComponentContextMenu();

    void loadFromDB();                     // Завантаження даних з БД в компоненту
    bool m_firstStart;
    bool checkCorrectCharacterInName(const QString &text);
private slots:
    void slotAddPacient();
    void slotSearchPacient(int id);
    void slotOpenDialogSearch();
    void slotChangePhoto();
    void slotDeletePacient();
    void slotDeletePhoto();
    void slotDeleteInfoFromDataView();
    void slotUpdateBadTeeth(int nOfBad);
    void slotDeleteTeethImg();
    void slotDeleteTeeth();

    void slotPaintRectInTeeth();        // Замальовування частин зуба різними кольорами

    void slotAddTeethImages();
    void slotDownloadTeethImgsSelectedPacient(int currentTeeth);
    void slotShowMoreInfoATeeth(QListWidgetItem *);

    void slotShowTeethInListWidget(int ci);

    void slotUpdateStatusOfTeeth();
    void slotUpdateDateOfTeeth(QDate);
    // Tab3
    void slotUpdateDateViewMore();
    void slotOpenDialogAddDataView();
    void slotAddDateView(QDate, QString);

    void slotUpdateInfoAboutClient();
    void slotDownloadDataInComponentTab1(QModelIndex index);
    void slotDownloadDataInComponentTab2(QModelIndex index);
    void slotDownloadDataInComponentTab3(QModelIndex index);
};

#endif // MAINWINDOW_H
