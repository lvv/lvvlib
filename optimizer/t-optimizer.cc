// WIP, not finished

// http://www.boost.org/doc/libs/1_35_0/libs/math/doc/sf_and_dist/html/math_toolkit/toolkit/internals1/minima.html
class   Variable { public:
        Variable (
            double _min,
            double _max,
            double _initial = min+(max-min)/2.0,
            double _step,   =     (max-min)10.0
        ):
            double min(_min),
            double max(_max),
            double initial(_initial),
            double step(_step)
        { public:
            double min;
            double max;
            double initial;
            double step;
        };
};

class   Space { public:
        Space ( Variable _X1,)                 { X.push_back(_X1); };
        Space ( Variable _X1, Variable _X2):   { X.push_back(_X1);  X.push_back(_X2); };
        vector<Variable>    X;
};



    
