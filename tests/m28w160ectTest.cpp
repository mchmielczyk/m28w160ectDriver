#include "m28w160ectTest.hpp"
extern "C"{
extern STM28W_Env MOCK_Env;
}
TEST_GROUP(m28w)
{
    void setup(){}
    void teardown(){
        mock().checkExpectations();
        mock().clear();
    }
};
//call funkjca - wejscie rcfi - odczytmanufacter - odczyt device - wyjscie read - return
TEST(m28w,ProperInit)
{
    mock().expectOneCall("rcfiC_FN");
    mock().expectOneCall("read_FN").withParameter("reg",0x00).andReturnValue(0x0020);
    mock().expectOneCall("read_FN").withParameter("reg",0x01).andReturnValue(0x88CE);
    mock().expectOneCall("readC_FN");
    mock().returnIntValueOrDefault(0);
    STM28W_CheckDevice(&MOCK_Env);

    STM28W_Status result = STM28W_CheckDevice(&MOCK_Env);
    CHECK_EQUAL(STM28W_OK, result);
}