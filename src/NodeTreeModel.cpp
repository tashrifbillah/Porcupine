#include "NodeTreeModel.hpp"
#include "PortPair.hpp"

NodeTreeModel::NodeTreeModel(
        ) :
    QStandardItemModel()
{
    setHorizontalHeaderItem(0, new QStandardItem( "Node" ));
    setHorizontalHeaderItem(1, new QStandardItem( "File name" ));
    setHorizontalHeaderItem(2, new QStandardItem( "Data type" ));
}


void NodeTreeModel::addNode(
        const Node* _node
        )
{
    QStandardItem* item = new QStandardItem(_node->getName());
    foreach(PortPair* pair, _node->getPorts())
    {
        QList<QStandardItem*> ports;

        QStandardItem* nameItem = new QStandardItem(pair->getName());
        nameItem->setEditable(false);
        ports.append(nameItem);

        QStandardItem* fileItem = new QStandardItem("<file name>");
        fileItem->setEditable(true);
        ports.append(fileItem);

        QStandardItem* dataItem = new QStandardItem(pair->getType()[0]->getName());
        dataItem->setEditable(false);
        ports.append(dataItem);

        item->appendRow(ports);
    }
    setItem(this->rowCount(), 0, item);
}

NodeTreeModel::~NodeTreeModel(
        )
{
//    delete all items;
}
