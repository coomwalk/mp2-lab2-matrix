#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(5);
  m[2][2] = 7;
  TDynamicMatrix<int> m1(m);
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(m);
  m[2][2] = 7;
  EXPECT_NE(m, m1);
}///////

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(5);
  EXPECT_EQ(5, m.size());
}

//TEST(TDynamicMatrix, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0][3] = 4;
//
//  EXPECT_EQ(4, v[0][3]);
//}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(-3));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(20));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  m[2][2] = 7;
  m = m;
  EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(5);
  m1[0][0]= 5;
  m = m1;
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(7);
  m = m1;
  EXPECT_EQ(m.size(), 7);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(7);
  m[0][0]= 5;
  m1 = m;
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(5);
  m[0][0]= 5;
  m1[0][0]= 5;
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(5);
  m[0][0]= 5;
  EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(7);
  EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(5);
  TDynamicMatrix<int> m3(5);
  
  m[0][0] = 3;
  m1[0][1] = 4;

  m3[0][0] = 3;
  m3[0][1] = 4;

  EXPECT_EQ((m + m1), m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(7);
  ASSERT_ANY_THROW(m+m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(5);
  TDynamicMatrix<int> m3(5);
  
  m[0][0] = 3;
  m1[0][1] = 4;

  m3[0][0] = 3;
  m3[0][1] = -4;

  EXPECT_EQ((m - m1), m3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(7);
  ASSERT_ANY_THROW(m-m1);
}

TEST(TDynamicMatrix, can_multicate_matrixes_with_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m3(2);
  m[0][0] = 1;
  m[0][1] = 1;
  m[1][0] = 1;
  m[1][1] = 1;

  m1[0][0] = 2;
  m1[0][1] = 2;
  m1[1][0] = 2;
  m1[1][1] = 3;

  m3[0][0] = 4;
  m3[0][1] = 5;
  m3[1][0] = 4;
  m3[1][1] = 5;
  EXPECT_EQ(m * m1, m3);
}

TEST(TDynamicMatrix, cant_multicate_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(7);
  ASSERT_ANY_THROW(m * m1);
}

