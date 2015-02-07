namespace super_ast {
class StreamWrapper {
public:
    typedef char Ch;

    StreamWrapper(std::istream& is) : is_(is) {
    }

    Ch Peek() const {
        int c = is_.peek();
        return c == std::char_traits<char>::eof() ? '\0' : (Ch) c;
    }

    Ch Take() {
        int c = is_.get();
        return c == std::char_traits<char>::eof() ? '\0' : (Ch) c;
    }

    size_t Tell() const {
        return (size_t) is_.tellg();
    }

    Ch* PutBegin() {
        assert(false);
        return 0;
    }

    void Put(Ch) {
        assert(false);
    }

    void Flush() {
        assert(false);
    }

    size_t PutEnd(Ch*) {
        assert(false);
        return 0;
    }

private:
    StreamWrapper(const StreamWrapper&);

    StreamWrapper& operator=(const StreamWrapper&);

    std::istream& is_;
};
}
