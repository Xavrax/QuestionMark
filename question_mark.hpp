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

    std::unique_ptr<T> _ok;
    std::unique_ptr<E> _err;
private:
    Result(std::unique_ptr<T> ok, std::unique_ptr<E> err) {
        this->_ok = std::move(ok);
        this->_err = std::move(err);
    }
};



#endif //QUESTIONMARK_HEADER
