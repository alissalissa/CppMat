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

BOOST_AUTO_TEST_CASE(matrix){
	//0
	cppmat::Matrix m0;
	BOOST_REQUIRE(m0.Y()==0);
	BOOST_REQUIRE(m0.X()==0);
	BOOST_REQUIRE(!m0.Rows());
	BOOST_CHECK_THROW(m0.Cell(1,1),cppmat::MatrixBaseException);
	BOOST_CHECK_THROW(m0.Row(1),cppmat::MatrixBaseException);
	BOOST_CHECK_THROW(m0[0],cppmat::MatrixBaseException);
	BOOST_CHECK_THROW(m0[1],cppmat::MatrixBaseException);

	//1
	BOOST_CHECK_THROW(new cppmat::Matrix(-1,-1),cppmat::MatrixBaseException);

	//2
	cppmat::Matrix m2(3,3);
	BOOST_REQUIRE(m2.Y()==3);
	BOOST_REQUIRE(m2.X()==3);
	BOOST_REQUIRE(m2.Rows());
	for(size_t yi=0;yi<m2.Y();yi++)
		for(size_t xi=0;xi<m2.X();xi++)
			BOOST_CHECK_EQUAL(m2[yi][xi],0.0);
	BOOST_CHECK_THROW(m2[4],cppmat::MatrixBaseException);
	BOOST_CHECK_EQUAL(m2.is_square(),true);

	//3
	cppmat::Matrix m3(3,2);
	BOOST_CHECK_EQUAL(m3.is_square(),false);
	m3[0][1]=1.0;
	BOOST_CHECK_EQUAL(m3[0][1],1.0);
	cppmat::Matrix m31=m3.transpose();
	BOOST_REQUIRE(m31.X()==2);
	BOOST_REQUIRE(m31.Y()==3);
	BOOST_CHECK_EQUAL(m31[1][0],1.0);
	cppmat::Matrix m32(m31);
	BOOST_CHECK_EQUAL(m32[1][0],1.0);
	m32.swap(1,2);
	BOOST_CHECK_EQUAL(m32[2][0],1.0);
	BOOST_CHECK_EQUAL(m32[1][0],0.0);
	BOOST_CHECK_THROW(m32.swap(4,5),cppmat::MatrixBaseException);

	//4
	cppmat::Matrix ident(cppmat::Matrix::identity(4));
	BOOST_CHECK_EQUAL(ident.X(),4);
	BOOST_CHECK_EQUAL(ident.Y(),4);
	for(size_t y=0;y<ident.Y();y++)
		for(size_t x=0;x<ident.X();x++)
			if(x==y)
				BOOST_CHECK_EQUAL(ident[y][x],1.0);
			else
				BOOST_CHECK_EQUAL(ident[y][x],0.0);
	
	//5
	cppmat::Matrix m5(3,2);
	BOOST_CHECK_THROW(m5.determinant(),cppmat::MatrixBaseException);

	//6
	cppmat::Matrix m6(3,3);
	m6[0][0]=6;
	m6[0][1]=1;
	m6[0][2]=1;
	m6[1][0]=4;
	m6[1][1]=-2;
	m6[1][2]=5;
	m6[2][0]=2;
	m6[2][1]=8;
	m6[2][2]=7;
	BOOST_CHECK_EQUAL(m6.determinant(),-306);

	//7
	cppmat::Matrix m7(2,2);
	m7[0][0]=3;
	m7[0][1]=3;
	m7[1][0]=3;
	m7[1][1]=3;
	cppmat::Matrix m71=m7*2;
	m7*=3;
	BOOST_CHECK_EQUAL(m7[0][0],9);
	BOOST_CHECK_EQUAL(m71[0][0],6);

}
