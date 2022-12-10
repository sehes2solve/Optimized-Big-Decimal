#include "big_int_decimal.h"

/// constructors and destructor implementation ----------------------------

big_int_decimal::big_int_decimal()
{
    /// clear any garbage
    this->valid  = false;
    this->Number = "";
    this->sign = Positive;
    this->Number_of_digits = 0;
}

/** string parameter constructor :-
        time    complexity O( 3*N ) worst case
        memory  complexity O( 1 )
**/
big_int_decimal::big_int_decimal( string     _copy_STR ) : big_int_decimal()
{
    this->take_data_from_string( _copy_STR );
}

/** long long  parameter constructor :-
        time    complexity O( N ) worst case
        memory  complexity O( 1 )
**/
big_int_decimal :: big_int_decimal( long long  _copy_INT ) : big_int_decimal()
{
    int sequecne_length = ( _copy_INT == 0 );

    if     ( _copy_INT == 0 ){ this->Number = "0"; }
    else
    {
        if ( _copy_INT <  0 )
        {
            this->sign = Negative , _copy_INT = abs( _copy_INT );
        }

        while ( _copy_INT )
        {
            int digit  = _copy_INT%10;
            _copy_INT /= 10;

            sequecne_length++;
            this->Number = (char)(digit+'0') + this->Number;
        }
    }
    this->Number_of_digits = sequecne_length;
}

big_int_decimal::~big_int_decimal()
{
    this->valid  = false;
    this->Number = "";
    this->sign = Positive;
    this->Number_of_digits = 0;
}

/// operator overload implementation --------------------------------------

/** ( + ) operator operator :-
        time    complexity O( 2*N ) worst case
        memory  complexity O( N )
**/

big_int_decimal big_int_decimal :: operator + ( big_int_decimal object )
{
    big_int_decimal result; string sequence = "";

    if ( this->Number_of_digits == 0 || object.getSize() == 0 )
    {
        result.setNumber( sequence );
        return result;
    }

    if ( this->sign == object.get_sign() )
    {
        sequence = this->plus_operation( this->Number , object.get_number() );

        result.setNumber( sequence );
        result.setSign( this->sign );
    }
    else
    {
        bool _sign;
        if ( this->isGreater( this->Number , object.get_number() ) == false )
        {
            _sign = object.get_sign();
            sequence = this->minus_operation( object.get_number() , this->Number );
        }
        else
        {
            _sign = this->sign;
            sequence = this->minus_operation( this->Number , object.get_number() );
        }
        result.setNumber( sequence );
        result.setSign( _sign );
    }

    if ( result.get_number() == "0" ) result.setSign( Positive );
    return result;
}

/** ( - ) operator operator :-
        time    complexity O( 2*N ) worst case
        memory  complexity O( N )
**/

big_int_decimal big_int_decimal :: operator - ( big_int_decimal object )
{
    big_int_decimal result; string sequence = "";

    if      ( this->sign == Positive && object.get_sign() == Negative )
    {
        sequence = this->plus_operation( this->Number , object.get_number() );
        result.setNumber( sequence );
        result.setSign( Positive );
    }
    else if ( this->sign == Negative && object.get_sign() == Positive )
    {
        sequence = this->plus_operation( this->Number , object.get_number() );
        result.setNumber( sequence );
        result.setSign( Negative );
    }
    else
    {
        bool _sign;

        if ( object.get_sign() == Positive ) object.setSign( Negative );
        else object.setSign( Positive );

        if ( isGreater( this->Number , object.get_number() ) == false )
        {
            _sign = object.get_sign();
            sequence = this->minus_operation( object.get_number() , this->Number );
        }
        else
        {
            _sign = this->sign;
            sequence = this->minus_operation( this->Number , object.get_number() );
        }
        result.setNumber( sequence );
        result.setSign( _sign );
    }

    if ( result.get_number() == "0" ) result.setSign( Positive );
    return result;
}

/** Assign operator overload Function :-
        time    complexity O( N )
        memory  complexity O( 1 )
**/

big_int_decimal big_int_decimal :: operator = ( big_int_decimal object )
{
    this->sign              = object.get_sign();
    this->Number_of_digits  = object.getSize ();

    string& sequence        = object.get_number();
    this->Number            = "";
    for ( char index : sequence )
        this->Number += index;

    return *this;
}


ostream& operator << ( ostream& out , big_int_decimal  object )
{
    char sign = ( object.get_sign() == Negative ? '-' : '+' );
    string& sequence = object.get_number();

    if ( sequence.length() > 0 )
        out << sign << " " << sequence;
    else
        out << "Invalid";

    return out;
}

istream& operator >> ( istream& in  , big_int_decimal& object )
{
    string sequence = "";

    cin.ignore();
    getline( in , sequence );
    object.setNumber( sequence );
    return in;
}


/// setter and getters implementation -------------------------------------

/** getSize Function :-
        time    complexity O( 1 )
        memory  complexity O( 1 )
**/

long long int big_int_decimal :: getSize()
{
    return this->Number_of_digits;
}

bool big_int_decimal :: get_sign()
{
    return this->sign;
}

bool big_int_decimal :: get_valid()
{
    return this->valid;
}

string& big_int_decimal :: get_number()
{
    return this->Number;
}

void big_int_decimal :: setNumber( string number )
{
    this->take_data_from_string( number );
}

void big_int_decimal :: setSign( bool _sign )
{
    this->sign = _sign;
}


/// functions implementation ----------------------------------------------


/** isValid Function :-
        time    complexity O( N ) worst case
        memory  complexity O( 1 )
**/
bool big_int_decimal :: isValid( string number )
{
    bool valid = true;

    if ( number.front() != '+' && number.front() != '-' && isdigit( number.front() ) == false )
    {
        valid = false;
        return valid;
    }
    for ( int i = 1; i < (int)number.length(); i++ )
        if ( isdigit( number[i] ) == false ){ valid = false; break; }
    return this->valid = valid;
}

/** take_data_from_string Function :-
        time    complexity O( 3*N ) worst case
        memory  complexity O( 1 )
**/

void big_int_decimal :: take_data_from_string( string _copy_STR )
{
    /// O( N ) time complexity
    if ( this->isValid( _copy_STR ) )
    {
        bool have_sign = false;

        /// O( N ) time complexity
        this->remove_leading_zeros( _copy_STR );

        /// check for sign , O( 1 ) time complexity
        if ( isdigit( _copy_STR.front() ) == false )
        {
            /// memorize the sign of the number , O( 1 ) time complexity
            this->sign = ( _copy_STR.front() == '+' ? Positive : Negative );

            /**
                Instead of erase the sign of the number from the sequence and take
                time complexity O( N ) & memory complexity o( 1 ), we memorize an attribute
                to check if the sequence have sign - the range of the number is [ 1 , n ] -
                or not.
                this will take O( 1 ) time complexity and O( 1 ) memory complexity
            **/

            have_sign  = true;
        }
        else
            this->sign = Positive;

        long long int end_sequnce       = ( have_sign == true ? 1 : 0 );
        long long int sequence_length   = _copy_STR.length();

        /// time complexity O( N )
        for ( long long int index = sequence_length-1; index >= end_sequnce; index-- )
            this->Number = _copy_STR[ index ] + this->Number;

        this->Number_of_digits = sequence_length - end_sequnce;
    }
    else
        cout << "Invalid input\n";
}

/** remove_leading_zeros Function :-
        time    complexity O( N ) worst case
        memory  complexity O( N )
**/

void big_int_decimal :: remove_leading_zeros( string & number )
{
    string new_number = ""; bool ok = false;
    new_number += ( number.front() == '-' ? '-' : '+' );
    for ( char index : number )
    {
        if ( ok ) new_number += index;

        if ( isdigit( index ) == true && index != '0' && ok == false )
            new_number += index , ok = true;
    }

    if ( new_number == "+" || new_number == "-" ) new_number += "0";
    number = new_number;
}

/** isGreater Function :-
        time    complexity O( N ) worst case
        memory  complexity O( 1 )
**/

bool big_int_decimal :: isGreater( string& number1 , string& number2 )
{
    long long number1_length = number1.length();
    long long number2_length = number2.length();

    if ( number1_length == number2.length() )
    {
        for ( int i = 0; i < number1_length; i++ )
        {
            if ( number1[ i ] != number2[ i ] )
            {
                return number1[ i ] > number2[ i ];
            }
        }
    }
    return (number1_length > number2_length);
}

/** plus_operation Function :-
        time    complexity O( N ) worst case
        memory  complexity O( N )
**/

string big_int_decimal :: plus_operation( string& number1 , string& number2 )
{
    string sumation = ""; int reminder = 0;
    int number1_pointer = number1.length() -1 ;
    int number2_pointer = number2.length() -1 ;

    do
    {
        int n1 , n2;
        n1 = ( number1_pointer > -1 ? number1[ number1_pointer-- ] : '0' ) - '0';
        n2 = ( number2_pointer > -1 ? number2[ number2_pointer-- ] : '0' ) - '0';

        int result = n1 + n2 + reminder;
        sumation   = (char)(result%10 + '0') + sumation;
        result /= 10;

        reminder = (result > 0);
    }
    while( number1_pointer > -1 || number2_pointer > -1 );

    if ( reminder > 0 ) sumation = '1' + sumation;
    return sumation;
}

/** minus_operation Function :-
        time    complexity O( N ) worst case
        memory  complexity O( N )
**/

string big_int_decimal :: minus_operation( string& number1 , string& number2 )
{
    string minus_res = ""; int reminder = 0;
    int number1_pointer = number1.length() -1 ;
    int number2_pointer = number2.length() -1 ;

    do
    {
        int n1 , n2;
        n1 = ( number1_pointer > -1 ? number1[ number1_pointer-- ] : '0' ) - '0';
        n2 = ( number2_pointer > -1 ? number2[ number2_pointer-- ] : '0' ) - '0';


        int result = n1 - (n2+reminder);
        if ( result < 0 ) result += 10 , reminder = 1;
        else reminder = 0;

        minus_res = (char)( result+'0' ) + minus_res;
    }
    while( number1_pointer > -1 || number2_pointer > -1 );
    this->remove_leading_zeros( minus_res );
    return minus_res;
}

