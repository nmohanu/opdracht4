    #include "stack.hpp"
    
    Turn_Queue::Turn_Queue()
        {
            first_out = nullptr;
        }

    // Put a turn in the stack.
    void Turn_Queue::push(Turn* turn)
    {
        turn->next = first_out;
        first_out = turn;
    }

    // Delete the first out entry.
    void Turn_Queue::delete_first_out()
    {
        if(!this->is_empty())
        {
            Turn* temp = first_out;
            first_out = first_out->next;
            delete temp;
        }
    }

    // Check if stack is empty.
    bool Turn_Queue::is_empty()
    {
        return (first_out == nullptr);
    }