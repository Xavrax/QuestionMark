#ifndef QUESTIONMARK_HEADER
#define QUESTIONMARK_HEADER

#include <memory>

template <typename T, typename E>
class Result {
public:
    /// Creates successful result with some data
    static Result Ok(T value) {
        return Result(std::make_unique<T>(value), nullptr);
    }

    /// Creates result containing error
    static Result Err(E error) {
        return Result(nullptr, std::make_unique<E>(error));
    }

    /// Checks if result containing some data
    bool is_ok() const {
        return _ok != nullptr;
    }

    /// Checks if result containing error
    bool is_err() const {
        return _err != nullptr;
    }

    /// Checks if results containing given value
    bool contains(T value) {
        if (is_ok()) {
            return *_ok == value;
        }

        return false;
    }

    /// Checks if results containing given error
    bool contains_err(E error) {
        if (is_err()) {
            return *_err == error;
        }

        return false;
    }

private:
    Result(std::unique_ptr<T> ok, std::unique_ptr<E> err) {
        this->_ok = std::move(ok);
        this->_err = std::move(err);
    }

    std::unique_ptr<T> _ok;
    std::unique_ptr<E> _err;
};



#endif //QUESTIONMARK_HEADER
