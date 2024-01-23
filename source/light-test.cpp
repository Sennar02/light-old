#include <light/Memory/import.hpp>
#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

using namespace lgh;

TEST_GROUP(round) {};

TEST(round, is_aligned)
{
    char* memory = (char*) 0x1;

    for ( u32 i = 2u; i < 16u; i *= 2u )
        CHECK_EQUAL(round(memory, i), i - 1u);

    CHECK_EQUAL(round(memory, 1u), 0u);
}

int
main(int argc, const char* argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
