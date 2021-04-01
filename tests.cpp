#define CATCH_CONFIG_MAIN
#include "external/catch2.hpp"
#include "question_mark.hpp"

namespace tests {
    TEST_CASE("check Result's methods", "[Result<T,E>]") {
        SECTION("is ok") {
            REQUIRE(Result<int, int>::Ok(10).is_ok());
            REQUIRE_FALSE(Result<int, int>::Err(10).is_ok());
        }
    }
}
