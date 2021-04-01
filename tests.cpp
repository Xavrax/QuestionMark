#define CATCH_CONFIG_MAIN
#include "external/catch2.hpp"
#include "question_mark.hpp"

namespace tests {
    TEST_CASE("check Result's methods", "[Result<T,E>]") {
        SECTION("is ok") {
            REQUIRE(Result<int, int>::Ok(10).is_ok());
            REQUIRE_FALSE(Result<int, int>::Err(10).is_ok());
        }

        SECTION("is err") {
            REQUIRE(Result<int, int>::Err(10).is_err());
            REQUIRE_FALSE(Result<int, int>::Ok(10).is_err());
        }

        SECTION("contains") {
            REQUIRE(Result<int, int>::Ok(10).contains(10));
            REQUIRE_FALSE(Result<int, int>::Ok(20).contains(10));
            REQUIRE_FALSE(Result<int, int>::Err(10).contains(10));
        }

        SECTION("contains_err") {
            REQUIRE(Result<int, int>::Err(10).contains_err(10));
            REQUIRE_FALSE(Result<int, int>::Err(20).contains_err(10));
            REQUIRE_FALSE(Result<int, int>::Ok(10).contains_err(10));
        }
    }
}
