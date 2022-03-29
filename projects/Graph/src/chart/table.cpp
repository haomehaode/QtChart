#pragma execution_character_set("utf-8")

#include "table.h"

Table::Table(QWidget *parent)
	: QWidget(parent)
{
	m_table = new QTableWidget();
	m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(m_table);
	setLayout(layout);
}

Table::~Table()
{

}

void Table::add_data(QList<double>& list, const QString& name)
{
	m_head_list.append(name);
	m_table->setColumnCount(m_head_list.size());
	m_table->setHorizontalHeaderLabels(m_head_list);
	for (int i = 0;  i < list.size(); i++) 
	{
		int count = m_table->rowCount();
		if (i < count)
			m_table->setItem(i, m_head_list.size()-1,new QTableWidgetItem(QString::number(list[i]))); 
		else
		{
			m_table->setRowCount(count + 1);
			m_table->setItem(count, m_head_list.size() - 1, new QTableWidgetItem(QString::number(list[i]))); 
		}
	}
}

void Table::add_data(QList<int>& list, const QString& name)
{
	m_head_list.append(name);
	m_table->setColumnCount(m_head_list.size());
	m_table->setHorizontalHeaderLabels(m_head_list);
	for (int i = 0; i < list.size(); i++)
	{
		int count = m_table->rowCount();
		if (i < count)
			m_table->setItem(i, m_head_list.size() - 1, new QTableWidgetItem(QString::number(list[i])));
		else
		{
			m_table->setRowCount(count + 1);
			m_table->setItem(count, m_head_list.size() - 1, new QTableWidgetItem(QString::number(list[i]))); 
		}
	}
}

void Table::add_data(QList<QString>& list, const QString& name)
{
	m_head_list.append(name);
	m_table->setColumnCount(m_head_list.size());
	m_table->setHorizontalHeaderLabels(m_head_list);
	for (int i = 0; i < list.size(); i++)
	{
		int count = m_table->rowCount();
		if (i < count)
			m_table->setItem(i, m_head_list.size() - 1, new QTableWidgetItem(list[i]));
		else
		{
			m_table->setRowCount(count + 1);
			m_table->setItem(count, m_head_list.size() - 1, new QTableWidgetItem(list[i])); 
		}
	}
}

void Table::delete_data(const QString& name)
{
	m_head_list.removeOne(name);
	m_table->setColumnCount(m_head_list.size());
	m_table->setHorizontalHeaderLabels(m_head_list);
}
