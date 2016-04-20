#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include  <QSqlDatabase>

#include <QPainter>
#include <QByteArray>
#include <QBuffer>
#include <QFile>

//#include <QtWidgets>

class MySortFilterProxyModel;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QString DATABASE_NAME = "dbteeth.db";

    m_lblWithTeeth.resize(32);
    m_imgOfTeeth.resize(32);

    QFile f(DATABASE_NAME);
    if (!f.exists()) {
        QMessageBox::critical(this,
                             this->windowTitle(),
                             "База даних не існує! Зверніться до адміністратора або розробника програми.");
        exit(0);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if (!db.open()) {
        QMessageBox::critical(this,
                             this->windowTitle(),
                             "Не можливо відкрити базу даних!");
        return;
    }
    this->setFixedSize(820, 700);

    m_modelClients = new QSqlTableModel(this, db);
    modelBlogDoctor = new QSqlTableModel(this, db);

    // GrLay_T1_Down
    m_textEdit_diagnosis    = new MyQTextEdit();
    m_textEdit_bite         = new MyQTextEdit();
    m_textEdit_zax1         = new MyQTextEdit();
    m_textEdit_complaints   = new MyQTextEdit();
    m_textEdit_zax2         = new MyQTextEdit();
    m_textEdit_Vita         = new MyQTextEdit();
    m_textEdit_xrayExam     = new MyQTextEdit();

    m_lineEdit_sName        = new MyQTextEdit();
    m_textEdit_ContactInfo  = new MyQTextEdit();
    m_textEdit_status       = new MyQTextEdit(); // 2 vkladka

    m_textEdit_diagnosis->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_diagnosis->setMaximumHeight(40);

    m_textEdit_zax2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_zax2->setMaximumHeight(40);

    m_textEdit_bite->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_bite->setMaximumHeight(40);

    m_textEdit_zax1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_zax1->setMaximumHeight(40);

    m_textEdit_complaints->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_complaints->setMaximumHeight(40);

    m_textEdit_zax2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_zax2->setMaximumHeight(40);

    m_textEdit_Vita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_Vita->setMaximumHeight(40);

    m_textEdit_xrayExam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_xrayExam->setMaximumHeight(40);

    m_textEdit_ContactInfo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_ContactInfo->setMaximumHeight(100);

    ui->gridLayout_2->addWidget(m_lineEdit_sName,1,0,1,2);
    ui->gridLayout_2->addWidget(m_textEdit_ContactInfo,4,0,1,2);
    m_lineEdit_sName->setMaximumHeight(25);

    m_textEdit_conditionOfTheOral = new MyQTextEdit();
    m_textEdit_conditionOfTheOral->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_textEdit_conditionOfTheOral->setMaximumHeight(40);

    m_date_Training = new QDateEdit();
    m_date_Training->setDisplayFormat("dd-MM-yyyy");
    m_date_Training->setCalendarPopup(true);

    ui->GrLay_T1_Down->addWidget(new QLabel("Дата навчання навичкам гігієни порожнини рота:"), 1,1,1,1);
    ui->GrLay_T1_Down->addWidget(m_date_Training, 1,2,1,1);

    ui->GrLay_T1_Down->addWidget(new QLabel("Діагноз:"), 2,1,1,1);
    ui->GrLay_T1_Down->addWidget(m_textEdit_diagnosis,   3,1,1,1);

    ui->GrLay_T1_Down->addWidget(new QLabel("Прикус:"), 4,1,1,1);
    ui->GrLay_T1_Down->addWidget(m_textEdit_bite,  5,1,1,1);

    ui->GrLay_T1_Down->addWidget(new QLabel("Перенесенні та супутні захворювання:"), 6,1,1,1);
    ui->GrLay_T1_Down->addWidget(m_textEdit_zax1, 7,1,1,1);

    QLabel *lbl = new QLabel("Стан слизової оболонки порожнини рота, ясен, альвеолярних відростків та піднебіння, Індекси ГІ та РМА. Гігієна порожнини рота:");
    lbl->setWordWrap(true);
    ui->GrLay_T1_Down->addWidget(lbl, 8,1,1,1);
    ui->GrLay_T1_Down->addWidget(m_textEdit_conditionOfTheOral, 9,1,1,1);

    ui->GrLay_T1_Down->addWidget(new QLabel("Розвиток теперішнього захворювання:"), 2,2,1,1);
    ui->GrLay_T1_Down->addWidget(m_textEdit_zax2, 3,2,1,1);

    ui->GrLay_T1_Down->addWidget(new QLabel("Скарги:"), 4,2,1,1);
    ui->GrLay_T1_Down->addWidget(m_textEdit_complaints, 5,2,1,1);

    ui->GrLay_T1_Down->addWidget(new QLabel("Дані рентгенівських обстежень, лабораторних досліджень:"), 6,2,1,1);
    ui->GrLay_T1_Down->addWidget(m_textEdit_xrayExam, 7,2,1,1);

    ui->GrLay_T1_Down->addWidget(new QLabel("Колір за шкалою \"Vita\":"), 8,2,1,1, Qt::AlignBottom);
    ui->GrLay_T1_Down->addWidget(m_textEdit_Vita, 9,2,1,1);

    ui->tableView_listOfPeople->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_listOfPeople->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_DateView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_DateView->setSelectionBehavior(QAbstractItemView::SelectRows);

    textEdit_DateViewMore = new MyQTextEdit();
    ui->verticalLayout_7->addWidget(textEdit_DateViewMore);

    //
    m_lwgt = new QListWidget(this);
    m_lwgt->resize(225, 258);
    ui->gridLayout_photoOfTeeth->addWidget(m_lwgt, 1, 1, 3, 1);
    ui->gridLayout_photoOfTeeth->addWidget(m_textEdit_status, 1, 6, 3, 1);
    QObject::connect(m_textEdit_status, SIGNAL(signalLeave()), SLOT(slotUpdateStatusOfTeeth()));

    // Инициализация
    initComboBoxOfTeeth();

    // Вкладка 1
    loadInfoIncomboBoxType();
    loadFromDB();

    // Вкладка 2
    loadForComponentContextMenu();

    //
    m_textEdit_complaints->setObjectName("m_textEdit_complaints");
    m_textEdit_zax2->setObjectName("m_textEdit_zax2");
    m_textEdit_zax1->setObjectName("m_textEdit_zax1");
    m_textEdit_Vita->setObjectName("m_textEdit_Vita");
    m_textEdit_xrayExam->setObjectName("m_textEdit_xrayExam");
    m_textEdit_diagnosis->setObjectName("m_textEdit_diagnosis");
    m_textEdit_bite->setObjectName("m_textEdit_bite");
    m_textEdit_conditionOfTheOral->setObjectName("m_textEdit_conditionOfTheOral");
    m_date_Training->setObjectName("m_date_Training");
    ui->comboBox_Type->setObjectName("comboBox_Type");
    ui->dateDOB->setObjectName("dateDOB");

    m_lineEdit_sName->setObjectName("m_lineEdit_sName");
    m_textEdit_ContactInfo->setObjectName("m_textEdit_ContactInfo");

    // Відкрити діалог пошуку пацієнта
    QObject::connect(ui->pushButton_Search_Tab1, SIGNAL(clicked(bool)), SLOT(slotOpenDialogSearch()));

    m_dsp = new dialogsearchpacient();
    m_dlgAddDateView = new dialogAddDateView;

    emit slotShowTeethInListWidget(0);   //
    QObject::connect(ui->comboBox_nOfTeeth, SIGNAL(currentIndexChanged(int)), SLOT(slotShowTeethInListWidget(int)));

    QObject::connect(ui->pushButton_add, SIGNAL(clicked()), SLOT(slotAddTeethImages()));
    QObject::connect(ui->pushButton_remove, SIGNAL(clicked()), SLOT(slotDeleteTeeth()));

    QObject::connect(ui->dateEdit_dv, SIGNAL(dateChanged(QDate)), SLOT(slotUpdateDateOfTeeth(QDate)));

    QObject::connect(m_dsp, SIGNAL(sendData(int)), SLOT(slotSearchPacient(int)) );
    //
    QObject::connect(ui->pushButton_Add_Tab3, SIGNAL(clicked(bool)), SLOT(slotOpenDialogAddDataView()) );
    //
    QObject::connect(m_dlgAddDateView, SIGNAL(sendData(QDate,QString)), SLOT(slotAddDateView(QDate, QString)));

    QObject::connect(m_lineEdit_sName, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_ContactInfo, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));

    QObject::connect(m_textEdit_complaints, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_zax2, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_Vita, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_xrayExam, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_diagnosis, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_bite, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_zax1, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_textEdit_conditionOfTheOral, SIGNAL(signalLeave()), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(m_date_Training, SIGNAL(dateChanged(QDate)), SLOT(slotUpdateInfoAboutClient()));

    // Сигнали
    QObject::connect(textEdit_DateViewMore, SIGNAL(signalLeave()), SLOT(slotUpdateDateViewMore()));

    QObject::connect(ui->comboBox_Type, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateInfoAboutClient()));
    QObject::connect(ui->dateDOB, SIGNAL(dateChanged(QDate)), SLOT(slotUpdateInfoAboutClient()));

    QObject::connect(ui->tableView_listOfPeople, SIGNAL(clicked(QModelIndex)), SLOT(slotDownloadDataInComponentTab1(QModelIndex)));
    QObject::connect(ui->tableView_DateView    , SIGNAL(clicked(QModelIndex)), SLOT(slotDownloadDataInComponentTab3(QModelIndex)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadInfoIncomboBoxType() {
    ui->comboBox_Type->addItem("Чоловік");
    ui->comboBox_Type->addItem("Жінка");
}

void MainWindow::initComboBoxOfTeeth() {
    // Initialize comboBox
    QStringList list;
    list << "-"
         << "C" << "P"  << "Pt"  << "Lp"  << "Gp" << "R"
         << "A" << "Cd" << "Pl"  << "F"   << "ar" << "r"
         << "H" << "Am" << "res" << "pin" << "Rp" << "Dc";

    ui->badTeeth_11->addItems(list);
    ui->badTeeth_12->addItems(list);
    ui->badTeeth_13->addItems(list);
    ui->badTeeth_14->addItems(list);
    ui->badTeeth_15->addItems(list);
    ui->badTeeth_16->addItems(list);
    ui->badTeeth_17->addItems(list);
    ui->badTeeth_18->addItems(list);

    ui->badTeeth_21->addItems(list);
    ui->badTeeth_22->addItems(list);
    ui->badTeeth_23->addItems(list);
    ui->badTeeth_24->addItems(list);
    ui->badTeeth_25->addItems(list);
    ui->badTeeth_26->addItems(list);
    ui->badTeeth_27->addItems(list);
    ui->badTeeth_28->addItems(list);

    ui->badTeeth_31->addItems(list);
    ui->badTeeth_32->addItems(list);
    ui->badTeeth_33->addItems(list);
    ui->badTeeth_34->addItems(list);
    ui->badTeeth_35->addItems(list);
    ui->badTeeth_36->addItems(list);
    ui->badTeeth_37->addItems(list);
    ui->badTeeth_38->addItems(list);

    ui->badTeeth_41->addItems(list);
    ui->badTeeth_42->addItems(list);
    ui->badTeeth_43->addItems(list);
    ui->badTeeth_44->addItems(list);
    ui->badTeeth_45->addItems(list);
    ui->badTeeth_46->addItems(list);
    ui->badTeeth_47->addItems(list);
    ui->badTeeth_48->addItems(list);
}

void MainWindow::loadForComponentContextMenu() {
    QAction *addRec    = NULL,
            *deleteRec = NULL,
            *changeRec = NULL;

    // Контекстное меню для dateView(BlogDoctor)
    deleteRec = new QAction("&Видалити", this);
    connect(deleteRec, SIGNAL(triggered()), this, SLOT(slotDeleteInfoFromDataView()));
    ui->tableView_DateView->addAction(deleteRec);
    ui->tableView_DateView->setContextMenuPolicy(Qt::ActionsContextMenu);

//    addRec = new QAction(QIcon(":/build-QtStomaNotDemo-Desktop_Qt_5_4_2_MinGW_32bit-Debug/debug/images/btns/1.png"), "&Додати фотографію", this);

    // Фотографія пацієнта
    changeRec = new QAction("&Змінити фотографію", this);
    changeRec->setObjectName("changeRec");
    connect(changeRec, SIGNAL(triggered()), this, SLOT(slotChangePhoto()));
    ui->img_photo->addAction(changeRec);

    deleteRec = new QAction("&Видалити фотографію", this);
    connect(deleteRec, SIGNAL(triggered()), this, SLOT(slotDeletePhoto()));
    ui->img_photo->addAction(deleteRec);
    ui->img_photo->setContextMenuPolicy(Qt::ActionsContextMenu);

    // Знімок зуба
    changeRec = new QAction("&Змінити фотографію", this);
    connect(changeRec, SIGNAL(triggered()), this, SLOT(slotChangePhoto()));
    ui->lbl_photoOfTeeth->addAction(changeRec);
    changeRec->setObjectName("lbl_photoOfTeeth");

    deleteRec = new QAction("&Видалити фотографію", this);
    connect(deleteRec, SIGNAL(triggered()), this, SLOT(slotDeleteTeethImg()));
    ui->lbl_photoOfTeeth->addAction(deleteRec);
    ui->lbl_photoOfTeeth->setContextMenuPolicy(Qt::ActionsContextMenu);

    // Контекстное меню для tableView_listOfPeople
    addRec = new QAction("&Нова картка", this);
    connect(addRec, SIGNAL(triggered()), this, SLOT(slotAddPacient()) );
    ui->tableView_listOfPeople->addAction(addRec);

    deleteRec = new QAction("&Видалити", this);
    connect(deleteRec, SIGNAL(triggered()), this, SLOT(slotDeletePacient()) );
    ui->tableView_listOfPeople->addAction(deleteRec);
    ui->tableView_listOfPeople->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::loadFromDB() {
    modelBlogDoctor->setEditStrategy(QSqlTableModel::OnFieldChange);

    m_modelClients->setTable("clients");
//    m_modelClients->sort(1, Qt::AscendingOrder); // сортировка имени по убиванию
    proxyModel = new MySortFilterProxyModel();
    proxyModel->setSourceModel(m_modelClients);
    m_modelClients->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_modelClients->select();
    proxyModel->sort(1, Qt::AscendingOrder);
    ui->tableView_listOfPeople->setModel(proxyModel);
    m_modelClients->setHeaderData(1, Qt::Horizontal, tr("ПІБ"));

    ui->tableView_listOfPeople->hideColumn(0);
    for (int i = m_modelClients->columnCount()-1; i > 1; --i)
        ui->tableView_listOfPeople->hideColumn(i);

    ui->tableView_listOfPeople->resizeColumnsToContents();
    ui->tableView_DateView->resizeColumnsToContents();
    ui->tableView_listOfPeople->verticalHeader()->hide();

    ui->tableView_listOfPeople->selectRow(0);
    emit slotDownloadDataInComponentTab1(proxyModel->mapToSource(proxyModel->index(0,0)));
}

bool MainWindow::checkCorrectCharacterInName(const QString &text) {
    if (text.isEmpty())
        return false;

    QString alphabet  = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";
            alphabet += "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";

    int sizeText = text.size();
    int sizeAlph = alphabet.size();
    for (int i = 0; i < sizeText; ++i) {
        int j = 0;
        for (; j < sizeAlph; ++j) {
            if (text[i] == alphabet[j])
                break;
        }
        if (j == sizeAlph)
            return false;
    }
    return true;
}

void MainWindow::slotAddPacient() {
    bool ok;
    QString text = QInputDialog::getText(this,
                                         tr("Додати пацієнта"),
                                         tr("Введіть Прізвище, імя та по-батькові:"), QLineEdit::Normal,
                                         "",
                                         &ok
    );

    if (!checkCorrectCharacterInName(text) || !ok) {
        QMessageBox::critical(this,
                              this->windowTitle(),
                              "Не введено ім'я або було використано не українську мову.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO clients(pib) VALUES ('" + text + "');");
    if (!query.exec()) {
        QMessageBox::critical(this,
                              this->windowTitle(),
                              "Помилка додавання пацієнта!");
        return;
    }

    loadFromDB();

    ui->tableView_listOfPeople->selectRow(m_modelClients->rowCount()-1);
    ui->tableView_listOfPeople->setCurrentIndex(ui->tableView_listOfPeople->currentIndex());
    emit slotDownloadDataInComponentTab1(ui->tableView_listOfPeople->currentIndex());
}

// Пошук пацієнта у БД
void MainWindow::slotSearchPacient(int id) {
    int rc = m_modelClients->rowCount();
    for (int i = 0; i < rc; ++i) {
        int t_id = m_modelClients->data(m_modelClients->index(i, 0)).toInt();
        if (t_id == id) {
            ui->tableView_listOfPeople->selectRow(i);
            emit slotDownloadDataInComponentTab1(ui->tableView_listOfPeople->currentIndex());
            break;
        }
    }
}

void MainWindow::slotOpenDialogSearch() {
    m_dsp->exec();              // Показати діалог пошуку пацієнта
    QObject::connect(m_dsp, SIGNAL(destroyed(QObject*)), SLOT(deleteLater()));
}

void MainWindow::slotChangePhoto() {
    QString sender = QObject::sender()->objectName(); // Отримуємо вказівник на обєкт,

    if (sender == "lbl_photoOfTeeth")
        if (!m_lwgt->count() || !m_lwgt->selectedItems().count())
            return;

                                                      // котрий викликав цей слот.
    QFileDialog fd;
    fd.setFileMode(QFileDialog::ExistingFile);
    QString pathToPhoto = fd.getOpenFileName(this, "Завантаження фототографії","", "Image files(*.jpg)");
    QImage yourImage;
    if (!yourImage.load(pathToPhoto)) {
        return;
    }

    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    yourImage.save( &buf, "JPG" );
    buf.close();

    QSqlQuery query;
    if (sender == "lbl_photoOfTeeth") {
        int id_img = m_lwgt->currentItem()->text().toInt();
        query.prepare("UPDATE photosofteeth SET photoOfTeeth=:photoOfTeeth WHERE id_inc=:id_inc;");
        query.bindValue(":photoOfTeeth", ba);
        query.bindValue(":id_inc", id_img);
        foreach (imageOfTeeth *it, m_imgsTeeths) {
            if (it->id_inc == id_img) {
                QPixmap p;
                    p = p.fromImage(yourImage);
                    ui->lbl_photoOfTeeth->setPixmap(p);
                    it->blob = ba;
                    m_lwgt->currentItem()->setIcon(p);
                break;
            }
        }
    } else {
        query.prepare("UPDATE clients SET photo=:photo WHERE id=:id;");
        query.bindValue(":photo", ba);
        query.bindValue(":id", this->iSelectPacient);
        QModelIndex i = m_modelClients->index(ui->tableView_listOfPeople->currentIndex().row(), 9);
        m_modelClients->setData(i, ba);
        QPixmap pixmap;
        pixmap.loadFromData(ba);
        ui->img_photo->setPixmap(pixmap);
        ba.clear();
    }

    if (!query.exec()) {
        qDebug() << query.lastError();
    }
}

void MainWindow::slotDeletePacient() {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Пацієнт буде видалений.");
    msgBox.setInformativeText("Ви хочете видалити пацієнта?");
                         msgBox.addButton(tr("Так"), QMessageBox::ActionRole);
    QPushButton *btnNo = msgBox.addButton(tr("Ні"), QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() == btnNo)
        return;

    QModelIndex ind = ui->tableView_listOfPeople->currentIndex();
    m_modelClients->removeRow(ind.row());
    m_modelClients->submitAll();
    if (ind.row() == 0)
        ui->tableView_listOfPeople->selectRow(0);
    else
        ui->tableView_listOfPeople->selectRow(ind.row() - 1);
    ui->tableView_listOfPeople->setCurrentIndex(ui->tableView_listOfPeople->currentIndex());

    QSqlQuery query;
    query.prepare("DELETE FROM photosofteeth WHERE id=(SELECT id_inc FROM numberofteeth WHERE id=:id);");
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    query.clear();
    query.prepare("DELETE FROM blogdoctor WHERE id=:id;");
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    query.prepare("DELETE FROM legendstateofteeth WHERE id=:id;");
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    query.prepare("DELETE FROM numberofteeth WHERE id=:id;");
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    query.prepare("DELETE FROM clients WHERE id=:id;");
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    emit slotDownloadDataInComponentTab1(ui->tableView_listOfPeople->currentIndex());
}

void MainWindow::slotDeletePhoto() {
    int row = ui->tableView_listOfPeople->currentIndex().row();
    QByteArray ba = m_modelClients->record(row).value(9).toByteArray();
    if (ba.isEmpty()) // Якщо немає фотографії,
        return;       // тоді виходимо з процедури.

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Знімок буде видалений.");
    msgBox.setInformativeText("Ви хочете видалити знімок?");
                         msgBox.addButton(tr("Так"), QMessageBox::ActionRole);
    QPushButton *btnNo = msgBox.addButton(tr("Ні"), QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() == btnNo)
        return;

    QModelIndex delPhoto = m_modelClients->index(row, 9); // 9 - поле зберігання фотографії

    m_modelClients->setData(delPhoto,"");
    m_modelClients->submitAll();

    QPixmap px(m_sNoImage);
    ui->img_photo->setPixmap(px);
    ui->tableView_listOfPeople->selectRow(row);
}

void MainWindow::slotDeleteInfoFromDataView() {
    if (modelBlogDoctor->rowCount() < 1) // Якщо немає записів, значить
        return;                          // немає, що видаляти.

    QMessageBox msgBox;
    msgBox.setWindowTitle(this->windowTitle());
    msgBox.setText("Дату огляду пацієнта буде видалена.");
    msgBox.setInformativeText("Ви хочете видалити дату огляду?");
                         msgBox.addButton(tr("Так"), QMessageBox::ActionRole);
    QPushButton *btnNo = msgBox.addButton(tr("Ні"), QMessageBox::ActionRole);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
    if (msgBox.clickedButton() == btnNo)
        return;

    bool state = modelBlogDoctor->removeRow(ui->tableView_DateView->currentIndex().row());
    if (!state) {
        QMessageBox::warning(this,
                             this->windowTitle(),
                             "Не можливо видалити запис!");
        return;
    }
    modelBlogDoctor->select();

    ui->tableView_DateView->selectRow(modelBlogDoctor->rowCount()-1);
    ui->tableView_DateView->setCurrentIndex(ui->tableView_DateView->currentIndex());
    emit slotDownloadDataInComponentTab3(ui->tableView_DateView->currentIndex());
}

void MainWindow::loadImgsTeethsInLabels() {
    for (int fn = 0, ln = 8, i = 0;
              i < 32; ++i)
    {
        if (i % 8 == 0) {
            ++fn;
            ln = 8;
        }
        m_lblWithTeeth[i] = new MyQLabel();
        QString name = QString::number(fn) + QString::number(ln);
        m_lblWithTeeth[i]->setObjectName(name);
        --ln;
    }

    // 18..16
    m_imgOfTeeth[0] .load(":/teeths/images/teeths/1b.png");
    m_imgOfTeeth[1] .load(":/teeths/images/teeths/1b.png");
    m_imgOfTeeth[2] .load(":/teeths/images/teeths/1b.png");
    // 15..14
    m_imgOfTeeth[3] .load(":/teeths/images/teeths/2b.png");
    m_imgOfTeeth[4] .load(":/teeths/images/teeths/2b.png");
    //
    m_imgOfTeeth[5] .load(":/teeths/images/teeths/3b.png");
    m_imgOfTeeth[6] .load(":/teeths/images/teeths/3b.png");
    m_imgOfTeeth[7] .load(":/teeths/images/teeths/3b.png");

    // 28..26
    m_imgOfTeeth[8] .load(":/teeths/images/teeths/1b.png");
    m_imgOfTeeth[9] .load(":/teeths/images/teeths/1b.png");
    m_imgOfTeeth[10].load(":/teeths/images/teeths/1b.png");
    // 25..24
    m_imgOfTeeth[11].load(":/teeths/images/teeths/2b.png");
    m_imgOfTeeth[12].load(":/teeths/images/teeths/2b.png");
    // 23..21
    m_imgOfTeeth[13].load(":/teeths/images/teeths/3b.png");
    m_imgOfTeeth[14].load(":/teeths/images/teeths/3b.png");
    m_imgOfTeeth[15].load(":/teeths/images/teeths/3b.png");

    for (int n = 0, i = 16;
             i < 32; ++i)
    {
        if (i < 19)
            n = 2;
        else if (i > 20 && i < 24)
            n = 3;
        else if (i > 23 && i < 27)
            n = 2;
        else if (i == 19 || i == 20 || i == 27 || i == 28) {
            m_imgOfTeeth[i].load(":/teeths/images/teeths/3br_u.png");
            continue;
        }
        else {
            n = 3;
        }
        m_imgOfTeeth[i].load(":/teeths/images/teeths/"+ QString::number(n) +".png");
    }
    //
    for (int i = 0; i < 32; ++i) {
        m_lblWithTeeth[i]->setPixmap(QPixmap::fromImage(m_imgOfTeeth[i], Qt::AutoColor));
    }

    int c = 0, r = 1, tpos = 0;
    for (int i = 0; i < 8; ++i) {
        ui->gridLayout_Teeth->addWidget(m_lblWithTeeth[tpos++], r, c++, 1, 1, Qt::AlignHCenter);
    }

    c = 15;
    for (int i = 0; i < 8; ++i) {
        ui->gridLayout_Teeth->addWidget(m_lblWithTeeth[tpos++], r, c--, 1, 1, Qt::AlignHCenter);
    }

    tpos = 24;
    r = 4;
    c = 0;
    for (int i = 0; i < 8; ++i) {
        ui->gridLayout_Teeth->addWidget(m_lblWithTeeth[tpos++], r, c++, 1, 1, Qt::AlignHCenter);
    }

    tpos = 23;
    for (int i = 0; i < 8; ++i) {
        ui->gridLayout_Teeth->addWidget(m_lblWithTeeth[tpos--], r, c++, 1, 1, Qt::AlignHCenter);
    }
}

// Завантажування даних в компоненти з БД, котрі знаходяться в 1-й та 2-й вкладці.
void MainWindow::slotDownloadDataInComponentTab1(QModelIndex index) {
//    qDebug() << "downloadDataInComponentTab1";
    index = proxyModel->mapToSource(ui->tableView_listOfPeople->currentIndex());
    int tSelectPac = iSelectPacient;
    iSelectPacient = m_modelClients->data(m_modelClients->index(index.row(), 0)).toInt();
//    qDebug() << "iSelectPacient = " << iSelectPacient;

    if (tSelectPac == iSelectPacient)
        return;

    QSqlQuery query;        // Исполнитель запросов
    int row = index.row();
    QByteArray baPhoto = this->m_modelClients->record(row).value("photo").toByteArray();
    baPhoto = this->m_modelClients->data(m_modelClients->index(row, 9)).toByteArray();
    QDate dob = this->m_modelClients->record(row).value("DOB").toDate(),                       // Дата народження
          dataTraining = this->m_modelClients->record(row).value("dataTraining").toDate();        // Дата навчання гігієнічним навичкам

    int sex = this->m_modelClients->record(row).value("sex").toInt();

    QString pib = this->m_modelClients->record(row).value("pib").toString(),
            CI  = this->m_modelClients->record(row).value("contactInfo").toString(),
            diagnosis = this->m_modelClients->record(row).value("diagnosis").toString(),
            complaint = this->m_modelClients->record(row).value("complaint").toString(),
            pard = this->m_modelClients->record(row).value("PARD").toString(),
            dodp = this->m_modelClients->record(row).value("DODP").toString(),
            bite = this->m_modelClients->record(row).value("bite").toString(),
            conditionOfTheOral = this->m_modelClients->record(row).value("conditionOfTheOral").toString(),
            xrayExam  = this->m_modelClients->record(row).value("xrayExam").toString(),
            colorVita = this->m_modelClients->record(row).value("colorVita").toString();

    // Tab "Основна інформація"
    if (dob.isNull())
        ui->dateDOB->setDate(QDate::currentDate());
    else
        ui->dateDOB->setDate(dob);

    m_lineEdit_sName->setText(pib);
    m_textEdit_ContactInfo->setText(CI);
    m_textEdit_diagnosis->setText(diagnosis);
    m_textEdit_complaints->setText(complaint);
    m_textEdit_zax1->setText(pard);
    m_textEdit_zax2->setText(dodp);

    // Завантаження фотографії пацієнта у компоненту на вкладці 1
    QPixmap pixmap;
    if (!baPhoto.size()) {
        pixmap.load(m_sNoImage);
        ui->img_photo->setPixmap(pixmap);
    } else {
        pixmap.loadFromData(baPhoto);
        ui->img_photo->setPixmap(pixmap);
    }

    // Завантаження статі пацієнта
    ui->comboBox_Type->setCurrentIndex(sex);

    //
    if (dob.isNull())
        m_date_Training->setDate(QDate::currentDate());
    else
        m_date_Training->setDate(dataTraining);

    m_textEdit_bite->setText(bite);
    m_textEdit_conditionOfTheOral->setText(conditionOfTheOral);
    m_textEdit_xrayExam->setText(xrayExam);
    m_textEdit_Vita->setText(colorVita);

    // Вкладка 2
    ui->dateEdit_dv->setEnabled(false);
    ui->dateEdit_dv->setDate(QDate::currentDate());
    ui->lbl_photoOfTeeth->setPixmap(QPixmap(m_sNoImage));
    m_textEdit_status->clear();
    query.prepare("SELECT DISTINCT(nOfTeeth) FROM numberofteeth WHERE id=:id;");
    query.bindValue(":id",this->iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
    m_lwgt->clear();
    //  Вставка номерів зуба пацієнта в комбобокс.
    ui->comboBox_nOfTeeth->clear();
    while(query.next()) {
        ui->comboBox_nOfTeeth->addItem(query.value("nOfTeeth").toString());
    }
    int currentTeeth = ui->comboBox_nOfTeeth->itemText(ui->comboBox_nOfTeeth->currentIndex()).toInt();
    if (ui->comboBox_nOfTeeth->count()) {
        slotDownloadTeethImgsSelectedPacient(currentTeeth);
//        slotShowTeethInListWidget();
    }
    query.clear();

    // Tab "Щоденник лікаря"
    modelBlogDoctor->setTable("blogdoctor");
    ui->tableView_DateView->setModel(modelBlogDoctor);
    modelBlogDoctor->select();
    modelBlogDoctor->setHeaderData(2, Qt::Horizontal, tr("Дата"));
    modelBlogDoctor->setFilter("id = " + QString::number(iSelectPacient));

    ui->tableView_DateView->hideColumn(0);  // id
    ui->tableView_DateView->hideColumn(1);  // id inc
    ui->tableView_DateView->hideColumn(3);  // status

    textEdit_DateViewMore->clear();

    loadImgsTeethsInLabels();
    emit slotDownloadDataInComponentTab2(index);

    ui->tableView_DateView->selectRow(0);
    ui->tableView_DateView->setCurrentIndex(ui->tableView_DateView->currentIndex());

    emit slotDownloadDataInComponentTab3(ui->tableView_DateView->currentIndex());

    for (int i = 0; i < 32; ++i) {
        QObject::connect(m_lblWithTeeth[i], SIGNAL(mouseClicked()), SLOT(slotPaintRectInTeeth()));
    }
}

void MainWindow::slotDownloadDataInComponentTab2(QModelIndex index) {
    Q_UNUSED(index);
    QObject::disconnect(ui->badTeeth_11, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_12, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_13, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_14, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_15, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_16, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_17, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_18, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_21, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_22, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_23, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_24, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_25, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_26, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_27, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_28, 0, 0, 0);

    QObject::disconnect(ui->badTeeth_31, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_32, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_33, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_34, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_35, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_36, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_37, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_38, 0, 0, 0);

    QObject::disconnect(ui->badTeeth_41, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_42, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_43, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_44, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_45, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_46, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_47, 0, 0, 0);
    QObject::disconnect(ui->badTeeth_48, 0, 0, 0);
//    qDebug() << "downloadDataInComponentTab2() : " << "iSelectPacient = " << iSelectPacient;
//     Очищення від минулих позначок
//    this->loadImgsTeethsInLabels();

    ui->badTeeth_11->setCurrentIndex(0);
    ui->badTeeth_12->setCurrentIndex(0);
    ui->badTeeth_13->setCurrentIndex(0);
    ui->badTeeth_14->setCurrentIndex(0);
    ui->badTeeth_15->setCurrentIndex(0);
    ui->badTeeth_16->setCurrentIndex(0);
    ui->badTeeth_17->setCurrentIndex(0);
    ui->badTeeth_18->setCurrentIndex(0);

    ui->badTeeth_21->setCurrentIndex(0);
    ui->badTeeth_22->setCurrentIndex(0);
    ui->badTeeth_23->setCurrentIndex(0);
    ui->badTeeth_24->setCurrentIndex(0);
    ui->badTeeth_25->setCurrentIndex(0);
    ui->badTeeth_26->setCurrentIndex(0);
    ui->badTeeth_27->setCurrentIndex(0);
    ui->badTeeth_28->setCurrentIndex(0);

    ui->badTeeth_31->setCurrentIndex(0);
    ui->badTeeth_32->setCurrentIndex(0);
    ui->badTeeth_33->setCurrentIndex(0);
    ui->badTeeth_34->setCurrentIndex(0);
    ui->badTeeth_35->setCurrentIndex(0);
    ui->badTeeth_36->setCurrentIndex(0);
    ui->badTeeth_37->setCurrentIndex(0);
    ui->badTeeth_38->setCurrentIndex(0);

    ui->badTeeth_41->setCurrentIndex(0);
    ui->badTeeth_42->setCurrentIndex(0);
    ui->badTeeth_43->setCurrentIndex(0);
    ui->badTeeth_44->setCurrentIndex(0);
    ui->badTeeth_45->setCurrentIndex(0);
    ui->badTeeth_46->setCurrentIndex(0);
    ui->badTeeth_47->setCurrentIndex(0);
    ui->badTeeth_48->setCurrentIndex(0);

    QSqlQuery query;
    query.prepare("SELECT nOfTeeth, nTeethBadHealth, sqrtOfTeeth FROM legendstateofteeth WHERE id=:id;");
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }

    while(query.next()) {
        int teeth = query.value("nOfTeeth").toInt();
        int nTeethBad = query.value("nTeethBadHealth").toInt();
        QByteArray ba = query.value("sqrtOfTeeth").toByteArray();
        QPixmap px;
        px.loadFromData(ba);

        switch(teeth) {
            case 11:
                ui->badTeeth_11->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[7]->setPixmap(px);
                    m_imgOfTeeth[7].loadFromData(ba);
                }
            break;
            case 12:
                ui->badTeeth_12->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[6]->setPixmap(px);
                    m_imgOfTeeth[6].loadFromData(ba);
                }
            break;
            case 13:
                ui->badTeeth_13->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[5]->setPixmap(px);
                    m_imgOfTeeth[5].loadFromData(ba);
                }
            break;
            case 14:
                ui->badTeeth_14->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[4]->setPixmap(px);
                    m_imgOfTeeth[4].loadFromData(ba);
                }
            break;
            case 15:
                ui->badTeeth_15->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[3]->setPixmap(px);
                    m_imgOfTeeth[3].loadFromData(ba);
                }
            break;
            case 16:
                ui->badTeeth_16->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[2]->setPixmap(px);
                    m_imgOfTeeth[2].loadFromData(ba);
                }
            break;
            case 17:
                ui->badTeeth_17->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_imgOfTeeth[1].loadFromData(ba);
                    m_lblWithTeeth[1]->setPixmap(px);
                }
            break;
            case 18:
                ui->badTeeth_18->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[0]->setPixmap(px);
                    m_imgOfTeeth[0].loadFromData(ba);
                }
            break;

            case 21:
                ui->badTeeth_21->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[15]->setPixmap(px);
                    m_imgOfTeeth[15].loadFromData(ba);
                }
            break;
            case 22:
                ui->badTeeth_22->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[14]->setPixmap(px);
                    m_imgOfTeeth[14].loadFromData(ba);

                }
            break;
            case 23:
                ui->badTeeth_23->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[13]->setPixmap(px);
                    m_imgOfTeeth[13].loadFromData(ba);
                }
            break;
            case 24:
                ui->badTeeth_24->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[12]->setPixmap(px);
                    m_imgOfTeeth[12].loadFromData(ba);
                }
            break;
            case 25:
                ui->badTeeth_25->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[11]->setPixmap(px);
                    m_imgOfTeeth[11].loadFromData(ba);
                }
            break;
            case 26:
                ui->badTeeth_26->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[10]->setPixmap(px);
                    m_imgOfTeeth[10].loadFromData(ba);
                }
            break;
            case 27:
                ui->badTeeth_27->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[9]->setPixmap(px);
                    m_imgOfTeeth[9].loadFromData(ba);
                }
            break;
            case 28:
                ui->badTeeth_28->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[8]->setPixmap(px);
                    m_imgOfTeeth[8].loadFromData(ba);
                }
            break;

            case 31:
                ui->badTeeth_31->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[23]->setPixmap(px);
                    m_imgOfTeeth[23].loadFromData(ba);
                }
            break;
            case 32:
                ui->badTeeth_32->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[22]->setPixmap(px);
                    m_imgOfTeeth[22].loadFromData(ba);
                }
            break;
            case 33:
                ui->badTeeth_33->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[21]->setPixmap(px);
                    m_imgOfTeeth[21].loadFromData(ba);
                }
            break;
            case 34:
                ui->badTeeth_34->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[20]->setPixmap(px);
                    m_imgOfTeeth[20].loadFromData(ba);
                }
            break;
            case 35:
                ui->badTeeth_35->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[19]->setPixmap(px);
                    m_imgOfTeeth[19].loadFromData(ba);
                }
            break;
            case 36:
                ui->badTeeth_36->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[18]->setPixmap(px);
                    m_imgOfTeeth[18].loadFromData(ba);
                }
            break;
            case 37:
                ui->badTeeth_37->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[17]->setPixmap(px);
                    m_imgOfTeeth[17].loadFromData(ba);
                }
            break;
            case 38:
                ui->badTeeth_38->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[16]->setPixmap(px);
                    m_imgOfTeeth[16].loadFromData(ba);
                }
            break;

            case 41:
                ui->badTeeth_41->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[31]->setPixmap(px);
                    m_imgOfTeeth[31].loadFromData(ba);
                }
            break;
            case 42:
                ui->badTeeth_42->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[30]->setPixmap(px);
                    m_imgOfTeeth[30].loadFromData(ba);
                }
            break;
            case 43:
                ui->badTeeth_43->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[29]->setPixmap(px);
                    m_imgOfTeeth[29].loadFromData(ba);
                }
            break;
            case 44:
                ui->badTeeth_44->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[28]->setPixmap(px);
                    m_imgOfTeeth[28].loadFromData(ba);
                }
            break;
            case 45:
                ui->badTeeth_45->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[27]->setPixmap(px);
                    m_imgOfTeeth[27].loadFromData(ba);
                }
            break;
            case 46:
                ui->badTeeth_46->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[26]->setPixmap(px);
                    m_imgOfTeeth[26].loadFromData(ba);
                }
            break;
            case 47:
                ui->badTeeth_47->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[25]->setPixmap(px);
                    m_imgOfTeeth[25].loadFromData(ba);
                }
            break;
            case 48:
                ui->badTeeth_48->setCurrentIndex(nTeethBad);
                if (!ba.isEmpty()) {
                    m_lblWithTeeth[24]->setPixmap(px);
                    m_imgOfTeeth[24].loadFromData(ba);
                }
            break;
        }
    }
    query.clear();
//    downloadStatusAndDateOfImg();

    QObject::connect(ui->badTeeth_11, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_12, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_13, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_14, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_15, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_16, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_17, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_18, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));

    QObject::connect(ui->badTeeth_21, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_22, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_23, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_24, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_25, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_26, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_27, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_28, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));

    QObject::connect(ui->badTeeth_31, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_32, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_33, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_34, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_35, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_36, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_37, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_38, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));

    QObject::connect(ui->badTeeth_41, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_42, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_43, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_44, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_45, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_46, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_47, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
    QObject::connect(ui->badTeeth_48, SIGNAL(currentIndexChanged(int)), SLOT(slotUpdateBadTeeth(int)));
}

void MainWindow::slotUpdateBadTeeth(int nOfBad) {
//    qDebug() << "QObject::sender() " << QObject::sender()->objectName() << "; bad = " << nOfBad;
    int nOfTeeth = 0;
    QString obj = QObject::sender()->objectName();

    if (obj == ui->badTeeth_11->objectName()) {
        nOfTeeth = 11;
    } else if (obj == ui->badTeeth_12->objectName()) {
        nOfTeeth = 12;
    } else if (obj == ui->badTeeth_13->objectName()) {
        nOfTeeth = 13;
    } else if (obj == ui->badTeeth_14->objectName()) {
        nOfTeeth = 14;
    } else if (obj == ui->badTeeth_15->objectName()) {
        nOfTeeth = 15;
    } else if (obj == ui->badTeeth_16->objectName()) {
        nOfTeeth = 16;
    } else if (obj == ui->badTeeth_17->objectName()) {
        nOfTeeth = 17;
    } else if (obj == ui->badTeeth_18->objectName()) {
        nOfTeeth = 18;
    } else if (obj == ui->badTeeth_21->objectName()) {
        nOfTeeth = 21;
    } else if (obj == ui->badTeeth_22->objectName()) {
        nOfTeeth = 22;
    } else if (obj == ui->badTeeth_23->objectName()) {
        nOfTeeth = 23;
    } else if (obj == ui->badTeeth_24->objectName()) {
        nOfTeeth = 24;
    } else if (obj == ui->badTeeth_25->objectName()) {
        nOfTeeth = 25;
    } else if (obj == ui->badTeeth_26->objectName()) {
        nOfTeeth = 26;
    } else if (obj == ui->badTeeth_27->objectName()) {
        nOfTeeth = 27;
    } else if (obj == ui->badTeeth_28->objectName()) {
        nOfTeeth = 28;
    } else if (obj == ui->badTeeth_31->objectName()) {
        nOfTeeth = 31;
    } else if (obj == ui->badTeeth_32->objectName()) {
        nOfTeeth = 32;
    } else if (obj == ui->badTeeth_33->objectName()) {
        nOfTeeth = 33;
    } else if (obj == ui->badTeeth_34->objectName()) {
        nOfTeeth = 34;
    } else if (obj == ui->badTeeth_35->objectName()) {
        nOfTeeth = 35;
    } else if (obj == ui->badTeeth_36->objectName()) {
        nOfTeeth = 36;
    } else if (obj == ui->badTeeth_37->objectName()) {
        nOfTeeth = 37;
    } else if (obj == ui->badTeeth_38->objectName()) {
        nOfTeeth = 38;
    } else if (obj == ui->badTeeth_41->objectName()) {
        nOfTeeth = 41;
    } else if (obj == ui->badTeeth_42->objectName()) {
        nOfTeeth = 42;
    } else if (obj == ui->badTeeth_43->objectName()) {
        nOfTeeth = 43;
    } else if (obj == ui->badTeeth_44->objectName()) {
        nOfTeeth = 44;
    } else if (obj == ui->badTeeth_45->objectName()) {
        nOfTeeth = 45;
    } else if (obj == ui->badTeeth_46->objectName()) {
        nOfTeeth = 46;
    } else if (obj == ui->badTeeth_47->objectName()) {
        nOfTeeth = 47;
    } else if (obj == ui->badTeeth_48->objectName()) {
        nOfTeeth = 48;
    }

    QSqlQuery query;
    if (nOfBad == 0) {
        query.clear();
        query.prepare("DELETE FROM legendstateofteeth "
                      "WHERE (nOfTeeth=:nOfTeeth) AND (id=:id);");
        query.bindValue(":nOfTeeth", nOfTeeth);
        query.bindValue(":id", iSelectPacient);
        if (!query.exec()) {
            qDebug() << query.lastError();
        }
        return;
    }

    query.prepare("SELECT * FROM legendstateofteeth WHERE nOfTeeth=:nOfTeeth AND id=:id;");
    query.bindValue(":nOfTeeth", nOfTeeth);
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    if (query.size() <= 0) {
        query.clear();
        query.prepare("INSERT INTO legendstateofteeth (id, nOfTeeth, nTeethBadHealth) "
                                               "VALUES(:id, :nOfTeeth, :nTeethBadHealth);");
        query.bindValue(":id", iSelectPacient);
        query.bindValue(":nOfTeeth", nOfTeeth);
        query.bindValue(":nTeethBadHealth", nOfBad);
        if (!query.exec()) {
            qDebug() << query.lastError();
        }
        return;
    }
    query.clear();
    query.prepare("UPDATE legendstateofteeth SET nTeethBadHealth=:nTeethBadHealth "
                  "WHERE (nOfTeeth=:nOfTeeth) AND (id=:id);");
    query.bindValue(":nTeethBadHealth", nOfBad);
    query.bindValue(":nOfTeeth", nOfTeeth);
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
}

void MainWindow::slotDeleteTeethImg() {
    if (!m_lwgt->count() && !m_lwgt->selectedItems().count())
        return;

    QMessageBox msgBox;
    msgBox.setText("Знімок зуба буде видалений.");
    msgBox.setWindowTitle(this->windowTitle());
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setInformativeText("Ви хочете видалити знімок зуба?");
                         msgBox.addButton(tr("Так"), QMessageBox::ActionRole);
    QPushButton *btnNo = msgBox.addButton(tr("Ні"), QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() == btnNo)
        return;

    QSqlQuery query;
    query.prepare("DELETE FROM photosofteeth WHERE id_inc=:id;");
    query.bindValue(":id", m_lwgt->currentItem()->text());
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
    m_lwgt->removeItemWidget(m_lwgt->currentItem());
}

void MainWindow::slotDeleteTeeth() {
    if (!m_lwgt->count() && !m_lwgt->selectedItems().count())
        return;

    QMessageBox msgBox;
    msgBox.setWindowTitle(this->windowTitle());
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Зуб буде видалений.");
    msgBox.setInformativeText("Ви хочете видалити всі знімки зуба?");
                         msgBox.addButton(tr("Так"), QMessageBox::ActionRole);
    QPushButton *btnNo = msgBox.addButton(tr("Ні"), QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() == btnNo)
        return;

    int ind = ui->comboBox_nOfTeeth->currentIndex();
    QSqlQuery query;
    query.prepare("DELETE FROM numberofteeth WHERE id=:id AND nOfTeeth=:nt;");
    query.bindValue(":id", iSelectPacient);
    query.bindValue(":nt", ui->comboBox_nOfTeeth->currentText());
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
    ui->comboBox_nOfTeeth->removeItem(ind);

    int cnt = ui->comboBox_nOfTeeth->count()-1;
    if (ind == 0 || ind == cnt)
        ui->comboBox_nOfTeeth->setCurrentIndex(ind);
    else
        ui->comboBox_nOfTeeth->setCurrentIndex(ind+1);
}

void MainWindow::slotAddTeethImages() {
    bool ok = false;
    int nOfTeeth = QInputDialog::getText(this, this->windowTitle(),
                                      tr("Вкажіть номер зуба, який на знімку(-ах):"), QLineEdit::Normal,
                                      "", &ok).toInt(&ok);

    if ( !ok || nOfTeeth < 11 || nOfTeeth > 48  ||
        (nOfTeeth > 18 && nOfTeeth < 21)        ||
        (nOfTeeth > 28 && nOfTeeth < 31)
       )
    {
        return;
    }

    QFileDialog fd;
    QStringList imagesTeeth = fd.getOpenFileNames(this,
                                                  "Додавання знімків зуба",
                                                  "",
                                                  "Файли зображень(*.jpg)");

    if (imagesTeeth.size() < 1)
        return;

    int result = ui->comboBox_nOfTeeth->findText(QString::number(nOfTeeth));
    QSqlQuery query;
    int id_inc = -1;
    if (result == -1) {
        query.prepare("INSERT INTO numberofteeth (id, nOfTeeth) VALUES (:id, :nOfTeeth);");
        query.bindValue(":id", this->iSelectPacient);
        query.bindValue(":nOfTeeth", nOfTeeth);
        if (!query.exec()) {
            qDebug() << query.lastError();
        }
        query.clear();
    }
    query.prepare("SELECT id_inc FROM numberofteeth WHERE id=:id AND nOfTeeth=:nOfTeeth;");
    query.bindValue(":id", this->iSelectPacient);
    query.bindValue(":nOfTeeth", nOfTeeth);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return;
    }
    query.next();
    id_inc = query.value("id_inc").toInt();
    bool isTrueQueryExec = true;
    int countImgs = imagesTeeth.count();
    for (int i = 0; i < countImgs; ++i) {
        query.clear();
        QImage img;
        if (!img.load(imagesTeeth.at(i))) {
            qDebug() << "error load imageinto object img!";
        }
        QByteArray ba;
        QBuffer buf(&ba);
        buf.open(QIODevice::WriteOnly);
        img.save( &buf, "JPG" );
        buf.close();

        query.prepare("INSERT INTO photosofteeth(id, photoOfTeeth, dateViewOfTeeth) VALUES(:id, :photoOfTeeth, :dv);");
        query.bindValue(":id", id_inc);
        query.bindValue(":photoOfTeeth", ba);
        query.bindValue(":dv", QDate::currentDate().toString("yyyy-MM-dd"));
        if (!query.exec()) {
            qDebug() << query.lastError();
            isTrueQueryExec = false;
            break;
        }
    }
    if (!isTrueQueryExec) {
        QMessageBox::warning(this,
                             this->windowTitle(),
                             "Помилка додавання фотографії.");
    }

    query.clear();
    query.prepare("SELECT DISTINCT(nOfTeeth) FROM numberofteeth WHERE id=:id;");
    query.bindValue(":id",this->iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
    // Вставка номерів зуба пацієнта в комбобокс.
    ui->comboBox_nOfTeeth->clear();
    while(query.next()) {
        ui->comboBox_nOfTeeth->addItem(query.value("nOfTeeth").toString());
    }
    ui->comboBox_nOfTeeth->setCurrentIndex(ui->comboBox_nOfTeeth->count()-1);
//    emit downloadFirstImageTeeth(ui->comboBox_nOfTeeth->currentIndex());
}

void MainWindow::slotDownloadTeethImgsSelectedPacient(int currentTeeth) {
    if (currentTeeth == 0)
        return;

    m_imgsTeeths.clear();

    QSqlQuery query;
    query.prepare("SELECT DISTINCT(id_inc) FROM numberofteeth WHERE id=:id AND nOfTeeth=:nOfTeeth;");
    query.bindValue(":id", iSelectPacient);
    query.bindValue(":nOfTeeth", currentTeeth);
    if (!query.exec()) {
        qDebug() << "slotDownloadTeethImgsSelectedPacient" << query.lastError();
    }
    if (!query.size())
        return;

    query.next();
    int id = query.value("id_inc").toInt();
    query.clear();
    query.prepare("SELECT id_inc,dateViewOfTeeth,status,photoOfTeeth FROM photosofteeth "
                  "WHERE id=:id;");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "slotDownloadTeethImgsSelectedPacient 2:" << query.lastError();
    }

    while(query.next()) {
        int i = query.value("id_inc").toInt();
        QDate d = query.value("dateViewOfTeeth").toDate();
        QString s = query.value("status").toString();
        QByteArray b = query.value("photoOfTeeth").toByteArray();

        m_imgsTeeths.push_back(new imageOfTeeth(i, id, d, s, b));
    }
}

void MainWindow::slotShowMoreInfoATeeth(QListWidgetItem* ind) {
    int id_img = ind->text().toInt();

    foreach (imageOfTeeth *it, m_imgsTeeths) {
        if (it->id_inc == id_img) {
            QPixmap p;
                p.loadFromData(it->blob);
                ui->lbl_photoOfTeeth->setPixmap(p);
                m_textEdit_status->setText(it->status);
                ui->dateEdit_dv->setDate(it->dateView);
            break;
        }
    }
}

void MainWindow::slotShowTeethInListWidget(int ci) {
    ui->lbl_photoOfTeeth->setPixmap(QPixmap(m_sNoImage));
    m_textEdit_status->clear();
    ui->dateEdit_dv->setDate(QDate::currentDate());

    ui->dateEdit_dv->setEnabled(false);
    m_lwgt->setEnabled(false);
    m_textEdit_status->setEnabled(false);
    ui->lbl_photoOfTeeth->setEnabled(false);

    if (!ui->comboBox_nOfTeeth->count())
        return;

    m_lwgt->clear();
    int currentTeeth = ui->comboBox_nOfTeeth->itemText(ci).toInt();
    emit slotDownloadTeethImgsSelectedPacient(currentTeeth);

    if (m_imgsTeeths.empty())
        return;

    m_lwgt->setIconSize(QSize(48, 48));
    QListWidgetItem *lwgti = 0;
    foreach (imageOfTeeth *it, m_imgsTeeths) {
//        lwgti = new QListWidgetItem(QString::number(it->id_inc), m_lwgt);
        lwgti = new QListWidgetItem(m_lwgt);
        lwgti->setData(0,it->id_inc);
        QPixmap p;
        p.loadFromData(it->blob);
        lwgti->setIcon(p);
        lwgti->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    }
    m_lwgt->setViewMode(QListView::IconMode);

    ui->dateEdit_dv->setEnabled(true);
    m_lwgt->setEnabled(true);
    m_textEdit_status->setEnabled(true);
    ui->lbl_photoOfTeeth->setEnabled(true);

    connect(m_lwgt, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slotShowMoreInfoATeeth(QListWidgetItem*)));

    m_lwgt->setCurrentRow(0);
    emit m_lwgt->itemClicked(m_lwgt->currentItem());
}

void MainWindow::slotUpdateStatusOfTeeth() {
    if (!m_lwgt->count() || !m_lwgt->selectedItems().count())    // Якщо пусто в списку m_lwgt або
        return;                                                  // не вибрано жодного об'єкта

    int id = m_lwgt->currentItem()->data(0).toInt();

    QString text = m_textEdit_status->toPlainText();
    QSqlQuery query;
    query.prepare("UPDATE photosofteeth SET status=:fieldVal WHERE id_inc=:id;");
    query.bindValue(":fieldVal", text);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }

    foreach (imageOfTeeth *it, m_imgsTeeths) {
        if (it->id_inc == id) {
            it->status = text;
            return;
        }
    }
}

void MainWindow::slotUpdateDateOfTeeth(QDate d) {
    if (!m_lwgt->selectedItems().count())
        return;

    int id_inc = m_lwgt->currentItem()->text().toInt();
    QSqlQuery query;
    query.prepare("UPDATE photosofteeth SET dateViewOfTeeth=:fieldVal WHERE id_inc=:id;");
    query.bindValue(":fieldVal", d.toString("yyyy-MM-dd"));
    query.bindValue(":id", id_inc);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
    foreach (imageOfTeeth *it, m_imgsTeeths) {
        if (it->id_inc == id_inc) {
            it->dateView = d;
            return;
        }
    }
}

// Завантажування даних в компоненти з БД, котрі знаходяться в 3-й вкладці.
void MainWindow::slotDownloadDataInComponentTab3(QModelIndex index) {
    selectedIndexInDataView = modelBlogDoctor->index(index.row(), 3);
    QString status = modelBlogDoctor->data(modelBlogDoctor->index(index.row(), 3)).toString();
    textEdit_DateViewMore->setText(status);
}

void MainWindow::slotUpdateDateViewMore() {
    if (!textEdit_DateViewMore->getBTextChanged())
        return;
    QString st = textEdit_DateViewMore->toPlainText();
//    qDebug() <<"slotUpdateDateViewMore";
    textEdit_DateViewMore->resetBTextChanged();
    modelBlogDoctor->setData(selectedIndexInDataView, st);
}

// Додати дату огляду пацієнта
void MainWindow::slotOpenDialogAddDataView() {
    m_dlgAddDateView->show();
}

void MainWindow::slotAddDateView(QDate dateView, QString status) {
    QSqlQuery query;
    query.prepare("INSERT INTO blogdoctor (id, date, status)"
                  "VALUES (:id, :dateView, :status);");
    query.bindValue(":id", iSelectPacient);
    query.bindValue(":dateView", dateView.toString("yyyy-MM-dd"));
    query.bindValue(":status", status);
    if (!query.exec()) {
        QMessageBox::critical(this,
                              this->windowTitle(),
                              "Помилка додавання дати огляду.");
        return;
    }

    modelBlogDoctor->setTable("blogdoctor");
    modelBlogDoctor->setFilter("id = " + QString::number(iSelectPacient));
    modelBlogDoctor->select();
    modelBlogDoctor->setHeaderData(2, Qt::Horizontal, tr("Дата"));

    ui->tableView_DateView->selectRow(modelBlogDoctor->rowCount()-1);
    ui->tableView_DateView->setCurrentIndex(ui->tableView_DateView->currentIndex());
    emit slotDownloadDataInComponentTab3(ui->tableView_DateView->currentIndex());
}

void MainWindow::slotUpdateInfoAboutClient() {
    QString fieldName = "";
    QString fieldVal = "";
    QString senderName = sender()->objectName();
    int row = proxyModel->mapToSource(ui->tableView_listOfPeople->currentIndex()).row();

    if (m_textEdit_complaints->objectName() == senderName) {
        if (!m_textEdit_complaints->getBTextChanged())
            return;

        m_textEdit_complaints->resetBTextChanged();
        fieldName = "complaint";
        fieldVal  = m_textEdit_complaints->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 6), fieldVal);
    }
    else if (m_textEdit_zax2->objectName()  == senderName) {
        if (!m_textEdit_zax2->getBTextChanged())
            return;
        m_textEdit_zax2->resetBTextChanged();
        fieldName = "DODP";
        fieldVal  = m_textEdit_zax2->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 8),fieldVal);
    }
    else if (m_textEdit_Vita->objectName()  == senderName) {
        if (!m_textEdit_Vita->getBTextChanged())
            return;
        m_textEdit_Vita->resetBTextChanged();
        fieldName = "colorVita";
        fieldVal  = m_textEdit_Vita->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 14), fieldVal);
    }
    else if (m_textEdit_bite->objectName()  == senderName) {
        if (!m_textEdit_bite->getBTextChanged())
            return;
        m_textEdit_bite->resetBTextChanged();
        fieldName = "bite";
        fieldVal  = m_textEdit_bite->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 11), fieldVal);
    }
    else if (m_textEdit_zax1->objectName()  == senderName) {
        if (!m_textEdit_zax1->getBTextChanged())
            return;
        m_textEdit_zax1->resetBTextChanged();
        fieldName = "PARD";
        fieldVal  = m_textEdit_zax1->toPlainText();
    }
    else if (m_textEdit_xrayExam->objectName()  == senderName) {
        if (!m_textEdit_xrayExam->getBTextChanged())
            return;
        m_textEdit_xrayExam->resetBTextChanged();
        fieldName = "xrayExam";
        fieldVal  = m_textEdit_xrayExam->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 13), fieldVal);
    }
    else if (m_textEdit_diagnosis->objectName() == senderName) {
        if (!m_textEdit_diagnosis->getBTextChanged())
            return;
        m_textEdit_diagnosis->resetBTextChanged();
        fieldName = "diagnosis";
        fieldVal  = m_textEdit_diagnosis->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 5), fieldVal);
    }
    else if (m_textEdit_conditionOfTheOral->objectName() == senderName) {
        if (!m_textEdit_conditionOfTheOral->getBTextChanged())
            return;
        m_textEdit_conditionOfTheOral->resetBTextChanged();
        fieldName = "conditionOfTheOral";
        fieldVal = m_textEdit_conditionOfTheOral->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 12), fieldVal);
    }
    else if (m_date_Training->objectName() == senderName) {
        fieldName = "dataTraining";
        fieldVal = m_date_Training->date().toString("yyyy-MM-dd");
        m_modelClients->setData(m_modelClients->index(row, 10), fieldVal);
    }
    else if (ui->dateDOB->objectName() == senderName) {
        fieldName = "DOB";
        fieldVal = ui->dateDOB->date().toString("yyyy-MM-dd");
//        qDebug() << proxyModel->mapToSource(ui->tableView_listOfPeople->currentIndex()).data();
        m_modelClients->setData(m_modelClients->index(row, 3), fieldVal);
    }
    else if (ui->comboBox_Type->objectName() == senderName) {
        fieldName = "sex";
        fieldVal = QString::number(ui->comboBox_Type->currentIndex());
        m_modelClients->setData(m_modelClients->index(row, 2), fieldVal);
    }
    else if (m_lineEdit_sName->objectName() == senderName) {
        fieldName = "pib";
        fieldVal = m_lineEdit_sName->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 1), fieldVal);
//        proxyModel->setData();
    }
    else if (m_textEdit_ContactInfo->objectName() == senderName) {
        fieldName = "contactInfo";
        fieldVal = m_textEdit_ContactInfo->toPlainText();
        m_modelClients->setData(m_modelClients->index(row, 4), fieldVal);
    }

    if (fieldName == "")    // Якщо не вибрано жодного поля для обновлення,
        return;             // тоді виходимо

    QSqlQuery query;
    query.prepare("UPDATE clients SET " + fieldName +"=:fieldVal WHERE id=:id;");
    query.bindValue(":fieldVal", fieldVal);
    query.bindValue(":id", iSelectPacient);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
}

/*
    Кольори корінів зуба.
    Щоб можна було зрозуміти, який зафарбововувати корінець зуба, для кожного з корінців було
    обрано індивідуальний колір.
    center1  , left1   , right1      - лівий, центральний та правий корінь
    redCenterColor, redColor, yellowColor - кольори, в які закрашується коріні зуба.
    Різні кольори закраски корінців, тому що, може виникнути ситуація коли потрібно забрати позначення із зуба.
    І знову виникає ситуація, коли потрібно зрозуміти який саме з корінців було обрано, для того щоб закрасити
    необхідну ділянку зображення.

color =  4294901760 index 28 корінь лв
color =  4293991460 index 28 корінь пр

color =  4293598244 index 28 верх
color =  4293663780 index 28 право
color =  4293729316 index 28 низ
color =  4293794852 index 28 ліво
color =  4293860388 index 28 центр
*/
enum colorOfTeeth {
    whiteF          = 4294967295,
    // Корені
    left1           = 4294572537,
    center1         = 4294769916,
    right1          = 4294704123,
    redCenterColor  = 4294056996,
    redColor        = 4294901760,
    clearRightRoot  = 4293991460,

    // Чисті кольори, по яким відбувається
    // розпізнавання ділянки для закрашування
    upRectCl        = 4294835709,
    downRectCl      = 4294375158,
    rightRectCl     = 4294901502,
    leftRectCl      = 4294440951,
    centrRectCl     = 4294506744,

    // Кольори, по яким відбувається
    // розпізнавання ділянки для забирання кольору
    upRectBr        = 4278255615,
    rightRectBr     = 4278321151,
    downRectBr      = 4278386687,
    leftRectBr      = 4278452223,
    centrRectBr     = 4278517759
};

void MainWindow::slotPaintRectInTeeth() {
    QString senderName = QObject::sender()->objectName();
    int index = -1;

    for (int i = 0; i < 32; ++i) {
        if (senderName == m_lblWithTeeth[i]->objectName()) {
            index = i;
            break;
        }
    }
    unsigned int nOfTeeth = senderName.toInt();
    unsigned int fn = nOfTeeth / 10;
    unsigned int ln = nOfTeeth % 10;
    unsigned int color = m_imgOfTeeth[index].pixel(m_lblWithTeeth[index]->x, m_lblWithTeeth[index]->y);
    int ind = 0;

    switch (nOfTeeth) {
        case 18:
            ind = ui->badTeeth_18->currentIndex();
        break;
        case 17:
            ind = ui->badTeeth_17->currentIndex();
        break;
        case 16:
            ind = ui->badTeeth_16->currentIndex();
        break;
        case 15:
            ind = ui->badTeeth_15->currentIndex();
        break;
        case 14:
            ind = ui->badTeeth_14->currentIndex();
        break;
        case 13:
            ind = ui->badTeeth_13->currentIndex();
        break;
        case 12:
            ind = ui->badTeeth_12->currentIndex();
        break;
        case 11:
            ind = ui->badTeeth_11->currentIndex();
        break;

        case 28:
            ind = ui->badTeeth_28->currentIndex();
        break;
        case 27:
            ind = ui->badTeeth_27->currentIndex();
        break;
        case 26:
            ind = ui->badTeeth_26->currentIndex();
        break;
        case 25:
            ind = ui->badTeeth_25->currentIndex();
        break;
        case 24:
            ind = ui->badTeeth_24->currentIndex();
        break;
        case 23:
            ind = ui->badTeeth_23->currentIndex();
        break;
        case 22:
            ind = ui->badTeeth_22->currentIndex();
        break;
        case 21:
            ind = ui->badTeeth_21->currentIndex();
        break;

        case 38:
            ind = ui->badTeeth_38->currentIndex();
        break;
        case 37:
            ind = ui->badTeeth_37->currentIndex();
        break;
        case 36:
            ind = ui->badTeeth_36->currentIndex();
        break;
        case 35:
            ind = ui->badTeeth_35->currentIndex();
        break;
        case 34:
            ind = ui->badTeeth_34->currentIndex();
        break;
        case 33:
            ind = ui->badTeeth_33->currentIndex();
        break;
        case 32:
            ind = ui->badTeeth_32->currentIndex();
        break;
        case 31:
            ind = ui->badTeeth_31->currentIndex();
        break;

        case 48:
            ind = ui->badTeeth_48->currentIndex();
        break;
        case 47:
            ind = ui->badTeeth_47->currentIndex();
        break;
        case 46:
            ind = ui->badTeeth_46->currentIndex();
        break;
        case 45:
            ind = ui->badTeeth_45->currentIndex();
        break;
        case 44:
            ind = ui->badTeeth_44->currentIndex();
        break;
        case 43:
            ind = ui->badTeeth_43->currentIndex();
        break;
        case 42:
            ind = ui->badTeeth_42->currentIndex();
        break;
        case 41:
            ind = ui->badTeeth_41->currentIndex();
        break;
    }

    if (ind < 1) {
        QMessageBox::warning(this,
                             this->windowTitle(),
                             "Не додано стан зуба!");
        return;
    }
//    qDebug() << "nOfTeeth = " << nOfTeeth;
//    return;
//    qDebug() << senderName;
//    qDebug() << "color = " << color << "; fn = " << fn;
//    qDebug() << "color = " << color << "index" << index;
//    query.prepare("SELECT * FROM legendstateofteeth WHERE id=:id AND nOfTeeth=:nOfTeeth;");
//    query.bindValue(":id", iSelectPacient);
//    query.bindValue(":nOfTeeth", nOfTeeth);
//    if (!query.exec()) {
//        qDebug() << query.lastError();
//    }
//    query.next();
//    qDebug() << "query.size() =" << query.record().count();
//    qDebug() << "iSelectPacient = " << iSelectPacient << "; nOfTeeth = " << nOfTeeth;
//    if (!query.size())

    QPainter paint;
    if (color == whiteF) {
        return;
    }

    if (fn < 3) {   // Верх
        switch (color) {
            case upRectCl: {        // Закраска верху зуба(1-ша частина)
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(0, 255, 255, 255));
                    paint.setPen(QColor(0, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(6.0,2.0),
                            QPointF(22.0,2.0),
                            QPointF(17.0,7.0),
                            QPointF(11.0,7.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln > 0 && ln < 4) {
                        const QPointF points[3] = {
                            QPointF(5.0,2.0),
                            QPointF(23.0,2.0),
                            QPointF(14.0,11.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case upRectBr: {        // Очистка верху зуба(1-ша частина - верх)
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(253, 253, 253, 255));
                    paint.setPen(QColor(253, 253, 253, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(6.0,2.0),
                            QPointF(22.0,2.0),
                            QPointF(17.0,7.0),
                            QPointF(11.0,7.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln > 0 && ln < 4) {
                        const QPointF points[3] = {
                            QPointF(5.0,2.0),
                            QPointF(23.0,2.0),
                            QPointF(14.0,11.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case rightRectCl: {     // Закраска верху зуба(1-ша частина) право
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(1, 255, 255, 255));
                    paint.setPen(QColor(1, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(26.0,2.0),
                            QPointF(26.0,20.0),
                            QPointF(19.0,13.0),
                            QPointF(19.0,9.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(26.0,3.0),
                            QPointF(26.0,22.0),
                            QPointF(17.0,13.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case rightRectBr: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(254, 254, 254, 255));
                    paint.setPen(QColor(254, 254, 254, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(26.0,2.0),
                            QPointF(26.0,20.0),
                            QPointF(19.0,13.0),
                            QPointF(19.0,9.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(26.0,3.0),
                            QPointF(26.0,22.0),
                            QPointF(17.0,13.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case downRectCl: {  // Закраска нижнього паралелограма
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(2, 255, 255, 255));
                    paint.setPen(QColor(2, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(11.0,15.0),
                            QPointF(17.0,15.0),
                            QPointF(23.0,21.0),
                            QPointF( 5.0,21.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(14.0,14.0),
                            QPointF(23.0,22.0),
                            QPointF( 6.0,22.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case downRectBr: {  // Очистка нижнього паралелограма
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(246, 246, 246, 255));
                    paint.setPen(QColor(246, 246, 246, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(11.0,15.0),
                            QPointF(17.0,15.0),
                            QPointF(23.0,21.0),
                            QPointF( 5.0,21.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(14.0,14.0),
                            QPointF(23.0,22.0),
                            QPointF( 6.0,22.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case leftRectCl: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(3, 255, 255, 255));
                    paint.setPen(QColor(3, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(2.0,2.0),
                            QPointF(9.0,9.0),
                            QPointF(9.0,13.0),
                            QPointF(2.0,20.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(2.0,3.0),
                            QPointF(12.0,13.0),
                            QPointF(3.0,22.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case leftRectBr: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(247, 247, 247, 255));
                    paint.setPen(QColor(247, 247, 247, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(2.0,2.0),
                            QPointF(9.0,9.0),
                            QPointF(9.0,13.0),
                            QPointF(2.0,20.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(2.0,3.0),
                            QPointF(12.0,13.0),
                            QPointF(3.0,22.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
            break;
            }
            case centrRectCl: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(4, 255, 255, 255));
                    paint.setPen(QColor(4, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(12.0,9.0),
                            QPointF(16.0,9.0),
                            QPointF(16.0,13.0),
                            QPointF(12.0,13.0)
                        };
                        paint.drawPolygon(points, 4);
                    }
                paint.end();
            break;
            }
            case centrRectBr: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(248, 248, 248, 255));
                    paint.setPen(QColor(248, 248, 248, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(12.0,9.0),
                            QPointF(16.0,9.0),
                            QPointF(16.0,13.0),
                            QPointF(12.0,13.0)
                        };
                        paint.drawPolygon(points, 4);
                    }
                paint.end();
                break;
            }
            // Center of teeth
            case center1: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(242, 28, 36, 255));
                    paint.setPen(QColor(248, 28, 36, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(14.0,24.0),
                            QPointF(21.0,33.0),
                            QPointF(14.0,46.0),
                            QPointF(8.0,33.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else {
                        const QPointF points[3] = {
                            QPointF(4.0,25.0),
                            QPointF(14.0,46.0),
                            QPointF(24.0,25.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case redCenterColor: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(252, 252, 252, 255));
                    paint.setPen(QColor(252, 252, 252, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(14.0,24.0),
                            QPointF(21.0,33.0),
                            QPointF(14.0,46.0),
                            QPointF(8.0,33.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else {
                        const QPointF points[3] = {
                            QPointF(4.0,25.0),
                            QPointF(14.0,46.0),
                            QPointF(24.0,25.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case left1: {   // Намалювати червоний трикутник на лівому корені
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(Qt::red);
                    paint.setPen(Qt::red);

                    if (ln > 3) {
                        const QPointF points[3] = {
                            QPointF(2.0,25.0),
                            QPointF(11.0,25.0),
                            QPointF(2.0,37.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case redColor: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(249, 249, 249, 255));
                    paint.setPen(QColor(249, 249, 249, 255));

                    if (ln > 3) {
                        const QPointF points[3] = {
                            QPointF(2.0,25.0),
                            QPointF(11.0,25.0),
                            QPointF(2.0,37.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case right1: {  // Намалювати червоний трикутник на правому корені
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(241, 28, 36, 255));
                    paint.setPen(QColor(241, 28, 36, 255));

                    if (ln > 3) {
                        const QPointF points[3] = {
                            QPointF(17.0,25.0),
                            QPointF(27.0,25.0),
                            QPointF(27.0,36.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case clearRightRoot: {    // Стерти червоний трикутник на правому корені
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(251, 251, 251, 255));
                    paint.setPen(QColor(251, 251, 251, 255));

                    if (ln > 3) {
                        const QPointF points[3] = {
                            QPointF(17.0,25.0),
                            QPointF(27.0,25.0),
                            QPointF(27.0,36.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
        }
    } else {    // Низ
        switch (color) {
            case upRectCl: {        // Закраска верху зуба(1-ша частина)
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(0, 255, 255, 255));
                    paint.setPen(QColor(0, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(6.0,27.0),
                            QPointF(22.0,27.0),
                            QPointF(17.0,32.0),
                            QPointF(11.0,32.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln > 0 && ln < 4) {
                        const QPointF points[3] = {
                            QPointF(5.0,26.0),
                            QPointF(22.0,26.0),
                            QPointF(14.0,34.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case upRectBr: {        // Очистка верху зуба(1-ша частина - верх)
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(253, 253, 253, 255));
                    paint.setPen(QColor(253, 253, 253, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(6.0,27.0),
                            QPointF(22.0,27.0),
                            QPointF(17.0,32.0),
                            QPointF(11.0,32.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln > 0 && ln < 4) {
                        const QPointF points[3] = {
                            QPointF(5.0,26.0),
                            QPointF(22.0,26.0),
                            QPointF(14.0,34.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case rightRectCl: {     // Закраска верху зуба(1-ша частина) право
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(1, 255, 255, 255));
                    paint.setPen(QColor(1, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(26.0,27.0),
                            QPointF(26.0,45.0),
                            QPointF(19.0,38.0),
                            QPointF(19.0,34.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(26.0,26.0),
                            QPointF(26.0,45.0),
                            QPointF(17.0,36.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case rightRectBr: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(254, 254, 254, 255));
                    paint.setPen(QColor(254, 254, 254, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(26.0,27.0),
                            QPointF(26.0,45.0),
                            QPointF(19.0,38.0),
                            QPointF(19.0,34.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(26.0,26.0),
                            QPointF(26.0,45.0),
                            QPointF(17.0,36.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case downRectCl: {  // Закраска нижнього паралелограма
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(2, 255, 255, 255));
                    paint.setPen(QColor(2, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(11.0,40.0),
                            QPointF(17.0,40.0),
                            QPointF(24.0,46.0),
                            QPointF(5.0,46.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(14.0,37.0),
                            QPointF(23.0,46.0),
                            QPointF(5.0,46.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case downRectBr: {  // Очистка нижнього паралелограма
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(246, 246, 246, 255));
                    paint.setPen(QColor(246, 246, 246, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(11.0,40.0),
                            QPointF(17.0,40.0),
                            QPointF(24.0,46.0),
                            QPointF(5.0,46.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(14.0,37.0),
                            QPointF(23.0,46.0),
                            QPointF(5.0,46.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case leftRectCl: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(3, 255, 255, 255));
                    paint.setPen(QColor(3, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(2.0,27.0),
                            QPointF(9.0,34.0),
                            QPointF(9.0,38.0),
                            QPointF(2.0,45.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(2.0,27.0),
                            QPointF(11.0,36.0),
                            QPointF(2.0,45.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case leftRectBr: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(247, 247, 247, 255));
                    paint.setPen(QColor(247, 247, 247, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(2.0,27.0),
                            QPointF(9.0,34.0),
                            QPointF(9.0,38.0),
                            QPointF(2.0,45.0)
                        };
                        paint.drawPolygon(points, 4);
                    } else if (ln < 4) {
                        const QPointF points[3] = {
                            QPointF(2.0,27.0),
                            QPointF(11.0,36.0),
                            QPointF(2.0,45.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
            break;
            }
            case centrRectCl: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(4, 255, 255, 255));
                    paint.setPen(QColor(4, 255, 255, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(12.0,34.0),
                            QPointF(16.0,34.0),
                            QPointF(16.0,38.0),
                            QPointF(12.0,38.0)
                        };
                        paint.drawPolygon(points, 4);
                    }
                paint.end();
            break;
            }
            case centrRectBr: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(248, 248, 248, 255));
                    paint.setPen(QColor(248, 248, 248, 255));

                    if (ln > 3) {
                        const QPointF points[4] = {
                            QPointF(12.0,34.0),
                            QPointF(16.0,34.0),
                            QPointF(16.0,38.0),
                            QPointF(12.0,38.0)
                        };
                        paint.drawPolygon(points, 4);
                    }
                paint.end();
                break;
            }
            // Center of teeth
            case center1: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(242, 28, 36, 255));
                    paint.setPen(QColor(242, 28, 36, 255));

                    const QPointF points[3] = {
                        QPointF(14.0,3.0),
                        QPointF(5.0,23.0),
                        QPointF(24.0,23.0)
                    };
                    paint.drawPolygon(points, 3);
                paint.end();
            break;
            }
            case redCenterColor: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(252, 252, 252, 255));
                    paint.setPen(QColor(252, 252, 252, 255));

                    const QPointF points[3] = {
                        QPointF(5.0,23.0),
                        QPointF(14.0,3.0),
                        QPointF(24.0,23.0)
                    };
                    paint.drawPolygon(points, 3);
                paint.end();
            break;
            }
            case left1: {   // Намалювати червоний трикутник на лівому корені
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(Qt::red);
                    paint.setPen(Qt::red);

                    if (ln > 5) {
                        const QPointF points[3] = {
                            QPointF(2.0,24.0),
                            QPointF(2.0,12.0),
                            QPointF(11.0,24.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case redColor: {
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(249, 249, 249, 255));
                    paint.setPen(QColor(249, 249, 249, 255));

                    if (ln > 3) {
                        const QPointF points[3] = {
                            QPointF(2.0,24.0),
                            QPointF(2.0,12.0),
                            QPointF(11.0,24.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case right1: {  // Намалювати червоний трикутник на правому корені
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(241, 28, 36, 255));
                    paint.setPen(QColor(241, 28, 36, 255));

                    if (ln > 3) {
                        const QPointF points[3] = {
                            QPointF(26.0,14.0),
                            QPointF(26.0,23.0),
                            QPointF(17.0,23.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
            case clearRightRoot:{    // Стерти червоний трикутник на правому корені
                paint.begin(&m_imgOfTeeth[index]);
                    paint.setBrush(Qt::SolidPattern);
                    paint.setBrush(QColor(251, 251, 251, 255));
                    paint.setPen(QColor(251, 251, 251, 255));

                    if (ln > 3) {
                        const QPointF points[3] = {
                            QPointF(26.0,14.0),
                            QPointF(26.0,23.0),
                            QPointF(17.0,23.0)
                        };
                        paint.drawPolygon(points, 3);
                    }
                paint.end();
            break;
            }
        }
    }


    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    m_imgOfTeeth[index].save( &buf, "BMP" );
    buf.close();
    QPixmap px;
    px.loadFromData(ba);
    m_lblWithTeeth[index]->setPixmap(px);

    QSqlQuery query;
    query.prepare("UPDATE legendstateofteeth SET sqrtOfTeeth=:sqrtOfTeeth WHERE id=:id AND nOfTeeth=:nOfTeeth;");
    query.bindValue(":sqrtOfTeeth", ba);
    query.bindValue(":id", iSelectPacient);
    query.bindValue(":nOfTeeth", nOfTeeth);
    if (!query.exec()) {
        query.lastError().text();
    }
}
