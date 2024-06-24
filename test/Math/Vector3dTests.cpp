/*
 * Project: Cedar-Core
 * Copyright (C) 2024 Cedar Community
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>
#include <Cedar/Core/String.h>
#include <Cedar/Core/Exceptions/OutOfRangeException.h>
#include <Cedar/Core/Container/List.h>

#include <Cedar/Core/Math/Vector.h>

namespace Cedar::Core::Math {

    // Test the default constructor
    TEST(Vector3dTest, DefaultConstructor) {
        Math::Vec3d v3d{};
        EXPECT_DOUBLE_EQ(v3d[0], 0.0);
        EXPECT_DOUBLE_EQ(v3d[1], 0.0);
        EXPECT_DOUBLE_EQ(v3d[2], 0.0);
    }

    // Test the parameterized constructor
    TEST(Vector3dTest, ArgsConstructor) {
        Math::Vec3d v3d(1.0, 3.2, 2.5);
        EXPECT_DOUBLE_EQ(v3d[0], 1.0);
        EXPECT_DOUBLE_EQ(v3d[1], 3.2);
        EXPECT_DOUBLE_EQ(v3d[2], 2.5);
    }

    // Test unary positive operator (should return the original vector unchanged)
    TEST(Vector3dTest, PositiveOp) {
        Math::Vec3d v3d(-2.4, 6.7, 24.2);

        Math::Vec3d temp = +v3d; // Unary plus should not change the vector

        EXPECT_DOUBLE_EQ(temp[0], -2.4);
        EXPECT_DOUBLE_EQ(temp[1], 6.7);
        EXPECT_DOUBLE_EQ(temp[2], 24.2);
    }

    // Test unary negative operator
    TEST(Vector3dTest, NegativeOp) {
        Math::Vec3d v3d(-2.4, 6.7, -24.2);

        Math::Vec3d temp = -v3d;

        EXPECT_DOUBLE_EQ(temp[0], 2.4);
        EXPECT_DOUBLE_EQ(temp[1], -6.7);
        EXPECT_DOUBLE_EQ(temp[2], 24.2);
    }

    // Test addition operator
    TEST(Vector3dTest, AddOp) {
        Math::Vec3d v3d_0(-2.4, 6.7, 24.3);
        Math::Vec3d v3d_1(-12.73, -7.31, 337.21);

        Math::Vec3d temp = v3d_0 + v3d_1;

        EXPECT_DOUBLE_EQ(temp[0], (-2.4 + -12.73));
        EXPECT_DOUBLE_EQ(temp[1], (6.7 + -7.31));
        EXPECT_DOUBLE_EQ(temp[2], (24.3 + 337.21));
    }

    // Test subtraction operator
    TEST(Vector3dTest, SubOp) {
        Math::Vec3d v3d_0(-2.4, 6.7, 24.0);
        Math::Vec3d v3d_1(-12.73, -7.31, 35.1);

        Math::Vec3d temp = v3d_0 - v3d_1;

        EXPECT_DOUBLE_EQ(temp[0], (-2.4 - -12.73));
        EXPECT_DOUBLE_EQ(temp[1], (6.7 - -7.31));
        EXPECT_DOUBLE_EQ(temp[2], (24.0 - 35.1));
    }

    // Test multiplication operator (component-wise multiplication)
    TEST(Vector3dTest, MulOp) {
        Math::Vec3d v3d_0(-2.4, 6.7, 24.0);
        Math::Vec3d v3d_1(-12.73, -7.31, 35.1);

        Math::Vec3d temp = v3d_0 * v3d_1;

        EXPECT_DOUBLE_EQ(temp[0], (-2.4 * -12.73));
        EXPECT_DOUBLE_EQ(temp[1], (6.7 * -7.31));
        EXPECT_DOUBLE_EQ(temp[2], (24.0 * 35.1));
    }

    // Test division operator (component-wise division)
    TEST(Vector3dTest, DivOp) {
        Math::Vec3d v3d_0(-2.4, 6.7, 24.0);
        Math::Vec3d v3d_1(-12.73, -7.31, 35.1);

        Math::Vec3d temp = v3d_0 / v3d_1;

        EXPECT_DOUBLE_EQ(temp[0], (-2.4 / -12.73));
        EXPECT_DOUBLE_EQ(temp[1], (6.7 / -7.31));
        EXPECT_DOUBLE_EQ(temp[2], (24.0 / 35.1));
    }

    // Test equality operator
    TEST(Vector3dTest, EqualOp) {
        Math::Vec3d v3d_0(-2.4, 6.7, 2.4);
        Math::Vec3d v3d_1(-12.73, -7.31, 84.9);
        bool temp = v3d_0 == v3d_1;
        EXPECT_FALSE(temp);

        Math::Vec3d v3d_2(-2.4, 6.7, 25.1);
        Math::Vec3d v3d_3(-2.4, 6.7, 25.1);
        bool temp_1 = v3d_2 == v3d_3;
        EXPECT_TRUE(temp_1);
    }

    // Test inequality operator
    TEST(Vector3dTest, InverseEqualOp) {
        Math::Vec3d v3d_0(-2.4, 6.7, 2.4);
        Math::Vec3d v3d_1(-12.73, -7.31, 84.9);
        bool temp = v3d_0 != v3d_1;
        EXPECT_TRUE(temp);

        Math::Vec3d v3d_2(-2.4, 6.7, 25.1);
        Math::Vec3d v3d_3(-2.4, 6.7, 25.1);
        bool temp_1 = v3d_2 != v3d_3;
        EXPECT_FALSE(temp_1);
    }
}
