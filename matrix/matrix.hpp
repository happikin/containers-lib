namespace ylib {
    #include <memory.h>
    namespace math {

        template <typename type>
        class matrix {
            public:
                matrix() : data(nullptr), m_rows(0), m_cols(0) {std::cout << "def\n";}

                matrix(unsigned int _rows, unsigned int _columns) : m_rows(_rows), m_cols(_columns) {                    
                    this->data = new type[this->m_rows * this->m_cols]{};
                    std::cout << "par cons\n";
                }

                matrix(unsigned int _rows, unsigned int _columns, type _default_val)
                : m_rows(_rows), m_cols(_columns) {
                    this->data = new type[this->m_rows * this->m_cols]{_default_val};
                    std::cout << "par cons\n";
                }

                matrix(const matrix& _mat)
                : m_rows(_mat.m_rows), m_cols(_mat.m_cols) {
                    std::cout << "copy\n";
                    this->data = new type[this->m_cols * this->m_rows];
                    memcpy((void*)this->data, (const void*)_mat.data, (_mat.m_cols * _mat.m_rows * sizeof(type)));
                    // for( unsigned int i{0}; i < this->m_cols * this->m_rows; i++ )
                    //     this->data[i] = _mat.data[i];

                }

                matrix(matrix&& _mat) noexcept
                : m_rows(_mat.m_rows), m_cols(_mat.m_cols), data(_mat.data) {

                    std::cout << "move\n";
                    _mat.data = nullptr;
                    _mat.m_rows = 0;
                    _mat.m_cols = 0;

                }

                ~matrix() {
                    delete [] this->data;
                }

                type& operator() (unsigned int _i, unsigned int _j) {
                    // std::cout << "op overload\n";
                    return this->data[this->m_rows*_i + _j];
                }

                bool operator== (const matrix& _mat) {
                    if(this->data == nullptr || _mat.data == nullptr) {
                        return false;
                    } else if(this->col_size() == _mat.col_size() && this->row_size() == _mat.row_size()) {
                        return memcmp( (const void*)this->data, (const void*)_mat.data, (this->m_cols * this->m_rows * sizeof(type)) ) == 0;
                    } else return false;
                }

                matrix& operator= (matrix&& _mat) {

                    std::cout << "move ass\n";

                    this->m_rows = _mat.m_rows;
                    this->m_cols = _mat.m_cols;
                    this->data = _mat.data;

                    _mat.data = nullptr;
                    _mat.m_rows = 0;
                    _mat.m_cols = 0;

                    return *this;
                }

                unsigned int row_size() const { return this->m_rows; }
                unsigned int col_size() const { return this->m_cols; }
            
            private:
                type* data;
                unsigned int m_rows;
                unsigned int m_cols;
        };

    } // namespace math
} // namespace ylib
