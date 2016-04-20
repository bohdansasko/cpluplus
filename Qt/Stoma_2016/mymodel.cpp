#include "mymodel.h"

MyModel::MyModel(QObject *parent): QAbstractProxyModel(parent) {

}

QModelIndex MyModel::mapFromSource(const QModelIndex &sourceIndex) const {
    return index(sourceIndex.column(), sourceIndex.row());
}

QModelIndex MyModel::mapToSource(const QModelIndex &proxyIndex) const {
    return sourceModel()->index(proxyIndex.column(), proxyIndex.row());
}

QModelIndex MyModel::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column);
    Q_UNUSED(parent);
}

QModelIndex MyModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal)
        return sourceModel()->headerData(section, Qt::Vertical, role);
    else
        return sourceModel()->headerData(section, Qt::Horizontal, role);
}

int MyModel::rowCount(const QModelIndex & parent) const
{
   return sourceModel()->columnCount(parent);
}

int MyModel::columnCount(const QModelIndex & parent) const
{
    return sourceModel()->rowCount(parent);
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    return sourceModel()->data(mapToSource(index), role);
}

bool MyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE {
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    QString s1 = leftData.toString();
    QString s2 = rightData.toString();

    QString alphabet = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";
            alphabet += "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";

    const quint16 s1Length = s1.length();
    const quint16 s2Length = s2.length();
    quint16 posS1;
    quint16 posS2;
    for (int i = 0; i != s1Length || i != s2Length; ++i) {
        posS1 = 0;
        posS2 = 0;
        for (int j = 0; j < alphabet.length(); ++j) {
            if (s1[i] == alphabet[j]) {
                posS1 = j;
                break;
            }
        }

        for (int j = 0; j < alphabet.length(); ++j) {
            if (s2[i] == alphabet[j]) {
                posS2 = j;
                break;
            }
        }

        if (posS1 == posS2)
            continue;

        if (posS1 < posS2)
            return true;
        else
            return false;
    }

}
