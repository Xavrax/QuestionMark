#ifndef QUESTION_MARK_HEADER
#define QUESTION_MARK_HEADER

/// Mimic panic macro as exit with error code -1
#ifndef PANIC
#define PANIC(ERROR) {std::cout << "Program panicked! Error: " << ERROR << std::endl; exit(1);};
#endif

#include <memory>

template <typename T, typename E>
class Result;

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
    bool contains(T value) const {
        if (is_some()) {
            return *_some == value;
        }

        return false;
    }

    /// Returns contained value or panic with given message
    /// when value is none
    T expect(const std::string& msg) const {
        if (is_none()) {
            PANIC(msg);
        }

        return T(*_some);
    }

    /// Returns contained value or panic when value is none
    T unwrap() const {
        if (is_none()) {
            PANIC("Option::unwrap() called on a None");
        }

        return T(*_some);
    }

    /// Returns contained value or use given if not exists
    T unwrap_or(T value) const {
        if (is_none()) {
            return value;
        }

        return T(*_some);
    }

    /// Returns contained value or calls given function and takes
    /// him value
    T unwrap_or_else(std::function<T(void)> fn) const {
        if (is_none()) {
            return fn();
        }

        return T(*_some);
    }

    /// Maps an Option<T> to Option<U> by applying a function to a contained value
    /// or panic on no data;
    template<typename U>
    Option<U> map(std::function<U(T)> fn) const {
        if (is_none()) {
            return Option<U>::None();
        }

        return Option<U>::Some(fn(*_some));
    }

    /// Maps an Option<T> to Option<U> by applying a function to a contained value
    /// or use given if data not exists.
    template<typename U>
    Option<U> map_or(U value, std::function<U(T)> fn) const {
        if (is_none()) {
            return Option<U>::Some(value);
        }

        return Option<U>::Some(fn(*_some));
    }

    /// Maps an Option<T> to Option<U> by applying a function to a contained value
    /// or use default function given.
    template<typename U>
    Option<U> map_or_else(std::function<U(void)> fn_else, std::function<U(T)> fn) const {
        if (is_none()) {
            return Option<U>::Some(fn_else());
        }

        return Option<U>::Some(fn(*_some));
    }

    /// Returns Result with contained value or Error with the given one
    template<typename E>
    Result<T, E> ok_or(E value) {
        if (is_none()) {
            return Result<T, E>::Err(value);
        }

        return Result<T, E>::Ok(*_some);
    }

    /// Returns Result with contained value or Error with the given one
    template<typename E>
    Result<T, E> ok_or_else(std::function<E(void)> fn) {
        if (is_none()) {
            return Result<T, E>::Err(fn());
        }

        return Result<T, E>::Ok(*_some);
    }

    bool operator== (const Option<T>& other) const {
        if (is_none() || other.is_none()) {
            return is_none() && other.is_none();
        }

        return *_some == *other._some;
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

    bool operator== (const Result<T, E>& other) const {
        if (is_ok() && other.is_ok()) {
            return *_ok == *other._ok;
        } else if (is_err() && other.is_err()) {
            return *_err == *other._err;
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
