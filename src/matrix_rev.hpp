
//Students include on their own
//pared down version from Project 6

#ifndef MATRIX_REV_H
#define MATRIX_REV_H

class Matrix
{
   public:

	   Matrix(const unsigned r, const unsigned c);
	   Matrix(const unsigned r, const unsigned c, const std::string& e);
	   Matrix(const std::string& e);
      Matrix();
      Matrix(const Matrix& A); //Copy Constructor - Given
      Matrix(Matrix&& A); //Move Constructor - Given
      ~Matrix();

      //Basic Image Functionality
      void Save(std::string&);
      Matrix& operator=(const Matrix& A);
      double& operator()(const unsigned i, const unsigned j) const;

      // General Matrix Information
      unsigned NumRows() const;
      unsigned NumColumns() const;
      std::string Size() const;

   private:

      double **m;
      unsigned numRows;
      unsigned numColumns;
};

#endif


