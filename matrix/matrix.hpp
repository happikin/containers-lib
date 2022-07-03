#ifndef MEMORY_H
#include <memory.h>
#endif

#ifndef FUNCTIONAL
#include <functional>
#endif

#ifndef VECTOR
#include <vector>
#endif
#include <stdexcept>

namespace ycontainer {

    enum matrix_type {
        identity
    };

    enum snip_position {
        top_left,
        top_right,
        bottom_right,
        bottom_left
    };

    struct snip_setting {
        snip_position m_pos;
        size_t i;
        size_t j;
    };

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

            matrix(size_t _rows, size_t _columns, matrix_type _matrix_type)
            : m_rows(_rows), m_cols(_columns) {
                
                switch (_matrix_type) {
                    case matrix_type::identity :
                        this->data = new type[this->m_rows * this->m_cols];
                        for(size_t i{}; i<this->m_rows; i++) {
                            for(size_t j{}; j<this->m_cols; j++) {
                                (*this)(i,j) = ( i==j ? 1 : 0 );
                            }
                        }  
                        break;
                    
                    default:
                        break;
                }           
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

                if(this->data != nullptr) {
                    if(_i >= this->m_rows || _j >= this->m_cols) {
                        throw std::out_of_range("OutOfBoundsAccess@("+ std::to_string(_i) + "," + std::to_string(_j) + ")");
                    }
                    return this->data[this->m_cols*_i + _j];
                } else
                    throw std::out_of_range("IllegalAccess@("+ std::to_string(_i) + "," + std::to_string(_j) + ")");

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

            /**
             * reset();
             * this function will gracefully deallocate any internally held memory
             * and will reset the object to a valid state as if constructed right now
            */
            void reset();

            bool is_square_matrix() const { return this->m_rows == this->m_cols; }
            
            /**
             * is_symmetric_matrix();
             * this function will check the matrix dimensions and internal data
             * then if found symmetric mathematically by rules of linear algebra and matrices
             * it will return true or false accordingly
            */
            bool is_symmetric_matrix();

            /**
             * is_identity_matrix();
             * this function will check if the internal memory is an identity matrix
             * then return true or false accordingly
            */
            bool is_identity_matrix();

            /**
             * get_first_index();
             * this function will travel through the internal matrix data and will return
             * the 2D index of first found occurence in form of std::pair
             * where pair::first will be row number and pair::second will be column number
            */
            std::pair<size_t,size_t> get_first_index(type&&);
            std::pair<size_t,size_t> get_first_index(type&);

            /**
             * get_all_index();
             * this function takes in two arguments, one the value we need to search
             * second is the max number of indexes we wish to return with default value 0,
             * which means if we specify _limit = 2 then a std::vector of std::pair
             * containing 1st two occurences will be returned and if _limit is left as 0
             * then indexes for all occurences will be returned
            */
            std::vector<std::pair<size_t,size_t>> get_all_index(type, size_t _limit = 0);

            /**
             * second overload of get_all_index() has been provided taking into consideration
             * a case when the matrix is really huge and if number of matching occurences
             * same as the size of matrix then returning that index vector by value is
             * a bad choice. So the use of this overload is left to programmers wit
            */
            size_t get_all_index(
                type _data,
                std::vector<std::pair<size_t,size_t>>& _index_vec,
                size_t _limit = 0
            );

            /**
             * print();
             * this function will print the supplied matrix in simple box format
            */
            static void print(ycontainer::matrix<type>&) noexcept;

            /**
             * snip();
             * will select the sub matrix of dimension _newrows X _newcols starting from
             * specified _snip_pointer from the _src_matrix and construct _dest_matrix
            */
            // static void snip(
            //     ycontainer::matrix<type>& _dest_matrix,
            //     ycontainer::matrix<type>& _src_matrix,
            //     ycontainer::snip_setting _snip_pointer,
            //     size_t _newrows, size_t _newcols
            // );
            // static void for_each(ycontainer::matrix<type>&, std::function<bool(type&,bool)>& _pred);
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

    template <typename type>
    void matrix<type>::reset() {

        delete[] this->data;
        this->data = nullptr;
        this->m_rows = 0;
        this->m_cols = 0;

    }

    template <typename type>
    void matrix<type>::print(matrix<type>& _mat) noexcept {
        for(size_t i{}; i < _mat.row_size(); i++) {
            for(size_t j{}; j < _mat.col_size(); j++) {
                std::cout << _mat(i,j) << " ";
            } std::cout << "\n";
        } std::cout << "\n";
    }

    template <typename type>
    bool matrix<type>::is_symmetric_matrix() {
        if(!this->is_square_matrix())
            return false;
        else {
            for(size_t i{}; i<this->m_rows; i++) {
                for(size_t j{i+1}; j<this->m_cols; j++) {
                    if(i == j) continue;
                    else {
                        if((*this)(i,j) != (*this)(j,i)) {
                            return false;
                        }
                    }
                }
            } return true;
        }
    }

    template <typename type>
    bool matrix<type>::is_identity_matrix() {
        if(!this->is_square_matrix())
            return false;
        else {
            for(size_t i{}; i<this->m_rows; i++) {
                for(size_t j{}; j<this->m_cols; j++) {
                    if(i == j) {
                        if((*this)(i,j) != 1) return false;
                    } else {
                        if((*this)(i,j) != 0) return false;
                    }
                }
            } return true;
        }
    }   

    template <typename type>
    std::pair<size_t,size_t> matrix<type>::get_first_index(type&& _data) {
        std::pair<size_t,size_t> index_local;
        for(size_t i{}; i<this->m_rows; i++) {
            for(size_t j{}; j<this->m_cols; j++) {
                if((*this)(i,j) == _data) {
                    index_local = {i,j};
                    return index_local;
                }
            }
        } index_local = {};
        return index_local;
    }

    template <typename type>
    std::pair<size_t,size_t> matrix<type>::get_first_index(type& _data) {
        std::pair<size_t,size_t> index_local;
        for(size_t i{}; i<this->m_rows; i++) {
            for(size_t j{}; j<this->m_cols; j++) {
                if((*this)(i,j) == _data) {
                    index_local = {i,j};
                    return index_local;
                }
            }
        } index_local = {};
        return index_local;
    }

    template <typename type>
    std::vector<std::pair<size_t,size_t>> matrix<type>::get_all_index(type _data, size_t _limit) {
        std::vector<std::pair<size_t,size_t>> index_vector;
        for(size_t i{};i<this->m_rows;i++) {
            for(size_t j{};j<this->m_cols;j++) {
                if(_limit != 0) {
                    if(index_vector.size() >= _limit) break;
                }
                if((*this)(i,j) == _data) {
                    index_vector.push_back(std::make_pair(i,j));
                }
            }
        } return index_vector;
    }

    template <typename type>
    size_t matrix<type>::get_all_index(
        type _data,
        std::vector<std::pair<size_t,size_t>>& _index_vec,
        size_t _limit
    ) {
        _index_vec.clear();
        for(size_t i{};i<this->m_rows;i++) {
            for(size_t j{};j<this->m_cols;j++) {
                if(_limit != 0) {
                    if(_index_vec.size() >= _limit) break;
                }
                if((*this)(i,j) == _data) {
                    _index_vec.push_back(std::make_pair(i,j));
                }
            }
        } return _index_vec.size();
    }

} // namespace ycontainer

namespace ycontainer {
    namespace utils {

        template <typename type>
        void print(matrix<type>& _mat) noexcept {
            for(size_t i{}; i < _mat.row_size(); i++) {
                for(size_t j{}; j < _mat.col_size(); j++) {
                    std::cout << _mat(i,j) << " ";
                } std::cout << "\n";
            } std::cout << "\n";
        }

        /**
         * snip();
         * will select the sub matrix of dimension _newrows X _newcols starting from
         * specified _snip_pointer from the _src_matrix and construct _dest_matrix
        */
        template <typename type>
        void snip(
            ycontainer::matrix<type>& _dest_matrix,
            ycontainer::matrix<type>& _src_matrix,
            ycontainer::snip_setting _snip_pointer,
            size_t _newrows, size_t _newcols
        ) {
            // one thing to note is that the new matrix dimensions need to be smaller or equal
            // to the _src_mat even after applying the _snip_pointer
            _dest_matrix.resize(_newrows,_newcols,false);

            ycontainer::snip_position const _pos = _snip_pointer.m_pos;
            
            switch(_pos) {
                
                case ycontainer::snip_position::top_left: {
                    size_t initial_i = _snip_pointer.i;
                    size_t limit_i = initial_i + _newrows;
                    size_t initial_j = _snip_pointer.j;
                    size_t limit_j = initial_j + _newcols;
                    for(size_t i1{initial_i},i2{0}; i1<limit_i, i2<_newrows; i1++, i2++) {
                        for(size_t j1{initial_j}, j2{0}; j1<limit_j, j2<_newcols; j1++, j2++) {
                            // std::cout << "(" << i1 << "," << j1 << ") => " << _src_matrix(i1,j1) << "\n";
                            std::cout << "src: (" << i1 << "," << j1 << ") => " << "dest: (" << i2 << "," << j2 << ")\n";
                            _dest_matrix(i2,j2) = _src_matrix(i1,j1);
                        }
                    }
                } break;

                case ycontainer::snip_position::top_right: {
                    // size_t initial_i = _snip_pointer.i;
                    // size_t limit_i = initial_i + _newrows;
                    // size_t initial_j = _src_matrix.col_size() - _snip_pointer.j - 1;
                    // size_t limit_j = initial_j - _newcols;
                    
                    size_t initial_i = _snip_pointer.i;
                    size_t limit_i = initial_i + _newrows;
                    size_t initial_j = _snip_pointer.j;
                    size_t limit_j = initial_j - _newcols;
                    for(size_t i1{initial_i}, i2{0}; i1 < limit_i && i2 < _newrows; i1++, i2++) {
                        for(size_t j1{initial_j}, j2{_newcols-1}; j1 > limit_j && j2 >= 0; j1--, j2--) {
                            std::cout << "src: (" << i1 << "," << j1 << ") => " << "dest: (" << i2 << "," << j2 << ")\n";
                            _dest_matrix(i2,j2) = _src_matrix(i1,j1);
                        }
                    }
                } break;

                default:
                    break;
            }
        }
    }
} // namespace ycontainer
