//
// Created by develop on 22.05.2022.
//

#include <iostream>
#include <fstream>

struct ListNode
{
    ListNode* prev;
    ListNode* next;
    ListNode* rand;
    std::string data;
    ListNode();
};

class ListRand
{

public:
    ListRand();
    
    ListRand( const ListRand& ) = delete;
    ListRand& operator=( const ListRand& ) = delete;
    ~ListRand();
    
    void init( std::initializer_list<int> rands );
    void clear();
    
    void serialize( std::ostream& stream );
    void deserialize( std::istream& stream );

private:
    ListNode* head;
    ListNode* tail;
    int count;
    
    void fillNode( ListNode* it, std::istream& stream );
    
};
