//
// Created by root on 7/15/18.
//

#ifndef IADS_TEXTTABLE_H
#define IADS_TEXTTABLE_H

#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>



class TextTable {

    public:
    enum class Alignment { LEFT, RIGHT };
    typedef std::vector< std::string > Row;
    TextTable( char horizontal = '-', char vertical = '|', char corner = '+' ) :
        _horizontal( horizontal ),
        _vertical( vertical ),
        _corner( corner )
    {}

    void setAlignment( unsigned i, Alignment alignment )
    {
        _alignment[ i ] = alignment;
    }

    Alignment alignment( unsigned i ) const
    { return _alignment[ i ]; }

    char vertical() const
    { return _vertical; }

    char horizontal() const
    { return _horizontal; }

    void add( std::string const & content )
    {
        _current.push_back( content );
    }

    void endOfRow()
    {
        _rows.push_back( _current );
        _current.assign( 0, "" );
    }

    template <typename Iterator>
    void addRow( Iterator begin, Iterator end )
    {
        for( auto i = begin; i != end; ++i ) {
           add( * i );
        }
        endOfRow();
    }

    template <typename Container>
    void addRow( Container const & container )
    {
        addRow( container.begin(), container.end() );
    }

    std::vector< Row > const & rows() const
    {
        return _rows;
    }

    void setup() const
    {
        determineWidths();
        setupAlignment();
    }

    std::string ruler() const
    {
        std::string result;
        result += _corner;
        for( auto width = _width.begin(); width != _width.end(); ++ width ) {
            result += repeat( * width, _horizontal );
            result += _corner;
        }

        return result;
    }

    int width( unsigned i ) const
    { return _width[ i ]; }

    private:
    char _horizontal;
    char _vertical;
    char _corner;
    Row _current;
    std::vector< Row > _rows;
    std::vector< unsigned > mutable _width;
    std::map< unsigned, Alignment > mutable _alignment;

    static std::string repeat( unsigned times, char c )
    {
        std::string result;
        for( ; times > 0; -- times )
            result += c;

        return result;
    }

    unsigned columns() const
    {
        return _rows[ 0 ].size();
    }

    void determineWidths() const
    {
        _width.assign( columns(), 0 );
        for ( auto rowIterator = _rows.begin(); rowIterator != _rows.end(); ++ rowIterator ) {
            Row const & row = * rowIterator;
            for ( unsigned i = 0; i < row.size(); ++i ) {
                _width[ i ] = _width[ i ] > row[ i ].size() ? _width[ i ] : row[ i ].size();
            }
        }
    }

    void setupAlignment() const
    {
        for ( unsigned i = 0; i < columns(); ++i ) {
            if ( _alignment.find( i ) == _alignment.end() ) {
                _alignment[ i ] = Alignment::LEFT;
            }
        }
    }
};

std::ostream & operator<<( std::ostream & stream, TextTable const & table );

/*
 * TextTable t( '-', '|', '+' );

    t.add( "name" );
    t.add( "Sex00000000000000000000000000000000" );
    t.add( "Age" );
    t.endOfRow();

    t.add( "Stevy" );
    t.add( "male" );
    t.add( "4556" );
    t.endOfRow();

    t.setAlignment( 2, TextTable::Alignment::LEFT );
    cout << t << endl;
 */

#endif //IADS_TEXTTABLE_H
