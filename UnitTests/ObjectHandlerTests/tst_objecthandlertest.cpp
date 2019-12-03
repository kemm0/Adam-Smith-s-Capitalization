#include <QtTest>

// add necessary includes here
#include "gameobjectmanager.h"

class ObjectHandlerTest : public QObject
{
    Q_OBJECT

public:
    ObjectHandlerTest();
    ~ObjectHandlerTest();

private slots:
    void test_case1();

};

ObjectHandlerTest::ObjectHandlerTest()
{

}

ObjectHandlerTest::~ObjectHandlerTest()
{

}

void ObjectHandlerTest::test_case1()
{

}

QTEST_APPLESS_MAIN(ObjectHandlerTest)

#include "tst_objecthandlertest.moc"
