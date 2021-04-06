#define CATCH_CONFIG_MAIN
#include "external/catch2.hpp"
#include "question_mark.hpp"

namespace tests {
    TEST_CASE("check Option's methods", "[Option<T>]") {
        SECTION("is_some") {
            REQUIRE(Option<int>::Some(10).is_some());
            REQUIRE_FALSE(Option<int>::None().is_some());
        }

        SECTION("is_none") {
            REQUIRE(Option<int>::None().is_none());
            REQUIRE_FALSE(Option<int>::Some(10).is_none());
        }

        SECTION("contains") {
            REQUIRE(Option<int>::Some(10).contains(10));
            REQUIRE_FALSE(Option<int>::Some(20).contains(10));
            REQUIRE_FALSE(Option<int>::None().contains(10));
        }

        SECTION("expect") {
            REQUIRE(Option<int>::Some(10).expect("") == 10);
            REQUIRE_FALSE(Option<int>::Some(20).expect("") == 10);
        }

        SECTION("unwrap") {
            REQUIRE(Option<int>::Some(10).unwrap() == 10);
            REQUIRE_FALSE(Option<int>::Some(20).unwrap() == 10);
        }

        SECTION("unwrap_or") {
            REQUIRE(Option<int>::Some(10).unwrap_or(20) == 10);
            REQUIRE(Option<int>::None().unwrap_or(20) == 20);
        }

        SECTION("unwrap_or_else") {
            REQUIRE(Option<int>::Some(10).unwrap_or_else([]{return 20;}) == 10);
            REQUIRE(Option<int>::None().unwrap_or_else([]{return 20;}) == 20);
        }

        SECTION("operator==") {
            REQUIRE(Option<int>::Some(10) == Option<int>::Some(10));
            REQUIRE_FALSE(Option<int>::Some(10) == Option<int>::None());
            REQUIRE(Option<int>::None() == Option<int>::None());
        }

        SECTION("map") {
            REQUIRE(Option<std::string>::Some(std::string("test")).map<int>([](auto s){return s.length();}) == Option<int>::Some(4));
            REQUIRE(Option<std::string>::None().map<int>([](auto s){return s.length();}) == Option<int>::None());
        }

        SECTION("map_or") {
            REQUIRE(Option<std::string>::Some(std::string("test")).map_or<int>(10, [](auto s){return s.length();}) == Option<int>::Some(4));
            REQUIRE(Option<std::string>::None().map_or<int>(10, [](auto s){return s.length();}) == Option<int>::Some(10));
        }

        SECTION("map_or_else") {
            REQUIRE(Option<std::string>::Some(std::string("test")).map_or_else<int>([]{return 10;}, [](auto s){return s.length();}) == Option<int>::Some(4));
            REQUIRE(Option<std::string>::None().map_or_else<int>([]{return 10;}, [](auto s){return s.length();}) == Option<int>::Some(10));
        }

        SECTION("ok_or") {
            REQUIRE(Option<int>::Some(10).ok_or(20) == Result<int, int>::Ok(10));
            REQUIRE(Option<int>::None().ok_or(20) == Result<int, int>::Err(20));
        }

        SECTION("ok_or_else") {
            REQUIRE(Option<int>::Some(10).ok_or_else<int>([]{return 20;}) == Result<int, int>::Ok(10)); // todo: compiler cannot deduct
            REQUIRE(Option<int>::None().ok_or_else<int>([]{return 20;}) == Result<int, int>::Err(20));  //       type of returning value
                                                                                                        //       from lambda
        }

        SECTION("and") {
            REQUIRE(Option<int>::Some(10).and_(Option<int>::Some(20)) == Option<int>::Some(20));
            REQUIRE(Option<int>::None().and_(Option<int>::Some(20)) == Option<int>::None());
            REQUIRE(Option<int>::None().and_(Option<int>::None()) == Option<int>::None());
            REQUIRE(Option<int>::Some(20).and_(Option<int>::None()) == Option<int>::None());
        }

        SECTION("and_then") {
            REQUIRE(Option<int>::Some(10).and_then<int>([]{return Option<int>::Some(20);}) == Option<int>::Some(20)); // todo: compiler cannot deduct
            REQUIRE(Option<int>::None().and_then<int>([]{return Option<int>::Some(20);}) == Option<int>::None());     //       type of returning value
            REQUIRE(Option<int>::None().and_then<int>([]{return Option<int>::None();}) == Option<int>::None());       //       from lambda
            REQUIRE(Option<int>::Some(10).and_then<int>([]{return Option<int>::None();}) == Option<int>::None());
        }

        SECTION("filter") {
            REQUIRE(Option<int>::Some(10).filter([](auto _){return true;}) == Option<int>::Some(10));
            REQUIRE(Option<int>::Some(10).filter([](auto _){return false;}) == Option<int>::None());
            REQUIRE(Option<int>::None().filter([](auto _){return true;}) == Option<int>::None());
            REQUIRE(Option<int>::None().filter([](auto _){return false;}) == Option<int>::None());
        }

        SECTION("or") {
            REQUIRE(Option<int>::Some(10).or_(Option<int>::Some(20)) == Option<int>::Some(10));
            REQUIRE(Option<int>::None().or_(Option<int>::Some(20)) == Option<int>::Some(20));
            REQUIRE(Option<int>::None().or_(Option<int>::None()) == Option<int>::None());
            REQUIRE(Option<int>::Some(10).or_(Option<int>::None()) == Option<int>::Some(10));
        }

        SECTION("or_else") {
            REQUIRE(Option<int>::Some(10).or_else<int>([](){return Option<int>::Some(20);}) == Option<int>::Some(10)); // todo: compiler cannot deduct
            REQUIRE(Option<int>::None().or_else<int>([](){return Option<int>::Some(20);}) == Option<int>::Some(20));   //       type of returning value
            REQUIRE(Option<int>::None().or_else<int>([](){return Option<int>::None();}) == Option<int>::None());       //       from lambda
            REQUIRE(Option<int>::Some(10).or_else<int>([](){return Option<int>::None();}) == Option<int>::Some(10));
        }

        SECTION("xor") {
            REQUIRE(Option<int>::Some(10).xor_(Option<int>::Some(20)) == Option<int>::None());
            REQUIRE(Option<int>::None().xor_(Option<int>::Some(20)) == Option<int>::Some(20));
            REQUIRE(Option<int>::None().xor_(Option<int>::None()) == Option<int>::None());
            REQUIRE(Option<int>::Some(10).xor_(Option<int>::None()) == Option<int>::Some(10));
        }
    }

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

        SECTION("operator==") {
            REQUIRE(Result<int, int>::Ok(10) == Result<int, int>::Ok(10));
            REQUIRE(Result<int, int>::Err(10) == Result<int, int>::Err(10));
            REQUIRE_FALSE(Result<int, int>::Ok(10) == Result<int, int>::Err(10));
            REQUIRE_FALSE(Result<int, int>::Ok(10) == Result<int, int>::Ok(20));
            REQUIRE_FALSE(Result<int, int>::Err(10) == Result<int, int>::Err(20));
        }

        SECTION("ok") {
//            Result<int, int>::Ok(10).asd(10);
//            REQUIRE(Result<int, int>::Ok(10).ok() == Option<int>::Some(10));
        }
    }
}
