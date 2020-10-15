template <class T>
class Matrix{
 private:
  T **matrix;
  int rows;
  int cols;
 public:
  Matrix();
  Matrix(int row,int col);
  Matrix(const Matrix &obj);
  int getNoOfRows() const;
  int getNoOfCols() const;
  T getElement(int row, int col) const;
  void insertElement(T const& element, int rowNo, int colNo);
  Matrix& operator+(const Matrix & obj);
  void operator =(const Matrix &obj);
  void print();
  void transpose();
  ~Matrix();
};
