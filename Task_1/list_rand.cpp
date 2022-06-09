//
// Created by develop on 22.05.2022.
//

#include "include/list_rand.h"
#include <cassert>
#include <vector>

ListNode::ListNode()
    : prev( nullptr )
    , next( nullptr )
    , rand( nullptr )
    , data( "data" )
{ }

ListRand::ListRand()
    : head()
    , tail()
    , count()
{ }

ListRand::~ListRand()
{
    clear();
}

void ListRand::clear()
{
    auto first = findFirstNode();
    head = nullptr;
    tail = nullptr;
    count = 0;
    
    delete[] first;
}

void ListRand::init( std::initializer_list<int> rands )
{
    clear();
    count = static_cast<int>(rands.size());
    if( count != 0 )
    {
        head = new ListNode[count]();
        auto it = head;
        auto end = head + count;
        auto randCur = rands.begin();
        auto randEnd = rands.end();
        tail = end - 1;
        
        std::size_t i = 1;
        it->data = "ListNode" + std::to_string( i );
        assert( *randCur >= -1 && *randCur < count );
        if( *randCur != -1 )
        {
            it->rand = head + *randCur;
        }
        ++it;
        
        while( ++randCur != randEnd )
        {
            ++i;
            
            auto prev = it - 1;
            prev->next = it;
            it->prev = prev;
            it->data = "ListNode" + std::to_string( i );
            assert( *randCur >= -1 && *randCur < count );
            if( *randCur != -1 )
            {
                it->rand = head + *randCur;
            }
            ++it;
        }
    }
}

void ListRand::serialize( std::ostream& stream )
{
    assert( stream.good() );
    stream << count << std::endl;
    
    auto first = findFirstNode();
    
    std::size_t currentDistance = 0;
    std::vector<int> distances;
    distances.resize( count, -1 );
    for( auto cur = head; cur != nullptr; cur = cur->next )
    {
        std::size_t index = cur - first;
        
        distances[index] = currentDistance;
        ++currentDistance;
        
    }
    
    for( auto cur = head; cur != nullptr; cur = cur->next )
    {
        auto relativeDistance = -1;
        if( cur->rand )
        {
            auto randIndex = cur->rand - first;
            relativeDistance = distances[randIndex];
        }
        
        stream << cur->data << std::endl;
        stream << relativeDistance << std::endl;
    }
}

void ListRand::deserialize( std::istream& stream )
{
    clear();
    stream >> count;
    assert( count >= 0 );
    
    if( count != 0 )
    {
        head = new ListNode[count];
        auto it = head;
        auto end = head + count;
        tail = end - 1;
        
        fillNode( it++, stream );
        
        while( it != end )
        {
            auto prev = it - 1;
            prev->next = it;
            it->prev = prev;
            fillNode( it++, stream );
        }
    }
}

void ListRand::fillNode( ListNode* it, std::istream& stream )
{
    std::ptrdiff_t rand = -1;
    
    stream >> it->data;
    stream >> rand;
    
    assert( rand < count );
    
    if( rand != -1 )
    {
        it->rand = head + rand;
    }
}

ListNode* ListRand::findFirstNode() const
{
    auto first = head;
    for( auto cur = head; cur != nullptr; cur = cur->next )
    {
        if( cur < first )
        {
            first = cur;
        }
    }
    
    return first;
}
