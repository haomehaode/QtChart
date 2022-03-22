#ifndef TABLE_H
#define TABLE_H

#include "graph_global.h"

#include <QWidget>
#include <QTableWidget>
#include <QBoxLayout>

class GRAPH_EXPORT Table : public QWidget
{
	Q_OBJECT

public:

	Table(QWidget* parent = nullptr);

	~Table();

public:

	void add_data(QList<double>& list, const QString& name);

	void add_data(QList<int>& list, const QString& name);

	void add_data(QList<QString>& list, const QString& name);

	void delete_data(const QString& name);

private:

	QTableWidget* m_table = nullptr;

	QStringList m_head_list;

};

#endif // TABLE_H