#ifndef MEMORY_H
#include <memory.h>
#endif
namespace ylib {
    namespace math {
        
        template <typename type>
        class matrix {
            public:
                matrix() : data(nullptr), m_rows(0), m_cols(0) {}

                matrix(size_t _rows, size_t _columns) : m_rows(_rows), m_cols(_columns) {                    
                    this->data = new type[this->m_rows * this->m_cols]{};
                }

                matrix(size_t _rows, size_t _columns, type _default_val)
                : m_rows(_rows), m_cols(_columns) {
                    
                    this->data = new type[this->m_rows * this->m_cols];
                    for(size_t i{}; i < this->size(); i++)
                        this->data[i] = _default_val;
                    
                }

                matrix(const matrix& _mat) : m_rows(_mat.m_rows), m_cols(_mat.m_cols) {

                    this->data = new type[this->m_cols * this->m_rows];
                    memcpy((void*)this->data, (const void*)_mat.data, (_mat.m_cols * _mat.m_rows * sizeof(type)));

                }

                matrix(matrix&& _mat) noexcept
                : m_rows(_mat.m_rows), m_cols(_mat.m_cols), data(_mat.data) {

                    _mat.data = nullptr;
                    _mat.m_rows = 0;
                    _mat.m_cols = 0;

                }

                ~matrix() { delete [] this->data; }

                type& operator() (size_t _i, size_t _j) {

                    if(this->data != nullptr)
                        return this->data[this->m_cols*_i + _j];
                    else
                        throw "AccessOutOfBounds";

                }

                bool operator== (const matrix& _mat) {

                    if(this->data == nullptr || _mat.data == nullptr) {
                        return false;
                    } else if(this->col_size() == _mat.col_size() && this->row_size() == _mat.row_size()) {
                        return memcmp( (const void*)this->data, (const void*)_mat.data, (this->m_cols * this->m_rows * sizeof(type)) ) == 0;
                    } else return false;

                }

                matrix& operator= (matrix&& _mat) {

                    this->m_rows = _mat.m_rows;
                    this->m_cols = _mat.m_cols;
                    this->data = _mat.data;

                    _mat.data = nullptr;
                    _mat.m_rows = 0;
                    _mat.m_cols = 0;

                    return *this;
                }

                /**
                 * get_data() {}
                 * This is a bad function as it returns the inner pointer
                 * no one should be able to modify inner content
                 * or the pointer allocation outside of the scope of this class
                */
                const type* get_data() const { return const_cast<type*>(this->data); }
                bool is_square_matrix() const { return this->m_rows == this->m_cols; }
                size_t row_size() const { return this->m_rows; }
                size_t col_size() const { return this->m_cols; }
                size_t size() const { return (this->m_rows * this->m_cols); }
                
                /**
                 * resize() {}
                 * this function will resize the matrix by reallocating new memory
                 * and id _preserved argument is specified as `false`
                 * then will not preserve the old data else will preserve
                */
                void resize(size_t _newrows, size_t _newcols, bool _preserve = true);
            private:
                type* data;
                size_t m_rows;
                size_t m_cols;
        };

        template <typename type>
        void matrix<type>::resize(size_t _newrows, size_t _newcols, bool _preserve) {
            type* temp_data = new type[_newrows * _newcols];
            for(size_t i{0}; i < _newrows; i++) {
                for(size_t j{0}; j < _newcols; j++) {
                    type input_val{};
                    if(_preserve) {
                        if(i < this->m_rows && j < this->m_cols)
                            input_val = (*this)(i,j);
                    } temp_data[_newcols*i + j] = input_val;
                }
            }

            delete[] this->data;
            this->data = temp_data;
            temp_data = nullptr;

            this->m_rows = _newrows;
            this->m_cols = _newcols;
        }

    } // namespace math
} // namespace ylib
