#ifndef Unit_h
#define Unit_h
class Unit {
protected:
    int id;
    int cost;
public:
    Unit(int i, int c ) {
        id = i;
        cost = c;
    }
    int getId()
     { return id;
     }
    int getCost() 
    { return cost; 
    }
   
};
#endif