    #include "stack.hpp"
    
    Turn_Queue::Turn_Queue()
        {
            first_out = nullptr;
        }

    void Turn_Queue::push(Turn* turn)
    {
        turn->next = first_out;
        first_out = turn;
    }

    void Turn_Queue::delete_first_out()
    {
        if(!this->is_empty())
        {
            Turn* temp = first_out;
            first_out = first_out->next;
            delete temp;
        }
    }

    bool Turn_Queue::is_empty()
    {
        return (first_out == nullptr);
    }