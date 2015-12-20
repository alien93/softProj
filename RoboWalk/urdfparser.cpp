#include "urdfparser.h"
#include <QDebug>

//konstruktor
URDFparser::URDFparser()
{
}

void URDFparser::parseChildNodes(QDomElement root, int i)
{
    QDomNode node = root.childNodes().at(i);

    if(node.isElement())
    {
        QDomElement nodeElement = node.toElement();
        qDebug()<<nodeElement.tagName();

        if(node.childNodes().size()!=0)
        {
            for(int i=0; i<node.childNodes().count(); i++)
            parseChildNodes(nodeElement, i);
        }

    }



}

int URDFparser::parseURDF(QString filename)
{
    QDomDocument document;

    //loading file
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Failed to open file";
        return -1;
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug()<<"Failed to load document";
            return -1;
        }
        file.close();
    }

    //root element
    QDomElement root = document.firstChildElement();
    for(int i=0; i<root.childNodes().count(); i++)
    {
        parseChildNodes(root, i);
    }
}
