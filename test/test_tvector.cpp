#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(v);

  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(10);
	  TDynamicVector<int> v1(v);
	  v[3] = 3;
    v1[3] = 7;
	  EXPECT_NE(v, v1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v.at(-2));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v.at(20));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	v[0] = 1;
	v1[0] = 1;
	v = v;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	v[0] = 5;
	v1[0] = 7;
	v1 = v;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v(20);
	TDynamicVector<int> v1(52);
	v = v1;
	EXPECT_EQ(v.size(), 52);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(20);
	TDynamicVector<int> v1(52);
	v = v1;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v(20);
	TDynamicVector<int> v1(v);
  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(20);
  EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v(20);
	TDynamicVector<int> v1(52);
  EXPECT_NE(v, v1);
}
//
TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
	v = v + 52;
	TDynamicVector<int> v1(3);
  for(size_t i = 0; i < v1.size(); i++)
  {
	  v1[i] = 52;
  }
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
	v = v -52;
	TDynamicVector<int> v1(3);
	for(size_t i = 0; i < v1.size(); i++)
  {
	  v1[i] = -52;
  }
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3);
  for(size_t i = 0; i < v.size(); i++)
  {
	  v[i] = 52;
  }
  v = v * 2;
	TDynamicVector<int> v1(3);
	for(size_t i = 0; i < v1.size(); i++)
  {
	  v1[i] = 104;
  }
	EXPECT_EQ(v, v1);
  
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v(52);
  TDynamicVector<int> v1(52);
  TDynamicVector<int> out(52);
  for(size_t i = 0; i < v1.size(); i++)
  {
	  v[i] = 52;
    v1[i] = 8;
    out[i] = 60;
  }
  TDynamicVector<int> tmp(52);
  tmp = v + v1;
  EXPECT_EQ(tmp, out);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(52);
  TDynamicVector<int> v1(50);
  ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v(52);
  TDynamicVector<int> v1(52);
  TDynamicVector<int> out(52);
  for(size_t i = 0; i < v1.size(); i++)
  {
	  v[i] = 52;
    v1[i] = 8;
    out[i] = 44;
  }
  TDynamicVector<int> tmp(52);
  tmp = v - v1;
  EXPECT_EQ(tmp, out);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(52);
  TDynamicVector<int> v1(50);
  ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v(52);
  TDynamicVector<int> v1(52);
  for(size_t i = 0; i < v1.size(); i++)
  {
	  v[i] = 52;
    v1[i] = 10;
  }
  int tmp = (v * v1);
  EXPECT_EQ(tmp, (520 * 52));
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(52);
  TDynamicVector<int> v1(50);
  ASSERT_ANY_THROW(v * v1);
}

