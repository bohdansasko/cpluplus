#include "mysortfilterproxymodel.h"

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
{

}

QDate MySortFilterProxyModel::filterMinimumDate() const {
    return minDate;
}

void MySortFilterProxyModel::setFilterMinimumDate(const QDate &date) {
    minDate = date;
    invalidateFilter();
}

QDate MySortFilterProxyModel::filterMaximumDate() const { return maxDate; }

void MySortFilterProxyModel::setFilterMaximumDate(const QDate &date) {
    maxDate = date;
    invalidateFilter();
}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE {
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

    return (sourceModel()->data(index0).toString().contains(filterRegExp())
            || sourceModel()->data(index1).toString().contains(filterRegExp()))
            && dateInRange(sourceModel()->data(index2).toDate());
}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE {
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if (leftData.type() == QVariant::DateTime) {
        return leftData.toDateTime() < rightData.toDateTime();
    } else {
        QString s1 = leftData.toString();
        QString s2 = rightData.toString();

        QString alphabet = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";
        alphabet += "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";

        const quint16 s1Length = s1.length();
        const quint16 s2Length = s2.length();

        for (int i = 0; i != s1Length || i != s2Length; ++i) {
            quint16 posS1 = 0;
            quint16 posS2 = 0;
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
            else if (posS1 < posS2)
                return true;
            else if (posS1 > posS2)
                return false;
        }
    }
}

bool MySortFilterProxyModel::dateInRange(const QDate &date) const {
    return (!minDate.isValid() || date > minDate)
            && (!maxDate.isValid() || date < maxDate);
}
