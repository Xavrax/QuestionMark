#ifndef QUESTION_MARK_HEADER
#define QUESTION_MARK_HEADER

/// Mimic panic macro as exit with error code -1
#ifndef PANIC
#define PANIC(ERROR) {std::cout << "Program panicked! Error: " << ERROR << std::endl; exit(1);};
#endif

#include <memory>

/// Option class containing value or none
template <typename T>
class Option {
public:
    /// Creates option containing value
    static Option Some(T value) {
        return Some(std::make_unique<T>(value));
    }

    /// Creates option containing value
    static Option Some(std::unique_ptr<T> ptr) {
        return Option(std::move(ptr));
    }

    /// Creates option containing none
    static Option None() {
        return Option(nullptr);
    }

    /// Checks if option contains value
    bool is_some() const {
        return _some != nullptr;
    }

    /// Checks if option contains none
    bool is_none() const {
        return _some == nullptr;
    }

    /// Checks if option contains given value
    bool contains(T value) {
        if (is_some()) {
            return *_some == value;
        }

        return false;
    }

    /// Returns contained value and
    T expect(const std::string& msg) {
        if (is_none()) {
            PANIC(msg);
        }

        return T(*_some);
    }

    T unwrap() {
        if (is_none()) {
            PANIC("Option::unwrap() called on a None");
        }

        return T(*_some);
    }

private:
    explicit Option(std::unique_ptr<T> value) {
        this->_some = std::move(value);
    }

    std::unique_ptr<T> _some;
};

/// Result class containing data on successful or error
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



#endif //QUESTION_MARK_HEADER
