
//Students include on their own
//pared down version from Project 6

#include <cmath>        /* abs                                 */
#include <iomanip>      /* setprecision, setw, showpoint       */
#include <iostream>     /* cout, endl, flush, ostream          */
#include <sstream>      /* stringstream                        */
#include <utility>      /* move, swap                          */
#include "matrix_rev.hpp"
#include <fstream>

/*****************************************************************************
 * Function: (Default) Constructor
 * Description: Constructs an empty matrix.
 * Parameters: n/a
 * Return Value: n/a
 */
Matrix::Matrix()
{
   m = nullptr;
   numRows = numColumns = 0;
}

/*****************************************************************************
 * Function: (Size) Constructor
 * Description: Constructs a zero matrix with the provided size.
 * Parameters:
 *    nR - Number of rows.
 *    nC - Number of columns.
 * Return Value: n/a
 */
Matrix::Matrix(const unsigned nR, const unsigned nC)
{
   //std::cout << "Size Constructor... " << std::flush;
   numRows = nR;
   numColumns = nC;

   if (numRows == 0 && numColumns == 0)
   {
      m = nullptr;
   }
   else
   {
      m = new double*[numRows];
      for (unsigned i = 0; i < numRows; ++i)
      {
         m[i] = new double[numColumns];
         for (unsigned j = 0; j < numColumns; ++j)
         {
            m[i][j] = 255;
         }
      }
   }
   //std::cout << "Done" << std::endl;
}

/*****************************************************************************
 * Function: (Size) Constructor (w/ pgm file input)
 * Description: Constructs a matrix according to pgm input.
 * Parameters:
 *    A  - String containing a pgm filename with ending "pgm"
 * Return Value: n/a
 */
Matrix::Matrix(const std::string& A)
{
   std::ifstream in;
   in.open(A);
   if (!in)
      std::cout << "Error opening input file." << std::endl;

   std::string dummystring="";
   std::string inputstring="";
   int colns, rws, maxGray;
   
   in >> dummystring;
   in.ignore();

   while(in.peek()=='#')
      getline(in, dummystring, '\n');

   in >> colns >> rws;
   in.ignore();

   while(in.peek()=='#')
      getline(in, dummystring, '\n');

   in >> maxGray;
   in.ignore();

   dummystring = "";
   for (int i=0; i<rws; ++i)
   {    
      if (in.peek()=='#')
      {
         getline(in, dummystring, '\n');
         i--;
      }
      else
      {
         getline(in, dummystring, '\n');
         inputstring = inputstring + " " + dummystring;
      }
      inputstring+='\n';
      
   }
   in.close();

   std::stringstream ss;

   numRows = rws;
   numColumns = colns;

   if (rws == 0 || colns == 0)
   {
      m = nullptr;
      numRows = numColumns = 0;
   }
   else
   {
      ss << inputstring;

      m = new double*[numRows];
      for (unsigned i = 0; i < numRows; ++i)
      {
         m[i] = new double[numColumns];
         for (unsigned j = 0; j < numColumns; ++j)
         {
            m[i][j]=0;
            ss >> m[i][j];
         }
      }
   }
}

/*****************************************************************************
 * Function: (Size) Constructor (w/ Elements)
 * Description: Constructs a matrix with the provided size and elements.
 * Parameters:
 *    nR - Number of rows.
 *    nC - Number of columns.
 *    A  - String containing matrix elements.
 * Return Value: n/a
 */
Matrix::Matrix(const unsigned nR, const unsigned nC, const std::string& A)
{
   //std::cout << "Size Constructor w/ Elements... " << std::flush;
   std::stringstream ss;

   numRows = nR;
   numColumns = nC;

   if (nR == 0 || nC == 0)
   {
      m = nullptr;
      numRows = numColumns = 0;
   }
   else
   {
      ss << A;

      m = new double*[numRows];
      for (unsigned i = 0; i < numRows; ++i)
      {
         m[i] = new double[nC];
         for (unsigned j = 0; j < numColumns; ++j)
         {  
            m[i][j]=0;
            ss >> m[i][j];
         }
      }
   }

}

/*****************************************************************************
 * Function: (Copy) Constructor
 * Description: Constructs a matrix based off the provided one.
 * Parameters:
 *    A - Matrix to copy.
 * Return Value: n/a
 */
Matrix::Matrix(const Matrix& A)
{
   //std::cout << "Copy Constructor... " << std::flush;
   numRows = A.numRows;
   numColumns = A.numColumns;

   m = new double*[numRows];
   for (unsigned i = 0; i < numRows; ++i)
   {
      m[i] = new double[numColumns];
      for (unsigned j = 0; j < numColumns; ++j)
      {
         m[i][j] = A.m[i][j];
      }
   }
   //std::cout << "Done" << std::endl;
}

/*****************************************************************************
 * Function: (Move) Constructor
 * Description: 'Constructs' a matrix based off the provided one.
 * Parameters:
 *    A - Matrix to steal members of.
 * Return Value: n/a
 */
Matrix::Matrix(Matrix&& A)
{
   //std::cout << "Move Constructor... " << std::flush;
   numRows = std::move(A.numRows);
   numColumns = std::move(A.numColumns);
   m = A.m;
   A.m = nullptr;
   //std::cout << "Done" << std::endl;
}

/*****************************************************************************
 * Function: Destructor
 * Description: Deallocates dynamic memory used by the Matrix.
 * Parameters: n/a
 * Return Value: n/a
 */
Matrix::~Matrix()
{
   //std::cout << "Destructor... " << std::flush;
   if (m != nullptr)
   {
      for (unsigned i = 0; i < numRows; ++i)
      {
         delete [] m[i];
         m[i] = nullptr;
      }
      delete [] m;
      m = nullptr;
   }
   //std::cout << "Done" << std::endl;
}

/*****************************************************************************
 * Function: operator= ((Copy) Assignment)
 * Description: 
 * Parameters:
 *    A - The Matrix.
 * Return Value: Reference to the Matrix just constructed.
 */
Matrix& Matrix::operator=(const Matrix& A)
{
   Matrix T(A);

   std::swap((*this).numRows, T.numRows);
   std::swap((*this).numColumns, T.numColumns);
   std::swap((*this).m, T.m);

   return *this;
}

/*****************************************************************************
 * Function: NumRows
 * Description: Returns the number of rows of the Matrix.
 * Parameters: n/a
 * Return Value: The number of rows.
 */
unsigned Matrix::NumRows() const
{
   return numRows;
}

/*****************************************************************************
 * Function: NumColumns
 * Description: Returns the number of columns of the Matrix.
 * Parameters: n/a
 * Return Value: The number of columns.
 */
unsigned Matrix::NumColumns() const
{
   return numColumns;
}


/*****************************************************************************
 * Function: Size
 * Description: Returns the size of the matrix.
 *       Reference: en.wikipedia.org/wiki/Matrix_(mathematics)#Size
 * Parameters: n/a
 * Return Value: A string representing the size, of the form: <rows>x<cols>.
 */
std::string Matrix::Size() const
{
   return std::to_string(numRows) + "x" + std::to_string(numColumns);
}

/*****************************************************************************
 * Function: operator()
 * Description: Access an element of the Matrix. The element is mutable.
 *       Note that element subscripts start at 1, not 0, so 1 is taken
 *       away from the input indices to form the correct internal indices.
 * Parameters:
 *    i - Index of the row.
 *    j - Index of the column.
 * Return Value: Reference to the element.
 */
double& Matrix::operator()(const unsigned i, const unsigned j) const
{
   return m[i-1][j-1];
}

/*****************************************************************************
 * Function: Save
 * Description: Accepts an output filename as argument and saves the matrix 
 * content to the output file in PGM format.
 * Parameters:
 *    filename - the outfile filename
 * Return Value: none
 */
void Matrix::Save(std::string& filename)
{
   std::ofstream out;

   out.open(filename);

   out << "P2\n";
   out << this->numColumns << " " << this->numRows << "\n";

   //Do a loop to determine the number largest value
   int largest = 1;
   for (unsigned i = 0; i < this->numRows; ++i)
      for (unsigned j = 0; j < this->numColumns; ++j)
            if (this->m[i][j] > largest)
               largest = this->m[i][j];

   out << largest << "\n";

   for (unsigned i = 0; i < this->numRows; ++i)
   {
      for (unsigned j = 0; j < this->numColumns; ++j)
      {
            out << this->m[i][j];
            if (j!=this->numColumns-1) 
               out << " ";
      }
      out << "\n";
   }
   out.close();
}







