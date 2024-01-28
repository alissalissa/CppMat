//Unit tests for the matrix class
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE matrix_test

#include <boost/test/unit_test.hpp>

#include "matrix.h"
#include "matrow.h"
#include "matex.h"

BOOST_AUTO_TEST_CASE(row_test){
	//0
	cppmat::MatrixRow mr0;
	BOOST_CHECK(!mr0.Values());
	BOOST_CHECK_EQUAL(mr0.size(),(size_t)0);
	mr0.build(5);
	BOOST_CHECK_EQUAL(mr0.size(),(size_t)5);
	BOOST_REQUIRE(mr0.Values());
	for(size_t i=0;i<mr0.size();i++)
		BOOST_CHECK_EQUAL(mr0[i],0.0);
	mr0=mr0+1;
	BOOST_CHECK_EQUAL(mr0[0],1.0);
	mr0+=1;
	BOOST_CHECK_EQUAL(mr0[0],2.0);
	mr0*=2.0;
	BOOST_CHECK_EQUAL(mr0[1],4.0);

	//1
	cppmat::MatrixRow mr1(mr0);
	BOOST_CHECK(mr1.Values());
	BOOST_CHECK_EQUAL(mr1[0],4.0);

	//2
	cppmat::MatrixRow mr2(3);
	BOOST_CHECK_EQUAL(mr2.size(),size_t(3));
	BOOST_CHECK(mr2.Values());
	BOOST_CHECK_EQUAL(mr2.Value(0),0.0);

	//3
	cppmat::MatrixRow mr3;
	BOOST_CHECK_THROW(mr3.build(-4),cppmat::MatrixBaseException);
}