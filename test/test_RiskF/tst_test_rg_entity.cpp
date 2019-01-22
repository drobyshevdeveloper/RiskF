#include <QString>
#include <QtTest>

#include "../../src/lib/engine/rg_vector.h"
#include "../../src/lib/engine/rg_line.h"

class Test_rg_Line : public QObject
{
    Q_OBJECT

public:
    Test_rg_Line();

private Q_SLOTS:
    void testCase1();
};

Test_rg_Line::Test_rg_Line()
{
}

void Test_rg_Line::testCase1()
{
    RG_Vector v1 = RG_Vector(0.0, 0,0);
    RG_Vector v2 = RG_Vector(10.0, 10.0);

    RG_Line *pLine = new RG_Line(nullptr, {v1, v2});
    QCOMPARE(pLine->getStartPoint(), RG_Vector(0.0, 0.0));
    QCOMPARE(pLine->getEndPoint(), RG_Vector(0.0, 0.0));
    delete pLine;
}

QTEST_APPLESS_MAIN(Test_rg_Line)

#include "tst_test_rg_entity.moc"
