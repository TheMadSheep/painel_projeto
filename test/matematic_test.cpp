#include <gtest/gtest.h>
#include "../include/matematica.h"

TEST(MatematicaTest, Soma) {
    EXPECT_EQ(matematica::somar(2, 3), 5);
    EXPECT_EQ(matematica::somar(-1, 1), 0);
    EXPECT_EQ(matematica::somar(-5, -3), -8);
}

TEST(MatematicaTest, Subtracao) {
    EXPECT_EQ(matematica::subtrair(5, 3), 2);
    EXPECT_EQ(matematica::subtrair(0, 3), -3);
    EXPECT_EQ(matematica::subtrair(-5, -3), -2);
}

