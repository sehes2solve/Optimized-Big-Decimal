#ifndef BIG_INT_DECIMAL_H
#define BIG_INT_DECIMAL_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum number_sign { Positive = 0 , Negative = 1 };
class big_int_decimal
{
    public:
        /// Constructors definition ---------------------------------------------------------------------
        big_int_decimal();                                              /// Time O(  1  ) , Memory O( 1 )
        big_int_decimal( string     _copy_STR );                        /// Time O( 3*N ) , Memory O( 1 )
        big_int_decimal( long long  _copy_INT );                        /// Time O(  N  ) , Memory O( 1 )

        /// Destructor definition   ---------------------------------------------------------------------
        virtual ~big_int_decimal();                                     /// Time O(  1  ) , Memory O( 1 )

        /// operators overload definition----------------------------------------------------------------

        big_int_decimal operator + (  big_int_decimal object );         /// Time O( 2*N ) , Memory O( N )
        big_int_decimal operator - (  big_int_decimal object );         /// Time O( 2*N ) , Memory O( N )
        big_int_decimal operator = (  big_int_decimal object );         /// Time O(  N  ) , Memory O( 1 )

        friend ostream& operator << ( ostream& out ,  big_int_decimal  object );
        friend istream& operator >> ( istream& in  ,  big_int_decimal& object );

        /// setters and getters -------------------------------------------------------------------------
        bool get_sign();                                                /// Time O(  1  ) , Memory O( 1 )
        bool get_valid();                                               /// Time O(  1  ) , Memory O( 1 )
        string& get_number();                                           /// Time O(  1  ) , Memory O( 1 )
        long long int getSize();                                        /// Time O(  1  ) , Memory O( 1 )

        void setNumber( string number );                                /// Time O(  N  ) , Memory O( 1 )
        void setSign( bool _sign );                                     /// Time O(  1  ) , Memory O( 1 )

        /// functions definition ------------------------------------------------------------------------
        bool isValid( string number );                                  /// Time O(  N  ) , Memory O( 1 )
        void remove_leading_zeros( string & number );                   /// Time O(  N  ) , Memory O( N )
        void take_data_from_string( string _copy_STR );                 /// Time O( 3*N ) , Memory O( 1 )
        bool isGreater( string& number1 , string& number2 );            /// Time O(  N  ) , Memory O( 1 )
        string plus_operation ( string& number1 , string& number2 );    /// Time O(  N  ) , Memory O( N )
        string minus_operation( string& number1 , string& number2 );    /// Time O(  N  ) , Memory O( N )

    protected:

    private:

        bool sign;
        bool valid;
        string Number;
        const short bitLength = 8;
        long long int Number_of_digits;
};

ostream& operator << ( ostream& out , const   big_int_decimal  object );
istream& operator >> ( istream& in  ,         big_int_decimal& object );

#endif // BIG_INT_DECIMAL_H
