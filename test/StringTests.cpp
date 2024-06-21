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
#include <Cedar/Core/OutOfRangeException.h>
#include <Cedar/Core/Container/List.h>
#include <Cedar/Core/InvalidStateException.h>

namespace Cedar::Core {
// Test default constructor
    TEST(StringTest, DefaultConstructor) {
        String str;
        EXPECT_EQ(str.length(), 0);
        EXPECT_TRUE(str.rawString() == nullptr);
    }

// Test constructor from C string
    TEST(StringTest, ConstructFromCString) {
        String str("hello");
        EXPECT_EQ(str.length(), 5);
        EXPECT_STREQ(str.rawString(), "hello");
    }

// Test copy constructor
    TEST(StringTest, CopyConstructor) {
        String original("test");
        String copy(original);
        EXPECT_EQ(copy, original);
    }

// Test move constructor
    TEST(StringTest, MoveConstructor) {
        String original("move");
        String moved(std::move(original));

        // Check that the moved-to object has the correct length
        EXPECT_EQ(moved.length(), 4);

        // Check that accessing the moved-from object throws an exception
        try {
            original.length();  // This should throw an exception
            FAIL() << "Expected InvalidStateException";
        } catch (InvalidStateException const & err) {
            EXPECT_EQ(err.what(), std::string("Attempt to use a moved-from String object."));
        } catch (...) {
            FAIL() << "Expected InvalidStateException";
        }

        // Alternatively, check for nullptr directly if that's how you handle moved-from state
        EXPECT_TRUE(original.rawString() == nullptr);
    }

// Test for Unicode support
    TEST(StringTest, UnicodeHandling) {
        String unicode("你好🌍");
        EXPECT_EQ(unicode.length(), 3);
        EXPECT_TRUE(std::string(unicode.rawString()) == "你好🌍");
    }

// Test emojis
    TEST(StringTest, EmojiHandling) {
        String emoji("😊👍");
        EXPECT_EQ(emoji.length(), 2); // Assumes UTF-8 where each emoji is 4 bytes
        EXPECT_TRUE(std::string(emoji.rawString()) == "😊👍");
    }

// Test string operations
    TEST(StringTest, StringOperations) {
        String s("  trim me  ");
        EXPECT_EQ(s.trim(), "trim me");
        String prefix("unimportant");
        String important("important");
        EXPECT_TRUE(important.startsWith(prefix.stripPrefix("un")));
        EXPECT_TRUE(important.endsWith("tant"));
    }

// Test splitting strings
    TEST(StringTest, SplitStrings) {
        String s("one,two,three");
        auto parts = s.split(",");
        ASSERT_EQ(parts.size(), 3);
        EXPECT_EQ(parts[0], "one");
        EXPECT_EQ(parts[1], "two");
        EXPECT_EQ(parts[2], "three");
    }

}  // namespace Cedar::Core
